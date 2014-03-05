extern "C" {
#include <assert.h>
}
#include <math.h>

#include "follow.hpp"
#include "myhebp.hpp"
#include "system.hpp"
#include "fast2.hpp"
#include "mat.hpp"
#include "faces.hpp"
#include "search.hpp"
#include "vote.hpp"
#include "just.hpp"
#ifndef M_PI
#define M_PI       3.14159265358979323846
#endif

#define UseAngleCache
#define QuickOverlapZap
#define OrientationMerging
#define RotClassMerging

struct RandomTransform {
  double angle, x, y, scale;
  int flip;
  double *features;
};

#ifdef UseAngleCache
static int AngleCacheInitialized=0;
static int *AngleCache=NULL;
static double *LookupCos=NULL;
static double *LookupSin=NULL;

void InitializeAngleCache()
{
  AngleCache=new int[360*20*20*2];
  int *ptr=AngleCache;
  for (int a=0; a<360; a++)
    for (int y=-10; y<10; y++) 
      for (int x=-10; x<10; x++) {
        int xx=(int)floor((x+0.5)*cos(a*M_PI/180.0)-(y+0.5)*sin(a*M_PI/180.0));
        int yy=(int)floor((x+0.5)*sin(a*M_PI/180.0)+(y+0.5)*cos(a*M_PI/180.0));
        *(ptr++)=xx;
        *(ptr++)=yy;
      }
  LookupSin=new double[36];
  LookupCos=new double[36];
  for (int i=0; i<36; i++) {
    LookupCos[i]=cos(i*M_PI/18.0);
    LookupSin[i]=sin(i*M_PI/18.0);
  }
  AngleCacheInitialized=1;
}
#endif

void FreeRandomTransform(RandomTransform *rt)
{
  delete[] rt->features;
  delete rt;
}

double *CreateAngularHistogram(int num)
{
  double *hist=new double[num];
  for (int i=0; i<num; i++)
    hist[i]=0;
  return hist;
}

void DestroyAngularHistogram(double *hist)
{
  delete[] hist;
}

void PrintAngularHistogram(double *hist, int num, char *filename)
{
  FILE *outf=fopen(filename,"w");
  for (int i=0; i<num; i++) {
    fprintf(outf,"%d %g\n",i-180,hist[i]);
  }
  fprintf(outf,"%d %g\n",num-180,hist[0]);
  fclose(outf);
}

void NormalizeAngularHistogram(double *hist, int num, double val)
{
  if (val==0) {
    for (int i=0; i<num; i++) 
      if (fabs(hist[i])>val) val=fabs(hist[i]);
    if (val==0) val=1;
  }
  for (int i=0; i<num; i++)
    hist[i]/=val;
}

void SearchMultiAllOrientation(ByteImage *image, int numNetworks,
                               SearchCallback callback, ClientData data[],
                               int oneOrientation)
{
#ifdef UseAngleCache
  if (!AngleCacheInitialized) InitializeAngleCache();
#endif

  int ptr=0;
  Mat mat=Zero(3,3);
  ByteImage *mask=FindByteImageWithName("facemask");
  int halfW=mask->width/2;
  int halfH=mask->height/2;

  for (int j=-halfH; j<halfH; j++) for (int i=-halfW; i<halfW; i++) 
    if (mask->data(ptr++)) {
      mat(0,0)+=i*i;
      mat(0,1)+=i*j;
      mat(0,2)+=i;
      mat(1,0)+=i*j;
      mat(1,1)+=j*j;
      mat(1,2)+=j;
      mat(2,0)+=i;
      mat(2,1)+=j;
      mat(2,2)+=1;
    }
  mat=LUInverse(mat);

  int *tmp=new int[mask->size];

  Vec vec(3);
  double v0=0, v1=0, v2=0;
  double scale=1.0;
  int level=0;
  int hist[512];
  int map[512];

  int firstOrientation=oneOrientation;
  int lastOrientation=oneOrientation+20;

  if (oneOrientation==-1) {
    firstOrientation=0;
    lastOrientation=360;
  }

  while (image->height>=mask->height && image->width>=mask->width) {
    for (int y=0; y<image->height; y++) {
      for (int x=0; x<image->width; x++) {
        for (int angle=firstOrientation; angle<lastOrientation; angle+=20) {
          int ptr=0;
          v0=0; v1=0; v2=0;

#ifdef UseAngleCache
          int *aptr=AngleCache+(angle%360)*(20*20*2);
          for (int j=-halfH; j<halfH; j++) {
            for (int i=-halfW; i<halfW; i++) {
              int ii=x+(*(aptr++));
              int jj=y+(*(aptr++));
              if (ii<0) ii=0;
              if (jj<0) jj=0;
              if (ii>=image->width) ii=image->width-1;
              if (jj>=image->height) jj=image->height-1;
              int data=image->data(ii,jj);
              tmp[ptr]=data;
              if (mask->data(ptr++)) {
                v0+=i*data;
                v1+=j*data;
                v2+=data;
              }
            } 
          }
#else
          double a=angle*M_PI/180.0;
          for (int j=-halfH; j<halfH; j++) {
            for (int i=-halfW; i<halfW; i++) {
              double ii=x+(i+0.5)*cos(a)-(j+0.5)*sin(a)-0.5;
              double jj=y+(i+0.5)*sin(a)+(j+0.5)*cos(a)-0.5;
              int data=(int)(0.5+image->interpolateExtend(ii,jj));
#ifdef DEBUG
              if (x==DebugX && y==DebugY && level==DebugS) {
                int i2=i+x;
                if (i2<0) i2=0; if (i2>=image->width) i2=image->width-1;
                int j2=j+y;
                if (j2<0) j2=0; if (j2>=image->height) j2=image->height-1;
                fprintf(stderr,"i,j=%d,%d data=%d int=%d\n",i+x,j+y,data,
                        image->data(i2,j2));
              }
#endif
              tmp[ptr]=data;
              if (mask->data(ptr++)) {
                v0+=i*data;
                v1+=j*data;
                v2+=data;
              }
            } 
          }
#endif
          vec(0)=v0; vec(1)=v1; vec(2)=v2;
          vec=mat*vec;
          v0=vec(0); v1=vec(1); v2=vec(2);
          for (int i=0; i<512; i++) hist[i]=0;
          ptr=0;
          for (int j=-halfH; j<halfH; j++) for (int i=-halfW; i<halfW; i++) {
            int val=tmp[ptr]-(int)(i*v0+j*v1+v2-256.5);
            if (val<0) val=0;
            if (val>=512) val=511;
            if (mask->data(ptr)) hist[val]++;
            tmp[ptr++]=val;
          }
          int *to=map;
          int *from=hist;
          int total=0;
          for (int i=0; i<512; i++) {
            int old=total;
            total+=*(from++);
            *(to++)=old+total;
          }
          double scaleFactor=1.0/total;
          FastForwardUnit *unit=&(real_fast_list[0]->unitList[1]);
          for (int i=0; i<mask->size; i++)
            (unit++)->activation=map[tmp[i]]*scaleFactor-1.0;
          
          for (int i=0; i<numNetworks; i++) {
            if (i>0) {
              FastForwardUnit *unit=&(real_fast_list[0]->unitList[1]);
              FastForwardUnit *unit1=&(real_fast_list[i]->unitList[1]);
              for (int j=0; j<mask->size; j++)
                (unit1++)->activation=(unit++)->activation;
            }
            double output=FastForwardPass(real_fast_list[i]);
#ifdef DEBUG
            if (x==DebugX && y==DebugY && level==DebugS) {
              fprintf(stderr,"output=%g\n",output);
              exit(1);
            }
#endif
            if (output>0) {
              callback(data[i],image,x-halfW,y-halfH,mask->width,mask->height,
                       level,scale,output,angle);
            }
          }
        }
      }
    }
    ReduceSize(image,image);
    scale*=1.2;
    level++;
  }
  delete[] tmp;
}

void SearchMultiOrientation(ByteImage *image, int numNetworks, int rotationNet,
			    SearchCallback callback, ClientData data[],
                            double threshold)
{
#ifdef UseAngleCache
  if (!AngleCacheInitialized) InitializeAngleCache();
#endif

  int ptr=0;
  Mat mat=Zero(3,3);
  ByteImage *mask=FindByteImageWithName("facemask");
  int halfW=mask->width/2;
  int halfH=mask->height/2;

  for (int j=-halfH; j<halfH; j++) for (int i=-halfW; i<halfW; i++) 
    if (mask->data(ptr++)) {
      mat(0,0)+=i*i;
      mat(0,1)+=i*j;
      mat(0,2)+=i;
      mat(1,0)+=i*j;
      mat(1,1)+=j*j;
      mat(1,2)+=j;
      mat(2,0)+=i;
      mat(2,1)+=j;
      mat(2,2)+=1;
    }
  mat=LUInverse(mat);

  int *tmp=new int[mask->size];

  Vec vec(3);
  double v0=0, v1=0, v2=0;
  double scale=1.0;
  int level=0;
  while (image->height>=mask->height && image->width>=mask->width) {
    for (int y=0; y<image->height; y++) {
      for (int x=0; x<image->width; x++) {
        int ptr=0;
        v0=0; v1=0; v2=0;
        int hist[512];
        for (int i=0; i<256; i++) hist[i]=0;
        if (x-halfW>=0 && y-halfH>=0 &&
            x+halfW<=image->width && y+halfH<=image->height) {
          for (int iy=y-halfH; iy<y+halfH; iy++)
            for (int ix=x-halfW; ix<x+halfW; ix++) {
              int val=image->data(ix,iy);
              tmp[ptr++]=val;
	      hist[val]++;
            }
        } else {
          for (int iy=y-halfH; iy<y+halfH; iy++)
            for (int ix=x-halfW; ix<x+halfW; ix++) {
              int ii=ix; if (ii<0) ii=0;
              if (ii>=image->width) ii=image->width-1;
              int jj=iy; if (jj<0) jj=0;
              if (jj>=image->height) jj=image->height-1;
              int val=image->data(ii,jj);
              tmp[ptr++]=val;
	      hist[val]++;
            }
        }
        int map[512];
	int *to=map;
	int *from=hist;
	int tot=0;
	for (int i=0; i<256; i++) {
	  int old=tot;
	  tot+=*(from++);
	  *(to++)=old+tot;
	}
        double scaleFactor=1.0/tot;
        FastForwardUnit *unit=&(real_fast_list[rotationNet]->unitList[1]);
        for (int i=0; i<mask->size; i++)
          (unit++)->activation=map[tmp[i]]*scaleFactor-1.0;
	FastForwardPass(real_fast_list[rotationNet]);
	unit=real_fast_list[rotationNet]->unitList+
	  real_fast_list[rotationNet]->firstOutput;
	double a1=0, a2=0;
	for (int j=0; j<36; j++) {
	  double act=(unit++)->activation;
#ifdef UseAngleCache
	  a1+=act*LookupCos[j];
	  a2+=act*LookupSin[j];
#else
	  a1+=act*cos(j*M_PI/18);
	  a2+=act*sin(j*M_PI/18);
#endif
	}
	double a=-atan2(a2,a1);

	ptr=0;
        v0=0; v1=0; v2=0;
#ifdef UseAngleCache
        int ia=((int)(a*180.0/M_PI+360))%360;
        int *aptr=AngleCache+(ia*20*20*2);
        for (int j=-halfH; j<halfH; j++) {
          for (int i=-halfW; i<halfW; i++) {
            int ii=x+(*(aptr++));
            int jj=y+(*(aptr++));
            if (ii<0) ii=0;
            if (jj<0) jj=0;
            if (ii>=image->width) ii=image->width-1;
            if (jj>=image->height) jj=image->height-1;
            int data=image->data(ii,jj);
            tmp[ptr]=data;
            if (mask->data(ptr++)) {
              v0+=i*data;
              v1+=j*data;
              v2+=data;
            }
          } 
        }
#else
        for (int j=-halfH; j<halfH; j++) {
          for (int i=-halfW; i<halfW; i++) {
            double ii=x+(i+0.5)*cos(a)-(j+0.5)*sin(a)-0.5;
            double jj=y+(i+0.5)*sin(a)+(j+0.5)*cos(a)-0.5;
	    int data=(int)(0.5+image->interpolateExtend(ii,jj));
	    tmp[ptr]=data;
	    if (mask->data(ptr++)) {
	      v0+=i*data;
	      v1+=j*data;
	      v2+=data;
	    }
	  } 
	}
#endif
        vec(0)=v0; vec(1)=v1; vec(2)=v2;
        vec=mat*vec;
        v0=vec(0); v1=vec(1); v2=vec(2);
        for (int i=0; i<512; i++) hist[i]=0;
        ptr=0;
        for (int j=-halfH; j<halfH; j++) for (int i=-halfW; i<halfW; i++) {
          int val=tmp[ptr]-(int)(i*v0+j*v1+v2-256.5);
          if (val<0) val=0;
          if (val>=512) val=511;
          if (mask->data(ptr)) hist[val]++;
          tmp[ptr++]=val;
        }
        to=map;
        from=hist;
        int total=0;
        for (int i=0; i<512; i++) {
          int old=total;
          total+=*(from++);
          *(to++)=old+total;
        }
        scaleFactor=1.0/total;
        unit=&(real_fast_list[0]->unitList[1]);
        for (int i=0; i<mask->size; i++)
          (unit++)->activation=map[tmp[i]]*scaleFactor-1.0;
	
        for (int i=0; i<numNetworks; i++) {
          if (i>0) {
            FastForwardUnit *unit=&(real_fast_list[0]->unitList[1]);
            FastForwardUnit *unit1=&(real_fast_list[i]->unitList[1]);
            for (int j=0; j<mask->size; j++)
              (unit1++)->activation=(unit++)->activation;
          }
          double output=FastForwardPass(real_fast_list[i]);
          if (output>threshold) {
            callback(data[i],image,x-halfW,y-halfH,mask->width,mask->height,
                     level,scale,output,(int)floor(0.5+a*180.0/M_PI));
            //            fprintf(stderr,"x=%d,y=%d:\n",x,y);
            //            FastDebugNetwork(real_fast_list[i]);
            //            exit(0);
          }
        }
      }
    }
    ReduceSize(image,image);
    scale*=1.2;
    level++;
  }
  delete[] tmp;
}

double ApplyDerotationDetection(ByteImage *image, int net, int x, int y, 
                                double a)
{
  if (!AngleCacheInitialized) InitializeAngleCache();

  int ptr=0;
  Mat mat=Zero(3,3);
  ByteImage *mask=FindByteImageWithName("facemask");
  int halfW=mask->width/2;
  int halfH=mask->height/2;

  for (int j=-halfH; j<halfH; j++) for (int i=-halfW; i<halfW; i++) 
    if (mask->data(ptr++)) {
      mat(0,0)+=i*i;
      mat(0,1)+=i*j;
      mat(0,2)+=i;
      mat(1,0)+=i*j;
      mat(1,1)+=j*j;
      mat(1,2)+=j;
      mat(2,0)+=i;
      mat(2,1)+=j;
      mat(2,2)+=1;
    }
  mat=LUInverse(mat);

  int *tmp=new int[mask->size];

  Vec vec(3);
  double v0=0, v1=0, v2=0;

  int hist[512];
  for (int i=0; i<512; i++) hist[i]=0;

  int ia=((int)(a+360.5))%360;
  int *aptr=AngleCache+(ia*20*20*2);
  ptr=0;
  for (int j=-halfH; j<halfH; j++) {
    for (int i=-halfW; i<halfW; i++) {
      int ii=x+(*(aptr++));
      int jj=y+(*(aptr++));
      if (ii<0) ii=0;
      if (jj<0) jj=0;
      if (ii>=image->width) ii=image->width-1;
      if (jj>=image->height) jj=image->height-1;
      int data=image->data(ii,jj);
      tmp[ptr]=data;
      if (mask->data(ptr++)) {
        v0+=i*data;
        v1+=j*data;
        v2+=data;
      }
    } 
  }
  vec(0)=v0; vec(1)=v1; vec(2)=v2;
  vec=mat*vec;
  v0=vec(0); v1=vec(1); v2=vec(2);
  ptr=0;
  for (int j=-halfH; j<halfH; j++) for (int i=-halfW; i<halfW; i++) {
    int val=tmp[ptr]-(int)(i*v0+j*v1+v2-256.5);
    if (val<0) val=0;
    if (val>=512) val=511;
    if (mask->data(ptr)) hist[val]++;
    tmp[ptr++]=val;
  }
  int map[512];
  int *to=map;
  int *from=hist;
  int total=0;
  for (int i=0; i<512; i++) {
    int old=total;
    total+=*(from++);
    *(to++)=old+total;
  }
  double scaleFactor=1.0/total;
  FastForwardUnit *unit=&(real_fast_list[net]->unitList[1]);
  for (int i=0; i<mask->size; i++)
    (unit++)->activation=map[tmp[i]]*scaleFactor-1.0;
	
  double output=FastForwardPass(real_fast_list[net]);
  delete[] tmp;
  return output;
}

CheckResultsStruct *CheckResultsDirect2(char *canvas,
                                        ByteImage *image, char *imageFile, 
                                        List<Detection> *detections, 
                                        Tcl_HashTable *answers, 
                                        ByteImage *mask, 
                                        int angleLimit)
{
  int lw=3;
  int temWidth=image->width, temHeight=image->height;
  int numScales=0, examples=0;
  while (temWidth>=mask->width && temHeight>=mask->height)
  {
    examples+=(temWidth-mask->width+1)*(temHeight-mask->height+1);
    temWidth=(int)(floor(temWidth/1.2));
    temHeight=(int)(floor(temHeight/1.2));
    numScales++;
  }

  Tcl_HashEntry *entry=Tcl_FindHashEntry(answers,imageFile);
  List<Detection> *answerList=NULL;

  int *faceFound=NULL;
  int numFaces=0;
  if (entry!=NULL) {
    answerList=(List<Detection>*)Tcl_GetHashValue(entry);
    numFaces=answerList->length;
    faceFound=new int[numFaces];
    int ptr=0;
    for (Detection *d=answerList->first; d!=NULL; d=d->next) {
      // Hack to preserve behavior of the old CheckResultDirect,
      // not really necessary any more.
//      LimitScale(0,numScales-1,&d->s,&d->x,&d->y);
      faceFound[ptr++]=0;
      int s=d->s;
      int xx=d->x;
      int yy=d->y;
      double xcenter=xx*pow(1.2,s);
      double ycenter=yy*pow(1.2,s);
#ifndef NoTcl
      char cmd[512];
      sprintf(cmd,"%s create oval %g %g %g %g -fill blue -outline blue"
              " -tag real",
              canvas,xcenter-1,ycenter-1,xcenter+1,ycenter+1);
//      Tcl_Eval(theInterp,cmd);
#endif
    }
  }

  int falsePos=0;
  for (Detection *detect=detections->first; detect!=NULL; 
       detect=detect->next) {
    int found=0;
    if (answerList!=NULL) {
      int ptr=0;
      for (Detection *answer=answerList->first; answer!=NULL && !found;
           answer=answer->next, ptr++) {
        int dx=(int)floor(0.5+(detect->x+mask->width/2)*
                          pow(1.2,detect->s-answer->s));
        int dy=(int)floor(0.5+(detect->y+mask->height/2)*
                          pow(1.2,detect->s-answer->s));
        int angle=detect->orient-answer->orient;
        if (angle<0) angle+=360*(-angle/360+1);
        angle=angle % 360;
        if (angle>180) angle=360-angle;

//        fprintf(stderr,"x = %d\n",abs(dx-answer->x));
//        fprintf(stderr,"y = %d\n",abs(dy-answer->y));
//        fprintf(stderr,"s = %d\n",abs(detect->s-answer->s));
//        fprintf(stderr,"angle = %d  ( %d %d )\n",angle,detect->orient,answer->orient);
        if (abs(dx-answer->x)<=4 &&
            abs(dy-answer->y)<=4 &&
            abs(detect->s-answer->s)<=4 &&
//            detect->s>=answerScale-2 && detect->s<=answerScale+2 &&
            angle<30) {
//          fprintf(stderr,"Found!!!\n");
          found=1;
          faceFound[ptr]=1;
        }
      }
    }
    if (!found) falsePos++;
  }

  int falseNeg=0, detectableFaces=0;
  if (faceFound!=NULL) {
    Detection *answer=answerList->first;
    for (int i=0; i<numFaces; i++, answer=answer->next) {
      if (angleLimit!=-1) {
        int angle=answer->orient;
        while (angle<-180) angle+=360;
        while (angle>=180) angle-=360;
        if (abs(angle)>angleLimit) continue;
      }
      if (!faceFound[i]) {
        falseNeg++;
      }
      detectableFaces++;
    }
    delete[] faceFound;
  }
              
  CheckResultsStruct *results=new CheckResultsStruct;
  results->falseNeg=falseNeg;
  results->numFaces=detectableFaces;
  results->falsePos=falsePos;
  results->examples=examples;
  return results;
}

void CheckSearchInstrumentedDirect2(int numScales, char *imageFile,
                                    Tcl_HashTable *answers, ByteImage *mask,
                                    char *tradeName)
{
  FILE *outf=fopen(tradeName,"w");

  ByteImage **outputScale=new ByteImage*[numScales];
  ByteImage **inputScale=new ByteImage*[numScales];
  for (int i=0; i<numScales; i++) {
    char name[256];
    sprintf(name,"output%d",i);
    outputScale[i]=FindByteImageWithName(name);
//    FILE *img=fopen(name,"w");
//    SaveByteImagePgm(outputScale[i],img);
//    fclose(img);
    sprintf(name,"input%d",i);
    inputScale[i]=new ByteImage(name);
    inputScale[i]->ZeroBuffer(outputScale[i]->width,
                              outputScale[i]->height);
  }
  int numFaces=0;

  int facesFound[201];
  int falseAlarms[201];
  int numVal[201];
  for (int t=0; t<=200; t++) {
    facesFound[t]=0;
    falseAlarms[t]=0;
    numVal[t]=0;
  }

  Tcl_HashEntry *entry=Tcl_FindHashEntry(answers,imageFile);
  if (entry!=NULL) {
    List<Detection> *answerList=(List<Detection>*)Tcl_GetHashValue(entry);
    for (Detection *d=answerList->first; d!=NULL; d=d->next) {
      int angle=d->orient;
      while (angle<-180) angle+=360;
      while (angle>=180) angle-=360;
      if (abs(angle)>40) continue;
      numFaces++;
      int min=255;
//      fprintf(stderr,"Trying to look at %d,%d,%d\n",
//              d->x,d->y,d->s);
      for (int scale=d->s-4; scale<=d->s+4; scale++) {
        if (scale>=0 && scale<numScales) {
          int x1=(int)floor((d->x-4.5)*pow(1.2,d->s-scale));
          int x2=(int)ceil((d->x+4.5)*pow(1.2,scale-d->s));
          int y1=(int)floor((d->y-4.5)*pow(1.2,d->s-scale));
          int y2=(int)ceil((d->y+4.5)*pow(1.2,scale-d->s));
          for (int y=y1; y<=y2; y++) for (int x=x1; x<=x2; x++) {
//            fprintf(stderr,"%d,%d,%d -> %d,%d,%d\n",
//                    d->x,d->y,d->s,x,y,scale);
            int dx=(int)floor(0.5+x*pow(1.2,scale-d->s));
            int dy=(int)floor(0.5+y*pow(1.2,scale-d->s));
            if (abs(dx-d->x)<=4 && abs(dy-d->y)<=4) {
              if (x>=0 && y>=0 && 
                  x<outputScale[scale]->width && 
                  y<outputScale[scale]->height) {
//                fprintf(stderr,"%d,%d,%d -> %d,%d,%d\n",
//                        d->x,d->y,d->s,x,y,scale);
                if (outputScale[scale]->data(x,y)<min) 
                  min=outputScale[scale]->data(x,y);
                inputScale[scale]->data(x,y)=1;
              }
            }
          }
        }
      }
      if (min==255) {
        fprintf(stderr,"(%d,%d,%d)=%d\n",
                d->x,d->y,d->s,
                min);
        for (int scale=0; scale<numScales; scale++) {
          char name[256];
          sprintf(name,"trash%d",scale);
          FILE *img=fopen(name,"w");
          assert(img!=NULL);
          SaveByteImagePgm(outputScale[scale],img);
          fclose(img);
        }
        exit(1);
      }
      for (int t=0; t<=min; t++) 
        facesFound[t]++;
    }
  }

  for (int scale=0; scale<numScales; scale++) 
    for (int y=10; y<outputScale[scale]->height-9; y++) 
      for (int x=10; x<outputScale[scale]->width-9; x++) {
//        fprintf(stderr,"%d,%d,%d %d %d\n",x,y,scale,outputScale[scale]->width,outputScale[scale]->height);
        int val=outputScale[scale]->data(x,y);
        if (val>=200) {
          FILE *img=fopen("/tmp/trash","w");
          assert(img!=NULL);
          SaveByteImagePgm(outputScale[scale],img);
          fprintf(stderr,"Yes, I gneerated it !!!!!!\n");
          fprintf(stderr,"error code for close=%d\n",fclose(img));
          fprintf(stderr,"%d,%d,%d=%d\n",x,y,scale,val);
        }
        numVal[val]++;
        if (inputScale[scale]->data(x,y)==0) 
          for (int t=0; t<=outputScale[scale]->data(x,y); t++) 
            falseAlarms[t]++;
      }

  for (int t=200; t>=0; t--) {
    fprintf(outf,"%.2f %d %d %d\n",
            (t-100)/100.0,numVal[t],falseAlarms[t],numFaces-facesFound[t]);
  }
  for (int i=0; i<numScales; i++) {
    delete inputScale[i];
    delete outputScale[i];
  }
  delete[] inputScale;
  delete[] outputScale;
  fclose(outf);
}

// Set a value in the detection pyramid; if that location does not exist,
// then create it.  Also, add that location to the list of locations with
// that value.  
static void FuzzyVoteAccumInc2(Tcl_HashTable *accum, 
                               int x, int y, int s, int d, int p)
{
  int loc[5];
#ifdef OrientationMerging
  while (d<0) d+=36; d=d%36;
#endif
  loc[0]=x; loc[1]=y; loc[2]=s; loc[3]=d; loc[4]=p;
  Tcl_HashEntry *entry=Tcl_FindHashEntry(accum,(char*)loc);
  if (entry==NULL) {
    int newentry;
    entry=Tcl_CreateHashEntry(accum,(char*)loc,&newentry);
    Tcl_SetHashValue(entry,(char*)1);
  } else {
    int val=1+(int)Tcl_GetHashValue(entry);
    Tcl_SetHashValue(entry,(char*)val);
  }
}

// Set a value in the detection pyramid; if that location does not exist,
// then create it.  Also, add that location to the list of locations with
// that value.  
static void FuzzyVoteAccumZero2(Tcl_HashTable *accum, 
                                int x, int y, int s, int d, int p)
{
  int loc[5];
#ifdef OrientationMerging
  while (d<0) d+=36; d=d%36;
#endif
  loc[0]=x; loc[1]=y; loc[2]=s; loc[3]=d; loc[4]=p;
  Tcl_HashEntry *entry=Tcl_FindHashEntry(accum,(char*)loc);
  if (entry!=NULL) {
    Tcl_SetHashValue(entry,(char*)0);
  }
}

// Get the value of some location in the detection pyramid.  If that location
// does not exist, then return zero (but do not allocate that location).
static int FuzzyVoteAccumGet2(Tcl_HashTable *accum, 
                                int x, int y, int s, int d, int p)
{
  int loc[5];
#ifdef OrientationMerging
  while (d<0) d+=36; d=d%36;
#endif
  loc[0]=x; loc[1]=y; loc[2]=s; loc[3]=d; loc[4]=p;
  Tcl_HashEntry *entry=Tcl_FindHashEntry(accum,(char*)loc);
  if (entry==NULL) return 0;
  return (int)Tcl_GetHashValue(entry);
}

// Given some point in the detection pyramid, locate all 6-connection 
// locations with a value greater than or equal to the specified amount,
// and find their centroid.  The locations in the centroid are set to zero.
// Centroid in scale is computed by averaging the pyramid levels at which
// the faces are detected.
static void FindCentroidAccum2(Tcl_HashTable *accum,
                               int s, int x, int y, int d, int p,
                               int minVal, 
                               double *totalS, double *totalX, double *totalY,
                               double *total)
{
  int value=FuzzyVoteAccumGet2(accum,x,y,s,d,p);
//  fprintf(stderr,"val=%d, min=%d\n",value,minVal);
  if (value>=minVal) {
    fprintf(stderr,"adding %d,%d,%d,%d,%d\n",x,y,s,d,p);
    FuzzyVoteAccumZero2(accum,x,y,s,d,p);
    double rvalue=value;
    (*total)+=rvalue;
    (*totalS)+=s*rvalue;
    (*totalX)+=x*pow(1.2,s)*rvalue;
    (*totalY)+=y*pow(1.2,s)*rvalue;
    FindCentroidAccum2(accum,s,x,y,d,p-1,minVal,
                       totalS,totalX,totalY,total);
    FindCentroidAccum2(accum,s,x,y,d,p+1,minVal,
                       totalS,totalX,totalY,total);
    FindCentroidAccum2(accum,s,x,y,d-1,p,minVal,
                       totalS,totalX,totalY,total);
    FindCentroidAccum2(accum,s,x,y,d+1,p,minVal,
                       totalS,totalX,totalY,total);
    FindCentroidAccum2(accum,s,x+1,y,d,p,minVal,
                       totalS,totalX,totalY,total);
    FindCentroidAccum2(accum,s,x-1,y,d,p,minVal,
                       totalS,totalX,totalY,total);
    FindCentroidAccum2(accum,s,x,y+1,d,p,minVal,
                       totalS,totalX,totalY,total);
    FindCentroidAccum2(accum,s,x,y-1,d,p,minVal,
                       totalS,totalX,totalY,total);
    FindCentroidAccum2(accum,
                       s-1,(int)floor(0.5+x*1.2),(int)floor(0.5+y*1.2),d,p,
                       minVal,totalS,totalX,totalY,total);
    FindCentroidAccum2(accum,
                       s+1,(int)floor(0.5+x/1.2),(int)floor(0.5+y/1.2),d,p,
                       minVal,totalS,totalX,totalY,total);
  }
}

// New arbitration procedure.  Slower and takes more memory than (say)
// FuzzyVote2Direct, but is useful for the router networks because it
// keeps track of which view each detection is associated with, and
// counts that as part of the position of the detection.  Thus, only
// detections of the same view at the same location reinforce one another.
// (However, overlap removal will remove detections which overlap with each
// other but have different views.)
void NewFuzzyVote2(List<Detection> *outputList, 
                   List<Detection> *inputList, int numInputLists,
                   int width, int height, int maskWidth, int maskHeight,
                   int spread, int threshold, int overlap)
{
  // Hash table represents which locations/scales in the detection are
  // filled in, and with what values.  Any missing entries are assumed
  // to be zero.
  Tcl_HashTable accum;
  Tcl_InitHashTable(&accum,5);

  // Compute number of levels in input pyramid
  int temWidth=width, temHeight=height;
  int numScales=0;
  while (temWidth>=maskWidth && temHeight>=maskHeight) {
    temWidth=(int)(floor(temWidth/1.2));
    temHeight=(int)(floor(temHeight/1.2));
    numScales++;
  }

  // For each detection list given as input (all detections are treated
  // equally)

  for (int num=0; num<numInputLists; num++) {
    // For each detection
    for (Detection *detect=inputList[num].first; detect!=NULL;
         detect=detect->next) {
//      fprintf(stderr,"I");
      int xc=detect->x, yc=detect->y, s=detect->s, d=detect->orient;
#ifdef OrientationMerging
      d=(int)floor(0.5+0.1*d);
#endif
      // Spread out the detection in both scale and location by 
      // "spread" levels or pixels, incrementing the value of each
      // location in the detection pyramid
      for (int si=-spread; si<=spread; si++) {
        if (si+s<0 || si+s>=numScales) continue;
        int xci=(int)floor(0.5+xc*exp(log(1.2)*-si));
        int yci=(int)floor(0.5+yc*exp(log(1.2)*-si));
        for (int xx=xci-spread; xx<=xci+spread; xx++)
          for (int yy=yci-spread; yy<=yci+spread; yy++)
            for (int o=d-spread; o<=d+spread; o++)
              FuzzyVoteAccumInc2(&accum,xx,yy,s+si,o,0);
      }
    }
  }
//  fprintf(stderr,"\n");

  for (int num=0; num<numInputLists; num++) {
    // For each detection
    for (Detection *detect=inputList[num].first; detect!=NULL;
         detect=detect->next) {
//      fprintf(stderr,"M");
      int xc=detect->x, yc=detect->y, s=detect->s, d=detect->orient;
#ifdef OrientationMerging
      d=(int)floor(0.5+0.1*d);
#endif
      detect->output=0;
      // Spread out the detection in both scale and location by 
      // "spread" levels or pixels, incrementing the value of each
      // location in the detection pyramid
      for (int si=-spread; si<=spread; si++) {
        if (si+s<0 || si+s>=numScales) continue;
        int xci=(int)floor(0.5+xc*exp(log(1.2)*-si));
        int yci=(int)floor(0.5+yc*exp(log(1.2)*-si));
        for (int xx=xci-spread; xx<=xci+spread; xx++)
          for (int yy=yci-spread; yy<=yci+spread; yy++)
            for (int o=d-spread; o<=d+spread; o++) {
              int conf=FuzzyVoteAccumGet2(&accum,xx,yy,s+si,o,0);
              if (conf>detect->output) {
                detect->output=conf+0.5;
                detect->x=xx;
                detect->y=yy;
                detect->s=s+si;
                detect->orient=o;
              }
            }
      }
    }
  }
//  fprintf(stderr,"\n");

  for (int num=1; num<numInputLists; num++)
    inputList[0].append(&(inputList[num]));
//  fprintf(stderr,"S(%d)",inputList[0].length);
  inputList[0].sort(CompareDetections);
//  fprintf(stderr,"\n");

  outputList->deleteNodes();

  // Scan through the detection pyramid from highest to lowest value
  while (!inputList[0].empty() && inputList[0].first->output>=threshold) {
    Detection *detect=inputList[0].first;
//    fprintf(stderr,"Z(%g)",detect->output);
//    fprintf(stderr,"%d,%d s %d o %d c %g\n",
//            detect->x,detect->y,detect->s,detect->orient,detect->output);
    // Get the detection
    int x=detect->x;
    int y=detect->y;
    int s=detect->s;
    int d=detect->orient;
    int cs, cx, cy;
    double total=0.0;
    double totalS=0, totalX=0, totalY=0;
// Find the centroid of detections around this location
    FindCentroidAccum2(&accum,s,x,y,d,0,(int)floor(detect->output),
                       &totalS,&totalX,&totalY,&total);
//    fprintf(stderr,"centroid %g %g %g / %g\n",
//            totalX,totalY,totalS,total);
    cs=(int)floor(0.5+totalS/total);
    cx=(int)floor(0.5+totalX/total*pow(1.2,-cs));
    cy=(int)floor(0.5+totalY/total*pow(1.2,-cs));
//    fprintf(stderr,"centroid %d %d %d\n",cx,cy,cs);
//    cs=s;
//    cx=x;
//    cy=y;
    // If we are to remove overlapping detections, scan through
    // the detection pyramid, removing all possible overlaps
    if (overlap) {
      Detection *elem=inputList[0].first;
      while (elem!=NULL) {
        Detection *next=elem->next;
        int xpos=(int)floor(0.5+cx*pow(1.2,cs-elem->s));
        int ypos=(int)floor(0.5+cy*pow(1.2,cs-elem->s));
        int sizex=maskWidth/2+
          (int)floor(0.5+maskWidth/2*pow(1.2,cs-elem->s));
        int sizey=maskHeight/2+
          (int)floor(0.5+maskHeight/2*pow(1.2,cs-elem->s));
//        if (elem==detect) {
//          fprintf(stderr,"match %d,%d %dx%d %d,%d %d,%d,%d\n",
//                  xpos,ypos,sizex,sizey,cx,cy,elem->x,elem->y,elem->s);
//        }
        if (elem->x>=xpos-sizex && elem->x<=xpos+sizex &&
            elem->y>=ypos-sizey && elem->y<=ypos+sizey) {
//          fprintf(stderr,"Deleted\n");
          inputList[0].deleteNode(elem);
        }
        elem=next;
      }
    }
    
    // Record the detection
#ifdef OrientationMerging
    outputList->addLast(new Detection(cx,cy,cs,1,d*10));
#else
    outputList->addLast(new Detection(cx,cy,cs,1,d));
#endif
  }
//  fprintf(stderr,"\n");
  // Clean up
  Tcl_DeleteHashTable(&accum);
}

// New arbitration procedure.  Slower and takes more memory than (say)
// FuzzyVote2Direct, but is useful for the router networks because it
// keeps track of which view each detection is associated with, and
// counts that as part of the position of the detection.  Thus, only
// detections of the same view at the same location reinforce one another.
// (However, overlap removal will remove detections which overlap with each
// other but have different views.)
void NewFuzzyVote3(List<Detection> *outputList, 
                   List<Detection> *inputList, int numInputLists,
                   int width, int height, int maskWidth, int maskHeight,
                   int spread, int threshold, int overlap)
{
  // Hash table represents which locations/scales in the detection are
  // filled in, and with what values.  Any missing entries are assumed
  // to be zero.
  Tcl_HashTable accum;
  Tcl_InitHashTable(&accum,5);

  // Compute number of levels in input pyramid
  int temWidth=width, temHeight=height;
  int numScales=0;
  while (temWidth>=maskWidth && temHeight>=maskHeight) {
    temWidth=(int)(floor(temWidth/1.2));
    temHeight=(int)(floor(temHeight/1.2));
    numScales++;
  }

  // For each detection list given as input (all detections are treated
  // equally)

  for (int num=0; num<numInputLists; num++) {
    // For each detection
    for (Detection *detect=inputList[num].first; detect!=NULL;
         detect=detect->next) {
//      fprintf(stderr,"I");
      int xc=detect->x, yc=detect->y, s=detect->s, d=detect->orient;
#ifdef OrientationMerging
      d=(int)floor(0.5+0.1*d);
#endif
      FuzzyVoteAccumInc2(&accum,xc,yc,s,d,detect->profile);
    }
  }
//  fprintf(stderr,"\n");

  for (int num=0; num<numInputLists; num++) {
    // For each detection
    for (Detection *detect=inputList[num].first; detect!=NULL;
         detect=detect->next) {
//      fprintf(stderr,"M");
      int xc=detect->x, yc=detect->y, s=detect->s, d=detect->orient, 
        p=detect->profile;
//      fprintf(stderr,"Before: %d",d);
#ifdef OrientationMerging
      d=(int)floor(0.5+0.1*d);
#endif
      detect->output=0;
      // Spread out the detection in both scale and location by 
      // "spread" levels or pixels, incrementing the value of each
      // location in the detection pyramid
      double tx=0, ty=0, ts=0, tax=0, tay=0, tot=0, tp=0;
      for (int si=-spread; si<=spread; si++) {
        if (si+s<0 || si+s>=numScales) continue;
        int xci=(int)floor(0.5+xc*exp(log(1.2)*-si));
        int yci=(int)floor(0.5+yc*exp(log(1.2)*-si));
        for (int xx=xci-spread; xx<=xci+spread; xx++)
          for (int yy=yci-spread; yy<=yci+spread; yy++)
            for (int o=d-spread; o<=d+spread; o++) {
              for (int pp=p-1; pp<=p+1; pp++) {
                double val=FuzzyVoteAccumGet2(&accum,xx,yy,s+si,o,pp);
                if (val>0) {
                  tot+=val;
                  tx+=val*xx*pow(1.2,s+si);
                  ty+=val*yy*pow(1.2,s+si);
                  ts+=val*s;
                  tax+=val*cos(o*10.0*M_PI/180.0);
                  tay+=val*sin(o*10.0*M_PI/180.0);
                  tp+=val*pp;
                }
              }
            }
      }
      detect->output=tot;
      detect->s=(int)floor(0.5+ts/tot);
      detect->x=(int)floor(0.5+tx/tot*pow(1.2,-detect->s));
      detect->y=(int)floor(0.5+ty/tot*pow(1.2,-detect->s));
      detect->orient=(int)floor(0.5+180.0/M_PI*atan2(tay,tax));
      detect->profile=(int)floor(0.5+tp/tot);
//      fprintf(stderr,"   After: %d\n",detect->orient);
    }
  }
//  fprintf(stderr,"\n");

  for (int num=1; num<numInputLists; num++)
    inputList[0].append(&(inputList[num]));
//  fprintf(stderr,"S(%d)",inputList[0].length);
  inputList[0].sort(CompareDetections);
//  fprintf(stderr,"\n");

  outputList->deleteNodes();

  // Scan through the detection pyramid from highest to lowest value
  while (!inputList[0].empty() && inputList[0].first->output>=threshold) {
    Detection *detect=inputList[0].first;
//    fprintf(stderr,"Z(%g)",detect->output);
//    fprintf(stderr,"%d,%d s %d o %d c %g\n",
//            detect->x,detect->y,detect->s,detect->orient,detect->output);
    // Get the detection
    int x=detect->x;
    int y=detect->y;
    int s=detect->s;
    int d=detect->orient;
    int p=detect->profile;
    double conf=detect->output;
#ifdef OrientationMerging
    d=(int)floor(0.5+0.1*d);
#endif
    int cs, cx, cy;
    double total=0.0;
    double totalS=0, totalX=0, totalY=0;
// Find the centroid of detections around this location
//    FindCentroidAccum2(&accum,s,x,y,d,1,
//                       &totalS,&totalX,&totalY,&total);
//    fprintf(stderr,"centroid %g %g %g / %g\n",
//            totalX,totalY,totalS,total);
//    cs=(int)floor(0.5+totalS/total);
//    cx=(int)floor(0.5+totalX/total*pow(1.2,-cs));
//    cy=(int)floor(0.5+totalY/total*pow(1.2,-cs));
//    fprintf(stderr,"centroid %d %d %d\n",cx,cy,cs);
    cs=s;
    cx=x;
    cy=y;
    // If we are to remove overlapping detections, scan through
    // the detection pyramid, removing all possible overlaps
    if (overlap) {
      Detection *elem=inputList[0].first;
      while (elem!=NULL) {
        Detection *next=elem->next;
        int xpos=(int)floor(0.5+cx*pow(1.2,cs-elem->s));
        int ypos=(int)floor(0.5+cy*pow(1.2,cs-elem->s));
        int sizex=maskWidth/2+
          (int)floor(0.5+maskWidth/2*pow(1.2,cs-elem->s));
        int sizey=maskHeight/2+
          (int)floor(0.5+maskHeight/2*pow(1.2,cs-elem->s));
//        if (elem==detect) {
//          fprintf(stderr,"match %d,%d %dx%d %d,%d %d,%d,%d\n",
//                  xpos,ypos,sizex,sizey,cx,cy,elem->x,elem->y,elem->s);
//        }
        if (elem->x>=xpos-sizex && elem->x<=xpos+sizex &&
            elem->y>=ypos-sizey && elem->y<=ypos+sizey) {
//          fprintf(stderr,"Deleted\n");
          inputList[0].deleteNode(elem);
        }
        elem=next;
      }
    } else {
      inputList[0].deleteNode(detect);
    }
    
    // Record the detection
#ifdef OrientationMerging
    outputList->addLast(new Detection(cx,cy,cs,conf,d*10,p));
#else
    outputList->addLast(new Detection(cx,cy,cs,conf,d,p));
#endif
  }
//  fprintf(stderr,"\n");
  // Clean up
  Tcl_DeleteHashTable(&accum);
}

int FindNewLocationOrientation(ByteImage *image, ByteImage *mask,
                               double x, double y, double a, 
                               double *newX, double *newY, double *newA)
{
  if (!LightingCorrectionMatrixInitialized)
    InitializeLightingCorrectionMatrix();
#ifdef UseAngleCache
  if (!AngleCacheInitialized) InitializeAngleCache();
#endif

  Vec vec(3);
  int hist[512];
  int map[512];
  int *tmp=new int[mask->size];

  int found=1;

  int halfH=mask->height/2;
  int halfW=mask->width/2;

#if 0
  int incx=1;
  int incy=1;
  double inca=10.0*M_PI/180.0;
  int startx=0;
  int starty=0;
  double starta=-10.0*M_PI/180.0;
  int stepsx=1;
  int stepsy=1;
  int stepsa=3;
#endif
#if 1
  int incx=1;
  int incy=1;
  double inca=20.0*M_PI/180.0;
  int startx=-1;
  int starty=-1;
  double starta=-40.0*M_PI/180.0;
  int stepsx=3;
  int stepsy=3;
  int stepsa=5;
#endif
#if 0
  int incx=1;
  int incy=1;
  double inca=20.0*M_PI/180.0;
  int startx=-1;
  int starty=-1;
  double starta=0;
  int stepsx=3;
  int stepsy=3;
  int stepsa=1;
#endif

  double totX=0, totY=0, totDirX=0, totDirY=0;
  int tot=0;

//  ByteImage *history0=FindByteImageWithName("face0");

  for (int stepa=0; stepa<stepsa; stepa++)
    for (int stepy=0; stepy<stepsy; stepy++)
      for (int stepx=0; stepx<stepsx; stepx++) {
        int rx=(int)(x+startx+incx*stepx);
        int ry=(int)(y+starty+incy*stepy);
        double ra=a+starta+inca*stepa;
        int ptr=0;
        double v0=0, v1=0, v2=0;

#ifdef UseAngleCache
        int ia=((int)(ra*180.0/M_PI+360))%360;
        int *aptr=AngleCache+(ia*20*20*2);
        for (int j=-halfH; j<halfH; j++) {
          for (int i=-halfW; i<halfW; i++) {
            int ii=rx+(*(aptr++));
            int jj=ry+(*(aptr++));
            if (ii<0) ii=0;
            if (jj<0) jj=0;
            if (ii>=image->width) ii=image->width-1;
            if (jj>=image->height) jj=image->height-1;
            int data=image->data(ii,jj);
            tmp[ptr]=data;
            if (mask->data(ptr++)) {
              v0+=i*data;
              v1+=j*data;
              v2+=data;
            }
          } 
        }
#else
        for (int j=-halfH; j<halfH; j++) {
          for (int i=-halfW; i<halfW; i++) {
            double ii=rx+(i+0.5)*cos(ra)-(j+0.5)*sin(ra)-0.5;
            double jj=ry+(i+0.5)*sin(ra)+(j+0.5)*cos(ra)-0.5;
            int data=(int)(0.5+image->interpolateExtend(ii,jj));
            tmp[ptr]=data;
            if (mask->data(ptr++)) {
              v0+=i*data;
              v1+=j*data;
              v2+=data;
            }
//            history0->data(i+10,j+10)=data;
          } 
        }
#endif

        vec(0)=v0; vec(1)=v1; vec(2)=v2;
        vec=LightingCorrectionMatrix*vec;
        v0=vec(0); v1=vec(1); v2=vec(2);
        for (int i=0; i<512; i++) hist[i]=0;
        ptr=0;
        for (int j=-halfH; j<halfH; j++) for (int i=-halfW; i<halfW; i++) {
          int val=tmp[ptr]-(int)(i*v0+j*v1+v2-256.5);
          if (val<0) val=0;
          if (val>=512) val=511;
          if (mask->data(ptr)) hist[val]++;
          tmp[ptr++]=val;
        }
        int *to=map;
        int *from=hist;
        int total=0;
        for (int i=0; i<512; i++) {
          int old=total;
          total+=*(from++);
          *(to++)=old+total;
        }
        double scaleFactor=1.0/total;
        FastForwardUnit *unit=&(real_fast_list[1]->unitList[1]);
        for (int i=0; i<mask->size; i++)
          (unit++)->activation=map[tmp[i]]*scaleFactor-1.0;
  
        int found=1;
        for (int i=1; i<=2 && found; i++) {
          if (i>1) {
            FastForwardUnit *unit=&(real_fast_list[1]->unitList[1]);
            FastForwardUnit *unit1=&(real_fast_list[i]->unitList[1]);
            for (int j=0; j<mask->size; j++)
              (unit1++)->activation=(unit++)->activation;
          }
          double output=FastForwardPass(real_fast_list[i]);
//    fprintf(stderr,"net[%d]=%g\n",i,output);
          if (output<=0) found=0;
        }
#ifdef UsePosterLogging
        if (EnablePosterLogging) {
          VImage cand=VCreateImage(1,20,20,VUByteRepn);
          for (int y=0; y<20; y++) for (int x=0; x<20; x++) 
            VSetPixel(cand,0,y,x,
                      real_fast_list[1]->unitList[1+y*20+x].activation*127+
                      127);
          if (stepa==2 && stepx==1 && stepy==1)
            WriteVistaImageLogging(cand,"candc3"); else
              WriteVistaImageLogging(cand,"cand3");
          VDestroyImage(cand);
        }
#endif

        if (found) {
#ifdef UsePosterLogging
          if (EnablePosterLogging) {
            VImage cand=VCreateImage(1,20,20,VUByteRepn);
            for (int y=0; y<20; y++) for (int x=0; x<20; x++) 
              VSetPixel(cand,0,y,x,
                        real_fast_list[1]->unitList[1+y*20+x].activation*127+
                        127);
            WriteVistaImageLogging(cand,"cand4");
            VDestroyImage(cand);
          }
#endif
#if 0          
          *newX=rx;
          *newY=ry;
          *newA=ra;
//          history0->Change();
          delete[] tmp;
          return found;
#endif
          totX+=rx;
          totY+=ry;
          totDirX+=cos(ra);
          totDirY+=sin(ra);
          tot++;
        } 
      }
//  history0->Change();

  delete[] tmp;
  if (tot>0) { 
    *newX=totX/tot;
    *newY=totY/tot;
    *newA=atan2(totDirY,totDirX);
    return 1;
  }
    
  return 0;
}

int DuplicateFaceOrientation(double x1, double y1, double s1, double a1,
                             double x2, double y2, double s2, double a2)
{
  int dup=0;
  if (fabs(s1-s2)<=2) {
    x1/=pow(1.2,s2-s1);
    y1/=pow(1.2,s2-s1);
    if (sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2))<=8) {
      double ang=(a1-a2)*180.0/M_PI;
      while (ang<-180) ang+=360;
      while (ang>180) ang-=360;
      if (fabs(ang)<30) 
        dup=1;
    }
  }
  return dup;
}

#include "../Common/Context.h"
#include "../../../Common/Frame/Frame.h"

#include <QList>
#include <QSize>
#include <QPoint>

#include "img.hpp"
#include "gif.hpp"

#include <stdlib.h>
#include <stdio.h>
#ifndef hpux
#include <math.h>
#endif

#include "../detect.h"

#include <direct.h>

#ifdef hpux
#include <math.h>
#endif

#ifdef __GNUC__
#include <string.h>
#else
#ifndef WINNT
extern "C" {
#endif
#include <string.h>
#ifndef WINNT
}
#endif
#endif

#include "eye.hpp"
#include "search.hpp"
#include "follow.hpp"
#include "fast2.hpp"
#include "myhebp.hpp"
#include "kdoi.hpp"
#include "vote.hpp"
#include "just.hpp"

#ifndef M_PI
#define M_PI (atan(1.0)*4.0)
#endif

#define Library
//#define Albert
#define Fast
//#define Debug
//#define DebugInput
//#define SaveOutput

void Informedia_OutputDetection(ClientData data, ByteImage *image,
                                int x, int y, int width, int height,
                                int level,
                                double scale, double output, int orientation);

void Informedia_SaveDetections(ClientData data, ByteImage *image,
                               int x, int y, int width, int height,
                               int level,
                               double scale, double output, int orientation);

// Path for data
char Slow_DetectorPath[256];
char Eye_DetectorPath[256];
char Informedia_DetectorPath[256];
char Xavier_DetectorPath[256];
char Track_DetectorPath[256];
char Siemens_DetectorPath[256];
char Astro_DetectorPath[256];
char Rotation_DetectorPath[256];

void SetDataPath(char *path) 
{
	size_t len = strlen(path) + 1;
	memcpy(&Slow_DetectorPath, path, len);
	memcpy(&Eye_DetectorPath, path, len);
	memcpy(&Informedia_DetectorPath, path, len);
	memcpy(&Xavier_DetectorPath, path, len);
	memcpy(&Track_DetectorPath, path, len);
	memcpy(&Siemens_DetectorPath, path, len);
	memcpy(&Astro_DetectorPath, path, len);
	memcpy(&Rotation_DetectorPath, path, len);
}

// Apply the slow version of the detector (with any of the arbitration
// schemes) to the given image
int Slow_FindAllFaces(int width, int height, unsigned char *buffer,
                      int mode, struct FaceLocation **locs)
{
  // Make sure the image code is initialized
  static int imageInitialized=0;
  if (!imageInitialized) {
    Image_Init_NoTcl();
    imageInitialized=1;
  }

  // Change to the data directory
  char *prevPath=getcwd(NULL,1024);
  chdir(Slow_DetectorPath);

  // Create image
  ByteImage *image=new ByteImage(NULL);
  unsigned char *buf=image->AllocBuffer(width,height);
  memcpy(buf,buffer,width*height);
  image->NewBuffer(buf,width,height);

  List<Detection> detections[5];
  List<Detection> *index[5];
  for (int i=0; i<5; i++) index[i]=detections+i;

  // Load the face mask
  ByteImage *facemask=new ByteImage("facemask");
  FILE *inf=fopen("facemask20x20.pgm","r");
  LoadByteImagePgm(facemask,inf);
  fclose(inf);

  // For each arbitration scheme, load the appropriate set of 
  // networks, and compute their outputs, and apply arbitration
  switch (mode) {
    case 1: {
//      char *networks[]={"face12"};
      char *networks[]={"face17c"};
      FastAllocateNetworks(1);
      FastInitNetwork(0,1,networks);
      SearchMultiMerge(image,1,Informedia_SaveDetections,
                       (ClientData*)(index+4));
      break; 
    }
    case 2: {
//      char *networks[]={"face13"};
      char *networks[]={"face18c"};
      FastAllocateNetworks(1);
      FastInitNetwork(0,1,networks);
      SearchMultiMerge(image,1,Informedia_SaveDetections,
                       (ClientData*)(index+4));
      break;
    }
    case 3: {
//      char *networks[]={"face14"};
      char *networks[]={"face19c"};
      FastAllocateNetworks(1);
      FastInitNetwork(0,1,networks);
      SearchMultiMerge(image,1,Informedia_SaveDetections,
                       (ClientData*)(index+4));
      break;
    }
    case 4: {
//      char *networks[]={"face15"};
      char *networks[]={"face20c"};
      FastAllocateNetworks(1);
      FastInitNetwork(0,1,networks);
      SearchMultiMerge(image,1,Informedia_SaveDetections,
                       (ClientData*)(index+4));
      break;
    }
    case 5: {
//      char *networks[]={"face12"};
      char *networks[]={"face17c"};
      FastAllocateNetworks(1);
      FastInitNetwork(0,1,networks);
      SearchMultiMerge(image,1,Informedia_SaveDetections,
                       (ClientData*)(index));
      FuzzyVote2Direct(width,height,1,detections,detections+4,
                       2,1,1,1,0,facemask);
      break; 
    }
    case 6: {
//      char *networks[]={"face13"};
      char *networks[]={"face18c"};
      FastAllocateNetworks(1);
      FastInitNetwork(0,1,networks);
      SearchMultiMerge(image,1,Informedia_SaveDetections,
                       (ClientData*)(index));
      FuzzyVote2Direct(width,height,1,detections,detections+4,
                       2,1,1,1,0,facemask);
      break; 
    }
    case 7: {
//      char *networks[]={"face14"};
      char *networks[]={"face19c"};
      FastAllocateNetworks(1);
      FastInitNetwork(0,1,networks);
      SearchMultiMerge(image,1,Informedia_SaveDetections,
                       (ClientData*)(index));
      FuzzyVote2Direct(width,height,1,detections,detections+4,
                       2,1,1,1,0,facemask);
      break; 
    }
    case 8: {
//      char *networks[]={"face15"};
      char *networks[]={"face20c"};
      FastAllocateNetworks(1);
      FastInitNetwork(0,1,networks);
      SearchMultiMerge(image,1,Informedia_SaveDetections,
                       (ClientData*)(index));
      FuzzyVote2Direct(width,height,1,detections,detections+4,
                       2,1,1,1,0,facemask);
      break; 
    }
    case 9: {
//      char *networks[]={"face12","face13"};
      char *networks[]={"face17c","face18c"};
      FastAllocateNetworks(1);
      FastInitNetwork(0,2,networks);
      SearchMultiMerge(image,2,Informedia_SaveDetections,
                       (ClientData*)(index));
      FuzzyVote2Direct(width,height,2,detections,detections+4,
                       0,2,0,0,0,facemask);
      break; 
    }
    case 10: {
//      char *networks[]={"face12","face13"};
      char *networks[]={"face17c","face18c"};
      FastAllocateNetworks(1);
      FastInitNetwork(0,2,networks);
      SearchMultiMerge(image,2,Informedia_SaveDetections,
                       (ClientData*)(index));
      FuzzyVote2Direct(width,height,2,detections,detections+2,
                       0,2,0,0,0,facemask);
      FuzzyVote2Direct(width,height,1,detections+2,detections+4,
                       2,3,1,1,0,facemask);
      break; 
    }
    case 11: {
//      char *networks[]={"face12","face13"};
      char *networks[]={"face17c","face18c"};
      FastAllocateNetworks(1);
      FastInitNetwork(0,2,networks);
      SearchMultiMerge(image,2,Informedia_SaveDetections,
                       (ClientData*)(index));
      FuzzyVote2Direct(width,height,1,detections,detections+2,
                       2,2,1,1,0,facemask);
      FuzzyVote2Direct(width,height,1,detections+1,detections+3,
                       2,2,1,1,0,facemask);
      FuzzyVote2Direct(width,height,2,detections+2,detections+4,
                       2,2,1,1,0,facemask);
      break; 
    }
    case 12: {
//      char *networks[]={"face12","face13"};
      char *networks[]={"face17c","face18c"};
      FastAllocateNetworks(1);
      FastInitNetwork(0,2,networks);
      SearchMultiMerge(image,2,Informedia_SaveDetections,
                       (ClientData*)(index));
      FuzzyVote2Direct(width,height,1,detections,detections+2,
                       2,2,1,1,0,facemask);
      FuzzyVote2Direct(width,height,1,detections+1,detections+3,
                       2,2,1,1,0,facemask);
      FuzzyVote2Direct(width,height,2,detections+2,detections+4,
                       2,1,1,1,0,facemask);
      break; 
    }
    case 13: {
//      char *networks[]={"face12","face13","face14"};
      char *networks[]={"face17c","face18c","face19c"};
      FastAllocateNetworks(1);
      FastInitNetwork(0,3,networks);
      SearchMultiMerge(image,3,Informedia_SaveDetections,
                       (ClientData*)(index));
      FuzzyVote2Direct(width,height,3,detections,detections+4,
                       0,2,1,1,0,facemask);
      break; 
    }
    case 14: {
//      char *networks[]={"face12","face13","face14","netarb14"};
      char *networks[]={"face17c","face18c","face19c","netarb14c"};
      FastAllocateNetworks(2);
      FastInitNetwork(0,3,networks);
      FastInitNetwork(1,1,networks+3);
      SearchMultiMerge(image,3,Informedia_SaveDetections,
                       (ClientData*)(index));
      NetArbitrateDirect(width,height,3,detections,detections+3,1);
      FuzzyVote2Direct(width,height,1,detections+3,detections+4,
                       2,1,1,1,0,facemask);
      break; 
    }
    case 15: {
//      char *networks[]={"face12","face13","face14","netarb15"};
      char *networks[]={"face17c","face18c","face19c","netarb15c"};
      FastAllocateNetworks(2);
      FastInitNetwork(0,3,networks);
      FastInitNetwork(1,1,networks+3);
      SearchMultiMerge(image,3,Informedia_SaveDetections,
                       (ClientData*)(index));
      NetArbitrateDirect(width,height,3,detections,detections+3,1);
      FuzzyVote2Direct(width,height,1,detections+3,detections+4,
                       2,1,1,1,0,facemask);
      break; 
    }
    case 16: {
//      char *networks[]={"face12","face13","face14","netarb16"};
      char *networks[]={"face17c","face18c","face19c","netarb16c"};
      FastAllocateNetworks(2);
      FastInitNetwork(0,3,networks);
      FastInitNetwork(1,1,networks+3);
      SearchMultiMerge(image,3,Informedia_SaveDetections,
                       (ClientData*)(index));
      NetArbitrateDirect(width,height,3,detections,detections+3,1);
      FuzzyVote2Direct(width,height,1,detections+3,detections+4,
                       2,1,1,1,0,facemask);
      break; 
    }
    case 17: {
      fprintf(stderr,
              "Use the fast detector directly (Informedia_FindAllFaces()).\n");
      exit(1);
      break;
    }
    default: {
      fprintf(stderr,"Unknown arbitration mode %d!\n",mode);
      exit(1);
      break;
    }
  }

  // Put detection results in data structure for caller
  int counter=detections[4].length;
  if (locs!=NULL) {
    if (counter==0) *locs=NULL; else {
      *locs=(struct FaceLocation*)malloc(sizeof(struct FaceLocation)*counter);
      int i=0;
      for (Detection *d=detections[4].first; d!=NULL; d=d->next) {
        double s=pow(1.2,d->s);
        (*locs)[i].x1=(int)floor(d->x*s+0.5);
        (*locs)[i].y1=(int)floor(d->y*s+0.5);
        (*locs)[i].x2=(int)floor((d->x+20)*s+0.5);
        (*locs)[i].y2=(int)floor((d->y+20)*s+0.5);
        i++;
      }
    }
  }

  delete image;
  delete facemask;

  // Go back to original directory
  chdir(prevPath);
  free(prevPath);
  return counter;
}

int SearchEye(int width, int height, unsigned char *buffer,
              int eyeWidthGuess, int leftEye,
              int *x, int *y)
{
  static int initialized=0;
  static ByteImage *mask;
  if (!initialized) {
    char *prevPath=getcwd(NULL,1024);
    chdir(Eye_DetectorPath);
    FastAllocateNetworks(1);
    char *networks[]={"eye"};
    FastInitNetwork(0,1,networks);
    mask=new ByteImage(NULL);
    FILE *inf=fopen("eyemask25x15.pgm","r");
    LoadByteImagePgm(mask,inf);
    fclose(inf);
    chdir(prevPath);
    free(prevPath);
  }
  ByteImage *image=new ByteImage(NULL);
  image->NewBuffer(buffer,width,height);
  int result=SearchLeftEye(image,mask,eyeWidthGuess,x,y,leftEye);
  image->buffer=NULL;
  delete image;
  return result;
}

void Informedia_CountDetections(ClientData data, ByteImage *image,
                                int x, int y, int width, int height,
                                int level,
                                double scale, double output, int orientation)
{
#ifdef Debug
  fprintf(stderr,"Counting %g %g %g %g %d %d %d %g\n",
          scale*x,scale*y,
          scale*(x+width),scale*(y+height),
          x,y,level,output);
#endif
  int *counter=(int*)data;
  (*counter)++;
}

void Informedia_Init()
{
  static int initialized=0;
  if (initialized) return;
  Image_Init_NoTcl();
  char *prevPath=getcwd(NULL,1024);
  chdir(Informedia_DetectorPath);
#ifdef Fast
//  char *networks[]={"ume","face12","face13"};
  char *networks[]={"umec","face17c","face18c"};
  FastAllocateNetworks(3);
  FastInitNetwork(0,1,networks);
  FastInitNetwork(1,1,networks+1);
  FastInitNetwork(2,1,networks+2);
  //  FastInit("./",3,networks);
  //  HEBPInit("./",3,networks,0);
#else
//  char *networks[]={"face12","face13"};
  char *networks[]={"face17c","face18c"};
  FastInit("./",2,networks);
  HEBPInit("./",2,networks,0);
#endif
  ByteImage *mask=new ByteImage("facemask");
  FILE *inf=fopen("facemask20x20.pgm","r");
  LoadByteImagePgm(mask,inf);
  fclose(inf);
  initialized=1;
  chdir(prevPath);
  free(prevPath);
}

void Informedia_Init_Router()
{
  static int initialized=0;
  if (initialized) return;
  Image_Init_NoTcl();
  char *prevPath=getcwd(NULL,1024);
  chdir(Informedia_DetectorPath);
  char *networks[]={
    "router","face-fr-1a","face-hr-1a","face-pr-1a",
    "face-fr-1b","face-hr-1b","face-pr-1b"};
  FastAllocateNetworks(7);
  for (int i=0; i<7; i++)
    FastInitNetwork(i,1,networks+i);
  ByteImage *mask=new ByteImage("facemask");
  FILE *inf=fopen("facemask20x20.pgm","r");
  LoadByteImagePgm(mask,inf);
  fclose(inf);
  initialized=1;
  chdir(prevPath);
  free(prevPath);
}

#ifdef CompiledNets
void Informedia_Init_Compiled()
{
  static int initialized=0;
  if (initialized) return;
  Image_Init_NoTcl();
  char *prevPath=getcwd(NULL,1024);
  chdir(Informedia_DetectorPath);
  ByteImage *mask=new ByteImage("facemask");
  FILE *inf=fopen("facemask20x20.pgm","r");
  LoadByteImagePgm(mask,inf);
  fclose(inf);
  initialized=1;
  chdir(prevPath);
  free(prevPath);
}
#endif

int Informedia_FindFacesGray(int width, int height, unsigned char *buffer, 
                             struct FaceLocation **locs)
{
  Informedia_Init();
  ByteImage *image=new ByteImage(NULL);

  int i;

#ifdef DebugInput
{
  FILE *f=fopen("/tmp/input.ppm","w");
  fprintf(f,"P6\n%d %d\n255\n",width,height);
  fwrite((char*)buffer,width*height*3,1,f);
  fclose(f);
}
#endif

#ifndef Albert
  image->NewBuffer(buffer,width,height);
#else
  LoadByteImageGif(image,"/hosts/dylan/usr0/har/faces/test/albert.gif");
#endif

  int counter=0;
#ifdef Fast
  int levels=0;
  int w=width, h=height;
  while (w>=20 && h>=20) {
    w=(int)(w/1.2);
    h=(int)(h/1.2);
    levels++;
  }
  ByteImage *mainmask=new ByteImage(NULL);
  ByteImage **imagePyramid=new ByteImage*[levels];
  imagePyramid[0]=image;
  for (i=1; i<levels; i++)
  {
    imagePyramid[i]=new ByteImage(NULL);
    ReduceSize(imagePyramid[i],imagePyramid[i-1]);
  }
  mainmask->ZeroBuffer(width,height);
  ByteImage *levelmask=new ByteImage(NULL);
  ByteImage *mask=FindByteImageWithName("facemask");
  List<Detection> alldetections[1];
  for (i=levels-1; i>=0; i--)
  {
    ResampleByteImage(levelmask,mainmask,
                      imagePyramid[i]->width,imagePyramid[i]->height,
                      pow(1.2,-i));
    List<Detection> detections;
    SearchUmeEvenFaster(imagePyramid[i],levelmask,i,
                        Informedia_SaveDetections,(ClientData)(&detections));
    for (Detection* detect=detections.first; detect!=NULL;
                                             detect=detect->next)
    {
      int newX, newY, newS;
      if (FindNewLocation(levels,imagePyramid,mask,
                          detect->x,detect->y,detect->s,6,6,1,2,1,
                          &newX,&newY,&newS))
      {
        Informedia_SaveDetections((ClientData)alldetections,
                                 imagePyramid[newS],
                                 newX,newY,20,20,newS,
                                 pow(1.2,newS),1.0,0);
        FillRectangle(mainmask,
                      (int)(pow(1.2,newS)*newX+0.5),
                      (int)(pow(1.2,newS)*newY+0.5),
                      (int)(pow(1.2,newS)*(newX+20)+0.5),
                      (int)(pow(1.2,newS)*(newY+20)+0.5),
                      255);
      }
    }
  }
#ifdef SaveOutput
  char name[256];
  static filecounter=0;
  sprintf(name,"/tmp/%03d.loc",filecounter++);
  FILE *outf=fopen(name,"w");
  FuzzyVote2(width,height,1,alldetections,
             Informedia_OutputDetection,(ClientData)outf,
             2,1,1,0,0,mask);
  fclose(outf);
#else
  List<Detection> results;
  FuzzyVote2(width,height,1,alldetections,
             Informedia_SaveDetections,(ClientData)(&results),
             2,1,1,1,0,mask);
  counter=results.length;
  if (locs!=NULL)
  {
    if (counter==0) *locs=NULL; else
    {
      *locs=(struct FaceLocation*)malloc(sizeof(struct FaceLocation)*counter);
      int i=0;
      for (Detection *d=results.first; d!=NULL; d=d->next)
      {
        double s=pow(1.2,d->s);
        (*locs)[i].x1=(int)floor(d->x*s+0.5);
        (*locs)[i].y1=(int)floor(d->y*s+0.5);
        (*locs)[i].x2=(int)floor((d->x+20)*s+0.5);
        (*locs)[i].y2=(int)floor((d->y+20)*s+0.5);
        i++;
      }
    }
  }
#endif
  for (i=1; i<levels; i++) delete imagePyramid[i];
  delete[] imagePyramid;
  delete mainmask;
  delete levelmask;
#else
  List<Detection> *detections[2];
  detections[0]=new List<Detection>;
  detections[1]=new List<Detection>;
  SearchMulti(image,2,Informedia_SaveDetections,(ClientData*)detections);
  List<Detection> *detectionsClean[2];
  detectionsClean[0]=new List<Detection>;
  detectionsClean[1]=new List<Detection>;
  FuzzyVote2(width,height,1,detections,
             Informedia_SaveDetections,(ClientData)(detectionsClean[0]),
             2,2,1,1,0,mask);
  FuzzyVote2(width,height,1,detections+1,
             Informedia_SaveDetections,(ClientData)(detectionsClean[1]),
             2,2,1,1,0,mask);
#ifdef SaveOutput
  FILE *outf=fopen("/tmp/tmp","w");
  FuzzyVote2(width,height,2,detections,
             Informedia_OutputDetection,outf,
             2,1,1,1,0,mask);
  fclose(outf);
#else
  List<Detection> results;
  FuzzyVote2(width,height,2,detections,
             Informedia_SaveDetections,(ClientData)(&results),
             2,1,1,1,0,mask);
  counter=results.length;
  if (locs!=NULL)
  {
    if (counter==0) *locs=NULL; else
    {
      *locs=(struct FaceLocation*)malloc(sizeof(struct FaceLocation)*counter);
      int i=0;
      for (Detection *d=results.first; d!=NULL; d=d->next)
      {
        double s=pow(1.2,d->s);
        (*locs)[i].x1=(int)floor(d->x*s+0.5);
        (*locs)[i].y1=(int)floor(d->y*s+0.5);
        (*locs)[i].x2=(int)floor((d->x+20)*s+0.5);
        (*locs)[i].y2=(int)floor((d->y+20)*s+0.5);
        i++;
      }
    }
  }
#endif
  delete detections[0];
  delete detections[1];
  delete detectionsClean[0];
  delete detectionsClean[1];
#endif  
  image->buffer=NULL;
  delete image;
  return counter;
}

int Informedia_FindFaces(int width, int height, unsigned char *buffer, 
                         struct FaceLocation **locs)
{
  Byte *buf=(Byte*)malloc(width*height);
  Byte *iptr=(Byte*)buffer;
  Byte *optr=buf;
  for (int i=0; i<width*height; i++)
  {
    int val=(iptr[0]+iptr[1]+iptr[2])/3;
    *(optr++)=val;
    iptr+=3;
  }
  int counter=Informedia_FindFacesGray(width,height,buf,locs);
  free((char*)buf);
  return counter;
}

int Informedia_FindFacesOrientationGray(int width, int height, 
                                        unsigned char *buffer,
                                        struct FaceLocationOrientation **locs)
{
  Informedia_Init_Router();
  ByteImage *image=new ByteImage(NULL);

  ByteImage *mask=FindByteImageWithName("facemask");
  image->NewBuffer(buffer,width,height);

  List<Detection> alldetectionlists[2];
  List<Detection> *alldetections[2];
  alldetections[0]=alldetectionlists;
  alldetections[1]=alldetectionlists+1;

  SearchRouter(image,mask,
               Informedia_SaveDetections,(ClientData*)alldetections);

  List<Detection> merged;
  NewFuzzyVote(&merged,alldetectionlists,2,width,height,20,20,2,2,1);
  int counter=merged.length;
  if (locs!=NULL) {
    if (counter==0) *locs=NULL; else {
      *locs=(struct FaceLocationOrientation*)
	malloc(sizeof(struct FaceLocationOrientation)*counter);
      int i=0;
      for (Detection *d=merged.first; d!=NULL; d=d->next) {
	double s=pow(1.2,d->s);
	(*locs)[i].x1=(int)floor(d->x*s+0.5);
	(*locs)[i].y1=(int)floor(d->y*s+0.5);
	(*locs)[i].x2=(int)floor((d->x+20)*s+0.5);
	(*locs)[i].y2=(int)floor((d->y+20)*s+0.5);
	(*locs)[i].orientation=d->orient-2;
	i++;
      }
    }
  }
  image->buffer=NULL;
  delete image;
  return counter;
}

int Informedia_FindFacesOrientation(int width, int height, 
                                    unsigned char *buffer,
                                    struct FaceLocationOrientation **locs)
{
  Byte *buf=(Byte*)malloc(width*height);
  Byte *iptr=(Byte*)buffer;
  Byte *optr=buf;
  for (int i=0; i<width*height; i++)
  {
    int val=(iptr[0]+iptr[1]+iptr[2])/3;
    *(optr++)=val;
    iptr+=3;
  }
  int counter=Informedia_FindFacesOrientationGray(width,height,buf,locs);
  free((char*)buf);
  return counter;
}

int Informedia_FindFacesRGBA(int width, int height, unsigned char *buffer, 
                             struct FaceLocation **locs)
{
  Informedia_Init();
  ByteImage *image=new ByteImage(NULL);

  int i;

#ifndef Albert
  Byte *buf=image->AllocBuffer(width,height);
  Byte *iptr=(Byte*)buffer;
  Byte *optr=buf;
  for (i=0; i<width*height; i++)
  {
    int val=(iptr[0]+iptr[1]+iptr[2])/3;
    *(optr++)=val;
    iptr+=4;
  }
  image->NewBuffer(buf,width,height);
#else
  LoadByteImageGif(image,"/hosts/dylan/usr0/har/faces/test/albert.gif");
#endif

  int counter=0;
#ifdef Fast
  int levels=0;
  int w=width, h=height;
  while (w>=20 && h>=20) {
    w=(int)(w/1.2);
    h=(int)(h/1.2);
    levels++;
  }
  ByteImage *mainmask=new ByteImage(NULL);
  ByteImage **imagePyramid=new ByteImage*[levels];
  imagePyramid[0]=image;
  for (i=1; i<levels; i++)
  {
    imagePyramid[i]=new ByteImage(NULL);
    ReduceSize(imagePyramid[i],imagePyramid[i-1]);
  }
  mainmask->ZeroBuffer(width,height);
  ByteImage *levelmask=new ByteImage(NULL);
  ByteImage *mask=FindByteImageWithName("facemask");
  List<Detection> alldetections[1];
  for (i=levels-1; i>=0; i--)
  {
    ResampleByteImage(levelmask,mainmask,
                      imagePyramid[i]->width,imagePyramid[i]->height,
                      pow(1.2,-i));
    List<Detection> detections;
    SearchUmeEvenFaster(imagePyramid[i],levelmask,i,
                        Informedia_SaveDetections,(ClientData)(&detections));
    for (Detection* detect=detections.first; detect!=NULL;
                                             detect=detect->next)
    {
      int newX, newY, newS;
      if (FindNewLocation(levels,imagePyramid,mask,
                          detect->x,detect->y,detect->s,6,6,1,2,1,
                          &newX,&newY,&newS))
      {
        Informedia_SaveDetections((ClientData)alldetections,
                                 imagePyramid[newS],
                                 newX,newY,20,20,newS,
                                 pow(1.2,newS),1.0,0);
        FillRectangle(mainmask,
                      (int)(pow(1.2,newS)*newX+0.5),
                      (int)(pow(1.2,newS)*newY+0.5),
                      (int)(pow(1.2,newS)*(newX+20)+0.5),
                      (int)(pow(1.2,newS)*(newY+20)+0.5),
                      255);
      }
    }
  }
#ifdef SaveOutput
  char name[256];
  static filecounter=0;
  sprintf(name,"/tmp/%03d.loc",filecounter++);
  FILE *outf=fopen(name,"w");
  FuzzyVote2(width,height,1,alldetections,
             Informedia_OutputDetection,(ClientData)outf,
             2,1,1,0,0,mask);
  fclose(outf);
#else
  List<Detection> results;
  FuzzyVote2(width,height,1,alldetections,
             Informedia_SaveDetections,(ClientData)(&results),
             2,1,1,1,0,mask);
  counter=results.length;
  if (locs!=NULL)
  {
    if (counter==0) *locs=NULL; else
    {
      *locs=(struct FaceLocation*)malloc(sizeof(struct FaceLocation)*counter);
      int i=0;
      for (Detection *d=results.first; d!=NULL; d=d->next)
      {
        double s=pow(1.2,d->s);
        (*locs)[i].x1=(int)floor(d->x*s+0.5);
        (*locs)[i].y1=(int)floor(d->y*s+0.5);
        (*locs)[i].x2=(int)floor((d->x+20)*s+0.5);
        (*locs)[i].y2=(int)floor((d->y+20)*s+0.5);
        i++;
      }
    }
  }
#endif
  for (i=1; i<levels; i++) delete imagePyramid[i];
  delete[] imagePyramid;
  delete mainmask;
  delete levelmask;
#else
  List<Detection> *detections[2];
  detections[0]=new List<Detection>;
  detections[1]=new List<Detection>;
  SearchMulti(image,2,Informedia_SaveDetections,(ClientData*)detections);
  List<Detection> *detectionsClean[2];
  detectionsClean[0]=new List<Detection>;
  detectionsClean[1]=new List<Detection>;
  FuzzyVote2(width,height,1,detections,
             Informedia_SaveDetections,(ClientData)(detectionsClean[0]),
             2,2,1,1,0,mask);
  FuzzyVote2(width,height,1,detections+1,
             Informedia_SaveDetections,(ClientData)(detectionsClean[1]),
             2,2,1,1,0,mask);
#ifdef SaveOutput
  FILE *outf=fopen("/tmp/tmp","w");
  FuzzyVote2(width,height,2,detections,
             Informedia_OutputDetection,outf,
             2,1,1,1,0,mask);
  fclose(outf);
#else
  List<Detection> results;
  FuzzyVote2(width,height,2,detections,
             Informedia_SaveDetections,(ClientData)(&results),
             2,1,1,1,0,mask);
  counter=results.length;
  if (locs!=NULL)
  {
    if (counter==0) *locs=NULL; else
    {
      *locs=(struct FaceLocation*)malloc(sizeof(struct FaceLocation)*counter);
      int i=0;
      for (Detection *d=results.first; d!=NULL; d=d->next)
      {
        double s=pow(1.2,d->s);
        (*locs)[i].x1=(int)floor(d->x*s+0.5);
        (*locs)[i].y1=(int)floor(d->y*s+0.5);
        (*locs)[i].x2=(int)floor((d->x+20)*s+0.5);
        (*locs)[i].y2=(int)floor((d->y+20)*s+0.5);
        i++;
      }
    }
  }
#endif
  delete detections[0];
  delete detections[1];
  delete detectionsClean[0];
  delete detectionsClean[1];
#endif  
  
  delete image;
  return counter;
}

int CompareDetectionsDecreasing(Detection *d1, Detection *d2)
{
  if (d1->output<d2->output) return 1;
  if (d1->output>d2->output) return -1;
  return 0;
}

#ifdef CompiledNets
int Informedia_FindFaces_Compiled(int width, int height, unsigned char *buffer, 
                                  struct FaceLocation **locs)
{
  Informedia_Init_Compiled();
  ByteImage *image=new ByteImage(NULL);

  int i;

#ifndef Albert
  Byte *buf=image->AllocBuffer(width,height);
  Byte *iptr=(Byte*)buffer;
  Byte *optr=buf;
  for (i=0; i<width*height; i++)
  {
    int val=(iptr[0]+iptr[1]+iptr[2])/3;
    *(optr++)=val;
    iptr+=3;
  }
  image->NewBuffer(buf,width,height);
#else
  LoadByteImageGif(image,"/hosts/dylan/usr0/har/faces/test/albert.gif");
#endif

  int counter=0;
#ifdef Fast
  int levels=0;
  int w=width, h=height;
  while (w>=20 && h>=20) {
    w=(int)(w/1.2);
    h=(int)(h/1.2);
    levels++;
  }
  ByteImage *mainmask=new ByteImage(NULL);
  ByteImage **imagePyramid=new ByteImage*[levels];
  imagePyramid[0]=image;
  for (i=1; i<levels; i++)
  {
    imagePyramid[i]=new ByteImage(NULL);
    ReduceSize(imagePyramid[i],imagePyramid[i-1]);
  }
  mainmask->ZeroBuffer(width,height);
  ByteImage *levelmask=new ByteImage(NULL);
  ByteImage *mask=FindByteImageWithName("facemask");
  List<Detection> alldetections[1];
  for (i=levels-1; i>=0; i--)
  {
    ResampleByteImage(levelmask,mainmask,
                      imagePyramid[i]->width,imagePyramid[i]->height,
                      pow(1.2,-i));
    List<Detection> detections;
    SearchUmeEvenFasterCompiled(imagePyramid[i],levelmask,i,
                                Informedia_SaveDetections,
                                (ClientData)(&detections));
    for (Detection* detect=detections.first; detect!=NULL;
                                             detect=detect->next)
    {
      int newX, newY, newS;
      if (FindNewLocationCompiled2(levels,imagePyramid,mask,
                                   detect->x,detect->y,detect->s,6,6,1,2,1,
                                   &newX,&newY,&newS))
      {
        Informedia_SaveDetections((ClientData)alldetections,
                                 imagePyramid[newS],
                                 newX,newY,20,20,newS,
                                 pow(1.2,newS),1.0);
        FillRectangle(mainmask,
                      (int)(pow(1.2,newS)*newX+0.5),
                      (int)(pow(1.2,newS)*newY+0.5),
                      (int)(pow(1.2,newS)*(newX+20)+0.5),
                      (int)(pow(1.2,newS)*(newY+20)+0.5),
                      255);
      }
    }
  }
#ifdef SaveOutput
  char name[256];
  static filecounter=0;
  sprintf(name,"/tmp/%03d.loc",filecounter++);
  FILE *outf=fopen(name,"w");
  FuzzyVote2(width,height,1,alldetections,
             Informedia_OutputDetection,(ClientData)outf,
             2,1,1,0,0,mask);
  fclose(outf);
#else
  List<Detection> results;
  FuzzyVote2(width,height,1,alldetections,
             Informedia_SaveDetections,(ClientData)(&results),
             2,1,1,1,0,mask);
  counter=results.length;
  if (locs!=NULL)
  {
    if (counter==0) *locs=NULL; else
    {
      *locs=(struct FaceLocation*)malloc(sizeof(struct FaceLocation)*counter);
      int i=0;
      for (Detection *d=results.first; d!=NULL; d=d->next)
      {
        double s=pow(1.2,d->s);
        (*locs)[i].x1=(int)floor(d->x*s+0.5);
        (*locs)[i].y1=(int)floor(d->y*s+0.5);
        (*locs)[i].x2=(int)floor((d->x+20)*s+0.5);
        (*locs)[i].y2=(int)floor((d->y+20)*s+0.5);
        i++;
      }
    }
  }
#endif
  for (i=1; i<levels; i++) delete imagePyramid[i];
  delete[] imagePyramid;
  delete mainmask;
  delete levelmask;
#else
  List<Detection> *detections[2];
  detections[0]=new List<Detection>;
  detections[1]=new List<Detection>;
  SearchMulti(image,2,Informedia_SaveDetections,(ClientData*)detections);
  List<Detection> *detectionsClean[2];
  detectionsClean[0]=new List<Detection>;
  detectionsClean[1]=new List<Detection>;
  FuzzyVote2(width,height,1,detections,
             Informedia_SaveDetections,(ClientData)(detectionsClean[0]),
             2,2,1,1,0,mask);
  FuzzyVote2(width,height,1,detections+1,
             Informedia_SaveDetections,(ClientData)(detectionsClean[1]),
             2,2,1,1,0,mask);
#ifdef SaveOutput
  FILE *outf=fopen("/tmp/tmp","w");
  FuzzyVote2(width,height,2,detections,
             Informedia_OutputDetection,outf,
             2,1,1,1,0,mask);
  fclose(outf);
#else
  List<Detection> results;
  FuzzyVote2(width,height,2,detections,
             Informedia_SaveDetections,(ClientData)(&results),
             2,1,1,1,0,mask);
  counter=results.length;
  if (locs!=NULL)
  {
    if (counter==0) *locs=NULL; else
    {
      *locs=(struct FaceLocation*)malloc(sizeof(struct FaceLocation)*counter);
      int i=0;
      for (Detection *d=results.first; d!=NULL; d=d->next)
      {
        double s=pow(1.2,d->s);
        (*locs)[i].x1=(int)floor(d->x*s+0.5);
        (*locs)[i].y1=(int)floor(d->y*s+0.5);
        (*locs)[i].x2=(int)floor((d->x+20)*s+0.5);
        (*locs)[i].y2=(int)floor((d->y+20)*s+0.5);
        i++;
      }
    }
  }
#endif
  delete detections[0];
  delete detections[1];
  delete detectionsClean[0];
  delete detectionsClean[1];
#endif  
  
  delete image;
  return counter;
}
#endif

void Informedia_FindFacesAllCandidates(int width, int height,
                                       unsigned char *buffer, 
                                       int verificationThreshold,
                                       Informedia_CandidateCallback callback)
{
  int i;
  Informedia_Init();
  ByteImage *image=new ByteImage(NULL);
  Byte *buf=image->AllocBuffer(width,height);
  Byte *iptr=(Byte*)buffer;
  Byte *optr=buf;
  for (i=0; i<width*height; i++)
  {
    int val=(iptr[0]+iptr[1]+iptr[2])/3;
    *(optr++)=val;
    iptr+=3;
  }
  image->NewBuffer(buf,width,height);

  int levels=0;
  int w=width, h=height;
  while (w>=20 && h>=20) {
    w=(int)(w/1.2);
    h=(int)(h/1.2);
    levels++;
  }
  ByteImage *mainmask=new ByteImage(NULL);
  ByteImage **imagePyramid=new ByteImage*[levels];
  imagePyramid[0]=image;
  for (i=1; i<levels; i++)
  {
    imagePyramid[i]=new ByteImage(NULL);
    ReduceSize(imagePyramid[i],imagePyramid[i-1]);
  }
  ByteImage *mask=FindByteImageWithName("facemask");
  List<Detection> alldetections[1];
  List<Detection> detections;
  for (i=levels-1; i>=0; i--)
    SearchUmeEvenFaster(imagePyramid[i],NULL,i,
                        Informedia_SaveDetections,(ClientData)(&detections),
                        -2.0);
  detections.sort(CompareDetectionsDecreasing);
  for (Detection* detect=detections.first; detect!=NULL;
                                           detect=detect->next)
  {
    int x1, y1, s1, x2, y2, s2;
    double o1, o2;
    if (FindNewLocationRecordMax(levels,imagePyramid,mask,
                                 detect->x,detect->y,detect->s,6,6,1,1,1,
                                 &x1,&y1,&s1,&o1,
                                 &x2,&y2,&s2,&o2)>=verificationThreshold)
    {
      if (!callback(detect->output,
                    (int)floor(0.5+detect->x*pow(1.2,detect->s)),
                    (int)floor(0.5+detect->y*pow(1.2,detect->s)),
                    (int)floor(0.5+mask->width*pow(1.2,detect->s)),
                    o1,
                    (int)floor(0.5+x1*pow(1.2,s1)),
                    (int)floor(0.5+y1*pow(1.2,s1)),
                    (int)floor(0.5+mask->width*pow(1.2,s1)),
                    o2,
                    (int)floor(0.5+x2*pow(1.2,s2)),
                    (int)floor(0.5+y2*pow(1.2,s2)),
                    (int)floor(0.5+mask->width*pow(1.2,s2))))
        break;
    }
  }
  for (i=1; i<levels; i++) delete imagePyramid[i];
  delete[] imagePyramid;
  delete image;
}


void Xavier_Init()
{
  static int initialized=0;
  if (initialized) return;
  Image_Init_NoTcl();
  char *prevPath=getcwd(NULL,1024);
  chdir(Xavier_DetectorPath);
//  char *networks[]={"ume","face12","face13","facerot"};
  char *networks[]={"umec","face17c","face18c","facelocc"};
  FastAllocateNetworks(4);
  FastInitNetwork(0,1,networks);
  FastInitNetwork(1,1,networks+1);
  FastInitNetwork(2,1,networks+2);
  FastInitNetwork(3,1,networks+3);
  ByteImage *mask=new ByteImage("facemask");
  FILE *inf=fopen("facemask20x20.pgm","r");
  LoadByteImagePgm(mask,inf);
  fclose(inf);
  KDoiInit("mlist");
  initialized=1;
  chdir(prevPath);
  free(prevPath);
}

int Xavier_FindAllFaces(int width, int height, unsigned char *buffer, 
                        struct FaceLocation **locs)
{
  Xavier_Init();
  ByteImage *image=new ByteImage(NULL);

  int i;

  image->NewBuffer((unsigned char*)buffer,width,height);

  int counter=0;
  int levels=0;
  int w=width, h=height;
  while (w>=20 && h>=20) {
    w=(int)(w/1.2);
    h=(int)(h/1.2);
    levels++;
  }
  ByteImage *mainmask=new ByteImage(NULL);
  ByteImage **imagePyramid=new ByteImage*[levels];
  imagePyramid[0]=image;
  for (i=1; i<levels; i++)
  {
    imagePyramid[i]=new ByteImage(NULL);
    ReduceSize(imagePyramid[i],imagePyramid[i-1]);
  }

/*
  for (i=0; i<levels; i++) {
    int hash=1;
    for (int y=0; y<imagePyramid[i]->height; y++)
      for (int x=0; x<imagePyramid[i]->width; x++) {
        hash *= imagePyramid[i]->data(x,y)+1;
        hash = hash % 65535;
      }
    fprintf(stderr,"check level %d (%dx%d) is %d\n",i,
            imagePyramid[i]->width,imagePyramid[i]->height,
            hash);
  }
*/

//  fprintf(stderr,"levels=%d\n",levels);
  mainmask->ZeroBuffer(width,height);
  ByteImage *levelmask=new ByteImage(NULL);
  ByteImage *mask=FindByteImageWithName("facemask");
  List<Detection> alldetections[1];
  for (i=levels-1; i>=0; i--)
  {
    ResampleByteImage(levelmask,mainmask,
                      imagePyramid[i]->width,imagePyramid[i]->height,
                      pow(1.2,-i));
    List<Detection> detections;
    SearchUmeEvenFaster(imagePyramid[i],levelmask,i,
                        Informedia_SaveDetections,(ClientData)(&detections));
    for (Detection* detect=detections.first; detect!=NULL;
                                             detect=detect->next)
    {
      int newX, newY, newS;
//      fprintf(stderr,"Verifying candidate at %d,%d,%d=%g\n",
//      		  detect->x,detect->y,detect->s,detect->output);
      if (FindNewLocation(levels,imagePyramid,mask,
                          detect->x,detect->y,detect->s,6,6,1,2,1,
                          &newX,&newY,&newS))
      {
        Informedia_SaveDetections((ClientData)alldetections,
                                 imagePyramid[newS],
                                 newX,newY,20,20,newS,
                                 pow(1.2,newS),1.0,0);
        FillRectangle(mainmask,
                      (int)(pow(1.2,newS)*newX+0.5),
                      (int)(pow(1.2,newS)*newY+0.5),
                      (int)(pow(1.2,newS)*(newX+20)+0.5),
                      (int)(pow(1.2,newS)*(newY+20)+0.5),
                      255);
      }
    }
  }
  List<Detection> results;
  FuzzyVote2(width,height,1,alldetections,
             Informedia_SaveDetections,(ClientData)(&results),
             2,1,1,1,0,mask);
  counter=results.length;
  if (locs!=NULL)
  {
    if (counter==0) *locs=NULL; else
    {
      *locs=(struct FaceLocation*)malloc(sizeof(struct FaceLocation)*counter);
      int i=0;
      for (Detection *d=results.first; d!=NULL; d=d->next)
      {
        double s=pow(1.2,d->s);
        (*locs)[i].x1=(int)floor(d->x*s+0.5);
        (*locs)[i].y1=(int)floor(d->y*s+0.5);
        (*locs)[i].x2=(int)floor((d->x+20)*s+0.5);
        (*locs)[i].y2=(int)floor((d->y+20)*s+0.5);
        i++;
      }
    }
  }
  for (i=1; i<levels; i++) delete imagePyramid[i];
  delete[] imagePyramid;
  delete mainmask;
  delete levelmask;
 
  image->buffer=NULL;
  delete image;
  return counter;
}

int Xavier_FindAllFacesColor(int width, int height, unsigned char *buffer, 
                             struct FaceLocation **locs)
{
  Xavier_Init();
  ByteImage *image=new ByteImage(NULL);

  int i;

  unsigned char *newdata=(unsigned char*)malloc(width*height);
  unsigned char *iptr=buffer, *optr=newdata;
  for (i=0; i<width*height; i++)
  {
    int val=(int)floor(0.5+
                       0.299*(*(iptr))+
                       0.587*(*(iptr+1))+
                       0.114*(*(iptr+2)));
    if (val>=255) val=255;
    *(optr++)=val;
    iptr+=3;
  }

  image->NewBuffer((unsigned char*)newdata,width,height);

  int counter=0;
  int levels=0;
  int w=width, h=height;
  while (w>=20 && h>=20) {
    w=(int)(w/1.2);
    h=(int)(h/1.2);
    levels++;
  }
  ByteImage *mainmask=new ByteImage(NULL);
  ByteImage **imagePyramid=new ByteImage*[levels];
  imagePyramid[0]=image;
  for (i=1; i<levels; i++)
  {
    imagePyramid[i]=new ByteImage(NULL);
    ReduceSize(imagePyramid[i],imagePyramid[i-1]);
  }
  mainmask->ZeroBuffer(width,height,255);
  KDoiColorMask(buffer,width,height,mainmask,0);
  if (0) {
    FILE *outf=fopen("mask.pgm","w");
    SaveByteImagePgm(mainmask,outf);
    fclose(outf);
  }    
  ByteImage *levelmask=new ByteImage(NULL);
  ByteImage *mask=FindByteImageWithName("facemask");
  List<Detection> alldetections[1];
  for (i=levels-1; i>=0; i--)
  {
    ResampleByteImage(levelmask,mainmask,
                      imagePyramid[i]->width,imagePyramid[i]->height,
                      pow(1.2,-i));
    List<Detection> detections;
    SearchUmeEvenFaster(imagePyramid[i],levelmask,i,
                        Informedia_SaveDetections,(ClientData)(&detections));
    for (Detection* detect=detections.first; detect!=NULL;
                                             detect=detect->next)
    {
      int newX, newY, newS;
      if (FindNewLocation(levels,imagePyramid,mask,
                          detect->x,detect->y,detect->s,6,6,1,2,1,
                          &newX,&newY,&newS))
      {
        Informedia_SaveDetections((ClientData)alldetections,
                                 imagePyramid[newS],
                                 newX,newY,20,20,newS,
                                 pow(1.2,newS),1.0,0);
        FillRectangle(mainmask,
                      (int)(pow(1.2,newS)*newX+0.5),
                      (int)(pow(1.2,newS)*newY+0.5),
                      (int)(pow(1.2,newS)*(newX+20)+0.5),
                      (int)(pow(1.2,newS)*(newY+20)+0.5),
                      255);
      }
    }
  }
  List<Detection> results;
  FuzzyVote2(width,height,1,alldetections,
             Informedia_SaveDetections,(ClientData)(&results),
             2,1,1,1,0,mask);
  counter=results.length;
  if (locs!=NULL)
  {
    if (counter==0) *locs=NULL; else
    {
      *locs=(struct FaceLocation*)malloc(sizeof(struct FaceLocation)*counter);
      int i=0;
      for (Detection *d=results.first; d!=NULL; d=d->next)
      {
        double s=pow(1.2,d->s);
        (*locs)[i].x1=(int)floor(d->x*s+0.5);
        (*locs)[i].y1=(int)floor(d->y*s+0.5);
        (*locs)[i].x2=(int)floor((d->x+20)*s+0.5);
        (*locs)[i].y2=(int)floor((d->y+20)*s+0.5);
        i++;
      }
    }
  }
  for (i=1; i<levels; i++) delete imagePyramid[i];
  delete[] imagePyramid;
  delete mainmask;
  delete levelmask;
  delete image;
  return counter;
}

int Xavier_FindOneFaceCrop(int width, int height, unsigned char *buffer, 
                           int minX, int maxX, int minY, int maxY,
                           int minSize, int maxSize,
                           int optimizationFlags,
                           struct FaceLocation *loc)
{
  Xavier_Init();
  ByteImage *image=new ByteImage(NULL);
  image->NewBuffer((unsigned char*)buffer,width,height);

  if (minSize<20) minSize=20;
  int fromX=minX-maxSize/2;
  int fromY=minY-maxSize/2;
  int toX=maxX+maxSize/2;
  int toY=maxY+maxSize/2;
  if (fromX<0) fromX=0;
  if (fromX>=width) fromX=width-1;
  if (fromY<0) fromY=0;
  if (fromY>=height) fromY=height-1;
  if (toX<fromX) toX=fromX;
  if (toY<fromY) toY=fromY;
  if (toX>=width) toX=width-1;
  if (toY>=height) toY=height-1;
  double reduceFactor=(double)minSize/20.0;
  double sizeFactor=(double)maxSize/(double)minSize;
  int levels=(int)(ceil(log(sizeFactor)/log(1.2)));

  minX=(int)(0.5+(minX-fromX)/reduceFactor);
  maxX=(int)(0.5+(maxX-fromX)/reduceFactor);
  minY=(int)(0.5+(minY-fromY)/reduceFactor);
  maxY=(int)(0.5+(maxY-fromY)/reduceFactor);

  ByteImage **imagePyramid=new ByteImage*[levels];
  imagePyramid[0]=new ByteImage(NULL);
  ExtractAndZoom(imagePyramid[0],image,reduceFactor,
                 fromX,fromY,toX,toY);

  for (int i=1; i<levels; i++)
  {
    imagePyramid[i]=new ByteImage(NULL);
    ReduceSize(imagePyramid[i],imagePyramid[i-1]);
  }

  int scaleRange=(optimizationFlags & Xavier_QuickVerify)?0:1;

  ByteImage *mask=FindByteImageWithName("facemask");
  List<Detection> alldetections[1];
  int found=0;
  for (int i=levels-1; i>=0 && !found; i--)
  {
    List<Detection> detections;
    SearchUmeEvenFasterRegion(imagePyramid[i],NULL,
                              minX,maxX,minY,maxY,i,
                              Informedia_SaveDetections,
                              (ClientData)(&detections));
    for (Detection* detect=detections.first; detect!=NULL && !found;
                                             detect=detect->next)
    {
      int newX, newY, newS;
      if (FindNewLocation(levels,imagePyramid,mask,
                          detect->x,detect->y-1,detect->s,
                          5,5,scaleRange,2,1,
                          &newX,&newY,&newS))
      {
        loc->x1=(int)(pow(1.2,newS)*newX*reduceFactor+fromX+0.5);
        loc->y1=(int)(pow(1.2,newS)*newY*reduceFactor+fromY+0.5);
        loc->x2=(int)(pow(1.2,newS)*(newX+20)*reduceFactor+fromX+0.5);
        loc->y2=(int)(pow(1.2,newS)*(newY+20)*reduceFactor+fromY+0.5);
        found=1;
      }
    }
  }
  for (int i=0; i<levels; i++) delete imagePyramid[i];
  delete[] imagePyramid;
 
  image->buffer=NULL;
  delete image;
  return found;
}

int Xavier_FindOneFace(int width, int height, unsigned char *buffer, 
                       int minX, int maxX, int minY, int maxY,
                       int minSize, int maxSize,
                       int optimizationFlags,
                       unsigned char *prevImage,
                       int changeThreshold,
                       struct FaceLocation *loc)
{
  if (optimizationFlags & Xavier_CropImage) 
    return Xavier_FindOneFaceCrop(width,height,buffer,
                                  minX,maxX,minY,maxY,minSize,maxSize,
                                  optimizationFlags,loc);

  Xavier_Init();
  ByteImage *image=new ByteImage(NULL);

  int i;

  image->NewBuffer((unsigned char*)buffer,width,height);

  int counter=0;
  int levels=0;
  int w=width, h=height;
  while (w>=20 && h>=20) {
    w=(int)(w/1.2);
    h=(int)(h/1.2);
    levels++;
  }

  int scaleRange=(optimizationFlags & Xavier_QuickVerify)?0:1;
  int searchRange=(optimizationFlags & Xavier_QuickVerifyNN)?1:5;

  int minLevel=(int)floor(log(minSize/20.0)/log(1.2));
  if (minLevel<0) minLevel=0;
  int maxLevel=(int)ceil(log(maxSize/20.0)/log(1.2));
  if (maxLevel>=levels) maxLevel=levels-1;
  if (levels>maxLevel+1+scaleRange) levels=maxLevel+1+scaleRange;

  ByteImage **imagePyramid=new ByteImage*[levels];
  imagePyramid[0]=image;
  for (int i=1; i<levels; i++)
  {
    imagePyramid[i]=new ByteImage(NULL);
    ReduceSize(imagePyramid[i],imagePyramid[i-1]);
  }

  ByteImage *levelmask=NULL;
  ByteImage *mainmask=NULL;
  if (prevImage!=NULL) {
    levelmask=new ByteImage(NULL);
    mainmask=new ByteImage(NULL);
    mainmask->ZeroBuffer(width,height,255);
    ByteImage *prev=new ByteImage(NULL);
    prev->NewBuffer(prevImage,width,height);
    FindMotion(mainmask,prev,imagePyramid[0],changeThreshold,0);
    prev->buffer=NULL;
    delete prev;
  }

  ByteImage *mask=FindByteImageWithName("facemask");
  List<Detection> alldetections[1];
  int found=0;
  for (int i=maxLevel; i>=minLevel; i--)
  {
    if (prevImage!=NULL) {
      ResampleByteImage(levelmask,mainmask,
                        imagePyramid[i]->width,imagePyramid[i]->height,
                        pow(1.2,-i));
    }
    List<Detection> detections;
    if (optimizationFlags & Xavier_QuickVerifyNN) {
      SearchUmeEvenFasterRegionPrecise(imagePyramid[i],levelmask,
                                       minX,maxX,minY,maxY,i,3,
                                       Informedia_SaveDetections,
                                       (ClientData)(&detections));
    } else {
      SearchUmeEvenFasterRegion(imagePyramid[i],levelmask,
                                minX,maxX,minY,maxY,i,
                                Informedia_SaveDetections,
                                (ClientData)(&detections));
    }
    for (Detection* detect=detections.first; detect!=NULL;
                                             detect=detect->next)
    {
      int newX, newY, newS;
      if (FindNewLocation(levels,imagePyramid,mask,
                          detect->x,detect->y,detect->s,
                          searchRange,searchRange,scaleRange,2,1,
                          &newX,&newY,&newS))
      {
        loc->x1=(int)(pow(1.2,newS)*newX+0.5);
        loc->y1=(int)(pow(1.2,newS)*newY+0.5);
        loc->x2=(int)(pow(1.2,newS)*(newX+20)+0.5);
        loc->y2=(int)(pow(1.2,newS)*(newY+20)+0.5);
        found=1;
        break;
      }
    }
    if (found) break;
  }
  for (int i=1; i<levels; i++) delete imagePyramid[i];
  delete[] imagePyramid;
 
  image->buffer=NULL;
  delete image;
  if (prevImage!=NULL) {
    delete levelmask;
    delete mainmask;
  }
  return found;
}

int Xavier_FindOneFaceColor(int width, int height, unsigned char *buffer, 
                            int minX, int maxX, int minY, int maxY,
                            int minSize, int maxSize,
                            int optimizationFlags,
                            unsigned char *prevImage,
                            int changeThreshold,
                            struct FaceLocation *loc)
{
  Xavier_Init();
  ByteImage *image=new ByteImage(NULL);

  unsigned char *newdata=(unsigned char*)malloc(width*height);
  unsigned char *iptr=buffer, *optr=newdata;
  for (int i=0; i<width*height; i++)
  {
    int val=(int)floor(0.5+
                       0.299*(*(iptr))+
                       0.587*(*(iptr+1))+
                       0.114*(*(iptr+2)));
    if (val>=255) val=255;
    *(optr++)=val;
    iptr+=3;
  }

  image->NewBuffer((unsigned char*)newdata,width,height);

  int counter=0;
  int levels=0;
  int w=width, h=height;
  while (w>=20 && h>=20) {
    w=(int)(w/1.2);
    h=(int)(h/1.2);
    levels++;
  }

  int scaleRange=(optimizationFlags & Xavier_QuickVerify)?0:1;
  int searchRange=(optimizationFlags & Xavier_QuickVerifyNN)?0:5;

  int minLevel=(int)floor(log(minSize/20.0)/log(1.2));
  if (minLevel<0) minLevel=0;
  int maxLevel=(int)ceil(log(maxSize/20.0)/log(1.2));
  if (maxLevel>=levels) maxLevel=levels-1;
  if (levels>maxLevel+1+scaleRange) levels=maxLevel+1+scaleRange;

  ByteImage **imagePyramid=new ByteImage*[levels];
  imagePyramid[0]=image;
  for (int i=1; i<levels; i++)
  {
    imagePyramid[i]=new ByteImage(NULL);
    ReduceSize(imagePyramid[i],imagePyramid[i-1]);
  }

  ByteImage *levelmask=new ByteImage(NULL);
  ByteImage *mainmask=new ByteImage(NULL);
  mainmask->ZeroBuffer(width,height,255);
  KDoiColorMask(buffer,width,height,mainmask,(prevImage==NULL)?0:192);
  if (0) {
    FILE *outf=fopen("mask2.pgm","w");
    SaveByteImagePgm(mainmask,outf);
    fclose(outf);
  }    
  if (prevImage!=NULL) {
    ByteImage *prev=new ByteImage(NULL);
    unsigned char *newdata=(unsigned char*)malloc(width*height);
    unsigned char *iptr=prevImage, *optr=newdata;
    for (int i=0; i<width*height; i++)
    {
      int val=(int)floor(0.5+
                         0.299*(*(iptr))+
                         0.587*(*(iptr+1))+
                         0.114*(*(iptr+2)));
      if (val>=255) val=255;
      *(optr++)=val;
      iptr+=3;
    }
    prev->NewBuffer(newdata,width,height);
    FindMotion(mainmask,prev,imagePyramid[0],changeThreshold,63);
    delete prev;
  }

  ByteImage *mask=FindByteImageWithName("facemask");
  List<Detection> alldetections[1];
  int found=0;
  for (int i=maxLevel; i>=minLevel; i--)
  {
    ResampleByteImage(levelmask,mainmask,
                      imagePyramid[i]->width,imagePyramid[i]->height,
                      pow(1.2,-i));

    List<Detection> detections;
    if (optimizationFlags & Xavier_QuickVerifyNN) {
      SearchUmeEvenFasterRegionPrecise(imagePyramid[i],levelmask,
                                       minX,maxX,minY,maxY,i,2,
                                       Informedia_SaveDetections,
                                       (ClientData)(&detections));
    } else {
      SearchUmeEvenFasterRegion(imagePyramid[i],levelmask,
                                minX,maxX,minY,maxY,i,
                                Informedia_SaveDetections,
                                (ClientData)(&detections));
    }
    for (Detection* detect=detections.first; detect!=NULL;
                                             detect=detect->next)
    {
      int newX, newY, newS;
      if (FindNewLocation(levels,imagePyramid,mask,
                          detect->x,detect->y,detect->s,
                          searchRange,searchRange,scaleRange,2,1,
                          &newX,&newY,&newS))
      {
        loc->x1=(int)(pow(1.2,newS)*newX+0.5);
        loc->y1=(int)(pow(1.2,newS)*newY+0.5);
        loc->x2=(int)(pow(1.2,newS)*(newX+20)+0.5);
        loc->y2=(int)(pow(1.2,newS)*(newY+20)+0.5);
        found=1;
        break;
      }
    }
    if (found) break;
  }
  for (int i=1; i<levels; i++) delete imagePyramid[i];
  delete[] imagePyramid;
 
  delete image;
  delete levelmask;
  delete mainmask;
  return found;
}

// USED
// Directory from which to load data files (network architectures, weights,
// mask files, etc)

// USED
// Initialize the networks used by the Track_FindAllFaces function
void Track_Init()
{
  static int initialized=0;
  if (initialized) return;
  Image_Init_NoTcl();                 // Initialize name->image mapping
  char *prevPath=getcwd(NULL,1024);
  chdir(Track_DetectorPath);
//  char *networks[]={"ume","face12","face13","eye"};
  char *networks[]={"umec","face17c","face18c","eye"};
  FastAllocateNetworks(4);
  FastInitNetwork(0,1,networks);      // network 0: umec
  FastInitNetwork(1,1,networks+1);    // network 1: face12 + face13
  FastInitNetwork(2,1,networks+2);    // network 1: face12 + face13
  FastInitNetwork(3,1,networks+3);    // network 2: eye
  ByteImage *mask=new ByteImage("facemask");  // Load oval face mask
  FILE *inf=fopen("facemask20x20.pgm","r");
  LoadByteImagePgm(mask,inf);
  fclose(inf);
  mask=new ByteImage("eyemask");      // Load rectangular eye mask
  inf=fopen("eyemask25x15.pgm","r");
  LoadByteImagePgm(mask,inf);
  fclose(inf);
  chdir(prevPath);
  free(prevPath);
  initialized=1;
}

// USED
// Function to count and locate all faces in an image.  Input buffer
// is an array of unsigned char, 1 byte per pixel indicating the
// intensity.  The width and height are the width and height in
// pixels.  The return value is the number of faces found.  If locs is
// NULL, the actual locations are discarded.  Otherwise, if no faces
// were found, *locs is set to NULL.  If faces were found, *locs is
// set to a pointer to an array of struct FaceLocation.  It is the
// responsibility of the caller to free() this array.  The structures
// will also contain the locations of the eyes, if they are found.
// The left and right designations are from the user's point of view.
// The flags left and right are set to 1 if that eye is detected, 0 if
// it is not detected, or -1 if the face is to small to attempt
// detection.
int Track_FindAllFaces(int width, int height, unsigned char *buffer, 
                       struct FaceEyeLocation **locs)
{
  Track_Init();

  ByteImage *image=new ByteImage(NULL);    // Create image object for input
  image->NewBuffer((unsigned char*)buffer,width,height);

  int levels=0;                            // Figure out # levels in pyramid
  int w=width, h=height;
  while (w>=20 && h>=20) {
    w=(int)(w/1.2);
    h=(int)(h/1.2);
    levels++;
  }

  ByteImage **imagePyramid=new ByteImage*[levels];  // Create pyramid
  imagePyramid[0]=image;
  for (int i=1; i<levels; i++)
  {
    imagePyramid[i]=new ByteImage(NULL);
    ReduceSize(imagePyramid[i],imagePyramid[i-1]);
  }

  ByteImage *mainmask=new ByteImage(NULL);  // Mask, 0=scan, 255=face found
  mainmask->ZeroBuffer(width,height);
  ByteImage *levelmask=new ByteImage(NULL); // Mask for current level
  ByteImage *mask=FindByteImageWithName("facemask");
  ByteImage *eyemask=FindByteImageWithName("eyemask");

  List<Detection> alldetections[1];         // Store detections
  for (int i=levels-1; i>=0; i--)
  {
    // Get search mask at right level
    ResampleByteImage(levelmask,mainmask,
                      imagePyramid[i]->width,imagePyramid[i]->height,
                      pow(1.2,-i));

    List<Detection> detections;             // Find candidates
    SearchUmeEvenFaster(imagePyramid[i],levelmask,i,
                        Informedia_SaveDetections,(ClientData)(&detections));

    for (Detection* detect=detections.first; detect!=NULL;
                                             detect=detect->next)
    {
      int newX, newY, newS;
      // Verify candidates
      if (FindNewLocation(levels,imagePyramid,mask,
                          detect->x,detect->y,detect->s,6,6,1,2,1,
                          &newX,&newY,&newS))
      {
	// Save verified candidate
        Informedia_SaveDetections((ClientData)alldetections,
                                 imagePyramid[newS],
                                 newX,newY,20,20,newS,
                                 pow(1.2,newS),1.0,0);
	// Put detection in search mask, to save computation
        FillRectangle(mainmask,
                      (int)(pow(1.2,newS)*newX+0.5),
                      (int)(pow(1.2,newS)*newY+0.5),
                      (int)(pow(1.2,newS)*(newX+20)+0.5),
                      (int)(pow(1.2,newS)*(newY+20)+0.5),
                      255);
      }
    }
  }

  // Remove overlapping detections (a few may slip through)
  List<Detection> results;
  FuzzyVote2(width,height,1,alldetections,
             Informedia_SaveDetections,(ClientData)(&results),
             2,1,1,1,0,mask);

  int counter=results.length;
  if (locs!=NULL)
  {
    if (counter==0) *locs=NULL; else
    {
      // Make output array
      *locs=(struct FaceEyeLocation*)
        malloc(sizeof(struct FaceEyeLocation)*counter);
      int i=0;
      for (Detection *d=results.first; d!=NULL; d=d->next)
      {
	// Check for eyes
        int bigenough=
          SearchEyes(levels,imagePyramid,eyemask,
                     d->x,d->y,d->s,3,
                     &((*locs)[i].rightx),
                     &((*locs)[i].righty),
                     &((*locs)[i].leftx),
                     &((*locs)[i].lefty));
        if (bigenough) {
	  // Set flags: 1=eye found, 0=not found
          (*locs)[i].left=((*locs)[i].leftx==-1)?0:1;
          (*locs)[i].right=((*locs)[i].rightx==-1)?0:1;
        } else {
	  // Set flags: -1=face too small
          (*locs)[i].left=-1;
          (*locs)[i].right=-1;
        }
	// Map face location into original resolution
	// (eye locations are already set appropriately)
        double s=pow(1.2,d->s);
        (*locs)[i].x1=(int)floor(d->x*s+0.5);
        (*locs)[i].y1=(int)floor(d->y*s+0.5);
        (*locs)[i].x2=(int)floor((d->x+20)*s+0.5);
        (*locs)[i].y2=(int)floor((d->y+20)*s+0.5);
        i++;
      }
    }
  }

  // Clean up
  for (int i=1; i<levels; i++) delete imagePyramid[i];
  delete[] imagePyramid;
  delete mainmask;
  delete levelmask;
 
  image->buffer=NULL;
  delete image;
  return counter;
}

QList<AlgDetOutput> Track_FindAllFacesRegion( const QSize& MinObjSize, int width, int height, char* buffer )
{
  Track_Init();
  ByteImage *image=new ByteImage(NULL);

  const int minSize(qMin(MinObjSize.width(), MinObjSize.height()));
  const int maxSize(qMin(width, height));
  const int minX(0);
  const int maxX(width);
  const int minY(0);
  const int maxY(height);

  int i;

  image->NewBuffer((unsigned char*)buffer,width,height);

  int levels=0;
  int w=width, h=height;
  while (w>=20 && h>=20) {
    w=(int)(w/1.2);
    h=(int)(h/1.2);
    levels++;
  }

  int scaleRange=1;
  int minLevel=(int)floor(log(minSize/20.0)/log(1.2));
  if (minLevel<0) minLevel=0;
  int maxLevel=(int)ceil(log(maxSize/20.0)/log(1.2));
  if (maxLevel>=levels) maxLevel=levels-1;
  if (levels>maxLevel+1+scaleRange) levels=maxLevel+1+scaleRange;

  ByteImage *mainmask=new ByteImage(NULL);
  ByteImage **imagePyramid=new ByteImage*[levels];
  imagePyramid[0]=image;
  for (int i=1; i<levels; i++)
  {
    imagePyramid[i]=new ByteImage(NULL);
    ReduceSize(imagePyramid[i],imagePyramid[i-1]);
  }
  mainmask->ZeroBuffer(width,height);
  ByteImage *levelmask=new ByteImage(NULL);
  ByteImage *mask=FindByteImageWithName("facemask");
  ByteImage *eyemask=FindByteImageWithName("eyemask");
  List<Detection> alldetections[1];
  for (int i=maxLevel; i>=minLevel; i--)
  {
    ResampleByteImage(levelmask,mainmask,
                      imagePyramid[i]->width,imagePyramid[i]->height,
                      pow(1.2,-i));
    List<Detection> detections;
    SearchUmeEvenFasterRegion(imagePyramid[i],levelmask,
                              minX,maxX,minY,maxY,i,
                              Informedia_SaveDetections,
                              (ClientData)(&detections));
    for (Detection* detect=detections.first; detect!=NULL;
                                             detect=detect->next)
    {
      int newX, newY, newS;
      if (FindNewLocation(levels,imagePyramid,mask,
                          detect->x,detect->y,detect->s,6,6,1,2,1,
                          &newX,&newY,&newS))
      {
        Informedia_SaveDetections((ClientData)alldetections,
                                 imagePyramid[newS],
                                 newX,newY,20,20,newS,
                                 pow(1.2,newS),1.0,0);
        FillRectangle(mainmask,
                      (int)(pow(1.2,newS)*newX+0.5),
                      (int)(pow(1.2,newS)*newY+0.5),
                      (int)(pow(1.2,newS)*(newX+20)+0.5),
                      (int)(pow(1.2,newS)*(newY+20)+0.5),
                      255);
      }
    }
  }
  List<Detection> results;
  FuzzyVote2(width,height,1,alldetections,
             Informedia_SaveDetections,(ClientData)(&results),
             2,1,1,1,0,mask);
  QList<AlgDetOutput> foundObjs;
  for (Detection *d=results.first; d!=NULL; d=d->next)
  {
	  FaceEyeLocation location;
		int found = SearchEyes(levels,imagePyramid,eyemask,
					 d->x,d->y,d->s,3,
					 &(location.rightx),
					 &(location.righty),
					 &(location.leftx),
					 &(location.lefty));
    if (found) {
      location.left=(location.leftx==-1)?0:1;
      location.right=(location.rightx==-1)?0:1;
    } else {
      location.left=-1;
      location.right=-1;
    }
    double s=pow(1.2,d->s);
    location.x1=(int)floor(d->x*s+0.5);
    location.y1=(int)floor(d->y*s+0.5);
    location.x2=(int)floor((d->x+20)*s+0.5);
    location.y2=(int)floor((d->y+20)*s+0.5);
    AlgDetOutput objLoc;
    objLoc.Rectangle.setLeft(location.x1);
    objLoc.Rectangle.setTop(location.y1);
    objLoc.Rectangle.setRight(location.x2);
    objLoc.Rectangle.setBottom(location.y2);
    if (location.left == 1)
    {
      objLoc.Points.insert(algorithms::detection::LeftEyePoint, QPoint(location.leftx, location.lefty));
    }
    if (location.right == 1)
    {
      objLoc.Points.insert(algorithms::detection::RightEyePoint, QPoint(location.rightx, location.righty));
    }
    foundObjs << objLoc;
  }

  for (int i=1; i<levels; i++) delete imagePyramid[i];
  delete[] imagePyramid;
  delete mainmask;
  delete levelmask;
 
  image->buffer=NULL;
  delete image;
  return foundObjs;
}


void Siemens_Init()
{
  static int initialized=0;
  if (initialized) return;
  Image_Init_NoTcl();
  char *prevPath=getcwd(NULL,1024);
  chdir(Track_DetectorPath);
//  char *networks[]={"ume","face12","face13","eye"};
  char *networks[]={"umec","face17c","face18c","eye"};
  FastAllocateNetworks(4);
  FastInitNetwork(0,1,networks);
  FastInitNetwork(1,1,networks+1);
  FastInitNetwork(2,1,networks+2);
  FastInitNetwork(3,1,networks+3);
  ByteImage *mask=new ByteImage("facemask");
  FILE *inf=fopen("facemask20x20.pgm","r");
  LoadByteImagePgm(mask,inf);
  fclose(inf);
  mask=new ByteImage("eyemask");
  inf=fopen("eyemask25x15.pgm","r");
  LoadByteImagePgm(mask,inf);
  fclose(inf);
  chdir(prevPath);
  free(prevPath);
  initialized=1;
}

int Siemens_FindAllFaces(int width, int height, unsigned char *buffer, 
                         unsigned char *motionMask,
                         struct FaceEyeLocation **locs)
{
  Track_Init();
  ByteImage *image=new ByteImage(NULL);

  int i;

  image->NewBuffer((unsigned char*)buffer,width,height);

  int counter=0;
  int levels=0;
  int w=width, h=height;
  while (w>=20 && h>=20) {
    w=(int)(w/1.2);
    h=(int)(h/1.2);
    levels++;
  }
  ByteImage *mainmask=new ByteImage(NULL);
  ByteImage **imagePyramid=new ByteImage*[levels];
  imagePyramid[0]=image;
  for (i=1; i<levels; i++)
  {
    imagePyramid[i]=new ByteImage(NULL);
    ReduceSize(imagePyramid[i],imagePyramid[i-1]);
  }
  if (motionMask!=NULL)
    mainmask->NewBuffer(motionMask,width,height); else
      mainmask->ZeroBuffer(width,height);
  ByteImage *levelmask=new ByteImage(NULL);
  ByteImage *mask=FindByteImageWithName("facemask");
  ByteImage *eyemask=FindByteImageWithName("eyemask");
  List<Detection> alldetections[1];
  for (i=levels-1; i>=0; i--)
  {
    ResampleByteImage(levelmask,mainmask,
                      imagePyramid[i]->width,imagePyramid[i]->height,
                      pow(1.2,-i));
    List<Detection> detections;
    SearchUmeEvenFaster(imagePyramid[i],levelmask,i,
                        Informedia_SaveDetections,(ClientData)(&detections));
    for (Detection* detect=detections.first; detect!=NULL;
                                             detect=detect->next)
    {
      int newX, newY, newS;
      if (FindNewLocation(levels,imagePyramid,mask,
                          detect->x,detect->y,detect->s,6,6,1,2,1,
                          &newX,&newY,&newS))
      {
        Informedia_SaveDetections((ClientData)alldetections,
                                 imagePyramid[newS],
                                 newX,newY,20,20,newS,
                                 pow(1.2,newS),1.0,0);
        FillRectangle(mainmask,
                      (int)(pow(1.2,newS)*newX+0.5),
                      (int)(pow(1.2,newS)*newY+0.5),
                      (int)(pow(1.2,newS)*(newX+20)+0.5),
                      (int)(pow(1.2,newS)*(newY+20)+0.5),
                      255);
      }
    }
  }
  List<Detection> results;
  FuzzyVote2(width,height,1,alldetections,
             Informedia_SaveDetections,(ClientData)(&results),
             2,1,1,1,0,mask);
  counter=results.length;
  if (locs!=NULL)
  {
    if (counter==0) *locs=NULL; else
    {
      *locs=(struct FaceEyeLocation*)
        malloc(sizeof(struct FaceEyeLocation)*counter);
      int i=0;
      for (Detection *d=results.first; d!=NULL; d=d->next)
      {
        int found=
          SearchEyes(levels,imagePyramid,eyemask,
                     d->x,d->y,d->s,3,
                     &((*locs)[i].rightx),
                     &((*locs)[i].righty),
                     &((*locs)[i].leftx),
                     &((*locs)[i].lefty));
        if (found) {
          (*locs)[i].left=((*locs)[i].leftx==-1)?0:1;
          (*locs)[i].right=((*locs)[i].rightx==-1)?0:1;
        } else {
          (*locs)[i].left=-1;
          (*locs)[i].right=-1;
        }
        double s=pow(1.2,d->s);
        (*locs)[i].x1=(int)floor(d->x*s+0.5);
        (*locs)[i].y1=(int)floor(d->y*s+0.5);
        (*locs)[i].x2=(int)floor((d->x+20)*s+0.5);
        (*locs)[i].y2=(int)floor((d->y+20)*s+0.5);
        i++;
      }
    }
  }
  for (i=1; i<levels; i++) delete imagePyramid[i];
  delete[] imagePyramid;
  if (motionMask!=NULL) mainmask->buffer=NULL;
  delete mainmask;
  delete levelmask;
 
  image->buffer=NULL;
  delete image;
  return counter;
}


void Astro_Init()
{
  static int initialized=0;
  if (initialized) return;
  Image_Init_NoTcl();
  char *prevPath=getcwd(NULL,1024);
  chdir(Astro_DetectorPath);
  ByteImage *mask=new ByteImage("facemask");
  FILE *inf=fopen("facemask20x20.pgm","r");
  LoadByteImagePgm(mask,inf);
  fclose(inf);
  chdir(prevPath);
  free(prevPath);
  initialized=1;
}

int Astro_FindAllFaces(int width, int height, unsigned char *buffer, 
                       struct FaceLocation **locs)
{
  Astro_Init();
  ByteImage *image=new ByteImage(NULL);
  image->NewBuffer(buffer,width,height);
  List<Detection> results;
  SearchAstro(image,Informedia_SaveDetections,(ClientData)(&results));
  if (locs!=NULL)
  {
    if (results.length==0) *locs=NULL; else
    {
      *locs=(struct FaceLocation*)
        malloc(sizeof(struct FaceLocation)*results.length);
      int i=0;
      for (Detection *d=results.first; d!=NULL; d=d->next)
      {
        double s=pow(1.2,d->s);
        (*locs)[i].x1=(int)floor(d->x*s+0.5);
        (*locs)[i].y1=(int)floor(d->y*s+0.5);
        (*locs)[i].x2=(int)floor((d->x+20)*s+0.5);
        (*locs)[i].y2=(int)floor((d->y+20)*s+0.5);
        i++;
      }
    }
  }
  image->buffer=NULL;
  delete image;
  return results.length;
}

int Rotation_FindAllFacesSlow(int width, int height, unsigned char *buffer,
                              struct FaceLocationRotation **locs)
{
  static int initialized=0;
  if (!initialized) {
    Image_Init_NoTcl();
    char *prevPath=getcwd(NULL,1024);
    chdir(Rotation_DetectorPath);
    FastAllocateNetworks(3);
    char *networks[]={"face-with-rot-1","face-with-rot-2","facerot-angle-3b"};
    FastInitNetwork(0,1,networks);
    FastInitNetwork(1,1,networks+1);
    FastInitNetwork(2,1,networks+2);
    ByteImage *mask=new ByteImage("facemask");
    FILE *inf=fopen("facemask20x20.pgm","r");
    LoadByteImagePgm(mask,inf);
    fclose(inf);
    chdir(prevPath);
    free(prevPath);
  }

  ByteImage *image=new ByteImage(NULL);
  unsigned char *buf=image->AllocBuffer(width,height);
  memcpy(buf,buffer,width*height);
  image->NewBuffer(buf,width,height);

  List<Detection> detections[5];
  List<Detection> *index[5];
  for (int i=0; i<5; i++) index[i]=detections+i;
  SearchMultiOrientation(image,2,2,
			 Informedia_SaveDetections,
                         (ClientData*)index);
  DetectionListCornerToCenter(index[0]);
  DetectionListCornerToCenter(index[1]);
  NewFuzzyVote3(detections+2,detections+0,1,width,height,20,20,4,1,1);
  NewFuzzyVote3(detections+3,detections+1,1,width,height,20,20,4,1,1);
  NewFuzzyVote3(detections+4,detections+2,2,width,height,20,20,4,2,1);
  int number=detections[4].length;
  if (number==0) {
    *locs=NULL; 
  } else {
    *locs=(struct FaceLocationRotation*)malloc(
      sizeof(struct FaceLocationRotation)*number);
    Detection *d=detections[4].first;
    for (int i=0; i<number; i++) {
      double s=pow(1.2,d->s);
      (*locs)[i].x=(int)floor(d->x*s+0.5);
      (*locs)[i].y=(int)floor(d->y*s+0.5);
      (*locs)[i].angle=M_PI/180.0*d->orient;
      (*locs)[i].size=(int)floor(20*s);
      d=d->next;
    }
  }

  delete image;
  return number;
}

int Rotation_FindAllFacesSlowExtract(int width, int height, 
                                     unsigned char *buffer,
                                     double threshold, int arbThreshold,
                                     struct FaceLocationRotationExtract **locs)
{
  static int initialized=0;
  if (!initialized) {
    Image_Init_NoTcl();
    char *prevPath=getcwd(NULL,1024);
    chdir(Rotation_DetectorPath);
    FastAllocateNetworks(3);
    char *networks[]={"face-with-rot-1","face-with-rot-2","facerot-angle-3b"};
    FastInitNetwork(0,1,networks);
    FastInitNetwork(1,1,networks+1);
    FastInitNetwork(2,1,networks+2);
    ByteImage *mask=new ByteImage("facemask");
    FILE *inf=fopen("facemask20x20.pgm","r");
    LoadByteImagePgm(mask,inf);
    fclose(inf);
    chdir(prevPath);
    free(prevPath);
  }

  ByteImage *image=new ByteImage(NULL);
  unsigned char *buf=image->AllocBuffer(width,height);
  memcpy(buf,buffer,width*height);
  image->NewBuffer(buf,width,height);

  int levels=0;
  int w=width, h=height;
  while (w>=20 && h>=20) {
    w=(int)(w/1.2);
    h=(int)(h/1.2);
    levels++;
  }
  ByteImage **imagePyramid=new ByteImage*[levels];
  imagePyramid[0]=new ByteImage(NULL);
  buf=image->AllocBuffer(width,height);
  memcpy(buf,buffer,width*height);
  imagePyramid[0]->NewBuffer(buf,width,height);
  for (int i=1; i<levels; i++) {
    imagePyramid[i]=new ByteImage(NULL);
    ReduceSize(imagePyramid[i],imagePyramid[i-1]);
  }

  List<Detection> detections[5];
  List<Detection> *index[5];
  for (int i=0; i<5; i++) index[i]=detections+i;
  SearchMultiOrientation(image,2,2,
			 Informedia_SaveDetections,
                         (ClientData*)index,
                         threshold);
  DetectionListCornerToCenter(index[0]);
  DetectionListCornerToCenter(index[1]);
  NewFuzzyVote3(detections+2,detections+0,1,width,height,20,20,4,1,1);
  NewFuzzyVote3(detections+3,detections+1,1,width,height,20,20,4,1,1);
  NewFuzzyVote3(detections+4,detections+2,2,width,height,20,20,4,
                arbThreshold,1);
  int number=detections[4].length;
  ByteImage *extracted=new ByteImage(NULL);
  extracted->ZeroBuffer(20,20);
  if (number==0) {
    *locs=NULL; 
  } else {
    *locs=(struct FaceLocationRotationExtract*)malloc(
      sizeof(struct FaceLocationRotationExtract)*number);
    Detection *d=detections[4].first;
    for (int i=0; i<number; i++) {
      double s=pow(1.2,d->s);
      (*locs)[i].x=(int)floor(d->x*s+0.5);
      (*locs)[i].y=(int)floor(d->y*s+0.5);
      (*locs)[i].angle=M_PI/180.0*d->orient;
      (*locs)[i].size=(int)floor(20*s);
      ExtractAndRotate(extracted,imagePyramid[d->s],
                       d->x,d->y,
                       20,20,M_PI/180.0*d->orient);
      (*locs)[i].extracted=(unsigned char*)malloc(400);
      memcpy((*locs)[i].extracted,extracted->buffer,400);
      d=d->next;
    }
  }

  delete image;
  delete extracted;

  for (int i=0; i<levels; i++) delete imagePyramid[i];
  delete[] imagePyramid;
  return number;
}

#ifndef Library
int main(int argc, char *argv[])
{
  Byte buf[352*240*3];
#ifndef Albert
  while (1) {
    if (fread(&buf,1,15,stdin)!=15) break;
    if (fread(&buf,1,352*240*3,stdin)!=3*352*240) break;
#endif
    fprintf(stderr,"%d faces detected.\n",
            Informedia_FindFaces(352,240,(char*)buf));
#ifndef Albert
  }
#endif
  return 0;
}
#endif

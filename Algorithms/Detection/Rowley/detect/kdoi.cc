#include <stdlib.h>
#include <math.h>
#include "../detect.h"
#include "img.hpp"
#include "kdoi.hpp"
#include "maincore.h"
#include "tool.h"
#include "ip.h"
#define Threshold 0.1

// These parameters define the gaussian hue model
extern double gEx;
extern double gEy; 
extern double gExx;
extern double gEyy;
extern double gExy;
extern double gA11;
extern double gA12;
extern double gA22;
extern double gDet;

BOOL BuildModel(char *path);
void ClassfyImage( unsigned long*, int ,int );
unsigned long *Expansion4( unsigned long *pInbuf, int width, int height );
extern int gRegionCnt;
extern RectREC gRect[1000];

// USED
// Load in the images with examples of skin color.  The path parameter
// gives a file name which contains a list of .ppm image files to load.
void KDoiInit(char *path) 
{
  BuildModel(path);
}

// USED
// Given a color image as input (3 consecutive bytes per pixel),
// classify each pixel as containing skin color or not.  Then compute
// connected regions of skin color, and find their bounding rectangles.
// Mark those rectangles in the given mask image.
void KDoiColorMask(unsigned char *input, int gXsize, int gYsize,
                   ByteImage *image, int maskValue)
{
  int i, j, tmp, tmp1, tmp2, tmp3, tmp4;
  int delta;
  unsigned int ct, sum, size;
  unsigned char r, g;
  double xEx, yEy;
  unsigned char *ptr;
  unsigned char *ptrct, *endptr;
  unsigned long  *pWorkBuf, *pWorkBuf2;
  int width = (gXsize+1)/2, height = (gYsize+1)/2;
 
  size = width*height;
  pWorkBuf = (unsigned long*)calloc( sizeof(unsigned long), size );

  delta = 3*gXsize;
  ptr = input;
  endptr = ptr+delta*gYsize;
  ptrct = ptr+delta;

  i = 0;
  // Classify each pixel
  while( ptr<endptr ) {
    for( ; ptr<ptrct; ptr+=3*2, i++ ) {
      sum = ( r = *(ptr+0) ) +
        ( g = *(ptr+1) ) +
        *(ptr+2);
      if( sum < 50 )
        continue;
      xEx = ((double)r)/sum - gEx;
      yEy = ((double)g)/sum - gEy;
      if( xEx*(xEx*gA22-yEy*gA12)+yEy*yEy<gDet )
        *(pWorkBuf+i) = 1; else
          *(pWorkBuf+i) = 0;
    }
    ptr = ptrct+delta;
    ptrct = ptr+delta;
  }

  // Expand the skin color regions
  pWorkBuf = Expansion4( pWorkBuf, width, height );

  // Compute connected components, placing result in a global array
  ClassfyImage( pWorkBuf, width, height );
  free(pWorkBuf);
  //  fprintf(stderr,"Region count = %d\n",gRegionCnt);

  // Mark connected rectangles
  for (i=0; i<gRegionCnt; i++) {
    int x1=gRect[i].sx*2;
    int x2=gRect[i].ex*2;
    int y1=gRect[i].sy*2;
    int y2=gRect[i].ey*2;
    if (x1<0) x1=0;
    if (x1>=image->width) x1=image->width-1;
    if (x2<0) x2=0;
    if (x2>=image->width) x2=image->width-1;
    if (y1<0) y1=0;
    if (y1>=image->height) y1=image->height-1;
    if (y2<0) y2=0;
    if (y2>=image->height) y2=image->height-1;
    //    fprintf(stderr,"  (%d,%d) - (%d,%d)\n",x1,y1,x2,y2);
    for (int y=y1; y<=y2; y++) for (int x=x1; x<=x2; x++)
      image->data(x,y) &= maskValue;
  }
  image->Change();
}

void InvertColorCovariance()
{
  gA11 = gExx-gEx*gEx;
  gA12 = gExy-gEx*gEy;
  gA22 = gEyy-gEy*gEy;
  gDet = 2*(gA11*gA22-gA12*gA12);
    
  gA12 = 2*gA12/gA11;
  gA22 /= gA11;
  gDet /= gA11;
}

void EmptyColorMask()
{
  gEx=gEy=0.25;
  gExx=gEyy=0.625;
  gExy=0;
  InvertColorCovariance();
}

void BroadenColorMask(double amount)
{
  double u=0.25, v=0.25;
  double uu=0.625, uv=0, vv=0.625;
  gEx = gEx*(1-amount)+u*amount;
  gEy = gEy*(1-amount)+v*amount;
  gExx = gExx*(1-amount)+uu*amount;
  gExy = gExy*(1-amount)+uv*amount;
  gEyy = gEyy*(1-amount)+vv*amount;
  InvertColorCovariance();
}

void UpdateColorMaskFromBuffer(int width, int height,
                               unsigned char *buffer,
                               int x1, int y1, int x2, int y2,
                               double amount)
{
  double u=0, v=0, uu=0, vv=0, uv=0, tot=0;
  for (int j=y1; j<=y2; j++) if (j>=0 && j<height)
    for (int i=x1; i<=x2; i++) if (i>=0 && i<=width) {
      int r=buffer[j*width*3+i];
      int g=buffer[j*width*3+i+1];
      int b=buffer[j*width*3+i+2];
      int sum=r+g+b;
      if (sum>=50) {
        double thisu=r/(double)sum;
        double thisv=g/(double)sum;
        u+=thisu;
        v+=thisv;
        uu+=thisu*thisu;
        vv+=thisv*thisv;
        uv+=thisu*thisv;
        tot++;
      }
    }
  if (tot==0) tot=1;
  u/=tot;
  v/=tot;
  uu/=tot;
  uv/=tot;
  vv/=tot;

  gEx = gEx*(1-amount)+u*amount;
  gEy = gEy*(1-amount)+v*amount;
  gExx = gExx*(1-amount)+uu*amount;
  gExy = gExy*(1-amount)+uv*amount;
  gEyy = gEyy*(1-amount)+vv*amount;

  InvertColorCovariance();
}

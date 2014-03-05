extern "C"
{
#if !defined(hpux) && !defined(WINNT)
#include <math.h>
#endif
#include <assert.h>
#ifndef __GNUG__
#include <string.h>
#endif
}
#if defined(hpux) || defined(WINNT)
#include <math.h>
#endif
#ifdef __GNUG__
#include <string.h>
#endif

#include "myhebp.hpp"
#include "system.hpp"
#include "mat.hpp"
#include "img.hpp"
#include "faces.hpp"
#include "fft.hpp"
#include "follow.hpp"
//#define Test

//#define sqr(num) ((num)*(num))

#ifndef M_PI
#define M_PI       3.14159265358979323846
#endif

struct FloatInt {
  float quality;
  int index;
};

int CompareFloatIntDecreasing(const void *p1, const void *p2)
{
  const FloatInt *fi1=(const FloatInt *)p1;
  const FloatInt *fi2=(const FloatInt *)p2;
  if (fi1->quality>fi2->quality) return -1;
  if (fi1->quality<fi2->quality) return 1;
  return 0;
}

int CompareFloatIntIncreasing(const void *p1, const void *p2)
{
  const FloatInt *fi1=(const FloatInt *)p1;
  const FloatInt *fi2=(const FloatInt *)p2;
  if (fi1->quality>fi2->quality) return 1;
  if (fi1->quality<fi2->quality) return -1;
  return 0;
}

// USED
// Given the alignment data structure and a vector of features for a
// face, return the scale and position and which the face should be
// detected.  Note: the position returned is the center of the face
// (and assumes the window is 20x20 pixels).
void CorrectFaceDetection(Alignment *alignment, double *features,
                          int *x, int *y, int *s, int *angle)
{
  // Compute least squares transformation between the features and the
  // average feature locations in the alignment structure
  Mat mat=Zero(alignment->numFeatures*2,4);
  Vec vec=Zero(alignment->numFeatures*2);
  for (int feature=0; feature<alignment->numFeatures; feature++) {
    double x=features[feature*2];
    double y=features[feature*2+1];
    mat(feature*2,0)=x;
    mat(feature*2,1)=-y;
    mat(feature*2,2)=1;
    mat(feature*2,3)=0;
    mat(feature*2+1,0)=y;
    mat(feature*2+1,1)=x;
    mat(feature*2+1,2)=0;
    mat(feature*2+1,3)=1;
    vec(feature*2)=alignment->average[feature*2];
    vec(feature*2+1)=alignment->average[feature*2+1];
  }
  Vec ans=LUInverse(Transpose(mat)*mat)*(Transpose(mat)*vec);

  // Apply that transformation to the center of the face (10,10)
  Mat xform=Identity(3);
  xform(0,0)=ans(0);
  xform(0,1)=-ans(1);
  xform(0,2)=ans(2);
  xform(1,0)=ans(1);
  xform(1,1)=ans(0);
  xform(1,2)=ans(3);
  xform=LUInverse(xform);
  Vec pt(3);
  pt(0)=10; pt(1)=10; pt(2)=1;
  pt=xform*pt;
  double xx=pt(0);
  double yy=pt(1);

  Vec pt1(3);
  pt1(0)=10; pt1(1)=20; pt1(2)=1;
  pt1=xform*pt1-pt;

  // Compute how the transformation scales the face, convert to level in
  // image pyramid
  double ss=sqrt(xform(0,0)*xform(1,1)-xform(0,1)*xform(1,0));
  ss=log(ss)/log(1.2);

  // Return the results
  *s=(int)floor(0.5+ss);
  if (*s<0) *s=0;
  *x=(int)floor(0.5+xx/pow(1.2,*s));
  *y=(int)floor(0.5+yy/pow(1.2,*s));
  *angle=(int)floor((atan2(double(pt1(1)),double(pt1(0)))-atan2(double(1),double(0)))*180.0/M_PI+0.5);
  while (*angle<0) *angle+=360;
  *angle=(*angle) % 360;
}

void CorrectFaceDetectionValid(Alignment *alignment, double *features,
                               int *valid,
                               int *x, int *y, int *s, int *angle)
{
  // Compute least squares transformation between the features and the
  // average feature locations in the alignment structure
  
  int numFeatures=0;
  for (int i=0; i<alignment->numFeatures; i++) 
    if (valid[i]) numFeatures++;

  Mat mat=Zero(numFeatures*2,4);
  Vec vec=Zero(numFeatures*2);
  int ptr=0;
  for (int feature=0; feature<alignment->numFeatures; feature++) 
    if (valid[feature]) {
      double x=features[feature*2];
      double y=features[feature*2+1];
      mat(ptr*2,0)=x;
      mat(ptr*2,1)=-y;
      mat(ptr*2,2)=1;
      mat(ptr*2,3)=0;
      mat(ptr*2+1,0)=y;
      mat(ptr*2+1,1)=x;
      mat(ptr*2+1,2)=0;
      mat(ptr*2+1,3)=1;
      vec(ptr*2)=alignment->average[feature*2];
      vec(ptr*2+1)=alignment->average[feature*2+1];
      ptr++;
    }
  Vec ans=LUInverse(Transpose(mat)*mat)*(Transpose(mat)*vec);

  // Apply that transformation to the center of the face (10,10)
  Mat xform=Identity(3);
  xform(0,0)=ans(0);
  xform(0,1)=-ans(1);
  xform(0,2)=ans(2);
  xform(1,0)=ans(1);
  xform(1,1)=ans(0);
  xform(1,2)=ans(3);
  xform=LUInverse(xform);
  Vec pt(3);
  pt(0)=10; pt(1)=10; pt(2)=1;
  pt=xform*pt;
  double xx=pt(0);
  double yy=pt(1);

  Vec pt1(3);
  pt1(0)=10; pt1(1)=20; pt1(2)=1;
  pt1=xform*pt1-pt;

  // Compute how the transformation scales the face, convert to level in
  // image pyramid
  double ss=sqrt(xform(0,0)*xform(1,1)-xform(0,1)*xform(1,0));
  ss=log(ss)/log(1.2);

  // Return the results
  *s=(int)floor(0.5+ss);
  if (*s<0) *s=0;
  *x=(int)floor(0.5+xx/pow(1.2,*s));
  *y=(int)floor(0.5+yy/pow(1.2,*s));
  *angle=(int)floor((atan2(double(pt1(1)),double(pt1(0)))-atan2(double(1), double(0)))*180.0/M_PI+0.5);
  while (*angle<0) *angle+=360;
  *angle=(*angle) % 360;
}

double GetAlignmentAngle(Alignment *alignment, int face)
{
  double a=alignment->xform[face*4];
  double b=alignment->xform[face*4+1];
  return atan2(b,a)*180.0/M_PI;
}

// USED
// Get X position of a feature of a face, under the current alignment 
// transformation
double GetAlignmentX(Alignment *alignment, int face, int feature)
{
  double x=alignment->data[face*alignment->numFeatures*2+feature*2];
  double y=alignment->data[face*alignment->numFeatures*2+feature*2+1];
  double a=alignment->xform[face*4];
  double b=alignment->xform[face*4+1];
  double c=alignment->xform[face*4+2];
  double d=alignment->xform[face*4+3];
  double xx=a*x-b*y+c;
  double yy=b*x+a*y+d;
  return xx;
}

// USED
// Get Y position of a feature of a face, under the current alignment
// transformation
double GetAlignmentY(Alignment *alignment, int face, int feature)
{
  double x=alignment->data[face*alignment->numFeatures*2+feature*2];
  double y=alignment->data[face*alignment->numFeatures*2+feature*2+1];
  double a=alignment->xform[face*4];
  double b=alignment->xform[face*4+1];
  double c=alignment->xform[face*4+2];
  double d=alignment->xform[face*4+3];
  double xx=a*x-b*y+c;
  double yy=b*x+a*y+d;
  return yy;
}

double GetAlignmentEntry(Alignment *alignment, int face, int component)
{
  return alignment->xform[face*4+component];
}

// USED
// Create data structure used by example alignment code
Alignment *InitAlignment(int numFaces, int numFeatures)
{
  Alignment *alignment=new Alignment;
  alignment->numFaces=numFaces;
  alignment->numFeatures=numFeatures;
  alignment->average=new double[numFeatures*2];
  alignment->data=new double[numFeatures*numFaces*2];
  alignment->xform=new double[numFaces*4];
  alignment->valid=new int[numFeatures*numFaces];
  alignment->avgValid=new int[numFeatures];
  for (int i=0; i<numFeatures*numFaces; i++) alignment->valid[i]=1;
  for (int i=0; i<numFeatures*2*numFaces; i++) alignment->data[i]=0;
  for (int i=0; i<numFeatures*2; i++) alignment->average[i]=0;
  for (int i=0; i<numFeatures; i++) alignment->avgValid[i]=0;
  return alignment;
}

// USED
// Copy average facial feature locations from another alignment structure
void CopyAverageFeatures(Alignment *align, Alignment *other)
{
  for (int i=0; i<align->numFeatures*2; i++) 
    align->average[i]=other->average[i];
  for (int i=0; i<align->numFeatures; i++)
    align->avgValid[i]=other->avgValid[i];
}

// USED
// Free up the alignment information
void FreeAlignment(Alignment *alignment)
{
  delete[] alignment->average;
  delete[] alignment->data;
  delete[] alignment->xform;
  delete[] alignment->valid;
  delete[] alignment->avgValid;
  delete alignment;
}

// USED
// Set location of a feature of a face
void SetFaceFeature(Alignment *alignment, int face, int feature,
                    double x, double y, int fixscale)
{
  if (fixscale) x*=640.0/512.0;
  alignment->data[face*alignment->numFeatures*2+feature*2]=x;
  alignment->data[face*alignment->numFeatures*2+feature*2+1]=y;
}

void SetFaceFeatureValid(Alignment *alignment, int face, int feature, 
                         int valid)
{
  alignment->valid[face*alignment->numFeatures+feature]=valid;
}

// USED
// Initialize the alignment transformations to identity
void RunAlignmentInit(Alignment *alignment)
{
  int i;
  for (i=0; i<alignment->numFeatures; i++) 
    alignment->avgValid[i]=alignment->valid[i];
  for (i=0; i<alignment->numFeatures*2; i++) 
    alignment->average[i]=alignment->data[i];
  for (i=0; i<alignment->numFaces; i++) {
    alignment->xform[i*4]=1;
    alignment->xform[i*4]=0;
    alignment->xform[i*4]=0;
    alignment->xform[i*4]=0;
  }
}

// USED
// Compute the average position of each feature over all the faces, 
// using their current alignments
void RunAlignmentAverage(Alignment *alignment)
{
  int i=0; 
  int *samples=new int[alignment->numFeatures];
  for (i=0; i<alignment->numFeatures*2; i++) alignment->average[i]=0;
  for (i=0; i<alignment->numFeatures; i++) samples[i]=0;
  for (int face=0; face<alignment->numFaces; face++) {
    // Get transformation
    double a=alignment->xform[face*4];
    double b=alignment->xform[face*4+1];
    double c=alignment->xform[face*4+2];
    double d=alignment->xform[face*4+3];
    for (int feature=0; feature<alignment->numFeatures; feature++) {
      if (alignment->valid[face*alignment->numFeatures+feature]) {
        double x=alignment->data[face*alignment->numFeatures*2+feature*2];
        double y=alignment->data[face*alignment->numFeatures*2+feature*2+1];
        // Transform each feature coordinate
        double xx=a*x-b*y+c;
        double yy=b*x+a*y+d;
        // Add into average
        alignment->average[feature*2]+=xx;
        alignment->average[feature*2+1]+=yy;
        samples[feature]++;
      }
    }
  }
  for (i=0; i<alignment->numFeatures; i++) {
    if (samples[i]>0) {
      alignment->average[i*2]/=samples[i];
      alignment->average[i*2+1]/=samples[i];
      alignment->avgValid[i]=1;
    } else 
      alignment->avgValid[i]=0;
  }
  delete[] samples;
}

void AlignmentDebug(Alignment *alignment, int face) 
{
}

// USED
// Get average feature X position
double GetAverageX(Alignment *alignment, int feature)
{
  return alignment->average[feature*2];
}

// USED
// Get average feature Y position
double GetAverageY(Alignment *alignment, int feature)
{
  return alignment->average[feature*2+1];
}

// USED
// Translate, rotate, and scale the average feature positions to set the
// positions of two of them to some desired values.  This allows the faces
// to be placed at particular locations in their windows.
void FixAverage(Alignment *alignment,
                int feature1, double x1, double y1,
                int feature2, double x2, double y2)
{
  double fx1=alignment->average[feature1*2];
  double fy1=alignment->average[feature1*2+1];
  double fx2=alignment->average[feature2*2];
  double fy2=alignment->average[feature2*2+1];
  // Set up linear system to solve for transformation
  Mat mat(4,4);
  mat(0,0)=fx1; mat(0,1)=-fy1; mat(0,2)=1; mat(0,3)=0;
  mat(1,0)=fy1; mat(1,1)=fx1; mat(1,2)=0; mat(1,3)=1;
  mat(2,0)=fx2; mat(2,1)=-fy2; mat(2,2)=1; mat(2,3)=0;
  mat(3,0)=fy2; mat(3,1)=fx2; mat(3,2)=0; mat(3,3)=1;
  Vec vec(4);
  vec(0)=x1;
  vec(1)=y1;
  vec(2)=x2;
  vec(3)=y2;
  Vec param=LUInverse(mat)*vec;
  // Transform the average coordinates
  for (int feature=0; feature<alignment->numFeatures; feature++) {
    double fx=alignment->average[feature*2];
    double fy=alignment->average[feature*2+1];
    alignment->average[feature*2]=fx*param(0)-fy*param(1)+param(2);
    alignment->average[feature*2+1]=fx*param(1)+fy*param(0)+param(3);
  }
}

// USED
// Given the current average position of each feature, compute the best
// (in least squares sense) alignment for each face to those averages.
// Allowed transformations are translation, rotation, and scaling.
void RunAlignmentXform(Alignment *alignment)
{
  for (int face=0; face<alignment->numFaces; face++) {
    int numvalid=0;
    for (int feature=0; feature<alignment->numFeatures; feature++) 
      if (alignment->avgValid[feature] &&
          alignment->valid[face*alignment->numFeatures+feature]) numvalid++;
    assert(numvalid>=2);
    // Set up the over-constrained linear system to solve
    Mat mat=Zero(numvalid*2,4);
    Vec vec=Zero(numvalid*2);
    int ptr=0;
    for (int feature=0; feature<alignment->numFeatures; feature++) {
      if (alignment->avgValid[feature] &&
          alignment->valid[face*alignment->numFeatures+feature]) {
        double x=alignment->data[face*alignment->numFeatures*2+feature*2];
        double y=alignment->data[face*alignment->numFeatures*2+feature*2+1];
        mat(ptr*2,0)=x;
        mat(ptr*2,1)=-y;
        mat(ptr*2,2)=1;
        mat(ptr*2,3)=0;
        mat(ptr*2+1,0)=y;
        mat(ptr*2+1,1)=x;
        mat(ptr*2+1,2)=0;
        mat(ptr*2+1,3)=1;
        vec(ptr*2)=alignment->average[feature*2];
        vec(ptr*2+1)=alignment->average[feature*2+1];
        ptr++;
      }
    }
    // Solve for the transformation using pseudo-inverse
    Vec ans=LUInverse(Transpose(mat)*mat)*(Transpose(mat)*vec);
    alignment->xform[face*4]=ans(0);
    alignment->xform[face*4+1]=ans(1);
    alignment->xform[face*4+2]=ans(2);
    alignment->xform[face*4+3]=ans(3);
  }
}

void RunAlignmentXformNoRotation(Alignment *alignment)
{
  for (int face=0; face<alignment->numFaces; face++) {
    int numvalid=0;
    for (int feature=0; feature<alignment->numFeatures; feature++) 
      if (alignment->valid[face*alignment->numFeatures+feature]) numvalid++;
    // Set up the over-constrained linear system to solve
    Mat mat=Zero(numvalid*2,3);
    Vec vec=Zero(numvalid*2);
    int ptr=0;
    for (int feature=0; feature<alignment->numFeatures; feature++) {
      if (alignment->valid[face*alignment->numFeatures+feature]) {
        double x=alignment->data[face*alignment->numFeatures*2+feature*2];
        double y=alignment->data[face*alignment->numFeatures*2+feature*2+1];
        mat(ptr*2,0)=x;
        mat(ptr*2,1)=1;
        mat(ptr*2,2)=0;
        mat(ptr*2+1,0)=y;
        mat(ptr*2+1,1)=0;
        mat(ptr*2+1,2)=1;
        vec(ptr*2)=alignment->average[feature*2];
        vec(ptr*2+1)=alignment->average[feature*2+1];
        ptr++;
      }
    }
    // Solve for the transformation using pseudo-inverse
    Vec ans=LUInverse(Transpose(mat)*mat)*(Transpose(mat)*vec);
    alignment->xform[face*4]=ans(0);
    alignment->xform[face*4+1]=0;
    alignment->xform[face*4+2]=ans(1);
    alignment->xform[face*4+3]=ans(2);
  }
}

void UnpackAndFFTFast(int width, int height, signed char *bytes, 
                      FastForwardStruct *net)
{
  Complex *data=new Complex[width*height];
  Complex *row=new Complex[width];
  Complex *col=new Complex[height];
  for (int j=0; j<height; j++) {
    for (int i=0; i<width; i++) row[i]=Complex((*(bytes++))/127.0,0.0);
    ComputeFFT(row,width,1);
    for (int i=0; i<width; i++) data[i+j*width]=row[i];
  }
  for (int i=0; i<width; i++) {
    for (int j=0; j<height; j++) col[j]=data[i+j*width];
    ComputeFFT(col,height,1);
    for (int j=0; j<height; j++) net->unitList[1+i+j*width].activation=Abs(col[j]);
  }
  delete[] row;
  delete[] col;
  delete[] data;
}

void ImageToFFTFast(int width, int height, int *img, int *map, double scale,
                    FastForwardStruct *net)
{
  Complex *data=new Complex[width*height];
  Complex *row=new Complex[width];
  Complex *col=new Complex[height];
  for (int j=0; j<height; j++) {
    for (int i=0; i<width; i++) row[i]=Complex(map[*(img++)]*scale-1.0,0.0);
    ComputeFFT(row,width,1);
    for (int i=0; i<width; i++) data[i+j*width]=row[i];
  }
  for (int i=0; i<width; i++) {
    for (int j=0; j<height; j++) col[j]=data[i+j*width];
    ComputeFFT(col,height,1);
    for (int j=0; j<height; j++) net->unitList[1+i+j*width].activation=Abs(col[j]);
  }
  delete[] row;
  delete[] col;
  delete[] data;
}

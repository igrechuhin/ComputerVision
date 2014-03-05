#ifndef SearchIncluded
#define SearchIncluded

#include "img.hpp"
#include "list.cc"

typedef void *ClientData;

struct CheckResultsStruct {
  int falsePos, falseNeg, numFaces, examples;
  int falsePosByType[6];
  int falseNegByType[6];
  int numFacesByType[6];
  CheckResultsStruct() {
    for (int i=0; i<6; i++) {
      falsePosByType[i]=0;
      falseNegByType[i]=0;
      numFacesByType[i]=0;
    }
  }
};

// USED
// Definition of search callback function, used to save or otherwise
// process detection information
typedef void (*SearchCallback)(ClientData data, ByteImage *image,
                               int x, int y, int width, int height,
                               int level, double scale, double output,
                               int orientation);

// USED
// Class used to store detections
class Detection : public ListNode<Detection>
{
  public:
  int x, y, s, orient, profile;
  double output;
  Detection(int xx, int yy, int ss, double o, int dir, int pr=0) {
    x=xx; y=yy; s=ss; output=o; orient=dir; profile=pr;
  }
};

void SearchMulti(ByteImage *image, int numNetworks,
                 SearchCallback callback, ClientData data[]);

void SearchMultiMerge(ByteImage *image, int numNetworks,
                      SearchCallback callback, ClientData data[]);

void NetArbitrateDirect(int width, int height, int numLocFiles,
                        List<Detection> *detections, 
                        List<Detection> *outputDetections,
                        int arbnet);

void FuzzyVote2Direct(int width, int height, int numLocFiles,
                      List<Detection> *detections,
                      List<Detection> *outputDetections, 
                      int spread, int search, int collapse, int overlap,
                      int filterodd, ByteImage *mask);

void SearchRouter(ByteImage *image, ByteImage *mask,
                  SearchCallback callback, ClientData data[]);

void SearchAstro(ByteImage *image, SearchCallback callback, ClientData data);

void SearchUmeEvenFaster(ByteImage *image, ByteImage *levelmask, int level,
                         SearchCallback callback, ClientData data,
                         double threshold=0.0);

#ifdef CompiledNets
void SearchUmeEvenFasterCompiled(ByteImage *image, ByteImage *levelmask,
                                 int level,
                                 SearchCallback callback, ClientData data);
#endif

void SearchUmeEvenFasterRegion(ByteImage *image, ByteImage *levelmask,
                               int minX, int maxX, int minY, int maxY,
                               int level,
                               SearchCallback callback, ClientData data);

void SearchUmeEvenFasterRegionPrecise(ByteImage *image, ByteImage *levelmask,
                                      int minX, int maxX, int minY, int maxY,
                                      int level, int preciseNet,
                                      SearchCallback callback,
                                      ClientData data);

void SearchUmeEvenFasterAll(ByteImage *image,int level,
                            SearchCallback callback, ClientData data);

void FuzzyVote2(int width, int height, int numLocFiles,
                List<Detection> detections[],
                SearchCallback callback, ClientData data,
                int spread, int search, int collapse, int overlap,
                int filterodd, ByteImage *mask);

int SearchFalsePositives(ByteImage *image, 
                         char *clusterFile, int numClusters,
                         char *exampleFile, int maxExamples,
                         ByteImage *mask, int correctLight);

void SearchFalsePositivesDist(ByteImage *image, 
                              char *clusterFile, int numClusters,
                              char *exampleFile, int maxExamples);

extern char *NNDirectory;

void SearchMultiCallbackSave(ClientData data, ByteImage *image,
                             int x, int y, int width, int height, int level,
                             double scale, double output, int orient);
void LimitScale(int min, int max, int *s, int *x, int *y);

int CompareDetections(Detection *d1, Detection *d2);

#endif

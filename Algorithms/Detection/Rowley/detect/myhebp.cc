#ifdef __GNUC__
#include <string.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#ifndef __GNUC__
#include <string.h>
#endif
#ifndef hpux
#include <math.h>
#endif

#include <direct.h>

#ifdef hpux
#include <math.h>
#endif

#include "system.hpp"
#include "myhebp.hpp"

FastForwardStruct *real_fast=NULL;
FastForwardStruct **real_fast_list=NULL;
float real_inputs[30*30];
float real_outputs[30*30*2];
float real_targets[30*30*2];
int real_numNetworks;

// USED
// Allocate an array of pointers to neural networks.  This array is global
// (yuck!).  If an array already exists, it and the networks it points to
// are deleted.
void FastAllocateNetworks(int num)
{
  if (real_fast_list!=NULL) {
    for (int i=0; i<real_numNetworks; i++) delete real_fast_list[i];
    delete[] real_fast_list;
  }
  real_fast_list=new FastForwardStruct*[num];
  for (int i=0; i<num; i++) real_fast_list[i]=NULL;
  real_numNetworks=num;
}

// USED
// Load a network, and place it in the array created by FastAllocateNetworks
void FastInitNetwork(int num, int numNetworks, char *networkList[])
{
  if (real_fast_list[num]!=NULL) delete real_fast_list[num];
  real_fast_list[num]=FastLoadMerge(numNetworks,networkList);
  FastLoadMergeWeights(real_fast_list[num],numNetworks,networkList);
}

void FastInit(char *directory, int numNetworks, char *networkList[])
{
  char *olddir=getcwd(NULL,1024);
  chdir(directory);
  real_fast_list=new FastForwardStruct*[numNetworks];
  for (int i=0; i<numNetworks; i++)
  {
    real_fast_list[i]=FastLoadMerge(1,networkList+i);
    FastLoadMergeWeights(real_fast_list[i],1,networkList+i);
    if (i==0)
    {
      real_fast=FastLoadMerge(1,networkList+i);
      FastLoadMergeWeights(real_fast,1,networkList+i);
    }
  }
  chdir(olddir);
  free(olddir);
}

void MyHebp_InitNoTcl()
{
}

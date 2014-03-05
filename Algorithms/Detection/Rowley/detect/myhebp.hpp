#ifndef MyHebpIncluded
#define MyHebpIncluded

#include "fast2.hpp"

extern FastForwardStruct *real_fast;
extern float real_inputs[30*30];
extern float real_outputs[30*30*2];
extern float real_targets[30*30*2];
extern int real_numNetworks;
extern FastForwardStruct **real_fast_list;

void FastInit(char *directory, int numNetworks, char *networkList[]);
void FastAllocateNetworks(int num);
void FastInitNetwork(int num, int numNetworks, char *networkList[]);

void MyHebp_InitNoTcl();

#endif


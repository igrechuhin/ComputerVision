#ifndef KDoiIncluded
#define KDoiIncluded

void KDoiInit(char *path);
void KDoiColorMask(unsigned char *input, int gXsize, int gYsize,
                   ByteImage *image, int maskValue);

#endif

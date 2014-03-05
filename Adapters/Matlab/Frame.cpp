#include "Frame.h"

#include "../../Common/Frame/Frame.h"

#include <mclcppclass.h>

using namespace common;

void ConvertRGB32ToGray( mwArray& Output, const Frame& Input )
{
  const int imageHeight(Input.height());
  const int imageWidth(Input.width());
  const int imageSize(imageHeight * imageWidth);
  QByteArray grayImageArray(imageSize, 0);
  char* grayImageArrayPtr0(grayImageArray.data());
  for (int y(0); y < imageHeight; y++, grayImageArrayPtr0++)
  {
    char* grayImageArrayPtr(grayImageArrayPtr0);
    const QRgb* imagePtr(reinterpret_cast<const QRgb*>(Input.constScanLine(y)));
    for (int x(0); x < imageWidth; x++, grayImageArrayPtr+=imageHeight)  
    {
      *grayImageArrayPtr = qGray(*imagePtr++);
    }
  }
  mwArray tmp(imageHeight, imageWidth, mxUINT8_CLASS);
  tmp.SetData(reinterpret_cast<uchar*>(grayImageArray.data()), imageSize);
  Output.Set(tmp);
}

void ConvertRGB888ToGray( mwArray& Output, const Frame& Input )
{
  const int imageHeight(Input.height());
  const int imageWidth(Input.width());
  const int imageSize(imageHeight * imageWidth);
  QByteArray grayImageArray(imageSize, 0);
  char* grayImageArrayPtr0(grayImageArray.data());
  for (int y(0); y < imageHeight; y++, grayImageArrayPtr0++)
  {
    char* grayImageArrayPtr(grayImageArrayPtr0);
    const uchar* imagePtr(Input.constScanLine(y));
    for (int x(0); x < imageWidth; x++, grayImageArrayPtr+=imageHeight)  
    {
      uchar red(*imagePtr++);
      uchar green(*imagePtr++);
      uchar blue(*imagePtr++);
      *grayImageArrayPtr = qGray(red, green, blue);
    }
  }
  mwArray tmp(imageHeight, imageWidth, mxUINT8_CLASS);
  tmp.SetData(reinterpret_cast<uchar*>(grayImageArray.data()), imageSize);
  Output.Set(tmp);
}

namespace adapters
{
  void Convert( mwArray& Output, const Frame& Input, bool ToGray/* = true*/ )
  {
    switch (Input.format())
    {
    case QImage::Format_RGB32:
      if (ToGray)
      {
        ConvertRGB32ToGray(Output, Input);
        break;
      }
    case QImage::Format_RGB888:
      if (ToGray)
      {
        ConvertRGB888ToGray(Output, Input);
        break;
      }
    default: Q_ASSERT(!"TODO");
    }
  }
}
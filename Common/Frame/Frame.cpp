#include "Frame.h"

#include "../CRC/CRC64.h"

#include <QBuffer>

#include <highgui_c.h>
#include <imgproc.hpp>

namespace common
{
  void convertColor( Frame& Dst, const Frame& Src, int ConversionType )
  {
    cvtColor(Src, Dst, ConversionType);
    switch (ConversionType)
    {
    case CV_BGR2RGB: Dst.Format = QImage::Format_RGB888; break;
    default: Dst.Format = QImage::Format_Invalid;
    }
  }

  Frame::Frame()
    : cv::Mat(),
      Format(QImage::Format_Invalid)
  {
  }

  Frame::Frame( const QString& FileName )
    : cv::Mat(),
      Format(QImage::Format_Invalid)
  {
    IplImage* openedImage(cvLoadImage(FileName.toAscii().constData(), CV_LOAD_IMAGE_COLOR));
    Q_ASSERT(openedImage);
    *this = openedImage;
  }

  Frame::Frame( const Frame& Other )
    : cv::Mat(Other),
      Format(Other.Format)
  {
  }

  Frame::Frame( const cv::Mat& Other, const QImage::Format& OtherFormat )
    : cv::Mat(Other),
      Format(OtherFormat)
  {
  }

  Frame::Frame( const Frame& Other, const QRect& ROI )
    : cv::Mat(Other, cv::Rect(qMax(ROI.x(), 0), qMax(ROI.y(), 0),
              qMin(ROI.width(), Other.width() - qMax(ROI.x(), 0)),
              qMin(ROI.height(), Other.height() - qMax(ROI.y(), 0)))),
      Format(Other.Format)
  {
  }

  Frame::Frame( const IplImage* Image, bool CopyData/*=false*/ )
    : cv::Mat(Image, CopyData),
      Format(QImage::Format_RGB888)
  {
    if (Image->channelSeq[0] == 'B')
    {
      Frame dst;
      convertColor(dst, *this, CV_BGR2RGB);
      *this = dst;
    }
  }

  Frame::Frame( const QImage& Other )
    : cv::Mat(),
      Format(QImage::Format_Invalid)
  {
    operator=(Other);
  }

  Frame::~Frame()
  {
  }

  Frame& Frame::operator=( const Frame& Other )
  {
    cv::Mat::operator=(Other);
    Format = Other.Format;
    return *this;
  }

  Frame& Frame::operator=( const IplImage* Other )
  {
    *this = Frame(Other);
    return *this;
  }

  Frame& Frame::operator=( const QImage& Other )
  {
    Format = Other.format();
    create(Other.height(), Other.width(), getCVType());
    Q_ASSERT(Other.depth() >= 8);
    const uchar* srcBegin(Other.constBits());
    const uchar* srcEnd(srcBegin + width() * elemSize());
    const int srcStride(Other.bytesPerLine());
    uchar* dstBegin(data);
    const int dstStride(bytesPerLine());
    for (int lineIndex(0); lineIndex < height(); lineIndex++, srcBegin+=srcStride, srcEnd+=srcStride, dstBegin+=dstStride)
    {
      qCopy(srcBegin, srcEnd, dstBegin);
    }
    return *this;
  }

  Frame Frame::operator()( const QRect& ROI ) const
  {
    return Frame(*this, ROI);
  }

  Frame::operator QPixmap() const
  {
    Q_ASSERT(Format != QImage::Format_Invalid);
    Q_CHECK_PTR(data);
    return QPixmap::fromImage(operator QImage());
  }

  Frame::operator QImage() const
  {
    return QImage(data, width(), height(), bytesPerLine(), Format);
  }

  Frame::operator QByteArray() const
  {
    QByteArray byteArray;
    QBuffer buffer(&byteArray);
    buffer.open(QIODevice::WriteOnly);
    operator QImage().save(&buffer, "PNG", 100);
    return byteArray;
  }

  int Frame::width() const
  {
    Q_ASSERT(cols >= 0);
    return cols;
  }

  int Frame::height() const
  {
    Q_ASSERT(rows >= 0);
    return rows;
  }

  int Frame::bytesPerLine() const
  {
    return step.p[0];
  }

  int Frame::byteCount() const
  {
    return total() * elemSize();
  }

  bool Frame::isNull() const
  {
    return empty();
  }

  qint64 Frame::crc() const
  {
    QImage tmpImage(operator QImage().convertToFormat(QImage::Format_RGB32));
    return CRC64(tmpImage.bits(), tmpImage.byteCount());
  }

  void Frame::flipLR()
  {
    this->operator =(mirrored());
  }

  bool Frame::loadFromData( const QByteArray& Data )
  {
    QImage Image;
    bool loadOK(Image.loadFromData(Data));
    Q_ASSERT(loadOK);
    operator =(Image);
    return loadOK;
  }

  quint8 Frame::getColorDepth() const
  {
    return operator QImage().depth();
  }

  quint8 Frame::getMiddleBrightness() const
  {
    quint64 brightness(0);
    for (int heightIndex(0); heightIndex < height(); heightIndex++)
    {
      for (int widthIndex(0); widthIndex < width(); widthIndex++)
      {
        brightness += qGray(pixel(widthIndex, heightIndex));
      }
    }
    return static_cast<quint8>((brightness / height()) / width());
  }

  bool Frame::valid( const QPoint& Position ) const
  {
    return valid(Position.x(), Position.y());
  }

  bool Frame::valid( int X, int Y ) const
  {
    return 0 <= X && X < width() && 0 <= Y && Y < height();
  }

  QRgb Frame::pixel( const QPoint& Position ) const
  {
    return pixel(Position.x(), Position.y());
  }

  QRgb Frame::pixel( int X, int Y ) const
  {
    Q_ASSERT(valid(X, Y));
    return operator QImage().pixel(X, Y);
  }

  Frame Frame::scaled( const qreal& ScaleFactor ) const
  {
    QImage image(operator QImage());
    return image.scaled(image.size() * ScaleFactor, Qt::KeepAspectRatio, Qt::SmoothTransformation);
  }

  Frame Frame::mirrored() const
  {
    Frame mirrImage(clone(), Format);
    const int stride(mirrImage.step[0]);
    const int charsPerPixel(mirrImage.step[1]);
    const int v2PtrShift(2 * charsPerPixel);
    const int charsPerLine((mirrImage.width() - 1) * charsPerPixel);
    quint8* ptr0(mirrImage.ptr(0));
    for ( int yIndex(0); yIndex < mirrImage.height(); yIndex++, ptr0 += stride )
    {
      quint8* v1Ptr(ptr0);
      quint8* v2Ptr(ptr0 + charsPerLine);
      for (; v1Ptr < v2Ptr; v2Ptr -= v2PtrShift)
      {
        for (int charIndex(0); charIndex < charsPerPixel; charIndex++, v1Ptr++, v2Ptr++)
        {
          qSwap(*v1Ptr, *v2Ptr);
        }
      }
    }
    return mirrImage;
  }
  QImage::Format Frame::format() const
  {
    return Format;
  }

  uchar* Frame::scanLine( const int Line )
  {
    return cv::Mat::data + Line*bytesPerLine();
  }

  const uchar* Frame::constScanLine( const int Line ) const
  {
    return cv::Mat::data + Line*bytesPerLine();
  }

  int Frame::getCVType() const
  {
    switch (Format)
    {
    case QImage::Format_Invalid:              Q_ASSERT(false);
    case QImage::Format_Indexed8:             return CV_8UC1;
    case QImage::Format_RGB32:
    case QImage::Format_ARGB32:
    case QImage::Format_ARGB32_Premultiplied: return CV_8UC4;
    case QImage::Format_RGB888:               return CV_8UC3;
    default: Q_ASSERT(!"Not implemented");
    }
    return 0;
  }

}

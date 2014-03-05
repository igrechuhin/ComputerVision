#ifndef COMMON_MODELS_SHAPE_H
#define COMMON_MODELS_SHAPE_H

#include <QPointF>
#include <QVector>
#include <QDataStream>

namespace common
{
  namespace models
  {
    const qint16 SYMMETRIC_INDEX[] =
      // 1   2   3   4   5   6   7   8   9  10  11 12 13 14 15
    { 14, 13, 12, 11, 10,  9,  8,  7,  6,  5,  4, 3, 2, 1, 0, // Jaw -> Jaw
    //16  17  18  19  20  21  22  23  24  25  26
    30, 29, 28, 27, 26, 33, 32, 31, 35, 34, 36, // Left eye -> Right eye
    //27  28  29  30  31  32  33  34  35  36  37
    19, 18, 17, 16, 15, 22, 21, 20, 24, 23, 25, // Right eye -> Left eye
    //38  39  40  41  42  43  44  45  46  47  48  49  50  51  52  53  54  55
    43, 42, 41, 40, 39, 38, 37, 48, 47, 46, 45, 44, 51, 50, 49, 54, 53, 52, // Mouth -> Mouth
    //56  57  58  59  60  61  62
    66, 65, 64, 63, 62, 68, 67, // Right brow -> Left brow
    //63  64  65  66  67  68  69
    59, 58, 57, 56, 55, 61, 60, // Left brow -> Right brow
    //70  71  72  73  74  75  76  77  78  79  80
    79, 78, 77, 76, 75, 74, 73, 72, 71, 70, 69, // Nose contour -> Nose contour
    //81  82  83
    80, 81, 82, // Nose center -> Nose center
    //84  85
    84, 83, // Left nostril <-> Right nostril
    //86
    85}; // Under nose

    struct LandmarkTriangle
    {
      qint16 iPrev;
      qint16 iNext;
    };

    Q_DECLARE_TYPEINFO(LandmarkTriangle, Q_PRIMITIVE_TYPE);

    const LandmarkTriangle TRIANGLE_INDEX[] =
    // 1         2        3        4        5       6       7       8       9       10       11        12        13        14        15
    {{55, 1}, {28, 2}, {28, 3}, {28, 4}, {28, 5}, {0, 6}, {0, 7}, {6, 8}, {7, 14}, {8, 14}, {9, 17}, {10, 17}, {11, 17}, {12, 17}, {13, 66},
    //  16        17        18        19        20        21        22        23        24        25        26
    {17, 21}, {17, 21}, {20, 22}, {17, 20}, {17, 21}, {18, 21}, {15, 19}, {16, 21}, {18, 20}, {16, 22}, {18, 20},
    //  27        28        29        30        31        32        33        34        35        36        37
    {28, 32}, {33, 28}, {31, 33}, {28, 32}, {28, 32}, {29, 32}, {26, 30}, {27, 32}, {29, 31}, {27, 33}, {27, 33},
    //  38        39        40        41        42        43        44        45        46        47        48        49        50        51        52        53        54        55
    {40, 46}, {37, 46}, {38, 44}, {45, 47}, {48, 42}, {46, 43}, {40, 46}, {42, 45}, {40, 42}, {39, 41}, {38, 40}, {38, 47}, {46, 48}, {45, 47}, {44, 46}, {40, 42}, {39, 41}, {38, 40},
    //  56        57        58        59        60        61        62
    {56, 61}, {61, 57}, {55, 60}, {57, 60}, {58, 60}, {56, 58}, {56, 57},
    //  63        64        65        66        67        68        69
    {63, 68}, {68, 64}, {68, 66}, {64, 67}, {65, 67}, {64, 65}, {63, 65},
    //  70        71        72        73        74        75        76        77        78        79        80
    {17, 70}, {17, 71}, {72, 74}, {71, 74}, {71, 74}, {71, 77}, {74, 78}, {74, 77}, {24, 76}, {28, 77}, {28, 78},
    //  81        82        83
    {72, 76}, {17, 28}, {17, 28},
    //  84        85
    {28, 73}, {75, 17},
    //  86
    {44, 48}};

    QPointF getShapeCenter( const QVector<QPoint>& Shape );
    QVector<QPointF> getCenteredShape( const QVector<QPoint>& Shape );
    QVector<QPointF> getScaledShape( const QVector<QPoint>& Shape, const qreal& ScaleFactor );
    QVector<QPoint> getMirroredShape( const QVector<QPoint>& Shape, const int& ImageWidth );
    qint32 getShapeWidth( const QVector<QPoint>& Shape );
    qint32 getBetweenEyesDistance( const QVector<QPoint>& Shape );

    void alignShape( QVector<QPointF>& Shape, const QVector<QPointF>& AnchorShape, const QVector<qreal>& Weights );
  }
}

QDataStream& operator << (QDataStream& Stream, const common::models::LandmarkTriangle & Value);
QDataStream& operator >> (QDataStream& Stream, common::models::LandmarkTriangle & Value);

#endif // COMMON_MODELS_SHAPE_H
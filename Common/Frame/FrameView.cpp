#include "FrameView.h"

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>


namespace
{
  const int SPACING(2);
  const int POINT_SIZE(2);
  const QFont POINT_TEXT_FONT("Times", 5);

  Qt::GlobalColor getPointColorByIndex( qint16 Index ) 
  {
    if (Index <= 15) // Jaw
      return Qt::white;

    if (Index <= 23) // Left eye
      return Qt::green;

    if (Index <= 25) // Left eye iris
      return Qt::yellow;

    if (Index == 26) // Left eye pupil
      return Qt::red;

    if (Index <= 34) // Right eye
      return Qt::green;

    if (Index <= 36) // Right eye iris
      return Qt::yellow;

    if (Index == 37) // Right eye pupil
      return Qt::red;

    if (Index <= 55) // Mouth
      return Qt::red;

    if (Index <= 62) // Right brow
      return Qt::yellow;

    if (Index <= 69) // Left brow
      return Qt::yellow;

    if (Index <= 80) // Nose
      return Qt::blue;

    if (Index <= 83) // Nose center
      return Qt::red;

    if (Index == 84) // Right nostril
      return Qt::red;

    if (Index == 85) // Left nostril
      return Qt::red;

    if (Index == 86) // Under nose
      return Qt::white;

    return Qt::black;
  }
}

FrameView::FrameView(QWidget *parent)
  : QGraphicsView(parent),
    Scene(new QGraphicsScene(parent)),
    MaxFrameWidth(0),
    RectColor(Qt::red),
    Scale(1.0f)
{
  Scene->setSceneRect(0, 0, width(), height());
  setScene(Scene.data());
}

FrameView::~FrameView()
{
}

void FrameView::setFrame( const Frame& FrameRef )
{
  clearFrame();
  Images.append(FrameRef);
  if (FrameRef.isNull())
    return;
  QGraphicsPixmapItem* pixMapPtr(Scene->addPixmap(FrameRef));
  if ((width() < Images.first().width()) || (height() < FrameRef.height()))
  {
    qreal widthScale(static_cast<qreal>(width()) / static_cast<qreal>(FrameRef.width()));
    qreal heightScale(static_cast<qreal>(height()) / static_cast<qreal>(FrameRef.height()));
    Scale = qMin(widthScale, heightScale) * 0.98;
    pixMapPtr->setScale(Scale);
  }
}

void FrameView::addRect( const QRect& Rect, const QString& Description )
{
  QRect scaledRect(Rect.x() * Scale, Rect.y() * Scale, Rect.width() * Scale, Rect.height() * Scale);
  Scene->addRect(scaledRect, QPen(RectColor));

  QGraphicsTextItem* label(Scene->addText(Description));
  label->setPos(scaledRect.bottomLeft());
  label->setDefaultTextColor(RectColor);
  
  qint32 color(RectColor);
  ++color > Qt::yellow ? RectColor = Qt::red : RectColor = static_cast<Qt::GlobalColor>(color);
}

void FrameView::addShape( const QVector<QPoint>& Shape )
{
  for(qint16 pointIndex(0); pointIndex < Shape.size(); pointIndex++)
  {
    Qt::GlobalColor color(getPointColorByIndex(pointIndex+1));
    QPen Pen(color);
    QList<QGraphicsItem*> pointGroupList;
    QGraphicsLineItem* line1(new QGraphicsLineItem(-POINT_SIZE, 0, POINT_SIZE, 0));
    line1->setPen(Pen);
    pointGroupList.push_back(line1);
    QGraphicsLineItem* line2(new QGraphicsLineItem(0, -POINT_SIZE, 0, POINT_SIZE));
    line2->setPen(Pen);
    pointGroupList.push_back(line2);
    QGraphicsTextItem* label(new QGraphicsTextItem(QString::number(pointIndex)));
    label->setDefaultTextColor(color);
    label->setFont(POINT_TEXT_FONT);
    label->setPos(-2*POINT_SIZE, -2.5f*POINT_SIZE);
    pointGroupList.push_back(label);

    QGraphicsItemGroup* pointGroup = Scene->createItemGroup(pointGroupList);
    pointGroup->setPos(QPointF(Shape[pointIndex]) * Scale);
  }
}

void FrameView::clearFrame()
{
  Scene->clear();
  Images.clear();
  LastOffset = QPointF();
  LastSize = QSize();
  MaxFrameWidth = 0;
  RectColor = Qt::red;
}

void FrameView::addFrame( const Frame& FrameRef, const QString& Description )
{
  Images.append(FrameRef);
  QPointF offset(LastOffset);
  if (LastSize.isValid())
  {
    const qreal xShift(LastOffset.x() + LastSize.width());
    if (xShift + FrameRef.width() < Scene->width())
    {
      offset.setX(xShift + SPACING);
    }
    else
    {
      offset.setX(0);
      offset.setY(LastOffset.y() + LastSize.height() + SPACING);
    }
  }
  insertFrame(FrameRef, Description, offset);
}

void FrameView::insertFrame( const Frame& FrameRef, const QString& Description, const QPointF& Offset )
{
  if (FrameRef.empty())
    return;
  QGraphicsPixmapItem* pixMapPtr(Scene->addPixmap(FrameRef));
  pixMapPtr->setOffset(Offset);
  QRectF textRect;
  if (!Description.isEmpty())
  {
    QGraphicsSimpleTextItem* textPtr(Scene->addSimpleText(Description));
    textRect = textPtr->boundingRect();
    textPtr->setPos(Offset + QPointF((FrameRef.width() - textRect.width())/2, FrameRef.height()));
  }
  LastOffset = Offset;
  LastSize.setWidth(FrameRef.width());
  LastSize.setHeight(FrameRef.height() + textRect.height());
  MaxFrameWidth = qMax(MaxFrameWidth, static_cast<int>(LastOffset.x() + LastSize.width()));
}

void FrameView::resizeEvent( QResizeEvent* Event )
{
  if (!LastSize.isValid())
  {
    Scene->setSceneRect(0, 0, Event->size().width(), Event->size().height());
  }
  else
  {
    int newHeight(LastOffset.y() + LastSize.height());
    Scene->setSceneRect(0, 0, qMax(Event->size().width(), MaxFrameWidth), qMax(Event->size().height(), newHeight));
  }
}

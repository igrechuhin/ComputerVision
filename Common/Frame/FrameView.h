#ifndef COMMON_FRAMEVIEW_H
#define COMMON_FRAMEVIEW_H

#include "Frame.h"

#include <QGraphicsView>
#include <QGraphicsItemGroup>
#include <QResizeEvent>
#include <QVector>

using namespace common;

class FrameView : public QGraphicsView
{
  Q_OBJECT

public:
  FrameView(QWidget *parent);
  ~FrameView();

  void setFrame( const Frame& FrameRef );
  void addRect( const QRect& Rect, const QString& Description );
  void addShape( const QVector<QPoint>& Shape );

  void clearFrame();
  void addFrame( const Frame& FrameRef, const QString& Description );

protected:
  virtual void resizeEvent( QResizeEvent* Event );

private:
  void insertFrame( const Frame& FrameRef, const QString& Description, const QPointF& Offset );

private:
  QList<Frame> Images;
  QScopedPointer<QGraphicsScene> Scene;
  QPointF LastOffset;
  QSize LastSize;
  int MaxFrameWidth;
  Qt::GlobalColor RectColor;
  qreal Scale;
};

#endif // COMMON_FRAMEVIEW_H

#include <QtMath>
#include <QResizeEvent>
#include <QGraphicsScene>

#include "graphicsview.h"
#include "graphicsarrowitem.h"

using namespace MQGAPI;
GraphicsView::GraphicsView(QWidget *parent)
  : QGraphicsView(parent)
  , origin(0, 0)
  , x_axis(Q_NULLPTR)
  , y_axis(Q_NULLPTR)
{
  initialize();
}

GraphicsView::~GraphicsView()
{
}

QPointF GraphicsView::pixelToReal(const QPointF& pixel)
{
  return QPointF(pixel.x() - origin.x(), origin.y() - pixel.y());
}

QPointF GraphicsView::realToPixel(const QPointF& real)
{
  return QPointF(real.x() + origin.x(), origin.y() - real.y());
}

void GraphicsView::resizeEvent(QResizeEvent* event)
{
  QSize s = event->size();
  fitInView(0, 0, s.width(), s.height());//, Qt::KeepAspectRatio);
  resetAxis();
  QGraphicsView::resizeEvent(event);
}

void GraphicsView::setOrigin(qreal x, qreal y)
{
  origin.setX(x);
  origin.setY(y);
  resetAxis();

  QGraphicsView::update();
}

void GraphicsView::setOrigin(const QPointF& center)
{
  setOrigin(center.x(), center.y());
}

const QPointF& GraphicsView::getOrigin() const
{
  return origin;
}

void GraphicsView::initialize()
{
  this->setScene(new QGraphicsScene(this));
  resetAxis();
}

void GraphicsView::resetAxis()
{
  QRectF rect = this->rect();
  qreal W = rect.width();
  qreal H = rect.height();

  if (!x_axis) {
    x_axis = new GraphicsArrowItem(0, origin.y(), W, origin.y(), false);
    scene()->addItem(x_axis);
  }
  else {
      x_axis->setLine(0, origin.y(), W, origin.y());
  }

  if (!y_axis) {
    y_axis = new GraphicsArrowItem(origin.x(), H, origin.x(), 0, false);
    scene()->addItem(y_axis);
  }
  else {
      y_axis->setLine(origin.x(), H, origin.x(), 0);
  }
}

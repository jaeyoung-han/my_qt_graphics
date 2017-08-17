#include <QtMath>
#include <QResizeEvent>
#include <QGraphicsScene>

#include "graphicsview.h"
#include "graphicsarrowitem.h"

using namespace MQGAPI;

GraphicsView::GraphicsView(QWidget *parent)
  : QGraphicsView(parent)
  , origin(0, 0)
  , scale_factor(10)
  , x_axis(Q_NULLPTR)
  , y_axis(Q_NULLPTR)
{
  initialize();
  setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
}

GraphicsView::~GraphicsView()
{
}

QPointF GraphicsView::pixelToReal(const QPointF& pixel)
{
  return pixelToReal(pixel.x(), pixel.y());
}

QPointF GraphicsView::pixelToReal(qreal x, qreal y)
{
  return QPointF(x - origin.x(), origin.y() - y) / scale_factor;
}

QPointF GraphicsView::realToPixel(const QPointF& real)
{
  return realToPixel(real.x(), real.y());
}

QPointF GraphicsView::realToPixel(qreal x, qreal y)
{
  return QPointF(x * scale_factor + origin.x(), origin.y() - y * scale_factor);
}

void GraphicsView::resizeEvent(QResizeEvent* event)
{
  QSize s = event->size();
  fitInView(0, 0, s.width(), s.height());//, Qt::KeepAspectRatio);
  resetAxis();
  QGraphicsView::resizeEvent(event);
}

void GraphicsView::setAxisVisible(bool on)
{
	x_axis->setVisible(on);
	y_axis->setVisible(on);
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

void GraphicsView::setScale(qreal new_scale)
{
  Q_ASSERT(new_scale > 0);
  scale_factor = new_scale;
}

const QPointF& GraphicsView::getOrigin() const
{
  return origin;
}

void GraphicsView::setBackgroundColor(const QColor& color)
{
	QBrush brush(color, Qt::SolidPattern);
	scene()->setBackgroundBrush(brush);
}

void GraphicsView::initialize()
{
  this->setScene(new QGraphicsScene(this));
  resetAxis();
}

void GraphicsView::resetAxis()
{
  QRectF rect = this->rect();
  qreal W = qAbs(origin.x()) * 2;//rect.width();
  qreal H = qAbs(origin.y()) * 2;//rect.height();

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

void GraphicsView::save(const QString& filename)
{
	QPixmap pixmap(this->grab());
	pixmap.save(filename);
}

void GraphicsView::mouseMoveEvent(QMouseEvent* move)
{
    QPointF mov;
    mov = mapToScene(move->pos());
    emit sendMousePoint(mov);
}

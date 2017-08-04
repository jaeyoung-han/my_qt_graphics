#include <QtMath>
#include "graphicsarrowitem.h"

using namespace MQGAPI;

GraphicsArrowItem::GraphicsArrowItem(QGraphicsItem *parent)
  : QGraphicsLineItem(parent)
  , m_head(true)
  , m_tail(false)
{

}

GraphicsArrowItem::GraphicsArrowItem(const QLineF &line, bool tail_arrow, QGraphicsItem *parent)
  : QGraphicsLineItem(line, parent)
  , m_head(true)
  , m_tail(tail_arrow)
{

}

GraphicsArrowItem::GraphicsArrowItem(qreal x1, qreal y1, qreal x2, qreal y2, bool tail_arrow, QGraphicsItem *parent)
  : QGraphicsLineItem(x1, y1, x2, y2, parent)
  , m_head(true)
  , m_tail(tail_arrow)
{

}

GraphicsArrowItem::~GraphicsArrowItem()
{

}

void GraphicsArrowItem::flip()
{
  bool t = m_head;
  m_head = m_tail;
  m_tail = t;
}

double GraphicsArrowItem::GetAngle(const double dx, const double dy)
{
  return M_PI - (qAtan(dx/dy));
}

QPainterPath GraphicsArrowItem::shape() const
{
  QPainterPath path;
  QPainterPathStroker stroker;
  path.moveTo(line().p1());
  path.lineTo(line().p2());
  stroker.setWidth(10);
  return stroker.createStroke(path);
}

QRectF GraphicsArrowItem::boundingRect() const
{
  return shape().boundingRect();
}

void GraphicsArrowItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
  painter->setRenderHint(QPainter::Antialiasing);
  if (this->isSelected())
  {
    const QColor color(255,0,0);
    QPen pen;
    pen.setColor(color);
    pen.setWidth(3);
    painter->setPen(pen);
    QBrush brush;
    brush.setColor(color);
    brush.setStyle(Qt::SolidPattern);
    painter->setBrush(brush);
  }
  else
  {
    const QColor color(0,0,0);
    QPen pen;
    pen.setColor(color);
    pen.setWidth(1);
    painter->setPen(pen);
    QBrush brush;
    brush.setColor(color);
    brush.setStyle(Qt::SolidPattern);
    painter->setBrush(brush);
  }
  painter->drawLine(this->line());

  //The angle from tail to head
  double angle = GetAngle(line().dx(),line().dy());
  if (line().dy() >= 0.0) angle = (1.0 * M_PI) + angle;
  const double sz = 10.0; //pixels

  if (m_tail) {
    const QPointF p0 = this->line().p1();
    const QPointF p1
      = p0 + QPointF(
         std::sin(angle + M_PI + (M_PI * 0.1)) * sz,
        -std::cos(angle + M_PI + (M_PI * 0.1)) * sz);
    const QPointF p2
      = p0 + QPointF(
         std::sin(angle + M_PI - (M_PI * 0.1)) * sz,
        -std::cos(angle + M_PI - (M_PI * 0.1)) * sz);
    painter->drawPolygon(QPolygonF() << p0 << p1 << p2);
  }

  if (m_head) {
    const QPointF p0 = this->line().p2();

    const QPointF p1
      = p0 + QPointF(
         std::sin(angle +  0.0 + (M_PI * 0.1)) * sz,
        -std::cos(angle +  0.0 + (M_PI * 0.1)) * sz);
    const QPointF p2
      = p0 + QPointF(
         std::sin(angle +  0.0 - (M_PI * 0.1)) * sz,
        -std::cos(angle +  0.0 - (M_PI * 0.1)) * sz);

    painter->drawPolygon(QPolygonF() << p0 << p1 << p2);
  }
}

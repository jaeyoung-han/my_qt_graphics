#ifndef __MQGAPI_GRAPHICS_ARROW_ITEM_H__
#define __MQGAPI_GRAPHICS_ARROW_ITEM_H__

#include <QGraphicsItem>
#include <QPainter>

namespace MQGAPI {

  class GraphicsArrowItem : public QGraphicsLineItem
  {
  public:
    GraphicsArrowItem(QGraphicsItem *parent = Q_NULLPTR);
    GraphicsArrowItem(const QLineF &line, bool tail_arrow = true, QGraphicsItem *parent = Q_NULLPTR);
    GraphicsArrowItem(qreal x1, qreal y1, qreal x2, qreal y2, bool tail_arrow = true, QGraphicsItem *parent = Q_NULLPTR);
    virtual ~GraphicsArrowItem();

    void flip();

  private:
    ///Show arrow at head
    bool m_head;

    ///Show arrow at tail
    bool m_tail;

  protected:
    ///Paint a QtTextPositionItem
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);

    ///The rectangle that containg the item, used for rough calculations like
    ///collision detection
    QRectF boundingRect() const;

    ///More precise shape compared to boundingRect
    ///In this example, it is redefined to ease selecting those thin lines
    QPainterPath shape() const;

    ///Obtain the angle in radians between two deltas
    ///12 o'clock is 0.0 * pi
    /// 3 o'clock is 0.5 * pi
    /// 6 o'clock is 1.0 * pi
    /// 9 o'clock is 1.5 * pi
    //From www.richelbilderbeek.nl/CppGetAngle.htm
    static double GetAngle(const double dx, const double dy);

  };
};

#endif // __MQGAPI_GRAPHICS_ARROW_ITEM_H__

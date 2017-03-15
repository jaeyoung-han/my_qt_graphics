#ifndef __MQGAPI_GRAPHICS_VIEW_H__
#define __MQGAPI_GRAPHICS_VIEW_H__

#include <QGraphicsView>

namespace MQGAPI {

  class GraphicsArrowItem;
  class GraphicsView: public QGraphicsView
  {
    Q_OBJECT
  public:
    GraphicsView(QWidget *parent = Q_NULLPTR);
    virtual ~GraphicsView();

    void setOrigin(const QPointF& center);
    void setOrigin(qreal x, qreal y);
    const QPointF& getOrigin() const;

  protected:
    virtual void initialize();
    virtual void resizeEvent(QResizeEvent* event);

    void resetAxis();
    QPointF pixelToReal(const QPointF& pixel);
    QPointF realToPixel(const QPointF& real);

  private:
    QPointF origin;
    GraphicsArrowItem* x_axis;
    GraphicsArrowItem* y_axis;
  };

};

#endif // __MQGAPI_GRAPHICS_VIEW_H__

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

		void setAxisVisible(bool on);
		void setOrigin(const QPointF& center);
		void setOrigin(qreal x, qreal y);
		void setScale(qreal scale_factor);
		qreal getScale() const { return scale_factor; }
		const QPointF& getOrigin() const;

		QPointF pixelToReal(const QPointF& pixel);
		QPointF pixelToReal(qreal x, qreal y);
		QPointF realToPixel(const QPointF& real);
		QPointF realToPixel(qreal x, qreal y);

		void setBackgroundColor(const QColor& color);

	public slots:
		void save(const QString& filename);

	protected:
		virtual void initialize();
		virtual void resizeEvent(QResizeEvent* event);

		void resetAxis();

	private:
		QPointF origin;
		qreal scale_factor;
		GraphicsArrowItem* x_axis;
		GraphicsArrowItem* y_axis;
	};

};

#endif // __MQGAPI_GRAPHICS_VIEW_H__

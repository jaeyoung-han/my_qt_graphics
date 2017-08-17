#ifndef __SECTION_SHAPE_H__
#define __SECTION_SHAPE_H__

#include "data_types.h"
#include <QGraphicsScene>

namespace LCR {

	class SectionShape
	{
	public:
        SectionShape() : scale_factor_(0), origin_(0, 0) {}

        virtual void setCollimatorSize(const CollimatorEx& size) = 0;
		virtual void setParameters(double diameter, double septa, int direction) = 0;

		virtual QList<QGraphicsItem*> buildHoles(QGraphicsScene* scene, QPointF origin, qreal scale_factor, int flag) = 0;
        virtual int type() = 0;

    protected:
        qreal getScale() const {
            return scale_factor_;
        }

        void setScaleFactor(qreal scale_factor) {
            scale_factor_ = scale_factor;
        }

        void setOrigin(const QPointF& origin) {
            origin_ = origin;
        }

        QPointF realToPixel(qreal x, qreal y) {
            return QPointF(x * scale_factor_ + origin_.x(), origin_.y() - y * scale_factor_);
        }
    public slots:
        virtual void updateMousePos(QPointF point) {};
        virtual bool checkMousePointInAir(QPointF point) { return false;  }

    private:
        qreal scale_factor_;
        QPointF origin_;
	};
};

#endif // __SECTION_SHAPE_H__

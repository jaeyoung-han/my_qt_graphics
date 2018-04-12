#ifndef __SHAPE_SQUARE_THICKNESS_H__
#define __SHAPE_SQUARE_THICKNESS_H__

#include <QList>
#include "graphicsview.h"
#include "graphicshexagonitem.h"
#include "data_types.h"
#include "SectionShape.h"

class QGraphicsItemGroup;

namespace LCR {

    struct WallAngle {
        float tangent;
        float thick_in_plane;
    };

    class ShapeSquareThick : public SectionShape
    {
    public:
        explicit ShapeSquareThick() : SectionShape() {}

        void setCollimatorSize(const CollimatorEx& size);
        //void setParameters(double diameter, double septa, int direction);
        void setParameters(double diameter[2], double septa[2], int direction);

        QList<QGraphicsItem*> buildHoles(QGraphicsScene* scene, QPointF origin, qreal scale_factor, int flag);

        int type() { return 12; }

    public slots:
        void updateMousePos(QPointF point);
        bool checkMousePointInAir(QPointF point);

    private:
        void updateAngles();
        bool checkInX(qreal abs_x);
        bool checkInY(qreal y);

    private:
        QList<QGraphicsItem*> build_horizontal(QGraphicsScene* scene);

    private:
        //double diameter;  // inscribed circle
        //double septa;
        //int direction;

        std::vector<WallAngle> x_wallangles_;
        std::vector<WallAngle> y_wallangles_;

        CollimatorEx size_;
    };
};

#endif // __SHAPE_SQUARE_THICKNESS_H__

#ifndef __COLLIMATOR_HORIZONTAL_SECTION_VIEW_H__
#define __COLLIMATOR_HORIZONTAL_SECTION_VIEW_H__

#include <QList>
#include "graphicsview.h"
#include "graphicshexagonitem.h"
#include "data_types.h"
#include "SectionShape.h"

class QGraphicsItemGroup;

namespace LCR {

    class CollimatorHorizontalSectionView : public MQGAPI::GraphicsView
    {
        Q_OBJECT
    public:
        enum SHAPE {
            CIRCLE = 0,
            HEXAGON = 1,
            SQUARE = 2,
            SQUARE_THICK = 12,
        };

        CollimatorHorizontalSectionView(double ins_diameter = 0, double _septa = 0, int _direction = 0, QWidget *parent = Q_NULLPTR);

        void setCollimatorSize(const CollimatorEx& size, double ratio);
        void setParameters(double diameter, double septa, int direction);

        void buildHoles();
        void updateBase();
        void drawCircle(double radius);

        bool changeShape(int shape);

    signals:
        void pointInCheck(QPointF, bool);

    private:
        void build_horizontal();
        void build_vertical();
        void draw_outside();

    private slots:
        void updateMousePos(QPointF);

    private:
        SectionShape* shaper_;
        QGraphicsItemGroup* hex_group;
        QList<QGraphicsItem*> hex_list;

        QGraphicsRectItem* base_rect;

        QGraphicsRectItem* outrect_top;
        QGraphicsRectItem* outrect_bot;
        QGraphicsRectItem* outrect_left;
        QGraphicsRectItem* outrect_right;
        QGraphicsRectItem* shrink_rect;

        QGraphicsEllipseItem* circle;

        double diameter;  // inscribed circle
        double septa;
        int direction;

        v3 size_;
        v3 shrink_size_;
    };

};

#endif // __COLLIMATOR_HORIZONTAL_SECTION_VIEW_H__

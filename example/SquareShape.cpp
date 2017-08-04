#include <QtMath>

#include "SquareShape.h"
#include "graphicshexagonitem.h"

using namespace LCR;
using namespace MQGAPI;

void SquareShape::setCollimatorSize(const v3& coll_size)
{
    size = coll_size;
}

void SquareShape::setParameters(double _diameter, double _septa, int _direction)
{
    diameter = _diameter;
    septa = _septa;
    direction = _direction;
}

inline int positive_modulo(int i, int n) {
    return (i % n + n) % n;
}

QList<QGraphicsItem*> SquareShape::buildHoles(QGraphicsScene* scene, QPointF origin, qreal scale_factor, int flag)
{
    setScaleFactor(scale_factor);
    setOrigin(origin);

    return build_horizontal(scene);
}

QList<QGraphicsItem*> SquareShape::build_horizontal(QGraphicsScene* scene)
{
    QList<QGraphicsItem*> hex_list;

    QPen pen(Qt::black);
    QPen pen2(Qt::red);
    QBrush brush(Qt::white, Qt::SolidPattern);

    qreal circum_diameter = diameter;
    qreal scale = getScale();

    qreal delX = (diameter + septa);
    qreal delY = (diameter + septa);

    // 1st quadrant
    int j = 0;
    qreal ypos = j * delY;

    while (ypos - diameter / 2 < size.y / 2) {

        int imax = qCeil((size.x / 2 + circum_diameter / 2) / delX);
        for (int i = 0; i < imax; i++) {
            qreal xpos = i * delX;

            qreal hex_dia = circum_diameter;
            QGraphicsRectItem *hex = new QGraphicsRectItem(hex_dia * scale * -0.5, hex_dia * scale * -0.5, hex_dia * scale, hex_dia * scale);
            hex->setPen(pen);
            hex->setBrush(brush);
            hex->setPos(realToPixel(xpos, ypos));
            scene->addItem(hex);
            hex_list.push_back(hex);
        }
        ypos = delY * (++j);
    }

    // 2nd quadrant
    j = 0;
    ypos = j * delY;
    while (ypos - diameter / 2 < size.y / 2) {

        int imax = qCeil((size.x / 2 + circum_diameter / 2) / delX);
        for (int i = 1; i < imax; i++) {
            qreal xpos = -i * delX;

            qreal hex_dia = circum_diameter;
            QGraphicsRectItem *hex = new QGraphicsRectItem(hex_dia * scale * -0.5, hex_dia * scale * -0.5, hex_dia * scale, hex_dia * scale);
            hex->setPen(pen);
            hex->setBrush(brush);
            hex->setPos(realToPixel(xpos, ypos));
            scene->addItem(hex);
            hex_list.push_back(hex);
        }
        ypos = delY * (++j);
    }


    // 3rd quadrant
    j = -1;
    ypos = j * delY;
    while (ypos + diameter / 2 > size.y / -2) {

        int imax = qCeil((size.x / 2 + circum_diameter / 2) / delX);
        for (int i = 1; i < imax; i++) {
            qreal xpos = -i * delX;

            qreal hex_dia = circum_diameter;
            QGraphicsRectItem *hex = new QGraphicsRectItem(hex_dia * scale * -0.5, hex_dia * scale * -0.5, hex_dia * scale, hex_dia * scale);
            hex->setPen(pen);
            hex->setBrush(brush);
            hex->setPos(realToPixel(xpos, ypos));
            scene->addItem(hex);
            hex_list.push_back(hex);
        }
        ypos = delY * (--j);
    }

    // 4th quadrant
    j = -1;
    ypos = j * delY;
    while (ypos + diameter / 2 > size.y / -2) {
        int imax = qCeil((size.x / 2 + circum_diameter / 2) / delX);
        for (int i = 0; i < imax; i++) {
            qreal xpos = i * delX;

            qreal hex_dia = circum_diameter;
            QGraphicsRectItem *hex = new QGraphicsRectItem(hex_dia * scale * -0.5, hex_dia * scale * -0.5, hex_dia * scale, hex_dia * scale);
            hex->setPen(pen);
            hex->setBrush(brush);
            hex->setPos(realToPixel(xpos, ypos));
            scene->addItem(hex);
            hex_list.push_back(hex);
        }
        ypos = delY * (--j);
    }

    return hex_list;
}

#include <QtMath>

#include "shape_square.h"
#include "graphicshexagonitem.h"

using namespace LCR;
using namespace MQGAPI;

void SquareShape::setCollimatorSize(const CollimatorEx& size)
{
    size_ = size;
}

void SquareShape::setParameters(double _diameter, double _septa, int _direction)
{
    diameter = _diameter;
    septa = _septa;
    direction = _direction;
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

    while (ypos - diameter / 2 < size_.size.y / 2) {

        int imax = qCeil((size_.size.x / 2 + circum_diameter / 2) / delX);
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
    while (ypos - diameter / 2 < size_.size.y / 2) {

        int imax = qCeil((size_.size.x / 2 + circum_diameter / 2) / delX);
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
    while (ypos + diameter / 2 > size_.size.y / -2) {

        int imax = qCeil((size_.size.x / 2 + circum_diameter / 2) / delX);
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
    while (ypos + diameter / 2 > size_.size.y / -2) {
        int imax = qCeil((size_.size.x / 2 + circum_diameter / 2) / delX);
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

bool SquareShape::checkMousePointInAir(QPointF point)
{
    qreal h = size_.focus_distance - size_.section_height;
    qreal x = qAbs(point.x());
    qreal y = qAbs(point.y());

    if (x > size_.size.x * 0.5 || y > size_.size.y * 0.5)
        return false;

    QPointF center = getNearestRectangle(point);
    return checkPointInAir(point, center);
}

QPointF SquareShape::getNearestRectangle(QPointF point)
{
    qreal w = diameter + septa;

    int i = (int)floor((point.x() + 0.5 * w) / w);
    int j = (int)floor((point.y() + 0.5 * w) / w);

    return QPointF(i * w, j * w);
}

bool SquareShape::checkPointInAir(QPointF point, QPointF rect_center)
{
    qreal x = qAbs(point.x() - rect_center.x());
    qreal y = qAbs(point.y() - rect_center.y());

    return (x < diameter * 0.5) && (y < diameter * 0.5);
}

#include <QtMath>

#include "shape_square.h"
#include "graphicshexagonitem.h"

using namespace LCR;
using namespace MQGAPI;

void SquareShape::setCollimatorSize(const CollimatorEx& size)
{
    size_ = size;
}

//void SquareShape::setParameters(double _diameter, double _septa, int _direction)
//{
//    diameter_x = _diameter;
//    diameter_y = _diameter;
//    septa_x = _septa;
//    septa_y = _septa;
//    direction = _direction;
//}

void SquareShape::setParameters(double _diameter[2], double _septa[2], int _direction)
{
    diameter_x = _diameter[0];
    diameter_y = _diameter[1];
    septa_x = _septa[0];
    septa_y = _septa[1];
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

//    qreal circum_diameter = diameter;
    qreal scale = getScale();

    qreal delX = (diameter_x + septa_x);
    qreal delY = (diameter_y + septa_y);

    // 1st quadrant
    int j = 0;
    qreal ypos = j * delY;

    while (ypos - diameter_y / 2 < size_.size.y / 2) {

        int imax = qCeil((size_.size.x / 2 + diameter_x / 2) / delX);
        for (int i = 0; i < imax; i++) {
            qreal xpos = i * delX;

            qreal width = diameter_x * scale;
            qreal height = diameter_y * scale;
            QGraphicsRectItem *hex = new QGraphicsRectItem(width * -0.5, height * -0.5, width, height);
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
    while (ypos - diameter_y / 2 < size_.size.y / 2) {

        int imax = qCeil((size_.size.x / 2 + diameter_x / 2) / delX);
        for (int i = 1; i < imax; i++) {
            qreal xpos = -i * delX;

            qreal width = diameter_x * scale;
            qreal height = diameter_y * scale;
            QGraphicsRectItem *hex = new QGraphicsRectItem(width * -0.5, height * -0.5, width, height);
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
    while (ypos + diameter_y / 2 > size_.size.y / -2) {

        int imax = qCeil((size_.size.x / 2 + diameter_x / 2) / delX);
        for (int i = 1; i < imax; i++) {
            qreal xpos = -i * delX;

            qreal width = diameter_x * scale;
            qreal height = diameter_y * scale;
            QGraphicsRectItem *hex = new QGraphicsRectItem(width * -0.5, height * -0.5, width, height);
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
    while (ypos + diameter_y / 2 > size_.size.y / -2) {
        int imax = qCeil((size_.size.x / 2 + diameter_x / 2) / delX);
        for (int i = 0; i < imax; i++) {
            qreal xpos = i * delX;

            qreal width = diameter_x * scale;
            qreal height = diameter_y * scale;
            QGraphicsRectItem *hex = new QGraphicsRectItem(width * -0.5, height * -0.5, width, height);
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
//    qreal h = size_.focus_distance - size_.section_height;
    qreal x = qAbs(point.x());
    qreal y = qAbs(point.y());

    if (x > size_.size.x * 0.5 || y > size_.size.y * 0.5)
        return false;

    QPointF center = getNearestRectangle(point);
    return checkPointInAir(point, center);
}

QPointF SquareShape::getNearestRectangle(QPointF point)
{
    qreal w = diameter_x + septa_x;
    qreal h = diameter_y + septa_y;

    int i = (int)floor((point.x() + 0.5 * w) / w);
    int j = (int)floor((point.y() + 0.5 * h) / h);

    return QPointF(i * w, j * h);
}

bool SquareShape::checkPointInAir(QPointF point, QPointF rect_center)
{
    qreal x = qAbs(point.x() - rect_center.x());
    qreal y = qAbs(point.y() - rect_center.y());

    return (x < diameter_x * 0.5) && (y < diameter_y * 0.5);
}

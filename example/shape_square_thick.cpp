#include <QtMath>

#include "shape_square_thick.h"
#include "graphicshexagonitem.h"

using namespace LCR;
using namespace MQGAPI;

void ShapeSquareThick::setCollimatorSize(const CollimatorEx& size)
{
    size_ = size;
}

void ShapeSquareThick::setParameters(double _diameter, double _septa, int _direction)
{
    //diameter = _diameter;
    //septa = _septa;
    //direction = _direction;

    updateAngles();
}

QList<QGraphicsItem*> ShapeSquareThick::buildHoles(QGraphicsScene* scene, QPointF origin, qreal scale_factor, int flag)
{
    setScaleFactor(scale_factor);
    setOrigin(origin);

    return build_horizontal(scene);
}

void ShapeSquareThick::updateAngles()
{
    qreal diameter = size_.diameter[0];
    qreal septa = size_.septa[0];
    qreal b = size_.focus_distance - size_.size.z;
    qreal bb = b * b;

    x_wallangles_.clear();
    qreal x_size = b / size_.focus_distance * size_.size.x / 2;
    qreal xpos = 0;
    while (xpos < x_size + diameter / 2) {
        WallAngle wa;

        qreal r_cos_theta = sqrt((bb + (xpos + diameter / 2) * (xpos + diameter / 2)) / bb);
        wa.thick_in_plane = septa * r_cos_theta;
        wa.tangent = (xpos + wa.thick_in_plane / 2 + diameter / 2) / b;
        x_wallangles_.push_back(wa);

        xpos = xpos + diameter + wa.thick_in_plane;
    }

    y_wallangles_.clear();
    qreal y_size = b / size_.focus_distance * size_.size.y / 2;
    qreal ypos = 0;
    while (ypos < y_size + diameter / 2) {
        WallAngle wa;

        qreal r_cos_theta = sqrt((bb + (ypos + diameter / 2) * (ypos + diameter / 2)) / bb);
        wa.thick_in_plane = septa * r_cos_theta;
        wa.tangent = (ypos + wa.thick_in_plane / 2 + diameter / 2) / b;
        y_wallangles_.push_back(wa);

        ypos = ypos + diameter + wa.thick_in_plane;
    }
}

QList<QGraphicsItem*> ShapeSquareThick::build_horizontal(QGraphicsScene* scene)
{
    QList<QGraphicsItem*> sqr_list;

    QPen pen(Qt::black);
    QPen pen2(Qt::red);
    QBrush brush(Qt::white, Qt::SolidPattern);

    qreal scale = getScale();
    v3 size = size_.size;
    qreal b = size_.focus_distance - size_.section_height;

    // Y = 0
    qreal size_x = x_wallangles_[0].tangent * b * 2 - x_wallangles_[0].thick_in_plane;
    qreal size_y = size_x;
    qreal xpos = 0;
    qreal ypos = 0;

    // Center
    QGraphicsRectItem *sqr = new QGraphicsRectItem(size_x * scale * -0.5, size_y * scale * -0.5, size_x * scale, size_y * scale);
    sqr->setPen(pen);
    sqr->setBrush(brush);
    sqr->setPos(realToPixel(xpos, ypos));
    scene->addItem(sqr);
    sqr_list.push_back(sqr);

    for (int i = 0; i < x_wallangles_.size() - 1; ++i) {
        const WallAngle& wa2 = x_wallangles_[i+1];
        const WallAngle& wa1 = x_wallangles_[i];
        size_x = (wa2.tangent - wa1.tangent) * b - (wa2.thick_in_plane + wa1.thick_in_plane) / 2;
        xpos = wa1.tangent * b + size_x/2 + wa1.thick_in_plane/2;

        // Right 
        QGraphicsRectItem *sqr = new QGraphicsRectItem(size_x * scale * -0.5, size_y * scale * -0.5, size_x * scale, size_y * scale);
        sqr->setPen(pen);
        sqr->setBrush(brush);
        sqr->setPos(realToPixel(xpos, ypos));
        scene->addItem(sqr);
        sqr_list.push_back(sqr);

        // Left
        QGraphicsRectItem *sqr2 = new QGraphicsRectItem(size_x * scale * -0.5, size_y * scale * -0.5, size_x * scale, size_y * scale);
        sqr2->setPen(pen);
        sqr2->setBrush(brush);
        sqr2->setPos(realToPixel(-xpos, ypos));
        scene->addItem(sqr2);
        sqr_list.push_back(sqr2);
    }

    for (int j = 0; j < y_wallangles_.size() - 1; ++j) {
        // Set y size and position
        const WallAngle& ywa2 = y_wallangles_[j + 1];
        const WallAngle& ywa1 = y_wallangles_[j];

        size_y = (ywa2.tangent - ywa1.tangent) * b - (ywa2.thick_in_plane + ywa1.thick_in_plane) / 2;
        ypos = ywa1.tangent * b + size_y/2 + ywa1.thick_in_plane/2;

        /////////////////////////////////////////////////////
        // Upper line
        /////////////////////////////////////////////////////
        // Initialize x size and position
        size_x = x_wallangles_[0].tangent * b * 2 - x_wallangles_[0].thick_in_plane;
        xpos = 0;

        // Center
        QGraphicsRectItem *sqr = new QGraphicsRectItem(size_x * scale * -0.5, size_y * scale * -0.5, size_x * scale, size_y * scale);
        sqr->setPen(pen);
        sqr->setBrush(brush);
        sqr->setPos(realToPixel(xpos, ypos));
        scene->addItem(sqr);
        sqr_list.push_back(sqr);

        for (int i = 0; i < x_wallangles_.size() - 1; ++i) {
            const WallAngle& wa2 = x_wallangles_[i + 1];
            const WallAngle& wa1 = x_wallangles_[i];
            size_x = (wa2.tangent - wa1.tangent) * b - (wa2.thick_in_plane + wa1.thick_in_plane) / 2;
            xpos = wa1.tangent * b + size_x / 2 + wa1.thick_in_plane / 2;

            // Right
            QGraphicsRectItem *sqr = new QGraphicsRectItem(size_x * scale * -0.5, size_y * scale * -0.5, size_x * scale, size_y * scale);
            sqr->setPen(pen);
            sqr->setBrush(brush);
            sqr->setPos(realToPixel(xpos, ypos));
            scene->addItem(sqr);
            sqr_list.push_back(sqr);

            // Left
            QGraphicsRectItem *sqr2 = new QGraphicsRectItem(size_x * scale * -0.5, size_y * scale * -0.5, size_x * scale, size_y * scale);
            sqr2->setPen(pen);
            sqr2->setBrush(brush);
            sqr2->setPos(realToPixel(-xpos, ypos));
            scene->addItem(sqr2);
            sqr_list.push_back(sqr2);
        }

        /////////////////////////////////////////////////////
        // Lower line
        /////////////////////////////////////////////////////
        // Initialize x size and position
        size_x = x_wallangles_[0].tangent * b * 2 - x_wallangles_[0].thick_in_plane;
        xpos = 0;

        // Center
        QGraphicsRectItem *sqr2 = new QGraphicsRectItem(size_x * scale * -0.5, size_y * scale * -0.5, size_x * scale, size_y * scale);
        sqr2->setPen(pen);
        sqr2->setBrush(brush);
        sqr2->setPos(realToPixel(xpos, -ypos));
        scene->addItem(sqr2);
        sqr_list.push_back(sqr2);

        for (int i = 0; i < x_wallangles_.size() - 1; ++i) {
            const WallAngle& wa2 = x_wallangles_[i + 1];
            const WallAngle& wa1 = x_wallangles_[i];
            size_x = (wa2.tangent - wa1.tangent) * b - (wa2.thick_in_plane + wa1.thick_in_plane) / 2;
            xpos = wa1.tangent * b + size_x / 2 + wa1.thick_in_plane / 2;

            // Right
            QGraphicsRectItem *sqr = new QGraphicsRectItem(size_x * scale * -0.5, size_y * scale * -0.5, size_x * scale, size_y * scale);
            sqr->setPen(pen);
            sqr->setBrush(brush);
            sqr->setPos(realToPixel(xpos, -ypos));
            scene->addItem(sqr);
            sqr_list.push_back(sqr);

            // Left
            QGraphicsRectItem *sqr2 = new QGraphicsRectItem(size_x * scale * -0.5, size_y * scale * -0.5, size_x * scale, size_y * scale);
            sqr2->setPen(pen);
            sqr2->setBrush(brush);
            sqr2->setPos(realToPixel(-xpos, -ypos));
            scene->addItem(sqr2);
            sqr_list.push_back(sqr2);
        }
    }

    return sqr_list;
}

void ShapeSquareThick::updateMousePos(QPointF point)
{
    
}

bool ShapeSquareThick::checkMousePointInAir(QPointF point)
{
    qreal h = size_.focus_distance - size_.section_height;
    qreal x = qAbs(point.x());
    qreal y = qAbs(point.y());

    if (x > size_.size.x * 0.5 || y > size_.size.y * 0.5)
        return false;

    return checkInX(x) && checkInY(y);
}

bool ShapeSquareThick::checkInX(qreal abs_x)
{
    qreal h = size_.focus_distance - size_.section_height;

    if (abs_x < x_wallangles_[0].tangent * h - x_wallangles_[0].thick_in_plane * 0.5) {
        return true;
    }

    qreal xx = abs_x / h;

    for (int i = 0; i < x_wallangles_.size() - 1; ++i) {
        const WallAngle& wa1 = x_wallangles_[i];
        const WallAngle& wa2 = x_wallangles_[i + 1];

        if (wa1.tangent <= xx && xx < wa2.tangent) {
            if (h * wa1.tangent + 0.5 * wa1.thick_in_plane < abs_x &&
                h * wa2.tangent - 0.5 * wa2.thick_in_plane > abs_x)
                return true;
            else
                return false;
        }
    }

    return false;
}

bool ShapeSquareThick::checkInY(qreal abs_y)
{
    qreal h = size_.focus_distance - size_.section_height;

    if (abs_y < y_wallangles_[0].tangent * h - y_wallangles_[0].thick_in_plane * 0.5) {
        return true;
    }

    qreal yy = abs_y / h;

    for (int i = 0; i < y_wallangles_.size() - 1; ++i) {
        const WallAngle& wa1 = y_wallangles_[i];
        const WallAngle& wa2 = y_wallangles_[i + 1];

        if (wa1.tangent <= yy && yy < wa2.tangent) {
            if (h * wa1.tangent + 0.5 * wa1.thick_in_plane < abs_y &&
                h * wa2.tangent - 0.5 * wa2.thick_in_plane > abs_y)
                return true;
            else
                return false;
        }
    }

    return false;
}

#include <QtMath>

#include "CollimatorHorizontalSectionView.h"
#include "graphicshexagonitem.h"
#include "shape_hexagon.h"
#include "shape_square.h"
#include "shape_square_thick.h"

using namespace LCR;
using namespace MQGAPI;

CollimatorHorizontalSectionView::CollimatorHorizontalSectionView(double ins_diameter, double _septa, int _direction, QWidget *parent)
    : GraphicsView(parent)
    , shaper_(nullptr)
    , hex_group(Q_NULLPTR)
    , base_rect(Q_NULLPTR)
    , diameter(ins_diameter)
    , septa(_septa)
    , direction(_direction)
{
    setAxisVisible(false);
    setBackgroundColor(Qt::black);

    QPen pen;
    pen.setColor(Qt::red);
    pen.setWidth(2);

    QBrush bkbrush(Qt::black);

    circle = new QGraphicsEllipseItem();
    circle->setVisible(false);
    circle->setZValue(1);
    circle->setPen(pen);

    scene()->addItem(circle);


    base_rect = new QGraphicsRectItem(0, 0, 1, 1);
    base_rect->setZValue(0);

    scene()->addItem(base_rect);

    outrect_top = new QGraphicsRectItem(0, 0, 1, 1);
    outrect_bot = new QGraphicsRectItem(0, 0, 1, 1);
    outrect_left = new QGraphicsRectItem(0, 0, 1, 1);
    outrect_right = new QGraphicsRectItem(0, 0, 1, 1);
    shrink_rect = new QGraphicsRectItem(0, 0, 1, 1);

    outrect_top->setBrush(bkbrush);
    outrect_bot->setBrush(bkbrush);
    outrect_left->setBrush(bkbrush);
    outrect_right->setBrush(bkbrush);
    shrink_rect->setPen(pen);

    outrect_top->setZValue(1);
    outrect_bot->setZValue(1);
    outrect_left->setZValue(1);
    outrect_right->setZValue(1);
    shrink_rect->setZValue(1);


    scene()->addItem(outrect_top);
    scene()->addItem(outrect_bot);
    scene()->addItem(outrect_left);
    scene()->addItem(outrect_right);
    scene()->addItem(shrink_rect);

    changeShape(SQUARE);

    setMouseTracking(true);

    connect(this, SIGNAL(sendMousePoint(QPointF)), this, SLOT(updateMousePos(QPointF)));
}

bool CollimatorHorizontalSectionView::changeShape(int shape)
{
    if (shaper_) delete shaper_;

    switch (shape) {
    default:
    case CIRCLE:
    case HEXAGON:
        shaper_ = new HexagonShape();
        break;
    case SQUARE:
        shaper_ = new SquareShape();
        break;
    case SQUARE_THICK:
        shaper_ = new ShapeSquareThick();
        break;
    }

    return true;
}

void CollimatorHorizontalSectionView::setCollimatorSize(const CollimatorEx& size, double ratio)
{
    size_ = size.size;
    shrink_size_.x = size.size.x * ratio;
    shrink_size_.y = size.size.y * ratio;
    shrink_size_.z = size.size.z;
    shaper_->setCollimatorSize(size);
}

void CollimatorHorizontalSectionView::setParameters(double _diameter, double _septa, int _direction)
{
    diameter = _diameter;
    septa = _septa;
    direction = _direction;

    shaper_->setParameters(_diameter, _septa, _direction);
}

void CollimatorHorizontalSectionView::updateBase()
{
    if (septa < 0) {
        QBrush brush(Qt::white);
        base_rect->setBrush(brush);
    }
    else {
        QBrush brush(Qt::lightGray);
        base_rect->setBrush(brush);
    }

    base_rect->setRect(size_.x * getScale() * -0.5, size_.y * getScale() * -0.5, size_.x * getScale(), size_.y * getScale());
    base_rect->setPos(realToPixel(0, 0));
}

void CollimatorHorizontalSectionView::updateMousePos(QPointF point)
{
//    shaper_->updateMousePos(point);
    QPointF pos = pixelToReal(point);
    bool res = shaper_->checkMousePointInAir(pos);
    emit pointInCheck(pos, res);
}

void CollimatorHorizontalSectionView::buildHoles()
{
    if (hex_group) {
        scene()->destroyItemGroup(hex_group);

        for (int i = 0; i < hex_list.size(); ++i) {
            scene()->removeItem(hex_list[i]);
        }

        hex_group = Q_NULLPTR;
    }

    hex_list.clear();

    if (septa < 0) {
        updateBase();
        return;
    }

    if (diameter > 0) {
        hex_list = shaper_->buildHoles(scene(), getOrigin(), getScale(), direction);
        hex_group = scene()->createItemGroup(hex_list);
    }

    updateBase();
    draw_outside();
}

void CollimatorHorizontalSectionView::drawCircle(double radius)
{
    QPointF tl(-1 * radius, -1 * radius);
    QPointF br(radius, radius);

    QRectF rect;

    rect.setTopLeft(realToPixel(tl));
    rect.setBottomRight(realToPixel(br));
    circle->setRect(rect);
    circle->setVisible(true);
}

void CollimatorHorizontalSectionView::draw_outside()
{
    QRectF brect = this->base_rect->rect();
    QRectF rect = brect;
    QPointF pos = base_rect->pos();
    qreal pdia = diameter * 2 / sqrt(3) * getScale();

    // Top
    rect.setWidth(brect.width() + pdia);
    rect.setHeight(pdia);
    outrect_top->setRect(rect);
    outrect_top->setPos(pos - QPointF(0, pdia));

    // Bottom
    rect.setTop(brect.bottom());
    rect.setHeight(pdia);
    outrect_bot->setRect(rect);
    outrect_bot->setPos(pos - QPointF(pdia, 0));

    // Left
    rect = brect;
    rect.setWidth(pdia);
    rect.setHeight(brect.height() + pdia);
    outrect_left->setRect(rect);
    outrect_left->setPos(pos - QPointF(pdia, pdia));

    // Right
    rect.setLeft(brect.right());
    rect.setWidth(pdia);
    rect.setHeight(brect.height() + pdia);
    outrect_right->setRect(rect);
    outrect_right->setPos(pos);

    // Shrinked boundary
    shrink_rect->setRect(shrink_size_.x * getScale() * -0.5, shrink_size_.y * getScale() * -0.5, shrink_size_.x * getScale(), shrink_size_.y * getScale());
    shrink_rect->setPos(realToPixel(0, 0));

}

#include <QtMath>

#include "shape_hexagon.h"
#include "graphicshexagonitem.h"

using namespace LCR;
using namespace MQGAPI;

void HexagonShape::setCollimatorSize(const CollimatorEx& size)
{
	size_ = size;
}

void HexagonShape::setParameters(double _diameter, double _septa, int _direction)
{
	diameter = _diameter;
	septa = _septa;
	direction = _direction;
}

inline int positive_modulo(int i, int n) {
	return (i % n + n) % n;
}

QList<QGraphicsItem*> HexagonShape::buildHoles(QGraphicsScene* scene, QPointF origin, qreal scale_factor, int flag)
{
    setScaleFactor(scale_factor);
    setOrigin(origin);

    if (flag == 0)
        return build_horizontal(scene);
    else
        return build_vertical(scene);
}

QList<QGraphicsItem*> HexagonShape::build_horizontal(QGraphicsScene* scene)
{
    QList<QGraphicsItem*> hex_list;
    
    QPen pen(Qt::black);
	QPen pen2(Qt::red);
	QBrush brush(Qt::white, Qt::SolidPattern);

	qreal circum_diameter = diameter * 2 / sqrt(3);
	qreal scale = getScale();

	qreal circum_diameter2 = circum_diameter;// (diameter + 2 * (septa - 0.3)) * 2 / sqrt(3);

	qreal delX = sqrt(3) * (diameter + septa) / 2;
	qreal delY = (diameter + septa) / 2;

	qreal angle = 0;

	// 1st quadrant
	int j = 0;
	qreal ypos = j * delY;
	while (ypos - diameter / 2 < size_.size.y / 2) {

		int iminidx = qAbs(j % 2);
		qreal imin = iminidx * delX;

		int imax = qCeil((size_.size.x / 2 + circum_diameter / 2 - imin) / (2 * delX));
		for (int i = 0; i < imax; i++) {
			int p = 2 * i + iminidx;
			int q = 0.5 * (j - p);
			qreal xpos = p * delX;
			qreal ypos = delY * j;

			qreal hex_dia = circum_diameter;
			if (positive_modulo(p, 3) == positive_modulo(q, 3)) {
				hex_dia = circum_diameter2;
			}
			GraphicsHexagonItem *hex = new GraphicsHexagonItem(hex_dia * scale, angle);
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

		int iminidx = qAbs(j % 2);
		qreal imin = iminidx * delX;

		int imax = qCeil((size_.size.x / 2 + circum_diameter / 2 - imin) / (2 * delX));
		for (int i = qAbs((j + 1) % 2); i < imax; i++) {
			int p = 2 * i + iminidx;
			int q = 0.5 * (j - p);
			qreal xpos = -p * delX;
			qreal ypos = delY * j;

			qreal hex_dia = circum_diameter;
			if (positive_modulo(p, 3) == positive_modulo(q, 3)) {
				hex_dia = circum_diameter2;
			}
			GraphicsHexagonItem *hex = new GraphicsHexagonItem(hex_dia * scale, angle);
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

		int iminidx = qAbs(j % 2);
		qreal imin = iminidx * delX;

		int imax = qCeil((size_.size.x / 2 + circum_diameter / 2 - imin) / (2 * delX));
		for (int i = qAbs((j + 1) % 2); i < imax; i++) {
			int p = 2 * i + iminidx;
			int q = 0.5 * (j - p);

			qreal xpos = -p * delX;
			qreal ypos = delY * j;

			qreal hex_dia = circum_diameter;
			if (positive_modulo(p, 3) == positive_modulo(q, 3)) {
				hex_dia = circum_diameter2;
			}
			GraphicsHexagonItem *hex = new GraphicsHexagonItem(hex_dia * scale, angle);
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
		int iminidx = qAbs(j % 2);
		qreal imin = iminidx * delX;

		int imax = qCeil((size_.size.x / 2 + circum_diameter / 2 - imin) / (2 * delX));
		for (int i = 0; i < imax; i++) {
			int p = 2 * i + iminidx;
			int q = 0.5 * (j - p);

			qreal xpos = p * delX;
			qreal ypos = delY * j;

			qreal hex_dia = circum_diameter;
			if (positive_modulo(p, 3) == positive_modulo(q, 3)) {
				hex_dia = circum_diameter2;
			}
			GraphicsHexagonItem *hex = new GraphicsHexagonItem(hex_dia * scale, angle);
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

QList<QGraphicsItem*> HexagonShape::build_vertical(QGraphicsScene* scene)
{
    QList<QGraphicsItem*> hex_list;

	QPen pen(Qt::black);
	QPen pen2(Qt::red);
	QBrush brush(Qt::white, Qt::SolidPattern);

	qreal circum_diameter = diameter * 2 / sqrt(3);
	qreal scale = getScale();

	qreal circum_diameter2 = circum_diameter;// (diameter + 2 * (septa - 0.3)) * 2 / sqrt(3);

	qreal delX = (diameter + septa) / 2;
	qreal delY = sqrt(3) * (diameter + septa) / 2;

	qreal angle = M_PI_2;

	// 1st quadrant
	int i = 0;
	qreal xpos = i * delX;
	while (xpos - diameter / 2 < size_.size.x / 2) {

		int iminidx = qAbs(i % 2);
		qreal imin = iminidx * delY;

		int imax = qCeil((size_.size.y / 2 + circum_diameter / 2 - imin) / (2 * delY));
		for (int j = 0; j < imax; j++) {
			int q = 2 * j + iminidx;
			int p = 0.5 * (i - q);

			qreal xpos = delX * i;
			qreal ypos = q * delY;

			qreal hex_dia = circum_diameter;
			if (positive_modulo(p, 3) == positive_modulo(q, 3)) {
				hex_dia = circum_diameter2;
			}
			GraphicsHexagonItem *hex = new GraphicsHexagonItem(hex_dia * scale, angle);
			hex->setPen(pen);
			hex->setBrush(brush);
			hex->setPos(realToPixel(xpos, ypos));
			scene->addItem(hex);
			hex_list.push_back(hex);
		}
		xpos = delX * (++i);
	}

	// 2nd quadrant
	i = 0;
	xpos = i * delX;
	while (xpos - diameter / 2 < size_.size.x / 2) {

		int iminidx = qAbs(i % 2);
		qreal imin = iminidx * delY;

		int imax = qCeil((size_.size.y / 2 + circum_diameter / 2 - imin) / (2 * delY));
		for (int j = qAbs((i + 1) % 2); j < imax; j++) {
			int q = 2 * j + iminidx;
			int p = 0.5 * (i - q);

			qreal xpos = delX * i;
			qreal ypos = -q * delY;

			qreal hex_dia = circum_diameter;
			if (positive_modulo(p, 3) == positive_modulo(q, 3)) {
				hex_dia = circum_diameter2;
			}
			GraphicsHexagonItem *hex = new GraphicsHexagonItem(hex_dia * scale, angle);
			hex->setPen(pen);
			hex->setBrush(brush);
			hex->setPos(realToPixel(xpos, ypos));
			scene->addItem(hex);
			hex_list.push_back(hex);
		}
		xpos = delX * (++i);
	}

	// 3rd quadrant
	i = -1;
	xpos = i * delX;
	while (xpos + diameter / 2 > size_.size.x / -2) {

		int iminidx = qAbs(i % 2);
		qreal imin = iminidx * delY;

		int imax = qCeil((size_.size.y / 2 + circum_diameter / 2 - imin) / (2 * delY));
		for (int j = qAbs((i + 1) % 2); j < imax; j++) {
			int q = 2 * j + iminidx;
			int p = 0.5 * (i - q);

			qreal xpos = delX * i;
			qreal ypos = -q * delY;

			qreal hex_dia = circum_diameter;
			if (positive_modulo(p, 3) == positive_modulo(q, 3)) {
				hex_dia = circum_diameter2;
			}
			GraphicsHexagonItem *hex = new GraphicsHexagonItem(hex_dia * scale, angle);
			hex->setPen(pen);
			hex->setBrush(brush);
			hex->setPos(realToPixel(xpos, ypos));
			scene->addItem(hex);
			hex_list.push_back(hex);
		}
		xpos = delX * (--i);
	}

	// 4th quadrant
	i = -1;
	xpos = i * delX;
	while (xpos + diameter / 2 > size_.size.x / -2) {
		int iminidx = qAbs(i % 2);
		qreal imin = iminidx * delY;

		int imax = qCeil((size_.size.y / 2 + circum_diameter / 2 - imin) / (2 * delY));
		for (int j = 0; j < imax; j++) {
			int q = 2 * j + iminidx;
			int p = 0.5 * (i - q);

			qreal xpos = delX * i;
			qreal ypos = q * delY;

			qreal hex_dia = circum_diameter;
			if (positive_modulo(p, 3) == positive_modulo(q, 3)) {
				hex_dia = circum_diameter2;
			}
			GraphicsHexagonItem *hex = new GraphicsHexagonItem(hex_dia * scale, angle);
			hex->setPen(pen);
			hex->setBrush(brush);
			hex->setPos(realToPixel(xpos, ypos));
			scene->addItem(hex);
			hex_list.push_back(hex);
		}
		xpos = delX * (--i);
	}

    return hex_list;
}

#define SQRT_3 1.732050807568877f
#define R_COS_PI_6 1.15470053837925f

bool HexagonShape::checkMousePointInAir(QPointF point)
{
    qreal h = size_.focus_distance - size_.section_height;
    qreal x = qAbs(point.x());
    qreal y = qAbs(point.y());

    if (x > size_.size.x * 0.5 || y > size_.size.y * 0.5)
        return false;

    QPointF center = getNearestHexagon(point);
    return checkPointInAir(point, center);
}


QPointF HexagonShape::getNearestHexagon(QPointF point)
{
    qreal H = 0.5f * (diameter + septa);
    qreal W = SQRT_3 * H;

    if (size_.direction == 1) {
        W = 0.5f * (diameter + septa);
        H = SQRT_3 * W;
    }

    int i = (int)floor(point.x() / W);
    int j = (int)floor(point.y() / H);

    QPointF c1, c2;

    if ((i + j) % 2 == 0) {
        c1.setX(i * W);
        c1.setY(j * H);
        c2.setX((i + 1) * W);
        c2.setY((j + 1) * H);
    }
    else {
        c1.setX(i * W);
        c1.setY((j + 1) * H);
        c2.setX((i + 1) * W);
        c2.setY(j * H);
    }

    qreal dist1 = (c1.x() - point.x()) * (c1.x() - point.x()) + (c1.y() - point.y()) * (c1.y() - point.y());
    qreal dist2 = (c2.x() - point.x()) * (c2.x() - point.x()) + (c2.y() - point.y()) * (c2.y() - point.y());

    if (dist1 < dist2) {
        return c1;
    }
    else {
        return c2;
    }
}

bool HexagonShape::checkPointInAir(QPointF point, QPointF rect_center)
{
    qreal W = diameter * R_COS_PI_6;
    qreal H = diameter;

    qreal x = qAbs(point.x() - rect_center.x());
    qreal y = qAbs(point.y() - rect_center.y());

    if (size_.direction == 1) {
        x = qAbs(point.y() - rect_center.y());
        y = qAbs(point.x() - rect_center.x());
    }

    return (x < W * 0.5) && (y < H * 0.5) && (SQRT_3 * x + y - H) < 0;
}

#include <QtMath>

#include "HexagonShape.h"
#include "graphicshexagonitem.h"

using namespace LCR;
using namespace MQGAPI;

void HexagonShape::setCollimatorSize(const v3& coll_size)
{
	size = coll_size;
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
	while (ypos - diameter / 2 < size.y / 2) {

		int iminidx = qAbs(j % 2);
		qreal imin = iminidx * delX;

		int imax = qCeil((size.x / 2 + circum_diameter / 2 - imin) / (2 * delX));
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
	while (ypos - diameter / 2 < size.y / 2) {

		int iminidx = qAbs(j % 2);
		qreal imin = iminidx * delX;

		int imax = qCeil((size.x / 2 + circum_diameter / 2 - imin) / (2 * delX));
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
	while (ypos + diameter / 2 > size.y / -2) {

		int iminidx = qAbs(j % 2);
		qreal imin = iminidx * delX;

		int imax = qCeil((size.x / 2 + circum_diameter / 2 - imin) / (2 * delX));
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
	while (ypos + diameter / 2 > size.y / -2) {
		int iminidx = qAbs(j % 2);
		qreal imin = iminidx * delX;

		int imax = qCeil((size.x / 2 + circum_diameter / 2 - imin) / (2 * delX));
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
	while (xpos - diameter / 2 < size.x / 2) {

		int iminidx = qAbs(i % 2);
		qreal imin = iminidx * delY;

		int imax = qCeil((size.y / 2 + circum_diameter / 2 - imin) / (2 * delY));
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
	while (xpos - diameter / 2 < size.x / 2) {

		int iminidx = qAbs(i % 2);
		qreal imin = iminidx * delY;

		int imax = qCeil((size.y / 2 + circum_diameter / 2 - imin) / (2 * delY));
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
	while (xpos + diameter / 2 > size.x / -2) {

		int iminidx = qAbs(i % 2);
		qreal imin = iminidx * delY;

		int imax = qCeil((size.y / 2 + circum_diameter / 2 - imin) / (2 * delY));
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
	while (xpos + diameter / 2 > size.x / -2) {
		int iminidx = qAbs(i % 2);
		qreal imin = iminidx * delY;

		int imax = qCeil((size.y / 2 + circum_diameter / 2 - imin) / (2 * delY));
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

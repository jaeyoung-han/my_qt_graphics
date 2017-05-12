#include <QtMath>

#include "CollimatorHorizontalSectionView.h"
#include "graphicshexagonitem.h"

using namespace LCR;
using namespace MQGAPI;

CollimatorHorizontalSectionView::CollimatorHorizontalSectionView(double ins_diameter, double _septa, int _direction, QWidget *parent)
	: GraphicsView(parent)
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

	outrect_top->setBrush(bkbrush);
	outrect_bot->setBrush(bkbrush);
	outrect_left->setBrush(bkbrush);
	outrect_right->setBrush(bkbrush);

	outrect_top->setZValue(1);
	outrect_bot->setZValue(1);
	outrect_left->setZValue(1);
	outrect_right->setZValue(1);

	scene()->addItem(outrect_top);
	scene()->addItem(outrect_bot);
	scene()->addItem(outrect_left);
	scene()->addItem(outrect_right);
}

void CollimatorHorizontalSectionView::setCollimatorSize(const v3& coll_size)
{
	size = coll_size;
}

void CollimatorHorizontalSectionView::setParameters(double _diameter, double _septa, int _direction)
{
	diameter = _diameter;
	septa = _septa;
	direction = _direction;
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

	base_rect->setRect(size.x * getScale() * -0.5, size.y * getScale() * -0.5, size.x * getScale(), size.y * getScale());
	base_rect->setPos(realToPixel(0, 0));
}

inline int positive_modulo(int i, int n) {
	return (i % n + n) % n;
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

		if (direction == 0)
			build_horizontal();
		else
			build_vertical();

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
}

void CollimatorHorizontalSectionView::build_horizontal()
{
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
			scene()->addItem(hex);
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
			scene()->addItem(hex);
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
			scene()->addItem(hex);
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
			scene()->addItem(hex);
			hex_list.push_back(hex);
		}
		ypos = delY * (--j);
	}
}

void CollimatorHorizontalSectionView::build_vertical()
{
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
			scene()->addItem(hex);
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
			scene()->addItem(hex);
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
			scene()->addItem(hex);
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
			scene()->addItem(hex);
			hex_list.push_back(hex);
		}
		xpos = delX * (--i);
	}
}

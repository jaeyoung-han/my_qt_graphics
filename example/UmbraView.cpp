#include <QtMath>
#include <QGraphicsPolygonItem>

#include "qUtil.h"
#include "UmbraView.h"

using namespace LCR;
using namespace MQGAPI;

UmbraView::UmbraView(QWidget *parent)
	: GraphicsView(parent)
{
	setScale(30);
	setAxisVisible(false);
	initialize();
	//initialize2();
}

void UmbraView::initialize()
{
	const QColor rcolor(255, 0, 0);
	const QColor bcolor(0, 0, 255);
	const QColor gcolor(200, 200, 200, 200);
	const QColor dgcolor(100, 100, 100, 200);
	QPen pen;
	QBrush brush;

	collimator_polygon = new QGraphicsPolygonItem();
	top_hole = new QGraphicsLineItem();
	bottom_hole = new QGraphicsLineItem();
	detection_line = new QGraphicsLineItem();

	pen.setColor(Qt::black);
	detection_line->setPen(pen);

	pen.setColor(rcolor);

	umbra_line_l = new QGraphicsLineItem();
	umbra_line_l->setPen(pen);
	umbra_line_r = new QGraphicsLineItem();
	umbra_line_r->setPen(pen);

	pen.setColor(bcolor);
	penumbra_line_l = new QGraphicsLineItem();
	penumbra_line_l->setPen(pen);
	penumbra_line_r = new QGraphicsLineItem();
	penumbra_line_r->setPen(pen);

	pen.setColor(dgcolor);
	brush.setColor(dgcolor);
	brush.setStyle(Qt::SolidPattern);
	umbra_circle = new QGraphicsEllipseItem();
	umbra_circle->setPen(pen);
	umbra_circle->setBrush(brush);

	pen.setColor(gcolor);
	brush.setColor(gcolor);
	brush.setStyle(Qt::SolidPattern);
	penumbra_circle = new QGraphicsEllipseItem();
	penumbra_circle->setPen(pen);
	penumbra_circle->setBrush(brush);

	pen.setColor(bcolor);
	pen.setStyle(Qt::DotLine);
	middle_circle = new QGraphicsEllipseItem();
	middle_circle->setPen(pen);

	scene()->addItem(top_hole);
	scene()->addItem(bottom_hole);
	scene()->addItem(detection_line);
	scene()->addItem(penumbra_circle);
	scene()->addItem(middle_circle);
	scene()->addItem(umbra_circle);

	scene()->addItem(penumbra_line_l);
	scene()->addItem(penumbra_line_r);

	scene()->addItem(umbra_line_l);
	scene()->addItem(umbra_line_r);
}

void UmbraView::initialize2()
{
	QPen pen(Qt::darkGray, Qt::SolidPattern);
	QBrush brush(Qt::white, Qt::SolidPattern);

	setBackgroundColor(Qt::lightGray);

	block1 = new QGraphicsPolygonItem();
	block1->setPen(pen);
	block1->setBrush(brush);
	block2 = new QGraphicsPolygonItem();
	block2->setPen(pen);
	block2->setBrush(brush);
	block3 = new QGraphicsPolygonItem();
	block3->setPen(pen);
	block3->setBrush(brush);
	block4 = new QGraphicsPolygonItem();
	block4->setPen(pen);
	block4->setBrush(brush);

	scene()->addItem(block1);
	scene()->addItem(block2);
	scene()->addItem(block3);
	scene()->addItem(block4);
}

UmbraView::~UmbraView()
{
}

void UmbraView::setData(const Collimator& newData)
{
	data = newData;
	update();
}


void UmbraView::update()
{
	drawVerticalUmbra();
	//drawVerticalSection();
}

void UmbraView::drawVerticalUmbra()
{
	QPointF tl(data.diameter[0] * -0.5, data.size.z);
	QPointF tr(data.diameter[0] * 0.5, data.size.z);
	QPointF bl(data.diameter[1] * -0.5, 0);
	QPointF br(data.diameter[1] * 0.5, 0);

	QRectF rect;
	QLineF line;
	qreal x;


	// Top, bottom hole
	line.setPoints(realToPixel(tl), realToPixel(tr));
	top_hole->setLine(line);
	line.setPoints(realToPixel(bl), realToPixel(br));
	bottom_hole->setLine(line);

	// Center line


	// Umbra
	x = getX(data.focus_distance, tl, bl);
	QPointF ul(x, data.focus_distance);
	x = getX(data.focus_distance, tr, br);
	QPointF ur(x, data.focus_distance);

	x = getX(data.focus_distance, tl, br);
	QPointF pl(x, data.focus_distance);
	x = getX(data.focus_distance, tr, bl);
	QPointF pr(x, data.focus_distance);

	line.setPoints(realToPixel(pl), realToPixel(pr));
	detection_line->setLine(line);

	x = qAbs(pl.x() - pr.x()) * 0.5;
	rect.setBottomLeft(realToPixel(-x, data.focus_distance - x));
	rect.setTopRight(realToPixel(x, data.focus_distance + x));
	penumbra_circle->setRect(rect);

	x = qAbs(ul.x() - ur.x()) * 0.5;
	rect.setBottomLeft(realToPixel(-x, data.focus_distance - x));
	rect.setTopRight(realToPixel(x, data.focus_distance + x));
	umbra_circle->setRect(rect);

	x = (qAbs(ul.x() - ur.x()) * 0.5 + qAbs(pl.x() - pr.x()) * 0.5) * 0.5;
	rect.setBottomLeft(realToPixel(-x, data.focus_distance - x));
	rect.setTopRight(realToPixel(x, data.focus_distance + x));
	middle_circle->setRect(rect);


	line.setPoints(realToPixel(br), realToPixel(pl));
	penumbra_line_l->setLine(line);
	line.setPoints(realToPixel(bl), realToPixel(pr));
	penumbra_line_r->setLine(line);

	line.setPoints(realToPixel(bl), realToPixel(ul));
	umbra_line_l->setLine(line);
	line.setPoints(realToPixel(br), realToPixel(ur));
	umbra_line_r->setLine(line);
}

QPolygonF UmbraView::buildPolygon(const QPointF& top_center, qreal top_diameter, const QPointF& bot_center, qreal bot_diameter)
{
	// block center
	QPointF tl(top_center.x() + top_diameter * -0.5, top_center.y());
	QPointF tr(top_center.x() + top_diameter *  0.5, top_center.y());
	QPointF bl(bot_center.x() + bot_diameter * -0.5, bot_center.y());
	QPointF br(bot_center.x() + bot_diameter *  0.5, bot_center.y());

	QPolygonF polygon;
	polygon.push_back(realToPixel(tl));
	polygon.push_back(realToPixel(tr));
	polygon.push_back(realToPixel(br));
	polygon.push_back(realToPixel(bl));

	return polygon;
}

void UmbraView::drawVerticalSection()
{
	// block center
	QPointF t_center(0, data.size.z);
	QPointF b_center(0, 0);

	QPolygonF polygon = buildPolygon(t_center, data.diameter[0], b_center, data.diameter[1]);

	block1->setPolygon(polygon);

	// block right
	t_center.setX(data.diameter[0] + data.septa[0]);
	b_center.setX(data.diameter[1] + data.septa[1]);

	polygon = buildPolygon(t_center, data.diameter[0], b_center, data.diameter[1]);

	block2->setPolygon(polygon);

	// block left
	t_center.setX((data.diameter[0] + data.septa[0]) * -1.0);
	b_center.setX((data.diameter[1] + data.septa[1]) * -1.0);

	polygon = buildPolygon(t_center, data.diameter[0], b_center, data.diameter[1]);

	block3->setPolygon(polygon);
}

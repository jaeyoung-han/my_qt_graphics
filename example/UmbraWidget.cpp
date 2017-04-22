#include <QtMath>
#include <QResizeEvent>
#include <QGraphicsPolygonItem>

#include "qUtil.h"
#include "UmbraWidget.h"

using namespace LCR;
using namespace MQGAPI;

UmbraWidget::UmbraWidget()
	: diameter_umbra(10)
	, diameter_penumbra(20)
{
	initialize();
}

void UmbraWidget::initialize()
{
	setScene(new QGraphicsScene());

	const QColor rcolor(255, 0, 0);
	const QColor bcolor(0, 0, 255);
	const QColor gcolor(80, 80, 80);
	QPen pen;
	QBrush brush;

	umbra_circle = new QGraphicsEllipseItem();

	pen.setColor(gcolor);
	brush.setColor(gcolor);
	brush.setStyle(Qt::SolidPattern);
	penumbra_circle = new QGraphicsEllipseItem();
	penumbra_circle->setPen(pen);
	penumbra_circle->setBrush(brush);

	pen.setColor(Qt::cyan);
	pen.setStyle(Qt::DotLine);
	pen.setWidth(2);
	middle_circle = new QGraphicsEllipseItem();
	middle_circle->setPen(pen);

	brush.setColor(Qt::black);
	scene()->addItem(penumbra_circle);
	scene()->addItem(middle_circle);
	scene()->addItem(umbra_circle);
	scene()->setBackgroundBrush(brush);
}

void UmbraWidget::update(qreal dia_umbra, qreal dia_penumbra)
{
	diameter_umbra = dia_umbra;
	diameter_penumbra = dia_penumbra;

	this->update();
}

void UmbraWidget::resizeEvent(QResizeEvent* event)
{
	QSize s = event->size();
	fitInView(0, 0, s.width(), s.height());//, Qt::KeepAspectRatio);
	update();
	QGraphicsView::resizeEvent(event);
}

void UmbraWidget::update()
{
	qreal ratio = qAbs(diameter_umbra) / qAbs(diameter_penumbra);
	qreal length = 180;
	qreal dia_pen = length - 10;
	qreal dia_um = dia_pen * ratio;
	qreal dia_mid = (dia_pen + dia_um) / 2;

	
	QPointF tl((length - dia_pen) / 2, (length - dia_pen) / 2);
	QPointF br((length + dia_pen) / 2, (length + dia_pen) / 2);

	QRectF rect;
	rect.setTopLeft(tl);
	rect.setBottomRight(br);
	penumbra_circle->setRect(rect);


	const QColor dgcolor(255, 255, 255);
	const QColor dgcolor1(160, 160, 160);

	QPen pen;
	QBrush brush;

	if (diameter_umbra < 0) {
		pen.setColor(dgcolor1);
		brush.setColor(dgcolor1);
		brush.setStyle(Qt::SolidPattern);
	}
	else {
		pen.setColor(dgcolor);
		brush.setColor(dgcolor);
		brush.setStyle(Qt::SolidPattern);
	}

	umbra_circle->setPen(pen);
	umbra_circle->setBrush(brush);

	tl.setX((length - dia_um) / 2);
	tl.setY((length - dia_um) / 2);
	br.setX((length + dia_um) / 2);
	br.setY((length + dia_um) / 2);
	rect.setTopLeft(tl);
	rect.setBottomRight(br);
	umbra_circle->setRect(rect);

	tl.setX((length - dia_mid) / 2);
	tl.setY((length - dia_mid) / 2);
	br.setX((length + dia_mid) / 2);
	br.setY((length + dia_mid) / 2);
	rect.setTopLeft(tl);
	rect.setBottomRight(br);
	middle_circle->setRect(rect);
}

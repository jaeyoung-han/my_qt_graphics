#include <QtMath>
#include <QGraphicsPolygonItem>
#include "UmbraView.h"

using namespace LCR;
using namespace MQGAPI;

UmbraView::UmbraView(QWidget *parent)
  : GraphicsView(parent)
{
	collimator_polygon = new QGraphicsPolygonItem();
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
}

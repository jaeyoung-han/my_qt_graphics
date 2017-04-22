#include <QtMath>

#include "CollimatorHorizontalSectionView.h"
#include "graphicshexagonitem.h"

using namespace LCR;
using namespace MQGAPI;

CollimatorHorizontalSectionView::CollimatorHorizontalSectionView(double ins_diameter, double _septa, QWidget *parent)
  : GraphicsView(parent)
  , base_item(Q_NULLPTR)
  , hex_group(Q_NULLPTR)
  , diameter(ins_diameter)
  , septa(_septa)
{
	setAxisVisible(false);
}

CollimatorHorizontalSectionView::~CollimatorHorizontalSectionView()
{

}

void CollimatorHorizontalSectionView::setCollimatorSize(const v3& coll_size)
{
  this->size = coll_size;
  updateBase();
}

void CollimatorHorizontalSectionView::setParameters(double diameter, double septa)
{
  this->diameter = diameter;
  this->septa = septa;
}

void CollimatorHorizontalSectionView::updateBase()
{
  if (!base_item) {
    base_item = new QGraphicsRectItem(0, 0, 1, 1);
    scene()->addItem(base_item);
  }
  base_item->setRect(size.x * getScale() * -0.5, size.y * getScale() * -0.5, size.x * getScale(), size.y * getScale());
  base_item->setPos(realToPixel(0, 0));
}

void CollimatorHorizontalSectionView::buildHoles()
{
  if (hex_group) {
    scene()->destroyItemGroup(hex_group);

    for (size_t i = 0; i < hex_list.size(); ++i) {
      scene()->removeItem(hex_list[i]);
    }

	hex_group = Q_NULLPTR;
  }

  if (septa < 0) {
	  hex_list.clear();
	return;
  }

  if (diameter > 0) {
	  QPen pen(Qt::black);
	  QBrush brush;
	  brush.setColor(Qt::red);
	  
	  hex_list.clear();
    qreal circum_diameter = diameter * 2 / sqrt(3);
    qreal scale = getScale();

    qreal delX = sqrt(3) * (diameter + septa) /2;
    qreal delY = (diameter + septa)/2;

	// 1st quadrant
	int j = 0;
	qreal ypos = j * delY;
	while (ypos - diameter / 2 < size.y / 2) {
		qreal imin = qAbs(j % 2) * delX;
		int imax = qCeil((size.x / 2 + circum_diameter / 2 - imin) / (2 * delX));
		for (int i = 0; i < imax; i++) {
			qreal xpos = 2 * delX * i + imin;
			qreal ypos = delY * j;
			GraphicsHexagonItem *hex = new GraphicsHexagonItem(circum_diameter * scale, 0);
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
		qreal imin = qAbs(j % 2) * delX;
		int imax = qCeil((size.x / 2 + circum_diameter / 2 - imin) / (2 * delX));
		for (int i = qAbs((j + 1) % 2); i < imax; i++) {
			qreal xpos = -2 * delX * i - imin;
			qreal ypos = delY * j;
			GraphicsHexagonItem *hex = new GraphicsHexagonItem(circum_diameter * scale, 0);
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
		qreal imin = qAbs(j % 2) * delX;
		int imax = qCeil((size.x / 2 + circum_diameter / 2 - imin) / (2 * delX));
		for (int i = qAbs((j + 1) % 2); i < imax; i++) {
			qreal xpos = -2 * delX * i - imin;
			qreal ypos = delY * j;
			GraphicsHexagonItem *hex = new GraphicsHexagonItem(circum_diameter * scale, 0);
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
		qreal imin = qAbs(j % 2) * delX;
		int imax = qCeil((size.x / 2 + circum_diameter / 2 - imin) / (2 * delX));
		for (int i = 0; i < imax; i++) {
			qreal xpos = 2 * delX * i + imin;
			qreal ypos = delY * j;
			GraphicsHexagonItem *hex = new GraphicsHexagonItem(circum_diameter * scale, 0);
			hex->setPos(realToPixel(xpos, ypos));
			scene()->addItem(hex);
			hex_list.push_back(hex);
		}
		ypos = delY * (--j);
	}

	hex_group = scene()->createItemGroup(hex_list);
  }
  else {
  }
}

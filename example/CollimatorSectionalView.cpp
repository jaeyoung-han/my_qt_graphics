#include <QtMath>

#include "CollimatorSectionalView.h"
#include "graphicshexagonitem.h"

using namespace LCR;
using namespace MQGAPI;

CollimatorSectionalView::CollimatorSectionalView(double ins_diameter, double _septa, QWidget *parent)
  : GraphicsView(parent)
  , base_item(Q_NULLPTR)
  , hex_group(Q_NULLPTR)
  , diameter(ins_diameter)
  , septa(_septa)
{

}

CollimatorSectionalView::~CollimatorSectionalView()
{

}

void CollimatorSectionalView::setCollimatorSize(const v3& coll_size)
{
  this->size = coll_size;
  updateBase();
}

void CollimatorSectionalView::setParameters(double diameter, double septa)
{
  this->diameter = diameter;
  this->septa = septa;
}

void CollimatorSectionalView::updateBase()
{
  if (!base_item) {
    base_item = new QGraphicsRectItem(0, 0, 1, 1);
    scene()->addItem(base_item);
  }
  base_item->setRect(size.x * getScale() * -0.5, size.y * getScale() * -0.5, size.x * getScale(), size.y * getScale());
  base_item->setPos(realToPixel(0, 0));
}

void CollimatorSectionalView::buildHoles()
{
  if (hex_group) {
    scene()->destroyItemGroup(hex_group);

    for (size_t i = 0; i < hex_list.size(); ++i) {
      scene()->removeItem(hex_list[i]);
    }

	hex_group = Q_NULLPTR;
  }

  if (diameter > 0) {
    hex_list.clear();
    qreal circum_diameter = diameter * 2 / sqrt(3);
    qreal scale = getScale();

    qreal delX = sqrt(3) * (diameter + septa) / 2;
    qreal delY = (diameter + septa) / 2;

    int minX = size.x / delX / -2;
    int maxX = size.x / delX / 2 + 1;
    int minY = size.y / delY / -2 - 1;
    int maxY = size.y / delY / 2 + 2;

    for (int j = minY; j < maxY; ++j) {
      int i = minX + qAbs(j%2);
      for (; i < maxX; i += 2) {
        qreal xpos = delX * i;
        qreal ypos = delY * j;
        GraphicsHexagonItem *hex = new GraphicsHexagonItem(circum_diameter * scale, 0);
        hex->setPos(realToPixel(xpos, ypos));
        scene()->addItem(hex);
        hex_list.push_back(hex);
      }
    }
    // for (int i = 0; i < 6; ++i)
    // {
    //   for (int j = -4; j < 4; ++j)
    //   {
    //     qreal xpos = sqrt(3) * (diameter + septa) * (i + abs(j%2) * 0.5);
    //     qreal ypos = (diameter + septa) * j * 0.5;
    //     GraphicsHexagonItem *hex = new GraphicsHexagonItem(circum_diameter * scale, 0);
    //     hex->setPos(realToPixel(xpos, ypos));
    //     scene()->addItem(hex);
    //     hex_list.push_back(hex);
    //   }
    // }

    hex_group = scene()->createItemGroup(hex_list);
  }
  else {
  }
}

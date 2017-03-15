#include "CollimatorSectionalView.h"
#include "graphicshexagonitem.h"

using namespace LCR;
using namespace MQGAPI;

CollimatorSectionalView::CollimatorSectionalView(qreal _diameter, qreal _septa, QWidget *parent)
  : GraphicsView(parent)
  , diameter(_diameter)
  , septa(_septa)
{

}

CollimatorSectionalView::~CollimatorSectionalView()
{

}

void CollimatorSectionalView::setHole(qreal diameter, qreal septa)
{
  this->diameter = diameter;
  this->septa = septa;

  buildHoles();
}

void CollimatorSectionalView::buildHoles()
{
    // qreal diameter = 50;
    // qreal thickness = 2;
    // qreal ins_diameter = diameter * sqrt(3) * 0.5;
    // for (int i = 0; i < 6; ++i)
    // {
    //   for (int j = -4; j < 4; ++j)
    //   {
    //     qreal xpos = sqrt(3) * (ins_diameter + thickness) * (i + abs(j%2) * 0.5);
    //     qreal ypos = (ins_diameter + thickness) * j * 0.5;
    //     GraphicsHexagonItem *hex = new GraphicsHexagonItem(ins_diameter, 0);
    //     hex->setPos(xpos, ypos);
    //     _scene->addItem(hex);
    //
    //   }
    // }
}

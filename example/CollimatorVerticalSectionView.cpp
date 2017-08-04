#include <QtMath>

#include "CollimatorVerticalSectionView.h"
#include "graphicshexagonitem.h"

using namespace LCR;
using namespace MQGAPI;

CollimatorVerticalSectionView::CollimatorVerticalSectionView(double ins_diameter, double _septa, QWidget *parent)
  : GraphicsView(parent)
  , diameter(ins_diameter)
  , septa(_septa)
{
	setAxisVisible(false);
}

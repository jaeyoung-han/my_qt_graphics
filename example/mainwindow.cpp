#include <QSplitter>
#include <QLayout>
#include "mainwindow.h"
#include "graphicsarrowitem.h"

using namespace MQGAPI;

MainWindow::MainWindow()
{
  gview_upper = new GraphicsView();
  gview_upper->setOrigin(200, 200);
  gview_lower = new GraphicsView();

  QSplitter* spl_upper = new QSplitter();

  spl_upper->addWidget(gview_upper);
  spl_upper->addWidget(gview_lower);
  spl_upper->setOrientation(Qt::Vertical);

  setCentralWidget(spl_upper);
}

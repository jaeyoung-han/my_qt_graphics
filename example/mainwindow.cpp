#include <QtWidgets>
#include "mainwindow.h"

#include "graphicsarrowitem.h"
#include "DockCollimator.h"

using namespace MQGAPI;
using namespace LCR;

MainWindow::MainWindow()
{
  gview_top = new CollimatorSectionalView();
  gview_top->setOrigin(200, 200);
  gview_top->setScale(10);

  gview_section = new CollimatorSectionalView();
  gview_section->setOrigin(200, 200);
  gview_section->setScale(10);

  gview_bottom = new CollimatorSectionalView();
  gview_bottom->setOrigin(200, 200);
  gview_bottom->setScale(10);

  QSplitter* splitter = new QSplitter();

  splitter->addWidget(gview_top);
  splitter->addWidget(gview_section);
  splitter->addWidget(gview_bottom);
  splitter->setOrientation(Qt::Vertical);

  setCentralWidget(splitter);

  createActions();
  createMenus();
  createStatusBar();
  createDocks();

  sizeUpdated();
}

void MainWindow::createActions()
{
  act_quit = new QAction(tr("&Quit"), this);
  act_quit->setShortcuts(QKeySequence::Quit);
  act_quit->setStatusTip(tr("Quit the application"));
  connect(act_quit, SIGNAL(triggered()), this, SLOT(close()));

  act_about = new QAction(tr("&About"), this);
  act_about->setStatusTip(tr("Show the application's About box"));
  connect(act_about, SIGNAL(triggered()), this, SLOT(about()));
}

void MainWindow::createMenus()
{
  menu_file = menuBar()->addMenu(tr("&File"));
  menu_file->addAction(act_quit);

  menu_view = menuBar()->addMenu(tr("&View"));

  menu_help = menuBar()->addMenu(tr("&Help"));
  menu_help->addAction(act_about);
}

void MainWindow::createStatusBar()
{
  statusBar()->showMessage(tr("Ready"));
}

void MainWindow::createDocks()
{
  dockCollimator = new DockCollimator(tr("Collimator"), this);
  dockCollimator->setAllowedAreas(Qt::LeftDockWidgetArea);
  addDockWidget(Qt::LeftDockWidgetArea, dockCollimator);
  menu_view->addAction(dockCollimator->toggleViewAction());

  connect(dockCollimator, SIGNAL(updateSize()), this, SLOT(sizeUpdated()));
  connect(dockCollimator, SIGNAL(updateParameters()), this, SLOT(parameterUpdated()));
  connect(dockCollimator, SIGNAL(updateSection()), this, SLOT(sectionUpdated()));
}

void MainWindow::sizeUpdated()
{
  Collimator data = dockCollimator->getData();
  gview_bottom->setCollimatorSize(data.size);
//  gview_bottom->buildHoles();

  double ratio =(data.focus_distance - data.size.z)/data.focus_distance;
  v3 top_size;
  top_size.x = data.size.x * ratio;
  top_size.y = data.size.y * ratio;
  gview_top->setCollimatorSize(top_size);
  // gview_top->buildHoles();

  ratio =(data.focus_distance - data.section_height)/data.focus_distance;
  v3 section_size;
  section_size.x = data.size.x * ratio;
  section_size.y = data.size.y * ratio;
  gview_section->setCollimatorSize(section_size);
  // gview_section->buildHoles();

  parameterUpdated();
}

void MainWindow::parameterUpdated()
{
  Collimator data = dockCollimator->getData();

  gview_top->setParameters(data.diameter[0], data.septa[0]);
  gview_top->buildHoles();

  if (data.direction == Converging) {
    // Calculate entrance plane
    double ratio = (data.focus_distance - data.size.z)/data.focus_distance;
    data.diameter[1] = data.diameter[0] / ratio;
    data.septa[1] = data.septa[0] / ratio;
    gview_bottom->setParameters(data.diameter[1], data.septa[1]);
    gview_bottom->buildHoles();

    // Calculate sectional plane
    ratio =(data.focus_distance - (data.size.z - data.section_height))/data.focus_distance;
    gview_section->setParameters(data.diameter[0] / ratio, data.septa[0] / ratio);
    gview_section->buildHoles();

    data.focus_width = 0;
  }
  // Diverging hole
  else {
    // 1. determine diameters
    double section_diameter = data.diameter[1]
      + (data.diameter[0] - data.diameter[1]) / data.size.z * data.section_height;

    // 2. determine delY (distance btw the centers of hexagons)
    if (data.diameter[0] > data.diameter[1]) {
      double top_delY = data.diameter[0] + data.septa[0];
      double bottom_delY = top_delY * data.focus_distance / (data.focus_distance - data.size.z);
      double section_delY = top_delY * (data.focus_distance - data.section_height)/(data.focus_distance - data.size.z);
      data.septa[1] = bottom_delY - data.diameter[1];
      double section_septa = section_delY - section_diameter;

      gview_bottom->setParameters(data.diameter[1], data.septa[1]);
      gview_bottom->buildHoles();

      gview_section->setParameters(section_diameter, section_septa);
      gview_section->buildHoles();
    }

    data.focus_width = data.diameter[1]
      + (data.diameter[0] - data.diameter[1]) / data.size.z * data.focus_distance;
  }

  dockCollimator->update(data);
}

void MainWindow::sectionUpdated()
{
  Collimator data = dockCollimator->getData();
  double ratio =(data.focus_distance - data.section_height)/data.focus_distance;
  v3 section_size;
  section_size.x = data.size.x * ratio;
  section_size.y = data.size.y * ratio;
  gview_section->setCollimatorSize(section_size);

  if (data.direction == Converging) {
    // Calculate sectional plane
    ratio =(data.focus_distance - (data.size.z - data.section_height))/data.focus_distance;
    gview_section->setParameters(data.diameter[0] / ratio, data.septa[0] / ratio);
    gview_section->buildHoles();
  }
  // Diverging hole
  else {
    // 1. determine diameters
    double section_diameter = data.diameter[1]
      + (data.diameter[0] - data.diameter[1]) / data.size.z * data.section_height;

    // 2. determine delY (distance btw the centers of hexagons)
    if (data.diameter[0] > data.diameter[1]) {
      double top_delY = data.diameter[0] + data.septa[0];
      double section_delY = top_delY * (data.focus_distance - data.section_height)/(data.focus_distance - data.size.z);
      double section_septa = section_delY - section_diameter;

      gview_section->setParameters(section_diameter, section_septa);
      gview_section->buildHoles();
    }
  }
}

void MainWindow::about()
{
  QMessageBox::about(this, tr("About Example"),
    tr("Blah blah"));
}

#include <QtWidgets>
#include <QSettings>
#include "mainwindow.h"

#include "graphics_view_zoom.h"
#include "graphicsarrowitem.h"
#include "DockCollimator.h"

using namespace MQGAPI;
using namespace LCR;

MainWindow::MainWindow()
{
  // Horizontal Sectional View
  gview_top = new CollimatorSectionalView();
  gview_top->setOrigin(200, 200);
  gview_top->setScale(10);
  Graphics_view_zoom* zt = new Graphics_view_zoom(gview_top);
  zt->set_modifiers(Qt::NoModifier);

  gview_section = new CollimatorSectionalView();
  gview_section->setOrigin(200, 200);
  gview_section->setScale(10);

  gview_bottom = new CollimatorSectionalView();
  gview_bottom->setOrigin(200, 200);
  gview_bottom->setScale(10);

  // H-Section Splitter
  QSplitter* splitter = new QSplitter();

  splitter->addWidget(gview_top);
  splitter->addWidget(gview_section);
  splitter->addWidget(gview_bottom);
  splitter->setOrientation(Qt::Vertical);

  // Vertical Sectional View
  gview_umbra = new UmbraView();
  gview_umbra->setOrigin(200, 500);
  gview_umbra->setScale(2);
  Graphics_view_zoom* z = new Graphics_view_zoom(gview_umbra);
  z->set_modifiers(Qt::NoModifier);

  // Main Splitter
  QSplitter* main_splitter = new QSplitter();

  main_splitter->addWidget(splitter);
  main_splitter->addWidget(gview_umbra);
  main_splitter->setOrientation(Qt::Horizontal);


  // Set Main widget
  setCentralWidget(main_splitter);

  loadSettings();


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

  dockCollimator->update(collimator);
}

void MainWindow::loadSettings()
{
	QSettings settings;
	collimator.diameter[0] = settings.value("DIAMETER_PATIENT_SIDE", 2.0).toDouble();
	collimator.diameter[1] = settings.value("DIAMETER_X-RAY_SIDE", 2.5).toDouble();
	collimator.septa[0] = settings.value("SEPTA_PATIENT_SIDE", 0.3).toDouble();
	collimator.direction = settings.value("HEXAGON_DIRECTION", 0).toInt();

	collimator.size.x = settings.value("COLLIMATOR_LENGTH", 30).toDouble();
	collimator.size.y = settings.value("COLLIMATOR_WIDTH", 30).toDouble();
	collimator.size.z = settings.value("COLLIMATOR_HEIGHT", 100).toDouble();
	collimator.focus_distance = settings.value("FOCAL_LENGTH", 500).toDouble();
}

void MainWindow::saveSettings()
{
	QSettings settings;

	settings.setValue("DIAMETER_PATIENT_SIDE", collimator.diameter[0]);
	settings.setValue("DIAMETER_X-RAY_SIDE", collimator.diameter[1]);
	settings.setValue("SEPTA_PATIENT_SIDE", collimator.septa[0]);
	settings.setValue("HEXAGON_DIRECTION", collimator.direction);

	settings.setValue("COLLIMATOR_LENGTH", collimator.size.x);
	settings.setValue("COLLIMATOR_WIDTH", collimator.size.y);
	settings.setValue("COLLIMATOR_HEIGHT", collimator.size.z);
	settings.setValue("FOCAL_LENGTH", collimator.focus_distance);
}

void MainWindow::sizeUpdated()
{
  collimator = dockCollimator->getData();
  gview_bottom->setCollimatorSize(collimator.size);
//  gview_bottom->buildHoles();

  double ratio =(collimator.focus_distance - collimator.size.z)/ collimator.focus_distance;
  v3 top_size;
  top_size.x = collimator.size.x * ratio;
  top_size.y = collimator.size.y * ratio;
  gview_top->setCollimatorSize(top_size);
  // gview_top->buildHoles();

  ratio =(collimator.focus_distance - collimator.section_height)/ collimator.focus_distance;
  v3 section_size;
  section_size.x = collimator.size.x * ratio;
  section_size.y = collimator.size.y * ratio;
  gview_section->setCollimatorSize(section_size);
  // gview_section->buildHoles();

  parameterUpdated();
}

void MainWindow::parameterUpdated()
{
  collimator = dockCollimator->getData();

  gview_umbra->setData(collimator);

  gview_top->setParameters(collimator.diameter[0], collimator.septa[0]);
  gview_top->buildHoles();

  if (collimator.direction == Converging) {
    // Calculate entrance plane
    double ratio = (collimator.focus_distance - collimator.size.z)/ collimator.focus_distance;
	collimator.diameter[1] = collimator.diameter[0] / ratio;
	collimator.septa[1] = collimator.septa[0] / ratio;
    gview_bottom->setParameters(collimator.diameter[1], collimator.septa[1]);
    gview_bottom->buildHoles();

    // Calculate sectional plane
    ratio =(collimator.focus_distance - (collimator.size.z - collimator.section_height))/ collimator.focus_distance;
    gview_section->setParameters(collimator.diameter[0] / ratio, collimator.septa[0] / ratio);
    gview_section->buildHoles();

	collimator.focus_width = 0;
  }
  // Diverging hole
  else {
    // 1. determine diameters
    double section_diameter = collimator.diameter[1]
      + (collimator.diameter[0] - collimator.diameter[1]) / collimator.size.z * collimator.section_height;

    // 2. determine delY (distance btw the centers of hexagons)
    if (collimator.diameter[0] > collimator.diameter[1]) {
      double top_delY = collimator.diameter[0] + collimator.septa[0];
      double bottom_delY = top_delY * collimator.focus_distance / (collimator.focus_distance - collimator.size.z);
      double section_delY = top_delY * (collimator.focus_distance - collimator.section_height)/(collimator.focus_distance - collimator.size.z);
	  collimator.septa[1] = bottom_delY - collimator.diameter[1];
      double section_septa = section_delY - section_diameter;

      gview_bottom->setParameters(collimator.diameter[1], collimator.septa[1]);
      gview_bottom->buildHoles();

      gview_section->setParameters(section_diameter, section_septa);
      gview_section->buildHoles();
    }

	collimator.focus_width = collimator.diameter[1]
      + (collimator.diameter[0] - collimator.diameter[1]) / collimator.size.z * collimator.focus_distance;
  }

  dockCollimator->update(collimator);
  saveSettings();
}

void MainWindow::sectionUpdated()
{
	collimator = dockCollimator->getData();
  double ratio =(collimator.focus_distance - collimator.section_height)/ collimator.focus_distance;
  v3 section_size;
  section_size.x = collimator.size.x * ratio;
  section_size.y = collimator.size.y * ratio;
  gview_section->setCollimatorSize(section_size);

  if (collimator.direction == Converging) {
    // Calculate sectional plane
    ratio =(collimator.focus_distance - (collimator.size.z - collimator.section_height))/ collimator.focus_distance;
    gview_section->setParameters(collimator.diameter[0] / ratio, collimator.septa[0] / ratio);
    gview_section->buildHoles();
  }
  // Diverging hole
  else {
    // 1. determine diameters
    double section_diameter = collimator.diameter[1]
      + (collimator.diameter[0] - collimator.diameter[1]) / collimator.size.z * collimator.section_height;

    // 2. determine delY (distance btw the centers of hexagons)
    if (collimator.diameter[0] > collimator.diameter[1]) {
      double top_delY = collimator.diameter[0] + collimator.septa[0];
      double section_delY = top_delY * (collimator.focus_distance - collimator.section_height)/(collimator.focus_distance - collimator.size.z);
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

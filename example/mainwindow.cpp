#include <QtWidgets>
#include <QSettings>

#include "qUtil.h"
#include "mainwindow.h"

#include "graphics_view_zoom.h"
#include "graphicsarrowitem.h"
#include "DockCollimator.h"

using namespace MQGAPI;
using namespace LCR;

MainWindow::MainWindow()
{
	// Horizontal Sectional View
	gview_top = new CollimatorHorizontalSectionView();
	gview_top->setOrigin(200, 200);
	gview_top->setScale(10);

	gview_section = new CollimatorHorizontalSectionView();
	gview_section->setOrigin(200, 200);
	gview_section->setScale(10);

	gview_bottom = new CollimatorHorizontalSectionView();
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

	// Main Splitter
	QSplitter* main_splitter = new QSplitter();

	main_splitter->addWidget(splitter);
	main_splitter->addWidget(gview_umbra);
	main_splitter->setOrientation(Qt::Horizontal);


	// Set Main widget
	setCentralWidget(main_splitter);

	loadSettings();
	collimator.section_height = 0;

	createActions();
	createMenus();
	createStatusBar();
	createDocks();
	createConnections();

	QSettings settings;
	restoreGeometry(settings.value("geometry").toByteArray());
	dockCollimator->restoreGeometry(settings.value("dockCollimator/geometry").toByteArray());
	restoreState(settings.value("state").toByteArray());

	parameterUpdated();
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
	dockCollimator = new DockCollimator(tr("Collimator"), collimator, this);
	dockCollimator->setAllowedAreas(Qt::LeftDockWidgetArea);
	addDockWidget(Qt::LeftDockWidgetArea, dockCollimator);
	menu_view->addAction(dockCollimator->toggleViewAction());
}

void MainWindow::createConnections()
{
	connect(dockCollimator, SIGNAL(updateParameters()), this, SLOT(parameterUpdated()));
	connect(dockCollimator, SIGNAL(updateSection()), this, SLOT(sectionUpdated()));
}

void MainWindow::closeEvent(QCloseEvent* event)
{
	saveSettings();

	QSettings settings;
	settings.setValue("geometry", saveGeometry());
	settings.setValue("dockCollimator/geometry", dockCollimator->saveGeometry());
	settings.setValue("state", saveState());

	QMainWindow::closeEvent(event);
}

void MainWindow::loadSettings()
{
	QSettings settings;
	collimator.diameter[0] = settings.value("DIAMETER_PATIENT_SIDE", 2.0).toDouble();
	collimator.diameter[1] = settings.value("DIAMETER_X-RAY_SIDE", 2.5).toDouble();
	collimator.septa[0] = settings.value("SEPTA_PATIENT_SIDE", 0.3).toDouble();

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

	settings.setValue("COLLIMATOR_LENGTH", collimator.size.x);
	settings.setValue("COLLIMATOR_WIDTH", collimator.size.y);
	settings.setValue("COLLIMATOR_HEIGHT", collimator.size.z);
	settings.setValue("FOCAL_LENGTH", collimator.focus_distance);
}

void MainWindow::sizeUpdated()
{
}

void MainWindow::parameterUpdated()
{
	collimator = dockCollimator->getData();

	gview_bottom->setCollimatorSize(collimator.size);
	//  gview_bottom->buildHoles();

	double ratio = (collimator.focus_distance - collimator.size.z) / collimator.focus_distance;
	v3 top_size;
	top_size.x = collimator.size.x * ratio;
	top_size.y = collimator.size.y * ratio;
	gview_top->setCollimatorSize(top_size);
	// gview_top->buildHoles();

	ratio = (collimator.focus_distance - collimator.section_height) / collimator.focus_distance;
	v3 section_size;
	section_size.x = collimator.size.x * ratio;
	section_size.y = collimator.size.y * ratio;
	gview_section->setCollimatorSize(section_size);

	gview_umbra->setData(collimator);

	gview_top->setParameters(collimator.diameter[0], collimator.septa[0]);
	gview_top->buildHoles();

	// 1. determine diameters
	double section_diameter = collimator.diameter[1]
	+ (collimator.diameter[0] - collimator.diameter[1]) / collimator.size.z * collimator.section_height;

	// 2. determine delY (distance btw the centers of hexagons)
	double top_delY = collimator.diameter[0] + collimator.septa[0];
	double bottom_delY = top_delY * collimator.focus_distance / (collimator.focus_distance - collimator.size.z);
	double section_delY = top_delY * (collimator.focus_distance - collimator.section_height)/(collimator.focus_distance - collimator.size.z);
	collimator.septa[1] = bottom_delY - collimator.diameter[1];
	double section_septa = section_delY - section_diameter;

	gview_bottom->setParameters(collimator.diameter[1], collimator.septa[1]);
	gview_bottom->buildHoles();

	gview_section->setParameters(section_diameter, section_septa);
	gview_section->buildHoles();

	collimator.sec_diameter = section_diameter;
	collimator.sec_thickness = section_septa;

	updateUmbra();

	dockCollimator->update(collimator);
}

void MainWindow::sectionUpdated()
{
	collimator = dockCollimator->getData();
	double ratio =(collimator.focus_distance - collimator.section_height)/ collimator.focus_distance;
	v3 section_size;
	section_size.x = collimator.size.x * ratio;
	section_size.y = collimator.size.y * ratio;
	gview_section->setCollimatorSize(section_size);

	// 1. determine diameters
	double section_diameter = collimator.diameter[1]
	+ (collimator.diameter[0] - collimator.diameter[1]) / collimator.size.z * collimator.section_height;

	// 2. determine delY (distance btw the centers of hexagons)
	double top_delY = collimator.diameter[0] + collimator.septa[0];
	double section_delY = top_delY * (collimator.focus_distance - collimator.section_height)/(collimator.focus_distance - collimator.size.z);
	double section_septa = section_delY - section_diameter;

	gview_section->setParameters(section_diameter, section_septa);
	gview_section->buildHoles();

	collimator.sec_diameter = section_diameter;
	collimator.sec_thickness = section_septa;

	dockCollimator->update(collimator);
}

void MainWindow::updateUmbra()
{
	QPointF tl(collimator.diameter[0] * -0.5, collimator.size.z);
	QPointF tr(collimator.diameter[0] *  0.5, collimator.size.z);
	QPointF bl(collimator.diameter[1] * -0.5, 0);
	QPointF br(collimator.diameter[1] *  0.5, 0);

	// Umbra
	qreal x = getX(collimator.focus_distance, tl, bl);
	QPointF ul(x, collimator.focus_distance);
	x = getX(collimator.focus_distance, tr, br);
	QPointF ur(x, collimator.focus_distance);

	x = getX(collimator.focus_distance, tl, br);
	QPointF pl(x, collimator.focus_distance);
	x = getX(collimator.focus_distance, tr, bl);
	QPointF pr(x, collimator.focus_distance);

	collimator.umbra_width = ur.x() - ul.x();
	collimator.penumbra_width = pr.x() - pl.x();
}

void MainWindow::about()
{
	QMessageBox::about(this, 
		tr("About Example"),
		tr("Blah blah"));
}

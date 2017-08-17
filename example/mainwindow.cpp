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
	gview_bottom->drawCircle(5);

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

    changeShape(collimator.shape);
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

    connect(gview_top, SIGNAL(pointInCheck(QPointF, bool)), this, SLOT(updatePointInCheck(QPointF, bool)));
    connect(gview_section, SIGNAL(pointInCheck(QPointF, bool)), this, SLOT(updatePointInCheck(QPointF, bool)));
    connect(gview_bottom, SIGNAL(pointInCheck(QPointF, bool)), this, SLOT(updatePointInCheck(QPointF, bool)));
}

void MainWindow::createActions()
{
	act_save = new QAction(tr("&Save"), this);
	act_save->setShortcuts(QKeySequence::Save);
	act_save->setStatusTip(tr("Save"));
	connect(act_save, SIGNAL(triggered()), this, SLOT(save()));


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
	menu_file->addAction(act_save);
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

    collimator.shape = settings.value("HOLE_SHAPE", 0).toInt();

    collimator.direction = settings.value("HEXAGON_HORIZONTAL", 0).toInt();
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

    settings.setValue("HOLE_SHAPE", collimator.shape);

	settings.setValue("HEXAGON_HORIZONTAL", collimator.direction);
	settings.setValue("DIAMETER_PATIENT_SIDE", collimator.diameter[0]);
	settings.setValue("DIAMETER_X-RAY_SIDE", collimator.diameter[1]);
	settings.setValue("SEPTA_PATIENT_SIDE", collimator.septa[0]);

	settings.setValue("COLLIMATOR_LENGTH", collimator.size.x);
	settings.setValue("COLLIMATOR_WIDTH", collimator.size.y);
	settings.setValue("COLLIMATOR_HEIGHT", collimator.size.z);
	settings.setValue("FOCAL_LENGTH", collimator.focus_distance);
}

void MainWindow::changeShape(int shape)
{
    gview_top->changeShape(shape);
    gview_section->changeShape(shape);
    gview_bottom->changeShape(shape);
}

void MainWindow::sizeUpdated()
{
}

void MainWindow::parameterUpdated()
{
	collimator = dockCollimator->getData();

    changeShape(collimator.shape);

    double sec_height = collimator.section_height;
    collimator.section_height = 0;
	gview_bottom->setCollimatorSize(collimator, 1);

	double ratio = (collimator.focus_distance - collimator.size.z) / collimator.focus_distance;
    collimator.section_height = collimator.size.z;
    gview_top->setCollimatorSize(collimator, ratio);

	ratio = (collimator.focus_distance - collimator.section_height) / collimator.focus_distance;
    collimator.section_height = sec_height;
    gview_section->setCollimatorSize(collimator, ratio);

	gview_umbra->setData(collimator);

	gview_top->setParameters(collimator.diameter[0], collimator.septa[0], collimator.direction);
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

	gview_bottom->setParameters(collimator.diameter[1], collimator.septa[1], collimator.direction);
	gview_bottom->buildHoles();

	gview_section->setParameters(section_diameter, section_septa, collimator.direction);
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
	gview_section->setCollimatorSize(collimator, ratio);

	// 1. determine diameters
	double section_diameter = collimator.diameter[1]
	+ (collimator.diameter[0] - collimator.diameter[1]) / collimator.size.z * collimator.section_height;

	// 2. determine delY (distance btw the centers of hexagons)
	double top_delY = collimator.diameter[0] + collimator.septa[0];
	double section_delY = top_delY * (collimator.focus_distance - collimator.section_height)/(collimator.focus_distance - collimator.size.z);
	double section_septa = section_delY - section_diameter;

	gview_section->setParameters(section_diameter, section_septa, collimator.direction);
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

void MainWindow::updatePointInCheck(QPointF pos, bool res)
{
    statusBar()->setStyleSheet(res ? "background-color : #FF0000;" : "background-color : none;");
    statusBar()->showMessage(tr("(%1, %2) %3").arg(QString::number(pos.x(), 'f', 2)).arg(QString::number(pos.y(), 'f', 2)).arg(res));
}

void MainWindow::save()
{
	QSettings setting;

	QString name = QString("%1/D%2-D%3-H%4-F%5")
		.arg(setting.value("last_dir").toString())
		.arg(QString::number(collimator.diameter[0], 'f', 2))
		.arg(QString::number(collimator.diameter[1], 'f', 2))
		.arg(QString::number(collimator.size.z, 'f', 0))
		.arg(QString::number(collimator.focus_distance, 'f', 0))
		;

	QString fileName = QFileDialog::getSaveFileName(this,
		tr("Save Section"), name,
		tr("PNG (*.png)"));

	if (!fileName.isEmpty() && !fileName.isNull()) {

		fileName.replace(".png", "");
		gview_top->save(fileName + tr("-top.png"));
		gview_bottom->save(fileName + tr("-bot.png"));

		QDir dir(fileName);
		setting.setValue("last_dir", dir.absolutePath());
	}
}

void MainWindow::about()
{
	QMessageBox::about(this, 
		tr("About Example"),
		tr("Blah blah"));
}

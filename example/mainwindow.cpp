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
    collimator.loadSettings(settings);
}

void MainWindow::saveSettings()
{
	QSettings settings;
    collimator.saveSettings(settings);
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

	
    double diameters[2];
    double septas[2];

	gview_umbra->setData(collimator);

    diameters[0] = collimator.hole_ex.diameter_long;
    diameters[1] = collimator.hole_ex.diameter_tran;
    septas[0] = collimator.hole_ex.septa_long;
    septas[1] = collimator.hole_ex.septa_tran;

    gview_top->setCollimatorSize(collimator, collimator.hole_ex.z);
    gview_top->setParameters(diameters, septas, collimator.direction);
	gview_top->buildHoles();

    diameters[0] = collimator.hole_en.diameter_long;
    diameters[1] = collimator.hole_en.diameter_tran;
    septas[0] = collimator.hole_en.septa_long;
    septas[1] = collimator.hole_en.septa_tran;

    gview_bottom->setCollimatorSize(collimator, collimator.hole_en.z);
    gview_bottom->setParameters(diameters, septas, collimator.direction);
	gview_bottom->buildHoles();

    diameters[0] = collimator.hole_sec.diameter_long;
    diameters[1] = collimator.hole_sec.diameter_tran;
    septas[0] = collimator.hole_sec.septa_long;
    septas[1] = collimator.hole_sec.septa_tran;

    gview_section->setCollimatorSize(collimator, collimator.hole_sec.z);
    gview_section->setParameters(diameters, septas, collimator.direction);
	gview_section->buildHoles();

	updateUmbra();

	dockCollimator->update(collimator);
}

void MainWindow::sectionUpdated()
{
	collimator = dockCollimator->getData();

    double diameters[2];
    double septas[2];

    diameters[0] = collimator.hole_sec.diameter_long;
    diameters[1] = collimator.hole_sec.diameter_tran;
    septas[0] = collimator.hole_sec.septa_long;
    septas[1] = collimator.hole_sec.septa_tran;

    gview_section->setCollimatorSize(collimator, collimator.hole_sec.z);
    gview_section->setParameters(diameters, septas, collimator.direction);
	gview_section->buildHoles();
}

void MainWindow::updateUmbra()
{

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
		.arg(QString::number(collimator.hole_ex.diameter_long, 'f', 3))
		.arg(QString::number(collimator.hole_en.diameter_long, 'f', 3))
		.arg(QString::number(collimator.size.z, 'f', 0))
		.arg(QString::number(collimator.focus_coll_long, 'f', 0))
		;

	QString fileName = QFileDialog::getSaveFileName(this,
		tr("Save Section"), name,
		tr("PNG (*.png)"));

	if (!fileName.isEmpty() && !fileName.isNull()) {

		fileName.replace(".png", "");
		gview_top->save(fileName + tr("-top.png"));
        gview_section->save(fileName + tr("-sec.png"));
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

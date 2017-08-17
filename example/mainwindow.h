#ifndef __EXAMPLE_MAINWINDOW_H__
#define __EXAMPLE_MAINWINDOW_H__

#include <QMainWindow>
#include "CollimatorHorizontalSectionView.h"
#include "CollimatorVerticalSectionView.h"
#include "UmbraView.h"

using namespace MQGAPI;

class QMenu;
class QAction;
class DockCollimator;

class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
	MainWindow();

private slots:
	void save();
	void about();
	void sizeUpdated();
	void parameterUpdated();
	void sectionUpdated();
	void loadSettings();
	void saveSettings();
    void changeShape(int);
    void updatePointInCheck(QPointF, bool);

protected:
	void createActions();
	void createMenus();
	void createStatusBar();
	void createDocks();
	void createConnections();
	void closeEvent(QCloseEvent* event);

	void updateUmbra();

private:
	QMenu* menu_file;
	QMenu* menu_view;
	QMenu* menu_help;

	QAction* act_save;
	QAction* act_about;
	QAction* act_quit;

	LCR::CollimatorHorizontalSectionView* gview_top;
	LCR::CollimatorHorizontalSectionView* gview_section;
	LCR::CollimatorHorizontalSectionView* gview_bottom;
	LCR::CollimatorVerticalSectionView* gview_vertical;
	LCR::UmbraView* gview_umbra;

	DockCollimator* dockCollimator;

	LCR::CollimatorEx collimator;
};

#endif // __EXAMPLE_MAINWINDOW_H__

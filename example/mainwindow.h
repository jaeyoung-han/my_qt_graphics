#ifndef __EXAMPLE_MAINWINDOW_H__
#define __EXAMPLE_MAINWINDOW_H__

#include <QMainWindow>
#include "CollimatorSectionalView.h"
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
  void about();
  void sizeUpdated();
  void parameterUpdated();
  void sectionUpdated();
  void loadSettings();
  void saveSettings();

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

  QAction* act_about;
  QAction* act_quit;

  LCR::CollimatorSectionalView* gview_top;
  LCR::CollimatorSectionalView* gview_section;
  LCR::CollimatorSectionalView* gview_bottom;
  LCR::UmbraView* gview_umbra;

  DockCollimator* dockCollimator;

  LCR::CollimatorEx collimator;
};

#endif // __EXAMPLE_MAINWINDOW_H__

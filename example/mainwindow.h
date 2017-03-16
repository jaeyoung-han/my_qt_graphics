#ifndef __EXAMPLE_MAINWINDOW_H__
#define __EXAMPLE_MAINWINDOW_H__

#include <QMainWindow>
#include "CollimatorSectionalView.h"

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

protected:
  void createActions();
  void createMenus();
  void createStatusBar();
  void createDocks();

private:
  QMenu* menu_file;
  QMenu* menu_view;
  QMenu* menu_help;

  QAction* act_about;
  QAction* act_quit;

  LCR::CollimatorSectionalView* gview_top;
  LCR::CollimatorSectionalView* gview_section;
  LCR::CollimatorSectionalView* gview_bottom;

  DockCollimator* dockCollimator;
};

#endif // __EXAMPLE_MAINWINDOW_H__

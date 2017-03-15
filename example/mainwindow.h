#ifndef __EXAMPLE_MAINWINDOW_H__
#define __EXAMPLE_MAINWINDOW_H__

#include <QMainWindow>
#include "graphicsview.h"

using namespace MQGAPI;

class MainWindow : public QMainWindow
{
  Q_OBJECT
public:
  MainWindow();

private:
  GraphicsView* gview_upper;
  GraphicsView* gview_lower;
};

#endif // __EXAMPLE_MAINWINDOW_H__

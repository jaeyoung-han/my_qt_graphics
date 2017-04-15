#include <QApplication>
#include "mainwindow.h"

int main(int argc, char* argv[])
{
  QApplication app(argc, argv);

  QCoreApplication::setOrganizationName("TeleSecurity Sciences, Inc.");
  QCoreApplication::setApplicationName("Collimator View");

  MainWindow w;
  w.show();
  return app.exec();
}

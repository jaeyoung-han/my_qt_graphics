#include <QApplication>
#include "mainwindow.h"

#ifdef NDEBUG
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, char*, int nShowCmd)
{
    int argc = 0;
    QApplication app(argc, 0);
    QCoreApplication::setApplicationName("Collimator View");
#else
int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    QCoreApplication::setApplicationName("Collimator View - DEBUG");
#endif
    QCoreApplication::setOrganizationName("TeleSecurity Sciences, Inc.");

    MainWindow w;
    w.show();
    return app.exec();
}

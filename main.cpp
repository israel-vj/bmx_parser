
#include <QApplication>
#include "MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow *w = new MainWindow();

    w->show();

    int returnCode = a.exec();

    return returnCode;
}

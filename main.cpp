#include <QApplication>
#include "mainwindow.hpp"

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    MainWindow main_window;

    main_window.resize(600, 400);
    main_window.show();

    return QApplication::exec();
}

#include <iostream>
#include <QApplication>
#include "../header/mainwindow.h"

using namespace std;

int main(int argc, char *argv[]) {
    system("chcp 65001");

    QApplication app(argc, argv);
    mainwindow mainWindow;
    mainWindow.show();

    return QApplication::exec();
}
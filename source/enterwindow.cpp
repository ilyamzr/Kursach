#include "../header/enterwindow.h"
#include "ui_enterWindow.h"
#include <iostream>

enterWindow::enterWindow(QWidget *parent) :
        QWidget(parent), ui(new Ui::enterWindow) {
    ui->setupUi(this);
}


enterWindow::~enterWindow() {
    delete ui;
}

QString enterWindow::getLogin()
{
    return ui->loginField->text();
}

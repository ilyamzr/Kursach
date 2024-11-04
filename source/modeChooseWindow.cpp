#include "../header/modeChooseWindow.h"
#include "ui_modeChooseWindow.h"

modeChooseWindow::modeChooseWindow(QWidget *parent) :
        QWidget(parent), ui(new Ui::modeChooseWindow) {
    ui->setupUi(this);
}

modeChooseWindow::~modeChooseWindow() {
    delete ui;
}


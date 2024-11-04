#include "../header/regwindow.h"
#include "ui_regWindow.h"
#include <QLabel>
#include <QPushButton>


regWindow::regWindow(QWidget *parent) :
        QWidget(parent), ui(new Ui::regWindow) {
    ui->setupUi(this);
}

regWindow::~regWindow() {
    delete ui;
}

//
// Created by ASUS on 29.10.2024.
//

// You may need to build the project (run Qt uic code generator) to get "ui_sellermenu.h" resolved

#include "../header/sellermenu.h"
#include "ui_sellermenu.h"


sellermenu::sellermenu(QWidget *parent) :
        QWidget(parent), ui(new Ui::sellermenu) {
    ui->setupUi(this);
}

sellermenu::~sellermenu() {
    delete ui;
}

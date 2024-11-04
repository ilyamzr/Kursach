//
// Created by ASUS on 30.10.2024.
//

// You may need to build the project (run Qt uic code generator) to get "ui_IonInfo.h" resolved

#include "../header/ioninfo.h"
#include "ui_IonInfo.h"


IonInfo::IonInfo(QWidget *parent) :
        QWidget(parent), ui(new Ui::IonInfo) {
    ui->setupUi(this);
}

IonInfo::~IonInfo() {
    delete ui;
}

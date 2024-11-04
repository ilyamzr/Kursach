//
// Created by ASUS on 29.10.2024.
//

#ifndef UNTITLED51_SELLERMENU_H
#define UNTITLED51_SELLERMENU_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class sellermenu; }
QT_END_NAMESPACE

class sellermenu : public QWidget {
Q_OBJECT

public:
    explicit sellermenu(QWidget *parent = nullptr);

    ~sellermenu() override;

private:
    Ui::sellermenu *ui;
};


#endif //UNTITLED51_SELLERMENU_H

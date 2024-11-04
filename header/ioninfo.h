//
// Created by ASUS on 30.10.2024.
//

#ifndef UNTITLED51_IONINFO_H
#define UNTITLED51_IONINFO_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class IonInfo; }
QT_END_NAMESPACE

class IonInfo : public QWidget {
Q_OBJECT

public:
    explicit IonInfo(QWidget *parent = nullptr);

    ~IonInfo() override;

private:
    Ui::IonInfo *ui;
};


#endif //UNTITLED51_IONINFO_H

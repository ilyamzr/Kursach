//
// Created by ASUS on 13.10.2024.
//

#ifndef UNTITLED51_REGWINDOW_H
#define UNTITLED51_REGWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class regWindow; }
QT_END_NAMESPACE

class regWindow : public QWidget {
Q_OBJECT

public:
    explicit regWindow(QWidget *parent = nullptr);

    ~regWindow() override;

private:
    Ui::regWindow *ui;
};


#endif //UNTITLED51_REGWINDOW_H

//
// Created by ASUS on 13.10.2024.
//

#ifndef UNTITLED51_ENTERWINDOW_H
#define UNTITLED51_ENTERWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class enterWindow; }
QT_END_NAMESPACE

class enterWindow : public QWidget {
Q_OBJECT

public:
    explicit enterWindow(QWidget *parent = nullptr);
    QString getLogin();
    QLabel* getLoginLabel();
    ~enterWindow() override;

private:
    Ui::enterWindow *ui;
};


#endif //UNTITLED51_ENTERWINDOW_H

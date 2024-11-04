#ifndef UNTITLED51_MAINWINDOW_H
#define UNTITLED51_MAINWINDOW_H

#include <QWidget>
#include <QLineEdit>
#include "enterwindow.h"
#include "regwindow.h"
#include "modeChooseWindow.h"
#include "buyerwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class mainwindow; }
QT_END_NAMESPACE

class mainwindow : public QWidget {
    Q_OBJECT

public:
    explicit mainwindow(QWidget *parent = nullptr);
    ~mainwindow() override;

private slots:
void enterButtonClicked();
void regButtonClicked();
void backToMainWindow();
void buyerFunc(const std::string& login);
void sellerFunc();
void modeChooseMenuShow(const std::string& login);
void lightError(QLineEdit* loginField);

private:
    Ui::mainwindow *ui;
    enterWindow *enterWindow;
    regWindow *regWindow;
    modeChooseWindow *modeWindow;
    buyerWindow *buyerWindow;
};


#endif //UNTITLED51_MAINWINDOW_H

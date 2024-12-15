#ifndef UNTITLED51_MAINWINDOW_H
#define UNTITLED51_MAINWINDOW_H

#include <QWidget>
#include <QLineEdit>
#include "enterwindow.h"
#include "regwindow.h"
#include "modeChooseWindow.h"
#include "buyerwindow.h"
#include "sellerwindow.h"

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
    void buyerFunc(const std::string& login);
    void sellerFunc(const std::string& login);
    void adminFunc();
    void lightError(QLineEdit* loginField, const std::string& errorLine, QLabel *errorField);

public slots:
    void backToMainWindow();
    void modeChooseMenuShow(const std::string& login);

private:
    Ui::mainwindow *ui;
    enterWindow *enterWindow;
    regWindow *regWindow;
    modeChooseWindow *modeWindow;
    buyerWindow *buyerWindow;
    sellerwindow *sellerWindow;
};


#endif //UNTITLED51_MAINWINDOW_H

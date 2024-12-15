#include "../header/mainwindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>
#include "ui_modeChooseWindow.h"
#include "ui_regWindow.h"
#include "ui_enterWindow.h"
#include <iostream>
#include "ui_buyerWindow.h"
#include <QTimer>
#include "../header/Admin.h"
#include "ui_sellerwindow.h"

mainwindow::mainwindow(QWidget *parent) :
        QWidget(parent), ui(new Ui::mainwindow), enterWindow(nullptr), regWindow(nullptr), modeWindow(nullptr), buyerWindow(nullptr),sellerWindow(
        nullptr) {
    ui->setupUi(this);

    QPixmap logo("C:/Users/ASUS/CLionProjects/untitled51/resources/logo3.png");
    QPixmap bg("C:/Users/ASUS/CLionProjects/untitled51/resources/bg1.png");

    ui->logoLabel->setPixmap(logo.scaled(ui->logoLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    ui->background->setPixmap(bg.scaled(ui->background->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    connect(ui->enterButton, &QPushButton::clicked, this, &mainwindow::enterButtonClicked);
    connect(ui->regButton, &QPushButton::clicked, this, &mainwindow::regButtonClicked);
}

mainwindow::~mainwindow() {
    delete ui;
    delete enterWindow;
    delete regWindow;
    delete modeWindow;
}

void mainwindow::buyerFunc(const std::string& login)
{
    if (!buyerWindow) {
        buyerWindow = new class buyerWindow(login,this);
    }
    buyerWindow->show();
}


void mainwindow::sellerFunc(const std::string& login)
{
    if (!sellerWindow) {
        sellerWindow = new class sellerwindow(login,this);
    }
    sellerWindow->show();
}

void mainwindow::modeChooseMenuShow(const std::string& login) {
    if (enterWindow) enterWindow->hide();
    if (regWindow) regWindow->hide();
    if (!modeWindow) {
        modeWindow = new class modeChooseWindow(this);
        auto *modeUI = new Ui::modeChooseWindow;
        modeUI->setupUi(modeWindow);
        QPixmap bg("C:/Users/ASUS/CLionProjects/untitled51/resources/bg1.png");
        modeUI->background->setPixmap(bg.scaled(ui->background->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        connect(modeUI->cancelButton, &QPushButton::clicked, this, &mainwindow::backToMainWindow);
        modeWindow->setProperty("ui", QVariant::fromValue(static_cast<void*>(modeUI)));
        connect(modeUI->buyerButton, &QPushButton::clicked, this, [this,login]()
        {
            buyerFunc(login);
        });
        connect(modeUI->sellerButton, &QPushButton::clicked, this, [this,login]()
        {
            sellerFunc(login);
        });
    }
    modeWindow->show();
}

void mainwindow::backToMainWindow() {
    if (enterWindow) enterWindow->hide();
    if (regWindow) regWindow->hide();
    if (modeWindow) modeWindow->hide();

    ui->menuContainer->show();
}

void mainwindow::lightError(QLineEdit* loginField, const std::string& errorLine, QLabel *errorField)
{
    loginField->setStyleSheet(
            "QLineEdit {"
            " background-color: rgba(255, 0, 0, 0.2);"
            "       border: 2px solid rgb(255,0,0);"
            "       border-radius: 20px;"
            "       padding: 5px;"
            "}"
    );
    errorField->setVisible(true);
    QString str = QString::fromStdString(errorLine);
    errorField->setText(str);
    QTimer::singleShot(3000, this, [loginField,errorField]() {
        loginField->setStyleSheet(
                "QLineEdit {"
                " background-color: rgba(83, 208, 158, 0.2);"
                "       border: 2px solid #53D09E;"
                "       border-radius: 20px;"
                "       padding: 5px;"
                "}"
        );
        errorField->setVisible(false);
    });
}

void mainwindow::adminFunc()
{

}

void mainwindow::enterButtonClicked()  {
    ui->menuContainer->hide();
    std::string log;
    if (!enterWindow) {
        enterWindow = new class enterWindow(this);
        auto *enterUI = new Ui::enterWindow;
        enterUI->setupUi(enterWindow);
        enterUI->errorText1->setVisible(false);
        enterUI->errorText2->setVisible(false);
        enterUI->loginToChange->setVisible(false);
        enterUI->newPassword->setVisible(false);
        enterUI->ID->setVisible(false);
        enterUI->newID->setVisible(false);
        enterUI->introText_3->setVisible(false);
        enterUI->introText_4->setVisible(false);
        enterUI->introText_5->setVisible(false);
        enterUI->introText_6->setVisible(false);
        enterUI->passwordField->setEchoMode(QLineEdit::Password); // Устанавливаем режим отображения точек
        QPixmap bg("C:/Users/ASUS/CLionProjects/untitled51/resources/bg1.png");
        enterUI->background->setPixmap(bg.scaled(ui->background->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        QPixmap neon("C:/Users/ASUS/CLionProjects/untitled51/resources/neon.png");
        QPixmap login("C:/Users/ASUS/CLionProjects/untitled51/resources/user-interfacew.png");
        QPixmap admin("C:/Users/ASUS/CLionProjects/untitled51/resources/admin.png");
        enterUI->admin->setPixmap(admin.scaled(enterUI->admin->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        connect(enterUI->adminButton, &QPushButton::clicked, this, [this, log]() {
            this->close();
            Admin::adminFunc(log);
        });
        enterUI->login->setPixmap(login.scaled(enterUI->login->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        enterUI->neon->setPixmap(neon.scaled(enterUI->neon->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        connect(enterUI->cancelButton, &QPushButton::clicked, this, [this, log, enterUI]() {
            enterUI->loginField->clear();
            enterUI->passwordField->clear();
            backToMainWindow();
        });
        connect(enterUI->adminButton, &QPushButton::clicked, this, [this, log, enterUI]() {
            if (enterUI->loginField->text().toStdString() == "Admin" && enterUI->passwordField->text().toStdString() == "ADMINPASS")
            {
                adminFunc();
            }
        });
        std::string loginText = enterWindow->getLogin().toStdString();
        connect(enterUI->applyButton, &QPushButton::clicked, this, [this, log, enterUI]() {
            bool loginSuccessful = false;
            bool passwordSuccessful = false;
            try
            {
                Profile::checkLogin(enterUI->loginField->text().toStdString());
                loginSuccessful = true;
            }
            catch (std::string& errorLine)
            {
                lightError(enterUI->loginField, errorLine, enterUI->errorText1);
            }
            try
            {
                Profile::checkPassword(enterUI->loginField->text().toStdString(), enterUI->passwordField->text().toStdString());
                passwordSuccessful = true;
            }
            catch (std::string& errorLine)
            {
                lightError(enterUI->passwordField, errorLine, enterUI->errorText2);
            }
            if (loginSuccessful && passwordSuccessful)
            {
                modeChooseMenuShow(enterUI->loginField->text().toStdString());
                enterUI->loginField->clear();
                enterUI->passwordField->clear();
            }
        });
        enterWindow->setProperty("ui", QVariant::fromValue(static_cast<void*>(enterUI)));
    }
    std::string login = enterWindow->getLogin().toStdString();
    enterWindow->show();
}

void mainwindow::regButtonClicked() {
    ui->menuContainer->hide();
    if (!regWindow) {
        regWindow = new class regWindow(this);
        auto *regUI = new Ui::regWindow;
        regUI->setupUi(regWindow);
        regUI->passwordField->setEchoMode(QLineEdit::Password);
        QPixmap bg("C:/Users/ASUS/CLionProjects/untitled51/resources/bg1.png");
        regUI->background->setPixmap(bg.scaled(ui->background->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        QPixmap neon("C:/Users/ASUS/CLionProjects/untitled51/resources/neon.png");
        regUI->neon->setPixmap(neon.scaled(regUI->neon->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        QPixmap login("C:/Users/ASUS/CLionProjects/untitled51/resources/user-interfacew.png");
        regUI->login->setPixmap(login.scaled(regUI->login->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        QPixmap password("C:/Users/ASUS/CLionProjects/untitled51/resources/padlockw.png");
        regUI->password->setPixmap(password.scaled(regUI->password->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        connect(regUI->cancelButton, &QPushButton::clicked, this, [regUI, this]() {
            regUI->loginField->clear();
            regUI->passwordField->clear();
            backToMainWindow();
        });
        regWindow->setProperty("ui", QVariant::fromValue(static_cast<void*>(regUI)));
        connect(regUI->applyButton, &QPushButton::clicked, this, [regUI, this]() {
            bool loginValid = false;
            bool passwordValid = false;
            std::string login = regUI->loginField->text().toStdString();
            std::string password = regUI->passwordField->text().toStdString();
            try
            {
                Profile::checkRegLogin(login);
                loginValid = true;
            }
            catch (std::string& errorLine)
            {
                lightError(regUI->loginField, errorLine, regUI->errorText1);
            }
            try
            {
                Profile::checkRegPassword(password);
                passwordValid = true;
            }
            catch (std::string& errorLine)
            {
                lightError(regUI->passwordField, errorLine, regUI->errorText2);
            }

            if (loginValid && passwordValid)
            {
                Profile profile(login, password, 0.0f);
                Profile::saveProfileToFile(profile, "ProfileData.txt");
                regUI->loginField->clear();
                regUI->passwordField->clear();
                backToMainWindow();
            }
        });
    }
    regWindow->show();
}

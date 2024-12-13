#include "../header/sellerwindow.h"
#include "ui_sellerwindow.h"
#include "../header/Product.h"
#include <iostream>
#include <QTimer>
#include <QPropertyAnimation>
#include "QGraphicsOpacityEffect"
#include "../header/operationFuncs.h"
#include "../header/mainwindow.h"

const std::array<std::array<std::string, 6>, 9> allCategories = {{
                                                                         {"Техника", "Смартфон", "Ноутбуки", "Телевизоры", "Бытовая техника", "Аудио и видео техника"},
                                                                         {"Спорт и активный отдых", "Спортивная одежда", "Спортивная обувь", "Тренажеры и фитнес-оборудование", "Туристическое снаряжение", "Велосипеды и аксессуары"},
                                                                         {"Мебель", "Мебель для гостиной", "Мебель для спальни", "Мебель для кухни", "Офисная мебель", "Детская мебель"},
                                                                         {"Дом", "Декор", "Освещение", "Текстиль", "Хранение", "Уборка"},
                                                                         {"Игрушки", "Конструкторы", "Мягкие игрушки", "Настольные игры", "Развивающие игрушки", "Электронные игрушки"},
                                                                         {"Детям", "Одежда", "Обувь", "Игрушки", "Учебные материалы", "Спортивные товары"},
                                                                         {"Мужчинам", "Одежда", "Обувь", "Аксессуары", "Парфюмерия", "Спортивные товары"},
                                                                         {"Женщинам", "Одежда", "Обувь", "Аксессуары", "Косметика", "Парфюмерия"},
                                                                 }};

void sellerwindow::updateSubcategories(int index)
{
    ui->subcategoryChoose->clear();

    for (int i = 1; i < 6; i++)
    {
        ui->subcategoryChoose->addItem(QString::fromStdString(allCategories[index][i]));
    }
}

void sellerwindow::pullMessage(const std::string& message)
{
    ui->messageText->setText(QString::fromStdString(message));
    auto* opacityEffect = new QGraphicsOpacityEffect(ui->messageText);
    ui->messageText->setGraphicsEffect(opacityEffect);
    auto* opacityAnimation = new QPropertyAnimation(opacityEffect, "opacity");
    opacityAnimation->setDuration(2000);
    opacityAnimation->setStartValue(1.0);
    opacityAnimation->setEndValue(0.0);
    opacityAnimation->start(QAbstractAnimation::DeleteWhenStopped);
}

void sellerwindow::addProduct(const std::string& login) {

    disconnect(ui->applyButton, &QPushButton::clicked, this, nullptr);

    ui->nameField->clear();
    ui->priceField->clear();
    ui->descriptionField->clear();

    ui->addProductWidget->setVisible(true);
    ui->left->setVisible(false);
    ui->leftButton->setVisible(false);
    ui->right->setVisible(false);
    ui->rightButton->setVisible(false);
    ui->productInfo->setVisible(false);
    ui->deleteProductButton->setVisible(false);
    ui->leftButton->setVisible(false);
    ui->left->setVisible(false);
    ui->rightButton->setVisible(false);
    ui->right->setVisible(false);

    auto *validator = new QDoubleValidator(ui->priceField);
    validator->setNotation(QDoubleValidator::StandardNotation);
    validator->setDecimals(2);
    ui->priceField->setValidator(validator);
    ui->categoryChoose->clear();
    for (int i = 0; i < 8; i++) {
        ui->categoryChoose->addItem(QString::fromStdString(allCategories[i][0]));
    }
    updateSubcategories(ui->categoryChoose->currentIndex());
    connect(ui->categoryChoose, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &sellerwindow::updateSubcategories);
    connect(ui->applyButton, &QPushButton::clicked, this, [this,login]() {
        Product newProduct(
                ui->nameField->text().toStdString(),
                ui->categoryChoose->currentIndex(),
                ui->subcategoryChoose->currentIndex(),
                ui->priceField->text().toFloat(),
                ui->descriptionField->toPlainText().toStdString(),
                Product::generateID(),
                login
        );
        Product::saveProductToFile(newProduct,"products.txt");
        ui->addProductWidget->setVisible(false);
        pullMessage("Продукт успешно добавлен");
    });
}

std::string getLastWord(const std::string& text) {
    size_t lastSpace = text.find_last_of(' ');
    if (lastSpace == std::string::npos) {
        return text;
    }
    return text.substr(lastSpace + 1);
}

void sellerwindow::deleteButtonsVisible(bool mode)
{
    ui->deleteProductButton->setVisible(mode);
    ui->leftButton->setVisible(mode);
    ui->left->setVisible(mode);
    ui->rightButton->setVisible(mode);
    ui->right->setVisible(mode);
}

void sellerwindow::deleteProductMenu(const std::string& login) {

    disconnect(ui->deleteProductButton, &QPushButton::clicked, this, nullptr);

    ui->addProductWidget->setVisible(false);
    ui->left->setVisible(false);
    ui->leftButton->setVisible(false);
    ui->right->setVisible(false);
    ui->rightButton->setVisible(false);
    ui->productInfo->setVisible(false);
    deleteButtonsVisible(true);
    std::vector<Product> products = Product::getMyProducts(login);
    ui->productInfo->setStyleSheet(
            "QTextEdit {"
            "  background: transparent;"
            "  color: white;"
            "  font-family: 'Yu Gothic UI Light', sans-serif;"
            "  font-size: 20px;"
            "}"
    );
    int i = 0;
    QString info = updateProductInfo(i, products);
    ui->productInfo->setPlainText(info);
    ui->productInfo->setVisible(true);
    std::cout << "B ";

    connect(ui->deleteProductButton, &QPushButton::clicked, this, [this,products]() mutable {
        int id;
        std::istringstream(getLastWord(ui->productInfo->toPlainText().toStdString())) >> id;
        Product::deleteProduct(id);
        ui->productInfo->setVisible(false);
        deleteButtonsVisible(false);
        pullMessage("Продукт успешно удален");
    });
    auto index= std::make_shared<int>(i);

    connect(ui->rightButton, &QPushButton::clicked, this, [this, index, products]() mutable {
        if (++(*index) > products.size() - 1) {
            *index = 0;
        }
        QString inf;
        inf = updateProductInfo(*index, products);
        ui->productInfo->setPlainText(inf);
    });

    connect(ui->leftButton, &QPushButton::clicked, this, [this, index, products]() mutable {
        if (--(*index) < 0) {
            *index = static_cast<int>(products.size()) - 1;
        }
        QString inf;
        inf = updateProductInfo(*index, products);
        ui->productInfo->setPlainText(inf);
    });
}

void sellerwindow::myProductsMenu(const std::string& login)
{
    ui->addProductWidget->setVisible(false);
    deleteButtonsVisible(false);
    ui->productInfo->setVisible(false);

    std::vector<Product> products = Product::getMyProducts(login);
    ui->productInfo->setStyleSheet(
            "QTextEdit {"
            "  background: transparent;"
            "  color: white;"
            "  font-family: 'Yu Gothic UI Light', sans-serif;"
            "  font-size: 20px;"
            "}"
    );
    int i = 0;
    QString info = updateProductInfo(i, products);
    ui->productInfo->setPlainText(info);
    ui->productInfo->setVisible(true);
    if (products.size() > 1)
    {
        ui->left->setVisible(true);
        ui->leftButton->setVisible(true);
        ui->right->setVisible(true);
        ui->rightButton->setVisible(true);
        ui->productInfo->setVisible(true);
    }
}

sellerwindow::sellerwindow(const std::string& login, QWidget *parent) :
        QWidget(parent), ui(new Ui::sellerwindow) {
    ui->setupUi(this);

    ui->addProductWidget->setVisible(false);
    ui->left->setVisible(false);
    ui->leftButton->setVisible(false);
    ui->right->setVisible(false);
    ui->rightButton->setVisible(false);
    ui->productInfo->setVisible(false);
    ui->deleteProductButton->setVisible(false);

    QPixmap bg("C:/Users/ASUS/CLionProjects/untitled51/resources/bg1.png");
    ui->background->setPixmap(bg.scaled(ui->background->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    QPixmap neon("C:/Users/ASUS/CLionProjects/untitled51/resources/neon.png");
    ui->neon->setPixmap(neon.scaled(ui->neon->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    connect(ui->addButton, &QPushButton::clicked, this, [this,login]() {
        addProduct(login);
    });
    connect(ui->deleteButton, &QPushButton::clicked, this, [this,login]() {
        deleteProductMenu(login);
    });
    connect(ui->myProductsButton, &QPushButton::clicked, this, [this,login]() {
        myProductsMenu(login);
    });
    connect(ui->backButton, &QPushButton::clicked, this, [this,login]() {
        this->close();
        mainwindow mw;
        mw.modeChooseMenuShow(login);
    });
}

sellerwindow::~sellerwindow() {
    delete ui;
}

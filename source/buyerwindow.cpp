#include "ui_modeChooseWindow.h"
#include "../header/operationFuncs.h"
#include "../header/mainwindow.h"
#include "../header/Profile.h"
#include <QPropertyAnimation>
#include "ui_buyerWindow.h"
#include <QVBoxLayout>
#include <QWidget>
#include <QTimer>
#include <utility>
#include "QGraphicsOpacityEffect"

using namespace std;

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

QString updateProfileInfo(const Profile& profile) {
    QString inf = QString("Логин: %1\n")
                          .arg(QString::fromStdString(profile.login)) +
                      QString("Баланс: %1$\n")
                          .arg(QString::number(profile.balance));
    return inf;
}



QString updateProductInfo(int index, const vector<Product>& products) {
    QString inf = QString("Наименование продукта: %1\n")
                          .arg(QString::fromStdString(products[index].name)) +
                  QString("%1/%2\n")
                          .arg(QString::fromStdString(allCategories[products[index].category][0]),
                               QString::fromStdString(allCategories[products[index].category][products[index].subcategory + 1])) +
                  QString("Цена: %1$\n")
                          .arg(QString::number(products[index].price)) +
                  QString("Описание: %1\n")
                          .arg(QString::fromStdString(products[index].description)) +
                  QString("Артикул: %1")
                          .arg(QString::number(products[index].id));
    return inf;
}

vector<string> searchForMatches(const QString &input) {
    std::vector<Product> products = Product::getAllProducts();
    vector<string> newProducts;
    for (const auto& product : products) {
        QString productName = QString::fromStdString(product.name);
        if (productName.startsWith(input, Qt::CaseInsensitive) && input != "") {
            newProducts.push_back(product.name);
        }
    }

    if (newProducts.empty()) {
        newProducts.emplace_back("No matches found");
    }

    return newProducts;
}

void buyerWindow::pullMessage(const std::string& message)
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

void buyerWindow::searchMenu(const string& login){
    ui->categories->setVisible(false);
    ui->buyButton->setVisible(false);
    ui->categoriesChoosed->setVisible(false);
    ui->subCategories->setVisible(false);
    ui->productInfo->setVisible(false);
    ui->applyButton->setVisible(false);
    ui->backFromSCButton->setVisible(false);
    ui->depositMoney->setVisible(false);
    ui->depositMoneyButton->setVisible(false);
    ui->checkProducts->setVisible(false);
    ui->searchField->setVisible(true);
    ui->helpButton->setVisible(false);
    ui->download->setVisible(false);
    ui->downloadButton->setVisible(false);
    ui->leftButton->setVisible(false);
    ui->left->setVisible(false);
    ui->rightButton->setVisible(false);
    ui->right->setVisible(false);
    ui->price->setVisible(false);
    ui->priceField->setVisible(false);
    ui->applyButton2->setVisible(false);
    ui->cancelButton->setVisible(false);
    ui->searchField->clear();

    disconnect(ui->searchField, &QLineEdit::textChanged, this, nullptr);
    disconnect(ui->helpButton, &QPushButton::clicked, this, nullptr);
    disconnect(ui->downloadButton, &QPushButton::clicked, this, nullptr);

    connect(ui->searchField, &QLineEdit::textChanged, this, [this,login](const QString &text) {
        vector<string> suggestion = searchForMatches(text);
        if (suggestion.empty() || suggestion[0] == "No matches found")
        {
            ui->helpText->setVisible(false);
            ui->help->setVisible(false);
            ui->loupe->setVisible(false);
        }
        else {
            ui->helpText->setText(QString::fromStdString(suggestion[0]));
            ui->helpText->setVisible(true);
            ui->help->setVisible(true);
            ui->loupe->setVisible(true);
            ui->helpButton->setVisible(true);
            connect(ui->helpButton, &QPushButton::clicked, this, [this,suggestion]() {
                ui->searchField->setText(QString::fromStdString(suggestion[0]));
            });
        }
        disconnect(ui->searchField, &QLineEdit::returnPressed, this, nullptr);
        connect(ui->searchField, &QLineEdit::returnPressed, this, [this,login,suggestion]() {
            if (suggestion[0] != "No matches found")
            {
                string name = ui->searchField->text().toStdString();
                vector<Product> products = Product::getProductsByName("products.txt",suggestion);
                productsCheck(products,0, login);
                ui->download->setVisible(true);
                ui->downloadButton->setVisible(true);
            }
            else pullMessage("Ничего не найдено");
        });
    });
    connect(ui->downloadButton, &QPushButton::clicked, this, [this,login]() {
        string name = ui->searchField->text().toStdString();
        vector<string> suggestion = searchForMatches(QString::fromStdString(name));
        vector<Product> products = Product::getProductsByName("products.txt",suggestion);
        createJsonOutput(login, products);
        ui->download->setVisible(false);
        ui->downloadButton->setVisible(false);
    });
}

void buyerWindow::productsCheck(const vector<Product>& products, int mode, const string& login)
{
    if (!products.empty()) {

        disconnect(ui->leftButton, &QPushButton::clicked, this, nullptr);
        disconnect(ui->rightButton, &QPushButton::clicked, this, nullptr);
        ui->productInfo->setStyleSheet(
                "QTextEdit {"
                "  background: transparent;"
                "  color: white;"
                "  font-family: 'Yu Gothic UI Light', sans-serif;"
                "  font-size: 20px;"
                "}"
        );
        ui->categories->setVisible(false);
        ui->categoriesChoosed->setVisible(false);
        ui->subCategories->setVisible(false);
        ui->productInfo->setVisible(false);
        ui->applyButton->setVisible(false);
        ui->backFromSCButton->setVisible(false);
        if (products.size() > 1)
        {
            ui->left->setVisible(true);
            ui->right->setVisible(true);
            ui->leftButton->setVisible(true);
            ui->rightButton->setVisible(true);
        }
        ui->productFrame->setVisible(true);
        ui->depositMoney->setVisible(false);
        ui->depositMoneyButton->setVisible(false);
        if (mode == 0) ui->buyButton->setVisible(true);
        ui->checkProducts->setVisible(false);
        ui->searchField->setVisible(false);
        ui->helpText->setVisible(false);
        ui->help->setVisible(false);
        ui->loupe->setVisible(false);
        ui->helpButton->setVisible(false);
        ui->download->setVisible(false);
        ui->downloadButton->setVisible(false);
        ui->price->setVisible(false);
        ui->priceField->setVisible(false);
        ui->applyButton2->setVisible(false);
        ui->cancelButton->setVisible(false);

        int i = 0;
        QString info;
        info = updateProductInfo(i, products);
        ui->productInfo->setPlainText(info);
        ui->productInfo->setVisible(true);

        if (products.size() > 1)
        {
            auto index = std::make_shared<int>(i);

            connect(ui->rightButton, &QPushButton::clicked, this, [this, index, products, login]() mutable {
                disconnect(ui->buyButton, &QPushButton::clicked, this, nullptr);
                if (++(*index) > products.size() - 1) {
                    *index = 0;
                }
                std::cout << "E ";
                QString inf;
                inf = updateProductInfo(*index, products);
                ui->productInfo->setPlainText(inf);
                connect(ui->buyButton, &QPushButton::clicked, this, [this, index, login, products]() mutable {
                    int id = __gnu_cxx::__alloc_traits<std::allocator<Product>>::value_type::getID(products[*index]);
                    Profile profile;
                    profile = profile.getProfileByLogin("ProfileData.txt",login);
                    Product product;
                    product = product.getProductByID(id);
                    if (product.getPrice() >= profile.getBalance())
                    {
                        Product::buyProduct(login, id);
                    }
                    else
                    {
                        pullMessage("Недостаточно денег на балансе");
                    }
                });
            });

            connect(ui->leftButton, &QPushButton::clicked, this, [this, index, products, login]() mutable {
                disconnect(ui->buyButton, &QPushButton::clicked, this, nullptr);
                if (--(*index) < 0) {
                    *index = static_cast<int>(products.size()) - 1;
                }
                QString inf;
                inf = updateProductInfo(*index, products);
                ui->productInfo->setPlainText(inf);
                connect(ui->buyButton, &QPushButton::clicked, this, [index, login, products]() mutable {
                    int id = __gnu_cxx::__alloc_traits<std::allocator<Product>>::value_type::getID(products[*index]);
                    Product::buyProduct(login, id);
                });
            });
        }
    }
}

void buyerWindow::depositMoney(const string& login)
{
    ui->checkProducts->setVisible(false);
    ui->depositMoney->setVisible(false);
    ui->depositMoneyButton->setVisible(false);
    ui->price->setVisible(true);
    ui->priceField->setVisible(true);
    ui->applyButton2->setVisible(true);
    ui->cancelButton->setVisible(true);
    ui->productInfo->setVisible(false);

    connect(ui->applyButton2, &QPushButton::clicked, this, [this,login]() mutable {
        Profile profile;
        profile = profile.getProfileByLogin("ProfileData.txt", login);
        profile.updateBalance(ui->priceField->text().toFloat());
        profile.deleteProfile("ProfileData.txt", login);
        Profile::saveProfileToFile(profile, "ProfileData.txt");
        pullMessage("Баланс успешно пополнен");
        ui->price->setVisible(false);
        ui->priceField->setVisible(false);
        ui->applyButton2->setVisible(false);
        ui->cancelButton->setVisible(false);
        ui->priceField->clear();
    });
    connect(ui->cancelButton, &QPushButton::clicked, this, [this]() mutable {
        ui->checkProducts->setVisible(true);
        ui->depositMoney->setVisible(true);
        ui->depositMoneyButton->setVisible(true);
        ui->price->setVisible(false);
        ui->priceField->setVisible(false);
        ui->applyButton2->setVisible(false);
        ui->cancelButton->setVisible(false);
    });
}

void buyerWindow::showProfileInfo(const string& login)
{
    ui->searchField->clear();
    Profile profile;
    profile = profile.getProfileByLogin("ProfileData.txt",login);
    QString info = updateProfileInfo(profile);

    ui->categoriesChoosed->setVisible(false);
    ui->categories->setVisible(false);
    ui->subCategories->setVisible(false);
    ui->applyButton->setVisible(false);
    ui->backFromSCButton->setVisible(false);
    ui->left->setVisible(false);
    ui->right->setVisible(false);
    ui->leftButton->setVisible(false);
    ui->rightButton->setVisible(false);
    ui->productFrame->setVisible(false);
    ui->buyButton->setVisible(false);
    ui->checkProducts->setVisible(true);
    ui->depositMoney->setVisible(true);
    ui->depositMoneyButton->setVisible(true);
    ui->searchField->setVisible(false);
    ui->helpText->setVisible(false);
    ui->help->setVisible(false);
    ui->loupe->setVisible(false);
    ui->helpButton->setVisible(false);
    ui->download->setVisible(false);
    ui->downloadButton->setVisible(false);
    ui->price->setVisible(false);
    ui->priceField->setVisible(false);
    ui->applyButton2->setVisible(false);
    ui->cancelButton->setVisible(false);

    ui->productInfo->setStyleSheet(
                "QTextEdit {"
                "  background: transparent;"
                "  color: white;"
                "  font-family: 'Yu Gothic UI Light', sans-serif;"
                "  font-size: 20px;"
                "}"
        );
        ui->productInfo->setPlainText(info);
        ui->productInfo->setVisible(true);
    connect(ui->depositMoneyButton, &QPushButton::clicked, this, [this,login]() mutable {
        depositMoney(login);
    });
    connect(ui->checkProducts, &QPushButton::clicked, this, [this,login]() {
        ui->checkProducts->setVisible(false);
        ui->depositMoney->setVisible(false);
        ui->depositMoneyButton->setVisible(false);
        vector<Product> products;
        vector<Product> updatedProducts;
        products = Product::getMyProducts(login);
        for (const auto& product : products) {
            if (Product::getStatus(product) == 0)
            {
                updatedProducts.push_back(product);
            }
        }
        productsCheck(updatedProducts,1,login);
    });
}

void buyerWindow::sortProductsByCategory(int categoryIndex, int subCategoryIndex, const string& login) {
    vector<Product> products = Product::categoriesSort(categoryIndex, subCategoryIndex, login);
    if (products.empty()) {
        pullMessage("Товар такой категории не найден");
        ui->applyButton->setStyleSheet(
                "QPushButton {"
                    "   background-color: rgba(255, 0, 0, 0.2);"
                    "   border: 2px solid rgba(255, 0, 0, 0.5);"
                    "   border-radius: 20px;"
                "   font-family: 'Yu Gothic UI Light', sans-serif;"
                "   font-size: 20px;"
                "   text-align: center;"
                "}"
                "QPushButton:hover {"
                "   color: rgba(83, 208, 158, 1);"
                "}"
        );
        QTimer::singleShot(3000, this, [this]() {
            ui->applyButton->setStyleSheet(
                    "QPushButton {"
                    "   background-color: rgba(83, 208, 158, 0.2);"
                    "   border: 2px solid #53D09E;"
                    "   border-radius: 20px;"
                    "   font-family: 'Yu Gothic UI Light', sans-serif;"
                    "   font-size: 20px;"
                    "   text-align: center;"
                    "}"
                    "QPushButton:hover {"
                    "   color: rgba(83, 208, 158, 1);"
                    "}"
            );
        });
    } else {
        productsCheck(products,0, login);
    }
}

void buyerWindow::showAllProducts(const string& login)
{
    ui->searchField->clear();
    ifstream file("products.txt");
    if (!file.is_open()) {
        cout << "Не удалось открыть файл: " << endl;
        return;
    }

    vector <Product> products;
    string line;
    while (getline(file, line)) {
        if (!line.empty())
        {
            Product product = Product::readFromFile(line);
            if (Product::getOwner(product) != login) products.push_back(product);
        }
    }
    productsCheck(products,0, login);
}

void buyerWindow::showSubcategory(int index, const string& login){
    ui->categories->setVisible(false);
    ui->categoriesChoosed->setVisible(true);
    ui->subCategories->setVisible(true);
    ui->subCategories->clear();

    disconnect(ui->applyButton, &QPushButton::clicked, this, nullptr);
    disconnect(ui->backFromSCButton, &QPushButton::clicked, this, nullptr);

    for (int i = 1; i < 6; i++)
    {
        ui->subCategories->addItem(QString::fromStdString(allCategories[index][i]));
    }
    ui->applyButton->setVisible(true);
    ui->backFromSCButton->setVisible(true);

    connect(ui->applyButton, &QPushButton::clicked, this, [this, index, login]() {
        int selectedIndex = ui->subCategories->currentIndex();
        sortProductsByCategory(index,selectedIndex, login);
    });
    connect(ui->backFromSCButton, &QPushButton::clicked, this,[this, login]() {
        showCategories(login);
    });
}

void buyerWindow::showCategories(const string& login)
{
    ui->searchField->clear();
    ui->categoriesChoosed->setVisible(false);
    ui->subCategories->setVisible(false);
    ui->categories->setVisible(true);
    ui->applyButton->setVisible(false);
    ui->backFromSCButton->setVisible(false);
    ui->left->setVisible(false);
    ui->right->setVisible(false);
    ui->leftButton->setVisible(false);
    ui->rightButton->setVisible(false);
    ui->productFrame->setVisible(false);
    ui->productInfo->setVisible(false);
    ui->buyButton->setVisible(false);
    ui->checkProducts->setVisible(false);
    ui->depositMoney->setVisible(false);
    ui->depositMoneyButton->setVisible(false);
    ui->searchField->setVisible(false);
    ui->helpText->setVisible(false);
    ui->help->setVisible(false);
    ui->loupe->setVisible(false);
    ui->helpButton->setVisible(false);
    ui->download->setVisible(false);
    ui->downloadButton->setVisible(false);
    ui->price->setVisible(false);
    ui->priceField->setVisible(false);
    ui->applyButton2->setVisible(false);
    ui->cancelButton->setVisible(false);

    QPixmap category1("C:/Users/ASUS/CLionProjects/untitled51/resources/categories/1.png");
    ui->categoryFrame->setPixmap(category1.scaled(ui->categoryFrame->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

    QPixmap category2("C:/Users/ASUS/CLionProjects/untitled51/resources/categories/2.png");
    ui->categoryFrame_2->setPixmap(category2.scaled(ui->categoryFrame_2->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

    QPixmap category3("C:/Users/ASUS/CLionProjects/untitled51/resources/categories/3.png");
    ui->categoryFrame_3->setPixmap(category3.scaled(ui->categoryFrame_3->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

    QPixmap category4("C:/Users/ASUS/CLionProjects/untitled51/resources/categories/4.png");
    ui->categoryFrame_4->setPixmap(category4.scaled(ui->categoryFrame_4->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

    QPixmap category5("C:/Users/ASUS/CLionProjects/untitled51/resources/categories/5.png");
    ui->categoryFrame_5->setPixmap(category5.scaled(ui->categoryFrame_5->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

    QPixmap category6("C:/Users/ASUS/CLionProjects/untitled51/resources/categories/6.png");
    ui->categoryFrame_6->setPixmap(category6.scaled(ui->categoryFrame_6->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

    QPixmap category7("C:/Users/ASUS/CLionProjects/untitled51/resources/categories/7.png");
    ui->categoryFrame_7->setPixmap(category7.scaled(ui->categoryFrame_7->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

    QPixmap category8("C:/Users/ASUS/CLionProjects/untitled51/resources/categories/8.png");
    ui->categoryFrame_8->setPixmap(category8.scaled(ui->categoryFrame_8->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

    connect(ui->buyerButton_1, &QPushButton::clicked, this, [this, category1, login]() {
        ui->categoryFrame_10->setPixmap(category1.scaled(ui->categoryFrame_10->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        ui->categoryName_10->setText(ui->categoryName->text());
        ui->categoryName_10->setAlignment(Qt::AlignCenter);
        showSubcategory(0, login);
    });

    connect(ui->buyerButton_2, &QPushButton::clicked, this, [this, category2, login]() {
        ui->categoryFrame_10->setPixmap(category2.scaled(ui->categoryFrame_10->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        ui->categoryName_10->setText(ui->categoryName_2->text());
        ui->categoryName_10->setAlignment(Qt::AlignCenter);
        showSubcategory(1, login);
    });

    connect(ui->buyerButton_3, &QPushButton::clicked, this, [this, category3, login]() {
        ui->categoryFrame_10->setPixmap(category3.scaled(ui->categoryFrame_10->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        ui->categoryName_10->setText(ui->categoryName_3->text());
        ui->categoryName_10->setAlignment(Qt::AlignCenter);
        showSubcategory(2, login);
    });

    connect(ui->buyerButton_4, &QPushButton::clicked, this, [this, category4, login]() {
        ui->categoryFrame_10->setPixmap(category4.scaled(ui->categoryFrame_10->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        ui->categoryName_10->setText(ui->categoryName_4->text());
        ui->categoryName_10->setAlignment(Qt::AlignCenter);
        showSubcategory(3, login);
    });

    connect(ui->buyerButton_5, &QPushButton::clicked, this, [this, category5, login]() {
        ui->categoryFrame_10->setPixmap(category5.scaled(ui->categoryFrame_10->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        ui->categoryName_10->setText(ui->categoryName_5->text());
        ui->categoryName_10->setAlignment(Qt::AlignCenter);
        showSubcategory(4, login);
    });

    connect(ui->buyerButton_6, &QPushButton::clicked, this, [this, category6, login]() {
        ui->categoryFrame_10->setPixmap(category6.scaled(ui->categoryFrame_10->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        ui->categoryName_10->setText(ui->categoryName_6->text());
        ui->categoryName_10->setAlignment(Qt::AlignCenter);
        showSubcategory(5, login);
    });

    connect(ui->buyerButton_7, &QPushButton::clicked, this, [this, category7, login]() {
        ui->categoryFrame_10->setPixmap(category7.scaled(ui->categoryFrame_10->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        ui->categoryName_10->setText(ui->categoryName_7->text());
        ui->categoryName_10->setAlignment(Qt::AlignCenter);
        showSubcategory(6, login);
    });

    connect(ui->buyerButton_8, &QPushButton::clicked, this, [this, category8, login]() {
        ui->categoryFrame_10->setPixmap(category8.scaled(ui->categoryFrame_10->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        ui->categoryName_10->setText(ui->categoryName_8->text());
        ui->categoryName_10->setAlignment(Qt::AlignCenter);
        showSubcategory(7, login);
    });

}

buyerWindow::buyerWindow(string login,QWidget *parent) :
        QWidget(parent), ui(new Ui::buyerWindow), userLogin(std::move(login)), modeWindow(nullptr) {
    login = userLogin;
    ui->setupUi(this);
    ui->categoriesChoosed->setVisible(false);
    ui->subCategories->setVisible(false);
    ui->applyButton->setVisible(false);
    ui->backFromSCButton->setVisible(false);
    ui->categories->setVisible(false);
    ui->productInfo->setVisible(false);
    ui->left->setVisible(false);
    ui->right->setVisible(false);
    ui->leftButton->setVisible(false);
    ui->rightButton->setVisible(false);
    ui->productFrame->setVisible(false);
    ui->buyButton->setVisible(false);
    ui->checkProducts->setVisible(false);
    ui->depositMoney->setVisible(false);
    ui->depositMoneyButton->setVisible(false);
    ui->searchField->setVisible(false);
    ui->helpText->setVisible(false);
    ui->help->setVisible(false);
    ui->loupe->setVisible(false);
    ui->helpButton->setVisible(false);
    ui->download->setVisible(false);
    ui->downloadButton->setVisible(false);
    ui->price->setVisible(false);
    ui->priceField->setVisible(false);
    ui->applyButton2->setVisible(false);
    ui->cancelButton->setVisible(false);

    QPixmap bg("C:/Users/ASUS/CLionProjects/untitled51/resources/bg1.png");
    ui->background->setPixmap(bg.scaled(ui->background->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    QPixmap neon("C:/Users/ASUS/CLionProjects/untitled51/resources/neon.png");
    ui->neon->setPixmap(neon.scaled(ui->neon->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    QPixmap loupe("C:/Users/ASUS/CLionProjects/untitled51/resources/loupe.png");
    ui->loupe->setPixmap(loupe.scaled(ui->loupe->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    QPixmap download("C:/Users/ASUS/CLionProjects/untitled51/resources/download.png");
    ui->download->setPixmap(download.scaled(ui->loupe->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    connect(ui->categoryMenu, &QPushButton::clicked, this, [this, login]() {
        showCategories(login);
    });
    connect(ui->productsButton, &QPushButton::clicked, this, [this, login]() {
        showAllProducts(login);
    });
    connect(ui->profileButton, &QPushButton::clicked, this, [this, login]() {
        showProfileInfo(login);
    });
    connect(ui->searchButton, &QPushButton::clicked, this, [this, login]() {
        searchMenu(login);
    });
    connect(ui->backButton, &QPushButton::clicked, this, [this,login]() {
        this->close();
        mainwindow mw;
        mw.modeChooseMenuShow(login);
    });
}

buyerWindow::~buyerWindow() {
    delete ui;
}

#include "../header/buyerwindow.h"
#include "../header/profileFuncs.h"
#include "../header/operationFuncs.h"
#include <QPropertyAnimation>
#include "ui_buyerWindow.h"
#include <QVBoxLayout>
#include <QWidget>
#include <QTimer>
#include <utility>

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

QString updateProfileInfo(const Profile<float>& profile) {
    QString inf = QString("Логин: %1\n")
                          .arg(QString::fromStdString(profile.login)) +
                      QString("Баланс: %1$\n")
                          .arg(QString::number(profile.balance)) +
                  QString("Количество товаров: %1\n")
                          .arg(QString::number(profile.productsAmount));
    return inf;
}

QString updateProductInfo(int index, const vector<Product>& products) {
    QString inf = QString("Наименование продукта: %1\n")
                          .arg(QString::fromStdString(products[index].name)) +
                  QString("%1/%2\n")
                          .arg(QString::fromStdString(allCategories[products[index].category - 1][0]),
                               QString::fromStdString(allCategories[products[index].category - 1][products[index].subcategory])) +
                  QString("Цена: %1$\n")
                          .arg(QString::number(products[index].price)) +
                  QString("Описание: %1\n")
                          .arg(QString::fromStdString(products[index].description)) +
                  QString("Артикул: %1")
                          .arg(QString::number(products[index].id));
    return inf;
}

void buyerWindow::productsCheck(const vector <Product>& products, int mode, const string& login)
{
    if (!products.empty()) {
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
        ui->categoriesChoosed->setVisible(false);
        ui->subCategories->setVisible(false);
        ui->productInfo->setVisible(false);
        ui->applyButton->setVisible(false);
        ui->backFromSCButton->setVisible(false);
        ui->left->setVisible(true);
        ui->right->setVisible(true);
        ui->leftButton->setVisible(true);
        ui->rightButton->setVisible(true);
        ui->productFrame->setVisible(true);
        ui->depositMoney->setVisible(false);
        ui->depositMoneyButton->setVisible(false);
        if (mode == 0)ui->buyButton->setVisible(true);
        ui->checkProducts->setVisible(false);

        int i = 0;
        QString info;
        info = updateProductInfo(i, products);
        ui->productInfo->setPlainText(info);
        ui->productInfo->setVisible(true);

        connect(ui->rightButton, &QPushButton::clicked, this, [this, i, products, login]() mutable {
            if (++i > products.size()-1) {
                i = 0;
            }
            cout << i << endl;
            QString inf;
            inf = updateProductInfo(i, products);
            ui->productInfo->setPlainText(inf);
            connect(ui->buyButton, &QPushButton::clicked, this, [i, login, products]() mutable {
                int id = __gnu_cxx::__alloc_traits<std::allocator<Product>>::value_type::getID(products[i]);
                buyProduct(login,id);
            });
        });
        connect(ui->leftButton, &QPushButton::clicked, this, [this, i, products, login]() mutable {
            if (--i < 0) {
                i = static_cast<int>(products.size()) - 1;
            }
            cout << i << endl;
            QString inf;
            inf = updateProductInfo(i, products);
            ui->productInfo->setPlainText(inf);
            connect(ui->buyButton, &QPushButton::clicked, this, [i, login]() mutable {
                cout << i;
                buyProduct(login,i);
            });
        });

    }
}

void buyerWindow::showProfileInfo(const string& login)
{
    Profile profile = getProfileByLogin("ProfileData.txt",login);
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
        vector<int> productIds = Profile<float>::getProducts(profile);
        vector<Product> products;
        for (int productId : productIds)
        {
            products.push_back(getProductByID("products.txt",productId));
        }
        connect(ui->checkProducts, &QPushButton::clicked, this, [this, products, login]() mutable {
            productsCheck(products,1,login);
    });
    connect(ui->depositMoneyButton, &QPushButton::clicked, this, [this, products, login]() mutable {
        productsCheck(products,1,login);
    });
}

void buyerWindow::sortProductsByCategory(int categoryIndex, int subCategoryIndex, const string& login) {
    vector<Product> products = categoriesSort("products.txt", categoryIndex + 1, subCategoryIndex + 1);
    if (products.empty()) {
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
    ifstream file("products.txt");
    if (!file.is_open()) {
        cout << "Не удалось открыть файл: " << endl;
        return;
    }

    QPropertyAnimation *animation = new QPropertyAnimation(ui->productsButton, "pos");
    animation->setDuration(1000); // Длительность анимации в миллисекундах
    animation->setStartValue(pos());
    animation->setEndValue(QPoint(pos().x() + 100, pos().y() + 100)); // Новая позиция
    animation->start(QAbstractAnimation::DeleteWhenStopped); // Удалить анимацию после завершения

    vector <Product> products;
    string line;
    while (getline(file, line)) {
        if (!line.empty())
        {
            Product product = Product::readFromFile(line);
            products.push_back(product);
        }
    }
    productsCheck(products,0, login);
}

void buyerWindow::showSubcategory(int index, const string& login){
    ui->categories->setVisible(false);
    ui->categoriesChoosed->setVisible(true);
    ui->subCategories->setVisible(true);
    ui->subCategories->clear();

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
        QWidget(parent), ui(new Ui::buyerWindow), userLogin(std::move(login)) {
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

    QPixmap bg("C:/Users/ASUS/CLionProjects/untitled51/resources/bg1.png");
    ui->background->setPixmap(bg.scaled(ui->background->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    QPixmap neon("C:/Users/ASUS/CLionProjects/untitled51/resources/neon.png");
    ui->neon->setPixmap(neon.scaled(ui->neon->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    connect(ui->categoryMenu, &QPushButton::clicked, this, [this, login]() {
        showCategories(login);
    });
    connect(ui->productsButton, &QPushButton::clicked, this, [this, login]() {
        showAllProducts(login);
    });
    connect(ui->profileButton, &QPushButton::clicked, this, [this, login]() {
        showProfileInfo(login);
    });
}

buyerWindow::~buyerWindow() {
    delete ui;
}

#include <iostream>
#include <string>
#include <array>
#include <QApplication>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include "operationFuncs.h"

using namespace std;

void sellerMode()
{
    string filename = "products.txt";
    string login;
    cout << "Введите логин: ";
    cin >> login;
    int choice = 0;
    while (choice != 4)
    {
        cout << "Выберите действие:\n1) Добавить товар\n2) Посмотреть мои товары\n3) Удалить товар\n4) Назад";
        cin >> choice;
        if (choice == 1)
        {
            addProductFunc(login,filename);
        }
        else if (choice == 2)
        {
            viewProducts(login, filename,1);
        }
        else if (choice == 3)
        {
            deleteProductFunc(login,filename);
        }
        else if (choice != 4) cout << "Неверный выбор" << endl;
    }
}

void buyermode()
{
<<<<<<< HEAD
    string filename = "products.txt";
    int choice;
=======
    int choice = 0;
>>>>>>> 010c55f5ef3869b70f5dc6105b6a95c277507403
    while (choice != 4)
    {
        cout << "Выберите действие:\n1) Категории \n2) Все товары \n3) Профиль \n4) Назад";
        cin >> choice;
        if (choice == 1)
        {
            categoriesFunc(filename);
        }
        else if (choice == 2)
        {
            viewProducts("",filename,0);
        }
        else if (choice != 4) cout << "Неверный выбор" << endl;
    }
}

void setupUI(QWidget *window) {
    window->setWindowTitle("ION");
    window->resize(800, 600);

    QVBoxLayout *layout;
    layout = new QVBoxLayout(window);

    auto *label = new QLabel("Добро пожаловать на ИОН", window);
    label->resize(620, 150);
    label->setAlignment(Qt::AlignCenter);
    label->setFont(QFont("Yu Gothic UI Light", 30));
    layout->addWidget(label);

    auto *sellerButton = new QPushButton("Войти как продавец", window);
    sellerButton->resize(315, 50);
    sellerButton->setFont(QFont("Yu Gothic UI Light", 20));
    layout->addWidget(sellerButton);
    sellerButton->resize(315, 50);
    sellerButton->setFont(QFont("Yu Gothic UI Light", 20));

    QPushButton *buyerButton;
    buyerButton = new QPushButton("Войти как покупатель", window);
    buyerButton->resize(315, 50);
    buyerButton->setFont(QFont("Yu Gothic UI Light", 20));
    layout->addWidget(buyerButton);

    QPushButton *regButton;
    regButton = new QPushButton("Зарегестрироваться", window);
    regButton->resize(315, 50);
    regButton->setFont(QFont("Yu Gothic UI Light", 20));
    layout->addWidget(regButton);

    QPushButton *exitButton;
    exitButton = new QPushButton("Выйти", window);
    exitButton->resize(315, 50);
    exitButton->setFont(QFont("Yu Gothic UI Light", 20));
    layout->addWidget(exitButton);

    auto *image = new QLabel(window);
    QPixmap pixmap("C:\\bsuir\\logo2.png");
    image->setPixmap(pixmap);
    image->resize(200, 200);
    image->move(310, 0);
    image->setScaledContents(true);

    QObject::connect(sellerButton, &QPushButton::clicked, []() {
        QApplication::quit();
        sellerMode();
    });
    QObject::connect(buyerButton, &QPushButton::clicked, []() {
        QApplication::quit();
        buyermode();
    });
    QObject::connect(regButton, &QPushButton::clicked, []() {
        QApplication::quit();
        cout << "Еще не готово" << endl;
    });
    QObject::connect(exitButton, &QPushButton::clicked, []() {
        QApplication::quit();
    });

}

const std::array<std::array<std::string, 6>, 9> allCategories = {{
                                                                         {"Техника", "Смартфон", "Ноутбуки", "Телевизоры", "Бытовая техника", "Аудио и видео техника"},
                                                                         {"Спорт и активный отдых", "Спортивная одежда", "Спортивная обувь", "Тренажеры и фитнес-оборудование", "Туристическое снаряжение", "Велосипеды и аксессуары"},
                                                                         {"Мебель", "Мебель для гостиной", "Мебель для спальни", "Мебель для кухни", "Офисная мебель", "Детская мебель"},
                                                                         {"Дом", "Декор", "Освещение", "Текстиль", "Хранение", "Уборка"},
                                                                         {"Игрушки", "Конструкторы", "Мягкие игрушки", "Настольные игры", "Развивающие игрушки", "Электронные игрушки"},
                                                                         {"Мужчинам", "Одежда", "Обувь", "Аксессуары", "Парфюмерия", "Спортивные товары"},
                                                                         {"Женщинам", "Одежда", "Обувь", "Аксессуары", "Косметика", "Парфюмерия"},
                                                                         {"Детям", "Одежда", "Обувь", "Игрушки", "Учебные материалы", "Спортивные товары"},{"Продукты", "Фрукты и овощи", "Молочные продукты", "Мясо и рыба", "Бакалея", "Напитки" }
                                                                 }};

void printCategories()
{
    for (int i = 0; i < 9; i++)
    {
        cout << i+1 << ") " << allCategories[i][0] << endl;
    }
}
void printSubCategories(int category)
{
    for (int i = 1; i < 6; i++)
    {
        cout << i << ") " << allCategories[category][i] << endl;
    }
}

void printProductInfo(string &productInfo)
{
    string word = getWord(productInfo);
    cout << "Наименование товара: " << word << endl;
    word = getWord(productInfo);
    int num1;
    symbToDigit(word, &num1);
    cout << allCategories[num1-1][0] << "/";
    word = getWord(productInfo);
    int num2;
    symbToDigit(word, &num2);
    cout << allCategories[num1-1][num2] << endl;
    word = getWord(productInfo);
    cout << "Цена: " << word << "$" << endl;
    word = getWord(productInfo);
    cout << "Описание товара: " << word << endl;
    word = getWord(productInfo);
    cout << "Артикул: " << word << endl;
}

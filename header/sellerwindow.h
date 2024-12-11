//
// Created by ASUS on 01.12.2024.
//

#ifndef UNTITLED51_SELLERWINDOW_H
#define UNTITLED51_SELLERWINDOW_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class sellerwindow; }
QT_END_NAMESPACE

class sellerwindow : public QWidget {
Q_OBJECT

public:
    explicit sellerwindow(const std::string& login, QWidget *parent = nullptr);
    void addProduct(const std::string& login);
    void updateSubcategories(int index);
    void deleteProductMenu(const std::string& login);
    void deleteButtonsVisible(bool mode);
    void pullMessage(const std::string& message);
    void myProductsMenu(const std::string& login);
    ~sellerwindow() override;

private:
    Ui::sellerwindow *ui;
};


#endif //UNTITLED51_SELLERWINDOW_H

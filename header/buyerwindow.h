//
// Created by ASUS on 20.10.2024.
//

#ifndef UNTITLED51_BUYERWINDOW_H
#define UNTITLED51_BUYERWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QString>
#include <QComboBox>
#include "../header/Product.h"

QT_BEGIN_NAMESPACE
namespace Ui { class buyerWindow; }
QT_END_NAMESPACE

class buyerWindow : public QWidget {
Q_OBJECT

public:
    explicit buyerWindow(std::string  login, QWidget *parent = nullptr);
    void showCategories(const std::string& login);
    void showSubcategory(int index,const std::string& login);
    void sortProductsByCategory(int categoryIndex, int subCategoryIndex, const std::string& login);
    void showAllProducts(const std::string& login);
    void showProfileInfo(const std::string& login);
    void productsCheck(const std::vector <Product>& product, int mode, const std::string& logimn);
    void searchMenu(const std::string& login);
    ~buyerWindow() override;
private:
    Ui::buyerWindow *ui;
    std::string userLogin;
};


#endif //UNTITLED51_BUYERWINDOW_H

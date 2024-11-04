#ifndef UNTITLED51_MODECHOOSEWINDOW_H
#define UNTITLED51_MODECHOOSEWINDOW_H

#include <QWidget>
#include <Qlabel>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class modeChooseWindow; }
QT_END_NAMESPACE

class modeChooseWindow : public QWidget {
    Q_OBJECT

public:
    explicit modeChooseWindow(QWidget *parent = nullptr);

    ~modeChooseWindow() override;

private:
    Ui::modeChooseWindow *ui;
};


#endif //UNTITLED51_MODECHOOSEWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "./passwordmanager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    PasswordManager *passManager;

private slots:
    void digit_pressed();
    void unary_operation_pressed();
    void binary_operation_pressed();

    void on_decimal_btn_released();
    void on_clear_btn_released();
    void on_equality_btn_released();
};
#endif // MAINWINDOW_H

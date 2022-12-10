#include "mainwindow.h"
#include "./ui_mainwindow.h"

double firstNum;
bool userISTypingSecondNumber = false;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // digits
    connect(ui->num0_btn,SIGNAL(clicked()),this,SLOT(digit_pressed()));
    connect(ui->num1_btn,SIGNAL(clicked()),this,SLOT(digit_pressed()));
    connect(ui->num2_btn,SIGNAL(clicked()),this,SLOT(digit_pressed()));
    connect(ui->num3_btn,SIGNAL(clicked()),this,SLOT(digit_pressed()));
    connect(ui->num4_btn,SIGNAL(clicked()),this,SLOT(digit_pressed()));
    connect(ui->num5_btn,SIGNAL(clicked()),this,SLOT(digit_pressed()));
    connect(ui->num6_btn,SIGNAL(clicked()),this,SLOT(digit_pressed()));
    connect(ui->num7_btn,SIGNAL(clicked()),this,SLOT(digit_pressed()));
    connect(ui->num8_btn,SIGNAL(clicked()),this,SLOT(digit_pressed()));
    connect(ui->num9_btn,SIGNAL(clicked()),this,SLOT(digit_pressed()));


    //connect unary operation to unary_operation_pressed  SLOT method

    connect(ui->percentage_btn,SIGNAL(released()),this,SLOT(unary_operation_pressed()));
    connect(ui->plusminus_btn,SIGNAL(released()),this,SLOT(unary_operation_pressed()));



        connect(ui->plus_btn,SIGNAL(released()),this,SLOT(binary_operation_pressed()));
        connect(ui->minus_btn,SIGNAL(released()),this,SLOT(binary_operation_pressed()));
        connect(ui->division_btn,SIGNAL(released()),this,SLOT(binary_operation_pressed()));
        connect(ui->multiply_btn,SIGNAL(released()),this,SLOT(binary_operation_pressed()));

        ui->plus_btn->setCheckable(true);
        ui->minus_btn ->setCheckable(true);
        ui->multiply_btn->setCheckable(true);
        ui->division_btn->setCheckable(true);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::digit_pressed() {
    QPushButton * button = (QPushButton*)sender();

    double labelNumber;
    QString newLabel;


    bool signsPressed = ui-> plus_btn -> isChecked() ||
            ui-> minus_btn -> isChecked() ||
            ui-> division_btn -> isChecked() ||
            ui-> multiply_btn -> isChecked();
    if(signsPressed && !userISTypingSecondNumber)
    {
        labelNumber = button->text().toDouble();
        userISTypingSecondNumber = true;
        newLabel = QString::number(labelNumber,'g',15);
    } else {
        if(ui -> result_label -> text().contains(".") && button -> text() == "0") {
            newLabel = (ui->result_label->text() + button->text());
        } else {
            labelNumber = (ui->result_label->text() + button->text()).toDouble();
            newLabel = QString::number(labelNumber,'g',15);
        }
    }


    ui->result_label->setText(newLabel);
}

void MainWindow::on_decimal_btn_released()
{
    QString text = ui -> result_label -> text();

    if(!text.contains(".")) {
        ui->result_label->setText(ui-> result_label-> text() + ".");
    }
}



void MainWindow::unary_operation_pressed() {
       QPushButton * button = (QPushButton*)sender();
       QString operation = button -> text();

       QLabel * result = ui -> result_label;
       QString value = result -> text();

       double labelNumber;
       QString newLabel;

       if(operation == "+/-") {
             labelNumber = value.toDouble();
             labelNumber *= -1;

             newLabel = QString::number(labelNumber,'g',15);

             result -> setText(newLabel);
       }
       if(operation == "%") {
             labelNumber = value.toDouble();
             labelNumber *= 0.01;

             newLabel = QString::number(labelNumber,'g',15);

             result -> setText(newLabel);
       }
}

void MainWindow::on_clear_btn_released()
{
    ui -> plus_btn -> setChecked(false);
    ui -> minus_btn -> setChecked(false);
    ui -> multiply_btn -> setChecked(false);
    ui -> division_btn -> setChecked(false);

    userISTypingSecondNumber = false;

    ui -> result_label -> setText("0");
}


void MainWindow::on_equality_btn_released()
{
    double labelNumber, secondNum;
    QString newLabel;

    secondNum = ui -> result_label -> text().toDouble();

    if(ui-> plus_btn -> isChecked()) {
        labelNumber = firstNum + secondNum;
        newLabel = QString::number(labelNumber,'g',15);
        ui-> result_label -> setText(newLabel);
        ui -> plus_btn -> setChecked(false);
    } else if(ui-> minus_btn -> isChecked()) {
        labelNumber = firstNum - secondNum;
        newLabel = QString::number(labelNumber,'g',15);
        ui-> result_label -> setText(newLabel);
        ui -> minus_btn -> setChecked(false);
    } else if(ui-> multiply_btn -> isChecked()) {
        labelNumber = firstNum * secondNum;
        newLabel = QString::number(labelNumber,'g',15);
        ui-> result_label -> setText(newLabel);
        ui -> multiply_btn -> setChecked(false);
    } else if(ui-> division_btn -> isChecked()) {
        labelNumber = firstNum / secondNum;
        newLabel = QString::number(labelNumber,'g',15);
        ui-> result_label -> setText(newLabel);
        ui -> division_btn -> setChecked(false);
    }

    userISTypingSecondNumber = false;
}

void MainWindow::binary_operation_pressed() {
    QPushButton * button = (QPushButton*)sender();

    firstNum = ui -> result_label -> text().toDouble();

    button->setChecked(true);
}



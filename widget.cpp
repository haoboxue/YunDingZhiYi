#include "widget.h"
#include "ui_widget.h"
#include "caculator.h"
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_clicked()
{
    caculator *c = new caculator;
    c->show();
    this->close();
}

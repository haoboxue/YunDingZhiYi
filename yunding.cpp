#include "yunding.h"
#include "ui_yunding.h"

YunDing::YunDing(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::YunDing)
{
    ui->setupUi(this);
}

YunDing::~YunDing()
{
    delete ui;
}

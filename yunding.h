#ifndef YUNDING_H
#define YUNDING_H

#include <QMainWindow>

namespace Ui {
class YunDing;
}

class YunDing : public QMainWindow
{
    Q_OBJECT

public:
    explicit YunDing(QWidget *parent = nullptr);
    ~YunDing();

private:
    Ui::YunDing *ui;
};

#endif // YUNDING_H

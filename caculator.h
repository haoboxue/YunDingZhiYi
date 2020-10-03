#ifndef CACULATOR_H
#define CACULATOR_H

#include <QMainWindow>

namespace Ui {
class caculator;
}

class caculator : public QMainWindow
{
    Q_OBJECT

public:
    explicit caculator(QWidget *parent = nullptr);
    void caculate();
    void RecNum(int num);
    void RecOpe(QChar ch);
    int Recfunc(QString fun);
    void reverseAv();
    float compute();
    bool isCalFun(QString str);
    void trans(QString str);
    int getpriority(QChar ch);

    ~caculator();
signals:
    void click_caculate();
private:
    Ui::caculator *ui;

};

#endif // CACULATOR_H

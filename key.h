#ifndef KEY_H
#define KEY_H

#include <QObject>
#include <QLabel>
#include <QWidget>

class key : public QLabel
{
    Q_OBJECT
public:
    explicit key(QWidget *parent = nullptr);
    void mouseReleaseEvent(QMouseEvent *event);
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
signals:
    void clicked();


};

#endif // KEY_H

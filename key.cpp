#include "key.h"

key::key(QWidget *parent) : QLabel(parent)
{
   this->setStyleSheet(
                ".key:hover{background-color:lightgrey} ; \n key{border:2px solid grey};");
}


void key::mouseReleaseEvent(QMouseEvent *event)
{
    emit clicked();
}

void key::enterEvent(QEvent *event)
{

}

void key::leaveEvent(QEvent *event)
{

}

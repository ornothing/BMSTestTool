#include "mybutton.h"

MyButton::MyButton(const QString &text, unsigned int index, QWidget *parent)
{
    setText(text);
    setParent(parent);
    myIndex = index;
}

MyButton::~MyButton()
{

}

void MyButton::ClickHandle()
{
    emit myclick(myIndex);
}

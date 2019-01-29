#ifndef MYBUTTON_H
#define MYBUTTON_H
#include <QPushButton>

class MyButton : public QPushButton
{
    Q_OBJECT
public:
    MyButton(const QString &text, unsigned int index, QWidget *parent = Q_NULLPTR);
    ~MyButton();

private:
    unsigned int myIndex;

public slots:
    void ClickHandle();
signals:
    void myclick(unsigned int index);
};


#endif // MYBUTTON_H

#include <QApplication>
#include "MainDialog.h"
#include "databasedefine.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    BMSMainDialog w;
    w.show();

    return a.exec();
}

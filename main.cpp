#include "menuwindow.h"

#include <QApplication>

// initializes the game and creates a MenuWindow Option to display
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MenuWindow w;
    w.show();
    return a.exec();
}

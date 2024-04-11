#include "gameoflife.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GameofLife w;
    w.show();
    return a.exec();
}

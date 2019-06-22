#include <QApplication>
#include "Tile.h"
#include "BoardWnd.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BoardWnd::GetInstance()->Init();
    BoardWnd::GetInstance()->show();
    return a.exec();
}

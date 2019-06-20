#ifndef LOADIMAGE_H
#define LOADIMAGE_H
#include "Singleton.h"
#include <QPixmap>

class LoadImageMng: public Singleton<LoadImageMng>
{
public:
    const QIcon&       LoadIcon(QString iconStr);
    const QPixmap&     LoadPixmap(QString iconStr);
};

#endif // LOADIMAGE_H

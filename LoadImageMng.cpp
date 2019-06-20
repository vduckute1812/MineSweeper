#include "LoadImageMng.h"
#include <QIcon>
#include <QFileInfo>

const QIcon& LoadImageMng::LoadIcon(QString iconStr)
{
    const QList<QString> extensions = { ".svg", ".png", ".tga", ".ico", ".bmp" };

    QIcon* icon = nullptr;

    if(!iconStr.isEmpty())
    {
        for (int i = 0; i < static_cast<int>(extensions.size()); ++i)
        {
            QString fn(QString("Resources/") + iconStr + extensions[i]);

            QFileInfo info(fn);
            if (info.exists())
            {
                icon = new QIcon(fn);
                break;
            }
        }
    }

return *icon;
}

const QPixmap& LoadImageMng::LoadPixmap(QString iconStr)
{
    const QList<QString> extensions = { ".svg", ".png", ".tga", ".ico", ".bmp" };

    QPixmap* icon = nullptr;

    if(!iconStr.isEmpty())
    {
        for (int i = 0; i < static_cast<int>(extensions.size()); ++i)
        {
            QString fn(QString("Resources/") + iconStr + extensions[i]);

            QFileInfo info(fn);
            if (info.exists())
            {
                icon = new QPixmap(fn);
                break;
            }
        }
    }

return *icon;
}

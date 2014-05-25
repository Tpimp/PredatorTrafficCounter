#include "videolocator.h"
#include <QDir>
#include <QFileInfo>
#include <QFileInfoList>
#include <QDebug>
VideoLocator::VideoLocator(QObject *parent) :
    QObject(parent)
{
}

QStringList VideoLocator::findVideos(QString directory)
{
    QStringList video_list;

    QDir dir(directory);
    dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    dir.setSorting(QDir::Name);

    QFileInfoList list = dir.entryInfoList();
    if(list.size() < 1)
    {
        qDebug() << "No Videos were Found";
    }
    else
    {
        foreach( QFileInfo file_info, list)
        {
            if(file_info.fileName().endsWith("_info.txt"))
            {
                video_list.append(file_info.fileName());
            }
        }
    }
    return video_list;
}

#include "videoinforeader.h"
#include <QFile>
#include <QStringList>
VideoInfoReader::VideoInfoReader()
{

}


QString VideoInfoReader::readVideoInfo(QString video_info_filepath)
{
    QFile  video_info_file(video_info_filepath);
    QString video_info;

    if(video_info_file.exists())
    {
        video_info_file.open(QIODevice::ReadOnly);
        video_info = video_info_file.readAll();

    }
    else
    {
        video_info =  "Error: File Doesn't Exist.";
    }

    return video_info;
}

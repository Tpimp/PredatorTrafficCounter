#include "videosourcedataobject.h"

VideoSourceDataObject::VideoSourceDataObject(QString vidname, QObject *parent) :
    QObject(parent), mVideoName(vidname)
{}


VideoSourceDataObject::VideoSourceDataObject(const QString &vidname, const bool &local,
                                             const bool &onserver, const QString &info,
                                             const bool &downloading, const int &percentcomp,
                                             QObject * parent)
    : QObject(parent), mVideoName(vidname), mLocal(local), mOnServer(onserver),
      mVideoInfo(info), mDownloading(downloading), mPercentComplete(percentcomp)
{}


int VideoSourceDataObject::amountComplete()
{
    return mPercentComplete;
}



bool VideoSourceDataObject::isDownloading()
{
    return mDownloading;
}

bool VideoSourceDataObject::isLocal()
{
    return mLocal;
}

bool VideoSourceDataObject::onServer()
{
    return mOnServer;
}

QString VideoSourceDataObject::videoInfo()
{
    return mVideoInfo;
}

QString VideoSourceDataObject::videoName()
{
    return mVideoName;
}


QTime VideoSourceDataObject::getDuration()
{
    // Get the time string
    QString duration__unparsed_str(getInfoString("Duration"));

    // parse the string and create a QTime object
    int colon_index(duration__unparsed_str.indexOf(":"));
    QString duration_str(duration__unparsed_str.remove(0,colon_index));
    int duration_integer(duration_str.toInt());

    // create object from parsed time string using mediainfo format
    return QTime::fromMSecsSinceStartOfDay(duration_integer);
}



qint64 VideoSourceDataObject::getFileSize()
{
    // Get the file size string
    QString unparsed_file_size(getInfoString("File size"));

    // parse the string and create a QTime object
    int colon_index(unparsed_file_size.indexOf(":"));
    QString file_size_str(unparsed_file_size.remove(0,colon_index));

    // create object from parsed time string using mediainfo format
    return file_size_str.toLongLong();

}

QString VideoSourceDataObject::getInfoString(QString info_name)
{
    int index(mVideoInfo.indexOf(info_name));
    QString info_string(36);
    while(mVideoInfo.at(index) != '\n')
        info_string.append(mVideoInfo[index++]);
    return info_string;
}




void VideoSourceDataObject::setAmountComplete(const int amountcomplete)
{
    mPercentComplete = amountcomplete;
}

void VideoSourceDataObject::setDownloading(const bool downloading)
{
    mDownloading = downloading;
}

void VideoSourceDataObject::setLocal(const bool &local)
{
   mLocal = local;
}

void VideoSourceDataObject::setOnServer(const bool &servable)
{
    mOnServer = servable;
}


void VideoSourceDataObject::setVideoInfo(const QString &info)
{
    mVideoInfo = info;
}

void VideoSourceDataObject::setVideoName(const QString &name)
{
   mVideoName = name;
}


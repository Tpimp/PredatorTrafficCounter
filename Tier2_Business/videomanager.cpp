#include "videomanager.h"
#include <QFile>

VideoManager::VideoManager(QString & video_directory, QQmlContext *context, VideoTransferManager *video_manager, QObject *parent) :
    QObject(parent), mVideoDirectory(video_directory), mContext(context), mTransferManager(video_manager)
{}


// add methods

void VideoManager::addVideosFromLocal(QStringList videos)
{
    VideoSourceDataObject *video;
    foreach(QString video_name, videos)
    {
        video = getVideoObject(video_name);
        if(!video)
        {
            video = new VideoSourceDataObject(video_name,this);
            video->setLocal(true);
            mVideoObjects.append(qobject_cast<QObject *>(video));
        }
        else
        {
            video->setLocal(true);
        }
    }
    mContext->setContextProperty("videoList",QVariant::fromValue(mVideoObjects));
    emit videoObjectsChanged(mVideoObjects);
}


void VideoManager::addVideosFromServer(QStringList videos)
{
    VideoSourceDataObject *video;
    foreach(QString video_name, videos)
    {
        video = getVideoObject(video_name);
        if(!video)
        {
            video = new VideoSourceDataObject(video_name,this);
            video->setOnServer(true);
            mVideoObjects.append(qobject_cast<QObject *>(video));
        }
        else
        {
            video->setOnServer(true);
        }
    }
    mContext->setContextProperty("videoList",QVariant::fromValue(mVideoObjects));
    emit videoObjectsChanged(mVideoObjects);
}




void VideoManager::fetchAllVideoInfo()
{
        mFetchingAll = true;
        mCurrentIndex = 0;
        QTimer::singleShot(1500, this, SLOT(fetchNextInfo()));
}


void VideoManager::fetchNextInfo()
{
    if(mCurrentIndex <  mVideoObjects.length())
    {
        VideoSourceDataObject *video;
        video = reinterpret_cast<VideoSourceDataObject*>(mVideoObjects[mCurrentIndex]);
        QString video_name(video->videoName());
        mFetchingAll = true;
        mCurrentIndex++;
        mTransferManager->fetchVideoInfoFromServer(video_name);
    }

}

VideoSourceDataObject *VideoManager::getVideoObject(QString video_name)
{
    VideoSourceDataObject *ptr(nullptr);

    foreach(QObject * qptr, mVideoObjects)
    {
        VideoSourceDataObject * video = reinterpret_cast<VideoSourceDataObject *>(qptr);
        if(video->videoName() == video_name)
        {
            ptr = video;
            break;
        }
    }

    return ptr;
}

void VideoManager::updateVideoInfo(QString video_name, QString video_info)
{
    for(int index = 0; index < mVideoObjects.length(); ++index)
    {
        VideoSourceDataObject * video =
                reinterpret_cast<VideoSourceDataObject *>(mVideoObjects[index]);
        if(video->videoName() == video_name)
        {
            qDebug() << "Recieved Info for Video" << video_name;
            video->setVideoInfo(video_info);
            mContext->setContextProperty("videoList",QVariant::fromValue(mVideoObjects));
            emit videoInfoUpdated(video_name,index, video_info);
            if(mFetchingAll)
            {
                QTimer::singleShot(1500, this, SLOT(fetchNextInfo()));
            }
            break;
        }
    }

}

void VideoManager::removeVideoFromLocal(QString video_name)
{
    // check if the video exists
    QFile video(mVideoDirectory + video_name);
    if(video.exists())
    {
        video.remove(); // delete the video if it does
    }
}

VideoManager::~VideoManager()
{
    if(!mVideoObjects.isEmpty())
    {
        QObject * current_ptr;
        while(!mVideoObjects.isEmpty())
        {
            current_ptr = mVideoObjects.takeLast();
            delete current_ptr;
        }
    }
}

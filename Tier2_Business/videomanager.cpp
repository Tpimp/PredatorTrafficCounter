#include "videomanager.h"
#include <QFile>

VideoManager::VideoManager(QString & video_directory, QObject *parent) :
    QObject(parent), mVideoDirectory(video_directory)
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
            mVideoObjects.append(video);
        }
        else
        {
            video->setLocal(true);
        }
    }
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
            mVideoObjects.append(video);
        }
        else
        {
            video->setOnServer(true);
        }
    }

}


VideoSourceDataObject *VideoManager::getVideoObject(QString video_name)
{
    VideoSourceDataObject *ptr(nullptr);

    foreach(VideoSourceDataObject * video, mVideoObjects)
    {
        if(video->videoName().compare(video_name))
        {
            ptr = video;
            goto EXIT_GET_VID_OBJ;
        }
    }

    EXIT_GET_VID_OBJ:
    return ptr;
}

void VideoManager::updateVideoInfo(QString video_name, QString video_info)
{
    foreach(VideoSourceDataObject * video, mVideoObjects)
    {
        if(video->videoName().compare(video_name))
        {
            video->setVideoInfo(video_info);
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

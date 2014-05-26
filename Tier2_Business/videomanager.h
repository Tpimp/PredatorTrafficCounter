#ifndef VIDEOMANAGER_H
#define VIDEOMANAGER_H

#include <QObject>
#include <Tier2_Business/videosourcedataobject.h>
#include <QStringList>
/****************************************************************
**VideoManager class tracks local videos and videos stored on
** a server. VideoManager also handles removing videos from local
** storage.
****************************************************************/
class VideoManager : public QObject
{
    Q_OBJECT
public:
    explicit VideoManager(QString &video_directory, QObject *parent = 0);
    VideoSourceDataObject* getVideoObject(QString video_name);

signals:

    void videoDeleted();
    void videoInfoUpdated(QString video_name, QString video_info);
    void videoObjectsChanged(QList<VideoSourceDataObject *> video_source_list);

public slots:

    void addVideosFromServer(QStringList videos);
    void addVideosFromLocal(QStringList videos);
    void updateVideoInfo(QString video_name, QString video_info);
    void removeVideoFromLocal(QString video_name);

private:

    // members to assist video management
    QList<VideoSourceDataObject *>      mVideoObjects;
    QString                             mVideoDirectory;


};

#endif // VIDEOMANAGER_H

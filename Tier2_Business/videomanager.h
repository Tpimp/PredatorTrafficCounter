#ifndef VIDEOMANAGER_H
#define VIDEOMANAGER_H

#include <QObject>
#include <Tier2_Business/videosourcedataobject.h>
#include <QStringList>
#include <QQmlContext>
#include "Tier2_Business/filetransfermanager.h"
#include <QTimer>

/****************************************************************
**VideoManager class tracks local videos and videos stored on
** a server. VideoManager also handles removing videos from local
** storage.
****************************************************************/
class VideoManager : public QObject
{
    Q_OBJECT

public:
    explicit VideoManager(QString &video_directory,QQmlContext * context,
                          FileTransferManager* video_manager, QObject *parent = 0);
    VideoSourceDataObject* getVideoObject(QString video_name);
    ~VideoManager();
    Q_INVOKABLE void fetchAllVideoInfo();
signals:

    void videoDeleted();
    void videoInfoUpdated(QString video_name, int index, QString video_info);
    void videoObjectsChanged(QList<QObject *> video_source_list);
public slots:

    void addVideosFromServer(QStringList videos);
    void fetchNextInfo();
    void addVideosFromLocal(QStringList videos);
    void updateVideoInfo(QString video_name, QString video_info);
    void removeVideoFromLocal(QString video_name);


private:

    // members to assist video management
    QList<QObject *>                    mVideoObjects;
    QString                             mVideoDirectory;
    QQmlContext                         *mContext = nullptr;
    FileTransferManager                 *mTransferManager;
    bool                                mFetchingAll = false;
    int                                 mCurrentIndex;
};

#endif // VIDEOMANAGER_H

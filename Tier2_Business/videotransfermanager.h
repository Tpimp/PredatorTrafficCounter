#ifndef VIDEOTRANSFERMANAGER_H
#define VIDEOTRANSFERMANAGER_H

#include <QObject>
#include <QHostInfo>
#include <QTcpSocket>
#include <QList>

enum TransferState
{
    IDLE,
    CONNECTED,
    RECEIVING_LIST,
    RECEIVING_INFO,
    RECEIVING_VIDEO,
    FINISHED_RECEIVING
};

class VideoTransferManager : public QObject
{
    Q_OBJECT
public:
    explicit VideoTransferManager(QObject *parent = 0);

signals:

    void connectedForTransfer();
    void connectionFailed();
    void downloadPercentChanged(QString name,int percent);
    void videoListFetched(QStringList video_list);
    void downloadFinished(QString name);
    void recievedVideoInfo(QString name, QString info);

public slots:

    void    attemptConnectionToHost(QString host_ip);
    void    connectedToHost();
    void    connectionLost();
    void    fetchVideoListFromServer();
    void    fetchVideoFromServer(QString video_name,qint64 expected_file_size);
    void    fetchVideoInfoFromServer(QString video_name);
    void    readData();
    void    readFinishing();
    void    videoDownloadFinished(QString name);

protected:
    void    processMessage();


private:
    QHostInfo           mHostInfo;
    int                 mHostPort;
    QTcpSocket          mSocket;
    TransferState       mState;
    QString             mTransferItemName;
    QString             mVideoDirectory;
    QByteArray          mMessageRecieved;
    QByteArray          mIncomingMessage;
};

#endif // VIDEOTRANSFERMANAGER_H

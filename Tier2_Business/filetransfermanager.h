#ifndef FILETRANSFERMANAGER_H
#define FILETRANSFERMANAGER_H

#include <QObject>
#include <QHostInfo>
#include <QTcpSocket>
#include <QList>
#include <QTimer>

enum TransferState
{
    IDLE,
    CONNECTED,
    RECEIVING_LIST,
    RECEIVING_INFO,
    RECEIVING_THUMBNAIL,
    RECEIVING_VIDEO,
    FINISHED_RECEIVING
};

class FileTransferManager : public QObject
{
    Q_OBJECT
public:
    explicit FileTransferManager(QObject *parent = 0);
    ~FileTransferManager();
    void clearConnection();
signals:

    void connectedForTransfer();
    void connectionFailed();
    void downloadPercentChanged(QString name,int percent);
    void videoListFetched(QStringList video_list);
    void downloadFinished(QString name);
    void recievedVideoInfo(QString name, QString info);

public slots:

    void attemptConnectionToHost(QString host_ip, int port = 8889);
    void connectedToHost();
    void connectionLost();
    void failedToConnectToHost();
    void fetchVideoListFromServer();
    void fetchThumbnailFromServer(QString video_name);
    void fetchVideoFromServer(QString video_name);
    void fetchVideoInfoFromServer(QString video_name);
    void readData();
    void readFinishing();
    void videoDownloadFinished(QString name);

protected:
    void processMessage();
    void checkConnectionReady();


private:

    QHostInfo           mHostInfo;
    int                 mHostPort;
    QTcpSocket          mSocket;
    TransferState       mState;
    QString             mTransferItemName;
    QString             mVideoDirectory;
    QByteArray          mMessageRecieved;
    QByteArray          mIncomingMessage;
    int                 mCurrentRecordIndex = 0;
    QTimer              mWatchdogTimer;

};

#endif // VIDEOTRANSFERMANAGER_H

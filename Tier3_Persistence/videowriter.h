#ifndef VIDEOWRITER_H
#define VIDEOWRITER_H

#include <QObject>
#include <QTcpSocket>
#include <QBuffer>
#include <QFile>
#include "Tier2_Business/videotransfermanager.h"
class VideoWriter : public QObject
{
    Q_OBJECT
public:
    explicit VideoWriter(VideoTransferManager *parent, QString filepath_out, QTcpSocket &socket, qint64 expect_file_size);

signals:
    void fileTransferComplete();
public slots:
    void dataReadyForWrite();
    void dataFinishedSending();

private:
    QString               mFilePath;
    QTcpSocket           &mSocket;
    QFile                 mVideoOut;
    QBuffer               mBuffer;
    qint64                mExpectedFileSize;
    qint64                mBytesWritten;
    VideoTransferManager* mParent;

};

#endif // VIDEOWRITER_H

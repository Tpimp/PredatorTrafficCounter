#ifndef VIDEOWRITER_H
#define VIDEOWRITER_H

#include <QObject>
#include <QTcpSocket>
#include <QBuffer>
#include <QFile>
#include "Tier2_Business/filetransfermanager.h"
class FileWriter : public QObject
{
    Q_OBJECT
public:
    explicit FileWriter(FileTransferManager *parent, QString filepath_out, QTcpSocket &socket);

signals:
    void fileTransferComplete();
public slots:
    void dataReadyForWrite();
    void dataFinishedSending();

private:
    QString               mFilePath;
    QTcpSocket           &mSocket;
    QFile                 mFileOut;
    QBuffer               mBuffer;
    qint64                mExpectedFileSize;
    qint64                mBytesWritten;
    FileTransferManager*  mParent;

};

#endif // VIDEOWRITER_H

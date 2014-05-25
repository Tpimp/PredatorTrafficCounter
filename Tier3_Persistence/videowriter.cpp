#include "videowriter.h"
#include <QDebug>

VideoWriter::VideoWriter(VideoTransferManager *parent, QString filepath_out, QTcpSocket &socket, qint64 expect_file_size) :
    QObject(parent), mParent(parent), mBytesWritten(0), mFilePath(filepath_out), mSocket(socket), mVideoOut(filepath_out), mExpectedFileSize(expect_file_size)
{
    mVideoOut.open(QIODevice::WriteOnly);
    connect(&mSocket,SIGNAL(readyRead()),this,SLOT(dataReadyForWrite()));
    connect(&mSocket,SIGNAL(readChannelFinished()),this,SLOT(dataFinishedSending()));
}



void VideoWriter::dataFinishedSending()
{
    mBuffer.write(mSocket.readAll());
    mVideoOut.write(mBuffer.readAll());
    mVideoOut.close();
    if(mVideoOut.size() != mExpectedFileSize)
        qWarning() << "File failed to Transfer completely!";
    emit fileTransferComplete();
}


void VideoWriter::dataReadyForWrite()
{
    mBuffer.write(mSocket.readAll());
    mBytesWritten += mVideoOut.write(mBuffer.readAll());
    int percent_complete = (100 * (mVideoOut.size()/mExpectedFileSize));
    int percent_complete2 = (100 * (mBytesWritten/mExpectedFileSize));
    qDebug() << "Percent 1 mVideo: " << percent_complete
             << "Percent Written: " <<  percent_complete2;
    emit mParent->downloadPercentChanged(mFilePath,percent_complete);
}


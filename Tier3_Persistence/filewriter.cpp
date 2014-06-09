#include "Tier3_Persistence/filewriter.h"
#include <QDebug>

FileWriter::FileWriter(FileTransferManager *parent, QString filepath_out, QTcpSocket &socket) :
    QObject(parent), mParent(parent), mBytesWritten(0), mFilePath(filepath_out), mSocket(socket), mFileOut(filepath_out)
{
    mFileOut.open(QIODevice::WriteOnly);
    connect(&mSocket,SIGNAL(readyRead()),this,SLOT(dataReadyForWrite()));
    connect(&mSocket,SIGNAL(readChannelFinished()),this,SLOT(dataFinishedSending()));
}



void FileWriter::dataFinishedSending()
{
    mBuffer.write(mSocket.readAll());
    mFileOut.write(mBuffer.readAll());
    mFileOut.close();
    if(mFileOut.size() != mExpectedFileSize)
        qWarning() << "File failed to Transfer completely!";
    emit fileTransferComplete();
}


void FileWriter::dataReadyForWrite()
{
    mBuffer.write(mSocket.readAll());
    mBytesWritten += mFileOut.write(mBuffer.readAll());
    int percent_complete = (100 * (mFileOut.size()/mExpectedFileSize));
    int percent_complete2 = (100 * (mBytesWritten/mExpectedFileSize));
    qDebug() << "Percent 1 mVideo: " << percent_complete
             << "Percent Written: " <<  percent_complete2;
    emit mParent->downloadPercentChanged(mFilePath,percent_complete);
}


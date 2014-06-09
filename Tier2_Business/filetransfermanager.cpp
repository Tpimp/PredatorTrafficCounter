#include "filetransfermanager.h"
#include <QHostAddress>
#include <QList>
#include <QStringList>
#include <QFile>
#include "Tier2_Business/filewritethread.h"
#include "Tier2_Business/videosourcedataobject.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonObject>
#include <QDir>
#include <QListWidgetItem>
#include <QFileDialog>
#include <QtDebug>
#include <QBuffer>
#include <QImageWriter>

FileTransferManager::FileTransferManager(QObject *parent) :
    QObject(parent), mHostInfo(QHostInfo()), mState(IDLE),
    mVideoDirectory(QDir::homePath()), mWatchdogTimer(this)
{
    mSocket.setReadBufferSize(80000000);
    connect(&mSocket,SIGNAL(connected()),this,SLOT(connectedToHost()));
    connect(&mSocket,SIGNAL(readyRead()),this,SLOT(readData()));
    connect(&mWatchdogTimer, &QTimer::timeout, this, &FileTransferManager::failedToConnectToHost);
    connect(&mSocket,SIGNAL(disconnected()),this,SLOT(connectionLost()));
    connect(&mSocket,SIGNAL(readChannelFinished()),this,SLOT(readFinishing()));
}



void FileTransferManager::attemptConnectionToHost(QString host_ip, int port)
{
    qDebug() << host_ip << port;
    // set watchdog for one minute
    mWatchdogTimer.setInterval(45000);
    mWatchdogTimer.start();
    mSocket.connectToHost(QHostAddress(host_ip),port);

}

void FileTransferManager::connectedToHost()
{
    mWatchdogTimer.stop();
    emit connectedForTransfer();
}


void FileTransferManager::checkConnectionReady()
{
    if(mSocket.state() == QTcpSocket::UnconnectedState)
       mSocket.connectToHost(mSocket.peerAddress(),8889);
    if(!mSocket.isOpen())
       mSocket.open(QIODevice::ReadWrite);
}

void  FileTransferManager::connectionLost()
{
    emit connectionFailed();
    checkConnectionReady();
}

void FileTransferManager::failedToConnectToHost()
{
    mSocket.disconnectFromHost();
    mSocket.close();
    emit connectionFailed();
}

void FileTransferManager::fetchThumbnailFromServer(QString video_name)
{

    mTransferItemName = video_name;
    FileWriteThread* thumbnailthread(new FileWriteThread(this,
                                                     mHostInfo.addresses()[0],
                                                     mHostPort,
                                                     video_name));

    mState = RECEIVING_THUMBNAIL;

}

void FileTransferManager::fetchVideoListFromServer()
{
    checkConnectionReady();
    QJsonDocument doc;
    QJsonArray    array;
    QJsonObject funcname;
    funcname["FuncName"] = QJsonValue::fromVariant(QVariant::fromValue(QString("VideoList")));
    array.append(funcname);
    QJsonObject max_return;
    max_return["MaxReturn"] = QJsonValue::fromVariant(QVariant::fromValue(-1));
    array.append(max_return);
    doc.setArray(array);
    QByteArray message("\001");
    message.append(doc.toJson());
    message.append("\004");
    mSocket.write(message);
    mSocket.waitForBytesWritten(3000);
    mState = RECEIVING_LIST;

}

void  FileTransferManager::fetchVideoFromServer(QString video_name)
{
    mTransferItemName = video_name;
    FileWriteThread* videothread(new FileWriteThread(this,
                                                     mHostInfo.addresses()[0],
                                                     mHostPort,
                                                     video_name));
    //connect()
    mState = RECEIVING_VIDEO;
}


void  FileTransferManager::fetchVideoInfoFromServer(QString video_name)
{

    checkConnectionReady();

    // Create JSON Objects for encoding to string message
    QJsonDocument doc;
    QJsonArray    array;
    QJsonObject   funcname;

    // Add Function name
    funcname["FuncName"] = QJsonValue::fromVariant(QVariant::fromValue(QString("VideoInfo")));
    array.append(funcname);

    // Add Video Name Parameter
    QJsonObject max_return;
    max_return["VideoName"] = QJsonValue::fromVariant(QVariant::fromValue(video_name));
    array.append(max_return);

    // set the documents internal (shared memory) array
    doc.setArray(array);

    // Begin the message (start byte)
    QByteArray message("\001");
    // append the JSON body
    message.append(doc.toJson());
    // append Finished signal
    message.append("\004");// (stop byte)

    // Write the messge to the socket and wait for the bytes to be written
    mSocket.write(message);
    mSocket.waitForBytesWritten(3000);

    // Update the current state
    mState = RECEIVING_INFO;
}


void FileTransferManager::processMessage()
{

    switch(mState)
    {
        case IDLE: {break;}
        case CONNECTED: {break;}
        case RECEIVING_LIST:
        {
         //  qDebug() << mMessageRecieved;

            // unpack the Video List
            QJsonDocument doc(QJsonDocument::fromJson(mMessageRecieved));

            QJsonObject json_object(doc.object());

            QJsonValue  json_value(json_object.value("VideoList"));
            // notify the (monitoring) Objects of video list's arrival
            emit videoListFetched(json_value.toVariant().toStringList());
            break;
        }
        case RECEIVING_INFO:
        {
            // What did we get? (UNCOMMENT FOR DEBUG)
            //qDebug() << mMessageRecieved;

            // Get Expected JSON Doc
            QJsonDocument doc(QJsonDocument::fromJson(mMessageRecieved));

            // unpack JSON Object
            QJsonObject object(doc.object());
            // Get the Video name and info
            QJsonValue  name(object["VideoName"]);
            QJsonValue  info(object["VideoInfo"]);

            //QVariant    varthumb(thumb.toVariant());
            //QByteArray ba(varthumb.toByteArray());
            //qDebug() << "        IMAGE            "<<  ba;
           /* QFile image(QDir::homePath()+"\\Videos\\thumbnail7.png");
            image.open(QFile::WriteOnly);
            image.write(ba);
            image.close();*/
            //QImageWriter  imwriter(QDir::homePath()+"\\Videos\\thumbnail7.png");
            //qDebug() << QDir::homePath()+"\\Videos\\thumbnail.png";
            //qDebug() << image;
            //imwriter.
            /*if(!imwriter.write(image))
            {
                qDebug() << "Failed to save thumbnail.";
            }
            else
            {
                qDebug() << "Saved the file off correctly";
            }*/

            // notify the listening objects that the video info was recieved
            // If the JSON Values are not strings they will instead return the error string
            emit recievedVideoInfo(name.toString("Name Not A String Error"),
                                   info.toString("Info Not A String Error") );
            break;
        }
        case RECEIVING_THUMBNAIL:{qDebug() << "Error? Should be in transfer thread...";break;}
        case RECEIVING_VIDEO: {qDebug() << "Error? Should be in transfer thread...";break;}
        case FINISHED_RECEIVING: {break;}
        default: {qDebug() << "Unknown Message " << mIncomingMessage; break;}
    }
    mState = IDLE;
}


void  FileTransferManager::readData()
{
    mIncomingMessage.append(mSocket.readAll());
    int index(-1);
    if( index = mIncomingMessage.lastIndexOf("\004"))
    {
        mMessageRecieved.clear();
        mMessageRecieved.append(mIncomingMessage.left(index+1),index+1);
       // qDebug() << "Message Recieved: " << mMessageRecieved;
        mMessageRecieved.remove(0,1);
        mMessageRecieved.chop(1);
        processMessage();
        mIncomingMessage.remove(0,index+1);
        mMessageRecieved.clear();
    }

}


void FileTransferManager::readFinishing()
{
    // channel or socket is closing
    mIncomingMessage.append(mSocket.readAll());
    mMessageRecieved = mIncomingMessage;
    mIncomingMessage.clear();
    processMessage();
}




void FileTransferManager::videoDownloadFinished(QString name)
{
        //Clean up and exit the VideoWriter Thread
    emit downloadFinished(name);
}

FileTransferManager::~FileTransferManager()
{
    mSocket.flush();
    mSocket.disconnectFromHost();
    mSocket.close();
    mHostInfo = QHostInfo();
    mHostPort = 0;
    mState = IDLE;
    mTransferItemName.clear();
    mVideoDirectory.clear();
    mMessageRecieved.clear();
    mIncomingMessage.clear();
}

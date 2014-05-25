#include "videowritethread.h"
#include "Tier3_Persistence/videowriter.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QTimer>
VideoWriteThread::VideoWriteThread(QObject * parent,QHostAddress address, int port, QString filename, qint64 expected_size) :
    QThread(parent), mHostAddress(address), mHostPort(port), mFileName(filename), mExpectedSize(expected_size)
{

}


void VideoWriteThread::run()
{

    // initialize objects for file transfer
    QTcpSocket hostconnection;
    hostconnection.connectToHost(mHostAddress,mHostPort);
    hostconnection.waitForConnected();
    // CREATE the Video Transfer request from the server
    QJsonObject   vid_req_obj;
    vid_req_obj["FuncName"] = QString("VideoTransfer");
    vid_req_obj["VideoName"] = mFileName;
    QByteArray  messageout("\001");
    QJsonDocument doc;
    doc.setObject(vid_req_obj);
    messageout.append(doc.toJson());
    messageout.append("\004");
    VideoWriter videowriter(qobject_cast<VideoTransferManager*>(parent()), mFileName, hostconnection, mExpectedSize);
    connect(&videowriter,SIGNAL(fileTransferComplete()),this,SLOT(quit()));
    int data_wrote(hostconnection.write(messageout.data(),messageout.size()));

    // make signal and slot connections for objecs

    // begin event loop

    exec();
}

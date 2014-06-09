#include "filewritethread.h"

#include "Tier3_Persistence/filewriter.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QTimer>

class FileTransferManager;

FileWriteThread::FileWriteThread(QObject * parent, QHostAddress address, int port, QString filename) :
    QThread(parent), mHostAddress(address), mHostPort(port), mFileName(filename)
{

}


void FileWriteThread::run()
{

    // initialize objects for file transfer
    QTcpSocket hostconnection;
    hostconnection.connectToHost(mHostAddress,mHostPort);
    hostconnection.waitForConnected();
    // CREATE the Video Transfer request from the server
    QJsonObject   vid_req_obj;
    vid_req_obj["FuncName"] = QString("FileTransfer");
    vid_req_obj["FileName"] = mFileName;
    QByteArray  messageout("\001");
    QJsonDocument doc;
    doc.setObject(vid_req_obj);
    messageout.append(doc.toJson());
    messageout.append("\004");
    FileWriter filewriter(qobject_cast<FileTransferManager*>(parent()), mFileName, hostconnection);
    connect(&filewriter,SIGNAL(fileTransferComplete()),this,SLOT(quit()));
    int data_wrote(hostconnection.write(messageout.data(),messageout.size()));

    // begin event loop

    exec();
}

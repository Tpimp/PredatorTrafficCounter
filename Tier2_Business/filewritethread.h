#ifndef FILEWRITETHREAD_H
#define FILEWRITETHREAD_H
#include <QThread>
#include <QHostAddress>
#include <QByteArray>
#include <QString>

class FileWriteThread : public QThread
{
    Q_OBJECT
public:

    explicit FileWriteThread(QObject *parent, QHostAddress address, int port, QString filename);
    void run();

signals:
    void finishedTransferingFile(QString name);

public slots:


private:
    QHostAddress mHostAddress;
    int          mHostPort;
    QString      mFileName;
    qint64       mExpectedSize;
};

#endif // VIDEOWRITETHREAD_H

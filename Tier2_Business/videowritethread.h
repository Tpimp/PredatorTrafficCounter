#ifndef VIDEOWRITETHREAD_H
#define VIDEOWRITETHREAD_H
#include <QThread>
#include <QHostAddress>
#include <QByteArray>
#include <QString>

class VideoWriteThread : public QThread
{
    Q_OBJECT
public:

    explicit VideoWriteThread(QObject *parent, QHostAddress address, int port, QString filename,qint64 expected_size);
    void run();

signals:
    void finishedTransferingVideo(QString name);

public slots:


private:
    QHostAddress mHostAddress;
    int          mHostPort;
    QString      mFileName;
    qint64       mExpectedSize;
};

#endif // VIDEOWRITETHREAD_H

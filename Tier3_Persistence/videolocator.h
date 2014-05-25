#ifndef VIDEOLOCATOR_H
#define VIDEOLOCATOR_H

#include <QObject>
#include <QStringList>
class VideoLocator : public QObject
{
    Q_OBJECT
public:
    static QStringList findVideos(QString directory);

signals:

public slots:

    
private: 
    explicit VideoLocator(QObject *parent = 0);
    
};

#endif // VIDEOLOCATOR_H

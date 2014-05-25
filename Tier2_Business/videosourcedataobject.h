#ifndef VIDEOSOURCEDATAOBJECT_H
#define VIDEOSOURCEDATAOBJECT_H

#include <QObject>
#include <QTime>
class VideoSourceDataObject : public QObject
{
    Q_OBJECT
    
    // Define the data members for QML interface (Class Properties)
    Q_PROPERTY(QString videoname READ videoName WRITE setVideoName)
    Q_PROPERTY(bool    local     READ isLocal   WRITE setLocal)
    Q_PROPERTY(bool    servable  READ onServer  WRITE setOnServer)
    Q_PROPERTY(QString videoinfo READ videoInfo WRITE setVideoInfo)
    Q_PROPERTY(bool    downloading READ isDownloading
               WRITE setDownloading NOTIFY startedDownloading)
    Q_PROPERTY(int     amountcomplete READ amountComplete
               WRITE setAmountComplete NOTIFY amountCompleteUpdated)
    
public:
    // define class CTORs
    VideoSourceDataObject(QString vidname, QObject *parent = 0);
    VideoSourceDataObject(const QString & vidname, const bool & local,
                          const bool & onserver, const QString & info,
                          const bool & downloading, const int & percentcomp, QObject * = nullptr);
    
    
    // define setters and getters
    
    //SETTERS
    void setVideoName(const QString & name);
    void setLocal(const bool & local);
    void setOnServer(const bool & servable);
    void setVideoInfo(const QString & info);
    void setDownloading(const bool downloading);
    void setAmountComplete(const int amountcomplete);

    //GETTERS
    QString videoName();
    bool    isLocal();
    bool    onServer();
    QString videoInfo();
    bool    isDownloading();
    int     amountComplete();

    // String version of getters
    QString  getInfoString(QString info_name);

    // String Parse getters
    qint64 getFileSize();
    QTime  getDuration();
    QSize  getResolution();

signals:
    // Callback signals
    void startedDownloading();
    void amountCompleteUpdated();

private:
    // Declare member variables and their default values
    QString mVideoName = "";
    bool mLocal = false;
    bool mOnServer = false;
    QString mVideoInfo = "";
    bool mDownloading = false;
    int  mPercentComplete = 0;

};

#endif // VIDEOSOURCEDATAOBJECT_H

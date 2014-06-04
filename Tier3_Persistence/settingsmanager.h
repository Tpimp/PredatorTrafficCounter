#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include <QObject>
#include <QSize>

class SettingsManager : public QObject
{
    Q_OBJECT
    // declare properties for exposure to QML
    Q_PROPERTY(QString video_directory READ videoDirectory WRITE setVideoDirectory NOTIFY videoDirectoryChanged)
    Q_PROPERTY(bool size_override READ windowSizeOverride WRITE setWindowSizeOverRide NOTIFY windowSizeOverRideChanged)
    Q_PROPERTY(int window_width READ windowWidth WRITE setWindowWidth NOTIFY windowWidthChanged)
    Q_PROPERTY(int window_height READ windowHeight WRITE setWindowHeight NOTIFY windowHeightChanged)
    //Q_PROPERTY(bool droneDiscovery READ windowHeight WRITE setWindowHeight NOTIFY windowHeightChanged)
    Q_PROPERTY(QString last_connected READ lastConnectedIp WRITE setLastConnectedIp NOTIFY lastConnectedIpChanged)
    Q_PROPERTY(QString drone_list READ knownDroneList WRITE setKnownDroneList NOTIFY knownDroneListChanged)
public:
    // CTOR
    explicit SettingsManager(QObject *parent = 0, QString video_directory = "", bool size_override = false,
                             int window_width = 0, int window_height = 0, QString last_connected = "", QString drone_list = "" );
    // DTOR
    ~SettingsManager();
    // getters
    QString videoDirectory(){ return mVideoDirectory;}
    bool windowSizeOverride(){ return mWindowSizeOverRide;}
    int windowWidth(){ return mWindowWidth;}
    int windowHeight(){ return mWindowHeight;}
    //bool droneDiscovery(){ return mDroneDiscovery;}
    QString lastConnectedIp(){ return mLastConnectedIp;}
    QString knownDroneList() { return mKnownDroneList;}

    // File Read and Write methods
    void readSettingIntoMemory(const QString& filename);
    void saveSettingsToFile(const QString& filename);

public slots:
    // setters
    void setVideoDirectory(const QString& video_directory){ mVideoDirectory = video_directory;}
    void setWindowSizeOverRide(const bool& size_override){ mWindowSizeOverRide = size_override;}
    void setWindowHeight(const int& window_height){ mWindowHeight = window_height;}
    void setWindowWidth(const int& window_width){ mWindowWidth = window_width;}
    void setLastConnectedIp(const QString& last_connected){ mLastConnectedIp = last_connected;}
    void setDroneDiscovery( const bool& drone_discovery ){ mDroneDiscovery = drone_discovery;}
    void setKnownDroneList(const  QString& drone_list){ mKnownDroneList = drone_list;}

signals:
    void videoDirectoryChanged();
    void windowSizeOverRideChanged();
    void windowWidthChanged();
    void windowHeightChanged();
    void lastConnectedIpChanged();
    void knownDroneListChanged();

private:
    QString  mVideoDirectory;
    bool     mWindowSizeOverRide;
    int      mWindowHeight;
    int      mWindowWidth;
    QString  mLastConnectedIp;
    bool     mDroneDiscovery;
    QString  mKnownDroneList;

};

#endif // SETTINGSMANAGER_H

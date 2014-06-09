#include <QtGui/QScreen>
#include <QtGui/QGuiApplication>
#include <QQmlContext>
#include <QQmlComponent>
#include <QScreen>
#include <QObject>
#include "Tier2_Business/videomanager.h"
#include "Tier2_Business/filetransfermanager.h"
#include <QDir>
#include <QObject>
#include <QQmlApplicationEngine>
#include "Tier3_Persistence/settingsmanager.h"
#include "Tier2_Business/dronemanager.h"
int main(int argc, char *argv[])
{
  //  QApplication app(argc, argv);

    QGuiApplication app(argc, argv);
    QScreen * pscreen = app.primaryScreen();
    QQmlApplicationEngine engine;
    int  screen_width;
    int  screen_height;
    bool show_expanded(true);
    QString display_mode("FullScreen");


    show_expanded = false; // Uncomment for FULLSCREEN

    if(!show_expanded)
    {
        screen_width = pscreen->size().width();
        screen_height = pscreen->size().height();
    }
    else
    {
        screen_width = pscreen->availableGeometry().width();
        screen_height = pscreen->availableGeometry().height();
        display_mode = "Maximized";
    }
    int temp_width(screen_width);
    if(screen_height > screen_width)
    {
        screen_width = screen_height;
        screen_height = temp_width;
    }

    //Create the VideoManager classes
    QString vid_directory(QDir::homePath() +  "\\Videos"); // to be re-implemented as Application Settings

    FileTransferManager video_transfer_manager(&app);
    SettingsManager      settings_manager(&app);
    QString application_directory_path;

    // GET THE different locations to save the file for each platform

    // TODO: find a better method of asking the user where to store their settings
    #if defined(Q_OS_ANDROID)
        application_directory_path = (QDir::rootPath()+"sdcard//" + "com.predator.trafficcounter/");
    #elif defined(Q_OS_WIN)
        QDir directory_config(app.applicationDirPath());
        directory_config.cdUp();
        application_directory_path = (directory_config.path() + "\\");
    #elif defined(Q_OS_LINUX)
        application_directory_path = (QDir::homePath() + "/.")
    #else
        #  error "Unknown System Type"        qError() << "Unknown System type";
    #endif



    //directory.cdUp();
    QString config_dir(application_directory_path+"config" + QDir::separator().toLatin1());
    QString settings_file_location(config_dir + "predator_config.cfg");
    qDebug() << settings_file_location;
    settings_manager.readSettingIntoMemory(settings_file_location);
    //settings_manager.setWindowSizeOverRide(true);
    //settings_manager.saveSettingsToFile(settings_file_location);

    VideoManager  video_manager(vid_directory,engine.rootContext(), &video_transfer_manager, &app ); // video manager will be alive the life of the program
    // Connect their signal and slots
    QObject::connect(&video_transfer_manager, &FileTransferManager::videoListFetched, &video_manager, &VideoManager::addVideosFromServer);
    QObject::connect(&video_transfer_manager, &FileTransferManager::recievedVideoInfo, &video_manager, &VideoManager::updateVideoInfo);
    DroneManager drone_manager(engine.rootContext(),&app);
    QString drone_file_location(config_dir  + "KnownDrones.txt");
    drone_manager.readKnownDroneList(drone_file_location);
    // add the VideoTransferManager and VideoManagers tothe root object

    // add external variable references to QMLEngine
    engine.rootContext()->setContextProperty("ScreenWidth",screen_width);
    engine.rootContext()->setContextProperty("ScreenHeight",screen_height);
    engine.rootContext()->setContextProperty("DisplayMode",display_mode);
    engine.rootContext()->setContextProperty("VideoTransferManager",&video_transfer_manager);
    engine.rootContext()->setContextProperty("VideoManager",&video_manager);
    engine.rootContext()->setContextProperty("SettingsManager",&settings_manager);


    engine.load(QUrl(QString(R"(qrc:/main.qml)")));

    return app.exec();
}

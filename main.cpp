#include <QtGui/QScreen>
#include <QtGui/QGuiApplication>
#include <QQmlContext>
#include <QQmlEngine>
#include <QQmlComponent>
#include <QScreen>
#include <QQmlApplicationEngine>
#include <QObject>
#include "Tier2_Business/videomanager.h"
#include "Tier2_Business/videotransfermanager.h"
#include <QDir>
#include <QObject>

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
    VideoManager  video_manager(vid_directory, &app ); // video manager will be alive the life of the program
    VideoTransferManager video_transfer_manager(&app);

    // Connect their signal and slots
    QObject::connect(&video_transfer_manager, &VideoTransferManager::videoListFetched, &video_manager, &VideoManager::addVideosFromServer);
    QObject::connect(&video_transfer_manager, &VideoTransferManager::recievedVideoInfo, &video_manager, &VideoManager::updateVideoInfo);

    // add the VideoTransferManager and VideoManagers tothe root object



    // add external variable references to QMLEngine
    engine.rootContext()->setContextProperty("ScreenWidth",screen_width);
    engine.rootContext()->setContextProperty("ScreenHeight",screen_height);
    engine.rootContext()->setContextProperty("DisplayMode",display_mode);
    engine.rootContext()->setContextProperty("VideoTransferManager",&video_transfer_manager);
    engine.rootContext()->setContextProperty("VideoManager",&video_manager);


    engine.load(QUrl(QString(R"(qrc:/main.qml)")));

    return app.exec();
}

#include <QtGui/QScreen>
#include <QtGui/QGuiApplication>
#include <QQmlContext>
#include <QQmlEngine>
#include <QQmlComponent>
#include <QScreen>
#include <QQmlApplicationEngine>
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

    // add external variable references to QMLEngine
    engine.rootContext()->setContextProperty("ScreenWidth",screen_width);
    engine.rootContext()->setContextProperty("ScreenHeight",screen_height);
    engine.rootContext()->setContextProperty("DisplayMode",display_mode);

    engine.load(QUrl(QString(R"(qrc:/main.qml)")));

    return app.exec();
}

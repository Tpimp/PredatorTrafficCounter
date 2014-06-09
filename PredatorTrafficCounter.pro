TEMPLATE = app

QT += qml quick widgets sql



SOURCES += main.cpp \
    Tier2_Business/videomanager.cpp \
    Tier2_Business/videosourcedataobject.cpp \
    Tier3_Persistence/videoinforeader.cpp \
    Tier3_Persistence/videolocator.cpp \
    Tier3_Persistence/settingsmanager.cpp \
    Tier2_Business/dronemanager.cpp \
    Tier2_Business/filetransfermanager.cpp \
    Tier2_Business/filewritethread.cpp \
    Tier3_Persistence/filewriter.cpp \
    Tier2_Business/bicycledataobject.cpp \
    Tier2_Business/vehicledataobject.cpp \
    Tier2_Business/dronedataobject.cpp \
    Tier3_Persistence/databasemanager.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH = qml

# Default rules for deployment.
include(deployment.pri)

OTHER_FILES += \
    qml/main.qml \
    qml/ConnectView.qml \
    qml/TrafficCountView.qml \
    qml/DroneItem.qml \
    android/AndroidManifest.xml \
    qml/SettingsView.qml

CONFIG += C++11

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

folder_01.source = config
folder_01.target = config
DEPLOYMENTFOLDERS += folder_01

HEADERS += \
    Tier2_Business/videomanager.h \
    Tier2_Business/videosourcedataobject.h \
    Tier3_Persistence/videoinforeader.h \
    Tier3_Persistence/videolocator.h \
    Tier3_Persistence/settingsmanager.h \
    Tier2_Business/dronemanager.h \
    Tier2_Business/filetransfermanager.h \
    Tier2_Business/filewritethread.h \
    Tier3_Persistence/filewriter.h \
    Tier2_Business/bicycledataobject.h \
    Tier2_Business/vehicledataobject.h \
    Tier2_Business/dronedataobject.h \
    Tier3_Persistence/DatabaseDefinition.h \
    Tier3_Persistence/databasemanager.h


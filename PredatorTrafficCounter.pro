TEMPLATE = app

QT += qml quick widgets

SOURCES += main.cpp \
    Tier2_Business/videomanager.cpp \
    Tier2_Business/videosourcedataobject.cpp \
    Tier2_Business/videotransfermanager.cpp \
    Tier2_Business/videowritethread.cpp \
    Tier3_Persistence/videoinforeader.cpp \
    Tier3_Persistence/videolocator.cpp \
    Tier3_Persistence/videowriter.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

OTHER_FILES += \
    qml/main.qml \
    qml/ConnectView.qml

CONFIG += C++11

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

HEADERS += \
    Tier2_Business/videomanager.h \
    Tier2_Business/videosourcedataobject.h \
    Tier2_Business/videotransfermanager.h \
    Tier2_Business/videowritethread.h \
    Tier3_Persistence/videoinforeader.h \
    Tier3_Persistence/videolocator.h \
    Tier3_Persistence/videowriter.h

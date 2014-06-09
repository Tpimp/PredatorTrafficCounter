#include "settingsmanager.h"
#include <QFile>
#include <QDir>
#include <QStringList>
#include <QRegularExpression>
#include <QDebug>
SettingsManager::SettingsManager(QObject *parent, QString video_directory,
                                 bool size_override, int window_width, int window_height,
                                 QString last_connected, QString drone_list)
    :QObject(parent),
     mVideoDirectory(video_directory),
     mWindowSizeOverRide(size_override),
     mWindowWidth(window_width),
     mWindowHeight(window_height),
     mLastConnectedIp(last_connected),
     mKnownDroneList(drone_list)
{}


void SettingsManager::readSettingIntoMemory(const QString& filename)
{
    QFile settings_file(filename);
    QStringList settings_in_file;
    //qDebug() << filename;
    if(settings_file.exists())
    {
        settings_file.open(QFile::ReadOnly);
        QString file_data(settings_file.readAll());
        settings_file.close();
        QStringList lines_in_file(file_data.split("\r\n"));
        //qDebug() << lines_in_file;
        foreach(QString line, lines_in_file)
        {
            if(line.contains('='))
            {
                settings_in_file.append(line);
            }
        }
    }
    else
    {
        saveSettingsToFile(filename);
    }
    //qDebug() << settings_in_file;
    // if found settings, parse them
    if(settings_in_file.size() > 0)
    {
        foreach(QString setting_string, settings_in_file)
        {
            // get the name (first space)
            int name_end_index = setting_string.indexOf(" ");
            QString setting_name(setting_string.left(name_end_index));
            setting_string.remove(0, name_end_index+2).replace("\"","");
            QString setting_value(setting_string);
            // find which setting was read and input the value
            switch(setting_name.at(0).toLatin1())
            {
                case 'H':
                {
                    mWindowHeight = setting_value.toInt();
                    break;
                }
                case 'K':
                {
                    mKnownDroneList =  setting_value.remove(0,1);
                    break;
                }
                case 'L':
                {
                    mLastConnectedIp = setting_value.remove(0,1);
                    break;
                }
                case 'W':
                {
                    switch(setting_name.at(3).toLatin1())
                    {
                        case 'd':
                        {
                            mWindowWidth = setting_value.toInt();
                            break;
                        }
                        case 'n':
                        {
                            mWindowSizeOverRide = bool(setting_value.toInt());
                            break;
                        }
                         default: break;
                    }
                    break;
                }
                case 'V':
                {
                    mVideoDirectory = setting_value.remove(0,1);
                    break;
                }

            }
        }
    }


}

void SettingsManager::saveSettingsToFile(const QString& filename)
{
    QFile settings_file(filename);

    QDir config_dir(filename);
    if(!config_dir.exists(config_dir.absoluteFilePath(filename)))
    {
        QString abs_path(config_dir.absoluteFilePath(filename));
        int index_last_dir = abs_path.lastIndexOf(QDir::separator());
        abs_path = abs_path.remove(index_last_dir,abs_path.size()-1);
        qDebug() <<"Creating path: " << abs_path;
        config_dir.mkpath(abs_path);
    }

    settings_file.open(QFile::WriteOnly);

    // write the header
    QString settings_header = "## Comments are ignored - Use Double # for a comment\r\n"
                              "## White space is also ignored (BLANK LINES) - "
                              "File cannot be repaired from manual corruption.\r\n"
                              "## Suggestions is to leave this file alone. "
                              "Edit settings through the GUI\r\n"
                              "## Client application Settings -\r\n";
    settings_file.write(settings_header.toLocal8Bit());

    // write the application settings
    settings_file.write(QString("VideoDirectory = \"" + mVideoDirectory + "\"\r\n").toLocal8Bit());
    settings_file.write(QString("WindowSizeOverRide = " + QString::number(int(mWindowSizeOverRide)) + "\r\n").toLocal8Bit());
    settings_file.write(QString("Height = " + QString::number(mWindowHeight) + "\r\n").toLocal8Bit());
    settings_file.write(QString("Width = " + QString::number(mWindowWidth) + "\r\n\r\n").toLocal8Bit());
    settings_file.write(QString("## Store Quad-Copter Specific settings\r\n").toLocal8Bit());
    settings_file.write(QString("LastConnectedIP = \"" + mLastConnectedIp + "\"\r\n").toLocal8Bit());
    settings_file.write(QString("KnownDroneList = \"" + mKnownDroneList + "\"\r\n").toLocal8Bit());
    settings_file.close();
}


SettingsManager::~SettingsManager()
{

}

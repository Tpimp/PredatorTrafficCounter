#include "dronemanager.h"
#include <QFile>
#include "Tier2_Business/dronedataobject.h"
#include <QStringList>
#include <QDebug>
#include <QVariant>
#include <QDir>

DroneManager::DroneManager(QQmlContext * context, QObject *parent) :
    QObject(parent), mContext(context)
{
}


void DroneManager::createKnownDroneList(QString filename)
{

    qDebug() << "Create Known DroneList file -> " << filename;

    QFile file(filename);

    if(!file.exists())
    {
        qDebug() << "Did not find file " << filename;
        saveKnownDroneList(filename);
    }
    else
    {
        qDebug() << "Did find file" << filename << "!";
    }
}


void DroneManager::readKnownDroneList(QString filename)
{
    QFile known_drone_list(filename);
    if(!known_drone_list.exists())
        createKnownDroneList(filename);
    QString file_contents;
    known_drone_list.open(QFile::ReadOnly);
    file_contents.append(known_drone_list.readAll());
    QStringList  all_lines(file_contents.split("\r\n"));
    QStringList  variable_lines;
    known_drone_list.close();
    foreach(QString line,all_lines)
    {
        if(!line.startsWith("##") && line.contains("="))
        {
            variable_lines.append(line);
        }
    }
    DroneDataObject * object;
    foreach( QString variable, variable_lines)
    {
        if(variable.size() < 8)
            continue;
        int name_end_index = variable.indexOf("=");
        QString variable_name(variable.left(name_end_index-1));
        variable.remove(0, name_end_index+2).replace("\"","");
        QString setting_value(variable);

        switch(variable_name.at(6).toLatin1())
        {
            case 'N':
            {
                object = new DroneDataObject(this,setting_value);
                break;
            }
            case 'O':
            {
                object->setDroneOwner(setting_value);
                break;
            }
            case 'I':
            {
                object->setDroneIP(setting_value);
                break;
            }
            case 'T':
            {
                object->setDroneType(setting_value);
                mDroneList.append(object);
                break;
            }
            default:
            {
                qDebug() << "Error Bad Variable recieved in drone manager from " << filename
                         << "\n" << variable;
                break;
            }
        }
    }

    mContext->setContextProperty("knownDrones", QVariant::fromValue(mDroneList));
}


void DroneManager::saveKnownDroneList(QString filename)
{
    QString header("## Comments are ignored - Use Double # for a comment\r\n"
                   "## White space is also ignored (BLANK LINES) - File cannot be repaired from manual corruption.\r\n"
                   "## Suggestions is to leave this file alone. Edit settings through the GUI\r\n"
                   "## Known Drones\r\n\r\n"
                   "## Drone Definition Prototype\r\n"
                   "## Drone Name = \"Name\"\r\n"
                   "## Drone Owner = \"Owners Name\"\r\n"
                   "## Drone IP    = \"ipip.ipip.ip.ip\"\r\n"
                   "## Drone Type = \"DroneType\"\r\n\r\n");
    QFile known_drone_list(filename);
    known_drone_list.open(QFile::WriteOnly);
    known_drone_list.write(header.toLocal8Bit());

    foreach( QObject* drone, mDroneList)
    {
        DroneDataObject * drone_ptr(reinterpret_cast<DroneDataObject *>(drone));
        known_drone_list.write(QString("Drone Name = \"" + drone_ptr->droneName() + "\"\r\n").toLocal8Bit());
        known_drone_list.write(QString("Drone Owner = \"" + drone_ptr->droneOwner()+ "\"\r\n").toLocal8Bit());
        known_drone_list.write(QString("Drone IP = \"" + drone_ptr->droneIP()+ "\"\r\n").toLocal8Bit());
        known_drone_list.write(QString("Drone Type = \"" + drone_ptr->droneType()+ "\"\r\n\r\n").toLocal8Bit());
    }
    known_drone_list.close();
}


DroneManager::~DroneManager()
{
    while(!mDroneList.isEmpty())
    {
        DroneDataObject* drone_ptr(reinterpret_cast<DroneDataObject *>(mDroneList.takeLast()));
        delete drone_ptr;
    }

}

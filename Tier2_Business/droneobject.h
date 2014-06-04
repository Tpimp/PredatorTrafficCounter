#ifndef DRONEOBJECT_H
#define DRONEOBJECT_H

#include <QObject>

class DroneObject : public QObject
{
    Q_OBJECT
    // declare properties for exposure to QML
    Q_PROPERTY(QString drone_name READ droneName WRITE setDroneName NOTIFY droneNameChanged)
    Q_PROPERTY(QString drone_owner READ droneOwner WRITE setDroneOwner NOTIFY droneOwnerChanged)
    Q_PROPERTY(QString drone_ip READ droneIP WRITE setDroneIP NOTIFY droneIPChanged)
    Q_PROPERTY(QString drone_type READ droneType WRITE setDroneType NOTIFY droneTypeChanged)

public: 
    explicit DroneObject(QObject *parent = 0, QString drone_name = "", QString drone_owner = "",
                          QString drone_ip = "", QString drone_type = "" );

    // Drone Set Methods
    void setDroneName(QString drone_name){mDroneName = drone_name;}
    void setDroneOwner(QString drone_owner){ mOwnerName = drone_owner;}
    void setDroneIP(QString drone_ip){ mDroneIp = drone_ip;}
    void setDroneType(QString drone_type){ mDroneType = drone_type;}

    // Drone Getter Methods
    QString droneName(){ return mDroneName;}
    QString droneOwner(){ return mOwnerName;}
    QString droneIP(){ return mDroneIp;}
    QString droneType(){ return mDroneType;}


signals:

    // Signals for values changed
    void droneNameChanged();
    void droneOwnerChanged();
    void droneTypeChanged();
    void droneIPChanged();



private:

    QString   mDroneName;
    QString   mOwnerName;
    QString   mDroneIp;
    QString   mDroneType;
};

#endif // DRONEOBJECT_H

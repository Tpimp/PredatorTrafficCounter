#include "dronedataobject.h"

DroneDataObject::DroneDataObject(QObject *parent, QString drone_name, QString drone_owner,
                         QString drone_ip,QString drone_type ) :
    QObject(parent),
    mDroneName(drone_name),
    mOwnerName(drone_owner),
    mDroneIp(drone_ip),
    mDroneType(drone_type)
{}

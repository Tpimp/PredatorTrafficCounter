#ifndef DRONEMANAGER_H
#define DRONEMANAGER_H

#include <QObject>
#include <QList>
#include <QQmlContext>
class DroneManager : public QObject
{
    Q_OBJECT
public:
    explicit DroneManager(QQmlContext * context,QObject *parent = 0 );
    void createKnownDroneList(QString filename);
    void readKnownDroneList(QString filename);
    void saveKnownDroneList(QString filename);
    QList<QObject *> getDroneList(){ return mDroneList; }
    void setDroneList(QList<QObject *> drone_list) { mDroneList = drone_list;}
    ~DroneManager();

private:
    QList<QObject *>  mDroneList;
    QQmlContext *     mContext;
};

#endif // DRONEMANAGER_H

#ifndef BICYCLEDATAOBJECT_H
#define BICYCLEDATAOBJECT_H

#include <QObject>

class BicycleDataObject : public QObject
{
    Q_OBJECT
    // declare properties for exposure to QML
    Q_PROPERTY(int bike_id READ bikeID WRITE setBikeID NOTIFY bikeIDChanged)
    Q_PROPERTY(int bike_count_north READ northCount WRITE setNorthCount NOTIFY northCountChanged)
    Q_PROPERTY(int bike_count_south READ southCount WRITE setSouthCount NOTIFY southCountChanged)
    Q_PROPERTY(int bike_count_west READ westCount WRITE setWestCount NOTIFY westCountChanged)
    Q_PROPERTY(int bike_count_east READ eastCount WRITE setEastCount NOTIFY eastCountChanged)

public:

    explicit BicycleDataObject(QObject *parent = 0,int id = 0, int north_count = 0, int south_count = 0,
                               int west_count = 0, int east_count = 0);
    ~BicycleDataObject();

    //getters
    int bikeID(){return mBicycleID;}
    int northCount(){return mNorthCount;}
    int southCount(){return mSouthCount;}
    int westCount() {return mWestCount;}
    int eastCount() {return mEastCount;}


    // setters
    void setBikeID(int bikeid){ mBicycleID = bikeid;}
    void setNorthCount(int north_count){ mNorthCount = north_count;}
    void setSouthCount(int south_count){ mSouthCount = south_count;}
    void setWestCount(int west_count){ mWestCount = west_count;}
    void setEastCount(int east_count){ mEastCount = east_count;}


signals:
    void bikeIDChanged(int bikeid);
    void northCountChanged(int north_count);
    void southCountChanged(int south_count);
    void westCountChanged(int west_count);
    void eastCountChanged(int east_count);



private:

    int   mBicycleID;
    int   mNorthCount;
    int   mSouthCount;
    int   mWestCount;
    int   mEastCount;
};

#endif // BICYCLEDATAOBJECT_H

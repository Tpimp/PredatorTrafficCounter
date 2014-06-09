#ifndef VEHICLEDATAOBJECT_H
#define VEHICLEDATAOBJECT_H

#include <QObject>

class VehicleDataObject : public QObject
{
    Q_OBJECT
    // declare properties for exposure to QML
    Q_PROPERTY(int vehicle_id READ vehicleID WRITE setVehicleID NOTIFY vehicleIDChanged)

    // NORTH PROPERTIES
    Q_PROPERTY(int north_count_left READ northCountLeft
               WRITE setNorthCountLeft NOTIFY northCountLeftChanged)

    Q_PROPERTY(int north_count_straight READ northCountStraight
               WRITE setNorthCountStraight NOTIFY northCountStraightChanged)

    Q_PROPERTY(int north_count_right READ northCountRight
               WRITE setNorthCountRight NOTIFY northCountRightChanged)

    Q_PROPERTY(int north_count_uturn READ northCountUTurn
               WRITE setNorthCountUTurn NOTIFY northCountUTurnChanged)

    // SOUTH PROPERTIES
    Q_PROPERTY(int south_count_left READ southCountLeft
               WRITE setSouthCountLeft NOTIFY southCountLeftChanged)

    Q_PROPERTY(int south_count_straight READ southCountStraight
               WRITE setSouthCountStraight NOTIFY southCountStraightChanged)

    Q_PROPERTY(int south_count_right READ southCountRight
               WRITE setSouthCountRight NOTIFY southCountRightChanged)

    Q_PROPERTY(int south_count_uturn READ southCountUTurn
               WRITE setSouthCountUTurn NOTIFY southCountUTurnChanged)

    // WEST PROPERTIES
    Q_PROPERTY(int west_count_left READ westCountLeft
               WRITE setWestCountLeft NOTIFY westCountLeftChanged)
    Q_PROPERTY(int west_count_straight READ westCountStraight
               WRITE setWestCountStraight NOTIFY westCountStraightChanged)
    Q_PROPERTY(int west_count_right READ westCountRight WRITE
               setWestCountRight NOTIFY westCountRightChanged)
    Q_PROPERTY(int west_count_uturn READ westCountUTurn WRITE
               setWestCountUTurn NOTIFY westCountUTurnChanged)

    // EAST PROPERTIES
    Q_PROPERTY(int east_count_left READ eastCountLeft WRITE
               setEastCountLeft NOTIFY eastCountLeftChanged)
    Q_PROPERTY(int east_count_straight READ eastCountStraight WRITE
               setEastCountStraight NOTIFY eastCountStraightChanged)
    Q_PROPERTY(int east_count_right READ eastCountRight WRITE
               setEastCountRight NOTIFY eastCountRightChanged)
    Q_PROPERTY(int east_count_uturn READ eastCountUTurn WRITE
               setEastCountUTurn NOTIFY eastCountUTurnChanged)
public:
    explicit VehicleDataObject(QObject *parent = 0,int id = 0,
                               int north_count_left = 0,int north_count_straight = 0,
                               int north_count_right = 0, int north_count_uturn = 0,
                               int south_count_left = 0,int south_count_straight = 0,
                               int south_count_right = 0, int south_count_uturn = 0,
                               int west_count_left = 0,int west_count_straight = 0,
                               int west_count_right = 0, int west_count_uturn = 0,
                               int east_count_left = 0,int east_count_straight = 0,
                               int east_count_right = 0, int east_count_uturn = 0);
    ~VehicleDataObject();

    //getters
    int vehicleID(){return mVehicleID;}
    int northCountLeft(){return mNorthLeft;}
    int northCountStraight(){return mNorthStraight;}
    int northCountRight(){return mNorthRight;}
    int northCountUTurn() {return mNorthUTurn;}

    int southCountLeft(){return mSouthLeft;}
    int southCountStraight(){return mSouthStraight;}
    int southCountRight(){return mSouthRight;}
    int southCountUTurn() {return mSouthUTurn;}

    int westCountLeft(){return mWestLeft;}
    int westCountStraight(){return mWestStraight;}
    int westCountRight(){return mWestRight;}
    int westCountUTurn() {return mWestUTurn;}

    int eastCountLeft(){return mEastLeft;}
    int eastCountStraight(){return mEastStraight;}
    int eastCountRight(){return mEastRight;}
    int eastCountUTurn() {return mEastUTurn;}


    // setters
    void setVehicleID(int vehicleid){ mVehicleID = vehicleid;}

    void setNorthCountLeft(int north_count_left){ mNorthLeft = north_count_left;}
    void setNorthCountStraight(int north_count_straight){ mNorthStraight = north_count_straight;}
    void setNorthCountRight(int north_count_right){ mNorthRight = north_count_right;}
    void setNorthCountUTurn(int north_count_uturn){ mNorthUTurn = north_count_uturn;}

    void setSouthCountLeft(int south_count_left){ mSouthLeft = south_count_left;}
    void setSouthCountStraight(int south_count_straight){ mSouthStraight = south_count_straight;}
    void setSouthCountRight(int south_count_right){ mSouthRight = south_count_right;}
    void setSouthCountUTurn(int south_count_uturn){ mSouthUTurn = south_count_uturn;}

    void setWestCountLeft(int west_count_left){ mWestLeft = west_count_left;}
    void setWestCountStraight(int west_count_straight){ mWestStraight = west_count_straight;}
    void setWestCountRight(int west_count_right){ mWestRight = west_count_right;}
    void setWestCountUTurn(int west_count_uturn){ mWestUTurn = west_count_uturn;}

    void setEastCountLeft(int east_count_left){ mEastLeft = east_count_left;}
    void setEastCountStraight(int east_count_straight){ mEastStraight = east_count_straight;}
    void setEastCountRight(int east_count_right){ mEastRight = east_count_right;}
    void setEastCountUTurn(int east_count_uturn){ mEastUTurn = east_count_uturn;}

signals:
    void vehicleIDChanged(int vehicleid);

    void northCountLeftChanged(int north_count_left);
    void northCountStraightChanged(int north_count_straight);
    void northCountRightChanged(int north_count_right);
    void northCountUTurnChanged(int north_count_uturn);

    void southCountLeftChanged(int south_count_left);
    void southCountStraightChanged(int south_count_straight);
    void southCountRightChanged(int south_count_right);
    void southCountUTurnChanged(int south_count_uturn);

    void westCountLeftChanged(int west_count_left);
    void westCountStraightChanged(int west_count_straight);
    void westCountRightChanged(int west_count_right);
    void westCountUTurnChanged(int west_count_uturn);

    void eastCountLeftChanged(int east_count_left);
    void eastCountStraightChanged(int east_count_straight);
    void eastCountRightChanged(int east_count_right);
    void eastCountUTurnChanged(int east_count_uturn);





private:

    int   mVehicleID;

    int   mNorthLeft;
    int   mNorthStraight;
    int   mNorthRight;
    int   mNorthUTurn;

    int   mSouthLeft;
    int   mSouthStraight;
    int   mSouthRight;
    int   mSouthUTurn;

    int   mWestLeft;
    int   mWestStraight;
    int   mWestRight;
    int   mWestUTurn;

    int   mEastLeft;
    int   mEastStraight;
    int   mEastRight;
    int   mEastUTurn;

};

#endif // VEHICLEDATAOBJECT_H

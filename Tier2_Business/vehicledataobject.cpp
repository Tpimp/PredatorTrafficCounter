#include "vehicledataobject.h"

VehicleDataObject::VehicleDataObject(QObject *parent, int id,
                                     int north_count_left,int north_count_straight,
                                     int north_count_right, int north_count_uturn,
                                     int south_count_left,int south_count_straight,
                                     int south_count_right, int south_count_uturn,
                                     int west_count_left,int west_count_straight,
                                     int west_count_right, int west_count_uturn,
                                     int east_count_left,int east_count_straight,
                                     int east_count_right, int east_count_uturn):
    QObject(parent),
    mVehicleID(id),
    mNorthLeft(north_count_left),
    mNorthStraight(north_count_straight),
    mNorthRight(north_count_right),
    mNorthUTurn(north_count_uturn),
    mSouthLeft(south_count_left),
    mSouthStraight(south_count_straight),
    mSouthRight(south_count_right),
    mSouthUTurn(south_count_uturn),
    mWestLeft(west_count_left),
    mWestStraight(west_count_straight),
    mWestRight(west_count_right),
    mWestUTurn(west_count_uturn),
    mEastLeft(east_count_left),
    mEastStraight(east_count_straight),
    mEastRight(east_count_right),
    mEastUTurn(east_count_uturn)
{}



VehicleDataObject::~VehicleDataObject()
{
    mVehicleID = 0;
    mNorthLeft = 0;
    mNorthStraight = 0;
    mNorthRight = 0;
    mNorthUTurn = 0;
    mSouthLeft = 0;
    mSouthStraight = 0;
    mSouthRight = 0;
    mSouthUTurn = 0;
    mWestLeft = 0;
    mWestStraight = 0;
    mWestRight = 0;
    mWestUTurn = 0;
    mEastLeft = 0;
    mEastStraight = 0;
    mEastRight = 0;
    mEastUTurn = 0;
}

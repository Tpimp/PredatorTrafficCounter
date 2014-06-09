#include "bicycledataobject.h"

// CTOR
BicycleDataObject::BicycleDataObject(QObject *parent, int id, int north_count, int south_count,
                                     int west_count, int east_count) :
    QObject(parent),  // INITIALIZE DATA MEMBERS
    mBicycleID(id),
    mNorthCount(north_count),
    mSouthCount(south_count),
    mWestCount(west_count),
    mEastCount(east_count)
{}

//DTOR
BicycleDataObject::~BicycleDataObject()
{
    // clear data
    mBicycleID = 0;
    mNorthCount = 0;
    mSouthCount = 0;
    mWestCount = 0;
    mEastCount = 0;
}

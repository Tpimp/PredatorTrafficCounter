#ifndef DATABASEDEFINITION_H
#define DATABASEDEFINITION_H

#include <QString>

/**********************************************************************************
* This file contains all statically defined string data related to the creation,
* manipulation, and general maintenance of the database - providing a central
* source for all database modifications
**********************************************************************************/

//const static QString DATABASE_NAME = "Traffic.db";
const static int DATABASE_VERSION = 3;

//Table Names
const static QString VEHICLES_TABLE = "Vehicles";
const static QString BICYCLES_TABLE = "Bicycles";
const static QString SESSIONS_TABLE = "Sessions";
const static QString VIDEOS_TABLE = "Videos";
const static QString INTERSECTIONS_TABLE = "Intersections";
const static QString PEDESTRIANS_TABLE = "Pedestrians";
const static QString USERS_TABLE = "Users";
const static QString BUTTON_MAPS_TABLE = "ButtonMaps";
//End Table Names

//**********************************************************************************
//**********************************************************************************
//Create Table Statements
//**********************************************************************************
const static QString VEHICLES_CREATE_TABLE = "CREATE TABLE IF NOT EXISTS Vehicles ("
        " VehicleID INTEGER PRIMARY KEY AUTOINCREMENT, "
        " NorthLeft INTEGER, "
        " NorthStraight INTEGER, "
        " NorthRight INTEGER, "
        " NorthUTurn INTEGER, "
        " SouthLeft INTEGER, "
        " SouthStraight INTEGER, "
        " SouthRight INTEGER, "
        " SouthUTurn INTEGER, "
        " EastLeft INTEGER, "
        " EastStraight INTEGER, "
        " EastRight INTEGER, "
        " EastUTurn INTEGER, "
        " WestLeft INTEGER, "
        " WestStraight INTEGER, "
        " WestRight INTEGER, "
        " WestUTurn INTEGER );";

//Vehicles Column Labels
//**********************************************************************************
const static QString VEHICLE_ID = "VehicleID";
const static QString NORTH_LEFT = "NorthLeft";
const static QString NORTH_STRAIGHT = "NorthStraight";
const static QString NORTH_RIGHT = "NorthRight";
const static QString NORTH_U_TURN = "NorthUTurn";
const static QString SOUTH_LEFT = "NorthLeft";
const static QString SOUTH_STRAIGHT = "NorthStraight";
const static QString SOUTH_RIGHT = "NorthRight";
const static QString SOUTH_U_TURN = "NorthUTurn";
const static QString EAST_LEFT = "NorthLeft";
const static QString EAST_STRAIGHT = "NorthStraight";
const static QString EAST_RIGHT = "NorthRight";
const static QString EAST_U_TURN = "NorthUTurn";
const static QString WEST_LEFT = "NorthLeft";
const static QString WEST_STRAIGHT = "NorthStraight";
const static QString WEST_RIGHT = "NorthRight";
const static QString WEST_U_TURN = "NorthUTurn";
//**********************************************************************************
//End Vehicles Column Labels

const static QString BICYCLES_CREATE_TABLE = "CREATE TABLE IF NOT EXISTS Bicycles ("
        " BicycleID INTEGER PRIMARY KEY AUTOINCREMENT, "
        " Bicycle_North INTEGER, "
        " Bicycle_South INTEGER, "
        " Bicycle_East INTEGER, "
        " Bicycle_West INTEGER );";

//Bicycles Column Labels
//**********************************************************************************
const static QString BICYCLE_ID = "BicycleID";
const static QString BICYCLE_NORTH = "Bicycle_North";
const static QString BICYCLE_SOUTH = "Bicycle_South";
const static QString BICYCLE_EAST = "Bicycle_East";
const static QString BICYCLE_WEST = "Bicycle_West";
//**********************************************************************************
//End Bicycles Column Labels

const static QString USERS_CREATE_TABLE = "CREATE TABLE IF NOT EXISTS Users ("
        " UsersID INTEGER PRIMARY KEY AUTOINCREMENT, "
        " UserName TEXT NOT NULL );";

//Users Column Labels
//**********************************************************************************
const static QString USER_ID = "UserID";
const static QString USER_NAME = "UserName";
//**********************************************************************************
//End Users Column Labels

const static QString PEDESTRIANS_CREATE_TABLE = "CREATE TABLE IF NOT EXISTS Pedestrians ("
        " PedestrianID INTEGER PRIMARY KEY AUTOINCREMENT, "
        " Pedestrian_North INTEGER, "
        " Pedestrian_South INTEGER, "
        " Pedestrian_East INTEGER, "
        " Pedestrian_West INTEGER );";

//Bicycles Column Labels
//**********************************************************************************
const static QString PEDESTRIAN_ID = "PedestrianID";
const static QString PEDESTRIAN_NORTH = "Pedestrian_North";
const static QString PEDESTRIAN_SOUTH = "Pedestrian_South";
const static QString PEDESTRIAN_EAST = "Pedestrian_East";
const static QString PEDESTRIAN_WEST = "Pedestrian_West";
//**********************************************************************************
//End Bicycles Column Labels

const static QString INTERSECTIONS_CREATE_TABLE = "CREATE TABLE IF NOT EXISTS Intersections ("
        " IntersectionID INTEGER PRIMARY KEY AUTOINCREMENT, "
        " NorthSouthStreet TEXT NOT NULL, "
        " EastWestStreet TEXT NOT NULL );";

//Bicycles Column Labels
//**********************************************************************************
const static QString INTERSECTION_ID = "PedestrianID";
const static QString NORTH_SOUTH_STREET = "NorthSouthStreet";
const static QString EAST_WEST_STREET = "EastWestStreet";
//**********************************************************************************
//End Bicycles Column Labels

const static QString VIDEOS_CREATE_TABLE = "CREATE TABLE IF NOT EXISTS Videos ("
        " VideoID INTEGER PRIMARY KEY AUTOINCREMENT, "
        " VideoPath TEXT NOT NULL, "
        " ThumbnailPath TEXT NOT NULL );";

//Bicycles Column Labels
//**********************************************************************************
const static QString VIDEO_ID = "VideoID";
const static QString VIDEO_PATH = "VideoPath";
const static QString THUMBNAIL_PATH = "ThumbnailPath";
//**********************************************************************************
//End Bicycles Column Labels

const static QString SESSIONS_CREATE_TABLE = "CREATE TABLE IF NOT EXISTS Sessions ("
        " SessionID INTEGER PRIMARY KEY AUTOINCREMENT, "
        " UserID INTEGER NOT NULL, "
        " VehicleID INTEGER NOT NULL, "
        " BicycleID INTEGER NOT NULL, "
        " PedestrianID INTEGER NOT NULL, "
        " IntersectionID INTEGER NOT NULL, "
        " ButtonMapID INTEGER, "
        " VideoID INTEGER NOT NULL );";

//Bicycles Column Labels
//**********************************************************************************
const static QString SESSION_ID = "SessionID";
//All columns are foreign key IDs to other tables which are previously defined
//**********************************************************************************
//End Bicycles Column Labels

#endif // DATABASEDEFINITION_H

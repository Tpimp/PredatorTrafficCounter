#include "databasemanager.h"

DatabaseManager::DatabaseManager()
{
    //database initialization code
    mDriverName = "QSQLITE";
    mDatabase = QSqlDatabase::addDatabase(mDriverName);
    mDatabase.setDatabaseName(DATABASE_NAME);
    mDatabase.setHostName("localhost");
    mDatabase.open();
    if (mDatabase.isOpen() && mDatabase.isValid())
    {//our database does not exist
        qDebug() << "Create Tables If Not Exists";
        QSqlQuery query;
        query.exec(VEHICLES_CREATE_TABLE);
        query.exec(BICYCLES_CREATE_TABLE);
        query.exec(VIDEOS_CREATE_TABLE);
        query.exec(INTERSECTIONS_CREATE_TABLE);
        query.exec(PEDESTRIANS_CREATE_TABLE);
        query.exec(USERS_CREATE_TABLE);
        query.exec(SESSIONS_CREATE_TABLE);
    }

    //end database initialization
}


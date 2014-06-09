#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QDebug>
#include "DatabaseDefinition.h"
#include <QList>

class DatabaseManager
{
    public:
        DatabaseManager(QString database_name);


    private:
        QString mDriverName;
        QSqlDatabase mDatabase;

};

#endif // DATABASEMANAGER_H

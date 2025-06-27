#include "database.h"
#include <QtDebug>
#include <QSqlError>

DatabaseManager::DatabaseManager(const QString& databaseName)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(databaseName);

    bool exists = QFile::exists(databaseName);

    if(!db.open()){
        qCritical() << "Failed to open database: " << db.lastError().text();
        return;
    }

    if(!exists)
        createTable();
}

DatabaseManager::~DatabaseManager()
{
    if(db.isOpen())
        db.close();
}

bool DatabaseManager::createTable()
{
    QSqlQuery query;

    QString table;
    table = "CREATE TABLE IF NOT EXISTS users ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "name TEXT NOT NULL,"
            "mode1TG INTEGER DEFAULT 0,"
            "mode2TG INTEGER DEFAULT 0,"
            "mode3TG INTEGER DEFAULT 0,"
            "mode1W INTEGER DEFAULT 0,"
            "mode2W INTEGER DEFAULT 0,"
            "mode3W INTEGER DEFAULT 0,"
            "mode1HS TEXT,"
            "mode2HS TEXT,"
            "mode3HS TEXT,"
            "mode1DT TEXT,"
            "mode2DT TEXT,"
            "mode3DT TEXT);";

    if(!query.exec(table)){
        qCritical() << "Failed to create table: " << query.lastError().text();
        return false;
    }
    return true;
}

bool DatabaseManager::addUser(const QString &name)
{
    QSqlQuery query;
    query.prepare("INSERT INTO users (name) VALUES (:name)");
    query.bindValue(":name", name);

    if (!query.exec()) {
        qWarning() << "Failed to add user:" << query.lastError().text();
        return false;
    }
    return true;
}




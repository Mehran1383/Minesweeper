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
            "mode1_total_games INTEGER DEFAULT 0,"
            "mode2_total_games INTEGER DEFAULT 0,"
            "mode3_total_games INTEGER DEFAULT 0,"
            "mode1_won_games INTEGER DEFAULT 0,"
            "mode2_won_games INTEGER DEFAULT 0,"
            "mode3_won_games INTEGER DEFAULT 0,"
            "mode1_best_score INTEGER,"
            "mode2_best_score INTEGER,"
            "mode3_best_score INTEGER,"
            "mode1_date_time TEXT,"
            "mode2_date_time TEXT,"
            "mode3_date_time TEXT);";

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




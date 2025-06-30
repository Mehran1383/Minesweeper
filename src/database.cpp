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
            "mode1_date_time TIMESTAMP,"
            "mode2_date_time TIMESTAMP,"
            "mode3_date_time TIMESTAMP);";

    if(!query.exec(table)){
        qCritical() << "Failed to create table: " << query.lastError().text();
        return false;
    }
    return true;
}

bool DatabaseManager::addUser(const QString &name, int mode, int score)
{
    QSqlQuery query;

    switch (mode) {
    case 1: query.prepare("INSERT INTO users (name, mode1_best_score, mode1_date_time) VALUES (:username, :best_score, :date_time)");
        query.bindValue(":username", name);
        query.bindValue(":best_score", score);
        query.bindValue(":date_time", QDateTime::currentDateTime().toString(Qt::ISODate));
        break;
    case 2:query.prepare("INSERT INTO users (name, mode2_best_score, mode2_date_time) VALUES (:username, :best_score, :date_time)");
        query.bindValue(":username", name);
        query.bindValue(":best_score", score);
        query.bindValue(":date_time", QDateTime::currentDateTime().toString(Qt::ISODate));
        break;
    case 3: query.prepare("INSERT INTO users (name, mode3_best_score, mode3_date_time) VALUES (:username, :best_score, :date_time)");
        query.bindValue(":username", name);
        query.bindValue(":best_score", score);
        query.bindValue(":date_time", QDateTime::currentDateTime().toString(Qt::ISODate));
    }

    if (!query.exec()) {
        qWarning() << "Failed to add user:" << query.lastError().text();
        QMessageBox::critical(this, "Save Highe Scores", "Failed to add your score!");
        return false;
    }
    return true;
}

int DatabaseManager::updateUser(const QString &name, int mode, int score)
{
    QSqlQuery query;

    switch (mode) {
    case 1: query.prepare("SELECT name, mode1_best_score FROM users WHERE name = :username"); break;
    case 2: query.prepare("SELECT name, mode2_best_score FROM users WHERE name = :username"); break;
    case 3: query.prepare("SELECT name, mode3_best_score FROM users WHERE name = :username");
    }
    query.bindValue(":username", name);

    if (query.exec())
    {
        if (query.next())
        {
            if(score < query.value(1).toInt() || query.isNull(1)){
                switch (mode) {
                case 1: query.prepare("UPDATE users SET mode1_best_score = :new_best_score, mode1_date_time = :new_date_time WHERE name = :username");
                    query.bindValue(":new_best_score", score);
                    query.bindValue(":new_date_time", QDateTime::currentDateTime().toString(Qt::ISODate));
                    query.bindValue(":username", name);
                    break;
                case 2: query.prepare("UPDATE users SET mode2_best_score = :new_best_score, mode2_date_time = :new_date_time WHERE name = :username");
                    query.bindValue(":new_best_score", score);
                    query.bindValue(":new_date_time", QDateTime::currentDateTime().toString(Qt::ISODate));
                    query.bindValue(":username", name);
                    break;
                case 3: query.prepare("UPDATE users SET mode3_best_score = :new_best_score, mode3_date_time = :new_date_time WHERE name = :username");
                    query.bindValue(":new_best_score", score);
                    query.bindValue(":new_date_time", QDateTime::currentDateTime().toString(Qt::ISODate));
                    query.bindValue(":username", name);
                }
                if(!query.exec()){
                    qWarning() << "Failed to check user:" << query.lastError().text();
                    QMessageBox::critical(this, "Save Highe Scores", "Failed to add your score!");
                    return ERROR;
                }
            }
            return USER_FOUND;
        }
        return USER_NOT_FOUND;
    }

    qWarning() << "Failed to check user:" << query.lastError().text();
    QMessageBox::critical(this, "Save Highe Scores", "Failed to add your score!");
    return ERROR;
}



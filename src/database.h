#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QFile>
#include <QSqlQuery>

class DatabaseManager
{
public:
    DatabaseManager(const QString& databaseName);
    ~DatabaseManager();

    bool createTable();
    bool addUser(const QString &name);

private:
    QSqlDatabase db;
};

#endif // DATABASE_H

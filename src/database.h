#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QFile>
#include <QSqlQuery>
#include <QMessageBox>
#include <QDateTime>

#define USER_FOUND 1
#define USER_NOT_FOUND 0
#define ERROR -1

class DatabaseManager : public QWidget
{
public:
    DatabaseManager(const QString& databaseName);
    ~DatabaseManager();

    bool createTable();
    bool addUser(const QString &name, int mode, int score);
    int updateUser(const QString &name, int mode, int score);

private:
    QSqlDatabase db;
};

#endif // DATABASE_H

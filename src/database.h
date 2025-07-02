#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QFile>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QDateTime>
#include <QTableView>
#include <QHeaderView>

#define USER_FOUND 1
#define USER_NOT_FOUND 0
#define ERROR -1

class DatabaseManager : public QWidget
{
public:
    DatabaseManager(const QString& databaseName);
    ~DatabaseManager();

    bool addUser(const QString &name, int mode, int score);
    int updateUser(const QString &name, int mode, int score);
    void populateTable(QTableView* view, int mode);
    int maxScore(int mode);
    int count(int mode);
    void deleteUserRecord(int mode);

private:
    QSqlDatabase db;
    QSqlQueryModel model1;
    QSqlQueryModel model2;
    QSqlQueryModel model3;

    bool createTable();
};

#endif // DATABASE_H

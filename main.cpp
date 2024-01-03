#include "login.h"

#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    login w;
    w.show();

    // 连接数据库(用完注释，先判断数据库是否能正常打开再进行后续操作)
    QSqlDatabase sqldb = QSqlDatabase::addDatabase("QMYSQL");
    sqldb.setHostName("localhost");
    sqldb.setDatabaseName("emarket");
    sqldb.setUserName("root");
    sqldb.setPassword("12345678");

    if(!sqldb.open())
    {
        qDebug() << "数据库打开失败";
    }
    else
    {
        qDebug() << "数据库打开成功";
    }
    return a.exec();
}

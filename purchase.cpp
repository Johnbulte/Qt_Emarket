#include "purchase.h"
#include "ui_purchase.h"
#include <QSqlQuery>
#include <QDebug>
#include <QSqlQueryModel>

purchase::purchase(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::purchase)
{
    ui->setupUi(this);
    this->setFixedSize(720,400);
    setvalue();
}

purchase::~purchase()
{
    delete ui;
}

// 通过数据库查询到的数据，将识别的数据存储到Qlist数组中，并通过数组将值设置到Qcombox中
void purchase::setvalue()
{
    QSqlQuery queryvalue;
    queryvalue.exec("SELECT commodity.category FROM commodity");

    // 核心代码
    while (queryvalue.next())
    {
        QString country = queryvalue.value(0).toString();
        QList<QString> list;
        list.append(country);
        ui->comboBox->addItems(list);
    }
}



void purchase::on_comboBox_currentTextChanged(const QString &arg1)
{
    // 每次执行改槽函数时将combobox_2的数据清空
    ui->comboBox_2->clear();
    QString sql = QString("SELECT commodity.`Name` FROM commodity WHERE commodity.category = '" + ui->comboBox->currentText() + "'");

    QSqlQuery sqlsearch;
    sqlsearch.exec(sql);

    // 定义sqlist数组，将查询到的数据用additems添加到combobox中
    QList<QString> sqllist;
    QString country;
    while (sqlsearch.next())
    {
        country = sqlsearch.value(0).toString();
        sqllist.append(country);
    }
    ui->comboBox_2->addItems(sqllist);
}


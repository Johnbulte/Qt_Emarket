#include "purchase.h"
#include "ui_purchase.h"
#include <QSqlQuery>
#include <QByteArray>
#include <QDebug>

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
    queryvalue.exec("SELECT `Name` FROM category");

    // 核心代码
    while (queryvalue.next())
    {
        QString country = queryvalue.value(0).toString();
        QList<QString> list;
        list.append(country);
        ui->comboBox->addItems(list);
    }
}

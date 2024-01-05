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
    ui->commodityPrice->setEnabled(false);
    ui->commodityInventory->setEnabled(false);
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


// combobox的槽函数
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

// combobox_2槽函数实现
void purchase::on_comboBox_2_currentTextChanged(const QString &arg1)
{
    QSqlQueryModel* commditModel = new QSqlQueryModel(this);
    QString name = ui->comboBox_2->currentText();
    // qDebug() << name;
    commditModel->setQuery("SELECT OutputPrice, Amount , Picture FROM commodity WHERE `Name`='" + name + "'");
    QModelIndex index;

    // 价格
    index = commditModel->index(0,0);
    ui->commodityPrice->setText(commditModel->data(index).toString());

    // 库存
    index = commditModel->index(0,1);
    ui->commodityInventory->setText(commditModel->data(index).toString());

    // 图片
    QPixmap pix;
    index = commditModel->index(0,2);
    pix.loadFromData(commditModel->data(index).toByteArray(),"jpg");
    pix.scaled(ui->photoImage->width(),ui->photoImage->height(),Qt::KeepAspectRatio);
    ui->photoImage->setPixmap(pix);

    // 初始化槽函数时调用一次
    ui->editSumPrice->setText(QString::number(ui->spinBox->value()*ui->commodityPrice->text().toFloat()));
}

// spinbox值改变时出发该槽函数
void purchase::on_spinBox_valueChanged(int arg1)
{
    // 计算总价(需要使用QString::number函数，不然无法直接相乘)
    ui->editSumPrice->setText(QString::number(ui->spinBox->value()*ui->commodityPrice->text().toFloat()));
}

// 购买(简单实现)
void purchase::on_btnBuy_clicked()
{
    ui->textEdit->insertPlainText("购买成功");
    ui->textEdit->insertPlainText("总计消费" + ui->editSumPrice->text() + "元\n");
}

// 取消(简单实现)
void purchase::on_btnCancel_clicked()
{
    ui->spinBox->setValue(1);
    ui->textEdit->clear();
    ui->textEdit->insertPlainText("用户取消购买\n");
}


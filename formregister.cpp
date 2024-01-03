#include "formregister.h"
#include "ui_formregister.h"
#include <QMessageBox>

FormRegister::FormRegister(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormRegister)
{
    ui->setupUi(this);

    // 美化注册窗口
    this->setWindowTitle("register");
    this->setStyleSheet("background-color:white");
    this->setFixedSize(640,400);
    QPixmap registerimage(":/rec/9878764.jpg");
    registerimage.scaled(registerimage.width(),registerimage.height(),Qt::IgnoreAspectRatio);
    ui->registerImage->setPixmap(registerimage);
    ui->frame->setStyleSheet(".QLineEdit{background-color: white;\
            border-top: transparent;\
            border-left: transparent;\
            border-right: transparent;\
            border-bottom: 2px solid blue}");
    ui->btnRegister->setFixedSize(150,32);
    ui->btnRegister->setStyleSheet("border:none;color:white;background-color:blue;border-radius:10px");

}

FormRegister::~FormRegister()
{
    delete ui;
}

// 注册功能实现
void FormRegister::on_btnRegister_clicked()
{
    // 这里可以从数据库获取字段值和用户输入的文本进行匹配
    QString username = ui->registerUserName->text();
    QSqlQuery query;
    query.prepare("SELECT * FROM member WHERE MermberID ='" + ui->registerUserName->text() + "'");
    query.addBindValue(username);

    // 用户名
    if(ui->registerUserName->text().isEmpty() || ui->registerPassword->text().isEmpty())
    {
        QMessageBox::warning(this,"警告","用户名或密码不能为空");
    }
    else if(ui->registerPassword->text().toStdString() != ui->registerPasswordOK->text().toStdString())
    {
        QMessageBox::warning(this,"错误","两次密码输入不一致请重新输入");
        ui->registerPasswordOK->clear();
        ui->registerPasswordOK->setFocus();
    }
    else if(query.exec() && query.next())
    {
        QMessageBox::warning(this,"错误","该用户已存在，请重新输入");
    }
    else
    {
        QSqlQuery query;

        // 使用SQL语句从数据库查询密码字段
        QString sql = "INSERT INTO emarket.member(MermberID, Password) VALUES ('" + ui->registerUserName->text() +  "'" + "," + \
                      "MD5('" + ui->registerPassword->text() + "'))";
        query.exec(sql);
        QMessageBox::information(this,"恭喜","注册成功请返回主窗口进行登录");
        this->close();
    }
}


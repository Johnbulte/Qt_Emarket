#include "login.h"
#include "ui_login.h"
#include <QSize>

login::login(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::login)
{
    ui->setupUi(this);
    this->setFixedSize(658,396);

    // 设置登录页面
    this->setStyleSheet("background-color:white");
    QPixmap image(":/rec/8418293_Mesa de trabajo 1.jpg");
    image.scaled(image.width(),image.height(),Qt::IgnoreAspectRatio);

    ui->image->setPixmap(image);

    // 美化界面
    ui->label_3->setStyleSheet("color:gray");
    ui->label_4->setStyleSheet("color:gray");
    ui->frame->setStyleSheet(".QLineEdit{background-color: white;\
            border-top: transparent;\
            border-left: transparent;\
            border-right: transparent;\
            border-bottom: 2px solid purple}");

    ui->btnRegister->setStyleSheet("border:none;color:purple;background-color:white");
    ui->btnLogin->setStyleSheet("background-color:purple;\
                                color:white;\
                                border-radius: 10px");
    ui->btnLogin->setFixedSize(150,30);
}

login::~login()
{
    delete ui;
}

// 加密算法的实现
QString login::strToMd5(QString str)
{
    QString strMd5;
    QByteArray qba;
    qba = QCryptographicHash::hash(str.toLatin1(),QCryptographicHash::Md5);
    strMd5.append(qba.toHex());
    return strMd5;
}

// 注册功能的实现
void login::on_btnRegister_clicked()
{
    FormRegister *formregister = new FormRegister;
    formregister->show();
}



// 登录功能的实现
void login::on_btnLogin_clicked()
{
    if(!ui->editPassword->text().isEmpty())
    {
        QSqlQuery query;

        // 使用SQL语句从数据库查询密码字段
        query.exec("SELECT `Password` FROM member WHERE MermberID='" + ui->editUserName->text() + "'");
        query.next();

        QString pwdMD5 = strToMd5(ui->editPassword->text());
        if(query.value(0).toString() == pwdMD5)
        {
            QMessageBox::information(this,"欢迎回来","欢迎"+ui->editUserName->text() + \
                                     "登录在线商城系统");
        }
        else
        {
            QMessageBox::information(this,"错误","账号或密码错误");
            ui->editPassword->clear();
            ui->editPassword->setFocus();
        }
    }
}


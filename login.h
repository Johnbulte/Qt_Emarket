#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QCryptographicHash>
#include <QPaintEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class login; }
QT_END_NAMESPACE

class login : public QWidget
{
    Q_OBJECT

public:
    login(QWidget *parent = nullptr);
    ~login();
    QString strToMd5(QString str); // 加密


private slots:
    void on_btnRegister_clicked();
    void on_btnLogin_clicked();

private:
    Ui::login *ui;
};
#endif // LOGIN_H

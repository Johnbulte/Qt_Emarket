#ifndef FORMREGISTER_H
#define FORMREGISTER_H

#include <QWidget>
#include <QSqlQuery>
#include <QSqlDatabase>

namespace Ui {
class FormRegister;
}

class FormRegister : public QWidget
{
    Q_OBJECT

public:
    explicit FormRegister(QWidget *parent = nullptr);
    ~FormRegister();

private slots:
    void on_btnRegister_clicked();

private:
    Ui::FormRegister *ui;
};

#endif // FORMREGISTER_H

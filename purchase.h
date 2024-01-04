#ifndef PURCHASE_H
#define PURCHASE_H

#include <QWidget>

namespace Ui {
class purchase;
}

class purchase : public QWidget
{
    Q_OBJECT

public:
    explicit purchase(QWidget *parent = nullptr);
    ~purchase();

private:
    void setvalue();

private:
    Ui::purchase *ui;
};

#endif // PURCHASE_H

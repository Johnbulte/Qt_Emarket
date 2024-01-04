# 一款基于Qt+Mysql的网上商城软件
1. 编译Mysql驱动；
# Qt使用Mysql数据库

## 准备工作==（整个编译过程有点复杂，请耐心看完）==

1.   在[MySQL官网](https://dev.mysql.com/downloads/mysql/)下载相应版本的MySQL，这里使用最新版本进行演示。

![image-20240101200656500](https://gitee.com/minghenjiujie/picgo-md/raw/master/image-20240101200656500.png)

2.   选择一个版本进行下载，这里建议选择MSI的安装程序。
3.   提示需要登录账号，这里选择最下面的直接下载。

![image-20240101200830767](https://gitee.com/minghenjiujie/picgo-md/raw/master/image-20240101200830767.png)

4.   双击下载的安装程序进行安装，安装步骤和配置方法网上教程有很多，这里就不详细介绍了。
5.   配置好MySQL后，启动MySQL服务。
6.   打开CMD测试MySQL是否可以正常使用。**输入mysql -u你的用户名 -p密码**，出现以下界面及说明安装成功。

![image-20240101201209784](https://gitee.com/minghenjiujie/picgo-md/raw/master/image-20240101201209784.png)



## 编译驱动

1.   请先确认安装Qt时是否选择了Source源码选项，如果不确定是否选择了该选项请在Qt安装目录找到**MaintenanceTool.exe**文件，并使用**CMD**打开，将该程序拖入CMD窗口中，并在后面加上镜像源选项，这样将会提高下载速度。

![image-20240101202031913](https://gitee.com/minghenjiujie/picgo-md/raw/master/image-20240101202031913.png)

2.   安装完成后直接退出该程序即可。
3.   新建一个Qt项目，打开MySQLServer程序的安装目录，将lib和include文件夹拷贝到新建的Qt项目中。

![image-20240101204640695](https://gitee.com/minghenjiujie/picgo-md/raw/master/image-20240101204640695.png)

![image-20240101204737950](https://gitee.com/minghenjiujie/picgo-md/raw/master/image-20240101204737950.png)

4.   打开[Qt安装目录]\[Qt版本号]\Src\qtbase\src\plugins\sqldrivers，使用Qtcreator打开CmakeList文件。

![image-20240101203641787](https://gitee.com/minghenjiujie/picgo-md/raw/master/image-20240101203641787.png)

5.   打开后提示选择编译器，一定一定一定要选择和刚刚复制的两个文件的库的版本要一致，64位选择64位编译器，32位就选择32位的编译器，千万不要弄错了！

6.   打开后会出现下面的文件，在.cmake.conf文件中新增以下代码。

![image-20240101204917158](https://gitee.com/minghenjiujie/picgo-md/raw/master/image-20240101204917158.png)

```cmake
SET(FEATURE_sql_mysql ON)
SET(MySQL_INCLUDE_DIR "D:/Qt_Project/Qt_Sql/include")
SET(MySQL_LIBRARY "D:/Qt_Project/Qt_Sql/lib")
```

7.   点击构建按钮，在编译输出中未见明显错误即可表示构建成功。

![image-20240101205137701](https://gitee.com/minghenjiujie/picgo-md/raw/master/image-20240101205137701.png)

![image-20240101205154075](https://gitee.com/minghenjiujie/picgo-md/raw/master/image-20240101205154075.png)

8.   构建完成后，在Qt->项目中找到构建目录，并打开该目录。

![image-20240101205308442](https://gitee.com/minghenjiujie/picgo-md/raw/master/image-20240101205308442.png)

![image-20240101205324794](https://gitee.com/minghenjiujie/picgo-md/raw/master/image-20240101205324794.png)

9.   找到plugin/sqldrivers目录，找到如下文件，并复制到编译器的plugin\sqldrivers目录。

![image-20240101205548097](https://gitee.com/minghenjiujie/picgo-md/raw/master/image-20240101205548097.png)

![image-20240101205824781](https://gitee.com/minghenjiujie/picgo-md/raw/master/image-20240101205824781.png)

10.   到这里还不算结束，请将MySQLserver安装路径中的lib文件下下面的libmysql.dll和libmysql.lib文件复制到，Qt编译器中的bin文件夹中。

![image-20240101210207710](https://gitee.com/minghenjiujie/picgo-md/raw/master/image-20240101210207710.png)

## 测试效果

1.   ==新建==一个Qt项目，在.pro文件中增加Qt += sql语句。

![image-20240101210320556](https://gitee.com/minghenjiujie/picgo-md/raw/master/image-20240101210320556.png)

2.   保存pro文件，并打开该项目的cpp文件，在cpp文件中添加以下代码，请根据自己的数据库填写，不要直接复制。

```cpp
#include "widget.h"
#include "ui_widget.h"
#include <QSqlError>
#include <QMessageBox>
#include <QSqlDatabase>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1"); //连接本地主机
    db.setPort(3306);
    db.setDatabaseName("数据库名称");
    db.setUserName("数据库名");
    db.setPassword("数据库密码");
    bool ok = db.open();
    if (ok){
        QMessageBox::information(this, "infor", "link success");
    }
    else {
        QMessageBox::information(this, "infor", "link failed");
        qDebug()<<"error open database because"<<db.lastError().text();
    }
}

Widget::~Widget()
{
    delete ui;
}
```

3.   点击运行按钮，出现以下提示及为成功，如果失败请仔细按照教程重新配置一遍，请确保databasename的字段是正确的，否则将会失败。

![image-20240101210654823](https://gitee.com/minghenjiujie/picgo-md/raw/master/image-20240101210654823.png)

3. 使用Qt命令操作mysql数据库；
5. 登录界面的实现；
6. 实现登录界面的账密判断；
7. 注册界面的实现；
8. 通过查询mysql数据库查看用户名是否已被注册；

## 登录界面
![image](https://github.com/Johnbulte/Qt_Emarket/assets/39647360/ce727885-e7ef-41c3-88bb-3c775430450a)
## 登录成功后显示
![image](https://github.com/Johnbulte/Qt_Emarket/assets/39647360/8ff277fc-56e7-49bc-bb35-61f50f59a556)
## 登录失败后显示
![image](https://github.com/Johnbulte/Qt_Emarket/assets/39647360/c1879116-b6b4-40c2-bbe0-377e5ee0e6e2)

## 注册界面
![image](https://github.com/Johnbulte/Qt_Emarket/assets/39647360/8ea28247-e7e5-4abf-b3bc-e85aeb69f525)

## 注册成功后显示
![image](https://github.com/Johnbulte/Qt_Emarket/assets/39647360/8fe1990c-d4e5-46a0-9a62-5c1d2d230f27)

## 注册失败后显示
![image](https://github.com/Johnbulte/Qt_Emarket/assets/39647360/47e0acbb-1787-4dda-a9ea-15a6c98119ec)


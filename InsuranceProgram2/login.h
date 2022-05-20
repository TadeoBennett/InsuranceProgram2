#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include <QMessageBox>
#include "CreateAccount.h"
#include "Menu.h"

#include "Administrator.h"
#include "Desk.h"
#include "Customer.h"
#include "Database.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Login; }
QT_END_NAMESPACE

class Login : public QMainWindow
{
    Q_OBJECT

public:
    Login(QWidget *parent = nullptr);
    ~Login();

private slots:
    void on_actionDeveloperInfo_triggered();

    void on_loginButton_clicked();

    void on_createaccountButton_clicked();

    void on_actionCreateAccount_triggered();

    void updateLoginInterface();
private:
    Ui::Login *ui;
};
#endif // LOGIN_H

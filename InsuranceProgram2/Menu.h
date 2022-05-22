#ifndef MENU_H
#define MENU_H

#include <QMainWindow>
#include <QInputDialog>
#include <QLineEdit>
#include "CreateAccount.h"
#include "Login.h"
#include "PolicyDetailsView.h"

#include "Administrator.h"
#include "Desk.h"
#include "Customer.h"
#include "Database.h"

namespace Ui {
class Menu;
}

class Menu : public QMainWindow
{
    Q_OBJECT

public:
    explicit Menu(QWidget *parent = nullptr);
    ~Menu();

    void updateMenuInterface();


private slots:
    void showDeveloperInfo();
    void showCreateAccountForm();
    void logoutuser();
    void changePassword();
    void viewPolicyDetails();
    void createInsurancesReport();

private:
    Ui::Menu *ui;
};

#endif // MENU_H

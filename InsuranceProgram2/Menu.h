#ifndef MENU_H
#define MENU_H

#include <QMainWindow>
#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QInputDialog>
#include <QLineEdit>
#include <QTableView>
#include "CreateAccount.h"
#include "Login.h"
#include "PolicyDetailsView.h"
#include "EditEmployeeForm.h"

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
    void showCreateAccountForm(); //only admins this one
    void logoutuser();
    void changePassword();

    //customer
    void viewPolicyDetails();
    void createInsurancesReport();

    //admin
    void createRevenueReport();
    void createInsuranceDistributionReport();
    void showEmployeeList();
    void editEmployee();

private:
    Ui::Menu *ui;
};

#endif // MENU_H

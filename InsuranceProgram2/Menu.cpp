//Tadeo Bennett
#include "Menu.h"
#include "ui_Menu.h"

extern bool loggedIn; //flag to check if a user is logged in
extern Database* globaldb; //holds the database object

extern BaseUserInfo * loggedInUser; //holds the values of the logged in user

Menu::Menu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Menu)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/images/shield.ico"));

    //General Actions
    connect(ui->actionAboutQt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
    connect(ui->actionDeveloperInfo, SIGNAL(triggered()), this, SLOT(showDeveloperInfo()));
    connect(ui->actionLogout, SIGNAL(triggered()), this, SLOT(logoutuser()));
    connect(ui->actionChangePassword, SIGNAL(triggered()), this, SLOT(changePassword()));

    //customer Actions
    connect(ui->viewPolicyDetailsButton, SIGNAL(clicked()), this, SLOT(viewPolicyDetails()));
    connect(ui->actionViewPolicyDetails, SIGNAL(triggered()), this, SLOT(viewPolicyDetails()));
    connect(ui->actionCreateInsurancesReport, SIGNAL(triggered()), this, SLOT(createInsurancesReport()));
    connect(ui->createInsuranceReportButton, SIGNAL(clicked()), this, SLOT(createInsurancesReport()));

    //admin actions
    connect(ui->actionAddEmployee, SIGNAL(triggered()), this, SLOT(showCreateAccountForm()));
    connect(ui->addEmployeeButton, SIGNAL(clicked()), this, SLOT(showCreateAccountForm()));
    connect(ui->revenueReportButton, SIGNAL(clicked()), this, SLOT(createRevenueReport())); //Report1
    connect(ui->actionRevenueReport, SIGNAL(triggered()), this, SLOT(createRevenueReport()));
    connect(ui->insuranceDistributionReportButton, SIGNAL(clicked()), this, SLOT(createInsuranceDistributionReport())); //Report2
    connect(ui->actionInsuranceDistReport, SIGNAL(triggered()), this, SLOT(createInsuranceDistributionReport()));
    connect(ui->seeAllEmployeesButton, SIGNAL(clicked()), this, SLOT(showEmployeeList()));
    connect(ui->actionSeeAllEmployees, SIGNAL(triggered()), this, SLOT(showEmployeeList()));
    connect(ui->editEmployeeButton, SIGNAL(clicked()), this, SLOT(editEmployee()));
    connect(ui->actionEditEmployee, SIGNAL(triggered()), this, SLOT(editEmployee()));

    //desk actions
    connect(ui->seeCustomerListButton, SIGNAL(clicked()), this, SLOT(showCustomerList()));
    connect(ui->actionCustomerList, SIGNAL(triggered()), this, SLOT(showCustomerList()));
    connect(ui->newCustomerButton, SIGNAL(clicked()), this, SLOT(newCustomer()));
    connect(ui->actionNewCustomer, SIGNAL(triggered()), this, SLOT(newCustomer()));
    connect(ui->editCustomerButton, SIGNAL(clicked()), this, SLOT(editCustomer()));
    connect(ui->actionEditCustomer, SIGNAL(triggered()), this, SLOT(editCustomer()));

    updateMenuInterface(); //load the right interface for the right usertype
}

Menu::~Menu()
{
    delete ui;
}

void Menu::updateMenuInterface()
{
    if(loggedIn == false){
        qDebug()<<"not logged in";
        //changes the main content of the window that holds the buttion options
        ui->adminBox->setVisible(false);
        ui->deskBox->setVisible(false);
        ui->customerBox->setVisible(false);
        ui->loadOptionsLabel->setVisible(false);

        //admin menu actions
        ui->menuActions->removeAction(ui->actionCreateAccount);
        ui->menuReports->menuAction()->setVisible(false);
        ui->menuEmployeeActions->menuAction()->setVisible(false);

        //desk menu actions
//        ui->menuActions->removeAction(ui->actionRenewPolicy);
        ui->menuActions->removeAction(ui->actionCustomerList);
        ui->menuActions->removeAction(ui->actionNewCustomer);

        //customer menu action
        ui->menuActions->removeAction(ui->actionCreateInsurancesReport);
        ui->menuActions->removeAction(ui->actionViewPolicyDetails);
    }else if(loggedIn){
        int userlevelid = loggedInUser->get_userlevelid();

        if(userlevelid == 1){
            qDebug()<<"is an admin";
            //changes the main content of the window that holds the buttion options
            ui->adminBox->setVisible(true);
            ui->deskBox->setVisible(false);
            ui->customerBox->setVisible(false);
            ui->loadOptionsLabel->setVisible(false);

            //admin menu actions
            ui->menuActions->removeAction(ui->actionCreateAccount);
            ui->menuReports->menuAction()->setVisible(true);
            ui->menuEmployeeActions->menuAction()->setVisible(true);

            //desk menu actions
//            ui->menuActions->removeAction(ui->actionRenewPolicy);
            ui->menuActions->removeAction(ui->actionCustomerList);
            ui->menuActions->removeAction(ui->actionNewCustomer);
            ui->menuActions->removeAction(ui->actionEditCustomer);

            //customer menu action
            ui->menuActions->removeAction(ui->actionCreateInsurancesReport);
            ui->menuActions->removeAction(ui->actionViewPolicyDetails);

        }else if(userlevelid == 2){
            qDebug()<<"is a desk";
            //changes the main content of the window that holds the buttion options
            ui->adminBox->setVisible(false);
            ui->deskBox->setVisible(true);
            ui->customerBox->setVisible(false);
            ui->loadOptionsLabel->setVisible(false);

            //admin menu actions
            ui->menuActions->removeAction(ui->actionCreateAccount);
            ui->menuReports->menuAction()->setVisible(false);
            ui->menuEmployeeActions->menuAction()->setVisible(false);

            //desk menu actions
//            ui->actionRenewPolicy->setVisible(true);
            ui->actionCustomerList->setVisible(true);
            ui->actionNewCustomer->setVisible(true);

            //customer menu action
            ui->menuActions->removeAction(ui->actionCreateInsurancesReport);
            ui->menuActions->removeAction(ui->actionViewPolicyDetails);

        }else if(userlevelid == 3){
            qDebug()<<"is a customer";
            //changes the main content of the window that holds the buttion options
            ui->adminBox->setVisible(false);
            ui->deskBox->setVisible(false);
            ui->customerBox->setVisible(true);
            ui->loadOptionsLabel->setVisible(false);

            //admin menu actions
            ui->menuActions->removeAction(ui->actionCreateAccount);
            ui->menuReports->menuAction()->setVisible(false);
            ui->menuEmployeeActions->menuAction()->setVisible(false);

            //desk menu actions
//            ui->menuActions->removeAction(ui->actionRenewPolicy);
            ui->menuActions->removeAction(ui->actionCustomerList);
            ui->menuActions->removeAction(ui->actionNewCustomer);

            //customer menu action
            ui->actionCreateInsurancesReport->setVisible(true);
            ui->actionViewPolicyDetails->setVisible(true);
            ui->menuActions->removeAction(ui->actionEditCustomer);

        }else{
            qDebug()<<"no userlevel read";
            //changes the main content of the window that holds the buttion options
            ui->adminBox->setVisible(false);
            ui->deskBox->setVisible(false);
            ui->customerBox->setVisible(false);
            ui->loadOptionsLabel->setVisible(true);

            //admin menu actions
            ui->menuActions->removeAction(ui->actionCreateAccount);
            ui->menuReports->menuAction()->setVisible(false);
            ui->menuEmployeeActions->menuAction()->setVisible(false);

            //desk menu actions
//            ui->menuActions->removeAction(ui->actionRenewPolicy);
            ui->menuActions->removeAction(ui->actionCustomerList);
            ui->menuActions->removeAction(ui->actionNewCustomer);

            //customer menu action
            ui->menuActions->removeAction(ui->actionCreateInsurancesReport);
            ui->menuActions->removeAction(ui->actionViewPolicyDetails);
        }
    }
}

void Menu::showCreateAccountForm()
{
    CreateAccount * newAccountPage = new CreateAccount(this);
    newAccountPage->open();
}

void Menu::logoutuser()
{
    loggedIn = false; //set logged in flag to false
    loggedInUser = new BaseUserInfo(); //reset the object that holds details of the logged in user

    qDebug()<<"re-opening login form";
    Login * w = new Login;
    w->setWindowIcon(QIcon(":/images/shield.ico"));
    w->show();

    this->close(); //closes the menu
}

void Menu::changePassword()
{
    bool ok;

    //get the new tag string from the user
    QString password = QInputDialog::getText(this, tr("Change Password"), tr("New Password:"), QLineEdit::Normal, QString(), &ok);


    if(ok){ //a password was specified
        if(!password.trimmed().isEmpty()){
            qDebug()<<"valid password";
            if(globaldb->get_databaseStatus()){ //check if the database is connected
                //check if the password was changed successfully
                bool changePassword = globaldb->changePassword(loggedInUser->get_userid(), password);

                if(changePassword){
                    //create the menu
                    qDebug()<<"password has been changed";
                    QMessageBox::information(this, tr("Password changed"), tr("Future logins will require this new password"));

                }else{
                    QMessageBox::warning(this, tr("Cannot change password"), tr("Password could not be changed at this time"));
                    return;
                }
            }else if(globaldb->get_databaseStatus() == false){ //database not connected
                qDebug()<<"no database connection was set";
                QMessageBox::warning(this, tr("Cannot change password"), tr("Could not connect to database"));
                return;
            }
        }else{
            qDebug()<<"invalid password";
            QMessageBox::warning(this, tr("Cannot change password"), tr("Password input must not be empty"));
            return;
        }
    }//end if
}

void Menu::viewPolicyDetails()
{
    PolicyDetailsView* insurancesForm = new PolicyDetailsView(this);
    insurancesForm->show();
}

void Menu::createInsurancesReport()
{
    qDebug()<<"Insurances Report created";
}

void Menu::createRevenueReport()
{
    qDebug()<<"Revenue Report created";
    QMessageBox::critical(this, tr("Sorry :-("), tr("Feature Under Development"));
}

void Menu::createInsuranceDistributionReport()
{
    qDebug()<<"Insurance Distribution Report created";
    QMessageBox::critical(this, tr("Sorry :-("), tr("Feature Under Development"));
}

void Menu::showEmployeeList()
{
    qDebug()<<"showing list of employees";

    QDialog* employeeList = new QDialog(this);
    QVBoxLayout* layout = new QVBoxLayout;

    QTableView* tableView = new QTableView();
    tableView->setModel(globaldb->getEmployeeListModel()); //set the table view the model that contains a list of all employees in the database

    layout->addWidget(tableView); //add the tableView to the layout

    employeeList->setLayout(layout); //make the QDialog have the layout which contains the table of employees
    employeeList->setGeometry(0, 0, 1100, 500); //setting the window geometry
    employeeList->setWindowTitle("Employee List");
    employeeList->open(); //show the QDialog as a modal window
}

void Menu::editEmployee()
{
    //create form to edit/delete employee
    EditEmployeeForm* newForm = new EditEmployeeForm(this);
    newForm->open();
}

void Menu::showCustomerList()
{
    qDebug()<<"showing list of customers";

    QDialog* customerList = new QDialog(this);
    QVBoxLayout* layout = new QVBoxLayout;

    QTableView* tableView = new QTableView();
    tableView->setModel(globaldb->getCustomerListModel()); //set the table view the model that contains a list of all employees in the database

    layout->addWidget(tableView); //add the tableView to the layout

    customerList->setLayout(layout); //make the QDialog have the layout which contains the table of employees
    customerList->setGeometry(0, 0, 1100, 500); //setting the window geometry
    customerList->setWindowTitle("Customer List");
    customerList->open(); //show the QDialog as a modal window
}

void Menu::newCustomer()
{
    newCustomerOptions* newDialog = new newCustomerOptions(this);
    newDialog->open();
}

void Menu::editCustomer()
{
    EditCustomerForm* newDialog = new EditCustomerForm(this);
    newDialog->open();
}

void Menu::showDeveloperInfo()
{
    QString message = "";
    message.append("<div><p>Developed by Tadeo Bennett</p>");
    message.append("<p>This project was first built as a c++ console application in the span of 2-3 weeks. "
                   "Many object-oriented concepts were used, enhanced and some were even learnt. My plan "
                   "was to take what I had learnt in my gui programming class which was taught using the Qt software, and "
                   "re-do this project. This gives me the opportunity to iron out the mistakes from my previous project, and "
                   "sharpen my skills in creating graphical applications backed by object-oriented principles. My success "
                   "with this application can only be measured by how well it works so you can be the judge of that :')</p>");
    message.append("<p>Thank you for reading and testing out this project :-)</p>");
    message.append(QString("%1").arg("<p>You can check out more of my projects at <a href='https://github.com/TadeoBennett' style='color:blue;'>GITHUB</a></p>"));
    message.append(QString("%1").arg("</br><p>I am also on <a href='https://twitter.com/tadeob_' style='color:blue;'>TWITTER</a></p></div>"));

    QMessageBox::about(this, "Developer Info", message);
}

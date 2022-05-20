#include "login.h"
#include "ui_login.h"

extern bool loggedIn; //flag to check if a user is logged in
extern Database* globaldb; //holds the database object

extern BaseUserInfo * loggedInUser; //holds the values of the logged in user

Login::Login(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);

    setCentralWidget(ui->groupBox);

    connect(ui->actionAboutQt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));  //about Qt

    //these slots are auto-connected
    //connect(ui->actionDeveloperInfo, SIGNAL(triggered()), this, SLOT(on_actionDeveloperInfo_triggered()));  //developer info
    //connect(ui->actionCreateAccount, SIGNAL(triggered()), this, SLOT(on_actionCreateAccount_triggered()));  //show create account dialog
    //connect(ui->createaccountButton, SIGNAL(clicked()), this, SLOT(on_createaccountButton_clicked()));  //show create account dialog



    //----- DISABLE/ENABLE ACTIONS IF THE USER IS/IS NOT LOGGED IN
    updateLoginInterface();

}

Login::~Login()
{
    delete ui;
}


void Login::on_actionDeveloperInfo_triggered()
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


void Login::on_loginButton_clicked()
{
    if(ui->emailInput->text().trimmed().isEmpty()){
        QMessageBox::warning(this, tr("Cannot log in"), tr("Email input is empty."));
        return;
    }

    if(ui->passwordInput->text().trimmed().isEmpty()){
        QMessageBox::warning(this, tr("Cannot log in"), tr("Password input is empty."));
        return;
    }

    QString email = ui->emailInput->text().trimmed();
    QString password = ui->passwordInput->text().trimmed();

    if(globaldb){ //check if the database is connected
        //check if password and username exists in database(returns true if yes)
        bool login_flag = globaldb->loginUser(email, password);

        if(login_flag){
            loggedIn = true; //setting the global logged in variable to true so this user may access the system
            updateLoginInterface(); //update the interface

            //create the menu
            qDebug()<<"showing the menu to logged in user";
            Menu * newMenu = new Menu;
            newMenu->show();
            this->close();
        }else{
            QMessageBox::warning(this, tr("Cannot log in"), tr("Password/Email combination is incorrect."
                                                               " If the problem persists and you are sure your "
                                                               "credentials are correct, please contact the developer."));
        }
    }else{ //database not connected
        qDebug()<<"no database connection was set";
        QMessageBox::warning(this, tr("Cannot log in"), tr("Could not connect to database"));
    }

    return;
}


void Login::on_createaccountButton_clicked()
{
    CreateAccount * newAccountPage = new CreateAccount(this);
    newAccountPage->show();
}


void Login::on_actionCreateAccount_triggered()
{
    CreateAccount * newAccountPage = new CreateAccount(this);
    newAccountPage->show();
}

void Login::updateLoginInterface()
{
    if(loggedIn == false){
        ui->actionAdminActions->setVisible(false);
        ui->actionDeskActions->setVisible(false);
        ui->actionCustomerActions->setVisible(false);
    }else if(loggedIn){
        int userlevelid = loggedInUser->get_userlevelid();

        if(userlevelid == 1){
            ui->actionAdminActions->setVisible(true);
            ui->actionDeskActions->setVisible(false);
            ui->actionCustomerActions->setVisible(false);
        }else if(userlevelid == 2){
            ui->actionAdminActions->setVisible(false);
            ui->actionDeskActions->setVisible(true);
            ui->actionCustomerActions->setVisible(false);
        }else if(userlevelid == 3){
            ui->actionAdminActions->setVisible(false);
            ui->actionDeskActions->setVisible(false);
            ui->actionCustomerActions->setVisible(true);
        }else{
            ui->actionAdminActions->setVisible(false);
            ui->actionDeskActions->setVisible(false);
            ui->actionCustomerActions->setVisible(false);
        }
    }
}


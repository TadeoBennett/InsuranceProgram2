#include "login.h"
#include "ui_login.h"

extern bool loggedIn;

Login::Login(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);

    setCentralWidget(ui->groupBox);

    connect(ui->actionAboutQt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));  //about Qt
    connect(ui->actionDeveloperInfo, SIGNAL(triggered()), this, SLOT(on_actionDeveloperInfo_triggered()));  //developer info

    //these slots are auto-connected
    //connect(ui->actionCreateAccount, SIGNAL(triggered()), this, SLOT(on_actionCreateAccount_triggered()));  //show create account dialog
    //connect(ui->createaccountButton, SIGNAL(clicked()), this, SLOT(on_createaccountButton_clicked()));  //show create account dialog



    //----------------------------------------------------- DISABLE ACTIONS IF THE USER IS NOT LOGGED IN
    if(loggedIn == false){
        ui->actionAdminActions->setEnabled(false);
        ui->actionDeskActions->setEnabled(false);
        ui->actionCustomerActions->setEnabled(false);
    }else{
        ui->actionAdminActions->setEnabled(true);
        ui->actionDeskActions->setEnabled(true);
        ui->actionCustomerActions->setEnabled(true);
    }

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
    if(ui->usernameInput->text().trimmed().isEmpty()){
        QMessageBox::warning(this, tr("Cannot log in"), tr("Username input is empty."));
    }

    if(ui->passwordInput->text().trimmed().isEmpty()){
        QMessageBox::warning(this, tr("Cannot log in"), tr("Password input is empty."));
    }


    //check if password and username exists in database

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


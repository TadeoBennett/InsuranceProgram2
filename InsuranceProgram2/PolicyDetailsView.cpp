#include "PolicyDetailsView.h"
#include "ui_PolicyDetailsView.h"

PolicyDetailsView::PolicyDetailsView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PolicyDetailsView)
{
    ui->setupUi(this);

    ui->scrollContents->setLayout(ui->verticalLayout); //add the layout to the scroll area and make it scroll

    //use the parent slot to create the insurance report after clicking the print button
    connect(ui->printButton, SIGNAL(clicked()), parent, SLOT(createInsurancesReport()));

    loadPolicyDetails();
}

PolicyDetailsView::~PolicyDetailsView()
{
    delete ui;
}

void PolicyDetailsView::loadPolicyDetails()
{

}

#ifndef EDITCUSTOMERFORM_H
#define EDITCUSTOMERFORM_H

#include <QDialog>
#include "Database.h"
#include "newCustomerOptions.h"

namespace Ui {
class EditCustomerForm;
}

class EditCustomerForm : public QDialog
{
    Q_OBJECT

public:
    explicit EditCustomerForm(QWidget *parent = nullptr);
    ~EditCustomerForm();

public:
    void updateTableData();

private slots:
    void on_tableView_activated(const QModelIndex &index);
    void refreshTable();
    void addCustomer();
    void deleteCustomer();
    void updateDetails();
    void showMoreUpdateDetails();
    void renewPolicy();
    void on_searchText_textChanged(const QString &arg1);

private:
    Ui::EditCustomerForm *ui;

    int selectedRecord;
};

#endif // EDITCUSTOMERFORM_H

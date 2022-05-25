#ifndef EDITEMPLOYEEFORM_H
#define EDITEMPLOYEEFORM_H

#include <QDialog>
#include "Database.h"

namespace Ui {
class EditEmployeeForm;
}

class EditEmployeeForm : public QDialog
{
    Q_OBJECT

public:
    explicit EditEmployeeForm(QWidget *parent = nullptr);
    ~EditEmployeeForm();

public:
    void updateTableData();

private slots:
    void on_tableView_activated(const QModelIndex &index);
    void deleteEmployee();
    void updateEmployee();
    void refreshTable();

private:
    Ui::EditEmployeeForm *ui;
};

#endif // EDITEMPLOYEEFORM_H

#ifndef NEWCUSTOMEROPTIONS_H
#define NEWCUSTOMEROPTIONS_H

#include <QDialog>
#include <QMessageBox>
#include <QSettings>
#include "CreateCustomerForm.h"

namespace Ui {
class newCustomerOptions;
}

class newCustomerOptions : public QDialog
{
    Q_OBJECT

public:
    explicit newCustomerOptions(QWidget *parent = nullptr);
    ~newCustomerOptions();

private slots:
    void cancelButtonClicked();
    void okButtonClicked();

private:
    Ui::newCustomerOptions *ui;

    QWidget* parentWidget;
};

#endif // NEWCUSTOMEROPTIONS_H

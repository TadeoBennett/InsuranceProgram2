#ifndef RENEWPOLICYOPTIONS_H
#define RENEWPOLICYOPTIONS_H

#include <QDialog>
#include <QMessageBox>
#include <QSettings>
#include "RenewPolicyForm.h"

namespace Ui {
class renewPolicyOptions;
}

class renewPolicyOptions : public QDialog
{
    Q_OBJECT

public:
    explicit renewPolicyOptions(QWidget *parent = nullptr);
    ~renewPolicyOptions();

private slots:
    void cancelButtonClicked();
    void okButtonClicked();

private:
    Ui::renewPolicyOptions *ui;

    QWidget* parentWidget;

public:
    void loadForm();
};

#endif // RENEWPOLICYOPTIONS_H

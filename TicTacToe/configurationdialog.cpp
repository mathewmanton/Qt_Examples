#include "configurationdialog.h"
#include "ui_configurationdialog.h"

#include <QPushButton>

ConfigurationDialog::ConfigurationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigurationDialog)
{
    ui->setupUi(this);
    connect(ui->Player1Name, &QLineEdit::textChanged, this, &ConfigurationDialog::UpdateOKButtonState);
    connect(ui->Player2Name, &QLineEdit::textChanged, this, &ConfigurationDialog::UpdateOKButtonState);
    UpdateOKButtonState();
}

ConfigurationDialog::~ConfigurationDialog()
{
    delete ui;
}

void ConfigurationDialog::SetPlayer1Name(const QString &p1Name)
{
    ui->Player1Name->setText(p1Name);
}

void ConfigurationDialog::SetPlayer2Name(const QString &p2Name)
{
    ui->Player2Name->setText(p2Name);
}

QString ConfigurationDialog::Player1Name() const
{
    return ui->Player1Name->text();
}

QString ConfigurationDialog::Player2Name() const
{
    return ui->Player2Name->text();
}

void ConfigurationDialog::UpdateOKButtonState()
{
    QPushButton *okButton = ui->buttonBox->button(QDialogButtonBox::Ok);
    okButton->setEnabled(!ui->Player1Name->text().isEmpty() && !ui->Player2Name->text().isEmpty());
}

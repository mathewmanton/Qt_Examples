#ifndef CONFIGURATIONDIALOG_H
#define CONFIGURATIONDIALOG_H

#include <QDialog>

namespace Ui {
class ConfigurationDialog;
}

class ConfigurationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConfigurationDialog(QWidget *parent = nullptr);
    ~ConfigurationDialog();
    void SetPlayer1Name(const QString &p1Name);
    void SetPlayer2Name(const QString &p2Name);
    QString Player1Name() const;
    QString Player2Name() const;

private:
    Ui::ConfigurationDialog *ui;

private slots:
    void UpdateOKButtonState();
};



#endif // CONFIGURATIONDIALOG_H

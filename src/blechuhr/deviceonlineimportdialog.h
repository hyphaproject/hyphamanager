#ifndef DEVICEONLINEIMPORTDIALOG_H
#define DEVICEONLINEIMPORTDIALOG_H

#include <QtWidgets/QDialog>
#include "../database/database.h"
#include "../database/userdatabase.h"
#include "../settings/hyphamanagersettings.h"
#include "model/workingtime.h"

namespace Ui {
class DeviceOnlineImportDialog;
}

class DeviceOnlineImportDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DeviceOnlineImportDialog(HyphaManagerSettings * settings, Database *database, UserDatabase * userDatabase, QWidget *parent = 0);
    ~DeviceOnlineImportDialog();

private slots:
    void on_DeviceOnlineImportDialog_accepted();
    void reload();
    void reloadTimesList();

    void on_dateEdit_editingFinished();

    void on_usernameComboBox_currentTextChanged(const QString &arg1);

    void on_exportCSVButton_clicked();

    void on_printPDFButton_clicked();

    void on_mailPDFButton_clicked();

    void on_mailCSVButton_clicked();

private:
    void init();
    Ui::DeviceOnlineImportDialog *ui;
    QString username;
    Database * database;
    UserDatabase *userDatabase;
    HyphaManagerSettings * settings;
    QList<WorkingTime*> times;
};

#endif // DEVICEONLINEIMPORTDIALOG_H

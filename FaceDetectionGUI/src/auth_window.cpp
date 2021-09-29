#include "ui_auth_window.h"
#include "auth_window.h"
#include <QFile>
#include <QMessageBox>

void AuthWindow::readSettings()
{
    settings->beginGroup("USER_DATA");
    if(settings->value("checkbox").toString() == "true")
    {
        ui->checkBox->setChecked(true);

        ui->login->setText(settings->value("login").toString());
        ui->password->setText(settings->value("password").toString());

        user_name = ui->login->text();
        user_pass = ui->password->text();
    }
    settings->endGroup();
}

void AuthWindow::writeSettings()
{
    settings->beginGroup("USER_DATA");
    settings->setValue("checkbox", ui->checkBox->isChecked());
    settings->setValue("login", ui->login->text());
    settings->setValue("password", ui->password->text());
    settings->endGroup();
}

AuthWindow::AuthWindow(QWidget *parent) : QWidget(parent), ui(new Ui::AuthWindow)
{
    ui->setupUi(this);
    setWindowTitle("Face Detection GUI");
    setWindowIcon(QIcon("icon.png"));

    settings = new QSettings("settings.ini", QSettings::IniFormat);

    readSettings();
}

AuthWindow::~AuthWindow()
{
    delete ui;
    delete settings;
}

void AuthWindow::on_doLogin_clicked()
{
    if(ui->checkBox->isChecked())
    {
        writeSettings();
    }

    emit login_button_clicked();
}

void AuthWindow::on_login_textEdited(const QString &log)
{
    user_name = log;
}

void AuthWindow::on_password_textEdited(const QString &pass)
{
    user_pass = pass;
}

QString AuthWindow::getLogin()
{
    return user_name;
}

QString AuthWindow::getPass()
{
    return user_pass;
}

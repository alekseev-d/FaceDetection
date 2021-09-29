#ifndef AUTH_WINDOW_H
#define AUTH_WINDOW_H

#include <QWidget>
#include <QSettings>

namespace Ui {
class AuthWindow;
}

class AuthWindow : public QWidget
{
    Q_OBJECT

public:
    explicit AuthWindow(QWidget *parent = nullptr);
    ~AuthWindow();
    QString getLogin();
    QString getPass();

signals:
    void login_button_clicked();
    void register_button_clicked();

private slots:
    void on_login_textEdited(const QString &arg1);
    void on_password_textEdited(const QString &arg1);
    void on_doLogin_clicked();

private:
    Ui::AuthWindow *ui;
    QString user_name;
    QString user_pass;
    QSettings *settings;

    void readSettings();
    void writeSettings();

    friend class mainwindow;
};

#endif // AUTH_WINDOW_H

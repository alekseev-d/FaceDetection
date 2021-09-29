#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include "teviandll.h"
#include "json_parser.h"
#include "auth_window.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void display();

private slots:
    void on_fileChoose_clicked();
    void on_processing_clicked();
    void on_files_itemClicked(QListWidgetItem *item);
    void authorizeUser();

private:
    Ui::MainWindow *ui;

    AuthWindow ui_Auth;
    TevianDLL tevian_cl;
    QString token;
    QStringList images;
    QMap<QString, FaceInfo> info;

    QVector<QString> urls
    {
        "https://backend.facecloud.tevian.ru/api/v1/login",
        "https://backend.facecloud.tevian.ru/api/v1/detect?demographics=true"
    };

    QString lastFile;
    QSettings *settings;
    JsonParser parser;
    QString prev_item;

    qreal zoom_x, zoom_y;

    void loginSuccess(const QByteArray& file);
    void detectSuccess(const QByteArray& file);
    void requestError(const QString& error);

    void processNextImage();
    void resizeEvent(QResizeEvent* resize);
};

#endif // MAINWINDOW_H

#ifndef TEVIANCONSOLE_H
#define TEVIANCONSOLE_H

#include "teviandll.h"
#include "json_parser.h"
#include <QTimer>

class TevianClient : public QObject
{
    Q_OBJECT

    TevianDLL tevian_cl;
    JsonParser parser;

    QString cur_file;
    QString det_url;
    QString token;
    QStringList images;
    QTimer r_timer;

    bool status, login_status;

signals:
    void requestDone();

public:
    TevianClient();

    void responseTimeout();
    void processImage();
    bool getStatus();
    bool getLoginStatus();
    const QString getToken() const;

    void requestError(const QString& errorMessage);
    void loginSuccess(const QByteArray& jsonData);
    void detectSuccess(const QByteArray& rawJSON);

    void login(const QString& url, const QString& email, const QString& password);
    void detect(const QString& url, const QStringList& imagePaths, const QString& token);


};

#endif // TEVIANCONSOLE_H

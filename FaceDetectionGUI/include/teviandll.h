#ifndef TEVIANDLL_H
#define TEVIANDLL_H

#include <QObject>

#include "teviandll_global.h"
#include "face_info.h"
#include <QUrl>
#include <QFile>
#include <QTimer>
#include <QObject>
#include <QVariant>
#include <QJsonObject>
#include <QJsonDocument>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonParseError>
#include <QNetworkAccessManager>

class DetectRequest;
class LoginRequest;

extern "C" class TEVIANDLLSHARED_EXPORT TevianDLL : public QObject
{
    Q_OBJECT

    LoginRequest *log_req;
    DetectRequest *det_req;

signals:
    void loginSuccess(const QByteArray& file);
    void detectSuccess(const QByteArray& file);
    void requestError(const QString& error);
public:
    TevianDLL();

    void login(const QString& url, const QString& email, const QString& pass);
    void detect(const QString& url, const QString& image, const QString& token);
};

#endif // TEVIANDLL_H

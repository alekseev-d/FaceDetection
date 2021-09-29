#ifndef TEVIANDLL_H
#define TEVIANDLL_H

#include <QObject>
#include "tevian_dll_global.h"
#include <QNetworkReply>
#include <QJsonParseError>
#include <QNetworkAccessManager>

class Request : public QObject
{
    Q_OBJECT

protected:
    QNetworkAccessManager *manager;
    QNetworkReply *reply;

    QJsonParseError parse_error;
    QMap<int, QString> errors
    {
        {400, "Request Error : Bad request"},
        {401, "Authorization Error : Invalid credentials"},
        {404, "Page Error : Page not found"}
    };

    int getResponseStatus(const QByteArray& rep);

public:
    Request();
    virtual ~Request();

    virtual void request(const QString& url, const QStringList& req_param) {};
    virtual void processResponse();

signals:
    void requestError(const QString& error);
    void statusCode(int code);
    void rawJSON(const QByteArray& file);
    void badParameters();

};

class DetectRequest : public Request
{
    Q_OBJECT

public:
    void request(const QString& url, const QStringList& req_param) override;

signals:
    void cantOpenFile();

};

class LoginRequest : public Request
{
    Q_OBJECT

    QMap<int, QString> errors
    {
        {400, "Request Error : Bad request"},
        {401, "Specification Error : Invalid email/password"}
    };

public:
    void request(const QString& url, const QStringList& req_param) override;

};

extern "C++" class TEVIANDLLSHARED_EXPORT TevianDLL : public QObject
{
    Q_OBJECT

    LoginRequest *log_req;
    DetectRequest *det_req;

signals:
    void loginSuccess(const QByteArray& file);
    void detectSuccess(const QByteArray&  file);
    void requestError(const QString& error);

public:
    TevianDLL();
    ~TevianDLL();

    void login(const QString& url, const QString& email, const QString& pass);
    void detect(const QString& url, const QString& image, const QString& token);

};

#endif // TEVIANDLL_H

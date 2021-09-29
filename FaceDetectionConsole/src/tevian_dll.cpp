#include "tevian_dll.h"
#include <QFile>

int Request::getResponseStatus(const QByteArray& rep)
{
    return QJsonDocument::fromJson(rep, &parse_error).toVariant().toMap()["status_code"].toInt();
}

Request::Request()
{
    manager = new QNetworkAccessManager(this);
}

Request::~Request()
{
    delete manager;
}

void Request::processResponse()
{
    QByteArray body = qobject_cast<QNetworkReply *>(sender())->readAll();
    int status_code = getResponseStatus(body);

    statusCode(status_code);
    if(status_code != 200)
    {
        requestError(errors.value(status_code));
        return;
    }

    rawJSON(body);
}

void LoginRequest::request(const QString& url, const QStringList& req_param)
{
    if(req_param.size() != 2)
    {
        badParameters();
        return;
    }

    QUrl qurl(url);
    QNetworkRequest request(url);
    QString load = "{\"email\":\"" + req_param[0] + "\",\"password\":\"" + req_param[1] + "\"}";

    request.setRawHeader("Content-Type", "application/json");
    reply = manager->post(request, load.toUtf8());

    connect(reply, &QNetworkReply::finished,this, &LoginRequest::processResponse);
}

void DetectRequest::request(const QString& url, const QStringList& req_param)
{
    if(req_param.size() != 2)
    {
        badParameters();
        return;
    }

    QFile imageFile(req_param[1]);
    if(!imageFile.open(QIODevice::ReadOnly))
    {
        cantOpenFile();
        return;
    }

    QUrl qurl(url);
    QNetworkRequest request(qurl);

    request.setRawHeader("Content-Type", "image/jpeg");
    request.setRawHeader("Authorization", ("Bearer " + req_param[0]).toUtf8());
    request.setRawHeader("Content-Length", QString::number(imageFile.size()).toUtf8());

    reply = manager->post(request, imageFile.readAll());

    connect(reply, &QNetworkReply::finished,this, &DetectRequest::processResponse);
}

TevianDLL::TevianDLL()
{
    det_req = new DetectRequest();
    log_req = new LoginRequest();

    connect(log_req, &LoginRequest::rawJSON, this, &TevianDLL::loginSuccess);
    connect(log_req, &LoginRequest::requestError, this, &TevianDLL::requestError);
    connect(det_req, &DetectRequest::rawJSON, this, &TevianDLL::detectSuccess);
    connect(det_req, &DetectRequest::requestError, this, &TevianDLL::requestError);
}

void TevianDLL::login(const QString& url, const QString& email, const QString& pass)
{
    log_req->request(url, {email, pass});
}

void TevianDLL::detect(const QString& url, const QString& image, const QString& token)
{
    det_req->request(url, {token, image});
}

TevianDLL::~TevianDLL()
{
    delete log_req;
    delete det_req;
}

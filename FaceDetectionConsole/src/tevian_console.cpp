#include "tevian_console.h"
#include <iostream>
#include <QFile>

TevianClient::TevianClient()
{
    status = false;
    login_status = false;

    connect(&tevian_cl, &TevianDLL::loginSuccess,  this, &TevianClient::loginSuccess);
    connect(&tevian_cl, &TevianDLL::requestError,  this, &TevianClient::requestError);
    connect(&tevian_cl, &TevianDLL::detectSuccess, this, &TevianClient::detectSuccess);
    connect(&r_timer, &QTimer::timeout, this, &TevianClient::responseTimeout);
}

void TevianClient::responseTimeout()
{
    std::cout << "[LoggerTevian] : Response timeout" << std::endl;
    r_timer.stop();
}

void TevianClient::requestError(const QString& error)
{
    std::cout << error.toUtf8().data() << std::endl;
    status = true;
}

void TevianClient::loginSuccess(const QByteArray& jsonData)
{
    std::cout << "[LoggerTevian] : You have been logged in" << std::endl << std::endl;
    token = parser.getToken(jsonData);
    login_status = true;
}

void TevianClient::detectSuccess(const QByteArray& file)
{
    std::cout << "[Image " << cur_file.toUtf8().data() << "] : " << std::endl
              << parser.getFaceInfo(file).toString().toUtf8().data() << std::endl;

    if(images.count() > 0)
    {
        images.pop_front();
        processImage();
    }
}

void TevianClient::login(const QString& url, const QString& email, const QString& password)
{
    tevian_cl.login(url, email, password);
    r_timer.start(10000);
}

void TevianClient::processImage()
{
    if(images.count() > 0)
    {
        if(!QFile(images[0]).exists())
        {
            std::cout << "[LoggerTevian] : Image " << images[0].toUtf8().data() << " wasn't found" << std::endl << std::endl;
            images.pop_front();
            processImage();

            return;
        }

        tevian_cl.detect(det_url, images[0], token);
        cur_file = images[0];
        r_timer.start(10000);
    }
    else
    {
        std::cout << "[LoggerTevian] : All images has been processed" << std::endl << std::endl;
        status = true;
    }
}

bool TevianClient::getLoginStatus()
{
    return login_status;
}

bool TevianClient::getStatus()
{
    return status;
}

void TevianClient::detect(const QString& url, const QStringList& img, const QString& t)
{
    if(img.count() == 0)
    {
        std::cout << "[LoggerTevian] : Images list is empty" << std::endl << std::endl;
        return;
    }

    det_url = url;
    images = img;
    token = t;
    processImage();
}

const QString TevianClient::getToken() const
{
    return token;
}

#include <iostream>
#include <QCommandLineParser>
#include "tevian_console.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QCommandLineParser clp;
    QStringList urls =
    {
        "https://backend.facecloud.tevian.ru/api/v1/login",
        "https://backend.facecloud.tevian.ru/api/v1/detect?demographics=true"
    };

    QCommandLineOption authorize_opt({ "c", "create_token" }, "", "-c");
    QCommandLineOption detect_opt({ "d", "detect_face" }, "", "-d");

    clp.addOption(authorize_opt);
    clp.addOption(detect_opt);

    clp.process(app);

    bool auth = clp.isSet(authorize_opt);
    bool det = clp.isSet(detect_opt);

    if((!auth) && (!det))
    {
        std::cout << "[LoggerMain] : Bad parameters in console line" << std::endl << std::endl;
        return 1;
    }

    TevianClient test;

    if(auth)
    {
        QStringList user_data = clp.value(authorize_opt).split(':');
        test.login(urls[0], user_data[0], user_data[1]);
    }
    while(!test.getLoginStatus())
    {
        app.processEvents();
    }

    if(det)
    {
        QStringList images = clp.value(detect_opt).split(',');
        QString token = test.getToken();

        std::cout << "[LoggerMain] : Files for recognition: ";
        for(const auto& img : images)
        {
            std::cout << img.toUtf8().data() << " ";
        }
        std::cout << std::endl << std::endl;

        if(token == "")
        {
            std::cout << "[LoggerMain] : Token is empty" << std::endl << std::endl;
            return 2;
        }

        images.pop_back();
        test.detect(urls[1], images, token);
    }
    while(!test.getStatus())
    {
        app.processEvents();
    }

    app.exit();
}

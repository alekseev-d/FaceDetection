#include "json_parser.h"

QString JsonParser::getToken(const QByteArray& response)
{
    QJsonDocument doc = QJsonDocument::fromJson(response, &parse_error);

    if(parse_error.error != 0)
    {
        return "";
    }

    return doc.toVariant().toMap()[key_data].toMap()[key_access_token].toString();
}

FaceInfo JsonParser::getFaceInfo(const QByteArray& response)
{
    FaceInfo face_info;
    if(response.count() == 0)
    {
        face_info.status = false;
        return face_info;
    }

    QJsonDocument doc = QJsonDocument::fromJson(response, &parse_error);
    if(parse_error.error != 0)
    {
        face_info.status = false;
        return face_info;
    }

    face_info = infoFromJson(doc);

    return face_info;
}

#ifndef JSONPARSER_H
#define JSONPARSER_H

#include <QString>
#include <QJsonParseError>
#include <QVariant>
#include <QJsonDocument>
#include <QJsonObject>
#include "face_info.h"

class JsonParser
{
    QJsonParseError parse_error;

    const QString key_data = "data";
    const QString key_access_token = "access_token";
    const QString key_bbox = "bbox";
    const QString key_demographics = "demographics";
    const QString key_age = "age";
    const QString key_x = "x";
    const QString key_y = "y";
    const QString key_width = "width";
    const QString key_height = "height";
    const QString key_ethnicity = "ethnicity";
    const QString key_gender = "gender";
    const QString key_mean = "mean";
    const QString key_variance = "variance";

    FaceInfo infoFromJson(const QJsonDocument& doc)
    {
        FaceInfo face_info;
        QVariant data = doc.object()[key_data].toVariant().toList()[0];
        QMap<QString, QVariant> face = data.toMap()[key_bbox].toMap();
        QMap<QString, QVariant> demograph = data.toMap()[key_demographics].toMap();
        QMap<QString, QVariant> age = demograph[key_age].toMap();

        if(face[key_x].toString() != "")
        {
            face_info.x = face[key_x].toInt();
        }
        if(face[key_y].toString() != "")
        {
            face_info.y = face[key_y].toInt();
        }
        if(face[key_width].toString() != "")
        {
            face_info.width = face[key_width].toInt();
        }
        if(face[key_height].toString() != "")
        {
            face_info.height = face[key_height].toInt();
        }

        face_info.ethnicity = demograph[key_ethnicity].toString();
        face_info.gender = demograph[key_gender].toString();

        face_info.age = age[key_mean].toFloat();
        face_info.variance = age[key_variance].toFloat();

        return face_info;
    }

public:
    JsonParser() = default;
    ~JsonParser() = default;

    QString getToken(const QByteArray& response);
    FaceInfo getFaceInfo(const QByteArray& response);
};

#endif // JSONPARSER_H

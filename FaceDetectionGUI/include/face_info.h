#ifndef FACEINFO_H
#define FACEINFO_H

#include <QString>

struct FaceInfo
{
    bool status = false;

    int x, y, width, height;

    float age, variance;

    QString ethnicity, gender;

public:
    FaceInfo() = default;
    ~FaceInfo() = default;

    const QString toString()
    {
        return "Coordinates:\r\n   X:\t" + QString::number(x) + "\r\n" +
               "   Y:\t" + QString::number(y) + "\r\n \nSize:\r\n" +
               "   Width:\t" + QString::number(width) + "\r\n" +
               "   Height:\t" + QString::number(height) + "\r\n\nSpecification:\r\n" +
               "   Ethnicity:\t" + ethnicity + "\r\n" +
               "   Gender:\t" + gender + "\r\n" +
               "   Age:\t" + QString::number(age,'f',2) + "\r\n" +
               "   Variance:\t" + QString::number(variance,'f',2) + "\r\n";
    }
};

#endif // FACEINFO_H

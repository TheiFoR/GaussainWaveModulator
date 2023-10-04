#ifndef FILE_H
#define FILE_H

#include <QObject>
#include <QFile>
#include "noise.h"

class File : public QObject
{
    Q_OBJECT
public:
    explicit File(QObject *parent = nullptr);
    File(QString path);

    QString read();

    int applyNoise(Noise* noise);

    void setPath(QString path);
    QString getPath();

private:
    QString path;

};

#endif // FILE_H

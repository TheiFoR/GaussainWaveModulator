#include "file.h"

File::File(QObject *parent)
    : QObject{parent}
{

}

File::File(QString path)
{
    this->path = path;
}

int File::applyNoise(Noise *noise)
{

}

void File::setPath(QString path)
{
    this->path = path;
}

QString File::getPath()
{
    return path;
}

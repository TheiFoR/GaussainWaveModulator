#include "saver.h"

Saver::Saver(QObject *parent) : QObject(parent)
{
    settings = new QSettings("settings.ini", QSettings::IniFormat, this);
}

Saver::~Saver()
{
    delete settings;
}

void Saver::set(const QString& key, const QVariant& value)
{
    settings->setValue(key, value);
}

QVariant Saver::get(const QString& key)
{
    return settings->value(key);
}

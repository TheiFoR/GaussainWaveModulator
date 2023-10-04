#ifndef SAVER_H
#define SAVER_H

#include <QObject>
#include <unordered_map>
#include <QSettings>
#include <QFile>

class Saver : public QObject
{
    Q_OBJECT
public:
    explicit Saver(QObject *parent = nullptr);
    ~Saver();

    void set(const QString& key, const QVariant& value);
    QVariant get(const QString& key);

private:
    QSettings* settings;
};

#endif // SAVER_H

#ifndef NOISE_H
#define NOISE_H

#include <QObject>
#include <cmath>
#include <QTime>
#include <QtGlobal>
#include <cmath>

class Noise : public QObject
{
    Q_OBJECT
public:
    explicit Noise(QObject *parent = nullptr);

    int generate();

    void setSeed(int seed);
    int getSeed();

    void setDB(double dB);
private:
    int seed;

    int noise;
    double scaled_noise;

    double u1;
    double u2;
    double z1;

    double gain;
};

#endif // NOISE_H

#include "noise.h"

Noise::Noise(QObject *parent)
    : QObject{parent}
{
    seed = static_cast<quint64>(QTime::currentTime().msecsSinceStartOfDay());
    srand(seed);
}

int Noise::generate()
{
    u1 = (rand() + 1.0) / (RAND_MAX + 2.0);
    u2 = (rand() + 1.0) / (RAND_MAX + 2.0);
    z1 = sqrt(-2.0 * log(u1)) * cos(2.0 * M_PI * u2);

    noise = static_cast<int>(z1 * gain);

    return noise;
}

void Noise::setSeed(int seed)
{
    this->seed = seed;
    srand(seed);
}

int Noise::getSeed()
{
    return this->seed;
}

void Noise::setDB(double dB)
{
    gain = pow(10, dB / 20);
}

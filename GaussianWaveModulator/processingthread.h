#ifndef PROCESSINGTHREAD_H
#define PROCESSINGTHREAD_H

#include <QThread>
#include <QFile>
#include "noise.h"
#include <QProgressBar>

class ProcessingThread : public QThread
{
    Q_OBJECT
public:
    ProcessingThread() = delete;
    ProcessingThread(QString selectedFilePath, QString resultFilePath, bool isCheck, double noiseAmount);

signals:
    void progressUpdated(int value);
    void buttonEnabled(bool state);
    void buttonText(QString text);
    void buttonStyle(QString style);

protected:
    void run() override;

private:
    QString selectedFilePath = "";
    QString resultFilePath = "";
    bool isCheck = true;
    double noiseAmount = 0;
};


#endif // PROCESSINGTHREAD_H

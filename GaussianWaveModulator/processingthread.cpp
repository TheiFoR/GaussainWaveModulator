#include "processingthread.h"

ProcessingThread::ProcessingThread(QString selectedFilePath, QString resultFilePath, bool isCheck, double noiseAmount)
{
    this->selectedFilePath = selectedFilePath;
    this->resultFilePath = resultFilePath;
    this->isCheck = isCheck;
    this->noiseAmount = noiseAmount;
}

void ProcessingThread::run()
{
    emit buttonEnabled(false);
    emit buttonText("In progress...");
    emit buttonStyle("background-color: \"#CFCFCF\";\ncolor: \"#505050\";");

    const int updateInterval = 10000;

    emit progressUpdated(0);
    Noise gaussain;

    QFile inputFile(selectedFilePath);
    QFile outputFile(resultFilePath + (isCheck ? "" : ".tmp"));

    quint64 allBytes = inputFile.size();

    if (!inputFile.open(QIODevice::ReadOnly))
    {
        return;
    }

    if (!outputFile.open(QIODevice::WriteOnly))
    {
        return;
    }

    QDataStream inStream(&inputFile);
    QDataStream outStream(&outputFile);

    inStream.setByteOrder(QDataStream::LittleEndian);
    outStream.setByteOrder(QDataStream::LittleEndian);

    quint64 readyBytes = 0;
    qint16 value;
    qint16 newValue;

    gaussain.setDB(noiseAmount);

    while (!inStream.atEnd()) {
        inStream >> value;

        newValue = value;

        newValue += gaussain.generate();

        outStream << newValue;

        readyBytes += 2;

        if (readyBytes % updateInterval<<1 == 0) {
            emit progressUpdated((readyBytes << 7) / allBytes);
        }
    }

    outputFile.close();
    inputFile.close();

    if(!isCheck){
        QFile::remove(selectedFilePath);
        outputFile.rename(selectedFilePath);
    }

    emit progressUpdated(128);
    emit buttonEnabled(true);
    emit buttonText("Apply noise");
    emit buttonStyle("background-color: \"#FFFFFF\";\ncolor: \"#000000\";");
}

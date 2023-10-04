#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->currentSeed->setText("Current seed: " + QString::number(gaussain.getSeed()));
    ui->outputFileName->setText("none");

    selectedFilePath = sett.get("inputFilePath").toString();
    resultFilePath = sett.get("outputFilePath").toString();
    fileInfo.setFile(selectedFilePath);

    on_createFile_stateChanged(sett.get("newFileCheck").toInt());
    ui->createFile->setCheckState(sett.get("newFileCheck").toBool() == 0 ? Qt::Unchecked : Qt::Checked);

    ui->outputFileName->setText(sett.get("newFileCheck").toBool() == 0 ? "" : sett.get("outputFileName").toString());
    if (fileInfo.fileName() != "") {
        ui->fileInfo->setText(fileInfo.baseName() + "." + fileInfo.suffix());
    }
    else{
        ui->fileInfo->setText("none");
    }

    on_randomSeed_valueChanged(sett.get("seed").toInt());
    ui->randomSeed->setValue(sett.get("seed").toInt());

    ui->dBAmount->setValue(sett.get("noiseAmount").toDouble());


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_openFile_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Выберите файл");
    if (!filePath.isEmpty()) {
        fileInfo.setFile(filePath);
        selectedFilePath = filePath;
        ui->fileInfo->setText(fileInfo.baseName() + "." + fileInfo.suffix());
        if(ui->createFile->checkState()){
            if (fileInfo.fileName() != "") {
                ui->outputFileName->setText(fileInfo.baseName() + "_with_noise." + fileInfo.suffix());
            }
            else {
                ui->outputFileName->setText("none");
            }
        }
        resultFilePath = fileInfo.path() + "/" + fileInfo.baseName() + "_with_noise." + fileInfo.suffix();
        sett.set("inputFileName", fileInfo.baseName() + "." + fileInfo.suffix());
        sett.set("inputFilePath", filePath);
        sett.set("outputFilePath", resultFilePath);
        sett.set("outputFileName", fileInfo.baseName() + "_with_noise." + fileInfo.suffix());
    }
}


void MainWindow::on_randomSeed_valueChanged(int seed)
{
    if(seed){
        gaussain.setSeed(seed);
        ui->currentSeed->setText("Current seed: " + QString::number(seed));
    }
    else{
        int curSeed = static_cast<quint64>(QTime::currentTime().msecsSinceStartOfDay());
        gaussain.setSeed(curSeed);
        ui->currentSeed->setText("Current seed: " + QString::number(curSeed));
    }
    sett.set("seed", seed);
}


void MainWindow::on_createFile_stateChanged(int arg1)
{
    switch(arg1){
        case 0:
            ui->label->setEnabled(false);
            ui->outputFileName->setEnabled(false);
            ui->outputFileName->setText("");
            break;
        case 2:
            ui->label->setEnabled(true);
            ui->outputFileName->setEnabled(true);
            if(fileInfo.fileName() != "")
                ui->outputFileName->setText(fileInfo.baseName() + "_with_noise." + fileInfo.suffix());
            else
                ui->outputFileName->setText("none");
            break;
        default:
            qDebug() << arg1;
    }
    sett.set("newFileCheck", arg1);
}


void MainWindow::on_applNoise_clicked()
{
    ProcessingThread* thread = new ProcessingThread(selectedFilePath, resultFilePath, ui->createFile->checkState(), ui->dBAmount->value());

    connect(thread, &ProcessingThread::progressUpdated, ui->progressBar, &QProgressBar::setValue);
    connect(thread, &ProcessingThread::buttonEnabled, ui->applNoise, &QPushButton::setEnabled);
    connect(thread, &ProcessingThread::buttonText, ui->applNoise, &QPushButton::setText);
    connect(thread, &ProcessingThread::buttonStyle, ui->applNoise, &QPushButton::setStyleSheet);

    thread->start();
}




void MainWindow::on_outputFileName_textChanged(const QString &arg1)
{
    sett.set("outputFileName", arg1);
}


void MainWindow::on_dBAmount_textChanged(const QString &arg1)
{
    sett.set("noiseAmount", arg1);
}


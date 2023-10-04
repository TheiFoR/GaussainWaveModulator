#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include "noise.h"
#include "saver.h"
#include "processingthread.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    Noise gaussain;

private slots:
    void on_openFile_clicked();

    void on_randomSeed_valueChanged(int arg1);

    void on_createFile_stateChanged(int arg1);

    void on_applNoise_clicked();

    void on_outputFileName_textChanged(const QString &arg1);

    void on_dBAmount_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;

    Saver sett;
    QString selectedFilePath;
    QString resultFilePath;
    QFileInfo fileInfo;

};
#endif // MAINWINDOW_H

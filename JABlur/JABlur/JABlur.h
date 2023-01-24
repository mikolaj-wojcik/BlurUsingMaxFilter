#pragma once

#include <QtWidgets/QMainWindow>
#include <QBarSet>
#include <QBarSeries>
#include <QChart>
#include<QtCharts/qchartview.h>
#include <QChartView>
#include <QBarCategoryAxis>
#include <QValueAxis>
#include <qdebug.h>
#include <qfiledialog.h>
#include <iostream>
#include <array>
#include "ui_JABlur.h"
#include "Listener.h"


class JABlur : public QMainWindow
{
    Q_OBJECT

public:
    JABlur(QWidget *parent = nullptr);
    ~JABlur();

    void loadButtonClicked();
public slots:
    void loadButtonPressed();
    void saveButtonPressed();
    void changeNumberOfThreads();
    void changeLibraryAsm() { listen.changeLib(false); }
    void changeLibraryCpp() { listen.changeLib(true); }
    void changeRay(int newRay);
    void runProgram();
    void changeModifiedPicture(QString path);
    void insertNewTime(QString data);
private:
    Ui::JABlurClass ui;
    Listener listen;

    int numberOfThreads = 1;
    bool selectedLib; //true cpp, false asm
    void loadImage(QString path, QLabel* target);
    void createHistograms(std::array<float, 6> colorTab);
    QString tempFilePath;
};

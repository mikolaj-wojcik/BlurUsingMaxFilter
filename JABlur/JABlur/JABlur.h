#pragma once

#include <QtWidgets/QMainWindow>
#include <qdebug.h>
#include <qfiledialog.h>
#include <iostream>
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
    void changeNumberOfThreads();
    void changeLibraryAsm() { listen.changeLib(false); }
    void changeLibraryCpp() { listen.changeLib(true); }
    void runProgram();
    void changeModifiedPicture(QString path);
private:
    Ui::JABlurClass ui;
    Listener listen;

    int numberOfThreads = 1;
    bool selectedLib; //true cpp, false asm
    void loadImage(QString path, QLabel* target);
    QString tempFilePath;
};

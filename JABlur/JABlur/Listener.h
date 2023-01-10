#pragma once
#include <QObject>
#include <QDebug>
#include <array>
#include <string>
#include "ImageHandling.h"

class Listener : public QObject{
	Q_OBJECT
private:
	QString sourceFilePath = "";
	int numberOfThreads = 1;
	bool selectedLib; //true cpp, false asm
	std::array<int, 3> loadedHistogram;
	std::array<int, 3> modifiedHistogram;
	ImageHandling img;

	
	
public:
	Listener() {}
	~Listener() {}
	void setSourcePath(QString src);
	void changeLib(bool newValue);
	void runModification();
	void save(QString path);
	//std::array
public slots:
	void loadButtonPressed();
	void changeThreads(QString newNumber);
signals:
	void photoModified(QString tempPath);
	void newTime(QString time);
};


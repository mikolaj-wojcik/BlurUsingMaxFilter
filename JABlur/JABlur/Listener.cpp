#include "Listener.h"


void Listener::loadButtonPressed() {
	qDebug() << "Nacisnieto";
}

void Listener::setSourcePath(QString src) {
	sourceFilePath = src;
}

void Listener::changeThreads(QString newNumber) {
	numberOfThreads = newNumber.toInt();
	img.setNumberOfThreads(newNumber.toInt());
}

void Listener::changeLib(bool newValue) {
	selectedLib = newValue;
}

void Listener::save(QString path) {
	img.saveImage(path.toStdString());
}

void Listener::runModification() {
	QString temp = "C:\\Users\\Mikolaj\\Pictures\\football.png";

	if (sourceFilePath != "") {

		img.setPath(sourceFilePath.toStdString());

		img.loadImage();
		img.saveImage("temp.bmp");
	}


	emit photoModified("temp.bmp");
}
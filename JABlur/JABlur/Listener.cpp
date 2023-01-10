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



void Listener::runModification() {
	QString temp = "C:\\Users\\Mikolaj\\Pictures\\football.png";

	if (sourceFilePath != "") {

		img.setPath(sourceFilePath.toStdString());

		img.loadImage();
		img.saveImage();
	}


	emit photoModified(temp);
}
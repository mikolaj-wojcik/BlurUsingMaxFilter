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
	img.changeLib(newValue);
}

void Listener::save(QString path) {
	img.saveImage(path.toStdString());
}

void Listener::runModification() {
	QString temp = "C:\\Users\\Mikolaj\\Pictures\\football.png";

	if (sourceFilePath != "") {

		img.setPath(sourceFilePath.toStdString());

		double timeElapsed = img.run();
		std::string timeString = std::to_string(timeElapsed);
		
		if (selectedLib) {
			timeString = "C++    " + std::to_string(numberOfThreads) + "      " + timeString;
		}
		else {
			timeString = "Asm    " + std::to_string(numberOfThreads) + "      " + timeString;
		}
		emit photoModified("temp.bmp");
		emit newTime(QString::fromStdString(timeString));

	}


}
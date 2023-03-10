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

void Listener::changeRay(int newRay) {
	ray = newRay;
	img.setRay(newRay);
}

void Listener::save(QString path) {
	img.saveImage(path.toStdString());
}

void Listener::runModification() {
	

	if (!sourceFilePath.isEmpty()) {

		img.setPath(sourceFilePath.toStdString());

		double timeElapsed = img.run();
		std::string timeString = std::to_string(timeElapsed);
		
		if (selectedLib) {
			timeString = "C++    " + timeString;
		}
		else {
			timeString = "Asm    " + timeString;
		}
		timeString += "     " + std::to_string(ray) + "    " + std::to_string(numberOfThreads);
		emit photoModified("temp.bmp");
		emit newTime(QString::fromStdString(timeString));
		emit histogramsData(runColorCount());
		emit fileCanSave();
	}


}

std::array<float, 6> Listener::runColorCount() {
	return img.calculateHistorgrams();
}

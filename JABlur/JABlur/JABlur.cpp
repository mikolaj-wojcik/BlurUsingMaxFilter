#include "JABlur.h"

JABlur::JABlur(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    
    QObject::connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(loadButtonPressed()));
    QObject::connect(ui.pushButton_2, SIGNAL(clicked()), this, SLOT(saveButtonPressed()));
    QObject::connect(ui.pushButton_3, SIGNAL(clicked()), this, SLOT(runProgram()));
    QObject::connect(ui.comboBox, SIGNAL(currentTextChanged(QString)), this, SLOT(changeNumberOfThreads()));
    QObject::connect(ui.cppRadio, SIGNAL(clicked()), this, SLOT(changeLibraryCpp));
    QObject::connect(ui.asmRadio, SIGNAL(clicked()), this, SLOT(changeLibraryAsm));
    QObject::connect(&listen, SIGNAL(photoModified(QString)), this, SLOT(changeModifiedPicture(QString)));
    QObject::connect(&listen, SIGNAL(newTime(QString)), this, SLOT(insertNewTime(QString)));
    
}

JABlur::~JABlur()
{}


void JABlur::loadButtonPressed() {
    std::cout << "Elo!\n";

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
        "",
        tr("Images (*.bmp)"));
    if (fileName != "") {
        listen.setSourcePath(fileName);
        loadImage(fileName, ui.label);
    }
        
}
void JABlur::loadButtonClicked() {
    int i = 0;
}

void JABlur::saveButtonPressed() {
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
        "",
        tr("Images (*.bmp)"));
    if (fileName != "") {
        listen.save(fileName);
    }
}

void JABlur::loadImage(QString src, QLabel* target) {
    QPixmap originalfile;
    if (!originalfile.load(src)) {
        qWarning() << "Cant openFile";
    }
    target->setPixmap(originalfile.scaled(target->width(), target->height(), Qt::KeepAspectRatio));
}


void JABlur::changeNumberOfThreads() {
    
    listen.changeThreads(ui.comboBox->currentText());
}

void JABlur::changeModifiedPicture(QString temp) {
    loadImage(temp, ui.label_2);
    tempFilePath = temp;
}

void JABlur::insertNewTime(QString data) {
    ui.listWidget->addItem(data);
}

void JABlur::runProgram() {
    listen.runModification();
}
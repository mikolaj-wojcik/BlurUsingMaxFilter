#include "JABlur.h"

JABlur::JABlur(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    ui.verticalSlider->setRange(1, 50);
    QObject::connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(loadButtonPressed()));
    QObject::connect(ui.pushButton_2, SIGNAL(clicked()), this, SLOT(saveButtonPressed()));
    QObject::connect(ui.pushButton_3, SIGNAL(clicked()), this, SLOT(runProgram()));
    QObject::connect(ui.comboBox, SIGNAL(currentTextChanged(QString)), this, SLOT(changeNumberOfThreads()));
    QObject::connect(ui.cppRadio, SIGNAL(clicked()), this, SLOT(changeLibraryCpp()));
    QObject::connect(ui.asmRadio, SIGNAL(clicked()), this, SLOT(changeLibraryAsm()));
    QObject::connect(&listen, SIGNAL(photoModified(QString)), this, SLOT(changeModifiedPicture(QString)));
    QObject::connect(&listen, SIGNAL(newTime(QString)), this, SLOT(insertNewTime(QString)));
    QObject::connect(ui.verticalSlider, SIGNAL(valueChanged(int)), this, SLOT(changeRay(int)));
    QObject::connect(&listen, SIGNAL(histogramsData(std::array<float, 6>)), this, SLOT(createHistograms(std::array<float, 6>)));
    QObject::connect(&listen, SIGNAL(fileCanSave()), this, SLOT(chFileCanBeSaved()));
    
}

JABlur::~JABlur()
{}


void JABlur::loadButtonPressed() {

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
    if (fileCanBeSaved) {
        QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
            "",
            tr("Images (*.bmp)"));
        if (fileName != "") {
            listen.save(fileName);
        }
    }
}

void JABlur::loadImage(QString src, QLabel* target) {
    QPixmap originalfile;
    if (!originalfile.load(src)) {
        qWarning() << "Cant openFile";
    }
    target->setPixmap(originalfile.scaled(target->width(), target->height(), Qt::KeepAspectRatio));
}

void JABlur::changeRay(int newRay) {
    listen.changeRay(newRay);
}

void JABlur::changeNumberOfThreads() {
    
    listen.changeThreads(ui.comboBox->currentText());
    numberOfThreads = ui.comboBox->currentText().toInt();

    
    
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
    //createHistograms(listen.runColorCount());
}

void JABlur::createHistograms(std::array<float, 6> colorTab){
    QBarSet* redSet = new QBarSet("Red");
    QBarSet* greenSet = new QBarSet("Green");
    QBarSet* blueSet = new QBarSet("Blue");
    redSet->setColor(Qt::red);
    blueSet->setColor(Qt::blue);
    greenSet->setColor(Qt::green);

    *blueSet << colorTab[0] << colorTab[3];
    *greenSet << colorTab[1] << colorTab[4];
    *redSet << colorTab[2] << colorTab[5];

    QBarSeries* series = new QBarSeries();
    series->append(redSet);
    series->append(greenSet);
    series->append(blueSet);

    QChart* chart = new QChart();
    chart->addSeries(series);
    
    QStringList cats;
    cats << "Before" << "After";
    QBarCategoryAxis* axisX = new QBarCategoryAxis();
    axisX->append(cats);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    int maxArrVal = *std::max_element(colorTab.begin(), colorTab.end());
    QValueAxis* axisY = new QValueAxis();
    axisY->setRange(0, maxArrVal);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);
    QChartView* chartView = new QChartView(chart);
    ui.gridLayout->addWidget(chartView,1,1);

}
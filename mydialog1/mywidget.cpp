#include "mywidget.h"
#include <QPushButton>
using namespace cv;
MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
    this->setWindowTitle("主窗口");
    //One
    oneButton = new QPushButton(this);
    oneButton->setText("One");
    oneButton->resize(70,40);
    oneButton->move(100,100);
    //Two
    twoButton=new QPushButton(this);
    twoButton->setText("Two");
    twoButton->resize(70,40);
    twoButton->move(100,200);

    //three
    threeButton=new QPushButton(this);
    threeButton->setText("Three");
    threeButton->resize(70,40);
    threeButton->move(100,300);
    fourButton=new QPushButton(this);
    fourButton->setText("Four");
    fourButton->resize(70,40);
    fourButton->move(100,400);

    fiveButton=new QPushButton(this);
    fiveButton->setText("Five");
    fiveButton->resize(70,40);
    fiveButton->move(100,500);
    sixButton=new QPushButton(this);
    sixButton->setText("Six");
    sixButton->resize(70,40);
    sixButton->move(100,600);

    QObject::connect(twoButton,SIGNAL(clicked()),this,SLOT(toTwoSlot()));
    QObject::connect(&twoWin,SIGNAL(mySignal()),this,SLOT(TtomainSlot()));
    QObject::connect(&oneWin,SIGNAL(mySignal()),this,SLOT(OtomainSlot()));
    QObject::connect(oneButton,SIGNAL(clicked()),this,SLOT(toOneSlot()));
    QObject::connect(&threeWin,SIGNAL(mySignal()),this,SLOT(ThtomainSlot()));
    QObject::connect(threeButton,SIGNAL(clicked()),this,SLOT(toThreeSlot()));

    QObject::connect(&fourWin,SIGNAL(mySignal()),this,SLOT(FotomainSlot()));
    QObject::connect(fourButton,SIGNAL(clicked()),this,SLOT(toFourSlot()));

    QObject::connect(&fiveWin,SIGNAL(mySignal()),this,SLOT(FivetomainSlot()));
    QObject::connect(fiveButton,SIGNAL(clicked()),this,SLOT(toFiveSlot()));
    QObject::connect(sixButton,SIGNAL(clicked()),this,SLOT(sixtoshow()));

    this->resize(800,800);

}



MainWidget::~MainWidget()
{

}

void MainWidget::toOneSlot()
{
    this->hide();
    oneWin.show();
}

void MainWidget::OtomainSlot()
{
    this->show();
    oneWin.hide();
}
void MainWidget::toTwoSlot(){
    this->hide();
    twoWin.show();
}
void MainWidget::TtomainSlot(){
    this->show();
    twoWin.hide();
}
void MainWidget::toThreeSlot(){
    this->hide();
    threeWin.show();
}
void MainWidget::ThtomainSlot(){
    this->show();
    threeWin.hide();
}

void MainWidget::toFourSlot(){
    this->hide();
    fourWin.show();
}
void MainWidget::FotomainSlot(){
    this->show();
    fourWin.hide();
}
void MainWidget::toFiveSlot(){
    this->hide();
    fiveWin.show();
}
void MainWidget::FivetomainSlot(){
    this->show();
    fiveWin.hide();
}
void MainWidget::sixtoshow(){
    cv::VideoCapture video("d:\\test6.mp4");

    int frameNum = 1;
    Mat frame, mask, thresholdImage, output;
    if (!video.isOpened())
        cout << "fail to open!" << endl;

    double totalFrameNumber = video.get(CAP_PROP_FRAME_COUNT);
    video >> frame;
    Ptr<BackgroundSubtractorMOG2> bgsubtractor = cv::createBackgroundSubtractorMOG2();
    bgsubtractor->setVarThreshold(40);
    Mat kernel = getStructuringElement(MORPH_RECT, Size(2, 2));
    while (true) {
        if (totalFrameNumber == frameNum)
            break;
        video >> frame;
        ++frameNum;
        //bgSubtractor(frame, mask, 0.001);
        bgsubtractor->apply(frame, mask, 0.01);
        morphologyEx(mask, mask, 2, kernel);
        morphologyEx(mask,mask, 3, kernel);
        imshow("mask", mask);
        waitKey(10);

    }
}

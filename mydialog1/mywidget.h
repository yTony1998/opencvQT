#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QPushButton>
#include "subwidget.h" //子窗口头文件
#include "twowidget.h"
#include "threewidget.h"
#include "fourwidget.h"
#include "fivewidget.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>


class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = 0);
    ~MainWidget();

public:
    OneWidget oneWin;
    TwoWidget twoWin;
    ThreeWidget threeWin;
    FourWidget fourWin;
    FiveWidget fiveWin;
    QPushButton * oneButton;
    QPushButton * twoButton;
    QPushButton * threeButton;
    QPushButton * fourButton;
    QPushButton * fiveButton;
    QPushButton * sixButton;
private slots:
    void OtomainSlot();
    void toOneSlot();
    void toTwoSlot();
    void TtomainSlot();
    void toThreeSlot();
    void ThtomainSlot();
    void toFourSlot();
    void FotomainSlot();
    void toFiveSlot();
    void FivetomainSlot();
    void sixtoshow();

};

#endif // MAINWIDGET_H

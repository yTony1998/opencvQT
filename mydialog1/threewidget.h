#ifndef THREEWIDGET_H
#define THREEWIDGET_H
#include <QWidget>
#include <QPushButton>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QFileDialog>
#include <QLabel>
#include <QLineEdit>
using namespace cv;

class ThreeWidget:public QWidget{
    Q_OBJECT
public:
    explicit ThreeWidget(QWidget * parent=0);

private:

    Mat img1;
    QPushButton * Remain;
    QPushButton * Open;

    QPushButton * Ex;
    QPushButton * Lx;
    QPushButton * Hist;

    QLabel * label0;
    QLabel * label1;
    QLabel * label2;
    QLabel * label3;

private slots:
    void changeSlot();
    void on_show_clicked();
    Mat imageEx(Mat& src);
    Mat ImageLx(Mat& src);
    Mat equalizeHistmy(Mat& src);
    void showEx();
    void showLx();
    void showHist();

signals:
    void mySignal();
};

#endif // THREEWIDGET_H

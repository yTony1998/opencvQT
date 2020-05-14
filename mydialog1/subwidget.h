#ifndef SUBWIDGET_H
#define SUBWIDGET_H

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

class OneWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OneWidget(QWidget *parent = 0);

private:

    QPushButton * Remain;
    QPushButton * Show;
    QPushButton * RgbToGray;
    QPushButton * Binary;
    QPushButton * BMP;

    QLabel *label1;
    QLabel *label2;
    QLabel *label3;
    QLabel *label4;
    Mat img1;

    Mat rgbTogray(Mat& src);
    Mat grayTobinary(Mat& src,int& threshold);
    Mat creatColor(Mat& src,int& n);

    QLineEdit *Myinput1;
    QLineEdit *Myinput2;

private slots:
    void changeSlot();
    void on_show_clicked();
    void on_gray_clicked();
    void on_binary_clicked();
    void on_bmp_clicked();

signals:
    void mySignal();
};

#endif // SUBWIDGET_H

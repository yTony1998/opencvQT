#ifndef FOURWIDGET_H
#define FOURWIDGET_H
#include <QWidget>
#include <QPushButton>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QFileDialog>
#include <QLabel>
#include <QLineEdit>
#include <random>
#include <algorithm>
#define pi 3.14159
#define random(a,b) (rand()%(b-a+1)+a)
using namespace cv;

class FourWidget:public QWidget{
    Q_OBJECT
public:
    explicit FourWidget(QWidget * parent=0);

private:
    Mat img1;
    Mat imgguass;
    QPushButton * Remain;
    QPushButton * Myguass;
    QPushButton * Mysalt;
    QPushButton * Mypossion;
    QPushButton * Mymiddle;
    QPushButton * Mysobel;
    QPushButton * Mypre;
    QPushButton * Mylow;
    QPushButton * Myhigh;
    QPushButton * Open;
    QLabel* label0;
    QLabel* label1;
    QLabel* label2;
    QLabel* label3;
    QLabel* label4;
    QLabel* label5;
    QLabel* label6;
    QLabel* label7;
    QLabel* label8;
    QLineEdit* Myinput1;
    QLineEdit* Myinput2;

    QLineEdit* Myinput3;

    Mat salt(Mat& src,int& n);
    Mat guass(Mat& src);
    Mat bosong(Mat& src);
    Mat middleP(Mat& src);
    Mat sobel(Mat& src,int &n);
    Mat pre(Mat& src,int &n);
    void myMagnitude(Mat& complexImg,Mat& mI);
    void dftshift(Mat& ds);
    void displayDftSpectrum(Mat& dftDst, String winName, bool inverseSpectrum);
    void makeFilter(Mat& filter, int R, bool isLowPassFilter, String winname, int num);
    int possion();
    double U_Random();
private slots:
    void changeSlot();
    void on_show_clicked();
    void mysalt();
    void myguass();
    void mybosong();
    void mymiddle();
    void mysobel();
    void mypre();
    void mylow();
    void myhigh();
signals:
    void mySignal();
};
#endif // FOURWIDGET_H

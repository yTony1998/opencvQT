#ifndef FIVEWIDGET_H
#define FIVEWIDGET_H

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
using namespace cv;
using namespace std;

class Mydeal
{
public:
    Mydeal();
    Mydeal(Mat& src,int & n);
    ~Mydeal();
    void Myshow();


    Mat SobelX(Mat& src,int& n );
    Mat MyPre(Mat& src,int& n);
    Mat MyRobort(Mat& src, int& n);
    Mat MyEdge(Mat& src, int& n);
    Mat MyFS(Mat& mysrc);
    Vec3b RandomColor(int value);


private:
    Mat img;
    int  n;
};

class FiveWidget:public QWidget{
    Q_OBJECT
public:
    explicit FiveWidget(QWidget * parent=nullptr);

private:
    QPushButton * Remain;
    QPushButton * Open;
    QPushButton * Sobel;
    QPushButton * Pre;
    QPushButton * Robort;
    QPushButton * Edge;
    QPushButton * Fs;

    QLabel* label2;
    QLabel* label0;
    QLabel* label1;
    QLabel* label3;
    QLabel* label4;
    QLabel* label5;

    Mat img1;
    int n=100;
    Mydeal *mydeal=new Mydeal(img1,n);
private slots:
    void changeSlot();
    void on_show_clicked();
    void sobel();
    void pre();
    void robort();
    void edge();
    void fs();
signals:
    void mySignal();
};
#endif // FIVEWIDGET_H

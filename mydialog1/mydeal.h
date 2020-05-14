#ifndef MYDEAL_H
#define MYDEAL_H
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
    Mat MyFS();
    Vec3b RandomColor(int value);


private:
    Mat img;
    int  n;
};

#endif // MYDEAL_H

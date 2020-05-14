#ifndef TWOWIDGET_H
#define TWOWIDGET_H

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
class TwoWidget:public QWidget{
    Q_OBJECT
public:
    explicit TwoWidget(QWidget * parent=0);

private:
    Mat img1;
    QPushButton * Remain;
    QPushButton * Open;
    QPushButton * Pmove;
    QPushButton * X;
    QPushButton * Y;
    QPushButton * Rorate;
    QPushButton * K;
    QLineEdit *Myinput1;
    QLineEdit *Myinput2;
    QLineEdit *Myinput3;
    QLineEdit *Myinput4;
    QLabel * label0;
    QLabel * label1;
    QLabel * label2;
    QLabel * label3;
    QLabel * label4;
    QLabel * label5;
    Mat translate(Mat& src,int& n,int& m);
    Mat SymmetryX(Mat& src);
    Mat SymmetryY(Mat& src);
    //Mat BigSmall(Mat& src,int& n);
    Mat MyRarote(Mat& src,int& n);
private slots:
    void changeSlot();
    void on_show_clicked();
    void MovePicture();
    void ForX();
    void ForY();
    void BigSmall();
    void ClickedRa();
signals:
    void mySignal();
};

#endif // TWOWIDGET_H

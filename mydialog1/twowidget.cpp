#include "twowidget.h"


TwoWidget::TwoWidget(QWidget *parent):QWidget (parent){
    this->setWindowTitle("实验二");
    this->resize(800,800);
    this->move(300,0);
   //return main
    Remain = new QPushButton;
    Remain->setParent(this);
    Remain->setText("to main");
    Remain->move(600,600);
    Remain->resize(70,30);
    //open picture
    Open=new QPushButton;
    Open->setParent(this);
    Open->setText("打开图片");
    Open->move(200,50);
    Open->resize(70,30);
    label0 =new QLabel;
    label0->setParent(this);
    label0->setText("SHOW");
    label0->move(0,0);
    label0->resize(180,120);
    // picture move
    Pmove=new QPushButton;
    Pmove->setParent(this);
    Pmove->setText("move");
    Pmove->move(200,100);
    Pmove->resize(70,30);
    Myinput1=new QLineEdit;
    Myinput1->setParent(this);
    Myinput1->move(200,150);
    Myinput1->resize(70,30);
    Myinput2=new QLineEdit;
    Myinput2->setParent(this);
    Myinput2->move(200,200);
    Myinput2->resize(70,30);
    label1=new QLabel;
    label1->setParent(this);
    label1->setText("平移之后");
    label1->move(0,200);
    label1->resize(180,120);

    X=new QPushButton;
    X->setParent(this);
    X->setText("X对称");
    X->move(200,250);
    X->resize(70,30);
    label2=new QLabel;
    label2->setParent(this);
    label2->setText("X对称");
    label2->move(0,400);
    label2->resize(180,120);


    Y=new QPushButton;
    Y->setParent(this);
    Y->setText("Y对称");
    Y->move(200,300);
    Y->resize(70,30);
    label3=new QLabel;
    label3->setParent(this);
    label3->setText("Y对称");
    label3->move(0,600);
    label3->resize(180,120);


    Rorate=new QPushButton;
    Rorate->setParent(this);
    Rorate->setText("RORATE");
    Rorate->move(200,350);
    Rorate->resize(70,30);
    Myinput4=new QLineEdit;
    Myinput4->setParent(this);
    Myinput4->move(200,500);
    Myinput4->resize(70,30);
    label4=new QLabel;
    label4->setParent(this);
    label4->setText("旋转区域");
    label4->move(300,0);
    label4->resize(180,120);

    K=new QPushButton;
    K->setParent(this);
    K->setText("K");
    K->move(200,400);
    K->resize(70,30);
    Myinput3=new QLineEdit;
    Myinput3->setParent(this);
    Myinput3->move(200,450);
    Myinput3->resize(70,30);
    label5=new QLabel;
    label5->setParent(this);
    label5->setText("缩放区域");
    label5->move(300,200);
    label5->resize(180,120);

    QObject::connect(Remain,SIGNAL(clicked()),this,SLOT(changeSlot()));
    QObject::connect(Open,SIGNAL(clicked()),this,SLOT(on_show_clicked()));
    QObject::connect(Pmove,SIGNAL(clicked()),this,SLOT(MovePicture()));
    QObject::connect(X,SIGNAL(clicked()),this,SLOT(ForX()));
    QObject::connect(Y,SIGNAL(clicked()),this,SLOT(ForY()));
    QObject::connect(K,SIGNAL(clicked()),this,SLOT(BigSmall()));
    QObject::connect(Rorate,SIGNAL(clicked()),this,SLOT(ClickedRa()));
}
void TwoWidget::changeSlot(){
    emit mySignal();
}
void TwoWidget::on_show_clicked(){
    QString fileName=QFileDialog::getOpenFileName(this,tr("Open Iamge"),".",tr("Image Flie((*.png *.jpg *.jpeg *.bmp)"));
    if(fileName.isEmpty()){
        return;
    }
    Mat src=imread(fileName.toLatin1().data());
    Size mysize;
    mysize.width=180;
    mysize.height=120;
    Mat dst(mysize,src.type());
    cv::resize(src,dst,mysize,0,0,INTER_LINEAR);
    img1=src;
    cvtColor(dst,dst,CV_BGR2RGB);
    QImage img=QImage((const unsigned char*)(dst.data),dst.cols,dst.rows,dst.cols*dst.channels(),QImage::Format_RGB888);
    this->label0->clear();
    this->label0->setPixmap(QPixmap::fromImage(img));
    this->label0->resize(this->label0->pixmap()->size());
}
Mat TwoWidget::translate(Mat &src,int& n,int& m){
    Mat dst(cvSize( 2*src.rows,  2*src.cols), src.type());
    for (int i = 0; i < src.rows; i++)
    {
        for (int j = 0; j < src.cols; j++)
        {
           if(i+n<2*src.rows||j+m<2*src.cols){
            dst.at<Vec3b>( i+n, j+m)[0] = src.at<Vec3b>(i, j)[0];
            dst.at<Vec3b>( i+n, j+m)[1] = src.at<Vec3b>(i, j)[1];
            dst.at<Vec3b>( i+n, j+m)[2] = src.at<Vec3b>(i, j)[2];
            }
        }
    }
    return dst;
}
void TwoWidget::MovePicture(){
    QString str=this->Myinput1->text();
    int val=str.toInt();
    QString str2=this->Myinput2->text();
    int val2=str2.toInt();
    Mat AfterTran=translate(img1,val,val2);
    Size mysize;
    mysize.width=180;
    mysize.height=120;

    cv::resize(AfterTran,AfterTran,mysize,0,0,INTER_LINEAR);
    cvtColor(AfterTran,AfterTran,CV_BGR2RGB);
    QImage img=QImage((const unsigned char*)(AfterTran.data),AfterTran.cols,AfterTran.rows,AfterTran.cols*AfterTran.channels(),QImage::Format_RGB888);
    this->label1->clear();
    this->label1->setPixmap(QPixmap::fromImage(img));
    this->label1->resize(this->label1->pixmap()->size());
}
Mat TwoWidget::SymmetryX(Mat &src){
    Mat dst(cvSize( src.rows,  src.cols), src.type());
    for (int i = 0; i < src.rows; i++)
    {
        for (int j = 0; j < src.cols; j++)
        {
            dst.at<Vec3b>(i, j)[0] = src.at<Vec3b>(src.rows-i-1, j)[0];
            dst.at<Vec3b>(i, j)[1] = src.at<Vec3b>(src.rows-i-1, j)[1];
            dst.at<Vec3b>(i, j)[2] = src.at<Vec3b>(src.rows-i-1, j)[2];
        }
    }
    return dst;
}
Mat TwoWidget::SymmetryY(Mat &src){
    Mat dst(cvSize( src.rows,  src.cols), src.type());
    for (int i = 0; i < src.rows; i++)
    {
        for (int j = 0; j < src.cols; j++)
        {
            dst.at<Vec3b>(i, j)[0] = src.at<Vec3b>(i, src.cols-j-1)[0];
            dst.at<Vec3b>(i, j)[1] = src.at<Vec3b>(i, src.cols-j-1)[1];
            dst.at<Vec3b>(i, j)[2] = src.at<Vec3b>(i, src.cols-j-1)[2];
        }
    }
    return dst;
}

void TwoWidget::ForX(){
    Mat AfterX=SymmetryX(img1);
    Size mysize;
    mysize.width=180;
    mysize.height=120;
    cv::resize(AfterX,AfterX,mysize,0,0,INTER_LINEAR);
    cvtColor(AfterX,AfterX,CV_BGR2RGB);
    QImage img=QImage((const unsigned char*)(AfterX.data),AfterX.cols,AfterX.rows,AfterX.cols*AfterX.channels(),QImage::Format_RGB888);
    this->label2->clear();
    this->label2->setPixmap(QPixmap::fromImage(img));
    this->label2->resize(this->label2->pixmap()->size());
}
void TwoWidget::ForY(){
    Mat AfterY=SymmetryY(img1);
    Size mysize;
    mysize.width=180;
    mysize.height=120;
    cv::resize(AfterY,AfterY,mysize,0,0,INTER_LINEAR);
    cvtColor(AfterY,AfterY,CV_BGR2RGB);
    QImage img=QImage((const unsigned char*)(AfterY.data),AfterY.cols,AfterY.rows,AfterY.cols*AfterY.channels(),QImage::Format_RGB888);
    this->label3->clear();
    this->label3->setPixmap(QPixmap::fromImage(img));
    this->label3->resize(this->label3->pixmap()->size());
}
void TwoWidget::BigSmall(){
    QString str=this->Myinput3->text();
    int val=str.toInt();
    Size mysize;
    mysize.width=val*90;
    mysize.height=val*60;
    Mat dst;
    cv::resize(img1,dst,mysize,0,0,INTER_LINEAR);
    cvtColor(dst,dst,CV_BGR2RGB);
    QImage img=QImage((const unsigned char*)(dst.data),dst.cols,dst.rows,dst.cols*dst.channels(),QImage::Format_RGB888);
    this->label5->clear();
    this->label5->setPixmap(QPixmap::fromImage(img));
    this->label5->resize(this->label5->pixmap()->size());
}
Mat TwoWidget::MyRarote(Mat &src, int &n){
    int ycenter = src.rows / 2;
    int xcenter = src.cols / 2;
    Mat dst(cvSize( 2*src.rows,  2*src.cols), src.type());
    //n=n/3.14*180;//应该是直接可以是角度制不是弧度制
    for (int i = 1; i < src.rows; i++)
    {
        for (int j = 1; j < src.cols; j++)
        {
            //不知道为什么公式是对的，现象有点不对
            int x = ceil((j - xcenter) * cos(n) - (i - ycenter) * sin(n)+2*xcenter);
            int y = ceil((j - xcenter) * sin(n) - (i - ycenter) * cos(n) +2* ycenter);
            y=2*src.rows-y;
            if(x>0&&x<2*src.rows-1&&y>0 && y < 2 * src.cols - 1){
                dst.at<Vec3b>(y, x)[0] = src.at<Vec3b>(i,j)[0];
                dst.at<Vec3b>(y, x)[1] = src.at<Vec3b>(i,j)[1];
                dst.at<Vec3b>(y, x)[2] = src.at<Vec3b>(i,j)[2];
            }
        }
    }
    return dst;
}
void TwoWidget::ClickedRa(){
    QString str=this->Myinput4->text();
    int val=str.toDouble();
//    Mat AfterRo=MyRarote(img1,val);

    double angle = -45;
    cv::Point2f center(img1.cols / 2, img1.rows / 2);
    cv::Mat rot = cv::getRotationMatrix2D(center, angle, 1);
    cv::Rect bbox = cv::RotatedRect(center, img1.size(), val).boundingRect();

    rot.at<double>(0, 2) += bbox.width / 2.0 - center.x;
    rot.at<double>(1, 2) += bbox.height / 2.0 - center.y;

    cv::Mat AfterRo;
    cv::warpAffine(img1, AfterRo, rot, bbox.size());








    Size mysize;
    mysize.width=180;
    mysize.height=120;
    cv::resize(AfterRo,AfterRo,mysize,0,0,INTER_LINEAR);
    cvtColor(AfterRo,AfterRo,CV_BGR2RGB);
    QImage img=QImage((const unsigned char*)(AfterRo.data),AfterRo.cols,AfterRo.rows,AfterRo.cols*AfterRo.channels(),QImage::Format_RGB888);
    this->label4->clear();
    this->label4->setPixmap(QPixmap::fromImage(img));
    this->label4->resize(this->label4->pixmap()->size());
}

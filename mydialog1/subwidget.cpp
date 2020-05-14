#include "subwidget.h"

OneWidget::OneWidget(QWidget *parent) : QWidget(parent)
{
    //界面按钮和显示区域在构造函数中的初始化
     this->setWindowTitle("实验一");
    //return main
     Remain = new QPushButton;
     Remain->setParent(this);
     Remain->setText("to main");
     Remain->move(600,600);
     Remain->resize(70,30);
     // show  picture
     Show = new QPushButton;
     Show->setParent(this);
     Show->setText("打开图片");
     Show->move(200,50);
     Show->resize(70,30);
     label1 = new QLabel;
     label1->setParent(this);
     label1->setText("图片");
     label1->move(0,0);
     label1->resize(180,120);

     //rgbtogray
     RgbToGray =new QPushButton;
     RgbToGray->setParent(this);
     RgbToGray->setText("gray");
     RgbToGray->move(200,100);
     RgbToGray->resize(70,30);
     label2 = new QLabel;
     label2->setParent(this);
     label2->setText("GRAY");
     label2->move(0,200);
     label2->resize(180,120);
     //graytobinary
     Binary = new QPushButton;
     Binary->setParent(this);
     Binary->setText("binary");
     Binary->move(200,150);
     Binary->resize(70,30);
     label3 = new QLabel;
     label3->setParent(this);
     label3->setText("BINARY");
     label3->move(0,400);
     label3->resize(180,120);
     Myinput1 =new QLineEdit;
     Myinput1->setParent(this);
     Myinput1->move(200,200);
     Myinput1->resize(70,30);
     //bmp 调色版
     BMP=new QPushButton;
     BMP->setParent(this);
     BMP->setText("bmp");
     BMP->move(200,250);
     BMP->resize(70,30);
     label4 = new QLabel;
     label4->setParent(this);
     label4->setText("BMP");
     label4->move(0,600);
     label4->resize(180,120);
     Myinput2 =new QLineEdit;
     Myinput2->setParent(this);
     Myinput2->move(200,300);
     Myinput2->resize(70,30);

     //信息槽的添加，与按钮绑定进行响应
     QObject::connect(Remain,SIGNAL(clicked()),this,SLOT(changeSlot()));
     QObject::connect(Show,SIGNAL(clicked()),this,SLOT(on_show_clicked()));
     QObject::connect(RgbToGray,SIGNAL(clicked()),this,SLOT(on_gray_clicked()));
     QObject::connect(Binary,SIGNAL(clicked()),this,SLOT(on_binary_clicked()));
     QObject::connect(BMP,SIGNAL(clicked()),this,SLOT(on_bmp_clicked()));
     this->resize(900,900);

}

void OneWidget::changeSlot()
{
    emit mySignal();
}
//打开图片函数
void OneWidget::on_show_clicked(){
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
    img1=dst;
    cvtColor(dst,dst,CV_BGR2RGB);
    QImage img=QImage((const unsigned char*)(dst.data),dst.cols,dst.rows,dst.cols*dst.channels(),QImage::Format_RGB888);
    this->label1->clear();
    this->label1->setPixmap(QPixmap::fromImage(img));
    this->label1->resize(this->label1->pixmap()->size());
}
//转灰度函数
void OneWidget::on_gray_clicked(){
    img1=rgbTogray(img1);
    cvtColor(img1,img1,CV_BGR2RGB);
    QImage img=QImage((const unsigned char*)(img1.data),img1.cols,img1.rows,img1.cols*img1.channels(),QImage::Format_RGB888);
    this->label2->clear();
    this->label2->setPixmap(QPixmap::fromImage(img));
    this->label2->resize(this->label2->pixmap()->size());
}
//二值化函数
void OneWidget::on_binary_clicked(){
    QString str=this->Myinput1->text();
    int val=str.toInt();
    Mat binary;
    binary=grayTobinary(img1,val);
    cvtColor(binary,binary,CV_BGR2RGB);
    QImage img=QImage((const unsigned char*)(binary.data),binary.cols,binary.rows,binary.cols*binary.channels(),QImage::Format_RGB888);
    this->label3->clear();
    this->label3->setPixmap(QPixmap::fromImage(img));
    this->label3->resize(this->label3->pixmap()->size());
}
//bmp图片函数
void OneWidget::on_bmp_clicked(){
    QString str=this->Myinput2->text();
    int val=str.toInt();
    Mat bmp;
    bmp=creatColor(img1,val);
    cvtColor(bmp,bmp,CV_BGR2RGB);
    QImage img=QImage((const unsigned char*)(bmp.data),bmp.cols,bmp.rows,bmp.cols*bmp.channels(),QImage::Format_RGB888);
    this->label4->clear();
    this->label4->setPixmap(QPixmap::fromImage(img));
    this->label4->resize(this->label4->pixmap()->size());
}
Mat OneWidget::rgbTogray(Mat &src){
    Mat gray(src.size(), CV_8UC3);
    for (int i = 0; i < src.rows; i++)
    {
        for (int j = 0; j < src.cols; j++)
        {
            gray.at<Vec3b>(i, j)[0] = 0.2989 * src.at<Vec3b>(i, j)[0] + 0.5870 * src.at<Vec3b>(i, j)[1] + 0.1140 * src.at<Vec3b>(i, j)[2];
            gray.at<Vec3b>(i, j)[1] = 0.2989 * src.at<Vec3b>(i, j)[0] + 0.5870 * src.at<Vec3b>(i, j)[1] + 0.1140 * src.at<Vec3b>(i, j)[2];
            gray.at<Vec3b>(i, j)[2] = 0.2989 * src.at<Vec3b>(i, j)[0] + 0.5870 * src.at<Vec3b>(i, j)[1] + 0.1140 * src.at<Vec3b>(i, j)[2];
        }
    }
    return gray;
}

Mat OneWidget::grayTobinary(Mat &src, int& threshold){
    Mat binary(src.size(), CV_8UC3);
    for (int i = 0; i < src.rows; i++)
    {
        for (int j = 0; j < src.cols; j++)
        {
            if (src.at<Vec3b>(i, j)[0] < threshold) {
                binary.at<Vec3b>(i, j)[0] = 255;
                binary.at<Vec3b>(i, j)[1] = 255;
                binary.at<Vec3b>(i, j)[2] = 255;
            }
            else {
                binary.at<Vec3b>(i, j)[0] = 1;
                binary.at<Vec3b>(i, j)[1] = 1;
                binary.at<Vec3b>(i, j)[2] = 1;
            }

        }
    }
    return binary;
}
Mat OneWidget::creatColor(Mat &src,int &n){
    Mat dst(src.size(), CV_8UC3);
        for (int i = 0; i < src.rows; i++)
        {
            for (int j = 0; j < src.cols; j++)
            {

                dst.at<Vec3b>(i, j)[0] = src.at<Vec3b>(i, j)[0] / n+1;
                dst.at<Vec3b>(i, j)[1] = src.at<Vec3b>(i, j)[0] / n;
                dst.at<Vec3b>(i, j)[2] = src.at<Vec3b>(i, j)[0];
            }
        }
        return dst;
}

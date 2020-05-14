#include "threewidget.h"
#include <QtDebug>
ThreeWidget::ThreeWidget(QWidget *parent):QWidget (parent){
    this->setWindowTitle("实验三");
    this->move(100,100);
    this->resize(800,800);
    Remain = new QPushButton;
    Remain->setParent(this);
    Remain->setText("to main");
    Remain->move(600,600);
    Remain->resize(70,30);

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
    Ex=new QPushButton;
    Ex->setParent(this);
    Ex->setText("指数");
    Ex->move(200,100);
    Ex->resize(70,30);
    label1=new QLabel;
    label1->setParent(this);
    label1->move(0,200);
    label1->setText("Ex");
    label1->resize(180,120);

    Lx=new QPushButton;
    Lx->setParent(this);
    Lx->setText("对数");
    Lx->move(200,150);
    Lx->resize(70,30);
    label2=new QLabel;
    label2->setParent(this);
    label2->move(0,400);
    label2->resize(180,120);
    label2->setText("Lx");

    Hist=new QPushButton;
    Hist->setParent(this);
    Hist->setText("直方图均衡");
    Hist->move(200,200);
    Hist->resize(70,30);
    label3=new QLabel;
    label3->setParent(this);
    label3->move(0,600);
    label3->resize(180,120);
    label3->setText("直方图");

    QObject::connect(Remain,SIGNAL(clicked()),this,SLOT(changeSlot()));
    QObject::connect(Open,SIGNAL(clicked()),this,SLOT(on_show_clicked()));
    QObject::connect(Ex,SIGNAL(clicked()),this,SLOT(showEx()));
    QObject::connect(Lx,SIGNAL(clicked()),this,SLOT(showLx()));
    QObject::connect(Hist,SIGNAL(clicked()),this,SLOT(showHist()));
}
void ThreeWidget::changeSlot(){
    emit mySignal();
}
void ThreeWidget::on_show_clicked(){
    QString fileName=QFileDialog::getOpenFileName(this,tr("Open Iamge"),".",tr("Image Flie((*.png *.jpg *.jpeg *.bmp)"));
    if(fileName.isEmpty()){
        return;
    }
    Mat src=imread(fileName.toLatin1().data());


//    qDebug()<<"40";
    Size mysize;
    mysize.width=180;
    mysize.height=120;
    Mat dst(mysize,src.type());

    img1=src;

    cv::resize(src,dst,mysize,0,0,INTER_LINEAR);
//    qDebug()<<"36";
//    qDebug()<<"42";
    cvtColor(dst,dst,CV_BGR2RGB);
    QImage img=QImage((const unsigned char*)(dst.data),dst.cols,dst.rows,dst.cols*dst.channels(),QImage::Format_RGB888);
    this->label0->clear();
//    qDebug()<<"46";
    this->label0->setPixmap(QPixmap::fromImage(img));
    this->label0->resize(this->label0->pixmap()->size());
}

Mat ThreeWidget::imageEx(Mat& src){
    float pixelsEx[255];
    Mat MyimageEx(src.size(),CV_32FC3);
    for (int i=0;i<255;i++) {
        pixelsEx[i]=pow(2,0.05*(i-1))-1;
    }
    for (int i=0;i<src.rows;i++) {
        for (int j=0;j<src.cols;j++) {
            MyimageEx.at<Vec3f>(i,j)[0]=pixelsEx[src.at<Vec3b>(i,j)[0]];
            MyimageEx.at<Vec3f>(i,j)[1]=pixelsEx[src.at<Vec3b>(i,j)[1]];
            MyimageEx.at<Vec3f>(i,j)[2]=pixelsEx[src.at<Vec3b>(i,j)[2]];
        }
    }
    //qDebug()<<"105";
    normalize(MyimageEx,MyimageEx,0,255,CV_MINMAX);
    convertScaleAbs(MyimageEx,MyimageEx);
    return MyimageEx;
}
void ThreeWidget::showEx(){

    Mat AfterEx=imageEx(img1);
    Size mysize;
    mysize.width=180;
    mysize.height=120;
    //qDebug()<<"115";
    cv::resize(AfterEx,AfterEx,mysize,0,0,INTER_LINEAR);
    cvtColor(AfterEx,AfterEx,CV_BGR2RGB);
    QImage img=QImage((const unsigned char*)(AfterEx.data),AfterEx.cols,AfterEx.rows,AfterEx.cols*AfterEx.channels(),QImage::Format_RGB888);
    this->label1->clear();
    this->label1->setPixmap(QPixmap::fromImage(img));
    this->label1->resize(this->label1->pixmap()->size());
}


Mat ThreeWidget::ImageLx(Mat& src){
    float pixelsLx[255];
    Mat MyimageLx(src.size(),CV_32FC3);
    for (int i=0;i<255;i++) {
        pixelsLx[i]=3*log(1 + i);
    }
    for (int i=0;i<src.rows;i++) {
        for (int j=0;j<src.cols;j++) {
            MyimageLx.at<Vec3f>(i,j)[0]=pixelsLx[src.at<Vec3b>(i,j)[0]];
            MyimageLx.at<Vec3f>(i,j)[1]=pixelsLx[src.at<Vec3b>(i,j)[1]];
            MyimageLx.at<Vec3f>(i,j)[2]=pixelsLx[src.at<Vec3b>(i,j)[2]];
        }
    }
    qDebug()<<"139";
    normalize(MyimageLx,MyimageLx,0,255,CV_MINMAX);
    convertScaleAbs(MyimageLx,MyimageLx);
    return MyimageLx;

}
void ThreeWidget::showLx(){

    Mat AfterLx=ImageLx(img1);
    Size mysize;
    mysize.width=180;
    mysize.height=120;
    qDebug()<<"150";
    cv::resize(AfterLx,AfterLx,mysize,0,0,INTER_LINEAR);
    cvtColor(AfterLx,AfterLx,CV_BGR2RGB);
    QImage img=QImage((const unsigned char*)(AfterLx.data),AfterLx.cols,AfterLx.rows,AfterLx.cols*AfterLx.channels(),QImage::Format_RGB888);
    this->label2->clear();
    this->label2->setPixmap(QPixmap::fromImage(img));
    this->label2->resize(this->label2->pixmap()->size());
}

Mat ThreeWidget::equalizeHistmy(Mat& src){
    Mat MyHist=src.clone();
    int sum=0;
    int Green[256]={0};
    int Blue[256]={0};
    int Red[256]={0};
    double green_prob[256]={0};
    double blue_prob[256]={0};
    double red_prob[256]={0};
    double green_distribution[256]={0};
    double blue_distribution[256]={0};
    double red_distribution[256]={0};
    int green_equa[256]={0};
    int blue_equa[256]={0};
    int red_equa[256]={0};
    sum=src.cols*src.rows;
    for (int i=0;i<src.rows;i++) {
        for (int j=0;j<src.cols;j++) {
            int B=src.at<Vec3b>(i,j)[0];
            int G=src.at<Vec3b>(i,j)[2];
            int R=src.at<Vec3b>(i,j)[1];
            Blue[B]++;
            Green[G]++;
            Red[R]++;
        }
    }
    for (int i=0;i<256;i++) {
        blue_prob[i]=((double)Blue[i]/sum);
        green_prob[i]=((double)Green[i]/sum);
        red_prob[i]=((double)Red[i]/sum);
    }
    blue_distribution[0]=blue_prob[0];
    green_distribution[0]=green_prob[0];
    red_distribution[0]=red_prob[0];
    for (int i=1;i<256;i++) {
        blue_distribution[i]=blue_distribution[i-1]+blue_prob[i];
        green_distribution[i]=green_distribution[i-1]+green_prob[i];
        red_distribution[i]=red_distribution[i-1]+red_prob[i];
    }
    for (int i=0;i<255;i++) {
        blue_equa[i]=(uchar)(255*blue_distribution[i]+0.5);
        green_equa[i]=(uchar)(255*green_distribution[i]+0.5);
        red_equa[i]=(uchar)(255*red_distribution[i]+0.5);
        //qDebug()<<blue_equa[i];
    }
    for (int i=0;i<MyHist.rows;i++) {
        for (int j=0;j<MyHist.cols;j++) {
            MyHist.at<Vec3b>(i,j)[0]=blue_equa[MyHist.at<Vec3b>(i,j)[0]];
            MyHist.at<Vec3b>(i,j)[1]=green_equa[MyHist.at<Vec3b>(i,j)[1]];
            MyHist.at<Vec3b>(i,j)[2]=red_equa[MyHist.at<Vec3b>(i,j)[2]];
        }
    }
    normalize(MyHist,MyHist,0,255,CV_MINMAX);
    convertScaleAbs(MyHist,MyHist);
    return MyHist;
}

void ThreeWidget::showHist(){

    Mat AfterHist=equalizeHistmy(img1);
    Size mysize;
    mysize.width=180;
    mysize.height=120;
    qDebug()<<"215";
    cv::resize(AfterHist,AfterHist,mysize,0,0,INTER_LINEAR);
    cvtColor(AfterHist,AfterHist,CV_BGR2RGB);
    QImage img=QImage((const unsigned char*)(AfterHist.data),AfterHist.cols,AfterHist.rows,AfterHist.cols*AfterHist.channels(),QImage::Format_RGB888);
    this->label3->clear();
    this->label3->setPixmap(QPixmap::fromImage(img));
    this->label3->resize(this->label3->pixmap()->size());
}

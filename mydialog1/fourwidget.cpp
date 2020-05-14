#include"fourwidget.h"
#include<QtDebug>

FourWidget::FourWidget(QWidget *parent):QWidget (parent){
    this->setWindowTitle("实验四");
    this->move(100,100);
    this->resize(1000,1000);
    Remain = new QPushButton;
    Remain->setParent(this);
    Remain->setText("to main");
    Remain->move(600,600);
    Remain->resize(70,30);

    label0 = new QLabel;
    label0->setParent(this);
    label0->setText("图片");
    label0->move(0,0);
    label0->resize(180,120);

    label1 = new QLabel;
    label1->setParent(this);
    label1->setText("Guass");
    label1->move(0,200);
    label1->resize(180,120);

    label2 = new QLabel;
    label2->setParent(this);
    label2->setText("Salt");
    label2->move(0,400);
    label2->resize(180,120);

    label3 = new QLabel;
    label3->setParent(this);
    label3->setText("Possion");
    label3->move(0,600);
    label3->resize(180,120);

    label4 = new QLabel;
    label4->setParent(this);
    label4->setText("Middle");
    label4->move(400,0);
    label4->resize(180,120);

    label5 = new QLabel;
    label5->setParent(this);
    label5->setText("Sobel");
    label5->move(400,200);
    label5->resize(180,120);

    label6 = new QLabel;
    label6->setParent(this);
    label6->setText("Pre");
    label6->move(400,400);
    label6->resize(180,120);


    label7 = new QLabel;
    label7->setParent(this);
    label7->setText("Low");
    label7->move(400,600);
    label7->resize(180,120);

    label8 = new QLabel;
    label8->setParent(this);
    label8->setText("Low");
    label8->move(400,800);
    label8->resize(180,120);

    Open=new QPushButton;
    Open->setParent(this);
    Open->setText("打开图片");
    Open->move(200,50);
    Open->resize(70,30);

    Myguass=new QPushButton;
    Myguass->setParent(this);
    Myguass->setText("guass");
    Myguass->move(200,100);
    Myguass->resize(70,30);

    Mysalt=new QPushButton;
    Mysalt->setParent(this);
    Mysalt->setText("slat");
    Mysalt->move(200,150);
    Mysalt->resize(70,30);

    Mypossion=new QPushButton;
    Mypossion->setParent(this);
    Mypossion->setText("possion");
    Mypossion->move(200,200);
    Mypossion->resize(70,30);

    Mymiddle=new QPushButton;
    Mymiddle->setParent(this);
    Mymiddle->setText("middle");
    Mymiddle->move(200,250);
    Mymiddle->resize(70,30);


    Mysobel=new QPushButton;
    Mysobel->setParent(this);
    Mysobel->setText("sobel");
    Mysobel->move(200,300);
    Mysobel->resize(70,30);

    Mypre=new QPushButton;
    Mypre->setParent(this);
    Mypre->setText("pre");
    Mypre->move(200,350);
    Mypre->resize(70,30);


    Mylow=new QPushButton;
    Mylow->setParent(this);
    Mylow->setText("low");
    Mylow->move(200,400);
    Mylow->resize(70,30);

    Myhigh=new QPushButton;
    Myhigh->setParent(this);
    Myhigh->setText("high");
    Myhigh->move(200,450);
    Myhigh->resize(70,30);

    Myinput1=new QLineEdit;
    Myinput1->setParent(this);
    Myinput1->move(200,500);
    Myinput1->resize(70,30);

    Myinput2=new QLineEdit;
    Myinput2->setParent(this);
    Myinput2->move(200,550);
    Myinput2->resize(70,30);



    Myinput3=new QLineEdit;
    Myinput3->setParent(this);
    Myinput3->move(200,600);
    Myinput3->resize(70,30);

    QObject::connect(Remain,SIGNAL(clicked()),this,SLOT(changeSlot()));
    QObject::connect(Open,SIGNAL(clicked()),this,SLOT(on_show_clicked()));
    QObject::connect(Mysalt,SIGNAL(clicked()),this,SLOT(mysalt()));
    QObject::connect(Myguass,SIGNAL(clicked()),this,SLOT(myguass()));
    QObject::connect(Mypossion,SIGNAL(clicked()),this,SLOT(mybosong()));
    QObject::connect(Mymiddle,SIGNAL(clicked()),this,SLOT(mymiddle()));
    QObject::connect(Mysobel,SIGNAL(clicked()),this,SLOT(mysobel()));
    QObject::connect(Mypre,SIGNAL(clicked()),this,SLOT(mypre()));
    QObject::connect(Mylow,SIGNAL(clicked()),this,SLOT(mylow()));
    QObject::connect(Myhigh,SIGNAL(clicked()),this,SLOT(myhigh()));

}
void FourWidget::changeSlot(){
    emit mySignal();
}
void FourWidget::on_show_clicked(){
    QString fileName=QFileDialog::getOpenFileName(this,tr("Open Iamge"),".",tr("Image Flie((*.png *.jpg *.jpeg *.bmp)"));
    if(fileName.isEmpty()){
        return;
    }
    Mat src=imread(fileName.toLatin1().data());


    Size mysize;
    mysize.width=180;
    mysize.height=120;
    Mat dst(mysize,src.type());

    img1=src;
    //imshow("see1",img1);
    cv::resize(src,dst,mysize,0,0,INTER_LINEAR);
    cvtColor(dst,dst,CV_BGR2RGB);
    QImage img=QImage((const unsigned char*)(dst.data),dst.cols,dst.rows,dst.cols*dst.channels(),QImage::Format_RGB888);
    this->label0->clear();
    this->label0->setPixmap(QPixmap::fromImage(img));
    this->label0->resize(this->label0->pixmap()->size());

}

Mat FourWidget::salt(Mat &src, int &n){
    //qDebug()<<"161";
    for (int k = 0; k < n; k++)
    {
        int i = rand() % src.cols;
        int j = rand() % src.rows;
        src.at<uchar>(j, i) = 255;
    }
    return src;
}
void FourWidget::mysalt(){
    Mat src(img1.size(),img1.type());
    cvtColor(img1,src,CV_BGR2GRAY);
    QString str=this->Myinput1->text();
    int val=str.toInt();
    Size mysize;
    mysize.width=180;
    mysize.height=120;
    src=salt(src,val);
    imgguass=src;
    cv::resize(src,src,mysize,0,0,INTER_LINEAR);


    QImage img=QImage((const unsigned char*)(src.data),src.cols,src.rows,src.cols*src.channels(),QImage::Format_Indexed8);
    this->label2->clear();
    this->label2->setPixmap(QPixmap::fromImage(img));
    this->label2->resize(this->label2->pixmap()->size());
}

Mat FourWidget::guass(Mat &src){
    Mat dst = src.clone();
        const int G = 256;
        double sigma = 20;
        srand((unsigned)time(NULL));
        for (int i = 0; i < src.rows; i++)
        {
            for (int j = 0; j < src.cols-1; j++)
            {
                double gamma = random(0, 1);
                double phi = random(0, 1);
                double z1 = sigma * cos(2 * pi * phi) * sqrt(-2 * log(gamma));
                double z2 = sigma * sin(2 * pi * phi) * sqrt(-2 * log(gamma));

                double tmpxy = src.at<uchar>(i, j) + z1;
                double tmpxy1 = src.at<uchar>(i, j + 1) + z2;


                if (tmpxy < 0)
                    dst.at<uchar>(i, j) = 0;
                else if (tmpxy > G - 1)
                    dst.at<uchar>(i, j) = G - 1;
                else
                    dst.at<uchar>(i, j) = static_cast<int>(tmpxy);


                if (tmpxy1 < 0)
                    dst.at<uchar>(i, j + 1) = 0;
                else if (tmpxy > G - 1)
                    dst.at<uchar>(i, j + 1) = G - 1;
                else
                    dst.at<uchar>(i, j + 1) = static_cast<int>(tmpxy1);

            }
        }
        return dst;
}
void FourWidget::myguass(){
    Mat src(img1.size(),img1.type());
    cvtColor(img1,src,CV_BGR2GRAY);

    Size mysize;
    mysize.width=180;
    mysize.height=120;
    src=guass(src);

    cv::resize(src,src,mysize,0,0,INTER_LINEAR);


    QImage img=QImage((const unsigned char*)(src.data),src.cols,src.rows,src.cols*src.channels(),QImage::Format_Indexed8);
    this->label1->clear();
    this->label1->setPixmap(QPixmap::fromImage(img));
    this->label1->resize(this->label1->pixmap()->size());
}
double FourWidget::U_Random(){
    double f;
    f = (float)(rand() % 100);
    return f / 100;
}
int FourWidget::possion(){
    int Lambda = 50, k = 0;
        long double p = 1.0;
        long double l = exp(-Lambda);  /* 为了精度，才定义为long double的，exp(-Lambda)是接近0的小数*/
        while (p >= l)
        {
            double u = U_Random();
            p *= u;
            k++;
        }
        return k - 1;
}
Mat FourWidget::bosong(Mat &src){
    Mat dst = src.clone();
        double sigma = 20;
        const int G = 256;
        const int lamda = 1;
        srand((unsigned)time(NULL));
        //normalize(dst, dst, 1, 0, NORM_MINMAX);
        for (int i = 0; i < src.rows; i++)
        {
            for (int j = 0; j < src.cols - 1; j++)
            {
                double u = U_Random();
                int p = possion();
                //printf("%d\n", p);
                double tmpxy = src.at<uchar>(i, j) + p;


                if (tmpxy < 0)
                    dst.at<uchar>(i, j) = 0;
                else if (tmpxy > G - 1)
                    dst.at<uchar>(i, j) = G - 1;
                else
                    dst.at<uchar>(i, j) = (tmpxy);

            }

        }
        return dst;
}
void FourWidget::mybosong(){

    Mat src(img1.size(),img1.type());
    cvtColor(img1,src,CV_BGR2GRAY);

    Size mysize;
    mysize.width=180;
    mysize.height=120;
    src=bosong(src);

    cv::resize(src,src,mysize,0,0,INTER_LINEAR);


    QImage img=QImage((const unsigned char*)(src.data),src.cols,src.rows,src.cols*src.channels(),QImage::Format_Indexed8);
    this->label3->clear();
    this->label3->setPixmap(QPixmap::fromImage(img));
    this->label3->resize(this->label3->pixmap()->size());
}

Mat FourWidget::middleP(Mat &src){
    for (int i = 1; i < src.rows; i++)
    {
        for (int j = 1; j < src.cols; j++) {
            if ((i - 1 >= 0) && (j - 1) >= 0 && (i + 1) < src.rows && (j + 1) < src.cols)
            {
                int a[9] = { src.at<uchar>(i - 1, j - 1) , src.at<uchar>(i, j - 1) , src.at<uchar>(i + 1, j - 1) ,
                    src.at<uchar>(i - 1, j) , src.at<uchar>(i, j) , src.at<uchar>(i + 1, j) ,
                src.at<uchar>(i - 1, j + 1) , src.at<uchar>(i, j + 1) , src.at<uchar>(i + 1, j + 1) };
                std::sort(a, a + 9);
                src.at<uchar>(i, j) = a[4];

            }
        }

    }
    return src;
}
void FourWidget::mymiddle(){
    Mat src(imgguass.size(),imgguass.type());
//    cvtColor(imgguass,src,CV_BGR2GRAY);

    Size mysize;
    mysize.width=180;
    mysize.height=120;
    src=middleP(imgguass);

    cv::resize(src,src,mysize,0,0,INTER_LINEAR);

    qDebug()<<"342";
    QImage img=QImage((const unsigned char*)(src.data),src.cols,src.rows,src.cols*src.channels(),QImage::Format_Indexed8);
    this->label4->clear();
    this->label4->setPixmap(QPixmap::fromImage(img));
    this->label4->resize(this->label4->pixmap()->size());

}

Mat FourWidget::sobel(Mat &src,int & n){
    Mat dst(cvSize(src.rows, src.cols) , src.type());
        for (int i = 1; i < src.rows; i++)
        {
            for (int j = 1; j < src.cols; j++) {
                if ((i - 1 >= 0) && (j - 1) >= 0 && (i + 1) < src.rows && (j + 1) < src.cols)
                {
                    if (abs(src.at<uchar>(i - 1, j - 1) - src.at<uchar>(i + 1, j - 1) +
                        2 * src.at<uchar>(i - 1, j) - 2 * src.at<uchar>(i + 1, j) +
                        src.at<uchar>(i - 1, j + 1) - src.at<uchar>(i + 1, j + 1)) > n)
                        dst.at<uchar>(i, j) = 255;
                    else
                        dst.at<uchar>(i, j) = 0;
                }
            }

        }
        return  dst;
}
void FourWidget::mysobel(){

    Mat src(img1.size(),img1.type());
    cvtColor(img1,src,CV_BGR2GRAY);
    QString str=this->Myinput2->text();
    int val=str.toInt();
    Size mysize;
    mysize.width=180;
    mysize.height=120;
    src=sobel(src,val);

    cv::resize(src,src,mysize,0,0,INTER_LINEAR);


    QImage img=QImage((const unsigned char*)(src.data),src.cols,src.rows,src.cols*src.channels(),QImage::Format_Indexed8);
    this->label5->clear();
    this->label5->setPixmap(QPixmap::fromImage(img));
    this->label5->resize(this->label5->pixmap()->size());

}

Mat FourWidget::pre(Mat &src,int & n ){
    Mat dst(cvSize(src.rows, src.cols), src.type());
        for (int i = 1; i < src.rows; i++)
        {
            for (int j = 1; j < src.cols; j++) {
                if ((i - 1 >= 0) && (j - 1) >= 0 && (i + 1) < src.rows && (j + 1) < src.cols)
                {
                    if (abs(src.at<uchar>(i - 1, j - 1) - src.at<uchar>(i + 1, j - 1)  +
                        src.at<uchar>(i - 1, j + 1) - src.at<uchar>(i + 1, j + 1)) > n)
                        dst.at<uchar>(i, j) = 255;
                    else
                        dst.at<uchar>(i, j) = 0;
                }
            }

        }
        return  dst;
}
void FourWidget::mypre(){
    Mat src(img1.size(),img1.type());
    cvtColor(img1,src,CV_BGR2GRAY);

    QString str=this->Myinput3->text();
    int val=str.toInt();


    Size mysize;
    mysize.width=180;
    mysize.height=120;
    src=pre(src,val);

    cv::resize(src,src,mysize,0,0,INTER_LINEAR);


    QImage img=QImage((const unsigned char*)(src.data),src.cols,src.rows,src.cols*src.channels(),QImage::Format_Indexed8);
    this->label6->clear();
    this->label6->setPixmap(QPixmap::fromImage(img));
    this->label6->resize(this->label6->pixmap()->size());

}

void FourWidget::myMagnitude(Mat &complexImg, Mat &mI){
    Mat planes[2];
    split(complexImg, planes);
    magnitude(planes[0], planes[1], mI);
}

void FourWidget::dftshift(Mat &ds){
    int cx = ds.cols / 2;//图像的中心点x 坐标
    int cy = ds.rows / 2;//图像的中心点y 坐标
    Mat q0 = ds(Rect(0, 0, cx, cy));//左上
    Mat q1 = ds(Rect(cx, 0, cx, cy));//右上
    Mat q2 = ds(Rect(0, cy, cx, cy));//左下
    Mat q3 = ds(Rect(cx, cy, cx, cy));//右下
    Mat tmp;
    q0.copyTo(tmp);
    q3.copyTo(q0);
    tmp.copyTo(q3);
    q1.copyTo(tmp);
    q2.copyTo(q1);
    tmp.copyTo(q2);
}

void FourWidget::displayDftSpectrum(Mat &dftDst, String winName, bool inverseSpectrum){
    Mat magI;
    myMagnitude(dftDst, magI);
    if (!inverseSpectrum)//如果是正向傅里叶变换谱
    {
        magI += Scalar::all(1);
        log(magI, magI);
    }
    normalize(magI, magI, 0, 255, NORM_MINMAX);
    //imshow(winName, magI);
    imwrite(winName + ".jpg", magI);
    //return magI;
}

void FourWidget::makeFilter(Mat &filter, int R, bool isLowPassFilter, String winname, int num){
    int cx = filter.cols / 2, cy = filter.rows / 2;
        int R2 = R * R;
        if (num == 0)
        {
            for (int i = 0; i < filter.rows; i++)
            {
                Vec2d* pf = filter.ptr<Vec2d>(i);
                for (int j = 0; j < filter.cols; j++)
                {
                    int r2 = (j - cx) * (j - cx) + (i - cy) * (i - cy);
                    if (r2 < R2)
                    {
                        pf[j][0] = 1;
                        pf[j][1] = pf[j][0];
                    }
                }
            }
            if (!isLowPassFilter)
            {
                filter = Scalar::all(1) - filter;
            }
        }
        else if (num == 1) {
            for (int i = 0; i < filter.rows; i++)
            {
                Vec2d* pf = filter.ptr<Vec2d>(i);
                for (int j = 0; j < filter.cols; j++)
                {
                    int r2 = (j - cx) * (j - cx) + (i - cy) * (i - cy);
                    if (r2 < R2)
                    {
                        pf[j][0] = 1 / (1 + pow(r2 / R2, 3));
                        pf[j][1] = pf[j][0];
                    }
                }
            }
            if (!isLowPassFilter)
            {
                filter = Scalar::all(1) - filter;
            }
        }

        Mat displayFilter;
        extractChannel(filter, displayFilter, 0);
}
void FourWidget::mylow(){
    Mat src1=imgguass;
    src1.convertTo(src1, CV_64FC2);
    Mat dftDst(src1.size(), CV_64FC2);

    Mat filter(src1.size(), CV_64FC2, Scalar::all(0));
    dft(src1, dftDst, DFT_COMPLEX_OUTPUT, 0);
    dftshift(dftDst);
    makeFilter(filter, 50, false, "1", 1);
    Mat fftTemp = dftDst.mul(filter);
    Mat srcFiltered;
    dft(fftTemp, srcFiltered, DFT_INVERSE);
    displayDftSpectrum(srcFiltered, "filtered image lx", true);
    qDebug()<<"524";
    Mat src=imread("filtered image lx.jpg",0);

    //imshow("see",src);
    Size mysize;
    mysize.width=180;
    mysize.height=120;


    cv::resize(src,src,mysize,0,0,INTER_LINEAR);


    QImage img=QImage((const unsigned char*)(src.data),src.cols,src.rows,src.cols*src.channels(),QImage::Format_Indexed8);
    this->label7->clear();
    this->label7->setPixmap(QPixmap::fromImage(img));
    this->label7->resize(this->label7->pixmap()->size());
}

void FourWidget::myhigh(){
    Mat src1=imgguass;
    src1.convertTo(src1, CV_64FC2);
    Mat dftDst(src1.size(), CV_64FC2);
    dft(src1, dftDst, DFT_COMPLEX_OUTPUT, 0);
    dftshift(dftDst);
    Mat filterHigh(src1.size(), CV_64FC2, Scalar::all(0));
    makeFilter(filterHigh, 50, true, "2", 1);
    Mat fftTempH = dftDst.mul(filterHigh);
    Mat srcFilteredH;
    dft(fftTempH, srcFilteredH, DFT_INVERSE);
    displayDftSpectrum(srcFilteredH, "filteredH image lx", true);
    qDebug()<<"554";
    Mat src=imread("filteredH image lx.jpg",0);

    //imshow("see",src);
    Size mysize;
    mysize.width=180;
    mysize.height=120;


    cv::resize(src,src,mysize,0,0,INTER_LINEAR);


    QImage img=QImage((const unsigned char*)(src.data),src.cols,src.rows,src.cols*src.channels(),QImage::Format_Indexed8);
    this->label8->clear();
    this->label8->setPixmap(QPixmap::fromImage(img));
    this->label8->resize(this->label8->pixmap()->size());
}

#include "fivewidget.h"
Mydeal::Mydeal()
{	img = imread("D:\\lena.jpg", 0);
    n = 25;
}

Mydeal::Mydeal(Mat& src,int &n)
{
    img = src;
    this->n = n;
}

Mydeal::~Mydeal()
{

}

void Mydeal::Myshow()
{
    Mat dst0 = SobelX(img, n);
    Mat dst1 = MyPre(img, n);
    Mat dst2 = MyRobort(img, n);
    Mat dst3 = MyEdge(img, n);
    Mat dst4 = MyFS(img);
    imshow("Sobel", dst0);
    imshow("Pre", dst1);
    imshow("Robort", dst2);
    imshow("Edge", dst3);
    imshow("Fs", dst4);
    waitKey(60000);
}

Mat Mydeal::SobelX(Mat& src,int& n) {
    Mat dst(cvSize(src.rows, src.cols), src.type());
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

Mat Mydeal::MyPre(Mat& src, int& n)
{
    Mat dst(cvSize(src.rows, src.cols), src.type());
    for (int i = 1; i < src.rows; i++)
    {
        for (int j = 1; j < src.cols; j++) {
            if ((i - 1 >= 0) && (j - 1) >= 0 && (i + 1) < src.rows && (j + 1) < src.cols)
            {
                if (abs(src.at<uchar>(i - 1, j - 1) - src.at<uchar>(i + 1, j - 1) +
                    src.at<uchar>(i - 1, j + 1) - src.at<uchar>(i + 1, j + 1)) > n)
                    dst.at<uchar>(i, j) = 255;
                else
                    dst.at<uchar>(i, j) = 0;
            }
        }

    }
    return  dst;
}

Mat Mydeal::MyRobort(Mat& src, int& n)
{
    Mat dst(cvSize(src.rows, src.cols), src.type());
    for (int i = 1; i < src.rows; i++)
    {
        for (int j = 1; j < src.cols; j++) {
            if ((i - 1 >= 0) && (j - 1) >= 0 && (i + 1) < src.rows && (j + 1) < src.cols)
            {
                if (abs(src.at<uchar>(i - 1, j - 1) - src.at<uchar>(i, j)) > n)
                    dst.at<uchar>(i, j) = 255;
                else
                    dst.at<uchar>(i, j) = 0;
            }
        }

    }
    return  dst;
}

Mat Mydeal::MyEdge(Mat& src, int& n)
{
    threshold(src, src, 150, 255, THRESH_BINARY);
    Mat dst(src.size(), src.type());
    for (int i = 1; i < src.rows; i++)
    {
        for (int j = 1; j < src.cols; j++)
        {
            int temp1 = src.at<uchar>(i, j) + src.at<uchar>(i - 1, j);
            int temp2 = src.at<uchar>(i, j) + src.at<uchar>(i, j - 1);
            temp1 = temp1 / 2;
            temp2 = temp2 / 2;
            if ((temp1 != 0 && temp1 != 255) || (temp2 != 0 && temp2 != 255)) {
                dst.at<uchar>(i, j) = 255;
            }
            else
                dst.at<uchar>(i, j) = 0;
        }
    }
    return dst;
}

Mat Mydeal::MyFS(Mat& mysrc)
{
    Mat src = mysrc;
    //imshow("src", src);
    Mat  image_gray;
    cvtColor(src, image_gray, CV_RGB2GRAY);
    GaussianBlur(image_gray, image_gray, Size(5, 5), 2);
    Canny(image_gray, image_gray, 80, 150);
    //imshow("ge", image_gray);
    //边缘检测
    vector<vector<Point>>contours;
    vector<Vec4i> hierarchy;
    findContours(image_gray, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point());
    Mat imageContours = Mat::zeros(src.size(), CV_8UC1);
    Mat marks(src.size(), CV_32S);
    marks = Scalar::all(0);
    int index = 0;
    int compCount = 0;
    for (; index >= 0; index = hierarchy[index][0], compCount++)
    {
        drawContours(marks, contours, index, Scalar::all(compCount + 1), 1, 8, hierarchy);
        drawContours(imageContours, contours, index, Scalar(255), 1, 8, hierarchy);
    }
    Mat marksShows;
    convertScaleAbs(marks, marksShows);
    //imshow("marksShow", marksShows);
    //imshow("轮廓", imageContours);
    watershed(src, marks);

    Mat afterWatered;
    convertScaleAbs(marks, afterWatered);
    /*imshow("after", afterWatered);
    */
    //颜色填充
    Mat PerspectiveImage = Mat::zeros(src.size(), CV_8UC3);
    for (int i = 0; i < marks.cols; i++)
    {
        for (int j = 0; j < marks.cols; j++)
        {
            int index = marks.at<int>(i, j);
            if (marks.at<int>(i, j) == -1)
                PerspectiveImage.at<Vec3b>(i, j) = Vec3b(255, 255, 255);
            else
                PerspectiveImage.at<Vec3b>(i, j) = RandomColor(index);
        }
    }
    //imshow("afterall", PerspectiveImage);

    Mat wshed;
    addWeighted(src, 0.4, PerspectiveImage, 0.6, 0, wshed);
    return wshed;
}

Vec3b Mydeal::RandomColor(int value)
{
    value = value % 255;
    RNG rng;
    int aa = rng.uniform(0, value);
    int bb = rng.uniform(0, value);
    int cc = rng.uniform(0, value);
    return Vec3b(aa, bb, cc);
}




FiveWidget::FiveWidget(QWidget *parent):QWidget (parent){
    this->setWindowTitle("实验五");
    this->move(100,100);
    this->resize(1000,1000);
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

    Sobel=new QPushButton;
    Sobel->setParent(this);
    Sobel->setText("SOBEL");
    Sobel->move(200,100);
    Sobel->resize(70,30);

    Pre=new QPushButton;
    Pre->setParent(this);
    Pre->setText("Pre");
    Pre->move(200,150);
    Pre->resize(70,30);

    Robort=new QPushButton;
    Robort->setParent(this);
    Robort->setText("ROBORT");
    Robort->move(200,200);
    Robort->resize(70,30);

    Edge=new QPushButton;
    Edge->setParent(this);
    Edge->setText("Edge");
    Edge->move(200,250);
    Edge->resize(70,30);

    Fs=new QPushButton;
    Fs->setParent(this);
    Fs->setText("Edge");
    Fs->move(200,300);
    Fs->resize(70,30);

    label0 = new QLabel;
    label0->setParent(this);
    label0->setText("图片");
    label0->move(0,0);
    label0->resize(180,120);

    label1 = new QLabel;
    label1->setParent(this);
    label1->setText("Sobel");
    label1->move(0,200);
    label1->resize(180,120);

    label2 = new QLabel;
    label2->setParent(this);
    label2->setText("Pre");
    label2->move(0,400);
    label2->resize(180,120);

    label3 = new QLabel;
    label3->setParent(this);
    label3->setText("Robort");
    label3->move(0,600);
    label3->resize(180,120);

    label4 = new QLabel;
    label4->setParent(this);
    label4->setText("Robort");
    label4->move(400,0);
    label4->resize(180,120);


    label5 = new QLabel;
    label5->setParent(this);
    label5->setText("分水岭");
    label5->move(400,200);
    label5->resize(180,120);


    QObject::connect(Remain,SIGNAL(clicked()),this,SLOT(changeSlot()));
    QObject::connect(Open,SIGNAL(clicked()),this,SLOT(on_show_clicked()));
    QObject::connect(Sobel,SIGNAL(clicked()),this,SLOT(sobel()));
    QObject::connect(Pre,SIGNAL(clicked()),this,SLOT(pre()));
    QObject::connect(Robort,SIGNAL(clicked()),this,SLOT(robort()));
    QObject::connect(Edge,SIGNAL(clicked()),this,SLOT(edge()));
    QObject::connect(Fs,SIGNAL(clicked()),this,SLOT(fs()));

}

void FiveWidget::changeSlot(){
    emit mySignal();
}
void FiveWidget::on_show_clicked(){
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
void FiveWidget::sobel(){
    Mat src1;
    cvtColor(img1,src1,CV_BGR2GRAY);
    int n=100;
    Mat src=mydeal->SobelX(src1,n);
    Size mysize;
    mysize.width=180;
    mysize.height=120;
    cv::resize(src,src,mysize,0,0,INTER_LINEAR);


    QImage img=QImage((const unsigned char*)(src.data),src.cols,src.rows,src.cols*src.channels(),QImage::Format_Indexed8);
    this->label1->clear();
    this->label1->setPixmap(QPixmap::fromImage(img));
    this->label1->resize(this->label1->pixmap()->size());
}

void FiveWidget::pre(){
    Mat src1;
    cvtColor(img1,src1,CV_BGR2GRAY);
    int n=100;
    Mat src=mydeal->MyPre(src1,n);
    Size mysize;
    mysize.width=180;
    mysize.height=120;
    cv::resize(src,src,mysize,0,0,INTER_LINEAR);


    QImage img=QImage((const unsigned char*)(src.data),src.cols,src.rows,src.cols*src.channels(),QImage::Format_Indexed8);
    this->label2->clear();
    this->label2->setPixmap(QPixmap::fromImage(img));
    this->label2->resize(this->label2->pixmap()->size());
}

void FiveWidget::robort(){
    Mat src1;
    cvtColor(img1,src1,CV_BGR2GRAY);
    int n=100;
    Mat src=mydeal->MyRobort(src1,n);
    Size mysize;
    mysize.width=180;
    mysize.height=120;
    cv::resize(src,src,mysize,0,0,INTER_LINEAR);


    QImage img=QImage((const unsigned char*)(src.data),src.cols,src.rows,src.cols*src.channels(),QImage::Format_Indexed8);
    this->label3->clear();
    this->label3->setPixmap(QPixmap::fromImage(img));
    this->label3->resize(this->label3->pixmap()->size());
}
void FiveWidget::edge(){
    Mat src1;
    cvtColor(img1,src1,CV_BGR2GRAY);
    int n=100;
    Mat src=mydeal->MyEdge(src1,n);
    Size mysize;
    mysize.width=180;
    mysize.height=120;
    cv::resize(src,src,mysize,0,0,INTER_LINEAR);


    QImage img=QImage((const unsigned char*)(src.data),src.cols,src.rows,src.cols*src.channels(),QImage::Format_Indexed8);
    this->label4->clear();
    this->label4->setPixmap(QPixmap::fromImage(img));
    this->label4->resize(this->label4->pixmap()->size());
}
void FiveWidget::fs(){
    //Mat src1;
    //cvtColor(img1,src1,CV_BGR2GRAY);
    //int n=100;
    Mat src=mydeal->MyFS(img1);
    cvtColor(src,src,CV_BGR2RGB);
    Size mysize;
    mysize.width=180;
    mysize.height=120;
    cv::resize(src,src,mysize,0,0,INTER_LINEAR);


    QImage img=QImage((const unsigned char*)(src.data),src.cols,src.rows,src.cols*src.channels(),QImage::Format_RGB888);
    this->label5->clear();
    this->label5->setPixmap(QPixmap::fromImage(img));
    this->label5->resize(this->label5->pixmap()->size());
}

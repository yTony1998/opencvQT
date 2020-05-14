#ifndef MYDEAL_CPP
#define MYDEAL_CPP
#include"mydeal.h"
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
    Mat dst4 = MyFS();
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

Mat Mydeal::MyFS()
{
    Mat src = imread("D:\\lena.jpg", 1);
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
    imshow("marksShow", marksShows);
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
//	addWeighted(src, 0.4, PerspectiveImage, 0.6, 0, wshed);
    return PerspectiveImage;
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


#endif // MYDEAL_CPP

#include <typeinfo>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/features2d/features2d.hpp"

using namespace cv;
using namespace std;

int scaleImage (Mat img1);
vector<int> multiply_Matrices(int a, int b, int c, int d, int tx, int ty, int x, int y);
int c_x=0;
int c_y=0;
int r[3][1];
int main()
{
    Mat img1;
    img1 = imread("/home/mwason/IAAssignment0/2.jpg", CV_LOAD_IMAGE_GRAYSCALE);

    if ( !img1.data )
    { cout <<  "Could not open or find the image" << endl ; return -1;}


           namedWindow("image", WINDOW_AUTOSIZE);
           imshow("image", img1);
         waitKey(0);
//    //        destroyWindow(argv[1]);

    scaleImage(img1);



    return 0;
}

bool check(int x,int y,Mat image)
{
    cout<<"\n x-,y- "<<x<<","<<y;
    if((image.rows>=x&&image.cols>=y)&&(x>=0&&y>=0))
        return true;
    return false;
}

int scaleImage(Mat img1)
{
    int i, j, k;

    Mat img3 = Mat::zeros(img1.rows, img1.cols, img1.type());
    float xScale;
    float yScale;

    cout<<"enter x translation"<<endl;
    cin>>xScale;

    cout<<"enter y translation"<<endl;
    cin>>yScale;

    cout<<"x,y "<< xScale << ","<< yScale <<endl;
    for (i = 0; i<img1.rows; i++)
    {
        for (j = 0; j<img1.cols; j++)
        {
            cout<<"\n x,y "<<i<<","<<j;
           vector<int> points= multiply_Matrices(xScale, 0, 0,yScale, 0, 0, i, j);
            k = img1.at<uchar>(i, j);
            if(check(points.at(0),points.at(1),img1))
              img3.at<uchar>(points.at(0),points.at(1)) = k;
        }
    }

    namedWindow( "ANS", WINDOW_AUTOSIZE );
    imshow( "ANS", img3);
    waitKey();
    //destroyWindow("ANS");
    return 0;
}

vector<int> multiply_Matrices(int a, int b, int c, int d, int tx, int ty, int x, int y){
    int m1[3][3], m2[3][1];
    vector<int> points;
    m1[0][0] = a;
    m1[0][1] = b;
    m1[0][2] = tx;
    m1[1][0] = c;
    m1[1][1] = d;
    m1[1][2] = ty;
    m1[2][0] = 0;
    m1[2][1] = 0;
    m1[2][2] = 1;

    m2[0][0] = x;
    m2[1][0] = y;
    m2[2][0] = 1;
    int i,j;

    for(i=0;i<3;i++)
    {
        for(j=0;j<1;j++)
        {
            r[i][j]=0;
            for(int k=0;k<3;k++)
            {
                r[i][j]=r[i][j]+m1[i][k]*m2[k][j];
            }
        }
    }


    points.push_back(r[0][0]);
    points.push_back(r[1][0]);

    return points;
}

// ADD TWO IMAGES
int addImg 	(Mat img1, Mat img2)
{
    int i, j, k;
    Size s1, s2;
    s1 = img1.size();
    s2 = img2.size();
    if ( !(s1.height==s2.height && s1.width==s2.width) )
    { cout<<"Incompatible images for arithmetic operations"<<endl; return -1;}

    Mat img3 = Mat::ones(s1.height, s1.width, CV_8UC1);
    for (i = 0; i<s1.height; i++)
    {
        for (j = 0; j<s1.width; j++)
        {
            k = img1.at<uchar>(i, j) + img2.at<uchar>(i, j);
            if (k > 255) {k=255;}
            img3.at<uchar>(i, j) = k;
        }
    }

    namedWindow( "A+B", WINDOW_AUTOSIZE );
    imshow( "A+B", img3);
    waitKey(0);
    destroyWindow("A+B");
    return 0;
}

// ADD CONSTANT TO TWO IMAGES
int addConstantImg 	(Mat img1)
{
    int i, j, k;
    Size s1;
    s1 = img1.size();

    Mat img3 = Mat::ones(s1.height, s1.width, CV_8UC1);
    for (i = 0; i<s1.height; i++)
    {
        for (j = 0; j<s1.width; j++)
        {
            k = img1.at<uchar>(i, j) + 50;
            if (k > 255) {k=255;}
            img3.at<uchar>(i, j) = k;
        }
    }

    namedWindow( "A+k", WINDOW_AUTOSIZE );
    imshow( "A+k", img3);
    waitKey(0);
    destroyWindow("A+k");
    return 0;
}

//ABSOLUTE DIFFERENCE
int absDiff (Mat img1, Mat img2)
{
    int i, j, k;
    Size s1, s2;
    s1 = img1.size();
    s2 = img2.size();
    if ( !(s1.height==s2.height && s1.width==s2.width) )
    { cout<<"Incompatible images for arithmetic operations"<<endl; return -1;}

    Mat img3 = Mat::ones(s1.height, s1.width, CV_8UC1);
    for (i = 0; i<s1.height; i++)
    {
        for (j = 0; j<s1.width; j++)
        {
            k = img1.at<uchar>(i, j) - img2.at<uchar>(i, j);
            if (k < 0 ) {k=0;}
            img3.at<uchar>(i, j) = k;
        }
    }

    namedWindow( "|A - B|", WINDOW_AUTOSIZE );
    imshow( "|A - B|", img3);
    waitKey(0);
    destroyWindow("|A - B|");
    return 0;
}

//COMPLEMENTING THE IMAGE(NEGATIVE)
int complementImg 	(Mat img1)
{
    int i, j, k;
    Size s1;
    s1 = img1.size();

    Mat img3 = Mat::ones(s1.height, s1.width, CV_8UC1);
    for (i = 0; i<s1.height; i++)
    {
        for (j = 0; j<s1.width; j++)
        {
            k = 255 - img1.at<uchar>(i, j);
            if (k < 0) {k=0;}
            img3.at<uchar>(i, j) = k;
        }
    }

    namedWindow( "255 - A", WINDOW_AUTOSIZE );
    imshow( "255 - A", img3);
    waitKey(0);
    destroyWindow("255 - A");
    return 0;
}

//DIVIDE 2 IMAGES
int Divide2Img (Mat img1, Mat img2)
{
    int i, j, k;
    Size s1, s2;
    s1 = img1.size();
    s2 = img2.size();
    if ( !(s1.height==s2.height && s1.width==s2.width) )
    { cout<<"Incompatible images for arithmetic operations"<<endl; return -1;}

    Mat img3 = Mat::ones(s1.height, s1.width, CV_8UC1);
    for (i = 0; i<s1.height; i++)
    {
        for (j = 0; j<s1.width; j++)
        {
            if(img2.at<uchar>(i, j) != 0){
                k = img1.at<uchar>(i, j) / img2.at<uchar>(i, j);
            }
            if (k < 0 ) {k=0;}
            img3.at<uchar>(i, j) = k;
        }
    }

    namedWindow( "A/B", WINDOW_AUTOSIZE );
    imshow( "A/B", img3);
    waitKey(0);
    destroyWindow("A/B");
    return 0;
}

//LINEAR COMBINATION
int Lcombination (Mat img1, Mat img2)
{
    int i, j, k,a,b;
    Size s1, s2;
    s1 = img1.size();
    s2 = img2.size();
    a = 10;
    b = 15;
    if ( !(s1.height==s2.height && s1.width==s2.width) )
    { cout<<"Incompatible images for arithmetic operations"<<endl; return -1;}

    Mat img3 = Mat::ones(s1.height, s1.width, CV_8UC1);
    for (i = 0; i<s1.height; i++)
    {
        for (j = 0; j<s1.width; j++)
        {
            if(img2.at<uchar>(i, j) != 0){
                k = a*(img1.at<uchar>(i, j)) +  b*(img2.at<uchar>(i, j));
            }
            //CHECK BOTH >255 AND <0 BECAUSE a,b CAN BE +VE AND -VE BOTH
            if (k < 0 ) {k=0;}
            if (k > 255){k=255;}
            img3.at<uchar>(i, j) = k;
        }
    }

    namedWindow( "xA + yB", WINDOW_AUTOSIZE );
    imshow( "xA + yB", img3);
    waitKey(0);
    destroyWindow("xA + yB");
    return 0;
}

//SUBTRACT 2 IMAGES
int SubImage (Mat img1, Mat img2)
{
    int i, j, k;
    Size s1, s2;
    s1 = img1.size();
    s2 = img2.size();
    if ( !(s1.height==s2.height && s1.width==s2.width) )
    { cout<<"Incompatible images for arithmetic operations"<<endl; return -1;}

    Mat img3 = Mat::ones(s1.height, s1.width, CV_8UC1);
    for (i = 0; i<s1.height; i++)
    {
        for (j = 0; j<s1.width; j++)
        {
            if(img2.at<uchar>(i, j) != 0){
                k = (img1.at<uchar>(i, j)) -  (img2.at<uchar>(i, j));
            }
            if (k < 0 ) {k=0;}
            img3.at<uchar>(i, j) = k;
        }
    }

    namedWindow( "A - B", WINDOW_AUTOSIZE );
    imshow( "A - B", img3);
    waitKey(0);
    destroyWindow("A - B");
    return 0;
}

//MULTIPLY 2 IMAGES
int MultiplyImage (Mat img1, Mat img2)
{
    int i, j, k;
    Size s1, s2;
    s1 = img1.size();
    s2 = img2.size();
    if ( !(s1.height==s2.height && s1.width==s2.width) )
    { cout<<"Incompatible images for arithmetic operations"<<endl; return -1;}

    Mat img3 = Mat::ones(s1.height, s1.width, CV_8UC1);
    for (i = 0; i<s1.height; i++)
    {
        for (j = 0; j<s1.width; j++)
        {
            if(img2.at<uchar>(i, j) != 0){
                k = (img1.at<uchar>(i, j)) *  (img2.at<uchar>(i, j));
            }
            if (k > 255 ) {k=255;}
            img3.at<uchar>(i, j) = k;
        }
    }

    namedWindow( "A * B", WINDOW_AUTOSIZE );
    imshow( "A * B", img3);
    waitKey(0);
    destroyWindow("A * B");
    return 0;
}

//DIVIDE IMAGE BY CONSTANT
int DivideImgConst (Mat img1)
{
    int i, j, k;
    Size s1;
    s1 = img1.size();

    Mat img3 = Mat::ones(s1.height, s1.width, CV_8UC1);
    for (i = 0; i<s1.height; i++)
    {
        for (j = 0; j<s1.width; j++)
        {
            k = img1.at<uchar>(i, j) / 50;
            if (k < 0) {k=0;}
            img3.at<uchar>(i, j) = k;
        }
    }

    namedWindow( "A/k", WINDOW_AUTOSIZE );
    imshow( "A/k", img3);
    waitKey(0);
    destroyWindow("A/k");
    return 0;
}

//MULTIPLY IMAGE BY CONSTANT
int MultiplyImgConst (Mat img1)
{
    int i, j, k;
    Size s1;
    s1 = img1.size();

    Mat img3 = Mat::ones(s1.height, s1.width, CV_8UC1);
    for (i = 0; i<s1.height; i++)
    {
        for (j = 0; j<s1.width; j++)
        {
            k = img1.at<uchar>(i, j) * 50;
            if (k > 255) {k=255;}
            img3.at<uchar>(i, j) = k;
        }
    }

    namedWindow( "A*k", WINDOW_AUTOSIZE );
    imshow( "A*k", img3);
    waitKey(0);
    destroyWindow("A*k");
    return 0;
}

//SUBTRACT CONSTANT FROM IMAGE
int SubImgConst (Mat img1)
{
    int i, j, k;
    Size s1;
    s1 = img1.size();

    Mat img3 = Mat::ones(s1.height, s1.width, CV_8UC1);
    for (i = 0; i<s1.height; i++)
    {
        for (j = 0; j<s1.width; j++)
        {
            k = img1.at<uchar>(i, j) * 50;
            if (k < 0) {k=0;}
            img3.at<uchar>(i, j) = k;
        }
    }

    namedWindow( "A-k", WINDOW_AUTOSIZE );
    imshow( "A-k", img3);
    waitKey(0);
    destroyWindow("A-k");
    return 0;
}



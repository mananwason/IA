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

int addImg (Mat img1, Mat img2);

int absDiff (Mat img1, Mat img2);

int Divide2Img (Mat img1, Mat img2);

int Lcombination(Mat img1, Mat img2);

int SubImage(Mat img1, Mat img2);

int MultiplyImage(Mat img1, Mat img2);

int addConstantImg (Mat img1);

int complementImg (Mat img1);

int DivideImgConst (Mat img1);

int MultiplyImgConst (Mat img1);

int SubImgConst (Mat img1);

int main( int argc, char** argv )
{
    int i, j, k;

    if( argc != 3)
    {cout << "Usage: display_image Image_1 Image_2" << endl; return -1;}

    Mat img1, img2, img3;
    img1 = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
    img2 = imread(argv[2], CV_LOAD_IMAGE_GRAYSCALE);

    if ( !img1.data || !img2.data)
    { cout <<  "Could not open or find the image" << endl ; return -1;}

    cout<<"Please press ENTER after an image is shown.\nDoing so will show the next image.";
    cout<<"\nPress ENTER!";
    waitKey(0);

    namedWindow(argv[1], WINDOW_AUTOSIZE);
    imshow(argv[1], img1);
    waitKey(0);
    destroyWindow(argv[1]);

    namedWindow(argv[2], WINDOW_AUTOSIZE);
    imshow(argv[2], img2);
    waitKey(0);
    destroyWindow(argv[2]);

    addImg(img1, img2);

    absDiff(img1, img2);

    Divide2Img(img1, img2);

    Lcombination(img1,img2);

    MultiplyImage(img1, img2);

    SubImage(img1, img2);

    addConstantImg(img1);

    complementImg(img1);

    DivideImgConst(img1);

    MultiplyImgConst(img1);

    SubImgConst(img1);


    return 0;
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

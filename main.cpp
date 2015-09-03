#include <typeinfo>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/features2d/features2d.hpp"
#define PI 3.14159265
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

int scaleImage (Mat img1);
int rotateImg(Mat img1);
int translateImage(Mat img1);
int showCumulative(Mat img1);
int complementImg(Mat img1);
int gammaTransform(Mat img1, float gamma, float c);
int contrastStrech(Mat img1, float a, float b, float c, float d);
void showHistogram(Mat& img1);


vector<float> multiply_Matrices(float a, float b, float c, float d, float tx, float ty, float x, float y);
int c_x=0;
int c_y=0;
int r[3][1];

int main()
{
    Mat img1, img2;
    img1 = imread("/home/mwason/IAOpenCv/lena.jpg", CV_LOAD_IMAGE_GRAYSCALE);

    if ( !img1.data )
    { cout <<  "Could not open or find the image" << endl ; return -1;}


    namedWindow("image", WINDOW_AUTOSIZE);
    imshow("image", img1);
    waitKey(0);
    destroyWindow("image");
    cout<<"\t\t\t\tEnter";
    cout<<"\n\n1)Scale\n2)Translation\n3)Rotation\n4)Histogram or Cumulative\n5)Transformations";
    int option,option1 = 0;
    cout<<"\n\nEnter selection"<<endl;
    cin>>option;
    switch(option)
    {
    case 1 :
        scaleImage(img1);
        break;
    case 2 :
        translateImage(img1);
        break;
    case 3 :
        rotateImg(img1);
        break;
    case 4 :
    {cout<<"\n\n1)Histogram\n2)Cumulative";
        cout<<"\nEnter selection"<<endl;
        cin>>option1;
        switch(option1)
        {
        case 1 :
            img2 = imread("/home/mwason/IAOpenCv/lena.jpg");
            if (img2.empty())
                return -1;
            showHistogram(img2);
            imshow("src", img2);
            waitKey(0);
            break;

        case 2:
            img2 = imread("/home/mwason/IAOpenCv/lena.jpg");
            imshow("src", img2);
            waitKey(0);
            if (img2.empty())
                return -1;
            showCumulative(img2);

            break;}
        break;}
    case 5:
        cout<<"\n\n1)Negative\n2)Gamma\n3)Contrast stretching";
        cout<<"\nEnter selection"<<endl;
        cin>>option1;
        switch(option1)
        {
        case 1 :
        {
            img2 = imread("/home/mwason/IAOpenCv/lena.jpg");
            imshow("src", img2);
            waitKey(0);
            complementImg(img2);

            break;
        }
        case 2 :
        {
            float gamma;
            float constant;
            cout<<"\nEnter Gamma"<<endl;
            cin>>gamma;
            cout<<"\nEnter c"<<endl;
            cin>>constant;
            img2 = imread("/home/mwason/IAOpenCv/lena.jpg");
            imshow("src", img2);
            waitKey(0);
            gammaTransform(img2,gamma,constant);

            break;
        }
        case 3 :
        {
            float a,b,c,d;
            float constant;
            cout<<"\nEnter a"<<endl;
            cin>>a;
            cout<<"\nEnter b"<<endl;
            cin>>b;
            cout<<"\nEnter c"<<endl;
            cin>>c;
            cout<<"\nEnter d"<<endl;
            cin>>d;
            img2 = imread("/home/mwason/IAOpenCv/lena.jpg");
            imshow("src", img2);
            waitKey(0);
            contrastStrech(img2, a, b,c, d);
            break;
        }

        }
    default :
        cout << "Invalid" << endl;
    }
    return 0;
}


bool check(int x,int y,Mat image)
{
    cout<<"\n x-,y- "<<x<<","<<y;
    if((image.rows>=x&&image.cols>=y)&&(x>=0&&y>=0))
    {cout<<"\n x1-,y1- "<<x<<","<<y;
        return true;}
    return false;
}

int scaleImage(Mat img1)
{
    int i, j, k;

    Mat img3 = Mat::zeros(img1.rows, img1.cols, img1.type());


    float xScale;
    float yScale;

    cout<<"\nenter x scaling"<<endl;
    cin>>xScale;

    cout<<"\nenter y sclaing"<<endl;
    cin>>yScale;

    cout<<"x,y "<< xScale << ","<< yScale <<endl;
    for (i = 0; i<img1.rows; i++)
    {
        for (j = 0; j<img1.cols; j++)
        {
            cout<<"\n x,y "<<i<<","<<j;
            vector<float> points= multiply_Matrices(xScale, 0, 0,yScale, 0, 0, i, j);
            k = img1.at<uchar>(i, j);
            if(check(points.at(0),points.at(1),img1))
                img3.at<uchar>(points.at(0),points.at(1)) = k;
        }
    }

    namedWindow( "ANS", WINDOW_AUTOSIZE );
    imshow( "ANS", img3);
    waitKey(0);
    destroyWindow("ANS");
    return 0;
}

int translateImage(Mat img1)
{
    int i, j;
    double k;


    float xTranslation;
    float yTranslation;

    cout<<"\nenter x translation"<<endl;
    cin>>xTranslation;

    cout<<"\nenter y translation"<<endl;
    cin>>yTranslation;
    Mat img3 = Mat::zeros(img1.rows+xTranslation, img1.cols+yTranslation, img1.type());

    cout<<"x,y "<< xTranslation << ","<< yTranslation <<endl;
    for (i = 0; i<img1.rows; i++)
    {
        for (j = 0; j<img1.cols; j++)
        {
            cout<<"\n x,y "<<i<<","<<j;
            img3.at<uchar>(i+xTranslation, j+yTranslation) = img1.at<uchar>(i, j);
        }
    }

    namedWindow( "ANS", WINDOW_AUTOSIZE );
    imshow( "ANS", img3);
    waitKey();
    destroyWindow("ANS");
    return 0;
}

int rotateImg(Mat img1)
{
    int i, j, k;

    Mat img3 = Mat::zeros(img1.rows, img1.cols, img1.type());
    float degrees, sine, cosine;

    cout<<"\nenter rotation angle"<<endl;
    cin>>degrees;

    sine = sin(degrees * PI/180.0);

    cosine = cos(degrees * PI/180.0);

    cout<<"angle "<< degrees <<"sin "<<sine<<" cos"<<cosine<<endl;
    for (i = 0; i<img1.rows; i++)
    {
        for (j = 0; j<img1.cols; j++)
        {
            cout<<"\n x,y "<<i<<","<<j;
            vector<float> points= multiply_Matrices(cosine, -sine, sine,cosine, 0, 0, i, j);
            k = img1.at<uchar>(i, j);
            cout<<"\n a,b "<<points.at(0)<<", "<<points.at(1);
            if(check(points.at(0),points.at(1),img1))
                img3.at<uchar>(points.at(0),points.at(1)) = k;
        }
    }

    namedWindow( "ANS", WINDOW_AUTOSIZE );
    imshow( "ANS", img3);
    waitKey(0);
    destroyWindow("ANS");
    return 0;
}

vector<float> multiply_Matrices(float a, float b, float c, float d, float tx, float ty, float x, float y){
    float m1[3][3], m2[3][1];
    vector<float> points;
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

void showHistogram(Mat& img)
{
    int bins = 256;
    int nc = img.channels();
    vector<Mat> hist(nc);
    for (int i = 0; i < hist.size(); i++)
        hist[i] = Mat::zeros(1, bins, CV_32SC1);

    for (int i = 0; i < img.rows; i++)
    {
        for (int j = 0; j < img.cols; j++)
        {
            for (int k = 0; k < nc; k++)
            {
                uchar val = nc == 1 ? img.at<uchar>(i,j) : img.at<Vec3b>(i,j)[k];
                hist[k].at<int>(val) += 1;
            }
        }
    }

    int hmax[3] = {0,0,0};
    for (int i = 0; i < nc; i++)
    {
        for (int j = 0; j < bins-1; j++)
            hmax[i] = hist[i].at<int>(j) > hmax[i] ? hist[i].at<int>(j) : hmax[i];
    }

    const char* wname[3] = { "blue", "green", "red" };
    Scalar colors[3] = { Scalar(255,0,0), Scalar(0,255,0), Scalar(0,0,255) };

    vector<Mat> canvas(nc);
    for (int i = 0; i < nc; i++)
    {
        canvas[i] = Mat::ones(125, bins, CV_8UC3);

        for (int j = 0, rows = canvas[i].rows; j < bins-1; j++)
        {
            line(
                        canvas[i],
                        Point(j, rows),
                        Point(j, rows - (hist[i].at<int>(j) * rows/hmax[i])),
                        nc == 1 ? Scalar(200,200,200) : colors[i],
                        1, 8, 0
                        );
        }

        imshow(nc == 1 ? "value" : wname[i], canvas[i]);
    }
}

int showCumulative(Mat img)
{
    int bins = 256;
    int nc = img.channels();

    vector<Mat> hist(nc);
    for (int i = 0; i < hist.size(); i++)
        hist[i] = Mat::zeros(1, bins, CV_32SC1);

    for (int i = 0; i < img.rows; i++)
    {
        for (int j = 0; j < img.cols; j++)
        {
            for (int k = 0; k < nc; k++)
            {
                uchar val = nc == 1 ? img.at<uchar>(i,j) : img.at<Vec3b>(i,j)[k];
                hist[k].at<int>(val) += 1;
            }
        }
    }

    for (int i = 1; i < 256; i++)
    {
        for (int k = 0; k < nc; k++)
        {

            hist[k].at<int>(i) =hist[k].at<int>(i)+hist[k].at<int>(i-1);
        }
    }



    int hmax[3] = {0,0,0};
    for (int i = 0; i < nc; i++)
    {
        for (int j = 0; j < bins-1; j++)
            hmax[i] = hist[i].at<int>(j) > hmax[i] ? hist[i].at<int>(j) : hmax[i];
    }

    const char* wname[3] = { "blue", "green", "red" };
    Scalar colors[3] = { Scalar(255,0,0), Scalar(0,255,0), Scalar(0,0,255) };

    vector<Mat> canvas(nc);

    // Display each histogram in a canvas
    for (int i = 0; i < nc; i++)
    {
        canvas[i] = Mat::ones(125, bins, CV_8UC3);

        for (int j = 0, rows = canvas[i].rows; j < bins-1; j++)
        {
            line(
                        canvas[i],
                        Point(j, rows),
                        Point(j, rows - (hist[i].at<int>(j) * rows/hmax[i])),
                        nc == 1 ? Scalar(200,200,200) : colors[i],
                        1, 8, 0
                        );
        }
        imshow(nc == 1 ? "value" : wname[i], canvas[i]);
    }
}

//COMPLEMENTING THE IMAGE(NEGATIVE)
int complementImg 	(Mat img1)
{
    int i, j;
    int red,green, blue;
    Size s1;
    s1 = img1.size();

    Mat img3 = Mat::ones(s1.height, s1.width, img1.type());
    for (i = 0; i<s1.height; i++)
    {
        for (j = 0; j<s1.width; j++)
        {
            red = 255 - img1.at<Vec3b>(i, j)[0];
            green = 255 - img1.at<Vec3b>(i, j)[1];
            blue = 255 - img1.at<Vec3b>(i, j)[2];

            if (red < 0) {red=0;}
            if (blue < 0) {blue=0;}
            if (green < 0) {green=0;}
            img3.at<Vec3b>(i, j)[0]= red;
            img3.at<Vec3b>(i, j)[1]= green;
            img3.at<Vec3b>(i, j)[2]= blue;

        }
    }

    namedWindow( "255 - A", WINDOW_AUTOSIZE );
    imshow( "255 - A", img3);
    waitKey(0);
    destroyWindow("255 - A");
    return 0;
}

int gammaTransform 	(Mat img1, float gamma, float c)
{
    int i, j;
    float red,green, blue;
    Size s1;
    s1 = img1.size();

    Mat img3 = Mat::ones(s1.height, s1.width, img1.type());
    for (i = 0; i<s1.height; i++)
    {
        for (j = 0; j<s1.width; j++)
        {
            red = c*(pow((double)(img1.at<Vec3b>(i, j)[0]/255.0),(double)gamma));
            green = c*(pow((double)(img1.at<Vec3b>(i, j)[1]/255.0),(double)gamma));
            blue = c*(pow((double)(img1.at<Vec3b>(i, j)[2]/255.0),(double)gamma));

            cout<<"\nr,g,b "<<red<<", "<<green<<", "<<blue;
            if (red < 0) {red=0;}
            if (blue < 0) {blue=0;}
            if (green < 0) {green=0;}
            img3.at<Vec3b>(i, j)[0]= red*255;
            img3.at<Vec3b>(i, j)[1]= green*255;
            img3.at<Vec3b>(i, j)[2]= blue*255;

        }
    }

    namedWindow( "Gamma", WINDOW_AUTOSIZE );
    imshow( "Gamma", img3);
    waitKey(0);
    destroyWindow("Gamma");
    return 0;
}

int contrastStrech 	(Mat img1, float a, float b, float c, float d)
{
    int i, j;
    float red,green, blue;
    Size s1;
    s1 = img1.size();

    Mat img3 = Mat::ones(s1.height, s1.width, img1.type());
    for (i = 0; i<s1.height; i++)
    {
        for (j = 0; j<s1.width; j++)
        {
            red = (((img1.at<Vec3b>(i, j)[0]) -c)*((b-a)/(d-c))) + a;
            green = (((img1.at<Vec3b>(i, j)[1]) -c)*((b-a)/(d-c))) + a;
            blue = (((img1.at<Vec3b>(i, j)[2]) -c)*((b-a)/(d-c))) + a;

            cout<<"\nr,g,b "<<red<<", "<<green<<", "<<blue;
            if (red > 0) {red=255;}
            if (blue > 0) {blue=255;}
            if (green > 0) {green=255;}
            if (red < 0) {red=0;}
            if (blue < 0) {blue=0;}
            if (green < 0) {green=0;}
            cout<<"red"<<red*255;
            img3.at<Vec3b>(i, j)[0]= red;
            img3.at<Vec3b>(i, j)[1]= green;
            img3.at<Vec3b>(i, j)[2]= blue;

        }
    }

    namedWindow( "contrast", WINDOW_AUTOSIZE );
    imshow( "contrast", img3);
    waitKey(0);
    destroyWindow("contrast");
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



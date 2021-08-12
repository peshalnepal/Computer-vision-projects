#include<iostream>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/video.hpp>
#include<opencv2/highgui.hpp>
#include<fstream>
using namespace cv;
using namespace std;
int main(int argc, char* argv[])
{
   string pathread;
   Mat img;
   VideoCapture capturevideo;
   ifstream ifile;
       try
       {
        if (argc==1)
            {
                pathread="videos/check.mp4";
            }
        if(argc >=2)
            {
                pathread=argv[1];
            }
      ifile.open(pathread);
       if(!ifile) {
          throw("video not found in the path");
       }
        capturevideo.open(pathread);
        if(!capturevideo.isOpened())
           {
               throw("video not found in the path");
           }
       }
       catch(const char* msg)
       {
          cerr << msg << '\n';
          return 0;
       }
       catch(...)
       {
          cerr << "video not found " << '\n';
          return 0;
       }
Mat imgfv;
double FPS;
int width,height;
string pathwrite="videos/output.mp4";
FPS=capturevideo.get(CAP_PROP_FPS);
width=int(capturevideo.get(CAP_PROP_FRAME_WIDTH));
height=int(capturevideo.get(CAP_PROP_FRAME_HEIGHT));
cout<<"Input fps "<<FPS<<endl;
cout<<"Input height "<<height<<endl;
cout<<"Input width "<<width<<endl;
int codecc=VideoWriter::fourcc('m','p','4','v');
VideoWriter videoWriter(pathwrite,codecc,(FPS*2),Size(int(width/2),int(height/2)));
cout<<"output fps "<<(FPS*2)<<endl;
cout<<"output height "<<int(height/2)<<endl;
cout<<"output width "<<int(width/2)<<endl;
if(capturevideo.isOpened() && videoWriter.isOpened())
{
    while (true)
    {
      capturevideo.read(imgfv);

      if(imgfv.empty())
      {
      break;
      }
      imshow("Display video",imgfv);
      resize(imgfv,imgfv,Size(int(width/2),int(height/2)));
      videoWriter.write(imgfv);
      int k =waitKey(1);
      if(k==27)
      {

      break;
      }
    }
}
      destroyAllWindows();
      videoWriter.release();
      capturevideo.release();
return 0;
}

#include <IOInterface.h>
IOInterface io;
Mat color,depth,birdView;
Vec3f imuPose;
float speed,angle;
int x_scan=200;
int main(){
    while(true){
        io.chooseCarMode();
        io.ready();
        x_scan=180;
        io.setCamAngle(-20);
        sleep(0.5); 
        io.printLCD(0,0,"Running!!!");
	    //VideoWriter video("outvideo.avi",CV_FOURCC('M','J','P','G'),20, Size(300,300));
        
        while(true){
            color=io.getBGR();
            depth=io.getDepth();
            cvtColor(color,birdView,COLOR_BGR2GRAY);
            Point2f p1[4] = {Point2f(120, 105), Point2f(200, 105), Point2f(320, 240), Point2f(0, 240)};
            Point2f p2[4] = {Point2f(100, 0), Point2f(200, 0), Point2f(200, 285), Point2f(120, 285)};
            Mat M = getPerspectiveTransform(p1, p2);
            warpPerspective(birdView, birdView, M, Size(300, 300));
            Mat r = getRotationMatrix2D(Point(150,300), -16, 1.0);
            warpAffine(birdView, birdView, r, birdView.size());
            imshow("display",birdView);
            threshold(birdView,birdView,180,255,THRESH_BINARY);
            int x_white=-1;
            for(int i = 0; i<60; i++)
            {
                if(birdView.at<uchar>(250,x_scan+60/2-i)==255){
                    x_white=x_scan+60/2-i;
                    break;
                }
            }
            if(x_white>-1){
                x_scan=x_white;
                angle=3*(180-x_scan); //PD
            }
            line(birdView,Point(x_scan-30,250),Point(x_scan+30,250),255);
	        Mat display;
            cvtColor(birdView,display,COLOR_GRAY2BGR);
            
            waitKey(1);
	        //video.write(display);
            if(io.getLCDkey()==5){
                break;
            }
            io.setSpeed(0);
            //io.setSteer(angle);
        }
    }
}

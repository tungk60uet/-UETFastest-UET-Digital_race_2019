#include <IOInterface.h>
IOInterface io;
Mat color,depth;
Vec3f imuPose;
int main(){
    while(true){
        io.chooseCarMode();
        io.ready();
        io.printLCD(0,0,"Runing!!!");
        while(true){
            color=io.getBGR();
            imshow("color",color);
            depth=io.getDepth();
            Mat adjMap;
            convertScaleAbs(depth, adjMap, 255.0 / 6500);
            imshow("depth",adjMap);
            waitKey(1);
            imuPose=io.getIMUPose();
            cout<<imuPose<<endl;
            io.setSpeed(10);
            io.setSteer(50);
            io.setCamAngle(50);
            int LCDKey=io.getLCDkey();
            if(LCDKey==4||LCDKey==5) break;
        }
    }   
}
#include <iostream>
#include "IOInterface.h"
using namespace std;
IOInterface io("192.168.237.1");
int main(){
    io.chooseCarMode();
    io.ready();
    do{
        imshow("color",io.getBGR());
        imshow("depth",io.getDepth());
        io.setSpeed(5);
        waitKey(1);
    }while(true);
}
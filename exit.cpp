#include "exit.h"

Exit::Exit(double x,double y,int t):xpos{x},ypos{y},type{t}
{

}

void Exit::updateState(double x, double y){
    double dist = sqrt((x-xpos)*(x-xpos)+(y-ypos)*(y-ypos));
    if(dist <= radius){
        if(type == Exit::TYPE_FAKE_TRANSFER_TO_START){
            state = Exit::STATE_BACK_TO_START;
        }else if(type == Exit::TYPE_REAL){
            state = Exit::STATE_GAME_OVER;
        }else;
    }else state = Exit::STATE_GAME_UNGOING;
}


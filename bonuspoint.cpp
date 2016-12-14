#include "bonuspoint.h"

BonusPoint::BonusPoint(double x,double y,double a):xpos{x},ypos{y},ammount{a}
{

}

void BonusPoint::updateState(double x, double y){
    double dist = sqrt((x-xpos)*(x-xpos)+(y-ypos)*(y-ypos));
    if(dist <= radius){
        if(valid){
            triggered = true;
        }
    }
}



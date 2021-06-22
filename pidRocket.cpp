
#include "model.h"
#include "pidRocket.h"

const float Kp = -1.1;

void
pidRocket (
    int    dMsec,
    float  yDeg  )
{
    modelSetAlphaYdeg (Kp * yDeg);
}

// model of a rocket with gimballed motor

#include <stdio.h>
#include <stdlib.h>

#include "model.h"
#include "math.h"

#define deg(w)      ((w) * 180 / M_PI)
#define rad(w)      ((w) * M_PI / 180)

const float Mass    = 2;    // kg
const float Length  = 1;    // meter
const float MoI     = (Mass / (Length * Length)) / 12;  // kg

float thrust  = 3;    // newton

//   x
//   |  z
//   | /
//   |/____ y

enum { Linear, Angular };

struct Vec_s {
    const char *desc;

    int     type;

    float   mass;       // or moment of inertia

    float   acc;        // or angualar acceleration
    float   vel;        // or angualar velocity
    float   pos;        // or angualar position

    float   radAcc;
    float   radVel;
    float   radPos;

    float   w;          // angle in radians
    float   force;
};

Vec_s  x = { "x", Linear,  Mass };
Vec_s  y = { "y", Angular, MoI  };
Vec_s  z = { "z", Angular, MoI  };

float  alphaY = 0;   // thrust (gimbal) vector
float  alphaZ = 0;

// -----------------------------------------------------------------------------
void
disp (
    Vec_s  &v )
{
    printf (" |");
    printf (" %s",       v.desc);
    
    if (Linear == v.type)  {
        printf (" %5.2f m",     v.pos);
        printf (" %5.2f m/s",   v.vel);
        printf (" %5.2f m/s/s", v.acc);
    }
    else  {
        printf (" %8.4f deg",   deg(v.pos));
        printf (" %5.2f r/s",   v.vel);
        printf (" %6.2f r/s/s", v.acc);
    }

    printf ("  %6.3f F",  v.force);
}

// -----------------------------------------------------------------------------
void
_update (
    Vec_s  &v,
    float   force,
    int     dMsec )
{
    v.force   = force;
    v.acc     = v.force / v.mass; 
    v.vel    += v.acc * dMsec / 1000;
    v.pos    += v.vel * dMsec / 1000;
}

// -----------------------------------------------------------------------------
float
modelGetYdeg (void)
{
    return deg(y.pos);
}

// -----------------------------------------------------------------------------
void
modelSetAlphaYdeg (
    float  ang )
{
    alphaY = rad(ang);
}

// -----------------------------------------------------------------------------
void
model (     // 2d model
    int  dMsec )
{
    static int timeMsec  = 0;
               timeMsec += dMsec;

    float randY = 0;
#if 1
    if (! (timeMsec % 500))
        randY = 0.02 * (random () - (RAND_MAX / 2)) / RAND_MAX;;
#endif

    printf ("%s:", __func__);
    printf (" %6.2f alpha",  deg(alphaY));
    printf (" %6.2f rndY",   deg(randY));

    _update (x, thrust * cos (alphaY + y.pos), dMsec);
    _update (y, thrust * sin (alphaY + randY), dMsec);

    // doesn't consider rotation

    disp   (x);
    disp   (y);

    printf ("\n");
}

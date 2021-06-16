// model of a rocket with gimballed motor

#include <stdio.h>
#include <stdlib.h>

#include "model.h"
#include "math.h"

#define deg(w)      ((w) * 180 / M_PI)

float mass    = 2;    // kg
float thrust  = 3;    // newton
float length  = 1;    // meter

//   x
//   |  z
//   | /
//   |/____ y

struct Vec_s {
    const char *desc;

    float   acc;
    float   vel;
    float   pos;

    float   radAcc;
    float   radVel;
    float   radPos;

    float   w;          // angle in radians
    float   force;
};

Vec_s  x = { "x" };     // rocket vector
Vec_s  y = { "y" };     // rocket vector
Vec_s  z = { "z" };     // rocket vector

Vec_s  alphaY, betaZ;   // thrust (gimbal) vector

// -----------------------------------------------------------------------------
void
disp (
    Vec_s  &v )
{
    printf (" | %5.2f p", v.pos);
    printf ("  %5.2f v", v.vel);
    printf ("  %5.2f a", v.acc);
    printf ("  %5.2f F", v.force);
    printf ("  %s",     v.desc);
}

// -----------------------------------------------------------------------------
void
update (
    Vec_s  &v,
    float   force,
    int     dMsec )
{
    v.force   = force;
    v.acc     = v.force / mass; 
    v.vel    += v.acc * dMsec / 1000;
    v.pos    += v.vel * dMsec / 1000;
}

// -----------------------------------------------------------------------------
void
model (     // 2d model
    int  dMsec )
{
    float wY;
    wY    = atan2 (y.vel, x.vel);     // trajectory
    wY    = 0.2 * (random () - (RAND_MAX / 2)) / RAND_MAX;;

    printf ("%s: %6.1f angY", __func__, deg(alphaY.w + wY));

    update (x, thrust * cos (alphaY.w + wY), dMsec);
    update (y, thrust * sin (alphaY.w + wY), dMsec);

    // doesn't consider rotation

    disp   (x);
    disp   (y);

    printf ("\n");
}

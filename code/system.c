#include "system.h"

void initSettings(settings *param)
{
    param->load = 1; //doit charger une map
    param->done = false;
    param->redraw = true;
    param->mode = STARTING_SCREEN;
}

camera initCam(void)
{
    camera cam;
    cam.x = 0;
    cam.y = 0;
    return cam;
}

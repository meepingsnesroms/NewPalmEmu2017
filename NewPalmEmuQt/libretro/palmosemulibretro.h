#ifndef palmosemulibretro_h
#define palmosemulibretro_h

#ifdef __cplusplus
extern "C" {
#endif

void  libretro_palm_init();
void  libretro_palm_deinit();
void  libretro_palm_setresolution(int x,int y);
void  libretro_palm_setbutton(int button, bool state);
void  libretro_palm_touchmouse(int relx,int rely);
void  libretro_palm_touchmouseclick(bool down);
void* libretro_palm_getframebuffer();

#ifdef __cplusplus
}
#endif

#endif /* palmosemulibretro_h */

#pragma once
#include<graphics.h>
#pragma comment(lib,"MSIMG32.LIB")
inline bool isPointInRect(int px, int py, int rx, int ry, int rw, int rh) {
    return (px >= rx && px <= rx + rw && py >= ry && py <= ry + rh);
}
//支持透明度渲染
inline void putimage_alpha(int dst_x, int dst_y, IMAGE* img)
{
	int w = img->getwidth();
	int h = img->getheight();
	AlphaBlend(GetImageHDC(GetWorkingImage()), dst_x, dst_y, w, h,
		GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER,0,255,AC_SRC_ALPHA });
}
//支持图像缩放渲染
inline void putimage_alpha(int dst_x, int dst_y, int dst_w, int dst_h, IMAGE* img) {
    int src_w = img->getwidth();
    int src_h = img->getheight();
    AlphaBlend(GetImageHDC(GetWorkingImage()), dst_x, dst_y, dst_w, dst_h,
        GetImageHDC(img), 0, 0, src_w, src_h,
        { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA });
}
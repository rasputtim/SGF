/*
  SGF - Super Game Fabric  Super Game Fabric
  Copyright (C) 2010-2011 Rasputtim <raputtim@hotmail.com>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

  */

#include "graphics/all.h"
#include <vector>
#include "graphics/SGF_FireEffect.h"
#include <string.h>
#include "util/SGF_Util.h"
#include "graphics/SGF_Poligon.h"
#include <math.h>


using namespace std;
namespace SGF{
class CBitmap;
static int MAX_X = 320;
static int MAX_Y = 240;

CFire::CFire(){
     Colors::ColorDefinition color1;
	 Colors::ColorDefinition color2;
	 Colors::ColorDefinition color3;
	 Colors::ColorDefinition color4;
	color1.r= 64;
	color1.g= 0;
	color1.b= 0;
	color2.r= 255;
	color2.g= 0;
	color2.b= 0;
	color3.r= 255;
	color3.g= 255;
	color3.b= 0;
	color4.r= 255;
	color4.g= 255;
	color4.b= 255;
	Colors::blend_palette(colors, 64, color1, color2);
    Colors::blend_palette(colors + 64, 64, color2, color3);
    Colors::blend_palette(colors + 64 + 64, 96, color3, color4);
    Colors::blend_palette(colors + 64 + 64 + 64 + 32, 32, color4,color4);

    data = new unsigned char*[MAX_Y];
    for (int i = 0; i < MAX_Y; i++){
        data[i] = new unsigned char[MAX_X];
        memset(data[i], 0, MAX_X);
    }

    for (int i = 0; i < MAX_HOTSPOTS; i++){
        hotspots[i] = Util::rnd(MAX_X);
        directions[i] = 0;
    }

    for (int i = 0; i < MAX_WISPS; i++){
        Wisp & wisp = wisps[i];
        wisp.y = MAX_Y-1 + Util::rnd(MAX_Y);
        wisp.x = Util::rnd(MAX_X);
        wisp.life = MAX_Y;
        wisp.angle = Util::rnd(360);
    }
}

void CFire::updateHotspots(){
    for (int i = 0; i < MAX_HOTSPOTS; i++){
        // hotspots[i] = (hotspots[i] + Util::rnd(5) - 2) % MAX_X;
        hotspots[i] += directions[i];
        if (hotspots[i] >= MAX_X){
            hotspots[i] -= MAX_X;
        }
        if (hotspots[i] < 0){
            hotspots[i] += MAX_X;
        }
        directions[i] += (double) (Util::rnd(7) - 3) / 5.0;
        if (directions[i] < -4){
            directions[i] = -4;
        }
        if (directions[i] > 4){
            directions[i] = 4;
        }
    }

    int hotspot_length = 40;

    for (int i = 0; i < MAX_HOTSPOTS; i++){
        for (int x = -hotspot_length/2; x < hotspot_length/2; x++){
            int position = ((int) hotspots[i] + x + MAX_X) % MAX_X;
            int more = (int) (data[MAX_Y-1][position] + (hotspot_length / 2 - fabs((double)x)));
            if (more >= MAX_COLORS){
                more = MAX_COLORS - 1;
            }
            data[MAX_Y-1][position] = more;
        }
    }
}

void CFire::updateWisps(){
    for (int i = 0; i < MAX_WISPS; i++){
        Wisp & wisp = wisps[i];
        wisp.y -= 2;
        wisp.life -= 1;
        wisp.angle = (wisp.angle + 1) % 360;
        if (wisp.life < 0){
            wisp.y = MAX_Y-1 + Util::rnd(MAX_Y);
            wisp.life = MAX_Y;
        }

        int my = (int) wisp.y;
        int mx = (int)(wisp.x + sin(Util::radians(wisp.angle)) * 10);
        if (mx < 0){
            mx += MAX_X;
        }
        if (mx >= MAX_X){
            mx -= MAX_X;
        }
        if (my > 0 && my < MAX_Y){
            int z = data[my][mx] + wisp.life * 2;
            if (z >= MAX_COLORS){
                z = MAX_COLORS - 1;
            }
            // z = MAX_COLORS - 1;
            // cout << "Update flicker at " << mx << ", " << my << " to " << z << endl;
            data[my][mx] = z;
        }
    }
}

void CFire::update(){
    updateHotspots();
    // updateWisps();

//    int decay = 1;

    // for (int y = MAX_Y-1; y > 0; y--){
    for (int y = 0; y < MAX_Y; y++){
        for (int x = 0; x < MAX_X; x++){
            if (y < MAX_Y-1){
                int lx = x-1;
                if (lx < 0){
                    lx += MAX_X;
                }
                int rx = x+1;
                if (rx >= MAX_X){
                    rx -= MAX_X;
                }
                // int less = (int)((double) data[y+1][x] * 0.6 + (double) data[y+1][lx] * 0.3 + (double) data[y+1][rx] * 0.3);
                unsigned char * down = data[y+1];
                /* dont change these numbers (0.2, 0.62, 9) because they affect
                 * the height of the flames. if the value of fire does not go down
                 * monotonically then the entire screen will be filled with flames.
                 */
                int less = (int)((double) down[lx] * 0.19);
                less += (int)((double) down[rx] * 0.19);
                less += (int)((double) down[x] * (0.4 + Util::rnd(25) / 100.0));
                less += (int)((double) data[y][x] * 0.10);
                // less -= Util::rnd(15);
                if (less < 0){
                    less = 0;
                }
                if (less >= MAX_COLORS){
                    less = MAX_COLORS - 1;
                }
                data[y][x] = (unsigned char) less;
            } else {
                int less = (int)((double) data[y][x] * 0.95);
                if (less < 0){
                    less = 0;
                }
                data[y][x] = (unsigned char) less;
            }
        }
    }
}

void CFire::draw(const CBitmap & work){
    //CBitmap::drawingMode(CBitmap::MODE_TRANS);
    for (int y = 0; y < MAX_Y; y++){
        for (int x = 0; x < MAX_X; x++){
            // work.putPixelSurface(x, y, colors[data[y][x]]);
            if (data[y][x] > 0){
                work.polygon().rectangleFill(x*2, y*2, x*2+1, y*2+1, colors[data[y][x]]);
            }
        }
    }
    // CBitmap::drawingMode(CBitmap::MODE_SOLID);
}

CFire::~CFire(){
    for (int y = 0; y < MAX_Y; y++){
        delete[] data[y];
    }
    delete[] data;
}

} //end SGF

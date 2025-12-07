#include "fire.h"

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "freesia_tuilib.h"

Fire init_fire(short w, short h, int heat) {
    srand(time(NULL));
    
    short** mat = malloc(h * sizeof(short*));
    for (int i=0; i<=h; i++) {
        mat[i] = malloc(w * sizeof(short));
        
        // set heat randomly
        for (int j=0; j<=w; j++) {
            if (i>=h) {
                mat[i][j] = heat - (rand()%(heat/2));
            } 
        }
    }
    
    Fire fire = {
        w,
        h,
        heat,
        mat
    };

    return fire;
}


void update_fire(Fire* fire, short direction, short heat_decay, short extinguish) {
    short height = fire->height;
    short width = fire->width;

    for (int h=0; h<height; h++) {
        for (int w=0; w<width; w++) {
            int prevh, prevw, new_heat;
            prevh = h+1;
            if (direction > 0) prevw = w + (rand()%abs(direction));
            else if (direction<0) prevw = w - (rand()%abs(direction));
            prevw += (rand()*10 < 5)? 1 : -1;

            //making sure we are in bound
            if (w<width && w>0) {
                new_heat = fire->fire_mat[prevh][prevw] - (1+rand()%heat_decay);
            } else {
                new_heat = fire->fire_mat[prevh][w] - (1+rand()%heat_decay*2);
            }
            // the higher it is the more chance it get to decay of +1
            if ((rand()%height-h) < height/fire->heat ) new_heat--;
            if (new_heat<0) new_heat = 0;
            fire->fire_mat[h][w] = new_heat;
        }
    }

    if (extinguish>0) {
        for (int w=0; w<width; w++) {
            fire->fire_mat[height][w] -= (1+rand()%heat_decay*2);
        }
    }
}

void free_fire(Fire* fire) {
    if (fire->fire_mat != NULL) {
        for (int i=0; i<= fire->height; i++) {
            if (fire->fire_mat[i] != NULL) free(fire->fire_mat[i]);
        }
        free(fire->fire_mat);
    }
}

void _render_fire_values(Fire* fire) {
    short height = fire->height;
    short width = fire->width;
    for (short i=0; i<height; i++) {
        for (short j=0; j<width; j++) {
            printf("%2.d", fire->fire_mat[i][j]);
        }
        printf("\n");
    }

}

void render_fire(Fire* fire, char* charmap) {
    static int colors[9] = {
        0x300000,
        0x5c0101, 
        0xa30000,  
        0xff0000,  
        0xff8330,  
        0xff8335,  
        0xffc130,  
        0xfff5f5,  
        0xfff9f9   
    };

    short height = fire->height;
    short width = fire->width;
    short maxheat = fire->heat;

    for (short i = 0; i < height; i++) {
        
        
        for (short j = 0; j < width; j++) {
            setCursorPos(j, i);
            short heat = fire->fire_mat[i][j];
            if (heat < 0)        heat = 0;
            if (heat > maxheat)  heat = 0;
            
            int idx = (heat * 8) / maxheat;

            setTextColor(COLORSPACE_RGB, colors[idx]);
            putchar(charmap[heat]);
        }
    }

}


#ifndef FIRE_H
#define FIRE_H

typedef struct {
    short width;
    short height;
    short heat;
    short** fire_mat;
} Fire;

Fire init_fire(short w, short h, int heat);
void free_fire(Fire* fire);
void update_fire(Fire* fire, short direction, short heat_decay, short extinguish);
 
void render_fire(Fire* fire, char* charmap);

// used for debuging 
void _render_fire_values(Fire* fire);

#endif
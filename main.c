#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

#include "src/fire.h"
#include "src/freesia_tuilib.h"

//TODO remove heat

TermW tw = {10, 10};
char* asciiTable = " ..\'``\",,,:::;IIIl!!iii????*####&&&8888MMWWBBBBB@@@@@$$$$░░░▒▒▒▓▓▓\0";

short direction = 1;
short heat = 80;
short heat_decay = 2;

short exit_code = 0;

Fire fire;

void clear_on_close(int sig) {
    TermW tw = TermWGet();
    
    for (int i=0; i<heat; i++) {
        setCursorPos(0,0);
        render_fire(&fire, asciiTable);
        update_fire(&fire, direction, heat_decay, 1);
        usleep(80000);
    }

    free_fire(&fire);

    exit(0);
}

// clear screen and reset style on exit
void resetStyleOnEnd( void ) __attribute__ ((destructor)); 
void resetStyleOnEnd( void ) {
    if (exit_code==0) {
        for (short i=0; i<tw.height;i++) printf("\n");
        setCursorPos(0,0);
        resetStyle();
    } else {
        resetStyle();
    }
    
}

int main(int argc, char* argv[]) {

    tw = TermWGet();
    fire = init_fire(tw.width, tw.height+1, heat);
    signal(SIGINT, clear_on_close);

    if (argc < 2) {
        setTextColor(COLORSPACE_RGB, 0xff0000);
        printf("Usage: %s heat_decay (direction) \n", argv[0]);
        resetStyle();
        exit_code = 1;
        return 1;
    }

    heat_decay = atoi(argv[1]);
    // prevent crash with invalid values
    heat_decay = heat_decay>0?heat_decay: 1;

    if (argc >= 3) direction = atoi(argv[2]);

    for (int i=0; i<1000; i--) { //made the loop infinite
        setCursorPos(0,0);
        render_fire(&fire, asciiTable);
        update_fire(&fire, direction, heat_decay, 0);

        usleep(80000);
    }

    // never called exept if the loop somehow stops
    free_fire(&fire);

    return 0;
}
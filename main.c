#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

#include "src/fire.h"
#include "src/freesia_tuilib.h"

TermW tw = {10, 10};
char* asciiTable = " ..\'``\",,,:::;IIIl!!iii????*####&&&8888MMWWBBBBB@@@@@$$$$░░░▒▒▒▓▓▓\0";

short direction = 0;
short heat = 80;
short heat_decay = 2;

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

    for (short i=0; i<tw.height;i++) printf("\n");
    setCursorPos(0,0);
    resetStyle();
    exit(0);
}

int main(int argc, char* argv[]) {

    tw = TermWGet();
    fire = init_fire(tw.width, tw.height+1, heat);
    signal(SIGINT, clear_on_close);

    if (argc < 3) {
        setTextColor(COLORSPACE_RGB, 0xff0000);
        printf("Usage: %s heat(short), heat_decay(short) \n", argv[0]);
        resetStyle();
        return 1;
    }

    heat = atoi(argv[1]);
    heat_decay = atoi(argv[2]);

    if (argc >= 4) direction = atoi(argv[3]);
    
    if (heat > strlen(asciiTable)) {
        setTextColor(COLORSPACE_RGB, 0xff0000);
        printf("Value: %d heat(short) is too high, maximum value is %d\n", heat, strlen(asciiTable));
        resetStyle();
        return 2;
    }

    for (int i=0; i<1000; i--) { //made the loop infinite
        setCursorPos(0,0);
        render_fire(&fire, asciiTable);
        update_fire(&fire, direction, heat_decay, 0);

        usleep(80000);
    }

    //free_fire(&fire);

    return 0;
}
#ifndef FREESIA_TUILIB_H
#define FREESIA_TUILIB_H

#ifndef VECTOR2_H
// STRUCT
typedef struct {
    int x;
    int y;
} Vec2i;

int vec2i_distance(Vec2i a, Vec2i b);
#endif
#ifndef ANSI_STYLES_H

#define COLORSPACE_NULL     0x0
#define COLORSPACE_ANSI     0x1
#define COLORSPACE_RGB      0x2

#define FONTTYPE_BOLD       0x1 // 0001
#define FONTTYPE_UNDERLINE  0x2 // 0010

#define ALIGN_CENTER 'c'
#define ALIGN_LEFT 'l'
#define ALIGN_RIGHT 'r'
#define ALIGN_TOP 't'
#define ALIGN_BOTTOM 'b'

//STRUCT
typedef struct {
    unsigned char COLORSPACE;
    int color;
    int bgColor;
    unsigned char FONTTYPE;
    unsigned char halign;
    unsigned char valign;
} AnsiStyle;

// FUNCTIONS
AnsiStyle parse_style(char* filepath, char* classname);

void setTextColor(int COLORSPACE, int color);
void setTextBgColor(int COLORSPACE, int bgColor);
void setTextFontType(int FONTTYPE);
void setTextStyle(AnsiStyle* style);
void resetStyle();


#endif
#ifndef ANSI_CURSOR_H

#define ANSI_CURSOR_UP 'A'
#define ANSI_CURSOR_DOWN 'B'
#define ANSI_CURSOR_LEFT 'D'
#define ANSI_CURSOR_RIGHT 'C'

void setCursorPos(int column, int line);
void moveCursor(int directionFlag, int amount);

#endif
#ifndef WIDGETS_H
// STRUCT
typedef struct {
    short width;
    short height;
} TermW;
typedef struct {
    Vec2i upperleft;
    Vec2i lowerright;
    AnsiStyle* style;
} Box;
// box with text goes brrrr
typedef struct {
    Box box;
    char* content;
} Label;

// FUNCTIONS
TermW TermWGet();
int does_fit_in(Box* box, TermW* w);
void drawBox(Box* box);
void drawLabel(Label* label);

#endif

#endif
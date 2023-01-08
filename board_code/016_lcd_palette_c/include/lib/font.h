#ifndef __FONT_H
#define __FONT_H

extern const unsigned char fontdata_7x14[];
extern const unsigned char fontdata_8x8[];
extern const unsigned char fontdata_6x11[];
extern const unsigned char fontdata_8x16[];

void draw_char_8x8(int x, int y, char ch, int frontColor, int background);
void draw_char_8x16(int x, int y, char ch, int frontColor, int background);
void draw_char_6x11(int x, int y, char ch, int frontColor, int background);
void draw_char_7x14(int x, int y, char ch, int frontColor, int background);

#endif



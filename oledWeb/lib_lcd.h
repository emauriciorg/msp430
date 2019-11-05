//  Author: declis (xdec.de)

#ifndef LIB_LCD_H_
#define LIB_LCD_H_

struct meta_b
{
	signed int x,y;
	unsigned char direction;
};

// P1 is Data-Port (Parallel-Interface)
#define CS		0x0010		// P2.4
#define RES		0x0008		// P2.3
#define DC		0x0004		// P2.2
#define WR		0x0002		// P2.1
#define RD		0x0001		// P2.0

#define lcd_width		128
#define lcd_height		64
#define lcd_height_b	8

#define space_char	1		// space between chars

void bouncy_bmp(signed int,unsigned int,unsigned int,unsigned int,unsigned int,const char*);
void draw_metaballs(struct meta_b*,unsigned char,unsigned int);
unsigned int get_meta_pot(signed int,signed int,struct meta_b,unsigned int);
void meta_ball_physics(struct meta_b*,unsigned char,unsigned char,unsigned int);
void clean_area(unsigned char,unsigned char,unsigned char,unsigned char);
void string_typer(unsigned char,unsigned char,const char*,unsigned char,unsigned int);
void write_h_string(unsigned char,unsigned char,const char*,unsigned char);
void draw_string_sin_fixed(signed int,signed int,const char*,unsigned int,unsigned char);
void draw_string_sin(signed int,signed int,const char*,unsigned char);
void draw_string(signed int,signed int,const char*);
void draw_bitmap(signed int,signed int,unsigned int,unsigned int,const char*);
void convert_font_size(unsigned char,unsigned char,unsigned char,unsigned char);
void write_string(unsigned char,unsigned char,const char*,unsigned char);
void write_char(unsigned char,unsigned char,unsigned char,unsigned char);
void send_data_array(const char*,unsigned char);
void set_cursor(unsigned char,unsigned char);
void fill_display(unsigned char,unsigned char,unsigned char);
void set_instruction(unsigned char,unsigned char);

#endif /*LIB_LCD_H_*/

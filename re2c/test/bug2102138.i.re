#include <stdio.h>

int scan(const unsigned char *cr)
{
	unsigned char  ch;
/*!re2c

re2c:define:YYCTYPE     = "unsigned char";
re2c:define:YYCURSOR    = cr;
re2c:define:YYFILL      = fill;
re2c:variable:yych      = ch;
re2c:yyfill:enable      = 0;

"\x00" := return 0x00;
"\x01" := return 0x01;
"\x02" := return 0x02;
"\x03" := return 0x03;
"\x04" := return 0x04;
"\x05" := return 0x05;
"\x06" := return 0x06;
"\x07" := return 0x07;
"\x08" := return 0x08;
"\x09" := return 0x09;
"\x0A" := return 0x0A;
"\x0B" := return 0x0B;
"\x0C" := return 0x0C;
"\x0D" := return 0x0D;
"\x0E" := return 0x0E;
"\x0F" := return 0x0F;

"\x10" := return 0x10;
"\x11" := return 0x11;
"\x12" := return 0x12;
"\x13" := return 0x13;
"\x14" := return 0x14;
"\x15" := return 0x15;
"\x16" := return 0x16;
"\x17" := return 0x17;
"\x18" := return 0x18;
"\x19" := return 0x19;
"\x1A" := return 0x1A;
"\x1B" := return 0x1B;
"\x1C" := return 0x1C;
"\x1D" := return 0x1D;
"\x1E" := return 0x1E;
"\x1F" := return 0x1F;

" " := return 0x20;
"!" := return 0x21;
"\"" := return 0x22;
"#" := return 0x23;
"$" := return 0x24;
"%" := return 0x25;
"&" := return 0x26;
"'" := return 0x27;
"(" := return 0x28;
")" := return 0x29;
"*" := return 0x2A;
"+" := return 0x2B;
"," := return 0x2C;
"-" := return 0x2D;
"." := return 0x2E;
"/" := return 0x2F;

"0" := return 0x30;
"1" := return 0x31;
"2" := return 0x32;
"3" := return 0x33;
"4" := return 0x34;
"5" := return 0x35;
"6" := return 0x36;
"7" := return 0x37;
"8" := return 0x38;
"9" := return 0x39;
":" := return 0x3A;
";" := return 0x3B;
"<" := return 0x3C;
"=" := return 0x3D;
">" := return 0x3E;
"?" := return 0x3F;

"@" := return 0x40;
"A" := return 0x41;
"B" := return 0x42;
"C" := return 0x43;
"D" := return 0x44;
"E" := return 0x45;
"F" := return 0x46;
"G" := return 0x47;
"H" := return 0x48;
"I" := return 0x49;
"J" := return 0x4A;
"K" := return 0x4B;
"L" := return 0x4C;
"M" := return 0x4D;
"N" := return 0x4E;
"O" := return 0x4F;

"P" := return 0x50;
"Q" := return 0x51;
"R" := return 0x52;
"S" := return 0x53;
"T" := return 0x54;
"U" := return 0x55;
"V" := return 0x56;
"W" := return 0x57;
"X" := return 0x58;
"Y" := return 0x59;
"Z" := return 0x5A;
"[" := return 0x5B;
"\\" := return 0x5C;
"]" := return 0x5D;
"^" := return 0x5E;
"_" := return 0x5F;

"`" := return 0x60;
"a" := return 0x61;
"b" := return 0x62;
"c" := return 0x63;
"d" := return 0x64;
"e" := return 0x65;
"f" := return 0x66;
"g" := return 0x67;
"h" := return 0x68;
"i" := return 0x69;
"j" := return 0x6A;
"k" := return 0x6B;
"l" := return 0x6C;
"m" := return 0x6D;
"n" := return 0x6E;
"o" := return 0x6F;

"p" := return 0x70;
"q" := return 0x71;
"r" := return 0x72;
"s" := return 0x73;
"t" := return 0x74;
"u" := return 0x75;
"v" := return 0x76;
"w" := return 0x77;
"x" := return 0x78;
"y" := return 0x79;
"z" := return 0x7A;
"{" := return 0x7B;
"|" := return 0x7C;
"}" := return 0x7D;
"~" := return 0x7E;
"\x7F" := return 0x7F;

"\x80" := return 0x80;
"\x81" := return 0x81;
"\x82" := return 0x82;
"\x83" := return 0x83;
"\x84" := return 0x84;
"\x85" := return 0x85;
"\x86" := return 0x86;
"\x87" := return 0x87;
"\x88" := return 0x88;
"\x89" := return 0x89;
"\x8A" := return 0x8A;
"\x8B" := return 0x8B;
"\x8C" := return 0x8C;
"\x8D" := return 0x8D;
"\x8E" := return 0x8E;
"\x8F" := return 0x8F;

"\x90" := return 0x90;
"\x91" := return 0x91;
"\x92" := return 0x92;
"\x93" := return 0x93;
"\x94" := return 0x94;
"\x95" := return 0x95;
"\x96" := return 0x96;
"\x97" := return 0x97;
"\x98" := return 0x98;
"\x99" := return 0x99;
"\x9A" := return 0x9A;
"\x9B" := return 0x9B;
"\x9C" := return 0x9C;
"\x9D" := return 0x9D;
"\x9E" := return 0x9E;
"\x9F" := return 0x9F;

"\xA0" := return 0xA0;
"\xA1" := return 0xA1;
"\xA2" := return 0xA2;
"\xA3" := return 0xA3;
"\xA4" := return 0xA4;
"\xA5" := return 0xA5;
"\xA6" := return 0xA6;
"\xA7" := return 0xA7;
"\xA8" := return 0xA8;
"\xA9" := return 0xA9;
"\xAA" := return 0xAA;
"\xAB" := return 0xAB;
"\xAC" := return 0xAC;
"\xAD" := return 0xAD;
"\xAE" := return 0xAE;
"\xAF" := return 0xAF;

"\xB0" := return 0xB0;
"\xB1" := return 0xB1;
"\xB2" := return 0xB2;
"\xB3" := return 0xB3;
"\xB4" := return 0xB4;
"\xB5" := return 0xB5;
"\xB6" := return 0xB6;
"\xB7" := return 0xB7;
"\xB8" := return 0xB8;
"\xB9" := return 0xB9;
"\xBA" := return 0xBA;
"\xBB" := return 0xBB;
"\xBC" := return 0xBC;
"\xBD" := return 0xBD;
"\xBE" := return 0xBE;
"\xBF" := return 0xBF;

"\xC0" := return 0xC0;
"\xC1" := return 0xC1;
"\xC2" := return 0xC2;
"\xC3" := return 0xC3;
"\xC4" := return 0xC4;
"\xC5" := return 0xC5;
"\xC6" := return 0xC6;
"\xC7" := return 0xC7;
"\xC8" := return 0xC8;
"\xC9" := return 0xC9;
"\xCA" := return 0xCA;
"\xCB" := return 0xCB;
"\xCC" := return 0xCC;
"\xCD" := return 0xCD;
"\xCE" := return 0xCE;
"\xCF" := return 0xCF;

"\xD0" := return 0xD0;
"\xD1" := return 0xD1;
"\xD2" := return 0xD2;
"\xD3" := return 0xD3;
"\xD4" := return 0xD4;
"\xD5" := return 0xD5;
"\xD6" := return 0xD6;
"\xD7" := return 0xD7;
"\xD8" := return 0xD8;
"\xD9" := return 0xD9;
"\xDA" := return 0xDA;
"\xDB" := return 0xDB;
"\xDC" := return 0xDC;
"\xDD" := return 0xDD;
"\xDE" := return 0xDE;
"\xDF" := return 0xDF;

"\xE0" := return 0xE0;
"\xE1" := return 0xE1;
"\xE2" := return 0xE2;
"\xE3" := return 0xE3;
"\xE4" := return 0xE4;
"\xE5" := return 0xE5;
"\xE6" := return 0xE6;
"\xE7" := return 0xE7;
"\xE8" := return 0xE8;
"\xE9" := return 0xE9;
"\xEA" := return 0xEA;
"\xEB" := return 0xEB;
"\xEC" := return 0xEC;
"\xED" := return 0xED;
"\xEE" := return 0xEE;
"\xEF" := return 0xEF;

"\xF0" := return 0xF0;
"\xF1" := return 0xF1;
"\xF2" := return 0xF2;
"\xF3" := return 0xF3;
"\xF4" := return 0xF4;
"\xF5" := return 0xF5;
"\xF6" := return 0xF6;
"\xF7" := return 0xF7;
"\xF8" := return 0xF8;
"\xF9" := return 0xF9;
"\xFA" := return 0xFA;
"\xFB" := return 0xFB;
"\xFC" := return 0xFC;
"\xFD" := return 0xFD;
"\xFE" := return 0xFE;
"\xFF" := return 0xFF;

*/
}

int main(int argc, char** argv) {
	unsigned char buf[2];
	unsigned int ch = 0;
	buf[1] = 0u;

	printf("const uint asc2asc[256] =\n");
	printf("    {\n");
	for (;;) {
		if (ch % 16 == 0) {
			printf("        ");
		}
		buf[0] = ch++;
		printf("0x%02x", scan(buf));
		if (ch == 256) {
			printf("\n");
			break;
		}
		if (ch % 16 == 0) {
			printf(",\n");
		} else {
			printf(", ");
		}
	}
	printf("    };\n");
	return 0;
}

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

"\x20" := return 0x20;
"\x21" := return 0x21;
"\x22" := return 0x22;
"\x23" := return 0x23;
"\x24" := return 0x24;
"\x25" := return 0x25;
"\x26" := return 0x26;
"\x27" := return 0x27;
"\x28" := return 0x28;
"\x29" := return 0x29;
"\x2A" := return 0x2A;
"\x2B" := return 0x2B;
"\x2C" := return 0x2C;
"\x2D" := return 0x2D;
"\x2E" := return 0x2E;
"\x2F" := return 0x2F;

"\x30" := return 0x30;
"\x31" := return 0x31;
"\x32" := return 0x32;
"\x33" := return 0x33;
"\x34" := return 0x34;
"\x35" := return 0x35;
"\x36" := return 0x36;
"\x37" := return 0x37;
"\x38" := return 0x38;
"\x39" := return 0x39;
"\x3A" := return 0x3A;
"\x3B" := return 0x3B;
"\x3C" := return 0x3C;
"\x3D" := return 0x3D;
"\x3E" := return 0x3E;
"\x3F" := return 0x3F;

"\x40" := return 0x40;
"\x41" := return 0x41;
"\x42" := return 0x42;
"\x43" := return 0x43;
"\x44" := return 0x44;
"\x45" := return 0x45;
"\x46" := return 0x46;
"\x47" := return 0x47;
"\x48" := return 0x48;
"\x49" := return 0x49;
"\x4A" := return 0x4A;
"\x4B" := return 0x4B;
"\x4C" := return 0x4C;
"\x4D" := return 0x4D;
"\x4E" := return 0x4E;
"\x4F" := return 0x4F;

"\x50" := return 0x50;
"\x51" := return 0x51;
"\x52" := return 0x52;
"\x53" := return 0x53;
"\x54" := return 0x54;
"\x55" := return 0x55;
"\x56" := return 0x56;
"\x57" := return 0x57;
"\x58" := return 0x58;
"\x59" := return 0x59;
"\x5A" := return 0x5A;
"\x5B" := return 0x5B;
"\x5C" := return 0x5C;
"\x5D" := return 0x5D;
"\x5E" := return 0x5E;
"\x5F" := return 0x5F;

"\x60" := return 0x60;
"\x61" := return 0x61;
"\x62" := return 0x62;
"\x63" := return 0x63;
"\x64" := return 0x64;
"\x65" := return 0x65;
"\x66" := return 0x66;
"\x67" := return 0x67;
"\x68" := return 0x68;
"\x69" := return 0x69;
"\x6A" := return 0x6A;
"\x6B" := return 0x6B;
"\x6C" := return 0x6C;
"\x6D" := return 0x6D;
"\x6E" := return 0x6E;
"\x6F" := return 0x6F;

"\x70" := return 0x70;
"\x71" := return 0x71;
"\x72" := return 0x72;
"\x73" := return 0x73;
"\x74" := return 0x74;
"\x75" := return 0x75;
"\x76" := return 0x76;
"\x77" := return 0x77;
"\x78" := return 0x78;
"\x79" := return 0x79;
"\x7A" := return 0x7A;
"\x7B" := return 0x7B;
"\x7C" := return 0x7C;
"\x7D" := return 0x7D;
"\x7E" := return 0x7E;
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

	printf("const uint ebc2asc[256] =\n");
	printf("    { /* Based on ISO 8859/1 and Code Page 37 */\n");
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

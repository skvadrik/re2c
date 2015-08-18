#include <string.h>

#include "src/parse/scanner.h"
#include "src/parse/unescape.h"

namespace re2c {

// expected characters: [0-9a-zA-Z]
static inline uint32_t hex_digit (const char c)
{
	switch (c)
	{
		case '0': return 0;
		case '1': return 1;
		case '2': return 2;
		case '3': return 3;
		case '4': return 4;
		case '5': return 5;
		case '6': return 6;
		case '7': return 7;
		case '8': return 8;
		case '9': return 9;
		case 'a':
		case 'A': return 0xA;
		case 'b':
		case 'B': return 0xB;
		case 'c':
		case 'C': return 0xC;
		case 'd':
		case 'D': return 0xD;
		case 'e':
		case 'E': return 0xE;
		case 'f':
		case 'F': return 0xF;
		default:  return ~0u; // unexpected
	}
}

// expected string format: "\" [abfnrtv\\]
uint32_t unesc_escapable (char * s)
{
	switch (s[1])
	{
		case 'a': return '\a';
		case 'b': return '\b';
		case 'f': return '\f';
		case 'n': return '\n';
		case 'r': return '\r';
		case 't': return '\t';
		case 'v': return '\v';
		case '\\': return '\\';
		default:  return ~0u; // unexpected
	}
}

// expected string format: "\" [xXuU] [0-9a-zA-Z]*
uint32_t unesc_hex (const char * s, const char * s_end)
{
	uint32_t n = 0;
	for (s += 2; s != s_end; ++s)
	{
		n <<= 4;
		n += hex_digit (*s);
	}
	return n;
}

// expected string format: "\" [0-7]*
uint32_t unesc_oct (const char * s, const char * s_end)
{
	uint32_t n = 0;
	for (++s; s != s_end; ++s)
	{
		n <<= 3;
		n += static_cast<uint32_t> (*s - '0');
	}
	return n;
}

uint32_t Scanner::unescape(SubStr &s) const
{
	static const char * hex = "0123456789abcdef";
	static const char * oct = "01234567";

	s.len--;
	uint32_t c, ucb = 0;

	if ((c = *s.str++) != '\\' || s.len == 0)
	{
		return c;
	}

	s.len--;

	switch (c = *s.str++)
	{
		case 'n': return '\n';
		case 't': return '\t';
		case 'v': return '\v';
		case 'b': return '\b';
		case 'r': return '\r';
		case 'f': return '\f';
		case 'a': return '\a';

		case 'x':
		{
			if (s.len < 2)
			{
				fatal(s.ofs()+s.len, "Illegal hexadecimal character code, two hexadecimal digits are required");
				return ~0u;
			}
			
			const char *p1 = strchr(hex, tolower(s.str[0]));
			const char *p2 = strchr(hex, tolower(s.str[1]));

			if (!p1 || !p2)
			{
				fatal(s.ofs()+(p1?1:0), "Illegal hexadecimal character code");
				return ~0u;
			}
			else
			{
				s.len -= 2;
				s.str += 2;
				
				uint32_t v = (uint32_t)((p1 - hex) << 4) 
				       + (uint32_t)((p2 - hex));
	
				return v;
			}
		}

		case 'U':
		{
			if (s.len < 8)
			{
				fatal(s.ofs()+s.len, "Illegal unicode character, eight hexadecimal digits are required");
				return ~0u;
			}

			uint32_t l = 0;
			if (s.str[0] == '0')
			{
				l++;
				if (s.str[1] == '0')
				{
					l++;
					if (s.str[2] == '0' || (s.str[2] == '1' && encoding.szCodePoint() == 4))
					{
						l++;
						if (encoding.szCodePoint() == 4)
						{
							const char *u3 = strchr(hex, tolower(s.str[2]));
							const char *u4 = strchr(hex, tolower(s.str[3]));
							if (u3 && u4)
							{
								ucb = (uint32_t)((u3 - hex) << 20)
							        + (uint32_t)((u4 - hex) << 16);
								l++;
							}
						}
						else if (s.str[3] == '0')
						{
							l++;
						}
					}
				}
			}

			if (l != 4)
			{
				fatal(s.ofs()+l, "Illegal unicode character, eight hexadecimal digits are required");
			}

			s.len -= 4;
			s.str += 4;
			
			// no break;
		}
		case 'X':
		case 'u':
		{
			if (s.len < 4)
			{
				fatal(s.ofs()+s.len, 
					c == 'X'
					? "Illegal hexadecimal character code, four hexadecimal digits are required"
					: "Illegal unicode character, four hexadecimal digits are required");
				return ~0u;
			}
			
			const char *p1 = strchr(hex, tolower(s.str[0]));
			const char *p2 = strchr(hex, tolower(s.str[1]));
			const char *p3 = strchr(hex, tolower(s.str[2]));
			const char *p4 = strchr(hex, tolower(s.str[3]));

			if (!p1 || !p2 || !p3 || !p4)
			{
				fatal(s.ofs()+(p1?1:0)+(p2?1:0)+(p3?1:0), 
					c == 'X'
					? "Illegal hexadecimal character code, non hexxdecimal digit found"
					: "Illegal unicode character, non hexadecimal digit found");
				return ~0u;
			}
			else
			{
				s.len -= 4;
				s.str += 4;
				
				uint32_t v = (uint32_t)((p1 - hex) << 12) 
				       + (uint32_t)((p2 - hex) <<  8)
				       + (uint32_t)((p3 - hex) <<  4)
				       + (uint32_t)((p4 - hex))
				       + ucb;
	
				if (v >= encoding.nCodePoints())
				{
					fatal(s.ofs(),
						c == 'X'
						? "Illegal hexadecimal character code, out of range"
						: "Illegal unicode character, out of range");
				}
	
				return v;
			}
		}

		case '4':
		case '5':
		case '6':
		case '7':
		{
			fatal(s.ofs()-1, "Illegal octal character code, first digit must be 0 thru 3");
			return ~0u;
		}

		case '0':
		case '1':
		case '2':
		case '3':
		{
			if (s.len < 2)
			{
				fatal(s.ofs()+s.len, "Illegal octal character code, three octal digits are required");
				return ~0u;
			}

			const char *p0 = strchr(oct, c);
			const char *p1 = strchr(oct, s.str[0]);
			const char *p2 = strchr(oct, s.str[1]);

			if (!p0 || !p1 || !p2)
			{
				fatal(s.ofs()+(p1?1:0), "Illegal octal character code, non octal digit found");
				return ~0u;
			}
			else
			{
				s.len -= 2;
				s.str += 2;
				
				uint32_t v = (uint32_t)((p0 - oct) << 6) + (uint32_t)((p1 - oct) << 3) + (uint32_t)(p2 - oct);
	
				return v;
			}
		}

		default:
		return c;
	}
}

std::string& Scanner::unescape(SubStr& str_in, std::string& str_out) const
{
	str_out.clear();

	while(str_in.len)
	{
		uint32_t c = unescape(str_in);

		if (c > 0xFF)
		{
			fatal(str_in.ofs(), "Illegal character");
		}

		str_out += static_cast<char>(c);
	}

	return str_out;
}

} // namespace re2c

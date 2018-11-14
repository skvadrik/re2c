#include <stdio.h>

#define YYCTYPE unsigned int
enum Block
{
	Basic_Latin,
	Latin___Supplement,
	Latin_Extended_A,
	Latin_Extended_B,
	IPA_Extensions,
	Spacing_Modifier_Letters,
	Combining_Diacritical_Marks,
	Greek_and_Coptic,
	Cyrillic,
	Cyrillic_Supplementary,
	Armenian,
	Hebrew,
	Arabic,
	Syriac,
	Thaana,
	Devanagari,
	Bengali,
	Gurmukhi,
	Gujarati,
	Oriya,
	Tamil,
	Telugu,
	Kannada,
	Malayalam,
	Sinhala,
	Thai,
	Lao,
	Tibetan,
	Myanmar,
	Georgian,
	Hangul_Jamo,
	Ethiopic,
	Cherokee,
	Unified_Canadian_Aboriginal_Syllabics,
	Ogham,
	Runic,
	Tagalog,
	Hanunoo,
	Buhid,
	Tagbanwa,
	Khmer,
	Mongolian,
	Limbu,
	Tai_Le,
	Khmer_Symbols,
	Phonetic_Extensions,
	Latin_Extended_Additional,
	Greek_Extended,
	General_Punctuation,
	Superscripts_and_Subscripts,
	Currency_Symbols,
	Combining_Diacritical_Marks_for_Symbols,
	Letterlike_Symbols,
	Number_Forms,
	Arrows,
	Mathematical_Operators,
	Miscellaneous_Technical,
	Control_Pictures,
	Optical_Character_Recognition,
	Enclosed_Alphanumerics,
	Box_Drawing,
	Block_Elements,
	Geometric_Shapes,
	Miscellaneous_Symbols,
	Dingbats,
	Miscellaneous_Mathematical_Symbols_A,
	Supplemental_Arrows_A,
	Braille_Patterns,
	Supplemental_Arrows_B,
	Miscellaneous_Mathematical_Symbols_B,
	Supplemental_Mathematical_Operators,
	Miscellaneous_Symbols_and_Arrows,
	CJK_Radicals_Supplement,
	Kangxi_Radicals,
	Ideographic_Description_Characters,
	CJK_Symbols_and_Punctuation,
	Hiragana,
	Katakana,
	Bopomofo,
	Hangul_Compatibility_Jamo,
	Kanbun,
	Bopomofo_Extended,
	Katakana_Phonetic_Extensions,
	Enclosed_CJK_Letters_and_Months,
	CJK_Compatibility,
	CJK_Unified_Ideographs_Extension_A,
	Yijing_Hexagram_Symbols,
	CJK_Unified_Ideographs,
	Yi_Syllables,
	Yi_Radicals,
	Hangul_Syllables,
	High_Surrogates,
	High_Private_Use_Surrogates,
	Low_Surrogates,
	Private_Use_Area,
	CJK_Compatibility_Ideographs,
	Alphabetic_Presentation_Forms,
	Arabic_Presentation_Forms_A,
	Variation_Selectors,
	Combining_Half_Marks,
	CJK_Compatibility_Forms,
	Small_Form_Variants,
	Arabic_Presentation_Forms_B,
	Halfwidth_and_Fullwidth_Forms,
	Specials,
	All,

	Error
};
Block scan(const YYCTYPE * start, const YYCTYPE * const limit, Block blk)
{
	__attribute__((unused)) const YYCTYPE * YYMARKER; // silence compiler warnings when YYMARKER is not used
#	define YYCURSOR start
	switch (blk)
	{
		case Basic_Latin: goto Basic_Latin ;
		case Latin___Supplement: goto Latin___Supplement ;
		case Latin_Extended_A: goto Latin_Extended_A ;
		case Latin_Extended_B: goto Latin_Extended_B ;
		case IPA_Extensions: goto IPA_Extensions ;
		case Spacing_Modifier_Letters: goto Spacing_Modifier_Letters ;
		case Combining_Diacritical_Marks: goto Combining_Diacritical_Marks ;
		case Greek_and_Coptic: goto Greek_and_Coptic ;
		case Cyrillic: goto Cyrillic ;
		case Cyrillic_Supplementary: goto Cyrillic_Supplementary ;
		case Armenian: goto Armenian ;
		case Hebrew: goto Hebrew ;
		case Arabic: goto Arabic ;
		case Syriac: goto Syriac ;
		case Thaana: goto Thaana ;
		case Devanagari: goto Devanagari ;
		case Bengali: goto Bengali ;
		case Gurmukhi: goto Gurmukhi ;
		case Gujarati: goto Gujarati ;
		case Oriya: goto Oriya ;
		case Tamil: goto Tamil ;
		case Telugu: goto Telugu ;
		case Kannada: goto Kannada ;
		case Malayalam: goto Malayalam ;
		case Sinhala: goto Sinhala ;
		case Thai: goto Thai ;
		case Lao: goto Lao ;
		case Tibetan: goto Tibetan ;
		case Myanmar: goto Myanmar ;
		case Georgian: goto Georgian ;
		case Hangul_Jamo: goto Hangul_Jamo ;
		case Ethiopic: goto Ethiopic ;
		case Cherokee: goto Cherokee ;
		case Unified_Canadian_Aboriginal_Syllabics: goto Unified_Canadian_Aboriginal_Syllabics ;
		case Ogham: goto Ogham ;
		case Runic: goto Runic ;
		case Tagalog: goto Tagalog ;
		case Hanunoo: goto Hanunoo ;
		case Buhid: goto Buhid ;
		case Tagbanwa: goto Tagbanwa ;
		case Khmer: goto Khmer ;
		case Mongolian: goto Mongolian ;
		case Limbu: goto Limbu ;
		case Tai_Le: goto Tai_Le ;
		case Khmer_Symbols: goto Khmer_Symbols ;
		case Phonetic_Extensions: goto Phonetic_Extensions ;
		case Latin_Extended_Additional: goto Latin_Extended_Additional ;
		case Greek_Extended: goto Greek_Extended ;
		case General_Punctuation: goto General_Punctuation ;
		case Superscripts_and_Subscripts: goto Superscripts_and_Subscripts ;
		case Currency_Symbols: goto Currency_Symbols ;
		case Combining_Diacritical_Marks_for_Symbols: goto Combining_Diacritical_Marks_for_Symbols ;
		case Letterlike_Symbols: goto Letterlike_Symbols ;
		case Number_Forms: goto Number_Forms ;
		case Arrows: goto Arrows ;
		case Mathematical_Operators: goto Mathematical_Operators ;
		case Miscellaneous_Technical: goto Miscellaneous_Technical ;
		case Control_Pictures: goto Control_Pictures ;
		case Optical_Character_Recognition: goto Optical_Character_Recognition ;
		case Enclosed_Alphanumerics: goto Enclosed_Alphanumerics ;
		case Box_Drawing: goto Box_Drawing ;
		case Block_Elements: goto Block_Elements ;
		case Geometric_Shapes: goto Geometric_Shapes ;
		case Miscellaneous_Symbols: goto Miscellaneous_Symbols ;
		case Dingbats: goto Dingbats ;
		case Miscellaneous_Mathematical_Symbols_A: goto Miscellaneous_Mathematical_Symbols_A ;
		case Supplemental_Arrows_A: goto Supplemental_Arrows_A ;
		case Braille_Patterns: goto Braille_Patterns ;
		case Supplemental_Arrows_B: goto Supplemental_Arrows_B ;
		case Miscellaneous_Mathematical_Symbols_B: goto Miscellaneous_Mathematical_Symbols_B ;
		case Supplemental_Mathematical_Operators: goto Supplemental_Mathematical_Operators ;
		case Miscellaneous_Symbols_and_Arrows: goto Miscellaneous_Symbols_and_Arrows ;
		case CJK_Radicals_Supplement: goto CJK_Radicals_Supplement ;
		case Kangxi_Radicals: goto Kangxi_Radicals ;
		case Ideographic_Description_Characters: goto Ideographic_Description_Characters ;
		case CJK_Symbols_and_Punctuation: goto CJK_Symbols_and_Punctuation ;
		case Hiragana: goto Hiragana ;
		case Katakana: goto Katakana ;
		case Bopomofo: goto Bopomofo ;
		case Hangul_Compatibility_Jamo: goto Hangul_Compatibility_Jamo ;
		case Kanbun: goto Kanbun ;
		case Bopomofo_Extended: goto Bopomofo_Extended ;
		case Katakana_Phonetic_Extensions: goto Katakana_Phonetic_Extensions ;
		case Enclosed_CJK_Letters_and_Months: goto Enclosed_CJK_Letters_and_Months ;
		case CJK_Compatibility: goto CJK_Compatibility ;
		case CJK_Unified_Ideographs_Extension_A: goto CJK_Unified_Ideographs_Extension_A ;
		case Yijing_Hexagram_Symbols: goto Yijing_Hexagram_Symbols ;
		case CJK_Unified_Ideographs: goto CJK_Unified_Ideographs ;
		case Yi_Syllables: goto Yi_Syllables ;
		case Yi_Radicals: goto Yi_Radicals ;
		case Hangul_Syllables: goto Hangul_Syllables ;
		case High_Surrogates: goto High_Surrogates ;
		case High_Private_Use_Surrogates: goto High_Private_Use_Surrogates ;
		case Low_Surrogates: goto Low_Surrogates ;
		case Private_Use_Area: goto Private_Use_Area ;
		case CJK_Compatibility_Ideographs: goto CJK_Compatibility_Ideographs ;
		case Alphabetic_Presentation_Forms: goto Alphabetic_Presentation_Forms ;
		case Arabic_Presentation_Forms_A: goto Arabic_Presentation_Forms_A ;
		case Variation_Selectors: goto Variation_Selectors ;
		case Combining_Half_Marks: goto Combining_Half_Marks ;
		case CJK_Compatibility_Forms: goto CJK_Compatibility_Forms ;
		case Small_Form_Variants: goto Small_Form_Variants ;
		case Arabic_Presentation_Forms_B: goto Arabic_Presentation_Forms_B ;
		case Halfwidth_and_Fullwidth_Forms: goto Halfwidth_and_Fullwidth_Forms ;
		case Specials: goto Specials ;
		case All: goto All ;

		default: return Error;
	}
	/*!re2c
		Basic_Latin = [\x00-\x7f];
		Latin___Supplement = [\x80-\u00ff];
		Latin_Extended_A = [\u0100-\u017f];
		Latin_Extended_B = [\u0180-\u024f];
		IPA_Extensions = [\u0250-\u02af];
		Spacing_Modifier_Letters = [\u02b0-\u02ff];
		Combining_Diacritical_Marks = [\u0300-\u036f];
		Greek_and_Coptic = [\u0370-\u03ff];
		Cyrillic = [\u0400-\u04ff];
		Cyrillic_Supplementary = [\u0500-\u052f];
		Armenian = [\u0530-\u058f];
		Hebrew = [\u0590-\u05ff];
		Arabic = [\u0600-\u06ff];
		Syriac = [\u0700-\u074f];
		Thaana = [\u0780-\u07bf];
		Devanagari = [\u0900-\u097f];
		Bengali = [\u0980-\u09ff];
		Gurmukhi = [\u0a00-\u0a7f];
		Gujarati = [\u0a80-\u0aff];
		Oriya = [\u0b00-\u0b7f];
		Tamil = [\u0b80-\u0bff];
		Telugu = [\u0c00-\u0c7f];
		Kannada = [\u0c80-\u0cff];
		Malayalam = [\u0d00-\u0d7f];
		Sinhala = [\u0d80-\u0dff];
		Thai = [\u0e00-\u0e7f];
		Lao = [\u0e80-\u0eff];
		Tibetan = [\u0f00-\u0fff];
		Myanmar = [\u1000-\u109f];
		Georgian = [\u10a0-\u10ff];
		Hangul_Jamo = [\u1100-\u11ff];
		Ethiopic = [\u1200-\u137f];
		Cherokee = [\u13a0-\u13ff];
		Unified_Canadian_Aboriginal_Syllabics = [\u1400-\u167f];
		Ogham = [\u1680-\u169f];
		Runic = [\u16a0-\u16ff];
		Tagalog = [\u1700-\u171f];
		Hanunoo = [\u1720-\u173f];
		Buhid = [\u1740-\u175f];
		Tagbanwa = [\u1760-\u177f];
		Khmer = [\u1780-\u17ff];
		Mongolian = [\u1800-\u18af];
		Limbu = [\u1900-\u194f];
		Tai_Le = [\u1950-\u197f];
		Khmer_Symbols = [\u19e0-\u19ff];
		Phonetic_Extensions = [\u1d00-\u1d7f];
		Latin_Extended_Additional = [\u1e00-\u1eff];
		Greek_Extended = [\u1f00-\u1fff];
		General_Punctuation = [\u2000-\u206f];
		Superscripts_and_Subscripts = [\u2070-\u209f];
		Currency_Symbols = [\u20a0-\u20cf];
		Combining_Diacritical_Marks_for_Symbols = [\u20d0-\u20ff];
		Letterlike_Symbols = [\u2100-\u214f];
		Number_Forms = [\u2150-\u218f];
		Arrows = [\u2190-\u21ff];
		Mathematical_Operators = [\u2200-\u22ff];
		Miscellaneous_Technical = [\u2300-\u23ff];
		Control_Pictures = [\u2400-\u243f];
		Optical_Character_Recognition = [\u2440-\u245f];
		Enclosed_Alphanumerics = [\u2460-\u24ff];
		Box_Drawing = [\u2500-\u257f];
		Block_Elements = [\u2580-\u259f];
		Geometric_Shapes = [\u25a0-\u25ff];
		Miscellaneous_Symbols = [\u2600-\u26ff];
		Dingbats = [\u2700-\u27bf];
		Miscellaneous_Mathematical_Symbols_A = [\u27c0-\u27ef];
		Supplemental_Arrows_A = [\u27f0-\u27ff];
		Braille_Patterns = [\u2800-\u28ff];
		Supplemental_Arrows_B = [\u2900-\u297f];
		Miscellaneous_Mathematical_Symbols_B = [\u2980-\u29ff];
		Supplemental_Mathematical_Operators = [\u2a00-\u2aff];
		Miscellaneous_Symbols_and_Arrows = [\u2b00-\u2bff];
		CJK_Radicals_Supplement = [\u2e80-\u2eff];
		Kangxi_Radicals = [\u2f00-\u2fdf];
		Ideographic_Description_Characters = [\u2ff0-\u2fff];
		CJK_Symbols_and_Punctuation = [\u3000-\u303f];
		Hiragana = [\u3040-\u309f];
		Katakana = [\u30a0-\u30ff];
		Bopomofo = [\u3100-\u312f];
		Hangul_Compatibility_Jamo = [\u3130-\u318f];
		Kanbun = [\u3190-\u319f];
		Bopomofo_Extended = [\u31a0-\u31bf];
		Katakana_Phonetic_Extensions = [\u31f0-\u31ff];
		Enclosed_CJK_Letters_and_Months = [\u3200-\u32ff];
		CJK_Compatibility = [\u3300-\u33ff];
		CJK_Unified_Ideographs_Extension_A = [\u3400-\u4dbf];
		Yijing_Hexagram_Symbols = [\u4dc0-\u4dff];
		CJK_Unified_Ideographs = [\u4e00-\u9fff];
		Yi_Syllables = [\ua000-\ua48f];
		Yi_Radicals = [\ua490-\ua4cf];
		Hangul_Syllables = [\uac00-\ud7af];
		High_Surrogates = [\ud800-\udb7f];
		High_Private_Use_Surrogates = [\udb80-\udbff];
		Low_Surrogates = [\udc00-\udfff];
		Private_Use_Area = [\ue000-\uf8ff];
		CJK_Compatibility_Ideographs = [\uf900-\ufaff];
		Alphabetic_Presentation_Forms = [\ufb00-\ufb4f];
		Arabic_Presentation_Forms_A = [\ufb50-\ufdff];
		Variation_Selectors = [\ufe00-\ufe0f];
		Combining_Half_Marks = [\ufe20-\ufe2f];
		CJK_Compatibility_Forms = [\ufe30-\ufe4f];
		Small_Form_Variants = [\ufe50-\ufe6f];
		Arabic_Presentation_Forms_B = [\ufe70-\ufeff];
		Halfwidth_and_Fullwidth_Forms = [\uff00-\uffef];
		Specials = [\ufff0-\U0000ffff];
		All = [\x00-\u074f\u0780-\u07bf\u0900-\u137f\u13a0-\u18af\u1900-\u197f\u19e0-\u19ff\u1d00-\u1d7f\u1e00-\u2bff\u2e80-\u2fdf\u2ff0-\u31bf\u31f0-\ua4cf\uac00-\ud7af\ud800-\ufe0f\ufe20-\U0000ffff];

	*/
Basic_Latin:
	/*!re2c
		re2c:yyfill:enable = 0;
		Basic_Latin { goto Basic_Latin; }
		* { if (YYCURSOR == limit) return Basic_Latin; else return Error; }
	*/

Latin___Supplement:
	/*!re2c
		re2c:yyfill:enable = 0;
		Latin___Supplement { goto Latin___Supplement; }
		* { if (YYCURSOR == limit) return Latin___Supplement; else return Error; }
	*/

Latin_Extended_A:
	/*!re2c
		re2c:yyfill:enable = 0;
		Latin_Extended_A { goto Latin_Extended_A; }
		* { if (YYCURSOR == limit) return Latin_Extended_A; else return Error; }
	*/

Latin_Extended_B:
	/*!re2c
		re2c:yyfill:enable = 0;
		Latin_Extended_B { goto Latin_Extended_B; }
		* { if (YYCURSOR == limit) return Latin_Extended_B; else return Error; }
	*/

IPA_Extensions:
	/*!re2c
		re2c:yyfill:enable = 0;
		IPA_Extensions { goto IPA_Extensions; }
		* { if (YYCURSOR == limit) return IPA_Extensions; else return Error; }
	*/

Spacing_Modifier_Letters:
	/*!re2c
		re2c:yyfill:enable = 0;
		Spacing_Modifier_Letters { goto Spacing_Modifier_Letters; }
		* { if (YYCURSOR == limit) return Spacing_Modifier_Letters; else return Error; }
	*/

Combining_Diacritical_Marks:
	/*!re2c
		re2c:yyfill:enable = 0;
		Combining_Diacritical_Marks { goto Combining_Diacritical_Marks; }
		* { if (YYCURSOR == limit) return Combining_Diacritical_Marks; else return Error; }
	*/

Greek_and_Coptic:
	/*!re2c
		re2c:yyfill:enable = 0;
		Greek_and_Coptic { goto Greek_and_Coptic; }
		* { if (YYCURSOR == limit) return Greek_and_Coptic; else return Error; }
	*/

Cyrillic:
	/*!re2c
		re2c:yyfill:enable = 0;
		Cyrillic { goto Cyrillic; }
		* { if (YYCURSOR == limit) return Cyrillic; else return Error; }
	*/

Cyrillic_Supplementary:
	/*!re2c
		re2c:yyfill:enable = 0;
		Cyrillic_Supplementary { goto Cyrillic_Supplementary; }
		* { if (YYCURSOR == limit) return Cyrillic_Supplementary; else return Error; }
	*/

Armenian:
	/*!re2c
		re2c:yyfill:enable = 0;
		Armenian { goto Armenian; }
		* { if (YYCURSOR == limit) return Armenian; else return Error; }
	*/

Hebrew:
	/*!re2c
		re2c:yyfill:enable = 0;
		Hebrew { goto Hebrew; }
		* { if (YYCURSOR == limit) return Hebrew; else return Error; }
	*/

Arabic:
	/*!re2c
		re2c:yyfill:enable = 0;
		Arabic { goto Arabic; }
		* { if (YYCURSOR == limit) return Arabic; else return Error; }
	*/

Syriac:
	/*!re2c
		re2c:yyfill:enable = 0;
		Syriac { goto Syriac; }
		* { if (YYCURSOR == limit) return Syriac; else return Error; }
	*/

Thaana:
	/*!re2c
		re2c:yyfill:enable = 0;
		Thaana { goto Thaana; }
		* { if (YYCURSOR == limit) return Thaana; else return Error; }
	*/

Devanagari:
	/*!re2c
		re2c:yyfill:enable = 0;
		Devanagari { goto Devanagari; }
		* { if (YYCURSOR == limit) return Devanagari; else return Error; }
	*/

Bengali:
	/*!re2c
		re2c:yyfill:enable = 0;
		Bengali { goto Bengali; }
		* { if (YYCURSOR == limit) return Bengali; else return Error; }
	*/

Gurmukhi:
	/*!re2c
		re2c:yyfill:enable = 0;
		Gurmukhi { goto Gurmukhi; }
		* { if (YYCURSOR == limit) return Gurmukhi; else return Error; }
	*/

Gujarati:
	/*!re2c
		re2c:yyfill:enable = 0;
		Gujarati { goto Gujarati; }
		* { if (YYCURSOR == limit) return Gujarati; else return Error; }
	*/

Oriya:
	/*!re2c
		re2c:yyfill:enable = 0;
		Oriya { goto Oriya; }
		* { if (YYCURSOR == limit) return Oriya; else return Error; }
	*/

Tamil:
	/*!re2c
		re2c:yyfill:enable = 0;
		Tamil { goto Tamil; }
		* { if (YYCURSOR == limit) return Tamil; else return Error; }
	*/

Telugu:
	/*!re2c
		re2c:yyfill:enable = 0;
		Telugu { goto Telugu; }
		* { if (YYCURSOR == limit) return Telugu; else return Error; }
	*/

Kannada:
	/*!re2c
		re2c:yyfill:enable = 0;
		Kannada { goto Kannada; }
		* { if (YYCURSOR == limit) return Kannada; else return Error; }
	*/

Malayalam:
	/*!re2c
		re2c:yyfill:enable = 0;
		Malayalam { goto Malayalam; }
		* { if (YYCURSOR == limit) return Malayalam; else return Error; }
	*/

Sinhala:
	/*!re2c
		re2c:yyfill:enable = 0;
		Sinhala { goto Sinhala; }
		* { if (YYCURSOR == limit) return Sinhala; else return Error; }
	*/

Thai:
	/*!re2c
		re2c:yyfill:enable = 0;
		Thai { goto Thai; }
		* { if (YYCURSOR == limit) return Thai; else return Error; }
	*/

Lao:
	/*!re2c
		re2c:yyfill:enable = 0;
		Lao { goto Lao; }
		* { if (YYCURSOR == limit) return Lao; else return Error; }
	*/

Tibetan:
	/*!re2c
		re2c:yyfill:enable = 0;
		Tibetan { goto Tibetan; }
		* { if (YYCURSOR == limit) return Tibetan; else return Error; }
	*/

Myanmar:
	/*!re2c
		re2c:yyfill:enable = 0;
		Myanmar { goto Myanmar; }
		* { if (YYCURSOR == limit) return Myanmar; else return Error; }
	*/

Georgian:
	/*!re2c
		re2c:yyfill:enable = 0;
		Georgian { goto Georgian; }
		* { if (YYCURSOR == limit) return Georgian; else return Error; }
	*/

Hangul_Jamo:
	/*!re2c
		re2c:yyfill:enable = 0;
		Hangul_Jamo { goto Hangul_Jamo; }
		* { if (YYCURSOR == limit) return Hangul_Jamo; else return Error; }
	*/

Ethiopic:
	/*!re2c
		re2c:yyfill:enable = 0;
		Ethiopic { goto Ethiopic; }
		* { if (YYCURSOR == limit) return Ethiopic; else return Error; }
	*/

Cherokee:
	/*!re2c
		re2c:yyfill:enable = 0;
		Cherokee { goto Cherokee; }
		* { if (YYCURSOR == limit) return Cherokee; else return Error; }
	*/

Unified_Canadian_Aboriginal_Syllabics:
	/*!re2c
		re2c:yyfill:enable = 0;
		Unified_Canadian_Aboriginal_Syllabics { goto Unified_Canadian_Aboriginal_Syllabics; }
		* { if (YYCURSOR == limit) return Unified_Canadian_Aboriginal_Syllabics; else return Error; }
	*/

Ogham:
	/*!re2c
		re2c:yyfill:enable = 0;
		Ogham { goto Ogham; }
		* { if (YYCURSOR == limit) return Ogham; else return Error; }
	*/

Runic:
	/*!re2c
		re2c:yyfill:enable = 0;
		Runic { goto Runic; }
		* { if (YYCURSOR == limit) return Runic; else return Error; }
	*/

Tagalog:
	/*!re2c
		re2c:yyfill:enable = 0;
		Tagalog { goto Tagalog; }
		* { if (YYCURSOR == limit) return Tagalog; else return Error; }
	*/

Hanunoo:
	/*!re2c
		re2c:yyfill:enable = 0;
		Hanunoo { goto Hanunoo; }
		* { if (YYCURSOR == limit) return Hanunoo; else return Error; }
	*/

Buhid:
	/*!re2c
		re2c:yyfill:enable = 0;
		Buhid { goto Buhid; }
		* { if (YYCURSOR == limit) return Buhid; else return Error; }
	*/

Tagbanwa:
	/*!re2c
		re2c:yyfill:enable = 0;
		Tagbanwa { goto Tagbanwa; }
		* { if (YYCURSOR == limit) return Tagbanwa; else return Error; }
	*/

Khmer:
	/*!re2c
		re2c:yyfill:enable = 0;
		Khmer { goto Khmer; }
		* { if (YYCURSOR == limit) return Khmer; else return Error; }
	*/

Mongolian:
	/*!re2c
		re2c:yyfill:enable = 0;
		Mongolian { goto Mongolian; }
		* { if (YYCURSOR == limit) return Mongolian; else return Error; }
	*/

Limbu:
	/*!re2c
		re2c:yyfill:enable = 0;
		Limbu { goto Limbu; }
		* { if (YYCURSOR == limit) return Limbu; else return Error; }
	*/

Tai_Le:
	/*!re2c
		re2c:yyfill:enable = 0;
		Tai_Le { goto Tai_Le; }
		* { if (YYCURSOR == limit) return Tai_Le; else return Error; }
	*/

Khmer_Symbols:
	/*!re2c
		re2c:yyfill:enable = 0;
		Khmer_Symbols { goto Khmer_Symbols; }
		* { if (YYCURSOR == limit) return Khmer_Symbols; else return Error; }
	*/

Phonetic_Extensions:
	/*!re2c
		re2c:yyfill:enable = 0;
		Phonetic_Extensions { goto Phonetic_Extensions; }
		* { if (YYCURSOR == limit) return Phonetic_Extensions; else return Error; }
	*/

Latin_Extended_Additional:
	/*!re2c
		re2c:yyfill:enable = 0;
		Latin_Extended_Additional { goto Latin_Extended_Additional; }
		* { if (YYCURSOR == limit) return Latin_Extended_Additional; else return Error; }
	*/

Greek_Extended:
	/*!re2c
		re2c:yyfill:enable = 0;
		Greek_Extended { goto Greek_Extended; }
		* { if (YYCURSOR == limit) return Greek_Extended; else return Error; }
	*/

General_Punctuation:
	/*!re2c
		re2c:yyfill:enable = 0;
		General_Punctuation { goto General_Punctuation; }
		* { if (YYCURSOR == limit) return General_Punctuation; else return Error; }
	*/

Superscripts_and_Subscripts:
	/*!re2c
		re2c:yyfill:enable = 0;
		Superscripts_and_Subscripts { goto Superscripts_and_Subscripts; }
		* { if (YYCURSOR == limit) return Superscripts_and_Subscripts; else return Error; }
	*/

Currency_Symbols:
	/*!re2c
		re2c:yyfill:enable = 0;
		Currency_Symbols { goto Currency_Symbols; }
		* { if (YYCURSOR == limit) return Currency_Symbols; else return Error; }
	*/

Combining_Diacritical_Marks_for_Symbols:
	/*!re2c
		re2c:yyfill:enable = 0;
		Combining_Diacritical_Marks_for_Symbols { goto Combining_Diacritical_Marks_for_Symbols; }
		* { if (YYCURSOR == limit) return Combining_Diacritical_Marks_for_Symbols; else return Error; }
	*/

Letterlike_Symbols:
	/*!re2c
		re2c:yyfill:enable = 0;
		Letterlike_Symbols { goto Letterlike_Symbols; }
		* { if (YYCURSOR == limit) return Letterlike_Symbols; else return Error; }
	*/

Number_Forms:
	/*!re2c
		re2c:yyfill:enable = 0;
		Number_Forms { goto Number_Forms; }
		* { if (YYCURSOR == limit) return Number_Forms; else return Error; }
	*/

Arrows:
	/*!re2c
		re2c:yyfill:enable = 0;
		Arrows { goto Arrows; }
		* { if (YYCURSOR == limit) return Arrows; else return Error; }
	*/

Mathematical_Operators:
	/*!re2c
		re2c:yyfill:enable = 0;
		Mathematical_Operators { goto Mathematical_Operators; }
		* { if (YYCURSOR == limit) return Mathematical_Operators; else return Error; }
	*/

Miscellaneous_Technical:
	/*!re2c
		re2c:yyfill:enable = 0;
		Miscellaneous_Technical { goto Miscellaneous_Technical; }
		* { if (YYCURSOR == limit) return Miscellaneous_Technical; else return Error; }
	*/

Control_Pictures:
	/*!re2c
		re2c:yyfill:enable = 0;
		Control_Pictures { goto Control_Pictures; }
		* { if (YYCURSOR == limit) return Control_Pictures; else return Error; }
	*/

Optical_Character_Recognition:
	/*!re2c
		re2c:yyfill:enable = 0;
		Optical_Character_Recognition { goto Optical_Character_Recognition; }
		* { if (YYCURSOR == limit) return Optical_Character_Recognition; else return Error; }
	*/

Enclosed_Alphanumerics:
	/*!re2c
		re2c:yyfill:enable = 0;
		Enclosed_Alphanumerics { goto Enclosed_Alphanumerics; }
		* { if (YYCURSOR == limit) return Enclosed_Alphanumerics; else return Error; }
	*/

Box_Drawing:
	/*!re2c
		re2c:yyfill:enable = 0;
		Box_Drawing { goto Box_Drawing; }
		* { if (YYCURSOR == limit) return Box_Drawing; else return Error; }
	*/

Block_Elements:
	/*!re2c
		re2c:yyfill:enable = 0;
		Block_Elements { goto Block_Elements; }
		* { if (YYCURSOR == limit) return Block_Elements; else return Error; }
	*/

Geometric_Shapes:
	/*!re2c
		re2c:yyfill:enable = 0;
		Geometric_Shapes { goto Geometric_Shapes; }
		* { if (YYCURSOR == limit) return Geometric_Shapes; else return Error; }
	*/

Miscellaneous_Symbols:
	/*!re2c
		re2c:yyfill:enable = 0;
		Miscellaneous_Symbols { goto Miscellaneous_Symbols; }
		* { if (YYCURSOR == limit) return Miscellaneous_Symbols; else return Error; }
	*/

Dingbats:
	/*!re2c
		re2c:yyfill:enable = 0;
		Dingbats { goto Dingbats; }
		* { if (YYCURSOR == limit) return Dingbats; else return Error; }
	*/

Miscellaneous_Mathematical_Symbols_A:
	/*!re2c
		re2c:yyfill:enable = 0;
		Miscellaneous_Mathematical_Symbols_A { goto Miscellaneous_Mathematical_Symbols_A; }
		* { if (YYCURSOR == limit) return Miscellaneous_Mathematical_Symbols_A; else return Error; }
	*/

Supplemental_Arrows_A:
	/*!re2c
		re2c:yyfill:enable = 0;
		Supplemental_Arrows_A { goto Supplemental_Arrows_A; }
		* { if (YYCURSOR == limit) return Supplemental_Arrows_A; else return Error; }
	*/

Braille_Patterns:
	/*!re2c
		re2c:yyfill:enable = 0;
		Braille_Patterns { goto Braille_Patterns; }
		* { if (YYCURSOR == limit) return Braille_Patterns; else return Error; }
	*/

Supplemental_Arrows_B:
	/*!re2c
		re2c:yyfill:enable = 0;
		Supplemental_Arrows_B { goto Supplemental_Arrows_B; }
		* { if (YYCURSOR == limit) return Supplemental_Arrows_B; else return Error; }
	*/

Miscellaneous_Mathematical_Symbols_B:
	/*!re2c
		re2c:yyfill:enable = 0;
		Miscellaneous_Mathematical_Symbols_B { goto Miscellaneous_Mathematical_Symbols_B; }
		* { if (YYCURSOR == limit) return Miscellaneous_Mathematical_Symbols_B; else return Error; }
	*/

Supplemental_Mathematical_Operators:
	/*!re2c
		re2c:yyfill:enable = 0;
		Supplemental_Mathematical_Operators { goto Supplemental_Mathematical_Operators; }
		* { if (YYCURSOR == limit) return Supplemental_Mathematical_Operators; else return Error; }
	*/

Miscellaneous_Symbols_and_Arrows:
	/*!re2c
		re2c:yyfill:enable = 0;
		Miscellaneous_Symbols_and_Arrows { goto Miscellaneous_Symbols_and_Arrows; }
		* { if (YYCURSOR == limit) return Miscellaneous_Symbols_and_Arrows; else return Error; }
	*/

CJK_Radicals_Supplement:
	/*!re2c
		re2c:yyfill:enable = 0;
		CJK_Radicals_Supplement { goto CJK_Radicals_Supplement; }
		* { if (YYCURSOR == limit) return CJK_Radicals_Supplement; else return Error; }
	*/

Kangxi_Radicals:
	/*!re2c
		re2c:yyfill:enable = 0;
		Kangxi_Radicals { goto Kangxi_Radicals; }
		* { if (YYCURSOR == limit) return Kangxi_Radicals; else return Error; }
	*/

Ideographic_Description_Characters:
	/*!re2c
		re2c:yyfill:enable = 0;
		Ideographic_Description_Characters { goto Ideographic_Description_Characters; }
		* { if (YYCURSOR == limit) return Ideographic_Description_Characters; else return Error; }
	*/

CJK_Symbols_and_Punctuation:
	/*!re2c
		re2c:yyfill:enable = 0;
		CJK_Symbols_and_Punctuation { goto CJK_Symbols_and_Punctuation; }
		* { if (YYCURSOR == limit) return CJK_Symbols_and_Punctuation; else return Error; }
	*/

Hiragana:
	/*!re2c
		re2c:yyfill:enable = 0;
		Hiragana { goto Hiragana; }
		* { if (YYCURSOR == limit) return Hiragana; else return Error; }
	*/

Katakana:
	/*!re2c
		re2c:yyfill:enable = 0;
		Katakana { goto Katakana; }
		* { if (YYCURSOR == limit) return Katakana; else return Error; }
	*/

Bopomofo:
	/*!re2c
		re2c:yyfill:enable = 0;
		Bopomofo { goto Bopomofo; }
		* { if (YYCURSOR == limit) return Bopomofo; else return Error; }
	*/

Hangul_Compatibility_Jamo:
	/*!re2c
		re2c:yyfill:enable = 0;
		Hangul_Compatibility_Jamo { goto Hangul_Compatibility_Jamo; }
		* { if (YYCURSOR == limit) return Hangul_Compatibility_Jamo; else return Error; }
	*/

Kanbun:
	/*!re2c
		re2c:yyfill:enable = 0;
		Kanbun { goto Kanbun; }
		* { if (YYCURSOR == limit) return Kanbun; else return Error; }
	*/

Bopomofo_Extended:
	/*!re2c
		re2c:yyfill:enable = 0;
		Bopomofo_Extended { goto Bopomofo_Extended; }
		* { if (YYCURSOR == limit) return Bopomofo_Extended; else return Error; }
	*/

Katakana_Phonetic_Extensions:
	/*!re2c
		re2c:yyfill:enable = 0;
		Katakana_Phonetic_Extensions { goto Katakana_Phonetic_Extensions; }
		* { if (YYCURSOR == limit) return Katakana_Phonetic_Extensions; else return Error; }
	*/

Enclosed_CJK_Letters_and_Months:
	/*!re2c
		re2c:yyfill:enable = 0;
		Enclosed_CJK_Letters_and_Months { goto Enclosed_CJK_Letters_and_Months; }
		* { if (YYCURSOR == limit) return Enclosed_CJK_Letters_and_Months; else return Error; }
	*/

CJK_Compatibility:
	/*!re2c
		re2c:yyfill:enable = 0;
		CJK_Compatibility { goto CJK_Compatibility; }
		* { if (YYCURSOR == limit) return CJK_Compatibility; else return Error; }
	*/

CJK_Unified_Ideographs_Extension_A:
	/*!re2c
		re2c:yyfill:enable = 0;
		CJK_Unified_Ideographs_Extension_A { goto CJK_Unified_Ideographs_Extension_A; }
		* { if (YYCURSOR == limit) return CJK_Unified_Ideographs_Extension_A; else return Error; }
	*/

Yijing_Hexagram_Symbols:
	/*!re2c
		re2c:yyfill:enable = 0;
		Yijing_Hexagram_Symbols { goto Yijing_Hexagram_Symbols; }
		* { if (YYCURSOR == limit) return Yijing_Hexagram_Symbols; else return Error; }
	*/

CJK_Unified_Ideographs:
	/*!re2c
		re2c:yyfill:enable = 0;
		CJK_Unified_Ideographs { goto CJK_Unified_Ideographs; }
		* { if (YYCURSOR == limit) return CJK_Unified_Ideographs; else return Error; }
	*/

Yi_Syllables:
	/*!re2c
		re2c:yyfill:enable = 0;
		Yi_Syllables { goto Yi_Syllables; }
		* { if (YYCURSOR == limit) return Yi_Syllables; else return Error; }
	*/

Yi_Radicals:
	/*!re2c
		re2c:yyfill:enable = 0;
		Yi_Radicals { goto Yi_Radicals; }
		* { if (YYCURSOR == limit) return Yi_Radicals; else return Error; }
	*/

Hangul_Syllables:
	/*!re2c
		re2c:yyfill:enable = 0;
		Hangul_Syllables { goto Hangul_Syllables; }
		* { if (YYCURSOR == limit) return Hangul_Syllables; else return Error; }
	*/

High_Surrogates:
	/*!re2c
		re2c:yyfill:enable = 0;
		High_Surrogates { goto High_Surrogates; }
		* { if (YYCURSOR == limit) return High_Surrogates; else return Error; }
	*/

High_Private_Use_Surrogates:
	/*!re2c
		re2c:yyfill:enable = 0;
		High_Private_Use_Surrogates { goto High_Private_Use_Surrogates; }
		* { if (YYCURSOR == limit) return High_Private_Use_Surrogates; else return Error; }
	*/

Low_Surrogates:
	/*!re2c
		re2c:yyfill:enable = 0;
		Low_Surrogates { goto Low_Surrogates; }
		* { if (YYCURSOR == limit) return Low_Surrogates; else return Error; }
	*/

Private_Use_Area:
	/*!re2c
		re2c:yyfill:enable = 0;
		Private_Use_Area { goto Private_Use_Area; }
		* { if (YYCURSOR == limit) return Private_Use_Area; else return Error; }
	*/

CJK_Compatibility_Ideographs:
	/*!re2c
		re2c:yyfill:enable = 0;
		CJK_Compatibility_Ideographs { goto CJK_Compatibility_Ideographs; }
		* { if (YYCURSOR == limit) return CJK_Compatibility_Ideographs; else return Error; }
	*/

Alphabetic_Presentation_Forms:
	/*!re2c
		re2c:yyfill:enable = 0;
		Alphabetic_Presentation_Forms { goto Alphabetic_Presentation_Forms; }
		* { if (YYCURSOR == limit) return Alphabetic_Presentation_Forms; else return Error; }
	*/

Arabic_Presentation_Forms_A:
	/*!re2c
		re2c:yyfill:enable = 0;
		Arabic_Presentation_Forms_A { goto Arabic_Presentation_Forms_A; }
		* { if (YYCURSOR == limit) return Arabic_Presentation_Forms_A; else return Error; }
	*/

Variation_Selectors:
	/*!re2c
		re2c:yyfill:enable = 0;
		Variation_Selectors { goto Variation_Selectors; }
		* { if (YYCURSOR == limit) return Variation_Selectors; else return Error; }
	*/

Combining_Half_Marks:
	/*!re2c
		re2c:yyfill:enable = 0;
		Combining_Half_Marks { goto Combining_Half_Marks; }
		* { if (YYCURSOR == limit) return Combining_Half_Marks; else return Error; }
	*/

CJK_Compatibility_Forms:
	/*!re2c
		re2c:yyfill:enable = 0;
		CJK_Compatibility_Forms { goto CJK_Compatibility_Forms; }
		* { if (YYCURSOR == limit) return CJK_Compatibility_Forms; else return Error; }
	*/

Small_Form_Variants:
	/*!re2c
		re2c:yyfill:enable = 0;
		Small_Form_Variants { goto Small_Form_Variants; }
		* { if (YYCURSOR == limit) return Small_Form_Variants; else return Error; }
	*/

Arabic_Presentation_Forms_B:
	/*!re2c
		re2c:yyfill:enable = 0;
		Arabic_Presentation_Forms_B { goto Arabic_Presentation_Forms_B; }
		* { if (YYCURSOR == limit) return Arabic_Presentation_Forms_B; else return Error; }
	*/

Halfwidth_and_Fullwidth_Forms:
	/*!re2c
		re2c:yyfill:enable = 0;
		Halfwidth_and_Fullwidth_Forms { goto Halfwidth_and_Fullwidth_Forms; }
		* { if (YYCURSOR == limit) return Halfwidth_and_Fullwidth_Forms; else return Error; }
	*/

Specials:
	/*!re2c
		re2c:yyfill:enable = 0;
		Specials { goto Specials; }
		* { if (YYCURSOR == limit) return Specials; else return Error; }
	*/

All:
	/*!re2c
		re2c:yyfill:enable = 0;
		All { goto All; }
		* { if (YYCURSOR == limit) return All; else return Error; }
	*/


}
static const unsigned int chars_Basic_Latin [] = {0x0,0x7f,  0x80,0x80};
static const unsigned int chars_Latin___Supplement [] = {0x80,0xff,  0x0,0x0};
static const unsigned int chars_Latin_Extended_A [] = {0x100,0x17f,  0x0,0x0};
static const unsigned int chars_Latin_Extended_B [] = {0x180,0x24f,  0x0,0x0};
static const unsigned int chars_IPA_Extensions [] = {0x250,0x2af,  0x0,0x0};
static const unsigned int chars_Spacing_Modifier_Letters [] = {0x2b0,0x2ff,  0x0,0x0};
static const unsigned int chars_Combining_Diacritical_Marks [] = {0x300,0x36f,  0x0,0x0};
static const unsigned int chars_Greek_and_Coptic [] = {0x370,0x3ff,  0x0,0x0};
static const unsigned int chars_Cyrillic [] = {0x400,0x4ff,  0x0,0x0};
static const unsigned int chars_Cyrillic_Supplementary [] = {0x500,0x52f,  0x0,0x0};
static const unsigned int chars_Armenian [] = {0x530,0x58f,  0x0,0x0};
static const unsigned int chars_Hebrew [] = {0x590,0x5ff,  0x0,0x0};
static const unsigned int chars_Arabic [] = {0x600,0x6ff,  0x0,0x0};
static const unsigned int chars_Syriac [] = {0x700,0x74f,  0x0,0x0};
static const unsigned int chars_Thaana [] = {0x780,0x7bf,  0x0,0x0};
static const unsigned int chars_Devanagari [] = {0x900,0x97f,  0x0,0x0};
static const unsigned int chars_Bengali [] = {0x980,0x9ff,  0x0,0x0};
static const unsigned int chars_Gurmukhi [] = {0xa00,0xa7f,  0x0,0x0};
static const unsigned int chars_Gujarati [] = {0xa80,0xaff,  0x0,0x0};
static const unsigned int chars_Oriya [] = {0xb00,0xb7f,  0x0,0x0};
static const unsigned int chars_Tamil [] = {0xb80,0xbff,  0x0,0x0};
static const unsigned int chars_Telugu [] = {0xc00,0xc7f,  0x0,0x0};
static const unsigned int chars_Kannada [] = {0xc80,0xcff,  0x0,0x0};
static const unsigned int chars_Malayalam [] = {0xd00,0xd7f,  0x0,0x0};
static const unsigned int chars_Sinhala [] = {0xd80,0xdff,  0x0,0x0};
static const unsigned int chars_Thai [] = {0xe00,0xe7f,  0x0,0x0};
static const unsigned int chars_Lao [] = {0xe80,0xeff,  0x0,0x0};
static const unsigned int chars_Tibetan [] = {0xf00,0xfff,  0x0,0x0};
static const unsigned int chars_Myanmar [] = {0x1000,0x109f,  0x0,0x0};
static const unsigned int chars_Georgian [] = {0x10a0,0x10ff,  0x0,0x0};
static const unsigned int chars_Hangul_Jamo [] = {0x1100,0x11ff,  0x0,0x0};
static const unsigned int chars_Ethiopic [] = {0x1200,0x137f,  0x0,0x0};
static const unsigned int chars_Cherokee [] = {0x13a0,0x13ff,  0x0,0x0};
static const unsigned int chars_Unified_Canadian_Aboriginal_Syllabics [] = {0x1400,0x167f,  0x0,0x0};
static const unsigned int chars_Ogham [] = {0x1680,0x169f,  0x0,0x0};
static const unsigned int chars_Runic [] = {0x16a0,0x16ff,  0x0,0x0};
static const unsigned int chars_Tagalog [] = {0x1700,0x171f,  0x0,0x0};
static const unsigned int chars_Hanunoo [] = {0x1720,0x173f,  0x0,0x0};
static const unsigned int chars_Buhid [] = {0x1740,0x175f,  0x0,0x0};
static const unsigned int chars_Tagbanwa [] = {0x1760,0x177f,  0x0,0x0};
static const unsigned int chars_Khmer [] = {0x1780,0x17ff,  0x0,0x0};
static const unsigned int chars_Mongolian [] = {0x1800,0x18af,  0x0,0x0};
static const unsigned int chars_Limbu [] = {0x1900,0x194f,  0x0,0x0};
static const unsigned int chars_Tai_Le [] = {0x1950,0x197f,  0x0,0x0};
static const unsigned int chars_Khmer_Symbols [] = {0x19e0,0x19ff,  0x0,0x0};
static const unsigned int chars_Phonetic_Extensions [] = {0x1d00,0x1d7f,  0x0,0x0};
static const unsigned int chars_Latin_Extended_Additional [] = {0x1e00,0x1eff,  0x0,0x0};
static const unsigned int chars_Greek_Extended [] = {0x1f00,0x1fff,  0x0,0x0};
static const unsigned int chars_General_Punctuation [] = {0x2000,0x206f,  0x0,0x0};
static const unsigned int chars_Superscripts_and_Subscripts [] = {0x2070,0x209f,  0x0,0x0};
static const unsigned int chars_Currency_Symbols [] = {0x20a0,0x20cf,  0x0,0x0};
static const unsigned int chars_Combining_Diacritical_Marks_for_Symbols [] = {0x20d0,0x20ff,  0x0,0x0};
static const unsigned int chars_Letterlike_Symbols [] = {0x2100,0x214f,  0x0,0x0};
static const unsigned int chars_Number_Forms [] = {0x2150,0x218f,  0x0,0x0};
static const unsigned int chars_Arrows [] = {0x2190,0x21ff,  0x0,0x0};
static const unsigned int chars_Mathematical_Operators [] = {0x2200,0x22ff,  0x0,0x0};
static const unsigned int chars_Miscellaneous_Technical [] = {0x2300,0x23ff,  0x0,0x0};
static const unsigned int chars_Control_Pictures [] = {0x2400,0x243f,  0x0,0x0};
static const unsigned int chars_Optical_Character_Recognition [] = {0x2440,0x245f,  0x0,0x0};
static const unsigned int chars_Enclosed_Alphanumerics [] = {0x2460,0x24ff,  0x0,0x0};
static const unsigned int chars_Box_Drawing [] = {0x2500,0x257f,  0x0,0x0};
static const unsigned int chars_Block_Elements [] = {0x2580,0x259f,  0x0,0x0};
static const unsigned int chars_Geometric_Shapes [] = {0x25a0,0x25ff,  0x0,0x0};
static const unsigned int chars_Miscellaneous_Symbols [] = {0x2600,0x26ff,  0x0,0x0};
static const unsigned int chars_Dingbats [] = {0x2700,0x27bf,  0x0,0x0};
static const unsigned int chars_Miscellaneous_Mathematical_Symbols_A [] = {0x27c0,0x27ef,  0x0,0x0};
static const unsigned int chars_Supplemental_Arrows_A [] = {0x27f0,0x27ff,  0x0,0x0};
static const unsigned int chars_Braille_Patterns [] = {0x2800,0x28ff,  0x0,0x0};
static const unsigned int chars_Supplemental_Arrows_B [] = {0x2900,0x297f,  0x0,0x0};
static const unsigned int chars_Miscellaneous_Mathematical_Symbols_B [] = {0x2980,0x29ff,  0x0,0x0};
static const unsigned int chars_Supplemental_Mathematical_Operators [] = {0x2a00,0x2aff,  0x0,0x0};
static const unsigned int chars_Miscellaneous_Symbols_and_Arrows [] = {0x2b00,0x2bff,  0x0,0x0};
static const unsigned int chars_CJK_Radicals_Supplement [] = {0x2e80,0x2eff,  0x0,0x0};
static const unsigned int chars_Kangxi_Radicals [] = {0x2f00,0x2fdf,  0x0,0x0};
static const unsigned int chars_Ideographic_Description_Characters [] = {0x2ff0,0x2fff,  0x0,0x0};
static const unsigned int chars_CJK_Symbols_and_Punctuation [] = {0x3000,0x303f,  0x0,0x0};
static const unsigned int chars_Hiragana [] = {0x3040,0x309f,  0x0,0x0};
static const unsigned int chars_Katakana [] = {0x30a0,0x30ff,  0x0,0x0};
static const unsigned int chars_Bopomofo [] = {0x3100,0x312f,  0x0,0x0};
static const unsigned int chars_Hangul_Compatibility_Jamo [] = {0x3130,0x318f,  0x0,0x0};
static const unsigned int chars_Kanbun [] = {0x3190,0x319f,  0x0,0x0};
static const unsigned int chars_Bopomofo_Extended [] = {0x31a0,0x31bf,  0x0,0x0};
static const unsigned int chars_Katakana_Phonetic_Extensions [] = {0x31f0,0x31ff,  0x0,0x0};
static const unsigned int chars_Enclosed_CJK_Letters_and_Months [] = {0x3200,0x32ff,  0x0,0x0};
static const unsigned int chars_CJK_Compatibility [] = {0x3300,0x33ff,  0x0,0x0};
static const unsigned int chars_CJK_Unified_Ideographs_Extension_A [] = {0x3400,0x4dbf,  0x0,0x0};
static const unsigned int chars_Yijing_Hexagram_Symbols [] = {0x4dc0,0x4dff,  0x0,0x0};
static const unsigned int chars_CJK_Unified_Ideographs [] = {0x4e00,0x9fff,  0x0,0x0};
static const unsigned int chars_Yi_Syllables [] = {0xa000,0xa48f,  0x0,0x0};
static const unsigned int chars_Yi_Radicals [] = {0xa490,0xa4cf,  0x0,0x0};
static const unsigned int chars_Hangul_Syllables [] = {0xac00,0xd7af,  0x0,0x0};
static const unsigned int chars_High_Surrogates [] = {0xd800,0xdb7f,  0x0,0x0};
static const unsigned int chars_High_Private_Use_Surrogates [] = {0xdb80,0xdbff,  0x0,0x0};
static const unsigned int chars_Low_Surrogates [] = {0xdc00,0xdfff,  0x0,0x0};
static const unsigned int chars_Private_Use_Area [] = {0xe000,0xf8ff,  0x0,0x0};
static const unsigned int chars_CJK_Compatibility_Ideographs [] = {0xf900,0xfaff,  0x0,0x0};
static const unsigned int chars_Alphabetic_Presentation_Forms [] = {0xfb00,0xfb4f,  0x0,0x0};
static const unsigned int chars_Arabic_Presentation_Forms_A [] = {0xfb50,0xfdff,  0x0,0x0};
static const unsigned int chars_Variation_Selectors [] = {0xfe00,0xfe0f,  0x0,0x0};
static const unsigned int chars_Combining_Half_Marks [] = {0xfe20,0xfe2f,  0x0,0x0};
static const unsigned int chars_CJK_Compatibility_Forms [] = {0xfe30,0xfe4f,  0x0,0x0};
static const unsigned int chars_Small_Form_Variants [] = {0xfe50,0xfe6f,  0x0,0x0};
static const unsigned int chars_Arabic_Presentation_Forms_B [] = {0xfe70,0xfeff,  0x0,0x0};
static const unsigned int chars_Halfwidth_and_Fullwidth_Forms [] = {0xff00,0xffef,  0x0,0x0};
static const unsigned int chars_Specials [] = {0xfff0,0xffff,  0x0,0x0};
static const unsigned int chars_All [] = {0x0,0x74f,  0x780,0x7bf,  0x900,0x137f,  0x13a0,0x18af,  0x1900,0x197f,  0x19e0,0x19ff,  0x1d00,0x1d7f,  0x1e00,0x2bff,  0x2e80,0x2fdf,  0x2ff0,0x31bf,  0x31f0,0xa4cf,  0xac00,0xd7af,  0xd800,0xfe0f,  0xfe20,0xffff,  0x750,0x750};

static unsigned int encode_utf32 (const unsigned int * ranges, unsigned int ranges_count, unsigned int * s)
{
	unsigned int * const s_start = s;
	for (unsigned int i = 0; i < ranges_count; i += 2)
		for (unsigned int j = ranges[i]; j <= ranges[i + 1]; ++j)
			*s++ = j;
	return s - s_start;
}

int main()
{
	YYCTYPE * buffer_Basic_Latin = new YYCTYPE [129];
	unsigned int buffer_Basic_Latin_len = encode_utf32 (chars_Basic_Latin, sizeof (chars_Basic_Latin) / sizeof (unsigned int), buffer_Basic_Latin);
	if (scan (reinterpret_cast<const YYCTYPE *> (buffer_Basic_Latin), reinterpret_cast<const YYCTYPE *> (buffer_Basic_Latin + buffer_Basic_Latin_len), Basic_Latin) != Basic_Latin)
		printf ("test 'Basic_Latin' failed\n");
	delete [] buffer_Basic_Latin;

	YYCTYPE * buffer_Latin___Supplement = new YYCTYPE [129];
	unsigned int buffer_Latin___Supplement_len = encode_utf32 (chars_Latin___Supplement, sizeof (chars_Latin___Supplement) / sizeof (unsigned int), buffer_Latin___Supplement);
	if (scan (reinterpret_cast<const YYCTYPE *> (buffer_Latin___Supplement), reinterpret_cast<const YYCTYPE *> (buffer_Latin___Supplement + buffer_Latin___Supplement_len), Latin___Supplement) != Latin___Supplement)
		printf ("test 'Latin___Supplement' failed\n");
	delete [] buffer_Latin___Supplement;

	YYCTYPE * buffer_Latin_Extended_A = new YYCTYPE [129];
	unsigned int buffer_Latin_Extended_A_len = encode_utf32 (chars_Latin_Extended_A, sizeof (chars_Latin_Extended_A) / sizeof (unsigned int), buffer_Latin_Extended_A);
	if (scan (reinterpret_cast<const YYCTYPE *> (buffer_Latin_Extended_A), reinterpret_cast<const YYCTYPE *> (buffer_Latin_Extended_A + buffer_Latin_Extended_A_len), Latin_Extended_A) != Latin_Extended_A)
		printf ("test 'Latin_Extended_A' failed\n");
	delete [] buffer_Latin_Extended_A;

	YYCTYPE * buffer_Latin_Extended_B = new YYCTYPE [209];
	unsigned int buffer_Latin_Extended_B_len = encode_utf32 (chars_Latin_Extended_B, sizeof (chars_Latin_Extended_B) / sizeof (unsigned int), buffer_Latin_Extended_B);
	if (scan (reinterpret_cast<const YYCTYPE *> (buffer_Latin_Extended_B), reinterpret_cast<const YYCTYPE *> (buffer_Latin_Extended_B + buffer_Latin_Extended_B_len), Latin_Extended_B) != Latin_Extended_B)
		printf ("test 'Latin_Extended_B' failed\n");
	delete [] buffer_Latin_Extended_B;

	YYCTYPE * buffer_IPA_Extensions = new YYCTYPE [97];
	unsigned int buffer_IPA_Extensions_len = encode_utf32 (chars_IPA_Extensions, sizeof (chars_IPA_Extensions) / sizeof (unsigned int), buffer_IPA_Extensions);
	if (scan (reinterpret_cast<const YYCTYPE *> (buffer_IPA_Extensions), reinterpret_cast<const YYCTYPE *> (buffer_IPA_Extensions + buffer_IPA_Extensions_len), IPA_Extensions) != IPA_Extensions)
		printf ("test 'IPA_Extensions' failed\n");
	delete [] buffer_IPA_Extensions;

	YYCTYPE * buffer_Spacing_Modifier_Letters = new YYCTYPE [81];
	unsigned int buffer_Spacing_Modifier_Letters_len = encode_utf32 (chars_Spacing_Modifier_Letters, sizeof (chars_Spacing_Modifier_Letters) / sizeof (unsigned int), buffer_Spacing_Modifier_Letters);
	if (scan (reinterpret_cast<const YYCTYPE *> (buffer_Spacing_Modifier_Letters), reinterpret_cast<const YYCTYPE *> (buffer_Spacing_Modifier_Letters + buffer_Spacing_Modifier_Letters_len), Spacing_Modifier_Letters) != Spacing_Modifier_Letters)
		printf ("test 'Spacing_Modifier_Letters' failed\n");
	delete [] buffer_Spacing_Modifier_Letters;

	YYCTYPE * buffer_Combining_Diacritical_Marks = new YYCTYPE [113];
	unsigned int buffer_Combining_Diacritical_Marks_len = encode_utf32 (chars_Combining_Diacritical_Marks, sizeof (chars_Combining_Diacritical_Marks) / sizeof (unsigned int), buffer_Combining_Diacritical_Marks);
	if (scan (reinterpret_cast<const YYCTYPE *> (buffer_Combining_Diacritical_Marks), reinterpret_cast<const YYCTYPE *> (buffer_Combining_Diacritical_Marks + buffer_Combining_Diacritical_Marks_len), Combining_Diacritical_Marks) != Combining_Diacritical_Marks)
		printf ("test 'Combining_Diacritical_Marks' failed\n");
	delete [] buffer_Combining_Diacritical_Marks;

	YYCTYPE * buffer_Greek_and_Coptic = new YYCTYPE [145];
	unsigned int buffer_Greek_and_Coptic_len = encode_utf32 (chars_Greek_and_Coptic, sizeof (chars_Greek_and_Coptic) / sizeof (unsigned int), buffer_Greek_and_Coptic);
	if (scan (reinterpret_cast<const YYCTYPE *> (buffer_Greek_and_Coptic), reinterpret_cast<const YYCTYPE *> (buffer_Greek_and_Coptic + buffer_Greek_and_Coptic_len), Greek_and_Coptic) != Greek_and_Coptic)
		printf ("test 'Greek_and_Coptic' failed\n");
	delete [] buffer_Greek_and_Coptic;

	YYCTYPE * buffer_Cyrillic = new YYCTYPE [257];
	unsigned int buffer_Cyrillic_len = encode_utf32 (chars_Cyrillic, sizeof (chars_Cyrillic) / sizeof (unsigned int), buffer_Cyrillic);
	if (scan (reinterpret_cast<const YYCTYPE *> (buffer_Cyrillic), reinterpret_cast<const YYCTYPE *> (buffer_Cyrillic + buffer_Cyrillic_len), Cyrillic) != Cyrillic)
		printf ("test 'Cyrillic' failed\n");
	delete [] buffer_Cyrillic;

	YYCTYPE * buffer_Cyrillic_Supplementary = new YYCTYPE [49];
	unsigned int buffer_Cyrillic_Supplementary_len = encode_utf32 (chars_Cyrillic_Supplementary, sizeof (chars_Cyrillic_Supplementary) / sizeof (unsigned int), buffer_Cyrillic_Supplementary);
	if (scan (reinterpret_cast<const YYCTYPE *> (buffer_Cyrillic_Supplementary), reinterpret_cast<const YYCTYPE *> (buffer_Cyrillic_Supplementary + buffer_Cyrillic_Supplementary_len), Cyrillic_Supplementary) != Cyrillic_Supplementary)
		printf ("test 'Cyrillic_Supplementary' failed\n");
	delete [] buffer_Cyrillic_Supplementary;

	YYCTYPE * buffer_Armenian = new YYCTYPE [97];
	unsigned int buffer_Armenian_len = encode_utf32 (chars_Armenian, sizeof (chars_Armenian) / sizeof (unsigned int), buffer_Armenian);
	if (scan (reinterpret_cast<const YYCTYPE *> (buffer_Armenian), reinterpret_cast<const YYCTYPE *> (buffer_Armenian + buffer_Armenian_len), Armenian) != Armenian)
		printf ("test 'Armenian' failed\n");
	delete [] buffer_Armenian;

	YYCTYPE * buffer_Hebrew = new YYCTYPE [113];
	unsigned int buffer_Hebrew_len = encode_utf32 (chars_Hebrew, sizeof (chars_Hebrew) / sizeof (unsigned int), buffer_Hebrew);
	if (scan (reinterpret_cast<const YYCTYPE *> (buffer_Hebrew), reinterpret_cast<const YYCTYPE *> (buffer_Hebrew + buffer_Hebrew_len), Hebrew) != Hebrew)
		printf ("test 'Hebrew' failed\n");
	delete [] buffer_Hebrew;

	YYCTYPE * buffer_Arabic = new YYCTYPE [257];
	unsigned int buffer_Arabic_len = encode_utf32 (chars_Arabic, sizeof (chars_Arabic) / sizeof (unsigned int), buffer_Arabic);
	if (scan (reinterpret_cast<const YYCTYPE *> (buffer_Arabic), reinterpret_cast<const YYCTYPE *> (buffer_Arabic + buffer_Arabic_len), Arabic) != Arabic)
		printf ("test 'Arabic' failed\n");
	delete [] buffer_Arabic;

	YYCTYPE * buffer_Syriac = new YYCTYPE [81];
	unsigned int buffer_Syriac_len = encode_utf32 (chars_Syriac, sizeof (chars_Syriac) / sizeof (unsigned int), buffer_Syriac);
	if (scan (reinterpret_cast<const YYCTYPE *> (buffer_Syriac), reinterpret_cast<const YYCTYPE *> (buffer_Syriac + buffer_Syriac_len), Syriac) != Syriac)
		printf ("test 'Syriac' failed\n");
	delete [] buffer_Syriac;

	YYCTYPE * buffer_Thaana = new YYCTYPE [65];
	unsigned int buffer_Thaana_len = encode_utf32 (chars_Thaana, sizeof (chars_Thaana) / sizeof (unsigned int), buffer_Thaana);
	if (scan (reinterpret_cast<const YYCTYPE *> (buffer_Thaana), reinterpret_cast<const YYCTYPE *> (buffer_Thaana + buffer_Thaana_len), Thaana) != Thaana)
		printf ("test 'Thaana' failed\n");
	delete [] buffer_Thaana;

	YYCTYPE * buffer_Devanagari = new YYCTYPE [129];
	unsigned int buffer_Devanagari_len = encode_utf32 (chars_Devanagari, sizeof (chars_Devanagari) / sizeof (unsigned int), buffer_Devanagari);
	if (scan (reinterpret_cast<const YYCTYPE *> (buffer_Devanagari), reinterpret_cast<const YYCTYPE *> (buffer_Devanagari + buffer_Devanagari_len), Devanagari) != Devanagari)
		printf ("test 'Devanagari' failed\n");
	delete [] buffer_Devanagari;

	YYCTYPE * buffer_Bengali = new YYCTYPE [129];
	unsigned int buffer_Bengali_len = encode_utf32 (chars_Bengali, sizeof (chars_Bengali) / sizeof (unsigned int), buffer_Bengali);
	if (scan (reinterpret_cast<const YYCTYPE *> (buffer_Bengali), reinterpret_cast<const YYCTYPE *> (buffer_Bengali + buffer_Bengali_len), Bengali) != Bengali)
		printf ("test 'Bengali' failed\n");
	delete [] buffer_Bengali;

	YYCTYPE * buffer_Gurmukhi = new YYCTYPE [129];
	unsigned int buffer_Gurmukhi_len = encode_utf32 (chars_Gurmukhi, sizeof (chars_Gurmukhi) / sizeof (unsigned int), buffer_Gurmukhi);
	if (scan (reinterpret_cast<const YYCTYPE *> (buffer_Gurmukhi), reinterpret_cast<const YYCTYPE *> (buffer_Gurmukhi + buffer_Gurmukhi_len), Gurmukhi) != Gurmukhi)
		printf ("test 'Gurmukhi' failed\n");
	delete [] buffer_Gurmukhi;

	YYCTYPE * buffer_Gujarati = new YYCTYPE [129];
	unsigned int buffer_Gujarati_len = encode_utf32 (chars_Gujarati, sizeof (chars_Gujarati) / sizeof (unsigned int), buffer_Gujarati);
	if (scan (reinterpret_cast<const YYCTYPE *> (buffer_Gujarati), reinterpret_cast<const YYCTYPE *> (buffer_Gujarati + buffer_Gujarati_len), Gujarati) != Gujarati)
		printf ("test 'Gujarati' failed\n");
	delete [] buffer_Gujarati;

	YYCTYPE * buffer_Oriya = new YYCTYPE [129];
	unsigned int buffer_Oriya_len = encode_utf32 (chars_Oriya, sizeof (chars_Oriya) / sizeof (unsigned int), buffer_Oriya);
	if (scan (reinterpret_cast<const YYCTYPE *> (buffer_Oriya), reinterpret_cast<const YYCTYPE *> (buffer_Oriya + buffer_Oriya_len), Oriya) != Oriya)
		printf ("test 'Oriya' failed\n");
	delete [] buffer_Oriya;

	YYCTYPE * buffer_Tamil = new YYCTYPE [129];
	unsigned int buffer_Tamil_len = encode_utf32 (chars_Tamil, sizeof (chars_Tamil) / sizeof (unsigned int), buffer_Tamil);
	if (scan (reinterpret_cast<const YYCTYPE *> (buffer_Tamil), reinterpret_cast<const YYCTYPE *> (buffer_Tamil + buffer_Tamil_len), Tamil) != Tamil)
		printf ("test 'Tamil' failed\n");
	delete [] buffer_Tamil;

	YYCTYPE * buffer_Telugu = new YYCTYPE [129];
	unsigned int buffer_Telugu_len = encode_utf32 (chars_Telugu, sizeof (chars_Telugu) / sizeof (unsigned int), buffer_Telugu);
	if (scan (reinterpret_cast<const YYCTYPE *> (buffer_Telugu), reinterpret_cast<const YYCTYPE *> (buffer_Telugu + buffer_Telugu_len), Telugu) != Telugu)
		printf ("test 'Telugu' failed\n");
	delete [] buffer_Telugu;

	YYCTYPE * buffer_Kannada = new YYCTYPE [129];
	unsigned int buffer_Kannada_len = encode_utf32 (chars_Kannada, sizeof (chars_Kannada) / sizeof (unsigned int), buffer_Kannada);
	if (scan (reinterpret_cast<const YYCTYPE *> (buffer_Kannada), reinterpret_cast<const YYCTYPE *> (buffer_Kannada + buffer_Kannada_len), Kannada) != Kannada)
		printf ("test 'Kannada' failed\n");
	delete [] buffer_Kannada;

	YYCTYPE * buffer_Malayalam = new YYCTYPE [129];
	unsigned int buffer_Malayalam_len = encode_utf32 (chars_Malayalam, sizeof (chars_Malayalam) / sizeof (unsigned int), buffer_Malayalam);
	if (scan (reinterpret_cast<const YYCTYPE *> (buffer_Malayalam), reinterpret_cast<const YYCTYPE *> (buffer_Malayalam + buffer_Malayalam_len), Malayalam) != Malayalam)
		printf ("test 'Malayalam' failed\n");
	delete [] buffer_Malayalam;

	YYCTYPE * buffer_Sinhala = new YYCTYPE [129];
	unsigned int buffer_Sinhala_len = encode_utf32 (chars_Sinhala, sizeof (chars_Sinhala) / sizeof (unsigned int), buffer_Sinhala);
	if (scan (reinterpret_cast<const YYCTYPE *> (buffer_Sinhala), reinterpret_cast<const YYCTYPE *> (buffer_Sinhala + buffer_Sinhala_len), Sinhala) != Sinhala)
		printf ("test 'Sinhala' failed\n");
	delete [] buffer_Sinhala;

	YYCTYPE * buffer_Thai = new YYCTYPE [129];
	unsigned int buffer_Thai_len = encode_utf32 (chars_Thai, sizeof (chars_Thai) / sizeof (unsigned int), buffer_Thai);
	if (scan (reinterpret_cast<const YYCTYPE *> (buffer_Thai), reinterpret_cast<const YYCTYPE *> (buffer_Thai + buffer_Thai_len), Thai) != Thai)
		printf ("test 'Thai' failed\n");
	delete [] buffer_Thai;

	YYCTYPE * buffer_Lao = new YYCTYPE [129];
	unsigned int buffer_Lao_len = encode_utf32 (chars_Lao, sizeof (chars_Lao) / sizeof (unsigned int), buffer_Lao);
	if (scan (reinterpret_cast<const YYCTYPE *> (buffer_Lao), reinterpret_cast<const YYCTYPE *> (buffer_Lao + buffer_Lao_len), Lao) != Lao)
		printf ("test 'Lao' failed\n");
	delete [] buffer_Lao;

	YYCTYPE * buffer_Tibetan = new YYCTYPE [257];
	unsigned int buffer_Tibetan_len = encode_utf32 (chars_Tibetan, sizeof (chars_Tibetan) / sizeof (unsigned int), buffer_Tibetan);
	if (scan (reinterpret_cast<const YYCTYPE *> (buffer_Tibetan), reinterpret_cast<const YYCTYPE *> (buffer_Tibetan + buffer_Tibetan_len), Tibetan) != Tibetan)
		printf ("test 'Tibetan' failed\n");
	delete [] buffer_Tibetan;

	YYCTYPE * buffer_Myanmar = new YYCTYPE [161];
	unsigned int buffer_Myanmar_len = encode_utf32 (chars_Myanmar, sizeof (chars_Myanmar) / sizeof (unsigned int), buffer_Myanmar);
	if (scan (reinterpret_cast<const YYCTYPE *> (buffer_Myanmar), reinterpret_cast<const YYCTYPE *> (buffer_Myanmar + buffer_Myanmar_len), Myanmar) != Myanmar)
		printf ("test 'Myanmar' failed\n");
	delete [] buffer_Myanmar;

	YYCTYPE * buffer_Georgian = new YYCTYPE [97];
	unsigned int buffer_Georgian_len = encode_utf32 (chars_Georgian, sizeof (chars_Georgian) / sizeof (unsigned int), buffer_Georgian);
	if (scan (reinterpret_cast<const YYCTYPE *> (buffer_Georgian), reinterpret_cast<const YYCTYPE *> (buffer_Georgian + buffer_Georgian_len), Georgian) != Georgian)
		printf ("test 'Georgian' failed\n");
	delete [] buffer_Georgian;

	YYCTYPE * buffer_Hangul_Jamo = new YYCTYPE [257];
	unsigned int buffer_Hangul_Jamo_len = encode_utf32 (chars_Hangul_Jamo, sizeof (chars_Hangul_Jamo) / sizeof (unsigned int), buffer_Hangul_Jamo);
	if (scan (reinterpret_cast<const YYCTYPE *> (buffer_Hangul_Jamo), reinterpret_cast<const YYCTYPE *> (buffer_Hangul_Jamo + buffer_Hangul_Jamo_len), Hangul_Jamo) != Hangul_Jamo)
		printf ("test 'Hangul_Jamo' failed\n");
	delete [] buffer_Hangul_Jamo;

	YYCTYPE * buffer_Ethiopic = new YYCTYPE [385];
	unsigned int buffer_Ethiopic_len = encode_utf32 (chars_Ethiopic, sizeof (chars_Ethiopic) / sizeof (unsigned int), buffer_Ethiopic);
	if (scan (reinterpret_cast<const YYCTYPE *> (buffer_Ethiopic), reinterpret_cast<const YYCTYPE *> (buffer_Ethiopic + buffer_Ethiopic_len), Ethiopic) != Ethiopic)
		printf ("test 'Ethiopic' failed\n");
	delete [] buffer_Ethiopic;

	YYCTYPE * buffer_Cherokee = new YYCTYPE [97];
	unsigned int buffer_Cherokee_len = encode_utf32 (chars_Cherokee, sizeof (chars_Cherokee) / sizeof (unsigned int), buffer_Cherokee);
	if (scan (reinterpret_cast<const YYCTYPE *> (buffer_Cherokee), reinterpret_cast<const YYCTYPE *> (buffer_Cherokee + buffer_Cherokee_len), Cherokee) != Cherokee)
		printf ("test 'Cherokee' failed\n");
	delete [] buffer_Cherokee;

	YYCTYPE * buffer_Unified_Canadian_Aboriginal_Syllabics = new YYCTYPE [641];
	unsigned int buffer_Unified_Canadian_Aboriginal_Syllabics_len = encode_utf32 (chars_Unified_Canadian_Aboriginal_Syllabics, sizeof (chars_Unified_Canadian_Aboriginal_Syllabics) / sizeof (unsigned int), buffer_Unified_Canadian_Aboriginal_Syllabics);
	if (scan (reinterpret_cast<const YYCTYPE *> (buffer_Unified_Canadian_Aboriginal_Syllabics), reinterpret_cast<const YYCTYPE *> (buffer_Unified_Canadian_Aboriginal_Syllabics + buffer_Unified_Canadian_Aboriginal_Syllabics_len), Unified_Canadian_Aboriginal_Syllabics) != Unified_Canadian_Aboriginal_Syllabics)
		printf ("test 'Unified_Canadian_Aboriginal_Syllabics' failed\n");
	delete [] buffer_Unified_Canadian_Aboriginal_Syllabics;

	YYCTYPE * buffer_Ogham = new YYCTYPE [33];
	unsigned int buffer_Ogham_len = encode_utf32 (chars_Ogham, sizeof (chars_Ogham) / sizeof (unsigned int), buffer_Ogham);
	if (scan (reinterpret_cast<const YYCTYPE *> (buffer_Ogham), reinterpret_cast<const YYCTYPE *> (buffer_Ogham + buffer_Ogham_len), Ogham) != Ogham)
		printf ("test 'Ogham' failed\n");
	delete [] buffer_Ogham;

	YYCTYPE * buffer_Runic = new YYCTYPE [97];
	unsigned int buffer_Runic_len = encode_utf32 (chars_Runic, sizeof (chars_Runic) / sizeof (unsigned int), buffer_Runic);
	if (scan (reinterpret_cast<const YYCTYPE *> (buffer_Runic), reinterpret_cast<const YYCTYPE *> (buffer_Runic + buffer_Runic_len), Runic) != Runic)
		printf ("test 'Runic' failed\n");
	delete [] buffer_Runic;

	YYCTYPE * buffer_Tagalog = new YYCTYPE [33];
	unsigned int buffer_Tagalog_len = encode_utf32 (chars_Tagalog, sizeof (chars_Tagalog) / sizeof (unsigned int), buffer_Tagalog);
	if (scan (reinterpret_cast<const YYCTYPE *> (buffer_Tagalog), reinterpret_cast<const YYCTYPE *> (buffer_Tagalog + buffer_Tagalog_len), Tagalog) != Tagalog)
		printf ("test 'Tagalog' failed\n");
	delete [] buffer_Tagalog;

	YYCTYPE * buffer_Hanunoo = new YYCTYPE [33];
	unsigned int buffer_Hanunoo_len = encode_utf32 (chars_Hanunoo, sizeof (chars_Hanunoo) / sizeof (unsigned int), buffer_Hanunoo);
	if (scan (reinterpret_cast<const YYCTYPE *> (buffer_Hanunoo), reinterpret_cast<const YYCTYPE *> (buffer_Hanunoo + buffer_Hanunoo_len), Hanunoo) != Hanunoo)
		printf ("test 'Hanunoo' failed\n");
	delete [] buffer_Hanunoo;

	YYCTYPE * buffer_Buhid = new YYCTYPE [33];
	unsigned int buffer_Buhid_len = encode_utf32 (chars_Buhid, sizeof (chars_Buhid) / sizeof (unsigned int), buffer_Buhid);
	if (scan (reinterpret_cast<const YYCTYPE *> (buffer_Buhid), reinterpret_cast<const YYCTYPE *> (buffer_Buhid + buffer_Buhid_len), Buhid) != Buhid)
		printf ("test 'Buhid' failed\n");
	delete [] buffer_Buhid;

	YYCTYPE * buffer_Tagbanwa = new YYCTYPE [33];
	unsigned int buffer_Tagbanwa_len = encode_utf32 (chars_Tagbanwa, sizeof (chars_Tagbanwa) / sizeof (unsigned int), buffer_Tagbanwa);
	if (scan (reinterpret_cast<const YYCTYPE *> (buffer_Tagbanwa), reinterpret_cast<const YYCTYPE *> (buffer_Tagbanwa + buffer_Tagbanwa_len), Tagbanwa) != Tagbanwa)
		printf ("test 'Tagbanwa' failed\n");
	delete [] buffer_Tagbanwa;

	YYCTYPE * buffer_Khmer = new YYCTYPE [129];
	unsigned int buffer_Khmer_len = encode_utf32 (chars_Khmer, sizeof (chars_Khmer) / sizeof (unsigned int), buffer_Khmer);
	if (scan (reinterpret_cast<const YYCTYPE *> (buffer_Khmer), reinterpret_cast<const YYCTYPE *> (buffer_Khmer + buffer_Khmer_len), Khmer) != Khmer)
		printf ("test 'Khmer' failed\n");
	delete [] buffer_Khmer;

	YYCTYPE * buffer_Mongolian = new YYCTYPE [177];
	unsigned int buffer_Mongolian_len = encode_utf32 (chars_Mongolian, sizeof (chars_Mongolian) / sizeof (unsigned int), buffer_Mongolian);
	if (scan (reinterpret_cast<const YYCTYPE *> (buffer_Mongolian), reinterpret_cast<const YYCTYPE *> (buffer_Mongolian + buffer_Mongolian_len), Mongolian) != Mongolian)
		printf ("test 'Mongolian' failed\n");
	delete [] buffer_Mongolian;

	YYCTYPE * buffer_Limbu = new YYCTYPE [81];
	unsigned int buffer_Limbu_len = encode_utf32 (chars_Limbu, sizeof (chars_Limbu) / sizeof (unsigned int), buffer_Limbu);
	if (scan (reinterpret_cast<const YYCTYPE *> (buffer_Limbu), reinterpret_cast<const YYCTYPE *> (buffer_Limbu + buffer_Limbu_len), Limbu) != Limbu)
		printf ("test 'Limbu' failed\n");
	delete [] buffer_Limbu;

	YYCTYPE * buffer_Tai_Le = new YYCTYPE [49];
	unsigned int buffer_Tai_Le_len = encode_utf32 (chars_Tai_Le, sizeof (chars_Tai_Le) / sizeof (unsigned int), buffer_Tai_Le);
	if (scan (reinterpret_cast<const YYCTYPE *> (buffer_Tai_Le), reinterpret_cast<const YYCTYPE *> (buffer_Tai_Le + buffer_Tai_Le_len), Tai_Le) != Tai_Le)
		printf ("test 'Tai_Le' failed\n");
	delete [] buffer_Tai_Le;

	YYCTYPE * buffer_Khmer_Symbols = new YYCTYPE [33];
	unsigned int buffer_Khmer_Symbols_len = encode_utf32 (chars_Khmer_Symbols, sizeof (chars_Khmer_Symbols) / sizeof (unsigned int), buffer_Khmer_Symbols);
	if (scan (reinterpret_cast<const YYCTYPE *> (buffer_Khmer_Symbols), reinterpret_cast<const YYCTYPE *> (buffer_Khmer_Symbols + buffer_Khmer_Symbols_len), Khmer_Symbols) != Khmer_Symbols)
		printf ("test 'Khmer_Symbols' failed\n");
	delete [] buffer_Khmer_Symbols;

	YYCTYPE * buffer_Phonetic_Extensions = new YYCTYPE [129];
	unsigned int buffer_Phonetic_Extensions_len = encode_utf32 (chars_Phonetic_Extensions, sizeof (chars_Phonetic_Extensions) / sizeof (unsigned int), buffer_Phonetic_Extensions);
	if (scan (reinterpret_cast<const YYCTYPE *> (buffer_Phonetic_Extensions), reinterpret_cast<const YYCTYPE *> (buffer_Phonetic_Extensions + buffer_Phonetic_Extensions_len), Phonetic_Extensions) != Phonetic_Extensions)
		printf ("test 'Phonetic_Extensions' failed\n");
	delete [] buffer_Phonetic_Extensions;

	YYCTYPE * buffer_Latin_Extended_Additional = new YYCTYPE [257];
	unsigned int buffer_Latin_Extended_Additional_len = encode_utf32 (chars_Latin_Extended_Additional, sizeof (chars_Latin_Extended_Additional) / sizeof (unsigned int), buffer_Latin_Extended_Additional);
	if (scan (reinterpret_cast<const YYCTYPE *> (buffer_Latin_Extended_Additional), reinterpret_cast<const YYCTYPE *> (buffer_Latin_Extended_Additional + buffer_Latin_Extended_Additional_len), Latin_Extended_Additional) != Latin_Extended_Additional)
		printf ("test 'Latin_Extended_Additional' failed\n");
	delete [] buffer_Latin_Extended_Additional;

	YYCTYPE * buffer_Greek_Extended = new YYCTYPE [257];
	unsigned int buffer_Greek_Extended_len = encode_utf32 (chars_Greek_Extended, sizeof (chars_Greek_Extended) / sizeof (unsigned int), buffer_Greek_Extended);
	if (scan (reinterpret_cast<const YYCTYPE *> (buffer_Greek_Extended), reinterpret_cast<const YYCTYPE *> (buffer_Greek_Extended + buffer_Greek_Extended_len), Greek_Extended) != Greek_Extended)
		printf ("test 'Greek_Extended' failed\n");
	delete [] buffer_Greek_Extended;

	YYCTYPE * buffer_General_Punctuation = new YYCTYPE [113];
	unsigned int buffer_General_Punctuation_len = encode_utf32 (chars_General_Punctuation, sizeof (chars_General_Punctuation) / sizeof (unsigned int), buffer_General_Punctuation);
	if (scan (reinterpret_cast<const YYCTYPE *> (buffer_General_Punctuation), reinterpret_cast<const YYCTYPE *> (buffer_General_Punctuation + buffer_General_Punctuation_len), General_Punctuation) != General_Punctuation)
		printf ("test 'General_Punctuation' failed\n");
	delete [] buffer_General_Punctuation;

	YYCTYPE * buffer_Superscripts_and_Subscripts = new YYCTYPE [49];
	unsigned int buffer_Superscripts_and_Subscripts_len = encode_utf32 (chars_Superscripts_and_Subscripts, sizeof (chars_Superscripts_and_Subscripts) / sizeof (unsigned int), buffer_Superscripts_and_Subscripts);
	if (scan (reinterpret_cast<const YYCTYPE *> (buffer_Superscripts_and_Subscripts), reinterpret_cast<const YYCTYPE *> (buffer_Superscripts_and_Subscripts + buffer_Superscripts_and_Subscripts_len), Superscripts_and_Subscripts) != Superscripts_and_Subscripts)
		printf ("test 'Superscripts_and_Subscripts' failed\n");
	delete [] buffer_Superscripts_and_Subscripts;

	YYCTYPE * buffer_Currency_Symbols = new YYCTYPE [49];
	unsigned int buffer_Currency_Symbols_len = encode_utf32 (chars_Currency_Symbols, sizeof (chars_Currency_Symbols) / sizeof (unsigned int), buffer_Currency_Symbols);
	if (scan (reinterpret_cast<const YYCTYPE *> (buffer_Currency_Symbols), reinterpret_cast<const YYCTYPE *> (buffer_Currency_Symbols + buffer_Currency_Symbols_len), Currency_Symbols) != Currency_Symbols)
		printf ("test 'Currency_Symbols' failed\n");
	delete [] buffer_Currency_Symbols;

	YYCTYPE * buffer_Combining_Diacritical_Marks_for_Symbols = new YYCTYPE [49];
	unsigned int buffer_Combining_Diacritical_Marks_for_Symbols_len = encode_utf32 (chars_Combining_Diacritical_Marks_for_Symbols, sizeof (chars_Combining_Diacritical_Marks_for_Symbols) / sizeof (unsigned int), buffer_Combining_Diacritical_Marks_for_Symbols);
	if (scan (reinterpret_cast<const YYCTYPE *> (buffer_Combining_Diacritical_Marks_for_Symbols), reinterpret_cast<const YYCTYPE *> (buffer_Combining_Diacritical_Marks_for_Symbols + buffer_Combining_Diacritical_Marks_for_Symbols_len), Combining_Diacritical_Marks_for_Symbols) != Combining_Diacritical_Marks_for_Symbols)
		printf ("test 'Combining_Diacritical_Marks_for_Symbols' failed\n");
	delete [] buffer_Combining_Diacritical_Marks_for_Symbols;

	YYCTYPE * buffer_Letterlike_Symbols = new YYCTYPE [81];
	unsigned int buffer_Letterlike_Symbols_len = encode_utf32 (chars_Letterlike_Symbols, sizeof (chars_Letterlike_Symbols) / sizeof (unsigned int), buffer_Letterlike_Symbols);
	if (scan (reinterpret_cast<const YYCTYPE *> (buffer_Letterlike_Symbols), reinterpret_cast<const YYCTYPE *> (buffer_Letterlike_Symbols + buffer_Letterlike_Symbols_len), Letterlike_Symbols) != Letterlike_Symbols)
		printf ("test 'Letterlike_Symbols' failed\n");
	delete [] buffer_Letterlike_Symbols;

	YYCTYPE * buffer_Number_Forms = new YYCTYPE [65];
	unsigned int buffer_Number_Forms_len = encode_utf32 (chars_Number_Forms, sizeof (chars_Number_Forms) / sizeof (unsigned int), buffer_Number_Forms);
	if (scan (reinterpret_cast<const YYCTYPE *> (buffer_Number_Forms), reinterpret_cast<const YYCTYPE *> (buffer_Number_Forms + buffer_Number_Forms_len), Number_Forms) != Number_Forms)
		printf ("test 'Number_Forms' failed\n");
	delete [] buffer_Number_Forms;

	YYCTYPE * buffer_Arrows = new YYCTYPE [113];
	unsigned int buffer_Arrows_len = encode_utf32 (chars_Arrows, sizeof (chars_Arrows) / sizeof (unsigned int), buffer_Arrows);
	if (scan (reinterpret_cast<const YYCTYPE *> (buffer_Arrows), reinterpret_cast<const YYCTYPE *> (buffer_Arrows + buffer_Arrows_len), Arrows) != Arrows)
		printf ("test 'Arrows' failed\n");
	delete [] buffer_Arrows;

	YYCTYPE * buffer_Mathematical_Operators = new YYCTYPE [257];
	unsigned int buffer_Mathematical_Operators_len = encode_utf32 (chars_Mathematical_Operators, sizeof (chars_Mathematical_Operators) / sizeof (unsigned int), buffer_Mathematical_Operators);
	if (scan (reinterpret_cast<const YYCTYPE *> (buffer_Mathematical_Operators), reinterpret_cast<const YYCTYPE *> (buffer_Mathematical_Operators + buffer_Mathematical_Operators_len), Mathematical_Operators) != Mathematical_Operators)
		printf ("test 'Mathematical_Operators' failed\n");
	delete [] buffer_Mathematical_Operators;

	YYCTYPE * buffer_Miscellaneous_Technical = new YYCTYPE [257];
	unsigned int buffer_Miscellaneous_Technical_len = encode_utf32 (chars_Miscellaneous_Technical, sizeof (chars_Miscellaneous_Technical) / sizeof (unsigned int), buffer_Miscellaneous_Technical);
	if (scan (reinterpret_cast<const YYCTYPE *> (buffer_Miscellaneous_Technical), reinterpret_cast<const YYCTYPE *> (buffer_Miscellaneous_Technical + buffer_Miscellaneous_Technical_len), Miscellaneous_Technical) != Miscellaneous_Technical)
		printf ("test 'Miscellaneous_Technical' failed\n");
	delete [] buffer_Miscellaneous_Technical;

	YYCTYPE * buffer_Control_Pictures = new YYCTYPE [65];
	unsigned int buffer_Control_Pictures_len = encode_utf32 (chars_Control_Pictures, sizeof (chars_Control_Pictures) / sizeof (unsigned int), buffer_Control_Pictures);
	if (scan (reinterpret_cast<const YYCTYPE *> (buffer_Control_Pictures), reinterpret_cast<const YYCTYPE *> (buffer_Control_Pictures + buffer_Control_Pictures_len), Control_Pictures) != Control_Pictures)
		printf ("test 'Control_Pictures' failed\n");
	delete [] buffer_Control_Pictures;

	YYCTYPE * buffer_Optical_Character_Recognition = new YYCTYPE [33];
	unsigned int buffer_Optical_Character_Recognition_len = encode_utf32 (chars_Optical_Character_Recognition, sizeof (chars_Optical_Character_Recognition) / sizeof (unsigned int), buffer_Optical_Character_Recognition);
	if (scan (reinterpret_cast<const YYCTYPE *> (buffer_Optical_Character_Recognition), reinterpret_cast<const YYCTYPE *> (buffer_Optical_Character_Recognition + buffer_Optical_Character_Recognition_len), Optical_Character_Recognition) != Optical_Character_Recognition)
		printf ("test 'Optical_Character_Recognition' failed\n");
	delete [] buffer_Optical_Character_Recognition;

	YYCTYPE * buffer_Enclosed_Alphanumerics = new YYCTYPE [161];
	unsigned int buffer_Enclosed_Alphanumerics_len = encode_utf32 (chars_Enclosed_Alphanumerics, sizeof (chars_Enclosed_Alphanumerics) / sizeof (unsigned int), buffer_Enclosed_Alphanumerics);
	if (scan (reinterpret_cast<const YYCTYPE *> (buffer_Enclosed_Alphanumerics), reinterpret_cast<const YYCTYPE *> (buffer_Enclosed_Alphanumerics + buffer_Enclosed_Alphanumerics_len), Enclosed_Alphanumerics) != Enclosed_Alphanumerics)
		printf ("test 'Enclosed_Alphanumerics' failed\n");
	delete [] buffer_Enclosed_Alphanumerics;

	YYCTYPE * buffer_Box_Drawing = new YYCTYPE [129];
	unsigned int buffer_Box_Drawing_len = encode_utf32 (chars_Box_Drawing, sizeof (chars_Box_Drawing) / sizeof (unsigned int), buffer_Box_Drawing);
	if (scan (reinterpret_cast<const YYCTYPE *> (buffer_Box_Drawing), reinterpret_cast<const YYCTYPE *> (buffer_Box_Drawing + buffer_Box_Drawing_len), Box_Drawing) != Box_Drawing)
		printf ("test 'Box_Drawing' failed\n");
	delete [] buffer_Box_Drawing;

	YYCTYPE * buffer_Block_Elements = new YYCTYPE [33];
	unsigned int buffer_Block_Elements_len = encode_utf32 (chars_Block_Elements, sizeof (chars_Block_Elements) / sizeof (unsigned int), buffer_Block_Elements);
	if (scan (reinterpret_cast<const YYCTYPE *> (buffer_Block_Elements), reinterpret_cast<const YYCTYPE *> (buffer_Block_Elements + buffer_Block_Elements_len), Block_Elements) != Block_Elements)
		printf ("test 'Block_Elements' failed\n");
	delete [] buffer_Block_Elements;

	YYCTYPE * buffer_Geometric_Shapes = new YYCTYPE [97];
	unsigned int buffer_Geometric_Shapes_len = encode_utf32 (chars_Geometric_Shapes, sizeof (chars_Geometric_Shapes) / sizeof (unsigned int), buffer_Geometric_Shapes);
	if (scan (reinterpret_cast<const YYCTYPE *> (buffer_Geometric_Shapes), reinterpret_cast<const YYCTYPE *> (buffer_Geometric_Shapes + buffer_Geometric_Shapes_len), Geometric_Shapes) != Geometric_Shapes)
		printf ("test 'Geometric_Shapes' failed\n");
	delete [] buffer_Geometric_Shapes;

	YYCTYPE * buffer_Miscellaneous_Symbols = new YYCTYPE [257];
	unsigned int buffer_Miscellaneous_Symbols_len = encode_utf32 (chars_Miscellaneous_Symbols, sizeof (chars_Miscellaneous_Symbols) / sizeof (unsigned int), buffer_Miscellaneous_Symbols);
	if (scan (reinterpret_cast<const YYCTYPE *> (buffer_Miscellaneous_Symbols), reinterpret_cast<const YYCTYPE *> (buffer_Miscellaneous_Symbols + buffer_Miscellaneous_Symbols_len), Miscellaneous_Symbols) != Miscellaneous_Symbols)
		printf ("test 'Miscellaneous_Symbols' failed\n");
	delete [] buffer_Miscellaneous_Symbols;

	YYCTYPE * buffer_Dingbats = new YYCTYPE [193];
	unsigned int buffer_Dingbats_len = encode_utf32 (chars_Dingbats, sizeof (chars_Dingbats) / sizeof (unsigned int), buffer_Dingbats);
	if (scan (reinterpret_cast<const YYCTYPE *> (buffer_Dingbats), reinterpret_cast<const YYCTYPE *> (buffer_Dingbats + buffer_Dingbats_len), Dingbats) != Dingbats)
		printf ("test 'Dingbats' failed\n");
	delete [] buffer_Dingbats;

	YYCTYPE * buffer_Miscellaneous_Mathematical_Symbols_A = new YYCTYPE [49];
	unsigned int buffer_Miscellaneous_Mathematical_Symbols_A_len = encode_utf32 (chars_Miscellaneous_Mathematical_Symbols_A, sizeof (chars_Miscellaneous_Mathematical_Symbols_A) / sizeof (unsigned int), buffer_Miscellaneous_Mathematical_Symbols_A);
	if (scan (reinterpret_cast<const YYCTYPE *> (buffer_Miscellaneous_Mathematical_Symbols_A), reinterpret_cast<const YYCTYPE *> (buffer_Miscellaneous_Mathematical_Symbols_A + buffer_Miscellaneous_Mathematical_Symbols_A_len), Miscellaneous_Mathematical_Symbols_A) != Miscellaneous_Mathematical_Symbols_A)
		printf ("test 'Miscellaneous_Mathematical_Symbols_A' failed\n");
	delete [] buffer_Miscellaneous_Mathematical_Symbols_A;

	YYCTYPE * buffer_Supplemental_Arrows_A = new YYCTYPE [17];
	unsigned int buffer_Supplemental_Arrows_A_len = encode_utf32 (chars_Supplemental_Arrows_A, sizeof (chars_Supplemental_Arrows_A) / sizeof (unsigned int), buffer_Supplemental_Arrows_A);
	if (scan (reinterpret_cast<const YYCTYPE *> (buffer_Supplemental_Arrows_A), reinterpret_cast<const YYCTYPE *> (buffer_Supplemental_Arrows_A + buffer_Supplemental_Arrows_A_len), Supplemental_Arrows_A) != Supplemental_Arrows_A)
		printf ("test 'Supplemental_Arrows_A' failed\n");
	delete [] buffer_Supplemental_Arrows_A;

	YYCTYPE * buffer_Braille_Patterns = new YYCTYPE [257];
	unsigned int buffer_Braille_Patterns_len = encode_utf32 (chars_Braille_Patterns, sizeof (chars_Braille_Patterns) / sizeof (unsigned int), buffer_Braille_Patterns);
	if (scan (reinterpret_cast<const YYCTYPE *> (buffer_Braille_Patterns), reinterpret_cast<const YYCTYPE *> (buffer_Braille_Patterns + buffer_Braille_Patterns_len), Braille_Patterns) != Braille_Patterns)
		printf ("test 'Braille_Patterns' failed\n");
	delete [] buffer_Braille_Patterns;

	YYCTYPE * buffer_Supplemental_Arrows_B = new YYCTYPE [129];
	unsigned int buffer_Supplemental_Arrows_B_len = encode_utf32 (chars_Supplemental_Arrows_B, sizeof (chars_Supplemental_Arrows_B) / sizeof (unsigned int), buffer_Supplemental_Arrows_B);
	if (scan (reinterpret_cast<const YYCTYPE *> (buffer_Supplemental_Arrows_B), reinterpret_cast<const YYCTYPE *> (buffer_Supplemental_Arrows_B + buffer_Supplemental_Arrows_B_len), Supplemental_Arrows_B) != Supplemental_Arrows_B)
		printf ("test 'Supplemental_Arrows_B' failed\n");
	delete [] buffer_Supplemental_Arrows_B;

	YYCTYPE * buffer_Miscellaneous_Mathematical_Symbols_B = new YYCTYPE [129];
	unsigned int buffer_Miscellaneous_Mathematical_Symbols_B_len = encode_utf32 (chars_Miscellaneous_Mathematical_Symbols_B, sizeof (chars_Miscellaneous_Mathematical_Symbols_B) / sizeof (unsigned int), buffer_Miscellaneous_Mathematical_Symbols_B);
	if (scan (reinterpret_cast<const YYCTYPE *> (buffer_Miscellaneous_Mathematical_Symbols_B), reinterpret_cast<const YYCTYPE *> (buffer_Miscellaneous_Mathematical_Symbols_B + buffer_Miscellaneous_Mathematical_Symbols_B_len), Miscellaneous_Mathematical_Symbols_B) != Miscellaneous_Mathematical_Symbols_B)
		printf ("test 'Miscellaneous_Mathematical_Symbols_B' failed\n");
	delete [] buffer_Miscellaneous_Mathematical_Symbols_B;

	YYCTYPE * buffer_Supplemental_Mathematical_Operators = new YYCTYPE [257];
	unsigned int buffer_Supplemental_Mathematical_Operators_len = encode_utf32 (chars_Supplemental_Mathematical_Operators, sizeof (chars_Supplemental_Mathematical_Operators) / sizeof (unsigned int), buffer_Supplemental_Mathematical_Operators);
	if (scan (reinterpret_cast<const YYCTYPE *> (buffer_Supplemental_Mathematical_Operators), reinterpret_cast<const YYCTYPE *> (buffer_Supplemental_Mathematical_Operators + buffer_Supplemental_Mathematical_Operators_len), Supplemental_Mathematical_Operators) != Supplemental_Mathematical_Operators)
		printf ("test 'Supplemental_Mathematical_Operators' failed\n");
	delete [] buffer_Supplemental_Mathematical_Operators;

	YYCTYPE * buffer_Miscellaneous_Symbols_and_Arrows = new YYCTYPE [257];
	unsigned int buffer_Miscellaneous_Symbols_and_Arrows_len = encode_utf32 (chars_Miscellaneous_Symbols_and_Arrows, sizeof (chars_Miscellaneous_Symbols_and_Arrows) / sizeof (unsigned int), buffer_Miscellaneous_Symbols_and_Arrows);
	if (scan (reinterpret_cast<const YYCTYPE *> (buffer_Miscellaneous_Symbols_and_Arrows), reinterpret_cast<const YYCTYPE *> (buffer_Miscellaneous_Symbols_and_Arrows + buffer_Miscellaneous_Symbols_and_Arrows_len), Miscellaneous_Symbols_and_Arrows) != Miscellaneous_Symbols_and_Arrows)
		printf ("test 'Miscellaneous_Symbols_and_Arrows' failed\n");
	delete [] buffer_Miscellaneous_Symbols_and_Arrows;

	YYCTYPE * buffer_CJK_Radicals_Supplement = new YYCTYPE [129];
	unsigned int buffer_CJK_Radicals_Supplement_len = encode_utf32 (chars_CJK_Radicals_Supplement, sizeof (chars_CJK_Radicals_Supplement) / sizeof (unsigned int), buffer_CJK_Radicals_Supplement);
	if (scan (reinterpret_cast<const YYCTYPE *> (buffer_CJK_Radicals_Supplement), reinterpret_cast<const YYCTYPE *> (buffer_CJK_Radicals_Supplement + buffer_CJK_Radicals_Supplement_len), CJK_Radicals_Supplement) != CJK_Radicals_Supplement)
		printf ("test 'CJK_Radicals_Supplement' failed\n");
	delete [] buffer_CJK_Radicals_Supplement;

	YYCTYPE * buffer_Kangxi_Radicals = new YYCTYPE [225];
	unsigned int buffer_Kangxi_Radicals_len = encode_utf32 (chars_Kangxi_Radicals, sizeof (chars_Kangxi_Radicals) / sizeof (unsigned int), buffer_Kangxi_Radicals);
	if (scan (reinterpret_cast<const YYCTYPE *> (buffer_Kangxi_Radicals), reinterpret_cast<const YYCTYPE *> (buffer_Kangxi_Radicals + buffer_Kangxi_Radicals_len), Kangxi_Radicals) != Kangxi_Radicals)
		printf ("test 'Kangxi_Radicals' failed\n");
	delete [] buffer_Kangxi_Radicals;

	YYCTYPE * buffer_Ideographic_Description_Characters = new YYCTYPE [17];
	unsigned int buffer_Ideographic_Description_Characters_len = encode_utf32 (chars_Ideographic_Description_Characters, sizeof (chars_Ideographic_Description_Characters) / sizeof (unsigned int), buffer_Ideographic_Description_Characters);
	if (scan (reinterpret_cast<const YYCTYPE *> (buffer_Ideographic_Description_Characters), reinterpret_cast<const YYCTYPE *> (buffer_Ideographic_Description_Characters + buffer_Ideographic_Description_Characters_len), Ideographic_Description_Characters) != Ideographic_Description_Characters)
		printf ("test 'Ideographic_Description_Characters' failed\n");
	delete [] buffer_Ideographic_Description_Characters;

	YYCTYPE * buffer_CJK_Symbols_and_Punctuation = new YYCTYPE [65];
	unsigned int buffer_CJK_Symbols_and_Punctuation_len = encode_utf32 (chars_CJK_Symbols_and_Punctuation, sizeof (chars_CJK_Symbols_and_Punctuation) / sizeof (unsigned int), buffer_CJK_Symbols_and_Punctuation);
	if (scan (reinterpret_cast<const YYCTYPE *> (buffer_CJK_Symbols_and_Punctuation), reinterpret_cast<const YYCTYPE *> (buffer_CJK_Symbols_and_Punctuation + buffer_CJK_Symbols_and_Punctuation_len), CJK_Symbols_and_Punctuation) != CJK_Symbols_and_Punctuation)
		printf ("test 'CJK_Symbols_and_Punctuation' failed\n");
	delete [] buffer_CJK_Symbols_and_Punctuation;

	YYCTYPE * buffer_Hiragana = new YYCTYPE [97];
	unsigned int buffer_Hiragana_len = encode_utf32 (chars_Hiragana, sizeof (chars_Hiragana) / sizeof (unsigned int), buffer_Hiragana);
	if (scan (reinterpret_cast<const YYCTYPE *> (buffer_Hiragana), reinterpret_cast<const YYCTYPE *> (buffer_Hiragana + buffer_Hiragana_len), Hiragana) != Hiragana)
		printf ("test 'Hiragana' failed\n");
	delete [] buffer_Hiragana;

	YYCTYPE * buffer_Katakana = new YYCTYPE [97];
	unsigned int buffer_Katakana_len = encode_utf32 (chars_Katakana, sizeof (chars_Katakana) / sizeof (unsigned int), buffer_Katakana);
	if (scan (reinterpret_cast<const YYCTYPE *> (buffer_Katakana), reinterpret_cast<const YYCTYPE *> (buffer_Katakana + buffer_Katakana_len), Katakana) != Katakana)
		printf ("test 'Katakana' failed\n");
	delete [] buffer_Katakana;

	YYCTYPE * buffer_Bopomofo = new YYCTYPE [49];
	unsigned int buffer_Bopomofo_len = encode_utf32 (chars_Bopomofo, sizeof (chars_Bopomofo) / sizeof (unsigned int), buffer_Bopomofo);
	if (scan (reinterpret_cast<const YYCTYPE *> (buffer_Bopomofo), reinterpret_cast<const YYCTYPE *> (buffer_Bopomofo + buffer_Bopomofo_len), Bopomofo) != Bopomofo)
		printf ("test 'Bopomofo' failed\n");
	delete [] buffer_Bopomofo;

	YYCTYPE * buffer_Hangul_Compatibility_Jamo = new YYCTYPE [97];
	unsigned int buffer_Hangul_Compatibility_Jamo_len = encode_utf32 (chars_Hangul_Compatibility_Jamo, sizeof (chars_Hangul_Compatibility_Jamo) / sizeof (unsigned int), buffer_Hangul_Compatibility_Jamo);
	if (scan (reinterpret_cast<const YYCTYPE *> (buffer_Hangul_Compatibility_Jamo), reinterpret_cast<const YYCTYPE *> (buffer_Hangul_Compatibility_Jamo + buffer_Hangul_Compatibility_Jamo_len), Hangul_Compatibility_Jamo) != Hangul_Compatibility_Jamo)
		printf ("test 'Hangul_Compatibility_Jamo' failed\n");
	delete [] buffer_Hangul_Compatibility_Jamo;

	YYCTYPE * buffer_Kanbun = new YYCTYPE [17];
	unsigned int buffer_Kanbun_len = encode_utf32 (chars_Kanbun, sizeof (chars_Kanbun) / sizeof (unsigned int), buffer_Kanbun);
	if (scan (reinterpret_cast<const YYCTYPE *> (buffer_Kanbun), reinterpret_cast<const YYCTYPE *> (buffer_Kanbun + buffer_Kanbun_len), Kanbun) != Kanbun)
		printf ("test 'Kanbun' failed\n");
	delete [] buffer_Kanbun;

	YYCTYPE * buffer_Bopomofo_Extended = new YYCTYPE [33];
	unsigned int buffer_Bopomofo_Extended_len = encode_utf32 (chars_Bopomofo_Extended, sizeof (chars_Bopomofo_Extended) / sizeof (unsigned int), buffer_Bopomofo_Extended);
	if (scan (reinterpret_cast<const YYCTYPE *> (buffer_Bopomofo_Extended), reinterpret_cast<const YYCTYPE *> (buffer_Bopomofo_Extended + buffer_Bopomofo_Extended_len), Bopomofo_Extended) != Bopomofo_Extended)
		printf ("test 'Bopomofo_Extended' failed\n");
	delete [] buffer_Bopomofo_Extended;

	YYCTYPE * buffer_Katakana_Phonetic_Extensions = new YYCTYPE [17];
	unsigned int buffer_Katakana_Phonetic_Extensions_len = encode_utf32 (chars_Katakana_Phonetic_Extensions, sizeof (chars_Katakana_Phonetic_Extensions) / sizeof (unsigned int), buffer_Katakana_Phonetic_Extensions);
	if (scan (reinterpret_cast<const YYCTYPE *> (buffer_Katakana_Phonetic_Extensions), reinterpret_cast<const YYCTYPE *> (buffer_Katakana_Phonetic_Extensions + buffer_Katakana_Phonetic_Extensions_len), Katakana_Phonetic_Extensions) != Katakana_Phonetic_Extensions)
		printf ("test 'Katakana_Phonetic_Extensions' failed\n");
	delete [] buffer_Katakana_Phonetic_Extensions;

	YYCTYPE * buffer_Enclosed_CJK_Letters_and_Months = new YYCTYPE [257];
	unsigned int buffer_Enclosed_CJK_Letters_and_Months_len = encode_utf32 (chars_Enclosed_CJK_Letters_and_Months, sizeof (chars_Enclosed_CJK_Letters_and_Months) / sizeof (unsigned int), buffer_Enclosed_CJK_Letters_and_Months);
	if (scan (reinterpret_cast<const YYCTYPE *> (buffer_Enclosed_CJK_Letters_and_Months), reinterpret_cast<const YYCTYPE *> (buffer_Enclosed_CJK_Letters_and_Months + buffer_Enclosed_CJK_Letters_and_Months_len), Enclosed_CJK_Letters_and_Months) != Enclosed_CJK_Letters_and_Months)
		printf ("test 'Enclosed_CJK_Letters_and_Months' failed\n");
	delete [] buffer_Enclosed_CJK_Letters_and_Months;

	YYCTYPE * buffer_CJK_Compatibility = new YYCTYPE [257];
	unsigned int buffer_CJK_Compatibility_len = encode_utf32 (chars_CJK_Compatibility, sizeof (chars_CJK_Compatibility) / sizeof (unsigned int), buffer_CJK_Compatibility);
	if (scan (reinterpret_cast<const YYCTYPE *> (buffer_CJK_Compatibility), reinterpret_cast<const YYCTYPE *> (buffer_CJK_Compatibility + buffer_CJK_Compatibility_len), CJK_Compatibility) != CJK_Compatibility)
		printf ("test 'CJK_Compatibility' failed\n");
	delete [] buffer_CJK_Compatibility;

	YYCTYPE * buffer_CJK_Unified_Ideographs_Extension_A = new YYCTYPE [6593];
	unsigned int buffer_CJK_Unified_Ideographs_Extension_A_len = encode_utf32 (chars_CJK_Unified_Ideographs_Extension_A, sizeof (chars_CJK_Unified_Ideographs_Extension_A) / sizeof (unsigned int), buffer_CJK_Unified_Ideographs_Extension_A);
	if (scan (reinterpret_cast<const YYCTYPE *> (buffer_CJK_Unified_Ideographs_Extension_A), reinterpret_cast<const YYCTYPE *> (buffer_CJK_Unified_Ideographs_Extension_A + buffer_CJK_Unified_Ideographs_Extension_A_len), CJK_Unified_Ideographs_Extension_A) != CJK_Unified_Ideographs_Extension_A)
		printf ("test 'CJK_Unified_Ideographs_Extension_A' failed\n");
	delete [] buffer_CJK_Unified_Ideographs_Extension_A;

	YYCTYPE * buffer_Yijing_Hexagram_Symbols = new YYCTYPE [65];
	unsigned int buffer_Yijing_Hexagram_Symbols_len = encode_utf32 (chars_Yijing_Hexagram_Symbols, sizeof (chars_Yijing_Hexagram_Symbols) / sizeof (unsigned int), buffer_Yijing_Hexagram_Symbols);
	if (scan (reinterpret_cast<const YYCTYPE *> (buffer_Yijing_Hexagram_Symbols), reinterpret_cast<const YYCTYPE *> (buffer_Yijing_Hexagram_Symbols + buffer_Yijing_Hexagram_Symbols_len), Yijing_Hexagram_Symbols) != Yijing_Hexagram_Symbols)
		printf ("test 'Yijing_Hexagram_Symbols' failed\n");
	delete [] buffer_Yijing_Hexagram_Symbols;

	YYCTYPE * buffer_CJK_Unified_Ideographs = new YYCTYPE [20993];
	unsigned int buffer_CJK_Unified_Ideographs_len = encode_utf32 (chars_CJK_Unified_Ideographs, sizeof (chars_CJK_Unified_Ideographs) / sizeof (unsigned int), buffer_CJK_Unified_Ideographs);
	if (scan (reinterpret_cast<const YYCTYPE *> (buffer_CJK_Unified_Ideographs), reinterpret_cast<const YYCTYPE *> (buffer_CJK_Unified_Ideographs + buffer_CJK_Unified_Ideographs_len), CJK_Unified_Ideographs) != CJK_Unified_Ideographs)
		printf ("test 'CJK_Unified_Ideographs' failed\n");
	delete [] buffer_CJK_Unified_Ideographs;

	YYCTYPE * buffer_Yi_Syllables = new YYCTYPE [1169];
	unsigned int buffer_Yi_Syllables_len = encode_utf32 (chars_Yi_Syllables, sizeof (chars_Yi_Syllables) / sizeof (unsigned int), buffer_Yi_Syllables);
	if (scan (reinterpret_cast<const YYCTYPE *> (buffer_Yi_Syllables), reinterpret_cast<const YYCTYPE *> (buffer_Yi_Syllables + buffer_Yi_Syllables_len), Yi_Syllables) != Yi_Syllables)
		printf ("test 'Yi_Syllables' failed\n");
	delete [] buffer_Yi_Syllables;

	YYCTYPE * buffer_Yi_Radicals = new YYCTYPE [65];
	unsigned int buffer_Yi_Radicals_len = encode_utf32 (chars_Yi_Radicals, sizeof (chars_Yi_Radicals) / sizeof (unsigned int), buffer_Yi_Radicals);
	if (scan (reinterpret_cast<const YYCTYPE *> (buffer_Yi_Radicals), reinterpret_cast<const YYCTYPE *> (buffer_Yi_Radicals + buffer_Yi_Radicals_len), Yi_Radicals) != Yi_Radicals)
		printf ("test 'Yi_Radicals' failed\n");
	delete [] buffer_Yi_Radicals;

	YYCTYPE * buffer_Hangul_Syllables = new YYCTYPE [11185];
	unsigned int buffer_Hangul_Syllables_len = encode_utf32 (chars_Hangul_Syllables, sizeof (chars_Hangul_Syllables) / sizeof (unsigned int), buffer_Hangul_Syllables);
	if (scan (reinterpret_cast<const YYCTYPE *> (buffer_Hangul_Syllables), reinterpret_cast<const YYCTYPE *> (buffer_Hangul_Syllables + buffer_Hangul_Syllables_len), Hangul_Syllables) != Hangul_Syllables)
		printf ("test 'Hangul_Syllables' failed\n");
	delete [] buffer_Hangul_Syllables;

	YYCTYPE * buffer_High_Surrogates = new YYCTYPE [897];
	unsigned int buffer_High_Surrogates_len = encode_utf32 (chars_High_Surrogates, sizeof (chars_High_Surrogates) / sizeof (unsigned int), buffer_High_Surrogates);
	if (scan (reinterpret_cast<const YYCTYPE *> (buffer_High_Surrogates), reinterpret_cast<const YYCTYPE *> (buffer_High_Surrogates + buffer_High_Surrogates_len), High_Surrogates) != High_Surrogates)
		printf ("test 'High_Surrogates' failed\n");
	delete [] buffer_High_Surrogates;

	YYCTYPE * buffer_High_Private_Use_Surrogates = new YYCTYPE [129];
	unsigned int buffer_High_Private_Use_Surrogates_len = encode_utf32 (chars_High_Private_Use_Surrogates, sizeof (chars_High_Private_Use_Surrogates) / sizeof (unsigned int), buffer_High_Private_Use_Surrogates);
	if (scan (reinterpret_cast<const YYCTYPE *> (buffer_High_Private_Use_Surrogates), reinterpret_cast<const YYCTYPE *> (buffer_High_Private_Use_Surrogates + buffer_High_Private_Use_Surrogates_len), High_Private_Use_Surrogates) != High_Private_Use_Surrogates)
		printf ("test 'High_Private_Use_Surrogates' failed\n");
	delete [] buffer_High_Private_Use_Surrogates;

	YYCTYPE * buffer_Low_Surrogates = new YYCTYPE [1025];
	unsigned int buffer_Low_Surrogates_len = encode_utf32 (chars_Low_Surrogates, sizeof (chars_Low_Surrogates) / sizeof (unsigned int), buffer_Low_Surrogates);
	if (scan (reinterpret_cast<const YYCTYPE *> (buffer_Low_Surrogates), reinterpret_cast<const YYCTYPE *> (buffer_Low_Surrogates + buffer_Low_Surrogates_len), Low_Surrogates) != Low_Surrogates)
		printf ("test 'Low_Surrogates' failed\n");
	delete [] buffer_Low_Surrogates;

	YYCTYPE * buffer_Private_Use_Area = new YYCTYPE [6401];
	unsigned int buffer_Private_Use_Area_len = encode_utf32 (chars_Private_Use_Area, sizeof (chars_Private_Use_Area) / sizeof (unsigned int), buffer_Private_Use_Area);
	if (scan (reinterpret_cast<const YYCTYPE *> (buffer_Private_Use_Area), reinterpret_cast<const YYCTYPE *> (buffer_Private_Use_Area + buffer_Private_Use_Area_len), Private_Use_Area) != Private_Use_Area)
		printf ("test 'Private_Use_Area' failed\n");
	delete [] buffer_Private_Use_Area;

	YYCTYPE * buffer_CJK_Compatibility_Ideographs = new YYCTYPE [513];
	unsigned int buffer_CJK_Compatibility_Ideographs_len = encode_utf32 (chars_CJK_Compatibility_Ideographs, sizeof (chars_CJK_Compatibility_Ideographs) / sizeof (unsigned int), buffer_CJK_Compatibility_Ideographs);
	if (scan (reinterpret_cast<const YYCTYPE *> (buffer_CJK_Compatibility_Ideographs), reinterpret_cast<const YYCTYPE *> (buffer_CJK_Compatibility_Ideographs + buffer_CJK_Compatibility_Ideographs_len), CJK_Compatibility_Ideographs) != CJK_Compatibility_Ideographs)
		printf ("test 'CJK_Compatibility_Ideographs' failed\n");
	delete [] buffer_CJK_Compatibility_Ideographs;

	YYCTYPE * buffer_Alphabetic_Presentation_Forms = new YYCTYPE [81];
	unsigned int buffer_Alphabetic_Presentation_Forms_len = encode_utf32 (chars_Alphabetic_Presentation_Forms, sizeof (chars_Alphabetic_Presentation_Forms) / sizeof (unsigned int), buffer_Alphabetic_Presentation_Forms);
	if (scan (reinterpret_cast<const YYCTYPE *> (buffer_Alphabetic_Presentation_Forms), reinterpret_cast<const YYCTYPE *> (buffer_Alphabetic_Presentation_Forms + buffer_Alphabetic_Presentation_Forms_len), Alphabetic_Presentation_Forms) != Alphabetic_Presentation_Forms)
		printf ("test 'Alphabetic_Presentation_Forms' failed\n");
	delete [] buffer_Alphabetic_Presentation_Forms;

	YYCTYPE * buffer_Arabic_Presentation_Forms_A = new YYCTYPE [689];
	unsigned int buffer_Arabic_Presentation_Forms_A_len = encode_utf32 (chars_Arabic_Presentation_Forms_A, sizeof (chars_Arabic_Presentation_Forms_A) / sizeof (unsigned int), buffer_Arabic_Presentation_Forms_A);
	if (scan (reinterpret_cast<const YYCTYPE *> (buffer_Arabic_Presentation_Forms_A), reinterpret_cast<const YYCTYPE *> (buffer_Arabic_Presentation_Forms_A + buffer_Arabic_Presentation_Forms_A_len), Arabic_Presentation_Forms_A) != Arabic_Presentation_Forms_A)
		printf ("test 'Arabic_Presentation_Forms_A' failed\n");
	delete [] buffer_Arabic_Presentation_Forms_A;

	YYCTYPE * buffer_Variation_Selectors = new YYCTYPE [17];
	unsigned int buffer_Variation_Selectors_len = encode_utf32 (chars_Variation_Selectors, sizeof (chars_Variation_Selectors) / sizeof (unsigned int), buffer_Variation_Selectors);
	if (scan (reinterpret_cast<const YYCTYPE *> (buffer_Variation_Selectors), reinterpret_cast<const YYCTYPE *> (buffer_Variation_Selectors + buffer_Variation_Selectors_len), Variation_Selectors) != Variation_Selectors)
		printf ("test 'Variation_Selectors' failed\n");
	delete [] buffer_Variation_Selectors;

	YYCTYPE * buffer_Combining_Half_Marks = new YYCTYPE [17];
	unsigned int buffer_Combining_Half_Marks_len = encode_utf32 (chars_Combining_Half_Marks, sizeof (chars_Combining_Half_Marks) / sizeof (unsigned int), buffer_Combining_Half_Marks);
	if (scan (reinterpret_cast<const YYCTYPE *> (buffer_Combining_Half_Marks), reinterpret_cast<const YYCTYPE *> (buffer_Combining_Half_Marks + buffer_Combining_Half_Marks_len), Combining_Half_Marks) != Combining_Half_Marks)
		printf ("test 'Combining_Half_Marks' failed\n");
	delete [] buffer_Combining_Half_Marks;

	YYCTYPE * buffer_CJK_Compatibility_Forms = new YYCTYPE [33];
	unsigned int buffer_CJK_Compatibility_Forms_len = encode_utf32 (chars_CJK_Compatibility_Forms, sizeof (chars_CJK_Compatibility_Forms) / sizeof (unsigned int), buffer_CJK_Compatibility_Forms);
	if (scan (reinterpret_cast<const YYCTYPE *> (buffer_CJK_Compatibility_Forms), reinterpret_cast<const YYCTYPE *> (buffer_CJK_Compatibility_Forms + buffer_CJK_Compatibility_Forms_len), CJK_Compatibility_Forms) != CJK_Compatibility_Forms)
		printf ("test 'CJK_Compatibility_Forms' failed\n");
	delete [] buffer_CJK_Compatibility_Forms;

	YYCTYPE * buffer_Small_Form_Variants = new YYCTYPE [33];
	unsigned int buffer_Small_Form_Variants_len = encode_utf32 (chars_Small_Form_Variants, sizeof (chars_Small_Form_Variants) / sizeof (unsigned int), buffer_Small_Form_Variants);
	if (scan (reinterpret_cast<const YYCTYPE *> (buffer_Small_Form_Variants), reinterpret_cast<const YYCTYPE *> (buffer_Small_Form_Variants + buffer_Small_Form_Variants_len), Small_Form_Variants) != Small_Form_Variants)
		printf ("test 'Small_Form_Variants' failed\n");
	delete [] buffer_Small_Form_Variants;

	YYCTYPE * buffer_Arabic_Presentation_Forms_B = new YYCTYPE [145];
	unsigned int buffer_Arabic_Presentation_Forms_B_len = encode_utf32 (chars_Arabic_Presentation_Forms_B, sizeof (chars_Arabic_Presentation_Forms_B) / sizeof (unsigned int), buffer_Arabic_Presentation_Forms_B);
	if (scan (reinterpret_cast<const YYCTYPE *> (buffer_Arabic_Presentation_Forms_B), reinterpret_cast<const YYCTYPE *> (buffer_Arabic_Presentation_Forms_B + buffer_Arabic_Presentation_Forms_B_len), Arabic_Presentation_Forms_B) != Arabic_Presentation_Forms_B)
		printf ("test 'Arabic_Presentation_Forms_B' failed\n");
	delete [] buffer_Arabic_Presentation_Forms_B;

	YYCTYPE * buffer_Halfwidth_and_Fullwidth_Forms = new YYCTYPE [241];
	unsigned int buffer_Halfwidth_and_Fullwidth_Forms_len = encode_utf32 (chars_Halfwidth_and_Fullwidth_Forms, sizeof (chars_Halfwidth_and_Fullwidth_Forms) / sizeof (unsigned int), buffer_Halfwidth_and_Fullwidth_Forms);
	if (scan (reinterpret_cast<const YYCTYPE *> (buffer_Halfwidth_and_Fullwidth_Forms), reinterpret_cast<const YYCTYPE *> (buffer_Halfwidth_and_Fullwidth_Forms + buffer_Halfwidth_and_Fullwidth_Forms_len), Halfwidth_and_Fullwidth_Forms) != Halfwidth_and_Fullwidth_Forms)
		printf ("test 'Halfwidth_and_Fullwidth_Forms' failed\n");
	delete [] buffer_Halfwidth_and_Fullwidth_Forms;

	YYCTYPE * buffer_Specials = new YYCTYPE [17];
	unsigned int buffer_Specials_len = encode_utf32 (chars_Specials, sizeof (chars_Specials) / sizeof (unsigned int), buffer_Specials);
	if (scan (reinterpret_cast<const YYCTYPE *> (buffer_Specials), reinterpret_cast<const YYCTYPE *> (buffer_Specials + buffer_Specials_len), Specials) != Specials)
		printf ("test 'Specials' failed\n");
	delete [] buffer_Specials;

	YYCTYPE * buffer_All = new YYCTYPE [61425];
	unsigned int buffer_All_len = encode_utf32 (chars_All, sizeof (chars_All) / sizeof (unsigned int), buffer_All);
	if (scan (reinterpret_cast<const YYCTYPE *> (buffer_All), reinterpret_cast<const YYCTYPE *> (buffer_All + buffer_All_len), All) != All)
		printf ("test 'All' failed\n");
	delete [] buffer_All;


	return 0;
}

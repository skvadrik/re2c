// re2c $INPUT -o $OUTPUT -u --encoding-policy fail
#include <stdint.h>
#include <stdio.h>
#define YYCTYPE uint32_t

enum Block {
	Basic_Latin,
	Latin_1_Supplement,
	Latin_Extended_A,
	Latin_Extended_B,
	IPA_Extensions,
	Spacing_Modifier_Letters,
	Combining_Diacritical_Marks,
	Greek_and_Coptic,
	Cyrillic,
	Cyrillic_Supplement,
	Armenian,
	Hebrew,
	Arabic,
	Syriac,
	Arabic_Supplement,
	Thaana,
	NKo,
	Samaritan,
	Mandaic,
	Syriac_Supplement,
	Arabic_Extended_B,
	Arabic_Extended_A,
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
	Ethiopic_Supplement,
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
	Unified_Canadian_Aboriginal_Syllabics_Extended,
	Limbu,
	Tai_Le,
	New_Tai_Lue,
	Khmer_Symbols,
	Buginese,
	Tai_Tham,
	Combining_Diacritical_Marks_Extended,
	Balinese,
	Sundanese,
	Batak,
	Lepcha,
	Ol_Chiki,
	Cyrillic_Extended_C,
	Georgian_Extended,
	Sundanese_Supplement,
	Vedic_Extensions,
	Phonetic_Extensions,
	Phonetic_Extensions_Supplement,
	Combining_Diacritical_Marks_Supplement,
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
	Glagolitic,
	Latin_Extended_C,
	Coptic,
	Georgian_Supplement,
	Tifinagh,
	Ethiopic_Extended,
	Cyrillic_Extended_A,
	Supplemental_Punctuation,
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
	CJK_Strokes,
	Katakana_Phonetic_Extensions,
	Enclosed_CJK_Letters_and_Months,
	CJK_Compatibility,
	CJK_Unified_Ideographs_Extension_A,
	Yijing_Hexagram_Symbols,
	CJK_Unified_Ideographs,
	Yi_Syllables,
	Yi_Radicals,
	Lisu,
	Vai,
	Cyrillic_Extended_B,
	Bamum,
	Modifier_Tone_Letters,
	Latin_Extended_D,
	Syloti_Nagri,
	Common_Indic_Number_Forms,
	Phags_pa,
	Saurashtra,
	Devanagari_Extended,
	Kayah_Li,
	Rejang,
	Hangul_Jamo_Extended_A,
	Javanese,
	Myanmar_Extended_B,
	Cham,
	Myanmar_Extended_A,
	Tai_Viet,
	Meetei_Mayek_Extensions,
	Ethiopic_Extended_A,
	Latin_Extended_E,
	Cherokee_Supplement,
	Meetei_Mayek,
	Hangul_Syllables,
	Hangul_Jamo_Extended_B,
	High_Surrogates,
	High_Private_Use_Surrogates,
	Low_Surrogates,
	Private_Use_Area,
	CJK_Compatibility_Ideographs,
	Alphabetic_Presentation_Forms,
	Arabic_Presentation_Forms_A,
	Variation_Selectors,
	Vertical_Forms,
	Combining_Half_Marks,
	CJK_Compatibility_Forms,
	Small_Form_Variants,
	Arabic_Presentation_Forms_B,
	Halfwidth_and_Fullwidth_Forms,
	Specials,
	Linear_B_Syllabary,
	Linear_B_Ideograms,
	Aegean_Numbers,
	Ancient_Greek_Numbers,
	Ancient_Symbols,
	Phaistos_Disc,
	Lycian,
	Carian,
	Coptic_Epact_Numbers,
	Old_Italic,
	Gothic,
	Old_Permic,
	Ugaritic,
	Old_Persian,
	Deseret,
	Shavian,
	Osmanya,
	Osage,
	Elbasan,
	Caucasian_Albanian,
	Vithkuqi,
	Linear_A,
	Latin_Extended_F,
	Cypriot_Syllabary,
	Imperial_Aramaic,
	Palmyrene,
	Nabataean,
	Hatran,
	Phoenician,
	Lydian,
	Meroitic_Hieroglyphs,
	Meroitic_Cursive,
	Kharoshthi,
	Old_South_Arabian,
	Old_North_Arabian,
	Manichaean,
	Avestan,
	Inscriptional_Parthian,
	Inscriptional_Pahlavi,
	Psalter_Pahlavi,
	Old_Turkic,
	Old_Hungarian,
	Hanifi_Rohingya,
	Rumi_Numeral_Symbols,
	Yezidi,
	Arabic_Extended_C,
	Old_Sogdian,
	Sogdian,
	Old_Uyghur,
	Chorasmian,
	Elymaic,
	Brahmi,
	Kaithi,
	Sora_Sompeng,
	Chakma,
	Mahajani,
	Sharada,
	Sinhala_Archaic_Numbers,
	Khojki,
	Multani,
	Khudawadi,
	Grantha,
	Newa,
	Tirhuta,
	Siddham,
	Modi,
	Mongolian_Supplement,
	Takri,
	Ahom,
	Dogra,
	Warang_Citi,
	Dives_Akuru,
	Nandinagari,
	Zanabazar_Square,
	Soyombo,
	Unified_Canadian_Aboriginal_Syllabics_Extended_A,
	Pau_Cin_Hau,
	Devanagari_Extended_A,
	Bhaiksuki,
	Marchen,
	Masaram_Gondi,
	Gunjala_Gondi,
	Makasar,
	Kawi,
	Lisu_Supplement,
	Tamil_Supplement,
	Cuneiform,
	Cuneiform_Numbers_and_Punctuation,
	Early_Dynastic_Cuneiform,
	Cypro_Minoan,
	Egyptian_Hieroglyphs,
	Egyptian_Hieroglyph_Format_Controls,
	Anatolian_Hieroglyphs,
	Bamum_Supplement,
	Mro,
	Tangsa,
	Bassa_Vah,
	Pahawh_Hmong,
	Medefaidrin,
	Miao,
	Ideographic_Symbols_and_Punctuation,
	Tangut,
	Tangut_Components,
	Khitan_Small_Script,
	Tangut_Supplement,
	Kana_Extended_B,
	Kana_Supplement,
	Kana_Extended_A,
	Small_Kana_Extension,
	Nushu,
	Duployan,
	Shorthand_Format_Controls,
	Znamenny_Musical_Notation,
	Byzantine_Musical_Symbols,
	Musical_Symbols,
	Ancient_Greek_Musical_Notation,
	Kaktovik_Numerals,
	Mayan_Numerals,
	Tai_Xuan_Jing_Symbols,
	Counting_Rod_Numerals,
	Mathematical_Alphanumeric_Symbols,
	Sutton_SignWriting,
	Latin_Extended_G,
	Glagolitic_Supplement,
	Cyrillic_Extended_D,
	Nyiakeng_Puachue_Hmong,
	Toto,
	Wancho,
	Nag_Mundari,
	Ethiopic_Extended_B,
	Mende_Kikakui,
	Adlam,
	Indic_Siyaq_Numbers,
	Ottoman_Siyaq_Numbers,
	Arabic_Mathematical_Alphabetic_Symbols,
	Mahjong_Tiles,
	Domino_Tiles,
	Playing_Cards,
	Enclosed_Alphanumeric_Supplement,
	Enclosed_Ideographic_Supplement,
	Miscellaneous_Symbols_and_Pictographs,
	Emoticons,
	Ornamental_Dingbats,
	Transport_and_Map_Symbols,
	Alchemical_Symbols,
	Geometric_Shapes_Extended,
	Supplemental_Arrows_C,
	Supplemental_Symbols_and_Pictographs,
	Chess_Symbols,
	Symbols_and_Pictographs_Extended_A,
	Symbols_for_Legacy_Computing,
	CJK_Unified_Ideographs_Extension_B,
	CJK_Unified_Ideographs_Extension_C,
	CJK_Unified_Ideographs_Extension_D,
	CJK_Unified_Ideographs_Extension_E,
	CJK_Unified_Ideographs_Extension_F,
	CJK_Unified_Ideographs_Extension_I,
	CJK_Compatibility_Ideographs_Supplement,
	CJK_Unified_Ideographs_Extension_G,
	CJK_Unified_Ideographs_Extension_H,
	Tags,
	Variation_Selectors_Supplement,
	Supplementary_Private_Use_Area_A,
	Supplementary_Private_Use_Area_B,
	Error
};

Block scan(const YYCTYPE* start, const YYCTYPE* const limit, Block blk) {
	__attribute__((unused)) const YYCTYPE* YYMARKER;
#define YYCURSOR start
	switch (blk) {
		case Basic_Latin: goto Basic_Latin;
		case Latin_1_Supplement: goto Latin_1_Supplement;
		case Latin_Extended_A: goto Latin_Extended_A;
		case Latin_Extended_B: goto Latin_Extended_B;
		case IPA_Extensions: goto IPA_Extensions;
		case Spacing_Modifier_Letters: goto Spacing_Modifier_Letters;
		case Combining_Diacritical_Marks: goto Combining_Diacritical_Marks;
		case Greek_and_Coptic: goto Greek_and_Coptic;
		case Cyrillic: goto Cyrillic;
		case Cyrillic_Supplement: goto Cyrillic_Supplement;
		case Armenian: goto Armenian;
		case Hebrew: goto Hebrew;
		case Arabic: goto Arabic;
		case Syriac: goto Syriac;
		case Arabic_Supplement: goto Arabic_Supplement;
		case Thaana: goto Thaana;
		case NKo: goto NKo;
		case Samaritan: goto Samaritan;
		case Mandaic: goto Mandaic;
		case Syriac_Supplement: goto Syriac_Supplement;
		case Arabic_Extended_B: goto Arabic_Extended_B;
		case Arabic_Extended_A: goto Arabic_Extended_A;
		case Devanagari: goto Devanagari;
		case Bengali: goto Bengali;
		case Gurmukhi: goto Gurmukhi;
		case Gujarati: goto Gujarati;
		case Oriya: goto Oriya;
		case Tamil: goto Tamil;
		case Telugu: goto Telugu;
		case Kannada: goto Kannada;
		case Malayalam: goto Malayalam;
		case Sinhala: goto Sinhala;
		case Thai: goto Thai;
		case Lao: goto Lao;
		case Tibetan: goto Tibetan;
		case Myanmar: goto Myanmar;
		case Georgian: goto Georgian;
		case Hangul_Jamo: goto Hangul_Jamo;
		case Ethiopic: goto Ethiopic;
		case Ethiopic_Supplement: goto Ethiopic_Supplement;
		case Cherokee: goto Cherokee;
		case Unified_Canadian_Aboriginal_Syllabics: goto Unified_Canadian_Aboriginal_Syllabics;
		case Ogham: goto Ogham;
		case Runic: goto Runic;
		case Tagalog: goto Tagalog;
		case Hanunoo: goto Hanunoo;
		case Buhid: goto Buhid;
		case Tagbanwa: goto Tagbanwa;
		case Khmer: goto Khmer;
		case Mongolian: goto Mongolian;
		case Unified_Canadian_Aboriginal_Syllabics_Extended: goto Unified_Canadian_Aboriginal_Syllabics_Extended;
		case Limbu: goto Limbu;
		case Tai_Le: goto Tai_Le;
		case New_Tai_Lue: goto New_Tai_Lue;
		case Khmer_Symbols: goto Khmer_Symbols;
		case Buginese: goto Buginese;
		case Tai_Tham: goto Tai_Tham;
		case Combining_Diacritical_Marks_Extended: goto Combining_Diacritical_Marks_Extended;
		case Balinese: goto Balinese;
		case Sundanese: goto Sundanese;
		case Batak: goto Batak;
		case Lepcha: goto Lepcha;
		case Ol_Chiki: goto Ol_Chiki;
		case Cyrillic_Extended_C: goto Cyrillic_Extended_C;
		case Georgian_Extended: goto Georgian_Extended;
		case Sundanese_Supplement: goto Sundanese_Supplement;
		case Vedic_Extensions: goto Vedic_Extensions;
		case Phonetic_Extensions: goto Phonetic_Extensions;
		case Phonetic_Extensions_Supplement: goto Phonetic_Extensions_Supplement;
		case Combining_Diacritical_Marks_Supplement: goto Combining_Diacritical_Marks_Supplement;
		case Latin_Extended_Additional: goto Latin_Extended_Additional;
		case Greek_Extended: goto Greek_Extended;
		case General_Punctuation: goto General_Punctuation;
		case Superscripts_and_Subscripts: goto Superscripts_and_Subscripts;
		case Currency_Symbols: goto Currency_Symbols;
		case Combining_Diacritical_Marks_for_Symbols: goto Combining_Diacritical_Marks_for_Symbols;
		case Letterlike_Symbols: goto Letterlike_Symbols;
		case Number_Forms: goto Number_Forms;
		case Arrows: goto Arrows;
		case Mathematical_Operators: goto Mathematical_Operators;
		case Miscellaneous_Technical: goto Miscellaneous_Technical;
		case Control_Pictures: goto Control_Pictures;
		case Optical_Character_Recognition: goto Optical_Character_Recognition;
		case Enclosed_Alphanumerics: goto Enclosed_Alphanumerics;
		case Box_Drawing: goto Box_Drawing;
		case Block_Elements: goto Block_Elements;
		case Geometric_Shapes: goto Geometric_Shapes;
		case Miscellaneous_Symbols: goto Miscellaneous_Symbols;
		case Dingbats: goto Dingbats;
		case Miscellaneous_Mathematical_Symbols_A: goto Miscellaneous_Mathematical_Symbols_A;
		case Supplemental_Arrows_A: goto Supplemental_Arrows_A;
		case Braille_Patterns: goto Braille_Patterns;
		case Supplemental_Arrows_B: goto Supplemental_Arrows_B;
		case Miscellaneous_Mathematical_Symbols_B: goto Miscellaneous_Mathematical_Symbols_B;
		case Supplemental_Mathematical_Operators: goto Supplemental_Mathematical_Operators;
		case Miscellaneous_Symbols_and_Arrows: goto Miscellaneous_Symbols_and_Arrows;
		case Glagolitic: goto Glagolitic;
		case Latin_Extended_C: goto Latin_Extended_C;
		case Coptic: goto Coptic;
		case Georgian_Supplement: goto Georgian_Supplement;
		case Tifinagh: goto Tifinagh;
		case Ethiopic_Extended: goto Ethiopic_Extended;
		case Cyrillic_Extended_A: goto Cyrillic_Extended_A;
		case Supplemental_Punctuation: goto Supplemental_Punctuation;
		case CJK_Radicals_Supplement: goto CJK_Radicals_Supplement;
		case Kangxi_Radicals: goto Kangxi_Radicals;
		case Ideographic_Description_Characters: goto Ideographic_Description_Characters;
		case CJK_Symbols_and_Punctuation: goto CJK_Symbols_and_Punctuation;
		case Hiragana: goto Hiragana;
		case Katakana: goto Katakana;
		case Bopomofo: goto Bopomofo;
		case Hangul_Compatibility_Jamo: goto Hangul_Compatibility_Jamo;
		case Kanbun: goto Kanbun;
		case Bopomofo_Extended: goto Bopomofo_Extended;
		case CJK_Strokes: goto CJK_Strokes;
		case Katakana_Phonetic_Extensions: goto Katakana_Phonetic_Extensions;
		case Enclosed_CJK_Letters_and_Months: goto Enclosed_CJK_Letters_and_Months;
		case CJK_Compatibility: goto CJK_Compatibility;
		case CJK_Unified_Ideographs_Extension_A: goto CJK_Unified_Ideographs_Extension_A;
		case Yijing_Hexagram_Symbols: goto Yijing_Hexagram_Symbols;
		case CJK_Unified_Ideographs: goto CJK_Unified_Ideographs;
		case Yi_Syllables: goto Yi_Syllables;
		case Yi_Radicals: goto Yi_Radicals;
		case Lisu: goto Lisu;
		case Vai: goto Vai;
		case Cyrillic_Extended_B: goto Cyrillic_Extended_B;
		case Bamum: goto Bamum;
		case Modifier_Tone_Letters: goto Modifier_Tone_Letters;
		case Latin_Extended_D: goto Latin_Extended_D;
		case Syloti_Nagri: goto Syloti_Nagri;
		case Common_Indic_Number_Forms: goto Common_Indic_Number_Forms;
		case Phags_pa: goto Phags_pa;
		case Saurashtra: goto Saurashtra;
		case Devanagari_Extended: goto Devanagari_Extended;
		case Kayah_Li: goto Kayah_Li;
		case Rejang: goto Rejang;
		case Hangul_Jamo_Extended_A: goto Hangul_Jamo_Extended_A;
		case Javanese: goto Javanese;
		case Myanmar_Extended_B: goto Myanmar_Extended_B;
		case Cham: goto Cham;
		case Myanmar_Extended_A: goto Myanmar_Extended_A;
		case Tai_Viet: goto Tai_Viet;
		case Meetei_Mayek_Extensions: goto Meetei_Mayek_Extensions;
		case Ethiopic_Extended_A: goto Ethiopic_Extended_A;
		case Latin_Extended_E: goto Latin_Extended_E;
		case Cherokee_Supplement: goto Cherokee_Supplement;
		case Meetei_Mayek: goto Meetei_Mayek;
		case Hangul_Syllables: goto Hangul_Syllables;
		case Hangul_Jamo_Extended_B: goto Hangul_Jamo_Extended_B;
		case High_Surrogates: goto High_Surrogates;
		case High_Private_Use_Surrogates: goto High_Private_Use_Surrogates;
		case Low_Surrogates: goto Low_Surrogates;
		case Private_Use_Area: goto Private_Use_Area;
		case CJK_Compatibility_Ideographs: goto CJK_Compatibility_Ideographs;
		case Alphabetic_Presentation_Forms: goto Alphabetic_Presentation_Forms;
		case Arabic_Presentation_Forms_A: goto Arabic_Presentation_Forms_A;
		case Variation_Selectors: goto Variation_Selectors;
		case Vertical_Forms: goto Vertical_Forms;
		case Combining_Half_Marks: goto Combining_Half_Marks;
		case CJK_Compatibility_Forms: goto CJK_Compatibility_Forms;
		case Small_Form_Variants: goto Small_Form_Variants;
		case Arabic_Presentation_Forms_B: goto Arabic_Presentation_Forms_B;
		case Halfwidth_and_Fullwidth_Forms: goto Halfwidth_and_Fullwidth_Forms;
		case Specials: goto Specials;
		case Linear_B_Syllabary: goto Linear_B_Syllabary;
		case Linear_B_Ideograms: goto Linear_B_Ideograms;
		case Aegean_Numbers: goto Aegean_Numbers;
		case Ancient_Greek_Numbers: goto Ancient_Greek_Numbers;
		case Ancient_Symbols: goto Ancient_Symbols;
		case Phaistos_Disc: goto Phaistos_Disc;
		case Lycian: goto Lycian;
		case Carian: goto Carian;
		case Coptic_Epact_Numbers: goto Coptic_Epact_Numbers;
		case Old_Italic: goto Old_Italic;
		case Gothic: goto Gothic;
		case Old_Permic: goto Old_Permic;
		case Ugaritic: goto Ugaritic;
		case Old_Persian: goto Old_Persian;
		case Deseret: goto Deseret;
		case Shavian: goto Shavian;
		case Osmanya: goto Osmanya;
		case Osage: goto Osage;
		case Elbasan: goto Elbasan;
		case Caucasian_Albanian: goto Caucasian_Albanian;
		case Vithkuqi: goto Vithkuqi;
		case Linear_A: goto Linear_A;
		case Latin_Extended_F: goto Latin_Extended_F;
		case Cypriot_Syllabary: goto Cypriot_Syllabary;
		case Imperial_Aramaic: goto Imperial_Aramaic;
		case Palmyrene: goto Palmyrene;
		case Nabataean: goto Nabataean;
		case Hatran: goto Hatran;
		case Phoenician: goto Phoenician;
		case Lydian: goto Lydian;
		case Meroitic_Hieroglyphs: goto Meroitic_Hieroglyphs;
		case Meroitic_Cursive: goto Meroitic_Cursive;
		case Kharoshthi: goto Kharoshthi;
		case Old_South_Arabian: goto Old_South_Arabian;
		case Old_North_Arabian: goto Old_North_Arabian;
		case Manichaean: goto Manichaean;
		case Avestan: goto Avestan;
		case Inscriptional_Parthian: goto Inscriptional_Parthian;
		case Inscriptional_Pahlavi: goto Inscriptional_Pahlavi;
		case Psalter_Pahlavi: goto Psalter_Pahlavi;
		case Old_Turkic: goto Old_Turkic;
		case Old_Hungarian: goto Old_Hungarian;
		case Hanifi_Rohingya: goto Hanifi_Rohingya;
		case Rumi_Numeral_Symbols: goto Rumi_Numeral_Symbols;
		case Yezidi: goto Yezidi;
		case Arabic_Extended_C: goto Arabic_Extended_C;
		case Old_Sogdian: goto Old_Sogdian;
		case Sogdian: goto Sogdian;
		case Old_Uyghur: goto Old_Uyghur;
		case Chorasmian: goto Chorasmian;
		case Elymaic: goto Elymaic;
		case Brahmi: goto Brahmi;
		case Kaithi: goto Kaithi;
		case Sora_Sompeng: goto Sora_Sompeng;
		case Chakma: goto Chakma;
		case Mahajani: goto Mahajani;
		case Sharada: goto Sharada;
		case Sinhala_Archaic_Numbers: goto Sinhala_Archaic_Numbers;
		case Khojki: goto Khojki;
		case Multani: goto Multani;
		case Khudawadi: goto Khudawadi;
		case Grantha: goto Grantha;
		case Newa: goto Newa;
		case Tirhuta: goto Tirhuta;
		case Siddham: goto Siddham;
		case Modi: goto Modi;
		case Mongolian_Supplement: goto Mongolian_Supplement;
		case Takri: goto Takri;
		case Ahom: goto Ahom;
		case Dogra: goto Dogra;
		case Warang_Citi: goto Warang_Citi;
		case Dives_Akuru: goto Dives_Akuru;
		case Nandinagari: goto Nandinagari;
		case Zanabazar_Square: goto Zanabazar_Square;
		case Soyombo: goto Soyombo;
		case Unified_Canadian_Aboriginal_Syllabics_Extended_A: goto Unified_Canadian_Aboriginal_Syllabics_Extended_A;
		case Pau_Cin_Hau: goto Pau_Cin_Hau;
		case Devanagari_Extended_A: goto Devanagari_Extended_A;
		case Bhaiksuki: goto Bhaiksuki;
		case Marchen: goto Marchen;
		case Masaram_Gondi: goto Masaram_Gondi;
		case Gunjala_Gondi: goto Gunjala_Gondi;
		case Makasar: goto Makasar;
		case Kawi: goto Kawi;
		case Lisu_Supplement: goto Lisu_Supplement;
		case Tamil_Supplement: goto Tamil_Supplement;
		case Cuneiform: goto Cuneiform;
		case Cuneiform_Numbers_and_Punctuation: goto Cuneiform_Numbers_and_Punctuation;
		case Early_Dynastic_Cuneiform: goto Early_Dynastic_Cuneiform;
		case Cypro_Minoan: goto Cypro_Minoan;
		case Egyptian_Hieroglyphs: goto Egyptian_Hieroglyphs;
		case Egyptian_Hieroglyph_Format_Controls: goto Egyptian_Hieroglyph_Format_Controls;
		case Anatolian_Hieroglyphs: goto Anatolian_Hieroglyphs;
		case Bamum_Supplement: goto Bamum_Supplement;
		case Mro: goto Mro;
		case Tangsa: goto Tangsa;
		case Bassa_Vah: goto Bassa_Vah;
		case Pahawh_Hmong: goto Pahawh_Hmong;
		case Medefaidrin: goto Medefaidrin;
		case Miao: goto Miao;
		case Ideographic_Symbols_and_Punctuation: goto Ideographic_Symbols_and_Punctuation;
		case Tangut: goto Tangut;
		case Tangut_Components: goto Tangut_Components;
		case Khitan_Small_Script: goto Khitan_Small_Script;
		case Tangut_Supplement: goto Tangut_Supplement;
		case Kana_Extended_B: goto Kana_Extended_B;
		case Kana_Supplement: goto Kana_Supplement;
		case Kana_Extended_A: goto Kana_Extended_A;
		case Small_Kana_Extension: goto Small_Kana_Extension;
		case Nushu: goto Nushu;
		case Duployan: goto Duployan;
		case Shorthand_Format_Controls: goto Shorthand_Format_Controls;
		case Znamenny_Musical_Notation: goto Znamenny_Musical_Notation;
		case Byzantine_Musical_Symbols: goto Byzantine_Musical_Symbols;
		case Musical_Symbols: goto Musical_Symbols;
		case Ancient_Greek_Musical_Notation: goto Ancient_Greek_Musical_Notation;
		case Kaktovik_Numerals: goto Kaktovik_Numerals;
		case Mayan_Numerals: goto Mayan_Numerals;
		case Tai_Xuan_Jing_Symbols: goto Tai_Xuan_Jing_Symbols;
		case Counting_Rod_Numerals: goto Counting_Rod_Numerals;
		case Mathematical_Alphanumeric_Symbols: goto Mathematical_Alphanumeric_Symbols;
		case Sutton_SignWriting: goto Sutton_SignWriting;
		case Latin_Extended_G: goto Latin_Extended_G;
		case Glagolitic_Supplement: goto Glagolitic_Supplement;
		case Cyrillic_Extended_D: goto Cyrillic_Extended_D;
		case Nyiakeng_Puachue_Hmong: goto Nyiakeng_Puachue_Hmong;
		case Toto: goto Toto;
		case Wancho: goto Wancho;
		case Nag_Mundari: goto Nag_Mundari;
		case Ethiopic_Extended_B: goto Ethiopic_Extended_B;
		case Mende_Kikakui: goto Mende_Kikakui;
		case Adlam: goto Adlam;
		case Indic_Siyaq_Numbers: goto Indic_Siyaq_Numbers;
		case Ottoman_Siyaq_Numbers: goto Ottoman_Siyaq_Numbers;
		case Arabic_Mathematical_Alphabetic_Symbols: goto Arabic_Mathematical_Alphabetic_Symbols;
		case Mahjong_Tiles: goto Mahjong_Tiles;
		case Domino_Tiles: goto Domino_Tiles;
		case Playing_Cards: goto Playing_Cards;
		case Enclosed_Alphanumeric_Supplement: goto Enclosed_Alphanumeric_Supplement;
		case Enclosed_Ideographic_Supplement: goto Enclosed_Ideographic_Supplement;
		case Miscellaneous_Symbols_and_Pictographs: goto Miscellaneous_Symbols_and_Pictographs;
		case Emoticons: goto Emoticons;
		case Ornamental_Dingbats: goto Ornamental_Dingbats;
		case Transport_and_Map_Symbols: goto Transport_and_Map_Symbols;
		case Alchemical_Symbols: goto Alchemical_Symbols;
		case Geometric_Shapes_Extended: goto Geometric_Shapes_Extended;
		case Supplemental_Arrows_C: goto Supplemental_Arrows_C;
		case Supplemental_Symbols_and_Pictographs: goto Supplemental_Symbols_and_Pictographs;
		case Chess_Symbols: goto Chess_Symbols;
		case Symbols_and_Pictographs_Extended_A: goto Symbols_and_Pictographs_Extended_A;
		case Symbols_for_Legacy_Computing: goto Symbols_for_Legacy_Computing;
		case CJK_Unified_Ideographs_Extension_B: goto CJK_Unified_Ideographs_Extension_B;
		case CJK_Unified_Ideographs_Extension_C: goto CJK_Unified_Ideographs_Extension_C;
		case CJK_Unified_Ideographs_Extension_D: goto CJK_Unified_Ideographs_Extension_D;
		case CJK_Unified_Ideographs_Extension_E: goto CJK_Unified_Ideographs_Extension_E;
		case CJK_Unified_Ideographs_Extension_F: goto CJK_Unified_Ideographs_Extension_F;
		case CJK_Unified_Ideographs_Extension_I: goto CJK_Unified_Ideographs_Extension_I;
		case CJK_Compatibility_Ideographs_Supplement: goto CJK_Compatibility_Ideographs_Supplement;
		case CJK_Unified_Ideographs_Extension_G: goto CJK_Unified_Ideographs_Extension_G;
		case CJK_Unified_Ideographs_Extension_H: goto CJK_Unified_Ideographs_Extension_H;
		case Tags: goto Tags;
		case Variation_Selectors_Supplement: goto Variation_Selectors_Supplement;
		case Supplementary_Private_Use_Area_A: goto Supplementary_Private_Use_Area_A;
		case Supplementary_Private_Use_Area_B: goto Supplementary_Private_Use_Area_B;
		default: return Error;
	}
/*!re2c
Basic_Latin = [\x00-\x7f];
Latin_1_Supplement = [\x80-\xff];
Latin_Extended_A = [\u0100-\u017f];
Latin_Extended_B = [\u0180-\u024f];
IPA_Extensions = [\u0250-\u02af];
Spacing_Modifier_Letters = [\u02b0-\u02ff];
Combining_Diacritical_Marks = [\u0300-\u036f];
Greek_and_Coptic = [\u0370-\u03ff];
Cyrillic = [\u0400-\u04ff];
Cyrillic_Supplement = [\u0500-\u052f];
Armenian = [\u0530-\u058f];
Hebrew = [\u0590-\u05ff];
Arabic = [\u0600-\u06ff];
Syriac = [\u0700-\u074f];
Arabic_Supplement = [\u0750-\u077f];
Thaana = [\u0780-\u07bf];
NKo = [\u07c0-\u07ff];
Samaritan = [\u0800-\u083f];
Mandaic = [\u0840-\u085f];
Syriac_Supplement = [\u0860-\u086f];
Arabic_Extended_B = [\u0870-\u089f];
Arabic_Extended_A = [\u08a0-\u08ff];
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
Ethiopic_Supplement = [\u1380-\u139f];
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
Unified_Canadian_Aboriginal_Syllabics_Extended = [\u18b0-\u18ff];
Limbu = [\u1900-\u194f];
Tai_Le = [\u1950-\u197f];
New_Tai_Lue = [\u1980-\u19df];
Khmer_Symbols = [\u19e0-\u19ff];
Buginese = [\u1a00-\u1a1f];
Tai_Tham = [\u1a20-\u1aaf];
Combining_Diacritical_Marks_Extended = [\u1ab0-\u1aff];
Balinese = [\u1b00-\u1b7f];
Sundanese = [\u1b80-\u1bbf];
Batak = [\u1bc0-\u1bff];
Lepcha = [\u1c00-\u1c4f];
Ol_Chiki = [\u1c50-\u1c7f];
Cyrillic_Extended_C = [\u1c80-\u1c8f];
Georgian_Extended = [\u1c90-\u1cbf];
Sundanese_Supplement = [\u1cc0-\u1ccf];
Vedic_Extensions = [\u1cd0-\u1cff];
Phonetic_Extensions = [\u1d00-\u1d7f];
Phonetic_Extensions_Supplement = [\u1d80-\u1dbf];
Combining_Diacritical_Marks_Supplement = [\u1dc0-\u1dff];
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
Glagolitic = [\u2c00-\u2c5f];
Latin_Extended_C = [\u2c60-\u2c7f];
Coptic = [\u2c80-\u2cff];
Georgian_Supplement = [\u2d00-\u2d2f];
Tifinagh = [\u2d30-\u2d7f];
Ethiopic_Extended = [\u2d80-\u2ddf];
Cyrillic_Extended_A = [\u2de0-\u2dff];
Supplemental_Punctuation = [\u2e00-\u2e7f];
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
CJK_Strokes = [\u31c0-\u31ef];
Katakana_Phonetic_Extensions = [\u31f0-\u31ff];
Enclosed_CJK_Letters_and_Months = [\u3200-\u32ff];
CJK_Compatibility = [\u3300-\u33ff];
CJK_Unified_Ideographs_Extension_A = [\u3400-\u4dbf];
Yijing_Hexagram_Symbols = [\u4dc0-\u4dff];
CJK_Unified_Ideographs = [\u4e00-\u9fff];
Yi_Syllables = [\ua000-\ua48f];
Yi_Radicals = [\ua490-\ua4cf];
Lisu = [\ua4d0-\ua4ff];
Vai = [\ua500-\ua63f];
Cyrillic_Extended_B = [\ua640-\ua69f];
Bamum = [\ua6a0-\ua6ff];
Modifier_Tone_Letters = [\ua700-\ua71f];
Latin_Extended_D = [\ua720-\ua7ff];
Syloti_Nagri = [\ua800-\ua82f];
Common_Indic_Number_Forms = [\ua830-\ua83f];
Phags_pa = [\ua840-\ua87f];
Saurashtra = [\ua880-\ua8df];
Devanagari_Extended = [\ua8e0-\ua8ff];
Kayah_Li = [\ua900-\ua92f];
Rejang = [\ua930-\ua95f];
Hangul_Jamo_Extended_A = [\ua960-\ua97f];
Javanese = [\ua980-\ua9df];
Myanmar_Extended_B = [\ua9e0-\ua9ff];
Cham = [\uaa00-\uaa5f];
Myanmar_Extended_A = [\uaa60-\uaa7f];
Tai_Viet = [\uaa80-\uaadf];
Meetei_Mayek_Extensions = [\uaae0-\uaaff];
Ethiopic_Extended_A = [\uab00-\uab2f];
Latin_Extended_E = [\uab30-\uab6f];
Cherokee_Supplement = [\uab70-\uabbf];
Meetei_Mayek = [\uabc0-\uabff];
Hangul_Syllables = [\uac00-\ud7af];
Hangul_Jamo_Extended_B = [\ud7b0-\ud7ff];
High_Surrogates = [\ud800-\udb7f];
High_Private_Use_Surrogates = [\udb80-\udbff];
Low_Surrogates = [\udc00-\udfff];
Private_Use_Area = [\ue000-\uf8ff];
CJK_Compatibility_Ideographs = [\uf900-\ufaff];
Alphabetic_Presentation_Forms = [\ufb00-\ufb4f];
Arabic_Presentation_Forms_A = [\ufb50-\ufdff];
Variation_Selectors = [\ufe00-\ufe0f];
Vertical_Forms = [\ufe10-\ufe1f];
Combining_Half_Marks = [\ufe20-\ufe2f];
CJK_Compatibility_Forms = [\ufe30-\ufe4f];
Small_Form_Variants = [\ufe50-\ufe6f];
Arabic_Presentation_Forms_B = [\ufe70-\ufeff];
Halfwidth_and_Fullwidth_Forms = [\uff00-\uffef];
Specials = [\ufff0-\uffff];
Linear_B_Syllabary = [\U00010000-\U0001007f];
Linear_B_Ideograms = [\U00010080-\U000100ff];
Aegean_Numbers = [\U00010100-\U0001013f];
Ancient_Greek_Numbers = [\U00010140-\U0001018f];
Ancient_Symbols = [\U00010190-\U000101cf];
Phaistos_Disc = [\U000101d0-\U000101ff];
Lycian = [\U00010280-\U0001029f];
Carian = [\U000102a0-\U000102df];
Coptic_Epact_Numbers = [\U000102e0-\U000102ff];
Old_Italic = [\U00010300-\U0001032f];
Gothic = [\U00010330-\U0001034f];
Old_Permic = [\U00010350-\U0001037f];
Ugaritic = [\U00010380-\U0001039f];
Old_Persian = [\U000103a0-\U000103df];
Deseret = [\U00010400-\U0001044f];
Shavian = [\U00010450-\U0001047f];
Osmanya = [\U00010480-\U000104af];
Osage = [\U000104b0-\U000104ff];
Elbasan = [\U00010500-\U0001052f];
Caucasian_Albanian = [\U00010530-\U0001056f];
Vithkuqi = [\U00010570-\U000105bf];
Linear_A = [\U00010600-\U0001077f];
Latin_Extended_F = [\U00010780-\U000107bf];
Cypriot_Syllabary = [\U00010800-\U0001083f];
Imperial_Aramaic = [\U00010840-\U0001085f];
Palmyrene = [\U00010860-\U0001087f];
Nabataean = [\U00010880-\U000108af];
Hatran = [\U000108e0-\U000108ff];
Phoenician = [\U00010900-\U0001091f];
Lydian = [\U00010920-\U0001093f];
Meroitic_Hieroglyphs = [\U00010980-\U0001099f];
Meroitic_Cursive = [\U000109a0-\U000109ff];
Kharoshthi = [\U00010a00-\U00010a5f];
Old_South_Arabian = [\U00010a60-\U00010a7f];
Old_North_Arabian = [\U00010a80-\U00010a9f];
Manichaean = [\U00010ac0-\U00010aff];
Avestan = [\U00010b00-\U00010b3f];
Inscriptional_Parthian = [\U00010b40-\U00010b5f];
Inscriptional_Pahlavi = [\U00010b60-\U00010b7f];
Psalter_Pahlavi = [\U00010b80-\U00010baf];
Old_Turkic = [\U00010c00-\U00010c4f];
Old_Hungarian = [\U00010c80-\U00010cff];
Hanifi_Rohingya = [\U00010d00-\U00010d3f];
Rumi_Numeral_Symbols = [\U00010e60-\U00010e7f];
Yezidi = [\U00010e80-\U00010ebf];
Arabic_Extended_C = [\U00010ec0-\U00010eff];
Old_Sogdian = [\U00010f00-\U00010f2f];
Sogdian = [\U00010f30-\U00010f6f];
Old_Uyghur = [\U00010f70-\U00010faf];
Chorasmian = [\U00010fb0-\U00010fdf];
Elymaic = [\U00010fe0-\U00010fff];
Brahmi = [\U00011000-\U0001107f];
Kaithi = [\U00011080-\U000110cf];
Sora_Sompeng = [\U000110d0-\U000110ff];
Chakma = [\U00011100-\U0001114f];
Mahajani = [\U00011150-\U0001117f];
Sharada = [\U00011180-\U000111df];
Sinhala_Archaic_Numbers = [\U000111e0-\U000111ff];
Khojki = [\U00011200-\U0001124f];
Multani = [\U00011280-\U000112af];
Khudawadi = [\U000112b0-\U000112ff];
Grantha = [\U00011300-\U0001137f];
Newa = [\U00011400-\U0001147f];
Tirhuta = [\U00011480-\U000114df];
Siddham = [\U00011580-\U000115ff];
Modi = [\U00011600-\U0001165f];
Mongolian_Supplement = [\U00011660-\U0001167f];
Takri = [\U00011680-\U000116cf];
Ahom = [\U00011700-\U0001174f];
Dogra = [\U00011800-\U0001184f];
Warang_Citi = [\U000118a0-\U000118ff];
Dives_Akuru = [\U00011900-\U0001195f];
Nandinagari = [\U000119a0-\U000119ff];
Zanabazar_Square = [\U00011a00-\U00011a4f];
Soyombo = [\U00011a50-\U00011aaf];
Unified_Canadian_Aboriginal_Syllabics_Extended_A = [\U00011ab0-\U00011abf];
Pau_Cin_Hau = [\U00011ac0-\U00011aff];
Devanagari_Extended_A = [\U00011b00-\U00011b5f];
Bhaiksuki = [\U00011c00-\U00011c6f];
Marchen = [\U00011c70-\U00011cbf];
Masaram_Gondi = [\U00011d00-\U00011d5f];
Gunjala_Gondi = [\U00011d60-\U00011daf];
Makasar = [\U00011ee0-\U00011eff];
Kawi = [\U00011f00-\U00011f5f];
Lisu_Supplement = [\U00011fb0-\U00011fbf];
Tamil_Supplement = [\U00011fc0-\U00011fff];
Cuneiform = [\U00012000-\U000123ff];
Cuneiform_Numbers_and_Punctuation = [\U00012400-\U0001247f];
Early_Dynastic_Cuneiform = [\U00012480-\U0001254f];
Cypro_Minoan = [\U00012f90-\U00012fff];
Egyptian_Hieroglyphs = [\U00013000-\U0001342f];
Egyptian_Hieroglyph_Format_Controls = [\U00013430-\U0001345f];
Anatolian_Hieroglyphs = [\U00014400-\U0001467f];
Bamum_Supplement = [\U00016800-\U00016a3f];
Mro = [\U00016a40-\U00016a6f];
Tangsa = [\U00016a70-\U00016acf];
Bassa_Vah = [\U00016ad0-\U00016aff];
Pahawh_Hmong = [\U00016b00-\U00016b8f];
Medefaidrin = [\U00016e40-\U00016e9f];
Miao = [\U00016f00-\U00016f9f];
Ideographic_Symbols_and_Punctuation = [\U00016fe0-\U00016fff];
Tangut = [\U00017000-\U000187ff];
Tangut_Components = [\U00018800-\U00018aff];
Khitan_Small_Script = [\U00018b00-\U00018cff];
Tangut_Supplement = [\U00018d00-\U00018d7f];
Kana_Extended_B = [\U0001aff0-\U0001afff];
Kana_Supplement = [\U0001b000-\U0001b0ff];
Kana_Extended_A = [\U0001b100-\U0001b12f];
Small_Kana_Extension = [\U0001b130-\U0001b16f];
Nushu = [\U0001b170-\U0001b2ff];
Duployan = [\U0001bc00-\U0001bc9f];
Shorthand_Format_Controls = [\U0001bca0-\U0001bcaf];
Znamenny_Musical_Notation = [\U0001cf00-\U0001cfcf];
Byzantine_Musical_Symbols = [\U0001d000-\U0001d0ff];
Musical_Symbols = [\U0001d100-\U0001d1ff];
Ancient_Greek_Musical_Notation = [\U0001d200-\U0001d24f];
Kaktovik_Numerals = [\U0001d2c0-\U0001d2df];
Mayan_Numerals = [\U0001d2e0-\U0001d2ff];
Tai_Xuan_Jing_Symbols = [\U0001d300-\U0001d35f];
Counting_Rod_Numerals = [\U0001d360-\U0001d37f];
Mathematical_Alphanumeric_Symbols = [\U0001d400-\U0001d7ff];
Sutton_SignWriting = [\U0001d800-\U0001daaf];
Latin_Extended_G = [\U0001df00-\U0001dfff];
Glagolitic_Supplement = [\U0001e000-\U0001e02f];
Cyrillic_Extended_D = [\U0001e030-\U0001e08f];
Nyiakeng_Puachue_Hmong = [\U0001e100-\U0001e14f];
Toto = [\U0001e290-\U0001e2bf];
Wancho = [\U0001e2c0-\U0001e2ff];
Nag_Mundari = [\U0001e4d0-\U0001e4ff];
Ethiopic_Extended_B = [\U0001e7e0-\U0001e7ff];
Mende_Kikakui = [\U0001e800-\U0001e8df];
Adlam = [\U0001e900-\U0001e95f];
Indic_Siyaq_Numbers = [\U0001ec70-\U0001ecbf];
Ottoman_Siyaq_Numbers = [\U0001ed00-\U0001ed4f];
Arabic_Mathematical_Alphabetic_Symbols = [\U0001ee00-\U0001eeff];
Mahjong_Tiles = [\U0001f000-\U0001f02f];
Domino_Tiles = [\U0001f030-\U0001f09f];
Playing_Cards = [\U0001f0a0-\U0001f0ff];
Enclosed_Alphanumeric_Supplement = [\U0001f100-\U0001f1ff];
Enclosed_Ideographic_Supplement = [\U0001f200-\U0001f2ff];
Miscellaneous_Symbols_and_Pictographs = [\U0001f300-\U0001f5ff];
Emoticons = [\U0001f600-\U0001f64f];
Ornamental_Dingbats = [\U0001f650-\U0001f67f];
Transport_and_Map_Symbols = [\U0001f680-\U0001f6ff];
Alchemical_Symbols = [\U0001f700-\U0001f77f];
Geometric_Shapes_Extended = [\U0001f780-\U0001f7ff];
Supplemental_Arrows_C = [\U0001f800-\U0001f8ff];
Supplemental_Symbols_and_Pictographs = [\U0001f900-\U0001f9ff];
Chess_Symbols = [\U0001fa00-\U0001fa6f];
Symbols_and_Pictographs_Extended_A = [\U0001fa70-\U0001faff];
Symbols_for_Legacy_Computing = [\U0001fb00-\U0001fbff];
CJK_Unified_Ideographs_Extension_B = [\U00020000-\U0002a6df];
CJK_Unified_Ideographs_Extension_C = [\U0002a700-\U0002b73f];
CJK_Unified_Ideographs_Extension_D = [\U0002b740-\U0002b81f];
CJK_Unified_Ideographs_Extension_E = [\U0002b820-\U0002ceaf];
CJK_Unified_Ideographs_Extension_F = [\U0002ceb0-\U0002ebef];
CJK_Unified_Ideographs_Extension_I = [\U0002ebf0-\U0002ee5f];
CJK_Compatibility_Ideographs_Supplement = [\U0002f800-\U0002fa1f];
CJK_Unified_Ideographs_Extension_G = [\U00030000-\U0003134f];
CJK_Unified_Ideographs_Extension_H = [\U00031350-\U000323af];
Tags = [\U000e0000-\U000e007f];
Variation_Selectors_Supplement = [\U000e0100-\U000e01ef];
Supplementary_Private_Use_Area_A = [\U000f0000-\U000fffff];
Supplementary_Private_Use_Area_B = [\U00100000-\U0010ffff];
*/
Basic_Latin:
	/*!re2c
		re2c:yyfill:enable = 0;
		Basic_Latin { goto Basic_Latin; }
		* { if (YYCURSOR - 1 == limit) return Basic_Latin; else return Error; }
	*/
Latin_1_Supplement:
	/*!re2c
		re2c:yyfill:enable = 0;
		Latin_1_Supplement { goto Latin_1_Supplement; }
		* { if (YYCURSOR - 1 == limit) return Latin_1_Supplement; else return Error; }
	*/
Latin_Extended_A:
	/*!re2c
		re2c:yyfill:enable = 0;
		Latin_Extended_A { goto Latin_Extended_A; }
		* { if (YYCURSOR - 1 == limit) return Latin_Extended_A; else return Error; }
	*/
Latin_Extended_B:
	/*!re2c
		re2c:yyfill:enable = 0;
		Latin_Extended_B { goto Latin_Extended_B; }
		* { if (YYCURSOR - 1 == limit) return Latin_Extended_B; else return Error; }
	*/
IPA_Extensions:
	/*!re2c
		re2c:yyfill:enable = 0;
		IPA_Extensions { goto IPA_Extensions; }
		* { if (YYCURSOR - 1 == limit) return IPA_Extensions; else return Error; }
	*/
Spacing_Modifier_Letters:
	/*!re2c
		re2c:yyfill:enable = 0;
		Spacing_Modifier_Letters { goto Spacing_Modifier_Letters; }
		* { if (YYCURSOR - 1 == limit) return Spacing_Modifier_Letters; else return Error; }
	*/
Combining_Diacritical_Marks:
	/*!re2c
		re2c:yyfill:enable = 0;
		Combining_Diacritical_Marks { goto Combining_Diacritical_Marks; }
		* { if (YYCURSOR - 1 == limit) return Combining_Diacritical_Marks; else return Error; }
	*/
Greek_and_Coptic:
	/*!re2c
		re2c:yyfill:enable = 0;
		Greek_and_Coptic { goto Greek_and_Coptic; }
		* { if (YYCURSOR - 1 == limit) return Greek_and_Coptic; else return Error; }
	*/
Cyrillic:
	/*!re2c
		re2c:yyfill:enable = 0;
		Cyrillic { goto Cyrillic; }
		* { if (YYCURSOR - 1 == limit) return Cyrillic; else return Error; }
	*/
Cyrillic_Supplement:
	/*!re2c
		re2c:yyfill:enable = 0;
		Cyrillic_Supplement { goto Cyrillic_Supplement; }
		* { if (YYCURSOR - 1 == limit) return Cyrillic_Supplement; else return Error; }
	*/
Armenian:
	/*!re2c
		re2c:yyfill:enable = 0;
		Armenian { goto Armenian; }
		* { if (YYCURSOR - 1 == limit) return Armenian; else return Error; }
	*/
Hebrew:
	/*!re2c
		re2c:yyfill:enable = 0;
		Hebrew { goto Hebrew; }
		* { if (YYCURSOR - 1 == limit) return Hebrew; else return Error; }
	*/
Arabic:
	/*!re2c
		re2c:yyfill:enable = 0;
		Arabic { goto Arabic; }
		* { if (YYCURSOR - 1 == limit) return Arabic; else return Error; }
	*/
Syriac:
	/*!re2c
		re2c:yyfill:enable = 0;
		Syriac { goto Syriac; }
		* { if (YYCURSOR - 1 == limit) return Syriac; else return Error; }
	*/
Arabic_Supplement:
	/*!re2c
		re2c:yyfill:enable = 0;
		Arabic_Supplement { goto Arabic_Supplement; }
		* { if (YYCURSOR - 1 == limit) return Arabic_Supplement; else return Error; }
	*/
Thaana:
	/*!re2c
		re2c:yyfill:enable = 0;
		Thaana { goto Thaana; }
		* { if (YYCURSOR - 1 == limit) return Thaana; else return Error; }
	*/
NKo:
	/*!re2c
		re2c:yyfill:enable = 0;
		NKo { goto NKo; }
		* { if (YYCURSOR - 1 == limit) return NKo; else return Error; }
	*/
Samaritan:
	/*!re2c
		re2c:yyfill:enable = 0;
		Samaritan { goto Samaritan; }
		* { if (YYCURSOR - 1 == limit) return Samaritan; else return Error; }
	*/
Mandaic:
	/*!re2c
		re2c:yyfill:enable = 0;
		Mandaic { goto Mandaic; }
		* { if (YYCURSOR - 1 == limit) return Mandaic; else return Error; }
	*/
Syriac_Supplement:
	/*!re2c
		re2c:yyfill:enable = 0;
		Syriac_Supplement { goto Syriac_Supplement; }
		* { if (YYCURSOR - 1 == limit) return Syriac_Supplement; else return Error; }
	*/
Arabic_Extended_B:
	/*!re2c
		re2c:yyfill:enable = 0;
		Arabic_Extended_B { goto Arabic_Extended_B; }
		* { if (YYCURSOR - 1 == limit) return Arabic_Extended_B; else return Error; }
	*/
Arabic_Extended_A:
	/*!re2c
		re2c:yyfill:enable = 0;
		Arabic_Extended_A { goto Arabic_Extended_A; }
		* { if (YYCURSOR - 1 == limit) return Arabic_Extended_A; else return Error; }
	*/
Devanagari:
	/*!re2c
		re2c:yyfill:enable = 0;
		Devanagari { goto Devanagari; }
		* { if (YYCURSOR - 1 == limit) return Devanagari; else return Error; }
	*/
Bengali:
	/*!re2c
		re2c:yyfill:enable = 0;
		Bengali { goto Bengali; }
		* { if (YYCURSOR - 1 == limit) return Bengali; else return Error; }
	*/
Gurmukhi:
	/*!re2c
		re2c:yyfill:enable = 0;
		Gurmukhi { goto Gurmukhi; }
		* { if (YYCURSOR - 1 == limit) return Gurmukhi; else return Error; }
	*/
Gujarati:
	/*!re2c
		re2c:yyfill:enable = 0;
		Gujarati { goto Gujarati; }
		* { if (YYCURSOR - 1 == limit) return Gujarati; else return Error; }
	*/
Oriya:
	/*!re2c
		re2c:yyfill:enable = 0;
		Oriya { goto Oriya; }
		* { if (YYCURSOR - 1 == limit) return Oriya; else return Error; }
	*/
Tamil:
	/*!re2c
		re2c:yyfill:enable = 0;
		Tamil { goto Tamil; }
		* { if (YYCURSOR - 1 == limit) return Tamil; else return Error; }
	*/
Telugu:
	/*!re2c
		re2c:yyfill:enable = 0;
		Telugu { goto Telugu; }
		* { if (YYCURSOR - 1 == limit) return Telugu; else return Error; }
	*/
Kannada:
	/*!re2c
		re2c:yyfill:enable = 0;
		Kannada { goto Kannada; }
		* { if (YYCURSOR - 1 == limit) return Kannada; else return Error; }
	*/
Malayalam:
	/*!re2c
		re2c:yyfill:enable = 0;
		Malayalam { goto Malayalam; }
		* { if (YYCURSOR - 1 == limit) return Malayalam; else return Error; }
	*/
Sinhala:
	/*!re2c
		re2c:yyfill:enable = 0;
		Sinhala { goto Sinhala; }
		* { if (YYCURSOR - 1 == limit) return Sinhala; else return Error; }
	*/
Thai:
	/*!re2c
		re2c:yyfill:enable = 0;
		Thai { goto Thai; }
		* { if (YYCURSOR - 1 == limit) return Thai; else return Error; }
	*/
Lao:
	/*!re2c
		re2c:yyfill:enable = 0;
		Lao { goto Lao; }
		* { if (YYCURSOR - 1 == limit) return Lao; else return Error; }
	*/
Tibetan:
	/*!re2c
		re2c:yyfill:enable = 0;
		Tibetan { goto Tibetan; }
		* { if (YYCURSOR - 1 == limit) return Tibetan; else return Error; }
	*/
Myanmar:
	/*!re2c
		re2c:yyfill:enable = 0;
		Myanmar { goto Myanmar; }
		* { if (YYCURSOR - 1 == limit) return Myanmar; else return Error; }
	*/
Georgian:
	/*!re2c
		re2c:yyfill:enable = 0;
		Georgian { goto Georgian; }
		* { if (YYCURSOR - 1 == limit) return Georgian; else return Error; }
	*/
Hangul_Jamo:
	/*!re2c
		re2c:yyfill:enable = 0;
		Hangul_Jamo { goto Hangul_Jamo; }
		* { if (YYCURSOR - 1 == limit) return Hangul_Jamo; else return Error; }
	*/
Ethiopic:
	/*!re2c
		re2c:yyfill:enable = 0;
		Ethiopic { goto Ethiopic; }
		* { if (YYCURSOR - 1 == limit) return Ethiopic; else return Error; }
	*/
Ethiopic_Supplement:
	/*!re2c
		re2c:yyfill:enable = 0;
		Ethiopic_Supplement { goto Ethiopic_Supplement; }
		* { if (YYCURSOR - 1 == limit) return Ethiopic_Supplement; else return Error; }
	*/
Cherokee:
	/*!re2c
		re2c:yyfill:enable = 0;
		Cherokee { goto Cherokee; }
		* { if (YYCURSOR - 1 == limit) return Cherokee; else return Error; }
	*/
Unified_Canadian_Aboriginal_Syllabics:
	/*!re2c
		re2c:yyfill:enable = 0;
		Unified_Canadian_Aboriginal_Syllabics { goto Unified_Canadian_Aboriginal_Syllabics; }
		* { if (YYCURSOR - 1 == limit) return Unified_Canadian_Aboriginal_Syllabics; else return Error; }
	*/
Ogham:
	/*!re2c
		re2c:yyfill:enable = 0;
		Ogham { goto Ogham; }
		* { if (YYCURSOR - 1 == limit) return Ogham; else return Error; }
	*/
Runic:
	/*!re2c
		re2c:yyfill:enable = 0;
		Runic { goto Runic; }
		* { if (YYCURSOR - 1 == limit) return Runic; else return Error; }
	*/
Tagalog:
	/*!re2c
		re2c:yyfill:enable = 0;
		Tagalog { goto Tagalog; }
		* { if (YYCURSOR - 1 == limit) return Tagalog; else return Error; }
	*/
Hanunoo:
	/*!re2c
		re2c:yyfill:enable = 0;
		Hanunoo { goto Hanunoo; }
		* { if (YYCURSOR - 1 == limit) return Hanunoo; else return Error; }
	*/
Buhid:
	/*!re2c
		re2c:yyfill:enable = 0;
		Buhid { goto Buhid; }
		* { if (YYCURSOR - 1 == limit) return Buhid; else return Error; }
	*/
Tagbanwa:
	/*!re2c
		re2c:yyfill:enable = 0;
		Tagbanwa { goto Tagbanwa; }
		* { if (YYCURSOR - 1 == limit) return Tagbanwa; else return Error; }
	*/
Khmer:
	/*!re2c
		re2c:yyfill:enable = 0;
		Khmer { goto Khmer; }
		* { if (YYCURSOR - 1 == limit) return Khmer; else return Error; }
	*/
Mongolian:
	/*!re2c
		re2c:yyfill:enable = 0;
		Mongolian { goto Mongolian; }
		* { if (YYCURSOR - 1 == limit) return Mongolian; else return Error; }
	*/
Unified_Canadian_Aboriginal_Syllabics_Extended:
	/*!re2c
		re2c:yyfill:enable = 0;
		Unified_Canadian_Aboriginal_Syllabics_Extended { goto Unified_Canadian_Aboriginal_Syllabics_Extended; }
		* { if (YYCURSOR - 1 == limit) return Unified_Canadian_Aboriginal_Syllabics_Extended; else return Error; }
	*/
Limbu:
	/*!re2c
		re2c:yyfill:enable = 0;
		Limbu { goto Limbu; }
		* { if (YYCURSOR - 1 == limit) return Limbu; else return Error; }
	*/
Tai_Le:
	/*!re2c
		re2c:yyfill:enable = 0;
		Tai_Le { goto Tai_Le; }
		* { if (YYCURSOR - 1 == limit) return Tai_Le; else return Error; }
	*/
New_Tai_Lue:
	/*!re2c
		re2c:yyfill:enable = 0;
		New_Tai_Lue { goto New_Tai_Lue; }
		* { if (YYCURSOR - 1 == limit) return New_Tai_Lue; else return Error; }
	*/
Khmer_Symbols:
	/*!re2c
		re2c:yyfill:enable = 0;
		Khmer_Symbols { goto Khmer_Symbols; }
		* { if (YYCURSOR - 1 == limit) return Khmer_Symbols; else return Error; }
	*/
Buginese:
	/*!re2c
		re2c:yyfill:enable = 0;
		Buginese { goto Buginese; }
		* { if (YYCURSOR - 1 == limit) return Buginese; else return Error; }
	*/
Tai_Tham:
	/*!re2c
		re2c:yyfill:enable = 0;
		Tai_Tham { goto Tai_Tham; }
		* { if (YYCURSOR - 1 == limit) return Tai_Tham; else return Error; }
	*/
Combining_Diacritical_Marks_Extended:
	/*!re2c
		re2c:yyfill:enable = 0;
		Combining_Diacritical_Marks_Extended { goto Combining_Diacritical_Marks_Extended; }
		* { if (YYCURSOR - 1 == limit) return Combining_Diacritical_Marks_Extended; else return Error; }
	*/
Balinese:
	/*!re2c
		re2c:yyfill:enable = 0;
		Balinese { goto Balinese; }
		* { if (YYCURSOR - 1 == limit) return Balinese; else return Error; }
	*/
Sundanese:
	/*!re2c
		re2c:yyfill:enable = 0;
		Sundanese { goto Sundanese; }
		* { if (YYCURSOR - 1 == limit) return Sundanese; else return Error; }
	*/
Batak:
	/*!re2c
		re2c:yyfill:enable = 0;
		Batak { goto Batak; }
		* { if (YYCURSOR - 1 == limit) return Batak; else return Error; }
	*/
Lepcha:
	/*!re2c
		re2c:yyfill:enable = 0;
		Lepcha { goto Lepcha; }
		* { if (YYCURSOR - 1 == limit) return Lepcha; else return Error; }
	*/
Ol_Chiki:
	/*!re2c
		re2c:yyfill:enable = 0;
		Ol_Chiki { goto Ol_Chiki; }
		* { if (YYCURSOR - 1 == limit) return Ol_Chiki; else return Error; }
	*/
Cyrillic_Extended_C:
	/*!re2c
		re2c:yyfill:enable = 0;
		Cyrillic_Extended_C { goto Cyrillic_Extended_C; }
		* { if (YYCURSOR - 1 == limit) return Cyrillic_Extended_C; else return Error; }
	*/
Georgian_Extended:
	/*!re2c
		re2c:yyfill:enable = 0;
		Georgian_Extended { goto Georgian_Extended; }
		* { if (YYCURSOR - 1 == limit) return Georgian_Extended; else return Error; }
	*/
Sundanese_Supplement:
	/*!re2c
		re2c:yyfill:enable = 0;
		Sundanese_Supplement { goto Sundanese_Supplement; }
		* { if (YYCURSOR - 1 == limit) return Sundanese_Supplement; else return Error; }
	*/
Vedic_Extensions:
	/*!re2c
		re2c:yyfill:enable = 0;
		Vedic_Extensions { goto Vedic_Extensions; }
		* { if (YYCURSOR - 1 == limit) return Vedic_Extensions; else return Error; }
	*/
Phonetic_Extensions:
	/*!re2c
		re2c:yyfill:enable = 0;
		Phonetic_Extensions { goto Phonetic_Extensions; }
		* { if (YYCURSOR - 1 == limit) return Phonetic_Extensions; else return Error; }
	*/
Phonetic_Extensions_Supplement:
	/*!re2c
		re2c:yyfill:enable = 0;
		Phonetic_Extensions_Supplement { goto Phonetic_Extensions_Supplement; }
		* { if (YYCURSOR - 1 == limit) return Phonetic_Extensions_Supplement; else return Error; }
	*/
Combining_Diacritical_Marks_Supplement:
	/*!re2c
		re2c:yyfill:enable = 0;
		Combining_Diacritical_Marks_Supplement { goto Combining_Diacritical_Marks_Supplement; }
		* { if (YYCURSOR - 1 == limit) return Combining_Diacritical_Marks_Supplement; else return Error; }
	*/
Latin_Extended_Additional:
	/*!re2c
		re2c:yyfill:enable = 0;
		Latin_Extended_Additional { goto Latin_Extended_Additional; }
		* { if (YYCURSOR - 1 == limit) return Latin_Extended_Additional; else return Error; }
	*/
Greek_Extended:
	/*!re2c
		re2c:yyfill:enable = 0;
		Greek_Extended { goto Greek_Extended; }
		* { if (YYCURSOR - 1 == limit) return Greek_Extended; else return Error; }
	*/
General_Punctuation:
	/*!re2c
		re2c:yyfill:enable = 0;
		General_Punctuation { goto General_Punctuation; }
		* { if (YYCURSOR - 1 == limit) return General_Punctuation; else return Error; }
	*/
Superscripts_and_Subscripts:
	/*!re2c
		re2c:yyfill:enable = 0;
		Superscripts_and_Subscripts { goto Superscripts_and_Subscripts; }
		* { if (YYCURSOR - 1 == limit) return Superscripts_and_Subscripts; else return Error; }
	*/
Currency_Symbols:
	/*!re2c
		re2c:yyfill:enable = 0;
		Currency_Symbols { goto Currency_Symbols; }
		* { if (YYCURSOR - 1 == limit) return Currency_Symbols; else return Error; }
	*/
Combining_Diacritical_Marks_for_Symbols:
	/*!re2c
		re2c:yyfill:enable = 0;
		Combining_Diacritical_Marks_for_Symbols { goto Combining_Diacritical_Marks_for_Symbols; }
		* { if (YYCURSOR - 1 == limit) return Combining_Diacritical_Marks_for_Symbols; else return Error; }
	*/
Letterlike_Symbols:
	/*!re2c
		re2c:yyfill:enable = 0;
		Letterlike_Symbols { goto Letterlike_Symbols; }
		* { if (YYCURSOR - 1 == limit) return Letterlike_Symbols; else return Error; }
	*/
Number_Forms:
	/*!re2c
		re2c:yyfill:enable = 0;
		Number_Forms { goto Number_Forms; }
		* { if (YYCURSOR - 1 == limit) return Number_Forms; else return Error; }
	*/
Arrows:
	/*!re2c
		re2c:yyfill:enable = 0;
		Arrows { goto Arrows; }
		* { if (YYCURSOR - 1 == limit) return Arrows; else return Error; }
	*/
Mathematical_Operators:
	/*!re2c
		re2c:yyfill:enable = 0;
		Mathematical_Operators { goto Mathematical_Operators; }
		* { if (YYCURSOR - 1 == limit) return Mathematical_Operators; else return Error; }
	*/
Miscellaneous_Technical:
	/*!re2c
		re2c:yyfill:enable = 0;
		Miscellaneous_Technical { goto Miscellaneous_Technical; }
		* { if (YYCURSOR - 1 == limit) return Miscellaneous_Technical; else return Error; }
	*/
Control_Pictures:
	/*!re2c
		re2c:yyfill:enable = 0;
		Control_Pictures { goto Control_Pictures; }
		* { if (YYCURSOR - 1 == limit) return Control_Pictures; else return Error; }
	*/
Optical_Character_Recognition:
	/*!re2c
		re2c:yyfill:enable = 0;
		Optical_Character_Recognition { goto Optical_Character_Recognition; }
		* { if (YYCURSOR - 1 == limit) return Optical_Character_Recognition; else return Error; }
	*/
Enclosed_Alphanumerics:
	/*!re2c
		re2c:yyfill:enable = 0;
		Enclosed_Alphanumerics { goto Enclosed_Alphanumerics; }
		* { if (YYCURSOR - 1 == limit) return Enclosed_Alphanumerics; else return Error; }
	*/
Box_Drawing:
	/*!re2c
		re2c:yyfill:enable = 0;
		Box_Drawing { goto Box_Drawing; }
		* { if (YYCURSOR - 1 == limit) return Box_Drawing; else return Error; }
	*/
Block_Elements:
	/*!re2c
		re2c:yyfill:enable = 0;
		Block_Elements { goto Block_Elements; }
		* { if (YYCURSOR - 1 == limit) return Block_Elements; else return Error; }
	*/
Geometric_Shapes:
	/*!re2c
		re2c:yyfill:enable = 0;
		Geometric_Shapes { goto Geometric_Shapes; }
		* { if (YYCURSOR - 1 == limit) return Geometric_Shapes; else return Error; }
	*/
Miscellaneous_Symbols:
	/*!re2c
		re2c:yyfill:enable = 0;
		Miscellaneous_Symbols { goto Miscellaneous_Symbols; }
		* { if (YYCURSOR - 1 == limit) return Miscellaneous_Symbols; else return Error; }
	*/
Dingbats:
	/*!re2c
		re2c:yyfill:enable = 0;
		Dingbats { goto Dingbats; }
		* { if (YYCURSOR - 1 == limit) return Dingbats; else return Error; }
	*/
Miscellaneous_Mathematical_Symbols_A:
	/*!re2c
		re2c:yyfill:enable = 0;
		Miscellaneous_Mathematical_Symbols_A { goto Miscellaneous_Mathematical_Symbols_A; }
		* { if (YYCURSOR - 1 == limit) return Miscellaneous_Mathematical_Symbols_A; else return Error; }
	*/
Supplemental_Arrows_A:
	/*!re2c
		re2c:yyfill:enable = 0;
		Supplemental_Arrows_A { goto Supplemental_Arrows_A; }
		* { if (YYCURSOR - 1 == limit) return Supplemental_Arrows_A; else return Error; }
	*/
Braille_Patterns:
	/*!re2c
		re2c:yyfill:enable = 0;
		Braille_Patterns { goto Braille_Patterns; }
		* { if (YYCURSOR - 1 == limit) return Braille_Patterns; else return Error; }
	*/
Supplemental_Arrows_B:
	/*!re2c
		re2c:yyfill:enable = 0;
		Supplemental_Arrows_B { goto Supplemental_Arrows_B; }
		* { if (YYCURSOR - 1 == limit) return Supplemental_Arrows_B; else return Error; }
	*/
Miscellaneous_Mathematical_Symbols_B:
	/*!re2c
		re2c:yyfill:enable = 0;
		Miscellaneous_Mathematical_Symbols_B { goto Miscellaneous_Mathematical_Symbols_B; }
		* { if (YYCURSOR - 1 == limit) return Miscellaneous_Mathematical_Symbols_B; else return Error; }
	*/
Supplemental_Mathematical_Operators:
	/*!re2c
		re2c:yyfill:enable = 0;
		Supplemental_Mathematical_Operators { goto Supplemental_Mathematical_Operators; }
		* { if (YYCURSOR - 1 == limit) return Supplemental_Mathematical_Operators; else return Error; }
	*/
Miscellaneous_Symbols_and_Arrows:
	/*!re2c
		re2c:yyfill:enable = 0;
		Miscellaneous_Symbols_and_Arrows { goto Miscellaneous_Symbols_and_Arrows; }
		* { if (YYCURSOR - 1 == limit) return Miscellaneous_Symbols_and_Arrows; else return Error; }
	*/
Glagolitic:
	/*!re2c
		re2c:yyfill:enable = 0;
		Glagolitic { goto Glagolitic; }
		* { if (YYCURSOR - 1 == limit) return Glagolitic; else return Error; }
	*/
Latin_Extended_C:
	/*!re2c
		re2c:yyfill:enable = 0;
		Latin_Extended_C { goto Latin_Extended_C; }
		* { if (YYCURSOR - 1 == limit) return Latin_Extended_C; else return Error; }
	*/
Coptic:
	/*!re2c
		re2c:yyfill:enable = 0;
		Coptic { goto Coptic; }
		* { if (YYCURSOR - 1 == limit) return Coptic; else return Error; }
	*/
Georgian_Supplement:
	/*!re2c
		re2c:yyfill:enable = 0;
		Georgian_Supplement { goto Georgian_Supplement; }
		* { if (YYCURSOR - 1 == limit) return Georgian_Supplement; else return Error; }
	*/
Tifinagh:
	/*!re2c
		re2c:yyfill:enable = 0;
		Tifinagh { goto Tifinagh; }
		* { if (YYCURSOR - 1 == limit) return Tifinagh; else return Error; }
	*/
Ethiopic_Extended:
	/*!re2c
		re2c:yyfill:enable = 0;
		Ethiopic_Extended { goto Ethiopic_Extended; }
		* { if (YYCURSOR - 1 == limit) return Ethiopic_Extended; else return Error; }
	*/
Cyrillic_Extended_A:
	/*!re2c
		re2c:yyfill:enable = 0;
		Cyrillic_Extended_A { goto Cyrillic_Extended_A; }
		* { if (YYCURSOR - 1 == limit) return Cyrillic_Extended_A; else return Error; }
	*/
Supplemental_Punctuation:
	/*!re2c
		re2c:yyfill:enable = 0;
		Supplemental_Punctuation { goto Supplemental_Punctuation; }
		* { if (YYCURSOR - 1 == limit) return Supplemental_Punctuation; else return Error; }
	*/
CJK_Radicals_Supplement:
	/*!re2c
		re2c:yyfill:enable = 0;
		CJK_Radicals_Supplement { goto CJK_Radicals_Supplement; }
		* { if (YYCURSOR - 1 == limit) return CJK_Radicals_Supplement; else return Error; }
	*/
Kangxi_Radicals:
	/*!re2c
		re2c:yyfill:enable = 0;
		Kangxi_Radicals { goto Kangxi_Radicals; }
		* { if (YYCURSOR - 1 == limit) return Kangxi_Radicals; else return Error; }
	*/
Ideographic_Description_Characters:
	/*!re2c
		re2c:yyfill:enable = 0;
		Ideographic_Description_Characters { goto Ideographic_Description_Characters; }
		* { if (YYCURSOR - 1 == limit) return Ideographic_Description_Characters; else return Error; }
	*/
CJK_Symbols_and_Punctuation:
	/*!re2c
		re2c:yyfill:enable = 0;
		CJK_Symbols_and_Punctuation { goto CJK_Symbols_and_Punctuation; }
		* { if (YYCURSOR - 1 == limit) return CJK_Symbols_and_Punctuation; else return Error; }
	*/
Hiragana:
	/*!re2c
		re2c:yyfill:enable = 0;
		Hiragana { goto Hiragana; }
		* { if (YYCURSOR - 1 == limit) return Hiragana; else return Error; }
	*/
Katakana:
	/*!re2c
		re2c:yyfill:enable = 0;
		Katakana { goto Katakana; }
		* { if (YYCURSOR - 1 == limit) return Katakana; else return Error; }
	*/
Bopomofo:
	/*!re2c
		re2c:yyfill:enable = 0;
		Bopomofo { goto Bopomofo; }
		* { if (YYCURSOR - 1 == limit) return Bopomofo; else return Error; }
	*/
Hangul_Compatibility_Jamo:
	/*!re2c
		re2c:yyfill:enable = 0;
		Hangul_Compatibility_Jamo { goto Hangul_Compatibility_Jamo; }
		* { if (YYCURSOR - 1 == limit) return Hangul_Compatibility_Jamo; else return Error; }
	*/
Kanbun:
	/*!re2c
		re2c:yyfill:enable = 0;
		Kanbun { goto Kanbun; }
		* { if (YYCURSOR - 1 == limit) return Kanbun; else return Error; }
	*/
Bopomofo_Extended:
	/*!re2c
		re2c:yyfill:enable = 0;
		Bopomofo_Extended { goto Bopomofo_Extended; }
		* { if (YYCURSOR - 1 == limit) return Bopomofo_Extended; else return Error; }
	*/
CJK_Strokes:
	/*!re2c
		re2c:yyfill:enable = 0;
		CJK_Strokes { goto CJK_Strokes; }
		* { if (YYCURSOR - 1 == limit) return CJK_Strokes; else return Error; }
	*/
Katakana_Phonetic_Extensions:
	/*!re2c
		re2c:yyfill:enable = 0;
		Katakana_Phonetic_Extensions { goto Katakana_Phonetic_Extensions; }
		* { if (YYCURSOR - 1 == limit) return Katakana_Phonetic_Extensions; else return Error; }
	*/
Enclosed_CJK_Letters_and_Months:
	/*!re2c
		re2c:yyfill:enable = 0;
		Enclosed_CJK_Letters_and_Months { goto Enclosed_CJK_Letters_and_Months; }
		* { if (YYCURSOR - 1 == limit) return Enclosed_CJK_Letters_and_Months; else return Error; }
	*/
CJK_Compatibility:
	/*!re2c
		re2c:yyfill:enable = 0;
		CJK_Compatibility { goto CJK_Compatibility; }
		* { if (YYCURSOR - 1 == limit) return CJK_Compatibility; else return Error; }
	*/
CJK_Unified_Ideographs_Extension_A:
	/*!re2c
		re2c:yyfill:enable = 0;
		CJK_Unified_Ideographs_Extension_A { goto CJK_Unified_Ideographs_Extension_A; }
		* { if (YYCURSOR - 1 == limit) return CJK_Unified_Ideographs_Extension_A; else return Error; }
	*/
Yijing_Hexagram_Symbols:
	/*!re2c
		re2c:yyfill:enable = 0;
		Yijing_Hexagram_Symbols { goto Yijing_Hexagram_Symbols; }
		* { if (YYCURSOR - 1 == limit) return Yijing_Hexagram_Symbols; else return Error; }
	*/
CJK_Unified_Ideographs:
	/*!re2c
		re2c:yyfill:enable = 0;
		CJK_Unified_Ideographs { goto CJK_Unified_Ideographs; }
		* { if (YYCURSOR - 1 == limit) return CJK_Unified_Ideographs; else return Error; }
	*/
Yi_Syllables:
	/*!re2c
		re2c:yyfill:enable = 0;
		Yi_Syllables { goto Yi_Syllables; }
		* { if (YYCURSOR - 1 == limit) return Yi_Syllables; else return Error; }
	*/
Yi_Radicals:
	/*!re2c
		re2c:yyfill:enable = 0;
		Yi_Radicals { goto Yi_Radicals; }
		* { if (YYCURSOR - 1 == limit) return Yi_Radicals; else return Error; }
	*/
Lisu:
	/*!re2c
		re2c:yyfill:enable = 0;
		Lisu { goto Lisu; }
		* { if (YYCURSOR - 1 == limit) return Lisu; else return Error; }
	*/
Vai:
	/*!re2c
		re2c:yyfill:enable = 0;
		Vai { goto Vai; }
		* { if (YYCURSOR - 1 == limit) return Vai; else return Error; }
	*/
Cyrillic_Extended_B:
	/*!re2c
		re2c:yyfill:enable = 0;
		Cyrillic_Extended_B { goto Cyrillic_Extended_B; }
		* { if (YYCURSOR - 1 == limit) return Cyrillic_Extended_B; else return Error; }
	*/
Bamum:
	/*!re2c
		re2c:yyfill:enable = 0;
		Bamum { goto Bamum; }
		* { if (YYCURSOR - 1 == limit) return Bamum; else return Error; }
	*/
Modifier_Tone_Letters:
	/*!re2c
		re2c:yyfill:enable = 0;
		Modifier_Tone_Letters { goto Modifier_Tone_Letters; }
		* { if (YYCURSOR - 1 == limit) return Modifier_Tone_Letters; else return Error; }
	*/
Latin_Extended_D:
	/*!re2c
		re2c:yyfill:enable = 0;
		Latin_Extended_D { goto Latin_Extended_D; }
		* { if (YYCURSOR - 1 == limit) return Latin_Extended_D; else return Error; }
	*/
Syloti_Nagri:
	/*!re2c
		re2c:yyfill:enable = 0;
		Syloti_Nagri { goto Syloti_Nagri; }
		* { if (YYCURSOR - 1 == limit) return Syloti_Nagri; else return Error; }
	*/
Common_Indic_Number_Forms:
	/*!re2c
		re2c:yyfill:enable = 0;
		Common_Indic_Number_Forms { goto Common_Indic_Number_Forms; }
		* { if (YYCURSOR - 1 == limit) return Common_Indic_Number_Forms; else return Error; }
	*/
Phags_pa:
	/*!re2c
		re2c:yyfill:enable = 0;
		Phags_pa { goto Phags_pa; }
		* { if (YYCURSOR - 1 == limit) return Phags_pa; else return Error; }
	*/
Saurashtra:
	/*!re2c
		re2c:yyfill:enable = 0;
		Saurashtra { goto Saurashtra; }
		* { if (YYCURSOR - 1 == limit) return Saurashtra; else return Error; }
	*/
Devanagari_Extended:
	/*!re2c
		re2c:yyfill:enable = 0;
		Devanagari_Extended { goto Devanagari_Extended; }
		* { if (YYCURSOR - 1 == limit) return Devanagari_Extended; else return Error; }
	*/
Kayah_Li:
	/*!re2c
		re2c:yyfill:enable = 0;
		Kayah_Li { goto Kayah_Li; }
		* { if (YYCURSOR - 1 == limit) return Kayah_Li; else return Error; }
	*/
Rejang:
	/*!re2c
		re2c:yyfill:enable = 0;
		Rejang { goto Rejang; }
		* { if (YYCURSOR - 1 == limit) return Rejang; else return Error; }
	*/
Hangul_Jamo_Extended_A:
	/*!re2c
		re2c:yyfill:enable = 0;
		Hangul_Jamo_Extended_A { goto Hangul_Jamo_Extended_A; }
		* { if (YYCURSOR - 1 == limit) return Hangul_Jamo_Extended_A; else return Error; }
	*/
Javanese:
	/*!re2c
		re2c:yyfill:enable = 0;
		Javanese { goto Javanese; }
		* { if (YYCURSOR - 1 == limit) return Javanese; else return Error; }
	*/
Myanmar_Extended_B:
	/*!re2c
		re2c:yyfill:enable = 0;
		Myanmar_Extended_B { goto Myanmar_Extended_B; }
		* { if (YYCURSOR - 1 == limit) return Myanmar_Extended_B; else return Error; }
	*/
Cham:
	/*!re2c
		re2c:yyfill:enable = 0;
		Cham { goto Cham; }
		* { if (YYCURSOR - 1 == limit) return Cham; else return Error; }
	*/
Myanmar_Extended_A:
	/*!re2c
		re2c:yyfill:enable = 0;
		Myanmar_Extended_A { goto Myanmar_Extended_A; }
		* { if (YYCURSOR - 1 == limit) return Myanmar_Extended_A; else return Error; }
	*/
Tai_Viet:
	/*!re2c
		re2c:yyfill:enable = 0;
		Tai_Viet { goto Tai_Viet; }
		* { if (YYCURSOR - 1 == limit) return Tai_Viet; else return Error; }
	*/
Meetei_Mayek_Extensions:
	/*!re2c
		re2c:yyfill:enable = 0;
		Meetei_Mayek_Extensions { goto Meetei_Mayek_Extensions; }
		* { if (YYCURSOR - 1 == limit) return Meetei_Mayek_Extensions; else return Error; }
	*/
Ethiopic_Extended_A:
	/*!re2c
		re2c:yyfill:enable = 0;
		Ethiopic_Extended_A { goto Ethiopic_Extended_A; }
		* { if (YYCURSOR - 1 == limit) return Ethiopic_Extended_A; else return Error; }
	*/
Latin_Extended_E:
	/*!re2c
		re2c:yyfill:enable = 0;
		Latin_Extended_E { goto Latin_Extended_E; }
		* { if (YYCURSOR - 1 == limit) return Latin_Extended_E; else return Error; }
	*/
Cherokee_Supplement:
	/*!re2c
		re2c:yyfill:enable = 0;
		Cherokee_Supplement { goto Cherokee_Supplement; }
		* { if (YYCURSOR - 1 == limit) return Cherokee_Supplement; else return Error; }
	*/
Meetei_Mayek:
	/*!re2c
		re2c:yyfill:enable = 0;
		Meetei_Mayek { goto Meetei_Mayek; }
		* { if (YYCURSOR - 1 == limit) return Meetei_Mayek; else return Error; }
	*/
Hangul_Syllables:
	/*!re2c
		re2c:yyfill:enable = 0;
		Hangul_Syllables { goto Hangul_Syllables; }
		* { if (YYCURSOR - 1 == limit) return Hangul_Syllables; else return Error; }
	*/
Hangul_Jamo_Extended_B:
	/*!re2c
		re2c:yyfill:enable = 0;
		Hangul_Jamo_Extended_B { goto Hangul_Jamo_Extended_B; }
		* { if (YYCURSOR - 1 == limit) return Hangul_Jamo_Extended_B; else return Error; }
	*/
High_Surrogates:
	/*!re2c
		re2c:yyfill:enable = 0;
		High_Surrogates { goto High_Surrogates; }
		* { if (YYCURSOR - 1 == limit) return High_Surrogates; else return Error; }
	*/
High_Private_Use_Surrogates:
	/*!re2c
		re2c:yyfill:enable = 0;
		High_Private_Use_Surrogates { goto High_Private_Use_Surrogates; }
		* { if (YYCURSOR - 1 == limit) return High_Private_Use_Surrogates; else return Error; }
	*/
Low_Surrogates:
	/*!re2c
		re2c:yyfill:enable = 0;
		Low_Surrogates { goto Low_Surrogates; }
		* { if (YYCURSOR - 1 == limit) return Low_Surrogates; else return Error; }
	*/
Private_Use_Area:
	/*!re2c
		re2c:yyfill:enable = 0;
		Private_Use_Area { goto Private_Use_Area; }
		* { if (YYCURSOR - 1 == limit) return Private_Use_Area; else return Error; }
	*/
CJK_Compatibility_Ideographs:
	/*!re2c
		re2c:yyfill:enable = 0;
		CJK_Compatibility_Ideographs { goto CJK_Compatibility_Ideographs; }
		* { if (YYCURSOR - 1 == limit) return CJK_Compatibility_Ideographs; else return Error; }
	*/
Alphabetic_Presentation_Forms:
	/*!re2c
		re2c:yyfill:enable = 0;
		Alphabetic_Presentation_Forms { goto Alphabetic_Presentation_Forms; }
		* { if (YYCURSOR - 1 == limit) return Alphabetic_Presentation_Forms; else return Error; }
	*/
Arabic_Presentation_Forms_A:
	/*!re2c
		re2c:yyfill:enable = 0;
		Arabic_Presentation_Forms_A { goto Arabic_Presentation_Forms_A; }
		* { if (YYCURSOR - 1 == limit) return Arabic_Presentation_Forms_A; else return Error; }
	*/
Variation_Selectors:
	/*!re2c
		re2c:yyfill:enable = 0;
		Variation_Selectors { goto Variation_Selectors; }
		* { if (YYCURSOR - 1 == limit) return Variation_Selectors; else return Error; }
	*/
Vertical_Forms:
	/*!re2c
		re2c:yyfill:enable = 0;
		Vertical_Forms { goto Vertical_Forms; }
		* { if (YYCURSOR - 1 == limit) return Vertical_Forms; else return Error; }
	*/
Combining_Half_Marks:
	/*!re2c
		re2c:yyfill:enable = 0;
		Combining_Half_Marks { goto Combining_Half_Marks; }
		* { if (YYCURSOR - 1 == limit) return Combining_Half_Marks; else return Error; }
	*/
CJK_Compatibility_Forms:
	/*!re2c
		re2c:yyfill:enable = 0;
		CJK_Compatibility_Forms { goto CJK_Compatibility_Forms; }
		* { if (YYCURSOR - 1 == limit) return CJK_Compatibility_Forms; else return Error; }
	*/
Small_Form_Variants:
	/*!re2c
		re2c:yyfill:enable = 0;
		Small_Form_Variants { goto Small_Form_Variants; }
		* { if (YYCURSOR - 1 == limit) return Small_Form_Variants; else return Error; }
	*/
Arabic_Presentation_Forms_B:
	/*!re2c
		re2c:yyfill:enable = 0;
		Arabic_Presentation_Forms_B { goto Arabic_Presentation_Forms_B; }
		* { if (YYCURSOR - 1 == limit) return Arabic_Presentation_Forms_B; else return Error; }
	*/
Halfwidth_and_Fullwidth_Forms:
	/*!re2c
		re2c:yyfill:enable = 0;
		Halfwidth_and_Fullwidth_Forms { goto Halfwidth_and_Fullwidth_Forms; }
		* { if (YYCURSOR - 1 == limit) return Halfwidth_and_Fullwidth_Forms; else return Error; }
	*/
Specials:
	/*!re2c
		re2c:yyfill:enable = 0;
		Specials { goto Specials; }
		* { if (YYCURSOR - 1 == limit) return Specials; else return Error; }
	*/
Linear_B_Syllabary:
	/*!re2c
		re2c:yyfill:enable = 0;
		Linear_B_Syllabary { goto Linear_B_Syllabary; }
		* { if (YYCURSOR - 1 == limit) return Linear_B_Syllabary; else return Error; }
	*/
Linear_B_Ideograms:
	/*!re2c
		re2c:yyfill:enable = 0;
		Linear_B_Ideograms { goto Linear_B_Ideograms; }
		* { if (YYCURSOR - 1 == limit) return Linear_B_Ideograms; else return Error; }
	*/
Aegean_Numbers:
	/*!re2c
		re2c:yyfill:enable = 0;
		Aegean_Numbers { goto Aegean_Numbers; }
		* { if (YYCURSOR - 1 == limit) return Aegean_Numbers; else return Error; }
	*/
Ancient_Greek_Numbers:
	/*!re2c
		re2c:yyfill:enable = 0;
		Ancient_Greek_Numbers { goto Ancient_Greek_Numbers; }
		* { if (YYCURSOR - 1 == limit) return Ancient_Greek_Numbers; else return Error; }
	*/
Ancient_Symbols:
	/*!re2c
		re2c:yyfill:enable = 0;
		Ancient_Symbols { goto Ancient_Symbols; }
		* { if (YYCURSOR - 1 == limit) return Ancient_Symbols; else return Error; }
	*/
Phaistos_Disc:
	/*!re2c
		re2c:yyfill:enable = 0;
		Phaistos_Disc { goto Phaistos_Disc; }
		* { if (YYCURSOR - 1 == limit) return Phaistos_Disc; else return Error; }
	*/
Lycian:
	/*!re2c
		re2c:yyfill:enable = 0;
		Lycian { goto Lycian; }
		* { if (YYCURSOR - 1 == limit) return Lycian; else return Error; }
	*/
Carian:
	/*!re2c
		re2c:yyfill:enable = 0;
		Carian { goto Carian; }
		* { if (YYCURSOR - 1 == limit) return Carian; else return Error; }
	*/
Coptic_Epact_Numbers:
	/*!re2c
		re2c:yyfill:enable = 0;
		Coptic_Epact_Numbers { goto Coptic_Epact_Numbers; }
		* { if (YYCURSOR - 1 == limit) return Coptic_Epact_Numbers; else return Error; }
	*/
Old_Italic:
	/*!re2c
		re2c:yyfill:enable = 0;
		Old_Italic { goto Old_Italic; }
		* { if (YYCURSOR - 1 == limit) return Old_Italic; else return Error; }
	*/
Gothic:
	/*!re2c
		re2c:yyfill:enable = 0;
		Gothic { goto Gothic; }
		* { if (YYCURSOR - 1 == limit) return Gothic; else return Error; }
	*/
Old_Permic:
	/*!re2c
		re2c:yyfill:enable = 0;
		Old_Permic { goto Old_Permic; }
		* { if (YYCURSOR - 1 == limit) return Old_Permic; else return Error; }
	*/
Ugaritic:
	/*!re2c
		re2c:yyfill:enable = 0;
		Ugaritic { goto Ugaritic; }
		* { if (YYCURSOR - 1 == limit) return Ugaritic; else return Error; }
	*/
Old_Persian:
	/*!re2c
		re2c:yyfill:enable = 0;
		Old_Persian { goto Old_Persian; }
		* { if (YYCURSOR - 1 == limit) return Old_Persian; else return Error; }
	*/
Deseret:
	/*!re2c
		re2c:yyfill:enable = 0;
		Deseret { goto Deseret; }
		* { if (YYCURSOR - 1 == limit) return Deseret; else return Error; }
	*/
Shavian:
	/*!re2c
		re2c:yyfill:enable = 0;
		Shavian { goto Shavian; }
		* { if (YYCURSOR - 1 == limit) return Shavian; else return Error; }
	*/
Osmanya:
	/*!re2c
		re2c:yyfill:enable = 0;
		Osmanya { goto Osmanya; }
		* { if (YYCURSOR - 1 == limit) return Osmanya; else return Error; }
	*/
Osage:
	/*!re2c
		re2c:yyfill:enable = 0;
		Osage { goto Osage; }
		* { if (YYCURSOR - 1 == limit) return Osage; else return Error; }
	*/
Elbasan:
	/*!re2c
		re2c:yyfill:enable = 0;
		Elbasan { goto Elbasan; }
		* { if (YYCURSOR - 1 == limit) return Elbasan; else return Error; }
	*/
Caucasian_Albanian:
	/*!re2c
		re2c:yyfill:enable = 0;
		Caucasian_Albanian { goto Caucasian_Albanian; }
		* { if (YYCURSOR - 1 == limit) return Caucasian_Albanian; else return Error; }
	*/
Vithkuqi:
	/*!re2c
		re2c:yyfill:enable = 0;
		Vithkuqi { goto Vithkuqi; }
		* { if (YYCURSOR - 1 == limit) return Vithkuqi; else return Error; }
	*/
Linear_A:
	/*!re2c
		re2c:yyfill:enable = 0;
		Linear_A { goto Linear_A; }
		* { if (YYCURSOR - 1 == limit) return Linear_A; else return Error; }
	*/
Latin_Extended_F:
	/*!re2c
		re2c:yyfill:enable = 0;
		Latin_Extended_F { goto Latin_Extended_F; }
		* { if (YYCURSOR - 1 == limit) return Latin_Extended_F; else return Error; }
	*/
Cypriot_Syllabary:
	/*!re2c
		re2c:yyfill:enable = 0;
		Cypriot_Syllabary { goto Cypriot_Syllabary; }
		* { if (YYCURSOR - 1 == limit) return Cypriot_Syllabary; else return Error; }
	*/
Imperial_Aramaic:
	/*!re2c
		re2c:yyfill:enable = 0;
		Imperial_Aramaic { goto Imperial_Aramaic; }
		* { if (YYCURSOR - 1 == limit) return Imperial_Aramaic; else return Error; }
	*/
Palmyrene:
	/*!re2c
		re2c:yyfill:enable = 0;
		Palmyrene { goto Palmyrene; }
		* { if (YYCURSOR - 1 == limit) return Palmyrene; else return Error; }
	*/
Nabataean:
	/*!re2c
		re2c:yyfill:enable = 0;
		Nabataean { goto Nabataean; }
		* { if (YYCURSOR - 1 == limit) return Nabataean; else return Error; }
	*/
Hatran:
	/*!re2c
		re2c:yyfill:enable = 0;
		Hatran { goto Hatran; }
		* { if (YYCURSOR - 1 == limit) return Hatran; else return Error; }
	*/
Phoenician:
	/*!re2c
		re2c:yyfill:enable = 0;
		Phoenician { goto Phoenician; }
		* { if (YYCURSOR - 1 == limit) return Phoenician; else return Error; }
	*/
Lydian:
	/*!re2c
		re2c:yyfill:enable = 0;
		Lydian { goto Lydian; }
		* { if (YYCURSOR - 1 == limit) return Lydian; else return Error; }
	*/
Meroitic_Hieroglyphs:
	/*!re2c
		re2c:yyfill:enable = 0;
		Meroitic_Hieroglyphs { goto Meroitic_Hieroglyphs; }
		* { if (YYCURSOR - 1 == limit) return Meroitic_Hieroglyphs; else return Error; }
	*/
Meroitic_Cursive:
	/*!re2c
		re2c:yyfill:enable = 0;
		Meroitic_Cursive { goto Meroitic_Cursive; }
		* { if (YYCURSOR - 1 == limit) return Meroitic_Cursive; else return Error; }
	*/
Kharoshthi:
	/*!re2c
		re2c:yyfill:enable = 0;
		Kharoshthi { goto Kharoshthi; }
		* { if (YYCURSOR - 1 == limit) return Kharoshthi; else return Error; }
	*/
Old_South_Arabian:
	/*!re2c
		re2c:yyfill:enable = 0;
		Old_South_Arabian { goto Old_South_Arabian; }
		* { if (YYCURSOR - 1 == limit) return Old_South_Arabian; else return Error; }
	*/
Old_North_Arabian:
	/*!re2c
		re2c:yyfill:enable = 0;
		Old_North_Arabian { goto Old_North_Arabian; }
		* { if (YYCURSOR - 1 == limit) return Old_North_Arabian; else return Error; }
	*/
Manichaean:
	/*!re2c
		re2c:yyfill:enable = 0;
		Manichaean { goto Manichaean; }
		* { if (YYCURSOR - 1 == limit) return Manichaean; else return Error; }
	*/
Avestan:
	/*!re2c
		re2c:yyfill:enable = 0;
		Avestan { goto Avestan; }
		* { if (YYCURSOR - 1 == limit) return Avestan; else return Error; }
	*/
Inscriptional_Parthian:
	/*!re2c
		re2c:yyfill:enable = 0;
		Inscriptional_Parthian { goto Inscriptional_Parthian; }
		* { if (YYCURSOR - 1 == limit) return Inscriptional_Parthian; else return Error; }
	*/
Inscriptional_Pahlavi:
	/*!re2c
		re2c:yyfill:enable = 0;
		Inscriptional_Pahlavi { goto Inscriptional_Pahlavi; }
		* { if (YYCURSOR - 1 == limit) return Inscriptional_Pahlavi; else return Error; }
	*/
Psalter_Pahlavi:
	/*!re2c
		re2c:yyfill:enable = 0;
		Psalter_Pahlavi { goto Psalter_Pahlavi; }
		* { if (YYCURSOR - 1 == limit) return Psalter_Pahlavi; else return Error; }
	*/
Old_Turkic:
	/*!re2c
		re2c:yyfill:enable = 0;
		Old_Turkic { goto Old_Turkic; }
		* { if (YYCURSOR - 1 == limit) return Old_Turkic; else return Error; }
	*/
Old_Hungarian:
	/*!re2c
		re2c:yyfill:enable = 0;
		Old_Hungarian { goto Old_Hungarian; }
		* { if (YYCURSOR - 1 == limit) return Old_Hungarian; else return Error; }
	*/
Hanifi_Rohingya:
	/*!re2c
		re2c:yyfill:enable = 0;
		Hanifi_Rohingya { goto Hanifi_Rohingya; }
		* { if (YYCURSOR - 1 == limit) return Hanifi_Rohingya; else return Error; }
	*/
Rumi_Numeral_Symbols:
	/*!re2c
		re2c:yyfill:enable = 0;
		Rumi_Numeral_Symbols { goto Rumi_Numeral_Symbols; }
		* { if (YYCURSOR - 1 == limit) return Rumi_Numeral_Symbols; else return Error; }
	*/
Yezidi:
	/*!re2c
		re2c:yyfill:enable = 0;
		Yezidi { goto Yezidi; }
		* { if (YYCURSOR - 1 == limit) return Yezidi; else return Error; }
	*/
Arabic_Extended_C:
	/*!re2c
		re2c:yyfill:enable = 0;
		Arabic_Extended_C { goto Arabic_Extended_C; }
		* { if (YYCURSOR - 1 == limit) return Arabic_Extended_C; else return Error; }
	*/
Old_Sogdian:
	/*!re2c
		re2c:yyfill:enable = 0;
		Old_Sogdian { goto Old_Sogdian; }
		* { if (YYCURSOR - 1 == limit) return Old_Sogdian; else return Error; }
	*/
Sogdian:
	/*!re2c
		re2c:yyfill:enable = 0;
		Sogdian { goto Sogdian; }
		* { if (YYCURSOR - 1 == limit) return Sogdian; else return Error; }
	*/
Old_Uyghur:
	/*!re2c
		re2c:yyfill:enable = 0;
		Old_Uyghur { goto Old_Uyghur; }
		* { if (YYCURSOR - 1 == limit) return Old_Uyghur; else return Error; }
	*/
Chorasmian:
	/*!re2c
		re2c:yyfill:enable = 0;
		Chorasmian { goto Chorasmian; }
		* { if (YYCURSOR - 1 == limit) return Chorasmian; else return Error; }
	*/
Elymaic:
	/*!re2c
		re2c:yyfill:enable = 0;
		Elymaic { goto Elymaic; }
		* { if (YYCURSOR - 1 == limit) return Elymaic; else return Error; }
	*/
Brahmi:
	/*!re2c
		re2c:yyfill:enable = 0;
		Brahmi { goto Brahmi; }
		* { if (YYCURSOR - 1 == limit) return Brahmi; else return Error; }
	*/
Kaithi:
	/*!re2c
		re2c:yyfill:enable = 0;
		Kaithi { goto Kaithi; }
		* { if (YYCURSOR - 1 == limit) return Kaithi; else return Error; }
	*/
Sora_Sompeng:
	/*!re2c
		re2c:yyfill:enable = 0;
		Sora_Sompeng { goto Sora_Sompeng; }
		* { if (YYCURSOR - 1 == limit) return Sora_Sompeng; else return Error; }
	*/
Chakma:
	/*!re2c
		re2c:yyfill:enable = 0;
		Chakma { goto Chakma; }
		* { if (YYCURSOR - 1 == limit) return Chakma; else return Error; }
	*/
Mahajani:
	/*!re2c
		re2c:yyfill:enable = 0;
		Mahajani { goto Mahajani; }
		* { if (YYCURSOR - 1 == limit) return Mahajani; else return Error; }
	*/
Sharada:
	/*!re2c
		re2c:yyfill:enable = 0;
		Sharada { goto Sharada; }
		* { if (YYCURSOR - 1 == limit) return Sharada; else return Error; }
	*/
Sinhala_Archaic_Numbers:
	/*!re2c
		re2c:yyfill:enable = 0;
		Sinhala_Archaic_Numbers { goto Sinhala_Archaic_Numbers; }
		* { if (YYCURSOR - 1 == limit) return Sinhala_Archaic_Numbers; else return Error; }
	*/
Khojki:
	/*!re2c
		re2c:yyfill:enable = 0;
		Khojki { goto Khojki; }
		* { if (YYCURSOR - 1 == limit) return Khojki; else return Error; }
	*/
Multani:
	/*!re2c
		re2c:yyfill:enable = 0;
		Multani { goto Multani; }
		* { if (YYCURSOR - 1 == limit) return Multani; else return Error; }
	*/
Khudawadi:
	/*!re2c
		re2c:yyfill:enable = 0;
		Khudawadi { goto Khudawadi; }
		* { if (YYCURSOR - 1 == limit) return Khudawadi; else return Error; }
	*/
Grantha:
	/*!re2c
		re2c:yyfill:enable = 0;
		Grantha { goto Grantha; }
		* { if (YYCURSOR - 1 == limit) return Grantha; else return Error; }
	*/
Newa:
	/*!re2c
		re2c:yyfill:enable = 0;
		Newa { goto Newa; }
		* { if (YYCURSOR - 1 == limit) return Newa; else return Error; }
	*/
Tirhuta:
	/*!re2c
		re2c:yyfill:enable = 0;
		Tirhuta { goto Tirhuta; }
		* { if (YYCURSOR - 1 == limit) return Tirhuta; else return Error; }
	*/
Siddham:
	/*!re2c
		re2c:yyfill:enable = 0;
		Siddham { goto Siddham; }
		* { if (YYCURSOR - 1 == limit) return Siddham; else return Error; }
	*/
Modi:
	/*!re2c
		re2c:yyfill:enable = 0;
		Modi { goto Modi; }
		* { if (YYCURSOR - 1 == limit) return Modi; else return Error; }
	*/
Mongolian_Supplement:
	/*!re2c
		re2c:yyfill:enable = 0;
		Mongolian_Supplement { goto Mongolian_Supplement; }
		* { if (YYCURSOR - 1 == limit) return Mongolian_Supplement; else return Error; }
	*/
Takri:
	/*!re2c
		re2c:yyfill:enable = 0;
		Takri { goto Takri; }
		* { if (YYCURSOR - 1 == limit) return Takri; else return Error; }
	*/
Ahom:
	/*!re2c
		re2c:yyfill:enable = 0;
		Ahom { goto Ahom; }
		* { if (YYCURSOR - 1 == limit) return Ahom; else return Error; }
	*/
Dogra:
	/*!re2c
		re2c:yyfill:enable = 0;
		Dogra { goto Dogra; }
		* { if (YYCURSOR - 1 == limit) return Dogra; else return Error; }
	*/
Warang_Citi:
	/*!re2c
		re2c:yyfill:enable = 0;
		Warang_Citi { goto Warang_Citi; }
		* { if (YYCURSOR - 1 == limit) return Warang_Citi; else return Error; }
	*/
Dives_Akuru:
	/*!re2c
		re2c:yyfill:enable = 0;
		Dives_Akuru { goto Dives_Akuru; }
		* { if (YYCURSOR - 1 == limit) return Dives_Akuru; else return Error; }
	*/
Nandinagari:
	/*!re2c
		re2c:yyfill:enable = 0;
		Nandinagari { goto Nandinagari; }
		* { if (YYCURSOR - 1 == limit) return Nandinagari; else return Error; }
	*/
Zanabazar_Square:
	/*!re2c
		re2c:yyfill:enable = 0;
		Zanabazar_Square { goto Zanabazar_Square; }
		* { if (YYCURSOR - 1 == limit) return Zanabazar_Square; else return Error; }
	*/
Soyombo:
	/*!re2c
		re2c:yyfill:enable = 0;
		Soyombo { goto Soyombo; }
		* { if (YYCURSOR - 1 == limit) return Soyombo; else return Error; }
	*/
Unified_Canadian_Aboriginal_Syllabics_Extended_A:
	/*!re2c
		re2c:yyfill:enable = 0;
		Unified_Canadian_Aboriginal_Syllabics_Extended_A { goto Unified_Canadian_Aboriginal_Syllabics_Extended_A; }
		* { if (YYCURSOR - 1 == limit) return Unified_Canadian_Aboriginal_Syllabics_Extended_A; else return Error; }
	*/
Pau_Cin_Hau:
	/*!re2c
		re2c:yyfill:enable = 0;
		Pau_Cin_Hau { goto Pau_Cin_Hau; }
		* { if (YYCURSOR - 1 == limit) return Pau_Cin_Hau; else return Error; }
	*/
Devanagari_Extended_A:
	/*!re2c
		re2c:yyfill:enable = 0;
		Devanagari_Extended_A { goto Devanagari_Extended_A; }
		* { if (YYCURSOR - 1 == limit) return Devanagari_Extended_A; else return Error; }
	*/
Bhaiksuki:
	/*!re2c
		re2c:yyfill:enable = 0;
		Bhaiksuki { goto Bhaiksuki; }
		* { if (YYCURSOR - 1 == limit) return Bhaiksuki; else return Error; }
	*/
Marchen:
	/*!re2c
		re2c:yyfill:enable = 0;
		Marchen { goto Marchen; }
		* { if (YYCURSOR - 1 == limit) return Marchen; else return Error; }
	*/
Masaram_Gondi:
	/*!re2c
		re2c:yyfill:enable = 0;
		Masaram_Gondi { goto Masaram_Gondi; }
		* { if (YYCURSOR - 1 == limit) return Masaram_Gondi; else return Error; }
	*/
Gunjala_Gondi:
	/*!re2c
		re2c:yyfill:enable = 0;
		Gunjala_Gondi { goto Gunjala_Gondi; }
		* { if (YYCURSOR - 1 == limit) return Gunjala_Gondi; else return Error; }
	*/
Makasar:
	/*!re2c
		re2c:yyfill:enable = 0;
		Makasar { goto Makasar; }
		* { if (YYCURSOR - 1 == limit) return Makasar; else return Error; }
	*/
Kawi:
	/*!re2c
		re2c:yyfill:enable = 0;
		Kawi { goto Kawi; }
		* { if (YYCURSOR - 1 == limit) return Kawi; else return Error; }
	*/
Lisu_Supplement:
	/*!re2c
		re2c:yyfill:enable = 0;
		Lisu_Supplement { goto Lisu_Supplement; }
		* { if (YYCURSOR - 1 == limit) return Lisu_Supplement; else return Error; }
	*/
Tamil_Supplement:
	/*!re2c
		re2c:yyfill:enable = 0;
		Tamil_Supplement { goto Tamil_Supplement; }
		* { if (YYCURSOR - 1 == limit) return Tamil_Supplement; else return Error; }
	*/
Cuneiform:
	/*!re2c
		re2c:yyfill:enable = 0;
		Cuneiform { goto Cuneiform; }
		* { if (YYCURSOR - 1 == limit) return Cuneiform; else return Error; }
	*/
Cuneiform_Numbers_and_Punctuation:
	/*!re2c
		re2c:yyfill:enable = 0;
		Cuneiform_Numbers_and_Punctuation { goto Cuneiform_Numbers_and_Punctuation; }
		* { if (YYCURSOR - 1 == limit) return Cuneiform_Numbers_and_Punctuation; else return Error; }
	*/
Early_Dynastic_Cuneiform:
	/*!re2c
		re2c:yyfill:enable = 0;
		Early_Dynastic_Cuneiform { goto Early_Dynastic_Cuneiform; }
		* { if (YYCURSOR - 1 == limit) return Early_Dynastic_Cuneiform; else return Error; }
	*/
Cypro_Minoan:
	/*!re2c
		re2c:yyfill:enable = 0;
		Cypro_Minoan { goto Cypro_Minoan; }
		* { if (YYCURSOR - 1 == limit) return Cypro_Minoan; else return Error; }
	*/
Egyptian_Hieroglyphs:
	/*!re2c
		re2c:yyfill:enable = 0;
		Egyptian_Hieroglyphs { goto Egyptian_Hieroglyphs; }
		* { if (YYCURSOR - 1 == limit) return Egyptian_Hieroglyphs; else return Error; }
	*/
Egyptian_Hieroglyph_Format_Controls:
	/*!re2c
		re2c:yyfill:enable = 0;
		Egyptian_Hieroglyph_Format_Controls { goto Egyptian_Hieroglyph_Format_Controls; }
		* { if (YYCURSOR - 1 == limit) return Egyptian_Hieroglyph_Format_Controls; else return Error; }
	*/
Anatolian_Hieroglyphs:
	/*!re2c
		re2c:yyfill:enable = 0;
		Anatolian_Hieroglyphs { goto Anatolian_Hieroglyphs; }
		* { if (YYCURSOR - 1 == limit) return Anatolian_Hieroglyphs; else return Error; }
	*/
Bamum_Supplement:
	/*!re2c
		re2c:yyfill:enable = 0;
		Bamum_Supplement { goto Bamum_Supplement; }
		* { if (YYCURSOR - 1 == limit) return Bamum_Supplement; else return Error; }
	*/
Mro:
	/*!re2c
		re2c:yyfill:enable = 0;
		Mro { goto Mro; }
		* { if (YYCURSOR - 1 == limit) return Mro; else return Error; }
	*/
Tangsa:
	/*!re2c
		re2c:yyfill:enable = 0;
		Tangsa { goto Tangsa; }
		* { if (YYCURSOR - 1 == limit) return Tangsa; else return Error; }
	*/
Bassa_Vah:
	/*!re2c
		re2c:yyfill:enable = 0;
		Bassa_Vah { goto Bassa_Vah; }
		* { if (YYCURSOR - 1 == limit) return Bassa_Vah; else return Error; }
	*/
Pahawh_Hmong:
	/*!re2c
		re2c:yyfill:enable = 0;
		Pahawh_Hmong { goto Pahawh_Hmong; }
		* { if (YYCURSOR - 1 == limit) return Pahawh_Hmong; else return Error; }
	*/
Medefaidrin:
	/*!re2c
		re2c:yyfill:enable = 0;
		Medefaidrin { goto Medefaidrin; }
		* { if (YYCURSOR - 1 == limit) return Medefaidrin; else return Error; }
	*/
Miao:
	/*!re2c
		re2c:yyfill:enable = 0;
		Miao { goto Miao; }
		* { if (YYCURSOR - 1 == limit) return Miao; else return Error; }
	*/
Ideographic_Symbols_and_Punctuation:
	/*!re2c
		re2c:yyfill:enable = 0;
		Ideographic_Symbols_and_Punctuation { goto Ideographic_Symbols_and_Punctuation; }
		* { if (YYCURSOR - 1 == limit) return Ideographic_Symbols_and_Punctuation; else return Error; }
	*/
Tangut:
	/*!re2c
		re2c:yyfill:enable = 0;
		Tangut { goto Tangut; }
		* { if (YYCURSOR - 1 == limit) return Tangut; else return Error; }
	*/
Tangut_Components:
	/*!re2c
		re2c:yyfill:enable = 0;
		Tangut_Components { goto Tangut_Components; }
		* { if (YYCURSOR - 1 == limit) return Tangut_Components; else return Error; }
	*/
Khitan_Small_Script:
	/*!re2c
		re2c:yyfill:enable = 0;
		Khitan_Small_Script { goto Khitan_Small_Script; }
		* { if (YYCURSOR - 1 == limit) return Khitan_Small_Script; else return Error; }
	*/
Tangut_Supplement:
	/*!re2c
		re2c:yyfill:enable = 0;
		Tangut_Supplement { goto Tangut_Supplement; }
		* { if (YYCURSOR - 1 == limit) return Tangut_Supplement; else return Error; }
	*/
Kana_Extended_B:
	/*!re2c
		re2c:yyfill:enable = 0;
		Kana_Extended_B { goto Kana_Extended_B; }
		* { if (YYCURSOR - 1 == limit) return Kana_Extended_B; else return Error; }
	*/
Kana_Supplement:
	/*!re2c
		re2c:yyfill:enable = 0;
		Kana_Supplement { goto Kana_Supplement; }
		* { if (YYCURSOR - 1 == limit) return Kana_Supplement; else return Error; }
	*/
Kana_Extended_A:
	/*!re2c
		re2c:yyfill:enable = 0;
		Kana_Extended_A { goto Kana_Extended_A; }
		* { if (YYCURSOR - 1 == limit) return Kana_Extended_A; else return Error; }
	*/
Small_Kana_Extension:
	/*!re2c
		re2c:yyfill:enable = 0;
		Small_Kana_Extension { goto Small_Kana_Extension; }
		* { if (YYCURSOR - 1 == limit) return Small_Kana_Extension; else return Error; }
	*/
Nushu:
	/*!re2c
		re2c:yyfill:enable = 0;
		Nushu { goto Nushu; }
		* { if (YYCURSOR - 1 == limit) return Nushu; else return Error; }
	*/
Duployan:
	/*!re2c
		re2c:yyfill:enable = 0;
		Duployan { goto Duployan; }
		* { if (YYCURSOR - 1 == limit) return Duployan; else return Error; }
	*/
Shorthand_Format_Controls:
	/*!re2c
		re2c:yyfill:enable = 0;
		Shorthand_Format_Controls { goto Shorthand_Format_Controls; }
		* { if (YYCURSOR - 1 == limit) return Shorthand_Format_Controls; else return Error; }
	*/
Znamenny_Musical_Notation:
	/*!re2c
		re2c:yyfill:enable = 0;
		Znamenny_Musical_Notation { goto Znamenny_Musical_Notation; }
		* { if (YYCURSOR - 1 == limit) return Znamenny_Musical_Notation; else return Error; }
	*/
Byzantine_Musical_Symbols:
	/*!re2c
		re2c:yyfill:enable = 0;
		Byzantine_Musical_Symbols { goto Byzantine_Musical_Symbols; }
		* { if (YYCURSOR - 1 == limit) return Byzantine_Musical_Symbols; else return Error; }
	*/
Musical_Symbols:
	/*!re2c
		re2c:yyfill:enable = 0;
		Musical_Symbols { goto Musical_Symbols; }
		* { if (YYCURSOR - 1 == limit) return Musical_Symbols; else return Error; }
	*/
Ancient_Greek_Musical_Notation:
	/*!re2c
		re2c:yyfill:enable = 0;
		Ancient_Greek_Musical_Notation { goto Ancient_Greek_Musical_Notation; }
		* { if (YYCURSOR - 1 == limit) return Ancient_Greek_Musical_Notation; else return Error; }
	*/
Kaktovik_Numerals:
	/*!re2c
		re2c:yyfill:enable = 0;
		Kaktovik_Numerals { goto Kaktovik_Numerals; }
		* { if (YYCURSOR - 1 == limit) return Kaktovik_Numerals; else return Error; }
	*/
Mayan_Numerals:
	/*!re2c
		re2c:yyfill:enable = 0;
		Mayan_Numerals { goto Mayan_Numerals; }
		* { if (YYCURSOR - 1 == limit) return Mayan_Numerals; else return Error; }
	*/
Tai_Xuan_Jing_Symbols:
	/*!re2c
		re2c:yyfill:enable = 0;
		Tai_Xuan_Jing_Symbols { goto Tai_Xuan_Jing_Symbols; }
		* { if (YYCURSOR - 1 == limit) return Tai_Xuan_Jing_Symbols; else return Error; }
	*/
Counting_Rod_Numerals:
	/*!re2c
		re2c:yyfill:enable = 0;
		Counting_Rod_Numerals { goto Counting_Rod_Numerals; }
		* { if (YYCURSOR - 1 == limit) return Counting_Rod_Numerals; else return Error; }
	*/
Mathematical_Alphanumeric_Symbols:
	/*!re2c
		re2c:yyfill:enable = 0;
		Mathematical_Alphanumeric_Symbols { goto Mathematical_Alphanumeric_Symbols; }
		* { if (YYCURSOR - 1 == limit) return Mathematical_Alphanumeric_Symbols; else return Error; }
	*/
Sutton_SignWriting:
	/*!re2c
		re2c:yyfill:enable = 0;
		Sutton_SignWriting { goto Sutton_SignWriting; }
		* { if (YYCURSOR - 1 == limit) return Sutton_SignWriting; else return Error; }
	*/
Latin_Extended_G:
	/*!re2c
		re2c:yyfill:enable = 0;
		Latin_Extended_G { goto Latin_Extended_G; }
		* { if (YYCURSOR - 1 == limit) return Latin_Extended_G; else return Error; }
	*/
Glagolitic_Supplement:
	/*!re2c
		re2c:yyfill:enable = 0;
		Glagolitic_Supplement { goto Glagolitic_Supplement; }
		* { if (YYCURSOR - 1 == limit) return Glagolitic_Supplement; else return Error; }
	*/
Cyrillic_Extended_D:
	/*!re2c
		re2c:yyfill:enable = 0;
		Cyrillic_Extended_D { goto Cyrillic_Extended_D; }
		* { if (YYCURSOR - 1 == limit) return Cyrillic_Extended_D; else return Error; }
	*/
Nyiakeng_Puachue_Hmong:
	/*!re2c
		re2c:yyfill:enable = 0;
		Nyiakeng_Puachue_Hmong { goto Nyiakeng_Puachue_Hmong; }
		* { if (YYCURSOR - 1 == limit) return Nyiakeng_Puachue_Hmong; else return Error; }
	*/
Toto:
	/*!re2c
		re2c:yyfill:enable = 0;
		Toto { goto Toto; }
		* { if (YYCURSOR - 1 == limit) return Toto; else return Error; }
	*/
Wancho:
	/*!re2c
		re2c:yyfill:enable = 0;
		Wancho { goto Wancho; }
		* { if (YYCURSOR - 1 == limit) return Wancho; else return Error; }
	*/
Nag_Mundari:
	/*!re2c
		re2c:yyfill:enable = 0;
		Nag_Mundari { goto Nag_Mundari; }
		* { if (YYCURSOR - 1 == limit) return Nag_Mundari; else return Error; }
	*/
Ethiopic_Extended_B:
	/*!re2c
		re2c:yyfill:enable = 0;
		Ethiopic_Extended_B { goto Ethiopic_Extended_B; }
		* { if (YYCURSOR - 1 == limit) return Ethiopic_Extended_B; else return Error; }
	*/
Mende_Kikakui:
	/*!re2c
		re2c:yyfill:enable = 0;
		Mende_Kikakui { goto Mende_Kikakui; }
		* { if (YYCURSOR - 1 == limit) return Mende_Kikakui; else return Error; }
	*/
Adlam:
	/*!re2c
		re2c:yyfill:enable = 0;
		Adlam { goto Adlam; }
		* { if (YYCURSOR - 1 == limit) return Adlam; else return Error; }
	*/
Indic_Siyaq_Numbers:
	/*!re2c
		re2c:yyfill:enable = 0;
		Indic_Siyaq_Numbers { goto Indic_Siyaq_Numbers; }
		* { if (YYCURSOR - 1 == limit) return Indic_Siyaq_Numbers; else return Error; }
	*/
Ottoman_Siyaq_Numbers:
	/*!re2c
		re2c:yyfill:enable = 0;
		Ottoman_Siyaq_Numbers { goto Ottoman_Siyaq_Numbers; }
		* { if (YYCURSOR - 1 == limit) return Ottoman_Siyaq_Numbers; else return Error; }
	*/
Arabic_Mathematical_Alphabetic_Symbols:
	/*!re2c
		re2c:yyfill:enable = 0;
		Arabic_Mathematical_Alphabetic_Symbols { goto Arabic_Mathematical_Alphabetic_Symbols; }
		* { if (YYCURSOR - 1 == limit) return Arabic_Mathematical_Alphabetic_Symbols; else return Error; }
	*/
Mahjong_Tiles:
	/*!re2c
		re2c:yyfill:enable = 0;
		Mahjong_Tiles { goto Mahjong_Tiles; }
		* { if (YYCURSOR - 1 == limit) return Mahjong_Tiles; else return Error; }
	*/
Domino_Tiles:
	/*!re2c
		re2c:yyfill:enable = 0;
		Domino_Tiles { goto Domino_Tiles; }
		* { if (YYCURSOR - 1 == limit) return Domino_Tiles; else return Error; }
	*/
Playing_Cards:
	/*!re2c
		re2c:yyfill:enable = 0;
		Playing_Cards { goto Playing_Cards; }
		* { if (YYCURSOR - 1 == limit) return Playing_Cards; else return Error; }
	*/
Enclosed_Alphanumeric_Supplement:
	/*!re2c
		re2c:yyfill:enable = 0;
		Enclosed_Alphanumeric_Supplement { goto Enclosed_Alphanumeric_Supplement; }
		* { if (YYCURSOR - 1 == limit) return Enclosed_Alphanumeric_Supplement; else return Error; }
	*/
Enclosed_Ideographic_Supplement:
	/*!re2c
		re2c:yyfill:enable = 0;
		Enclosed_Ideographic_Supplement { goto Enclosed_Ideographic_Supplement; }
		* { if (YYCURSOR - 1 == limit) return Enclosed_Ideographic_Supplement; else return Error; }
	*/
Miscellaneous_Symbols_and_Pictographs:
	/*!re2c
		re2c:yyfill:enable = 0;
		Miscellaneous_Symbols_and_Pictographs { goto Miscellaneous_Symbols_and_Pictographs; }
		* { if (YYCURSOR - 1 == limit) return Miscellaneous_Symbols_and_Pictographs; else return Error; }
	*/
Emoticons:
	/*!re2c
		re2c:yyfill:enable = 0;
		Emoticons { goto Emoticons; }
		* { if (YYCURSOR - 1 == limit) return Emoticons; else return Error; }
	*/
Ornamental_Dingbats:
	/*!re2c
		re2c:yyfill:enable = 0;
		Ornamental_Dingbats { goto Ornamental_Dingbats; }
		* { if (YYCURSOR - 1 == limit) return Ornamental_Dingbats; else return Error; }
	*/
Transport_and_Map_Symbols:
	/*!re2c
		re2c:yyfill:enable = 0;
		Transport_and_Map_Symbols { goto Transport_and_Map_Symbols; }
		* { if (YYCURSOR - 1 == limit) return Transport_and_Map_Symbols; else return Error; }
	*/
Alchemical_Symbols:
	/*!re2c
		re2c:yyfill:enable = 0;
		Alchemical_Symbols { goto Alchemical_Symbols; }
		* { if (YYCURSOR - 1 == limit) return Alchemical_Symbols; else return Error; }
	*/
Geometric_Shapes_Extended:
	/*!re2c
		re2c:yyfill:enable = 0;
		Geometric_Shapes_Extended { goto Geometric_Shapes_Extended; }
		* { if (YYCURSOR - 1 == limit) return Geometric_Shapes_Extended; else return Error; }
	*/
Supplemental_Arrows_C:
	/*!re2c
		re2c:yyfill:enable = 0;
		Supplemental_Arrows_C { goto Supplemental_Arrows_C; }
		* { if (YYCURSOR - 1 == limit) return Supplemental_Arrows_C; else return Error; }
	*/
Supplemental_Symbols_and_Pictographs:
	/*!re2c
		re2c:yyfill:enable = 0;
		Supplemental_Symbols_and_Pictographs { goto Supplemental_Symbols_and_Pictographs; }
		* { if (YYCURSOR - 1 == limit) return Supplemental_Symbols_and_Pictographs; else return Error; }
	*/
Chess_Symbols:
	/*!re2c
		re2c:yyfill:enable = 0;
		Chess_Symbols { goto Chess_Symbols; }
		* { if (YYCURSOR - 1 == limit) return Chess_Symbols; else return Error; }
	*/
Symbols_and_Pictographs_Extended_A:
	/*!re2c
		re2c:yyfill:enable = 0;
		Symbols_and_Pictographs_Extended_A { goto Symbols_and_Pictographs_Extended_A; }
		* { if (YYCURSOR - 1 == limit) return Symbols_and_Pictographs_Extended_A; else return Error; }
	*/
Symbols_for_Legacy_Computing:
	/*!re2c
		re2c:yyfill:enable = 0;
		Symbols_for_Legacy_Computing { goto Symbols_for_Legacy_Computing; }
		* { if (YYCURSOR - 1 == limit) return Symbols_for_Legacy_Computing; else return Error; }
	*/
CJK_Unified_Ideographs_Extension_B:
	/*!re2c
		re2c:yyfill:enable = 0;
		CJK_Unified_Ideographs_Extension_B { goto CJK_Unified_Ideographs_Extension_B; }
		* { if (YYCURSOR - 1 == limit) return CJK_Unified_Ideographs_Extension_B; else return Error; }
	*/
CJK_Unified_Ideographs_Extension_C:
	/*!re2c
		re2c:yyfill:enable = 0;
		CJK_Unified_Ideographs_Extension_C { goto CJK_Unified_Ideographs_Extension_C; }
		* { if (YYCURSOR - 1 == limit) return CJK_Unified_Ideographs_Extension_C; else return Error; }
	*/
CJK_Unified_Ideographs_Extension_D:
	/*!re2c
		re2c:yyfill:enable = 0;
		CJK_Unified_Ideographs_Extension_D { goto CJK_Unified_Ideographs_Extension_D; }
		* { if (YYCURSOR - 1 == limit) return CJK_Unified_Ideographs_Extension_D; else return Error; }
	*/
CJK_Unified_Ideographs_Extension_E:
	/*!re2c
		re2c:yyfill:enable = 0;
		CJK_Unified_Ideographs_Extension_E { goto CJK_Unified_Ideographs_Extension_E; }
		* { if (YYCURSOR - 1 == limit) return CJK_Unified_Ideographs_Extension_E; else return Error; }
	*/
CJK_Unified_Ideographs_Extension_F:
	/*!re2c
		re2c:yyfill:enable = 0;
		CJK_Unified_Ideographs_Extension_F { goto CJK_Unified_Ideographs_Extension_F; }
		* { if (YYCURSOR - 1 == limit) return CJK_Unified_Ideographs_Extension_F; else return Error; }
	*/
CJK_Unified_Ideographs_Extension_I:
	/*!re2c
		re2c:yyfill:enable = 0;
		CJK_Unified_Ideographs_Extension_I { goto CJK_Unified_Ideographs_Extension_I; }
		* { if (YYCURSOR - 1 == limit) return CJK_Unified_Ideographs_Extension_I; else return Error; }
	*/
CJK_Compatibility_Ideographs_Supplement:
	/*!re2c
		re2c:yyfill:enable = 0;
		CJK_Compatibility_Ideographs_Supplement { goto CJK_Compatibility_Ideographs_Supplement; }
		* { if (YYCURSOR - 1 == limit) return CJK_Compatibility_Ideographs_Supplement; else return Error; }
	*/
CJK_Unified_Ideographs_Extension_G:
	/*!re2c
		re2c:yyfill:enable = 0;
		CJK_Unified_Ideographs_Extension_G { goto CJK_Unified_Ideographs_Extension_G; }
		* { if (YYCURSOR - 1 == limit) return CJK_Unified_Ideographs_Extension_G; else return Error; }
	*/
CJK_Unified_Ideographs_Extension_H:
	/*!re2c
		re2c:yyfill:enable = 0;
		CJK_Unified_Ideographs_Extension_H { goto CJK_Unified_Ideographs_Extension_H; }
		* { if (YYCURSOR - 1 == limit) return CJK_Unified_Ideographs_Extension_H; else return Error; }
	*/
Tags:
	/*!re2c
		re2c:yyfill:enable = 0;
		Tags { goto Tags; }
		* { if (YYCURSOR - 1 == limit) return Tags; else return Error; }
	*/
Variation_Selectors_Supplement:
	/*!re2c
		re2c:yyfill:enable = 0;
		Variation_Selectors_Supplement { goto Variation_Selectors_Supplement; }
		* { if (YYCURSOR - 1 == limit) return Variation_Selectors_Supplement; else return Error; }
	*/
Supplementary_Private_Use_Area_A:
	/*!re2c
		re2c:yyfill:enable = 0;
		Supplementary_Private_Use_Area_A { goto Supplementary_Private_Use_Area_A; }
		* { if (YYCURSOR - 1 == limit) return Supplementary_Private_Use_Area_A; else return Error; }
	*/
Supplementary_Private_Use_Area_B:
	/*!re2c
		re2c:yyfill:enable = 0;
		Supplementary_Private_Use_Area_B { goto Supplementary_Private_Use_Area_B; }
		* { if (YYCURSOR - 1 == limit) return Supplementary_Private_Use_Area_B; else return Error; }
	*/
}

static const uint32_t chars_Basic_Latin[] = {0x0,0x7f};
static const uint32_t chars_Latin_1_Supplement[] = {0x80,0xff};
static const uint32_t chars_Latin_Extended_A[] = {0x100,0x17f};
static const uint32_t chars_Latin_Extended_B[] = {0x180,0x24f};
static const uint32_t chars_IPA_Extensions[] = {0x250,0x2af};
static const uint32_t chars_Spacing_Modifier_Letters[] = {0x2b0,0x2ff};
static const uint32_t chars_Combining_Diacritical_Marks[] = {0x300,0x36f};
static const uint32_t chars_Greek_and_Coptic[] = {0x370,0x3ff};
static const uint32_t chars_Cyrillic[] = {0x400,0x4ff};
static const uint32_t chars_Cyrillic_Supplement[] = {0x500,0x52f};
static const uint32_t chars_Armenian[] = {0x530,0x58f};
static const uint32_t chars_Hebrew[] = {0x590,0x5ff};
static const uint32_t chars_Arabic[] = {0x600,0x6ff};
static const uint32_t chars_Syriac[] = {0x700,0x74f};
static const uint32_t chars_Arabic_Supplement[] = {0x750,0x77f};
static const uint32_t chars_Thaana[] = {0x780,0x7bf};
static const uint32_t chars_NKo[] = {0x7c0,0x7ff};
static const uint32_t chars_Samaritan[] = {0x800,0x83f};
static const uint32_t chars_Mandaic[] = {0x840,0x85f};
static const uint32_t chars_Syriac_Supplement[] = {0x860,0x86f};
static const uint32_t chars_Arabic_Extended_B[] = {0x870,0x89f};
static const uint32_t chars_Arabic_Extended_A[] = {0x8a0,0x8ff};
static const uint32_t chars_Devanagari[] = {0x900,0x97f};
static const uint32_t chars_Bengali[] = {0x980,0x9ff};
static const uint32_t chars_Gurmukhi[] = {0xa00,0xa7f};
static const uint32_t chars_Gujarati[] = {0xa80,0xaff};
static const uint32_t chars_Oriya[] = {0xb00,0xb7f};
static const uint32_t chars_Tamil[] = {0xb80,0xbff};
static const uint32_t chars_Telugu[] = {0xc00,0xc7f};
static const uint32_t chars_Kannada[] = {0xc80,0xcff};
static const uint32_t chars_Malayalam[] = {0xd00,0xd7f};
static const uint32_t chars_Sinhala[] = {0xd80,0xdff};
static const uint32_t chars_Thai[] = {0xe00,0xe7f};
static const uint32_t chars_Lao[] = {0xe80,0xeff};
static const uint32_t chars_Tibetan[] = {0xf00,0xfff};
static const uint32_t chars_Myanmar[] = {0x1000,0x109f};
static const uint32_t chars_Georgian[] = {0x10a0,0x10ff};
static const uint32_t chars_Hangul_Jamo[] = {0x1100,0x11ff};
static const uint32_t chars_Ethiopic[] = {0x1200,0x137f};
static const uint32_t chars_Ethiopic_Supplement[] = {0x1380,0x139f};
static const uint32_t chars_Cherokee[] = {0x13a0,0x13ff};
static const uint32_t chars_Unified_Canadian_Aboriginal_Syllabics[] = {0x1400,0x167f};
static const uint32_t chars_Ogham[] = {0x1680,0x169f};
static const uint32_t chars_Runic[] = {0x16a0,0x16ff};
static const uint32_t chars_Tagalog[] = {0x1700,0x171f};
static const uint32_t chars_Hanunoo[] = {0x1720,0x173f};
static const uint32_t chars_Buhid[] = {0x1740,0x175f};
static const uint32_t chars_Tagbanwa[] = {0x1760,0x177f};
static const uint32_t chars_Khmer[] = {0x1780,0x17ff};
static const uint32_t chars_Mongolian[] = {0x1800,0x18af};
static const uint32_t chars_Unified_Canadian_Aboriginal_Syllabics_Extended[] = {0x18b0,0x18ff};
static const uint32_t chars_Limbu[] = {0x1900,0x194f};
static const uint32_t chars_Tai_Le[] = {0x1950,0x197f};
static const uint32_t chars_New_Tai_Lue[] = {0x1980,0x19df};
static const uint32_t chars_Khmer_Symbols[] = {0x19e0,0x19ff};
static const uint32_t chars_Buginese[] = {0x1a00,0x1a1f};
static const uint32_t chars_Tai_Tham[] = {0x1a20,0x1aaf};
static const uint32_t chars_Combining_Diacritical_Marks_Extended[] = {0x1ab0,0x1aff};
static const uint32_t chars_Balinese[] = {0x1b00,0x1b7f};
static const uint32_t chars_Sundanese[] = {0x1b80,0x1bbf};
static const uint32_t chars_Batak[] = {0x1bc0,0x1bff};
static const uint32_t chars_Lepcha[] = {0x1c00,0x1c4f};
static const uint32_t chars_Ol_Chiki[] = {0x1c50,0x1c7f};
static const uint32_t chars_Cyrillic_Extended_C[] = {0x1c80,0x1c8f};
static const uint32_t chars_Georgian_Extended[] = {0x1c90,0x1cbf};
static const uint32_t chars_Sundanese_Supplement[] = {0x1cc0,0x1ccf};
static const uint32_t chars_Vedic_Extensions[] = {0x1cd0,0x1cff};
static const uint32_t chars_Phonetic_Extensions[] = {0x1d00,0x1d7f};
static const uint32_t chars_Phonetic_Extensions_Supplement[] = {0x1d80,0x1dbf};
static const uint32_t chars_Combining_Diacritical_Marks_Supplement[] = {0x1dc0,0x1dff};
static const uint32_t chars_Latin_Extended_Additional[] = {0x1e00,0x1eff};
static const uint32_t chars_Greek_Extended[] = {0x1f00,0x1fff};
static const uint32_t chars_General_Punctuation[] = {0x2000,0x206f};
static const uint32_t chars_Superscripts_and_Subscripts[] = {0x2070,0x209f};
static const uint32_t chars_Currency_Symbols[] = {0x20a0,0x20cf};
static const uint32_t chars_Combining_Diacritical_Marks_for_Symbols[] = {0x20d0,0x20ff};
static const uint32_t chars_Letterlike_Symbols[] = {0x2100,0x214f};
static const uint32_t chars_Number_Forms[] = {0x2150,0x218f};
static const uint32_t chars_Arrows[] = {0x2190,0x21ff};
static const uint32_t chars_Mathematical_Operators[] = {0x2200,0x22ff};
static const uint32_t chars_Miscellaneous_Technical[] = {0x2300,0x23ff};
static const uint32_t chars_Control_Pictures[] = {0x2400,0x243f};
static const uint32_t chars_Optical_Character_Recognition[] = {0x2440,0x245f};
static const uint32_t chars_Enclosed_Alphanumerics[] = {0x2460,0x24ff};
static const uint32_t chars_Box_Drawing[] = {0x2500,0x257f};
static const uint32_t chars_Block_Elements[] = {0x2580,0x259f};
static const uint32_t chars_Geometric_Shapes[] = {0x25a0,0x25ff};
static const uint32_t chars_Miscellaneous_Symbols[] = {0x2600,0x26ff};
static const uint32_t chars_Dingbats[] = {0x2700,0x27bf};
static const uint32_t chars_Miscellaneous_Mathematical_Symbols_A[] = {0x27c0,0x27ef};
static const uint32_t chars_Supplemental_Arrows_A[] = {0x27f0,0x27ff};
static const uint32_t chars_Braille_Patterns[] = {0x2800,0x28ff};
static const uint32_t chars_Supplemental_Arrows_B[] = {0x2900,0x297f};
static const uint32_t chars_Miscellaneous_Mathematical_Symbols_B[] = {0x2980,0x29ff};
static const uint32_t chars_Supplemental_Mathematical_Operators[] = {0x2a00,0x2aff};
static const uint32_t chars_Miscellaneous_Symbols_and_Arrows[] = {0x2b00,0x2bff};
static const uint32_t chars_Glagolitic[] = {0x2c00,0x2c5f};
static const uint32_t chars_Latin_Extended_C[] = {0x2c60,0x2c7f};
static const uint32_t chars_Coptic[] = {0x2c80,0x2cff};
static const uint32_t chars_Georgian_Supplement[] = {0x2d00,0x2d2f};
static const uint32_t chars_Tifinagh[] = {0x2d30,0x2d7f};
static const uint32_t chars_Ethiopic_Extended[] = {0x2d80,0x2ddf};
static const uint32_t chars_Cyrillic_Extended_A[] = {0x2de0,0x2dff};
static const uint32_t chars_Supplemental_Punctuation[] = {0x2e00,0x2e7f};
static const uint32_t chars_CJK_Radicals_Supplement[] = {0x2e80,0x2eff};
static const uint32_t chars_Kangxi_Radicals[] = {0x2f00,0x2fdf};
static const uint32_t chars_Ideographic_Description_Characters[] = {0x2ff0,0x2fff};
static const uint32_t chars_CJK_Symbols_and_Punctuation[] = {0x3000,0x303f};
static const uint32_t chars_Hiragana[] = {0x3040,0x309f};
static const uint32_t chars_Katakana[] = {0x30a0,0x30ff};
static const uint32_t chars_Bopomofo[] = {0x3100,0x312f};
static const uint32_t chars_Hangul_Compatibility_Jamo[] = {0x3130,0x318f};
static const uint32_t chars_Kanbun[] = {0x3190,0x319f};
static const uint32_t chars_Bopomofo_Extended[] = {0x31a0,0x31bf};
static const uint32_t chars_CJK_Strokes[] = {0x31c0,0x31ef};
static const uint32_t chars_Katakana_Phonetic_Extensions[] = {0x31f0,0x31ff};
static const uint32_t chars_Enclosed_CJK_Letters_and_Months[] = {0x3200,0x32ff};
static const uint32_t chars_CJK_Compatibility[] = {0x3300,0x33ff};
static const uint32_t chars_CJK_Unified_Ideographs_Extension_A[] = {0x3400,0x4dbf};
static const uint32_t chars_Yijing_Hexagram_Symbols[] = {0x4dc0,0x4dff};
static const uint32_t chars_CJK_Unified_Ideographs[] = {0x4e00,0x9fff};
static const uint32_t chars_Yi_Syllables[] = {0xa000,0xa48f};
static const uint32_t chars_Yi_Radicals[] = {0xa490,0xa4cf};
static const uint32_t chars_Lisu[] = {0xa4d0,0xa4ff};
static const uint32_t chars_Vai[] = {0xa500,0xa63f};
static const uint32_t chars_Cyrillic_Extended_B[] = {0xa640,0xa69f};
static const uint32_t chars_Bamum[] = {0xa6a0,0xa6ff};
static const uint32_t chars_Modifier_Tone_Letters[] = {0xa700,0xa71f};
static const uint32_t chars_Latin_Extended_D[] = {0xa720,0xa7ff};
static const uint32_t chars_Syloti_Nagri[] = {0xa800,0xa82f};
static const uint32_t chars_Common_Indic_Number_Forms[] = {0xa830,0xa83f};
static const uint32_t chars_Phags_pa[] = {0xa840,0xa87f};
static const uint32_t chars_Saurashtra[] = {0xa880,0xa8df};
static const uint32_t chars_Devanagari_Extended[] = {0xa8e0,0xa8ff};
static const uint32_t chars_Kayah_Li[] = {0xa900,0xa92f};
static const uint32_t chars_Rejang[] = {0xa930,0xa95f};
static const uint32_t chars_Hangul_Jamo_Extended_A[] = {0xa960,0xa97f};
static const uint32_t chars_Javanese[] = {0xa980,0xa9df};
static const uint32_t chars_Myanmar_Extended_B[] = {0xa9e0,0xa9ff};
static const uint32_t chars_Cham[] = {0xaa00,0xaa5f};
static const uint32_t chars_Myanmar_Extended_A[] = {0xaa60,0xaa7f};
static const uint32_t chars_Tai_Viet[] = {0xaa80,0xaadf};
static const uint32_t chars_Meetei_Mayek_Extensions[] = {0xaae0,0xaaff};
static const uint32_t chars_Ethiopic_Extended_A[] = {0xab00,0xab2f};
static const uint32_t chars_Latin_Extended_E[] = {0xab30,0xab6f};
static const uint32_t chars_Cherokee_Supplement[] = {0xab70,0xabbf};
static const uint32_t chars_Meetei_Mayek[] = {0xabc0,0xabff};
static const uint32_t chars_Hangul_Syllables[] = {0xac00,0xd7af};
static const uint32_t chars_Hangul_Jamo_Extended_B[] = {0xd7b0,0xd7ff};
static const uint32_t chars_High_Surrogates[] = {0xd800,0xdb7f};
static const uint32_t chars_High_Private_Use_Surrogates[] = {0xdb80,0xdbff};
static const uint32_t chars_Low_Surrogates[] = {0xdc00,0xdfff};
static const uint32_t chars_Private_Use_Area[] = {0xe000,0xf8ff};
static const uint32_t chars_CJK_Compatibility_Ideographs[] = {0xf900,0xfaff};
static const uint32_t chars_Alphabetic_Presentation_Forms[] = {0xfb00,0xfb4f};
static const uint32_t chars_Arabic_Presentation_Forms_A[] = {0xfb50,0xfdff};
static const uint32_t chars_Variation_Selectors[] = {0xfe00,0xfe0f};
static const uint32_t chars_Vertical_Forms[] = {0xfe10,0xfe1f};
static const uint32_t chars_Combining_Half_Marks[] = {0xfe20,0xfe2f};
static const uint32_t chars_CJK_Compatibility_Forms[] = {0xfe30,0xfe4f};
static const uint32_t chars_Small_Form_Variants[] = {0xfe50,0xfe6f};
static const uint32_t chars_Arabic_Presentation_Forms_B[] = {0xfe70,0xfeff};
static const uint32_t chars_Halfwidth_and_Fullwidth_Forms[] = {0xff00,0xffef};
static const uint32_t chars_Specials[] = {0xfff0,0xffff};
static const uint32_t chars_Linear_B_Syllabary[] = {0x10000,0x1007f};
static const uint32_t chars_Linear_B_Ideograms[] = {0x10080,0x100ff};
static const uint32_t chars_Aegean_Numbers[] = {0x10100,0x1013f};
static const uint32_t chars_Ancient_Greek_Numbers[] = {0x10140,0x1018f};
static const uint32_t chars_Ancient_Symbols[] = {0x10190,0x101cf};
static const uint32_t chars_Phaistos_Disc[] = {0x101d0,0x101ff};
static const uint32_t chars_Lycian[] = {0x10280,0x1029f};
static const uint32_t chars_Carian[] = {0x102a0,0x102df};
static const uint32_t chars_Coptic_Epact_Numbers[] = {0x102e0,0x102ff};
static const uint32_t chars_Old_Italic[] = {0x10300,0x1032f};
static const uint32_t chars_Gothic[] = {0x10330,0x1034f};
static const uint32_t chars_Old_Permic[] = {0x10350,0x1037f};
static const uint32_t chars_Ugaritic[] = {0x10380,0x1039f};
static const uint32_t chars_Old_Persian[] = {0x103a0,0x103df};
static const uint32_t chars_Deseret[] = {0x10400,0x1044f};
static const uint32_t chars_Shavian[] = {0x10450,0x1047f};
static const uint32_t chars_Osmanya[] = {0x10480,0x104af};
static const uint32_t chars_Osage[] = {0x104b0,0x104ff};
static const uint32_t chars_Elbasan[] = {0x10500,0x1052f};
static const uint32_t chars_Caucasian_Albanian[] = {0x10530,0x1056f};
static const uint32_t chars_Vithkuqi[] = {0x10570,0x105bf};
static const uint32_t chars_Linear_A[] = {0x10600,0x1077f};
static const uint32_t chars_Latin_Extended_F[] = {0x10780,0x107bf};
static const uint32_t chars_Cypriot_Syllabary[] = {0x10800,0x1083f};
static const uint32_t chars_Imperial_Aramaic[] = {0x10840,0x1085f};
static const uint32_t chars_Palmyrene[] = {0x10860,0x1087f};
static const uint32_t chars_Nabataean[] = {0x10880,0x108af};
static const uint32_t chars_Hatran[] = {0x108e0,0x108ff};
static const uint32_t chars_Phoenician[] = {0x10900,0x1091f};
static const uint32_t chars_Lydian[] = {0x10920,0x1093f};
static const uint32_t chars_Meroitic_Hieroglyphs[] = {0x10980,0x1099f};
static const uint32_t chars_Meroitic_Cursive[] = {0x109a0,0x109ff};
static const uint32_t chars_Kharoshthi[] = {0x10a00,0x10a5f};
static const uint32_t chars_Old_South_Arabian[] = {0x10a60,0x10a7f};
static const uint32_t chars_Old_North_Arabian[] = {0x10a80,0x10a9f};
static const uint32_t chars_Manichaean[] = {0x10ac0,0x10aff};
static const uint32_t chars_Avestan[] = {0x10b00,0x10b3f};
static const uint32_t chars_Inscriptional_Parthian[] = {0x10b40,0x10b5f};
static const uint32_t chars_Inscriptional_Pahlavi[] = {0x10b60,0x10b7f};
static const uint32_t chars_Psalter_Pahlavi[] = {0x10b80,0x10baf};
static const uint32_t chars_Old_Turkic[] = {0x10c00,0x10c4f};
static const uint32_t chars_Old_Hungarian[] = {0x10c80,0x10cff};
static const uint32_t chars_Hanifi_Rohingya[] = {0x10d00,0x10d3f};
static const uint32_t chars_Rumi_Numeral_Symbols[] = {0x10e60,0x10e7f};
static const uint32_t chars_Yezidi[] = {0x10e80,0x10ebf};
static const uint32_t chars_Arabic_Extended_C[] = {0x10ec0,0x10eff};
static const uint32_t chars_Old_Sogdian[] = {0x10f00,0x10f2f};
static const uint32_t chars_Sogdian[] = {0x10f30,0x10f6f};
static const uint32_t chars_Old_Uyghur[] = {0x10f70,0x10faf};
static const uint32_t chars_Chorasmian[] = {0x10fb0,0x10fdf};
static const uint32_t chars_Elymaic[] = {0x10fe0,0x10fff};
static const uint32_t chars_Brahmi[] = {0x11000,0x1107f};
static const uint32_t chars_Kaithi[] = {0x11080,0x110cf};
static const uint32_t chars_Sora_Sompeng[] = {0x110d0,0x110ff};
static const uint32_t chars_Chakma[] = {0x11100,0x1114f};
static const uint32_t chars_Mahajani[] = {0x11150,0x1117f};
static const uint32_t chars_Sharada[] = {0x11180,0x111df};
static const uint32_t chars_Sinhala_Archaic_Numbers[] = {0x111e0,0x111ff};
static const uint32_t chars_Khojki[] = {0x11200,0x1124f};
static const uint32_t chars_Multani[] = {0x11280,0x112af};
static const uint32_t chars_Khudawadi[] = {0x112b0,0x112ff};
static const uint32_t chars_Grantha[] = {0x11300,0x1137f};
static const uint32_t chars_Newa[] = {0x11400,0x1147f};
static const uint32_t chars_Tirhuta[] = {0x11480,0x114df};
static const uint32_t chars_Siddham[] = {0x11580,0x115ff};
static const uint32_t chars_Modi[] = {0x11600,0x1165f};
static const uint32_t chars_Mongolian_Supplement[] = {0x11660,0x1167f};
static const uint32_t chars_Takri[] = {0x11680,0x116cf};
static const uint32_t chars_Ahom[] = {0x11700,0x1174f};
static const uint32_t chars_Dogra[] = {0x11800,0x1184f};
static const uint32_t chars_Warang_Citi[] = {0x118a0,0x118ff};
static const uint32_t chars_Dives_Akuru[] = {0x11900,0x1195f};
static const uint32_t chars_Nandinagari[] = {0x119a0,0x119ff};
static const uint32_t chars_Zanabazar_Square[] = {0x11a00,0x11a4f};
static const uint32_t chars_Soyombo[] = {0x11a50,0x11aaf};
static const uint32_t chars_Unified_Canadian_Aboriginal_Syllabics_Extended_A[] = {0x11ab0,0x11abf};
static const uint32_t chars_Pau_Cin_Hau[] = {0x11ac0,0x11aff};
static const uint32_t chars_Devanagari_Extended_A[] = {0x11b00,0x11b5f};
static const uint32_t chars_Bhaiksuki[] = {0x11c00,0x11c6f};
static const uint32_t chars_Marchen[] = {0x11c70,0x11cbf};
static const uint32_t chars_Masaram_Gondi[] = {0x11d00,0x11d5f};
static const uint32_t chars_Gunjala_Gondi[] = {0x11d60,0x11daf};
static const uint32_t chars_Makasar[] = {0x11ee0,0x11eff};
static const uint32_t chars_Kawi[] = {0x11f00,0x11f5f};
static const uint32_t chars_Lisu_Supplement[] = {0x11fb0,0x11fbf};
static const uint32_t chars_Tamil_Supplement[] = {0x11fc0,0x11fff};
static const uint32_t chars_Cuneiform[] = {0x12000,0x123ff};
static const uint32_t chars_Cuneiform_Numbers_and_Punctuation[] = {0x12400,0x1247f};
static const uint32_t chars_Early_Dynastic_Cuneiform[] = {0x12480,0x1254f};
static const uint32_t chars_Cypro_Minoan[] = {0x12f90,0x12fff};
static const uint32_t chars_Egyptian_Hieroglyphs[] = {0x13000,0x1342f};
static const uint32_t chars_Egyptian_Hieroglyph_Format_Controls[] = {0x13430,0x1345f};
static const uint32_t chars_Anatolian_Hieroglyphs[] = {0x14400,0x1467f};
static const uint32_t chars_Bamum_Supplement[] = {0x16800,0x16a3f};
static const uint32_t chars_Mro[] = {0x16a40,0x16a6f};
static const uint32_t chars_Tangsa[] = {0x16a70,0x16acf};
static const uint32_t chars_Bassa_Vah[] = {0x16ad0,0x16aff};
static const uint32_t chars_Pahawh_Hmong[] = {0x16b00,0x16b8f};
static const uint32_t chars_Medefaidrin[] = {0x16e40,0x16e9f};
static const uint32_t chars_Miao[] = {0x16f00,0x16f9f};
static const uint32_t chars_Ideographic_Symbols_and_Punctuation[] = {0x16fe0,0x16fff};
static const uint32_t chars_Tangut[] = {0x17000,0x187ff};
static const uint32_t chars_Tangut_Components[] = {0x18800,0x18aff};
static const uint32_t chars_Khitan_Small_Script[] = {0x18b00,0x18cff};
static const uint32_t chars_Tangut_Supplement[] = {0x18d00,0x18d7f};
static const uint32_t chars_Kana_Extended_B[] = {0x1aff0,0x1afff};
static const uint32_t chars_Kana_Supplement[] = {0x1b000,0x1b0ff};
static const uint32_t chars_Kana_Extended_A[] = {0x1b100,0x1b12f};
static const uint32_t chars_Small_Kana_Extension[] = {0x1b130,0x1b16f};
static const uint32_t chars_Nushu[] = {0x1b170,0x1b2ff};
static const uint32_t chars_Duployan[] = {0x1bc00,0x1bc9f};
static const uint32_t chars_Shorthand_Format_Controls[] = {0x1bca0,0x1bcaf};
static const uint32_t chars_Znamenny_Musical_Notation[] = {0x1cf00,0x1cfcf};
static const uint32_t chars_Byzantine_Musical_Symbols[] = {0x1d000,0x1d0ff};
static const uint32_t chars_Musical_Symbols[] = {0x1d100,0x1d1ff};
static const uint32_t chars_Ancient_Greek_Musical_Notation[] = {0x1d200,0x1d24f};
static const uint32_t chars_Kaktovik_Numerals[] = {0x1d2c0,0x1d2df};
static const uint32_t chars_Mayan_Numerals[] = {0x1d2e0,0x1d2ff};
static const uint32_t chars_Tai_Xuan_Jing_Symbols[] = {0x1d300,0x1d35f};
static const uint32_t chars_Counting_Rod_Numerals[] = {0x1d360,0x1d37f};
static const uint32_t chars_Mathematical_Alphanumeric_Symbols[] = {0x1d400,0x1d7ff};
static const uint32_t chars_Sutton_SignWriting[] = {0x1d800,0x1daaf};
static const uint32_t chars_Latin_Extended_G[] = {0x1df00,0x1dfff};
static const uint32_t chars_Glagolitic_Supplement[] = {0x1e000,0x1e02f};
static const uint32_t chars_Cyrillic_Extended_D[] = {0x1e030,0x1e08f};
static const uint32_t chars_Nyiakeng_Puachue_Hmong[] = {0x1e100,0x1e14f};
static const uint32_t chars_Toto[] = {0x1e290,0x1e2bf};
static const uint32_t chars_Wancho[] = {0x1e2c0,0x1e2ff};
static const uint32_t chars_Nag_Mundari[] = {0x1e4d0,0x1e4ff};
static const uint32_t chars_Ethiopic_Extended_B[] = {0x1e7e0,0x1e7ff};
static const uint32_t chars_Mende_Kikakui[] = {0x1e800,0x1e8df};
static const uint32_t chars_Adlam[] = {0x1e900,0x1e95f};
static const uint32_t chars_Indic_Siyaq_Numbers[] = {0x1ec70,0x1ecbf};
static const uint32_t chars_Ottoman_Siyaq_Numbers[] = {0x1ed00,0x1ed4f};
static const uint32_t chars_Arabic_Mathematical_Alphabetic_Symbols[] = {0x1ee00,0x1eeff};
static const uint32_t chars_Mahjong_Tiles[] = {0x1f000,0x1f02f};
static const uint32_t chars_Domino_Tiles[] = {0x1f030,0x1f09f};
static const uint32_t chars_Playing_Cards[] = {0x1f0a0,0x1f0ff};
static const uint32_t chars_Enclosed_Alphanumeric_Supplement[] = {0x1f100,0x1f1ff};
static const uint32_t chars_Enclosed_Ideographic_Supplement[] = {0x1f200,0x1f2ff};
static const uint32_t chars_Miscellaneous_Symbols_and_Pictographs[] = {0x1f300,0x1f5ff};
static const uint32_t chars_Emoticons[] = {0x1f600,0x1f64f};
static const uint32_t chars_Ornamental_Dingbats[] = {0x1f650,0x1f67f};
static const uint32_t chars_Transport_and_Map_Symbols[] = {0x1f680,0x1f6ff};
static const uint32_t chars_Alchemical_Symbols[] = {0x1f700,0x1f77f};
static const uint32_t chars_Geometric_Shapes_Extended[] = {0x1f780,0x1f7ff};
static const uint32_t chars_Supplemental_Arrows_C[] = {0x1f800,0x1f8ff};
static const uint32_t chars_Supplemental_Symbols_and_Pictographs[] = {0x1f900,0x1f9ff};
static const uint32_t chars_Chess_Symbols[] = {0x1fa00,0x1fa6f};
static const uint32_t chars_Symbols_and_Pictographs_Extended_A[] = {0x1fa70,0x1faff};
static const uint32_t chars_Symbols_for_Legacy_Computing[] = {0x1fb00,0x1fbff};
static const uint32_t chars_CJK_Unified_Ideographs_Extension_B[] = {0x20000,0x2a6df};
static const uint32_t chars_CJK_Unified_Ideographs_Extension_C[] = {0x2a700,0x2b73f};
static const uint32_t chars_CJK_Unified_Ideographs_Extension_D[] = {0x2b740,0x2b81f};
static const uint32_t chars_CJK_Unified_Ideographs_Extension_E[] = {0x2b820,0x2ceaf};
static const uint32_t chars_CJK_Unified_Ideographs_Extension_F[] = {0x2ceb0,0x2ebef};
static const uint32_t chars_CJK_Unified_Ideographs_Extension_I[] = {0x2ebf0,0x2ee5f};
static const uint32_t chars_CJK_Compatibility_Ideographs_Supplement[] = {0x2f800,0x2fa1f};
static const uint32_t chars_CJK_Unified_Ideographs_Extension_G[] = {0x30000,0x3134f};
static const uint32_t chars_CJK_Unified_Ideographs_Extension_H[] = {0x31350,0x323af};
static const uint32_t chars_Tags[] = {0xe0000,0xe007f};
static const uint32_t chars_Variation_Selectors_Supplement[] = {0xe0100,0xe01ef};
static const uint32_t chars_Supplementary_Private_Use_Area_A[] = {0xf0000,0xfffff};
static const uint32_t chars_Supplementary_Private_Use_Area_B[] = {0x100000,0x10ffff};

static uint32_t encode_utf32(uint32_t first, uint32_t last, uint32_t* s) {
	uint32_t* const s0 = s;
	for (uint32_t i = first; i <= last; ++i) *s++ = i;
	for (uint32_t i = 0; i < 1; ++i) *s++ = (first == 0) ? 0xFFFFffff : 0;
	return s - s0;
}

int main() {
	YYCTYPE *buffer_Basic_Latin = new YYCTYPE[129];
	uint32_t buffer_Basic_Latin_len = encode_utf32(chars_Basic_Latin[0], chars_Basic_Latin[1], buffer_Basic_Latin) - 1;
	if (scan(buffer_Basic_Latin, buffer_Basic_Latin + buffer_Basic_Latin_len, Basic_Latin) != Basic_Latin)
		printf("test 'Basic_Latin' failed\n");
	delete[] buffer_Basic_Latin;

	YYCTYPE *buffer_Latin_1_Supplement = new YYCTYPE[129];
	uint32_t buffer_Latin_1_Supplement_len = encode_utf32(chars_Latin_1_Supplement[0], chars_Latin_1_Supplement[1], buffer_Latin_1_Supplement) - 1;
	if (scan(buffer_Latin_1_Supplement, buffer_Latin_1_Supplement + buffer_Latin_1_Supplement_len, Latin_1_Supplement) != Latin_1_Supplement)
		printf("test 'Latin_1_Supplement' failed\n");
	delete[] buffer_Latin_1_Supplement;

	YYCTYPE *buffer_Latin_Extended_A = new YYCTYPE[129];
	uint32_t buffer_Latin_Extended_A_len = encode_utf32(chars_Latin_Extended_A[0], chars_Latin_Extended_A[1], buffer_Latin_Extended_A) - 1;
	if (scan(buffer_Latin_Extended_A, buffer_Latin_Extended_A + buffer_Latin_Extended_A_len, Latin_Extended_A) != Latin_Extended_A)
		printf("test 'Latin_Extended_A' failed\n");
	delete[] buffer_Latin_Extended_A;

	YYCTYPE *buffer_Latin_Extended_B = new YYCTYPE[209];
	uint32_t buffer_Latin_Extended_B_len = encode_utf32(chars_Latin_Extended_B[0], chars_Latin_Extended_B[1], buffer_Latin_Extended_B) - 1;
	if (scan(buffer_Latin_Extended_B, buffer_Latin_Extended_B + buffer_Latin_Extended_B_len, Latin_Extended_B) != Latin_Extended_B)
		printf("test 'Latin_Extended_B' failed\n");
	delete[] buffer_Latin_Extended_B;

	YYCTYPE *buffer_IPA_Extensions = new YYCTYPE[97];
	uint32_t buffer_IPA_Extensions_len = encode_utf32(chars_IPA_Extensions[0], chars_IPA_Extensions[1], buffer_IPA_Extensions) - 1;
	if (scan(buffer_IPA_Extensions, buffer_IPA_Extensions + buffer_IPA_Extensions_len, IPA_Extensions) != IPA_Extensions)
		printf("test 'IPA_Extensions' failed\n");
	delete[] buffer_IPA_Extensions;

	YYCTYPE *buffer_Spacing_Modifier_Letters = new YYCTYPE[81];
	uint32_t buffer_Spacing_Modifier_Letters_len = encode_utf32(chars_Spacing_Modifier_Letters[0], chars_Spacing_Modifier_Letters[1], buffer_Spacing_Modifier_Letters) - 1;
	if (scan(buffer_Spacing_Modifier_Letters, buffer_Spacing_Modifier_Letters + buffer_Spacing_Modifier_Letters_len, Spacing_Modifier_Letters) != Spacing_Modifier_Letters)
		printf("test 'Spacing_Modifier_Letters' failed\n");
	delete[] buffer_Spacing_Modifier_Letters;

	YYCTYPE *buffer_Combining_Diacritical_Marks = new YYCTYPE[113];
	uint32_t buffer_Combining_Diacritical_Marks_len = encode_utf32(chars_Combining_Diacritical_Marks[0], chars_Combining_Diacritical_Marks[1], buffer_Combining_Diacritical_Marks) - 1;
	if (scan(buffer_Combining_Diacritical_Marks, buffer_Combining_Diacritical_Marks + buffer_Combining_Diacritical_Marks_len, Combining_Diacritical_Marks) != Combining_Diacritical_Marks)
		printf("test 'Combining_Diacritical_Marks' failed\n");
	delete[] buffer_Combining_Diacritical_Marks;

	YYCTYPE *buffer_Greek_and_Coptic = new YYCTYPE[145];
	uint32_t buffer_Greek_and_Coptic_len = encode_utf32(chars_Greek_and_Coptic[0], chars_Greek_and_Coptic[1], buffer_Greek_and_Coptic) - 1;
	if (scan(buffer_Greek_and_Coptic, buffer_Greek_and_Coptic + buffer_Greek_and_Coptic_len, Greek_and_Coptic) != Greek_and_Coptic)
		printf("test 'Greek_and_Coptic' failed\n");
	delete[] buffer_Greek_and_Coptic;

	YYCTYPE *buffer_Cyrillic = new YYCTYPE[257];
	uint32_t buffer_Cyrillic_len = encode_utf32(chars_Cyrillic[0], chars_Cyrillic[1], buffer_Cyrillic) - 1;
	if (scan(buffer_Cyrillic, buffer_Cyrillic + buffer_Cyrillic_len, Cyrillic) != Cyrillic)
		printf("test 'Cyrillic' failed\n");
	delete[] buffer_Cyrillic;

	YYCTYPE *buffer_Cyrillic_Supplement = new YYCTYPE[49];
	uint32_t buffer_Cyrillic_Supplement_len = encode_utf32(chars_Cyrillic_Supplement[0], chars_Cyrillic_Supplement[1], buffer_Cyrillic_Supplement) - 1;
	if (scan(buffer_Cyrillic_Supplement, buffer_Cyrillic_Supplement + buffer_Cyrillic_Supplement_len, Cyrillic_Supplement) != Cyrillic_Supplement)
		printf("test 'Cyrillic_Supplement' failed\n");
	delete[] buffer_Cyrillic_Supplement;

	YYCTYPE *buffer_Armenian = new YYCTYPE[97];
	uint32_t buffer_Armenian_len = encode_utf32(chars_Armenian[0], chars_Armenian[1], buffer_Armenian) - 1;
	if (scan(buffer_Armenian, buffer_Armenian + buffer_Armenian_len, Armenian) != Armenian)
		printf("test 'Armenian' failed\n");
	delete[] buffer_Armenian;

	YYCTYPE *buffer_Hebrew = new YYCTYPE[113];
	uint32_t buffer_Hebrew_len = encode_utf32(chars_Hebrew[0], chars_Hebrew[1], buffer_Hebrew) - 1;
	if (scan(buffer_Hebrew, buffer_Hebrew + buffer_Hebrew_len, Hebrew) != Hebrew)
		printf("test 'Hebrew' failed\n");
	delete[] buffer_Hebrew;

	YYCTYPE *buffer_Arabic = new YYCTYPE[257];
	uint32_t buffer_Arabic_len = encode_utf32(chars_Arabic[0], chars_Arabic[1], buffer_Arabic) - 1;
	if (scan(buffer_Arabic, buffer_Arabic + buffer_Arabic_len, Arabic) != Arabic)
		printf("test 'Arabic' failed\n");
	delete[] buffer_Arabic;

	YYCTYPE *buffer_Syriac = new YYCTYPE[81];
	uint32_t buffer_Syriac_len = encode_utf32(chars_Syriac[0], chars_Syriac[1], buffer_Syriac) - 1;
	if (scan(buffer_Syriac, buffer_Syriac + buffer_Syriac_len, Syriac) != Syriac)
		printf("test 'Syriac' failed\n");
	delete[] buffer_Syriac;

	YYCTYPE *buffer_Arabic_Supplement = new YYCTYPE[49];
	uint32_t buffer_Arabic_Supplement_len = encode_utf32(chars_Arabic_Supplement[0], chars_Arabic_Supplement[1], buffer_Arabic_Supplement) - 1;
	if (scan(buffer_Arabic_Supplement, buffer_Arabic_Supplement + buffer_Arabic_Supplement_len, Arabic_Supplement) != Arabic_Supplement)
		printf("test 'Arabic_Supplement' failed\n");
	delete[] buffer_Arabic_Supplement;

	YYCTYPE *buffer_Thaana = new YYCTYPE[65];
	uint32_t buffer_Thaana_len = encode_utf32(chars_Thaana[0], chars_Thaana[1], buffer_Thaana) - 1;
	if (scan(buffer_Thaana, buffer_Thaana + buffer_Thaana_len, Thaana) != Thaana)
		printf("test 'Thaana' failed\n");
	delete[] buffer_Thaana;

	YYCTYPE *buffer_NKo = new YYCTYPE[65];
	uint32_t buffer_NKo_len = encode_utf32(chars_NKo[0], chars_NKo[1], buffer_NKo) - 1;
	if (scan(buffer_NKo, buffer_NKo + buffer_NKo_len, NKo) != NKo)
		printf("test 'NKo' failed\n");
	delete[] buffer_NKo;

	YYCTYPE *buffer_Samaritan = new YYCTYPE[65];
	uint32_t buffer_Samaritan_len = encode_utf32(chars_Samaritan[0], chars_Samaritan[1], buffer_Samaritan) - 1;
	if (scan(buffer_Samaritan, buffer_Samaritan + buffer_Samaritan_len, Samaritan) != Samaritan)
		printf("test 'Samaritan' failed\n");
	delete[] buffer_Samaritan;

	YYCTYPE *buffer_Mandaic = new YYCTYPE[33];
	uint32_t buffer_Mandaic_len = encode_utf32(chars_Mandaic[0], chars_Mandaic[1], buffer_Mandaic) - 1;
	if (scan(buffer_Mandaic, buffer_Mandaic + buffer_Mandaic_len, Mandaic) != Mandaic)
		printf("test 'Mandaic' failed\n");
	delete[] buffer_Mandaic;

	YYCTYPE *buffer_Syriac_Supplement = new YYCTYPE[17];
	uint32_t buffer_Syriac_Supplement_len = encode_utf32(chars_Syriac_Supplement[0], chars_Syriac_Supplement[1], buffer_Syriac_Supplement) - 1;
	if (scan(buffer_Syriac_Supplement, buffer_Syriac_Supplement + buffer_Syriac_Supplement_len, Syriac_Supplement) != Syriac_Supplement)
		printf("test 'Syriac_Supplement' failed\n");
	delete[] buffer_Syriac_Supplement;

	YYCTYPE *buffer_Arabic_Extended_B = new YYCTYPE[49];
	uint32_t buffer_Arabic_Extended_B_len = encode_utf32(chars_Arabic_Extended_B[0], chars_Arabic_Extended_B[1], buffer_Arabic_Extended_B) - 1;
	if (scan(buffer_Arabic_Extended_B, buffer_Arabic_Extended_B + buffer_Arabic_Extended_B_len, Arabic_Extended_B) != Arabic_Extended_B)
		printf("test 'Arabic_Extended_B' failed\n");
	delete[] buffer_Arabic_Extended_B;

	YYCTYPE *buffer_Arabic_Extended_A = new YYCTYPE[97];
	uint32_t buffer_Arabic_Extended_A_len = encode_utf32(chars_Arabic_Extended_A[0], chars_Arabic_Extended_A[1], buffer_Arabic_Extended_A) - 1;
	if (scan(buffer_Arabic_Extended_A, buffer_Arabic_Extended_A + buffer_Arabic_Extended_A_len, Arabic_Extended_A) != Arabic_Extended_A)
		printf("test 'Arabic_Extended_A' failed\n");
	delete[] buffer_Arabic_Extended_A;

	YYCTYPE *buffer_Devanagari = new YYCTYPE[129];
	uint32_t buffer_Devanagari_len = encode_utf32(chars_Devanagari[0], chars_Devanagari[1], buffer_Devanagari) - 1;
	if (scan(buffer_Devanagari, buffer_Devanagari + buffer_Devanagari_len, Devanagari) != Devanagari)
		printf("test 'Devanagari' failed\n");
	delete[] buffer_Devanagari;

	YYCTYPE *buffer_Bengali = new YYCTYPE[129];
	uint32_t buffer_Bengali_len = encode_utf32(chars_Bengali[0], chars_Bengali[1], buffer_Bengali) - 1;
	if (scan(buffer_Bengali, buffer_Bengali + buffer_Bengali_len, Bengali) != Bengali)
		printf("test 'Bengali' failed\n");
	delete[] buffer_Bengali;

	YYCTYPE *buffer_Gurmukhi = new YYCTYPE[129];
	uint32_t buffer_Gurmukhi_len = encode_utf32(chars_Gurmukhi[0], chars_Gurmukhi[1], buffer_Gurmukhi) - 1;
	if (scan(buffer_Gurmukhi, buffer_Gurmukhi + buffer_Gurmukhi_len, Gurmukhi) != Gurmukhi)
		printf("test 'Gurmukhi' failed\n");
	delete[] buffer_Gurmukhi;

	YYCTYPE *buffer_Gujarati = new YYCTYPE[129];
	uint32_t buffer_Gujarati_len = encode_utf32(chars_Gujarati[0], chars_Gujarati[1], buffer_Gujarati) - 1;
	if (scan(buffer_Gujarati, buffer_Gujarati + buffer_Gujarati_len, Gujarati) != Gujarati)
		printf("test 'Gujarati' failed\n");
	delete[] buffer_Gujarati;

	YYCTYPE *buffer_Oriya = new YYCTYPE[129];
	uint32_t buffer_Oriya_len = encode_utf32(chars_Oriya[0], chars_Oriya[1], buffer_Oriya) - 1;
	if (scan(buffer_Oriya, buffer_Oriya + buffer_Oriya_len, Oriya) != Oriya)
		printf("test 'Oriya' failed\n");
	delete[] buffer_Oriya;

	YYCTYPE *buffer_Tamil = new YYCTYPE[129];
	uint32_t buffer_Tamil_len = encode_utf32(chars_Tamil[0], chars_Tamil[1], buffer_Tamil) - 1;
	if (scan(buffer_Tamil, buffer_Tamil + buffer_Tamil_len, Tamil) != Tamil)
		printf("test 'Tamil' failed\n");
	delete[] buffer_Tamil;

	YYCTYPE *buffer_Telugu = new YYCTYPE[129];
	uint32_t buffer_Telugu_len = encode_utf32(chars_Telugu[0], chars_Telugu[1], buffer_Telugu) - 1;
	if (scan(buffer_Telugu, buffer_Telugu + buffer_Telugu_len, Telugu) != Telugu)
		printf("test 'Telugu' failed\n");
	delete[] buffer_Telugu;

	YYCTYPE *buffer_Kannada = new YYCTYPE[129];
	uint32_t buffer_Kannada_len = encode_utf32(chars_Kannada[0], chars_Kannada[1], buffer_Kannada) - 1;
	if (scan(buffer_Kannada, buffer_Kannada + buffer_Kannada_len, Kannada) != Kannada)
		printf("test 'Kannada' failed\n");
	delete[] buffer_Kannada;

	YYCTYPE *buffer_Malayalam = new YYCTYPE[129];
	uint32_t buffer_Malayalam_len = encode_utf32(chars_Malayalam[0], chars_Malayalam[1], buffer_Malayalam) - 1;
	if (scan(buffer_Malayalam, buffer_Malayalam + buffer_Malayalam_len, Malayalam) != Malayalam)
		printf("test 'Malayalam' failed\n");
	delete[] buffer_Malayalam;

	YYCTYPE *buffer_Sinhala = new YYCTYPE[129];
	uint32_t buffer_Sinhala_len = encode_utf32(chars_Sinhala[0], chars_Sinhala[1], buffer_Sinhala) - 1;
	if (scan(buffer_Sinhala, buffer_Sinhala + buffer_Sinhala_len, Sinhala) != Sinhala)
		printf("test 'Sinhala' failed\n");
	delete[] buffer_Sinhala;

	YYCTYPE *buffer_Thai = new YYCTYPE[129];
	uint32_t buffer_Thai_len = encode_utf32(chars_Thai[0], chars_Thai[1], buffer_Thai) - 1;
	if (scan(buffer_Thai, buffer_Thai + buffer_Thai_len, Thai) != Thai)
		printf("test 'Thai' failed\n");
	delete[] buffer_Thai;

	YYCTYPE *buffer_Lao = new YYCTYPE[129];
	uint32_t buffer_Lao_len = encode_utf32(chars_Lao[0], chars_Lao[1], buffer_Lao) - 1;
	if (scan(buffer_Lao, buffer_Lao + buffer_Lao_len, Lao) != Lao)
		printf("test 'Lao' failed\n");
	delete[] buffer_Lao;

	YYCTYPE *buffer_Tibetan = new YYCTYPE[257];
	uint32_t buffer_Tibetan_len = encode_utf32(chars_Tibetan[0], chars_Tibetan[1], buffer_Tibetan) - 1;
	if (scan(buffer_Tibetan, buffer_Tibetan + buffer_Tibetan_len, Tibetan) != Tibetan)
		printf("test 'Tibetan' failed\n");
	delete[] buffer_Tibetan;

	YYCTYPE *buffer_Myanmar = new YYCTYPE[161];
	uint32_t buffer_Myanmar_len = encode_utf32(chars_Myanmar[0], chars_Myanmar[1], buffer_Myanmar) - 1;
	if (scan(buffer_Myanmar, buffer_Myanmar + buffer_Myanmar_len, Myanmar) != Myanmar)
		printf("test 'Myanmar' failed\n");
	delete[] buffer_Myanmar;

	YYCTYPE *buffer_Georgian = new YYCTYPE[97];
	uint32_t buffer_Georgian_len = encode_utf32(chars_Georgian[0], chars_Georgian[1], buffer_Georgian) - 1;
	if (scan(buffer_Georgian, buffer_Georgian + buffer_Georgian_len, Georgian) != Georgian)
		printf("test 'Georgian' failed\n");
	delete[] buffer_Georgian;

	YYCTYPE *buffer_Hangul_Jamo = new YYCTYPE[257];
	uint32_t buffer_Hangul_Jamo_len = encode_utf32(chars_Hangul_Jamo[0], chars_Hangul_Jamo[1], buffer_Hangul_Jamo) - 1;
	if (scan(buffer_Hangul_Jamo, buffer_Hangul_Jamo + buffer_Hangul_Jamo_len, Hangul_Jamo) != Hangul_Jamo)
		printf("test 'Hangul_Jamo' failed\n");
	delete[] buffer_Hangul_Jamo;

	YYCTYPE *buffer_Ethiopic = new YYCTYPE[385];
	uint32_t buffer_Ethiopic_len = encode_utf32(chars_Ethiopic[0], chars_Ethiopic[1], buffer_Ethiopic) - 1;
	if (scan(buffer_Ethiopic, buffer_Ethiopic + buffer_Ethiopic_len, Ethiopic) != Ethiopic)
		printf("test 'Ethiopic' failed\n");
	delete[] buffer_Ethiopic;

	YYCTYPE *buffer_Ethiopic_Supplement = new YYCTYPE[33];
	uint32_t buffer_Ethiopic_Supplement_len = encode_utf32(chars_Ethiopic_Supplement[0], chars_Ethiopic_Supplement[1], buffer_Ethiopic_Supplement) - 1;
	if (scan(buffer_Ethiopic_Supplement, buffer_Ethiopic_Supplement + buffer_Ethiopic_Supplement_len, Ethiopic_Supplement) != Ethiopic_Supplement)
		printf("test 'Ethiopic_Supplement' failed\n");
	delete[] buffer_Ethiopic_Supplement;

	YYCTYPE *buffer_Cherokee = new YYCTYPE[97];
	uint32_t buffer_Cherokee_len = encode_utf32(chars_Cherokee[0], chars_Cherokee[1], buffer_Cherokee) - 1;
	if (scan(buffer_Cherokee, buffer_Cherokee + buffer_Cherokee_len, Cherokee) != Cherokee)
		printf("test 'Cherokee' failed\n");
	delete[] buffer_Cherokee;

	YYCTYPE *buffer_Unified_Canadian_Aboriginal_Syllabics = new YYCTYPE[641];
	uint32_t buffer_Unified_Canadian_Aboriginal_Syllabics_len = encode_utf32(chars_Unified_Canadian_Aboriginal_Syllabics[0], chars_Unified_Canadian_Aboriginal_Syllabics[1], buffer_Unified_Canadian_Aboriginal_Syllabics) - 1;
	if (scan(buffer_Unified_Canadian_Aboriginal_Syllabics, buffer_Unified_Canadian_Aboriginal_Syllabics + buffer_Unified_Canadian_Aboriginal_Syllabics_len, Unified_Canadian_Aboriginal_Syllabics) != Unified_Canadian_Aboriginal_Syllabics)
		printf("test 'Unified_Canadian_Aboriginal_Syllabics' failed\n");
	delete[] buffer_Unified_Canadian_Aboriginal_Syllabics;

	YYCTYPE *buffer_Ogham = new YYCTYPE[33];
	uint32_t buffer_Ogham_len = encode_utf32(chars_Ogham[0], chars_Ogham[1], buffer_Ogham) - 1;
	if (scan(buffer_Ogham, buffer_Ogham + buffer_Ogham_len, Ogham) != Ogham)
		printf("test 'Ogham' failed\n");
	delete[] buffer_Ogham;

	YYCTYPE *buffer_Runic = new YYCTYPE[97];
	uint32_t buffer_Runic_len = encode_utf32(chars_Runic[0], chars_Runic[1], buffer_Runic) - 1;
	if (scan(buffer_Runic, buffer_Runic + buffer_Runic_len, Runic) != Runic)
		printf("test 'Runic' failed\n");
	delete[] buffer_Runic;

	YYCTYPE *buffer_Tagalog = new YYCTYPE[33];
	uint32_t buffer_Tagalog_len = encode_utf32(chars_Tagalog[0], chars_Tagalog[1], buffer_Tagalog) - 1;
	if (scan(buffer_Tagalog, buffer_Tagalog + buffer_Tagalog_len, Tagalog) != Tagalog)
		printf("test 'Tagalog' failed\n");
	delete[] buffer_Tagalog;

	YYCTYPE *buffer_Hanunoo = new YYCTYPE[33];
	uint32_t buffer_Hanunoo_len = encode_utf32(chars_Hanunoo[0], chars_Hanunoo[1], buffer_Hanunoo) - 1;
	if (scan(buffer_Hanunoo, buffer_Hanunoo + buffer_Hanunoo_len, Hanunoo) != Hanunoo)
		printf("test 'Hanunoo' failed\n");
	delete[] buffer_Hanunoo;

	YYCTYPE *buffer_Buhid = new YYCTYPE[33];
	uint32_t buffer_Buhid_len = encode_utf32(chars_Buhid[0], chars_Buhid[1], buffer_Buhid) - 1;
	if (scan(buffer_Buhid, buffer_Buhid + buffer_Buhid_len, Buhid) != Buhid)
		printf("test 'Buhid' failed\n");
	delete[] buffer_Buhid;

	YYCTYPE *buffer_Tagbanwa = new YYCTYPE[33];
	uint32_t buffer_Tagbanwa_len = encode_utf32(chars_Tagbanwa[0], chars_Tagbanwa[1], buffer_Tagbanwa) - 1;
	if (scan(buffer_Tagbanwa, buffer_Tagbanwa + buffer_Tagbanwa_len, Tagbanwa) != Tagbanwa)
		printf("test 'Tagbanwa' failed\n");
	delete[] buffer_Tagbanwa;

	YYCTYPE *buffer_Khmer = new YYCTYPE[129];
	uint32_t buffer_Khmer_len = encode_utf32(chars_Khmer[0], chars_Khmer[1], buffer_Khmer) - 1;
	if (scan(buffer_Khmer, buffer_Khmer + buffer_Khmer_len, Khmer) != Khmer)
		printf("test 'Khmer' failed\n");
	delete[] buffer_Khmer;

	YYCTYPE *buffer_Mongolian = new YYCTYPE[177];
	uint32_t buffer_Mongolian_len = encode_utf32(chars_Mongolian[0], chars_Mongolian[1], buffer_Mongolian) - 1;
	if (scan(buffer_Mongolian, buffer_Mongolian + buffer_Mongolian_len, Mongolian) != Mongolian)
		printf("test 'Mongolian' failed\n");
	delete[] buffer_Mongolian;

	YYCTYPE *buffer_Unified_Canadian_Aboriginal_Syllabics_Extended = new YYCTYPE[81];
	uint32_t buffer_Unified_Canadian_Aboriginal_Syllabics_Extended_len = encode_utf32(chars_Unified_Canadian_Aboriginal_Syllabics_Extended[0], chars_Unified_Canadian_Aboriginal_Syllabics_Extended[1], buffer_Unified_Canadian_Aboriginal_Syllabics_Extended) - 1;
	if (scan(buffer_Unified_Canadian_Aboriginal_Syllabics_Extended, buffer_Unified_Canadian_Aboriginal_Syllabics_Extended + buffer_Unified_Canadian_Aboriginal_Syllabics_Extended_len, Unified_Canadian_Aboriginal_Syllabics_Extended) != Unified_Canadian_Aboriginal_Syllabics_Extended)
		printf("test 'Unified_Canadian_Aboriginal_Syllabics_Extended' failed\n");
	delete[] buffer_Unified_Canadian_Aboriginal_Syllabics_Extended;

	YYCTYPE *buffer_Limbu = new YYCTYPE[81];
	uint32_t buffer_Limbu_len = encode_utf32(chars_Limbu[0], chars_Limbu[1], buffer_Limbu) - 1;
	if (scan(buffer_Limbu, buffer_Limbu + buffer_Limbu_len, Limbu) != Limbu)
		printf("test 'Limbu' failed\n");
	delete[] buffer_Limbu;

	YYCTYPE *buffer_Tai_Le = new YYCTYPE[49];
	uint32_t buffer_Tai_Le_len = encode_utf32(chars_Tai_Le[0], chars_Tai_Le[1], buffer_Tai_Le) - 1;
	if (scan(buffer_Tai_Le, buffer_Tai_Le + buffer_Tai_Le_len, Tai_Le) != Tai_Le)
		printf("test 'Tai_Le' failed\n");
	delete[] buffer_Tai_Le;

	YYCTYPE *buffer_New_Tai_Lue = new YYCTYPE[97];
	uint32_t buffer_New_Tai_Lue_len = encode_utf32(chars_New_Tai_Lue[0], chars_New_Tai_Lue[1], buffer_New_Tai_Lue) - 1;
	if (scan(buffer_New_Tai_Lue, buffer_New_Tai_Lue + buffer_New_Tai_Lue_len, New_Tai_Lue) != New_Tai_Lue)
		printf("test 'New_Tai_Lue' failed\n");
	delete[] buffer_New_Tai_Lue;

	YYCTYPE *buffer_Khmer_Symbols = new YYCTYPE[33];
	uint32_t buffer_Khmer_Symbols_len = encode_utf32(chars_Khmer_Symbols[0], chars_Khmer_Symbols[1], buffer_Khmer_Symbols) - 1;
	if (scan(buffer_Khmer_Symbols, buffer_Khmer_Symbols + buffer_Khmer_Symbols_len, Khmer_Symbols) != Khmer_Symbols)
		printf("test 'Khmer_Symbols' failed\n");
	delete[] buffer_Khmer_Symbols;

	YYCTYPE *buffer_Buginese = new YYCTYPE[33];
	uint32_t buffer_Buginese_len = encode_utf32(chars_Buginese[0], chars_Buginese[1], buffer_Buginese) - 1;
	if (scan(buffer_Buginese, buffer_Buginese + buffer_Buginese_len, Buginese) != Buginese)
		printf("test 'Buginese' failed\n");
	delete[] buffer_Buginese;

	YYCTYPE *buffer_Tai_Tham = new YYCTYPE[145];
	uint32_t buffer_Tai_Tham_len = encode_utf32(chars_Tai_Tham[0], chars_Tai_Tham[1], buffer_Tai_Tham) - 1;
	if (scan(buffer_Tai_Tham, buffer_Tai_Tham + buffer_Tai_Tham_len, Tai_Tham) != Tai_Tham)
		printf("test 'Tai_Tham' failed\n");
	delete[] buffer_Tai_Tham;

	YYCTYPE *buffer_Combining_Diacritical_Marks_Extended = new YYCTYPE[81];
	uint32_t buffer_Combining_Diacritical_Marks_Extended_len = encode_utf32(chars_Combining_Diacritical_Marks_Extended[0], chars_Combining_Diacritical_Marks_Extended[1], buffer_Combining_Diacritical_Marks_Extended) - 1;
	if (scan(buffer_Combining_Diacritical_Marks_Extended, buffer_Combining_Diacritical_Marks_Extended + buffer_Combining_Diacritical_Marks_Extended_len, Combining_Diacritical_Marks_Extended) != Combining_Diacritical_Marks_Extended)
		printf("test 'Combining_Diacritical_Marks_Extended' failed\n");
	delete[] buffer_Combining_Diacritical_Marks_Extended;

	YYCTYPE *buffer_Balinese = new YYCTYPE[129];
	uint32_t buffer_Balinese_len = encode_utf32(chars_Balinese[0], chars_Balinese[1], buffer_Balinese) - 1;
	if (scan(buffer_Balinese, buffer_Balinese + buffer_Balinese_len, Balinese) != Balinese)
		printf("test 'Balinese' failed\n");
	delete[] buffer_Balinese;

	YYCTYPE *buffer_Sundanese = new YYCTYPE[65];
	uint32_t buffer_Sundanese_len = encode_utf32(chars_Sundanese[0], chars_Sundanese[1], buffer_Sundanese) - 1;
	if (scan(buffer_Sundanese, buffer_Sundanese + buffer_Sundanese_len, Sundanese) != Sundanese)
		printf("test 'Sundanese' failed\n");
	delete[] buffer_Sundanese;

	YYCTYPE *buffer_Batak = new YYCTYPE[65];
	uint32_t buffer_Batak_len = encode_utf32(chars_Batak[0], chars_Batak[1], buffer_Batak) - 1;
	if (scan(buffer_Batak, buffer_Batak + buffer_Batak_len, Batak) != Batak)
		printf("test 'Batak' failed\n");
	delete[] buffer_Batak;

	YYCTYPE *buffer_Lepcha = new YYCTYPE[81];
	uint32_t buffer_Lepcha_len = encode_utf32(chars_Lepcha[0], chars_Lepcha[1], buffer_Lepcha) - 1;
	if (scan(buffer_Lepcha, buffer_Lepcha + buffer_Lepcha_len, Lepcha) != Lepcha)
		printf("test 'Lepcha' failed\n");
	delete[] buffer_Lepcha;

	YYCTYPE *buffer_Ol_Chiki = new YYCTYPE[49];
	uint32_t buffer_Ol_Chiki_len = encode_utf32(chars_Ol_Chiki[0], chars_Ol_Chiki[1], buffer_Ol_Chiki) - 1;
	if (scan(buffer_Ol_Chiki, buffer_Ol_Chiki + buffer_Ol_Chiki_len, Ol_Chiki) != Ol_Chiki)
		printf("test 'Ol_Chiki' failed\n");
	delete[] buffer_Ol_Chiki;

	YYCTYPE *buffer_Cyrillic_Extended_C = new YYCTYPE[17];
	uint32_t buffer_Cyrillic_Extended_C_len = encode_utf32(chars_Cyrillic_Extended_C[0], chars_Cyrillic_Extended_C[1], buffer_Cyrillic_Extended_C) - 1;
	if (scan(buffer_Cyrillic_Extended_C, buffer_Cyrillic_Extended_C + buffer_Cyrillic_Extended_C_len, Cyrillic_Extended_C) != Cyrillic_Extended_C)
		printf("test 'Cyrillic_Extended_C' failed\n");
	delete[] buffer_Cyrillic_Extended_C;

	YYCTYPE *buffer_Georgian_Extended = new YYCTYPE[49];
	uint32_t buffer_Georgian_Extended_len = encode_utf32(chars_Georgian_Extended[0], chars_Georgian_Extended[1], buffer_Georgian_Extended) - 1;
	if (scan(buffer_Georgian_Extended, buffer_Georgian_Extended + buffer_Georgian_Extended_len, Georgian_Extended) != Georgian_Extended)
		printf("test 'Georgian_Extended' failed\n");
	delete[] buffer_Georgian_Extended;

	YYCTYPE *buffer_Sundanese_Supplement = new YYCTYPE[17];
	uint32_t buffer_Sundanese_Supplement_len = encode_utf32(chars_Sundanese_Supplement[0], chars_Sundanese_Supplement[1], buffer_Sundanese_Supplement) - 1;
	if (scan(buffer_Sundanese_Supplement, buffer_Sundanese_Supplement + buffer_Sundanese_Supplement_len, Sundanese_Supplement) != Sundanese_Supplement)
		printf("test 'Sundanese_Supplement' failed\n");
	delete[] buffer_Sundanese_Supplement;

	YYCTYPE *buffer_Vedic_Extensions = new YYCTYPE[49];
	uint32_t buffer_Vedic_Extensions_len = encode_utf32(chars_Vedic_Extensions[0], chars_Vedic_Extensions[1], buffer_Vedic_Extensions) - 1;
	if (scan(buffer_Vedic_Extensions, buffer_Vedic_Extensions + buffer_Vedic_Extensions_len, Vedic_Extensions) != Vedic_Extensions)
		printf("test 'Vedic_Extensions' failed\n");
	delete[] buffer_Vedic_Extensions;

	YYCTYPE *buffer_Phonetic_Extensions = new YYCTYPE[129];
	uint32_t buffer_Phonetic_Extensions_len = encode_utf32(chars_Phonetic_Extensions[0], chars_Phonetic_Extensions[1], buffer_Phonetic_Extensions) - 1;
	if (scan(buffer_Phonetic_Extensions, buffer_Phonetic_Extensions + buffer_Phonetic_Extensions_len, Phonetic_Extensions) != Phonetic_Extensions)
		printf("test 'Phonetic_Extensions' failed\n");
	delete[] buffer_Phonetic_Extensions;

	YYCTYPE *buffer_Phonetic_Extensions_Supplement = new YYCTYPE[65];
	uint32_t buffer_Phonetic_Extensions_Supplement_len = encode_utf32(chars_Phonetic_Extensions_Supplement[0], chars_Phonetic_Extensions_Supplement[1], buffer_Phonetic_Extensions_Supplement) - 1;
	if (scan(buffer_Phonetic_Extensions_Supplement, buffer_Phonetic_Extensions_Supplement + buffer_Phonetic_Extensions_Supplement_len, Phonetic_Extensions_Supplement) != Phonetic_Extensions_Supplement)
		printf("test 'Phonetic_Extensions_Supplement' failed\n");
	delete[] buffer_Phonetic_Extensions_Supplement;

	YYCTYPE *buffer_Combining_Diacritical_Marks_Supplement = new YYCTYPE[65];
	uint32_t buffer_Combining_Diacritical_Marks_Supplement_len = encode_utf32(chars_Combining_Diacritical_Marks_Supplement[0], chars_Combining_Diacritical_Marks_Supplement[1], buffer_Combining_Diacritical_Marks_Supplement) - 1;
	if (scan(buffer_Combining_Diacritical_Marks_Supplement, buffer_Combining_Diacritical_Marks_Supplement + buffer_Combining_Diacritical_Marks_Supplement_len, Combining_Diacritical_Marks_Supplement) != Combining_Diacritical_Marks_Supplement)
		printf("test 'Combining_Diacritical_Marks_Supplement' failed\n");
	delete[] buffer_Combining_Diacritical_Marks_Supplement;

	YYCTYPE *buffer_Latin_Extended_Additional = new YYCTYPE[257];
	uint32_t buffer_Latin_Extended_Additional_len = encode_utf32(chars_Latin_Extended_Additional[0], chars_Latin_Extended_Additional[1], buffer_Latin_Extended_Additional) - 1;
	if (scan(buffer_Latin_Extended_Additional, buffer_Latin_Extended_Additional + buffer_Latin_Extended_Additional_len, Latin_Extended_Additional) != Latin_Extended_Additional)
		printf("test 'Latin_Extended_Additional' failed\n");
	delete[] buffer_Latin_Extended_Additional;

	YYCTYPE *buffer_Greek_Extended = new YYCTYPE[257];
	uint32_t buffer_Greek_Extended_len = encode_utf32(chars_Greek_Extended[0], chars_Greek_Extended[1], buffer_Greek_Extended) - 1;
	if (scan(buffer_Greek_Extended, buffer_Greek_Extended + buffer_Greek_Extended_len, Greek_Extended) != Greek_Extended)
		printf("test 'Greek_Extended' failed\n");
	delete[] buffer_Greek_Extended;

	YYCTYPE *buffer_General_Punctuation = new YYCTYPE[113];
	uint32_t buffer_General_Punctuation_len = encode_utf32(chars_General_Punctuation[0], chars_General_Punctuation[1], buffer_General_Punctuation) - 1;
	if (scan(buffer_General_Punctuation, buffer_General_Punctuation + buffer_General_Punctuation_len, General_Punctuation) != General_Punctuation)
		printf("test 'General_Punctuation' failed\n");
	delete[] buffer_General_Punctuation;

	YYCTYPE *buffer_Superscripts_and_Subscripts = new YYCTYPE[49];
	uint32_t buffer_Superscripts_and_Subscripts_len = encode_utf32(chars_Superscripts_and_Subscripts[0], chars_Superscripts_and_Subscripts[1], buffer_Superscripts_and_Subscripts) - 1;
	if (scan(buffer_Superscripts_and_Subscripts, buffer_Superscripts_and_Subscripts + buffer_Superscripts_and_Subscripts_len, Superscripts_and_Subscripts) != Superscripts_and_Subscripts)
		printf("test 'Superscripts_and_Subscripts' failed\n");
	delete[] buffer_Superscripts_and_Subscripts;

	YYCTYPE *buffer_Currency_Symbols = new YYCTYPE[49];
	uint32_t buffer_Currency_Symbols_len = encode_utf32(chars_Currency_Symbols[0], chars_Currency_Symbols[1], buffer_Currency_Symbols) - 1;
	if (scan(buffer_Currency_Symbols, buffer_Currency_Symbols + buffer_Currency_Symbols_len, Currency_Symbols) != Currency_Symbols)
		printf("test 'Currency_Symbols' failed\n");
	delete[] buffer_Currency_Symbols;

	YYCTYPE *buffer_Combining_Diacritical_Marks_for_Symbols = new YYCTYPE[49];
	uint32_t buffer_Combining_Diacritical_Marks_for_Symbols_len = encode_utf32(chars_Combining_Diacritical_Marks_for_Symbols[0], chars_Combining_Diacritical_Marks_for_Symbols[1], buffer_Combining_Diacritical_Marks_for_Symbols) - 1;
	if (scan(buffer_Combining_Diacritical_Marks_for_Symbols, buffer_Combining_Diacritical_Marks_for_Symbols + buffer_Combining_Diacritical_Marks_for_Symbols_len, Combining_Diacritical_Marks_for_Symbols) != Combining_Diacritical_Marks_for_Symbols)
		printf("test 'Combining_Diacritical_Marks_for_Symbols' failed\n");
	delete[] buffer_Combining_Diacritical_Marks_for_Symbols;

	YYCTYPE *buffer_Letterlike_Symbols = new YYCTYPE[81];
	uint32_t buffer_Letterlike_Symbols_len = encode_utf32(chars_Letterlike_Symbols[0], chars_Letterlike_Symbols[1], buffer_Letterlike_Symbols) - 1;
	if (scan(buffer_Letterlike_Symbols, buffer_Letterlike_Symbols + buffer_Letterlike_Symbols_len, Letterlike_Symbols) != Letterlike_Symbols)
		printf("test 'Letterlike_Symbols' failed\n");
	delete[] buffer_Letterlike_Symbols;

	YYCTYPE *buffer_Number_Forms = new YYCTYPE[65];
	uint32_t buffer_Number_Forms_len = encode_utf32(chars_Number_Forms[0], chars_Number_Forms[1], buffer_Number_Forms) - 1;
	if (scan(buffer_Number_Forms, buffer_Number_Forms + buffer_Number_Forms_len, Number_Forms) != Number_Forms)
		printf("test 'Number_Forms' failed\n");
	delete[] buffer_Number_Forms;

	YYCTYPE *buffer_Arrows = new YYCTYPE[113];
	uint32_t buffer_Arrows_len = encode_utf32(chars_Arrows[0], chars_Arrows[1], buffer_Arrows) - 1;
	if (scan(buffer_Arrows, buffer_Arrows + buffer_Arrows_len, Arrows) != Arrows)
		printf("test 'Arrows' failed\n");
	delete[] buffer_Arrows;

	YYCTYPE *buffer_Mathematical_Operators = new YYCTYPE[257];
	uint32_t buffer_Mathematical_Operators_len = encode_utf32(chars_Mathematical_Operators[0], chars_Mathematical_Operators[1], buffer_Mathematical_Operators) - 1;
	if (scan(buffer_Mathematical_Operators, buffer_Mathematical_Operators + buffer_Mathematical_Operators_len, Mathematical_Operators) != Mathematical_Operators)
		printf("test 'Mathematical_Operators' failed\n");
	delete[] buffer_Mathematical_Operators;

	YYCTYPE *buffer_Miscellaneous_Technical = new YYCTYPE[257];
	uint32_t buffer_Miscellaneous_Technical_len = encode_utf32(chars_Miscellaneous_Technical[0], chars_Miscellaneous_Technical[1], buffer_Miscellaneous_Technical) - 1;
	if (scan(buffer_Miscellaneous_Technical, buffer_Miscellaneous_Technical + buffer_Miscellaneous_Technical_len, Miscellaneous_Technical) != Miscellaneous_Technical)
		printf("test 'Miscellaneous_Technical' failed\n");
	delete[] buffer_Miscellaneous_Technical;

	YYCTYPE *buffer_Control_Pictures = new YYCTYPE[65];
	uint32_t buffer_Control_Pictures_len = encode_utf32(chars_Control_Pictures[0], chars_Control_Pictures[1], buffer_Control_Pictures) - 1;
	if (scan(buffer_Control_Pictures, buffer_Control_Pictures + buffer_Control_Pictures_len, Control_Pictures) != Control_Pictures)
		printf("test 'Control_Pictures' failed\n");
	delete[] buffer_Control_Pictures;

	YYCTYPE *buffer_Optical_Character_Recognition = new YYCTYPE[33];
	uint32_t buffer_Optical_Character_Recognition_len = encode_utf32(chars_Optical_Character_Recognition[0], chars_Optical_Character_Recognition[1], buffer_Optical_Character_Recognition) - 1;
	if (scan(buffer_Optical_Character_Recognition, buffer_Optical_Character_Recognition + buffer_Optical_Character_Recognition_len, Optical_Character_Recognition) != Optical_Character_Recognition)
		printf("test 'Optical_Character_Recognition' failed\n");
	delete[] buffer_Optical_Character_Recognition;

	YYCTYPE *buffer_Enclosed_Alphanumerics = new YYCTYPE[161];
	uint32_t buffer_Enclosed_Alphanumerics_len = encode_utf32(chars_Enclosed_Alphanumerics[0], chars_Enclosed_Alphanumerics[1], buffer_Enclosed_Alphanumerics) - 1;
	if (scan(buffer_Enclosed_Alphanumerics, buffer_Enclosed_Alphanumerics + buffer_Enclosed_Alphanumerics_len, Enclosed_Alphanumerics) != Enclosed_Alphanumerics)
		printf("test 'Enclosed_Alphanumerics' failed\n");
	delete[] buffer_Enclosed_Alphanumerics;

	YYCTYPE *buffer_Box_Drawing = new YYCTYPE[129];
	uint32_t buffer_Box_Drawing_len = encode_utf32(chars_Box_Drawing[0], chars_Box_Drawing[1], buffer_Box_Drawing) - 1;
	if (scan(buffer_Box_Drawing, buffer_Box_Drawing + buffer_Box_Drawing_len, Box_Drawing) != Box_Drawing)
		printf("test 'Box_Drawing' failed\n");
	delete[] buffer_Box_Drawing;

	YYCTYPE *buffer_Block_Elements = new YYCTYPE[33];
	uint32_t buffer_Block_Elements_len = encode_utf32(chars_Block_Elements[0], chars_Block_Elements[1], buffer_Block_Elements) - 1;
	if (scan(buffer_Block_Elements, buffer_Block_Elements + buffer_Block_Elements_len, Block_Elements) != Block_Elements)
		printf("test 'Block_Elements' failed\n");
	delete[] buffer_Block_Elements;

	YYCTYPE *buffer_Geometric_Shapes = new YYCTYPE[97];
	uint32_t buffer_Geometric_Shapes_len = encode_utf32(chars_Geometric_Shapes[0], chars_Geometric_Shapes[1], buffer_Geometric_Shapes) - 1;
	if (scan(buffer_Geometric_Shapes, buffer_Geometric_Shapes + buffer_Geometric_Shapes_len, Geometric_Shapes) != Geometric_Shapes)
		printf("test 'Geometric_Shapes' failed\n");
	delete[] buffer_Geometric_Shapes;

	YYCTYPE *buffer_Miscellaneous_Symbols = new YYCTYPE[257];
	uint32_t buffer_Miscellaneous_Symbols_len = encode_utf32(chars_Miscellaneous_Symbols[0], chars_Miscellaneous_Symbols[1], buffer_Miscellaneous_Symbols) - 1;
	if (scan(buffer_Miscellaneous_Symbols, buffer_Miscellaneous_Symbols + buffer_Miscellaneous_Symbols_len, Miscellaneous_Symbols) != Miscellaneous_Symbols)
		printf("test 'Miscellaneous_Symbols' failed\n");
	delete[] buffer_Miscellaneous_Symbols;

	YYCTYPE *buffer_Dingbats = new YYCTYPE[193];
	uint32_t buffer_Dingbats_len = encode_utf32(chars_Dingbats[0], chars_Dingbats[1], buffer_Dingbats) - 1;
	if (scan(buffer_Dingbats, buffer_Dingbats + buffer_Dingbats_len, Dingbats) != Dingbats)
		printf("test 'Dingbats' failed\n");
	delete[] buffer_Dingbats;

	YYCTYPE *buffer_Miscellaneous_Mathematical_Symbols_A = new YYCTYPE[49];
	uint32_t buffer_Miscellaneous_Mathematical_Symbols_A_len = encode_utf32(chars_Miscellaneous_Mathematical_Symbols_A[0], chars_Miscellaneous_Mathematical_Symbols_A[1], buffer_Miscellaneous_Mathematical_Symbols_A) - 1;
	if (scan(buffer_Miscellaneous_Mathematical_Symbols_A, buffer_Miscellaneous_Mathematical_Symbols_A + buffer_Miscellaneous_Mathematical_Symbols_A_len, Miscellaneous_Mathematical_Symbols_A) != Miscellaneous_Mathematical_Symbols_A)
		printf("test 'Miscellaneous_Mathematical_Symbols_A' failed\n");
	delete[] buffer_Miscellaneous_Mathematical_Symbols_A;

	YYCTYPE *buffer_Supplemental_Arrows_A = new YYCTYPE[17];
	uint32_t buffer_Supplemental_Arrows_A_len = encode_utf32(chars_Supplemental_Arrows_A[0], chars_Supplemental_Arrows_A[1], buffer_Supplemental_Arrows_A) - 1;
	if (scan(buffer_Supplemental_Arrows_A, buffer_Supplemental_Arrows_A + buffer_Supplemental_Arrows_A_len, Supplemental_Arrows_A) != Supplemental_Arrows_A)
		printf("test 'Supplemental_Arrows_A' failed\n");
	delete[] buffer_Supplemental_Arrows_A;

	YYCTYPE *buffer_Braille_Patterns = new YYCTYPE[257];
	uint32_t buffer_Braille_Patterns_len = encode_utf32(chars_Braille_Patterns[0], chars_Braille_Patterns[1], buffer_Braille_Patterns) - 1;
	if (scan(buffer_Braille_Patterns, buffer_Braille_Patterns + buffer_Braille_Patterns_len, Braille_Patterns) != Braille_Patterns)
		printf("test 'Braille_Patterns' failed\n");
	delete[] buffer_Braille_Patterns;

	YYCTYPE *buffer_Supplemental_Arrows_B = new YYCTYPE[129];
	uint32_t buffer_Supplemental_Arrows_B_len = encode_utf32(chars_Supplemental_Arrows_B[0], chars_Supplemental_Arrows_B[1], buffer_Supplemental_Arrows_B) - 1;
	if (scan(buffer_Supplemental_Arrows_B, buffer_Supplemental_Arrows_B + buffer_Supplemental_Arrows_B_len, Supplemental_Arrows_B) != Supplemental_Arrows_B)
		printf("test 'Supplemental_Arrows_B' failed\n");
	delete[] buffer_Supplemental_Arrows_B;

	YYCTYPE *buffer_Miscellaneous_Mathematical_Symbols_B = new YYCTYPE[129];
	uint32_t buffer_Miscellaneous_Mathematical_Symbols_B_len = encode_utf32(chars_Miscellaneous_Mathematical_Symbols_B[0], chars_Miscellaneous_Mathematical_Symbols_B[1], buffer_Miscellaneous_Mathematical_Symbols_B) - 1;
	if (scan(buffer_Miscellaneous_Mathematical_Symbols_B, buffer_Miscellaneous_Mathematical_Symbols_B + buffer_Miscellaneous_Mathematical_Symbols_B_len, Miscellaneous_Mathematical_Symbols_B) != Miscellaneous_Mathematical_Symbols_B)
		printf("test 'Miscellaneous_Mathematical_Symbols_B' failed\n");
	delete[] buffer_Miscellaneous_Mathematical_Symbols_B;

	YYCTYPE *buffer_Supplemental_Mathematical_Operators = new YYCTYPE[257];
	uint32_t buffer_Supplemental_Mathematical_Operators_len = encode_utf32(chars_Supplemental_Mathematical_Operators[0], chars_Supplemental_Mathematical_Operators[1], buffer_Supplemental_Mathematical_Operators) - 1;
	if (scan(buffer_Supplemental_Mathematical_Operators, buffer_Supplemental_Mathematical_Operators + buffer_Supplemental_Mathematical_Operators_len, Supplemental_Mathematical_Operators) != Supplemental_Mathematical_Operators)
		printf("test 'Supplemental_Mathematical_Operators' failed\n");
	delete[] buffer_Supplemental_Mathematical_Operators;

	YYCTYPE *buffer_Miscellaneous_Symbols_and_Arrows = new YYCTYPE[257];
	uint32_t buffer_Miscellaneous_Symbols_and_Arrows_len = encode_utf32(chars_Miscellaneous_Symbols_and_Arrows[0], chars_Miscellaneous_Symbols_and_Arrows[1], buffer_Miscellaneous_Symbols_and_Arrows) - 1;
	if (scan(buffer_Miscellaneous_Symbols_and_Arrows, buffer_Miscellaneous_Symbols_and_Arrows + buffer_Miscellaneous_Symbols_and_Arrows_len, Miscellaneous_Symbols_and_Arrows) != Miscellaneous_Symbols_and_Arrows)
		printf("test 'Miscellaneous_Symbols_and_Arrows' failed\n");
	delete[] buffer_Miscellaneous_Symbols_and_Arrows;

	YYCTYPE *buffer_Glagolitic = new YYCTYPE[97];
	uint32_t buffer_Glagolitic_len = encode_utf32(chars_Glagolitic[0], chars_Glagolitic[1], buffer_Glagolitic) - 1;
	if (scan(buffer_Glagolitic, buffer_Glagolitic + buffer_Glagolitic_len, Glagolitic) != Glagolitic)
		printf("test 'Glagolitic' failed\n");
	delete[] buffer_Glagolitic;

	YYCTYPE *buffer_Latin_Extended_C = new YYCTYPE[33];
	uint32_t buffer_Latin_Extended_C_len = encode_utf32(chars_Latin_Extended_C[0], chars_Latin_Extended_C[1], buffer_Latin_Extended_C) - 1;
	if (scan(buffer_Latin_Extended_C, buffer_Latin_Extended_C + buffer_Latin_Extended_C_len, Latin_Extended_C) != Latin_Extended_C)
		printf("test 'Latin_Extended_C' failed\n");
	delete[] buffer_Latin_Extended_C;

	YYCTYPE *buffer_Coptic = new YYCTYPE[129];
	uint32_t buffer_Coptic_len = encode_utf32(chars_Coptic[0], chars_Coptic[1], buffer_Coptic) - 1;
	if (scan(buffer_Coptic, buffer_Coptic + buffer_Coptic_len, Coptic) != Coptic)
		printf("test 'Coptic' failed\n");
	delete[] buffer_Coptic;

	YYCTYPE *buffer_Georgian_Supplement = new YYCTYPE[49];
	uint32_t buffer_Georgian_Supplement_len = encode_utf32(chars_Georgian_Supplement[0], chars_Georgian_Supplement[1], buffer_Georgian_Supplement) - 1;
	if (scan(buffer_Georgian_Supplement, buffer_Georgian_Supplement + buffer_Georgian_Supplement_len, Georgian_Supplement) != Georgian_Supplement)
		printf("test 'Georgian_Supplement' failed\n");
	delete[] buffer_Georgian_Supplement;

	YYCTYPE *buffer_Tifinagh = new YYCTYPE[81];
	uint32_t buffer_Tifinagh_len = encode_utf32(chars_Tifinagh[0], chars_Tifinagh[1], buffer_Tifinagh) - 1;
	if (scan(buffer_Tifinagh, buffer_Tifinagh + buffer_Tifinagh_len, Tifinagh) != Tifinagh)
		printf("test 'Tifinagh' failed\n");
	delete[] buffer_Tifinagh;

	YYCTYPE *buffer_Ethiopic_Extended = new YYCTYPE[97];
	uint32_t buffer_Ethiopic_Extended_len = encode_utf32(chars_Ethiopic_Extended[0], chars_Ethiopic_Extended[1], buffer_Ethiopic_Extended) - 1;
	if (scan(buffer_Ethiopic_Extended, buffer_Ethiopic_Extended + buffer_Ethiopic_Extended_len, Ethiopic_Extended) != Ethiopic_Extended)
		printf("test 'Ethiopic_Extended' failed\n");
	delete[] buffer_Ethiopic_Extended;

	YYCTYPE *buffer_Cyrillic_Extended_A = new YYCTYPE[33];
	uint32_t buffer_Cyrillic_Extended_A_len = encode_utf32(chars_Cyrillic_Extended_A[0], chars_Cyrillic_Extended_A[1], buffer_Cyrillic_Extended_A) - 1;
	if (scan(buffer_Cyrillic_Extended_A, buffer_Cyrillic_Extended_A + buffer_Cyrillic_Extended_A_len, Cyrillic_Extended_A) != Cyrillic_Extended_A)
		printf("test 'Cyrillic_Extended_A' failed\n");
	delete[] buffer_Cyrillic_Extended_A;

	YYCTYPE *buffer_Supplemental_Punctuation = new YYCTYPE[129];
	uint32_t buffer_Supplemental_Punctuation_len = encode_utf32(chars_Supplemental_Punctuation[0], chars_Supplemental_Punctuation[1], buffer_Supplemental_Punctuation) - 1;
	if (scan(buffer_Supplemental_Punctuation, buffer_Supplemental_Punctuation + buffer_Supplemental_Punctuation_len, Supplemental_Punctuation) != Supplemental_Punctuation)
		printf("test 'Supplemental_Punctuation' failed\n");
	delete[] buffer_Supplemental_Punctuation;

	YYCTYPE *buffer_CJK_Radicals_Supplement = new YYCTYPE[129];
	uint32_t buffer_CJK_Radicals_Supplement_len = encode_utf32(chars_CJK_Radicals_Supplement[0], chars_CJK_Radicals_Supplement[1], buffer_CJK_Radicals_Supplement) - 1;
	if (scan(buffer_CJK_Radicals_Supplement, buffer_CJK_Radicals_Supplement + buffer_CJK_Radicals_Supplement_len, CJK_Radicals_Supplement) != CJK_Radicals_Supplement)
		printf("test 'CJK_Radicals_Supplement' failed\n");
	delete[] buffer_CJK_Radicals_Supplement;

	YYCTYPE *buffer_Kangxi_Radicals = new YYCTYPE[225];
	uint32_t buffer_Kangxi_Radicals_len = encode_utf32(chars_Kangxi_Radicals[0], chars_Kangxi_Radicals[1], buffer_Kangxi_Radicals) - 1;
	if (scan(buffer_Kangxi_Radicals, buffer_Kangxi_Radicals + buffer_Kangxi_Radicals_len, Kangxi_Radicals) != Kangxi_Radicals)
		printf("test 'Kangxi_Radicals' failed\n");
	delete[] buffer_Kangxi_Radicals;

	YYCTYPE *buffer_Ideographic_Description_Characters = new YYCTYPE[17];
	uint32_t buffer_Ideographic_Description_Characters_len = encode_utf32(chars_Ideographic_Description_Characters[0], chars_Ideographic_Description_Characters[1], buffer_Ideographic_Description_Characters) - 1;
	if (scan(buffer_Ideographic_Description_Characters, buffer_Ideographic_Description_Characters + buffer_Ideographic_Description_Characters_len, Ideographic_Description_Characters) != Ideographic_Description_Characters)
		printf("test 'Ideographic_Description_Characters' failed\n");
	delete[] buffer_Ideographic_Description_Characters;

	YYCTYPE *buffer_CJK_Symbols_and_Punctuation = new YYCTYPE[65];
	uint32_t buffer_CJK_Symbols_and_Punctuation_len = encode_utf32(chars_CJK_Symbols_and_Punctuation[0], chars_CJK_Symbols_and_Punctuation[1], buffer_CJK_Symbols_and_Punctuation) - 1;
	if (scan(buffer_CJK_Symbols_and_Punctuation, buffer_CJK_Symbols_and_Punctuation + buffer_CJK_Symbols_and_Punctuation_len, CJK_Symbols_and_Punctuation) != CJK_Symbols_and_Punctuation)
		printf("test 'CJK_Symbols_and_Punctuation' failed\n");
	delete[] buffer_CJK_Symbols_and_Punctuation;

	YYCTYPE *buffer_Hiragana = new YYCTYPE[97];
	uint32_t buffer_Hiragana_len = encode_utf32(chars_Hiragana[0], chars_Hiragana[1], buffer_Hiragana) - 1;
	if (scan(buffer_Hiragana, buffer_Hiragana + buffer_Hiragana_len, Hiragana) != Hiragana)
		printf("test 'Hiragana' failed\n");
	delete[] buffer_Hiragana;

	YYCTYPE *buffer_Katakana = new YYCTYPE[97];
	uint32_t buffer_Katakana_len = encode_utf32(chars_Katakana[0], chars_Katakana[1], buffer_Katakana) - 1;
	if (scan(buffer_Katakana, buffer_Katakana + buffer_Katakana_len, Katakana) != Katakana)
		printf("test 'Katakana' failed\n");
	delete[] buffer_Katakana;

	YYCTYPE *buffer_Bopomofo = new YYCTYPE[49];
	uint32_t buffer_Bopomofo_len = encode_utf32(chars_Bopomofo[0], chars_Bopomofo[1], buffer_Bopomofo) - 1;
	if (scan(buffer_Bopomofo, buffer_Bopomofo + buffer_Bopomofo_len, Bopomofo) != Bopomofo)
		printf("test 'Bopomofo' failed\n");
	delete[] buffer_Bopomofo;

	YYCTYPE *buffer_Hangul_Compatibility_Jamo = new YYCTYPE[97];
	uint32_t buffer_Hangul_Compatibility_Jamo_len = encode_utf32(chars_Hangul_Compatibility_Jamo[0], chars_Hangul_Compatibility_Jamo[1], buffer_Hangul_Compatibility_Jamo) - 1;
	if (scan(buffer_Hangul_Compatibility_Jamo, buffer_Hangul_Compatibility_Jamo + buffer_Hangul_Compatibility_Jamo_len, Hangul_Compatibility_Jamo) != Hangul_Compatibility_Jamo)
		printf("test 'Hangul_Compatibility_Jamo' failed\n");
	delete[] buffer_Hangul_Compatibility_Jamo;

	YYCTYPE *buffer_Kanbun = new YYCTYPE[17];
	uint32_t buffer_Kanbun_len = encode_utf32(chars_Kanbun[0], chars_Kanbun[1], buffer_Kanbun) - 1;
	if (scan(buffer_Kanbun, buffer_Kanbun + buffer_Kanbun_len, Kanbun) != Kanbun)
		printf("test 'Kanbun' failed\n");
	delete[] buffer_Kanbun;

	YYCTYPE *buffer_Bopomofo_Extended = new YYCTYPE[33];
	uint32_t buffer_Bopomofo_Extended_len = encode_utf32(chars_Bopomofo_Extended[0], chars_Bopomofo_Extended[1], buffer_Bopomofo_Extended) - 1;
	if (scan(buffer_Bopomofo_Extended, buffer_Bopomofo_Extended + buffer_Bopomofo_Extended_len, Bopomofo_Extended) != Bopomofo_Extended)
		printf("test 'Bopomofo_Extended' failed\n");
	delete[] buffer_Bopomofo_Extended;

	YYCTYPE *buffer_CJK_Strokes = new YYCTYPE[49];
	uint32_t buffer_CJK_Strokes_len = encode_utf32(chars_CJK_Strokes[0], chars_CJK_Strokes[1], buffer_CJK_Strokes) - 1;
	if (scan(buffer_CJK_Strokes, buffer_CJK_Strokes + buffer_CJK_Strokes_len, CJK_Strokes) != CJK_Strokes)
		printf("test 'CJK_Strokes' failed\n");
	delete[] buffer_CJK_Strokes;

	YYCTYPE *buffer_Katakana_Phonetic_Extensions = new YYCTYPE[17];
	uint32_t buffer_Katakana_Phonetic_Extensions_len = encode_utf32(chars_Katakana_Phonetic_Extensions[0], chars_Katakana_Phonetic_Extensions[1], buffer_Katakana_Phonetic_Extensions) - 1;
	if (scan(buffer_Katakana_Phonetic_Extensions, buffer_Katakana_Phonetic_Extensions + buffer_Katakana_Phonetic_Extensions_len, Katakana_Phonetic_Extensions) != Katakana_Phonetic_Extensions)
		printf("test 'Katakana_Phonetic_Extensions' failed\n");
	delete[] buffer_Katakana_Phonetic_Extensions;

	YYCTYPE *buffer_Enclosed_CJK_Letters_and_Months = new YYCTYPE[257];
	uint32_t buffer_Enclosed_CJK_Letters_and_Months_len = encode_utf32(chars_Enclosed_CJK_Letters_and_Months[0], chars_Enclosed_CJK_Letters_and_Months[1], buffer_Enclosed_CJK_Letters_and_Months) - 1;
	if (scan(buffer_Enclosed_CJK_Letters_and_Months, buffer_Enclosed_CJK_Letters_and_Months + buffer_Enclosed_CJK_Letters_and_Months_len, Enclosed_CJK_Letters_and_Months) != Enclosed_CJK_Letters_and_Months)
		printf("test 'Enclosed_CJK_Letters_and_Months' failed\n");
	delete[] buffer_Enclosed_CJK_Letters_and_Months;

	YYCTYPE *buffer_CJK_Compatibility = new YYCTYPE[257];
	uint32_t buffer_CJK_Compatibility_len = encode_utf32(chars_CJK_Compatibility[0], chars_CJK_Compatibility[1], buffer_CJK_Compatibility) - 1;
	if (scan(buffer_CJK_Compatibility, buffer_CJK_Compatibility + buffer_CJK_Compatibility_len, CJK_Compatibility) != CJK_Compatibility)
		printf("test 'CJK_Compatibility' failed\n");
	delete[] buffer_CJK_Compatibility;

	YYCTYPE *buffer_CJK_Unified_Ideographs_Extension_A = new YYCTYPE[6593];
	uint32_t buffer_CJK_Unified_Ideographs_Extension_A_len = encode_utf32(chars_CJK_Unified_Ideographs_Extension_A[0], chars_CJK_Unified_Ideographs_Extension_A[1], buffer_CJK_Unified_Ideographs_Extension_A) - 1;
	if (scan(buffer_CJK_Unified_Ideographs_Extension_A, buffer_CJK_Unified_Ideographs_Extension_A + buffer_CJK_Unified_Ideographs_Extension_A_len, CJK_Unified_Ideographs_Extension_A) != CJK_Unified_Ideographs_Extension_A)
		printf("test 'CJK_Unified_Ideographs_Extension_A' failed\n");
	delete[] buffer_CJK_Unified_Ideographs_Extension_A;

	YYCTYPE *buffer_Yijing_Hexagram_Symbols = new YYCTYPE[65];
	uint32_t buffer_Yijing_Hexagram_Symbols_len = encode_utf32(chars_Yijing_Hexagram_Symbols[0], chars_Yijing_Hexagram_Symbols[1], buffer_Yijing_Hexagram_Symbols) - 1;
	if (scan(buffer_Yijing_Hexagram_Symbols, buffer_Yijing_Hexagram_Symbols + buffer_Yijing_Hexagram_Symbols_len, Yijing_Hexagram_Symbols) != Yijing_Hexagram_Symbols)
		printf("test 'Yijing_Hexagram_Symbols' failed\n");
	delete[] buffer_Yijing_Hexagram_Symbols;

	YYCTYPE *buffer_CJK_Unified_Ideographs = new YYCTYPE[20993];
	uint32_t buffer_CJK_Unified_Ideographs_len = encode_utf32(chars_CJK_Unified_Ideographs[0], chars_CJK_Unified_Ideographs[1], buffer_CJK_Unified_Ideographs) - 1;
	if (scan(buffer_CJK_Unified_Ideographs, buffer_CJK_Unified_Ideographs + buffer_CJK_Unified_Ideographs_len, CJK_Unified_Ideographs) != CJK_Unified_Ideographs)
		printf("test 'CJK_Unified_Ideographs' failed\n");
	delete[] buffer_CJK_Unified_Ideographs;

	YYCTYPE *buffer_Yi_Syllables = new YYCTYPE[1169];
	uint32_t buffer_Yi_Syllables_len = encode_utf32(chars_Yi_Syllables[0], chars_Yi_Syllables[1], buffer_Yi_Syllables) - 1;
	if (scan(buffer_Yi_Syllables, buffer_Yi_Syllables + buffer_Yi_Syllables_len, Yi_Syllables) != Yi_Syllables)
		printf("test 'Yi_Syllables' failed\n");
	delete[] buffer_Yi_Syllables;

	YYCTYPE *buffer_Yi_Radicals = new YYCTYPE[65];
	uint32_t buffer_Yi_Radicals_len = encode_utf32(chars_Yi_Radicals[0], chars_Yi_Radicals[1], buffer_Yi_Radicals) - 1;
	if (scan(buffer_Yi_Radicals, buffer_Yi_Radicals + buffer_Yi_Radicals_len, Yi_Radicals) != Yi_Radicals)
		printf("test 'Yi_Radicals' failed\n");
	delete[] buffer_Yi_Radicals;

	YYCTYPE *buffer_Lisu = new YYCTYPE[49];
	uint32_t buffer_Lisu_len = encode_utf32(chars_Lisu[0], chars_Lisu[1], buffer_Lisu) - 1;
	if (scan(buffer_Lisu, buffer_Lisu + buffer_Lisu_len, Lisu) != Lisu)
		printf("test 'Lisu' failed\n");
	delete[] buffer_Lisu;

	YYCTYPE *buffer_Vai = new YYCTYPE[321];
	uint32_t buffer_Vai_len = encode_utf32(chars_Vai[0], chars_Vai[1], buffer_Vai) - 1;
	if (scan(buffer_Vai, buffer_Vai + buffer_Vai_len, Vai) != Vai)
		printf("test 'Vai' failed\n");
	delete[] buffer_Vai;

	YYCTYPE *buffer_Cyrillic_Extended_B = new YYCTYPE[97];
	uint32_t buffer_Cyrillic_Extended_B_len = encode_utf32(chars_Cyrillic_Extended_B[0], chars_Cyrillic_Extended_B[1], buffer_Cyrillic_Extended_B) - 1;
	if (scan(buffer_Cyrillic_Extended_B, buffer_Cyrillic_Extended_B + buffer_Cyrillic_Extended_B_len, Cyrillic_Extended_B) != Cyrillic_Extended_B)
		printf("test 'Cyrillic_Extended_B' failed\n");
	delete[] buffer_Cyrillic_Extended_B;

	YYCTYPE *buffer_Bamum = new YYCTYPE[97];
	uint32_t buffer_Bamum_len = encode_utf32(chars_Bamum[0], chars_Bamum[1], buffer_Bamum) - 1;
	if (scan(buffer_Bamum, buffer_Bamum + buffer_Bamum_len, Bamum) != Bamum)
		printf("test 'Bamum' failed\n");
	delete[] buffer_Bamum;

	YYCTYPE *buffer_Modifier_Tone_Letters = new YYCTYPE[33];
	uint32_t buffer_Modifier_Tone_Letters_len = encode_utf32(chars_Modifier_Tone_Letters[0], chars_Modifier_Tone_Letters[1], buffer_Modifier_Tone_Letters) - 1;
	if (scan(buffer_Modifier_Tone_Letters, buffer_Modifier_Tone_Letters + buffer_Modifier_Tone_Letters_len, Modifier_Tone_Letters) != Modifier_Tone_Letters)
		printf("test 'Modifier_Tone_Letters' failed\n");
	delete[] buffer_Modifier_Tone_Letters;

	YYCTYPE *buffer_Latin_Extended_D = new YYCTYPE[225];
	uint32_t buffer_Latin_Extended_D_len = encode_utf32(chars_Latin_Extended_D[0], chars_Latin_Extended_D[1], buffer_Latin_Extended_D) - 1;
	if (scan(buffer_Latin_Extended_D, buffer_Latin_Extended_D + buffer_Latin_Extended_D_len, Latin_Extended_D) != Latin_Extended_D)
		printf("test 'Latin_Extended_D' failed\n");
	delete[] buffer_Latin_Extended_D;

	YYCTYPE *buffer_Syloti_Nagri = new YYCTYPE[49];
	uint32_t buffer_Syloti_Nagri_len = encode_utf32(chars_Syloti_Nagri[0], chars_Syloti_Nagri[1], buffer_Syloti_Nagri) - 1;
	if (scan(buffer_Syloti_Nagri, buffer_Syloti_Nagri + buffer_Syloti_Nagri_len, Syloti_Nagri) != Syloti_Nagri)
		printf("test 'Syloti_Nagri' failed\n");
	delete[] buffer_Syloti_Nagri;

	YYCTYPE *buffer_Common_Indic_Number_Forms = new YYCTYPE[17];
	uint32_t buffer_Common_Indic_Number_Forms_len = encode_utf32(chars_Common_Indic_Number_Forms[0], chars_Common_Indic_Number_Forms[1], buffer_Common_Indic_Number_Forms) - 1;
	if (scan(buffer_Common_Indic_Number_Forms, buffer_Common_Indic_Number_Forms + buffer_Common_Indic_Number_Forms_len, Common_Indic_Number_Forms) != Common_Indic_Number_Forms)
		printf("test 'Common_Indic_Number_Forms' failed\n");
	delete[] buffer_Common_Indic_Number_Forms;

	YYCTYPE *buffer_Phags_pa = new YYCTYPE[65];
	uint32_t buffer_Phags_pa_len = encode_utf32(chars_Phags_pa[0], chars_Phags_pa[1], buffer_Phags_pa) - 1;
	if (scan(buffer_Phags_pa, buffer_Phags_pa + buffer_Phags_pa_len, Phags_pa) != Phags_pa)
		printf("test 'Phags_pa' failed\n");
	delete[] buffer_Phags_pa;

	YYCTYPE *buffer_Saurashtra = new YYCTYPE[97];
	uint32_t buffer_Saurashtra_len = encode_utf32(chars_Saurashtra[0], chars_Saurashtra[1], buffer_Saurashtra) - 1;
	if (scan(buffer_Saurashtra, buffer_Saurashtra + buffer_Saurashtra_len, Saurashtra) != Saurashtra)
		printf("test 'Saurashtra' failed\n");
	delete[] buffer_Saurashtra;

	YYCTYPE *buffer_Devanagari_Extended = new YYCTYPE[33];
	uint32_t buffer_Devanagari_Extended_len = encode_utf32(chars_Devanagari_Extended[0], chars_Devanagari_Extended[1], buffer_Devanagari_Extended) - 1;
	if (scan(buffer_Devanagari_Extended, buffer_Devanagari_Extended + buffer_Devanagari_Extended_len, Devanagari_Extended) != Devanagari_Extended)
		printf("test 'Devanagari_Extended' failed\n");
	delete[] buffer_Devanagari_Extended;

	YYCTYPE *buffer_Kayah_Li = new YYCTYPE[49];
	uint32_t buffer_Kayah_Li_len = encode_utf32(chars_Kayah_Li[0], chars_Kayah_Li[1], buffer_Kayah_Li) - 1;
	if (scan(buffer_Kayah_Li, buffer_Kayah_Li + buffer_Kayah_Li_len, Kayah_Li) != Kayah_Li)
		printf("test 'Kayah_Li' failed\n");
	delete[] buffer_Kayah_Li;

	YYCTYPE *buffer_Rejang = new YYCTYPE[49];
	uint32_t buffer_Rejang_len = encode_utf32(chars_Rejang[0], chars_Rejang[1], buffer_Rejang) - 1;
	if (scan(buffer_Rejang, buffer_Rejang + buffer_Rejang_len, Rejang) != Rejang)
		printf("test 'Rejang' failed\n");
	delete[] buffer_Rejang;

	YYCTYPE *buffer_Hangul_Jamo_Extended_A = new YYCTYPE[33];
	uint32_t buffer_Hangul_Jamo_Extended_A_len = encode_utf32(chars_Hangul_Jamo_Extended_A[0], chars_Hangul_Jamo_Extended_A[1], buffer_Hangul_Jamo_Extended_A) - 1;
	if (scan(buffer_Hangul_Jamo_Extended_A, buffer_Hangul_Jamo_Extended_A + buffer_Hangul_Jamo_Extended_A_len, Hangul_Jamo_Extended_A) != Hangul_Jamo_Extended_A)
		printf("test 'Hangul_Jamo_Extended_A' failed\n");
	delete[] buffer_Hangul_Jamo_Extended_A;

	YYCTYPE *buffer_Javanese = new YYCTYPE[97];
	uint32_t buffer_Javanese_len = encode_utf32(chars_Javanese[0], chars_Javanese[1], buffer_Javanese) - 1;
	if (scan(buffer_Javanese, buffer_Javanese + buffer_Javanese_len, Javanese) != Javanese)
		printf("test 'Javanese' failed\n");
	delete[] buffer_Javanese;

	YYCTYPE *buffer_Myanmar_Extended_B = new YYCTYPE[33];
	uint32_t buffer_Myanmar_Extended_B_len = encode_utf32(chars_Myanmar_Extended_B[0], chars_Myanmar_Extended_B[1], buffer_Myanmar_Extended_B) - 1;
	if (scan(buffer_Myanmar_Extended_B, buffer_Myanmar_Extended_B + buffer_Myanmar_Extended_B_len, Myanmar_Extended_B) != Myanmar_Extended_B)
		printf("test 'Myanmar_Extended_B' failed\n");
	delete[] buffer_Myanmar_Extended_B;

	YYCTYPE *buffer_Cham = new YYCTYPE[97];
	uint32_t buffer_Cham_len = encode_utf32(chars_Cham[0], chars_Cham[1], buffer_Cham) - 1;
	if (scan(buffer_Cham, buffer_Cham + buffer_Cham_len, Cham) != Cham)
		printf("test 'Cham' failed\n");
	delete[] buffer_Cham;

	YYCTYPE *buffer_Myanmar_Extended_A = new YYCTYPE[33];
	uint32_t buffer_Myanmar_Extended_A_len = encode_utf32(chars_Myanmar_Extended_A[0], chars_Myanmar_Extended_A[1], buffer_Myanmar_Extended_A) - 1;
	if (scan(buffer_Myanmar_Extended_A, buffer_Myanmar_Extended_A + buffer_Myanmar_Extended_A_len, Myanmar_Extended_A) != Myanmar_Extended_A)
		printf("test 'Myanmar_Extended_A' failed\n");
	delete[] buffer_Myanmar_Extended_A;

	YYCTYPE *buffer_Tai_Viet = new YYCTYPE[97];
	uint32_t buffer_Tai_Viet_len = encode_utf32(chars_Tai_Viet[0], chars_Tai_Viet[1], buffer_Tai_Viet) - 1;
	if (scan(buffer_Tai_Viet, buffer_Tai_Viet + buffer_Tai_Viet_len, Tai_Viet) != Tai_Viet)
		printf("test 'Tai_Viet' failed\n");
	delete[] buffer_Tai_Viet;

	YYCTYPE *buffer_Meetei_Mayek_Extensions = new YYCTYPE[33];
	uint32_t buffer_Meetei_Mayek_Extensions_len = encode_utf32(chars_Meetei_Mayek_Extensions[0], chars_Meetei_Mayek_Extensions[1], buffer_Meetei_Mayek_Extensions) - 1;
	if (scan(buffer_Meetei_Mayek_Extensions, buffer_Meetei_Mayek_Extensions + buffer_Meetei_Mayek_Extensions_len, Meetei_Mayek_Extensions) != Meetei_Mayek_Extensions)
		printf("test 'Meetei_Mayek_Extensions' failed\n");
	delete[] buffer_Meetei_Mayek_Extensions;

	YYCTYPE *buffer_Ethiopic_Extended_A = new YYCTYPE[49];
	uint32_t buffer_Ethiopic_Extended_A_len = encode_utf32(chars_Ethiopic_Extended_A[0], chars_Ethiopic_Extended_A[1], buffer_Ethiopic_Extended_A) - 1;
	if (scan(buffer_Ethiopic_Extended_A, buffer_Ethiopic_Extended_A + buffer_Ethiopic_Extended_A_len, Ethiopic_Extended_A) != Ethiopic_Extended_A)
		printf("test 'Ethiopic_Extended_A' failed\n");
	delete[] buffer_Ethiopic_Extended_A;

	YYCTYPE *buffer_Latin_Extended_E = new YYCTYPE[65];
	uint32_t buffer_Latin_Extended_E_len = encode_utf32(chars_Latin_Extended_E[0], chars_Latin_Extended_E[1], buffer_Latin_Extended_E) - 1;
	if (scan(buffer_Latin_Extended_E, buffer_Latin_Extended_E + buffer_Latin_Extended_E_len, Latin_Extended_E) != Latin_Extended_E)
		printf("test 'Latin_Extended_E' failed\n");
	delete[] buffer_Latin_Extended_E;

	YYCTYPE *buffer_Cherokee_Supplement = new YYCTYPE[81];
	uint32_t buffer_Cherokee_Supplement_len = encode_utf32(chars_Cherokee_Supplement[0], chars_Cherokee_Supplement[1], buffer_Cherokee_Supplement) - 1;
	if (scan(buffer_Cherokee_Supplement, buffer_Cherokee_Supplement + buffer_Cherokee_Supplement_len, Cherokee_Supplement) != Cherokee_Supplement)
		printf("test 'Cherokee_Supplement' failed\n");
	delete[] buffer_Cherokee_Supplement;

	YYCTYPE *buffer_Meetei_Mayek = new YYCTYPE[65];
	uint32_t buffer_Meetei_Mayek_len = encode_utf32(chars_Meetei_Mayek[0], chars_Meetei_Mayek[1], buffer_Meetei_Mayek) - 1;
	if (scan(buffer_Meetei_Mayek, buffer_Meetei_Mayek + buffer_Meetei_Mayek_len, Meetei_Mayek) != Meetei_Mayek)
		printf("test 'Meetei_Mayek' failed\n");
	delete[] buffer_Meetei_Mayek;

	YYCTYPE *buffer_Hangul_Syllables = new YYCTYPE[11185];
	uint32_t buffer_Hangul_Syllables_len = encode_utf32(chars_Hangul_Syllables[0], chars_Hangul_Syllables[1], buffer_Hangul_Syllables) - 1;
	if (scan(buffer_Hangul_Syllables, buffer_Hangul_Syllables + buffer_Hangul_Syllables_len, Hangul_Syllables) != Hangul_Syllables)
		printf("test 'Hangul_Syllables' failed\n");
	delete[] buffer_Hangul_Syllables;

	YYCTYPE *buffer_Hangul_Jamo_Extended_B = new YYCTYPE[81];
	uint32_t buffer_Hangul_Jamo_Extended_B_len = encode_utf32(chars_Hangul_Jamo_Extended_B[0], chars_Hangul_Jamo_Extended_B[1], buffer_Hangul_Jamo_Extended_B) - 1;
	if (scan(buffer_Hangul_Jamo_Extended_B, buffer_Hangul_Jamo_Extended_B + buffer_Hangul_Jamo_Extended_B_len, Hangul_Jamo_Extended_B) != Hangul_Jamo_Extended_B)
		printf("test 'Hangul_Jamo_Extended_B' failed\n");
	delete[] buffer_Hangul_Jamo_Extended_B;

	YYCTYPE *buffer_High_Surrogates = new YYCTYPE[897];
	uint32_t buffer_High_Surrogates_len = encode_utf32(chars_High_Surrogates[0], chars_High_Surrogates[1], buffer_High_Surrogates) - 1;
	if (scan(buffer_High_Surrogates, buffer_High_Surrogates + buffer_High_Surrogates_len, High_Surrogates) != High_Surrogates)
		printf("test 'High_Surrogates' failed\n");
	delete[] buffer_High_Surrogates;

	YYCTYPE *buffer_High_Private_Use_Surrogates = new YYCTYPE[129];
	uint32_t buffer_High_Private_Use_Surrogates_len = encode_utf32(chars_High_Private_Use_Surrogates[0], chars_High_Private_Use_Surrogates[1], buffer_High_Private_Use_Surrogates) - 1;
	if (scan(buffer_High_Private_Use_Surrogates, buffer_High_Private_Use_Surrogates + buffer_High_Private_Use_Surrogates_len, High_Private_Use_Surrogates) != High_Private_Use_Surrogates)
		printf("test 'High_Private_Use_Surrogates' failed\n");
	delete[] buffer_High_Private_Use_Surrogates;

	YYCTYPE *buffer_Low_Surrogates = new YYCTYPE[1025];
	uint32_t buffer_Low_Surrogates_len = encode_utf32(chars_Low_Surrogates[0], chars_Low_Surrogates[1], buffer_Low_Surrogates) - 1;
	if (scan(buffer_Low_Surrogates, buffer_Low_Surrogates + buffer_Low_Surrogates_len, Low_Surrogates) != Low_Surrogates)
		printf("test 'Low_Surrogates' failed\n");
	delete[] buffer_Low_Surrogates;

	YYCTYPE *buffer_Private_Use_Area = new YYCTYPE[6401];
	uint32_t buffer_Private_Use_Area_len = encode_utf32(chars_Private_Use_Area[0], chars_Private_Use_Area[1], buffer_Private_Use_Area) - 1;
	if (scan(buffer_Private_Use_Area, buffer_Private_Use_Area + buffer_Private_Use_Area_len, Private_Use_Area) != Private_Use_Area)
		printf("test 'Private_Use_Area' failed\n");
	delete[] buffer_Private_Use_Area;

	YYCTYPE *buffer_CJK_Compatibility_Ideographs = new YYCTYPE[513];
	uint32_t buffer_CJK_Compatibility_Ideographs_len = encode_utf32(chars_CJK_Compatibility_Ideographs[0], chars_CJK_Compatibility_Ideographs[1], buffer_CJK_Compatibility_Ideographs) - 1;
	if (scan(buffer_CJK_Compatibility_Ideographs, buffer_CJK_Compatibility_Ideographs + buffer_CJK_Compatibility_Ideographs_len, CJK_Compatibility_Ideographs) != CJK_Compatibility_Ideographs)
		printf("test 'CJK_Compatibility_Ideographs' failed\n");
	delete[] buffer_CJK_Compatibility_Ideographs;

	YYCTYPE *buffer_Alphabetic_Presentation_Forms = new YYCTYPE[81];
	uint32_t buffer_Alphabetic_Presentation_Forms_len = encode_utf32(chars_Alphabetic_Presentation_Forms[0], chars_Alphabetic_Presentation_Forms[1], buffer_Alphabetic_Presentation_Forms) - 1;
	if (scan(buffer_Alphabetic_Presentation_Forms, buffer_Alphabetic_Presentation_Forms + buffer_Alphabetic_Presentation_Forms_len, Alphabetic_Presentation_Forms) != Alphabetic_Presentation_Forms)
		printf("test 'Alphabetic_Presentation_Forms' failed\n");
	delete[] buffer_Alphabetic_Presentation_Forms;

	YYCTYPE *buffer_Arabic_Presentation_Forms_A = new YYCTYPE[689];
	uint32_t buffer_Arabic_Presentation_Forms_A_len = encode_utf32(chars_Arabic_Presentation_Forms_A[0], chars_Arabic_Presentation_Forms_A[1], buffer_Arabic_Presentation_Forms_A) - 1;
	if (scan(buffer_Arabic_Presentation_Forms_A, buffer_Arabic_Presentation_Forms_A + buffer_Arabic_Presentation_Forms_A_len, Arabic_Presentation_Forms_A) != Arabic_Presentation_Forms_A)
		printf("test 'Arabic_Presentation_Forms_A' failed\n");
	delete[] buffer_Arabic_Presentation_Forms_A;

	YYCTYPE *buffer_Variation_Selectors = new YYCTYPE[17];
	uint32_t buffer_Variation_Selectors_len = encode_utf32(chars_Variation_Selectors[0], chars_Variation_Selectors[1], buffer_Variation_Selectors) - 1;
	if (scan(buffer_Variation_Selectors, buffer_Variation_Selectors + buffer_Variation_Selectors_len, Variation_Selectors) != Variation_Selectors)
		printf("test 'Variation_Selectors' failed\n");
	delete[] buffer_Variation_Selectors;

	YYCTYPE *buffer_Vertical_Forms = new YYCTYPE[17];
	uint32_t buffer_Vertical_Forms_len = encode_utf32(chars_Vertical_Forms[0], chars_Vertical_Forms[1], buffer_Vertical_Forms) - 1;
	if (scan(buffer_Vertical_Forms, buffer_Vertical_Forms + buffer_Vertical_Forms_len, Vertical_Forms) != Vertical_Forms)
		printf("test 'Vertical_Forms' failed\n");
	delete[] buffer_Vertical_Forms;

	YYCTYPE *buffer_Combining_Half_Marks = new YYCTYPE[17];
	uint32_t buffer_Combining_Half_Marks_len = encode_utf32(chars_Combining_Half_Marks[0], chars_Combining_Half_Marks[1], buffer_Combining_Half_Marks) - 1;
	if (scan(buffer_Combining_Half_Marks, buffer_Combining_Half_Marks + buffer_Combining_Half_Marks_len, Combining_Half_Marks) != Combining_Half_Marks)
		printf("test 'Combining_Half_Marks' failed\n");
	delete[] buffer_Combining_Half_Marks;

	YYCTYPE *buffer_CJK_Compatibility_Forms = new YYCTYPE[33];
	uint32_t buffer_CJK_Compatibility_Forms_len = encode_utf32(chars_CJK_Compatibility_Forms[0], chars_CJK_Compatibility_Forms[1], buffer_CJK_Compatibility_Forms) - 1;
	if (scan(buffer_CJK_Compatibility_Forms, buffer_CJK_Compatibility_Forms + buffer_CJK_Compatibility_Forms_len, CJK_Compatibility_Forms) != CJK_Compatibility_Forms)
		printf("test 'CJK_Compatibility_Forms' failed\n");
	delete[] buffer_CJK_Compatibility_Forms;

	YYCTYPE *buffer_Small_Form_Variants = new YYCTYPE[33];
	uint32_t buffer_Small_Form_Variants_len = encode_utf32(chars_Small_Form_Variants[0], chars_Small_Form_Variants[1], buffer_Small_Form_Variants) - 1;
	if (scan(buffer_Small_Form_Variants, buffer_Small_Form_Variants + buffer_Small_Form_Variants_len, Small_Form_Variants) != Small_Form_Variants)
		printf("test 'Small_Form_Variants' failed\n");
	delete[] buffer_Small_Form_Variants;

	YYCTYPE *buffer_Arabic_Presentation_Forms_B = new YYCTYPE[145];
	uint32_t buffer_Arabic_Presentation_Forms_B_len = encode_utf32(chars_Arabic_Presentation_Forms_B[0], chars_Arabic_Presentation_Forms_B[1], buffer_Arabic_Presentation_Forms_B) - 1;
	if (scan(buffer_Arabic_Presentation_Forms_B, buffer_Arabic_Presentation_Forms_B + buffer_Arabic_Presentation_Forms_B_len, Arabic_Presentation_Forms_B) != Arabic_Presentation_Forms_B)
		printf("test 'Arabic_Presentation_Forms_B' failed\n");
	delete[] buffer_Arabic_Presentation_Forms_B;

	YYCTYPE *buffer_Halfwidth_and_Fullwidth_Forms = new YYCTYPE[241];
	uint32_t buffer_Halfwidth_and_Fullwidth_Forms_len = encode_utf32(chars_Halfwidth_and_Fullwidth_Forms[0], chars_Halfwidth_and_Fullwidth_Forms[1], buffer_Halfwidth_and_Fullwidth_Forms) - 1;
	if (scan(buffer_Halfwidth_and_Fullwidth_Forms, buffer_Halfwidth_and_Fullwidth_Forms + buffer_Halfwidth_and_Fullwidth_Forms_len, Halfwidth_and_Fullwidth_Forms) != Halfwidth_and_Fullwidth_Forms)
		printf("test 'Halfwidth_and_Fullwidth_Forms' failed\n");
	delete[] buffer_Halfwidth_and_Fullwidth_Forms;

	YYCTYPE *buffer_Specials = new YYCTYPE[17];
	uint32_t buffer_Specials_len = encode_utf32(chars_Specials[0], chars_Specials[1], buffer_Specials) - 1;
	if (scan(buffer_Specials, buffer_Specials + buffer_Specials_len, Specials) != Specials)
		printf("test 'Specials' failed\n");
	delete[] buffer_Specials;

	YYCTYPE *buffer_Linear_B_Syllabary = new YYCTYPE[129];
	uint32_t buffer_Linear_B_Syllabary_len = encode_utf32(chars_Linear_B_Syllabary[0], chars_Linear_B_Syllabary[1], buffer_Linear_B_Syllabary) - 1;
	if (scan(buffer_Linear_B_Syllabary, buffer_Linear_B_Syllabary + buffer_Linear_B_Syllabary_len, Linear_B_Syllabary) != Linear_B_Syllabary)
		printf("test 'Linear_B_Syllabary' failed\n");
	delete[] buffer_Linear_B_Syllabary;

	YYCTYPE *buffer_Linear_B_Ideograms = new YYCTYPE[129];
	uint32_t buffer_Linear_B_Ideograms_len = encode_utf32(chars_Linear_B_Ideograms[0], chars_Linear_B_Ideograms[1], buffer_Linear_B_Ideograms) - 1;
	if (scan(buffer_Linear_B_Ideograms, buffer_Linear_B_Ideograms + buffer_Linear_B_Ideograms_len, Linear_B_Ideograms) != Linear_B_Ideograms)
		printf("test 'Linear_B_Ideograms' failed\n");
	delete[] buffer_Linear_B_Ideograms;

	YYCTYPE *buffer_Aegean_Numbers = new YYCTYPE[65];
	uint32_t buffer_Aegean_Numbers_len = encode_utf32(chars_Aegean_Numbers[0], chars_Aegean_Numbers[1], buffer_Aegean_Numbers) - 1;
	if (scan(buffer_Aegean_Numbers, buffer_Aegean_Numbers + buffer_Aegean_Numbers_len, Aegean_Numbers) != Aegean_Numbers)
		printf("test 'Aegean_Numbers' failed\n");
	delete[] buffer_Aegean_Numbers;

	YYCTYPE *buffer_Ancient_Greek_Numbers = new YYCTYPE[81];
	uint32_t buffer_Ancient_Greek_Numbers_len = encode_utf32(chars_Ancient_Greek_Numbers[0], chars_Ancient_Greek_Numbers[1], buffer_Ancient_Greek_Numbers) - 1;
	if (scan(buffer_Ancient_Greek_Numbers, buffer_Ancient_Greek_Numbers + buffer_Ancient_Greek_Numbers_len, Ancient_Greek_Numbers) != Ancient_Greek_Numbers)
		printf("test 'Ancient_Greek_Numbers' failed\n");
	delete[] buffer_Ancient_Greek_Numbers;

	YYCTYPE *buffer_Ancient_Symbols = new YYCTYPE[65];
	uint32_t buffer_Ancient_Symbols_len = encode_utf32(chars_Ancient_Symbols[0], chars_Ancient_Symbols[1], buffer_Ancient_Symbols) - 1;
	if (scan(buffer_Ancient_Symbols, buffer_Ancient_Symbols + buffer_Ancient_Symbols_len, Ancient_Symbols) != Ancient_Symbols)
		printf("test 'Ancient_Symbols' failed\n");
	delete[] buffer_Ancient_Symbols;

	YYCTYPE *buffer_Phaistos_Disc = new YYCTYPE[49];
	uint32_t buffer_Phaistos_Disc_len = encode_utf32(chars_Phaistos_Disc[0], chars_Phaistos_Disc[1], buffer_Phaistos_Disc) - 1;
	if (scan(buffer_Phaistos_Disc, buffer_Phaistos_Disc + buffer_Phaistos_Disc_len, Phaistos_Disc) != Phaistos_Disc)
		printf("test 'Phaistos_Disc' failed\n");
	delete[] buffer_Phaistos_Disc;

	YYCTYPE *buffer_Lycian = new YYCTYPE[33];
	uint32_t buffer_Lycian_len = encode_utf32(chars_Lycian[0], chars_Lycian[1], buffer_Lycian) - 1;
	if (scan(buffer_Lycian, buffer_Lycian + buffer_Lycian_len, Lycian) != Lycian)
		printf("test 'Lycian' failed\n");
	delete[] buffer_Lycian;

	YYCTYPE *buffer_Carian = new YYCTYPE[65];
	uint32_t buffer_Carian_len = encode_utf32(chars_Carian[0], chars_Carian[1], buffer_Carian) - 1;
	if (scan(buffer_Carian, buffer_Carian + buffer_Carian_len, Carian) != Carian)
		printf("test 'Carian' failed\n");
	delete[] buffer_Carian;

	YYCTYPE *buffer_Coptic_Epact_Numbers = new YYCTYPE[33];
	uint32_t buffer_Coptic_Epact_Numbers_len = encode_utf32(chars_Coptic_Epact_Numbers[0], chars_Coptic_Epact_Numbers[1], buffer_Coptic_Epact_Numbers) - 1;
	if (scan(buffer_Coptic_Epact_Numbers, buffer_Coptic_Epact_Numbers + buffer_Coptic_Epact_Numbers_len, Coptic_Epact_Numbers) != Coptic_Epact_Numbers)
		printf("test 'Coptic_Epact_Numbers' failed\n");
	delete[] buffer_Coptic_Epact_Numbers;

	YYCTYPE *buffer_Old_Italic = new YYCTYPE[49];
	uint32_t buffer_Old_Italic_len = encode_utf32(chars_Old_Italic[0], chars_Old_Italic[1], buffer_Old_Italic) - 1;
	if (scan(buffer_Old_Italic, buffer_Old_Italic + buffer_Old_Italic_len, Old_Italic) != Old_Italic)
		printf("test 'Old_Italic' failed\n");
	delete[] buffer_Old_Italic;

	YYCTYPE *buffer_Gothic = new YYCTYPE[33];
	uint32_t buffer_Gothic_len = encode_utf32(chars_Gothic[0], chars_Gothic[1], buffer_Gothic) - 1;
	if (scan(buffer_Gothic, buffer_Gothic + buffer_Gothic_len, Gothic) != Gothic)
		printf("test 'Gothic' failed\n");
	delete[] buffer_Gothic;

	YYCTYPE *buffer_Old_Permic = new YYCTYPE[49];
	uint32_t buffer_Old_Permic_len = encode_utf32(chars_Old_Permic[0], chars_Old_Permic[1], buffer_Old_Permic) - 1;
	if (scan(buffer_Old_Permic, buffer_Old_Permic + buffer_Old_Permic_len, Old_Permic) != Old_Permic)
		printf("test 'Old_Permic' failed\n");
	delete[] buffer_Old_Permic;

	YYCTYPE *buffer_Ugaritic = new YYCTYPE[33];
	uint32_t buffer_Ugaritic_len = encode_utf32(chars_Ugaritic[0], chars_Ugaritic[1], buffer_Ugaritic) - 1;
	if (scan(buffer_Ugaritic, buffer_Ugaritic + buffer_Ugaritic_len, Ugaritic) != Ugaritic)
		printf("test 'Ugaritic' failed\n");
	delete[] buffer_Ugaritic;

	YYCTYPE *buffer_Old_Persian = new YYCTYPE[65];
	uint32_t buffer_Old_Persian_len = encode_utf32(chars_Old_Persian[0], chars_Old_Persian[1], buffer_Old_Persian) - 1;
	if (scan(buffer_Old_Persian, buffer_Old_Persian + buffer_Old_Persian_len, Old_Persian) != Old_Persian)
		printf("test 'Old_Persian' failed\n");
	delete[] buffer_Old_Persian;

	YYCTYPE *buffer_Deseret = new YYCTYPE[81];
	uint32_t buffer_Deseret_len = encode_utf32(chars_Deseret[0], chars_Deseret[1], buffer_Deseret) - 1;
	if (scan(buffer_Deseret, buffer_Deseret + buffer_Deseret_len, Deseret) != Deseret)
		printf("test 'Deseret' failed\n");
	delete[] buffer_Deseret;

	YYCTYPE *buffer_Shavian = new YYCTYPE[49];
	uint32_t buffer_Shavian_len = encode_utf32(chars_Shavian[0], chars_Shavian[1], buffer_Shavian) - 1;
	if (scan(buffer_Shavian, buffer_Shavian + buffer_Shavian_len, Shavian) != Shavian)
		printf("test 'Shavian' failed\n");
	delete[] buffer_Shavian;

	YYCTYPE *buffer_Osmanya = new YYCTYPE[49];
	uint32_t buffer_Osmanya_len = encode_utf32(chars_Osmanya[0], chars_Osmanya[1], buffer_Osmanya) - 1;
	if (scan(buffer_Osmanya, buffer_Osmanya + buffer_Osmanya_len, Osmanya) != Osmanya)
		printf("test 'Osmanya' failed\n");
	delete[] buffer_Osmanya;

	YYCTYPE *buffer_Osage = new YYCTYPE[81];
	uint32_t buffer_Osage_len = encode_utf32(chars_Osage[0], chars_Osage[1], buffer_Osage) - 1;
	if (scan(buffer_Osage, buffer_Osage + buffer_Osage_len, Osage) != Osage)
		printf("test 'Osage' failed\n");
	delete[] buffer_Osage;

	YYCTYPE *buffer_Elbasan = new YYCTYPE[49];
	uint32_t buffer_Elbasan_len = encode_utf32(chars_Elbasan[0], chars_Elbasan[1], buffer_Elbasan) - 1;
	if (scan(buffer_Elbasan, buffer_Elbasan + buffer_Elbasan_len, Elbasan) != Elbasan)
		printf("test 'Elbasan' failed\n");
	delete[] buffer_Elbasan;

	YYCTYPE *buffer_Caucasian_Albanian = new YYCTYPE[65];
	uint32_t buffer_Caucasian_Albanian_len = encode_utf32(chars_Caucasian_Albanian[0], chars_Caucasian_Albanian[1], buffer_Caucasian_Albanian) - 1;
	if (scan(buffer_Caucasian_Albanian, buffer_Caucasian_Albanian + buffer_Caucasian_Albanian_len, Caucasian_Albanian) != Caucasian_Albanian)
		printf("test 'Caucasian_Albanian' failed\n");
	delete[] buffer_Caucasian_Albanian;

	YYCTYPE *buffer_Vithkuqi = new YYCTYPE[81];
	uint32_t buffer_Vithkuqi_len = encode_utf32(chars_Vithkuqi[0], chars_Vithkuqi[1], buffer_Vithkuqi) - 1;
	if (scan(buffer_Vithkuqi, buffer_Vithkuqi + buffer_Vithkuqi_len, Vithkuqi) != Vithkuqi)
		printf("test 'Vithkuqi' failed\n");
	delete[] buffer_Vithkuqi;

	YYCTYPE *buffer_Linear_A = new YYCTYPE[385];
	uint32_t buffer_Linear_A_len = encode_utf32(chars_Linear_A[0], chars_Linear_A[1], buffer_Linear_A) - 1;
	if (scan(buffer_Linear_A, buffer_Linear_A + buffer_Linear_A_len, Linear_A) != Linear_A)
		printf("test 'Linear_A' failed\n");
	delete[] buffer_Linear_A;

	YYCTYPE *buffer_Latin_Extended_F = new YYCTYPE[65];
	uint32_t buffer_Latin_Extended_F_len = encode_utf32(chars_Latin_Extended_F[0], chars_Latin_Extended_F[1], buffer_Latin_Extended_F) - 1;
	if (scan(buffer_Latin_Extended_F, buffer_Latin_Extended_F + buffer_Latin_Extended_F_len, Latin_Extended_F) != Latin_Extended_F)
		printf("test 'Latin_Extended_F' failed\n");
	delete[] buffer_Latin_Extended_F;

	YYCTYPE *buffer_Cypriot_Syllabary = new YYCTYPE[65];
	uint32_t buffer_Cypriot_Syllabary_len = encode_utf32(chars_Cypriot_Syllabary[0], chars_Cypriot_Syllabary[1], buffer_Cypriot_Syllabary) - 1;
	if (scan(buffer_Cypriot_Syllabary, buffer_Cypriot_Syllabary + buffer_Cypriot_Syllabary_len, Cypriot_Syllabary) != Cypriot_Syllabary)
		printf("test 'Cypriot_Syllabary' failed\n");
	delete[] buffer_Cypriot_Syllabary;

	YYCTYPE *buffer_Imperial_Aramaic = new YYCTYPE[33];
	uint32_t buffer_Imperial_Aramaic_len = encode_utf32(chars_Imperial_Aramaic[0], chars_Imperial_Aramaic[1], buffer_Imperial_Aramaic) - 1;
	if (scan(buffer_Imperial_Aramaic, buffer_Imperial_Aramaic + buffer_Imperial_Aramaic_len, Imperial_Aramaic) != Imperial_Aramaic)
		printf("test 'Imperial_Aramaic' failed\n");
	delete[] buffer_Imperial_Aramaic;

	YYCTYPE *buffer_Palmyrene = new YYCTYPE[33];
	uint32_t buffer_Palmyrene_len = encode_utf32(chars_Palmyrene[0], chars_Palmyrene[1], buffer_Palmyrene) - 1;
	if (scan(buffer_Palmyrene, buffer_Palmyrene + buffer_Palmyrene_len, Palmyrene) != Palmyrene)
		printf("test 'Palmyrene' failed\n");
	delete[] buffer_Palmyrene;

	YYCTYPE *buffer_Nabataean = new YYCTYPE[49];
	uint32_t buffer_Nabataean_len = encode_utf32(chars_Nabataean[0], chars_Nabataean[1], buffer_Nabataean) - 1;
	if (scan(buffer_Nabataean, buffer_Nabataean + buffer_Nabataean_len, Nabataean) != Nabataean)
		printf("test 'Nabataean' failed\n");
	delete[] buffer_Nabataean;

	YYCTYPE *buffer_Hatran = new YYCTYPE[33];
	uint32_t buffer_Hatran_len = encode_utf32(chars_Hatran[0], chars_Hatran[1], buffer_Hatran) - 1;
	if (scan(buffer_Hatran, buffer_Hatran + buffer_Hatran_len, Hatran) != Hatran)
		printf("test 'Hatran' failed\n");
	delete[] buffer_Hatran;

	YYCTYPE *buffer_Phoenician = new YYCTYPE[33];
	uint32_t buffer_Phoenician_len = encode_utf32(chars_Phoenician[0], chars_Phoenician[1], buffer_Phoenician) - 1;
	if (scan(buffer_Phoenician, buffer_Phoenician + buffer_Phoenician_len, Phoenician) != Phoenician)
		printf("test 'Phoenician' failed\n");
	delete[] buffer_Phoenician;

	YYCTYPE *buffer_Lydian = new YYCTYPE[33];
	uint32_t buffer_Lydian_len = encode_utf32(chars_Lydian[0], chars_Lydian[1], buffer_Lydian) - 1;
	if (scan(buffer_Lydian, buffer_Lydian + buffer_Lydian_len, Lydian) != Lydian)
		printf("test 'Lydian' failed\n");
	delete[] buffer_Lydian;

	YYCTYPE *buffer_Meroitic_Hieroglyphs = new YYCTYPE[33];
	uint32_t buffer_Meroitic_Hieroglyphs_len = encode_utf32(chars_Meroitic_Hieroglyphs[0], chars_Meroitic_Hieroglyphs[1], buffer_Meroitic_Hieroglyphs) - 1;
	if (scan(buffer_Meroitic_Hieroglyphs, buffer_Meroitic_Hieroglyphs + buffer_Meroitic_Hieroglyphs_len, Meroitic_Hieroglyphs) != Meroitic_Hieroglyphs)
		printf("test 'Meroitic_Hieroglyphs' failed\n");
	delete[] buffer_Meroitic_Hieroglyphs;

	YYCTYPE *buffer_Meroitic_Cursive = new YYCTYPE[97];
	uint32_t buffer_Meroitic_Cursive_len = encode_utf32(chars_Meroitic_Cursive[0], chars_Meroitic_Cursive[1], buffer_Meroitic_Cursive) - 1;
	if (scan(buffer_Meroitic_Cursive, buffer_Meroitic_Cursive + buffer_Meroitic_Cursive_len, Meroitic_Cursive) != Meroitic_Cursive)
		printf("test 'Meroitic_Cursive' failed\n");
	delete[] buffer_Meroitic_Cursive;

	YYCTYPE *buffer_Kharoshthi = new YYCTYPE[97];
	uint32_t buffer_Kharoshthi_len = encode_utf32(chars_Kharoshthi[0], chars_Kharoshthi[1], buffer_Kharoshthi) - 1;
	if (scan(buffer_Kharoshthi, buffer_Kharoshthi + buffer_Kharoshthi_len, Kharoshthi) != Kharoshthi)
		printf("test 'Kharoshthi' failed\n");
	delete[] buffer_Kharoshthi;

	YYCTYPE *buffer_Old_South_Arabian = new YYCTYPE[33];
	uint32_t buffer_Old_South_Arabian_len = encode_utf32(chars_Old_South_Arabian[0], chars_Old_South_Arabian[1], buffer_Old_South_Arabian) - 1;
	if (scan(buffer_Old_South_Arabian, buffer_Old_South_Arabian + buffer_Old_South_Arabian_len, Old_South_Arabian) != Old_South_Arabian)
		printf("test 'Old_South_Arabian' failed\n");
	delete[] buffer_Old_South_Arabian;

	YYCTYPE *buffer_Old_North_Arabian = new YYCTYPE[33];
	uint32_t buffer_Old_North_Arabian_len = encode_utf32(chars_Old_North_Arabian[0], chars_Old_North_Arabian[1], buffer_Old_North_Arabian) - 1;
	if (scan(buffer_Old_North_Arabian, buffer_Old_North_Arabian + buffer_Old_North_Arabian_len, Old_North_Arabian) != Old_North_Arabian)
		printf("test 'Old_North_Arabian' failed\n");
	delete[] buffer_Old_North_Arabian;

	YYCTYPE *buffer_Manichaean = new YYCTYPE[65];
	uint32_t buffer_Manichaean_len = encode_utf32(chars_Manichaean[0], chars_Manichaean[1], buffer_Manichaean) - 1;
	if (scan(buffer_Manichaean, buffer_Manichaean + buffer_Manichaean_len, Manichaean) != Manichaean)
		printf("test 'Manichaean' failed\n");
	delete[] buffer_Manichaean;

	YYCTYPE *buffer_Avestan = new YYCTYPE[65];
	uint32_t buffer_Avestan_len = encode_utf32(chars_Avestan[0], chars_Avestan[1], buffer_Avestan) - 1;
	if (scan(buffer_Avestan, buffer_Avestan + buffer_Avestan_len, Avestan) != Avestan)
		printf("test 'Avestan' failed\n");
	delete[] buffer_Avestan;

	YYCTYPE *buffer_Inscriptional_Parthian = new YYCTYPE[33];
	uint32_t buffer_Inscriptional_Parthian_len = encode_utf32(chars_Inscriptional_Parthian[0], chars_Inscriptional_Parthian[1], buffer_Inscriptional_Parthian) - 1;
	if (scan(buffer_Inscriptional_Parthian, buffer_Inscriptional_Parthian + buffer_Inscriptional_Parthian_len, Inscriptional_Parthian) != Inscriptional_Parthian)
		printf("test 'Inscriptional_Parthian' failed\n");
	delete[] buffer_Inscriptional_Parthian;

	YYCTYPE *buffer_Inscriptional_Pahlavi = new YYCTYPE[33];
	uint32_t buffer_Inscriptional_Pahlavi_len = encode_utf32(chars_Inscriptional_Pahlavi[0], chars_Inscriptional_Pahlavi[1], buffer_Inscriptional_Pahlavi) - 1;
	if (scan(buffer_Inscriptional_Pahlavi, buffer_Inscriptional_Pahlavi + buffer_Inscriptional_Pahlavi_len, Inscriptional_Pahlavi) != Inscriptional_Pahlavi)
		printf("test 'Inscriptional_Pahlavi' failed\n");
	delete[] buffer_Inscriptional_Pahlavi;

	YYCTYPE *buffer_Psalter_Pahlavi = new YYCTYPE[49];
	uint32_t buffer_Psalter_Pahlavi_len = encode_utf32(chars_Psalter_Pahlavi[0], chars_Psalter_Pahlavi[1], buffer_Psalter_Pahlavi) - 1;
	if (scan(buffer_Psalter_Pahlavi, buffer_Psalter_Pahlavi + buffer_Psalter_Pahlavi_len, Psalter_Pahlavi) != Psalter_Pahlavi)
		printf("test 'Psalter_Pahlavi' failed\n");
	delete[] buffer_Psalter_Pahlavi;

	YYCTYPE *buffer_Old_Turkic = new YYCTYPE[81];
	uint32_t buffer_Old_Turkic_len = encode_utf32(chars_Old_Turkic[0], chars_Old_Turkic[1], buffer_Old_Turkic) - 1;
	if (scan(buffer_Old_Turkic, buffer_Old_Turkic + buffer_Old_Turkic_len, Old_Turkic) != Old_Turkic)
		printf("test 'Old_Turkic' failed\n");
	delete[] buffer_Old_Turkic;

	YYCTYPE *buffer_Old_Hungarian = new YYCTYPE[129];
	uint32_t buffer_Old_Hungarian_len = encode_utf32(chars_Old_Hungarian[0], chars_Old_Hungarian[1], buffer_Old_Hungarian) - 1;
	if (scan(buffer_Old_Hungarian, buffer_Old_Hungarian + buffer_Old_Hungarian_len, Old_Hungarian) != Old_Hungarian)
		printf("test 'Old_Hungarian' failed\n");
	delete[] buffer_Old_Hungarian;

	YYCTYPE *buffer_Hanifi_Rohingya = new YYCTYPE[65];
	uint32_t buffer_Hanifi_Rohingya_len = encode_utf32(chars_Hanifi_Rohingya[0], chars_Hanifi_Rohingya[1], buffer_Hanifi_Rohingya) - 1;
	if (scan(buffer_Hanifi_Rohingya, buffer_Hanifi_Rohingya + buffer_Hanifi_Rohingya_len, Hanifi_Rohingya) != Hanifi_Rohingya)
		printf("test 'Hanifi_Rohingya' failed\n");
	delete[] buffer_Hanifi_Rohingya;

	YYCTYPE *buffer_Rumi_Numeral_Symbols = new YYCTYPE[33];
	uint32_t buffer_Rumi_Numeral_Symbols_len = encode_utf32(chars_Rumi_Numeral_Symbols[0], chars_Rumi_Numeral_Symbols[1], buffer_Rumi_Numeral_Symbols) - 1;
	if (scan(buffer_Rumi_Numeral_Symbols, buffer_Rumi_Numeral_Symbols + buffer_Rumi_Numeral_Symbols_len, Rumi_Numeral_Symbols) != Rumi_Numeral_Symbols)
		printf("test 'Rumi_Numeral_Symbols' failed\n");
	delete[] buffer_Rumi_Numeral_Symbols;

	YYCTYPE *buffer_Yezidi = new YYCTYPE[65];
	uint32_t buffer_Yezidi_len = encode_utf32(chars_Yezidi[0], chars_Yezidi[1], buffer_Yezidi) - 1;
	if (scan(buffer_Yezidi, buffer_Yezidi + buffer_Yezidi_len, Yezidi) != Yezidi)
		printf("test 'Yezidi' failed\n");
	delete[] buffer_Yezidi;

	YYCTYPE *buffer_Arabic_Extended_C = new YYCTYPE[65];
	uint32_t buffer_Arabic_Extended_C_len = encode_utf32(chars_Arabic_Extended_C[0], chars_Arabic_Extended_C[1], buffer_Arabic_Extended_C) - 1;
	if (scan(buffer_Arabic_Extended_C, buffer_Arabic_Extended_C + buffer_Arabic_Extended_C_len, Arabic_Extended_C) != Arabic_Extended_C)
		printf("test 'Arabic_Extended_C' failed\n");
	delete[] buffer_Arabic_Extended_C;

	YYCTYPE *buffer_Old_Sogdian = new YYCTYPE[49];
	uint32_t buffer_Old_Sogdian_len = encode_utf32(chars_Old_Sogdian[0], chars_Old_Sogdian[1], buffer_Old_Sogdian) - 1;
	if (scan(buffer_Old_Sogdian, buffer_Old_Sogdian + buffer_Old_Sogdian_len, Old_Sogdian) != Old_Sogdian)
		printf("test 'Old_Sogdian' failed\n");
	delete[] buffer_Old_Sogdian;

	YYCTYPE *buffer_Sogdian = new YYCTYPE[65];
	uint32_t buffer_Sogdian_len = encode_utf32(chars_Sogdian[0], chars_Sogdian[1], buffer_Sogdian) - 1;
	if (scan(buffer_Sogdian, buffer_Sogdian + buffer_Sogdian_len, Sogdian) != Sogdian)
		printf("test 'Sogdian' failed\n");
	delete[] buffer_Sogdian;

	YYCTYPE *buffer_Old_Uyghur = new YYCTYPE[65];
	uint32_t buffer_Old_Uyghur_len = encode_utf32(chars_Old_Uyghur[0], chars_Old_Uyghur[1], buffer_Old_Uyghur) - 1;
	if (scan(buffer_Old_Uyghur, buffer_Old_Uyghur + buffer_Old_Uyghur_len, Old_Uyghur) != Old_Uyghur)
		printf("test 'Old_Uyghur' failed\n");
	delete[] buffer_Old_Uyghur;

	YYCTYPE *buffer_Chorasmian = new YYCTYPE[49];
	uint32_t buffer_Chorasmian_len = encode_utf32(chars_Chorasmian[0], chars_Chorasmian[1], buffer_Chorasmian) - 1;
	if (scan(buffer_Chorasmian, buffer_Chorasmian + buffer_Chorasmian_len, Chorasmian) != Chorasmian)
		printf("test 'Chorasmian' failed\n");
	delete[] buffer_Chorasmian;

	YYCTYPE *buffer_Elymaic = new YYCTYPE[33];
	uint32_t buffer_Elymaic_len = encode_utf32(chars_Elymaic[0], chars_Elymaic[1], buffer_Elymaic) - 1;
	if (scan(buffer_Elymaic, buffer_Elymaic + buffer_Elymaic_len, Elymaic) != Elymaic)
		printf("test 'Elymaic' failed\n");
	delete[] buffer_Elymaic;

	YYCTYPE *buffer_Brahmi = new YYCTYPE[129];
	uint32_t buffer_Brahmi_len = encode_utf32(chars_Brahmi[0], chars_Brahmi[1], buffer_Brahmi) - 1;
	if (scan(buffer_Brahmi, buffer_Brahmi + buffer_Brahmi_len, Brahmi) != Brahmi)
		printf("test 'Brahmi' failed\n");
	delete[] buffer_Brahmi;

	YYCTYPE *buffer_Kaithi = new YYCTYPE[81];
	uint32_t buffer_Kaithi_len = encode_utf32(chars_Kaithi[0], chars_Kaithi[1], buffer_Kaithi) - 1;
	if (scan(buffer_Kaithi, buffer_Kaithi + buffer_Kaithi_len, Kaithi) != Kaithi)
		printf("test 'Kaithi' failed\n");
	delete[] buffer_Kaithi;

	YYCTYPE *buffer_Sora_Sompeng = new YYCTYPE[49];
	uint32_t buffer_Sora_Sompeng_len = encode_utf32(chars_Sora_Sompeng[0], chars_Sora_Sompeng[1], buffer_Sora_Sompeng) - 1;
	if (scan(buffer_Sora_Sompeng, buffer_Sora_Sompeng + buffer_Sora_Sompeng_len, Sora_Sompeng) != Sora_Sompeng)
		printf("test 'Sora_Sompeng' failed\n");
	delete[] buffer_Sora_Sompeng;

	YYCTYPE *buffer_Chakma = new YYCTYPE[81];
	uint32_t buffer_Chakma_len = encode_utf32(chars_Chakma[0], chars_Chakma[1], buffer_Chakma) - 1;
	if (scan(buffer_Chakma, buffer_Chakma + buffer_Chakma_len, Chakma) != Chakma)
		printf("test 'Chakma' failed\n");
	delete[] buffer_Chakma;

	YYCTYPE *buffer_Mahajani = new YYCTYPE[49];
	uint32_t buffer_Mahajani_len = encode_utf32(chars_Mahajani[0], chars_Mahajani[1], buffer_Mahajani) - 1;
	if (scan(buffer_Mahajani, buffer_Mahajani + buffer_Mahajani_len, Mahajani) != Mahajani)
		printf("test 'Mahajani' failed\n");
	delete[] buffer_Mahajani;

	YYCTYPE *buffer_Sharada = new YYCTYPE[97];
	uint32_t buffer_Sharada_len = encode_utf32(chars_Sharada[0], chars_Sharada[1], buffer_Sharada) - 1;
	if (scan(buffer_Sharada, buffer_Sharada + buffer_Sharada_len, Sharada) != Sharada)
		printf("test 'Sharada' failed\n");
	delete[] buffer_Sharada;

	YYCTYPE *buffer_Sinhala_Archaic_Numbers = new YYCTYPE[33];
	uint32_t buffer_Sinhala_Archaic_Numbers_len = encode_utf32(chars_Sinhala_Archaic_Numbers[0], chars_Sinhala_Archaic_Numbers[1], buffer_Sinhala_Archaic_Numbers) - 1;
	if (scan(buffer_Sinhala_Archaic_Numbers, buffer_Sinhala_Archaic_Numbers + buffer_Sinhala_Archaic_Numbers_len, Sinhala_Archaic_Numbers) != Sinhala_Archaic_Numbers)
		printf("test 'Sinhala_Archaic_Numbers' failed\n");
	delete[] buffer_Sinhala_Archaic_Numbers;

	YYCTYPE *buffer_Khojki = new YYCTYPE[81];
	uint32_t buffer_Khojki_len = encode_utf32(chars_Khojki[0], chars_Khojki[1], buffer_Khojki) - 1;
	if (scan(buffer_Khojki, buffer_Khojki + buffer_Khojki_len, Khojki) != Khojki)
		printf("test 'Khojki' failed\n");
	delete[] buffer_Khojki;

	YYCTYPE *buffer_Multani = new YYCTYPE[49];
	uint32_t buffer_Multani_len = encode_utf32(chars_Multani[0], chars_Multani[1], buffer_Multani) - 1;
	if (scan(buffer_Multani, buffer_Multani + buffer_Multani_len, Multani) != Multani)
		printf("test 'Multani' failed\n");
	delete[] buffer_Multani;

	YYCTYPE *buffer_Khudawadi = new YYCTYPE[81];
	uint32_t buffer_Khudawadi_len = encode_utf32(chars_Khudawadi[0], chars_Khudawadi[1], buffer_Khudawadi) - 1;
	if (scan(buffer_Khudawadi, buffer_Khudawadi + buffer_Khudawadi_len, Khudawadi) != Khudawadi)
		printf("test 'Khudawadi' failed\n");
	delete[] buffer_Khudawadi;

	YYCTYPE *buffer_Grantha = new YYCTYPE[129];
	uint32_t buffer_Grantha_len = encode_utf32(chars_Grantha[0], chars_Grantha[1], buffer_Grantha) - 1;
	if (scan(buffer_Grantha, buffer_Grantha + buffer_Grantha_len, Grantha) != Grantha)
		printf("test 'Grantha' failed\n");
	delete[] buffer_Grantha;

	YYCTYPE *buffer_Newa = new YYCTYPE[129];
	uint32_t buffer_Newa_len = encode_utf32(chars_Newa[0], chars_Newa[1], buffer_Newa) - 1;
	if (scan(buffer_Newa, buffer_Newa + buffer_Newa_len, Newa) != Newa)
		printf("test 'Newa' failed\n");
	delete[] buffer_Newa;

	YYCTYPE *buffer_Tirhuta = new YYCTYPE[97];
	uint32_t buffer_Tirhuta_len = encode_utf32(chars_Tirhuta[0], chars_Tirhuta[1], buffer_Tirhuta) - 1;
	if (scan(buffer_Tirhuta, buffer_Tirhuta + buffer_Tirhuta_len, Tirhuta) != Tirhuta)
		printf("test 'Tirhuta' failed\n");
	delete[] buffer_Tirhuta;

	YYCTYPE *buffer_Siddham = new YYCTYPE[129];
	uint32_t buffer_Siddham_len = encode_utf32(chars_Siddham[0], chars_Siddham[1], buffer_Siddham) - 1;
	if (scan(buffer_Siddham, buffer_Siddham + buffer_Siddham_len, Siddham) != Siddham)
		printf("test 'Siddham' failed\n");
	delete[] buffer_Siddham;

	YYCTYPE *buffer_Modi = new YYCTYPE[97];
	uint32_t buffer_Modi_len = encode_utf32(chars_Modi[0], chars_Modi[1], buffer_Modi) - 1;
	if (scan(buffer_Modi, buffer_Modi + buffer_Modi_len, Modi) != Modi)
		printf("test 'Modi' failed\n");
	delete[] buffer_Modi;

	YYCTYPE *buffer_Mongolian_Supplement = new YYCTYPE[33];
	uint32_t buffer_Mongolian_Supplement_len = encode_utf32(chars_Mongolian_Supplement[0], chars_Mongolian_Supplement[1], buffer_Mongolian_Supplement) - 1;
	if (scan(buffer_Mongolian_Supplement, buffer_Mongolian_Supplement + buffer_Mongolian_Supplement_len, Mongolian_Supplement) != Mongolian_Supplement)
		printf("test 'Mongolian_Supplement' failed\n");
	delete[] buffer_Mongolian_Supplement;

	YYCTYPE *buffer_Takri = new YYCTYPE[81];
	uint32_t buffer_Takri_len = encode_utf32(chars_Takri[0], chars_Takri[1], buffer_Takri) - 1;
	if (scan(buffer_Takri, buffer_Takri + buffer_Takri_len, Takri) != Takri)
		printf("test 'Takri' failed\n");
	delete[] buffer_Takri;

	YYCTYPE *buffer_Ahom = new YYCTYPE[81];
	uint32_t buffer_Ahom_len = encode_utf32(chars_Ahom[0], chars_Ahom[1], buffer_Ahom) - 1;
	if (scan(buffer_Ahom, buffer_Ahom + buffer_Ahom_len, Ahom) != Ahom)
		printf("test 'Ahom' failed\n");
	delete[] buffer_Ahom;

	YYCTYPE *buffer_Dogra = new YYCTYPE[81];
	uint32_t buffer_Dogra_len = encode_utf32(chars_Dogra[0], chars_Dogra[1], buffer_Dogra) - 1;
	if (scan(buffer_Dogra, buffer_Dogra + buffer_Dogra_len, Dogra) != Dogra)
		printf("test 'Dogra' failed\n");
	delete[] buffer_Dogra;

	YYCTYPE *buffer_Warang_Citi = new YYCTYPE[97];
	uint32_t buffer_Warang_Citi_len = encode_utf32(chars_Warang_Citi[0], chars_Warang_Citi[1], buffer_Warang_Citi) - 1;
	if (scan(buffer_Warang_Citi, buffer_Warang_Citi + buffer_Warang_Citi_len, Warang_Citi) != Warang_Citi)
		printf("test 'Warang_Citi' failed\n");
	delete[] buffer_Warang_Citi;

	YYCTYPE *buffer_Dives_Akuru = new YYCTYPE[97];
	uint32_t buffer_Dives_Akuru_len = encode_utf32(chars_Dives_Akuru[0], chars_Dives_Akuru[1], buffer_Dives_Akuru) - 1;
	if (scan(buffer_Dives_Akuru, buffer_Dives_Akuru + buffer_Dives_Akuru_len, Dives_Akuru) != Dives_Akuru)
		printf("test 'Dives_Akuru' failed\n");
	delete[] buffer_Dives_Akuru;

	YYCTYPE *buffer_Nandinagari = new YYCTYPE[97];
	uint32_t buffer_Nandinagari_len = encode_utf32(chars_Nandinagari[0], chars_Nandinagari[1], buffer_Nandinagari) - 1;
	if (scan(buffer_Nandinagari, buffer_Nandinagari + buffer_Nandinagari_len, Nandinagari) != Nandinagari)
		printf("test 'Nandinagari' failed\n");
	delete[] buffer_Nandinagari;

	YYCTYPE *buffer_Zanabazar_Square = new YYCTYPE[81];
	uint32_t buffer_Zanabazar_Square_len = encode_utf32(chars_Zanabazar_Square[0], chars_Zanabazar_Square[1], buffer_Zanabazar_Square) - 1;
	if (scan(buffer_Zanabazar_Square, buffer_Zanabazar_Square + buffer_Zanabazar_Square_len, Zanabazar_Square) != Zanabazar_Square)
		printf("test 'Zanabazar_Square' failed\n");
	delete[] buffer_Zanabazar_Square;

	YYCTYPE *buffer_Soyombo = new YYCTYPE[97];
	uint32_t buffer_Soyombo_len = encode_utf32(chars_Soyombo[0], chars_Soyombo[1], buffer_Soyombo) - 1;
	if (scan(buffer_Soyombo, buffer_Soyombo + buffer_Soyombo_len, Soyombo) != Soyombo)
		printf("test 'Soyombo' failed\n");
	delete[] buffer_Soyombo;

	YYCTYPE *buffer_Unified_Canadian_Aboriginal_Syllabics_Extended_A = new YYCTYPE[17];
	uint32_t buffer_Unified_Canadian_Aboriginal_Syllabics_Extended_A_len = encode_utf32(chars_Unified_Canadian_Aboriginal_Syllabics_Extended_A[0], chars_Unified_Canadian_Aboriginal_Syllabics_Extended_A[1], buffer_Unified_Canadian_Aboriginal_Syllabics_Extended_A) - 1;
	if (scan(buffer_Unified_Canadian_Aboriginal_Syllabics_Extended_A, buffer_Unified_Canadian_Aboriginal_Syllabics_Extended_A + buffer_Unified_Canadian_Aboriginal_Syllabics_Extended_A_len, Unified_Canadian_Aboriginal_Syllabics_Extended_A) != Unified_Canadian_Aboriginal_Syllabics_Extended_A)
		printf("test 'Unified_Canadian_Aboriginal_Syllabics_Extended_A' failed\n");
	delete[] buffer_Unified_Canadian_Aboriginal_Syllabics_Extended_A;

	YYCTYPE *buffer_Pau_Cin_Hau = new YYCTYPE[65];
	uint32_t buffer_Pau_Cin_Hau_len = encode_utf32(chars_Pau_Cin_Hau[0], chars_Pau_Cin_Hau[1], buffer_Pau_Cin_Hau) - 1;
	if (scan(buffer_Pau_Cin_Hau, buffer_Pau_Cin_Hau + buffer_Pau_Cin_Hau_len, Pau_Cin_Hau) != Pau_Cin_Hau)
		printf("test 'Pau_Cin_Hau' failed\n");
	delete[] buffer_Pau_Cin_Hau;

	YYCTYPE *buffer_Devanagari_Extended_A = new YYCTYPE[97];
	uint32_t buffer_Devanagari_Extended_A_len = encode_utf32(chars_Devanagari_Extended_A[0], chars_Devanagari_Extended_A[1], buffer_Devanagari_Extended_A) - 1;
	if (scan(buffer_Devanagari_Extended_A, buffer_Devanagari_Extended_A + buffer_Devanagari_Extended_A_len, Devanagari_Extended_A) != Devanagari_Extended_A)
		printf("test 'Devanagari_Extended_A' failed\n");
	delete[] buffer_Devanagari_Extended_A;

	YYCTYPE *buffer_Bhaiksuki = new YYCTYPE[113];
	uint32_t buffer_Bhaiksuki_len = encode_utf32(chars_Bhaiksuki[0], chars_Bhaiksuki[1], buffer_Bhaiksuki) - 1;
	if (scan(buffer_Bhaiksuki, buffer_Bhaiksuki + buffer_Bhaiksuki_len, Bhaiksuki) != Bhaiksuki)
		printf("test 'Bhaiksuki' failed\n");
	delete[] buffer_Bhaiksuki;

	YYCTYPE *buffer_Marchen = new YYCTYPE[81];
	uint32_t buffer_Marchen_len = encode_utf32(chars_Marchen[0], chars_Marchen[1], buffer_Marchen) - 1;
	if (scan(buffer_Marchen, buffer_Marchen + buffer_Marchen_len, Marchen) != Marchen)
		printf("test 'Marchen' failed\n");
	delete[] buffer_Marchen;

	YYCTYPE *buffer_Masaram_Gondi = new YYCTYPE[97];
	uint32_t buffer_Masaram_Gondi_len = encode_utf32(chars_Masaram_Gondi[0], chars_Masaram_Gondi[1], buffer_Masaram_Gondi) - 1;
	if (scan(buffer_Masaram_Gondi, buffer_Masaram_Gondi + buffer_Masaram_Gondi_len, Masaram_Gondi) != Masaram_Gondi)
		printf("test 'Masaram_Gondi' failed\n");
	delete[] buffer_Masaram_Gondi;

	YYCTYPE *buffer_Gunjala_Gondi = new YYCTYPE[81];
	uint32_t buffer_Gunjala_Gondi_len = encode_utf32(chars_Gunjala_Gondi[0], chars_Gunjala_Gondi[1], buffer_Gunjala_Gondi) - 1;
	if (scan(buffer_Gunjala_Gondi, buffer_Gunjala_Gondi + buffer_Gunjala_Gondi_len, Gunjala_Gondi) != Gunjala_Gondi)
		printf("test 'Gunjala_Gondi' failed\n");
	delete[] buffer_Gunjala_Gondi;

	YYCTYPE *buffer_Makasar = new YYCTYPE[33];
	uint32_t buffer_Makasar_len = encode_utf32(chars_Makasar[0], chars_Makasar[1], buffer_Makasar) - 1;
	if (scan(buffer_Makasar, buffer_Makasar + buffer_Makasar_len, Makasar) != Makasar)
		printf("test 'Makasar' failed\n");
	delete[] buffer_Makasar;

	YYCTYPE *buffer_Kawi = new YYCTYPE[97];
	uint32_t buffer_Kawi_len = encode_utf32(chars_Kawi[0], chars_Kawi[1], buffer_Kawi) - 1;
	if (scan(buffer_Kawi, buffer_Kawi + buffer_Kawi_len, Kawi) != Kawi)
		printf("test 'Kawi' failed\n");
	delete[] buffer_Kawi;

	YYCTYPE *buffer_Lisu_Supplement = new YYCTYPE[17];
	uint32_t buffer_Lisu_Supplement_len = encode_utf32(chars_Lisu_Supplement[0], chars_Lisu_Supplement[1], buffer_Lisu_Supplement) - 1;
	if (scan(buffer_Lisu_Supplement, buffer_Lisu_Supplement + buffer_Lisu_Supplement_len, Lisu_Supplement) != Lisu_Supplement)
		printf("test 'Lisu_Supplement' failed\n");
	delete[] buffer_Lisu_Supplement;

	YYCTYPE *buffer_Tamil_Supplement = new YYCTYPE[65];
	uint32_t buffer_Tamil_Supplement_len = encode_utf32(chars_Tamil_Supplement[0], chars_Tamil_Supplement[1], buffer_Tamil_Supplement) - 1;
	if (scan(buffer_Tamil_Supplement, buffer_Tamil_Supplement + buffer_Tamil_Supplement_len, Tamil_Supplement) != Tamil_Supplement)
		printf("test 'Tamil_Supplement' failed\n");
	delete[] buffer_Tamil_Supplement;

	YYCTYPE *buffer_Cuneiform = new YYCTYPE[1025];
	uint32_t buffer_Cuneiform_len = encode_utf32(chars_Cuneiform[0], chars_Cuneiform[1], buffer_Cuneiform) - 1;
	if (scan(buffer_Cuneiform, buffer_Cuneiform + buffer_Cuneiform_len, Cuneiform) != Cuneiform)
		printf("test 'Cuneiform' failed\n");
	delete[] buffer_Cuneiform;

	YYCTYPE *buffer_Cuneiform_Numbers_and_Punctuation = new YYCTYPE[129];
	uint32_t buffer_Cuneiform_Numbers_and_Punctuation_len = encode_utf32(chars_Cuneiform_Numbers_and_Punctuation[0], chars_Cuneiform_Numbers_and_Punctuation[1], buffer_Cuneiform_Numbers_and_Punctuation) - 1;
	if (scan(buffer_Cuneiform_Numbers_and_Punctuation, buffer_Cuneiform_Numbers_and_Punctuation + buffer_Cuneiform_Numbers_and_Punctuation_len, Cuneiform_Numbers_and_Punctuation) != Cuneiform_Numbers_and_Punctuation)
		printf("test 'Cuneiform_Numbers_and_Punctuation' failed\n");
	delete[] buffer_Cuneiform_Numbers_and_Punctuation;

	YYCTYPE *buffer_Early_Dynastic_Cuneiform = new YYCTYPE[209];
	uint32_t buffer_Early_Dynastic_Cuneiform_len = encode_utf32(chars_Early_Dynastic_Cuneiform[0], chars_Early_Dynastic_Cuneiform[1], buffer_Early_Dynastic_Cuneiform) - 1;
	if (scan(buffer_Early_Dynastic_Cuneiform, buffer_Early_Dynastic_Cuneiform + buffer_Early_Dynastic_Cuneiform_len, Early_Dynastic_Cuneiform) != Early_Dynastic_Cuneiform)
		printf("test 'Early_Dynastic_Cuneiform' failed\n");
	delete[] buffer_Early_Dynastic_Cuneiform;

	YYCTYPE *buffer_Cypro_Minoan = new YYCTYPE[113];
	uint32_t buffer_Cypro_Minoan_len = encode_utf32(chars_Cypro_Minoan[0], chars_Cypro_Minoan[1], buffer_Cypro_Minoan) - 1;
	if (scan(buffer_Cypro_Minoan, buffer_Cypro_Minoan + buffer_Cypro_Minoan_len, Cypro_Minoan) != Cypro_Minoan)
		printf("test 'Cypro_Minoan' failed\n");
	delete[] buffer_Cypro_Minoan;

	YYCTYPE *buffer_Egyptian_Hieroglyphs = new YYCTYPE[1073];
	uint32_t buffer_Egyptian_Hieroglyphs_len = encode_utf32(chars_Egyptian_Hieroglyphs[0], chars_Egyptian_Hieroglyphs[1], buffer_Egyptian_Hieroglyphs) - 1;
	if (scan(buffer_Egyptian_Hieroglyphs, buffer_Egyptian_Hieroglyphs + buffer_Egyptian_Hieroglyphs_len, Egyptian_Hieroglyphs) != Egyptian_Hieroglyphs)
		printf("test 'Egyptian_Hieroglyphs' failed\n");
	delete[] buffer_Egyptian_Hieroglyphs;

	YYCTYPE *buffer_Egyptian_Hieroglyph_Format_Controls = new YYCTYPE[49];
	uint32_t buffer_Egyptian_Hieroglyph_Format_Controls_len = encode_utf32(chars_Egyptian_Hieroglyph_Format_Controls[0], chars_Egyptian_Hieroglyph_Format_Controls[1], buffer_Egyptian_Hieroglyph_Format_Controls) - 1;
	if (scan(buffer_Egyptian_Hieroglyph_Format_Controls, buffer_Egyptian_Hieroglyph_Format_Controls + buffer_Egyptian_Hieroglyph_Format_Controls_len, Egyptian_Hieroglyph_Format_Controls) != Egyptian_Hieroglyph_Format_Controls)
		printf("test 'Egyptian_Hieroglyph_Format_Controls' failed\n");
	delete[] buffer_Egyptian_Hieroglyph_Format_Controls;

	YYCTYPE *buffer_Anatolian_Hieroglyphs = new YYCTYPE[641];
	uint32_t buffer_Anatolian_Hieroglyphs_len = encode_utf32(chars_Anatolian_Hieroglyphs[0], chars_Anatolian_Hieroglyphs[1], buffer_Anatolian_Hieroglyphs) - 1;
	if (scan(buffer_Anatolian_Hieroglyphs, buffer_Anatolian_Hieroglyphs + buffer_Anatolian_Hieroglyphs_len, Anatolian_Hieroglyphs) != Anatolian_Hieroglyphs)
		printf("test 'Anatolian_Hieroglyphs' failed\n");
	delete[] buffer_Anatolian_Hieroglyphs;

	YYCTYPE *buffer_Bamum_Supplement = new YYCTYPE[577];
	uint32_t buffer_Bamum_Supplement_len = encode_utf32(chars_Bamum_Supplement[0], chars_Bamum_Supplement[1], buffer_Bamum_Supplement) - 1;
	if (scan(buffer_Bamum_Supplement, buffer_Bamum_Supplement + buffer_Bamum_Supplement_len, Bamum_Supplement) != Bamum_Supplement)
		printf("test 'Bamum_Supplement' failed\n");
	delete[] buffer_Bamum_Supplement;

	YYCTYPE *buffer_Mro = new YYCTYPE[49];
	uint32_t buffer_Mro_len = encode_utf32(chars_Mro[0], chars_Mro[1], buffer_Mro) - 1;
	if (scan(buffer_Mro, buffer_Mro + buffer_Mro_len, Mro) != Mro)
		printf("test 'Mro' failed\n");
	delete[] buffer_Mro;

	YYCTYPE *buffer_Tangsa = new YYCTYPE[97];
	uint32_t buffer_Tangsa_len = encode_utf32(chars_Tangsa[0], chars_Tangsa[1], buffer_Tangsa) - 1;
	if (scan(buffer_Tangsa, buffer_Tangsa + buffer_Tangsa_len, Tangsa) != Tangsa)
		printf("test 'Tangsa' failed\n");
	delete[] buffer_Tangsa;

	YYCTYPE *buffer_Bassa_Vah = new YYCTYPE[49];
	uint32_t buffer_Bassa_Vah_len = encode_utf32(chars_Bassa_Vah[0], chars_Bassa_Vah[1], buffer_Bassa_Vah) - 1;
	if (scan(buffer_Bassa_Vah, buffer_Bassa_Vah + buffer_Bassa_Vah_len, Bassa_Vah) != Bassa_Vah)
		printf("test 'Bassa_Vah' failed\n");
	delete[] buffer_Bassa_Vah;

	YYCTYPE *buffer_Pahawh_Hmong = new YYCTYPE[145];
	uint32_t buffer_Pahawh_Hmong_len = encode_utf32(chars_Pahawh_Hmong[0], chars_Pahawh_Hmong[1], buffer_Pahawh_Hmong) - 1;
	if (scan(buffer_Pahawh_Hmong, buffer_Pahawh_Hmong + buffer_Pahawh_Hmong_len, Pahawh_Hmong) != Pahawh_Hmong)
		printf("test 'Pahawh_Hmong' failed\n");
	delete[] buffer_Pahawh_Hmong;

	YYCTYPE *buffer_Medefaidrin = new YYCTYPE[97];
	uint32_t buffer_Medefaidrin_len = encode_utf32(chars_Medefaidrin[0], chars_Medefaidrin[1], buffer_Medefaidrin) - 1;
	if (scan(buffer_Medefaidrin, buffer_Medefaidrin + buffer_Medefaidrin_len, Medefaidrin) != Medefaidrin)
		printf("test 'Medefaidrin' failed\n");
	delete[] buffer_Medefaidrin;

	YYCTYPE *buffer_Miao = new YYCTYPE[161];
	uint32_t buffer_Miao_len = encode_utf32(chars_Miao[0], chars_Miao[1], buffer_Miao) - 1;
	if (scan(buffer_Miao, buffer_Miao + buffer_Miao_len, Miao) != Miao)
		printf("test 'Miao' failed\n");
	delete[] buffer_Miao;

	YYCTYPE *buffer_Ideographic_Symbols_and_Punctuation = new YYCTYPE[33];
	uint32_t buffer_Ideographic_Symbols_and_Punctuation_len = encode_utf32(chars_Ideographic_Symbols_and_Punctuation[0], chars_Ideographic_Symbols_and_Punctuation[1], buffer_Ideographic_Symbols_and_Punctuation) - 1;
	if (scan(buffer_Ideographic_Symbols_and_Punctuation, buffer_Ideographic_Symbols_and_Punctuation + buffer_Ideographic_Symbols_and_Punctuation_len, Ideographic_Symbols_and_Punctuation) != Ideographic_Symbols_and_Punctuation)
		printf("test 'Ideographic_Symbols_and_Punctuation' failed\n");
	delete[] buffer_Ideographic_Symbols_and_Punctuation;

	YYCTYPE *buffer_Tangut = new YYCTYPE[6145];
	uint32_t buffer_Tangut_len = encode_utf32(chars_Tangut[0], chars_Tangut[1], buffer_Tangut) - 1;
	if (scan(buffer_Tangut, buffer_Tangut + buffer_Tangut_len, Tangut) != Tangut)
		printf("test 'Tangut' failed\n");
	delete[] buffer_Tangut;

	YYCTYPE *buffer_Tangut_Components = new YYCTYPE[769];
	uint32_t buffer_Tangut_Components_len = encode_utf32(chars_Tangut_Components[0], chars_Tangut_Components[1], buffer_Tangut_Components) - 1;
	if (scan(buffer_Tangut_Components, buffer_Tangut_Components + buffer_Tangut_Components_len, Tangut_Components) != Tangut_Components)
		printf("test 'Tangut_Components' failed\n");
	delete[] buffer_Tangut_Components;

	YYCTYPE *buffer_Khitan_Small_Script = new YYCTYPE[513];
	uint32_t buffer_Khitan_Small_Script_len = encode_utf32(chars_Khitan_Small_Script[0], chars_Khitan_Small_Script[1], buffer_Khitan_Small_Script) - 1;
	if (scan(buffer_Khitan_Small_Script, buffer_Khitan_Small_Script + buffer_Khitan_Small_Script_len, Khitan_Small_Script) != Khitan_Small_Script)
		printf("test 'Khitan_Small_Script' failed\n");
	delete[] buffer_Khitan_Small_Script;

	YYCTYPE *buffer_Tangut_Supplement = new YYCTYPE[129];
	uint32_t buffer_Tangut_Supplement_len = encode_utf32(chars_Tangut_Supplement[0], chars_Tangut_Supplement[1], buffer_Tangut_Supplement) - 1;
	if (scan(buffer_Tangut_Supplement, buffer_Tangut_Supplement + buffer_Tangut_Supplement_len, Tangut_Supplement) != Tangut_Supplement)
		printf("test 'Tangut_Supplement' failed\n");
	delete[] buffer_Tangut_Supplement;

	YYCTYPE *buffer_Kana_Extended_B = new YYCTYPE[17];
	uint32_t buffer_Kana_Extended_B_len = encode_utf32(chars_Kana_Extended_B[0], chars_Kana_Extended_B[1], buffer_Kana_Extended_B) - 1;
	if (scan(buffer_Kana_Extended_B, buffer_Kana_Extended_B + buffer_Kana_Extended_B_len, Kana_Extended_B) != Kana_Extended_B)
		printf("test 'Kana_Extended_B' failed\n");
	delete[] buffer_Kana_Extended_B;

	YYCTYPE *buffer_Kana_Supplement = new YYCTYPE[257];
	uint32_t buffer_Kana_Supplement_len = encode_utf32(chars_Kana_Supplement[0], chars_Kana_Supplement[1], buffer_Kana_Supplement) - 1;
	if (scan(buffer_Kana_Supplement, buffer_Kana_Supplement + buffer_Kana_Supplement_len, Kana_Supplement) != Kana_Supplement)
		printf("test 'Kana_Supplement' failed\n");
	delete[] buffer_Kana_Supplement;

	YYCTYPE *buffer_Kana_Extended_A = new YYCTYPE[49];
	uint32_t buffer_Kana_Extended_A_len = encode_utf32(chars_Kana_Extended_A[0], chars_Kana_Extended_A[1], buffer_Kana_Extended_A) - 1;
	if (scan(buffer_Kana_Extended_A, buffer_Kana_Extended_A + buffer_Kana_Extended_A_len, Kana_Extended_A) != Kana_Extended_A)
		printf("test 'Kana_Extended_A' failed\n");
	delete[] buffer_Kana_Extended_A;

	YYCTYPE *buffer_Small_Kana_Extension = new YYCTYPE[65];
	uint32_t buffer_Small_Kana_Extension_len = encode_utf32(chars_Small_Kana_Extension[0], chars_Small_Kana_Extension[1], buffer_Small_Kana_Extension) - 1;
	if (scan(buffer_Small_Kana_Extension, buffer_Small_Kana_Extension + buffer_Small_Kana_Extension_len, Small_Kana_Extension) != Small_Kana_Extension)
		printf("test 'Small_Kana_Extension' failed\n");
	delete[] buffer_Small_Kana_Extension;

	YYCTYPE *buffer_Nushu = new YYCTYPE[401];
	uint32_t buffer_Nushu_len = encode_utf32(chars_Nushu[0], chars_Nushu[1], buffer_Nushu) - 1;
	if (scan(buffer_Nushu, buffer_Nushu + buffer_Nushu_len, Nushu) != Nushu)
		printf("test 'Nushu' failed\n");
	delete[] buffer_Nushu;

	YYCTYPE *buffer_Duployan = new YYCTYPE[161];
	uint32_t buffer_Duployan_len = encode_utf32(chars_Duployan[0], chars_Duployan[1], buffer_Duployan) - 1;
	if (scan(buffer_Duployan, buffer_Duployan + buffer_Duployan_len, Duployan) != Duployan)
		printf("test 'Duployan' failed\n");
	delete[] buffer_Duployan;

	YYCTYPE *buffer_Shorthand_Format_Controls = new YYCTYPE[17];
	uint32_t buffer_Shorthand_Format_Controls_len = encode_utf32(chars_Shorthand_Format_Controls[0], chars_Shorthand_Format_Controls[1], buffer_Shorthand_Format_Controls) - 1;
	if (scan(buffer_Shorthand_Format_Controls, buffer_Shorthand_Format_Controls + buffer_Shorthand_Format_Controls_len, Shorthand_Format_Controls) != Shorthand_Format_Controls)
		printf("test 'Shorthand_Format_Controls' failed\n");
	delete[] buffer_Shorthand_Format_Controls;

	YYCTYPE *buffer_Znamenny_Musical_Notation = new YYCTYPE[209];
	uint32_t buffer_Znamenny_Musical_Notation_len = encode_utf32(chars_Znamenny_Musical_Notation[0], chars_Znamenny_Musical_Notation[1], buffer_Znamenny_Musical_Notation) - 1;
	if (scan(buffer_Znamenny_Musical_Notation, buffer_Znamenny_Musical_Notation + buffer_Znamenny_Musical_Notation_len, Znamenny_Musical_Notation) != Znamenny_Musical_Notation)
		printf("test 'Znamenny_Musical_Notation' failed\n");
	delete[] buffer_Znamenny_Musical_Notation;

	YYCTYPE *buffer_Byzantine_Musical_Symbols = new YYCTYPE[257];
	uint32_t buffer_Byzantine_Musical_Symbols_len = encode_utf32(chars_Byzantine_Musical_Symbols[0], chars_Byzantine_Musical_Symbols[1], buffer_Byzantine_Musical_Symbols) - 1;
	if (scan(buffer_Byzantine_Musical_Symbols, buffer_Byzantine_Musical_Symbols + buffer_Byzantine_Musical_Symbols_len, Byzantine_Musical_Symbols) != Byzantine_Musical_Symbols)
		printf("test 'Byzantine_Musical_Symbols' failed\n");
	delete[] buffer_Byzantine_Musical_Symbols;

	YYCTYPE *buffer_Musical_Symbols = new YYCTYPE[257];
	uint32_t buffer_Musical_Symbols_len = encode_utf32(chars_Musical_Symbols[0], chars_Musical_Symbols[1], buffer_Musical_Symbols) - 1;
	if (scan(buffer_Musical_Symbols, buffer_Musical_Symbols + buffer_Musical_Symbols_len, Musical_Symbols) != Musical_Symbols)
		printf("test 'Musical_Symbols' failed\n");
	delete[] buffer_Musical_Symbols;

	YYCTYPE *buffer_Ancient_Greek_Musical_Notation = new YYCTYPE[81];
	uint32_t buffer_Ancient_Greek_Musical_Notation_len = encode_utf32(chars_Ancient_Greek_Musical_Notation[0], chars_Ancient_Greek_Musical_Notation[1], buffer_Ancient_Greek_Musical_Notation) - 1;
	if (scan(buffer_Ancient_Greek_Musical_Notation, buffer_Ancient_Greek_Musical_Notation + buffer_Ancient_Greek_Musical_Notation_len, Ancient_Greek_Musical_Notation) != Ancient_Greek_Musical_Notation)
		printf("test 'Ancient_Greek_Musical_Notation' failed\n");
	delete[] buffer_Ancient_Greek_Musical_Notation;

	YYCTYPE *buffer_Kaktovik_Numerals = new YYCTYPE[33];
	uint32_t buffer_Kaktovik_Numerals_len = encode_utf32(chars_Kaktovik_Numerals[0], chars_Kaktovik_Numerals[1], buffer_Kaktovik_Numerals) - 1;
	if (scan(buffer_Kaktovik_Numerals, buffer_Kaktovik_Numerals + buffer_Kaktovik_Numerals_len, Kaktovik_Numerals) != Kaktovik_Numerals)
		printf("test 'Kaktovik_Numerals' failed\n");
	delete[] buffer_Kaktovik_Numerals;

	YYCTYPE *buffer_Mayan_Numerals = new YYCTYPE[33];
	uint32_t buffer_Mayan_Numerals_len = encode_utf32(chars_Mayan_Numerals[0], chars_Mayan_Numerals[1], buffer_Mayan_Numerals) - 1;
	if (scan(buffer_Mayan_Numerals, buffer_Mayan_Numerals + buffer_Mayan_Numerals_len, Mayan_Numerals) != Mayan_Numerals)
		printf("test 'Mayan_Numerals' failed\n");
	delete[] buffer_Mayan_Numerals;

	YYCTYPE *buffer_Tai_Xuan_Jing_Symbols = new YYCTYPE[97];
	uint32_t buffer_Tai_Xuan_Jing_Symbols_len = encode_utf32(chars_Tai_Xuan_Jing_Symbols[0], chars_Tai_Xuan_Jing_Symbols[1], buffer_Tai_Xuan_Jing_Symbols) - 1;
	if (scan(buffer_Tai_Xuan_Jing_Symbols, buffer_Tai_Xuan_Jing_Symbols + buffer_Tai_Xuan_Jing_Symbols_len, Tai_Xuan_Jing_Symbols) != Tai_Xuan_Jing_Symbols)
		printf("test 'Tai_Xuan_Jing_Symbols' failed\n");
	delete[] buffer_Tai_Xuan_Jing_Symbols;

	YYCTYPE *buffer_Counting_Rod_Numerals = new YYCTYPE[33];
	uint32_t buffer_Counting_Rod_Numerals_len = encode_utf32(chars_Counting_Rod_Numerals[0], chars_Counting_Rod_Numerals[1], buffer_Counting_Rod_Numerals) - 1;
	if (scan(buffer_Counting_Rod_Numerals, buffer_Counting_Rod_Numerals + buffer_Counting_Rod_Numerals_len, Counting_Rod_Numerals) != Counting_Rod_Numerals)
		printf("test 'Counting_Rod_Numerals' failed\n");
	delete[] buffer_Counting_Rod_Numerals;

	YYCTYPE *buffer_Mathematical_Alphanumeric_Symbols = new YYCTYPE[1025];
	uint32_t buffer_Mathematical_Alphanumeric_Symbols_len = encode_utf32(chars_Mathematical_Alphanumeric_Symbols[0], chars_Mathematical_Alphanumeric_Symbols[1], buffer_Mathematical_Alphanumeric_Symbols) - 1;
	if (scan(buffer_Mathematical_Alphanumeric_Symbols, buffer_Mathematical_Alphanumeric_Symbols + buffer_Mathematical_Alphanumeric_Symbols_len, Mathematical_Alphanumeric_Symbols) != Mathematical_Alphanumeric_Symbols)
		printf("test 'Mathematical_Alphanumeric_Symbols' failed\n");
	delete[] buffer_Mathematical_Alphanumeric_Symbols;

	YYCTYPE *buffer_Sutton_SignWriting = new YYCTYPE[689];
	uint32_t buffer_Sutton_SignWriting_len = encode_utf32(chars_Sutton_SignWriting[0], chars_Sutton_SignWriting[1], buffer_Sutton_SignWriting) - 1;
	if (scan(buffer_Sutton_SignWriting, buffer_Sutton_SignWriting + buffer_Sutton_SignWriting_len, Sutton_SignWriting) != Sutton_SignWriting)
		printf("test 'Sutton_SignWriting' failed\n");
	delete[] buffer_Sutton_SignWriting;

	YYCTYPE *buffer_Latin_Extended_G = new YYCTYPE[257];
	uint32_t buffer_Latin_Extended_G_len = encode_utf32(chars_Latin_Extended_G[0], chars_Latin_Extended_G[1], buffer_Latin_Extended_G) - 1;
	if (scan(buffer_Latin_Extended_G, buffer_Latin_Extended_G + buffer_Latin_Extended_G_len, Latin_Extended_G) != Latin_Extended_G)
		printf("test 'Latin_Extended_G' failed\n");
	delete[] buffer_Latin_Extended_G;

	YYCTYPE *buffer_Glagolitic_Supplement = new YYCTYPE[49];
	uint32_t buffer_Glagolitic_Supplement_len = encode_utf32(chars_Glagolitic_Supplement[0], chars_Glagolitic_Supplement[1], buffer_Glagolitic_Supplement) - 1;
	if (scan(buffer_Glagolitic_Supplement, buffer_Glagolitic_Supplement + buffer_Glagolitic_Supplement_len, Glagolitic_Supplement) != Glagolitic_Supplement)
		printf("test 'Glagolitic_Supplement' failed\n");
	delete[] buffer_Glagolitic_Supplement;

	YYCTYPE *buffer_Cyrillic_Extended_D = new YYCTYPE[97];
	uint32_t buffer_Cyrillic_Extended_D_len = encode_utf32(chars_Cyrillic_Extended_D[0], chars_Cyrillic_Extended_D[1], buffer_Cyrillic_Extended_D) - 1;
	if (scan(buffer_Cyrillic_Extended_D, buffer_Cyrillic_Extended_D + buffer_Cyrillic_Extended_D_len, Cyrillic_Extended_D) != Cyrillic_Extended_D)
		printf("test 'Cyrillic_Extended_D' failed\n");
	delete[] buffer_Cyrillic_Extended_D;

	YYCTYPE *buffer_Nyiakeng_Puachue_Hmong = new YYCTYPE[81];
	uint32_t buffer_Nyiakeng_Puachue_Hmong_len = encode_utf32(chars_Nyiakeng_Puachue_Hmong[0], chars_Nyiakeng_Puachue_Hmong[1], buffer_Nyiakeng_Puachue_Hmong) - 1;
	if (scan(buffer_Nyiakeng_Puachue_Hmong, buffer_Nyiakeng_Puachue_Hmong + buffer_Nyiakeng_Puachue_Hmong_len, Nyiakeng_Puachue_Hmong) != Nyiakeng_Puachue_Hmong)
		printf("test 'Nyiakeng_Puachue_Hmong' failed\n");
	delete[] buffer_Nyiakeng_Puachue_Hmong;

	YYCTYPE *buffer_Toto = new YYCTYPE[49];
	uint32_t buffer_Toto_len = encode_utf32(chars_Toto[0], chars_Toto[1], buffer_Toto) - 1;
	if (scan(buffer_Toto, buffer_Toto + buffer_Toto_len, Toto) != Toto)
		printf("test 'Toto' failed\n");
	delete[] buffer_Toto;

	YYCTYPE *buffer_Wancho = new YYCTYPE[65];
	uint32_t buffer_Wancho_len = encode_utf32(chars_Wancho[0], chars_Wancho[1], buffer_Wancho) - 1;
	if (scan(buffer_Wancho, buffer_Wancho + buffer_Wancho_len, Wancho) != Wancho)
		printf("test 'Wancho' failed\n");
	delete[] buffer_Wancho;

	YYCTYPE *buffer_Nag_Mundari = new YYCTYPE[49];
	uint32_t buffer_Nag_Mundari_len = encode_utf32(chars_Nag_Mundari[0], chars_Nag_Mundari[1], buffer_Nag_Mundari) - 1;
	if (scan(buffer_Nag_Mundari, buffer_Nag_Mundari + buffer_Nag_Mundari_len, Nag_Mundari) != Nag_Mundari)
		printf("test 'Nag_Mundari' failed\n");
	delete[] buffer_Nag_Mundari;

	YYCTYPE *buffer_Ethiopic_Extended_B = new YYCTYPE[33];
	uint32_t buffer_Ethiopic_Extended_B_len = encode_utf32(chars_Ethiopic_Extended_B[0], chars_Ethiopic_Extended_B[1], buffer_Ethiopic_Extended_B) - 1;
	if (scan(buffer_Ethiopic_Extended_B, buffer_Ethiopic_Extended_B + buffer_Ethiopic_Extended_B_len, Ethiopic_Extended_B) != Ethiopic_Extended_B)
		printf("test 'Ethiopic_Extended_B' failed\n");
	delete[] buffer_Ethiopic_Extended_B;

	YYCTYPE *buffer_Mende_Kikakui = new YYCTYPE[225];
	uint32_t buffer_Mende_Kikakui_len = encode_utf32(chars_Mende_Kikakui[0], chars_Mende_Kikakui[1], buffer_Mende_Kikakui) - 1;
	if (scan(buffer_Mende_Kikakui, buffer_Mende_Kikakui + buffer_Mende_Kikakui_len, Mende_Kikakui) != Mende_Kikakui)
		printf("test 'Mende_Kikakui' failed\n");
	delete[] buffer_Mende_Kikakui;

	YYCTYPE *buffer_Adlam = new YYCTYPE[97];
	uint32_t buffer_Adlam_len = encode_utf32(chars_Adlam[0], chars_Adlam[1], buffer_Adlam) - 1;
	if (scan(buffer_Adlam, buffer_Adlam + buffer_Adlam_len, Adlam) != Adlam)
		printf("test 'Adlam' failed\n");
	delete[] buffer_Adlam;

	YYCTYPE *buffer_Indic_Siyaq_Numbers = new YYCTYPE[81];
	uint32_t buffer_Indic_Siyaq_Numbers_len = encode_utf32(chars_Indic_Siyaq_Numbers[0], chars_Indic_Siyaq_Numbers[1], buffer_Indic_Siyaq_Numbers) - 1;
	if (scan(buffer_Indic_Siyaq_Numbers, buffer_Indic_Siyaq_Numbers + buffer_Indic_Siyaq_Numbers_len, Indic_Siyaq_Numbers) != Indic_Siyaq_Numbers)
		printf("test 'Indic_Siyaq_Numbers' failed\n");
	delete[] buffer_Indic_Siyaq_Numbers;

	YYCTYPE *buffer_Ottoman_Siyaq_Numbers = new YYCTYPE[81];
	uint32_t buffer_Ottoman_Siyaq_Numbers_len = encode_utf32(chars_Ottoman_Siyaq_Numbers[0], chars_Ottoman_Siyaq_Numbers[1], buffer_Ottoman_Siyaq_Numbers) - 1;
	if (scan(buffer_Ottoman_Siyaq_Numbers, buffer_Ottoman_Siyaq_Numbers + buffer_Ottoman_Siyaq_Numbers_len, Ottoman_Siyaq_Numbers) != Ottoman_Siyaq_Numbers)
		printf("test 'Ottoman_Siyaq_Numbers' failed\n");
	delete[] buffer_Ottoman_Siyaq_Numbers;

	YYCTYPE *buffer_Arabic_Mathematical_Alphabetic_Symbols = new YYCTYPE[257];
	uint32_t buffer_Arabic_Mathematical_Alphabetic_Symbols_len = encode_utf32(chars_Arabic_Mathematical_Alphabetic_Symbols[0], chars_Arabic_Mathematical_Alphabetic_Symbols[1], buffer_Arabic_Mathematical_Alphabetic_Symbols) - 1;
	if (scan(buffer_Arabic_Mathematical_Alphabetic_Symbols, buffer_Arabic_Mathematical_Alphabetic_Symbols + buffer_Arabic_Mathematical_Alphabetic_Symbols_len, Arabic_Mathematical_Alphabetic_Symbols) != Arabic_Mathematical_Alphabetic_Symbols)
		printf("test 'Arabic_Mathematical_Alphabetic_Symbols' failed\n");
	delete[] buffer_Arabic_Mathematical_Alphabetic_Symbols;

	YYCTYPE *buffer_Mahjong_Tiles = new YYCTYPE[49];
	uint32_t buffer_Mahjong_Tiles_len = encode_utf32(chars_Mahjong_Tiles[0], chars_Mahjong_Tiles[1], buffer_Mahjong_Tiles) - 1;
	if (scan(buffer_Mahjong_Tiles, buffer_Mahjong_Tiles + buffer_Mahjong_Tiles_len, Mahjong_Tiles) != Mahjong_Tiles)
		printf("test 'Mahjong_Tiles' failed\n");
	delete[] buffer_Mahjong_Tiles;

	YYCTYPE *buffer_Domino_Tiles = new YYCTYPE[113];
	uint32_t buffer_Domino_Tiles_len = encode_utf32(chars_Domino_Tiles[0], chars_Domino_Tiles[1], buffer_Domino_Tiles) - 1;
	if (scan(buffer_Domino_Tiles, buffer_Domino_Tiles + buffer_Domino_Tiles_len, Domino_Tiles) != Domino_Tiles)
		printf("test 'Domino_Tiles' failed\n");
	delete[] buffer_Domino_Tiles;

	YYCTYPE *buffer_Playing_Cards = new YYCTYPE[97];
	uint32_t buffer_Playing_Cards_len = encode_utf32(chars_Playing_Cards[0], chars_Playing_Cards[1], buffer_Playing_Cards) - 1;
	if (scan(buffer_Playing_Cards, buffer_Playing_Cards + buffer_Playing_Cards_len, Playing_Cards) != Playing_Cards)
		printf("test 'Playing_Cards' failed\n");
	delete[] buffer_Playing_Cards;

	YYCTYPE *buffer_Enclosed_Alphanumeric_Supplement = new YYCTYPE[257];
	uint32_t buffer_Enclosed_Alphanumeric_Supplement_len = encode_utf32(chars_Enclosed_Alphanumeric_Supplement[0], chars_Enclosed_Alphanumeric_Supplement[1], buffer_Enclosed_Alphanumeric_Supplement) - 1;
	if (scan(buffer_Enclosed_Alphanumeric_Supplement, buffer_Enclosed_Alphanumeric_Supplement + buffer_Enclosed_Alphanumeric_Supplement_len, Enclosed_Alphanumeric_Supplement) != Enclosed_Alphanumeric_Supplement)
		printf("test 'Enclosed_Alphanumeric_Supplement' failed\n");
	delete[] buffer_Enclosed_Alphanumeric_Supplement;

	YYCTYPE *buffer_Enclosed_Ideographic_Supplement = new YYCTYPE[257];
	uint32_t buffer_Enclosed_Ideographic_Supplement_len = encode_utf32(chars_Enclosed_Ideographic_Supplement[0], chars_Enclosed_Ideographic_Supplement[1], buffer_Enclosed_Ideographic_Supplement) - 1;
	if (scan(buffer_Enclosed_Ideographic_Supplement, buffer_Enclosed_Ideographic_Supplement + buffer_Enclosed_Ideographic_Supplement_len, Enclosed_Ideographic_Supplement) != Enclosed_Ideographic_Supplement)
		printf("test 'Enclosed_Ideographic_Supplement' failed\n");
	delete[] buffer_Enclosed_Ideographic_Supplement;

	YYCTYPE *buffer_Miscellaneous_Symbols_and_Pictographs = new YYCTYPE[769];
	uint32_t buffer_Miscellaneous_Symbols_and_Pictographs_len = encode_utf32(chars_Miscellaneous_Symbols_and_Pictographs[0], chars_Miscellaneous_Symbols_and_Pictographs[1], buffer_Miscellaneous_Symbols_and_Pictographs) - 1;
	if (scan(buffer_Miscellaneous_Symbols_and_Pictographs, buffer_Miscellaneous_Symbols_and_Pictographs + buffer_Miscellaneous_Symbols_and_Pictographs_len, Miscellaneous_Symbols_and_Pictographs) != Miscellaneous_Symbols_and_Pictographs)
		printf("test 'Miscellaneous_Symbols_and_Pictographs' failed\n");
	delete[] buffer_Miscellaneous_Symbols_and_Pictographs;

	YYCTYPE *buffer_Emoticons = new YYCTYPE[81];
	uint32_t buffer_Emoticons_len = encode_utf32(chars_Emoticons[0], chars_Emoticons[1], buffer_Emoticons) - 1;
	if (scan(buffer_Emoticons, buffer_Emoticons + buffer_Emoticons_len, Emoticons) != Emoticons)
		printf("test 'Emoticons' failed\n");
	delete[] buffer_Emoticons;

	YYCTYPE *buffer_Ornamental_Dingbats = new YYCTYPE[49];
	uint32_t buffer_Ornamental_Dingbats_len = encode_utf32(chars_Ornamental_Dingbats[0], chars_Ornamental_Dingbats[1], buffer_Ornamental_Dingbats) - 1;
	if (scan(buffer_Ornamental_Dingbats, buffer_Ornamental_Dingbats + buffer_Ornamental_Dingbats_len, Ornamental_Dingbats) != Ornamental_Dingbats)
		printf("test 'Ornamental_Dingbats' failed\n");
	delete[] buffer_Ornamental_Dingbats;

	YYCTYPE *buffer_Transport_and_Map_Symbols = new YYCTYPE[129];
	uint32_t buffer_Transport_and_Map_Symbols_len = encode_utf32(chars_Transport_and_Map_Symbols[0], chars_Transport_and_Map_Symbols[1], buffer_Transport_and_Map_Symbols) - 1;
	if (scan(buffer_Transport_and_Map_Symbols, buffer_Transport_and_Map_Symbols + buffer_Transport_and_Map_Symbols_len, Transport_and_Map_Symbols) != Transport_and_Map_Symbols)
		printf("test 'Transport_and_Map_Symbols' failed\n");
	delete[] buffer_Transport_and_Map_Symbols;

	YYCTYPE *buffer_Alchemical_Symbols = new YYCTYPE[129];
	uint32_t buffer_Alchemical_Symbols_len = encode_utf32(chars_Alchemical_Symbols[0], chars_Alchemical_Symbols[1], buffer_Alchemical_Symbols) - 1;
	if (scan(buffer_Alchemical_Symbols, buffer_Alchemical_Symbols + buffer_Alchemical_Symbols_len, Alchemical_Symbols) != Alchemical_Symbols)
		printf("test 'Alchemical_Symbols' failed\n");
	delete[] buffer_Alchemical_Symbols;

	YYCTYPE *buffer_Geometric_Shapes_Extended = new YYCTYPE[129];
	uint32_t buffer_Geometric_Shapes_Extended_len = encode_utf32(chars_Geometric_Shapes_Extended[0], chars_Geometric_Shapes_Extended[1], buffer_Geometric_Shapes_Extended) - 1;
	if (scan(buffer_Geometric_Shapes_Extended, buffer_Geometric_Shapes_Extended + buffer_Geometric_Shapes_Extended_len, Geometric_Shapes_Extended) != Geometric_Shapes_Extended)
		printf("test 'Geometric_Shapes_Extended' failed\n");
	delete[] buffer_Geometric_Shapes_Extended;

	YYCTYPE *buffer_Supplemental_Arrows_C = new YYCTYPE[257];
	uint32_t buffer_Supplemental_Arrows_C_len = encode_utf32(chars_Supplemental_Arrows_C[0], chars_Supplemental_Arrows_C[1], buffer_Supplemental_Arrows_C) - 1;
	if (scan(buffer_Supplemental_Arrows_C, buffer_Supplemental_Arrows_C + buffer_Supplemental_Arrows_C_len, Supplemental_Arrows_C) != Supplemental_Arrows_C)
		printf("test 'Supplemental_Arrows_C' failed\n");
	delete[] buffer_Supplemental_Arrows_C;

	YYCTYPE *buffer_Supplemental_Symbols_and_Pictographs = new YYCTYPE[257];
	uint32_t buffer_Supplemental_Symbols_and_Pictographs_len = encode_utf32(chars_Supplemental_Symbols_and_Pictographs[0], chars_Supplemental_Symbols_and_Pictographs[1], buffer_Supplemental_Symbols_and_Pictographs) - 1;
	if (scan(buffer_Supplemental_Symbols_and_Pictographs, buffer_Supplemental_Symbols_and_Pictographs + buffer_Supplemental_Symbols_and_Pictographs_len, Supplemental_Symbols_and_Pictographs) != Supplemental_Symbols_and_Pictographs)
		printf("test 'Supplemental_Symbols_and_Pictographs' failed\n");
	delete[] buffer_Supplemental_Symbols_and_Pictographs;

	YYCTYPE *buffer_Chess_Symbols = new YYCTYPE[113];
	uint32_t buffer_Chess_Symbols_len = encode_utf32(chars_Chess_Symbols[0], chars_Chess_Symbols[1], buffer_Chess_Symbols) - 1;
	if (scan(buffer_Chess_Symbols, buffer_Chess_Symbols + buffer_Chess_Symbols_len, Chess_Symbols) != Chess_Symbols)
		printf("test 'Chess_Symbols' failed\n");
	delete[] buffer_Chess_Symbols;

	YYCTYPE *buffer_Symbols_and_Pictographs_Extended_A = new YYCTYPE[145];
	uint32_t buffer_Symbols_and_Pictographs_Extended_A_len = encode_utf32(chars_Symbols_and_Pictographs_Extended_A[0], chars_Symbols_and_Pictographs_Extended_A[1], buffer_Symbols_and_Pictographs_Extended_A) - 1;
	if (scan(buffer_Symbols_and_Pictographs_Extended_A, buffer_Symbols_and_Pictographs_Extended_A + buffer_Symbols_and_Pictographs_Extended_A_len, Symbols_and_Pictographs_Extended_A) != Symbols_and_Pictographs_Extended_A)
		printf("test 'Symbols_and_Pictographs_Extended_A' failed\n");
	delete[] buffer_Symbols_and_Pictographs_Extended_A;

	YYCTYPE *buffer_Symbols_for_Legacy_Computing = new YYCTYPE[257];
	uint32_t buffer_Symbols_for_Legacy_Computing_len = encode_utf32(chars_Symbols_for_Legacy_Computing[0], chars_Symbols_for_Legacy_Computing[1], buffer_Symbols_for_Legacy_Computing) - 1;
	if (scan(buffer_Symbols_for_Legacy_Computing, buffer_Symbols_for_Legacy_Computing + buffer_Symbols_for_Legacy_Computing_len, Symbols_for_Legacy_Computing) != Symbols_for_Legacy_Computing)
		printf("test 'Symbols_for_Legacy_Computing' failed\n");
	delete[] buffer_Symbols_for_Legacy_Computing;

	YYCTYPE *buffer_CJK_Unified_Ideographs_Extension_B = new YYCTYPE[42721];
	uint32_t buffer_CJK_Unified_Ideographs_Extension_B_len = encode_utf32(chars_CJK_Unified_Ideographs_Extension_B[0], chars_CJK_Unified_Ideographs_Extension_B[1], buffer_CJK_Unified_Ideographs_Extension_B) - 1;
	if (scan(buffer_CJK_Unified_Ideographs_Extension_B, buffer_CJK_Unified_Ideographs_Extension_B + buffer_CJK_Unified_Ideographs_Extension_B_len, CJK_Unified_Ideographs_Extension_B) != CJK_Unified_Ideographs_Extension_B)
		printf("test 'CJK_Unified_Ideographs_Extension_B' failed\n");
	delete[] buffer_CJK_Unified_Ideographs_Extension_B;

	YYCTYPE *buffer_CJK_Unified_Ideographs_Extension_C = new YYCTYPE[4161];
	uint32_t buffer_CJK_Unified_Ideographs_Extension_C_len = encode_utf32(chars_CJK_Unified_Ideographs_Extension_C[0], chars_CJK_Unified_Ideographs_Extension_C[1], buffer_CJK_Unified_Ideographs_Extension_C) - 1;
	if (scan(buffer_CJK_Unified_Ideographs_Extension_C, buffer_CJK_Unified_Ideographs_Extension_C + buffer_CJK_Unified_Ideographs_Extension_C_len, CJK_Unified_Ideographs_Extension_C) != CJK_Unified_Ideographs_Extension_C)
		printf("test 'CJK_Unified_Ideographs_Extension_C' failed\n");
	delete[] buffer_CJK_Unified_Ideographs_Extension_C;

	YYCTYPE *buffer_CJK_Unified_Ideographs_Extension_D = new YYCTYPE[225];
	uint32_t buffer_CJK_Unified_Ideographs_Extension_D_len = encode_utf32(chars_CJK_Unified_Ideographs_Extension_D[0], chars_CJK_Unified_Ideographs_Extension_D[1], buffer_CJK_Unified_Ideographs_Extension_D) - 1;
	if (scan(buffer_CJK_Unified_Ideographs_Extension_D, buffer_CJK_Unified_Ideographs_Extension_D + buffer_CJK_Unified_Ideographs_Extension_D_len, CJK_Unified_Ideographs_Extension_D) != CJK_Unified_Ideographs_Extension_D)
		printf("test 'CJK_Unified_Ideographs_Extension_D' failed\n");
	delete[] buffer_CJK_Unified_Ideographs_Extension_D;

	YYCTYPE *buffer_CJK_Unified_Ideographs_Extension_E = new YYCTYPE[5777];
	uint32_t buffer_CJK_Unified_Ideographs_Extension_E_len = encode_utf32(chars_CJK_Unified_Ideographs_Extension_E[0], chars_CJK_Unified_Ideographs_Extension_E[1], buffer_CJK_Unified_Ideographs_Extension_E) - 1;
	if (scan(buffer_CJK_Unified_Ideographs_Extension_E, buffer_CJK_Unified_Ideographs_Extension_E + buffer_CJK_Unified_Ideographs_Extension_E_len, CJK_Unified_Ideographs_Extension_E) != CJK_Unified_Ideographs_Extension_E)
		printf("test 'CJK_Unified_Ideographs_Extension_E' failed\n");
	delete[] buffer_CJK_Unified_Ideographs_Extension_E;

	YYCTYPE *buffer_CJK_Unified_Ideographs_Extension_F = new YYCTYPE[7489];
	uint32_t buffer_CJK_Unified_Ideographs_Extension_F_len = encode_utf32(chars_CJK_Unified_Ideographs_Extension_F[0], chars_CJK_Unified_Ideographs_Extension_F[1], buffer_CJK_Unified_Ideographs_Extension_F) - 1;
	if (scan(buffer_CJK_Unified_Ideographs_Extension_F, buffer_CJK_Unified_Ideographs_Extension_F + buffer_CJK_Unified_Ideographs_Extension_F_len, CJK_Unified_Ideographs_Extension_F) != CJK_Unified_Ideographs_Extension_F)
		printf("test 'CJK_Unified_Ideographs_Extension_F' failed\n");
	delete[] buffer_CJK_Unified_Ideographs_Extension_F;

	YYCTYPE *buffer_CJK_Unified_Ideographs_Extension_I = new YYCTYPE[625];
	uint32_t buffer_CJK_Unified_Ideographs_Extension_I_len = encode_utf32(chars_CJK_Unified_Ideographs_Extension_I[0], chars_CJK_Unified_Ideographs_Extension_I[1], buffer_CJK_Unified_Ideographs_Extension_I) - 1;
	if (scan(buffer_CJK_Unified_Ideographs_Extension_I, buffer_CJK_Unified_Ideographs_Extension_I + buffer_CJK_Unified_Ideographs_Extension_I_len, CJK_Unified_Ideographs_Extension_I) != CJK_Unified_Ideographs_Extension_I)
		printf("test 'CJK_Unified_Ideographs_Extension_I' failed\n");
	delete[] buffer_CJK_Unified_Ideographs_Extension_I;

	YYCTYPE *buffer_CJK_Compatibility_Ideographs_Supplement = new YYCTYPE[545];
	uint32_t buffer_CJK_Compatibility_Ideographs_Supplement_len = encode_utf32(chars_CJK_Compatibility_Ideographs_Supplement[0], chars_CJK_Compatibility_Ideographs_Supplement[1], buffer_CJK_Compatibility_Ideographs_Supplement) - 1;
	if (scan(buffer_CJK_Compatibility_Ideographs_Supplement, buffer_CJK_Compatibility_Ideographs_Supplement + buffer_CJK_Compatibility_Ideographs_Supplement_len, CJK_Compatibility_Ideographs_Supplement) != CJK_Compatibility_Ideographs_Supplement)
		printf("test 'CJK_Compatibility_Ideographs_Supplement' failed\n");
	delete[] buffer_CJK_Compatibility_Ideographs_Supplement;

	YYCTYPE *buffer_CJK_Unified_Ideographs_Extension_G = new YYCTYPE[4945];
	uint32_t buffer_CJK_Unified_Ideographs_Extension_G_len = encode_utf32(chars_CJK_Unified_Ideographs_Extension_G[0], chars_CJK_Unified_Ideographs_Extension_G[1], buffer_CJK_Unified_Ideographs_Extension_G) - 1;
	if (scan(buffer_CJK_Unified_Ideographs_Extension_G, buffer_CJK_Unified_Ideographs_Extension_G + buffer_CJK_Unified_Ideographs_Extension_G_len, CJK_Unified_Ideographs_Extension_G) != CJK_Unified_Ideographs_Extension_G)
		printf("test 'CJK_Unified_Ideographs_Extension_G' failed\n");
	delete[] buffer_CJK_Unified_Ideographs_Extension_G;

	YYCTYPE *buffer_CJK_Unified_Ideographs_Extension_H = new YYCTYPE[4193];
	uint32_t buffer_CJK_Unified_Ideographs_Extension_H_len = encode_utf32(chars_CJK_Unified_Ideographs_Extension_H[0], chars_CJK_Unified_Ideographs_Extension_H[1], buffer_CJK_Unified_Ideographs_Extension_H) - 1;
	if (scan(buffer_CJK_Unified_Ideographs_Extension_H, buffer_CJK_Unified_Ideographs_Extension_H + buffer_CJK_Unified_Ideographs_Extension_H_len, CJK_Unified_Ideographs_Extension_H) != CJK_Unified_Ideographs_Extension_H)
		printf("test 'CJK_Unified_Ideographs_Extension_H' failed\n");
	delete[] buffer_CJK_Unified_Ideographs_Extension_H;

	YYCTYPE *buffer_Tags = new YYCTYPE[129];
	uint32_t buffer_Tags_len = encode_utf32(chars_Tags[0], chars_Tags[1], buffer_Tags) - 1;
	if (scan(buffer_Tags, buffer_Tags + buffer_Tags_len, Tags) != Tags)
		printf("test 'Tags' failed\n");
	delete[] buffer_Tags;

	YYCTYPE *buffer_Variation_Selectors_Supplement = new YYCTYPE[241];
	uint32_t buffer_Variation_Selectors_Supplement_len = encode_utf32(chars_Variation_Selectors_Supplement[0], chars_Variation_Selectors_Supplement[1], buffer_Variation_Selectors_Supplement) - 1;
	if (scan(buffer_Variation_Selectors_Supplement, buffer_Variation_Selectors_Supplement + buffer_Variation_Selectors_Supplement_len, Variation_Selectors_Supplement) != Variation_Selectors_Supplement)
		printf("test 'Variation_Selectors_Supplement' failed\n");
	delete[] buffer_Variation_Selectors_Supplement;

	YYCTYPE *buffer_Supplementary_Private_Use_Area_A = new YYCTYPE[65537];
	uint32_t buffer_Supplementary_Private_Use_Area_A_len = encode_utf32(chars_Supplementary_Private_Use_Area_A[0], chars_Supplementary_Private_Use_Area_A[1], buffer_Supplementary_Private_Use_Area_A) - 1;
	if (scan(buffer_Supplementary_Private_Use_Area_A, buffer_Supplementary_Private_Use_Area_A + buffer_Supplementary_Private_Use_Area_A_len, Supplementary_Private_Use_Area_A) != Supplementary_Private_Use_Area_A)
		printf("test 'Supplementary_Private_Use_Area_A' failed\n");
	delete[] buffer_Supplementary_Private_Use_Area_A;

	YYCTYPE *buffer_Supplementary_Private_Use_Area_B = new YYCTYPE[65537];
	uint32_t buffer_Supplementary_Private_Use_Area_B_len = encode_utf32(chars_Supplementary_Private_Use_Area_B[0], chars_Supplementary_Private_Use_Area_B[1], buffer_Supplementary_Private_Use_Area_B) - 1;
	if (scan(buffer_Supplementary_Private_Use_Area_B, buffer_Supplementary_Private_Use_Area_B + buffer_Supplementary_Private_Use_Area_B_len, Supplementary_Private_Use_Area_B) != Supplementary_Private_Use_Area_B)
		printf("test 'Supplementary_Private_Use_Area_B' failed\n");
	delete[] buffer_Supplementary_Private_Use_Area_B;

	return 0;
}

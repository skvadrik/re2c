#define NULL            ((char*) 0)
#define YYCTYPE         unsigned char
#define YYCURSOR        *p
#define YYLIMIT         *p
#define YYMARKER        q
#define YYFILL(n)

/* backtrack to return other, semi-overlapped tokens; e.g.
   allow "abcdef" to return both "abc" and "cde" as tokens */
#define RET(x)          { YYCURSOR = YYMARKER; return (x); }
char *Mail_SpamAssassin_CompiledRegexps_body_0_scan1(unsigned char **p){
unsigned char *q;
/*!re2c
	" 1-2 stunden zeit t"            {RET("__ZMIde_JOBTIME5");}
	" @ only4private.net"            {RET("__ZMIde_PRIVGEIL10");}
	" @ privat2geil.com"            {RET("__ZMIde_PRIVGEIL10");}
	" absolut flat! keine extrakosten"            {RET("DIET_1 ZMIde_ABSFLAT");}
	" and am unable to read your message"            {RET("__BOUNCE_OOO_2");}
	" contains the virus"            {RET("__VBOUNCE_VALERT");}
	" credit"            {RET("BAD_CREDIT");}
	" debt"            {RET("BAD_CREDIT");}
	" diese angaben beruhen ausschliesslich auf erfolgreiche char"            {RET("__ZMIde_STOCK15");}
	" digit level in "            {RET("__DOS_TAKING_HOME");}
	" einsehen und dort auch einen termin vereinbaren"            {RET("ZMIde_INVEST4");}
	" euro die woche sind m"            {RET("__ZMIde_JOBEARN8");}
	" euro/stange incl. versand"            {RET("ZMIde_CHEAPSMOKE1");}
	" extended relative"            {RET("__FRAUD_SNT");}
	" gnassingbe eyadema"            {RET("__ZMIde_DEADPERSON1");}
	" grand promotions"            {RET("__KAM_LOTTO5");}
	" hat letzte nacht "            {RET("__ZMIde_ONLGAME6");}
	" heraus zu suchen um mit ihr in kontakt zu treten"            {RET("ZMIde_GIRLSRCH2");}
	" home loan"            {RET("FB_HOMELOAN __HOMELOANFVGT");}
	" i'll never see your message"            {RET("__BOUNCE_NEVER_SEE");}
	" ich ihre zuversicht in dieser verhandlung bitten"            {RET("ZMIde_NIGERIA");}
	" manfred becker"            {RET("__ZMIde_DEADPERSON1");}
	" please view this message in a different"            {RET("__RUDE_HTML_2");}
	" price"            {RET("LOW_PRICE");}
	" rating doesn"            {RET("YOUR_CRD_RATING");}
	" remove \""            {RET("__DRUG_RA_PRICE2");}
	" scoring doesn"            {RET("YOUR_CRD_RATING");}
	" sie dadurch eine chance bekommen, einen treffer in unserer"            {RET("__ZMIfish_POSTBANK2");}
	" so viel erfolg"            {RET("__ZMIde_REPLICA6_1");}
	" stunden pro woche und verdienen zwischen "            {RET("__ZMIde_JOBEARN7");}
	" sucht nach den hoch organisierten und verantwortlichen leut"            {RET("ZMIde_SAFESALE1");}
	" thousand"            {RET("__FRAUD_LTX");}
	" your girlfriend"            {RET("FB_UNLOCK_YOUR_G __DOS_BODY_FRI");}
	"!! der erste und einzige online-pokerraum auf deutsch!!"            {RET("FB_GET_MEDS FREE_QUOTE_INSTANT ZMIde_POKER1 ZMIde_POKER4");}
	"!! wir schenken ihnen 100 euro startguthaben kostenlos!!"            {RET("ZMIde_POKER3");}
	"* internet, e-mail, grundkenntnisse der hauptzahlungssysteme"            {RET("__ZMIde_JOBKNOW1");}
	", um das geld von unseren konten waschen zu k"            {RET("ZMIfish_NETBANKING_5");}
	"-- "            {RET("FB_LETTERS_21B");}
	"-optimal-erweitern-team"            {RET("ZMIde_OUTLOOKGOOD3");}
	".ob"            {RET("__DOS_BODY_TICKER");}
	".pk"            {RET("__DOS_BODY_TICKER");}
	"00423 663 902 344"            {RET("ZMIde_NOSCHUFAFAX");}
	"0522 4705"            {RET("ZMIde_HGS_TELFAX");}
	"100% anonym - jetzt gratis!"            {RET("ZMIde_ANONYMOUS");}
	"100% guaranteed"            {RET("GUARANTEED_100_PERCENT");}
	"100% legal filme saugen"            {RET("ZMIde_LEGALFILM");}
	"100% safe"            {RET("__FRAUD_IOU");}
	"25 schweizer juwelen - automatische aufladung"            {RET("ZMIde_REPLICA5 __ZMIde_SPAMDBCTR2_3");}
	"3-5 freien stunden pro woche"            {RET("__ZMIde_JOBTIME3");}
	"> tvqqaamaaaaeaaaa"            {RET("__VBOUNCE_QUOTED_EXE");}
	"$b"            {RET("__ISO_2022_JP_DELIM");}
	"a amazon o directamente v"            {RET("__ZMIde_BIOMETES3");}
	"a honest foreigner"            {RET("__FRAUD_XJR");}
	"a potentially executable attachment "            {RET("__VBOUNCE_EXIM");}
	"ab sofort suchen wir mitarbeiter aus der ganzen welt"            {RET("ZMIde_JOBSEARCH17");}
	"aber auch meine meinung:"            {RET("__ZMIRASSISMUSBD_2");}
	"aber bei den geilen titten ist es doch klar, wo der blick hi"            {RET("ZMIde_PORNTALK1");}
	"aber das ist noch nicht genug – einige belassen es se"            {RET("__ZMIde_STREET6");}
	"aber die kleine trotzdem mal in action sehen kannst du ja on"            {RET("ZMIde_MILFHUNTER6");}
	"abnormal geil, extrem verdorben und das auch noch in der bes"            {RET("ZMIde_SEXVIDEO3");}
	"absolut legal. kein kapitaleinsatz - kein risiko. super prov"            {RET("ZMIde_CHEAPSMOKE2 __DOS_BODY_SAT");}
	"account "            {RET("TVD_PH_BODY_ACCOUNTS_PRE TVD_PH_REC TVD_PH_SEC");}
	"accounts "            {RET("TVD_PH_BODY_ACCOUNTS_PRE");}
	"achtung : extremes hardcore material"            {RET("ZMIde_SEXUALEXPL2");}
	"achtung es ist keine geldwaesche mail!"            {RET("ZMIde_FUNTEXT2");}
	"achtung es ist keine spam mail!"            {RET("ZMIde_FUNTEXT1");}
	"act now"            {RET("ACT_NOW_CAPS");}
	"act of 193"            {RET("TVD_ACT_193");}
	"act of nineteen thirty"            {RET("TVD_ACT_193");}
	"add inches"            {RET("BODY_ENHANCEMENT BODY_ENHANCEMENT2 DIET_1 FB_ADD_INCHES");}
	"address direclty at"            {RET("__DOS_EMAIL_DIRECTLY");}
	"address directly at"            {RET("__DOS_EMAIL_DIRECTLY");}
	"adipex"            {RET("FB_GVR");}
	"affidavit"            {RET("__FRAUD_ULK");}
	"affordable "            {RET("PRICES_ARE_AFFORDABLE");}
	"all night!"            {RET("__FB_P_ALLNIGHT");}
	"alle e-mail-adressen wurden durch ein computerstimmzettelsys"            {RET("__ZMIde_LOTTERY4");}
	"alle postbankkonten, die nicht innerhalb einer woche authent"            {RET("__ZMIfish_POSTBANK8");}
	"alprazolam"            {RET("__DRUGS_ANXIETY2");}
	"als entgelt garantieren wir ihnen am anfang 10% von den tran"            {RET("__ZMIde_JOBEARN6");}
	"als versand-apotheke"            {RET("__ZMIde_DRUGS2");}
	"alternate "            {RET("__FRAUD_AON");}
	"alternative "            {RET("__FRAUD_AON");}
	"amalgamated bank"            {RET("__FRAUD_BEP");}
	"an honest foreigner"            {RET("__FRAUD_XJR");}
	"analbilder gratis anschauen:"            {RET("__ZMIde_PORNCRACK5");}
	"anbei erhalten sie wie gewohnt den aktuellen performaxx-info"            {RET("ZMIde_PXXNEWS __DOS_BODY_TUE");}
	"angagement;"            {RET("__ZMIde_JOBHAVE10");}
	"angebotene datenbanken beinhalten hunderttausende von e-mail"            {RET("__ZMIde_SENDLOTSASPAM3");}
	"antivirus system report"            {RET("__VBOUNCE_AVREPORT0");}
	"apex bank"            {RET("__FRAUD_BEP");}
	"approval manager"            {RET("__APPROVALFVGT __APPROVAL_MGR");}
	"approval"            {RET("__APPROVALFVGT");}
	"approved "            {RET("TVD_APPROVED TVD_APP_LOAN");}
	"approved"            {RET("TVD_APPROVED");}
	"arbeiten sie als finanzmanager, auch wenn sie keine erfahrun"            {RET("__ZMIde_OPENJOB4");}
	"armutswanderung aus osteuropa"            {RET("__ZMIRASSISMUSBD_15");}
	"as a foreigner"            {RET("__FRAUD_XJR");}
	"as the beneficiary"            {RET("__FRAUD_PVN");}
	"asasinated"            {RET("__FRAUD_PTS");}
	"asasination"            {RET("__FRAUD_PTS");}
	"asassinated"            {RET("__FRAUD_PTS");}
	"asassination"            {RET("__FRAUD_PTS");}
	"assasinated"            {RET("__FRAUD_PTS");}
	"assasination"            {RET("__FRAUD_PTS");}
	"assassinated"            {RET("__FRAUD_PTS");}
	"assassination"            {RET("__FRAUD_PTS");}
	"assistance"            {RET("URG_BIZ");}
	"attached to ticket number"            {RET("__FRAUD_BGP __KAM_LOTTO2");}
	"aus sicherheit grund muessen sie ihr antwort zu diesem email"            {RET("ZMIde_SECURITY");}
	"ausgefallene kontakte"            {RET("__ZMIde_PORNSITE3");}
	"ausgehungerten frauen"            {RET("__ZMIde_PPTREFF7a");}
	"auslaenderanteil in den schweizer gefaengnissen"            {RET("__ZMIRASSISMUSBD_7 __ZMIde_SPAMDBCTR2_3");}
	"auslaenderkriminalitaet"            {RET("__ZMIRASSISMUSBD_10");}
	"auslaendischer 'gesundheitstouristen'"            {RET("__DOS_BODY_SUN __ZMIRASSISMUSBD_9");}
	"ausweitung unseres marketings und die gewinnung neuer kunden"            {RET("ZMIde_JOBSEARCH19");}
	"autoleasing ohne schufa!"            {RET("ZMIde_NOSCHUFA ZMIde_NOSCHUFACC");}
	"avoid double claiming"            {RET("__DBLCLAIM __KAM_LOTTO3");}
	"award notification"            {RET("TVD_PH_BODY_ACCOUNTS_PRE __FRAUD_FVU");}
	"bachelor"            {RET("__BACHELORS");}
	"bank of nigeria"            {RET("__FRAUD_BEP __FRAUD_NEB");}
	"banking laws"            {RET("BANKING_LAWS");}
	"bankkonto f"            {RET("__ZMIde_JOBHAVE7");}
	"bankverbindung, um zahlungen entgegen zu nehmen"            {RET("__ZMIde_JOBHAVE18");}
	"baron bernado equity club"            {RET("ZMIde_INVEST3");}
	"be we can meet"            {RET("__DOS_MEET_EACH_OTHER");}
	"beherrschung ms office (excel, word,) und internet"            {RET("__ZMIde_JOBKNOW9");}
	"bei der standard bank nigeria plc, johannesburg"            {RET("__ZMIde_BANKAFRICA1");}
	"bei der standard bank nigeria plc, lagos"            {RET("__ZMIde_BANKAFRICA1");}
	"bei der standard bank south-africa plc, johannesburg"            {RET("__DOS_BODY_FRI __ZMIde_BANKAFRICA1");}
	"bei der standard bank south-africa plc, lagos"            {RET("__DOS_BODY_FRI __ZMIde_BANKAFRICA1");}
	"bei der union bank nigeria plc, johannesburg"            {RET("__ZMIde_BANKAFRICA1");}
	"bei der union bank nigeria plc, lagos"            {RET("__ZMIde_BANKAFRICA1");}
	"bei der union bank south-africa plc, johannesburg"            {RET("__DOS_BODY_FRI __ZMIde_BANKAFRICA1");}
	"bei der union bank south-africa plc, lagos"            {RET("__DOS_BODY_FRI __ZMIde_BANKAFRICA1");}
	"bei unseren livesexshows bist du der regisseur"            {RET("__WORD_SEX __ZMIde_LIVESEX1");}
	"ber 20n technologien erarbeitet"            {RET("ZMIde_20NTECH");}
	"ber – deshalb schaffen wir heute abhilfe"            {RET("__ZMIde_STREET2");}
	"ber amazon oder direkt beim lit verlag bestellen"            {RET("__ZMIde_BIOMETDE3");}
	"ber den versuch des unbefugten zugangs informiert"            {RET("__ZMIfish_POSTBANK13");}
	"ber die banktransfer und andere "            {RET("__ZMIde_JOBKNOW2");}
	"ber drei dutzend gut funktionierende strategien, um die zahl"            {RET("__ZMIde_SALE5");}
	"ber mehr als 4 millionen in deutschland angesiedelte unterne"            {RET("MILLION_USD NA_DOLLARS __ZMIde_3LANDECK1 __ZMIde_BROKER7");}
	"berhaupt hier zu sitzen und diesen text zu schreiben"            {RET("__ZMIde_SALE12");}
	"berschreitend in deutsch-griechischen rechtsfragen aktiv"            {RET("ZMIde_LAWGRDE2");}
	"bersichtlichen gebraucht handy basaar ist die produktsuche e"            {RET("ZMIde_HANDYBASAR2");}
	"berufsbegleitend im gewerblichen auf- und ausbau eines berat"            {RET("ZMIde_JOBSEARCH24");}
	"berweisungen von unseren kunden vornehmen m"            {RET("__DOS_BODY_SUN __ZMIde_JOBTRANS3");}
	"bestellen sie jetzt 250 professionelle visitenkarten im farb"            {RET("ZMIde_VCARDFREE");}
	"bestellen sie sa2 jetzt"            {RET("ZMIde_SA2MOBIL5");}
	"besuche diese webseite "            {RET("__ZMIde_ONLGAME2");}
	"bevatte bijlage besmet welke besmet was met een virus"            {RET("__VBOUNCE_DUTCH");}
	"bigger"            {RET("BODY_ENHANCEMENT BODY_ENHANCEMENT2");}
	"bitte auch lesen: hinweise zum folgenden"            {RET("__ZMIde_STOCK1");}
	"bliche sex, sondern knallharte fickspiele ohne jegliche tabu"            {RET("ZMIde_SEXVIDEO2 __WORD_SEX");}
	"blocked by mailsweeper"            {RET("__VBOUNCE_MAILSWEEP2");}
	"bondage"            {RET("__ZMIde_PPTREFF6b");}
	"bontril"            {RET("__DRUGS_DIET3");}
	"bonus: jetzt bestellen und sie erhalten 140 passende adressa"            {RET("ZMIde_VCARDFREE2");}
	"brand name"            {RET("__FB_BRAND_NAME");}
	"breast"            {RET("BODY_ENHANCEMENT BODY_ENHANCEMENT2");}
	"breitling"            {RET("__ZMIde_ROLEX2");}
	"britischer"            {RET("__ZMIde_SPAMDBCTR2_4");}
	"brother of the late"            {RET("__FRAUD_ZFJ");}
	"bsc"            {RET("__FB_BCs");}
	"burn"            {RET("DIET_1");}
	"business partner"            {RET("URG_BIZ __FRAUD_TDP");}
	"business"            {RET("URG_BIZ");}
	"c0mpany"            {RET("FB_C0MPANY");}
	"calis"            {RET("__DRUGS_ERECTILE4");}
	"campaign for: "            {RET("DOS_STOCK_CDYV_GENERIC");}
	"can last longer"            {RET("BODY_ENHANCEMENT BODY_ENHANCEMENT2 FB_CAN_LONGER");}
	"canadian dolla"            {RET("NA_DOLLARS");}
	"cartier"            {RET("__ZMIde_ROLEX5");}
	"cash prize of"            {RET("__CASHPRZ __KAM_LOTTO3");}
	"cash prize"            {RET("__KAM_LOTTO3");}
	"central bank of"            {RET("__FRAUD_BEP");}
	"cfri"            {RET("KAM_STOCKTIP14 __DOS_BODY_FRI");}
	"cher mit tausenden von seiten mit informationen die dich nic"            {RET("__ZMIde_SALE4");}
	"china world trade corporation"            {RET("KAM_STOCKTIP6");}
	"chst unsere firma und wir haben eine beschr"            {RET("ZMIde_JOBSEARCH2");}
	"chte ich sie informieren, dass das buch nachgedruckt wurde u"            {RET("__ZMIde_BIOMETDE2");}
	"chte man einfach zugreifen d"            {RET("ZMIde_PORNTALK2");}
	"chten betonen, dass keinerlei investitionen ihrerseits erfor"            {RET("ZMIde_JOBSEARCH3");}
	"chten sie extra geld durch teilzeitbesch"            {RET("DIET_1 __DRUG_RA_PRICE1 __ZMIde_JOBEARN2");}
	"chten sie mehr verdienen, und dabei von zu hause aus zu arbe"            {RET("__ZMIde_JOBEARN1");}
	"chten uns und unsere wirtschaftsrechtlich ausgerichtete anwa"            {RET("ZMIde_LAWGRDE1");}
	"chten wir einen auftrag mit ihnen legen, um eine relation de"            {RET("ZMIde_AUFTRAG2");}
	"chten wir uns bei ihnen bekannt machen"            {RET("__ZMIde_TRAVEL1");}
	"chtest die abende und wochenenden nicht mehr alleine verbrin"            {RET("ZMIde_DATING2");}
	"cialis"            {RET("DRUGS_SMEAR1 DRUG_ED_CAPS __DRUGS_ERECTILE_C");}
	"cilais"            {RET("__DRUGS_ERECTILE4");}
	"cilias"            {RET("__DRUGS_ERECTILE4");}
	"ck-garantie"            {RET("ZMIde_MONEYBACK");}
	"cken, erfurt, dresden, rostock, bremen, freiburg"            {RET("__DOS_BODY_STOCK __FB_S_STOCK __ZMIde_PRIVGEIL6");}
	"claim the money"            {RET("__DOS_BODY_MON __FRAUD_JYG __FRAUD_KJV __KAM_LOTTO3");}
	"claim this money"            {RET("__DOS_BODY_MON __FRAUD_JYG __FRAUD_KJV __KAM_LOTTO3");}
	"claim"            {RET("__KAM_LOTTO3");}
	"claims agent"            {RET("__KAM_LOTTO3 __KAM_LOTTO4");}
	"claims officer"            {RET("__KAM_LOTTO3 __KAM_LOTTO4");}
  [\000-\377]        { return NULL; }
*/
}

 	  	 

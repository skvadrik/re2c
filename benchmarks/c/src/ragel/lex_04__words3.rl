#include "ragel/base.h"

namespace ragel_lex_04__words3 {

const char *delim = "\n";

%%{
    machine lex_words;

    word = ("Aare River"
        | "Abakan River"
        | "Abitibi River"
        | "Abuna River"
        | "Achelous River"
        | "Acheron"
        | "Aconcagua River"
        | "Acre River"
        | "Adda River"
        | "Adelaide River"
        | "Adige River"
        | "Adour River"
        | "Afram River"
        | "Aguan River"
        | "Aguarico River"
        | "Agueda River"
        | "Agusan River"
        | "Ain River"
        | "Aksu River"
        | "Alabama River"
        | "Albany River"
        | "Albert Nile"
        | "Aldan River"
        | "Aliakmon River"
        | "Al-Kalb River"
        | "Allegheny River"
        | "Allier River"
        | "Alligator Rivers"
        | "Alpenrhein River"
        | "Alpheus River"
        | "Alster River"
        | "Amazon River"
        | "Amu Darya"
        | "Amur River"
        | "Androscoggin River"
        | "Angara River"
        | "Angerman River"
        | "Aniene River"
        | "Ankobra"
        | "Apa River"
        | "Apure River"
        | "Apurimac River"
        | "Aragon River"
        | "Araguaia River"
        | "Aras River"
        | "Arauca River"
        | "Arda River"
        | "Arges River"
        | "Argun River"
        | "Arinos River"
        | "Arkansas River"
        | "Arno River"
        | "Artibonite River"
        | "Arve River"
        | "Ashburton River"
        | "Assiniboine River"
        | "Atbara River"
        | "Atchafalaya River"
        | "Athabasca River"
        | "Atrato River"
        | "Attawapiskat River"
        | "Aube River"
        | "Awash River"
        | "Back River"
        | "Bafing River"
        | "Baghmati River"
        | "Bahr Al-Ghazal"
        | "Bahr Al-Jabal"
        | "Bahr Al-Zaraf"
        | "Bahr Al-Arab"
        | "Bakoye River"
        | "Balsas River"
        | "Banas River"
        | "Bandama River"
        | "Bani River"
        | "Barada River"
        | "Barron River"
        | "Battle River"
        | "Beas River"
        | "Bei River"
        | "Belait River"
        | "Belaya River"
        | "Belize River"
        | "Beni River"
        | "Benue River"
        | "Berbice River"
        | "Bermejo River"
        | "Besos River"
        | "Betwa River"
        | "Bhagirathi River"
        | "Bhima River"
        | "Bia River"
        | "Big Black River"
        | "Bighorn River"
        | "Big Sandy River"
        | "Big Sioux River"
        | "Big Wood River"
        | "Biobio River"
        | "Blackfoot River"
        | "Black River"
        | "Black River (Arkansas and Missouri)"
        | "Black River (Wisconsin)"
        | "Black Volta River"
        | "Black Warrior River"
        | "Blood River"
        | "Blue Nile River"
        | "Boeuf River"
        | "Boise River"
        | "Bomu River"
        | "Bonanza Creek"
        | "Bonny River"
        | "Bosna River"
        | "Boteti River"
        | "Boumbe II River"
        | "Bow River"
        | "Brahmani River"
        | "Brahmaputra River"
        | "Branco River"
        | "Brandywine Creek"
        | "Brazos River"
        | "Brisbane River"
        | "Broad River"
        | "Bug River"
        | "Buller River"
        | "Burdekin River"
        | "Burnett River"
        | "Byarezina River"
        | "Cagayan River"
        | "Caledon River"
        | "Campaspe River"
        | "Camu River"
        | "Canadian River"
        | "Caney Fork River"
        | "Caniapiscau River"
        | "Cannonball River"
        | "Cape Fear River"
        | "Capibaribe River"
        | "Ca River"
        | "Caroni River"
        | "Caroni River"
        | "Carson River"
        | "Casamance River"
        | "Casiquiare"
        | "Catatumbo River"
        | "Catawba River"
        | "Cauca River"
        | "Cauto River"
        | "Cavalla River"
        | "Cedar River"
        | "Ceyhan River"
        | "Chagres River"
        | "Chambal River"
        | "Chambeshi River"
        | "Chaobai River"
        | "Chao Phraya River"
        | "Charente River"
        | "Chari River"
        | "Charles River"
        | "Chattahoochee River"
        | "Chelif River"
        | "Chenab River"
        | "Cheoah River"
        | "Cher River"
        | "Cheyenne River"
        | "Chiana River"
        | "Chicago River"
        | "Chindwin River"
        | "Chixoy River"
        | "Choctawhatchee River"
        | "Ch'ongch'on River"
        | "Chubut River"
        | "Chulym River"
        | "Chuna River"
        | "Churchill River"
        | "Chu River"
        | "Cimarron River"
        | "Clarence River"
        | "Clarion River"
        | "Clark Fork"
        | "Cle Elum River"
        | "Clinch River"
        | "Clitunno River"
        | "Clutha River"
        | "Coco River"
        | "Coldwater River"
        | "Colorado River"
        | "Columbia River"
        | "Combahee River"
        | "Conchos River"
        | "Congaree River"
        | "Congo River"
        | "Connecticut River"
        | "Cooper Creek"
        | "Coosa River"
        | "Coppermine River"
        | "Courantyne River"
        | "Cross River"
        | "Cuanza River"
        | "Cuiaba River"
        | "Cumberland River"
        | "Cunene River"
        | "Current River"
        | "Cuyahoga River"
        | "Cuyuni River"
        | "Dades River"
        | "Dagua River"
        | "Dal River"
        | "Daly River"
        | "Damodar River"
        | "Dan River"
        | "Danube River"
        | "Darling River"
        | "Dawson River"
        | "De Grey River"
        | "Delaware River"
        | "Demerara River"
        | "Deseado River"
        | "Des Moines River"
        | "Desna River"
        | "Des Plaines River"
        | "Detroit River"
        | "Dhaleswari River"
        | "Diamantina River"
        | "Digul River"
        | "Dimbovita River"
        | "Dinder River"
        | "Dix River"
        | "Diyala River"
        | "Diyala River"
        | "Dja River"
        | "Djoua River"
        | "Dnieper River"
        | "Dniester River"
        | "Doce River"
        | "Dolores River"
        | "Donets River"
        | "Dong Nai River"
        | "Don River"
        | "Dordogne River"
        | "Doubs River"
        | "Douro River"
        | "Draa River"
        | "Drams River"
        | "Drava River"
        | "Drina River"
        | "Dunajec River"
        | "Durance"
        | "Dwangwa River"
        | "Eastmain River"
        | "Ebro River"
        | "Eider River"
        | "Elbe River"
        | "Elk River (Kansas)"
        | "Elk River (Tennessee and Alabama)"
        | "Ems River"
        | "Escravos River"
        | "Essequibo River"
        | "Euphrates River"
        | "Eure River"
        | "Evrotas River"
        | "Faleme River"
        | "Fall River"
        | "Farah River"
        | "Farmington River"
        | "Faro River"
        | "Fen River"
        | "Finke River"
        | "Fish River"
        | "Fitzroy River (Queensland)"
        | "Fitzroy River (Western Australia)"
        | "Flathead River"
        | "Flinders River"
        | "Flumendosa River"
        | "Fly River"
        | "Forcados River"
        | "Forth River"
        | "Fraser River"
        | "French Broad River"
        | "Fuchun River"
        | "Fuerte River"
        | "Fulda River"
        | "Gallatin River"
        | "Gal Oya"
        | "Gambia River"
        | "Gandak River"
        | "Ganges River"
        | "Gan River"
        | "Garonne River"
        | "Gasconade River"
        | "Gascoyne River"
        | "Gash River"
        | "Gatineau River"
        | "Genesee River"
        | "George River"
        | "Ghaggar River"
        | "Ghaghara River"
        | "Gila River"
        | "Glenelg River"
        | "Glomma"
        | "Goascoran River"
        | "Gomati River"
        | "Gongola River"
        | "Gordon River"
        | "Goulburn River"
        | "Grande River"
        | "Grand River (Iowa and Missouri)"
        | "Grand River (South Dakota)"
        | "Great Fish River"
        | "Great Kei River"
        | "Great Miami River"
        | "Great Scarcies River"
        | "Great Stour"
        | "Green River (Kentucky)"
        | "Green River (Wyoming)"
        | "Grijalva River"
        | "Guadalquivir River"
        | "Guadiana River"
        | "Guainia River"
        | "Guapore River"
        | "Guaviare River"
        | "Guayas River"
        | "Gui River"
        | "Gumal River"
        | "Gundlakamma River"
        | "Han River (Fujian and Guangdong provinces)"
        | "Han River (Hubei and Shaanxi provinces)"
        | "Harirud"
        | "Havel River"
        | "Hawkesbury River"
        | "Hayes River"
        | "Heart River"
        | "Hei River"
        | "Helmand River"
        | "Henrys Fork"
        | "Herbert River"
        | "Hernad River"
        | "Hiwassee River"
        | "Holston River"
        | "Hongshui River"
        | "Housatonic River"
        | "Huai River"
        | "Huallaga River"
        | "Huang He (Yellow River)"
        | "Hudson River"
        | "Hugli River"
        | "Humber River"
        | "Humboldt River"
        | "Hunter River"
        | "Hunyani River"
        | "Huon River"
        | "Hutt River"
        | "Ialomita River"
        | "Ibar River"
        | "Iguacu River"
        | "IJssel River"
        | "Ili River"
        | "Ili (Yili) River"
        | "Illinois River"
        | "Indigirka River"
        | "Indre River"
        | "Indus River"
        | "Innoko River"
        | "Inn River"
        | "Iowa River"
        | "Irrawaddy River"
        | "Irtysh River"
        | "Isar River"
        | "Isere River"
        | "Ishikari River"
        | "Ishim River"
        | "Iskur River"
        | "Itapicuru River"
        | "Jacui River"
        | "Jaguaribe River"
        | "James River (North Dakota and South Dakota)"
        | "James River (Virginia)"
        | "Japura River"
        | "Jari River"
        | "Javari River"
        | "Jefferson River"
        | "Jequitinhonha River"
        | "Jhelum River"
        | "Jialing River"
        | "Jing River"
        | "Jinsha River"
        | "Jiulong River"
        | "Jiu River"
        | "Jizera River"
        | "Jokulsa a Fjollum"
        | "Jordan River"
        | "Jubba River"
        | "Jucar River"
        | "Jurua River"
        | "Juruena River"
        | "Kabompo River"
        | "Kabul River"
        | "Kaduna River"
        | "Kafue River"
        | "Kagera River"
        | "Kamchatka River"
        | "Kaministiquia River"
        | "Kanawha River"
        | "Kankakee River"
        | "Kansas River"
        | "Kapuas River"
        | "Karnaphuli River"
        | "Karun River"
        | "Kasai River"
        | "Kaskaskia River"
        | "Katsina Ala River"
        | "Kaveri River"
        | "Kazan River"
        | "Kemi River"
        | "Kennebec River"
        | "Kentucky River"
        | "Khabur River"
        | "Khwae Noi River"
        | "Kiamichi River"
        | "Kinabatangan River"
        | "Kissimmee River"
        | "Kizil River"
        | "Klamath River"
        | "Kokemaen River"
        | "Kollidam River"
        | "Kolyma River"
        | "Komadugu Yobe River"
        | "Komati River"
        | "Komoe River"
        | "Konda River"
        | "Kootenay River"
        | "Kosi River"
        | "Kotto River"
        | "Kouilou River"
        | "Koulountou River"
        | "Koyukuk River"
        | "Kuban River"
        | "Kuiseb River"
        | "Kum River"
        | "Kura River"
        | "Kwando River"
        | "Lachlan River"
        | "Lagen (south-central Norway)"
        | "Lagen (southeastern Norway)"
        | "La Grande River"
        | "Lahn River"
        | "Laja River"
        | "Laramie River"
        | "Lempa River"
        | "Lena River"
        | "Lerma River"
        | "Lesse River"
        | "Lewes River"
        | "Liao River"
        | "Liard River"
        | "Licking River"
        | "Limpopo River"
        | "Linth River"
        | "Lippe River"
        | "Liri River"
        | "Litani River"
        | "Little Missouri River (Arkansas)"
        | "Little Missouri River (northwestern United States)"
        | "Little Tennessee River"
        | "Ljusnan River"
        | "Llobregat River"
        | "Loa River"
        | "Loddon River"
        | "Logone River"
        | "Loire River"
        | "Loir River"
        | "Lomami River"
        | "Lot River"
        | "Loup River"
        | "Lualaba River"
        | "Luangwa River"
        | "Luan River"
        | "Luapula River"
        | "Lufira River"
        | "Lukuga River"
        | "Lule River"
        | "Lulonga River"
        | "Lundi River"
        | "Lungwebungu River"
        | "Luni River"
        | "Luvua River"
        | "Luznice River"
        | "Mackenzie River"
        | "Madeira River"
        | "Madhumati River"
        | "Madison River"
        | "Madre de Dios River"
        | "Mafou River"
        | "Magdalena River"
        | "Mahakam River"
        | "Mahanadi River"
        | "Mahananda River"
        | "Mahaweli Ganga"
        | "Mahi River"
        | "Maine River"
        | "Main River"
        | "Maitengwe River"
        | "Malagarasi River"
        | "Malheur River"
        | "Mali River"
        | "Mamberamo River"
        | "Mamore River"
        | "Manawatu River"
        | "Manicouagan River"
        | "Mano River"
        | "Maputo River"
        | "Marais des Cygnes River"
        | "Maranon River"
        | "Marias River"
        | "Marico River"
        | "Maritsa River"
        | "Ma River"
        | "Markham River"
        | "Marne River"
        | "Maroni River"
        | "Mataura River"
        | "Maumee River"
        | "Mayenne River"
        | "Mazaruni River"
        | "McArthur River"
        | "Medicine Creek"
        | "Medicine Lodge River"
        | "Meghna River"
        | "Mekong River"
        | "Menderes River"
        | "Meramec River"
        | "Merrimack River"
        | "Meta River"
        | "Metauro River"
        | "Meuse River"
        | "Milk River"
        | "Milo River"
        | "Mindanao River"
        | "Minnesota River"
        | "Min River"
        | "Mississippi River"
        | "Missouri River"
        | "Mitchell River"
        | "Mobile River"
        | "Mohaka River"
        | "Mohawk River"
        | "Mokau River"
        | "Molopo River"
        | "Mondego River"
        | "Monongahela River"
        | "Mono River"
        | "Moose River"
        | "Morava River"
        | "Moreau River"
        | "Morghab River"
        | "Moscow River"
        | "Moselle River"
        | "Motagua River"
        | "Moulouya River"
        | "Mulde River"
        | "Mulligan River"
        | "Mun River"
        | "Murat River"
        | "Murchison River"
        | "Mures River"
        | "Mures River"
        | "Mu River"
        | "Murray River"
        | "Murrumbidgee River"
        | "Musi River"
        | "Muskingum River"
        | "Musselshell River"
        | "Naktong River"
        | "Nan River"
        | "Nantahala River"
        | "Napo River"
        | "Nara Canal"
        | "Narew River"
        | "Narmada River"
        | "Naryn River"
        | "Nazas River"
        | "Nechako River"
        | "Neckar River"
        | "Negro River"
        | "Neisse River"
        | "Nelson River"
        | "Neman River"
        | "Nen River"
        | "Neosho River"
        | "Neretva River"
        | "Nestos River"
        | "Neuse River"
        | "Neva River"
        | "New River"
        | "Niagara River"
        | "Niari River"
        | "Niger River"
        | "Nile River"
        | "Niobrara River"
        | "Nizhnyaya Tunguska River"
        | "Nmai Hka"
        | "Nolichucky River"
        | "Norman River"
        | "North Canadian River"
        | "Northern Dvina River"
        | "North Platte River"
        | "Nossob River"
        | "Nottaway River"
        | "Nottely River"
        | "Nun River"
        | "Nyong River"
        | "Obey River"
        | "Ob River"
        | "Ocoee River"
        | "Oder River"
        | "Ogooue River"
        | "Ohio River"
        | "Ohre River"
        | "Oise River"
        | "Oka River"
        | "Okavango River"
        | "Oldman River"
        | "Olenyok River"
        | "Olt River"
        | "Omo River"
        | "Orange River"
        | "Ord River"
        | "Orhon River"
        | "Orinoco River"
        | "Orne River"
        | "Orontes River"
        | "Osage River"
        | "Oti River"
        | "Ottawa River"
        | "Otter Creek"
        | "Ouachita River"
        | "Oueme River"
        | "Ouham River"
        | "Oum el-Rbia River"
        | "Ou River"
        | "Outardes River"
        | "Owens River"
        | "Owyhee River"
        | "Oyapock River"
        | "Padma River"
        | "Pahang River"
        | "Palar River"
        | "Pampanga River"
        | "Pangani River"
        | "Panjnad River"
        | "Panj River"
        | "Panuco River"
        | "Papaloapan River"
        | "Paraguacu River"
        | "Paraguay River"
        | "Paranaiba River"
        | "Paranapanema River"
        | "Parana River"
        | "Para River"
        | "Parnaiba River"
        | "Paru River"
        | "Pasig River"
        | "Passaic River"
        | "Patia River"
        | "Patuca River"
        | "Pawcatuck River"
        | "Payette River"
        | "Peace River"
        | "Pearl River"
        | "Pechora River"
        | "Pecos River"
        | "Pedieos River"
        | "Pee Dee River"
        | "Peel River"
        | "Pelly River"
        | "Pelotas River"
        | "Penneru River"
        | "Penobscot River"
        | "Periyar River"
        | "Pescara River"
        | "Petitcodiac River"
        | "Piave River"
        | "Pieman River"
        | "Pigeon River"
        | "Pilcomayo River"
        | "Pineios River"
        | "Ping River"
        | "Platte River"
        | "Podkamennaya Tunguska River"
        | "Polochic River"
        | "Ponnaiyar River"
        | "Ponnani River"
        | "Porcupine River"
        | "Po River"
        | "Portneuf River"
        | "Potomac River"
        | "Powder River"
        | "Powell River"
        | "Pra River"
        | "Price River"
        | "Pripet River"
        | "Prut River"
        | "Purari River"
        | "Purus River"
        | "Pusur River"
        | "Putumayo River"
        | "Pyshma River"
        | "Qin River"
        | "Qishon River"
        | "Qu'Appelle River"
        | "Rahad River"
        | "Rajang River"
        | "Rakaia River"
        | "Ramu River"
        | "Rance River"
        | "Rangitata River"
        | "Rangitikei River"
        | "Rappahannock River"
        | "Raritan River"
        | "Ravi River"
        | "Red Deer River"
        | "Red River"
        | "Red River of the North"
        | "Red Volta River"
        | "Regnitz River"
        | "Republican River"
        | "Rewa River"
        | "Rhine River"
        | "Rhone River"
        | "Richelieu River"
        | "Richmond River"
        | "Rio de Acari"
        | "Rio Grande"
        | "Rio Grande de Matagalpa"
        | "Rio Grande de Santiago"
        | "River Aire"
        | "River Avon (central England)"
        | "River Avon (southern England)"
        | "River Avon (western England)"
        | "River Bann"
        | "River Barrow"
        | "River Blackwater"
        | "River Boyne"
        | "River Clwyd"
        | "River Clyde"
        | "River Dee (Scotland)"
        | "River Dee (Wales and England)"
        | "River Derwent"
        | "River Don (England)"
        | "River Don (Scotland)"
        | "River Eden"
        | "River Erne"
        | "River Ettrick"
        | "River Exe"
        | "River Finn"
        | "River Forth"
        | "River Lagan"
        | "River Lea"
        | "River Liffey"
        | "River Lune"
        | "River Medina"
        | "River Medway"
        | "River Mersey"
        | "River Mourne"
        | "River Nen"
        | "River Ouse (eastern England)"
        | "River Ouse (northern England)"
        | "River Ribble"
        | "River Severn"
        | "River Shannon"
        | "River Slaney"
        | "River Spey"
        | "River Suir"
        | "River Swale"
        | "River Tamar"
        | "River Tay"
        | "River Tees"
        | "River Teviot"
        | "River Thames"
        | "River Trent"
        | "River Tummel"
        | "River Tweed"
        | "River Waveney"
        | "River Wear"
        | "River Weaver"
        | "River Welland"
        | "River Wensum"
        | "River Wharfe"
        | "River Witham"
        | "River Wye"
        | "River Yare"
        | "River Yarrow"
        | "Roanoke River"
        | "Rock River"
        | "Rokel River"
        | "Roper River"
        | "Rubicon"
        | "Rufiji River"
        | "Ruhr"
        | "Ruhuhu River"
        | "Ruki River"
        | "Ruo River"
        | "Rupert River"
        | "Rupnarayan River"
        | "Ruvubu River"
        | "Ruvuma River"
        | "Ruzizi River"
        | "Saale River"
        | "Saar River"
        | "Sabine River"
        | "Sabi River"
        | "Sacramento River"
        | "Safid River"
        | "Saguenay River"
        | "Saigon River"
        | "Saint Clair River"
        | "Saint Croix River"
        | "Saint Croix River (Maine)"
        | "Saint Croix River (Wisconsin)"
        | "Saint Francis River"
        | "Saint John River"
        | "Saint Johns River"
        | "Saint Joseph River"
        | "Saint Lawrence River and Seaway"
        | "Saint Marys River"
        | "Saint-Maurice River"
        | "Saint Paul River"
        | "Salado River"
        | "Saline River"
        | "Salmon River"
        | "Salt Fork Arkansas River"
        | "Salt River"
        | "Saluda River"
        | "Salween River"
        | "Samara River"
        | "Sanaga River"
        | "Sanggan River"
        | "Sangha River"
        | "San Joaquin River"
        | "San Juan River"
        | "Sankarani River"
        | "Sankuru River"
        | "Santa River"
        | "Santee River"
        | "Sao Francisco River"
        | "Sao Lourenco River"
        | "Saone River"
        | "Sarda River"
        | "Sarthe River"
        | "Saskatchewan River"
        | "Sassandra River"
        | "Savannah River"
        | "Sava River"
        | "Schelde River"
        | "Schuylkill River"
        | "Schwarze Elster River"
        | "Scioto River"
        | "Sebou River"
        | "Seekonk River"
        | "Segura River"
        | "Seine River"
        | "Selenga River"
        | "Semliki River"
        | "Senegal River"
        | "Sepik River"
        | "Sequatchie River"
        | "Severn River"
        | "Sevier River"
        | "Sewa River"
        | "Sharavati River"
        | "Shashi River"
        | "Shatt Al-Arab"
        | "Shebeli River"
        | "Shemanker River"
        | "Sheyenne River"
        | "Shilka River"
        | "Shinano River"
        | "Shire River"
        | "Shoalhaven River"
        | "Shoshone River"
        | "Shyok River"
        | "Sierra Leone River"
        | "Sileru River"
        | "Siret River"
        | "Sittang River"
        | "Skeena River"
        | "Skunk River"
        | "Slave River"
        | "Smoky Hill River"
        | "Snake River"
        | "Snoqualmie River"
        | "Snowy River"
        | "Sobat River"
        | "Sokoto River"
        | "Solimoes River"
        | "Solomon River"
        | "Solo River"
        | "Somes River"
        | "Somes River"
        | "Somme River"
        | "Sonora River"
        | "Son River"
        | "Souris River"
        | "Sous River"
        | "Southern Buh"
        | "South Platte River"
        | "Spokane River"
        | "Spoon River"
        | "Spree River"
        | "Stikine River"
        | "Stillwater River"
        | "Stones River"
        | "Strawberry River"
        | "Struma River"
        | "Subarnarekha River"
        | "Sungari (Songhua) River"
        | "Sun River"
        | "Sura River"
        | "Sure River"
        | "Suriname River"
        | "Surma River"
        | "Susquehanna River"
        | "Sutlej River"
        | "Suwannee River"
        | "Swan River"
        | "Swat River"
        | "Sweetwater River"
        | "Syr Darya"
        | "Taedong River"
        | "Tagus River"
        | "Taieri River"
        | "Tallahatchie River"
        | "Tallapoosa River"
        | "Tanana River"
        | "Tana River"
        | "Tano River"
        | "Tapajos River"
        | "Tapti River"
        | "Taquari River"
        | "Tarim River"
        | "Tarn River"
        | "Tar River"
        | "Tekeze River"
        | "Teles Pires River"
        | "Tennessee River"
        | "Tennsift River"
        | "Tensas River"
        | "Terek River"
        | "Teton River"
        | "Thames River"
        | "Tha River"
        | "Thelon River"
        | "Thjors River"
        | "Thompson River"
        | "Tiber River"
        | "Ticino River"
        | "Tiete River"
        | "Timis River"
        | "Tinkisso River"
        | "Tippecanoe River"
        | "Tirso River"
        | "Tista River"
        | "Tisza River"
        | "Tobol River"
        | "Tocantins River"
        | "Todd River"
        | "Tombigbee River"
        | "Tone River"
        | "Tongue River"
        | "Torne River"
        | "Towy River"
        | "Trebbia River"
        | "Trombetas River"
        | "Tuckasegee River"
        | "Tugaloo River"
        | "Tugela River"
        | "Tuira River"
        | "Tumen River"
        | "Tumut River"
        | "Tunguska River"
        | "Tuscarawas River"
        | "Tweed River"
        | "Ubangi River"
        | "Ucayali River"
        | "Ulua River"
        | "Umniati River"
        | "Unzha River"
        | "Ural River"
        | "Urubamba River"
        | "Uruguay River"
        | "Ussuri River"
        | "Ussuri (Wusuli) River"
        | "Usumacinta River"
        | "Vaal River"
        | "Vah River"
        | "Vaigai River"
        | "Vardar River"
        | "Verdigris River"
        | "Verdon River"
        | "Victoria Nile"
        | "Victoria River"
        | "Vienne River"
        | "Vilyuy River"
        | "Vistula River"
        | "Vitim River"
        | "Vltava River"
        | "Volga River"
        | "Volkhov River"
        | "Volta River"
        | "Volturno River"
        | "Vychegda River"
        | "Wabash River"
        | "Waccamaw River"
        | "Wadi Majardah"
        | "Wadi Seybouse"
        | "Waiau River (eastern South Island)"
        | "Waiau River (southwestern South Island)"
        | "Waikato River"
        | "Wailua River"
        | "Waimakariri River"
        | "Wainganga River"
        | "Wairau River"
        | "Waitaki River"
        | "Walhonding River"
        | "Wanganui River"
        | "Warta River"
        | "Washita River"
        | "Wateree River"
        | "Wei River"
        | "Werra River"
        | "Weser River"
        | "Western Dvina River"
        | "White Nile River"
        | "White River (Arkansas and Missouri)"
        | "White River (Indiana)"
        | "White River (Nebraska and South Dakota)"
        | "White Volta River"
        | "Willamette River"
        | "Wilmot River"
        | "Wind River"
        | "Winisk River"
        | "Winnipeg River"
        | "Winooski River"
        | "Wisconsin River"
        | "Wouri River"
        | "Xiang River"
        | "Xingu River"
        | "Xin River"
        | "Xi River system"
        | "Yakima River"
        | "Yalobusha River"
        | "Yalong River"
        | "Yalu River"
        | "Yampa River"
        | "Yamuna River"
        | "Yangon River"
        | "Yangtze River (Chang Jiang)"
        | "Yaque del Norte River"
        | "Yaque del Sur River"
        | "Yaqui River"
        | "Yarkand River"
        | "Yarmuk River"
        | "Yarqon River"
        | "Yarra River"
        | "Yazoo River"
        | "Yellowstone River"
        | "Yenisey River"
        | "Yodo River"
        | "Yongding River"
        | "Yongsan River"
        | "Yonne River"
        | "Youghiogheny River"
        | "Yser River"
        | "Yuan River"
        | "Yukon River"
        | "Yuna River"
        | "Yu River"
        | "Zambezi River"
        | "Zeravshan River"
    ) [\n];

    other = [a-zA-Z '-()]+ [\n];

    main := |*
        word { OUTS(ts, te); };
        other { };
    *|;
}%%

%% write data;

static int lex(Input *in, int count) {
    char *p = in->p;
    char *ts = in->ts;
    char *te = in->te;
    char *pe = in->pe;
    int act = in->act;
    int cs;

    %% write init;
    %% write exec;

    in->p = p;
    in->ts = ts;
    in->te = te;
    in->pe = pe;
    in->act = act;

    return count;
}

RAGEL_BENCH_AND_TEST()

} // namespace ragel_lex_04__words3

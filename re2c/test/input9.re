/*!re2c

any = [\000-\377];

"\000"       { return 1; }
"\001"       { return 2; }
"\007"       { return 3; }
"\010"       { return 4; }
"\100"       { return 5; }
"\123"       { return 6; }
"\3567"      { return 7; }

"\x02"       { return 8; }
"\x20"       { return 9; }
"\x34"       { return 10; }
"\xab"       { return 11; }
"\xCD"       { return 12; }
any          { return 0; }

*/

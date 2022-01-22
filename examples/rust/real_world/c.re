// re2rust -W $INPUT -o $OUTPUT --no-unsafe

// This example is based on a public domain C lex grammar originally
// hosted at http://www.quut.com/c/ANSI-C-grammar-l.html
// It has, however, been significantly modified.

// A real C lexer in a modern compiler typically postprocesses a tokenization
// step performed by the preprocessor. This example isn't actually practically
// usable as-is, and would require significant work to turn into part of a real
// C compiler.

// As with the original from quut.com, this grammar presupposes translation for
// phases 1 to 5 have already been performed, though it also still handles
// comments. It does handle string concatenation though in a sort of
// half-hearted manner.

// We specify unicode here to make the code in this example more interesting.
// We use the "ignore" Unicode encoding policy (which is the default anyway)
// because the Rust input routine we use is already checking for surrogates.
/*!re2c
    re2c:encoding:utf8 = 1;
    re2c:encoding-policy = ignore;
 */

use std::fmt;

// Errors type
#[derive(Debug, Clone)]
struct LexError {
    message: String,
    token_text: String,
    line: usize,
    column: usize,
}

impl fmt::Display for LexError {
    fn fmt(&self, f: &mut fmt::Formatter) -> Result<(), fmt::Error> {
        write!(f, "{}: {} ({}:{})",
            self.message, self.token_text, self.line, self.column)
    }
}

// The default definitions for the Error methods are fine.
impl std::error::Error for LexError { }

#[derive(Debug, Clone)]
#[allow(dead_code)] // silence 'field in not used' warnings
struct Position {
    // What line are we on? (starts on line 0.)
    line_num: usize,
    // What is the index of the first character on the line?
    bol: usize,
    // What is the index of the current token?
    start: usize,
    // What is the index of the end of the current token?
    end: usize,
}

// All the different kinds of tokens.
#[derive(Debug, Clone, Eq, PartialEq)]
enum TName {
    // General
    //Error(String),
    Comment,
    Whitespace,
    Newline,
    // Ids.
    Id,
    TypeId,
    EnumId,
    // Constants
    IntConst,
    FloatConst,
    StringLiteral,
    // Keywords
    Alignas,
    Alignof,
    Atomic,
    Bool,
    Complex,
    Generic,
    Imaginary,
    Noreturn,
    StaticAssert,
    ThreadLocal,
    Auto,
    Break,
    Case,
    Char,
    Const,
    Continue,
    Default,
    Do,
    Double,
    Else,
    Enum,
    Extern,
    Float,
    For,
    Goto,
    If,
    Inline,
    Int,
    Long,
    Register,
    Restrict,
    Return,
    Short,
    Signed,
    Sizeof,
    Static,
    Struct,
    Switch,
    Typedef,
    Union,
    Unsigned,
    Void,
    Volatile,
    While,
    // Punctuators
    Ellipsis,
    RSAsgn,
    LSAsgn,
    AddAsgn,
    SubAsgn,
    MulAsgn,
    DivAsgn,
    ModAsgn,
    BAndAsgn,
    BXorAsgn,
    BOrAsgn,
    RShift,
    LShift,
    Incr,
    Decr,
    Arrow,
    LAnd,
    LOr,
    LE,
    GE,
    Eq,
    NEq,
    Semi,
    OBrace,
    CBrace,
    Comma,
    Colon,
    Asgn,
    OParen,
    CParen,
    OBrack,
    CBrack,
    Dot,
    Amper,
    LNot,
    BNot,
    Sub,
    Add,
    Aster,
    Div,
    Mod,
    LT,
    GT,
    BXor,
    BOr,
    Ques,
}

#[derive(Debug, Clone)]
#[allow(dead_code)] // silence 'field in not used' warnings
struct Token {
    tname: TName,
    text: String,
    position: Position,
}

#[derive(Debug, Clone)]
enum SymType {
    #[allow(dead_code)] // silence 'variant is never constructed' warning
    TypeName,
    #[allow(dead_code)] // silence 'variant is never constructed' warning
    EnumConst,
    Identifier,
}

// C lexers (unfortunately) need information from the symbol table to return
// the correct token type, because an identifier could be a type name. (This
// ambiguity is a big source of trouble in C.) This is a fake "sym_type" that
// always returns Identifer. It needs to be fixed to actually hook into the
// parser's symbol table if this lexer is used in the real world.
fn sym_type(_ident: &str) -> SymType {
    SymType::Identifier
}

#[derive(Debug, Clone)]
struct Input {
    data: Vec<u8>,
    cursor: usize,
    token: usize,
    marker: usize,
    line: usize,
    bol: usize,
    eof: bool,
}

impl Input {
    fn new(s: String) -> Input {
        let data = s.into_bytes();
        Input {
            data: data,
            cursor: 0,
            token: 0,
            marker: 0,
            line: 0,
            bol: 0,
            eof: false,
        }
    }
    // text of the current token
    fn current_ttext(&self) -> String {
        // for maximum performance, this should actually be from_utf8_unchecked
        String::from_utf8(self.data[self.token..self.cursor].to_vec()).unwrap()
    }

    fn token(&mut self, tname: TName) -> Result<Option<Token>, LexError> {
        let text = self.current_ttext();

        let position = Position {
            line_num: self.line,
            bol: self.bol,
            start: self.token,
            end: self.cursor,
        };

        let lines = match tname {
            TName::Comment => text.lines().count() - 1,
            // We may have multiple string literals separated by
            // newlines or the like to fuse.
            TName::StringLiteral => text.lines().count() - 1,
            TName::Newline => 1,
            _ => 0,
        };

        if tname == TName::Newline {
            self.bol = self.cursor;
        } else if lines > 0 {
            // the unwrap should only fail if we have a bad bug.
            self.bol = self.data[0..self.cursor]
                .iter().rposition(|bytes| *bytes == b'\n')
                .unwrap();
        };

        self.line += lines;

        Ok(Some(Token {
            tname,
            text,
            position,
        }))
    }

    fn error(&self, s: &str) -> Result<Option<Token>, LexError> {
        Err(LexError {
            message: s.to_string(),
            token_text: self.current_ttext(),
            line: self.line,
            column: self.cursor - self.bol,
        })
    }

    // Tells us whether an identifier is a type name, an enum constant, or an
    // ordinary identifier.
    fn check_type(&mut self) -> Result<Option<Token>, LexError> {
        let text = self.current_ttext();
        match sym_type(&text) {
            SymType::TypeName   => self.token(TName::TypeId),
            SymType::EnumConst  => self.token(TName::EnumId),
            SymType::Identifier => self.token(TName::Id),
        }
    }
}

// Some of this lexer was taken from the C lex grammar at
// http://www.quut.com/c/ANSI-C-grammar-l.html
fn next_token(input: &mut Input) -> Result<Option<Token>, LexError> {
    if input.eof { return Ok(None) }

    input.token = input.cursor;
    /*!re2c
    re2c:yyfill:enable = 0;
    re2c:define:YYCTYPE      = "u8";
    re2c:define:YYPEEK       = "input.data[input.cursor]";
    re2c:define:YYSKIP       = "input.cursor += 1;";
    re2c:define:YYBACKUP     = "input.marker = input.cursor;";
    re2c:define:YYRESTORE    = "input.cursor = input.marker;";
    re2c:define:YYRESTORETAG = "input.cursor = ${tag};";
    re2c:define:YYSTAGP      = "@@{tag} = input.cursor;";
    re2c:define:YYSTAGN      = "@@{tag} = -1;";
    re2c:define:YYSHIFT      = "input.cursor += @@{shift};";
    re2c:define:YYSHIFTSTAG  = "@@{tag} += @@{shift};";

    O  = [0-7];
    D  = [0-9];
    NZ = [1-9];
    L  = [a-zA-Z_];
    A  = [a-zA-Z_0-9];
    H  = [a-fA-F0-9];
    HP = ("0"[xX]);
    E  = ([Ee][+-]?D+);
    P  = ([Pp][+-]?D+);
    FS = [fFlL];
    IS = (([uU]("l"|"L"|"ll"|"LL")?)|(("l"|"L"|"ll"|"LL")[uU]?));
    CP = ("u"|"U"|"L");
    SP = ("u8"|"u"|"U"|"L");
    ES = ("\\"(['"?\\abfnrtv]|[0-7]{1,3}|"x"[a-fA-F0-9]+));
    LWS = [ \t\v\f];
    WS = [ \t\v\n\f];

    // For efficiency, block comments should probably be handled by a special
    // function that tracks newlines etc. We're punting on that.
    "/" "*" ([^\x00*]|"*"+[^\x00/])* "*"+ "/" {
        return input.token(TName::Comment)
    }
    // A small rule to catch and error on unterminated comments.
    "/" "*" ([^\x00*]|"*"+[^\x00/])* {
        return input.error("unterminated comment")
    }
    // Line comments
    "//"[^\x00\n]* { return input.token(TName::Comment) }

    "_Alignas"       { return input.token(TName::Alignas) }
    "_Alignof"       { return input.token(TName::Alignof) }
    "_Atomic"        { return input.token(TName::Atomic) }
    "_Bool"          { return input.token(TName::Bool) }
    "_Complex"       { return input.token(TName::Complex) }
    "_Generic"       { return input.token(TName::Generic) }
    // _Imaginary is reserved but not used in C
    "_Imaginary"     { return input.token(TName::Imaginary) }
    "_Noreturn"      { return input.token(TName::Noreturn) }
    "_Static_assert" { return input.token(TName::StaticAssert) }
    "_Thread_local"  { return input.token(TName::ThreadLocal) }

    "auto"     { return input.token(TName::Auto) }
    "break"    { return input.token(TName::Break) }
    "case"     { return input.token(TName::Case) }
    "char"     { return input.token(TName::Char) }
    "const"    { return input.token(TName::Const) }
    "continue" { return input.token(TName::Continue) }
    "default"  { return input.token(TName::Default) }
    "do"       { return input.token(TName::Do) }
    "double"   { return input.token(TName::Double) }
    "else"     { return input.token(TName::Else) }
    "enum"     { return input.token(TName::Enum) }
    "extern"   { return input.token(TName::Extern) }
    "float"    { return input.token(TName::Float) }
    "for"      { return input.token(TName::For) }
    "goto"     { return input.token(TName::Goto) }
    "if"       { return input.token(TName::If) }
    "inline"   { return input.token(TName::Inline) }
    "int"      { return input.token(TName::Int) }
    "long"     { return input.token(TName::Long) }
    "register" { return input.token(TName::Register) }
    "restrict" { return input.token(TName::Restrict) }
    "return"   { return input.token(TName::Return) }
    "short"    { return input.token(TName::Short) }
    "signed"   { return input.token(TName::Signed) }
    "sizeof"   { return input.token(TName::Sizeof) }
    "static"   { return input.token(TName::Static) }
    "struct"   { return input.token(TName::Struct) }
    "switch"   { return input.token(TName::Switch) }
    "typedef"  { return input.token(TName::Typedef) }
    "union"    { return input.token(TName::Union) }
    "unsigned" { return input.token(TName::Unsigned) }
    "void"     { return input.token(TName::Void) }
    "volatile" { return input.token(TName::Volatile) }
    "while"    { return input.token(TName::While) }

    // In C, identifiers cannot actually be assigned a token type without
    // cooperation with the parser. We call a function that tells us what kind
    // of token this really is.
    L A*       { return input.check_type() }

    HP H+ IS?  { return input.token(TName::IntConst) }
    NZ D* IS?  { return input.token(TName::IntConst) }
    "0" O* IS? { return input.token(TName::IntConst) }

    // Character constants
    CP? "'" ([^\x00'\\\n]|ES)+ "'" { return input.token(TName::IntConst) }

    // A rule to catch unterminated character constants
    CP? "'" ([^\x00'\\\n]|ES)+ {
        return input.error("unterminated character constant")
    }

    D+ E FS?            { return input.token(TName::FloatConst) }
    D* "." D+ E? FS?    { return input.token(TName::FloatConst) }
    D+ "." E? FS?       { return input.token(TName::FloatConst) }
    HP H+ P FS?         { return input.token(TName::FloatConst) }
    HP H* "." H+ P FS?  { return input.token(TName::FloatConst) }
    HP H+ "." P FS?     { return input.token(TName::FloatConst) }

    // adjacent string literals get fused
    (SP? "\"" ([^\x00"\\\n]|ES)* "\"" WS*)+ {
        return input.token(TName::StringLiteral)
    }

    // A rule to catch unterminated strings.
    (SP? "\"" ([^\x00"\\\n]|ES)*) {
        return input.error("unterminated string")
    }

    "..."    { return input.token(TName::Ellipsis) }
    ">>="    { return input.token(TName::RSAsgn) }
    "<<="    { return input.token(TName::LSAsgn) }
    "+="     { return input.token(TName::AddAsgn) }
    "-="     { return input.token(TName::SubAsgn) }
    "*="     { return input.token(TName::MulAsgn) }
    "/="     { return input.token(TName::DivAsgn) }
    "%="     { return input.token(TName::ModAsgn) }
    "&="     { return input.token(TName::BAndAsgn) }
    "^="     { return input.token(TName::BXorAsgn) }
    "|="     { return input.token(TName::BOrAsgn) }
    ">>"     { return input.token(TName::RShift) }
    "<<"     { return input.token(TName::LShift) }
    "++"     { return input.token(TName::Incr) }
    "--"     { return input.token(TName::Decr) }
    "->"     { return input.token(TName::Arrow) }
    "&&"     { return input.token(TName::LAnd) }
    "||"     { return input.token(TName::LOr) }
    "<="     { return input.token(TName::LE) }
    ">="     { return input.token(TName::GE) }
    "=="     { return input.token(TName::Eq) }
    "!="     { return input.token(TName::NEq) }
    ";"      { return input.token(TName::Semi) }
    "{"      { return input.token(TName::OBrace) }
    "}"      { return input.token(TName::CBrace) }
    ","      { return input.token(TName::Comma) }
    ":"      { return input.token(TName::Colon) }
    "="      { return input.token(TName::Asgn) }
    "("      { return input.token(TName::OParen) }
    ")"      { return input.token(TName::CParen) }
    "["      { return input.token(TName::OBrack) }
    "]"      { return input.token(TName::CBrack) }
    "."      { return input.token(TName::Dot) }
    "&"      { return input.token(TName::Amper) }
    "!"      { return input.token(TName::LNot) }
    "~"      { return input.token(TName::BNot) }
    "-"      { return input.token(TName::Sub) }
    "+"      { return input.token(TName::Add) }
    "*"      { return input.token(TName::Aster) }
    "/"      { return input.token(TName::Div) }
    "%"      { return input.token(TName::Mod) }
    "<"      { return input.token(TName::LT) }
    ">"      { return input.token(TName::GT) }
    "^"      { return input.token(TName::BXor) }
    "|"      { return input.token(TName::BOr) }
    "?"      { return input.token(TName::Ques) }

    // Whitespace separates tokens. In general, most parsers are not going to
    // want to deal with these. In this example we're returning them as actual
    // tokens though. For no particularly deep or good reason, we've made
    // Newline its own token, though it does simplify some processing.
    LWS+   { return input.token(TName::Whitespace) }
    "\n"   { return input.token(TName::Newline) }

    // Bad characters generate an error.
    *      { return input.error("bad character") }

    // XXX shouldn't need return!
    [\x00] { input.eof = true; return Ok(None); }
    */

}

const DEBUG: bool = false;
macro_rules! log {
    ($($fmt:expr)? $(, $args:expr)*) => {
        if DEBUG { println!($($fmt)? $(, $args)*) }
    }
}

fn main() -> std::io::Result<()> {
    use std::env;
    use std::fs;

    // Treats the first command line argument as a filename and returns file
    // contents as a string. If there is no filename, returns a pre-defined
    // example string (this is used for testing).
    let args: Vec<String> = env::args().collect();

    // We append a '\0' at the end of the string to act as a sentinel.
    let mut str: String;
    if args.len() < 2 {
        str = "int main() { return 0; }\0".to_string(); // example C program
    } else {
        str = fs::read_to_string(&args[1])?;
        str.push('\0');
    }

    let mut input = Input::new(str);

    loop {
        match next_token(&mut input) {
            Ok(Some(token)) => log!("{:#?}", token),
            Ok(None) => {
                log!("EOF");
                break;
            },
            Err(error) => {
                log!("error: {:#?}", error);
                break;
            },
        };
    };

    Ok(())
}

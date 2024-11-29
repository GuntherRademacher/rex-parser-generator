# This file was created Thu Sep 17, 2009 21:18 by REx V5.5 (c) GR 2009

#option nogrammar
#option noabbreviations
#option noambiguities
#option classify
#option case-sensitive
#option nosymbols
#option error=1
#option xquery

# lookahead sets

# set 0
         [string];
# set 1
         [14];
# set 2
         [EPSILON, whitespace^token];
# set 3
         [eof, whitespace^token];
# set 4
         [whitespace^token, 8];
# set 5
         [whitespace^token, 10];
# set 6
         [whitespace^token, 15];
# set 7
         [string, whitespace^token, 15];
# set 8
         [whitespace^token, 7, 10];
# set 9
         [whitespace^token, 7, 15];
# set 10
         [string, number, 9, 11, 12, 13, 14];
# set 11
         [string, number, whitespace^token, 9, 10, 11, 12, 13, 14];

EPSILON (0)
        :  ;
eof (3)
        : $ ;
string (4)
        : """" ( ((anyUnicodeCharacterExceptQuoteOrBackslashOrControlCharacter)
           | ("\""") | ("\\") | ("\/") | ("\b") | ("\f") | ("\n") | ("\r") | (
          "\t") | ("\u" fourHexadecimalDigits)) ) * """" ;
number (5)
        : ( "-" ) ? (("0") | (digitOneThroughNine ( digit ) *)) ( "." ( digit )
          + ) ? ( (("e") | ("E")) ( (("+") | ("-")) ) ? ( digit ) + ) ? ;
whitespace^token (6)
        : whitespace ;
(7)
        : "," ;
(8)
        : ":" ;
(9)
        : "[" ;
(10)
        : "]" ;
(11)
        : "false" ;
(12)
        : "null" ;
(13)
        : "true" ;
(14)
        : "{" ;
(15)
        : "}" ;
anyUnicodeCharacterExceptQuoteOrBackslashOrControlCharacter
        : alphabet - ['"', 0x5C] ;
alphabet
        : (0x9) | (0xA) | (0xD) | ([" "..0xD7FF]) | ([0xE000..0xFFFD]) | ([
          0x10000..0x10FFFF]) ;
hexadecimalDigit
        : ['0'..'9', 'A'..'F', 'a'..'f'] ;
fourHexadecimalDigits
        : hexadecimalDigit hexadecimalDigit hexadecimalDigit hexadecimalDigit ;
digit
        : ['0'..'9'] ;
digitOneThroughNine
        : digit - "0" ;
whitespace
        : ( [0x9, 0xA, 0xD, " "] ) + ;

# EoF

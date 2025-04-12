lexer grammar GoliteLexer;

// Keywords
TYPE        : 'type';
STRUCT      : 'struct';
VAR         : 'var';
FUNC        : 'func';
IF          : 'if';
ELSE        : 'else';
FOR         : 'for';
RETURN      : 'return';
SCAN        : 'scan';
PRINTF      : 'printf';
DELETE      : 'delete';
NEW         : 'new';
TRUE        : 'true';
FALSE       : 'false';
NIL         : 'nil';
INT         : 'int';
BOOL        : 'bool';

// Punctuation
L_PAREN     : '(';
R_PAREN     : ')';
L_CURLY     : '{';
R_CURLY     : '}';
L_BRACKET   : '[';
R_BRACKET   : ']';
ASSIGN      : '=';
COMMA       : ',';
SEMI        : ';';
COLON       : ':';
DOT         : '.';
PLUS        : '+';
MINUS       : '-';
STAR        : '*';
DIV         : '/';
MOD         : '%';
EXCLAMATION : '!';
LOGICAL_OR  : '||';
LOGICAL_AND : '&&';
EQUALS      : '==';
NOT_EQUALS  : '!=';
LESS        : '<';
LESS_OR_EQUALS : '<=';
GREATER     : '>';
GREATER_OR_EQUALS : '>=';
PERCENT_D   : '%d'; // For printf format strings

// Identifiers
ID          : [a-zA-Z][a-zA-Z0-9]*;

// Number literals (only integers)
NUMBER : '0' | [1-9][0-9]*;

// String literals (only double-quoted strings)
STRING      : '"' (~["\\\r\n] | '\\' .)* '"';

// Whitespace and comments
WS          : [ \t\r\n]+ -> skip;
COMMENT     : '//' ~[\r\n]* -> skip;

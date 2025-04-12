parser grammar GoliteParser;

options {
    tokenVocab = GoliteLexer;
}

// Entry point
program
    : types declarations functions EOF
    ;

// Types
types
    : typeDeclaration*
    ;

typeDeclaration
    : TYPE ID STRUCT L_CURLY fields R_CURLY SEMI
    ;

fields
    : decl SEMI (decl SEMI)*
    ;

decl
    : ID type
    ;

type
    : INT
    | BOOL
    | STAR ID
    ;

// Declarations
declarations
    : declaration*
    ;

declaration
    : VAR ids type SEMI
    ;

ids
    : ID (COMMA ID)*
    ;

// Functions
functions
    : function*
    ;

function
    : FUNC ID parameters returnType? L_CURLY declarations statements R_CURLY
    ;

parameters
    : L_PAREN (decl (COMMA decl)*)? R_PAREN
    ;

returnType
    : type
    ;

// Statements
statements
    : statement*
    ;

statement
    : assignment
    | print
    | scan
    | delete
    | conditional
    | loop
    | return
    | block
    | invocation
    ;

invocation
    : ID arguments SEMI
    ;

block
    : L_CURLY statements R_CURLY
    ;

assignment
    : lvalue ASSIGN expression SEMI
    ;

print
    : PRINTF L_PAREN STRING (COMMA expression)* R_PAREN SEMI
    ;

scan
    : SCAN lvalue SEMI
    ;

delete
    : DELETE expression SEMI
    ;

conditional
    : IF L_PAREN expression R_PAREN block (ELSE block)?
    ;

loop
    : FOR L_PAREN expression R_PAREN block
    ;

return
    : RETURN expression? SEMI
    ;

// Expressions
expression
    : arithmeticExpression
    | boolExpression
    ;

boolExpression
    : boolTerm (LOGICAL_OR boolTerm)*
    ;

boolTerm
    : equalTerm (LOGICAL_AND equalTerm)*
    ;

equalTerm
    : relationTerm ((EQUALS | NOT_EQUALS) relationTerm)*
    ;

relationTerm
    : arithmeticExpression ((LESS | GREATER | LESS_OR_EQUALS | GREATER_OR_EQUALS) arithmeticExpression)*
    ;

arithmeticExpression
    : simpleTerm
    ;

simpleTerm
    : term ((PLUS | MINUS) term)*
    ;

term
    : unaryTerm ((STAR | DIV) unaryTerm)*
    ;

unaryTerm
    : EXCLAMATION unaryTerm
    | MINUS unaryTerm
    | selectorTerm
    ;


selectorTerm
    : factor (DOT ID)*
    ;

factor
    : L_PAREN expression R_PAREN
    | ID arguments?
    | NUMBER
    | NEW ID
    | TRUE
    | FALSE
    | NIL
    ;

arguments
    : L_PAREN (expression (COMMA expression)*)? R_PAREN
    ;

lvalue
    : selectorTerm
    ;

// Generated from GoliteLexer.g4 by ANTLR 4.11.1

#pragma once


#include "antlr4-runtime.h"


namespace lexer {


class  GoliteLexer : public antlr4::Lexer {
public:
  enum {
    TYPE = 1, STRUCT = 2, VAR = 3, FUNC = 4, IF = 5, ELSE = 6, FOR = 7, 
    RETURN = 8, SCAN = 9, PRINTF = 10, DELETE = 11, NEW = 12, TRUE = 13, 
    FALSE = 14, NIL = 15, INT = 16, BOOL = 17, L_PAREN = 18, R_PAREN = 19, 
    L_CURLY = 20, R_CURLY = 21, L_BRACKET = 22, R_BRACKET = 23, ASSIGN = 24, 
    COMMA = 25, SEMI = 26, COLON = 27, DOT = 28, PLUS = 29, MINUS = 30, 
    STAR = 31, DIV = 32, MOD = 33, EXCLAMATION = 34, LOGICAL_OR = 35, LOGICAL_AND = 36, 
    EQUALS = 37, NOT_EQUALS = 38, LESS = 39, LESS_OR_EQUALS = 40, GREATER = 41, 
    GREATER_OR_EQUALS = 42, PERCENT_D = 43, ID = 44, NUMBER = 45, STRING = 46, 
    WS = 47, COMMENT = 48
  };

  explicit GoliteLexer(antlr4::CharStream *input);

  ~GoliteLexer() override;


  std::string getGrammarFileName() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const std::vector<std::string>& getChannelNames() const override;

  const std::vector<std::string>& getModeNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;

  const antlr4::atn::ATN& getATN() const override;

  // By default the static state used to implement the lexer is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:

  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

};

}  // namespace lexer

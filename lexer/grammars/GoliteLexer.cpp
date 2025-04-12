
// Generated from grammars/GoliteLexer.g4 by ANTLR 4.11.1


#include "GoliteLexer.h"


using namespace antlr4;

using namespace GoliteLexer;


using namespace antlr4;

namespace {

struct GoliteLexerStaticData final {
  GoliteLexerStaticData(std::vector<std::string> ruleNames,
                          std::vector<std::string> channelNames,
                          std::vector<std::string> modeNames,
                          std::vector<std::string> literalNames,
                          std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), channelNames(std::move(channelNames)),
        modeNames(std::move(modeNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  GoliteLexerStaticData(const GoliteLexerStaticData&) = delete;
  GoliteLexerStaticData(GoliteLexerStaticData&&) = delete;
  GoliteLexerStaticData& operator=(const GoliteLexerStaticData&) = delete;
  GoliteLexerStaticData& operator=(GoliteLexerStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> channelNames;
  const std::vector<std::string> modeNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag golitelexerLexerOnceFlag;
GoliteLexerStaticData *golitelexerLexerStaticData = nullptr;

void golitelexerLexerInitialize() {
  assert(golitelexerLexerStaticData == nullptr);
  auto staticData = std::make_unique<GoliteLexerStaticData>(
    std::vector<std::string>{
      "TYPE", "STRUCT", "VAR", "FUNC", "IF", "ELSE", "FOR", "RETURN", "SCAN", 
      "PRINTF", "DELETE", "NEW", "TRUE", "FALSE", "NIL", "INT", "BOOL", 
      "L_PAREN", "R_PAREN", "L_CURLY", "R_CURLY", "L_BRACKET", "R_BRACKET", 
      "ASSIGN", "COMMA", "SEMI", "COLON", "DOT", "PLUS", "MINUS", "STAR", 
      "DIV", "MOD", "EXCLAMATION", "LOGICAL_OR", "LOGICAL_AND", "EQUALS", 
      "NOT_EQUALS", "LESS", "LESS_OR_EQUALS", "GREATER", "GREATER_OR_EQUALS", 
      "PERCENT_D", "ID", "NUMBER", "STRING", "WS", "COMMENT"
    },
    std::vector<std::string>{
      "DEFAULT_TOKEN_CHANNEL", "HIDDEN"
    },
    std::vector<std::string>{
      "DEFAULT_MODE"
    },
    std::vector<std::string>{
      "", "'type'", "'struct'", "'var'", "'func'", "'if'", "'else'", "'for'", 
      "'return'", "'scan'", "'printf'", "'delete'", "'new'", "'true'", "'false'", 
      "'nil'", "'int'", "'bool'", "'('", "')'", "'{'", "'}'", "'['", "']'", 
      "'='", "','", "';'", "':'", "'.'", "'+'", "'-'", "'*'", "'/'", "'%'", 
      "'!'", "'||'", "'&&'", "'=='", "'!='", "'<'", "'<='", "'>'", "'>='", 
      "'%d'"
    },
    std::vector<std::string>{
      "", "TYPE", "STRUCT", "VAR", "FUNC", "IF", "ELSE", "FOR", "RETURN", 
      "SCAN", "PRINTF", "DELETE", "NEW", "TRUE", "FALSE", "NIL", "INT", 
      "BOOL", "L_PAREN", "R_PAREN", "L_CURLY", "R_CURLY", "L_BRACKET", "R_BRACKET", 
      "ASSIGN", "COMMA", "SEMI", "COLON", "DOT", "PLUS", "MINUS", "STAR", 
      "DIV", "MOD", "EXCLAMATION", "LOGICAL_OR", "LOGICAL_AND", "EQUALS", 
      "NOT_EQUALS", "LESS", "LESS_OR_EQUALS", "GREATER", "GREATER_OR_EQUALS", 
      "PERCENT_D", "ID", "NUMBER", "STRING", "WS", "COMMENT"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,0,48,284,6,-1,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,
  	6,2,7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,
  	7,14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,
  	7,21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,
  	7,28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,2,34,7,34,2,35,
  	7,35,2,36,7,36,2,37,7,37,2,38,7,38,2,39,7,39,2,40,7,40,2,41,7,41,2,42,
  	7,42,2,43,7,43,2,44,7,44,2,45,7,45,2,46,7,46,2,47,7,47,1,0,1,0,1,0,1,
  	0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,2,1,2,1,2,1,3,1,3,1,3,1,3,1,3,
  	1,4,1,4,1,4,1,5,1,5,1,5,1,5,1,5,1,6,1,6,1,6,1,6,1,7,1,7,1,7,1,7,1,7,1,
  	7,1,7,1,8,1,8,1,8,1,8,1,8,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,10,1,10,1,10,
  	1,10,1,10,1,10,1,10,1,11,1,11,1,11,1,11,1,12,1,12,1,12,1,12,1,12,1,13,
  	1,13,1,13,1,13,1,13,1,13,1,14,1,14,1,14,1,14,1,15,1,15,1,15,1,15,1,16,
  	1,16,1,16,1,16,1,16,1,17,1,17,1,18,1,18,1,19,1,19,1,20,1,20,1,21,1,21,
  	1,22,1,22,1,23,1,23,1,24,1,24,1,25,1,25,1,26,1,26,1,27,1,27,1,28,1,28,
  	1,29,1,29,1,30,1,30,1,31,1,31,1,32,1,32,1,33,1,33,1,34,1,34,1,34,1,35,
  	1,35,1,35,1,36,1,36,1,36,1,37,1,37,1,37,1,38,1,38,1,39,1,39,1,39,1,40,
  	1,40,1,41,1,41,1,41,1,42,1,42,1,42,1,43,1,43,5,43,246,8,43,10,43,12,43,
  	249,9,43,1,44,4,44,252,8,44,11,44,12,44,253,1,45,1,45,1,45,1,45,5,45,
  	260,8,45,10,45,12,45,263,9,45,1,45,1,45,1,46,4,46,268,8,46,11,46,12,46,
  	269,1,46,1,46,1,47,1,47,1,47,1,47,5,47,278,8,47,10,47,12,47,281,9,47,
  	1,47,1,47,0,0,48,1,1,3,2,5,3,7,4,9,5,11,6,13,7,15,8,17,9,19,10,21,11,
  	23,12,25,13,27,14,29,15,31,16,33,17,35,18,37,19,39,20,41,21,43,22,45,
  	23,47,24,49,25,51,26,53,27,55,28,57,29,59,30,61,31,63,32,65,33,67,34,
  	69,35,71,36,73,37,75,38,77,39,79,40,81,41,83,42,85,43,87,44,89,45,91,
  	46,93,47,95,48,1,0,6,2,0,65,90,97,122,3,0,48,57,65,90,97,122,1,0,48,57,
  	4,0,10,10,13,13,34,34,92,92,3,0,9,10,13,13,32,32,2,0,10,10,13,13,289,
  	0,1,1,0,0,0,0,3,1,0,0,0,0,5,1,0,0,0,0,7,1,0,0,0,0,9,1,0,0,0,0,11,1,0,
  	0,0,0,13,1,0,0,0,0,15,1,0,0,0,0,17,1,0,0,0,0,19,1,0,0,0,0,21,1,0,0,0,
  	0,23,1,0,0,0,0,25,1,0,0,0,0,27,1,0,0,0,0,29,1,0,0,0,0,31,1,0,0,0,0,33,
  	1,0,0,0,0,35,1,0,0,0,0,37,1,0,0,0,0,39,1,0,0,0,0,41,1,0,0,0,0,43,1,0,
  	0,0,0,45,1,0,0,0,0,47,1,0,0,0,0,49,1,0,0,0,0,51,1,0,0,0,0,53,1,0,0,0,
  	0,55,1,0,0,0,0,57,1,0,0,0,0,59,1,0,0,0,0,61,1,0,0,0,0,63,1,0,0,0,0,65,
  	1,0,0,0,0,67,1,0,0,0,0,69,1,0,0,0,0,71,1,0,0,0,0,73,1,0,0,0,0,75,1,0,
  	0,0,0,77,1,0,0,0,0,79,1,0,0,0,0,81,1,0,0,0,0,83,1,0,0,0,0,85,1,0,0,0,
  	0,87,1,0,0,0,0,89,1,0,0,0,0,91,1,0,0,0,0,93,1,0,0,0,0,95,1,0,0,0,1,97,
  	1,0,0,0,3,102,1,0,0,0,5,109,1,0,0,0,7,113,1,0,0,0,9,118,1,0,0,0,11,121,
  	1,0,0,0,13,126,1,0,0,0,15,130,1,0,0,0,17,137,1,0,0,0,19,142,1,0,0,0,21,
  	149,1,0,0,0,23,156,1,0,0,0,25,160,1,0,0,0,27,165,1,0,0,0,29,171,1,0,0,
  	0,31,175,1,0,0,0,33,179,1,0,0,0,35,184,1,0,0,0,37,186,1,0,0,0,39,188,
  	1,0,0,0,41,190,1,0,0,0,43,192,1,0,0,0,45,194,1,0,0,0,47,196,1,0,0,0,49,
  	198,1,0,0,0,51,200,1,0,0,0,53,202,1,0,0,0,55,204,1,0,0,0,57,206,1,0,0,
  	0,59,208,1,0,0,0,61,210,1,0,0,0,63,212,1,0,0,0,65,214,1,0,0,0,67,216,
  	1,0,0,0,69,218,1,0,0,0,71,221,1,0,0,0,73,224,1,0,0,0,75,227,1,0,0,0,77,
  	230,1,0,0,0,79,232,1,0,0,0,81,235,1,0,0,0,83,237,1,0,0,0,85,240,1,0,0,
  	0,87,243,1,0,0,0,89,251,1,0,0,0,91,255,1,0,0,0,93,267,1,0,0,0,95,273,
  	1,0,0,0,97,98,5,116,0,0,98,99,5,121,0,0,99,100,5,112,0,0,100,101,5,101,
  	0,0,101,2,1,0,0,0,102,103,5,115,0,0,103,104,5,116,0,0,104,105,5,114,0,
  	0,105,106,5,117,0,0,106,107,5,99,0,0,107,108,5,116,0,0,108,4,1,0,0,0,
  	109,110,5,118,0,0,110,111,5,97,0,0,111,112,5,114,0,0,112,6,1,0,0,0,113,
  	114,5,102,0,0,114,115,5,117,0,0,115,116,5,110,0,0,116,117,5,99,0,0,117,
  	8,1,0,0,0,118,119,5,105,0,0,119,120,5,102,0,0,120,10,1,0,0,0,121,122,
  	5,101,0,0,122,123,5,108,0,0,123,124,5,115,0,0,124,125,5,101,0,0,125,12,
  	1,0,0,0,126,127,5,102,0,0,127,128,5,111,0,0,128,129,5,114,0,0,129,14,
  	1,0,0,0,130,131,5,114,0,0,131,132,5,101,0,0,132,133,5,116,0,0,133,134,
  	5,117,0,0,134,135,5,114,0,0,135,136,5,110,0,0,136,16,1,0,0,0,137,138,
  	5,115,0,0,138,139,5,99,0,0,139,140,5,97,0,0,140,141,5,110,0,0,141,18,
  	1,0,0,0,142,143,5,112,0,0,143,144,5,114,0,0,144,145,5,105,0,0,145,146,
  	5,110,0,0,146,147,5,116,0,0,147,148,5,102,0,0,148,20,1,0,0,0,149,150,
  	5,100,0,0,150,151,5,101,0,0,151,152,5,108,0,0,152,153,5,101,0,0,153,154,
  	5,116,0,0,154,155,5,101,0,0,155,22,1,0,0,0,156,157,5,110,0,0,157,158,
  	5,101,0,0,158,159,5,119,0,0,159,24,1,0,0,0,160,161,5,116,0,0,161,162,
  	5,114,0,0,162,163,5,117,0,0,163,164,5,101,0,0,164,26,1,0,0,0,165,166,
  	5,102,0,0,166,167,5,97,0,0,167,168,5,108,0,0,168,169,5,115,0,0,169,170,
  	5,101,0,0,170,28,1,0,0,0,171,172,5,110,0,0,172,173,5,105,0,0,173,174,
  	5,108,0,0,174,30,1,0,0,0,175,176,5,105,0,0,176,177,5,110,0,0,177,178,
  	5,116,0,0,178,32,1,0,0,0,179,180,5,98,0,0,180,181,5,111,0,0,181,182,5,
  	111,0,0,182,183,5,108,0,0,183,34,1,0,0,0,184,185,5,40,0,0,185,36,1,0,
  	0,0,186,187,5,41,0,0,187,38,1,0,0,0,188,189,5,123,0,0,189,40,1,0,0,0,
  	190,191,5,125,0,0,191,42,1,0,0,0,192,193,5,91,0,0,193,44,1,0,0,0,194,
  	195,5,93,0,0,195,46,1,0,0,0,196,197,5,61,0,0,197,48,1,0,0,0,198,199,5,
  	44,0,0,199,50,1,0,0,0,200,201,5,59,0,0,201,52,1,0,0,0,202,203,5,58,0,
  	0,203,54,1,0,0,0,204,205,5,46,0,0,205,56,1,0,0,0,206,207,5,43,0,0,207,
  	58,1,0,0,0,208,209,5,45,0,0,209,60,1,0,0,0,210,211,5,42,0,0,211,62,1,
  	0,0,0,212,213,5,47,0,0,213,64,1,0,0,0,214,215,5,37,0,0,215,66,1,0,0,0,
  	216,217,5,33,0,0,217,68,1,0,0,0,218,219,5,124,0,0,219,220,5,124,0,0,220,
  	70,1,0,0,0,221,222,5,38,0,0,222,223,5,38,0,0,223,72,1,0,0,0,224,225,5,
  	61,0,0,225,226,5,61,0,0,226,74,1,0,0,0,227,228,5,33,0,0,228,229,5,61,
  	0,0,229,76,1,0,0,0,230,231,5,60,0,0,231,78,1,0,0,0,232,233,5,60,0,0,233,
  	234,5,61,0,0,234,80,1,0,0,0,235,236,5,62,0,0,236,82,1,0,0,0,237,238,5,
  	62,0,0,238,239,5,61,0,0,239,84,1,0,0,0,240,241,5,37,0,0,241,242,5,100,
  	0,0,242,86,1,0,0,0,243,247,7,0,0,0,244,246,7,1,0,0,245,244,1,0,0,0,246,
  	249,1,0,0,0,247,245,1,0,0,0,247,248,1,0,0,0,248,88,1,0,0,0,249,247,1,
  	0,0,0,250,252,7,2,0,0,251,250,1,0,0,0,252,253,1,0,0,0,253,251,1,0,0,0,
  	253,254,1,0,0,0,254,90,1,0,0,0,255,261,5,34,0,0,256,260,8,3,0,0,257,258,
  	5,92,0,0,258,260,9,0,0,0,259,256,1,0,0,0,259,257,1,0,0,0,260,263,1,0,
  	0,0,261,259,1,0,0,0,261,262,1,0,0,0,262,264,1,0,0,0,263,261,1,0,0,0,264,
  	265,5,34,0,0,265,92,1,0,0,0,266,268,7,4,0,0,267,266,1,0,0,0,268,269,1,
  	0,0,0,269,267,1,0,0,0,269,270,1,0,0,0,270,271,1,0,0,0,271,272,6,46,0,
  	0,272,94,1,0,0,0,273,274,5,47,0,0,274,275,5,47,0,0,275,279,1,0,0,0,276,
  	278,8,5,0,0,277,276,1,0,0,0,278,281,1,0,0,0,279,277,1,0,0,0,279,280,1,
  	0,0,0,280,282,1,0,0,0,281,279,1,0,0,0,282,283,6,47,0,0,283,96,1,0,0,0,
  	7,0,247,253,259,261,269,279,1,6,0,0
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  golitelexerLexerStaticData = staticData.release();
}

}

GoliteLexer::GoliteLexer(CharStream *input) : Lexer(input) {
  GoliteLexer::initialize();
  _interpreter = new atn::LexerATNSimulator(this, *golitelexerLexerStaticData->atn, golitelexerLexerStaticData->decisionToDFA, golitelexerLexerStaticData->sharedContextCache);
}

GoliteLexer::~GoliteLexer() {
  delete _interpreter;
}

std::string GoliteLexer::getGrammarFileName() const {
  return "GoliteLexer.g4";
}

const std::vector<std::string>& GoliteLexer::getRuleNames() const {
  return golitelexerLexerStaticData->ruleNames;
}

const std::vector<std::string>& GoliteLexer::getChannelNames() const {
  return golitelexerLexerStaticData->channelNames;
}

const std::vector<std::string>& GoliteLexer::getModeNames() const {
  return golitelexerLexerStaticData->modeNames;
}

const dfa::Vocabulary& GoliteLexer::getVocabulary() const {
  return golitelexerLexerStaticData->vocabulary;
}

antlr4::atn::SerializedATNView GoliteLexer::getSerializedATN() const {
  return golitelexerLexerStaticData->serializedATN;
}

const atn::ATN& GoliteLexer::getATN() const {
  return *golitelexerLexerStaticData->atn;
}




void GoliteLexer::initialize() {
  ::antlr4::internal::call_once(golitelexerLexerOnceFlag, golitelexerLexerInitialize);
}

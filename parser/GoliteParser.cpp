
// Generated from GoliteParser.g4 by ANTLR 4.11.1


#include "GoliteParserListener.h"
#include "GoliteParserVisitor.h"

#include "GoliteParser.h"


using namespace antlrcpp;
using namespace parser;

using namespace antlr4;

namespace {

struct GoliteParserStaticData final {
  GoliteParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  GoliteParserStaticData(const GoliteParserStaticData&) = delete;
  GoliteParserStaticData(GoliteParserStaticData&&) = delete;
  GoliteParserStaticData& operator=(const GoliteParserStaticData&) = delete;
  GoliteParserStaticData& operator=(GoliteParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag goliteparserParserOnceFlag;
GoliteParserStaticData *goliteparserParserStaticData = nullptr;

void goliteparserParserInitialize() {
  assert(goliteparserParserStaticData == nullptr);
  auto staticData = std::make_unique<GoliteParserStaticData>(
    std::vector<std::string>{
      "program", "types", "typeDeclaration", "fields", "decl", "type", "declarations", 
      "declaration", "ids", "functions", "function", "parameters", "returnType", 
      "statements", "statement", "invocation", "block", "assignment", "print", 
      "scan", "delete", "conditional", "loop", "return", "expression", "boolExpression", 
      "boolTerm", "equalTerm", "relationTerm", "arithmeticExpression", "simpleTerm", 
      "term", "unaryTerm", "selectorTerm", "factor", "arguments", "lvalue"
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
  	4,1,48,336,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,7,
  	28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,2,34,7,34,2,35,7,
  	35,2,36,7,36,1,0,1,0,1,0,1,0,1,0,1,1,5,1,81,8,1,10,1,12,1,84,9,1,1,2,
  	1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,3,1,3,1,3,1,3,1,3,5,3,99,8,3,10,3,12,3,
  	102,9,3,1,4,1,4,1,4,1,5,1,5,1,5,1,5,3,5,111,8,5,1,6,5,6,114,8,6,10,6,
  	12,6,117,9,6,1,7,1,7,1,7,1,7,1,7,1,8,1,8,1,8,5,8,127,8,8,10,8,12,8,130,
  	9,8,1,9,5,9,133,8,9,10,9,12,9,136,9,9,1,10,1,10,1,10,1,10,3,10,142,8,
  	10,1,10,1,10,1,10,1,10,1,10,1,11,1,11,1,11,1,11,5,11,153,8,11,10,11,12,
  	11,156,9,11,3,11,158,8,11,1,11,1,11,1,12,1,12,1,13,5,13,165,8,13,10,13,
  	12,13,168,9,13,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,3,14,179,
  	8,14,1,15,1,15,1,15,1,15,1,16,1,16,1,16,1,16,1,17,1,17,1,17,1,17,1,17,
  	1,18,1,18,1,18,1,18,1,18,5,18,199,8,18,10,18,12,18,202,9,18,1,18,1,18,
  	1,18,1,19,1,19,1,19,1,19,1,20,1,20,1,20,1,20,1,21,1,21,1,21,1,21,1,21,
  	1,21,1,21,3,21,222,8,21,1,22,1,22,1,22,1,22,1,22,1,22,1,23,1,23,3,23,
  	232,8,23,1,23,1,23,1,24,1,24,3,24,238,8,24,1,25,1,25,1,25,5,25,243,8,
  	25,10,25,12,25,246,9,25,1,26,1,26,1,26,5,26,251,8,26,10,26,12,26,254,
  	9,26,1,27,1,27,1,27,5,27,259,8,27,10,27,12,27,262,9,27,1,28,1,28,1,28,
  	5,28,267,8,28,10,28,12,28,270,9,28,1,29,1,29,1,30,1,30,1,30,5,30,277,
  	8,30,10,30,12,30,280,9,30,1,31,1,31,1,31,5,31,285,8,31,10,31,12,31,288,
  	9,31,1,32,1,32,1,32,1,32,1,32,3,32,295,8,32,1,33,1,33,1,33,5,33,300,8,
  	33,10,33,12,33,303,9,33,1,34,1,34,1,34,1,34,1,34,1,34,3,34,311,8,34,1,
  	34,1,34,1,34,1,34,1,34,1,34,3,34,319,8,34,1,35,1,35,1,35,1,35,5,35,325,
  	8,35,10,35,12,35,328,9,35,3,35,330,8,35,1,35,1,35,1,36,1,36,1,36,0,0,
  	37,0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,
  	48,50,52,54,56,58,60,62,64,66,68,70,72,0,4,1,0,37,38,1,0,39,42,1,0,29,
  	30,1,0,31,32,339,0,74,1,0,0,0,2,82,1,0,0,0,4,85,1,0,0,0,6,93,1,0,0,0,
  	8,103,1,0,0,0,10,110,1,0,0,0,12,115,1,0,0,0,14,118,1,0,0,0,16,123,1,0,
  	0,0,18,134,1,0,0,0,20,137,1,0,0,0,22,148,1,0,0,0,24,161,1,0,0,0,26,166,
  	1,0,0,0,28,178,1,0,0,0,30,180,1,0,0,0,32,184,1,0,0,0,34,188,1,0,0,0,36,
  	193,1,0,0,0,38,206,1,0,0,0,40,210,1,0,0,0,42,214,1,0,0,0,44,223,1,0,0,
  	0,46,229,1,0,0,0,48,237,1,0,0,0,50,239,1,0,0,0,52,247,1,0,0,0,54,255,
  	1,0,0,0,56,263,1,0,0,0,58,271,1,0,0,0,60,273,1,0,0,0,62,281,1,0,0,0,64,
  	294,1,0,0,0,66,296,1,0,0,0,68,318,1,0,0,0,70,320,1,0,0,0,72,333,1,0,0,
  	0,74,75,3,2,1,0,75,76,3,12,6,0,76,77,3,18,9,0,77,78,5,0,0,1,78,1,1,0,
  	0,0,79,81,3,4,2,0,80,79,1,0,0,0,81,84,1,0,0,0,82,80,1,0,0,0,82,83,1,0,
  	0,0,83,3,1,0,0,0,84,82,1,0,0,0,85,86,5,1,0,0,86,87,5,44,0,0,87,88,5,2,
  	0,0,88,89,5,20,0,0,89,90,3,6,3,0,90,91,5,21,0,0,91,92,5,26,0,0,92,5,1,
  	0,0,0,93,94,3,8,4,0,94,100,5,26,0,0,95,96,3,8,4,0,96,97,5,26,0,0,97,99,
  	1,0,0,0,98,95,1,0,0,0,99,102,1,0,0,0,100,98,1,0,0,0,100,101,1,0,0,0,101,
  	7,1,0,0,0,102,100,1,0,0,0,103,104,5,44,0,0,104,105,3,10,5,0,105,9,1,0,
  	0,0,106,111,5,16,0,0,107,111,5,17,0,0,108,109,5,31,0,0,109,111,5,44,0,
  	0,110,106,1,0,0,0,110,107,1,0,0,0,110,108,1,0,0,0,111,11,1,0,0,0,112,
  	114,3,14,7,0,113,112,1,0,0,0,114,117,1,0,0,0,115,113,1,0,0,0,115,116,
  	1,0,0,0,116,13,1,0,0,0,117,115,1,0,0,0,118,119,5,3,0,0,119,120,3,16,8,
  	0,120,121,3,10,5,0,121,122,5,26,0,0,122,15,1,0,0,0,123,128,5,44,0,0,124,
  	125,5,25,0,0,125,127,5,44,0,0,126,124,1,0,0,0,127,130,1,0,0,0,128,126,
  	1,0,0,0,128,129,1,0,0,0,129,17,1,0,0,0,130,128,1,0,0,0,131,133,3,20,10,
  	0,132,131,1,0,0,0,133,136,1,0,0,0,134,132,1,0,0,0,134,135,1,0,0,0,135,
  	19,1,0,0,0,136,134,1,0,0,0,137,138,5,4,0,0,138,139,5,44,0,0,139,141,3,
  	22,11,0,140,142,3,24,12,0,141,140,1,0,0,0,141,142,1,0,0,0,142,143,1,0,
  	0,0,143,144,5,20,0,0,144,145,3,12,6,0,145,146,3,26,13,0,146,147,5,21,
  	0,0,147,21,1,0,0,0,148,157,5,18,0,0,149,154,3,8,4,0,150,151,5,25,0,0,
  	151,153,3,8,4,0,152,150,1,0,0,0,153,156,1,0,0,0,154,152,1,0,0,0,154,155,
  	1,0,0,0,155,158,1,0,0,0,156,154,1,0,0,0,157,149,1,0,0,0,157,158,1,0,0,
  	0,158,159,1,0,0,0,159,160,5,19,0,0,160,23,1,0,0,0,161,162,3,10,5,0,162,
  	25,1,0,0,0,163,165,3,28,14,0,164,163,1,0,0,0,165,168,1,0,0,0,166,164,
  	1,0,0,0,166,167,1,0,0,0,167,27,1,0,0,0,168,166,1,0,0,0,169,179,3,34,17,
  	0,170,179,3,36,18,0,171,179,3,38,19,0,172,179,3,40,20,0,173,179,3,42,
  	21,0,174,179,3,44,22,0,175,179,3,46,23,0,176,179,3,32,16,0,177,179,3,
  	30,15,0,178,169,1,0,0,0,178,170,1,0,0,0,178,171,1,0,0,0,178,172,1,0,0,
  	0,178,173,1,0,0,0,178,174,1,0,0,0,178,175,1,0,0,0,178,176,1,0,0,0,178,
  	177,1,0,0,0,179,29,1,0,0,0,180,181,5,44,0,0,181,182,3,70,35,0,182,183,
  	5,26,0,0,183,31,1,0,0,0,184,185,5,20,0,0,185,186,3,26,13,0,186,187,5,
  	21,0,0,187,33,1,0,0,0,188,189,3,72,36,0,189,190,5,24,0,0,190,191,3,48,
  	24,0,191,192,5,26,0,0,192,35,1,0,0,0,193,194,5,10,0,0,194,195,5,18,0,
  	0,195,200,5,46,0,0,196,197,5,25,0,0,197,199,3,48,24,0,198,196,1,0,0,0,
  	199,202,1,0,0,0,200,198,1,0,0,0,200,201,1,0,0,0,201,203,1,0,0,0,202,200,
  	1,0,0,0,203,204,5,19,0,0,204,205,5,26,0,0,205,37,1,0,0,0,206,207,5,9,
  	0,0,207,208,3,72,36,0,208,209,5,26,0,0,209,39,1,0,0,0,210,211,5,11,0,
  	0,211,212,3,48,24,0,212,213,5,26,0,0,213,41,1,0,0,0,214,215,5,5,0,0,215,
  	216,5,18,0,0,216,217,3,48,24,0,217,218,5,19,0,0,218,221,3,32,16,0,219,
  	220,5,6,0,0,220,222,3,32,16,0,221,219,1,0,0,0,221,222,1,0,0,0,222,43,
  	1,0,0,0,223,224,5,7,0,0,224,225,5,18,0,0,225,226,3,48,24,0,226,227,5,
  	19,0,0,227,228,3,32,16,0,228,45,1,0,0,0,229,231,5,8,0,0,230,232,3,48,
  	24,0,231,230,1,0,0,0,231,232,1,0,0,0,232,233,1,0,0,0,233,234,5,26,0,0,
  	234,47,1,0,0,0,235,238,3,58,29,0,236,238,3,50,25,0,237,235,1,0,0,0,237,
  	236,1,0,0,0,238,49,1,0,0,0,239,244,3,52,26,0,240,241,5,35,0,0,241,243,
  	3,52,26,0,242,240,1,0,0,0,243,246,1,0,0,0,244,242,1,0,0,0,244,245,1,0,
  	0,0,245,51,1,0,0,0,246,244,1,0,0,0,247,252,3,54,27,0,248,249,5,36,0,0,
  	249,251,3,54,27,0,250,248,1,0,0,0,251,254,1,0,0,0,252,250,1,0,0,0,252,
  	253,1,0,0,0,253,53,1,0,0,0,254,252,1,0,0,0,255,260,3,56,28,0,256,257,
  	7,0,0,0,257,259,3,56,28,0,258,256,1,0,0,0,259,262,1,0,0,0,260,258,1,0,
  	0,0,260,261,1,0,0,0,261,55,1,0,0,0,262,260,1,0,0,0,263,268,3,58,29,0,
  	264,265,7,1,0,0,265,267,3,58,29,0,266,264,1,0,0,0,267,270,1,0,0,0,268,
  	266,1,0,0,0,268,269,1,0,0,0,269,57,1,0,0,0,270,268,1,0,0,0,271,272,3,
  	60,30,0,272,59,1,0,0,0,273,278,3,62,31,0,274,275,7,2,0,0,275,277,3,62,
  	31,0,276,274,1,0,0,0,277,280,1,0,0,0,278,276,1,0,0,0,278,279,1,0,0,0,
  	279,61,1,0,0,0,280,278,1,0,0,0,281,286,3,64,32,0,282,283,7,3,0,0,283,
  	285,3,64,32,0,284,282,1,0,0,0,285,288,1,0,0,0,286,284,1,0,0,0,286,287,
  	1,0,0,0,287,63,1,0,0,0,288,286,1,0,0,0,289,290,5,34,0,0,290,295,3,64,
  	32,0,291,292,5,30,0,0,292,295,3,64,32,0,293,295,3,66,33,0,294,289,1,0,
  	0,0,294,291,1,0,0,0,294,293,1,0,0,0,295,65,1,0,0,0,296,301,3,68,34,0,
  	297,298,5,28,0,0,298,300,5,44,0,0,299,297,1,0,0,0,300,303,1,0,0,0,301,
  	299,1,0,0,0,301,302,1,0,0,0,302,67,1,0,0,0,303,301,1,0,0,0,304,305,5,
  	18,0,0,305,306,3,48,24,0,306,307,5,19,0,0,307,319,1,0,0,0,308,310,5,44,
  	0,0,309,311,3,70,35,0,310,309,1,0,0,0,310,311,1,0,0,0,311,319,1,0,0,0,
  	312,319,5,45,0,0,313,314,5,12,0,0,314,319,5,44,0,0,315,319,5,13,0,0,316,
  	319,5,14,0,0,317,319,5,15,0,0,318,304,1,0,0,0,318,308,1,0,0,0,318,312,
  	1,0,0,0,318,313,1,0,0,0,318,315,1,0,0,0,318,316,1,0,0,0,318,317,1,0,0,
  	0,319,69,1,0,0,0,320,329,5,18,0,0,321,326,3,48,24,0,322,323,5,25,0,0,
  	323,325,3,48,24,0,324,322,1,0,0,0,325,328,1,0,0,0,326,324,1,0,0,0,326,
  	327,1,0,0,0,327,330,1,0,0,0,328,326,1,0,0,0,329,321,1,0,0,0,329,330,1,
  	0,0,0,330,331,1,0,0,0,331,332,5,19,0,0,332,71,1,0,0,0,333,334,3,66,33,
  	0,334,73,1,0,0,0,27,82,100,110,115,128,134,141,154,157,166,178,200,221,
  	231,237,244,252,260,268,278,286,294,301,310,318,326,329
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  goliteparserParserStaticData = staticData.release();
}

}

GoliteParser::GoliteParser(TokenStream *input) : GoliteParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

GoliteParser::GoliteParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  GoliteParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *goliteparserParserStaticData->atn, goliteparserParserStaticData->decisionToDFA, goliteparserParserStaticData->sharedContextCache, options);
}

GoliteParser::~GoliteParser() {
  delete _interpreter;
}

const atn::ATN& GoliteParser::getATN() const {
  return *goliteparserParserStaticData->atn;
}

std::string GoliteParser::getGrammarFileName() const {
  return "GoliteParser.g4";
}

const std::vector<std::string>& GoliteParser::getRuleNames() const {
  return goliteparserParserStaticData->ruleNames;
}

const dfa::Vocabulary& GoliteParser::getVocabulary() const {
  return goliteparserParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView GoliteParser::getSerializedATN() const {
  return goliteparserParserStaticData->serializedATN;
}


//----------------- ProgramContext ------------------------------------------------------------------

GoliteParser::ProgramContext::ProgramContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

GoliteParser::TypesContext* GoliteParser::ProgramContext::types() {
  return getRuleContext<GoliteParser::TypesContext>(0);
}

GoliteParser::DeclarationsContext* GoliteParser::ProgramContext::declarations() {
  return getRuleContext<GoliteParser::DeclarationsContext>(0);
}

GoliteParser::FunctionsContext* GoliteParser::ProgramContext::functions() {
  return getRuleContext<GoliteParser::FunctionsContext>(0);
}

tree::TerminalNode* GoliteParser::ProgramContext::EOF() {
  return getToken(GoliteParser::EOF, 0);
}


size_t GoliteParser::ProgramContext::getRuleIndex() const {
  return GoliteParser::RuleProgram;
}

void GoliteParser::ProgramContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GoliteParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProgram(this);
}

void GoliteParser::ProgramContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GoliteParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProgram(this);
}


std::any GoliteParser::ProgramContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GoliteParserVisitor*>(visitor))
    return parserVisitor->visitProgram(this);
  else
    return visitor->visitChildren(this);
}

GoliteParser::ProgramContext* GoliteParser::program() {
  ProgramContext *_localctx = _tracker.createInstance<ProgramContext>(_ctx, getState());
  enterRule(_localctx, 0, GoliteParser::RuleProgram);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(74);
    types();
    setState(75);
    declarations();
    setState(76);
    functions();
    setState(77);
    match(GoliteParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TypesContext ------------------------------------------------------------------

GoliteParser::TypesContext::TypesContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<GoliteParser::TypeDeclarationContext *> GoliteParser::TypesContext::typeDeclaration() {
  return getRuleContexts<GoliteParser::TypeDeclarationContext>();
}

GoliteParser::TypeDeclarationContext* GoliteParser::TypesContext::typeDeclaration(size_t i) {
  return getRuleContext<GoliteParser::TypeDeclarationContext>(i);
}


size_t GoliteParser::TypesContext::getRuleIndex() const {
  return GoliteParser::RuleTypes;
}

void GoliteParser::TypesContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GoliteParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTypes(this);
}

void GoliteParser::TypesContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GoliteParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTypes(this);
}


std::any GoliteParser::TypesContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GoliteParserVisitor*>(visitor))
    return parserVisitor->visitTypes(this);
  else
    return visitor->visitChildren(this);
}

GoliteParser::TypesContext* GoliteParser::types() {
  TypesContext *_localctx = _tracker.createInstance<TypesContext>(_ctx, getState());
  enterRule(_localctx, 2, GoliteParser::RuleTypes);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(82);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == GoliteParser::TYPE) {
      setState(79);
      typeDeclaration();
      setState(84);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TypeDeclarationContext ------------------------------------------------------------------

GoliteParser::TypeDeclarationContext::TypeDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* GoliteParser::TypeDeclarationContext::TYPE() {
  return getToken(GoliteParser::TYPE, 0);
}

tree::TerminalNode* GoliteParser::TypeDeclarationContext::ID() {
  return getToken(GoliteParser::ID, 0);
}

tree::TerminalNode* GoliteParser::TypeDeclarationContext::STRUCT() {
  return getToken(GoliteParser::STRUCT, 0);
}

tree::TerminalNode* GoliteParser::TypeDeclarationContext::L_CURLY() {
  return getToken(GoliteParser::L_CURLY, 0);
}

GoliteParser::FieldsContext* GoliteParser::TypeDeclarationContext::fields() {
  return getRuleContext<GoliteParser::FieldsContext>(0);
}

tree::TerminalNode* GoliteParser::TypeDeclarationContext::R_CURLY() {
  return getToken(GoliteParser::R_CURLY, 0);
}

tree::TerminalNode* GoliteParser::TypeDeclarationContext::SEMI() {
  return getToken(GoliteParser::SEMI, 0);
}


size_t GoliteParser::TypeDeclarationContext::getRuleIndex() const {
  return GoliteParser::RuleTypeDeclaration;
}

void GoliteParser::TypeDeclarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GoliteParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTypeDeclaration(this);
}

void GoliteParser::TypeDeclarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GoliteParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTypeDeclaration(this);
}


std::any GoliteParser::TypeDeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GoliteParserVisitor*>(visitor))
    return parserVisitor->visitTypeDeclaration(this);
  else
    return visitor->visitChildren(this);
}

GoliteParser::TypeDeclarationContext* GoliteParser::typeDeclaration() {
  TypeDeclarationContext *_localctx = _tracker.createInstance<TypeDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 4, GoliteParser::RuleTypeDeclaration);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(85);
    match(GoliteParser::TYPE);
    setState(86);
    match(GoliteParser::ID);
    setState(87);
    match(GoliteParser::STRUCT);
    setState(88);
    match(GoliteParser::L_CURLY);
    setState(89);
    fields();
    setState(90);
    match(GoliteParser::R_CURLY);
    setState(91);
    match(GoliteParser::SEMI);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FieldsContext ------------------------------------------------------------------

GoliteParser::FieldsContext::FieldsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<GoliteParser::DeclContext *> GoliteParser::FieldsContext::decl() {
  return getRuleContexts<GoliteParser::DeclContext>();
}

GoliteParser::DeclContext* GoliteParser::FieldsContext::decl(size_t i) {
  return getRuleContext<GoliteParser::DeclContext>(i);
}

std::vector<tree::TerminalNode *> GoliteParser::FieldsContext::SEMI() {
  return getTokens(GoliteParser::SEMI);
}

tree::TerminalNode* GoliteParser::FieldsContext::SEMI(size_t i) {
  return getToken(GoliteParser::SEMI, i);
}


size_t GoliteParser::FieldsContext::getRuleIndex() const {
  return GoliteParser::RuleFields;
}

void GoliteParser::FieldsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GoliteParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFields(this);
}

void GoliteParser::FieldsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GoliteParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFields(this);
}


std::any GoliteParser::FieldsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GoliteParserVisitor*>(visitor))
    return parserVisitor->visitFields(this);
  else
    return visitor->visitChildren(this);
}

GoliteParser::FieldsContext* GoliteParser::fields() {
  FieldsContext *_localctx = _tracker.createInstance<FieldsContext>(_ctx, getState());
  enterRule(_localctx, 6, GoliteParser::RuleFields);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(93);
    decl();
    setState(94);
    match(GoliteParser::SEMI);
    setState(100);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == GoliteParser::ID) {
      setState(95);
      decl();
      setState(96);
      match(GoliteParser::SEMI);
      setState(102);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DeclContext ------------------------------------------------------------------

GoliteParser::DeclContext::DeclContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* GoliteParser::DeclContext::ID() {
  return getToken(GoliteParser::ID, 0);
}

GoliteParser::TypeContext* GoliteParser::DeclContext::type() {
  return getRuleContext<GoliteParser::TypeContext>(0);
}


size_t GoliteParser::DeclContext::getRuleIndex() const {
  return GoliteParser::RuleDecl;
}

void GoliteParser::DeclContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GoliteParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDecl(this);
}

void GoliteParser::DeclContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GoliteParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDecl(this);
}


std::any GoliteParser::DeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GoliteParserVisitor*>(visitor))
    return parserVisitor->visitDecl(this);
  else
    return visitor->visitChildren(this);
}

GoliteParser::DeclContext* GoliteParser::decl() {
  DeclContext *_localctx = _tracker.createInstance<DeclContext>(_ctx, getState());
  enterRule(_localctx, 8, GoliteParser::RuleDecl);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(103);
    match(GoliteParser::ID);
    setState(104);
    type();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TypeContext ------------------------------------------------------------------

GoliteParser::TypeContext::TypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* GoliteParser::TypeContext::INT() {
  return getToken(GoliteParser::INT, 0);
}

tree::TerminalNode* GoliteParser::TypeContext::BOOL() {
  return getToken(GoliteParser::BOOL, 0);
}

tree::TerminalNode* GoliteParser::TypeContext::STAR() {
  return getToken(GoliteParser::STAR, 0);
}

tree::TerminalNode* GoliteParser::TypeContext::ID() {
  return getToken(GoliteParser::ID, 0);
}


size_t GoliteParser::TypeContext::getRuleIndex() const {
  return GoliteParser::RuleType;
}

void GoliteParser::TypeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GoliteParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterType(this);
}

void GoliteParser::TypeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GoliteParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitType(this);
}


std::any GoliteParser::TypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GoliteParserVisitor*>(visitor))
    return parserVisitor->visitType(this);
  else
    return visitor->visitChildren(this);
}

GoliteParser::TypeContext* GoliteParser::type() {
  TypeContext *_localctx = _tracker.createInstance<TypeContext>(_ctx, getState());
  enterRule(_localctx, 10, GoliteParser::RuleType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(110);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case GoliteParser::INT: {
        enterOuterAlt(_localctx, 1);
        setState(106);
        match(GoliteParser::INT);
        break;
      }

      case GoliteParser::BOOL: {
        enterOuterAlt(_localctx, 2);
        setState(107);
        match(GoliteParser::BOOL);
        break;
      }

      case GoliteParser::STAR: {
        enterOuterAlt(_localctx, 3);
        setState(108);
        match(GoliteParser::STAR);
        setState(109);
        match(GoliteParser::ID);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DeclarationsContext ------------------------------------------------------------------

GoliteParser::DeclarationsContext::DeclarationsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<GoliteParser::DeclarationContext *> GoliteParser::DeclarationsContext::declaration() {
  return getRuleContexts<GoliteParser::DeclarationContext>();
}

GoliteParser::DeclarationContext* GoliteParser::DeclarationsContext::declaration(size_t i) {
  return getRuleContext<GoliteParser::DeclarationContext>(i);
}


size_t GoliteParser::DeclarationsContext::getRuleIndex() const {
  return GoliteParser::RuleDeclarations;
}

void GoliteParser::DeclarationsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GoliteParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDeclarations(this);
}

void GoliteParser::DeclarationsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GoliteParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDeclarations(this);
}


std::any GoliteParser::DeclarationsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GoliteParserVisitor*>(visitor))
    return parserVisitor->visitDeclarations(this);
  else
    return visitor->visitChildren(this);
}

GoliteParser::DeclarationsContext* GoliteParser::declarations() {
  DeclarationsContext *_localctx = _tracker.createInstance<DeclarationsContext>(_ctx, getState());
  enterRule(_localctx, 12, GoliteParser::RuleDeclarations);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(115);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == GoliteParser::VAR) {
      setState(112);
      declaration();
      setState(117);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DeclarationContext ------------------------------------------------------------------

GoliteParser::DeclarationContext::DeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* GoliteParser::DeclarationContext::VAR() {
  return getToken(GoliteParser::VAR, 0);
}

GoliteParser::IdsContext* GoliteParser::DeclarationContext::ids() {
  return getRuleContext<GoliteParser::IdsContext>(0);
}

GoliteParser::TypeContext* GoliteParser::DeclarationContext::type() {
  return getRuleContext<GoliteParser::TypeContext>(0);
}

tree::TerminalNode* GoliteParser::DeclarationContext::SEMI() {
  return getToken(GoliteParser::SEMI, 0);
}


size_t GoliteParser::DeclarationContext::getRuleIndex() const {
  return GoliteParser::RuleDeclaration;
}

void GoliteParser::DeclarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GoliteParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDeclaration(this);
}

void GoliteParser::DeclarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GoliteParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDeclaration(this);
}


std::any GoliteParser::DeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GoliteParserVisitor*>(visitor))
    return parserVisitor->visitDeclaration(this);
  else
    return visitor->visitChildren(this);
}

GoliteParser::DeclarationContext* GoliteParser::declaration() {
  DeclarationContext *_localctx = _tracker.createInstance<DeclarationContext>(_ctx, getState());
  enterRule(_localctx, 14, GoliteParser::RuleDeclaration);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(118);
    match(GoliteParser::VAR);
    setState(119);
    ids();
    setState(120);
    type();
    setState(121);
    match(GoliteParser::SEMI);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IdsContext ------------------------------------------------------------------

GoliteParser::IdsContext::IdsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> GoliteParser::IdsContext::ID() {
  return getTokens(GoliteParser::ID);
}

tree::TerminalNode* GoliteParser::IdsContext::ID(size_t i) {
  return getToken(GoliteParser::ID, i);
}

std::vector<tree::TerminalNode *> GoliteParser::IdsContext::COMMA() {
  return getTokens(GoliteParser::COMMA);
}

tree::TerminalNode* GoliteParser::IdsContext::COMMA(size_t i) {
  return getToken(GoliteParser::COMMA, i);
}


size_t GoliteParser::IdsContext::getRuleIndex() const {
  return GoliteParser::RuleIds;
}

void GoliteParser::IdsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GoliteParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIds(this);
}

void GoliteParser::IdsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GoliteParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIds(this);
}


std::any GoliteParser::IdsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GoliteParserVisitor*>(visitor))
    return parserVisitor->visitIds(this);
  else
    return visitor->visitChildren(this);
}

GoliteParser::IdsContext* GoliteParser::ids() {
  IdsContext *_localctx = _tracker.createInstance<IdsContext>(_ctx, getState());
  enterRule(_localctx, 16, GoliteParser::RuleIds);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(123);
    match(GoliteParser::ID);
    setState(128);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == GoliteParser::COMMA) {
      setState(124);
      match(GoliteParser::COMMA);
      setState(125);
      match(GoliteParser::ID);
      setState(130);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionsContext ------------------------------------------------------------------

GoliteParser::FunctionsContext::FunctionsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<GoliteParser::FunctionContext *> GoliteParser::FunctionsContext::function() {
  return getRuleContexts<GoliteParser::FunctionContext>();
}

GoliteParser::FunctionContext* GoliteParser::FunctionsContext::function(size_t i) {
  return getRuleContext<GoliteParser::FunctionContext>(i);
}


size_t GoliteParser::FunctionsContext::getRuleIndex() const {
  return GoliteParser::RuleFunctions;
}

void GoliteParser::FunctionsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GoliteParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunctions(this);
}

void GoliteParser::FunctionsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GoliteParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunctions(this);
}


std::any GoliteParser::FunctionsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GoliteParserVisitor*>(visitor))
    return parserVisitor->visitFunctions(this);
  else
    return visitor->visitChildren(this);
}

GoliteParser::FunctionsContext* GoliteParser::functions() {
  FunctionsContext *_localctx = _tracker.createInstance<FunctionsContext>(_ctx, getState());
  enterRule(_localctx, 18, GoliteParser::RuleFunctions);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(134);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == GoliteParser::FUNC) {
      setState(131);
      function();
      setState(136);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionContext ------------------------------------------------------------------

GoliteParser::FunctionContext::FunctionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* GoliteParser::FunctionContext::FUNC() {
  return getToken(GoliteParser::FUNC, 0);
}

tree::TerminalNode* GoliteParser::FunctionContext::ID() {
  return getToken(GoliteParser::ID, 0);
}

GoliteParser::ParametersContext* GoliteParser::FunctionContext::parameters() {
  return getRuleContext<GoliteParser::ParametersContext>(0);
}

tree::TerminalNode* GoliteParser::FunctionContext::L_CURLY() {
  return getToken(GoliteParser::L_CURLY, 0);
}

GoliteParser::DeclarationsContext* GoliteParser::FunctionContext::declarations() {
  return getRuleContext<GoliteParser::DeclarationsContext>(0);
}

GoliteParser::StatementsContext* GoliteParser::FunctionContext::statements() {
  return getRuleContext<GoliteParser::StatementsContext>(0);
}

tree::TerminalNode* GoliteParser::FunctionContext::R_CURLY() {
  return getToken(GoliteParser::R_CURLY, 0);
}

GoliteParser::ReturnTypeContext* GoliteParser::FunctionContext::returnType() {
  return getRuleContext<GoliteParser::ReturnTypeContext>(0);
}


size_t GoliteParser::FunctionContext::getRuleIndex() const {
  return GoliteParser::RuleFunction;
}

void GoliteParser::FunctionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GoliteParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunction(this);
}

void GoliteParser::FunctionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GoliteParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunction(this);
}


std::any GoliteParser::FunctionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GoliteParserVisitor*>(visitor))
    return parserVisitor->visitFunction(this);
  else
    return visitor->visitChildren(this);
}

GoliteParser::FunctionContext* GoliteParser::function() {
  FunctionContext *_localctx = _tracker.createInstance<FunctionContext>(_ctx, getState());
  enterRule(_localctx, 20, GoliteParser::RuleFunction);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(137);
    match(GoliteParser::FUNC);
    setState(138);
    match(GoliteParser::ID);
    setState(139);
    parameters();
    setState(141);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 2147680256) != 0) {
      setState(140);
      returnType();
    }
    setState(143);
    match(GoliteParser::L_CURLY);
    setState(144);
    declarations();
    setState(145);
    statements();
    setState(146);
    match(GoliteParser::R_CURLY);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ParametersContext ------------------------------------------------------------------

GoliteParser::ParametersContext::ParametersContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* GoliteParser::ParametersContext::L_PAREN() {
  return getToken(GoliteParser::L_PAREN, 0);
}

tree::TerminalNode* GoliteParser::ParametersContext::R_PAREN() {
  return getToken(GoliteParser::R_PAREN, 0);
}

std::vector<GoliteParser::DeclContext *> GoliteParser::ParametersContext::decl() {
  return getRuleContexts<GoliteParser::DeclContext>();
}

GoliteParser::DeclContext* GoliteParser::ParametersContext::decl(size_t i) {
  return getRuleContext<GoliteParser::DeclContext>(i);
}

std::vector<tree::TerminalNode *> GoliteParser::ParametersContext::COMMA() {
  return getTokens(GoliteParser::COMMA);
}

tree::TerminalNode* GoliteParser::ParametersContext::COMMA(size_t i) {
  return getToken(GoliteParser::COMMA, i);
}


size_t GoliteParser::ParametersContext::getRuleIndex() const {
  return GoliteParser::RuleParameters;
}

void GoliteParser::ParametersContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GoliteParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterParameters(this);
}

void GoliteParser::ParametersContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GoliteParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitParameters(this);
}


std::any GoliteParser::ParametersContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GoliteParserVisitor*>(visitor))
    return parserVisitor->visitParameters(this);
  else
    return visitor->visitChildren(this);
}

GoliteParser::ParametersContext* GoliteParser::parameters() {
  ParametersContext *_localctx = _tracker.createInstance<ParametersContext>(_ctx, getState());
  enterRule(_localctx, 22, GoliteParser::RuleParameters);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(148);
    match(GoliteParser::L_PAREN);
    setState(157);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == GoliteParser::ID) {
      setState(149);
      decl();
      setState(154);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == GoliteParser::COMMA) {
        setState(150);
        match(GoliteParser::COMMA);
        setState(151);
        decl();
        setState(156);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
    setState(159);
    match(GoliteParser::R_PAREN);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ReturnTypeContext ------------------------------------------------------------------

GoliteParser::ReturnTypeContext::ReturnTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

GoliteParser::TypeContext* GoliteParser::ReturnTypeContext::type() {
  return getRuleContext<GoliteParser::TypeContext>(0);
}


size_t GoliteParser::ReturnTypeContext::getRuleIndex() const {
  return GoliteParser::RuleReturnType;
}

void GoliteParser::ReturnTypeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GoliteParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterReturnType(this);
}

void GoliteParser::ReturnTypeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GoliteParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitReturnType(this);
}


std::any GoliteParser::ReturnTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GoliteParserVisitor*>(visitor))
    return parserVisitor->visitReturnType(this);
  else
    return visitor->visitChildren(this);
}

GoliteParser::ReturnTypeContext* GoliteParser::returnType() {
  ReturnTypeContext *_localctx = _tracker.createInstance<ReturnTypeContext>(_ctx, getState());
  enterRule(_localctx, 24, GoliteParser::RuleReturnType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(161);
    type();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StatementsContext ------------------------------------------------------------------

GoliteParser::StatementsContext::StatementsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<GoliteParser::StatementContext *> GoliteParser::StatementsContext::statement() {
  return getRuleContexts<GoliteParser::StatementContext>();
}

GoliteParser::StatementContext* GoliteParser::StatementsContext::statement(size_t i) {
  return getRuleContext<GoliteParser::StatementContext>(i);
}


size_t GoliteParser::StatementsContext::getRuleIndex() const {
  return GoliteParser::RuleStatements;
}

void GoliteParser::StatementsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GoliteParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStatements(this);
}

void GoliteParser::StatementsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GoliteParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStatements(this);
}


std::any GoliteParser::StatementsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GoliteParserVisitor*>(visitor))
    return parserVisitor->visitStatements(this);
  else
    return visitor->visitChildren(this);
}

GoliteParser::StatementsContext* GoliteParser::statements() {
  StatementsContext *_localctx = _tracker.createInstance<StatementsContext>(_ctx, getState());
  enterRule(_localctx, 26, GoliteParser::RuleStatements);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(166);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 52776559509408) != 0) {
      setState(163);
      statement();
      setState(168);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StatementContext ------------------------------------------------------------------

GoliteParser::StatementContext::StatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

GoliteParser::AssignmentContext* GoliteParser::StatementContext::assignment() {
  return getRuleContext<GoliteParser::AssignmentContext>(0);
}

GoliteParser::PrintContext* GoliteParser::StatementContext::print() {
  return getRuleContext<GoliteParser::PrintContext>(0);
}

GoliteParser::ScanContext* GoliteParser::StatementContext::scan() {
  return getRuleContext<GoliteParser::ScanContext>(0);
}

GoliteParser::DeleteContext* GoliteParser::StatementContext::delete_() {
  return getRuleContext<GoliteParser::DeleteContext>(0);
}

GoliteParser::ConditionalContext* GoliteParser::StatementContext::conditional() {
  return getRuleContext<GoliteParser::ConditionalContext>(0);
}

GoliteParser::LoopContext* GoliteParser::StatementContext::loop() {
  return getRuleContext<GoliteParser::LoopContext>(0);
}

GoliteParser::ReturnContext* GoliteParser::StatementContext::return_() {
  return getRuleContext<GoliteParser::ReturnContext>(0);
}

GoliteParser::BlockContext* GoliteParser::StatementContext::block() {
  return getRuleContext<GoliteParser::BlockContext>(0);
}

GoliteParser::InvocationContext* GoliteParser::StatementContext::invocation() {
  return getRuleContext<GoliteParser::InvocationContext>(0);
}


size_t GoliteParser::StatementContext::getRuleIndex() const {
  return GoliteParser::RuleStatement;
}

void GoliteParser::StatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GoliteParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStatement(this);
}

void GoliteParser::StatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GoliteParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStatement(this);
}


std::any GoliteParser::StatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GoliteParserVisitor*>(visitor))
    return parserVisitor->visitStatement(this);
  else
    return visitor->visitChildren(this);
}

GoliteParser::StatementContext* GoliteParser::statement() {
  StatementContext *_localctx = _tracker.createInstance<StatementContext>(_ctx, getState());
  enterRule(_localctx, 28, GoliteParser::RuleStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(178);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(169);
      assignment();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(170);
      print();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(171);
      scan();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(172);
      delete_();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(173);
      conditional();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(174);
      loop();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(175);
      return_();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(176);
      block();
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(177);
      invocation();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- InvocationContext ------------------------------------------------------------------

GoliteParser::InvocationContext::InvocationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* GoliteParser::InvocationContext::ID() {
  return getToken(GoliteParser::ID, 0);
}

GoliteParser::ArgumentsContext* GoliteParser::InvocationContext::arguments() {
  return getRuleContext<GoliteParser::ArgumentsContext>(0);
}

tree::TerminalNode* GoliteParser::InvocationContext::SEMI() {
  return getToken(GoliteParser::SEMI, 0);
}


size_t GoliteParser::InvocationContext::getRuleIndex() const {
  return GoliteParser::RuleInvocation;
}

void GoliteParser::InvocationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GoliteParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterInvocation(this);
}

void GoliteParser::InvocationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GoliteParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitInvocation(this);
}


std::any GoliteParser::InvocationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GoliteParserVisitor*>(visitor))
    return parserVisitor->visitInvocation(this);
  else
    return visitor->visitChildren(this);
}

GoliteParser::InvocationContext* GoliteParser::invocation() {
  InvocationContext *_localctx = _tracker.createInstance<InvocationContext>(_ctx, getState());
  enterRule(_localctx, 30, GoliteParser::RuleInvocation);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(180);
    match(GoliteParser::ID);
    setState(181);
    arguments();
    setState(182);
    match(GoliteParser::SEMI);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BlockContext ------------------------------------------------------------------

GoliteParser::BlockContext::BlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* GoliteParser::BlockContext::L_CURLY() {
  return getToken(GoliteParser::L_CURLY, 0);
}

GoliteParser::StatementsContext* GoliteParser::BlockContext::statements() {
  return getRuleContext<GoliteParser::StatementsContext>(0);
}

tree::TerminalNode* GoliteParser::BlockContext::R_CURLY() {
  return getToken(GoliteParser::R_CURLY, 0);
}


size_t GoliteParser::BlockContext::getRuleIndex() const {
  return GoliteParser::RuleBlock;
}

void GoliteParser::BlockContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GoliteParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBlock(this);
}

void GoliteParser::BlockContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GoliteParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBlock(this);
}


std::any GoliteParser::BlockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GoliteParserVisitor*>(visitor))
    return parserVisitor->visitBlock(this);
  else
    return visitor->visitChildren(this);
}

GoliteParser::BlockContext* GoliteParser::block() {
  BlockContext *_localctx = _tracker.createInstance<BlockContext>(_ctx, getState());
  enterRule(_localctx, 32, GoliteParser::RuleBlock);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(184);
    match(GoliteParser::L_CURLY);
    setState(185);
    statements();
    setState(186);
    match(GoliteParser::R_CURLY);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AssignmentContext ------------------------------------------------------------------

GoliteParser::AssignmentContext::AssignmentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

GoliteParser::LvalueContext* GoliteParser::AssignmentContext::lvalue() {
  return getRuleContext<GoliteParser::LvalueContext>(0);
}

tree::TerminalNode* GoliteParser::AssignmentContext::ASSIGN() {
  return getToken(GoliteParser::ASSIGN, 0);
}

GoliteParser::ExpressionContext* GoliteParser::AssignmentContext::expression() {
  return getRuleContext<GoliteParser::ExpressionContext>(0);
}

tree::TerminalNode* GoliteParser::AssignmentContext::SEMI() {
  return getToken(GoliteParser::SEMI, 0);
}


size_t GoliteParser::AssignmentContext::getRuleIndex() const {
  return GoliteParser::RuleAssignment;
}

void GoliteParser::AssignmentContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GoliteParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAssignment(this);
}

void GoliteParser::AssignmentContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GoliteParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAssignment(this);
}


std::any GoliteParser::AssignmentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GoliteParserVisitor*>(visitor))
    return parserVisitor->visitAssignment(this);
  else
    return visitor->visitChildren(this);
}

GoliteParser::AssignmentContext* GoliteParser::assignment() {
  AssignmentContext *_localctx = _tracker.createInstance<AssignmentContext>(_ctx, getState());
  enterRule(_localctx, 34, GoliteParser::RuleAssignment);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(188);
    lvalue();
    setState(189);
    match(GoliteParser::ASSIGN);
    setState(190);
    expression();
    setState(191);
    match(GoliteParser::SEMI);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PrintContext ------------------------------------------------------------------

GoliteParser::PrintContext::PrintContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* GoliteParser::PrintContext::PRINTF() {
  return getToken(GoliteParser::PRINTF, 0);
}

tree::TerminalNode* GoliteParser::PrintContext::L_PAREN() {
  return getToken(GoliteParser::L_PAREN, 0);
}

tree::TerminalNode* GoliteParser::PrintContext::STRING() {
  return getToken(GoliteParser::STRING, 0);
}

tree::TerminalNode* GoliteParser::PrintContext::R_PAREN() {
  return getToken(GoliteParser::R_PAREN, 0);
}

tree::TerminalNode* GoliteParser::PrintContext::SEMI() {
  return getToken(GoliteParser::SEMI, 0);
}

std::vector<tree::TerminalNode *> GoliteParser::PrintContext::COMMA() {
  return getTokens(GoliteParser::COMMA);
}

tree::TerminalNode* GoliteParser::PrintContext::COMMA(size_t i) {
  return getToken(GoliteParser::COMMA, i);
}

std::vector<GoliteParser::ExpressionContext *> GoliteParser::PrintContext::expression() {
  return getRuleContexts<GoliteParser::ExpressionContext>();
}

GoliteParser::ExpressionContext* GoliteParser::PrintContext::expression(size_t i) {
  return getRuleContext<GoliteParser::ExpressionContext>(i);
}


size_t GoliteParser::PrintContext::getRuleIndex() const {
  return GoliteParser::RulePrint;
}

void GoliteParser::PrintContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GoliteParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPrint(this);
}

void GoliteParser::PrintContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GoliteParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPrint(this);
}


std::any GoliteParser::PrintContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GoliteParserVisitor*>(visitor))
    return parserVisitor->visitPrint(this);
  else
    return visitor->visitChildren(this);
}

GoliteParser::PrintContext* GoliteParser::print() {
  PrintContext *_localctx = _tracker.createInstance<PrintContext>(_ctx, getState());
  enterRule(_localctx, 36, GoliteParser::RulePrint);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(193);
    match(GoliteParser::PRINTF);
    setState(194);
    match(GoliteParser::L_PAREN);
    setState(195);
    match(GoliteParser::STRING);
    setState(200);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == GoliteParser::COMMA) {
      setState(196);
      match(GoliteParser::COMMA);
      setState(197);
      expression();
      setState(202);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(203);
    match(GoliteParser::R_PAREN);
    setState(204);
    match(GoliteParser::SEMI);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ScanContext ------------------------------------------------------------------

GoliteParser::ScanContext::ScanContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* GoliteParser::ScanContext::SCAN() {
  return getToken(GoliteParser::SCAN, 0);
}

GoliteParser::LvalueContext* GoliteParser::ScanContext::lvalue() {
  return getRuleContext<GoliteParser::LvalueContext>(0);
}

tree::TerminalNode* GoliteParser::ScanContext::SEMI() {
  return getToken(GoliteParser::SEMI, 0);
}


size_t GoliteParser::ScanContext::getRuleIndex() const {
  return GoliteParser::RuleScan;
}

void GoliteParser::ScanContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GoliteParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterScan(this);
}

void GoliteParser::ScanContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GoliteParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitScan(this);
}


std::any GoliteParser::ScanContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GoliteParserVisitor*>(visitor))
    return parserVisitor->visitScan(this);
  else
    return visitor->visitChildren(this);
}

GoliteParser::ScanContext* GoliteParser::scan() {
  ScanContext *_localctx = _tracker.createInstance<ScanContext>(_ctx, getState());
  enterRule(_localctx, 38, GoliteParser::RuleScan);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(206);
    match(GoliteParser::SCAN);
    setState(207);
    lvalue();
    setState(208);
    match(GoliteParser::SEMI);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DeleteContext ------------------------------------------------------------------

GoliteParser::DeleteContext::DeleteContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* GoliteParser::DeleteContext::DELETE() {
  return getToken(GoliteParser::DELETE, 0);
}

GoliteParser::ExpressionContext* GoliteParser::DeleteContext::expression() {
  return getRuleContext<GoliteParser::ExpressionContext>(0);
}

tree::TerminalNode* GoliteParser::DeleteContext::SEMI() {
  return getToken(GoliteParser::SEMI, 0);
}


size_t GoliteParser::DeleteContext::getRuleIndex() const {
  return GoliteParser::RuleDelete;
}

void GoliteParser::DeleteContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GoliteParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDelete(this);
}

void GoliteParser::DeleteContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GoliteParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDelete(this);
}


std::any GoliteParser::DeleteContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GoliteParserVisitor*>(visitor))
    return parserVisitor->visitDelete(this);
  else
    return visitor->visitChildren(this);
}

GoliteParser::DeleteContext* GoliteParser::delete_() {
  DeleteContext *_localctx = _tracker.createInstance<DeleteContext>(_ctx, getState());
  enterRule(_localctx, 40, GoliteParser::RuleDelete);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(210);
    match(GoliteParser::DELETE);
    setState(211);
    expression();
    setState(212);
    match(GoliteParser::SEMI);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConditionalContext ------------------------------------------------------------------

GoliteParser::ConditionalContext::ConditionalContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* GoliteParser::ConditionalContext::IF() {
  return getToken(GoliteParser::IF, 0);
}

tree::TerminalNode* GoliteParser::ConditionalContext::L_PAREN() {
  return getToken(GoliteParser::L_PAREN, 0);
}

GoliteParser::ExpressionContext* GoliteParser::ConditionalContext::expression() {
  return getRuleContext<GoliteParser::ExpressionContext>(0);
}

tree::TerminalNode* GoliteParser::ConditionalContext::R_PAREN() {
  return getToken(GoliteParser::R_PAREN, 0);
}

std::vector<GoliteParser::BlockContext *> GoliteParser::ConditionalContext::block() {
  return getRuleContexts<GoliteParser::BlockContext>();
}

GoliteParser::BlockContext* GoliteParser::ConditionalContext::block(size_t i) {
  return getRuleContext<GoliteParser::BlockContext>(i);
}

tree::TerminalNode* GoliteParser::ConditionalContext::ELSE() {
  return getToken(GoliteParser::ELSE, 0);
}


size_t GoliteParser::ConditionalContext::getRuleIndex() const {
  return GoliteParser::RuleConditional;
}

void GoliteParser::ConditionalContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GoliteParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterConditional(this);
}

void GoliteParser::ConditionalContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GoliteParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitConditional(this);
}


std::any GoliteParser::ConditionalContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GoliteParserVisitor*>(visitor))
    return parserVisitor->visitConditional(this);
  else
    return visitor->visitChildren(this);
}

GoliteParser::ConditionalContext* GoliteParser::conditional() {
  ConditionalContext *_localctx = _tracker.createInstance<ConditionalContext>(_ctx, getState());
  enterRule(_localctx, 42, GoliteParser::RuleConditional);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(214);
    match(GoliteParser::IF);
    setState(215);
    match(GoliteParser::L_PAREN);
    setState(216);
    expression();
    setState(217);
    match(GoliteParser::R_PAREN);
    setState(218);
    block();
    setState(221);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == GoliteParser::ELSE) {
      setState(219);
      match(GoliteParser::ELSE);
      setState(220);
      block();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LoopContext ------------------------------------------------------------------

GoliteParser::LoopContext::LoopContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* GoliteParser::LoopContext::FOR() {
  return getToken(GoliteParser::FOR, 0);
}

tree::TerminalNode* GoliteParser::LoopContext::L_PAREN() {
  return getToken(GoliteParser::L_PAREN, 0);
}

GoliteParser::ExpressionContext* GoliteParser::LoopContext::expression() {
  return getRuleContext<GoliteParser::ExpressionContext>(0);
}

tree::TerminalNode* GoliteParser::LoopContext::R_PAREN() {
  return getToken(GoliteParser::R_PAREN, 0);
}

GoliteParser::BlockContext* GoliteParser::LoopContext::block() {
  return getRuleContext<GoliteParser::BlockContext>(0);
}


size_t GoliteParser::LoopContext::getRuleIndex() const {
  return GoliteParser::RuleLoop;
}

void GoliteParser::LoopContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GoliteParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLoop(this);
}

void GoliteParser::LoopContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GoliteParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLoop(this);
}


std::any GoliteParser::LoopContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GoliteParserVisitor*>(visitor))
    return parserVisitor->visitLoop(this);
  else
    return visitor->visitChildren(this);
}

GoliteParser::LoopContext* GoliteParser::loop() {
  LoopContext *_localctx = _tracker.createInstance<LoopContext>(_ctx, getState());
  enterRule(_localctx, 44, GoliteParser::RuleLoop);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(223);
    match(GoliteParser::FOR);
    setState(224);
    match(GoliteParser::L_PAREN);
    setState(225);
    expression();
    setState(226);
    match(GoliteParser::R_PAREN);
    setState(227);
    block();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ReturnContext ------------------------------------------------------------------

GoliteParser::ReturnContext::ReturnContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* GoliteParser::ReturnContext::RETURN() {
  return getToken(GoliteParser::RETURN, 0);
}

tree::TerminalNode* GoliteParser::ReturnContext::SEMI() {
  return getToken(GoliteParser::SEMI, 0);
}

GoliteParser::ExpressionContext* GoliteParser::ReturnContext::expression() {
  return getRuleContext<GoliteParser::ExpressionContext>(0);
}


size_t GoliteParser::ReturnContext::getRuleIndex() const {
  return GoliteParser::RuleReturn;
}

void GoliteParser::ReturnContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GoliteParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterReturn(this);
}

void GoliteParser::ReturnContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GoliteParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitReturn(this);
}


std::any GoliteParser::ReturnContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GoliteParserVisitor*>(visitor))
    return parserVisitor->visitReturn(this);
  else
    return visitor->visitChildren(this);
}

GoliteParser::ReturnContext* GoliteParser::return_() {
  ReturnContext *_localctx = _tracker.createInstance<ReturnContext>(_ctx, getState());
  enterRule(_localctx, 46, GoliteParser::RuleReturn);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(229);
    match(GoliteParser::RETURN);
    setState(231);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 52794812067840) != 0) {
      setState(230);
      expression();
    }
    setState(233);
    match(GoliteParser::SEMI);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExpressionContext ------------------------------------------------------------------

GoliteParser::ExpressionContext::ExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

GoliteParser::ArithmeticExpressionContext* GoliteParser::ExpressionContext::arithmeticExpression() {
  return getRuleContext<GoliteParser::ArithmeticExpressionContext>(0);
}

GoliteParser::BoolExpressionContext* GoliteParser::ExpressionContext::boolExpression() {
  return getRuleContext<GoliteParser::BoolExpressionContext>(0);
}


size_t GoliteParser::ExpressionContext::getRuleIndex() const {
  return GoliteParser::RuleExpression;
}

void GoliteParser::ExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GoliteParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExpression(this);
}

void GoliteParser::ExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GoliteParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExpression(this);
}


std::any GoliteParser::ExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GoliteParserVisitor*>(visitor))
    return parserVisitor->visitExpression(this);
  else
    return visitor->visitChildren(this);
}

GoliteParser::ExpressionContext* GoliteParser::expression() {
  ExpressionContext *_localctx = _tracker.createInstance<ExpressionContext>(_ctx, getState());
  enterRule(_localctx, 48, GoliteParser::RuleExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(237);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 14, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(235);
      arithmeticExpression();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(236);
      boolExpression();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BoolExpressionContext ------------------------------------------------------------------

GoliteParser::BoolExpressionContext::BoolExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<GoliteParser::BoolTermContext *> GoliteParser::BoolExpressionContext::boolTerm() {
  return getRuleContexts<GoliteParser::BoolTermContext>();
}

GoliteParser::BoolTermContext* GoliteParser::BoolExpressionContext::boolTerm(size_t i) {
  return getRuleContext<GoliteParser::BoolTermContext>(i);
}

std::vector<tree::TerminalNode *> GoliteParser::BoolExpressionContext::LOGICAL_OR() {
  return getTokens(GoliteParser::LOGICAL_OR);
}

tree::TerminalNode* GoliteParser::BoolExpressionContext::LOGICAL_OR(size_t i) {
  return getToken(GoliteParser::LOGICAL_OR, i);
}


size_t GoliteParser::BoolExpressionContext::getRuleIndex() const {
  return GoliteParser::RuleBoolExpression;
}

void GoliteParser::BoolExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GoliteParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBoolExpression(this);
}

void GoliteParser::BoolExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GoliteParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBoolExpression(this);
}


std::any GoliteParser::BoolExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GoliteParserVisitor*>(visitor))
    return parserVisitor->visitBoolExpression(this);
  else
    return visitor->visitChildren(this);
}

GoliteParser::BoolExpressionContext* GoliteParser::boolExpression() {
  BoolExpressionContext *_localctx = _tracker.createInstance<BoolExpressionContext>(_ctx, getState());
  enterRule(_localctx, 50, GoliteParser::RuleBoolExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(239);
    boolTerm();
    setState(244);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == GoliteParser::LOGICAL_OR) {
      setState(240);
      match(GoliteParser::LOGICAL_OR);
      setState(241);
      boolTerm();
      setState(246);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BoolTermContext ------------------------------------------------------------------

GoliteParser::BoolTermContext::BoolTermContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<GoliteParser::EqualTermContext *> GoliteParser::BoolTermContext::equalTerm() {
  return getRuleContexts<GoliteParser::EqualTermContext>();
}

GoliteParser::EqualTermContext* GoliteParser::BoolTermContext::equalTerm(size_t i) {
  return getRuleContext<GoliteParser::EqualTermContext>(i);
}

std::vector<tree::TerminalNode *> GoliteParser::BoolTermContext::LOGICAL_AND() {
  return getTokens(GoliteParser::LOGICAL_AND);
}

tree::TerminalNode* GoliteParser::BoolTermContext::LOGICAL_AND(size_t i) {
  return getToken(GoliteParser::LOGICAL_AND, i);
}


size_t GoliteParser::BoolTermContext::getRuleIndex() const {
  return GoliteParser::RuleBoolTerm;
}

void GoliteParser::BoolTermContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GoliteParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBoolTerm(this);
}

void GoliteParser::BoolTermContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GoliteParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBoolTerm(this);
}


std::any GoliteParser::BoolTermContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GoliteParserVisitor*>(visitor))
    return parserVisitor->visitBoolTerm(this);
  else
    return visitor->visitChildren(this);
}

GoliteParser::BoolTermContext* GoliteParser::boolTerm() {
  BoolTermContext *_localctx = _tracker.createInstance<BoolTermContext>(_ctx, getState());
  enterRule(_localctx, 52, GoliteParser::RuleBoolTerm);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(247);
    equalTerm();
    setState(252);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == GoliteParser::LOGICAL_AND) {
      setState(248);
      match(GoliteParser::LOGICAL_AND);
      setState(249);
      equalTerm();
      setState(254);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- EqualTermContext ------------------------------------------------------------------

GoliteParser::EqualTermContext::EqualTermContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<GoliteParser::RelationTermContext *> GoliteParser::EqualTermContext::relationTerm() {
  return getRuleContexts<GoliteParser::RelationTermContext>();
}

GoliteParser::RelationTermContext* GoliteParser::EqualTermContext::relationTerm(size_t i) {
  return getRuleContext<GoliteParser::RelationTermContext>(i);
}

std::vector<tree::TerminalNode *> GoliteParser::EqualTermContext::EQUALS() {
  return getTokens(GoliteParser::EQUALS);
}

tree::TerminalNode* GoliteParser::EqualTermContext::EQUALS(size_t i) {
  return getToken(GoliteParser::EQUALS, i);
}

std::vector<tree::TerminalNode *> GoliteParser::EqualTermContext::NOT_EQUALS() {
  return getTokens(GoliteParser::NOT_EQUALS);
}

tree::TerminalNode* GoliteParser::EqualTermContext::NOT_EQUALS(size_t i) {
  return getToken(GoliteParser::NOT_EQUALS, i);
}


size_t GoliteParser::EqualTermContext::getRuleIndex() const {
  return GoliteParser::RuleEqualTerm;
}

void GoliteParser::EqualTermContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GoliteParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterEqualTerm(this);
}

void GoliteParser::EqualTermContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GoliteParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitEqualTerm(this);
}


std::any GoliteParser::EqualTermContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GoliteParserVisitor*>(visitor))
    return parserVisitor->visitEqualTerm(this);
  else
    return visitor->visitChildren(this);
}

GoliteParser::EqualTermContext* GoliteParser::equalTerm() {
  EqualTermContext *_localctx = _tracker.createInstance<EqualTermContext>(_ctx, getState());
  enterRule(_localctx, 54, GoliteParser::RuleEqualTerm);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(255);
    relationTerm();
    setState(260);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == GoliteParser::EQUALS

    || _la == GoliteParser::NOT_EQUALS) {
      setState(256);
      _la = _input->LA(1);
      if (!(_la == GoliteParser::EQUALS

      || _la == GoliteParser::NOT_EQUALS)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(257);
      relationTerm();
      setState(262);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- RelationTermContext ------------------------------------------------------------------

GoliteParser::RelationTermContext::RelationTermContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<GoliteParser::ArithmeticExpressionContext *> GoliteParser::RelationTermContext::arithmeticExpression() {
  return getRuleContexts<GoliteParser::ArithmeticExpressionContext>();
}

GoliteParser::ArithmeticExpressionContext* GoliteParser::RelationTermContext::arithmeticExpression(size_t i) {
  return getRuleContext<GoliteParser::ArithmeticExpressionContext>(i);
}

std::vector<tree::TerminalNode *> GoliteParser::RelationTermContext::LESS() {
  return getTokens(GoliteParser::LESS);
}

tree::TerminalNode* GoliteParser::RelationTermContext::LESS(size_t i) {
  return getToken(GoliteParser::LESS, i);
}

std::vector<tree::TerminalNode *> GoliteParser::RelationTermContext::GREATER() {
  return getTokens(GoliteParser::GREATER);
}

tree::TerminalNode* GoliteParser::RelationTermContext::GREATER(size_t i) {
  return getToken(GoliteParser::GREATER, i);
}

std::vector<tree::TerminalNode *> GoliteParser::RelationTermContext::LESS_OR_EQUALS() {
  return getTokens(GoliteParser::LESS_OR_EQUALS);
}

tree::TerminalNode* GoliteParser::RelationTermContext::LESS_OR_EQUALS(size_t i) {
  return getToken(GoliteParser::LESS_OR_EQUALS, i);
}

std::vector<tree::TerminalNode *> GoliteParser::RelationTermContext::GREATER_OR_EQUALS() {
  return getTokens(GoliteParser::GREATER_OR_EQUALS);
}

tree::TerminalNode* GoliteParser::RelationTermContext::GREATER_OR_EQUALS(size_t i) {
  return getToken(GoliteParser::GREATER_OR_EQUALS, i);
}


size_t GoliteParser::RelationTermContext::getRuleIndex() const {
  return GoliteParser::RuleRelationTerm;
}

void GoliteParser::RelationTermContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GoliteParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterRelationTerm(this);
}

void GoliteParser::RelationTermContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GoliteParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitRelationTerm(this);
}


std::any GoliteParser::RelationTermContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GoliteParserVisitor*>(visitor))
    return parserVisitor->visitRelationTerm(this);
  else
    return visitor->visitChildren(this);
}

GoliteParser::RelationTermContext* GoliteParser::relationTerm() {
  RelationTermContext *_localctx = _tracker.createInstance<RelationTermContext>(_ctx, getState());
  enterRule(_localctx, 56, GoliteParser::RuleRelationTerm);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(263);
    arithmeticExpression();
    setState(268);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 8246337208320) != 0) {
      setState(264);
      _la = _input->LA(1);
      if (!(((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 8246337208320) != 0)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(265);
      arithmeticExpression();
      setState(270);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArithmeticExpressionContext ------------------------------------------------------------------

GoliteParser::ArithmeticExpressionContext::ArithmeticExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

GoliteParser::SimpleTermContext* GoliteParser::ArithmeticExpressionContext::simpleTerm() {
  return getRuleContext<GoliteParser::SimpleTermContext>(0);
}


size_t GoliteParser::ArithmeticExpressionContext::getRuleIndex() const {
  return GoliteParser::RuleArithmeticExpression;
}

void GoliteParser::ArithmeticExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GoliteParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArithmeticExpression(this);
}

void GoliteParser::ArithmeticExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GoliteParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArithmeticExpression(this);
}


std::any GoliteParser::ArithmeticExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GoliteParserVisitor*>(visitor))
    return parserVisitor->visitArithmeticExpression(this);
  else
    return visitor->visitChildren(this);
}

GoliteParser::ArithmeticExpressionContext* GoliteParser::arithmeticExpression() {
  ArithmeticExpressionContext *_localctx = _tracker.createInstance<ArithmeticExpressionContext>(_ctx, getState());
  enterRule(_localctx, 58, GoliteParser::RuleArithmeticExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(271);
    simpleTerm();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SimpleTermContext ------------------------------------------------------------------

GoliteParser::SimpleTermContext::SimpleTermContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<GoliteParser::TermContext *> GoliteParser::SimpleTermContext::term() {
  return getRuleContexts<GoliteParser::TermContext>();
}

GoliteParser::TermContext* GoliteParser::SimpleTermContext::term(size_t i) {
  return getRuleContext<GoliteParser::TermContext>(i);
}

std::vector<tree::TerminalNode *> GoliteParser::SimpleTermContext::PLUS() {
  return getTokens(GoliteParser::PLUS);
}

tree::TerminalNode* GoliteParser::SimpleTermContext::PLUS(size_t i) {
  return getToken(GoliteParser::PLUS, i);
}

std::vector<tree::TerminalNode *> GoliteParser::SimpleTermContext::MINUS() {
  return getTokens(GoliteParser::MINUS);
}

tree::TerminalNode* GoliteParser::SimpleTermContext::MINUS(size_t i) {
  return getToken(GoliteParser::MINUS, i);
}


size_t GoliteParser::SimpleTermContext::getRuleIndex() const {
  return GoliteParser::RuleSimpleTerm;
}

void GoliteParser::SimpleTermContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GoliteParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSimpleTerm(this);
}

void GoliteParser::SimpleTermContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GoliteParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSimpleTerm(this);
}


std::any GoliteParser::SimpleTermContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GoliteParserVisitor*>(visitor))
    return parserVisitor->visitSimpleTerm(this);
  else
    return visitor->visitChildren(this);
}

GoliteParser::SimpleTermContext* GoliteParser::simpleTerm() {
  SimpleTermContext *_localctx = _tracker.createInstance<SimpleTermContext>(_ctx, getState());
  enterRule(_localctx, 60, GoliteParser::RuleSimpleTerm);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(273);
    term();
    setState(278);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == GoliteParser::PLUS

    || _la == GoliteParser::MINUS) {
      setState(274);
      _la = _input->LA(1);
      if (!(_la == GoliteParser::PLUS

      || _la == GoliteParser::MINUS)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(275);
      term();
      setState(280);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TermContext ------------------------------------------------------------------

GoliteParser::TermContext::TermContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<GoliteParser::UnaryTermContext *> GoliteParser::TermContext::unaryTerm() {
  return getRuleContexts<GoliteParser::UnaryTermContext>();
}

GoliteParser::UnaryTermContext* GoliteParser::TermContext::unaryTerm(size_t i) {
  return getRuleContext<GoliteParser::UnaryTermContext>(i);
}

std::vector<tree::TerminalNode *> GoliteParser::TermContext::STAR() {
  return getTokens(GoliteParser::STAR);
}

tree::TerminalNode* GoliteParser::TermContext::STAR(size_t i) {
  return getToken(GoliteParser::STAR, i);
}

std::vector<tree::TerminalNode *> GoliteParser::TermContext::DIV() {
  return getTokens(GoliteParser::DIV);
}

tree::TerminalNode* GoliteParser::TermContext::DIV(size_t i) {
  return getToken(GoliteParser::DIV, i);
}


size_t GoliteParser::TermContext::getRuleIndex() const {
  return GoliteParser::RuleTerm;
}

void GoliteParser::TermContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GoliteParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTerm(this);
}

void GoliteParser::TermContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GoliteParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTerm(this);
}


std::any GoliteParser::TermContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GoliteParserVisitor*>(visitor))
    return parserVisitor->visitTerm(this);
  else
    return visitor->visitChildren(this);
}

GoliteParser::TermContext* GoliteParser::term() {
  TermContext *_localctx = _tracker.createInstance<TermContext>(_ctx, getState());
  enterRule(_localctx, 62, GoliteParser::RuleTerm);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(281);
    unaryTerm();
    setState(286);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == GoliteParser::STAR

    || _la == GoliteParser::DIV) {
      setState(282);
      _la = _input->LA(1);
      if (!(_la == GoliteParser::STAR

      || _la == GoliteParser::DIV)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(283);
      unaryTerm();
      setState(288);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- UnaryTermContext ------------------------------------------------------------------

GoliteParser::UnaryTermContext::UnaryTermContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* GoliteParser::UnaryTermContext::EXCLAMATION() {
  return getToken(GoliteParser::EXCLAMATION, 0);
}

GoliteParser::UnaryTermContext* GoliteParser::UnaryTermContext::unaryTerm() {
  return getRuleContext<GoliteParser::UnaryTermContext>(0);
}

tree::TerminalNode* GoliteParser::UnaryTermContext::MINUS() {
  return getToken(GoliteParser::MINUS, 0);
}

GoliteParser::SelectorTermContext* GoliteParser::UnaryTermContext::selectorTerm() {
  return getRuleContext<GoliteParser::SelectorTermContext>(0);
}


size_t GoliteParser::UnaryTermContext::getRuleIndex() const {
  return GoliteParser::RuleUnaryTerm;
}

void GoliteParser::UnaryTermContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GoliteParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterUnaryTerm(this);
}

void GoliteParser::UnaryTermContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GoliteParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitUnaryTerm(this);
}


std::any GoliteParser::UnaryTermContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GoliteParserVisitor*>(visitor))
    return parserVisitor->visitUnaryTerm(this);
  else
    return visitor->visitChildren(this);
}

GoliteParser::UnaryTermContext* GoliteParser::unaryTerm() {
  UnaryTermContext *_localctx = _tracker.createInstance<UnaryTermContext>(_ctx, getState());
  enterRule(_localctx, 64, GoliteParser::RuleUnaryTerm);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(294);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case GoliteParser::EXCLAMATION: {
        enterOuterAlt(_localctx, 1);
        setState(289);
        match(GoliteParser::EXCLAMATION);
        setState(290);
        unaryTerm();
        break;
      }

      case GoliteParser::MINUS: {
        enterOuterAlt(_localctx, 2);
        setState(291);
        match(GoliteParser::MINUS);
        setState(292);
        unaryTerm();
        break;
      }

      case GoliteParser::NEW:
      case GoliteParser::TRUE:
      case GoliteParser::FALSE:
      case GoliteParser::NIL:
      case GoliteParser::L_PAREN:
      case GoliteParser::ID:
      case GoliteParser::NUMBER: {
        enterOuterAlt(_localctx, 3);
        setState(293);
        selectorTerm();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SelectorTermContext ------------------------------------------------------------------

GoliteParser::SelectorTermContext::SelectorTermContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

GoliteParser::FactorContext* GoliteParser::SelectorTermContext::factor() {
  return getRuleContext<GoliteParser::FactorContext>(0);
}

std::vector<tree::TerminalNode *> GoliteParser::SelectorTermContext::DOT() {
  return getTokens(GoliteParser::DOT);
}

tree::TerminalNode* GoliteParser::SelectorTermContext::DOT(size_t i) {
  return getToken(GoliteParser::DOT, i);
}

std::vector<tree::TerminalNode *> GoliteParser::SelectorTermContext::ID() {
  return getTokens(GoliteParser::ID);
}

tree::TerminalNode* GoliteParser::SelectorTermContext::ID(size_t i) {
  return getToken(GoliteParser::ID, i);
}


size_t GoliteParser::SelectorTermContext::getRuleIndex() const {
  return GoliteParser::RuleSelectorTerm;
}

void GoliteParser::SelectorTermContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GoliteParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSelectorTerm(this);
}

void GoliteParser::SelectorTermContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GoliteParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSelectorTerm(this);
}


std::any GoliteParser::SelectorTermContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GoliteParserVisitor*>(visitor))
    return parserVisitor->visitSelectorTerm(this);
  else
    return visitor->visitChildren(this);
}

GoliteParser::SelectorTermContext* GoliteParser::selectorTerm() {
  SelectorTermContext *_localctx = _tracker.createInstance<SelectorTermContext>(_ctx, getState());
  enterRule(_localctx, 66, GoliteParser::RuleSelectorTerm);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(296);
    factor();
    setState(301);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == GoliteParser::DOT) {
      setState(297);
      match(GoliteParser::DOT);
      setState(298);
      match(GoliteParser::ID);
      setState(303);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FactorContext ------------------------------------------------------------------

GoliteParser::FactorContext::FactorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* GoliteParser::FactorContext::L_PAREN() {
  return getToken(GoliteParser::L_PAREN, 0);
}

GoliteParser::ExpressionContext* GoliteParser::FactorContext::expression() {
  return getRuleContext<GoliteParser::ExpressionContext>(0);
}

tree::TerminalNode* GoliteParser::FactorContext::R_PAREN() {
  return getToken(GoliteParser::R_PAREN, 0);
}

tree::TerminalNode* GoliteParser::FactorContext::ID() {
  return getToken(GoliteParser::ID, 0);
}

GoliteParser::ArgumentsContext* GoliteParser::FactorContext::arguments() {
  return getRuleContext<GoliteParser::ArgumentsContext>(0);
}

tree::TerminalNode* GoliteParser::FactorContext::NUMBER() {
  return getToken(GoliteParser::NUMBER, 0);
}

tree::TerminalNode* GoliteParser::FactorContext::NEW() {
  return getToken(GoliteParser::NEW, 0);
}

tree::TerminalNode* GoliteParser::FactorContext::TRUE() {
  return getToken(GoliteParser::TRUE, 0);
}

tree::TerminalNode* GoliteParser::FactorContext::FALSE() {
  return getToken(GoliteParser::FALSE, 0);
}

tree::TerminalNode* GoliteParser::FactorContext::NIL() {
  return getToken(GoliteParser::NIL, 0);
}


size_t GoliteParser::FactorContext::getRuleIndex() const {
  return GoliteParser::RuleFactor;
}

void GoliteParser::FactorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GoliteParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFactor(this);
}

void GoliteParser::FactorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GoliteParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFactor(this);
}


std::any GoliteParser::FactorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GoliteParserVisitor*>(visitor))
    return parserVisitor->visitFactor(this);
  else
    return visitor->visitChildren(this);
}

GoliteParser::FactorContext* GoliteParser::factor() {
  FactorContext *_localctx = _tracker.createInstance<FactorContext>(_ctx, getState());
  enterRule(_localctx, 68, GoliteParser::RuleFactor);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(318);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case GoliteParser::L_PAREN: {
        enterOuterAlt(_localctx, 1);
        setState(304);
        match(GoliteParser::L_PAREN);
        setState(305);
        expression();
        setState(306);
        match(GoliteParser::R_PAREN);
        break;
      }

      case GoliteParser::ID: {
        enterOuterAlt(_localctx, 2);
        setState(308);
        match(GoliteParser::ID);
        setState(310);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == GoliteParser::L_PAREN) {
          setState(309);
          arguments();
        }
        break;
      }

      case GoliteParser::NUMBER: {
        enterOuterAlt(_localctx, 3);
        setState(312);
        match(GoliteParser::NUMBER);
        break;
      }

      case GoliteParser::NEW: {
        enterOuterAlt(_localctx, 4);
        setState(313);
        match(GoliteParser::NEW);
        setState(314);
        match(GoliteParser::ID);
        break;
      }

      case GoliteParser::TRUE: {
        enterOuterAlt(_localctx, 5);
        setState(315);
        match(GoliteParser::TRUE);
        break;
      }

      case GoliteParser::FALSE: {
        enterOuterAlt(_localctx, 6);
        setState(316);
        match(GoliteParser::FALSE);
        break;
      }

      case GoliteParser::NIL: {
        enterOuterAlt(_localctx, 7);
        setState(317);
        match(GoliteParser::NIL);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArgumentsContext ------------------------------------------------------------------

GoliteParser::ArgumentsContext::ArgumentsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* GoliteParser::ArgumentsContext::L_PAREN() {
  return getToken(GoliteParser::L_PAREN, 0);
}

tree::TerminalNode* GoliteParser::ArgumentsContext::R_PAREN() {
  return getToken(GoliteParser::R_PAREN, 0);
}

std::vector<GoliteParser::ExpressionContext *> GoliteParser::ArgumentsContext::expression() {
  return getRuleContexts<GoliteParser::ExpressionContext>();
}

GoliteParser::ExpressionContext* GoliteParser::ArgumentsContext::expression(size_t i) {
  return getRuleContext<GoliteParser::ExpressionContext>(i);
}

std::vector<tree::TerminalNode *> GoliteParser::ArgumentsContext::COMMA() {
  return getTokens(GoliteParser::COMMA);
}

tree::TerminalNode* GoliteParser::ArgumentsContext::COMMA(size_t i) {
  return getToken(GoliteParser::COMMA, i);
}


size_t GoliteParser::ArgumentsContext::getRuleIndex() const {
  return GoliteParser::RuleArguments;
}

void GoliteParser::ArgumentsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GoliteParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArguments(this);
}

void GoliteParser::ArgumentsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GoliteParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArguments(this);
}


std::any GoliteParser::ArgumentsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GoliteParserVisitor*>(visitor))
    return parserVisitor->visitArguments(this);
  else
    return visitor->visitChildren(this);
}

GoliteParser::ArgumentsContext* GoliteParser::arguments() {
  ArgumentsContext *_localctx = _tracker.createInstance<ArgumentsContext>(_ctx, getState());
  enterRule(_localctx, 70, GoliteParser::RuleArguments);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(320);
    match(GoliteParser::L_PAREN);
    setState(329);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 52794812067840) != 0) {
      setState(321);
      expression();
      setState(326);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == GoliteParser::COMMA) {
        setState(322);
        match(GoliteParser::COMMA);
        setState(323);
        expression();
        setState(328);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
    setState(331);
    match(GoliteParser::R_PAREN);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LvalueContext ------------------------------------------------------------------

GoliteParser::LvalueContext::LvalueContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

GoliteParser::SelectorTermContext* GoliteParser::LvalueContext::selectorTerm() {
  return getRuleContext<GoliteParser::SelectorTermContext>(0);
}


size_t GoliteParser::LvalueContext::getRuleIndex() const {
  return GoliteParser::RuleLvalue;
}

void GoliteParser::LvalueContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GoliteParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLvalue(this);
}

void GoliteParser::LvalueContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GoliteParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLvalue(this);
}


std::any GoliteParser::LvalueContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GoliteParserVisitor*>(visitor))
    return parserVisitor->visitLvalue(this);
  else
    return visitor->visitChildren(this);
}

GoliteParser::LvalueContext* GoliteParser::lvalue() {
  LvalueContext *_localctx = _tracker.createInstance<LvalueContext>(_ctx, getState());
  enterRule(_localctx, 72, GoliteParser::RuleLvalue);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(333);
    selectorTerm();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

void GoliteParser::initialize() {
  ::antlr4::internal::call_once(goliteparserParserOnceFlag, goliteparserParserInitialize);
}

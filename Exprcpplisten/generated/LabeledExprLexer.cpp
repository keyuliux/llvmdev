
// Generated from LabeledExpr.g4 by ANTLR 4.7.2


#include "LabeledExprLexer.h"


using namespace antlr4;


LabeledExprLexer::LabeledExprLexer(CharStream *input) : Lexer(input) {
  _interpreter = new atn::LexerATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

LabeledExprLexer::~LabeledExprLexer() {
  delete _interpreter;
}

std::string LabeledExprLexer::getGrammarFileName() const {
  return "LabeledExpr.g4";
}

const std::vector<std::string>& LabeledExprLexer::getRuleNames() const {
  return _ruleNames;
}

const std::vector<std::string>& LabeledExprLexer::getChannelNames() const {
  return _channelNames;
}

const std::vector<std::string>& LabeledExprLexer::getModeNames() const {
  return _modeNames;
}

const std::vector<std::string>& LabeledExprLexer::getTokenNames() const {
  return _tokenNames;
}

dfa::Vocabulary& LabeledExprLexer::getVocabulary() const {
  return _vocabulary;
}

const std::vector<uint16_t> LabeledExprLexer::getSerializedATN() const {
  return _serializedATN;
}

const atn::ATN& LabeledExprLexer::getATN() const {
  return _atn;
}




// Static vars and initialization.
std::vector<dfa::DFA> LabeledExprLexer::_decisionToDFA;
atn::PredictionContextCache LabeledExprLexer::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN LabeledExprLexer::_atn;
std::vector<uint16_t> LabeledExprLexer::_serializedATN;

std::vector<std::string> LabeledExprLexer::_ruleNames = {
  u8"T__0", u8"T__1", u8"T__2", u8"MUL", u8"DIV", u8"ADD", u8"SUB", u8"ID", 
  u8"INT", u8"NEWLINE", u8"WS"
};

std::vector<std::string> LabeledExprLexer::_channelNames = {
  "DEFAULT_TOKEN_CHANNEL", "HIDDEN"
};

std::vector<std::string> LabeledExprLexer::_modeNames = {
  u8"DEFAULT_MODE"
};

std::vector<std::string> LabeledExprLexer::_literalNames = {
  "", u8"'='", u8"'('", u8"')'", u8"'*'", u8"'/'", u8"'+'", u8"'-'"
};

std::vector<std::string> LabeledExprLexer::_symbolicNames = {
  "", "", "", "", u8"MUL", u8"DIV", u8"ADD", u8"SUB", u8"ID", u8"INT", u8"NEWLINE", 
  u8"WS"
};

dfa::Vocabulary LabeledExprLexer::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> LabeledExprLexer::_tokenNames;

LabeledExprLexer::Initializer::Initializer() {
  // This code could be in a static initializer lambda, but VS doesn't allow access to private class members from there.
	for (size_t i = 0; i < _symbolicNames.size(); ++i) {
		std::string name = _vocabulary.getLiteralName(i);
		if (name.empty()) {
			name = _vocabulary.getSymbolicName(i);
		}

		if (name.empty()) {
			_tokenNames.push_back("<INVALID>");
		} else {
      _tokenNames.push_back(name);
    }
	}

  _serializedATN = {
    0x3, 0x608b, 0xa72a, 0x8133, 0xb9ed, 0x417c, 0x3be7, 0x7786, 0x5964, 
    0x2, 0xd, 0x3d, 0x8, 0x1, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 
    0x4, 0x9, 0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 
    0x7, 0x4, 0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 0x4, 
    0xb, 0x9, 0xb, 0x4, 0xc, 0x9, 0xc, 0x3, 0x2, 0x3, 0x2, 0x3, 0x3, 0x3, 
    0x3, 0x3, 0x4, 0x3, 0x4, 0x3, 0x5, 0x3, 0x5, 0x3, 0x6, 0x3, 0x6, 0x3, 
    0x7, 0x3, 0x7, 0x3, 0x8, 0x3, 0x8, 0x3, 0x9, 0x6, 0x9, 0x29, 0xa, 0x9, 
    0xd, 0x9, 0xe, 0x9, 0x2a, 0x3, 0xa, 0x6, 0xa, 0x2e, 0xa, 0xa, 0xd, 0xa, 
    0xe, 0xa, 0x2f, 0x3, 0xb, 0x5, 0xb, 0x33, 0xa, 0xb, 0x3, 0xb, 0x3, 0xb, 
    0x3, 0xc, 0x6, 0xc, 0x38, 0xa, 0xc, 0xd, 0xc, 0xe, 0xc, 0x39, 0x3, 0xc, 
    0x3, 0xc, 0x2, 0x2, 0xd, 0x3, 0x3, 0x5, 0x4, 0x7, 0x5, 0x9, 0x6, 0xb, 
    0x7, 0xd, 0x8, 0xf, 0x9, 0x11, 0xa, 0x13, 0xb, 0x15, 0xc, 0x17, 0xd, 
    0x3, 0x2, 0x5, 0x4, 0x2, 0x43, 0x5c, 0x63, 0x7c, 0x3, 0x2, 0x32, 0x3b, 
    0x4, 0x2, 0xb, 0xb, 0x22, 0x22, 0x2, 0x40, 0x2, 0x3, 0x3, 0x2, 0x2, 
    0x2, 0x2, 0x5, 0x3, 0x2, 0x2, 0x2, 0x2, 0x7, 0x3, 0x2, 0x2, 0x2, 0x2, 
    0x9, 0x3, 0x2, 0x2, 0x2, 0x2, 0xb, 0x3, 0x2, 0x2, 0x2, 0x2, 0xd, 0x3, 
    0x2, 0x2, 0x2, 0x2, 0xf, 0x3, 0x2, 0x2, 0x2, 0x2, 0x11, 0x3, 0x2, 0x2, 
    0x2, 0x2, 0x13, 0x3, 0x2, 0x2, 0x2, 0x2, 0x15, 0x3, 0x2, 0x2, 0x2, 0x2, 
    0x17, 0x3, 0x2, 0x2, 0x2, 0x3, 0x19, 0x3, 0x2, 0x2, 0x2, 0x5, 0x1b, 
    0x3, 0x2, 0x2, 0x2, 0x7, 0x1d, 0x3, 0x2, 0x2, 0x2, 0x9, 0x1f, 0x3, 0x2, 
    0x2, 0x2, 0xb, 0x21, 0x3, 0x2, 0x2, 0x2, 0xd, 0x23, 0x3, 0x2, 0x2, 0x2, 
    0xf, 0x25, 0x3, 0x2, 0x2, 0x2, 0x11, 0x28, 0x3, 0x2, 0x2, 0x2, 0x13, 
    0x2d, 0x3, 0x2, 0x2, 0x2, 0x15, 0x32, 0x3, 0x2, 0x2, 0x2, 0x17, 0x37, 
    0x3, 0x2, 0x2, 0x2, 0x19, 0x1a, 0x7, 0x3f, 0x2, 0x2, 0x1a, 0x4, 0x3, 
    0x2, 0x2, 0x2, 0x1b, 0x1c, 0x7, 0x2a, 0x2, 0x2, 0x1c, 0x6, 0x3, 0x2, 
    0x2, 0x2, 0x1d, 0x1e, 0x7, 0x2b, 0x2, 0x2, 0x1e, 0x8, 0x3, 0x2, 0x2, 
    0x2, 0x1f, 0x20, 0x7, 0x2c, 0x2, 0x2, 0x20, 0xa, 0x3, 0x2, 0x2, 0x2, 
    0x21, 0x22, 0x7, 0x31, 0x2, 0x2, 0x22, 0xc, 0x3, 0x2, 0x2, 0x2, 0x23, 
    0x24, 0x7, 0x2d, 0x2, 0x2, 0x24, 0xe, 0x3, 0x2, 0x2, 0x2, 0x25, 0x26, 
    0x7, 0x2f, 0x2, 0x2, 0x26, 0x10, 0x3, 0x2, 0x2, 0x2, 0x27, 0x29, 0x9, 
    0x2, 0x2, 0x2, 0x28, 0x27, 0x3, 0x2, 0x2, 0x2, 0x29, 0x2a, 0x3, 0x2, 
    0x2, 0x2, 0x2a, 0x28, 0x3, 0x2, 0x2, 0x2, 0x2a, 0x2b, 0x3, 0x2, 0x2, 
    0x2, 0x2b, 0x12, 0x3, 0x2, 0x2, 0x2, 0x2c, 0x2e, 0x9, 0x3, 0x2, 0x2, 
    0x2d, 0x2c, 0x3, 0x2, 0x2, 0x2, 0x2e, 0x2f, 0x3, 0x2, 0x2, 0x2, 0x2f, 
    0x2d, 0x3, 0x2, 0x2, 0x2, 0x2f, 0x30, 0x3, 0x2, 0x2, 0x2, 0x30, 0x14, 
    0x3, 0x2, 0x2, 0x2, 0x31, 0x33, 0x7, 0xf, 0x2, 0x2, 0x32, 0x31, 0x3, 
    0x2, 0x2, 0x2, 0x32, 0x33, 0x3, 0x2, 0x2, 0x2, 0x33, 0x34, 0x3, 0x2, 
    0x2, 0x2, 0x34, 0x35, 0x7, 0xc, 0x2, 0x2, 0x35, 0x16, 0x3, 0x2, 0x2, 
    0x2, 0x36, 0x38, 0x9, 0x4, 0x2, 0x2, 0x37, 0x36, 0x3, 0x2, 0x2, 0x2, 
    0x38, 0x39, 0x3, 0x2, 0x2, 0x2, 0x39, 0x37, 0x3, 0x2, 0x2, 0x2, 0x39, 
    0x3a, 0x3, 0x2, 0x2, 0x2, 0x3a, 0x3b, 0x3, 0x2, 0x2, 0x2, 0x3b, 0x3c, 
    0x8, 0xc, 0x2, 0x2, 0x3c, 0x18, 0x3, 0x2, 0x2, 0x2, 0x7, 0x2, 0x2a, 
    0x2f, 0x32, 0x39, 0x3, 0x8, 0x2, 0x2, 
  };

  atn::ATNDeserializer deserializer;
  _atn = deserializer.deserialize(_serializedATN);

  size_t count = _atn.getNumberOfDecisions();
  _decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    _decisionToDFA.emplace_back(_atn.getDecisionState(i), i);
  }
}

LabeledExprLexer::Initializer LabeledExprLexer::_init;

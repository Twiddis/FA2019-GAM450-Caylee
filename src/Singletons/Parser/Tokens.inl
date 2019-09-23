// Index of possible tokens
//   These are defined these way to make it easier to associate an enumeration value
//   to a specific token string

TOKEN(Invalid, "InvalidToken")

TOKEN(LabelName, "LabelName")
TOKEN(RegisterName, "LabelName")
TOKEN(Literal, "Literal")
TOKEN(Whitespace, "Whitespace")

// Symbols
TOKEN(_SYMBOLS, "SymbolStart")
TOKEN(Colon, ":")
TOKEN(Hashtag, "#")

// Instruction names
TOKEN(_KEYWORDS, "KeywordStart")
TOKEN(NoOperation, "NOP")
TOKEN(Call, "CALL")
TOKEN(Return, "RET")
TOKEN(Move, "MOV")
TOKEN(Jump, "JMP")
TOKEN(Add, "ADD")
TOKEN(Subtract, "SUB")
TOKEN(Negate, "NEG")
TOKEN(JumpIfNegative, "JNEG")
TOKEN(JumppIfPositive, "JPOS")
TOKEN(JumpIfZero, "JZERO")

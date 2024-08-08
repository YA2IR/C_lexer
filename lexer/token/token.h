#define FOREACH_TOKEN_T(TOKEN_T) \
        TOKEN_T(ILLEGAL)   \
        TOKEN_T(t_EOF)  \
        TOKEN_T(IDENT)   \
		TOKEN_T(NUM) \
        TOKEN_T(STR) \
        TOKEN_T(PLUS)  \
        TOKEN_T(MINUS)  \
        TOKEN_T(BANG)  \
        TOKEN_T(Q_MARK)  \
        TOKEN_T(STAR)  \
        TOKEN_T(CHAR_LITERAL) \
        TOKEN_T(DIV)  \
        TOKEN_T(LT)  \
        TOKEN_T(GT)  \
        TOKEN_T(COMMA)  \
        TOKEN_T(SEMICOLON)  \
        TOKEN_T(COLON)  \
        TOKEN_T(LPAREN)  \
        TOKEN_T(RPAREN)  \
        TOKEN_T(LBRACE)  \
        TOKEN_T(RBRACE)  \
		TOKEN_T(LBRACK)  \
        TOKEN_T(RBRACK)  \
        TOKEN_T(S_QUOTE)  \
        TOKEN_T(D_QUOTE)  \
        TOKEN_T(ASSIGN)  \
        TOKEN_T(EQ)  \
        TOKEN_T(NOT_EQ)  \
        TOKEN_T(GT_EQ)  \
        TOKEN_T(LT_EQ)  \
        TOKEN_T(INC)  \
        TOKEN_T(DEC)  \
        TOKEN_T(STAR_EQ)  \
        TOKEN_T(PLUS_EQ)  \
        TOKEN_T(MINUS_EQ)  \
        TOKEN_T(DIV_EQ)  \
        TOKEN_T(MOD_EQ)  \
        TOKEN_T(BIT_AND_EQ)  \
        TOKEN_T(BIT_XOR_EQ)  \
        TOKEN_T(BIT_OR_EQ)  \
        TOKEN_T(LSHIFT_EQ)  \
        TOKEN_T(RSHIFT_EQ)  \
        TOKEN_T(PERCENT)  \
        TOKEN_T(AND)  \
        TOKEN_T(OR)  \
        TOKEN_T(BIT_AND)  \
        TOKEN_T(BIT_OR)  \
        TOKEN_T(BIT_NOT)  \
        TOKEN_T(BIT_XOR)  \
        TOKEN_T(LSHIFT)  \
        TOKEN_T(RSHIFT)  \
	/* KEYWORDS ===> by C17 standard (ISO/IEC 9899:2017) */\
        TOKEN_T(AUTO)  \
        TOKEN_T(BREAK)  \
        TOKEN_T(CASE)  \
        TOKEN_T(CHAR)  \
        TOKEN_T(CONST)  \
        TOKEN_T(CONTINUE)  \
        TOKEN_T(DEFAULT)  \
        TOKEN_T(DO)  \
        TOKEN_T(DOUBLE)  \
        TOKEN_T(ELSE)  \
        TOKEN_T(ENUM)  \
        TOKEN_T(EXTERN)  \
        TOKEN_T(FLOAT)  \
        TOKEN_T(FOR)  \
        TOKEN_T(GOTO)  \
        TOKEN_T(IF)  \
        TOKEN_T(INLINE)  \
        TOKEN_T(INT)  \
        TOKEN_T(LONG)  \
        TOKEN_T(REGISTER)  \
        TOKEN_T(RESTRICT)  \
        TOKEN_T(RETURN)  \
        TOKEN_T(SHORT)  \
        TOKEN_T(SIGNED)  \
        TOKEN_T(SIZEOF)  \
        TOKEN_T(STATIC)  \
        TOKEN_T(STRUCT)  \
        TOKEN_T(SWITCH)  \
        TOKEN_T(TYPEDEF)  \
        TOKEN_T(UNION)  \
        TOKEN_T(UNSIGNED)  \
        TOKEN_T(VOID)  \
        TOKEN_T(VOLATILE)  \
        TOKEN_T(WHILE)  \
        TOKEN_T(_ALIGNAS)  \
        TOKEN_T(_ALIGNOF)  \
        TOKEN_T(_ATOMIC)  \
        TOKEN_T(_BOOL)  \
        TOKEN_T(_COMPLEX)  \
        TOKEN_T(_GENERIC)  \
        TOKEN_T(_IMAGINARY)  \
        TOKEN_T(_NORETURN)  \
        TOKEN_T(_STATIC_ASSERT)  \
        TOKEN_T(_THREAD_LOCAL)  \




#define GENERATE_ENUM(ENUM) ENUM,

#define GENERATE_STRING(STRING) #STRING,

typedef enum  {
    FOREACH_TOKEN_T(GENERATE_ENUM)
} token_t;
static const char *enum_str[] = {
    FOREACH_TOKEN_T(GENERATE_STRING)
};

struct token {
	token_t type;
	char* literal;
} typedef token;


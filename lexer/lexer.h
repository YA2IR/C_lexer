#include "token/token.h"
#include <stdlib.h>
#include <stdbool.h>

struct lexer {
    char *inpt;
    size_t len_inpt;
    size_t pos;
    size_t next_pos;
    char ch ;
} typedef lexer;

lexer* init_lexer(char* inpt);
void read_char(lexer* l);
token next_token(lexer* l);

token new_token(token_t type, char* literal);
token new_char_token(token_t type, char literal);
token tokenize_n_chars(lexer *l, token_t type, int n);

char* read_ident(lexer* l);
token_t ident_or_keyword(char* literal);
char* tokenize_str(lexer *l);
char* get_substring(lexer *l, int init_pos);

char* read_num(lexer* l);

char peek_char(lexer* l);
char double_peek_char(lexer *l);

void consume_ws(lexer* l);
bool is_letter(char ch);
bool is_digit(char ch);
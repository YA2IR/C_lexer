#include "lexer.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>


lexer* init_lexer(char* inpt) {
    lexer* l = (lexer*)malloc(sizeof(lexer));
    l->inpt = inpt;
    l->len_inpt = strlen(inpt);
    l->pos = 0;
    l->next_pos = 0;
    read_char(l);
    return l;
}

void read_char(lexer* l) {
    if (l->pos == l->len_inpt) 
        l->ch = 0;
    else {
       	l->ch = l->inpt[l->next_pos]; 
    	l->pos = l->next_pos;
    	l->next_pos++;
	}
}


token next_token(lexer* l) {
    token t;
    consume_ws(l);

    switch (l->ch) {
    default:
        if (is_letter(l->ch)) {
            t.literal = read_ident(l);
            t.type = ident_or_keyword(t.literal);            
            return t;
        } else if (is_digit(l->ch)) {
            t.literal = read_num(l);
            if(!t.literal) // nullptr returned on error
                return new_char_token(ILLEGAL, l->ch);
            t.type = NUM;
            return t;
        } else 
            return new_char_token(ILLEGAL, l->ch);
    case '=':
		if (peek_char(l) == '=')
			t = tokenize_n_chars(l, EQ, 2); 
		else 
			t = new_char_token(ASSIGN, l->ch);
        break;
    case '!':
		if (peek_char(l) == '=')
			t = tokenize_n_chars(l, NOT_EQ, 2);
		else
			t = new_char_token(BANG, l->ch);
        break;
    case ':':
        t = new_char_token(COLON, l->ch); break;
    case ';':
        t = new_char_token(SEMICOLON, l->ch); break;
    case '/':
        if (peek_char(l) == '=') 
            t = tokenize_n_chars(l, DIV_EQ,2);
        else
		    t = new_char_token(DIV, l->ch); break;
        break;
	case '*':
        if (peek_char(l) == '=') 
            t = tokenize_n_chars(l, STAR_EQ,2);
        else
		    t = new_char_token(STAR, l->ch); 
        break;
    case '%':
        if (peek_char(l) == '=') 
            t = tokenize_n_chars(l, MOD_EQ,2);
        else
		    t = new_char_token(PERCENT, l->ch); 
        break;
	case '<':
        if (peek_char(l) == '<')
            if(double_peek_char(l) == '=')
                t = tokenize_n_chars(l, LSHIFT_EQ, 3); 
		    else
               t = tokenize_n_chars(l, LSHIFT,2);
        else if(peek_char(l) == '=')
			t = tokenize_n_chars(l, LT_EQ,2);
        else {
		    t = new_char_token(LT, l->ch); 
        }
        break;
	case '>':
		if (peek_char(l) == '>')
            if(double_peek_char(l) == '=')
                t = tokenize_n_chars(l, RSHIFT_EQ,3);
		    else
                t = tokenize_n_chars(l, RSHIFT,2);
        else if(peek_char(l) == '=')
			t = tokenize_n_chars(l, GT_EQ,2);
        else
		    t = new_char_token(GT, l->ch); 
        break;
    case '^':
        if(peek_char(l) == '=')
            t = tokenize_n_chars(l, BIT_XOR_EQ,2);
        else
            t = new_char_token(BIT_XOR, l->ch);
        break;
    case '|':
        if (peek_char(l) == '|')
            t = tokenize_n_chars(l, OR,2);
        else if(peek_char(l) == '=')
            t = tokenize_n_chars(l, BIT_OR_EQ,2);
        else
		    t = new_char_token(BIT_OR, l->ch); 
        break;
    case '&':
        if (peek_char(l) == '&') 
            t = tokenize_n_chars(l, AND,2);
        else if(peek_char(l) == '=')
            t = tokenize_n_chars(l, BIT_AND_EQ,2);
        else
		    t = new_char_token(BIT_AND, l->ch); 
        break;
    case '~':
		t = new_char_token(BIT_NOT, l->ch); break;
	case '(':
		t = new_char_token(LPAREN, l->ch); break;
	case ')':
		t = new_char_token(RPAREN, l->ch); break;
	case ',':
		t = new_char_token(COMMA, l->ch); break;
	case '+': 
        if (peek_char(l) == '+')
            t = tokenize_n_chars(l, INC,2);
        else if (peek_char(l) == '=')
            t = tokenize_n_chars(l, PLUS_EQ,2);
        else
		    t = new_char_token(PLUS, l->ch); 
        break;
    case '-':
        if (peek_char(l) == '-')
            t = tokenize_n_chars(l, DEC,2);
        else if (peek_char(l) == '=')
            t = tokenize_n_chars(l, MINUS_EQ,2);
        else
		    t = new_char_token(MINUS, l->ch); 
        break;
	case '{':
		t = new_char_token(LBRACE, l->ch); break;
	case '}':
		t = new_char_token(RBRACE, l->ch); break;
    case '[':
		t = new_char_token(LBRACK, l->ch); break;
	case ']':
		t = new_char_token(RBRACK, l->ch); break;
    case '\0': // EOF
        t = new_char_token(t_EOF, l->ch); break;
    case '\'':
        if(double_peek_char(l) == '\'')
            t = tokenize_n_chars(l, CHAR_LITERAL,3);
        else if(peek_char(l) == '\\') {// e.g '\n'
            char literal[5];
            for (int i = 0; i < 5; i++) {
                literal[i] = l->ch;
                read_char(l);
            }
            literal[4] = '\0';
            if (literal[3] != '\'') 
                t = new_char_token(ILLEGAL, literal[3]); 
            else 
                t = (token){.literal = strdup(literal), .type = CHAR_LITERAL};
        } else 
            t = new_char_token(ILLEGAL, l->ch); 
        break;
    case '"':
        t.literal = tokenize_str(l);
        t.type = STR;
        break;
    case '?':
        t = new_char_token(Q_MARK, l->ch); break;
    }

    read_char(l);
    return t;
}

token tokenize_n_chars(lexer *l, token_t type, int n) {
    char literal[n+1];
    for (int i = 0; i < n; i++) {
        literal[i] = l->ch;
        read_char(l);
    }
    literal[n] = '\0';
    return (token){.literal = strdup(literal), .type = type}; 
}

token new_char_token(token_t type, char literal){
    char str[2] = {literal, '\0'};
    return (token) {
        .type = type,
        .literal = strdup(str),
    };
}

char* read_ident(lexer* l) {
    int pos = l->pos;

    while (is_letter(l->ch) || is_digit(l->ch)) 
        read_char(l);

    return get_substring(l, pos);
}


char* read_num(lexer* l) {

    int pos = l->pos;

    if(l->ch != '0') { // decimal

        bool dot_exists = false; 
        while (is_digit(l->ch)) {
            read_char(l); 
            if(l->ch == '.' && !dot_exists) {
                dot_exists = true;
                read_char(l);
            } }
        // validating suffixes
        if (is_letter(l->ch)) {
            
            if (dot_exists && (l->ch == 'f' || l->ch == 'l'))  // allow 1.0l and 1.0f
                    read_char(l);
            else { // allow 1l, 1ull and such.. currently, they are only lowercase.
                char allowed_suff[] = "ull"; 
                for (int i = 0; i < 3; i++) 
                    if (l->ch == allowed_suff[i]) 
                        read_char(l);
            } 
        } 

    } else if (peek_char(l) == 'x') { //hex
        	read_char(l);
        	read_char(l);
        	while(isxdigit(l->ch)) 
            	read_char(l);
    } else { // oct
        while('0' <= l->ch && l->ch <= '7')
            read_char(l);
        if(is_digit(l->ch)) // 8,9 ..
            return NULL;
    }

    if (is_letter(l->ch)) 
        return NULL;

    return get_substring(l, pos);
}

char* tokenize_str(lexer *l) {
    int pos = l->pos;
    read_char(l); // consume opening "
    while (l->ch != '"') 
        read_char(l);
    read_char(l); // consume closing "
    
   return get_substring(l, pos);
}

char peek_char(lexer* l){
    if(l->next_pos >= l->len_inpt)
        return 0;
    else
        return l->inpt[l->next_pos];
}

char double_peek_char(lexer *l) {
    if(l->next_pos+1 >= l->len_inpt)
        return 0;
    else
        return l->inpt[l->next_pos+1];
}

void consume_ws(lexer* l){
    while (l->ch == ' ' || l->ch == '\t' ||
             l->ch == '\n' || l->ch == '\r') 
	    read_char(l);	
}

char* get_substring(lexer *l, int init_pos) {

    int str_len = l->pos - init_pos;
    char str[str_len + 1];

    for (int i = 0; init_pos < l->pos; init_pos++) 
        str[i++] = l->inpt[init_pos];

    str[str_len] = '\0'; 
    return strdup(str);
}

token_t ident_or_keyword(char* literal){
    /* instead of a hash map */
    switch (literal[0]) {
        case 'a':
            if(strcmp(literal, "auto") == 0)
                    return AUTO;
            break; 
        case 'b':
            if(strcmp(literal, "break") == 0)
                    return BREAK;
            break; 
        case 'c':
            if(strcmp(literal, "char") == 0)
                    return CHAR;
            if(strcmp(literal, "case") == 0)
                    return CASE;
            if(strcmp(literal, "const") == 0)
                    return CONST;
            if(strcmp(literal, "continue") == 0)
                    return CONTINUE;
        case 'd':
            if(strcmp(literal, "double") == 0)
                    return DOUBLE;
            if(strcmp(literal, "default") == 0)
                    return DEFAULT;
            if(strcmp(literal, "do") == 0)
                    return DO;
        case 'e':
            if(strcmp(literal, "else") == 0)
                    return ELSE;
            if(strcmp(literal, "extern") == 0)
                    return EXTERN;
            if(strcmp(literal, "enum") == 0)
                    return ENUM;
            break; 
        case 'f':
            if(strcmp(literal, "for") == 0)
                    return FOR;
            if(strcmp(literal, "float") == 0)
                    return FLOAT;
            break;
        case 'i':
            if(strcmp(literal, "int") == 0)
                return INT;
            if(strcmp(literal, "if") == 0)
                return IF;
            if(strcmp(literal, "inline") == 0)
                return INLINE;
            break;
        case 'l':
            if(strcmp(literal, "long") == 0)
                return LONG;
            break;
        case 'r':
            if (strcmp(literal, "return") == 0)
                return RETURN;
            if(strcmp(literal, "restrict") == 0)
                return RESTRICT;
            if(strcmp(literal, "register") == 0)
                return REGISTER;
            break;
        case 's':
            if (strcmp(literal, "sizeof") == 0)
                return SIZEOF;
            if (strcmp(literal, "struct") == 0)
                return STRUCT;
            if (strcmp(literal, "static") == 0)
                return STATIC;
            if (strcmp(literal, "short") == 0)
                return SHORT;
            if (strcmp(literal, "switch") == 0)
                return SWITCH;
            if (strcmp(literal, "signed") == 0)
                return SIGNED;
            break;
        case 't':
            if (strcmp(literal, "typedef") == 0)
                return TYPEDEF;
            break;
        case 'u':
            if (strcmp(literal, "unsigned") == 0)
                return UNSIGNED;
            if (strcmp(literal, "union") == 0)
                return UNION;
            break;
        case 'v':
            if (strcmp(literal, "void") == 0)
                    return VOID;
            if (strcmp(literal, "volatile") == 0)
                    return VOLATILE;
            break;
        case 'w':
            if (strcmp(literal, "while") == 0)
                    return WHILE;
            break;
        case '_': // rare
            if (strcmp(literal, "_Alignas") == 0)
                    return _ALIGNAS;
            if (strcmp(literal, "_Alignof") == 0)
                    return _ALIGNOF;
            if (strcmp(literal, "_Atomic") == 0)
                    return _ATOMIC;
            if (strcmp(literal, "_Bool") == 0)
                    return _BOOL;
            if (strcmp(literal, "_Complex") == 0)
                    return _COMPLEX;
            if (strcmp(literal, "_Generic") == 0)
                    return _GENERIC;
            if (strcmp(literal, "_Imaginary") == 0)
                return _IMAGINARY;
            if (strcmp(literal, "_Noreturn") == 0)
                    return _NORETURN;
            if (strcmp(literal, "_Static_assert") == 0)
                    return _STATIC_ASSERT;
            if (strcmp(literal, "_Thread_local") == 0)
                    return _THREAD_LOCAL;
            break;

    }
    return IDENT;
}

bool is_letter(char ch){
    return isalpha((unsigned char)ch) || (ch == '_');
}

bool is_digit(char ch){
   return '0' <= ch && ch <= '9';
}

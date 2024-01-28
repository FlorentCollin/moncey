#pragma once

#include <sys/types.h>
#include "ma.h"

/*********/
/* TOKEN */
/*********/

typedef enum {
	TokenType_Illegal,
	TokenType_EOF,
	TokenType_Ident,
	TokenType_Int,
	TokenType_Assign,
	TokenType_Plus,
	TokenType_Minus,
	TokenType_Bang,
	TokenType_Asterisk,
	TokenType_Slash,
	TokenType_Eq,
	TokenType_NotEq,
	TokenType_LT,
	TokenType_GT,
	TokenType_Comma,
	TokenType_Semicolon,
	TokenType_LParen,
	TokenType_RParen,
	TokenType_LBrace,
	TokenType_RBrace,
	TokenType_Function,
	TokenType_Let,
	TokenType_If,
	TokenType_Else,
	TokenType_True,
	TokenType_False,
	TokenType_Return,
} TokenType;

typedef struct {
	TokenType type;
	Ma_StringView literal;
} Token;

void token_print_stdout(Token* token);

typedef struct {
	Ma_StringView key;
	TokenType value;
} Keyword;

TokenType token_lookup_ident(Ma_StringView indent); 

/*********/
/* LEXER */
/*********/

typedef struct {
	Ma_StringView input;
	uint position; // current position in input (points to the current char)
	uint read_position; // current reading position in input (after current char)
	uint8_t ch; // current char under examination (ch = char)
} Lexer;

Lexer lexer_init(Ma_StringView input);
void lexer_read_char(Lexer* l);
uint8_t lexer_peek_char(Lexer* l);
Token lexer_next_token(Lexer* l);
void lexer_skip_whitespace(Lexer* l);
Ma_StringView lexer_read_identifier(Lexer* l);
Ma_StringView lexer_read_number(Lexer* l);

bool is_letter(uint8_t ch);
bool is_digit(uint8_t ch);

/**********/
/* PARSER */
/**********/
typedef struct {
	Ma_StringView* data;	
	size_t length;
	size_t capacity;
} ParserErrors;

void parser_errors_free(ParserErrors errors);  

typedef struct {

} Program;

typedef struct {
	Lexer* lexer;
	Token current_token;
	Token peek_token;
	ParserErrors errors;
} Parser;

Parser parser_init(Lexer* lexer);
void parser_free(Parser* p);
void parser_next_token(Parser* p);
bool parser_current_token_is(Parser* p, TokenType type);
Program parser_parse_program(Parser* p);

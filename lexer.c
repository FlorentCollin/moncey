#include "ma.h"
#include "monkey.h"

Lexer lexer_init(Ma_StringView input) {
	Lexer l = { .input = input };
	lexer_read_char(&l);
	return l;
}

void lexer_read_char(Lexer* l) {
	if (l->read_position >= l->input.length) {
		l->ch = 0;
	} else {
		l->ch = l->input.data[l->read_position];
	}

	l->position = l->read_position;
	l->read_position += 1;
}

uint8_t lexer_peek_char(Lexer* l) {
	if (l->read_position >= l->input.length) {
		return 0;
	} 

	return l->input.data[l->read_position];
}

Token lexer_next_token(Lexer* l) {
	Token token = {0};
	token.literal.length = 1;

	lexer_skip_whitespace(l);
	switch (l->ch) {
		case '=':
			if (lexer_peek_char(l) == '=') {
				lexer_read_char(l);
				token.type = TokenType_Eq;
				token.literal.length = 2;
				token.literal.data = "==";
			} else {
				token.type = TokenType_Assign;
				token.literal.data = "=";
			}
		break;
		case ';':
			token.type = TokenType_Semicolon;
			token.literal.data = ";";
		break;
		case ',':
			token.type = TokenType_Comma;
			token.literal.data = ",";
		case '(':
			token.type = TokenType_LParen;
			token.literal.data = "(";
		break;
		case ')':
			token.type = TokenType_RParen;
			token.literal.data = ")";
		break;
		case '{':
			token.type = TokenType_LBrace;
			token.literal.data = "{";
		break;
		case '}':
			token.type = TokenType_RBrace;
			token.literal.data = "}";
		break;
		case '+':
			token.type = TokenType_Plus;
			token.literal.data = "+";
		break;
		case '-':
			token.type = TokenType_Minus;
			token.literal.data = "-";
		break;
		case '*':
			token.type = TokenType_Asterisk;
			token.literal.data = "*";
		break;
		case '/':
			token.type = TokenType_Slash;
			token.literal.data = "/";
		break;
		case '!':
			if (lexer_peek_char(l) == '=') {
				lexer_read_char(l);
				token.type = TokenType_NotEq;
				token.literal.length = 2;
				token.literal.data = "!=";
			} else {
				token.type = TokenType_Bang;
				token.literal.data = "!";
			}
		break;
		case '<':
			token.type = TokenType_LT;
			token.literal.data = "<";
		break;
		case '>':
			token.type = TokenType_GT;
			token.literal.data = ">";
		break;
		case 0:
			token.type = TokenType_EOF;
			token.literal.length = 0;
		break;
		default:
			if (is_letter(l->ch)) {
				token.literal = lexer_read_identifier(l);
				token.type = token_lookup_ident(token.literal);
				return token; // so we don't read another character
			} else if (is_digit(l->ch)) {
				token.type = TokenType_Int;
				token.literal = lexer_read_number(l);
				return token; // so we don't read another character
		}
	}

	lexer_read_char(l);
	return token;
}

void lexer_skip_whitespace(Lexer* l) {
	while (l->ch == ' ' || l->ch == '\t' || l->ch == '\n' || l->ch == '\r') {
		lexer_read_char(l);
	}
}

Ma_StringView lexer_read_identifier(Lexer* l) {
	size_t start = l->position;
	while (is_letter(l->ch)) {
		lexer_read_char(l);
	}

	return ma_stringview_sub(l->input, (Ma_StringViewPosition) {.start = start, .end = l->position});
}

Ma_StringView lexer_read_number(Lexer* l) {
	size_t start = l->position;
	while (is_digit(l->ch)) {
		lexer_read_char(l);
	}

	return ma_stringview_sub(l->input, (Ma_StringViewPosition) {.start = start, .end = l->position});
}

bool is_letter(uint8_t ch) {
	return ('a' <= ch && ch <= 'z') || ('A' <= ch && ch <= 'Z') || ch == '_';
}

bool is_digit(uint8_t ch) {
	return '0' <= ch && ch <= '9';
}

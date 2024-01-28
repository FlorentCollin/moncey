#include <stdio.h>

#include "monkey.h"
#include "ma.h"

const Keyword TOKEN_KEYWORDS[] = {
	{.key = {.length = 3, .data = "let"},    .value = TokenType_Let},
	{.key = {.length = 2, .data = "fn"},     .value = TokenType_Function},
	{.key = {.length = 4, .data = "true"},   .value = TokenType_True},
	{.key = {.length = 4, .data = "false"},  .value = TokenType_False},
	{.key = {.length = 2, .data = "if"},     .value = TokenType_If},
	{.key = {.length = 4, .data = "else"},   .value = TokenType_Else},
	{.key = {.length = 6, .data = "return"}, .value = TokenType_Return},
};

void token_print_stdout(Token* token) {
	char* type = "";
	switch (token->type) {
		case TokenType_Illegal:
			type = "Illegal";
			break;
		case TokenType_EOF:
			type = "EOF";
			break;
		case TokenType_Ident:
			type = "Ident";
			break;
		case TokenType_Int:
			type = "Int";
			break;
		case TokenType_Assign:
			type = "Assign";
			break;
		case TokenType_Plus:
			type = "Plus";
			break;
		case TokenType_Minus:
			type = "Minus";
			break;
		case TokenType_Bang:
			type = "Bang";
			break;
		case TokenType_Asterisk:
			type = "Asterisk";
			break;
		case TokenType_Slash:
			type = "Slash";
			break;
		case TokenType_Eq:
			type = "Eq";
			break;
		case TokenType_NotEq:
			type = "NotEq";
			break;
		case TokenType_LT:
			type = "LT";
			break;
		case TokenType_GT:
			type = "GT";
			break;
		case TokenType_Comma:
			type = "Comma";
			break;
		case TokenType_Semicolon:
			type = "Semicolon";
			break;
		case TokenType_LParen:
			type = "LParen";
			break;
		case TokenType_RParen:
			type = "RParen";
			break;
		case TokenType_LBrace:
			type = "LBrace";
			break;
		case TokenType_RBrace:
			type = "RBrace";
			break;
		case TokenType_Function:
			type = "Function";
			break;
		case TokenType_Let:
			type = "Let";
			break;
		case TokenType_If:
			type = "If";
			break;
		case TokenType_Else:
			type = "Else";
			break;
		case TokenType_True:
			type = "True";
			break;
		case TokenType_False:
			type = "False";
			break;
		case TokenType_Return:
			type = "Return";
			break;
	}

	printf("Token{type = %s, literal = %.*s}", type, (int)token->literal.length, token->literal.data);
}

TokenType token_lookup_ident(Ma_StringView indent) { size_t length =
	sizeof(TOKEN_KEYWORDS) / sizeof(TOKEN_KEYWORDS[0]);
	for (size_t i = 0; i < length; i++) {
		if (ma_stringview_eq(indent, TOKEN_KEYWORDS[i].key)) {
			return TOKEN_KEYWORDS[i].value;
		}
	}

	return TokenType_Ident;
}

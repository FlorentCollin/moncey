#include "monkey.h"
#include "ma.h"

void parser_errors_free(ParserErrors errors) {
	free(errors.data);
}

Parser parser_init(Lexer* lexer) {
	Parser p = {0};
	p.lexer = lexer;
	parser_next_token(&p);
	parser_next_token(&p);

	return p;
}

void parser_free(Parser* p) {
	parser_errors_free(p->errors);
}

void parser_next_token(Parser *p) {
	p->current_token = p->peek_token;
	p->peek_token = lexer_next_token(p->lexer);
}

bool parser_current_token_is(Parser* p, TokenType type) {
	return p->current_token.type == type;
}

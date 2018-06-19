/* Generated by lx */

#include <assert.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <errno.h>

#include LX_HEADER

static enum lx_token z0(struct lx *lx);
static enum lx_token z1(struct lx *lx);
static enum lx_token z2(struct lx *lx);
static enum lx_token z3(struct lx *lx);
static enum lx_token z4(struct lx *lx);

#if __STDC_VERSION__ >= 199901L
inline
#endif
static int
lx_getc(struct lx *lx)
{
	int c;

	assert(lx != NULL);
	assert(lx->lgetc != NULL);

	if (lx->c != EOF) {
		c = lx->c, lx->c = EOF;
	} else {
		c = lx->lgetc(lx);
		if (c == EOF) {
			return EOF;
		}
	}

	lx->end.byte++;
	lx->end.col++;

	if (c == '\n') {
		lx->end.line++;
		lx->end.col = 1;
	}

	return c;
}

#if __STDC_VERSION__ >= 199901L
inline
#endif
static void
lx_ungetc(struct lx *lx, int c)
{
	assert(lx != NULL);
	assert(lx->c == EOF);

	lx->c = c;


	lx->end.byte--;
	lx->end.col--;

	if (c == '\n') {
		lx->end.line--;
		lx->end.col = 0; /* XXX: lost information */
	}
}

int
lx_fgetc(struct lx *lx)
{
	assert(lx != NULL);
	assert(lx->getc_opaque != NULL);

	return fgetc(lx->getc_opaque);
}

int
lx_dynpush(void *buf_opaque, char c)
{
	struct lx_dynbuf *t = buf_opaque;

	assert(t != NULL);

	if (t->p == t->a + t->len) {
		size_t len;
		ptrdiff_t off;
		char *tmp;

		if (t->len == 0) {
			assert(LX_DYN_LOW > 0);
			len = LX_DYN_LOW;
		} else {
			len = t->len * LX_DYN_FACTOR;
			if (len < t->len) {
				errno = ERANGE;
				return -1;
			}
		}

		off = t->p - t->a;
		tmp = realloc(t->a, len);
		if (tmp == NULL) {
			return -1;
		}

		t->p   = tmp + off;
		t->a   = tmp;
		t->len = len;
	}

	assert(t->p != NULL);
	assert(t->a != NULL);

	*t->p++ = c;

	return 0;
}

int
lx_dynclear(void *buf_opaque)
{
	struct lx_dynbuf *t = buf_opaque;

	assert(t != NULL);

	if (t->len > LX_DYN_HIGH) {
		size_t len;
		char *tmp;

		len = t->len / LX_DYN_FACTOR;

		tmp = realloc(t->a, len);
		if (tmp == NULL) {
			return -1;
		}

		t->a   = tmp;
		t->len = len;
	}

	t->p = t->a;

	return 0;
}

void
lx_dynfree(void *buf_opaque)
{
	struct lx_dynbuf *t = buf_opaque;

	assert(t != NULL);

	free(t->a);
}
static enum lx_token
z0(struct lx *lx)
{
	int c;

	enum {
		S0, S1, S2, NONE
	} state;

	assert(lx != NULL);

	if (lx->clear != NULL) {
		lx->clear(lx->buf_opaque);
	}

	state = NONE;

	lx->start = lx->end;

	while (c = lx_getc(lx), c != EOF) {
		if (state == NONE) {
			state = S0;
		}

		switch (state) {
		case S0: /* start */
			switch ((unsigned char) c) {
			case '\x2f': state = S2; break;
			default: state = S1; break;
			}
			break;

		case S1: /* e.g. "a" */
			lx_ungetc(lx, c); return TOK_CHAR;

		case S2: /* e.g. "\x2f" */
			switch ((unsigned char) c) {
			case 'A':
			case 'B':
			case 'C':
			case 'D':
			case 'E':
			case 'F':
			case 'G':
			case 'H':
			case 'I':
			case 'J':
			case 'K':
			case 'L':
			case 'M':
			case 'N':
			case 'O':
			case 'P':
			case 'Q':
			case 'R':
			case 'S':
			case 'T':
			case 'U':
			case 'V':
			case 'W':
			case 'X':
			case 'Y':
			case 'Z': break;
			case 'a':
			case 'b':
			case 'c':
			case 'd':
			case 'e':
			case 'f':
			case 'g':
			case 'h':
			case 'i':
			case 'j':
			case 'k':
			case 'l':
			case 'm':
			case 'n':
			case 'o':
			case 'p':
			case 'q':
			case 'r':
			case 's':
			case 't':
			case 'u':
			case 'v':
			case 'w':
			case 'x':
			case 'y':
			case 'z': break;
			default:  lx_ungetc(lx, c); return lx->z = z4, TOK_RE;
			}
			break;

		default:
			; /* unreached */
		}

		if (lx->push != NULL) {
			if (-1 == lx->push(lx->buf_opaque, c)) {
				return TOK_ERROR;
			}
		}
	}

	lx->lgetc = NULL;

	switch (state) {
	case NONE: return TOK_EOF;
	case S1: return TOK_CHAR;
	case S2: return TOK_RE;
	default: errno = EINVAL; return TOK_ERROR;
	}
}

static enum lx_token
z1(struct lx *lx)
{
	int c;

	enum {
		S0, S1, S2, S3, S4, S5, S6, S7, NONE
	} state;

	assert(lx != NULL);

	if (lx->clear != NULL) {
		lx->clear(lx->buf_opaque);
	}

	state = NONE;

	lx->start = lx->end;

	while (c = lx_getc(lx), c != EOF) {
		if (state == NONE) {
			state = S0;
		}

		switch (state) {
		case S0: /* start */
			switch ((unsigned char) c) {
			case '"': state = S2; break;
			case '\\': state = S3; break;
			default: state = S1; break;
			}
			break;

		case S1: /* e.g. "a" */
			lx_ungetc(lx, c); return TOK_CHAR;

		case S2: /* e.g. """ */
			lx_ungetc(lx, c); return lx->z = z4, TOK_STR;

		case S3: /* e.g. "\\" */
			switch ((unsigned char) c) {
			case '"': state = S4; break;
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7': state = S5; break;
			case '\\': state = S4; break;
			case 'f': state = S4; break;
			case 'n': state = S4; break;
			case 'r': state = S4; break;
			case 't': state = S4; break;
			case 'v': state = S4; break;
			case 'x': state = S6; break;
			default:  lx_ungetc(lx, c); return TOK_CHAR;
			}
			break;

		case S4: /* e.g. "\\f" */
			lx_ungetc(lx, c); return TOK_ESC;

		case S5: /* e.g. "\\0" */
			switch ((unsigned char) c) {
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7': break;
			default:  lx_ungetc(lx, c); return TOK_OCT;
			}
			break;

		case S6: /* e.g. "\\x" */
			switch ((unsigned char) c) {
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9': state = S7; break;
			case 'A':
			case 'B':
			case 'C':
			case 'D':
			case 'E':
			case 'F': state = S7; break;
			case 'a':
			case 'b':
			case 'c':
			case 'd':
			case 'e':
			case 'f': state = S7; break;
			default:  lx->lgetc = NULL; return TOK_UNKNOWN;
			}
			break;

		case S7: /* e.g. "\\xa" */
			switch ((unsigned char) c) {
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9': break;
			case 'A':
			case 'B':
			case 'C':
			case 'D':
			case 'E':
			case 'F': break;
			case 'a':
			case 'b':
			case 'c':
			case 'd':
			case 'e':
			case 'f': break;
			default:  lx_ungetc(lx, c); return TOK_HEX;
			}
			break;

		default:
			; /* unreached */
		}

		if (lx->push != NULL) {
			if (-1 == lx->push(lx->buf_opaque, c)) {
				return TOK_ERROR;
			}
		}
	}

	lx->lgetc = NULL;

	switch (state) {
	case NONE: return TOK_EOF;
	case S1: return TOK_CHAR;
	case S2: return TOK_STR;
	case S3: return TOK_CHAR;
	case S4: return TOK_ESC;
	case S5: return TOK_OCT;
	case S7: return TOK_HEX;
	default: errno = EINVAL; return TOK_ERROR;
	}
}

static enum lx_token
z2(struct lx *lx)
{
	int c;

	enum {
		S0, S1, S2, NONE
	} state;

	assert(lx != NULL);

	if (lx->clear != NULL) {
		lx->clear(lx->buf_opaque);
	}

	state = NONE;

	lx->start = lx->end;

	while (c = lx_getc(lx), c != EOF) {
		if (state == NONE) {
			state = S0;
		}

		switch (state) {
		case S0: /* start */
			switch ((unsigned char) c) {
			case '\'': state = S2; break;
			default: state = S1; break;
			}
			break;

		case S1: /* e.g. "a" */
			lx_ungetc(lx, c); return TOK_CHAR;

		case S2: /* e.g. "\'" */
			lx_ungetc(lx, c); return lx->z = z4, TOK_STR;

		default:
			; /* unreached */
		}

		if (lx->push != NULL) {
			if (-1 == lx->push(lx->buf_opaque, c)) {
				return TOK_ERROR;
			}
		}
	}

	lx->lgetc = NULL;

	switch (state) {
	case NONE: return TOK_EOF;
	case S1: return TOK_CHAR;
	case S2: return TOK_STR;
	default: errno = EINVAL; return TOK_ERROR;
	}
}

static enum lx_token
z3(struct lx *lx)
{
	int c;

	enum {
		S0, S1, S2, NONE
	} state;

	assert(lx != NULL);

	if (lx->clear != NULL) {
		lx->clear(lx->buf_opaque);
	}

	state = NONE;

	lx->start = lx->end;

	while (c = lx_getc(lx), c != EOF) {
		if (state == NONE) {
			state = S0;
		}

		switch (state) {
		case S0: /* start */
			switch ((unsigned char) c) {
			case '\n': state = S2; break;
			default: state = S1; break;
			}
			break;

		case S1: /* e.g. "a" */
			lx_ungetc(lx, c); return lx->z(lx);

		case S2: /* e.g. "\n" */
			lx_ungetc(lx, c); return lx->z = z4, lx->z(lx);

		default:
			; /* unreached */
		}

		switch (state) {
		case S0:
		case S1:
		case S2:
			break;

		default:
			if (lx->push != NULL) {
				if (-1 == lx->push(lx->buf_opaque, c)) {
					return TOK_ERROR;
				}
			}
			break;

		}
	}

	lx->lgetc = NULL;

	switch (state) {
	case NONE: return TOK_EOF;
	case S1: return TOK_EOF;
	case S2: return TOK_EOF;
	default: errno = EINVAL; return TOK_ERROR;
	}
}

static enum lx_token
z4(struct lx *lx)
{
	int c;

	enum {
		S0, S1, S2, S3, S4, S5, S6, S7, S8, S9, 
		S10, S11, S12, S13, S14, S15, S16, S17, S18, S19, 
		S20, S21, S22, S23, S24, S25, S26, S27, NONE
	} state;

	assert(lx != NULL);

	if (lx->clear != NULL) {
		lx->clear(lx->buf_opaque);
	}

	state = NONE;

	lx->start = lx->end;

	while (c = lx_getc(lx), c != EOF) {
		if (state == NONE) {
			state = S0;
		}

		switch (state) {
		case S0: /* start */
			switch ((unsigned char) c) {
			case '\t':
			case '\n': state = S1; break;
			case '\r': state = S1; break;
			case ' ': state = S1; break;
			case '!': state = S2; break;
			case '"': state = S3; break;
			case '#': state = S4; break;
			case '$': state = S5; break;
			case '&': state = S6; break;
			case '\'': state = S7; break;
			case '(': state = S8; break;
			case ')': state = S9; break;
			case '*': state = S10; break;
			case '+': state = S11; break;
			case '-': state = S12; break;
			case '.': state = S13; break;
			case '\x2f': state = S14; break;
			case ';': state = S15; break;
			case '=': state = S16; break;
			case '?': state = S17; break;
			case 'A':
			case 'B':
			case 'C':
			case 'D':
			case 'E':
			case 'F':
			case 'G':
			case 'H':
			case 'I':
			case 'J':
			case 'K':
			case 'L':
			case 'M':
			case 'N':
			case 'O':
			case 'P':
			case 'Q':
			case 'R':
			case 'S':
			case 'T':
			case 'U':
			case 'V':
			case 'W':
			case 'X':
			case 'Y':
			case 'Z': state = S18; break;
			case '\\': state = S19; break;
			case '^': state = S20; break;
			case '_': state = S18; break;
			case 'a':
			case 'b':
			case 'c':
			case 'd':
			case 'e':
			case 'f':
			case 'g':
			case 'h':
			case 'i':
			case 'j':
			case 'k':
			case 'l':
			case 'm':
			case 'n':
			case 'o':
			case 'p':
			case 'q':
			case 'r':
			case 's':
			case 't':
			case 'u':
			case 'v':
			case 'w':
			case 'x':
			case 'y':
			case 'z': state = S18; break;
			case '{': state = S21; break;
			case '|': state = S22; break;
			case '}': state = S23; break;
			case '~': state = S24; break;
			default:  lx->lgetc = NULL; return TOK_UNKNOWN;
			}
			break;

		case S1: /* e.g. "\t" */
			switch ((unsigned char) c) {
			case '\t':
			case '\n': break;
			case '\r': break;
			case ' ': break;
			default:  lx_ungetc(lx, c); return lx->z(lx);
			}
			break;

		case S2: /* e.g. "!" */
			lx_ungetc(lx, c); return TOK_BANG;

		case S3: /* e.g. """ */
			lx_ungetc(lx, c); return lx->z = z1, lx->z(lx);

		case S4: /* e.g. "#" */
			lx_ungetc(lx, c); return lx->z = z3, lx->z(lx);

		case S5: /* e.g. "$" */
			switch ((unsigned char) c) {
			case 'A':
			case 'B':
			case 'C':
			case 'D':
			case 'E':
			case 'F':
			case 'G':
			case 'H':
			case 'I':
			case 'J':
			case 'K':
			case 'L':
			case 'M':
			case 'N':
			case 'O':
			case 'P':
			case 'Q':
			case 'R':
			case 'S':
			case 'T':
			case 'U':
			case 'V':
			case 'W':
			case 'X':
			case 'Y':
			case 'Z': state = S25; break;
			case '_': state = S25; break;
			case 'a':
			case 'b':
			case 'c':
			case 'd':
			case 'e':
			case 'f':
			case 'g':
			case 'h':
			case 'i':
			case 'j':
			case 'k':
			case 'l':
			case 'm':
			case 'n':
			case 'o':
			case 'p':
			case 'q':
			case 'r':
			case 's':
			case 't':
			case 'u':
			case 'v':
			case 'w':
			case 'x':
			case 'y':
			case 'z': state = S25; break;
			default:  lx->lgetc = NULL; return TOK_UNKNOWN;
			}
			break;

		case S6: /* e.g. "&" */
			lx_ungetc(lx, c); return TOK_AND;

		case S7: /* e.g. "\'" */
			lx_ungetc(lx, c); return lx->z = z2, lx->z(lx);

		case S8: /* e.g. "(" */
			lx_ungetc(lx, c); return TOK_LPAREN;

		case S9: /* e.g. ")" */
			lx_ungetc(lx, c); return TOK_RPAREN;

		case S10: /* e.g. "*" */
			lx_ungetc(lx, c); return TOK_STAR;

		case S11: /* e.g. "+" */
			lx_ungetc(lx, c); return TOK_CROSS;

		case S12: /* e.g. "-" */
			switch ((unsigned char) c) {
			case '>': state = S27; break;
			default:  lx_ungetc(lx, c); return TOK_DASH;
			}
			break;

		case S13: /* e.g. "." */
			switch ((unsigned char) c) {
			case '.': state = S26; break;
			default:  lx_ungetc(lx, c); return TOK_DOT;
			}
			break;

		case S14: /* e.g. "\x2f" */
			lx_ungetc(lx, c); return lx->z = z0, lx->z(lx);

		case S15: /* e.g. ";" */
			lx_ungetc(lx, c); return TOK_SEMI;

		case S16: /* e.g. "=" */
			lx_ungetc(lx, c); return TOK_BIND;

		case S17: /* e.g. "?" */
			lx_ungetc(lx, c); return TOK_QMARK;

		case S18: /* e.g. "a" */
			switch ((unsigned char) c) {
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9': break;
			case 'A':
			case 'B':
			case 'C':
			case 'D':
			case 'E':
			case 'F':
			case 'G':
			case 'H':
			case 'I':
			case 'J':
			case 'K':
			case 'L':
			case 'M':
			case 'N':
			case 'O':
			case 'P':
			case 'Q':
			case 'R':
			case 'S':
			case 'T':
			case 'U':
			case 'V':
			case 'W':
			case 'X':
			case 'Y':
			case 'Z': break;
			case '_': break;
			case 'a':
			case 'b':
			case 'c':
			case 'd':
			case 'e':
			case 'f':
			case 'g':
			case 'h':
			case 'i':
			case 'j':
			case 'k':
			case 'l':
			case 'm':
			case 'n':
			case 'o':
			case 'p':
			case 'q':
			case 'r':
			case 's':
			case 't':
			case 'u':
			case 'v':
			case 'w':
			case 'x':
			case 'y':
			case 'z': break;
			default:  lx_ungetc(lx, c); return TOK_IDENT;
			}
			break;

		case S19: /* e.g. "\\" */
			lx_ungetc(lx, c); return TOK_DASH;

		case S20: /* e.g. "^" */
			lx_ungetc(lx, c); return TOK_HAT;

		case S21: /* e.g. "{" */
			lx_ungetc(lx, c); return TOK_OPEN;

		case S22: /* e.g. "|" */
			lx_ungetc(lx, c); return TOK_PIPE;

		case S23: /* e.g. "}" */
			lx_ungetc(lx, c); return TOK_CLOSE;

		case S24: /* e.g. "~" */
			lx_ungetc(lx, c); return TOK_TILDE;

		case S25: /* e.g. "$a" */
			switch ((unsigned char) c) {
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9': break;
			case 'A':
			case 'B':
			case 'C':
			case 'D':
			case 'E':
			case 'F':
			case 'G':
			case 'H':
			case 'I':
			case 'J':
			case 'K':
			case 'L':
			case 'M':
			case 'N':
			case 'O':
			case 'P':
			case 'Q':
			case 'R':
			case 'S':
			case 'T':
			case 'U':
			case 'V':
			case 'W':
			case 'X':
			case 'Y':
			case 'Z': break;
			case '_': break;
			case 'a':
			case 'b':
			case 'c':
			case 'd':
			case 'e':
			case 'f':
			case 'g':
			case 'h':
			case 'i':
			case 'j':
			case 'k':
			case 'l':
			case 'm':
			case 'n':
			case 'o':
			case 'p':
			case 'q':
			case 'r':
			case 's':
			case 't':
			case 'u':
			case 'v':
			case 'w':
			case 'x':
			case 'y':
			case 'z': break;
			default:  lx_ungetc(lx, c); return TOK_TOKEN;
			}
			break;

		case S26: /* e.g. ".." */
			lx_ungetc(lx, c); return TOK_TO;

		case S27: /* e.g. "->" */
			lx_ungetc(lx, c); return TOK_MAP;

		default:
			; /* unreached */
		}

		switch (state) {
		case S1:
		case S3:
		case S4:
		case S7:
		case S14:
			break;

		default:
			if (lx->push != NULL) {
				if (-1 == lx->push(lx->buf_opaque, c)) {
					return TOK_ERROR;
				}
			}
			break;

		}
	}

	lx->lgetc = NULL;

	switch (state) {
	case NONE: return TOK_EOF;
	case S1: return TOK_EOF;
	case S2: return TOK_BANG;
	case S3: return TOK_EOF;
	case S4: return TOK_EOF;
	case S6: return TOK_AND;
	case S7: return TOK_EOF;
	case S8: return TOK_LPAREN;
	case S9: return TOK_RPAREN;
	case S10: return TOK_STAR;
	case S11: return TOK_CROSS;
	case S12: return TOK_DASH;
	case S13: return TOK_DOT;
	case S14: return TOK_EOF;
	case S15: return TOK_SEMI;
	case S16: return TOK_BIND;
	case S17: return TOK_QMARK;
	case S18: return TOK_IDENT;
	case S19: return TOK_DASH;
	case S20: return TOK_HAT;
	case S21: return TOK_OPEN;
	case S22: return TOK_PIPE;
	case S23: return TOK_CLOSE;
	case S24: return TOK_TILDE;
	case S25: return TOK_TOKEN;
	case S26: return TOK_TO;
	case S27: return TOK_MAP;
	default: errno = EINVAL; return TOK_ERROR;
	}
}

const char *
lx_name(enum lx_token t)
{
	switch (t) {
	case TOK_IDENT: return "IDENT";
	case TOK_TOKEN: return "TOKEN";
	case TOK_AND: return "AND";
	case TOK_PIPE: return "PIPE";
	case TOK_DOT: return "DOT";
	case TOK_DASH: return "DASH";
	case TOK_HAT: return "HAT";
	case TOK_BANG: return "BANG";
	case TOK_TILDE: return "TILDE";
	case TOK_QMARK: return "QMARK";
	case TOK_CROSS: return "CROSS";
	case TOK_STAR: return "STAR";
	case TOK_RPAREN: return "RPAREN";
	case TOK_LPAREN: return "LPAREN";
	case TOK_CLOSE: return "CLOSE";
	case TOK_OPEN: return "OPEN";
	case TOK_MAP: return "MAP";
	case TOK_TO: return "TO";
	case TOK_SEMI: return "SEMI";
	case TOK_BIND: return "BIND";
	case TOK_RE: return "RE";
	case TOK_HEX: return "HEX";
	case TOK_OCT: return "OCT";
	case TOK_ESC: return "ESC";
	case TOK_CHAR: return "CHAR";
	case TOK_STR: return "STR";
	case TOK_EOF:     return "EOF";
	case TOK_ERROR:   return "ERROR";
	case TOK_UNKNOWN: return "UNKNOWN";
	default: return "?";
	}
}

const char *
lx_example(enum lx_token (*z)(struct lx *), enum lx_token t)
{
	assert(z != NULL);

	if (z == z0) {
		switch (t) {
		case TOK_RE: return "\x2f";
		case TOK_CHAR: return "a";
		default: goto error;
		}
	} else
	if (z == z1) {
		switch (t) {
		case TOK_HEX: return "\\xa";
		case TOK_OCT: return "\\0";
		case TOK_ESC: return "\\f";
		case TOK_CHAR: return "a";
		case TOK_STR: return "\"";
		default: goto error;
		}
	} else
	if (z == z2) {
		switch (t) {
		case TOK_CHAR: return "a";
		case TOK_STR: return "\'";
		default: goto error;
		}
	} else
	if (z == z3) {
		switch (t) {
		default: goto error;
		}
	} else
	if (z == z4) {
		switch (t) {
		case TOK_IDENT: return "a";
		case TOK_TOKEN: return "$a";
		case TOK_AND: return "&";
		case TOK_PIPE: return "|";
		case TOK_DOT: return ".";
		case TOK_DASH: return "-";
		case TOK_HAT: return "^";
		case TOK_BANG: return "!";
		case TOK_TILDE: return "~";
		case TOK_QMARK: return "?";
		case TOK_CROSS: return "+";
		case TOK_STAR: return "*";
		case TOK_RPAREN: return ")";
		case TOK_LPAREN: return "(";
		case TOK_CLOSE: return "}";
		case TOK_OPEN: return "{";
		case TOK_MAP: return "->";
		case TOK_TO: return "..";
		case TOK_SEMI: return ";";
		case TOK_BIND: return "=";
		default: goto error;
		}
	}

error:

	errno = EINVAL;
	return NULL;
}

void
lx_init(struct lx *lx)
{
	static const struct lx lx_default;

	assert(lx != NULL);

	*lx = lx_default;

	lx->c = EOF;
	lx->z = z4;

	lx->end.byte = 0;
	lx->end.line = 1;
	lx->end.col  = 1;
}

enum lx_token
lx_next(struct lx *lx)
{
	enum lx_token t;

	assert(lx != NULL);
	assert(lx->z != NULL);

	if (lx->lgetc == NULL) {
		return TOK_EOF;
	}

	t = lx->z(lx);

	if (lx->push != NULL) {
		if (-1 == lx->push(lx->buf_opaque, '\0')) {
			return TOK_ERROR;
		}
	}

	return t;
}


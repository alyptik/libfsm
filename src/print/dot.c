/*
 * Copyright 2008-2017 Katherine Flavel
 *
 * See LICENCE for the full copyright terms.
 */

#include <assert.h>
#include <stdio.h>
#include <ctype.h>
#include <limits.h>

#include <fsm/options.h>

#include <print/edge.h>
#include <print/esc.h>

int
dot_escputc_html(FILE *f, const struct fsm_options *opt, char c)
{
	assert(f != NULL);
	assert(opt != NULL);

	if (opt->always_hex) {
		return fprintf(f, "\\x%02x", (unsigned char) c);
	}

	switch (c) {
	case '&':  return fputs("&amp;",  f);
	case '\"': return fputs("&quot;", f);
	case ']':  return fputs("&#x5D;", f); /* yes, even in a HTML label */
	case '<':  return fputs("&#x3C;", f);
	case '>':  return fputs("&#x3E;", f);
	case ' ':  return fputs("&#x2423;", f);

	default:
		break;
	}

	if (!isprint((unsigned char) c)) {
		return fprintf(f, "\\x%02x", (unsigned char) c); /* for humans */
	}

	return fprintf(f, "%c", c);
}

int
dot_escpute_html(FILE *f, const struct fsm_options *opt, enum fsm_edge_type symbol)
{
	assert(f != NULL);
	assert(opt != NULL);
	assert((symbol >= 0 && symbol <= UCHAR_MAX) || symbol == FSM_EDGE_EPSILON);

	if (symbol == FSM_EDGE_EPSILON) {
		return fputs("&#x3B5;", f);
	}

	return dot_escputc_html(f, opt, (unsigned char) symbol);
}


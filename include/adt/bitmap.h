/*
 * Copyright 2008-2017 Katherine Flavel
 *
 * See LICENCE for the full copyright terms.
 */

#ifndef BITMAP_H
#define BITMAP_H

struct fsm_state;
struct fsm_options;

struct bm {
	unsigned char map[UCHAR_MAX / CHAR_BIT + 1];
};

int
bm_get(const struct bm *bm, size_t i);

void
bm_set(struct bm *bm, size_t i);

size_t
bm_next(const struct bm *bm, int i, int value);

unsigned int
bm_count(const struct bm *bm);

void
bm_clear(struct bm *bm);

void
bm_invert(struct bm *bm);

int
bm_print(FILE *f, const struct fsm_options *opt, const struct bm *bm,
	int boxed,
	escpute *escpute);

int
bm_snprint(const struct bm *bm, const struct fsm_options *opt,
	char *s, size_t sz,
	int boxed,
	escpute *escpute);

#endif


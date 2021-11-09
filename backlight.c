/* See LICENSE file for copyright and license details. */
#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include <err.h>
#include "config.h"

static int
bget(const char *path)
{
	FILE *f;
	int ret, val;

	f = fopen(path, "r");
	if (!f)
		err(1, "%s", path);

	ret = fscanf(f, "%d", &val);
	if (ret < 0)
		err(1, "%s", path);

	fclose(f);
	return val;
}

static void
bset(const char *path, int val)
{
	FILE *f;
	int ret;

	f = fopen(path, "w");
	if (!f)
		err(1, "%s", path);

	ret = fprintf(f, "%d", val);
	if (ret < 0)
		err(1, "%s", path);

	fclose(f);
}

int
main(int argc, char **argv)
{
	int val, max, set;
	long arg;
	char *n, *p;
	char *argv0 = argv[0];

	if (argc >= 2 && argv[1][0] == '-') {
		switch (argv[1][1]) {
		case 'h':
			printf("usage: %s [-hv] [[=]VALUE[%%]]\n", argv0);
			exit(1);
		case 'v':
			printf("%s %s\n", argv0, VERSION);
			exit(1);
		default:
			break;
		}
	}

	max = bget(max_path);
	val = bget(val_path);

	if (argc >= 2) {
		n = argv[1];
		n += set = n[0] == '=';
		arg = strtol(n, &p, 10);
		if (arg == LONG_MIN || arg == LONG_MAX || n == p)
			errx(1, "Not a valid number");
		if (p && p[0] == '%')
			arg = (max * arg) / 100;

		val = (set) ? arg : val + arg;
		val = (val > max) ? max : val;
		val = (val < 0) ? 0 : val;
		bset(val_path, val);
	} else {
		printf("%d\n", val);
	}

	return 0;
}

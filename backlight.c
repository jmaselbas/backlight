#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include <err.h>

static int
get(const char *path)
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
set(const char *path, int val)
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
	const char *val_path = "/sys/class/backlight/intel_backlight/brightness";
	const char *max_path = "/sys/class/backlight/intel_backlight/max_brightness";
	FILE *f;
	int val, max, mode;
	long arg;
	char *n, *p;

	if (argc >= 2 && argv[1][0] == '-' && argv[1][1] == 'h') {
		printf("usage: backlight [-h] [[=]VALUE[%]]\n");
		return 0;
	}

	max = get(max_path);
	val = get(val_path);

	if (argc >= 2) {
		n = argv[1];
		if (n[0] == '=') {
			arg = strtol(n + 1, &p, 10);
			if (arg == LONG_MAX || (n + 1) == p)
				errx(1, "Not a valid number");
			if (p && p[0] == '%')
				arg = (max * arg) / 100;
			val = arg;
		} else {
			arg = strtol(n, &p, 10);
			if (arg == LONG_MAX || n == p)
				errx(1, "Not a valid number");
			if (p && p[0] == '%')
				arg = (max * arg) / 100;
			val += arg;
		}
		val = (val > max) ? max : val;
		val = (val < 0) ? 0 : val;
		set(val_path, val);
	} else {
		printf("%d\n", val);
	}

	return 0;
}
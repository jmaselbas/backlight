#include <stdlib.h>
#include <stdio.h>

int
main(int argc, char **argv)
{
	FILE *f = fopen("/sys/class/backlight/intel_backlight/brightness", "r+");
	int val, ret, inc;

	if (argc != 2) {
		fprintf(stderr, "usage: backlight [VALUE]\n");
		return 1;
	}
	inc = atoi(argv[1]);

	if (!f) {
		perror("fopen");
		return 1;
	}

	ret = fscanf(f, "%d", &val);
	if (ret < 0)
		perror("fscanf");
	ret = fprintf(f, "%d", val + inc);
	if (ret < 0)
		perror("fprintf");

	return ret;
}

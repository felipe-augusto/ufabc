#include <stdio.h>
#include <math.h>

int main () {
	int seconds;
	scanf("%d", &seconds);
	int hour = seconds / (60 * 60);
	seconds = seconds - (hour * 60 * 60);
	int minutes = seconds / 60;
	seconds = seconds - (minutes * 60);
	printf("%d:%d:%d\n", hour, minutes, seconds);
}
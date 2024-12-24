#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void usage(char *arg0) {
    fprintf(stderr, "Usage: %s <countdown_minutes>\n", arg0);
    exit(1);
}

char s[16] = {0};

char *secondsToClockString(int seconds) {
    sprintf(s, "%.2d:%.2d", seconds / 60, seconds % 60);

    return s;
}

void timesUp() {
    char *s = "Time's up !";

    printf("\n");
    for (int i = 0; i < 200; i++) {
        printf("*");
        fflush(stdout);
        usleep(20000);
    }
    for (int i = 1; i <= strlen(s); i++) {
        printf("%.*s\r", i, s);
        fflush(stdout);
        usleep(200000);
    }
    printf("\n");
}

int main(int argc, char **argv) {
    if (argc != 2) {
        usage(argv[0]);
    }

    int minutes = atoi(argv[1]);
    if (minutes == 0) {
        fprintf(stderr, "argument must be a positive integer\n");
        usage(argv[0]);
    }

    int startTime = time(NULL);
    int seconds = minutes * 60;
    int timeCost;

    while ((timeCost = time(NULL) - startTime) <= seconds) {
        char *s = secondsToClockString(seconds - timeCost);
        printf("%s                          \r", s);
        fflush(stdout);
        sleep(1);
    }

    timesUp();

    return 0;
}


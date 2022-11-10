#include <stdio.h>
#include <unistd.h>
#include <signal.h>

static void sighup(int unused);
static void sigterm(int unused);

static int restart = 0;
static int running = 1;

int main(int argc, char *argv[]) {
    printf("restart start\n");

    signal(SIGHUP, sighup);
    signal(SIGTERM, sigterm);

    while (running) {
        sleep(1);
        printf("running...\n");
    }

    if (restart) {
        printf("restart self...\n");
        // restart
        execvp(argv[0], argv);
    }

    printf("restart finished\n");

    return 0;
}

void
sighup(int unused)
{
    printf("received sighup\n");
    restart = 1;
    running = 0;
}

void
sigterm(int unused)
{
    printf("received sigterm\n");
    running = 0;
}

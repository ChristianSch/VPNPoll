#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#include "lib.h"


int main( int argc, char *argv[] )
{
    int out;

    while(1)
    {
        if (is_connected()) {
            printf("VPN Status:\t\x1b[32m[√] Connected\x1b[0m\n");
        } else {
            printf("VPN Status:\t\x1b[31m[x] NOT connected\x1b[0m\n");
        }

        out = sleep(30);

        if (out != 0)
            exit(EXIT_SUCCESS);
    };


}

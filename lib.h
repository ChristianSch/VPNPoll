#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

/**
 * Error describing the failure that prevented correct behavior.
 */
struct Error {
    char* description;
};

/**
 * Returns whether or not the computer is connected to
 * the ovpn.to network.
 *
 * @returns 1 if true, 0 otherwise
 */
int is_connected(void);

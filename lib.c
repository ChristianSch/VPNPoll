#include "lib.h"

struct curl_string {
    char *p;
    size_t len;
};

void init_curl_string(struct curl_string *s)
{
    s->len = 0;
    s->p = malloc(s->len + 1);

    if (s->p == NULL) {
        fprintf(stderr, "No memory available.\n");
        exit(EXIT_FAILURE);
    }

    /* the string is empty at the moment */
    s->p[0] = '\0';
}

size_t _write_curl_result_string( void *p, size_t size, size_t nmemb, struct curl_string *s)
{
    size_t new_len = s->len + (size * nmemb);
    s->p = realloc(s->p, new_len+1);

    if (s->p == NULL) {
        fprintf(stderr, "realloc() failed\n");
        exit(EXIT_FAILURE);
    }

    memcpy(s->p+s->len, p, size*nmemb);
    s->p[new_len] = '\0';
    s->len = new_len;

    return size*nmemb;
}

int is_connected(void)
{
    CURL *curl;
    CURLcode res;
    long http_code = 0;
    char *user_agent = "User-Agent: vpn-poll";
    char *url = "https://ovpn-ip.info/index.php";

    curl = curl_easy_init();

    if (curl != NULL) {
        struct curl_string s;
        struct curl_slist *chunk = NULL;

        init_curl_string(&s);

        chunk = curl_slist_append(chunk, user_agent);

        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, _write_curl_result_string);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);
        res = curl_easy_perform(curl);

        if (s.p != NULL) {
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);

            if (http_code ==  200) {
                if (strstr(s.p, "Connected to oVPN.to Server") != NULL) {
                    return 1;
                } else {
                    return 0;
                }
            } else {
                fprintf(stderr, "HTTP status %lu returned. Aborting.\n", http_code);
                exit(EXIT_FAILURE);
            }

            curl_slist_free_all(chunk);
        } else {
            fprintf(stderr, "BULLSHIT returned. Sorry\n");
            exit(EXIT_FAILURE);
        }

        free(s.p);
    } else {
        fprintf(stderr, "Could not init curl. Aborting.\n");
        exit(EXIT_FAILURE);
    }
    curl_easy_cleanup(curl);
}

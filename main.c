#include<stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h> // For usleep
#include <getopt.h>


#define LED3_PATH "/sys/class/leds/beaglebone:green:usr3"

int PRINT_CHARS = 1;
int DEBUG_PRINT = 1;


int morseToDitDah(char morse, char *ditDah, int convertToUpper) {

    if (convertToUpper) {
        morse = toupper(morse);
    }

    // Giant switch statement
    switch (morse) {
        case 'A': strcpy(ditDah, ".-"); break;
        case 'B': strcpy(ditDah, "-..."); break;
        case 'C': strcpy(ditDah, "-.-."); break;
        case 'D': strcpy(ditDah, "-.."); break;
        case 'E': strcpy(ditDah, "."); break;
        case 'F': strcpy(ditDah, "..-."); break;
        case 'G': strcpy(ditDah, "--."); break;
        case 'H': strcpy(ditDah, "...."); break;
        case 'I': strcpy(ditDah, ".."); break;
        case 'J': strcpy(ditDah, ".---"); break;
        case 'K': strcpy(ditDah, "-.-"); break;
        case 'L': strcpy(ditDah, ".-.."); break;
        case 'M': strcpy(ditDah, "--"); break;
        case 'N': strcpy(ditDah, "-."); break;
        case 'O': strcpy(ditDah, "---"); break;
        case 'P': strcpy(ditDah, ".--."); break;
        case 'Q': strcpy(ditDah, "--.-"); break;
        case 'R': strcpy(ditDah, ".-."); break;
        case 'S': strcpy(ditDah, "..."); break;
        case 'T': strcpy(ditDah, "-"); break;
        case 'U': strcpy(ditDah, "..-"); break;
        case 'V': strcpy(ditDah, "...-"); break;
        case 'W': strcpy(ditDah, ".--"); break;
        case 'X': strcpy(ditDah, "-..-"); break;
        case 'Y': strcpy(ditDah, "-.--"); break;
        case 'Z': strcpy(ditDah, "--.."); break;
        case '1': strcpy(ditDah, ".----"); break;
        case '2': strcpy(ditDah, "..---"); break;
        case '3': strcpy(ditDah, "...--"); break;
        case '4': strcpy(ditDah, "....-"); break;
        case '5': strcpy(ditDah, "....."); break;
        case '6': strcpy(ditDah, "-...."); break;
        case '7': strcpy(ditDah, "--..."); break;
        case '8': strcpy(ditDah, "---.."); break;
        case '9': strcpy(ditDah, "----."); break;
        case '0': strcpy(ditDah, "-----"); break;
        default: strcpy(ditDah, "");  // Return an empty string for unknown characters
    }

    if (strcmp(ditDah, "") == 0) {
        return 1;
    } else {
        return 0;
    }
}

int main(int argc, char *argv[])
{
    // Converts any alphanumberic character to Uppercase
    // Only supports US Latin Alphabet and numbers
    char string_to_morse[100];
    int wpm;
    int c;
    char *endptr;


    static struct option long_options[] =
        {
            /* These options don’t set a flag.
                We distinguish them by their indices. */
            {"wpm", required_argument, 0, 'w'},
            {"string", required_argument, 0, 's'},
            {0, 0, 0, 0}};
    /* getopt_long stores the option index here. */
    int option_index = 0;


    while ((c = getopt_long(argc, argv, "w:s:", long_options, &option_index)) != -1) {

        switch (c)
        {
            case 'w':
                // Convert the argument to an integer
                wpm = strtol(optarg, &endptr, 10);
                printf("option -w with value `%s'\n", optarg);
                break;

            case 's':
                strcpy(string_to_morse, optarg);
                printf("option -s with value `%s'\n", optarg);
                break;

            case '?':
                /* getopt_long already printed an error message. */
                break;

            default:
                abort();
        }
    }


    /* Print any remaining command line arguments (not options). */
    if (optind < argc)
    {
        printf ("non-option ARGV-elements: ");
        while (optind < argc)
            printf ("%s ", argv[optind++]);
        putchar ('\n');
    }


    float dot_period = ( 1200000 / wpm ); // In microseconds, also the rest period
    float dash_period = dot_period * 7;
    float inter_char = dot_period * 3;
    float inter_word = dot_period * 7;

    char ditDah[6];


    for (int i = 0; i < strlen(string_to_morse); i++) {
        int rc = morseToDitDah(toupper(string_to_morse[i]), ditDah, 1);
        if (rc) {
            printf("Failed to parse character %c to Morse Code, is it a standard character?\n", argv[1][0]);
            return rc;
        }

        size_t j = 0;
        while (ditDah[j] != '\0') {
            if (ditDah[j] == '-') {
                usleep(dash_period);
            } else if (ditDah[j] == '.')
            {
                usleep(dot_period);
            }
            else {
                usleep(inter_word);
            }
            printf("%c\n", ditDah[j]);
            usleep(inter_char);
            j++;
        }

        printf("\n");
    }

    usleep(inter_word);

    return 0;
}

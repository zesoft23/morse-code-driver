#include<stdio.h>
#include <string.h>
#include <ctype.h>


int morseToDitDah(char morse, char *ditDah) {
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



int main(int argc, char *argv[]) {
    // Converts any alphanumberic character to Uppercase
    // Only supports US Latin Alphabet and numbers
    if (argc < 2) {
        printf("Too Few Arguments\n");
        return 1;
    } else if (argc > 3)
    {
        printf("Too Many Arguments\n");
        return 1;
    }

    char ditDah[6];

    int rc = morseToDitDah(toupper(argv[1][0]), ditDah);
    if (rc) {
        printf("Failed to parse character %c to Morse Code, is it a standard character?\n", argv[1][0]);
        return rc;
    }

    printf("Character %s is %s in Morse Code\n", argv[1], ditDah);

    return 0;
}

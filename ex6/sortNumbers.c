#include "/share/ex_data/ex6/sortedBigIntList.h"
#include "/share/ex_data/ex6/bigInt.h"
#include <stdio.h>
#include <string.h>
/*** buffer size -max line length + newline + '\0' ***/
#define BUFFER_SIZE 202

/*####################################################################
*  sortNumbers.c
*  --------------------------------------------------------------------
*  This program uses the BigInt and SortedBigIntList data structures from previous problems
*  to sort numbers written in a given input file. 
#####################################################################*/
int main(int argc, char** argv) {
    int pFlag = 0;
    int rFlag = 0;
    int precision = 0;
    FILE* file;

    char* fileName = argv[1];
    file = fopen(fileName, "r");
    if (argc < 2) {
        fprintf(stderr, "Input file not specified.\n");
        return 1;
    }
    if (*argv[1] != '-' && !file) {
        fprintf(stderr, "Input file %s does not exist, or cannot be opened for reading.\n", fileName);
        return 2;
    }
    for (int i = 2; i < argc; i++) {
        if (strlen(argv[i]) >= 2) {
            if ((argv[i][0] == '-') && (argv[i][1] == 'p')) {
                //legal p flag
                if (strlen(argv[i]) == 3 && (argv[i][2] > '0' && argv[i][2] <= '9')) {
                    pFlag++;
                    precision = argv[i][2] - '0';
                } else {
                    if (strlen(argv[i]) == 4 && (argv[i][2] > '0' && argv[i][2] <= '9') && (argv[i][3] >= '0' && argv[i][3] <= '9')) {
                        pFlag++;
                        precision = 10 * (argv[i][2] - '0') + argv[i][3] - '0';
                    } else {
                        if (strlen(argv[i]) == 3) {
                            //Illegal p flag
                            fprintf(stderr, "Invalid precision value %c.\n", argv[i][2]);
                            return 3;
                        } else {
                            fprintf(stderr, "Invalid precision value %s.\n", &argv[i][2]);
                            return 3;
                        }
                    }
                }
                ////Illegal p flag
                if (strlen(argv[i]) == 2 || strlen(argv[i]) > 4) {
                    fprintf(stderr, "Invalid flag %s.\n", argv[i]);
                    return 3;
                }

            }

            //not p or r flags
            if (argv[i][0] != '-' || (argv[i][1] != 'p' && argv[i][1] != 'r')) {
                fprintf(stderr, "Invalid flag %s.\n", argv[i]);
                return 3;
            }
            //Illegal r flag
            if ((argv[i][0] == '-') && (argv[i][1] == 'r') && strlen(argv[i]) > 2) {
                fprintf(stderr, "Invalid flag %s.\n", argv[i]);
                return 3;
            }
            //legal r flag
            if (argv[i][0] == '-' && argv[i][1] == 'r' && strlen(argv[i]) == 2)
                rFlag++;
        } else {
            fprintf(stderr, "Invalid flag %s.\n", argv[i]);
            return 3;
        }
    }
    if (pFlag > 1) {
        fprintf(stderr, "Flag -p cannot be specified twice.\n");
        return 3;
    }
    if (rFlag > 1) {
        fprintf(stderr, "Flag -r cannot be specified twice.\n");
        return 3;
    }

    //The command is legal
    /*** buffer for holding line from file ***/
    char line[BUFFER_SIZE];
    int listStatus = 0;
    if (rFlag == 1)
        listStatus = 1;
    SortedBigIntList list = newSortedBigIntList(listStatus);
    if (!list) {
        fprintf(stderr, "Out of memory.\n");
    }
    if (argv[1][0] == '-' && strlen(argv[1]) == 1) {
        file = stdin;
    }
    BigInt bigInt;
    while (fgets(line, BUFFER_SIZE, file)) {
        for (int i = 0; i < strlen(line); i++) {
            if ((line[i] < '0' || line[i] > '9')&&(i != 0 && (line[i] == '-' || line[i] == '+')))
                i = strlen(line);
            if (line[i] == '\n' && i != 0) {
                line[i] = '\0';
                bigInt = newBigInt(line, precision);
                if (bigInt != NULL) {
                    addBigIntToSortedList(list, newBigInt(line, precision));
                    i = strlen(line);
                }
            }
        }
    } // end of while(fgets)
    printSortedBigIntList(list, precision);
    freeBigInt(bigInt);
    freeSortedBigIntList(list);
    /*** close file and return ***/
    fclose(file);
    return 0;
}

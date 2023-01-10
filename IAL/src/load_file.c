/**
* @file load_file.c
* @brief ial 6 obarvení grafu
*   Reší  zpracování  standardního  vstupu  programu.
* @author Viliam Podhajecky
* @author Tomáš Matušák
* @author Jan Pryč
* @date created: 5.10.2021
* @date last mod: 6.12.2021
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "load_file.h"
#include "list_edge.h"


void load_file(t_list_edge *list) {
    int c;
    int key_edge_counter = 0;
    char input_1[3] = "";
    char input_2[3] = "";

    int counter = 0;
    while ((c = getchar()) != EOF) {
        if (counter == 0) {
            if (isalpha(c) != 0 || isdigit(c) != 0) {
                counter++;
                input_1[0] = (char) c;
                continue;
            } else if (!isblank(c)) {
                continue;
            } else {
                fprintf(stderr, "Wrong Prefix\n");
                exit(1);
            }
        }
        if (counter == 1) {
            if (isalpha(c) != 0 || isdigit(c) != 0) {
                counter++;
                input_1[1] = (char) c;
                continue;
            } else {
                fprintf(stderr, "Wrong Prefix\n");
                exit(1);
            }
        }
        if (counter == 2) {
            if (c == ' ') {
                counter++;
                continue;
            } else {
                fprintf(stderr, "Wrong Prefix\n");
                exit(1);
            }
        }
        if (counter == 3) {
            if (isalpha(c) != 0 || isdigit(c) != 0) {
                counter++;
                input_2[0] = (char) c;
                continue;
            } else {
                fprintf(stderr, "Wrong Prefix\n");
                exit(1);
            }
        }
        if (counter == 4) {
            if (isalpha(c) != 0 || isdigit(c) != 0) {
                counter++;
                input_2[1] = (char) c;
                continue;
            } else {
                fprintf(stderr, "Wrong Prefix\n");
                exit(1);
            }
        }
        if (counter == 5) {
            if (c == '\n') {
                counter = 0;
            } else {
                fprintf(stderr, "Wrong Prefix\n");
                exit(1);
            }
        }

        // append loaded edge to list
        t_edge edge;
        edge.key_edge = key_edge_counter++;
        strcpy(edge.vertex_1, input_1);
        strcpy(edge.vertex_2, input_2);

        list_edge_push(list, edge);
    }

}
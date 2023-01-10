/**
* @file list_neighbor.c
* @brief ial 6 obarvení grafu
*   Pracuje nad vázaným seznamem t_list_neighbor, který se stará o sousednost uzlů.
* @author Viliam Podhajecky
* @author Tomáš Matušák
* @author Jan Pryč
* @date created: 5.10.2021
* @date last mod: 6.12.2021
*/

#include "list_neighbor.h"
#include "stdlib.h"
#include "string.h"
#include "stdio.h"

t_list_neighbor *init_neighbor_list(void) {
    t_list_neighbor *list = (t_list_neighbor *) malloc(sizeof(t_list_neighbor));

    // check if malloc was successful
    if (list == NULL) {
        fprintf(stderr, "LIST INIT: failed malloc()\n");
        exit(99);
    }

    list->count = 0;
    list->top = NULL;

    return list;
}


void list_neighbor_push(t_list_neighbor *list, char name[3]) {
    t_list_neighbor_item *top = list->top;

    if (top == NULL) {
        // empty list
        top = (t_list_neighbor_item *) malloc(sizeof(t_list_neighbor_item));
        strcpy(top->name, name);
        list->top = top;
        list->top->next = NULL;
    } else {
        // not empty list
        t_list_neighbor_item *last;

        do {
            // get last item
            last = top;
            if (strcmp(last->name, name) == 0) {
                return;
            }
        } while ((top = top->next) != NULL);

        // append to last item
        last->next = (t_list_neighbor_item *) malloc(sizeof(t_list_neighbor_item));
        strcpy(last->next->name, name);
        last->next->next = NULL;
    }

    list->count++;
}

void list_neighbor_clean(t_list_neighbor *list) {
    t_list_neighbor_item *current = list->top;
    t_list_neighbor_item *next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    free(list);
    list = NULL;
}

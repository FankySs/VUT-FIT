/**
* @file list_edge.c
* @brief ial 6 obarvení grafu
*   Reší práci nad vázaným seznamem t_list_edge.
* @author Viliam Podhajecky
* @author Tomáš Matušák
* @author Jan Pryč
* @date created: 5.10.2021
* @date last mod: 6.12.2021
*/

#ifndef __STRUCTURES_H_INCLUDED
#define __STRUCTURES_H_INCLUDED

#include "structures.h"

#endif

#include "stdio.h"
#include "stdlib.h"
#include "list_edge.h"

t_list_edge *init_edge_list(void) {
    t_list_edge *list = (t_list_edge *) malloc(sizeof(t_list_edge));

    // check if malloc was successful
    if (list == NULL) {
        fprintf(stderr, "LIST INIT: failed malloc()\n");
        exit(99);
    }

    list->count = 0;
    list->top = NULL;

    return list;
}


void list_edge_push(t_list_edge *list, t_edge edge) {
    t_list_edge_item *top = list->top;

    if (top == NULL) {
        // empty list
        top = (t_list_edge_item *) malloc(sizeof(t_list_edge_item));
        top->edge = edge;
        list->top = top;
        list->top->next = NULL;
    } else {
        // not empty list
        t_list_edge_item *last = top;

        do {
            // get last item
            last = top;
        } while ((top = top->next) != NULL);

        // append to last item
        last->next = (t_list_edge_item *) malloc(sizeof(t_list_edge_item));
        last->next->edge = edge;
        last->next->next = NULL;
    }

    list->count++;
}


t_list_edge_item *list_edge_get(t_list_edge *list, int index) {

    if (index < 0) {
        fprintf(stderr, "Invalid index in list_edge_get(): Can't be negative.");
        return NULL;
    }

    t_list_edge_item *item = list->top;

    for (int i = 1; i <= index; i++) {
        if (item->next != NULL) {
            item = item->next;
            continue;
        } else {
            fprintf(stderr, "Invalid index in list_edge_get().");
            return NULL;
        }
    }

    return item;
}

void list_edge_clean(t_list_edge *list) {
    t_list_edge_item *current = list->top;
    t_list_edge_item *next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    free(list);
    list = NULL;
}

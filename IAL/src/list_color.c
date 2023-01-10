/**
* @file list_color.c
* @brief ial 6 obarvení grafu
*   Pracuje nad vázaným seznamem t_list_color. Určuje barvu uzlu.
* @author Viliam Podhajecky
* @author Tomáš Matušák
* @author Jan Pryč
* @date created: 5.10.2021
* @date last mod: 6.12.2021
*/

#include "list_color.h"
#include "stdlib.h"
#include "stdio.h"

t_list_color *init_color_list(void) {
    t_list_color *list = (t_list_color *) malloc(sizeof(t_list_color));

    // check if malloc was successful
    if (list == NULL) {
        fprintf(stderr, "LIST INIT: failed malloc()\n");
        exit(99);
    }

    list->color_selected = -1;
    list->color_size = 0;
    list->count = 0;
    list->top = NULL;

    return list;
}


void list_color_push(t_list_color *list, int color) {
    t_list_color_item *top = list->top;

    if (top == NULL) {
        // empty list
        top = (t_list_color_item *) malloc(sizeof(t_list_color_item));
        top->color = color;
        list->top = top;
        list->top->next = NULL;
    } else {
        // not empty list
        t_list_color_item *last = top;

        do {
            // get last item
            last = top;
        } while ((top = top->next) != NULL);

        // append to last item
        last->next = (t_list_color_item *) malloc(sizeof(t_list_color_item));
        last->next->color = color;
        last->next->next = NULL;
    }

    list->count++;
}

void list_color_create_new_color(t_list_color *list) {
    list->color_size++;
    if (list->color_selected == -1)
        list_color_push(list, list->color_size - 1);
}

void list_color_clean(t_list_color *list) {
    t_list_color_item *current = list->top;
    t_list_color_item *next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    free(list);
    list = NULL;
}

void list_color_delete_color(t_list_color *list, int color) {
    t_list_color_item *prev = NULL;

    for (t_list_color_item *item = list->top; item != NULL; item = item->next) {
        // delete "top" node
        if (prev == NULL && item->color == color) {
            list->top = item->next;
            free(item);
            list->count--;
            return;
        }

        // delete node
        if (item->color == color) {
            prev->next = item->next;
            free(item);
            list->count--;
            return;
        }

        prev = item;
    }
}
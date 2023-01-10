/**
* @file list_m_coloring.c
* @brief ial 6 obarvení grafu
*   Pracuje nad vázaným seznamem t_list_m_coloring. Ukládá pro každý uzel, uzly sousední, seznam barev, a název.
* @author Viliam Podhajecky
* @author Tomáš Matušák
* @author Jan Pryč
* @date created: 5.10.2021
* @date last mod: 6.12.2021
*/

#include "list_m_coloring.h"
#include "list_neighbor.h"
#include "list_color.h"
#include "stdlib.h"
#include "stdio.h"
#include <stdbool.h>
#include <string.h>


t_list_m_coloring *init_m_coloring_list(t_list_edge *list_edge) {
    t_list_m_coloring *list = (t_list_m_coloring *) malloc(sizeof(t_list_m_coloring));

    if (list == NULL) {
        fprintf(stderr, "LIST INIT: failed malloc()\n");
        exit(99);
    }

    list->top = NULL;
    list->count = 0;

    list_m_coloring_push_all(list, list_edge);


    return list;
}


bool list_m_coloring_is_found(t_list_m_coloring *list, char vertex[3]) {
    for (t_list_m_coloring_item *item = list->top; item != NULL; item = item->next) {
        if (strcmp(item->name, vertex) == 0) {
            return true;
        }
    }
    return false;
}


void list_m_coloring_push(t_list_m_coloring *list, char edge[3]) {
    t_list_m_coloring_item *top = list->top;

    // check if edge is in m-coloring list
    if (list_m_coloring_is_found(list, edge) == true) {
        return;
    }

    // push to list
    if (top == NULL) {
        // empty list
        top = (t_list_m_coloring_item *) malloc(sizeof(t_list_m_coloring_item));

        // init data
        strcpy(top->name, edge);
        list->top = top;
        top->id = list->count;
        top->next = NULL;
        top->color = init_color_list();
        top->neighbors = NULL;

    } else {
        // not empty list
        t_list_m_coloring_item *last = NULL;

        do {
            // get last item
            last = top;
        } while ((top = top->next) != NULL);

        // append to last item
        last->next = (t_list_m_coloring_item *) malloc(sizeof(t_list_m_coloring_item));

        //init data
        strcpy(last->next->name, edge);
        last->next->id = list->count;
        last->next->next = NULL;
        last->next->color = init_color_list();
        last->next->neighbors = NULL;
    }

    list->count++;
}


void list_m_coloring_push_all(t_list_m_coloring *list_m_coloring, t_list_edge *list_edge) {

    for (t_list_edge_item *item_edge = list_edge->top; item_edge != NULL; item_edge = item_edge->next) {
        // solve vertex 1
        list_m_coloring_push(list_m_coloring, item_edge->edge.vertex_1);
        list_m_coloring_add_neighbor(list_m_coloring, item_edge->edge.vertex_1, item_edge->edge.vertex_2);

        // solve vertex 2
        list_m_coloring_push(list_m_coloring, item_edge->edge.vertex_2);
        list_m_coloring_add_neighbor(list_m_coloring, item_edge->edge.vertex_2, item_edge->edge.vertex_1);
    }
}


t_list_m_coloring_item *list_m_coloring_get_item_by_name(t_list_m_coloring *list, char vertex_name[3]) {
    for (t_list_m_coloring_item *item = list->top; item != NULL; item = item->next) {
        if (strcmp(item->name, vertex_name) == 0) {
            return item;
        }
    }
    return NULL;
}


void list_m_coloring_add_neighbor(t_list_m_coloring *list, char vertex[3], char vertex_neighbor[3]) {
    t_list_m_coloring_item *item = list_m_coloring_get_item_by_name(list, vertex);

    // check if initialized
    if (item->neighbors == NULL) {
        item->neighbors = init_neighbor_list();
    }

    // push neighbor to list
    list_neighbor_push(item->neighbors, vertex_neighbor);
}

void list_m_coloring_generate_new_color(t_list_m_coloring *list) {
    for (t_list_m_coloring_item *item = list->top; item != NULL; item = item->next) {
        list_color_create_new_color(item->color);
    }
}

void list_m_coloring_clean(t_list_m_coloring *list) {
    t_list_m_coloring_item *current = list->top;
    t_list_m_coloring_item *next;

    while (current != NULL) {
        next = current->next;
        list_color_clean(current->color); // free color list
        list_neighbor_clean(current->neighbors); // free neighbor list
        free(current);
        current = next;
    }

    free(list);
    list = NULL;
}
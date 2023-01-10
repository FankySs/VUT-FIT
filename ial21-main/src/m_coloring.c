/**
* @file m_coloring.c
* @brief ial 6 obarvení grafu
*   Implementování algoritmu pro přiřazování barev a výběr pořadí uzlů ke zpracování.
* @author Viliam Podhajecky
* @author Tomáš Matušák
* @author Jan Pryč
* @date created: 5.10.2021
* @date last mod: 6.12.2021
*/

#include "m_coloring.h"
#include "list_m_coloring.h"
#include "list_color.h"
#include "list_neighbor.h"

#include "stdio.h"
#include "stdbool.h"
#include "time.h"

#define NOT !


bool is_all_set(t_list_m_coloring *list) {
    for (t_list_m_coloring_item *item = list->top; item != NULL; item = item->next) {
        if (item->color->color_selected == -1) {
            return false;
        }
    }
    return true;

}

t_list_m_coloring_item *get_item_by_less_color(t_list_m_coloring *list) {
    t_list_m_coloring_item *item_less;

    // get first item without color_selected
    for (t_list_m_coloring_item *item = list->top; item != NULL; item = item->next) {
        if (item->color->color_selected == -1) {
            item_less = item;
            break;
        }
    }

    // get item with less color
    for (t_list_m_coloring_item *item = list->top; item != NULL; item = item->next) {
        if (item->color->color_selected == -1 && item->color->count < item_less->color->count) {
            item_less = item;
        }
    }

    if (item_less->color->count == 0)
        return NULL;

    return item_less;
}

void set_color(t_list_m_coloring *list_m_coloring, t_list_m_coloring_item *item) {
    item->color->color_selected = item->color->top->color;

    int color_selected = item->color->color_selected;

    // delete color for neighbor
    for (t_list_neighbor_item *neighbor = item->neighbors->top; neighbor != NULL; neighbor = neighbor->next) {
        t_list_m_coloring_item *m_coloring_item = list_m_coloring_get_item_by_name(list_m_coloring, neighbor->name);
        if (item->color->color_selected != -1) {
            list_color_delete_color(m_coloring_item->color, color_selected);
        }
    }
}

void print_result(t_list_m_coloring *list) {
    printf("vertex name \tcolor \t\tneighbors\n");
    for (t_list_m_coloring_item *item = list->top; item != NULL; item = item->next) {
        printf("%s\t\t%d \t\t", item->name, item->color->color_selected);
        for (t_list_neighbor_item *neighborItem = item->neighbors->top; neighborItem != NULL; neighborItem = neighborItem->next) {
            printf("%s, ",neighborItem->name);
        }
        printf("\n");
    }
}

/************************************
 * FORWARD CHECKING + MIN. COLLISION
 ************************************/
void solve_m_coloring(t_list_edge *list_edge) {
    t_list_m_coloring *list = init_m_coloring_list(list_edge);

    // start clock
    clock_t begin = clock();

    // init first color (0 - zero)
    list_m_coloring_generate_new_color(list);

    while (NOT is_all_set(list)) {
        t_list_m_coloring_item *item = get_item_by_less_color(list);

        // no color left generate new
        if (item == NULL) {
            list_m_coloring_generate_new_color(list);
            continue;
        }

        set_color(list, item);
    }

    // end clock
    clock_t end = clock();
    // get time
    double time_spent = (double) (end - begin) / CLOCKS_PER_SEC;

    print_result(list);
    printf("\nChromatic number: %d, speed: %f sec\n", list->top->color->color_size, time_spent);

    list_m_coloring_clean(list);
}


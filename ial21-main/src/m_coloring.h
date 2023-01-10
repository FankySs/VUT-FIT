/**
* @file m_coloring.h
* @brief ial 6 obarvení grafu
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

#include "stdbool.h"

/**
 * Check if all vertex have color.
 *
 * @param list list of m_coloring items
 * @return
 */
bool is_all_set(t_list_m_coloring *list);


/**
 * Get item from m-coloring list by less color.
 *
 * @param list list of m-coloring
 * @return return founded item, If not found return NULL
 */
t_list_m_coloring_item *get_item_by_less_color(t_list_m_coloring *list);


/**
 * Set color for m_coloring item.
 *
 * @param list_m_coloring list of m-coloring
 * @param item item to set up color
 */
void set_color(t_list_m_coloring *list_m_coloring, t_list_m_coloring_item *item);


/**
 * Main function for FORWARD CHECKING + MINIMUM COLLISION.
 *
 * @param list_edge list of edges
 */
void solve_m_coloring(t_list_edge *list_edge);



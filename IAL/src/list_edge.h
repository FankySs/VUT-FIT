/**
* @file list_edge.h
* @brief ial 6 obarvení 
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

/**
 * Init list.
 */
t_list_edge *init_edge_list();


/**
 * Append item (edge) to list.
 * @param list list to append item to
 * @param edge edge to add
 */
void list_edge_push(t_list_edge *list, t_edge edge);

/**
 *
 * Function return item by inserted index.
 *
 * @param list list to return from
 * @param index index of item to return
 * @return
 */
t_list_edge_item *list_edge_get(t_list_edge *list, int index);


/**
 * Clean all allocated memory
 *
 * @param list list to deallocate
 */
void list_edge_clean(t_list_edge *list);


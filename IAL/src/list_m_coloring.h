/**
* @file list_m_coloring.h
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


/**
 * Initialize m-coloring list.
 *
 * @return m_coloring list.
 */
t_list_m_coloring *init_m_coloring_list(t_list_edge *list_edge);


/**
 * Append all edge to m-coloring list.
 *
 * @param list_m_coloring m-coloring list
 * @param list_edge edge list (loaded from file)
 */
void list_m_coloring_push_all(t_list_m_coloring *list_m_coloring, t_list_edge *list_edge);

/**
 * Add neighbor.
 *
 * @param list which list
 * @param vertex name of vertex
 * @param vertex_neighbor neighbor name
 */
void list_m_coloring_add_neighbor(t_list_m_coloring *list, char vertex[3], char vertex_neighbor[3]);


/**
 * Get item by name in list of m-coloring vertexes.
 *
 * @param list in which list
 * @param vertex_name vertex name to find
 * @return m-color item by name
 */
t_list_m_coloring_item *list_m_coloring_get_item_by_name(t_list_m_coloring *list, char vertex_name[3]);

/**
 * Generate new color for all m-coloring items.
 *
 * @param list m-coloring list.
 */
void list_m_coloring_generate_new_color(t_list_m_coloring *list);


void list_m_coloring_clean(t_list_m_coloring *list);
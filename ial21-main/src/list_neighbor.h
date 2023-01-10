/**
* @file list_neighbor.h
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
 * Initialize neighbor list.
 *
 * @return initialized neighbor list
 */
t_list_neighbor *init_neighbor_list(void);


/**
 * Push to neighbor list new neighbor by name.
 *
 * @param list neighbor list
 * @param name name of new neighbor
 */
void list_neighbor_push(t_list_neighbor *list, char name[3]);


/**
 * Free all neighbor list.
 *
 * @param list neighbor list
 */
void list_neighbor_clean(t_list_neighbor *list);
/**
* @file list_color.h
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
 * Initialize color list.
 *
 * @return initialized color list
 */
t_list_color *init_color_list(void);


/**
 * Push new color item to list.
 *
 * @param list color list
 * @param color name of color (number)
 */
void list_color_push(t_list_color *list, int color);


/**
 * Create new color in color list.
 *
 * @param list color list
 */
void list_color_create_new_color(t_list_color *list);


/**
 * Free list color.
 *
 * @param list list to free
 */
void list_color_clean(t_list_color *list);


/**
 * Delete color from list.
 *
 * @param list list to delete from
 * @param color color to delete
 */
void list_color_delete_color(t_list_color *list, int color);
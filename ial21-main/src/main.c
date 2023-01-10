/**
* @file main.c
* @brief ial 6 obarvení grafu
*
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

#include "list_edge.h"
#include "load_file.h"
#include "m_coloring.h"


int main(void) {

    t_list_edge *list_edge = init_edge_list();
    load_file(list_edge);

    solve_m_coloring(list_edge);

    // free
    list_edge_clean(list_edge);

}

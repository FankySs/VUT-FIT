/**
* @file structures.h
* @brief ial 6 obarvení grafu
*   Obsahuje popisy všech datových struktur, které jsou v programu využity.
* @author Viliam Podhajecky
* @author Tomáš Matušák
* @author Jan Pryč
* @date created: 5.10.2021
* @date last mod: 6.12.2021
*/

/**
* @brief Edge data.
*/
typedef struct {
    int key_edge;
    char vertex_1[3];
    char vertex_2[3];
} t_edge;


/**
* @brief Edge item information.
*/
typedef struct list_item {
    t_edge edge;
    struct list_item *next;
} t_list_edge_item;


/**
* @brief List of vertexes.
*/
typedef struct {
    int count;
    t_list_edge_item *top;
} t_list_edge;


/**************************
 * color typedef structs
 **************************/

typedef struct color_item {
    int color;
    struct color_item *next;
} t_list_color_item;

typedef struct {
    int count;
    int color_selected;
    int color_size;// how many colors we use (counter)
    t_list_color_item *top;
} t_list_color;


/**************************
 * neighbors typedef structs
 **************************/

typedef struct neighbor_item {
    char name[3];
    struct neighbor_item *next;
} t_list_neighbor_item;

/**
 * @brief Neighbor list.
 */
typedef struct {
    int count;
    t_list_neighbor_item *top;
} t_list_neighbor;


/****************************
 * M-COLORING typedef structs
 ****************************/

/**
 * @brief M-Coloring vertex item.
 */
typedef struct m_coloring_item {
    int id;
    char name[3];
    t_list_neighbor *neighbors;
    t_list_color *color;
    struct m_coloring_item *next;
} t_list_m_coloring_item;


/**
 * @brief M-Coloring list.
 */
typedef struct {
    int count;
    t_list_m_coloring_item *top;
} t_list_m_coloring;


#include "../../include/minishell.h"
t_list* new_list_elem(char *str) {
    t_list *new_node = (t_list *)malloc(sizeof(t_list));
    if (!new_node)
        return NULL;
    new_node->str = ft_strdup(str); // Assurez-vous que 'str' est dupliqué ailleurs si nécessaire
    new_node->prev = new_node;
    new_node->next = new_node;
    return new_node;
}
//ajouter une element racine
void add_root_list(t_list **list, char *str) {
    t_list *new_root = new_list_elem(str);
    if (!new_root) return;

    if (*list == NULL) {
        *list = new_root;
    } else {
        t_list *last = (*list)->prev;
        new_root->next = *list;
        new_root->prev = last;
        last->next = new_root;
        (*list)->prev = new_root;
        *list = new_root;
    }
}
//ajouter un element a la fin de la liste
void append_list(t_list **list, char *str) {
    t_list *new_node;
    if (!(new_node = new_list_elem(str))) return;
    if (*list == NULL) {
        *list = new_node;
    } else
    {

        t_list *last = (*list)->prev;
        new_node->prev = last;
        new_node->next = *list;
        last->next = new_node;
        (*list)->prev = new_node;
    }
}
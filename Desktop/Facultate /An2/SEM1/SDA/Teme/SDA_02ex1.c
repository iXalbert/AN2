#ifndef INT_LIST_H
#define INT_LIST_H

#include <stddef.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct IntList{
    int data;
    struct IntList *urm;
} IntList;

IntList *create_list();
void adaugarelistaintreg(IntList *list, int value);
void stergelistaintreg(IntList *list, int value);
int gasireinlista(IntList *list, int value);
void sortarelista(IntList *list);
void afisare(IntList *list);
void stergerelista(IntList *list);

#endif 

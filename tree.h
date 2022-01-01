//first-class ADT
//
//
#ifndef tree_h

#define tree_h
#include <stdio.h>

typedef struct BSTab *bst;

bst BSTinit(void);
void BSTfree(bst tab);

void BSTinfo(bst tab);

void addItem(bst tab,char * str);
void BSTbalance(bst tab);

void save(FILE * fp,bst tab);
#endif /* tree_h */

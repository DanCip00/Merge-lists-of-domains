//ADT
//
//
#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>



//Nodo
typedef struct node *link,node;
struct node {
    char* item;
    long long  dim;
    link l,r;
};

struct BSTab{
    link head;
    link z;
    long long cont;
    long long dup;
};
static unsigned long i=5000000;

static int strmin(const char string_i[],const char string_2[]){
    int i,max;
    max=(int)(strlen(string_i)>=strlen(string_2)?strlen(string_2):strlen(string_i));
    for (i=0;i<max && toupper(string_i[i])==toupper(string_2[i]);i++);
    if (toupper(string_i[i])<toupper(string_2[i]))
        return 1;
    return 0;
}

static link NewNode(char* str,link l,link r,int dim){
    link new = malloc(sizeof(node));
    char *buf=NULL;
    
    if(str!=NULL){
        buf = malloc(sizeof(char)*(strlen(str)+1));
        strcpy(buf,str);
    }
    new->item=buf;
    new->l=l;
    new->r=r;
    return new;
}

static link InsertR(link h,link z,char *str,int *op){
    
    if (h==z){
        *op=1;
        return NewNode(str,z,z,1);
    }
    if (strcmp(str,h->item)==0)
        return h;
    if (strmin(str,h->item))
        h->l=InsertR(h->l,z,str,op);
    else
        h->r=InsertR(h->r,z,str,op);
    if (*op==1)
        h->dim++;
    return h;
}


void addItem(bst tab,char * str){
    int op=0;
    if (tab->head==NULL){
        tab->head=NewNode(str,tab->z,tab->z,1);
        tab->cont=1;
        return;
    }
    if (tab->cont%i==0){
        BSTbalance(tab);
        i=i*2;
    }
    if (str!=NULL){
        tab->head=InsertR(tab->head,tab->z,str,&op);
        if (op)
            tab->cont++;
        else
            tab->dup++;
        printf("Dom insert: %s\n",str);
        return;
    }
    printf("Stringa nulla \n");
}



bst BSTinit(void){
    bst tab =malloc (sizeof (struct BSTab));
    tab->z=NewNode("ITEM NULL",NULL,NULL,0);
    tab->head=NULL;
    tab->dup=tab->cont=0;
    return tab;
}

void BSTinfo(bst tab ){
    printf("Size :\t%lli \n",tab->cont);
    printf("Duplicati bloccati:\t%lli\n",tab->dup);
    printf("I :\t%lu \n",i);
}

static link rotR(link h,link z){
    link t=h->l;
    
    if(t==z)
        return h;
    h->l=t->r;
    t->r=h;
    t->dim=h->dim;
    h->dim=1;
    h->dim+=h->l->dim+h->r->dim;
    return t;
}

static link rotL(link h,link z){
    link t= h->r;
    
    if(t==z)
        return h;
    h->r=t->l;
    t->l=h;
    t->dim=h->dim;
    h->dim=1;
    h->dim+=h->l->dim+h->r->dim;
    return t;
}

static link partR(link h,link z,long long r){
    
    if (h==z)
        return h;
    if (r<(h->l->dim)){
        h->l=partR(h->l,z,r);
        h=rotR(h,z);
    }
    if (r>(h->l->dim)){
        h->r=partR(h->r,z,r-(h->l->dim)-1);
        h=rotL(h,z);
    }
    return h;
}

static link balanceR(link h,link z){
    long long m;
    
    if (h==z)
        return z;
    m=(h->dim+1)/2-1;
    h=partR(h,z,m);
    h->l=balanceR(h->l,z);
    h->r=balanceR(h->r,z);
    return h;
}

void BSTbalance(bst tab){
    printf("Bilancio il BST\n");
    if (tab->head==NULL)
        return;
    tab->head=balanceR(tab->head,tab->z);
}



//Stampa
static void stampa(FILE *fp,char *str){
    fprintf(fp,"%s\n",str);
}

static void inorderR(link h,link z,FILE *fp){
    if (h==z)
        return;
    inorderR(h->l,z,fp);
    stampa(fp,h->item);
    inorderR(h->r,z,fp);
}
void save(FILE * fp,bst tab){
    inorderR(tab->head,tab->z,fp);
    return;
}

//free
static void nodeFree(link h,link z){
    if (h->item!=NULL && h!=z)
        free(h->item);
    free(h);
}


static void iterfree(link h,link z){
    link t;
    
    if (h==NULL)
        return;
    t=h->r;
    iterfree(h->l,z);
    nodeFree(h,z);
    return iterfree(t,z);
    
}

void BSTfree(bst tab){
    
    iterfree(tab->head,tab->z);
    free(tab);
}



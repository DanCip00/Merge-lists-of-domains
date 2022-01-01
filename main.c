//
//
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

FILE* open_file(char nome[500]){
    FILE*fp=NULL;
    char dir[550];
    do{
        printf("Inserire directory del file %s:\n",nome);
        fgets(dir,550,stdin);
        dir[strlen(dir)-1]='\0';
        fp=fopen(dir,"r+");
        if(fp==NULL)
            printf("Dati errati \nRiprovare.\n");
    }while (fp==NULL);
    printf("File aperto \n");
    return fp;
}


FILE *fp;

void readfile(FILE *fp,bst tab){
    char *buf = malloc(sizeof(char)*700);
    while (!feof(fp)) {
        fscanf(fp,"%s",buf);
        if(strcmp(buf,"0.0.0.0")==0 || strcmp(buf,"127.0.0.1")==0)
            fscanf(fp,"%s",buf);
        if(!feof(fp))
            addItem(tab,buf);
    }
    free(buf);
}

void automatic_file(FILE * fp2,bst tab){
    FILE *in;
    char *buf = malloc(sizeof(char)*700);
    int size;
    
    fscanf(fp2,"%d",&size);
    for (int i=0;i<size;i++){
        fscanf(fp2,"%s",buf);
        in=fopen(buf,"r+");
        if(in==NULL)
            printf("ERRORE per: %s\n",buf);
        else
            readfile(in,tab);
    }
}

void menu(bst tab){
    int select;
    printf("1.Inserire un nuovo txt\n");
    printf("2.Salva su file\n");
    printf("3.BST info\n");
    printf("4.Free\n");
    printf("5.Bilancia \n");
    printf("6.Autofill\n");
    printf("7.Exit\n\t");
    scanf("%d",&select);
    switch (select) {
        case 1:
            fp=open_file("Nuova lista");
            readfile(fp,tab);
            fclose(fp);
            break;
        case 2:
            printf("se non si chide il programma si può strivere in diversi momenti\n");
            printf("Cosi facendo però si possono creare duplicati \n");
            fp=open_file("file di output (sovrascrive)");
            save(fp,tab);
            break;
        case 3:
            BSTinfo(tab);
            break;
        case 4:
            BSTfree(tab);
            break;
        case 5:
            BSTbalance(tab);
            break;
        case 6:
            automatic_file(open_file("directory file"),tab);
            break;
        default:
            BSTfree(tab);
            return ;
    }
    return menu(tab);
}

int main() {
    bst tab = BSTinit();
    menu(tab);
}

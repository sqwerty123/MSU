//
//  main.c
//  exam
//
//  Created by  Gleb on 12.01.2020.
//  Copyright © 2020  Gleb. All rights reserved.
//


#include <stdio.h>
#include <stdlib.h>
#include <string.h>



struct list{
    int data;
    struct list *next;
};


struct ListsMethods{
    void (*output) (struct list *root);
    void (*foutput) (FILE *f_output, struct list *root);
    struct list *(*create) (int x);
    void (*add) (struct list *root, int x);
    void (*free) (struct list *root);
};


void LM_foutput_list(FILE *f_output, struct list *root){
    if (root != NULL){
        while (root->next != NULL){
            fprintf(f_output, "%d ", root->data);
            root = root->next;
        }
        fprintf(f_output, "%d ", root->data);
    }
}


void LM_output_list(struct list *root){
    if (root != NULL){
        while (root->next != NULL){
            printf("%d ", root->data);
            root = root->next;
        }
        printf("%d ", root->data);
    }
}


struct list* LM_create_list_root(void){
    struct list *root = (struct list*)malloc(sizeof(struct list));
    root->next = NULL;
    return root;
}


struct list* LM_create_list_element(int x){
    struct list *root = (struct list*)malloc(sizeof(struct list));
    root->data = x;
    root->next = NULL;
    return root;
}


void LM_free_list(struct list *root){
    if (root->next != NULL){
        LM_free_list(root->next);
    }
    free(root);
}


void LM_add_element2list(struct list *root, int x){
    while(root->next != NULL){
        root = root->next;
    }
    root->next = LM_create_list_element(x);
}


struct ListsMethods LM_constructor(void){
    struct ListsMethods lm;
    lm.output = LM_output_list;
    lm.foutput = LM_foutput_list;
    lm.create = LM_create_list_element;
    lm.free = LM_free_list;
    lm.add = LM_add_element2list;
    return lm;
}



int cond_key(int key){
    if ((key & 2018) == 2018){
        return 1;
    }
    return 0;
}


struct list *braid(struct list *t, struct list *s){
    while ((s == NULL) && (t != NULL)){
        if (cond_key(t->data)){
            s = t;
        }
        t = t->next;
    }
    
    s->next = NULL;
    struct list *s_head = s;
    while (s->next != NULL){
        s = s->next;
    }
    
    while (t != NULL){
        if (cond_key(t->data)){
            s->next = t;
            s = s->next;
        }
        t = t->next;
    }
    
    s->next = NULL;
    return s_head;
}



int main(void) {
    FILE *fin  = fopen("/Users/gleb/Projects/C/exam/exam/!input.txt",  "r");
    FILE *fout = fopen("/Users/gleb/Projects/C/exam/exam/!output.txt", "w");
    struct ListsMethods lm = LM_constructor();
    
    int x;
    struct list *l1 = NULL, *l2 = NULL;
    
    if (fscanf(fin, "%d", &x) == -1){ goto stop; }
    l1 = lm.create(x);
    while(fscanf(fin, "%d", &x) != -1){
        lm.add(l1, x);
    }
    stop :
    
    //l2 = lm.create(77);
    l2 = braid(l1, l2);
    lm.foutput(fout, l2);
        
    fclose(fin);
    fclose(fout);
    return 0;
}

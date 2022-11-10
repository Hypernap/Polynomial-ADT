#include<stdio.h>
#include<stdlib.h>
typedef struct node {
    int coeffi;
    int expo; 
    struct node* next;
} node;
typedef struct poly {
    node* head;
    node* tail;
} poly;

void createpoly(poly *p){
  p->head=NULL;
  p->tail=NULL;
}



void doConsider(poly* pol , node* multiplicand) {
    node* curr , *beforeTail , *sameExpoNode;
    curr = pol->head;
    beforeTail = sameExpoNode = NULL;

    while(curr != multiplicand) {
        if(curr->expo == multiplicand->expo) {
            sameExpoNode = curr;
        }
        if(curr->next == pol->tail) {
            beforeTail = curr;
        }
    }

    //If sameExpoNode is present then its coeffi will be updated and multiplicand will be release
    //since multiplicad is at tail of list so tail would be updated too
    if(sameExpoNode != NULL) {
        sameExpoNode->coeffi += multiplicand->coeffi;
        pol->tail = beforeTail;
        free(multiplicand);
    }
    
}
void multiply(poly* pol , node* multiplier) {

    //basic multiplication
    node* multiplicand = pol->tail;
    multiplicand->coeffi *= multiplier->coeffi;
    multiplicand->expo += multiplier->expo;
    free(multiplier);

    //considering case where expo in multiplicand is already present in list
    // x^3 + x * x^2 = 2x^3

    doConsider(pol , multiplicand);
    
}


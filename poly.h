#include <stdio.h>
#include <stdlib.h>
typedef struct node {
  int coeffi;
  int expo;
  struct node *next;
} node;
typedef struct poly {
  node *head;
  node *tail;
  int len;
} poly;

void createpoly(poly *p) {
  p->head = NULL;
  p->tail = NULL;
  p->len = 0;
}

int length(poly *p) { return p->len; }

// void insertintoend(poly *p, int coef, int exp) {
//   node *ptr = (node *)malloc(sizeof(node));
//   ptr->coeffi = coef;
//   ptr->expo = exp;
//   ptr->next = NULL;
//   p->len++;
//   if (p->head == NULL && p->tail == NULL) {
//     p->head = ptr;
//   }
//   p->tail->next = ptr;
//   p->tail = ptr;
// }

void insertintofront(poly *p, int coef, int exp) {
  node *ptr = (node *)malloc(sizeof(node));
  p->len++;
  ptr->coeffi = coef;
  ptr->expo = exp;
  ptr->next = p->head;
  if (p->head == NULL && p->tail == NULL) {
    p->head = ptr;
    p->tail = ptr;
  }
  p->head = ptr;
}

void display(poly *p) {
  node *ptr = p->head;
  while (ptr != NULL) {
    printf("(%dx^%d)", ptr->coeffi, ptr->expo);
    if (ptr->next != NULL)
      printf("+");
    ptr = ptr->next;
  }
  printf("\n");
}

void doConsider(poly *pol) {
  node *multiplicand;
  node *curr, *beforeTail, *sameExpoNode;
  curr = pol->head;
  multiplicand = pol->tail;
  beforeTail = sameExpoNode = NULL;

  while (curr != multiplicand) {
    if (curr->expo == multiplicand->expo) {
      sameExpoNode = curr;
    }
    if (curr->next == pol->tail) {
      beforeTail = curr;
    }
    curr = curr->next;
  }

  // If sameExpoNode is present then its coeffi will be updated and
  // multiplicand
  // will be release since multiplicad is at tail of list so tail would be
  // updated too
  if (sameExpoNode != NULL) {
    sameExpoNode->coeffi += multiplicand->coeffi;
    pol->tail = beforeTail;
    free(multiplicand);
  }
}
poly sub(poly *p1, poly *p2) {
  poly ans;
  node *ptr1, *ptr2;
  createpoly(&ans);
  ptr1 = p1->head;
  ptr2 = p2->head;
  while (ptr1 != NULL && ptr2 != NULL) {
    if (ptr1->expo > ptr2->expo) {
      insertintofront(&ans, ptr1->coeffi, ptr1->expo);
      ptr1 = ptr1->next;
    } else if (ptr1->expo < ptr2->expo) {
      insertintofront(&ans, ptr2->coeffi, ptr2->expo);
      ptr2 = ptr2->next;
    } else {
      insertintofront(&ans, ptr1->coeffi - ptr2->coeffi, ptr2->expo);
      ptr1 = ptr1->next;
      ptr2 = ptr2->next;
    }
  }
  while (ptr2 != NULL) {
    insertintofront(&ans, ptr2->coeffi, ptr2->expo);
    ptr2 = ptr2->next;
  }
  while (ptr1 != NULL) {
    insertintofront(&ans, ptr1->coeffi, ptr1->expo);
    ptr1 = ptr1->next;
  }
  return ans;

}
poly add(poly *p1, poly *p2) {
  poly ans;
  node *ptr1, *ptr2;
  createpoly(&ans);
  ptr1 = p1->head;
  ptr2 = p2->head;
  while (ptr1 != NULL && ptr2 != NULL) {
    if (ptr1->expo > ptr2->expo) {
      insertintofront(&ans, ptr1->coeffi, ptr1->expo);
      ptr1 = ptr1->next;
    } else if (ptr1->expo < ptr2->expo) {
      insertintofront(&ans, ptr2->coeffi, ptr2->expo);
      ptr2 = ptr2->next;
    } else {
      insertintofront(&ans, ptr2->coeffi + ptr1->coeffi, ptr2->expo);
      ptr1 = ptr1->next;
      ptr2 = ptr2->next;
    }
  }
  while (ptr2 != NULL) {
    insertintofront(&ans, ptr2->coeffi, ptr2->expo);
    ptr2 = ptr2->next;
  }
  while (ptr1 != NULL) {
    insertintofront(&ans, ptr1->coeffi, ptr1->expo);
    ptr1 = ptr1->next;
  }
  return ans;
}
poly multiplyPoly(poly *p1, poly *p2) {

  poly ansPoly;
  node *ptr1, *ptr2, *temp;
  int coeff, exp;
  createpoly(&ansPoly);
  ptr1 = p1->head;
  ptr2 = p2->head;

  for (; ptr1 != NULL; ptr1 = ptr1->next) {
    temp = ptr2;
    for (; temp != NULL; temp = temp->next) {
      coeff = ptr1->coeffi * temp->coeffi;
      exp = ptr1->expo + temp->expo;
      if (ansPoly.head == NULL)
        insertintofront(&ansPoly, coeff, exp);
      else
        insertintofront(&ansPoly, coeff, exp);
      doConsider(&ansPoly);
    }
  }
  return ansPoly;
}

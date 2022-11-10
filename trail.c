#include "poly.h"
#include <stdio.h>

int main() {
  poly p1, p2;
  int choice, pow, coef, num, t = 1;
  printf("Enter in Ascending power of polynomial 1 \n");
  createpoly(&p1);
  createpoly(&p2);

  while (t) {
    printf("Enter the power\n");
    scanf("%d", &pow);
    printf("Enter the coefficient\n");
    scanf("%d", &coef);
    insertintofront(&p1, coef, pow);
    printf("Press 1 to enter term to Polynomial 1 \n");
    scanf("%d", &t);
  }
  t = 1;
  printf("Enter in Ascending power of polynomial 2\n");
  while (t) {
    printf("Enter the power\n");
    scanf("%d", &pow);
    printf("Enter the coefficient\n");
    scanf("%d", &coef);
    insertintofront(&p2, coef, pow);
    printf("Press 1 to enter term to Polynomial 2\n");
    scanf("%d", &t);
  }
  printf("\nPOLYNOMIAL 1:");
  display(&p1);
  printf("\nPOLYNOMIAL 2:");
  display(&p2);
  printf("\n");
  printf("Press 1 to Add two Polynomial\n");
  printf("Press 2 to Subtract two Polynomial\n");
  printf("Press 3 to Multiply two Polynomial\n");
  printf("Enter your choice:\n");
  scanf("%d", &choice);
  switch (choice) {
  case 1: {
    poly ans;
    ans = add(&p1, &p2);
    display(&ans);
    break;
  }
  case 2: {
    poly ans;
    ans = sub(&p1, &p2);
    display(&ans);
    break;
  }
  case 3: {
    poly ans;
    ans = multiplyPoly(&p1, &p2);
    display(&ans);
    break;
  }
  default:
    printf("wrong Input\n");
  }

  return 0;
}
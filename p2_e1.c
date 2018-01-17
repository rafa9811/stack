

#include <stdio.h>
#include <stdlib.h>

#include "stack_element.h"


int main(int argc, char **argv) {
    Stack *s,*sp,*si;
    Element *e;
    void *v;
    int i,x,*p;
 
    if (argc!=2){
    printf("Introduzca argumentos de entrada: ./p2_e1 **número de elementos que desea introducir**. Ejemplo: ./p2_e1 3");
    }

    s=stack_ini();
    sp=stack_ini();
    si=stack_ini();
    e=element_ini();
        
    for(i=0;i<atoi(argv[1]);i++){
        printf("Introduce número: ");
        scanf("%d",&x);
        v=(void*)&x;
        e=element_setInfo(e,v);
        
        stack_push(s,e);
    }
    
    if (stack_isEmpty(s) == FALSE && stack_isFull(s) == FALSE) {
        fprintf(stdout,"Pila total(no llena, no vacía):\n");
        stack_print(stdout,s);
    }
    
    while (stack_isEmpty(s)==FALSE){
        e=stack_pop(s);
        p=(int*)element_getInfo(e);
        if(*p%2==0){
            stack_push(sp,e);
        }
        else{
            stack_push(si,e);
        }
    }
    
    if (stack_isEmpty(sp) == FALSE && stack_isFull(sp) == FALSE) {
        fprintf(stdout,"Pila total(no llena, no vacía) con numeros pares:\n");
        stack_print(stdout,sp);
    }
    
    if (stack_isEmpty(si) == FALSE && stack_isFull(si) == FALSE) {
        fprintf(stdout,"Pila total(no llena, no vacía) con numeros impares:\n");
        stack_print(stdout,si);
    }
    

    return 0;
}


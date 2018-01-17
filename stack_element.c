#include "stack_element.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define REALLOC 2

struct _Stack {
    int top;
    Element *item[MAXSTACK];
    /*Element **item*/
};

Stack * stack_ini(){
    Stack *s;
    s=(Stack *)malloc(sizeof(Stack)); /*s->item=(Element **)malloc(sizeof(Element *));*/
    s->top=-1;
    
    return s;
}

void stack_destroy(Stack *s){
    int i;
    if(s==NULL)return;
    
    for(i=0;i<MAXSTACK;i++){
        element_destroy(s->item[i]);
    }
    free(s);
}

Stack * stack_push(Stack *s, const Element *e){
    Element *e2;
    e2=element_ini();
    if(e2==NULL)return NULL;
    e2=element_copy(e);
    if(s==NULL || e==NULL)return NULL;
    
    s->top++;
    s->item[s->top]=element_copy(e2);
    
    return s;        
}

Element * stack_pop(Stack *s){
    Element *e1;    
    if(s==NULL)return NULL;
    
    e1=element_ini();
    e1=element_copy(s->item[s->top]);
    
    element_destroy(s->item[s->top]);
    s->top--;
    
    return e1;
}

Element * stack_top(const Stack *s){
    Element *e1;
    
    if(s==NULL)return NULL;
    
    e1=element_ini();
    e1=element_copy(s->item[s->top]);
    
    return e1;
}

Bool stack_isEmpty(const Stack *s){
    if(s==NULL)return FALSE;
    
    if(s->top==-1){
        return TRUE;
    }
    
    return FALSE;
}

Bool stack_isFull(const Stack *s){
    if(s==NULL)return FALSE;
    
    if(s->top==MAXSTACK){
        return TRUE;
    }
    
    return FALSE;
}

int stack_print(FILE *f, const Stack *s){
    int i,c;
    
    if(s==NULL || f==NULL)return -1;
    
    for(i=(s->top);i>-1;i--){
        c+=element_print(f, s->item[i]);
        fprintf(f,"\n");
    }
    
    return c;
}


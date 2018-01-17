#include <stdlib.h>
#include <stdio.h>
#include "stack_fp.h"




struct _Stack {
    int   top;
    void *item[MAXSTACK];
    destroy_element_function_type destroy_element_function;
    copy_element_function_type    copy_element_function;
    print_element_function_type   print_element_function;
};

Stack * stack_ini(destroy_element_function_type f1, copy_element_function_type f2, print_element_function_type f3){
    Stack *s;
    s=(Stack *)malloc(sizeof(Stack)); /*s->item=(Element **)malloc(sizeof(Element *));*/
    s->top=-1;
    
    s->copy_element_function=f2;
    s->destroy_element_function=f1;
    s->print_element_function=f3;
    
    return s;
}

void stack_destroy(Stack *s){
    int i;
    if(s==NULL)return;
    
    for(i=0;i<MAXSTACK;i++){
        s->destroy_element_function(s->item[i]);
    }
    free(s);
}

Stack * stack_push(Stack *s, const void *v){
    void *v2;
    v2=s->copy_element_function(v);
    if(s==NULL)return NULL;
    
    s->top++;
    s->item[s->top]=s->copy_element_function(v2);
    
    return s;        
}

void * stack_pop(Stack *s){
    void *v1;    
    if(s==NULL)return NULL;
    

    v1=s->copy_element_function(s->item[s->top]);
    
    s->destroy_element_function(s->item[s->top]);
    s->top--;
    
    return v1;
}

void * stack_top(const Stack *s){
    void *v1;
    
    if(s==NULL)return NULL;
    
    v1=s->copy_element_function(s->item[s->top]);
    
    return v1;
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

int stack_print(FILE*f, const Stack*s){
    int i,c;
    
    if(s==NULL || f==NULL)return -1;
    
    for(i=(s->top);i>-1;i--){
        c+=s->print_element_function(f, s->item[i]);
        fprintf(f,"\n");
    }
    
    return c;
}
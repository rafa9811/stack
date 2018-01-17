#include "element.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _Element {
    int *info;
};

Element * element_ini(){
    Element *e=NULL;
    e=(Element *)malloc(sizeof(Element));
    e->info=(int *)malloc(sizeof(int));
    return e;
}

void element_destroy(Element *e){
    free(e->info);
    free(e);
}
/**------------------------------------------------------------------
Modifica los datos de un elemento. Entrada: 
 * El elemento a modificar y el contenido a guardar en dicho elemento. 
 * Salida: El elemento a modificar o NULL si ha habido error.
------------------------------------------------------------------*/
Element * element_setInfo(Element *e, void *v){
    if(e==NULL || v==NULL)return NULL;
    *e->info=*(int *)v;
    return e;
}

void * element_getInfo(Element *e){
    if(e==NULL)return NULL;
    return e->info;
}

Element * element_copy(const Element *e){
    Element *e2;
    e2 = element_ini();
    if(e==NULL || e2==NULL)return NULL;
    
    
    *e2->info=*e->info; /* copiamos el valor del entero por si cambia externamente */
    
    return e2;  
}

Bool element_equals(const Element *e1, const Element *e2){
    if(e1==NULL || e2==NULL)return FALSE;
    
    if(e2->info==e1->info){
        return TRUE;
    }
    return FALSE;
}

/**------------------------------------------------------------------
Imprime en un fichero ya abierto el elemento. 
 * Entrada: Fichero en el que se imprime y el elemento a imprimir. 
 * Salida: Devuelve el número de caracteres escritos.
------------------------------------------------------------------*/
int element_print(FILE *f, const Element *e){
    int c;
    if (f == NULL || e == NULL) {
        return 0;
    }

    c = fprintf(f, "[%d]", *e->info);

    return c;
}





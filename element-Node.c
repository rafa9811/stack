#include "element.h"
#include "Node.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _Element {
    Node *node;
};

Element * element_ini(){
    Element *e=NULL;
    e=(Element *)malloc(sizeof(Element));
    e->node=node_ini();
    return e;
}

void element_destroy(Element *e){
    node_destroy(e->node);
    free(e);
}
/**------------------------------------------------------------------
Modifica los datos de un elemento. Entrada: 
 * El elemento a modificar y el contenido a guardar en dicho elemento. 
 * Salida: El elemento a modificar o NULL si ha habido error.
------------------------------------------------------------------*/
Element * element_setInfo(Element *e, void *v){

    if(e==NULL)return NULL;

    e->node=node_copy((Node *)v);
    return e;
}

void * element_getInfo(Element *e){
    if(e==NULL) return NULL;
    return e->node;
}

Element * element_copy(const Element *e){
    Element *e2;
    e2 = element_ini();
    if(e==NULL || e2==NULL)return NULL;
    
    
    e2->node=node_copy(e->node); /* copiamos el valor del entero por si cambia externamente */
    
    return e2;  
}

Bool element_equals(const Element *e1, const Element *e2){
    if(e1==NULL || e2==NULL)return FALSE;
    
    if(node_equals(e2->node, e1->node)==TRUE){
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

    c = node_print(f,e->node);

    return c;
}

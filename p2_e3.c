

#include <stdio.h>
#include <stdlib.h>

#include "graph.h"
#include "stack_element.h"
#include "types.h"

#define MAX 255



Graph * read_graph_from_file(char * filename){
	FILE * in;
	Graph * g;
	Node * n;
    char buff[MAX], name[MAX];
	int i, nnodes, id1, id2;

	g = graph_ini();
	if (g == NULL){
		return NULL;
	}
	in = (FILE*) fopen(filename, "r");
	if (in == NULL){
		graph_destroy(g);
		return NULL;
	}
	/* Format: nnodes \n node1id node1name ... nodenid nodenname connection1a connection1b ... */
    fgets(buff, MAX, in);
    sscanf(buff, "%d", &nnodes);
    /* read nodes line by line */
    for(i=0; i<nnodes;i++) {
        fgets(buff, MAX, in);
		sscanf(buff, "%d %s", &id1, name);
		/* create node */
		n = node_ini();
		if (node_setId(n, id1) == NULL){
			fclose (in);
			node_destroy(n);
			graph_destroy(g);
			return NULL;
		}
		if (node_setName(n, name) == NULL){
			fclose (in);
			node_destroy(n);
			graph_destroy(g);
			return NULL;
		}
		/* add node to graph */
		if (graph_addNode(g, n) == NULL){
			fclose (in);
			node_destroy(n);
			graph_destroy(g);
			return NULL;
		}
		/* destroy node */
		node_destroy(n);
	}
	/* read connections */
	while (!feof(in)){
        fgets(buff, MAX, in);
		sscanf(buff, "%d %d", &id1, &id2);
		if (graph_addEdge(g, id1, id2) == NULL){
			fclose (in);
			graph_destroy(g);
			return NULL;
		}
	}

	fclose (in);

	return g;
}



Bool recorrer(Graph *g,int id1, int id2){
    int numnodos,numcon,i;    
    Stack *s=NULL;
    Stack *s2=NULL;
    Element *e=NULL;
    Node *n=NULL, *n2=NULL;
    int *idscon, *vdescubiertos;
    void *v=NULL;

    if(g==NULL)return FALSE;
    s=stack_ini();
    s2=stack_ini();
    e=element_ini();
    n=node_ini();
    n2=node_ini();
    numnodos=graph_getNnodes(g);
    vdescubiertos=(int*)malloc(numnodos*sizeof(int));
    idscon=(int*)malloc(numnodos*sizeof(int));
    for(i=0;i<numnodos;i++){
        vdescubiertos[i]=0;
    }
   
    n=graph_getNode(g, id1);
    e=element_setInfo(e,(void *)n);
    s=stack_push(s, e);
    
    
    while (stack_isEmpty(s)==FALSE){
        e=stack_pop(s);
        s2=stack_push(s2,e);
        
        v=element_getInfo(e);
        n=(Node *)v;

        numcon=graph_getNumberOfConnectionsFrom(g,node_getId(n));
        idscon=graph_getConnectionsFrom(g,node_getId(n));
        
        
        
        for(i=0;i<numcon;i++){
           
            if (vdescubiertos[idscon[i]-1] == 0) {
                vdescubiertos[idscon[i]-1] = 1;
                
                n2 = graph_getNode(g, idscon[i]);
                e = element_setInfo(e, (void *) n2);
                if (idscon[i] == id2) {
                    stack_push(s2, e);
                    printf("Es posible encontrar un camino.");
                    /* Intento de hallar el camino
 		       printf("\nEl camino es este:\n");
                       while (stack_isEmpty(s2) == FALSE) {
                        e = stack_pop(s2);
                        stack_push(s,e);
                    }
                    while (stack_isEmpty(s) == FALSE) {
                        e = stack_pop(s);
                        v = element_getInfo(e);
                        n = (Node *) v;
                        printf("%d\n", node_getId(n));
                    }*/
                    return TRUE;
                }
                stack_push(s, e);
            }
        }
        
        
    }
    printf("No es posible encontrar un camino.");
    return FALSE;
}




int main(int argc, char **argv) {
    Graph *g;
    int e, s;
    if(argc!=4){
    printf("Error. Introduzca argumentos de entrada: File nodo nodo . Por ejemplo (en este caso): G1.txt 1 3 // G1.txt 3 1");
    return -1;
    }
    e=atoi(argv[2]);
    s=atoi(argv[3]);
    g=read_graph_from_file(argv[1]);
    recorrer(g,e,s);
    

    return 0;
}


#include <stdio.h>
#include <stdlib.h>

#include "stack_fp.h"
#include "graph.h"
#define MAX 255

Graph * read_graph_from_file(char * filename) {
    FILE * in;
    Graph * g;
    Node * n;
    char buff[MAX], name[MAX];
    int i, nnodes, id1, id2;

    g = graph_ini();
    if (g == NULL) {
        return NULL;
    }
    in = (FILE*) fopen(filename, "r");
    if (in == NULL) {
        graph_destroy(g);
        return NULL;
    }
    /* Format: nnodes \n node1id node1name ... nodenid nodenname connection1a connection1b ... */
    fgets(buff, MAX, in);
    sscanf(buff, "%d", &nnodes);
    /* read nodes line by line */
    for (i = 0; i < nnodes; i++) {
        fgets(buff, MAX, in);
        sscanf(buff, "%d %s", &id1, name);
        /* create node */
        n = node_ini();
        if (node_setId(n, id1) == NULL) {
            fclose(in);
            node_destroy(n);
            graph_destroy(g);
            return NULL;
        }
        if (node_setName(n, name) == NULL) {
            fclose(in);
            node_destroy(n);
            graph_destroy(g);
            return NULL;
        }
        /* add node to graph */
        if (graph_addNode(g, n) == NULL) {
            fclose(in);
            node_destroy(n);
            graph_destroy(g);
            return NULL;
        }
        /* destroy node */
        node_destroy(n);
    }
    /* read connections */
    while (!feof(in)) {
        fgets(buff, MAX, in);
        sscanf(buff, "%d %d", &id1, &id2);
        if (graph_addEdge(g, id1, id2) == NULL) {
            fclose(in);
            graph_destroy(g);
            return NULL;
        }
    }

    fclose(in);

    return g;
}

Bool format_graph(const Graph * g) {


    int i, j, n, n2;
    Node *na = NULL;
    int *conn, *ids;
    Stack *sint = NULL, *snode = NULL;
    

    sint = stack_ini(destroy_intp_function, copy_intp_function, print_intp_function);
    snode = stack_ini(destroy_node_function, copy_node_function, print_node_function);

    if (g == NULL || sint == NULL || snode == NULL) return FALSE;


    /* For each node: */
    n = graph_getNnodes(g); /* Devuelve el número de nodos de un grafo, o -1 si se produce algún error */
    ids = graph_getNodeIds(g); /* Devuelve la lista de ids de nodos contenidos en el grafo */

    for (i = 0; i < n; i++) {

        n2 = graph_getNumberOfConnectionsTo(g, ids[i]); /* Devuelve el número de conexiones que se conocen en el grafo hacia un nodo*/
        conn = graph_getConnectionsTo(g, ids[i]); /* Devuelve una lista con los ids de los nodos conectados desde un nodo dado*/

        for (j = 0; j < n2; j++) {
            na = graph_getNode(g, conn[j]);
            
            
            sint = stack_push(sint, &conn[j]);
            snode = stack_push(snode, na);
        }

        node_destroy(na);
        free(conn);

        /* and also the connections from this node */
        n2 = graph_getNumberOfConnectionsFrom(g, ids[i]); /* Devuelve el número de conexiones que se conocen en el grafo desde un nodo*/
        conn = graph_getConnectionsFrom(g, ids[i]); /* Devuelve una lista con los ids de los nodos conectados desde un nodo dado*/

        for (j = 0; j < n2; j++) {
            na = graph_getNode(g, conn[j]);
            
            sint = stack_push(sint, &conn[j]);
            snode = stack_push(snode, na);
        }

        free(conn);
    }
    printf("Pila de enteros:\n");
    stack_print(stdout, sint);
    printf("Pila de nodos:\n");
    stack_print(stdout, snode);


    return TRUE;
}


int main() {
    Graph *g;
    
    g=read_graph_from_file("G1.txt");
    format_graph(g);    
    
    free (g);
    return 0;
}









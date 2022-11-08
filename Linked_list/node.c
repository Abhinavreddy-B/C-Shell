#include "node.h"
#include <assert.h>
#include <stdio.h>

nodeptr MakeNode(ListElement_ptr _x){
    nodeptr temp = (nodeptr) malloc(sizeof(node));
    assert(temp!=NULL);
    temp->prev=NULL;
    temp->next=NULL;
    temp->data=_x;
    return temp;
}
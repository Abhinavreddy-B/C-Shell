#include "my_dll.h"
#include "node.h"
#include <stdio.h>

my_dll CreateList(void) //creating an empty list
{
    my_dll temp;
    temp.root = NULL;
    temp.tail = NULL;
    return temp;
}

int IsEmpty(const my_dll _L)    //to check if empty
{
    if (_L.tail == NULL)
    {
        return 1;
    }
    return 0;
}

void insert(my_dll* _L, ListElement_ptr _x) 
{
    if (!IsEmpty(*_L))                      //when list is non-empty
    {
        _L->tail->next = MakeNode(_x);
        _L->tail->next->prev = _L->tail;
        _L->tail = _L->tail->next;
    }
    else
    {                                        //when list is empty
        _L->tail = MakeNode(_x);
        _L->root = _L->tail;
    }
    // printf("insert %s\n",_L->tail->data->name);
}

void insert_at(my_dll* _L,ListElement_ptr _x,int _i)
{
    if (!IsEmpty(*_L))                      //when list is non-empty
    {
        nodeptr curr_pos = _L->root;
        while (_i--)
        {
            if (curr_pos == NULL)   //when given is i more than size of list
            {
                printf("i is not under limits\n");
                return;
            }
            curr_pos = curr_pos->next;
        }
        nodeptr temp = MakeNode(_x);
        if(curr_pos==NULL){         //when new node is to be inserted at the end , special case
                                    //to update the "tail"
            temp->prev=_L->tail;
            _L->tail->next=temp;
            _L->tail=temp;
            return;
        }
        if(curr_pos->prev==NULL){       //when i=0 , special case in order to change the "root"
            temp->next=curr_pos;
            curr_pos->prev=temp;
            _L->root=temp;
            return;
        }
        temp->next = curr_pos;          //routine to insert 
        temp->prev = curr_pos->prev;
        curr_pos->prev = temp;
        temp->prev->next = temp;
    }
    else if (_i == 0)       //when list is empty and i is exactly 0
    {
        _L->tail = MakeNode(_x);
        _L->root = _L->tail;
    }
    else        //when list is empty and i is not 0
    {
        printf("i is not under limits\n");
    }
}

void delete(my_dll* _L,int _i)
{
    if (!IsEmpty(*_L))                             //when list is not empty
    {
        if(_L->root==_L->tail){
            //case where there is only 1 element
            free(_L->root->data);
            free(_L->root);
            _L->root=NULL;
            _L->tail=NULL;
            return;
        }
        nodeptr curr_pos = _L->root;
        if(_i==0){                          //when i=0 , special case in order to change the "root"
            _L->root=_L->root->next;
            free(_L->root->prev->data);
            free(_L->root->prev);
            _L->root->prev=NULL;
            return;
        }
        while (_i--)
        {
            //printf("inside delete function %d\n",_i);
            curr_pos = curr_pos->next;
            if (curr_pos == NULL)                              //when given is i more than size of list          
            {
                printf("i should not be more than the size of the list\n");
                return;
            }
        }
        if(curr_pos->next==NULL){           //when node is to be deleted at the end , special case
                                            //to update the "tail"
            _L->tail=_L->tail->prev;
            free(_L->root->next->data);
            free(_L->tail->next);
            _L->tail->next=NULL;
            return;
        }
        curr_pos->prev->next = curr_pos->next;
        curr_pos->next->prev = curr_pos->prev;
        free(curr_pos->data);
        free(curr_pos);
    }
    else                        //when list is empty 
    {
        printf("list is empty\n");
    }
}

int Find(const my_dll* _L,pid_t _pid)
{
    int pos = 0;
    nodeptr curr_pos = _L->root;
    while (curr_pos)
    {
        if (curr_pos->data->pid == _pid)
            return pos;

        pos++;
        curr_pos = curr_pos->next;
    }
    return -1;
}

ListElement_ptr Find_and_return(const my_dll* _L,pid_t _pid)
{
    int pos = 0;
    nodeptr curr_pos = _L->root;
    while (curr_pos)
    {
        if (curr_pos->data->pid == _pid){
            // printf("inside %s %d\n",curr_pos->data->name,curr_pos->data->pid);
            return curr_pos->data;
        }

        pos++;
        curr_pos = curr_pos->next;
    }
    return NULL;
}

void prune(my_dll* _L){
    //print(*_L);
    int pos=0;
    nodeptr curr_pos=_L->root;
    while(curr_pos){
       // printf("%d\n",pos);
        curr_pos=curr_pos->next;
        if(pos%2){
            delete(_L,(pos/2) + 1);
        }
        pos++;
    }
}

int return_last(my_dll * _L){
    if(_L == NULL || _L->tail == NULL || _L->tail->data == NULL){
        return 0;
    }
    return _L->tail->data->index;
}

unsigned int get_size(const my_dll _L){
    int pos=0;
    nodeptr curr_pos=_L.root;
    while(curr_pos){
     curr_pos=curr_pos->next;
     pos++;
    }     
    return pos;
}
//this document defines the functions declared in the header

#ifndef STACK_CPP
#define STACK_CPP
#include"stack.h"
#include<stdio.h>
#include<iostream>
#include<string>
#include <allegro.h>
using namespace std;

//STACK CLASS
//constructors
stack::stack() {
    head = NULL;
}

//destructor - deletes list
stack::~stack(){ 
    while(head){
        NODE *temp = head; 
        head = head->next;
        delete temp;
    }
}

//pushes new value at head of list
void stack::push (int f) { 
    NODE *temp = new NODE;
    temp->value = f;
    temp->next = head;
    head = temp;
}

//pops value from the list
int stack::pop (){ 
    if(!head) return -1;
    int i = head->value;
    NODE *temp = head;
    head = head->next;
    delete temp;
    return i;
}

//gives the value fromTop characters from the top of the list
int stack::get(int fromTop){
    if(!head) return -1;
    NODE *node = head;
    for(int i = fromTop; i > 0; i--){
        node = node->next;
    }
    return node->value;
}

//returns the size of the stack
int stack::size(){
    NODE *node = head;
    int counter = 0;
    while(node){
        node = node->next;
        counter++;
    }
    return counter;
}

#endif

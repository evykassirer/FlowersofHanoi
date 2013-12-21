//header declares class

#ifndef STACK_H //checks to make sure this header hasn't been run already to avoid double declarations
#define STACK_H

//STACK CLASS
class stack {
    private:
        struct NODE{ 
            int value;
            NODE *next;
        };
        NODE *head;
    public:
        stack(); //constructors 
        ~stack(); //desctructor
        void push(int f);
        int pop();
        //accessors
        int get(int fromTop); //gives the value fromTop characters from the top of the list
        int size(); //returns how many ints are in the stack
};

#endif

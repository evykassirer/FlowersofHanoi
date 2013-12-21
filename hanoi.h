//header declares functions used in the fowers of hanoi program

#ifndef HANOI_H //checks to make sure this header hasn't been run already to avoid double declarations
#define HANOI_H

//GLOBAL VARIABLES
//stacks
stack garden[3];
//move counter 
int numMoves;
//things that are selected by user - stores which one
int speedChoice;
int leafON;
int dirtSelect;

//function prototypes
void initialize(stack &garden, int n); //initializes a stack to 0, 1, 2, ... n-1 where 0 is on top
void mainMenu(); //main menu options
void displayMenu(); //displays the menu with the options that are currently selected
void displayInstructions(); //instructions

bool hanoi(int n, int s, int d, int i); //the recursive function that solves the puzzle
void move(int s, int d); //moves an object from one stack to another
bool checkMenu(); //checks if the menu button has been clicked while hanoi is going
void displayHanoi(); //displays the screen where the puzzle is being solved

void userGame(); //the function that involves everything related to the user game

#endif




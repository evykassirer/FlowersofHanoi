#ifndef HANOI_CPP
#define HANOI_CPP
#include"stack.h"
#include"stack.cpp"
#include"hanoi.h"
#include<stdio.h>
#include<iostream>
#include<string>
#include <allegro.h>
using namespace std;

//INITIALIZE STACK*****************************************************************************************************************************************
void initialize(stack &garden, int n) {
    //remove all old values in stack
    int i = garden.pop();
    while(i != -1){
        i = garden.pop();
    }
    //initialize from 0 to n-1 in the stack so 0 is the top
    for(int j = n-1; j >= 0; j--){
        garden.push(j);
    }
}

//MAIN MENU************************************************************************************************************************************************
void mainMenu(){    
    bool exit = false; //exit from the main menu
    bool click = false; //waits for the click to be released before reiterating the main while loop
    while(!exit){        
        displayMenu();
        
        if (!click && mouse_b & 1) { //if the mouse has a new click   
            //checks if the click changes the number of leafs option
            for(int i = 0; i < 9; i++){
                if (mouse_x > 60*i && mouse_x < 60*(i+1) && mouse_y > 200 && mouse_y < 260)
                    leafON = i;
            }
            //checks if the click changes the speed option
            for(int i = 0; i < 3; i++){
                if (mouse_x > 10+85*i && mouse_x < 91+85*i && mouse_y > 365 && mouse_y < 396)
                    speedChoice = i;
            }
            //checks if the click is to go to the instructions
            if (mouse_x > 150 && mouse_x < 400 && mouse_y > 100 && mouse_y < 160){
                displayInstructions();
                click = true; //this prevents exit from being selected after returning to the menu screen
            }   
            
            //if computer sovles is selected    
            else if (mouse_x > 8 && mouse_x < 258 && mouse_y > 300 && mouse_y < 360){
                //initialize the stacks and the number of moves
                initialize(garden[0], leafON+2);
                initialize(garden[1], 0);
                initialize(garden[2], 0);
                numMoves = 0;
                
                //display the initial setup and call the recursive function to solve the puzzle
                displayHanoi();
                bool menu = hanoi(leafON+1, 0, 2, 1); //returns false if menu has not been selected
                
                //when the puzzle is solved, wait until menu is selected to return to main screen
                while(!menu){
                    menu = checkMenu();
                }
                click = true; //waits for a fresh click on the menu screen
            }
            
            //if you play is selected
            else if (mouse_x > 275 && mouse_x < 525 && mouse_y > 300 && mouse_y < 360){
                displayInstructions(); //display instructions so they know how to play
                userGame(); //go to user game
                click = true; //waits for a fresh click on the menu screen
            }
            
            //if exit is selected
            else if (mouse_b & 1 && mouse_x > 150 && mouse_x < 404 && mouse_y > 424 && mouse_y < 484){
                exit = true;
            }
        }
        
        else { //if the mouse is still clicked down and none of the clicks can be checked, watch for a mouse up event
            if (!(mouse_b&1)) {//there it is!
                click = false;
            }   
        }
    }
}

//DISPLAY MENU**********************************************************************************************************************************************
void displayMenu() {    
    //buffer
    static BITMAP *buffer = create_bitmap(540,550);
    //load bitmaps
    static BITMAP *background = load_bitmap("menu.bmp", 0); //background 
    static BITMAP *numLeaves[9] = { //number of leaves options
        load_bitmap("1leaf.bmp", 0),  
        load_bitmap("2leaf.bmp", 0), 
        load_bitmap("3leaf.bmp", 0), 
        load_bitmap("4leaf.bmp", 0), 
        load_bitmap("5leaf.bmp", 0), 
        load_bitmap("6leaf.bmp", 0), 
        load_bitmap("7leaf.bmp", 0), 
        load_bitmap("8leaf.bmp", 0),
        load_bitmap("9leaf.bmp", 0),
    };
    static BITMAP *numLeavesON[9] = { //the darker number of leaves options that replaces the original bitmaps when clicked
        load_bitmap("1leafON.bmp", 0),  
        load_bitmap("2leafON.bmp", 0), 
        load_bitmap("3leafON.bmp", 0), 
        load_bitmap("4leafON.bmp", 0), 
        load_bitmap("5leafON.bmp", 0), 
        load_bitmap("6leafON.bmp", 0), 
        load_bitmap("7leafON.bmp", 0), 
        load_bitmap("8leafON.bmp", 0),
        load_bitmap("9leafON.bmp", 0),
    };
    
    static BITMAP *speed[3] = { //speed options
        load_bitmap("slow.bmp", 0),  
        load_bitmap("medium.bmp", 0), 
        load_bitmap("fast.bmp", 0), 
    };
    static BITMAP *speedON[9] = { //darker speed options that replace the original bitmaps when clicked
        load_bitmap("slowON.bmp", 0),  
        load_bitmap("mediumON.bmp", 0), 
        load_bitmap("fastON.bmp", 0), 
    };
    
    //clear screen
    clear_bitmap(buffer); 
    
    //print background
    draw_sprite(buffer, background, 0, 0);
    
    //print leaf options
    for(int i = 0; i < 9; i++){
        if(i==leafON) draw_sprite(buffer, numLeavesON[i], 60*i, 200);
        else draw_sprite(buffer, numLeaves[i], 60*i, 200);
    }
    
    //print speed options
    for(int i = 0; i < 3; i++){
        if(i==speedChoice) draw_sprite(buffer, speedON[i], 10+85*i, 365);
        else draw_sprite(buffer, speed[i], 10+85*i, 365);
    }
    
    //print buffer to screen
    blit (buffer, screen, 0,0,0,0,540,550);
}

//INSTRUCTIONS**********************************************************************************************************************************************
void displayInstructions(){
    //buffer
    static BITMAP *buffer = create_bitmap(540,550);
    //instructions bitmap
    static BITMAP *instructions = load_bitmap("instructions.bmp", 0);
    
    //clear screen and draw instructions to buffer to screen
    clear_bitmap(buffer); 
    draw_sprite(buffer, instructions, 0, 0);
    blit (buffer, screen, 0,0,0,0,540,550);

    rest(3000); //forces the reader to read them
    
    //waits until user clicks okay and returnns to screen
    bool okay = false;
    while(!okay){
        if (mouse_b & 1 && mouse_x > 150 && mouse_x < 404 && mouse_y > 424 && mouse_y < 484){
            okay = true;
        }
    }
}

//HANOI****************************************************************************************************************************************************
bool hanoi(int n, int s, int d, int i){ //returns true when return to menu is clicked
    if(checkMenu()) return true; //if return to menu is clicked, break and keep returning true through all the levels back to main
    if (n < 0) return false; //base case - break and finish as normal 
    if(hanoi(n-1,s,i,d)) return true; //move n-1 rings from s to i using d
    move(s,d);      //move ring from s to d
    if(hanoi(n-1,i,d,s)) return true; //move the n-1 rings from i to d using s
    return false; //if menu is not clicked and everything has proceeded as normal
}

//MOVE*****************************************************************************************************************************************************
void move(int s, int d){
    if(garden[s].get(0) == -1) return; //if the start is empty, don't move
    garden[d].push(garden[s].pop()); //transfer the top of the start to the top of the destination
    numMoves++; 
    displayHanoi(); //refresh the screen to show the move
}

//CHECK MENU***********************************************************************************************************************************************
bool checkMenu(){
    if (mouse_b & 1 && mouse_x > 55 && mouse_x < 230 && mouse_y > 20 && mouse_y < 170) //checks if the menu button has been clicked
        return true;
    return false;
}

//DISPLAY HANOI*********************************************************************************************************************************************
void displayHanoi(){    
    //buffer
    static BITMAP *buffer = create_bitmap(540,550);
    //load bitmaps - static so they don't have to be reloaded each time
    static BITMAP *background = load_bitmap("background.bmp", 0); //background
    static BITMAP *plant[10] = { //loads the parts of the flower, stems and flower bud 
        load_bitmap("1.bmp", 0),  //this is the flower - plant[0]
        load_bitmap("2.bmp", 0), 
        load_bitmap("3.bmp", 0), 
        load_bitmap("4.bmp", 0), 
        load_bitmap("5.bmp", 0), 
        load_bitmap("6.bmp", 0), 
        load_bitmap("7.bmp", 0), 
        load_bitmap("8.bmp", 0),
        load_bitmap("9.bmp", 0),
        load_bitmap("10.bmp", 0)
    };
    static BITMAP *dirt = load_bitmap("dirt.bmp", 0); //the dirt pile that goes below each flower stem
    static BITMAP *dirtON = load_bitmap("dirtON.bmp", 0); //when the dirt is selected (in user play) the dirt changes colour
    static BITMAP *cloud = load_bitmap("cloud.bmp", 0); //a cloud
    static BITMAP *sun = load_bitmap("sun.bmp", 0); //the sun (menu button)
    
    //clear screen
    clear_bitmap(buffer); 
    
    //print sky
    draw_sprite(buffer, background, 0, 0);
    draw_sprite(buffer, sun, 0, 0);
    draw_sprite(buffer, cloud, 190, 20);
    
    //draw text 
    if(numMoves == 1) textprintf_ex(buffer,font,300,100,makecol(0,0,0), -1,"1 move"); //if one move, print "1 move"
    else textprintf_ex(buffer,font,300,100,makecol(0,0,0), -1,"%d moves",numMoves); //otherwise print the number of moves
        
    //print flowers
    for(int i = 0; i < 3; i++){ 
        int x = i*200, y = 480;
        if(i==dirtSelect) draw_sprite(buffer, dirtON, x, y); //if that flower/dirt has been selected 
        else draw_sprite(buffer, dirt, x, y);  //otherwise print normal dirt
        y -= 20;
        for(int j = garden[i].size(); j > 0; j--){ //print leafs and flower
            y -= 45;
            draw_sprite(buffer, plant[garden[i].get(j-1)], x, y); 
        }
    }
    
    //print buffer to screen
    blit (buffer, screen, 0,0,0,0,540,550);
    
    //pause screen - no breaks (it accumliates, e.g. if slow is selected it rests for 320)
    switch(speedChoice){
        case 0: rest(200); //slow
        case 1: rest(100); //medium
        case 2: rest(20); //fasts
    }
}

//USER GAME************************************************************************************************************************************************
void userGame(){
    //initialize variables
    initialize(garden[0], leafON+2); //resize flowers so the first is the right size and the rest are empty
    initialize(garden[1], 0);
    initialize(garden[2], 0);
    numMoves = 0; //reset
    bool click = false; //stores if mouse is currently clicking
    bool menu = false; //stores if menu has been selecteds
    
    //stores which stacks have been selected
    int s, d;
            
    while(!menu){
        do{ //loops until a moveable choice is made
            //initialize variables
            dirtSelect = -1; //no dirt selected 
            s = -1; //no start selected
            d = -1; //no destiantino selected
            
            displayHanoi(); //update screen

            while(click){ //if there has been a click, wait for new click 
                if(!(mouse_b & 1)) click = false;
            }
            
            //wait for a start to be selected, or for exit to be selected
            while(s == -1 && !menu){ 
                menu = checkMenu(); //update exit variable
                for(int i = 0; i < 3; i++){ //check dirt piles for clicks
                    int x = i*200, y = 480;
                    if (mouse_b & 1 && mouse_x > x && mouse_x < x+162 && mouse_y > y && mouse_y < y+30){  
                        s =  i;
                        dirtSelect = i;
                        click = true;
                        break;
                    }
                }
            }
        
            displayHanoi(); //update with whatever has been selected as the start pile      
            
            while(click){ //wait for new click to select destination 
                if(!(mouse_b & 1)) click = false;
            }
            
            //wait for a destination to be selected (or menu)
            while(d == -1 && !menu){ 
                menu = checkMenu();
                for(int i = 0; i < 3; i++){ 
                    int x = i*200, y = 480;
                    if (mouse_b & 1 && mouse_x > x && mouse_x < x+162 && mouse_y > y && mouse_y < y+30){  
                        d =  i;
                        click = true;
                    }
                }
            }
        }while((garden[s].get(0) >= garden[d].get(0) && garden[d].get(0) != -1) && !menu); //loop the do statement util the start can be moved to the 
                                                                                           //destination, or menu is selected        
        dirtSelect = -1; //dirtSelect is no longer needed, because things are being moved
        if(!menu) move(s,d); //if menu wasn't selected, move the selected objects and print new updated sscreen
        
        if(garden[0].get(0) == -1 && garden[1].get(0) == -1){ //if solved 
            allegro_message("YOU WIN!"); //popup box
            menu = true;
        }
    }
}



#endif

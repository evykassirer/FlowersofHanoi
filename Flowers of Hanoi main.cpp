/* EVY KASSIRER     ICS4U     Mr Kroneberg
Assignment: Fowers of Hanoi*/

#include<stdio.h>
#include<iostream>
#include<string>
#include"stack.h"
#include"stack.cpp"
#include"hanoi.h"
#include"hanoi.cpp"
#include <allegro.h>
using namespace std;

int main(int argc, char *argv[]) {     
    //initialize globals declared in header
    numMoves = 0; 
    speedChoice = 1; //medium
    leafON = 4; //five leaves
    dirtSelect = -1; //no dirt selected
    
    //initialize Allegro
    allegro_init();
    set_color_depth(32); 
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, 540,550,0,0); 
    
    //install mouse
    install_mouse();
    enable_hardware_cursor();
    select_mouse_cursor(MOUSE_CURSOR_ARROW);
    show_mouse(screen);
    
    //install keyboard
    install_keyboard(); 
    
    //Open main menu (and everything else is done from there)
    mainMenu();
}
END_OF_MAIN();

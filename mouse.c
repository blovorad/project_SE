#include "mouse.h"

/**
 * \file mouse.c
 * \author Gautier Levesque
 * \brief fichier source qui regroupe les fonctions utile a la gestion de la souris
 */

SDL_bool BL_init_mouse(BL_Mouse *mouse){

	SDL_GetMouseState(&mouse->pos.x, &mouse->pos.y);						
	mouse->rightButton = SDL_FALSE;								
	mouse->leftButton = SDL_FALSE;								
	mouse->oldRightButton = SDL_FALSE;							
	mouse->oldLeftButton = SDL_FALSE;	
	mouse->pos.w = 1;
	mouse->pos.h = 1;				

	return SDL_TRUE;
}

void BL_get_mouse_pos(BL_Mouse *mouse){

	SDL_GetMouseState(&mouse->pos.x, &mouse->pos.y);						
}	

void BL_actualise_right_button(BL_Mouse *mouse, int n){

	if(n == 1){

		mouse->oldRightButton = mouse->rightButton;				
		mouse->rightButton = SDL_TRUE;						
	}
	else if(n == 2){

		mouse->oldRightButton = mouse->rightButton;				
		mouse->rightButton = SDL_FALSE;							
	}	
}

void BL_actualise_left_button(BL_Mouse *mouse, int n){

	if(n == 1){

		mouse->oldLeftButton = mouse->leftButton;				
		mouse->leftButton = SDL_TRUE;							
	}
	else if(n == 2){

		mouse->oldLeftButton = mouse->leftButton;					
		mouse->leftButton = SDL_FALSE;							
	}
}

void BL_actualise_old_left_button(BL_Mouse *mouse){

	mouse->oldLeftButton = mouse->leftButton;						
}

void BL_actualise_old_right_button(BL_Mouse *mouse){

	mouse->oldRightButton = mouse->rightButton;					
}

SDL_bool BL_get_state_of_right_button(BL_Mouse *mouse){

	return mouse->rightButton;									
}

SDL_bool BL_get_state_of_old_right_button(BL_Mouse *mouse){

	return mouse->oldRightButton;								
}

SDL_bool BL_get_state_of_left_button(BL_Mouse *mouse){

	return mouse->leftButton;									
}

SDL_bool BL_get_state_of_old_left_button(BL_Mouse *mouse){

	return mouse->oldLeftButton;									
}

int BL_get_mouse_x(BL_Mouse *mouse){

	return mouse->pos.x;												
}

int BL_get_mouse_y(BL_Mouse *mouse){

	return mouse->pos.y;												
}

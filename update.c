#include "update.h"

/**
 * \file update.c
 * \author Gautier Levesque
 * \brief fichier source qui regroupe les fonctions utile a la gestion de l'actualisation des elements
 */

SDL_bool BL_update(BL_Window window, double deltaTime, BL_Input *input, BL_Mouse *mouse, BL_Panel *panel, BL_Histogramme *histogramme, Simulation_array simulation_array){

	SDL_bool noError = SDL_TRUE;

	BL_get_mouse_pos(mouse);					
	if(BL_get_input_keyboard(input, mouse) == SDL_FALSE){
		
		return SDL_FALSE;
	}

	BL_update_panel(window, mouse, panel);

	if(histogramme->nb_blocks > 0){

		if(SDL_HasIntersection(&mouse->pos, &histogramme->button_graphe_1.position) == SDL_TRUE){

			if(BL_get_state_of_left_button(mouse) == SDL_TRUE && BL_get_state_of_old_left_button(mouse) == SDL_FALSE){

				BL_change_graphe_1(window, simulation_array, histogramme);
			}
			if(histogramme->button_graphe_1.is_hoover == SDL_FALSE){

				histogramme->button_graphe_1.is_hoover = SDL_TRUE;
				histogramme->button_graphe_1.color = BL_get_blanc(255);
			}
		}
		else{

			if(histogramme->button_graphe_1.is_hoover == SDL_TRUE){

				histogramme->button_graphe_1.is_hoover = SDL_FALSE;
				histogramme->button_graphe_1.color = BL_get_blanc(100);
			}
		}
	}

	if(histogramme->nb_blocks > 1){

		if(SDL_HasIntersection(&mouse->pos, &histogramme->button_graphe_2.position) == SDL_TRUE){

			if(BL_get_state_of_left_button(mouse) == SDL_TRUE && BL_get_state_of_old_left_button(mouse) == SDL_FALSE){

				BL_change_graphe_2(window, simulation_array, histogramme);
			}
			if(histogramme->button_graphe_2.is_hoover == SDL_FALSE){

				histogramme->button_graphe_2.is_hoover = SDL_TRUE;
				histogramme->button_graphe_2.color = BL_get_blanc(255);
			}
		}
		else{

			if(histogramme->button_graphe_2.is_hoover == SDL_TRUE){

				histogramme->button_graphe_2.is_hoover = SDL_FALSE;
				histogramme->button_graphe_2.color = BL_get_blanc(100);
			}
		}
	}

	BL_actualise_old_left_button(mouse);

	return noError;
}
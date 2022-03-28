#include "input.h"

/**
 * \file input.c
 * \author Gautier Levesque
 * \brief fichier source qui regroupe les fonctions utile a la gestion des touches du clavier
 */

SDL_bool BL_init_input(BL_Input *input){

	input->a = SDL_FALSE;
	input->z = SDL_FALSE;
	input->e = SDL_FALSE;
	input->r = SDL_FALSE;
	input->t = SDL_FALSE;
	input->y = SDL_FALSE;
	input->u = SDL_FALSE;
	input->i = SDL_FALSE;
	input->o = SDL_FALSE;
	input->p = SDL_FALSE;
	input->q = SDL_FALSE;
	input->s = SDL_FALSE;
	input->d = SDL_FALSE;
	input->f = SDL_FALSE;
	input->g = SDL_FALSE;
	input->h = SDL_FALSE;
	input->j = SDL_FALSE;
	input->k = SDL_FALSE;
	input->l = SDL_FALSE;
	input->m = SDL_FALSE;
	input->w = SDL_FALSE;
	input->x = SDL_FALSE;
	input->c = SDL_FALSE;
	input->v = SDL_FALSE;
	input->b = SDL_FALSE;
	input->n = SDL_FALSE;
	input->space = SDL_FALSE;
	input->up = SDL_FALSE;
	input->down = SDL_FALSE;
	input->left = SDL_FALSE;
	input->right = SDL_FALSE;
	input->escape = SDL_FALSE;

	return SDL_TRUE;
}

//CATALOGUE DES INPUTS ASSEZ CLAIR A LA LECTURE
SDL_bool BL_get_input_keyboard(BL_Input *input, BL_Mouse *mouse){

	SDL_Event event;

	while(SDL_PollEvent(&event)){

		switch(event.type){

			case SDL_QUIT :
				return SDL_FALSE;
				break;
				
			case SDL_MOUSEBUTTONDOWN :
				if(event.button.button == SDL_BUTTON_LEFT){

					BL_actualise_left_button(mouse, 1);
				}
				if(event.button.button == SDL_BUTTON_RIGHT){

					BL_actualise_right_button(mouse, 1);
				}
				break;

			case SDL_MOUSEBUTTONUP :
				if(event.button.button == SDL_BUTTON_LEFT){

					BL_actualise_left_button(mouse, 2);
				}
				if(event.button.button == SDL_BUTTON_RIGHT){

					BL_actualise_right_button(mouse, 2);
				}
				break;
			case SDL_KEYDOWN :
				if(event.key.keysym.sym == SDLK_ESCAPE){

					input->escape = SDL_TRUE;
				}

				if(event.key.keysym.sym == SDLK_a){

					input->a = SDL_TRUE;
				}
				if(event.key.keysym.sym == SDLK_z){

					input->z = SDL_TRUE;
				}
				if(event.key.keysym.sym == SDLK_e){

					input->e = SDL_TRUE;
				}
				if(event.key.keysym.sym == SDLK_r){

					input->r = SDL_TRUE;
				}
				if(event.key.keysym.sym == SDLK_t){

					input->t = SDL_TRUE;
				}
				if(event.key.keysym.sym == SDLK_y){

					input->y = SDL_TRUE;
				}
				if(event.key.keysym.sym == SDLK_u){

					input->u = SDL_TRUE;
				}
				if(event.key.keysym.sym == SDLK_i){

					input->i = SDL_TRUE;
				}
				if(event.key.keysym.sym == SDLK_o){

					input->o = SDL_TRUE;
				}
				if(event.key.keysym.sym == SDLK_p){

					input->p = SDL_TRUE;
				}
				if(event.key.keysym.sym == SDLK_q){

					input->q = SDL_TRUE;
				}
				if(event.key.keysym.sym == SDLK_s){

					input->s = SDL_TRUE;
				}
				if(event.key.keysym.sym == SDLK_d){

					input->d = SDL_TRUE;
				}
				if(event.key.keysym.sym == SDLK_f){

					input->f = SDL_TRUE;
				}
				if(event.key.keysym.sym == SDLK_g){

					input->g = SDL_TRUE;
				}
				if(event.key.keysym.sym == SDLK_h){

					input->h = SDL_TRUE;
				}
				if(event.key.keysym.sym == SDLK_j){

					input->j = SDL_TRUE;
				}
				if(event.key.keysym.sym == SDLK_k){

					input->k = SDL_TRUE;
				}
				if(event.key.keysym.sym == SDLK_l){

					input->l = SDL_TRUE;
				}
				if(event.key.keysym.sym == SDLK_m){

					input->m = SDL_TRUE;
				}
				if(event.key.keysym.sym == SDLK_w){

					input->w = SDL_TRUE;
				}
				if(event.key.keysym.sym == SDLK_x){

					input->x = SDL_TRUE;
				}
				if(event.key.keysym.sym == SDLK_c){

					input->c = SDL_TRUE;
				}
				if(event.key.keysym.sym == SDLK_v){

					input->v = SDL_TRUE;
				}
				if(event.key.keysym.sym == SDLK_b){

					input->b = SDL_TRUE;
				}
				if(event.key.keysym.sym == SDLK_n){

					input->n = SDL_TRUE;
				}
				if(event.key.keysym.sym == SDLK_UP){

					input->up = SDL_TRUE;
				}
				if(event.key.keysym.sym == SDLK_DOWN){

					input->down = SDL_TRUE;
				}
				if(event.key.keysym.sym == SDLK_RIGHT){

					input->right = SDL_TRUE;
				}
				if(event.key.keysym.sym == SDLK_LEFT){

					input->left = SDL_TRUE;
				}
				if(event.key.keysym.sym == SDLK_SPACE){

					input->space = SDL_TRUE;
				}
				break;

			case SDL_KEYUP :
				if(event.key.keysym.sym == SDLK_ESCAPE){

					input->escape = SDL_FALSE;
				}
				if(event.key.keysym.sym == SDLK_a){

					input->a = SDL_FALSE;
				}
				if(event.key.keysym.sym == SDLK_z){

					input->z = SDL_FALSE;
				}
				if(event.key.keysym.sym == SDLK_e){

					input->e = SDL_FALSE;
				}
				if(event.key.keysym.sym == SDLK_r){

					input->r = SDL_FALSE;
				}
				if(event.key.keysym.sym == SDLK_t){

					input->t = SDL_FALSE;
				}
				if(event.key.keysym.sym == SDLK_y){

					input->y = SDL_FALSE;
				}
				if(event.key.keysym.sym == SDLK_u){

					input->u = SDL_FALSE;
				}
				if(event.key.keysym.sym == SDLK_i){

					input->i = SDL_FALSE;
				}
				if(event.key.keysym.sym == SDLK_o){

					input->o = SDL_FALSE;
				}
				if(event.key.keysym.sym == SDLK_p){

					input->p = SDL_FALSE;
				}
				if(event.key.keysym.sym == SDLK_q){

					input->q = SDL_FALSE;
				}
				if(event.key.keysym.sym == SDLK_s){

					input->s = SDL_FALSE;
				}
				if(event.key.keysym.sym == SDLK_d){

					input->d = SDL_FALSE;
				}
				if(event.key.keysym.sym == SDLK_f){

					input->f = SDL_FALSE;
				}
				if(event.key.keysym.sym == SDLK_g){

					input->g = SDL_FALSE;
				}
				if(event.key.keysym.sym == SDLK_h){

					input->h = SDL_FALSE;
				}
				if(event.key.keysym.sym == SDLK_j){

					input->j = SDL_FALSE;
				}
				if(event.key.keysym.sym == SDLK_k){

					input->k = SDL_FALSE;
				}
				if(event.key.keysym.sym == SDLK_l){

					input->l = SDL_FALSE;
				}
				if(event.key.keysym.sym == SDLK_m){

					input->m = SDL_FALSE;
				}
				if(event.key.keysym.sym == SDLK_w){

					input->w = SDL_FALSE;
				}
				if(event.key.keysym.sym == SDLK_x){

					input->x = SDL_FALSE;
				}
				if(event.key.keysym.sym == SDLK_c){

					input->c = SDL_FALSE;
				}
				if(event.key.keysym.sym == SDLK_v){

					input->v = SDL_FALSE;
				}
				if(event.key.keysym.sym == SDLK_b){

					input->b = SDL_FALSE;
				}
				if(event.key.keysym.sym == SDLK_n){

					input->n = SDL_FALSE;
				}
				if(event.key.keysym.sym == SDLK_UP){

					input->up = SDL_FALSE;
				}
				if(event.key.keysym.sym == SDLK_DOWN){

					input->down = SDL_FALSE;
				}
				if(event.key.keysym.sym == SDLK_RIGHT){

					input->right = SDL_FALSE;
				}
				if(event.key.keysym.sym == SDLK_LEFT){

					input->left = SDL_FALSE;
				}
				if(event.key.keysym.sym == SDLK_SPACE){

					input->space = SDL_FALSE;
				}
				break;

			default :
				break;
		}
	}

	return SDL_TRUE;
}
#include "draw.h"

/**
 * \file draw.c
 * \author Gautier Levesque
 * \brief fichier source qui gere l'affichage de toute les entitees a l'ecran
 */

SDL_bool BL_draw(SDL_Renderer *renderer, BL_Graphics graphics, BL_Panel panel, BL_Histogramme histogramme){

	SDL_bool no_error = SDL_TRUE;
	if(SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255) < 0){

		return SDL_FALSE;
	}

	SDL_RenderClear(renderer);

	if(BL_draw_panel(renderer, graphics, panel) == SDL_FALSE){

		return SDL_FALSE;
	}
	if(BL_draw_histogramme(renderer, histogramme) == SDL_FALSE){

		return SDL_FALSE;
	}

	SDL_RenderPresent(renderer);																

	SDL_Delay(1);

	return no_error;																															
}


SDL_bool BL_draw_line(SDL_Renderer *renderer, const int x1, const int y1, const int x2, const int y2, SDL_Color *couleur){

	if(BL_set_render_color(renderer, couleur) == SDL_FALSE){

		return SDL_FALSE;
	}																

	if(SDL_RenderDrawLine(renderer, x1, y1, x2, y2) < 0){

		return SDL_FALSE;
	}

	return SDL_TRUE;
}

SDL_bool BL_draw_point(SDL_Renderer *renderer, const int x, const int y, SDL_Color *couleur){

	if(BL_set_render_color(renderer, couleur) == SDL_FALSE){

		return SDL_FALSE;
	}																			

	if(SDL_RenderDrawPoint(renderer, x, y) < 0){

		return SDL_FALSE;
	}

	return SDL_TRUE;
}

SDL_bool BL_draw_rect(SDL_Renderer *renderer, SDL_Rect *r, SDL_bool *fill, SDL_Color *couleur){

	if(couleur == NULL){

		*couleur = BL_get_blanc(255);
	}

	if(BL_set_render_color(renderer, couleur) == SDL_FALSE){

		return SDL_FALSE;
	}																	

	if(fill != NULL && *fill == SDL_TRUE){
		
		if(SDL_RenderFillRect(renderer, r) < 0){

			return SDL_FALSE;
		}												
	}
	else{

		if(SDL_RenderDrawRect(renderer, r) < 0){

			return SDL_FALSE;
		}																										
	}

	return SDL_TRUE;
}

SDL_bool BL_draw_texture(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Rect *dst, SDL_Rect *src){

	if(SDL_RenderCopy(renderer, texture, src, dst) < 0){

		return SDL_FALSE;
	}

	return SDL_TRUE;
}

SDL_bool BL_draw_textureEx(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Rect *dst, SDL_Rect *src, SDL_Point *center, int angle, SDL_RendererFlip flip){

	if(SDL_RenderCopyEx(renderer, texture, src, dst, angle, center, flip) < 0){

		return SDL_FALSE;
	}

	return SDL_TRUE;
}

SDL_bool BL_set_render_color(SDL_Renderer *renderer, SDL_Color *couleur){

	if(SDL_SetRenderDrawColor(renderer, couleur->r, couleur->g, couleur->b, couleur->a) < 0){

		return SDL_FALSE;
	}

	return SDL_TRUE;
}

SDL_bool BL_draw_cercle(SDL_Renderer *renderer, BL_Cercle cercle){

	int d, x, y;
	SDL_bool noError = SDL_TRUE;

	d = 3 - (2 - cercle.rayon);
	x = 0;
	y = cercle.rayon;

	while(y >= x && noError){

		noError = BL_draw_point(renderer, cercle.cx + x, cercle.cy + y, &cercle.couleur);
		if(noError == SDL_FALSE){

			return SDL_FALSE;
		}
	    noError = BL_draw_point(renderer, cercle.cx + y, cercle.cy + x, &cercle.couleur);
	    if(noError == SDL_FALSE){
			
			return SDL_FALSE;
		}
	    noError = BL_draw_point(renderer, cercle.cx - x, cercle.cy + y, &cercle.couleur);
	    if(noError == SDL_FALSE){
			
			return SDL_FALSE;
		}
	    noError = BL_draw_point(renderer, cercle.cx - y, cercle.cy + x, &cercle.couleur);
	    if(noError == SDL_FALSE){
			
			return SDL_FALSE;
		}
	    noError = BL_draw_point(renderer, cercle.cx + x, cercle.cy - y, &cercle.couleur);
	    if(noError == SDL_FALSE){
			
			return SDL_FALSE;
		}
	    noError = BL_draw_point(renderer, cercle.cx + y, cercle.cy - x, &cercle.couleur);
	    if(noError == SDL_FALSE){
			
			return SDL_FALSE;
		}
	    noError = BL_draw_point(renderer, cercle.cx - x, cercle.cy - y, &cercle.couleur);
	    if(noError == SDL_FALSE){
			
			return SDL_FALSE;
		}
	    noError = BL_draw_point(renderer, cercle.cx - y, cercle.cy - x, &cercle.couleur);

		if(d < 0){

			d = d + (4 * x) + 6;
		}
		else{

			d = d + 4 * (x - y) + 10;
     		 y--;
		}
		x++;
	}

	return noError;
}

SDL_bool BL_draw_disque(SDL_Renderer *renderer, BL_Cercle cercle){

	int d, y, x;
 	SDL_bool noError = SDL_TRUE;

	d = 3 - (2 * cercle.rayon);
	x = 0;
	y = cercle.rayon;
	 
	while(y >= x && noError){

		noError = BL_draw_line(renderer, cercle.cx - x, cercle.cy - y, (cercle.cx - x) + (2 * x + 1), cercle.cy - y, &cercle.couleur);
		if(noError == SDL_FALSE){
			
			return SDL_FALSE;
		}
	    noError = BL_draw_line(renderer, cercle.cx - x, cercle.cy + y, (cercle.cx - x) + (2 * x + 1), cercle.cy + y, &cercle.couleur);
	    if(noError == SDL_FALSE){
			
			return SDL_FALSE;
		}
	    noError = BL_draw_line(renderer, cercle.cx - y, cercle.cy - x, (cercle.cx - y) + (2 * y + 1), cercle.cy - x, &cercle.couleur);
	    if(noError == SDL_FALSE){
			
			return SDL_FALSE;
		}
	    noError = BL_draw_line(renderer, cercle.cx - y, cercle.cy + x, (cercle.cx - y) + (2 * y + 1), cercle.cy + x, &cercle.couleur);
	 
	    if (d < 0){

	      d = d + (4 * x) + 6;
	    }
	    else {

	      d = d + 4 * (x - y) + 10;
	      y--;
	    }
	 
	    x++;
	}

	return SDL_TRUE;
}

SDL_bool BL_draw_panel(SDL_Renderer *renderer, BL_Graphics graphics, BL_Panel panel){

	if(panel.is_visible == SDL_TRUE){

		if(panel.index_texture == -1){

			if(BL_draw_rect(renderer, &panel.position, &panel.fill, &panel.color) == SDL_FALSE){

				return SDL_FALSE;
			}
		}
		else{

			if(BL_draw_texture(renderer, BL_texture_get_index(graphics, panel.index_texture), &panel.position, NULL) == SDL_FALSE){

				return SDL_FALSE;
			}
		}

		int i = 0;
		SDL_bool no_error = SDL_TRUE;

		while(no_error == SDL_TRUE && i < panel.array_text.nb_texts){

			if(BL_draw_texture(renderer, panel.array_text.texts[i].texture, &panel.array_text.texts[i].position, NULL) == SDL_FALSE){

				no_error = SDL_FALSE;
			}
			i++;
		}

		i = 0;

		while(no_error == SDL_TRUE && i < panel.array_button.nb_buttons){

			if(BL_draw_texture(renderer, BL_texture_get_index(graphics, panel.array_button.buttons[i].index_texture), &panel.array_button.buttons[i].position, NULL) == SDL_FALSE){

				no_error = SDL_FALSE;
			}
			if(BL_draw_texture(renderer, panel.array_button.buttons[i].text.texture, &panel.array_button.buttons[i].text.position, NULL) == SDL_FALSE){

				no_error = SDL_FALSE;
			}
			i++;
		}
		
		return no_error;
	}

	return SDL_TRUE;
}


SDL_bool BL_draw_histogramme(SDL_Renderer *renderer, BL_Histogramme histogramme){

	if(BL_draw_texture(renderer, histogramme.title.texture, &histogramme.title.position, NULL) == SDL_FALSE){

		return SDL_FALSE;
	}
	if(BL_draw_texture(renderer, histogramme.x_label.texture, &histogramme.x_label.position, NULL) == SDL_FALSE){

		return SDL_FALSE;
	}
	if(BL_draw_texture(renderer, histogramme.y_label.texture, &histogramme.y_label.position, NULL) == SDL_FALSE){

		return SDL_FALSE;
	}

	if(BL_draw_texture(renderer, histogramme.title_legende.texture, &histogramme.title_legende.position, NULL) == SDL_FALSE){

		return SDL_FALSE;
	}

	SDL_Color white = BL_get_blanc(255);
	
	if(histogramme.nb_blocks > 1){

		if(BL_draw_line(renderer, histogramme.blocks[0].rects[0].x - 10, 450, histogramme.blocks[1].rects[2].x + 50, 450, &white) == SDL_FALSE){

			return SDL_FALSE;
		}
		if(BL_draw_line(renderer, histogramme.blocks[0].rects[0].x - 10, 150 - 20, histogramme.blocks[0].rects[0].x - 10, 450, &white) == SDL_FALSE){

			return SDL_FALSE;
		}

		if(BL_draw_texture(renderer, histogramme.first_print_name.texture, &histogramme.first_print_name.position, NULL) == SDL_FALSE){

			return SDL_FALSE;
		}
		if(BL_draw_texture(renderer, histogramme.second_print_name.texture, &histogramme.second_print_name.position, NULL) == SDL_FALSE){

			return SDL_FALSE;
		}

		if(BL_draw_rect(renderer, &histogramme.button_graphe_1.position, &histogramme.button_graphe_1.fill, &histogramme.button_graphe_1.color) == SDL_FALSE){

			return SDL_FALSE;
		}
		if(BL_draw_texture(renderer, histogramme.button_graphe_1.text.texture, &histogramme.button_graphe_1.text.position, NULL) == SDL_FALSE){

			return SDL_FALSE;
		}
		if(BL_draw_rect(renderer, &histogramme.button_graphe_2.position, &histogramme.button_graphe_2.fill, &histogramme.button_graphe_2.color) == SDL_FALSE){

			return SDL_FALSE;
		}
		if(BL_draw_texture(renderer, histogramme.button_graphe_2.text.texture, &histogramme.button_graphe_2.text.position, NULL) == SDL_FALSE){

			return SDL_FALSE;
		}

		if(BL_draw_texture(renderer, histogramme.cpu_usage_1.texture, &histogramme.cpu_usage_1.position, NULL) == SDL_FALSE){

			return SDL_FALSE;
		}
		if(BL_draw_texture(renderer, histogramme.cpu_usage_2.texture, &histogramme.cpu_usage_2.position, NULL) == SDL_FALSE){

			return SDL_FALSE;
		}
		if(BL_draw_texture(renderer, histogramme.cpu_legend_1.texture, &histogramme.cpu_legend_1.position, NULL) == SDL_FALSE){

			return SDL_FALSE;
		}
		if(BL_draw_texture(renderer, histogramme.cpu_legend_2.texture, &histogramme.cpu_legend_2.position, NULL) == SDL_FALSE){

			return SDL_FALSE;
		}

		if(BL_draw_texture(renderer, histogramme.time_restitution_usage_1.texture, &histogramme.time_restitution_usage_1.position, NULL) == SDL_FALSE){

			return SDL_FALSE;
		}
		if(BL_draw_texture(renderer, histogramme.time_restitution_legend_1.texture, &histogramme.time_restitution_legend_1.position, NULL) == SDL_FALSE){

			return SDL_FALSE;
		}
		if(BL_draw_texture(renderer, histogramme.time_restitution_usage_2.texture, &histogramme.time_restitution_usage_2.position, NULL) == SDL_FALSE){

			return SDL_FALSE;
		}
		if(BL_draw_texture(renderer, histogramme.time_restitution_legend_2.texture, &histogramme.time_restitution_legend_2.position, NULL) == SDL_FALSE){

			return SDL_FALSE;
		}
	}
	else if(histogramme.nb_blocks > 0){

		if(BL_draw_line(renderer, histogramme.blocks[0].rects[0].x - 10, 450, histogramme.blocks[0].rects[2].x + 50, 450, &white) == SDL_FALSE){

			return SDL_FALSE;
		}
		if(BL_draw_line(renderer, histogramme.blocks[0].rects[0].x - 10, 150 - 20, histogramme.blocks[0].rects[0].x - 10, 450, &white) == SDL_FALSE){

			return SDL_FALSE;
		}
		if(BL_draw_texture(renderer, histogramme.first_print_name.texture, &histogramme.first_print_name.position, NULL) == SDL_FALSE){

			return SDL_FALSE;
		}

		if(BL_draw_rect(renderer, &histogramme.button_graphe_1.position, &histogramme.button_graphe_1.fill, &histogramme.button_graphe_1.color) == SDL_FALSE){

			return SDL_FALSE;
		}
		if(BL_draw_texture(renderer, histogramme.button_graphe_1.text.texture, &histogramme.button_graphe_1.text.position, NULL) == SDL_FALSE){

			return SDL_FALSE;
		}

		if(BL_draw_texture(renderer, histogramme.cpu_usage_1.texture, &histogramme.cpu_usage_1.position, NULL) == SDL_FALSE){

			return SDL_FALSE;
		}
		if(BL_draw_texture(renderer, histogramme.cpu_legend_1.texture, &histogramme.cpu_legend_1.position, NULL) == SDL_FALSE){

			return SDL_FALSE;
		}

		if(BL_draw_texture(renderer, histogramme.time_restitution_usage_1.texture, &histogramme.time_restitution_usage_1.position, NULL) == SDL_FALSE){

			return SDL_FALSE;
		}
		if(BL_draw_texture(renderer, histogramme.time_restitution_legend_1.texture, &histogramme.time_restitution_legend_1.position, NULL) == SDL_FALSE){

			return SDL_FALSE;
		}
	}

	int i = 0;
	SDL_bool noError = SDL_TRUE;
	SDL_bool fill = SDL_TRUE;

	while(i < histogramme.legendes.nb_rects && noError == SDL_TRUE){

		if(BL_draw_rect(renderer, &histogramme.legendes.rects[i], &fill, &histogramme.legendes.colors[i]) == SDL_FALSE){

			noError = SDL_FALSE;
		}
		if(BL_draw_texture(renderer, histogramme.legendes.texts[i].texture, &histogramme.legendes.texts[i].position, NULL) == SDL_FALSE){

			noError = SDL_FALSE;
		}
		i++;
	}

	i = 0;
	int j = 0;

	while(i < histogramme.nb_blocks && noError == SDL_TRUE){

		while(j < histogramme.blocks[i].nb_rects && noError == SDL_TRUE){

			if(BL_draw_rect(renderer, &histogramme.blocks[i].rects[j], &fill, &histogramme.blocks[i].colors[j]) == SDL_FALSE){

				noError = SDL_FALSE;
			}
			if(BL_draw_texture(renderer, histogramme.blocks[i].texts[j].texture, &histogramme.blocks[i].texts[j].position, NULL) == SDL_FALSE){

				noError = SDL_FALSE;
			}
			j++;
		}

		i++;
		j = 0;
	}

	return noError;
}
#include "gui.h"

/**
 * \file gui.c
 * \author Gautier Levesque
 * \brief fichier source qui regroupe les fonctions utiles a la gestion de la GUI
 */

BL_Button BL_create_button(BL_Window window, int x, int y, int w, int h, SDL_bool fill, int index_texture, SDL_Color color, int event,  SDL_Color text_color, char *text, char *font_path){

	BL_Button button;

	button.position.x = x;
	button.position.y = y;
	button.position.w = w;
	button.position.h = h;
	button.is_hoover = SDL_FALSE;
	button.is_visible = SDL_TRUE;
	button.is_pressed = SDL_FALSE;
	button.fill = fill;
	button.event = event;
	button.index_texture = index_texture;
	button.color = color;

	button.text = BL_create_text(window, x, y, text_color, text, font_path, 15);

	button.text.rapport_x = button.text.position.x - x;
	button.text.rapport_y = button.text.position.y - y;
	button.rapport_x = 0;
	button.rapport_y = 0;

	return button;
}

BL_Panel BL_create_panel(int x, int y, int w, int h, SDL_bool fill, int index_texture, SDL_Color color, BL_Array_text array_text, BL_Array_button array_button){

	BL_Panel panel;

	panel.position.x = x;
	panel.position.y = y;
	panel.position.w = w;
	panel.position.h = h;
	panel.index_texture = index_texture;
	panel.color = color;
	panel.is_selected = SDL_FALSE;
	panel.is_visible = SDL_TRUE;
	panel.fill = fill;
	panel.dif_x = 0;
	panel.dif_y = 0;

	panel.array_text = array_text;
	panel.array_button = array_button;

	for(int i = 0; i < panel.array_text.nb_texts; i++){

		panel.array_text.texts[i].rapport_x = panel.array_text.texts[i].position.x - x;
		panel.array_text.texts[i].rapport_y = panel.array_text.texts[i].position.y - y;
	}
	for(int i = 0; i < panel.array_button.nb_buttons; i++){

		panel.array_button.buttons[i].rapport_x = panel.array_button.buttons[i].position.x - x;
		panel.array_button.buttons[i].rapport_y = panel.array_button.buttons[i].position.y - y;
	}

	return panel;
}

BL_Text BL_create_text(BL_Window window, int x, int y, SDL_Color color, char *text_string, char *path, int size_text){

	BL_Text text;

	text.position.x = x;
	text.position.y = y;

	text.rapport_x = 0;
	text.rapport_y = 0;

	TTF_Font *font;
	BL_init_font(&font, path, size_text);
	BL_create_texture_text(window.renderer, font, color, text_string, &text.position, &text.texture);
	BL_clean_font(&font);
	return text;
}

SDL_bool BL_update_panel(BL_Window window, BL_Mouse *mouse, BL_Panel *panel){

	//clic souris
	if(BL_get_state_of_left_button(mouse) == SDL_TRUE && BL_get_state_of_old_left_button(mouse) == SDL_FALSE){

		if(panel->is_selected == SDL_FALSE && SDL_HasIntersection(&mouse->pos, &panel->position) == SDL_TRUE){

			panel->dif_x = mouse->pos.x - panel->position.x;
			panel->dif_y = mouse->pos.y - panel->position.y;
			panel->is_selected = SDL_TRUE;
		}
		else if(panel->is_selected == SDL_TRUE){

			panel->is_selected = SDL_FALSE;
		}
	}
	else if(panel->is_selected == SDL_TRUE && BL_get_state_of_old_left_button(mouse) == SDL_FALSE){

		panel->is_selected = SDL_FALSE;
	}

	if(panel->is_selected == SDL_TRUE){

		panel->position.x = mouse->pos.x - panel->dif_x;
		panel->position.y = mouse->pos.y - panel->dif_y;
		if(panel->position.x < 0){

			panel->position.x = 0;
		}
		else if(panel->position.x > ((int)window.width - panel->position.w)){

			panel->position.x = window.width - panel->position.w;
		}

		if(panel->position.y < 0){

			panel->position.y = 0;
		}
		else if(panel->position.y > ((int)window.height - panel->position.h)){

			panel->position.y = window.height - panel->position.h;
		}

		for(int i = 0; i < panel->array_button.nb_buttons; i++){

			panel->array_button.buttons[i].position.x = panel->position.x + panel->array_button.buttons[i].rapport_x;
			panel->array_button.buttons[i].position.y = panel->position.y + panel->array_button.buttons[i].rapport_y;
			panel->array_button.buttons[i].text.position.x = panel->position.x + panel->array_button.buttons[i].text.rapport_x;
			panel->array_button.buttons[i].text.position.y = panel->position.y + panel->array_button.buttons[i].text.rapport_y;
		}

		for(int i = 0; i < panel->array_text.nb_texts; i++){

			panel->array_text.texts[i].position.x = panel->position.x + panel->array_text.texts[i].rapport_x;
			panel->array_text.texts[i].position.y = panel->position.y + panel->array_text.texts[i].rapport_y;
		}
	}

	return SDL_TRUE;
}

void BL_panel_set_visible(BL_Panel *panel, SDL_bool visible){

	panel->is_visible = visible;
}

void BL_panel_set_selected(BL_Panel *panel, SDL_bool selected){

	panel->is_selected = selected;
}

void BL_panel_set_position(BL_Panel *panel, int x, int y){

	panel->position.x = x;
	panel->position.y = y;
}

void BL_panel_resized(BL_Panel *panel, int w, int h){

	panel->position.w = w;
	panel->position.h = h;
}

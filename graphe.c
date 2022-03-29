#include "graphe.h"

/**
 * \file graphe.c
 * \author Gautier Levesque
 * \brief fichier source pour la creation et gestion des graphes
 */

BL_Histogramme generate_histogramme(BL_Window window, Simulation_array simulation_array){

	BL_Histogramme histogramme;

	histogramme.nb_blocks = simulation_array.nbSimulations;
	histogramme.blocks = malloc(sizeof(BL_Block) * histogramme.nb_blocks);

	histogramme.title = BL_create_text(window, 430, 100, BL_get_blanc(200), "Graphe des résultats des simulations", "./source/fonts/times.ttf", 18);
	histogramme.x_label = BL_create_text(window, 525, 460, BL_get_blanc(200), "Variables", "./source/fonts/times.ttf", 15);
	histogramme.y_label = BL_create_text(window, 280, 350, BL_get_blanc(200), "Temps seconde", "./source/fonts/times.ttf", 15);

	histogramme.nb_blocks = 0;
	histogramme.index_first_print = -1;
	histogramme.index_second_print = -1;
	histogramme.max_index = simulation_array.nbSimulations;
	
	if(simulation_array.nbSimulations > 0){

		histogramme.index_first_print = 0;
		histogramme.nb_blocks = 1;
	}
	if(simulation_array.nbSimulations > 1){

		histogramme.index_second_print = 1;
		histogramme.nb_blocks = 2;
	}

	histogramme.cpu_legend_1 = BL_create_text(window, 390, 480, BL_get_blanc(200), "Utilisation CPU graphe 1 = ", "./source/fonts/times.ttf", 15);
	histogramme.cpu_legend_2 = BL_create_text(window, 590, 480, BL_get_blanc(200), "Utilisation CPU graphe 2 = ", "./source/fonts/times.ttf", 15);
	histogramme.time_restitution_legend_1 =	BL_create_text(window, 390, 500, BL_get_blanc(200), "Temps restitution graphe 1 = ", "./source/fonts/times.ttf", 15);
	histogramme.time_restitution_legend_2 =	BL_create_text(window, 590, 500, BL_get_blanc(200), "Temps restitution graphe 2 = ", "./source/fonts/times.ttf", 15);
 	
	if(histogramme.nb_blocks > 0){

		histogramme.blocks = malloc(sizeof(BL_Block) * histogramme.nb_blocks);
		if(histogramme.blocks == NULL){

			perror("malloc failed");
			exit(1);
		}

		for(int i = 0; i < histogramme.nb_blocks; i++){

			histogramme.blocks[i].nb_rects = 3;
			histogramme.blocks[i].rects = malloc(sizeof(SDL_Rect) * histogramme.blocks[i].nb_rects);
			histogramme.blocks[i].colors = malloc(sizeof(SDL_Color) * histogramme.blocks[i].nb_rects);
			histogramme.blocks[i].texts = malloc(sizeof(BL_Text) * histogramme.blocks[i].nb_rects);
			if(histogramme.blocks[i].rects == NULL || histogramme.blocks[i].colors == NULL || histogramme.blocks[i].texts == NULL){

				perror("malloc failed");
				exit(1);
			}

			histogramme.blocks[i].texts[0].texture = NULL;
			histogramme.blocks[i].texts[1].texture = NULL;
			histogramme.blocks[i].texts[2].texture = NULL;

			histogramme.blocks[i].colors[0] = BL_get_rouge(255);
			histogramme.blocks[i].colors[1] = BL_get_jaune(255);
			histogramme.blocks[i].colors[2] = BL_get_vert(255);
		}

		histogramme.blocks[0].rects[0].x = 400;
		histogramme.blocks[0].rects[1].x = 443;
		histogramme.blocks[0].rects[2].x = 486;

		histogramme.blocks[0].rects[0].w = 40;
		histogramme.blocks[0].rects[1].w = 40;
		histogramme.blocks[0].rects[2].w = 40;
		histogramme.button_graphe_1 = BL_create_button(window, 230, 270, 120, 30, SDL_TRUE, -1, BL_get_blanc(100), -1,  BL_get_blanc(200), "Suivant graphe 1", "./source/fonts/times.ttf");
		histogramme.cpu_usage_1.texture = NULL;
		histogramme.time_restitution_usage_1.texture = NULL;
		if(histogramme.nb_blocks > 1){

			histogramme.blocks[1].rects[0].x = 590;
			histogramme.blocks[1].rects[1].x = 633;
			histogramme.blocks[1].rects[2].x = 676;

			histogramme.blocks[1].rects[0].w = 40;
			histogramme.blocks[1].rects[1].w = 40;
			histogramme.blocks[1].rects[2].w = 40;
			histogramme.button_graphe_2 = BL_create_button(window, 230, 310, 120, 30, SDL_TRUE, -1, BL_get_blanc(100), -1,  BL_get_blanc(200), "Suivant graphe 2", "./source/fonts/times.ttf");
			histogramme.cpu_usage_2.texture = NULL;
			histogramme.time_restitution_usage_2.texture = NULL;
		}
	}

	histogramme.first_print_name.texture = NULL;
	histogramme.second_print_name.texture = NULL;
	BL_change_histogramme(window, simulation_array, &histogramme);

	histogramme.legendes.nb_rects = 3;
	histogramme.legendes.rects = malloc(sizeof(SDL_Rect) * histogramme.legendes.nb_rects);
	histogramme.legendes.colors = malloc(sizeof(SDL_Color) * histogramme.legendes.nb_rects);
	histogramme.legendes.texts = malloc(sizeof(BL_Text) * histogramme.legendes.nb_rects);

	if(histogramme.legendes.rects == NULL || histogramme.legendes.colors == NULL || histogramme.legendes.texts == NULL){

		perror("malloc failed");
		exit(1);
	}

	histogramme.legendes.rects[0].x = 230;
	histogramme.legendes.rects[1].x = 230;
	histogramme.legendes.rects[2].x = 230;

	histogramme.legendes.rects[0].y = 150;
	histogramme.legendes.rects[1].y = 190;
	histogramme.legendes.rects[2].y = 230;

	histogramme.legendes.rects[0].w = 120;
	histogramme.legendes.rects[1].w = 120;
	histogramme.legendes.rects[2].w = 120;

	histogramme.legendes.rects[0].h = 20;
	histogramme.legendes.rects[1].h = 20;
	histogramme.legendes.rects[2].h = 20;

	histogramme.legendes.colors[0] = BL_get_rouge(255);
	histogramme.legendes.colors[1] = BL_get_jaune(255);
	histogramme.legendes.colors[2] = BL_get_vert(255);

	histogramme.legendes.texts[0] = BL_create_text(window, 230, 130, BL_get_blanc(200), "temps moyen restitution", "./source/fonts/times.ttf", 13);
	histogramme.legendes.texts[1] = BL_create_text(window, 230, 170, BL_get_blanc(200), "temps moyen attente", "./source/fonts/times.ttf", 13);
	histogramme.legendes.texts[2] = BL_create_text(window, 230, 210, BL_get_blanc(200), "temps moyen reponse", "./source/fonts/times.ttf", 13);

	histogramme.title_legende = BL_create_text(window, 270, 100, BL_get_blanc(200), "Legende", "./source/fonts/times.ttf", 15);

	return histogramme;
}

void BL_change_histogramme(BL_Window window, Simulation_array simulation_array, BL_Histogramme *histogramme){

	double max_value = BL_search_max_value(simulation_array, histogramme->index_first_print, histogramme->index_second_print);
	double max_hauteur = (double)450 - (double)150;
	int start_y = 450;

	//si l'histogramme contient un premier graphique
	if(histogramme->nb_blocks > 0){

		if(histogramme->first_print_name.texture != NULL){

			SDL_DestroyTexture(histogramme->first_print_name.texture);
		}

		if(histogramme->blocks[0].texts[0].texture != NULL){

			SDL_DestroyTexture(histogramme->blocks[0].texts[0].texture);
		}
		if(histogramme->blocks[0].texts[1].texture != NULL){

			SDL_DestroyTexture(histogramme->blocks[0].texts[1].texture);
		}
		if(histogramme->blocks[0].texts[2].texture != NULL){

			SDL_DestroyTexture(histogramme->blocks[0].texts[2].texture);
		}
		if(histogramme->cpu_usage_1.texture != NULL){

			SDL_DestroyTexture(histogramme->cpu_usage_1.texture);
		}
		if(histogramme->time_restitution_usage_1.texture != NULL){

			SDL_DestroyTexture(histogramme->time_restitution_usage_1.texture);
		}
		histogramme->first_print_name = BL_create_text(window, 400, 130, BL_get_blanc(200), get_string_from_algorithm(simulation_array.simulations[histogramme->index_first_print].code_algorithm), "./source/fonts/times.ttf", 13);
		
		double pourcentage1 = simulation_array.simulations[histogramme->index_first_print].average_time_attempt * (double)90 / max_value;
		double pourcentage2 = simulation_array.simulations[histogramme->index_first_print].average_time_restitution * (double)90 / max_value;
		double pourcentage3 = simulation_array.simulations[histogramme->index_first_print].average_time_respond * (double)90 / max_value;
		
		histogramme->blocks[0].rects[0].y = (int)max_hauteur + 150 - (int)(max_hauteur * pourcentage1 / (double)100);
		histogramme->blocks[0].rects[1].y = (int)max_hauteur + 150 - (int)(max_hauteur * pourcentage2 / (double)100);
		histogramme->blocks[0].rects[2].y = (int)max_hauteur + 150 - (int)(max_hauteur * pourcentage3 / (double)100);
		
		histogramme->blocks[0].rects[0].h = start_y - histogramme->blocks[0].rects[0].y;
		histogramme->blocks[0].rects[1].h = start_y - histogramme->blocks[0].rects[1].y;
		histogramme->blocks[0].rects[2].h = start_y - histogramme->blocks[0].rects[2].y;

		char number1[255];
		char number2[255];
		char number3[255];

		sprintf(number1, "%d", (int)simulation_array.simulations[histogramme->index_first_print].average_time_attempt);
		sprintf(number2, "%d", (int)simulation_array.simulations[histogramme->index_first_print].average_time_restitution);
		sprintf(number3, "%d", (int)simulation_array.simulations[histogramme->index_first_print].average_time_respond);

		histogramme->blocks[0].texts[0] = BL_create_text(window, histogramme->blocks[0].rects[0].x, histogramme->blocks[0].rects[0].y - 15, BL_get_blanc(200), number1, "./source/fonts/times.ttf", 15);
		histogramme->blocks[0].texts[1] = BL_create_text(window, histogramme->blocks[0].rects[1].x, histogramme->blocks[0].rects[1].y - 15, BL_get_blanc(200), number2, "./source/fonts/times.ttf", 15);
		histogramme->blocks[0].texts[2] = BL_create_text(window, histogramme->blocks[0].rects[2].x, histogramme->blocks[0].rects[2].y - 15, BL_get_blanc(200), number3, "./source/fonts/times.ttf", 15);
		
		char cpu_1[255];

		sprintf(cpu_1, "%d", (int)simulation_array.simulations[histogramme->index_first_print].average_pourcentage_CPU);

		histogramme->cpu_usage_1 = BL_create_text(window, 560, 480, BL_get_blanc(200), cpu_1, "./source/fonts/times.ttf", 15);

		char time_restitution_1[255];

		sprintf(time_restitution_1, "%d", (int)simulation_array.simulations[histogramme->index_first_print].time_restitution);

		histogramme->time_restitution_usage_1 = BL_create_text(window, 570, 500, BL_get_blanc(200), time_restitution_1, "./source/fonts/times.ttf", 15);
	}
	//si l'histogramme contient un deuxieme graphique
	if(histogramme->nb_blocks > 1){

		if(histogramme->second_print_name.texture != NULL){
			
			SDL_DestroyTexture(histogramme->second_print_name.texture);
		}
		if(histogramme->blocks[1].texts[0].texture != NULL){

			SDL_DestroyTexture(histogramme->blocks[1].texts[0].texture);
		}
		if(histogramme->blocks[1].texts[1].texture != NULL){

			SDL_DestroyTexture(histogramme->blocks[1].texts[1].texture);
		}
		if(histogramme->blocks[1].texts[2].texture != NULL){

			SDL_DestroyTexture(histogramme->blocks[1].texts[2].texture);
		}
		if(histogramme->cpu_usage_2.texture != NULL){

			SDL_DestroyTexture(histogramme->cpu_usage_2.texture);
		}
		if(histogramme->time_restitution_usage_2.texture != NULL){

			SDL_DestroyTexture(histogramme->time_restitution_usage_2.texture);
		}
		histogramme->second_print_name = BL_create_text(window, 590, 130, BL_get_blanc(200), get_string_from_algorithm(simulation_array.simulations[histogramme->index_second_print].code_algorithm), "./source/fonts/times.ttf", 13);
		
		double pourcentage1 = simulation_array.simulations[histogramme->index_second_print].average_time_attempt * (double)90 / max_value;
		double pourcentage2 = simulation_array.simulations[histogramme->index_second_print].average_time_restitution * (double)90 / max_value;
		double pourcentage3 = simulation_array.simulations[histogramme->index_second_print].average_time_respond * (double)90 / max_value;
		
		histogramme->blocks[1].rects[0].y = (int)max_hauteur + 150 - (int)(max_hauteur * pourcentage1 / (double)100);
		histogramme->blocks[1].rects[1].y = (int)max_hauteur + 150 - (int)(max_hauteur * pourcentage2 / (double)100);
		histogramme->blocks[1].rects[2].y = (int)max_hauteur + 150 - (int)(max_hauteur * pourcentage3 / (double)100);
		
		histogramme->blocks[1].rects[0].h = start_y - histogramme->blocks[1].rects[0].y;
		histogramme->blocks[1].rects[1].h = start_y - histogramme->blocks[1].rects[1].y;
		histogramme->blocks[1].rects[2].h = start_y - histogramme->blocks[1].rects[2].y;

		char number4[255];
		char number5[255];
		char number6[255];

		sprintf(number4, "%d", (int)simulation_array.simulations[histogramme->index_second_print].average_time_attempt);
		sprintf(number5, "%d", (int)simulation_array.simulations[histogramme->index_second_print].average_time_restitution);
		sprintf(number6, "%d", (int)simulation_array.simulations[histogramme->index_second_print].average_time_respond);

		histogramme->blocks[1].texts[0] = BL_create_text(window, histogramme->blocks[1].rects[0].x, histogramme->blocks[1].rects[0].y - 15, BL_get_blanc(200), number4, "./source/fonts/times.ttf", 15);
		histogramme->blocks[1].texts[1] = BL_create_text(window, histogramme->blocks[1].rects[1].x, histogramme->blocks[1].rects[1].y - 15, BL_get_blanc(200), number5, "./source/fonts/times.ttf", 15);
		histogramme->blocks[1].texts[2] = BL_create_text(window, histogramme->blocks[1].rects[2].x, histogramme->blocks[1].rects[2].y - 15, BL_get_blanc(200), number6, "./source/fonts/times.ttf", 15);
		
		char cpu_2[255];
		
		sprintf(cpu_2, "%d", (int)simulation_array.simulations[histogramme->index_second_print].average_pourcentage_CPU);

		histogramme->cpu_usage_2 = BL_create_text(window, 760, 480, BL_get_blanc(200), cpu_2, "./source/fonts/times.ttf", 15);
		
		char time_restitution_2[255];

		sprintf(time_restitution_2, "%d", (int)simulation_array.simulations[histogramme->index_second_print].time_restitution);

		histogramme->time_restitution_usage_2 = BL_create_text(window, 770, 500, BL_get_blanc(200), time_restitution_2, "./source/fonts/times.ttf", 15);
	}	
}

double BL_search_max_value(Simulation_array simulation_array, int first_index, int second_index){

	if(first_index > -1){

		double value = simulation_array.simulations[first_index].average_time_attempt;

		if(value < simulation_array.simulations[first_index].average_time_restitution){

			value = simulation_array.simulations[first_index].average_time_restitution;
		}
		if(value < simulation_array.simulations[first_index].average_time_respond){

			value = simulation_array.simulations[first_index].average_time_respond;
		}
		
		if(second_index > - 1){

			if(value < simulation_array.simulations[second_index].average_time_attempt){

				value = simulation_array.simulations[second_index].average_time_attempt;
			}
			if(value < simulation_array.simulations[second_index].average_time_restitution){

				value = simulation_array.simulations[second_index].average_time_restitution;
			}
			if(value < simulation_array.simulations[second_index].average_time_respond){

				value = simulation_array.simulations[second_index].average_time_respond;
			}
		}

		return value;
	}

	return -1;
}

void BL_change_graphe_1(BL_Window window, Simulation_array simulation_array, BL_Histogramme *histogramme){

	histogramme->index_first_print++;
	if(histogramme->index_first_print >= histogramme->max_index){

		histogramme->index_first_print = 0;
	}
	BL_change_histogramme(window, simulation_array, histogramme);
}

void BL_change_graphe_2(BL_Window window, Simulation_array simulation_array, BL_Histogramme *histogramme){

	histogramme->index_second_print++;
	if(histogramme->index_second_print >= histogramme->max_index){

		histogramme->index_second_print = 0;
	}
	BL_change_histogramme(window, simulation_array, histogramme);
}
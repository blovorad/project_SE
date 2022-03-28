#ifndef __GRAPHE__H__
#define __GRAPHE__H__

#include "define.h"
#include "gui.h"
#include "color.h"
#include "simulation.h"
#include "util.h"

/**
 * \file graphe.h
 * \author Gautier Levesque
 * \brief fichier entete pour la creation et gestion des graphes
 */

typedef struct{

	int nb_rects;
	SDL_Rect *rects;
	SDL_Color *colors;
	BL_Text *texts;
}BL_Block;

typedef struct{

	int nb_blocks;
	int nb_legendes;
	BL_Block *blocks;
	BL_Block legendes;
	BL_Text title_legende;

	BL_Text x_label;
	BL_Text y_label;
	BL_Text title;

	BL_Button button_graphe_1;
	BL_Button button_graphe_2;

	int index_first_print;
	int index_second_print;
	int max_index;
	BL_Text first_print_name;
	BL_Text second_print_name;

	BL_Text cpu_usage_1;
	BL_Text cpu_usage_2;
	BL_Text cpu_legend_1;
	BL_Text cpu_legend_2;

	BL_Text time_restitution_usage_1;
	BL_Text time_restitution_usage_2;
	BL_Text time_restitution_legend_1;
	BL_Text time_restitution_legend_2;
}BL_Histogramme;

/**
 * \fn BL_Histogramme generate_histogramme(BL_Window window, Simulation_array simulation_array)
 * \author Gautier Levesque
 * \brief creation de l'histogramme pour le projet
 * \param window necessaire pour creer les textures de textes
 * \param simulation_array tableau des resultats de la simulation pour generation de l'histogramme
 * \return BL_Histogramme, l'histogramme creer par la fonction
 */
BL_Histogramme generate_histogramme(BL_Window window, Simulation_array simulation_array);

/**
 * \fn void BL_change_histogramme(BL_Window window, Simulation_array simulation_array, BL_Histogramme *histogramme)
 * \author Gautier Levesque
 * \brief changer le graphe 1 ou 2 de l'histogramme
 * \param window pour pouvoir recreer les textures de textes qui vont changer
 * \param simulation_array pour pouvoir recreer les textures de textes qui vont changer
 * \param histogramme l'histogramme en question, sert a savoir quelle nouveau graphique on affiche
 */
void BL_change_histogramme(BL_Window window, Simulation_array simulation_array, BL_Histogramme *histogramme);

/**
 * \fn double BL_search_max_value(Simulation_array simulation_array, int first_index, int second_index)
 * \author Gautier Levesque
 * \brief permet de connaitre la valeur maximal de toutes les moyennes pour pouvoir faire un coeficient de proportionalite dessus
 * \param simulation_array pour la comparaison des valeurs
 * \param first_index ou chercher dans le tableau de simulation_array
 * \param second_index ou chercher dans le tableau de simulation_array
 * \return double, la valeur maximal de toutes les variables de chaque simulation
 */
double BL_search_max_value(Simulation_array simulation_array, int first_index, int second_index);

/**
 * \fn void BL_change_graphe_1(BL_Window window, Simulation_array simulation_array, BL_Histogramme *histogramme)
 * \author Gautier Levesque
 * \brief Permet de changer le graphique a afficher dans la premiere partie de l'histogramme
 * \param window passage pour pouvoir recreer les textures de textes qui vont changer
 * \param simulation_array passage pour pouvoir recreer les textures de textes qui vont changer
 * \param histogramme l'histogramme en question, sert a savoir quelle nouveau graphique on affiche
 */
void BL_change_graphe_1(BL_Window window, Simulation_array simulation_array, BL_Histogramme *histogramme);

/**
 * \fn void BL_change_graphe_2(BL_Window window, Simulation_array simulation_array, BL_Histogramme *histogramme)
 * \author Gautier Levesque
 * \brief Permet de changer le graphique a afficher dans la deuxieme partie de l'histogramme
 * \param window passage pour pouvoir recreer les textures de textes qui vont changer
 * \param simulation_array passage pour pouvoir recreer les textures de textes qui vont changer
 * \param histogramme l'histogramme en question, sert a savoir quelle nouveau graphique on affiche
 */
void BL_change_graphe_2(BL_Window window, Simulation_array simulation_array, BL_Histogramme *histogramme);

#endif
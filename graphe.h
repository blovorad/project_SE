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

/**
 * \struct BL_Block graphe.h
 * \brief variable pour la gestion des barres d'un histogramme
 */
typedef struct{

	int nb_rects; /*!< nombre de barres */
	SDL_Rect *rects; /*!< tableau de barres */
	SDL_Color *colors; /*!< couleur des barres */
	BL_Text *texts; /*!< texte sur les barres */
}BL_Block;

/**
 * \struct BL_Histogramme graphe.h
 * \brief variable pour la gestion d'histogramme
 */
typedef struct{

	int nb_blocks; /*!< nombre d'ensembles de barres */
	int nb_legendes; /*!< nombre de barres de legende */
	BL_Block *blocks; /*!< tableau d'ensemble de barres */
	BL_Block legendes; /*!< barre pour la legende */
	BL_Text title_legende; /*!< titre de la legende */

	BL_Text x_label; /*!< nom de l'abscisse de l'histogramme */
	BL_Text y_label; /*!< nom de l'ordonnee de l'histogramme */
	BL_Text title; /*!< titre de l'histogramme */

	BL_Button button_graphe_1; /*!< bouton pour gerer le graphe 1 */
	BL_Button button_graphe_2; /*!< bouton pour gerer le graphe 2 */

	int index_first_print; /*!< index de la simulation a afficher sur l'histogramme 1 */
	int index_second_print; /*!< index de la simulation a afficher sur l'histogramme 2 */
	int max_index; /*!< nombre maximal de simulations */
	BL_Text first_print_name; /*!< nom de la premiere simulation */
	BL_Text second_print_name; /*!< nom de la deuxieme simulation */

	BL_Text cpu_usage_1; /*!< utilisation cpu de la premiere simulation */
	BL_Text cpu_usage_2; /*!< utilisation cpu de la deuxieme simulation */
	BL_Text cpu_legend_1; /*!< texte qui va decrire l'utilisation de la premiere simulation */
	BL_Text cpu_legend_2; /*!< texte qui va decrire l'utilisation de la deuxieme simulation */

	BL_Text time_restitution_usage_1; /*!< temps de restitution de la premiere simulation */
	BL_Text time_restitution_usage_2; /*!<  temps de restitution de la deuxieme simulation */
	BL_Text time_restitution_legend_1; /*!< texte qui va decrire le temps de restitution de la premiere simulation */
	BL_Text time_restitution_legend_2; /*!< texte qui va decrire le temps de restitution de la deuxieme simulation */
}BL_Histogramme;

/**
 * \fn BL_Histogramme generate_histogramme(BL_Window window, Simulation_array simulation_array)
 * \author Gautier Levesque
 * \brief creation de l'histogramme pour le projet
 * \param window necessaire pour creer les textures de textes
 * \param simulation_array tableau des resultats de la simulation pour generation de l'histogramme
 * \return BL_Histogramme, l'histogramme cree par la fonction
 */
BL_Histogramme generate_histogramme(BL_Window window, Simulation_array simulation_array);

/**
 * \fn void BL_change_histogramme(BL_Window window, Simulation_array simulation_array, BL_Histogramme *histogramme)
 * \author Gautier Levesque
 * \brief changer le graphe 1 ou 2 de l'histogramme
 * \param window pour pouvoir recreer les textures de textes qui vont changer
 * \param simulation_array pour pouvoir recreer les textures de textes qui vont changer
 * \param histogramme l'histogramme en question, sert a savoir quel nouveau graphique on affiche
 */
void BL_change_histogramme(BL_Window window, Simulation_array simulation_array, BL_Histogramme *histogramme);

/**
 * \fn double BL_search_max_value(Simulation_array simulation_array, int first_index, int second_index)
 * \author Gautier Levesque
 * \brief permet de connaitre la valeur maximale de toutes les moyennes pour pouvoir faire un coefficient de proportionnalite dessus
 * \param simulation_array pour la comparaison des valeurs
 * \param first_index ou chercher dans le tableau de simulation_array
 * \param second_index ou chercher dans le tableau de simulation_array
 * \return double, la valeur maximale de toutes les variables de chaque simulation
 */
double BL_search_max_value(Simulation_array simulation_array, int first_index, int second_index);

/**
 * \fn void BL_change_graphe_1(BL_Window window, Simulation_array simulation_array, BL_Histogramme *histogramme)
 * \author Gautier Levesque
 * \brief Permet de changer le graphique a afficher dans la premiere partie de l'histogramme
 * \param window passage pour pouvoir recreer les textures de textes qui vont changer
 * \param simulation_array passage pour pouvoir recreer les textures de textes qui vont changer
 * \param histogramme l'histogramme en question, sert a savoir quel nouveau graphique on affiche
 */
void BL_change_graphe_1(BL_Window window, Simulation_array simulation_array, BL_Histogramme *histogramme);

/**
 * \fn void BL_change_graphe_2(BL_Window window, Simulation_array simulation_array, BL_Histogramme *histogramme)
 * \author Gautier Levesque
 * \brief Permet de changer le graphique a afficher dans la deuxieme partie de l'histogramme
 * \param window passage pour pouvoir recreer les textures de textes qui vont changer
 * \param simulation_array passage pour pouvoir recreer les textures de textes qui vont changer
 * \param histogramme l'histogramme en question, sert a savoir quel nouveau graphique on affiche
 */
void BL_change_graphe_2(BL_Window window, Simulation_array simulation_array, BL_Histogramme *histogramme);

#endif

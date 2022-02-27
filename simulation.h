#ifndef __SIMULATION__H__
#define __SIMULATION__H__

#include "processus.h"

/**
 * \file simulation.h
 * \author Gautier Levesque
 * \date 29/01/2022
 * \brief fichier entete qui gere la simulation, contient entre autre la structure du resultat et parametres de la simulation
 */

/**
 * \enum Algorithm
 * \brief Constantes pour les codes des algorithmes
 *
 * Agorithm est une série de constantes definissant les algo utiliser 
 * fonctions de l'objet Agorithm.
 */
typedef enum{
	
	FIFO, /*!< Algo FIFO */
	SJF, /*!< Algo SJF */
	SRJF, /*!< Algo SRJF */
	ROUND_ROBIN /*!< Algo ROUND_ROBIN */
}Algorithm;

/**
 * \struct Simulation simulation.h
 * \brief Constantes pour les codes des algorithmes
 *
 * Simulation definie les parametres de la simulation ainsi que ses resultats
 */
typedef struct{

    Algorithm code_algorithm; /*!< code de l'algo lier a l'enumeration Algorithm */
    int quantum; /*!< si round_robin */
    double average_time_attempt; /*!< temps moyen d'attente de tous les processus */
    double average_time_restitution; /*!< temps moyen de restitution de l'algorithme */
    double average_time_respond; /*!< temps de reponse moyen de l'algorithme */
    double average_pourcentage_CPU; /*!< utilisation de CPU */
    Processus_array processus_array; /*!< processus qui compose la simulation */
}Simulation;


/**
 * \struct Simulation_array simulation.h
 * \brief gerer un tableau de simuation, chaque simulation est lier a un algorithme d'ordonnancement
 */
typedef struct{
	
	int nbSimulations; /*!< nombre de simulation */
	Simulation *simulations;/*!< tableau des simulations */
}Simulation_array;

/**
 * \fn int start_simulation(Simulation_array *simulation_array)
 * \author Gautier Levesque
 * \date 27/02/2022
 * \brief lancer la simulation
 * \param simulation_array tableau contenant tout les algorithmes d'ordonnacement a lancer
 * \return entier 0 si ok, -1 si erreur
 */
int start_simulation(Simulation_array *simulation_array);

#endif

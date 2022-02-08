#ifndef __SIMULATION__H__
#define __SIMULATION__H__

/**
 * \file simulation.h
 * \author Gautier Levesque
 * \date 29/01/2022
 * \brief fichier entete qui gere la simulation, contient entre autre la structure du resultat et parametre de la simulation
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

    Algorithm code_algorithm; /*!< code de l'algo lier a l'enumeration Algorithm*/
    int quantum; /*!< si round_robin > 0*/
    double average_time_attempt; /*!< temps moyen d'attente de tout les processus*/
    double average_time_restitution; /*!< temps moyen de restitution de l'algorithme*/
    double average_time_respond; /*!< temps de reponse moyen de l'algorithme*/
    double average_pourcentage_CPU; /*!< utilisation de CPU*/
}Simulation;

#endif

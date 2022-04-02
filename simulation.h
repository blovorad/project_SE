#ifndef __SIMULATION__H__
#define __SIMULATION__H__

#include "processus.h"

/**
 * \file simulation.h
 * \author Gautier Levesque
 * \date 29/01/2022
 * \brief fichier entete qui gere la simulation, contient entre autre la structure du resultat et les parametres de la simulation
 */

/**
 * \enum Algorithm
 * \brief Constantes pour les codes des algorithmes
 *
 * Algorithm est une serie de constantes definissant les algorithmes utilises 
 * fonctions de l'objet Algorithm.
 */
typedef enum{
	
	FIFO, /*!< Algo FIFO */
	SJF, /*!< Algo SJF */
	ROUND_ROBIN /*!< Algo ROUND_ROBIN */
}Algorithm;

/**
 * \struct Simulation simulation.h
 * \brief Constantes pour les codes des algorithmes
 *
 * Simulation definit les parametres de la simulation ainsi que ses resultats
 */
typedef struct{

    Algorithm code_algorithm; /*!< code de l'algo lier a l'enumeration Algorithm */
    int quantum; /*!< si round_robin */
    double average_time_attempt; /*!< temps moyen d'attente de tous les processus */
    double average_time_restitution; /*!< temps moyen de restitution des processus de l'algorithme */
    double time_restitution; /*!< temps de restitution de l'algorithme */
    double average_time_respond; /*!< temps de reponse moyen de l'algorithme */
    double average_pourcentage_CPU; /*!< utilisation de CPU */
    Processus_array processus_array; /*!< tableau des processus qui composent la simulation */
}Simulation;


/**
 * \struct Simulation_array simulation.h
 * \brief gerer un tableau de simuations, chaque simulation est liee a un algorithme d'ordonnancement
 */
typedef struct{
	
	int nbSimulations; /*!< nombre de simulations */
	Simulation *simulations;/*!< tableau des simulations */
}Simulation_array;

#endif

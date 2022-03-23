#ifndef __ROUNDROBIN__H__
#define __ROUNDROBIN__H__

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <signal.h>

#include "simulation.h"
#include "util.h"
#include "resultat.h"
#include "config.h"
#include "ipcTools.h"

/**
 * \file round-robin.h
 * \author Ouliana Anikienko
 * \date 03/03/2022
 * \brief fichier entete associe a l'algorithme d'ordonnancement round-robin
 */

/*! \def CPU_BUSY
    \brief Un signal qu'un processus fils envoie pour dire qu'il occcupe la CPU.
*/ 
#define CPU_BUSY 1

/*! \def CPU_FREE
    \brief Un signal qu'un processus fils envoie pour dire qu'il libere la CPU.
*/
#define CPU_FREE 2

#endif
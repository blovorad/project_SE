#include "define.h"
#include "draw.h"
#include "init.h"
#include "timer.h"
#include "update.h"
#include "input.h"
#include "mouse.h"
#include "gui.h"
#include "starter.h"
#include "graphe.h"

int main(int argc, char *argv[]){

    Simulation_array simulation_array;

    if(start_simulations(argc, argv, &simulation_array) != 0){

        return 1;
    }

    BL_Window window;
    BL_Input input;
    BL_Mouse mouse;
    BL_Graphics graphics;
    BL_Timer timer;

    SDL_bool go = SDL_TRUE;

    if(BL_init_timer(&timer) == SDL_FALSE){

        go = SDL_FALSE;
    }

    if(go == SDL_TRUE){

        go = BL_init(&window, &graphics, &input, &mouse);
    }

    BL_Array_text array_text;
    BL_Array_button array_button;
    BL_Histogramme histogramme;
array_button.nb_buttons = 0;
    array_text.nb_texts = 2;
    array_text.texts = malloc(sizeof(BL_Text) * array_text.nb_texts);
    if(array_text.texts == NULL){

        BL_clean(&window, &graphics, &histogramme);
        return 1;
    }

    array_text.texts[0] = BL_create_text(window, 13, 5, BL_get_blanc(200), "Interface graphique d'affichage des résultats des simulations des algorithmes d'ordonnancement", "./fonts/times.ttf", 20);
    array_text.texts[1] = BL_create_text(window, 2, 585, BL_get_blanc(200), "Projet réalisé par O. Anikienko, M. Aberkane, G. Levesque pour le cours de système d'exploitation de la licence 3 d'informatique de CY Cergy Paris Université, 2021-2022", "./fonts/times.ttf", 11);

    BL_Panel panel = BL_create_panel(0, 0, 800, 600, SDL_TRUE, -1, BL_get_noir(255), array_text, array_button);

    histogramme = generate_histogramme(window, simulation_array);

while(go == SDL_TRUE){

        go = BL_update(window, timer.ms, &input, &mouse, &panel, &histogramme, simulation_array);

        if(go == SDL_TRUE){

            go = BL_draw(window.renderer, graphics, panel, histogramme);
        }

        if(BL_update_timer(&timer, 1000 / MAX_FPS) == SDL_FALSE){

            SDL_Delay( (1000 / MAX_FPS) - timer.ms);
        }
        timer.ms /= MAX_FPS;
    }

    BL_clean(&window, &graphics, &histogramme);

    return 0;
}


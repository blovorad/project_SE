#ifndef __GUI__H__
#define __GUI__H__

#include "define.h"
#include "mouse.h"
#include "font.h"
#include "color.h"
#include "texture.h"
#include "window.h"

/**
 * \file gui.h
 * \author Gautier Levesque
 * \brief fichier entete qui regroupe les fonctions/defines/structures utiles a la gestion de la GUI
 */

/**
 * \struct BL_Text gui.h
 * \brief structure pour la gestion de texte
 */
typedef struct{

	SDL_Rect position; /*!< position du texte */
	SDL_Texture *texture; /*!< texture a afficher du texte */

	int rapport_x; /*!< si jamais on doit bouger le texte par rapport a un panel */
	int rapport_y; /*!< si jamais on doit bouger le texte par rapport a un panel */
}BL_Text;

/**
 * \struct BL_Array_text gui.h
 * \brief structure pour la gestion de tableau de textes
 */
typedef struct{

	int nb_texts; /*!< nombre de textes dans le tableau */
	BL_Text *texts; /*!< tableau de textes */
}BL_Array_text;

/**
 * \struct BL_Button gui.h
 * \brief structure pour la gestion de bouton
 */
typedef struct{

	SDL_Rect position; /*!< position du bouton */
	SDL_Color color; /*!< couleur du bouton */
	int index_texture; /*!< index de la texture du bouton dans le tableau de graphics */
	SDL_bool is_hoover; /*!< si le bouton est survole */
	SDL_bool is_pressed; /*!< si le bouton est presse */
	SDL_bool is_visible; /*!< si le bouton est visible */
	SDL_bool fill; /*!< si le bouton est rempli de couleur */
	BL_Text text; /*!< le texte du bouton */

	int event; /*!< indice de la fonction a executer dans le tableau d'event */

	int rapport_x; /*!< si jamais on doit bouger le texte par rapport a un panel */
	int rapport_y; /*!< si jamais on doit bouger le texte par rapport a un panel */
}BL_Button;

/**
 * \struct BL_Array_button gui.h
 * \brief structure pour la gestion de tableau de bouton
 */
typedef struct{

	int nb_buttons; /*!< nombre de boutons dans le tableau */
	BL_Button *buttons; /*!< tableau de boutons */
}BL_Array_button;

/**
 * \struct BL_Panel gui.h
 * \brief structure pour la gestion de panel
 */
typedef struct{

	SDL_Rect position; /*!< position du panel */
	SDL_Color color; /*!< couleur du panel */
	int index_texture; /*!< index de la texture du panel dans le tableau de graphics */
	SDL_bool is_selected; /*!< si le panel est selectionne, si on a clique dessus */
	SDL_bool is_visible; /*!< si le panel est visible */
	SDL_bool fill; /*!< si le panel est rempli de la couleur */

	//to moving panel
	int dif_x; /*!< variable pour savoir combien il y a entre la position de la souris et le bord haut gauche du panel */
	int dif_y; /*!< variable pour savoir combien il y a entre la position de la souris et le bord haut gauche du panel */
 
	BL_Array_text array_text; /*!< tableau de texte attache au panel */
	BL_Array_button array_button; /*!< tableau de bouton attache au panel */
}BL_Panel;

/**
 * \fn BL_Button BL_create_button(BL_Window window, int x, int y, int w, int h, SDL_bool fill, int index_texture, SDL_Color color, int event,  SDL_Color text_color, char *text, char *font_path)
 * \author Gautier Levesque
 * \brief creaton d'un bouton
 * \param window structure contenant une variable, renderer qui est utile pour la creation de texture
 * \param x position x du bouton
 * \param y position y du bouton
 * \param w largeur du bouton
 * \param h hauteur du bouton
 * \param fill si le bouton est rempli ou non par une couleur
 * \param index_texture -1 si aucune texture n'est utilisee sinon envoyer son index par rapport au tableau de graphics
 * \param color la couleur du bouton
 * \param event index dans le tableau event d'une fonction qui s'execute a l'appui du bouton
 * \param text_color la couleur du texte
 * \param text le texte du bouton
 * \param font_path le chemin vers la police utilisee
 * \return BL_Button le bouton cree
 */
BL_Button BL_create_button(BL_Window window, int x, int y, int w, int h, SDL_bool fill, int index_texture, SDL_Color color, int event,  SDL_Color text_color, char *text, char *font_path);

/**
 * \fn BL_Panel BL_create_panel(int x, int y, int w, int h, SDL_bool fill, int index_texture, SDL_Color color, BL_Array_text array_text, BL_Array_button array_button)
 * \author Gautier Levesque
 * \brief creation d'un panel
 * \param x position x du panel
 * \param y position y du panel
 * \param w largeur du panel
 * \param h hauteur du panel
 * \param fill si le panel est rempli ou non par une couleur
 * \param index_texture -1 si aucune texture n'est utilisee sinon envoyer son index par rapport au tableau de graphics
 * \param color la couleur du panel
 * \param array_text tableau de tous les textes qui sont attaches au panel
 * \param array_button tableau de tous les boutons qui sont attaches au panel
 * \return BL_Panel le panel cree
 */
BL_Panel BL_create_panel(int x, int y, int w, int h, SDL_bool fill, int index_texture, SDL_Color color, BL_Array_text array_text, BL_Array_button array_button);

/**
 * \fn BL_Text BL_create_text(BL_Window window, int x, int y, SDL_Color color, char *text_string, char *path, int size_text)
 * \author Gautier Levesque
 * \brief creation d'un texte
 * \param window structure contenant une variable, renderer qui est utile pour la creation de texture
 * \param x position x du panel
 * \param y position y du panel
 * \param color la couleur du panel
 * \param text_string chaine de caractere du texte
 * \param path le chemin vers la police utilisee
 * \param size_text la taille du texte 
 * \return BL_Text le texte qui est cree
 */
BL_Text BL_create_text(BL_Window window, int x, int y, SDL_Color color, char *text_string, char *path, int size_text);

/**
 * \fn SDL_bool BL_update_panel(BL_Window window, BL_Mouse *mouse, BL_Panel *panel)
 * \author Gautier Levesque
 * \brief fonction qui actualise le contexte d'un panel
 * \param window structure contenant des variables necessaires a l'actualisation
 * \param panel le panel concerne par l'actualisation
 * \param mouse la souris pour savoir si le panel reagit en fonction de la position de la souris
 * \return booleen si la mise a jour a echoue ou non, SDL_FALSE si echec, SDL_TRUE sinon
 */
SDL_bool BL_update_panel(BL_Window window, BL_Mouse *mouse, BL_Panel *panel);

/**
 * \fn void BL_panel_set_visible(BL_Panel *panel, SDL_bool visible)
 * \author Gautier Levesque
 * \brief fonction qui change la variable visible d'un panel
 * \param panel le panel concerne par le changement
 * \param visible booleen qui represente si le panel est visible ou non
 */
void BL_panel_set_visible(BL_Panel *panel, SDL_bool visible);

/**
 * \fn void BL_panel_set_selected(BL_Panel *panel, SDL_bool selected)
 * \author Gautier Levesque
 * \brief fonction qui change la variable selected d'un panel
 * \param panel le panel concerne par le changement
 * \param selected booleen qui represente si le panel est selectionne ou non
 */
void BL_panel_set_selected(BL_Panel *panel, SDL_bool selected);

/**
 * \fn void BL_panel_set_position(BL_Panel *panel, int x, int y)
 * \author Gautier Levesque
 * \brief fonction qui place un panel sur un endroit precis
 * \param panel le panel concerne par le deplacement
 * \param x un entier qui represente sa nouvelle position x
 * \param y un entier qui represente sa nouvelle position y
 */
void BL_panel_set_position(BL_Panel *panel, int x, int y);

/**
 * \fn void BL_panel_resized(BL_Panel *panel, int w, int h)
 * \author Gautier Levesque
 * \brief fonction qui change la taille d'un panel
 * \param panel le panel concerne par la resize
 * \param w un entier qui represente sa nouvelle largeur
 * \param h un entier qui represente sa nouvelle hauteur
 */
void BL_panel_resized(BL_Panel *panel, int w, int h);

#endif
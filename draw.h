#ifndef __DRAW__H__
#define __DRAW__H__

#include "define.h"

#include "texture.h"
#include "geometrie.h"
#include "color.h"
#include "gui.h"
#include "graphe.h"

/**
 * \file draw.h
 * \author Gautier Levesque
 * \brief fichier entete qui gere l'affichage de toutes les entites a l'ecran
 */

/**
 * \fn SDL_bool BL_draw_rect(SDL_Renderer *renderer, SDL_Rect *r, SDL_bool *fill, SDL_Color *couleur)
 * \author Gautier Levesque
 * \brief dessine un rectangle
 * \param renderer necessaire pour savoir sur quoi on applique le changement de couleur
 * \param r le rectangle a dessiner
 * \param fill si le rectangle est rempli de couleur ou vide de couleur
 * \param couleur la couleur du rectangle
 * \return boolean SDL_TRUE si le dessin est ok, SDL_FALSE sinon
 */
SDL_bool BL_draw_rect(SDL_Renderer *renderer, SDL_Rect *r, SDL_bool *fill, SDL_Color *couleur);

/**
 * \fn SDL_bool BL_draw_texture(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Rect *dst, SDL_Rect *src)
 * \author Gautier Levesque
 * \brief dessine une texture
 * \param renderer necessaire pour savoir sur quoi on applique le changement de couleur
 * \param texture la texture a dessiner
 * \param dst l'endroit ou le dessiner
 * \param src si on veut qu'une partie de la texture soit appliquee a un endroit precis, cette partie est indiquee dans src
 * \return boolean SDL_TRUE si le dessin est ok, SDL_FALSE sinon
 */
SDL_bool BL_draw_texture(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Rect *dst, SDL_Rect *src);

/**
 * \fn SDL_bool BL_draw_textureEx(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Rect *dst, SDL_Rect *src, SDL_Point *center, int angle, SDL_RendererFlip flip)
 * \author Gautier Levesque
 * \brief dessine une texture avec plus de details, on peut appliquer plus de choses dessus, une rotation ou autre
 * \param renderer necessaire pour savoir sur quoi on applique le changement de couleur
 * \param texture la texture a dessiner
 * \param dst l'endroit ou le dessiner
 * \param src si on veut qu'une partie de la texture soit appliquee a un endroit precis, cette partie est indiquee dans src
 * \param center pour savoir par rapport a quel point on dessine la texture
 * \param angle angle qui permet de donner la rotation de la texture
 * \param flip pour savoir si l'image doit etre tournee vers la gauche ou la droite
 * \return boolean SDL_TRUE si le dessin est ok, SDL_FALSE sinon
 */
SDL_bool BL_draw_textureEx(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Rect *dst, SDL_Rect *src, SDL_Point *center, int angle, SDL_RendererFlip flip);

/**
 * \fn SDL_bool BL_set_render_color(SDL_Renderer *renderer, SDL_Color *couleur)
 * \author Gautier Levesque
 * \brief permet d'appliquer une couleur sur le renderer, tout ce qui est dessine apres aura cette couleur
 * \param renderer necessaire pour savoir sur quoi on applique le changement de couleur
 * \param couleur la couleur pour le changement de couleur
 * \return boolean SDL_TRUE si le changement de couleur est ok, SDL_FALSE sinon
 */
SDL_bool BL_set_render_color(SDL_Renderer *renderer, SDL_Color *couleur);

/**
 * \fn SDL_bool BL_draw_line(SDL_Renderer *renderer, const int x1, const int y1, const int x2, const int y2, SDL_Color *couleur)
 * \author Gautier Levesque
 * \brief permet de dessiner une ligne
 * \param renderer necessaire pour savoir sur quoi on dessine
 * \param x1 l'abscisse du point 1
 * \param y1 l'ordonnee du point 1
 * \param x2 l'abscisse du point 2
 * \param y2 l'ordonnee du point 2
 * \param couleur la couleur de la ligne
 * \return boolean SDL_TRUE si le dessin est ok, SDL_FALSE sinon
 */
SDL_bool BL_draw_line(SDL_Renderer *renderer, const int x1, const int y1, const int x2, const int y2, SDL_Color *couleur);

/**
 * \fn SDL_bool BL_draw_point(SDL_Renderer *renderer, const int x, const int y, SDL_Color *couleur)
 * \author Gautier Levesque
 * \brief permet de dessiner un point
 * \param renderer necessaire pour savoir sur quoi on dessine
 * \param x l'abscisse du point
 * \param y l'ordonnee du point
 * \param couleur la couleur du point
 * \return boolean SDL_TRUE si le dessin est ok, SDL_FALSE sinon
 */
SDL_bool BL_draw_point(SDL_Renderer *renderer, const int x, const int y, SDL_Color *couleur);

/**
 * \fn SDL_bool BL_draw_cercle(SDL_Renderer *renderer, BL_Cercle cercle)
 * \author Gautier Levesque
 * \brief permet de dessiner un cercle
 * \param renderer necessaire pour savoir sur quoi on dessine
 * \param cercle le cercle a dessiner
 * \return boolean SDL_TRUE si le dessin est ok, SDL_FALSE sinon
 */
SDL_bool BL_draw_cercle(SDL_Renderer *renderer, BL_Cercle cercle);

/**
 * \fn SDL_bool BL_draw_disque(SDL_Renderer *renderer, BL_Cercle cercle)
 * \author Gautier Levesque
 * \brief permet de dessiner un disque
 * \param renderer necessaire pour savoir sur quoi on dessine
 * \param cercle le disque a dessiner
 * \return boolean SDL_TRUE si le dessin est ok, SDL_FALSE sinon
 */
SDL_bool BL_draw_disque(SDL_Renderer *renderer, BL_Cercle cercle);

/**
 * \fn SDL_bool BL_draw(SDL_Renderer *renderer, BL_Graphics graphics, BL_Panel panel, BL_Histogramme histogramme)
 * \author Gautier Levesque
 * \brief fonction core de dessin qui appelle toutes les autres
 * \param renderer necessaire pour savoir sur quoi on dessine
 * \param graphics le tableau de toutes les textures
 * \param panel le panel a dessiner
 * \param histogramme l'histogramme a dessiner
 * \return boolean SDL_TRUE si le dessin est ok, SDL_FALSE sinon
 */
SDL_bool BL_draw(SDL_Renderer *renderer, BL_Graphics graphics, BL_Panel panel, BL_Histogramme histogramme);

/*GUI PART*/

/**
 * \fn SDL_bool BL_draw_panel(SDL_Renderer *renderer, BL_Graphics graphics, BL_Panel panel)
 * \author Gautier Levesque
 * \brief dessine un panel
 * \param renderer necessaire pour savoir sur quoi on dessine
 * \param graphics le tableau de toutes les textures
 * \param panel le panel a dessiner
 * \return boolean SDL_TRUE si le dessin est ok, SDL_FALSE sinon
 */
SDL_bool BL_draw_panel(SDL_Renderer *renderer, BL_Graphics graphics, BL_Panel panel);

/**
 * \fn SDL_bool BL_draw_histogramme(SDL_Renderer *renderer, BL_Histogramme histogramme)
 * \author Gautier Levesque
 * \brief dessine un histogramme
 * \param renderer necessaire pour savoir sur quoi on dessine
 * \param histogramme l'histogramme a dessiner
 * \return boolean SDL_TRUE si le dessin est ok, SDL_FALSE sinon
 */
SDL_bool BL_draw_histogramme(SDL_Renderer *renderer, BL_Histogramme histogramme);

#endif
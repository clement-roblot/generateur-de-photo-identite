/**
 * \file refait.h
 * \brief Fonctions utiles à tous.
 * \author Clément.R
 * \version 0.1
 * \date 11 Juillet 2012
 *
 * Fichier contenant les fonctions pouvant être utiles à toutes les objets du programme.
 *
 */

#ifndef REFAIT_H
#define REFAIT_H

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv/cxcore.h>



/** \brief La distance maximale tolérée entre les centres de deux cercles pour qu'ils soient considérés comme ressemblants. */
#define TOLERANCE_CENTRE 10      //old = 10
/** \brief La diffférence maximale tolérée entre les rayons de deux cercles pour qu'ils soient considérés comme ressemblants. */
#define TOLERANCE_RAYON 20      //old : 20






IplImage *creer_copie_image(IplImage *src);
int pixel_non_noir(IplImage *src, int j, int i);
int pixel_non_noir_colonne(IplImage *src, int *y, int x, int height);
int cercle_inscrit(int x1, int y1, int rayon1, int x2, int y2, int rayon2);
void decalage_bas_droit(IplImage *src, int delage);
IplImage *seuiller_image(IplImage *src, int seuil);
IplImage *incruster(IplImage *support, IplImage *incrustation, CvPoint position);
int ressemble(CvPoint centre1, int rayon1, CvPoint centre2, int rayon2, int tolerance_centre = TOLERANCE_CENTRE,  int tolerance_rayon = TOLERANCE_RAYON);


#endif // REFAIT_H

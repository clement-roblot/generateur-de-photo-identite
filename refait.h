/*
Copyright (c) 2013 Clement Roblot


This file is part of Generateur de photo d'identite.

Generateur de photo d'identite is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Generateur de photo d'identite is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Generateur de photo d'identite.  If not, see <http://www.gnu.org/licenses/>.
*/



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

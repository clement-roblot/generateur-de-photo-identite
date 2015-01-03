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

#ifndef CONCEPTIONPLANCHE_H
#define CONCEPTIONPLANCHE_H

#include <QDialog>
#include <QDebug>
#include <QTimer>
#include <QFileDialog>
#include <QApplication>

#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include "clicableqgraphicsview.h"
#include "recadragephoto.h"

#define LARGEUR_PLANCHE 101 //mm
#define HAUTEUR_PLANCHE 152 //mm

#define LARGEUR_IMAGE   35  //mm
#define HAUTEUR_IMAGE   45  //mm

#define TAILLE_VISAGE   34  //mm de hauteur par default
#define OFFSETHAUTEUR   25     //On décale vers le haut le cadre du visage pour prendre en compte les cheuveux
                               //En pourcentage de la taille du visage

#define TAILLE_MIN_VISAGE   32
#define TAILLE_MAX_VISAGE   36
#define ECART_ENTRE_IMAGE_LARGEUR   10
#define ECART_ENTRE_IMAGE_VERTICALE 10

using namespace std;
using namespace cv;


namespace Ui {
class ConceptionPlanche;
}

class ConceptionPlanche : public QDialog
{
    Q_OBJECT
    
public:
    explicit ConceptionPlanche(Mat image, Rect visage, QWidget *parent = 0);
    ~ConceptionPlanche();
    
private slots:
    void actualiser(void);
    void on_boutonSauvegarder_clicked();
    void on_bouttonRecadrerImage_clicked();
    void recadrageFini(Rect visage);

private:
    Ui::ConceptionPlanche *ui;

    RecadragePhoto *reca;

    ClicableQGraphicsView *photo;
    Mat image;
    Mat imageSortie;
    Rect visage;
};

#endif // CONCEPTIONPLANCHE_H

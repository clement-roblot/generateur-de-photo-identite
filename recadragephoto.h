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


#ifndef RECADRAGEPHOTO_H
#define RECADRAGEPHOTO_H

#include <QDialog>

#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include "clicableqgraphicsview.h"



using namespace std;
using namespace cv;


namespace Ui {
class RecadragePhoto;
}

class RecadragePhoto : public QDialog
{
    Q_OBJECT
    
public:
    explicit RecadragePhoto(Mat source, QWidget *parent = 0);
    ~RecadragePhoto();

signals:
    void configFinie(Rect visage);
    
private slots:
    void on_bouttonOK_clicked();

    void on_bouttonFront_clicked();

    void on_bouttonMenton_clicked();

    void on_bouttonOreille_clicked();

    void clicPhoto(QMouseEvent *event);

private:
    Ui::RecadragePhoto *ui;

    void recalculerCadre(void);
    void actualiserImage(void);

    ClicableQGraphicsView *photo;

    Mat image;
    Mat tmp;
    Rect visage;

    CvPoint front;
    CvPoint menton;
    CvPoint oreille;

    int numeroPrise;    //numero du point que l'on est en train de déterminer

};

#endif // RECADRAGEPHOTO_H

/*
Copyright (c) 2013 Clement Roblot


This file is part of Generateur de photo d'identite.

Generateur de photo d'identite is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Foobar is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
*/


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QTimer>
#include <QFileDialog>
#include <QApplication>

#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include "clicableqgraphicsview.h"
#include "conceptionplanche.h"
#include "recadragephoto.h"


using namespace std;
using namespace cv;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:

    Rect detectAndDisplay(void);

    void on_bouttonEnregistrer_clicked();

    void on_chargerImage_clicked();

    void prendreImage(void);

    void on_actionPrendre_une_image_triggered();

    void rependreEnregistrement(void);

    void recadrageFini(Rect visage);

    void on_actionCharger_une_image_triggered();

signals:
    void captureFinie(void);
    void calculFini(void);

private:
    Ui::MainWindow *ui;

    CascadeClassifier face_cascade;

    CvCapture *web;

    ClicableQGraphicsView *image;

    Mat affichage;
    Mat raw;
    QTimer *timer;
    ConceptionPlanche *fenetreConception;
    RecadragePhoto *reca;



    void composer(Mat image, Rect visage);

};

#endif // MAINWINDOW_H

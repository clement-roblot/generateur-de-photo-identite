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


#include "recadragephoto.h"
#include "ui_recadragephoto.h"

RecadragePhoto::RecadragePhoto(Mat source, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RecadragePhoto)
{
    ui->setupUi(this);

    numeroPrise = 0;

    visage.x = 0;
    visage.y = 0;
    visage.width = 1;
    visage.height = 1;

    source.copyTo(image);

    photo = new ClicableQGraphicsView();
    photo->keep_image_ratio(true);
    photo->set_background_color(QColor(255, 255, 255));
    ui->photo->addWidget(photo);

    //actualiserImage();


    image.copyTo(tmp);
    IplImage tmpo = tmp;
    photo->display(&tmpo);


    connect(photo, SIGNAL(mousePressEventEvent(QMouseEvent*)), this, SLOT(clicPhoto(QMouseEvent*)));
}

RecadragePhoto::~RecadragePhoto()
{
    delete ui;
}



void RecadragePhoto::clicPhoto(QMouseEvent *event){


    switch(numeroPrise){

    case 1 :    front.x = event->x() - photo->get_position_image().x();
                front.y = event->y() - photo->get_position_image().y();
                break;

    case 2 :    manton.x = event->x() - photo->get_position_image().x();
                manton.y = event->y() - photo->get_position_image().y();
                break;

    case 3 :    oreille.x = event->x() - photo->get_position_image().x();
                oreille.y = event->y() - photo->get_position_image().y();
                break;

    default :   return;

    }

    cout << "clic en : " << event->x() << "; " << event->y() << " position de l'image : " << photo->get_position_image().x() << "; " << photo->get_position_image().y() << endl;

    recalculerCadre();

    numeroPrise = 0;
}


void RecadragePhoto::recalculerCadre(void){

    visage.x = (oreille.x<front.x?oreille.x:((2*front.x)-oreille.x))*image.cols/photo->get_taille_image().width;
    visage.y = (front.y)*image.rows/photo->get_taille_image().height;
    visage.height = (manton.y - front.y)*image.rows/photo->get_taille_image().height;
    visage.width = (2*abs(front.x-oreille.x))*image.cols/photo->get_taille_image().width;

    actualiserImage();
}

void RecadragePhoto::actualiserImage(void){

    image.copyTo(tmp);
    //rectangle(tmp, visage, Scalar( 255, 0, 0 ), 5);

    CvPoint oreille_reel;
    oreille_reel.x = oreille.x*image.cols/photo->get_taille_image().width;
    oreille_reel.y = oreille.y*image.rows/photo->get_taille_image().height;

    circle(tmp, oreille_reel, 10, Scalar( 255, 0, 0 ), 3);
    putText(tmp, "Oreille", oreille_reel, FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(200,200,250), 1, CV_AA);



    CvPoint front_reel;
    front_reel.x = front.x*image.cols/photo->get_taille_image().width;
    front_reel.y = front.y*image.rows/photo->get_taille_image().height;

    circle(tmp, front_reel, 10, Scalar( 255, 0, 0 ), 3);
    putText(tmp, "Crane", front_reel, FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(200,200,250), 1, CV_AA);



    CvPoint manton_reel;
    manton_reel.x = manton.x*image.cols/photo->get_taille_image().width;
    manton_reel.y = manton.y*image.rows/photo->get_taille_image().height;

    circle(tmp, manton_reel, 10, Scalar( 255, 0, 0 ), 3);
    putText(tmp, "Manton", manton_reel, FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(200,200,250), 1, CV_AA);





    IplImage tmpo = tmp;
    photo->display(&tmpo);
}

void RecadragePhoto::on_bouttonOK_clicked()
{
    emit configFinie(visage);
    this->close();
}

void RecadragePhoto::on_bouttonFront_clicked()
{
    numeroPrise = 1;
}

void RecadragePhoto::on_bouttonManton_clicked()
{
    numeroPrise = 2;
}

void RecadragePhoto::on_bouttonOreille_clicked()
{
    numeroPrise = 3;
}

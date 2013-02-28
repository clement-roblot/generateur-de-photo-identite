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


#include "conceptionplanche.h"
#include "ui_conceptionplanche.h"

ConceptionPlanche::ConceptionPlanche(Mat image, Rect visage, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConceptionPlanche)
{
    ui->setupUi(this);

    this->visage = visage;
    image.copyTo(this->image);


    photo = new ClicableQGraphicsView();
    photo->keep_image_ratio(true);
    photo->set_background_color(QColor(50, 50, 50));
    ui->gauche->addWidget(photo);



    ui->tailleDuVisage->setMinimum(TAILLE_MIN_VISAGE);
    ui->tailleDuVisage->setValue(TAILLE_VISAGE);
    ui->tailleDuVisage->setMaximum(TAILLE_MAX_VISAGE);


    ui->hauteurDuVisage->setValue(0);
    ui->largeurDuVisage->setValue(0);

    actualiser();

    connect(ui->tailleDuVisage, SIGNAL(valueChanged(int)), this, SLOT(actualiser()));
    connect(ui->hauteurDuVisage, SIGNAL(valueChanged(int)), this, SLOT(actualiser()));
    connect(ui->largeurDuVisage, SIGNAL(valueChanged(int)), this, SLOT(actualiser()));
}

ConceptionPlanche::~ConceptionPlanche()
{
    delete ui;
}



void ConceptionPlanche::actualiser(void){

    int resol = visage.height/ui->tailleDuVisage->value();
    if(resol<=0) resol=1;   //évite de planter lorsque l'utilisateur fait n'import quoi

    int largeur = 35*resol; //taille de la photo a generer en px
    int hauteur = 45*resol; //taille de la photo a generer en px

    //calcul de la position de cadre pour extraire le visage de la photo originale
    int x = (visage.x + (visage.width/2))-(largeur/2)+(ui->largeurDuVisage->value()*resol);
    int y = (visage.y + (visage.height/2))-(hauteur/2)+(ui->hauteurDuVisage->value()*resol);

    Rect sortie;
    sortie.x = x;
    sortie.y = y;
    sortie.width = largeur;
    sortie.height = hauteur;

    //on test si on sort pas de l'image
    if(sortie.x<0) sortie.x = 0;
    if(sortie.x>(image.cols-2))sortie.x = image.cols-2;
    if(sortie.y<0) sortie.y = 0;
    if(sortie.y>(image.rows-2))sortie.y = image.rows-2;
    if(sortie.x+sortie.width>image.cols)sortie.width = image.cols-sortie.x;
    if(sortie.width<1)sortie.width = 1;
    if(sortie.y+sortie.height>image.rows)sortie.height = image.rows-sortie.y;
    if(sortie.height<1)sortie.height = 1;

    Mat imageUniqueSortie = image(sortie);

    imageSortie.create(150*resol, 100*resol, CV_8UC3);
    imageSortie = Scalar(255, 255, 255);

    Rect tmp;
    tmp.x = ECART_ENTRE_IMAGE_LARGEUR*resol; tmp.y = ECART_ENTRE_IMAGE_VERTICALE*resol; tmp.width = sortie.width; tmp.height = sortie.height;
    imageUniqueSortie.copyTo(imageSortie(tmp));
    tmp.x = (ECART_ENTRE_IMAGE_LARGEUR+HAUTEUR_IMAGE)*resol; tmp.y = ECART_ENTRE_IMAGE_VERTICALE*resol; tmp.width = sortie.width; tmp.height = sortie.height;
    imageUniqueSortie.copyTo(imageSortie(tmp));
    tmp.x = ECART_ENTRE_IMAGE_LARGEUR*resol; tmp.y = ((2*ECART_ENTRE_IMAGE_VERTICALE)+HAUTEUR_IMAGE)*resol; tmp.width = sortie.width; tmp.height = sortie.height;
    imageUniqueSortie.copyTo(imageSortie(tmp));
    tmp.x = (ECART_ENTRE_IMAGE_LARGEUR+HAUTEUR_IMAGE)*resol; tmp.y = ((2*ECART_ENTRE_IMAGE_VERTICALE)+HAUTEUR_IMAGE)*resol; tmp.width = sortie.width; tmp.height = sortie.height;
    imageUniqueSortie.copyTo(imageSortie(tmp));



    IplImage ipl_img = imageSortie;
    photo->display(&ipl_img);
}

void ConceptionPlanche::on_boutonSauvegarder_clicked()
{

    QFileDialog *dialog;
    dialog = new QFileDialog( this, QString::fromUtf8("Choisi un fichier image").toAscii());
    dialog->setAcceptMode(QFileDialog::AcceptSave);
    dialog->setFileMode(QFileDialog::AnyFile);
    dialog->setDefaultSuffix("jpg");
    dialog->show();

    if(dialog->exec() == QDialog::Accepted){    //si on valide un fichier correctement

        imwrite(dialog->selectedFiles().value(0).toUtf8().constData(), imageSortie);
        this->close();
    }
}

void ConceptionPlanche::on_bouttonRecadrerImage_clicked()
{
    reca = new RecadragePhoto(image, this);
    reca->show();
    //reca->setCadre(visage);
    connect(reca, SIGNAL(configFinie(Rect)), this, SLOT(recadrageFini(Rect)));
}


void ConceptionPlanche::recadrageFini(Rect visage){

    this->visage = visage;
    actualiser();
}

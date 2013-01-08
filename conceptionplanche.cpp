#include "conceptionplanche.h"
#include "ui_conceptionplanche.h"

ConceptionPlanche::ConceptionPlanche(Mat image, Rect visage, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::ConceptionPlanche)
{
    ui->setupUi(this);


    this->visage = visage;
    image.copyTo(this->image);


    photo = new ClicableQGraphicsView();
    photo->keep_image_ratio(true);
    photo->set_background_color(QColor(50, 50, 50));
    ui->gauche->addWidget(photo);



    ui->tailleDuVisage->setValue(TAILLE_VISAGE);
    ui->hauteurDuVisage->setValue(OFFSETHAUTEUR);

    actualiser();


    connect(ui->tailleDuVisage, SIGNAL(valueChanged(int)), this, SLOT(actualiser()));
    connect(ui->hauteurDuVisage, SIGNAL(valueChanged(int)), this, SLOT(actualiser()));
}

ConceptionPlanche::~ConceptionPlanche()
{
    delete ui;
}


void ConceptionPlanche::actualiser(void){

    int resol = visage.height/ui->tailleDuVisage->value();
    int largeur = 35*resol; //en px
    int hauteur = 45*resol; //en px

    int x = (visage.x + (visage.width/2))-(largeur/2);
    int y = (visage.y + (visage.height/2))-(hauteur/2)+(ui->hauteurDuVisage->value()*resol);

    Rect sortie;
    sortie.x = x;
    sortie.y = y;
    sortie.width = largeur;
    sortie.height = hauteur;

    Mat imageUniqueSortie = image(sortie);

    Mat imageSortie;
    imageSortie.create(150*resol, 100*resol, CV_8UC3);
    imageSortie = Scalar(255, 255, 255);

    Rect tmp;
    tmp.x = 10*resol; tmp.y = 10*resol; tmp.width = sortie.width; tmp.height = sortie.height;
    imageUniqueSortie.copyTo(imageSortie(tmp));
    tmp.x = 55*resol; tmp.y = 10*resol; tmp.width = sortie.width; tmp.height = sortie.height;
    imageUniqueSortie.copyTo(imageSortie(tmp));
    tmp.x = 10*resol; tmp.y = 65*resol; tmp.width = sortie.width; tmp.height = sortie.height;
    imageUniqueSortie.copyTo(imageSortie(tmp));
    tmp.x = 55*resol; tmp.y = 65*resol; tmp.width = sortie.width; tmp.height = sortie.height;
    imageUniqueSortie.copyTo(imageSortie(tmp));


    IplImage ipl_img = imageSortie;
    photo->display(&ipl_img);

    //enregistrerImage(imageSortie);
}

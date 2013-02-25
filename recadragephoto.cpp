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

    actualiserImage();

    connect(photo, SIGNAL(mousePressEventEvent(QMouseEvent*)), this, SLOT(clicPhoto(QMouseEvent*)));
}

RecadragePhoto::~RecadragePhoto()
{
    delete ui;
}


void RecadragePhoto::setCadre(Rect cadre){

    //ne fonctionne pas

    front.x = cadre.x+(cadre.width/2); front.y = cadre.y;
    manton.x = cadre.x+(cadre.width/2); manton.y = cadre.y+cadre.height;
    oreille.x = cadre.x; oreille.y = cadre.y+(cadre.height/2);


    recalculerCadre();
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
    rectangle(tmp, visage, Scalar( 255, 0, 0 ), 5);

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

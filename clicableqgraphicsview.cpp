#include "clicableqgraphicsview.h"

ClicableQGraphicsView::ClicableQGraphicsView(QWidget *)
{
    source_image = NULL;
    displayed_image = NULL;
    scene = NULL;

    keep_ratio = false;
    cursor = false;
    zoom = true;
    resize = true;

    aide = NULL;
    afficher_aide = false;

    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}


ClicableQGraphicsView::~ClicableQGraphicsView()
{
    if(source_image) cvReleaseImage(&source_image);
    if(displayed_image) cvReleaseImage(&displayed_image);
    if(scene) delete scene;
    if(aide) delete aide;
}


/**
  * \brief Fonction permettant d'ajouter une ligne à l'aide
  * \param msg Chaine de caractère à afficher.
  * \param couleur Pointeur vers la couleur du carre à afficher devant la ligne.
  *
  * Cette fonction va ajouter une ligne à l'aide si le pointeur couleur
  * vaut null, il n'y aura pas de carre affiché.
  */
void ClicableQGraphicsView::append_aide(QString msg, QColor *couleur)
{
    if(aide == NULL) aide = new QList<Aide>();

    Aide tmp;
    tmp.chaine = msg;       //on recopie les valeurs passés en paramètre
    tmp.couleur = couleur;

    aide->append(tmp);      //on ajoute à la liste

    refresh();              //on recalcul l'image
}



/**
  * \brief Fonction appelée lorsqu'on clique.
  *
  * Cette fonction ne fait que réimplémenter le signal de clique.
  */
void ClicableQGraphicsView::mousePressEvent(QMouseEvent *event){

    emit mousePressEventEvent(event);

    if( (event->x() > position_image.x()) && (event->x() < (position_image.x()+100)) ){       //si on est dans le coin suppérieur gauche de l'image (sur la légende)
        if( (event->y() > position_image.y()) && (event->y() < (position_image.y()+100)) ){       //si on est dans le coin suppérieur gauche de l'image (sur la légende)

            afficher_aide = !afficher_aide;
            refresh();
        }
    }
}

/**
  * \brief Fonction appelée lorsqu'on déplace la sourie.
  *
  * Cette fonction ne fait que réimplémenter le signal de déplacement de la sourie.
  */
void ClicableQGraphicsView::mouseMoveEvent(QMouseEvent *event){
    emit mouseMoveEventEvent(event);
}

/**
  * \brief Fonction appelée lorsqu'on relache le clique.
  *
  * Cette fonction ne fait que réimplémenter le signal de relachement du clique.
  */
void ClicableQGraphicsView::mouseReleaseEvent(QMouseEvent *event){
    emit mouseReleaseEventEvent(event);
}

/**
  * \brief Fonction appelée lorsqu'on double clique.
  *
  * Cette fonction ne fait que réimplémenter le signal de double clique.
  */
void ClicableQGraphicsView::mouseDoubleClickEvent(QMouseEvent *event){
    emit mouseDoubleEventEvent(event);
}

/**
  * \brief Fonction appelée lorsqu'on redimentionne.
  *
  * Cette fonction ne fait que réimplémenter le signal de clique.
  */
void ClicableQGraphicsView::resizeEvent(QResizeEvent *)
{
    refresh();
}

/**
  * \brief Fonction de remise à jour de l'affichage.
  *
  * Cette fonction recalcul l'image à afficher.
  */
void ClicableQGraphicsView::refresh(void)
{
    if(source_image){   //si une image à afficher est définie

        QSize taille;

        if(resize){
            if(zoom){   //si on doit la maximiser

                taille = this->size();
                if(keep_ratio){ //si on doit garder le ration de l'image

                    double ratio;
                    ratio = source_image->width*1.0/source_image->height*1.0;   //on calcul le ratio
                    if(taille.height()*ratio < taille.width()){     //puis on recalcul la plus grande (largeur ou hauteur) avec le ratio

                        taille.setWidth(taille.height()*ratio);
                    }else{

                        taille.setHeight(taille.width()/ratio);
                    }
                }
                taille_image = cvSize((int)taille.width(), (int)taille.height());

                //on calcul la position de l'image
                if(this->width() > taille.width()){

                    position_image.setY(0);
                    position_image.setX( ((this->width()-taille.width())/2) );
                }else{

                    position_image.setY( ((this->height()-taille.height())/2) );
                    position_image.setX(0);
                }
            }else{  //si on ne doit pas maximiser l'image

                taille_image = cvSize(source_image->width, source_image->height);    //on ne redimentionne pas

                position_image.setY(0);
                position_image.setX(0);
            }


            if( (taille_image.height > 0) && (taille_image.width > 0) ){  //si il y a des pixels à afficher

                if(displayed_image) cvReleaseImage(&displayed_image);
                displayed_image = cvCreateImage(taille_image, source_image->depth, source_image->nChannels);
                cvResize(source_image, displayed_image);    //on redimentionne l'image



                if(scene)delete scene;
                scene = new QGraphicsScene();   //on recréé une scene
                scene->setBackgroundBrush(QBrush(couleurBackground, Qt::SolidPattern));


                QImage tmp;
                tmp = IplImage2QImage(displayed_image); //on converti l'image

                QPixmap font;
                font = QPixmap::fromImage(tmp);     //on applique l'image

                scene->addPixmap(font);     //on l'ajoute à la scene


                if(afficher_aide && aide){

                    for(int i=0; i<aide->size(); i++){

                        QGraphicsTextItem *text;
                        //text = scene->addText(aide->value(i).chaine.toAscii());
                        text = scene->addText(QString().fromUtf8(aide->value(i).chaine.toStdString().c_str()));
                        text->setDefaultTextColor(QColor(255, 255, 255));

                        if(aide->value(i).couleur == NULL){

                            text->setPos(0, i*TAILLE_DE_LIGNE);
                        }else{

                            //QGraphicsRectItem *rectangle;
                            //rectangle = scene->addRect(5, i*TAILLE_DE_LIGNE+5, 10, 10, QPen(*(aide->value(i).couleur)), QBrush(*(aide->value(i).couleur)));

                            text->setPos(15, i*TAILLE_DE_LIGNE);
                        }
                    }
                }


                this->update();
                this->setScene(scene);      //on met à jour l'affichage
            }
        }
    }
}


/**
  * \brief Fonction permetant d'afficher une image d'opencv
  * \param src est un pointeur vers l'image à afficher
  *
  * Cette fonction va créer une copie de l'image src et va l'afficher.
  */
void ClicableQGraphicsView::display(IplImage *src)
{
    if(source_image) cvReleaseImage(&source_image); //on libère l'image en mémoire
    source_image = creer_copie_image(src);  //on copie en local l'image envoyée

    refresh();  //on recalcul l'affichage
}



/**
  * \brief Fonction permetant de convertire une IplImage en QImage.
  * \param iplimage est un pointeur vers l'image à afficher
  *
  * Cette fonction va convertire une IplImage en QImage.
  */
QImage ClicableQGraphicsView::IplImage2QImage(const IplImage *iplImage)
{

    int height = iplImage->height;
    int width = iplImage->width;

    if(iplImage->depth == IPL_DEPTH_8U && iplImage->nChannels == 3){    //si on aune image couleur

        const uchar *qImageBuffer = (const uchar*)iplImage->imageData;
        QImage img(qImageBuffer, width, height, QImage::Format_RGB888);
        return img.rgbSwapped();

    }else if( (iplImage->depth == IPL_DEPTH_8U) && (iplImage->nChannels == 1) ){    //si on a une image noir et blanc

        IplImage *tmp = cvCreateImage(cvGetSize(iplImage), IPL_DEPTH_8U, 3);

        for(int i=0; i< iplImage->width; i++){      //on la convertie en une image couleur
            for(int j=0; j < iplImage->height; j++){

                int numero_pixel = (j*tmp->widthStep + tmp->nChannels*i);
                int numero_pixel2 = (j*iplImage->widthStep + iplImage->nChannels*i);

                tmp->imageData[numero_pixel + 0] = iplImage->imageData[numero_pixel2];
                tmp->imageData[numero_pixel + 1] = iplImage->imageData[numero_pixel2];
                tmp->imageData[numero_pixel + 2] = iplImage->imageData[numero_pixel2];
            }
        }

        const uchar *qImageBuffer = (const uchar*)tmp->imageData;
        QImage img(qImageBuffer, width, height, QImage::Format_RGB888);

        cvReleaseImageHeader(&tmp);

        return img;

    }else{

        return QImage();
    }
}




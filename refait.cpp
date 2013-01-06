#include "refait.h"


/**
  * \brief Cette fonction crée une copie d'une image opencv.
  * \param src pointeur vers l'image à copier.
  * \return Pointeur vers l'image qui vient d'être créée
  *
  * Cette fonction va créer une nouvelle image et copier celle passée en paramètre dans la nouvelle
  * qu'elle retournera enfin.
  */
IplImage *creer_copie_image(IplImage *src)
{
    if(src == NULL) return 0;
    IplImage *tmp;

    tmp = cvCreateImage(cvGetSize(src), src->depth, src->nChannels);
    cvCopy(src, tmp);

    return tmp;
}

/**
  * \brief Cette fonction test si un pixel est alumé ou éteint.
  * \param src pointeur vers l'image à tester.
  * \param j Ordonée du pixel à tester.
  * \param i Abscisse du mixel à tester.
  * \return 1 si le pixel est alumé, 0 sinon.
  *
  * Cette fonction va tester si le pixel est allumé ou non. Elle fonctionne
  * avec les images à valeurs négatives comme positives.
  */
int pixel_non_noir(IplImage *src, int j, int i)
{

    int numero_pixel;
    numero_pixel = (j*src->widthStep + src->nChannels*i);

    if(numero_pixel >= src->imageSize) return 0;


    if(src->imageData[numero_pixel + 0] < 0) return 1;
    if(src->imageData[numero_pixel + 1] < 0) return 1;
    if(src->imageData[numero_pixel + 2] < 0) return 1;

    if(src->imageData[numero_pixel + 0] > 50) return 1;
    if(src->imageData[numero_pixel + 1] > 50) return 1;
    if(src->imageData[numero_pixel + 2] > 50) return 1;

    return 0;
}

/**
  * \brief Cette fonction test une colone de pixel contient encore un pixel alumé.
  * \param src pointeur vers l'image à tester.
  * \param y Pointeur vers l'ordonée de la colone à tester (la fonction y mettra la valeur du premier pixel alumé si il existe).
  * \param x Abscisse de la colone à tester.
  * \param height hauteur de la colone à tester.
  * \return 1 si la colone contient au moins un pixel alumé, 0 sinon.
  *
  * Cette fonction va tester si le pixel est allumé ou non. Elle fonctionne
  * avec les images à valeurs négatives comme positives.
  */
int pixel_non_noir_colonne(IplImage *src, int *y, int x, int height)
{
    for(int i=0; i<height; i++){

        if(pixel_non_noir(src, ((*y)+i), x)){

            *y += i;
            return 1;
        }
    }
    return 0;
}


/**
  * \brief Cette fonction Permet de décaler vers le bas droite l'image.
  * \param src pointeur vers l'image à décaler.
  * \param delage emplitude du décalage à réaliser (en pixels).
  *
  * Cette fonction va décaler l'image de delage pixels vers le bas droite,
  * cela permet de compenser le décalage entrainé par certaines transformations.
  */
void decalage_bas_droit(IplImage *src, int delage)
{
    int numero_pixel, numero_nouveau_pixel;

    for(int i=(src->width-1); i >= 0; i--){
        for(int j=(src->height-1); j >= 0; j--){

            numero_pixel = (j*src->widthStep + src->nChannels*i);

            if( (j >= delage) && (i >= delage) ){

                numero_nouveau_pixel = ((j-delage)*src->widthStep + src->nChannels*(i-delage));


                src->imageData[numero_pixel + 0] = src->imageData[numero_nouveau_pixel + 0];
                src->imageData[numero_pixel + 1] = src->imageData[numero_nouveau_pixel + 1];
                src->imageData[numero_pixel + 2] = src->imageData[numero_nouveau_pixel + 2];
            }else{

                src->imageData[numero_pixel + 0] = 0;
                src->imageData[numero_pixel + 1] = 0;
                src->imageData[numero_pixel + 2] = 0;
            }
        }
    }

}


/**
  * \brief Cette fonction determine si deux cercles sont inscrits l'un dans l'autre.
  * \param x1 Abscice du centre du premier cercle.
  * \param y1 Ordonnée du centre du premier cercle.
  * \param rayon1 Rayon du premier cercle.
  * \param x2 Abscice du centre du second cercle.
  * \param y2 Abscice du centre du second cercle.
  * \param rayon2 Rayon du second cercle.
  * \return 0 si les deux cercles sont distincts, 1 si le second est dans le premier et 2 si le premier est dans le second.
  *
  * Cette fonction va determiner lequel des deux cercles est contenu dans l'autre, ou si ils sont distincts.
  */
int cercle_inscrit(int x1, int y1, int rayon1, int x2, int y2, int rayon2)
{
    double disance_entre_centres;
    disance_entre_centres = sqrt( (pow(x2-x1, 2.0)) + (pow(y2-y1, 2.0)) );


    double pourcentage_tolerence = 50;  //pourcentage d'inclusion autorisée

    double tolerence1 = (pourcentage_tolerence*rayon1) / 100.0;   //tolérence sur l'inclucion du cercle 1 dans le 2
    double tolerence2 = (pourcentage_tolerence*rayon2) / 100.0;   //tolérence sur l'inclucion du cercle 2 dans le 1

    if( (disance_entre_centres-rayon2) < (rayon1-tolerence2)) return rayon1 > rayon2 ? 1 : 2;
    else if( (disance_entre_centres-rayon1) < (rayon2-tolerence1)) return rayon1 > rayon2 ? 1 : 2;
    else if( (disance_entre_centres < rayon2) && (disance_entre_centres < rayon1) ){

        return rayon1 > rayon2 ? 1 : 2;
    }

    return 0;
}



/**
  * \brief Cette fonction permet d'appliquer un seuil à une image.
  * \param src Pointeur vers l'image que l'on veut binariser.
  * \param seuil valeur du seuil que l'on veux appliquer.
  * \return un pointeur vers l'image binaire nouvellement créée.
  *
  * Cette fonction permet d'appliquer un seuil à une image.
  */
IplImage *seuiller_image(IplImage *src, int seuil)
{
    IplImage *tmp;
    tmp = cvCreateImage(cvGetSize(src), src->depth, src->nChannels);
    cvThreshold(src, tmp, seuil, 255, CV_THRESH_BINARY);
    return tmp;
}


/**
  * \brief Cette fonction permet d'incruster une image dans une autre
  * \param support Pointeur vers l'image dans laquelle on veut faire l'incrustation.
  * \param Incrustation Pointeur vers l'image que l'on veut incruster.
  * \param position Point où l'on veut placer l'incrustation sur le support.
  * \return un pointeur vers l'image incrustée.
  *
  * Cette fonction permet d'incruster une image dans une autre en un endroit définit.
  */
IplImage *incruster(IplImage *support, IplImage *incrustation, CvPoint position)
{
    IplImage *tmp, *incruste_tmp;
    CvRect ROI = cvRect(position.x, position.y, incrustation->width, incrustation->height);

    if(incrustation->nChannels == 3) incruste_tmp = creer_copie_image(incrustation);
    else if(incrustation->nChannels == 1){

        incruste_tmp = cvCreateImage(cvGetSize(incrustation), incrustation->depth, 3);

        for(int i=0; i<incrustation->width; i++){
            for(int j=0; j<incrustation->height; j++){

                int numero_pixel = (j*incruste_tmp->widthStep + incruste_tmp->nChannels*i);
                int numero_pixel2 = (j*incrustation->widthStep + incrustation->nChannels*i);

                incruste_tmp->imageData[numero_pixel + 0] = incrustation->imageData[numero_pixel2];
                incruste_tmp->imageData[numero_pixel + 1] = incrustation->imageData[numero_pixel2];
                incruste_tmp->imageData[numero_pixel + 2] = incrustation->imageData[numero_pixel2];
            }
        }

    }else return 0;



    //tmp = creer_copie_image(support);
    tmp = support;
    cvSetImageROI(tmp, ROI);
    cvCopy(incruste_tmp, tmp);
    cvResetImageROI(tmp);

    cvReleaseImage(&incruste_tmp);

    return tmp;
}


/**
  * \brief Fonction determinant si deux cercles sont ressemblants ou non.
  * \param centre1 est le point centrale du premier cercle.
  * \param rayon1 est le rayon du premier cercle.
  * \param centre2 est le point centrale du secon cercle.
  * \param rayon2 est le rayon du secon cercle.
  * \return 1 si les deux cercles sont ressemblants, 0 sinon.
  *
  * Cette fonction va meusurer la distance entre les deux centres des cercles et la différence entre leurs rayons.
  * Si ces écarts sont dans les tolérences, on retourn 1 sinon 0.
  */
int ressemble(CvPoint centre1, int rayon1, CvPoint centre2, int rayon2, int tolerance_centre,  int tolerance_rayon)
{
    if( (sqrt(pow((centre2.x-centre1.x), 2)+pow((centre2.y-centre1.y), 2)) < tolerance_centre) && ((rayon1-rayon2) < tolerance_rayon) ) return 1;
    else return 0;
}

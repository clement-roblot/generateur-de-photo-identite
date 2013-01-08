#include "mainwindow.h"
#include "ui_mainwindow.h"



//TODO
//- passer la cliqablegraphicsview en mat au lieu des IplImages
//- documenter le code
//- ajouter une nouvelle fenetre pour pouvoir configurer l'image exporte (notament l'offset en hauteur)
//- faire un fichier readme qui roxx avec des images d'exemple
//- lorsqu'on dezzom beaucoup, on sort de l'image et on plante

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    image = new ClicableQGraphicsView();
    image->keep_image_ratio(true);
    image->set_background_color(QColor(255, 255, 255));
    ui->gauche->addWidget(image);


    if(!face_cascade.load("./references/haarcascade_frontalface_alt.xml")){

        qDebug("Erreur lors du chargement du fichier de caractéristique des visages.\n");
    }

    web = cvCreateCameraCapture(-1);
    if(!web){

        cout << "erreur d'ouverture de la webcam" << endl;
    }



    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(prendreImage()));
    timer->start(100);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::prendreImage(void){

    timer->stop();

    raw = cvQueryFrame(web);

    detectAndDisplay();

    timer->start();
}



Rect MainWindow::detectAndDisplay(void)
{
   std::vector<Rect> faces;
   Mat frame_gray;

   raw.copyTo(affichage);

   cvtColor( affichage, frame_gray, CV_BGR2GRAY );
   equalizeHist( frame_gray, frame_gray );

   //-- Detect faces
   face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0, Size(80, 80) );

   //-- Draw the face
   if(faces.size() == 1){

       //Point center( faces[0].x + faces[0].width/2, faces[0].y + faces[0].height/2 );
       //ellipse( affichage, center, Size( faces[0].width/2, faces[0].height/2), 0, 0, 360, Scalar( 255, 0, 0 ), 2, 8, 0 );
       rectangle(affichage, faces[0], Scalar( 255, 0, 0 ), 5);
   }

   //-- Show what you got
   IplImage ipl_img = affichage;
   image->display(&ipl_img);

   //return faces[0];
   if(faces.size() == 1){
       return faces[0];
   }else{
       Rect tmp;
       return tmp;
   }

}

void MainWindow::on_bouttonEnregistrer_clicked()
{
    timer->stop();

    Rect visage;
    visage = detectAndDisplay();

    composer(raw, visage);

    //timer->start();
}


void MainWindow::composer(Mat image, Rect visage){

    timer->stop();

    ConceptionPlanche *fenetreConception = new ConceptionPlanche(image, visage);
    fenetreConception->show();
    //connect(fenetreConception, SIGNAL(destroyed()), this, SLOT(rependreEnregistrement()));
}



void MainWindow::on_chargerImage_clicked()
{

    //Sinon on ouvre une fenètre de selection du fichier
    QStringList file;
    QFileDialog *dialog;
    dialog = new QFileDialog( this, QString::fromUtf8("Choisi un fichier image").toAscii());
    dialog->setAcceptMode(QFileDialog::AcceptOpen);

    dialog->show();


    if(dialog->exec() == QDialog::Accepted){    //si on valide dans la fenètre de selection de fichier

        file = dialog->selectedFiles();

        timer->stop();

        raw = cvLoadImage(file.value(0).toAscii());

        Rect visage;
        visage = detectAndDisplay();

        composer(raw, visage);
    }
}

void MainWindow::on_actionPrendre_une_image_triggered()
{
    on_bouttonEnregistrer_clicked();
}

void MainWindow::rependreEnregistrement(void){

    timer->start();
}

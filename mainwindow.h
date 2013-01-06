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



#define TAILLE_VISAGE   34
#define OFFSETHAUTEUR   -3     //TAILLE_VISAGE-OFFSETHAUTEUR < 45       On décale vers le haut le cadre du visage pour prendre en compte les cheuveux


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



    void composer(Mat image, Rect visage);

    void enregistrerImage(Mat image);
};

#endif // MAINWINDOW_H

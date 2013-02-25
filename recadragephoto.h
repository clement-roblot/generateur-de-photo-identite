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

    void on_bouttonManton_clicked();

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
    CvPoint manton;
    CvPoint oreille;

    int numeroPrise;    //numero du point que l'on est en train de déterminer

};

#endif // RECADRAGEPHOTO_H

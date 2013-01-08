#ifndef CONCEPTIONPLANCHE_H
#define CONCEPTIONPLANCHE_H

#include <QFrame>

namespace Ui {
class ConceptionPlanche;
}

class ConceptionPlanche : public QFrame
{
    Q_OBJECT
    
public:
    explicit ConceptionPlanche(QWidget *parent = 0);
    ~ConceptionPlanche();
    
private:
    Ui::ConceptionPlanche *ui;
};

#endif // CONCEPTIONPLANCHE_H

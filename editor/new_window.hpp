#ifndef _NEW_WINDOW_H_
#define _NEW_WINDOW_H_

#include<QDialog>
#include<QLineEdit>
#include<QPushButton>
#include "../level.hpp"

class NewWindow : public QDialog {
    Q_OBJECT
public:
    NewWindow(game::Level *lvl, QWidget *parent);
public slots:
    void createMap();   

private:
    QLineEdit *page_width1, *page_height1;
    QPushButton *page_create;
    game::Level *level;    
};


#endif
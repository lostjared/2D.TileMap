#ifndef _NEW_WINDOW_H_
#define _NEW_WINDOW_H_

#include<QDialog>
#include<QLineEdit>
#include<QPushButton>
#include<QComboBox>

#include "../level.hpp"

class MainWindow;

class NewWindow : public QDialog {
    Q_OBJECT
public:
    NewWindow(game::Level *lvl, QWidget *parent);
    void setMainWindow(MainWindow *w);
public slots:
    void createMap();   
    void createNewGfx();
private:
    QLineEdit *page_width1, *page_height1;
    QPushButton *page_create;
    game::Level *level; 
    MainWindow *main_window;
    QComboBox *gfx_box;
    QPushButton *page_new_gfx;

};


#endif
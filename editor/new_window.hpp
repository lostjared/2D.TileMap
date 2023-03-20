#ifndef _NEW_WINDOW_H_
#define _NEW_WINDOW_H_

#include<QDialog>
#include<QLineEdit>
#include<QPushButton>
#include<QComboBox>
#include<QLabel>
#include "../level.hpp"

class MainWindow;

class NewWindow : public QDialog {
    Q_OBJECT
public:
    NewWindow(game::Level *lvl, QWidget *parent);
    void setMainWindow(MainWindow *w);
    QComboBox *gfx_box;
public slots:
    void createMap();   
    void createNewGfx();
    void setDirectory();
private:
    QLineEdit *page_width1, *page_height1;
    QPushButton *page_create;
    game::Level *level; 
    MainWindow *main_window;
    QPushButton *page_new_gfx;
    QPushButton *page_extract_dir;
    QLabel *extract_dir;
    QLineEdit *page_name;

};


#endif
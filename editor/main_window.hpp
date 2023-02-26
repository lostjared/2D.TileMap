#ifndef _EDITOR_H__
#define _EDITOR_H__

#include<QMainWindow>
#include<QMenu>
#include<QAction>
#include<QVector>
#include"tool_window.hpp"
#include"new_window.hpp"

const int MAP_WIDTH=1280/16;
const int MAP_HEIGHT=720/16;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow();
    void paintEvent(QPaintEvent *p);
public slots:
    void openNewMenu();

private:
    QMenu *file_menu;
    QAction *file_new;

    ToolWindow *tool_window;  
    NewWindow *new_window;  

    QVector<QImage> images;
    
    void loadImages();
};



#endif
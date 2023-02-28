#ifndef _EDITOR_H__
#define _EDITOR_H__

#include<QMainWindow>
#include<QMenu>
#include<QAction>
#include<QVector>
#include"tool_window.hpp"
#include"new_window.hpp"
#include "../level.hpp"

const int MAP_WIDTH=1280/16;
const int MAP_HEIGHT=720/16;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow();
    void paintEvent(QPaintEvent *p) override;
    void mouseMoveEvent(QMouseEvent *e) override;
    void mousePressEvent(QMouseEvent *e) override;
    void keyPressEvent(QKeyEvent *e) override;
    void createdNewMap();
    void setTile(const QPoint &pos);
    void updateLabelText();
public slots:
    void openNewMenu();
    void cameraChanged(int value);

private:
    QMenu *file_menu;
    QAction *file_new;

    ToolWindow *tool_window;  
    NewWindow *new_window;  

    QVector<QImage> images;
    QVector<game::Tile> tiles; 
    void loadImages();
    game::Level level;
    bool map_init;
    int pos_x, pos_y;
};



#endif
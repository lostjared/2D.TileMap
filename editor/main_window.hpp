#ifndef _EDITOR_H__
#define _EDITOR_H__

#include<QMainWindow>
#include<QMenu>
#include<QAction>
#include<QVector>
#include<QPainter>
#include<QProcess>
#include"tool_window.hpp"
#include"new_window.hpp"
#include"run_window.hpp"
#include"debug_window.hpp"
#include"gfx_window.hpp"
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
    void leaveEvent(QEvent *e) override;
    void keyPressEvent(QKeyEvent *e) override;
    void createdNewMap();
    void setTile(const QPoint &pos);
    void setObject(const QPoint &pos);
    void updateLabelText();
    void updateTitle();
    void drawLayer1(QPainter &paint);
    void drawLayer2(QPainter &paint);
    void drawLayer3(QPainter &paint);
    void closeEvent(QCloseEvent *c) override;
public slots:
    void openNewMenu();
    void saveFile();
    void saveFileAs();
    void loadFile();
    void cameraChanged(int value);
    void levelUp();
    void levelDown();
    void levelLeft();
    void levelRight();
    void updateMap(int);
    void runSettings();
    void runExec();
    void shutdownProgram();
    void procStopped(int exitcode, QProcess::ExitStatus status);
    void readStdout();
    void levelGraphicsOpen();
private:
    QMenu *file_menu, *level_menu, *run_menu;
    QAction *file_new, *file_save,*file_save_as,*file_load, *file_exit;
    QAction *level_left, *level_right, *level_down, *level_up, *level_gfx;
    QAction *run_settings, *run_exec;
    ToolWindow *tool_window;  
    NewWindow *new_window;  
    RunWindow *run_window;
    DebugWindow *debug_window;
    GfxWindow *gfx_window;
    QVector<QImage> images;
    QVector<QImage> col;
    QVector<game::Tile> tiles; 
    void loadImages();
    game::Level level;
    bool map_init;
    int pos_x, pos_y;
    QString file_name;
    bool cursor_visible;
    QPoint draw_pos;
    QProcess *proc = nullptr;
    bool proc_run = false;
    #ifdef __APPLE__
    const int offset_x = 0;
    const int offset_y = 0;
    #else
    const int offset_x = 0;
    const int offset_y = 24;
    #endif
};

#endif
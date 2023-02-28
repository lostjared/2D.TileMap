#ifndef _TOOL_WINDOW_H_
#define _TOOL_WINDOW_H_

#include<QDialog>
#include<QComboBox>
#include<QScrollBar>
#include<QLabel>
#include<cstdint>

class ToolWindow : public QDialog {
    Q_OBJECT
public:
    ToolWindow(QWidget *parent);
    int current_tile = 1;
    QComboBox *tiles;
    QComboBox *tool;
    QScrollBar *camera_x, *camera_y;
    QLabel *lbl_x, *lbl_y;
};

#endif
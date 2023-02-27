#ifndef _TOOL_WINDOW_H_
#define _TOOL_WINDOW_H_

#include<QDialog>
#include<QComboBox>

class ToolWindow : public QDialog {
    Q_OBJECT
public:
    ToolWindow(QWidget *parent);
    int current_tile = 1;
    QComboBox *tiles;
    QComboBox *tool;
};

#endif
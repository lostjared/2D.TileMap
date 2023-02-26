#ifndef _TOOL_WINDOW_H_
#define _TOOL_WINDOW_H_

#include<QDialog>

class ToolWindow : public QDialog {
    Q_OBJECT
public:
    ToolWindow(QWidget *parent);
};

#endif
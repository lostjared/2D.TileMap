#include"tool_window.hpp"

ToolWindow::ToolWindow(QWidget *parent) : QDialog(parent) {
    setFixedSize(150, 480);
    setWindowTitle(tr("Tool Window"));
}
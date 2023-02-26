#include"new_window.hpp"

NewWindow::NewWindow(QWidget *parent) : QDialog(parent) {
    setFixedSize(640, 480);
    setWindowTitle(tr("New Map"));
}
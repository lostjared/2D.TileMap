#include"gfx_window.hpp"
#include"main_window.hpp"

GfxWindow::GfxWindow(QWidget *parent) : QDialog(parent) {
    setFixedSize(800, 600);
    setWindowTitle("Graphics");
    setWindowIcon(QIcon(":/images/col3.bmp"));
}

void GfxWindow::setMainWindow(MainWindow *main) {
    main_window = main;
}
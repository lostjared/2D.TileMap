#include"export_window.hpp"
#include<QIcon>

// About Window constructor - (init)
ExportWindow::ExportWindow(QWidget *parent) : QDialog(parent) {
    setFixedSize(400, 120);
    setWindowTitle(tr("Export"));
    setWindowIcon(QIcon(":/images/bluebrick.bmp"));
}
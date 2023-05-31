#include"export_window.hpp"
#include<QIcon>
#include<QComboBox>
#include<QPushButton>

// About Window constructor - (init)
ExportWindow::ExportWindow(QWidget *parent) : QDialog(parent) {
    setFixedSize(400, 120);
    setWindowTitle(tr("Export"));
    setWindowIcon(QIcon(":/images/bluebrick.bmp"));
    export_type = new QComboBox(this);
    export_type->setGeometry(15, 15, 375, 25);
    export_type->addItem(tr("Export as Text"));

    export_file = new QPushButton("Export", this);
    export_file->setGeometry(400-125, 75, 100, 25);

}

void ExportWindow::exportFile() {

    
}
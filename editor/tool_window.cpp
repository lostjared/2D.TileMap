#include"tool_window.hpp"
#include<QLabel>

ToolWindow::ToolWindow(QWidget *parent) : QDialog(parent) {
    setFixedSize(150, 480);
    setWindowTitle(tr("Toolbox"));
    setWindowFlag(Qt::Tool);
    QLabel *lbl_tile = new QLabel(tr("Tiles: "), this);
    lbl_tile->setGeometry(20, 10, 75, 20);
    tiles = new QComboBox(this);
    tiles->setGeometry(10, 30, 120, 25);
    const char *fileNames[] = {  "black.bmp", "bluebrick.bmp", "bluesky.bmp", "brick.bmp", "eblock.bmp", "red_brick.bmp", "sand1.bmp", "sand2.bmp", "snow.bmp", "stone.bmp", "stone2.bmp", "stone3.bmp", "stone4.bmp", 0 };
    for(int i = 0; fileNames[i] != 0; ++i) {
        QString fn;
        QTextStream stream(&fn);
        stream << ":/images/" << fileNames[i];
        QPixmap pix(fn);
        tiles->addItem(fileNames[i]);
        tiles->setItemData(i,pix,Qt::DecorationRole);
    }
    tiles->setCurrentIndex(1);
    QLabel *lbl_tool = new QLabel(tr("Tool: "), this);
    lbl_tool->setGeometry(20, 65, 75, 20);
    tool = new QComboBox(this);
    tool->setGeometry(10, 90, 120, 25);
    tool->addItem("Pencil");
    tool->addItem("Eraser");
    tool->addItem("Fill");
    tool->setCurrentIndex(0);

    lbl_x = new QLabel(tr("Camera X: "), this);
    lbl_x->setGeometry(20, 230, 125, 20);

    camera_x = new QScrollBar(Qt::Orientation::Horizontal, this);
    camera_x->setGeometry(10, 250, 120, 25);
    camera_x->setMinimum(0);
    camera_x->setMaximum(1280);

    lbl_y = new QLabel(tr("Camera Y: "), this);
    lbl_y->setGeometry(20, 280, 125, 20);

    camera_y = new QScrollBar(Qt::Orientation::Horizontal, this);
    camera_y->setGeometry(10, 300, 120, 25);
    camera_y->setMinimum(0);
    camera_y->setMaximum(720);

}
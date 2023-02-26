#include"main_window.hpp"
#include<QPainter>
#include<QMenuBar>
#include<QAction>
#include<QDir>


MainWindow::MainWindow() {
    setGeometry(200, 10, 1280, 720);
    setFixedSize(1280, 720);
    setWindowTitle(tr("Editor"));

    loadImages();

    tool_window = new ToolWindow(this);
    tool_window->setGeometry(10, 10, 150, 480);
    tool_window->show(); 

    new_window = new NewWindow(this);
    new_window->hide();

    file_menu = menuBar()->addMenu(tr("&File"));
    file_new = new QAction(tr("New Map"), this);
    connect(file_new, SIGNAL(triggered()), this, SLOT(openNewMenu()));
    file_menu->addAction(file_new);

}

void MainWindow::paintEvent(QPaintEvent *p) {
    QPainter paint(this);
    paint.fillRect(QRect(0, 0, 1280, 720), QColor(255,255,255));
    for(int i = 0; i < MAP_WIDTH; ++i) {
        for(int z = 0; z < MAP_HEIGHT; ++z) {
            int x = i*16;
            int y = z*16;
            x += 1;
            y += 1;
            paint.fillRect(QRect(x, y, 15, 15), QColor(0, 0, 0));
            //paint.drawImage(i*16, z*16, images[2]);
        }
    }
}

void MainWindow::openNewMenu() {
    new_window->show();
}

void MainWindow::loadImages() {
    const char *fileNames[] = { "bg.bmp", "black.bmp", "bluebrick.bmp", "bluesky.bmp", "brick.bmp", "eblock.bmp", "red_brick.bmp", "sand1.bmp", "sand2.bmp", "snow.bmp", "stone.bmp", "stone2.bmp", "stone3.bmp", "stone4.bmp", 0 };
    for(int i = 0; fileNames[i] != 0; ++i) {
        QString fn;
        QTextStream stream(&fn);
        stream << QDir::currentPath() << "/" << "images/" << fileNames[i];
        images.append(QImage(fn));
    }
}
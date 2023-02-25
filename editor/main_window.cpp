#include"main_window.hpp"
#include<QPainter>

MainWindow::MainWindow() {
    setFixedSize(1280, 720);
    setWindowTitle("Editor");
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
        }
    }
}

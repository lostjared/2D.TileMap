#include"main_window.hpp"
#include<QPainter>
#include<QMenuBar>
#include<QAction>

MainWindow::MainWindow() {
    setGeometry(200, 10, 1280, 720);
    setFixedSize(1280, 720);
    setWindowTitle(tr("Editor"));

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
        }
    }
}

void MainWindow::openNewMenu() {
    new_window->show();
}
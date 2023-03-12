#include"debug_window.hpp"

DebugWindow::DebugWindow(QWidget *parent) : QDialog(parent) {
    setFixedSize(1280, 320);
    setWindowFlag(Qt::Tool);
    text_view = new QTextEdit(this);
    text_view->setGeometry(10, 10, 1280-20, 320-20);
    text_view->setReadOnly(true);
    text_view->setStyleSheet("font-size: 18px;");
    setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
}

void DebugWindow::Log(const QString &text) {
   QString current;
   current = text_view->toPlainText();
   current += text;
   text_view->setPlainText(current);
   QTextCursor tmpCursor = text_view->textCursor();
   tmpCursor.movePosition(QTextCursor::End, QTextCursor::MoveAnchor);
   text_view->setTextCursor(tmpCursor);
}
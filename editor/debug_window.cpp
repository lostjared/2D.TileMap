#include"debug_window.hpp"

DebugWindow::DebugWindow(QWidget *parent) : QDialog(parent) {
    setFixedSize(1280, 320);
    setWindowFlag(Qt::Tool);
    setWindowTitle(tr("Debug Console"));
    text_view = new QTextEdit(this);
    text_view->setGeometry(10, 10, 1280-20, 320-20);
    text_view->setReadOnly(true);
    text_view->setStyleSheet("background-color: rgb(0, 0, 0); color: rgb(255, 255, 255); font-size: 20px;");
}

void DebugWindow::clear() {
    text_view->setHtml("");
}

void DebugWindow::Log(const QString &text) {
   QString current;
   current = text_view->toPlainText();
   current += text;
   current.replace("editor: ", "<span style=\"color: red;\">editor: </span>");
   current.replace("game: ", "<span style=\"color: purple;\">game: </span>");
   current.replace("\n", "<br>");
   text_view->setHtml(current);
   QTextCursor tmpCursor = text_view->textCursor();
   tmpCursor.movePosition(QTextCursor::End, QTextCursor::MoveAnchor);
   text_view->setTextCursor(tmpCursor);
}
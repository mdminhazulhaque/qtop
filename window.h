#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include <QProcess>
#include <QDebug>

namespace Ui {
class Window;
}

class Window : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit Window(QWidget *parent = 0);
    ~Window();

private slots:
    void readStandardOutput();
    
private:
    Ui::Window *ui;
    QProcess *process;
};

#endif // WINDOW_H

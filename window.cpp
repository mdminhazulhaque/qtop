#include "window.h"
#include "ui_window.h"

Window::Window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Window)
{
    ui->setupUi(this);
    process = new QProcess;

    connect(process, SIGNAL(readyReadStandardOutput()), this, SLOT(readStandardOutput()));
    connect(ui->pushButton, SIGNAL(clicked()), qApp, SLOT(quit()));

    QStringList cmd;
    cmd << "-c";
    cmd << "top -b";

    QStringList env;
    env << "TERM=xterm";
    env << "PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin";
    process->setEnvironment(env);

    // stdin to top is not required
    //process->setProcessChannelMode(QProcess::MergedChannels);
    process->start("/bin/sh", cmd);

    setWindowTitle("Qtop");
    showMaximized();
}

Window::~Window()
{
    delete ui;
    process->kill();
}

void Window::readStandardOutput()
{
    // Clear old junks
    ui->textBrowser->clear();

    // Show me what you got
    ui->textBrowser->setText(process->readAllStandardOutput());
}

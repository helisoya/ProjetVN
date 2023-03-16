#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "novelcontroler.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    controler = new NovelControler(this);
    controler->LoadChapterFile("test");
}

MainWindow::~MainWindow()
{
    delete ui;
}


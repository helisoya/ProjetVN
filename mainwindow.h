#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "novelcontroler.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Ui::MainWindow *ui;

    void displayGameUI();
    void showMainMenu();
    void handleNewGame();

    void setChoices(QString choices[]);

private:
    NovelControler *controler;
};
#endif // MAINWINDOW_H

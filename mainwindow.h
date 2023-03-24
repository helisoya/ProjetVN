#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "novelcontroler.h"
#include "QLabel"

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
    void handleNext();
    void handleChoice(int value);


    void hideChoices();
    void setCharacterText(std::string script);
    void setCharacterName(std::string name);
    void setPngCharacterLeft(QWidget *scene,QString filename);
    void setPngCharacterRight(QWidget *scene,QString filename);
    void setBackground(QWidget *scene,QString filename);
    void generatePixmap(QLabel* label, QString filename);

    void setChoices(std::vector<std::string> choices);

private:
    NovelControler *controler;
};
#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "novelcontroler.h"
#include "QLabel"
#include "QAudioOutput"
#include "QMediaPlayer"

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
    void handleSave();
    void handleLoad();
    void handleChoice(int value);
    void handleOptions();
    void handleApplyOptions();
    void handleExit();
    void handleChangeSound();

    std::string random_string(int length);

    void hideChoices();
    void setCharacterText(std::string script);
    void setCharacterName(std::string name);
    void setPngCharacterLeft(std::string filename);
    void setPngCharacterRight(std::string filename);
    void setBackground(std::string filename);
    void generatePixmap(QLabel* label, QString filename);

    void setChoices(std::vector<std::string> choices);

    void playAudio(std::string source);

private:
    NovelControler *controler;
    QMediaPlayer *player;
    QAudioOutput *audioOutput;
};
#endif // MAINWINDOW_H

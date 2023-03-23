#include <QMediaPlayer>
#include <QAudioOutput>
#include <QPushButton>

#include "mainwindow.h"
#include "novelcontroler.h"
#include "./ui_mainwindow.h"

//showMainMenu(*ui);
void  MainWindow::showMainMenu(){
    ui->container->setViewport(ui->titleScreen);
}

//playAudio("qrc:/assets/audio/maxwell_theme.mp3");
void playAudio(QString source){
    QMediaPlayer *player = new QMediaPlayer;
    QAudioOutput *audioOutput = new QAudioOutput;
    player->setAudioOutput(audioOutput);
    player->setSource(source);
    audioOutput->setVolume(50);
    player->play();
}


void MainWindow::handleNewGame(){
    displayGameUI();
    controler->LoadChapterFile("A_1");
}

void MainWindow::handleNext(){
    controler->Next();
}

void MainWindow::handleChoice(int value){
    ui->continueBtn->show();
    controler->MakeChoice(value);
}

//generatePixmap(background, "filename"); PngCharac, PngCharac2 pour les images des persos
void MainWindow::generatePixmap(QLabel* label, QString filename){
    QPixmap pix;
    if(pix.load(filename)){
        /** scale pixmap to fit in label'size and keep ratio of pixmap | pas sûr de laisser ça*/
        pix = pix.scaled(label->size(),Qt::KeepAspectRatio);
        label->setPixmap(pix);
    }
}

void MainWindow::setBackground(QWidget *scene,QString filename){
    QLabel* background = scene->findChild<QLabel*>("background");
    generatePixmap(background, filename);
}

void MainWindow::setPngCharacterRight(QWidget *scene,QString filename){
    QLabel* pngCharac = scene->findChild<QLabel*>("pngCharac");
    generatePixmap(pngCharac, filename);
}

void MainWindow::setPngCharacterLeft(QWidget *scene,QString filename){
    QLabel* pngCharac2 = scene->findChild<QLabel*>("pngCharac2");
    generatePixmap(pngCharac2, filename);
}

void MainWindow::setCharacterName(std::string name){

    if(name.empty()){
        ui->CharacterName->hide();
    }else{
        ui->CharacterName->show();
    }
    ui->CharacterName->setText(QString(name.data()));
}

void MainWindow::setCharacterText(std::string script){
    ui->CharacterText->setText(QString(script.data()));
}


void MainWindow::displayGameUI(){

    ui->container->setViewport(ui->dialogScreen);
}

void MainWindow::setChoices(std::vector<std::string> choices){
    QLayoutItem *wItem;
    while ((wItem = ui->ChoiceBox->layout()->takeAt(0)) != 0)
        delete wItem;

    ui->continueBtn->hide();

    for(int i = 0; i < choices.size(); i++){
        std::cout << "Bouton " << i << std::endl;
        QPushButton button = QPushButton(QString(choices[i].data()));
        connect(&button, &QPushButton::released, this, [=](){handleChoice(i);});
        ui->ChoiceBox->layout()->addWidget(&button);
        button.show();
    }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(1000,600);
    controler = new NovelControler(this);


    connect(ui->newGameButton, &QPushButton::released, this, &MainWindow::handleNewGame);
    connect(ui->continueBtn, &QPushButton::released, this, &MainWindow::handleNext);
    showMainMenu();
}

MainWindow::~MainWindow()
{
    delete ui;
}

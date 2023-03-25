#include <QMediaPlayer>
#include <QAudioOutput>
#include <QPushButton>

#include "mainwindow.h"
#include "novelcontroler.h"
#include "ui_mainwindow.h"

//showMainMenu(*ui);
void  MainWindow::showMainMenu(){
    playAudio("qrc:/assets/audio/mainMenu.mp3");
    ui->container->setViewport(ui->titleScreen);

    if(controler->SaveFileExists()){
        ui->continueButton->show();
    }else{
        ui->continueButton->hide();
    }
}



//playAudio("qrc:/assets/audio/maxwell_theme.mp3");
void MainWindow::playAudio(std::string source){
    player->setAudioOutput(audioOutput);
    player->setSource(QString(source.data()));

    audioOutput->setVolume(30);
    player->setLoops(QMediaPlayer::Infinite);
    player->play();
}


void MainWindow::handleNewGame(){
    displayGameUI();
    playAudio("");
    controler->LoadChapterFile("A_1");
}

void MainWindow::handleNext(){
    controler->Next();
}

void MainWindow::handleSave(){
    controler->Save();
}

void MainWindow::handleLoad(){
    displayGameUI();
    playAudio("");
    controler->Load();
}

void MainWindow::handleChoice(int value){
    ui->continueBtn->show();
    ui->saveButton->show();
    ui->loadButton->show();
    hideChoices();
    controler->MakeChoice(value);
}

//generatePixmap(background, "filename"); PngCharac, PngCharac2 pour les images des persos
void MainWindow::generatePixmap(QLabel* label, QString filename){
    QPixmap pix;
    if(pix.load(filename)){
        /** scale pixmap to fit in label'size and keep ratio of pixmap | pas sûr de laisser ça*/
        pix = pix.scaled(label->size(),Qt::KeepAspectRatio);
        label->setPixmap(pix);
    }else{
        label->setPixmap(QPixmap());
    }
}

void MainWindow::setBackground(std::string filename){
    generatePixmap(ui->background, QString(filename.data()));
}

void MainWindow::setPngCharacterRight(std::string filename){
    generatePixmap(ui->PngCharac2, QString(filename.data()));
}

void MainWindow::setPngCharacterLeft(std::string filename){
    generatePixmap(ui->PngCharac, QString(filename.data()));
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

void MainWindow::hideChoices(){
    QLayoutItem *wItem;
    while ((wItem = ui->ChoiceBox->layout()->takeAt(0)) != 0)
        wItem->widget()->hide();
        delete wItem;
}

void MainWindow::setChoices(std::vector<std::string> choices){
    hideChoices();

    ui->continueBtn->hide();
    ui->saveButton->hide();
    ui->loadButton->hide();

    for(int i = 0; i < choices.size(); i++){
        std::cout << "Bouton " << i << std::endl;
        QPushButton* button = new QPushButton(QString(choices[i].data()));
        connect(button, &QPushButton::released, this, [=](){handleChoice(i);});
        ui->ChoiceBox->addWidget(button);
        button->show();
    }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    player = new QMediaPlayer;
    audioOutput = new QAudioOutput;
    ui->setupUi(this);
    this->setFixedSize(1000,600);
    controler = new NovelControler(this);

    connect(ui->newGameButton, &QPushButton::released, this, &MainWindow::handleNewGame);
    connect(ui->continueBtn, &QPushButton::released, this, &MainWindow::handleNext);

    connect(ui->continueButton, &QPushButton::released, this, &MainWindow::handleLoad);
    connect(ui->loadButton, &QPushButton::released, this, &MainWindow::handleLoad);
    connect(ui->saveButton, &QPushButton::released, this, &MainWindow::handleSave);
    showMainMenu();
}

MainWindow::~MainWindow()
{
    delete ui;
}

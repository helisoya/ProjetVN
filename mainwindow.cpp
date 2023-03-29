#include <QMediaPlayer>
#include <QAudioOutput>
#include <QPushButton>

#include "mainwindow.h"
#include "novelcontroler.h"
#include "ui_mainwindow.h"

//showMainMenu(*ui);
void  MainWindow::showMainMenu(){
    ui->VolumeSlider->setValue(70);
    ui->VolumeRate->setText(QString("70%"));
    playAudio("qrc:/assets/audio/mainMenu.mp3");

    ui->Options->hide();
    ui->dialogScreen->hide();
    ui->titleScreen->show();

    if(controler->SaveFileExists()){
        ui->continueButton->show();
    }else{
        ui->continueButton->hide();
    }
}


//playAudio("qrc:/assets/audio/maxwell_theme.mp3");
void MainWindow::playAudio(std::string source){
    if(!ui->dlcAudio->isChecked()) return;
    player->setAudioOutput(audioOutput);
    player->setSource(QString(source.data()));

    audioOutput->setVolume(((double)(ui->VolumeSlider->value()) /(double)100));
    player->setLoops(QMediaPlayer::Infinite);
    player->play();
}


void MainWindow::handleNewGame(){
    if(!ui->dlcJeu->isChecked()) exit(0);
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
    if(!ui->dlcJeu->isChecked()) exit(0);
    displayGameUI();
    playAudio("");
    controler->Load();
}

void MainWindow::handleOptions(){
    ui->Options->show();
    ui->titleScreen->hide();
}

void MainWindow::handleApplyOptions(){
    ui->Options->hide();
    ui->titleScreen->show();
}

void MainWindow::handleExit(){
    exit(0);
}

void MainWindow::handleChangeSound(){
    audioOutput->setVolume(((double)(ui->VolumeSlider->value()) /(double)100));
    ui->VolumeRate->setText(QString((std::to_string(ui->VolumeSlider->value())+"%").data()));
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
    if(ui->dlcBackground->isChecked()){
        generatePixmap(ui->background,QString(filename.data()));
    }else{
        generatePixmap(ui->background,QString(":/assets/Backgrounds/noDLC.png"));
    }

}

void MainWindow::setPngCharacterRight(std::string filename){
    if(ui->dlcPerso->isChecked()){
        generatePixmap(ui->PngCharac2, QString(filename.data()));
    }else{
        generatePixmap(ui->PngCharac2,QString(":/assets/Characters/noDLC.png"));
    }
}

void MainWindow::setPngCharacterLeft(std::string filename){
    if(ui->dlcPerso->isChecked()){
        generatePixmap(ui->PngCharac, QString(filename.data()));
    }else{
        generatePixmap(ui->PngCharac,QString(":/assets/Characters/noDLC.png"));
    }
}

void MainWindow::setCharacterName(std::string name){

    if(name.empty()){
        ui->CharacterName->hide();
    }else{
        ui->CharacterName->show();
    }

    if(!ui->dlcTexte->isChecked()){
        ui->CharacterName->setText(QString(random_string(5).data()));
    }else{
       ui->CharacterName->setText(QString(name.data()));
    }


}

void MainWindow::setCharacterText(std::string script){
    if(!ui->dlcTexte->isChecked()){
        ui->CharacterText->setText(QString(random_string(30).data()));
    }else{
       ui->CharacterText->setText(QString(script.data()));
    }

}


std::string MainWindow::random_string( int length )
{
    auto randchar = []() -> char
    {
        const char charset[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
        const size_t max_index = (sizeof(charset) - 1);
        return charset[ rand() % max_index ];
    };
    std::string str(length,0);
    std::generate_n( str.begin(), length, randchar );
    return str;
}

void MainWindow::displayGameUI(){
    ui->dialogScreen->show();
    ui->titleScreen->hide();
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

        QString label = QString(choices[i].data());
        if(!ui->dlcTexte->isChecked()){
            label = QString(random_string(5).data());
        }

        QPushButton* button = new QPushButton(label);
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

    connect(ui->optionsButton, &QPushButton::released, this, &MainWindow::handleOptions);
    connect(ui->ApplyBtn, &QPushButton::released, this, &MainWindow::handleApplyOptions);
    connect(ui->VolumeSlider, &QSlider::valueChanged, this, &MainWindow::handleChangeSound);

    connect(ui->quitButton, &QPushButton::released, this, &MainWindow::handleExit);
    showMainMenu();
}

MainWindow::~MainWindow()
{
    delete controler;
    delete ui;
}

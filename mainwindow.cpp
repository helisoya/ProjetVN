#include "mainwindow.h"

#include "novelcontroler.h"
#include "./ui_mainwindow.h"
#include "menu.h"

//showMainMenu(*ui);
void showMainMenu(Ui::MainWindow ui){
    ui.container->setViewport(ui.titleScreen);
}

//generatePixmap(background, "filename"); PngCharac, PngCharac2 pour les images des persos
void generatePixmap(QLabel* label, QString filename){
    QPixmap pix;
    if(pix.load(filename)){
        /** scale pixmap to fit in label'size and keep ratio of pixmap | pas sûr de laisser ça*/
        pix = pix.scaled(label->size(),Qt::KeepAspectRatio);
        label->setPixmap(pix);
    }
}

void setBackground(QWidget *scene,QString filename){
    QLabel* background = scene->findChild<QLabel*>("background");
    generatePixmap(background, filename);
}

void setPngCharacterRight(QWidget *scene,QString filename){
    QLabel* pngCharac = scene->findChild<QLabel*>("pngCharac");
    generatePixmap(pngCharac, filename);
}

void setPngCharacterLeft(QWidget *scene,QString filename){
    QLabel* pngCharac2 = scene->findChild<QLabel*>("pngCharac2");
    generatePixmap(pngCharac2, filename);
}

void setCharacterName(QWidget *scene,QString filename){
    QLabel* characterName = scene->findChild<QLabel*>("CharacterName");
    generatePixmap(characterName, filename);
}

void setCharacterText(QWidget *scene,QString filename){
    QLabel* characterText = scene->findChild<QLabel*>("CharacterText");
    generatePixmap(characterText, filename);
}

//displayDialog(*ui, "Test Name", "mon script");
void displayDialog(Ui::MainWindow ui, QString name, QString script, QString backgroundImg, QString pngCharac, QString pngCharac2){
    setCharacterName(ui.dialogScreen, name);
    setCharacterText(ui.dialogScreen, script);
    setBackground(ui.dialogScreen, backgroundImg);
    setPngCharacterLeft(ui.dialogScreen, pngCharac);
    setPngCharacterRight(ui.dialogScreen, pngCharac2);

    ui.container->setViewport(ui.dialogScreen);
}

//displayDialog(*ui, "Test Name", "mon script", ["Nice !","Oui !","Non !"], bgImgName, pngCharac, pngCharac2);
void displayChoiceDialogue(Ui::MainWindow ui, QString name, QString script, QString choices[], QString backgroundImg, QString pngCharac, QString pngCharac2){
    setCharacterName(ui.choiceDialogScreen, name);
    setCharacterText(ui.choiceDialogScreen, script);
    setBackground(ui.choiceDialogScreen, backgroundImg);
    setPngCharacterLeft(ui.choiceDialogScreen, pngCharac);
    setPngCharacterRight(ui.choiceDialogScreen, pngCharac2);

    for(int i = 0; i < choices->length(); i++){
        ui.ChoiceBox->layout()->addWidget(new QPushButton(choices[i], ui.choiceDialogScreen));
    }

    ui.container->setViewport(ui.choiceDialogScreen);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    controler = new NovelControler(this);
    controler->LoadChapterFile("test");
    QString choices[3];
    choices[0] = "Baptiste";
    choices[1] = "Oui !";
    choices[2] = "Non !";
    //displayChoiceDialogue(*ui, "Test Name", "mon script", choices);
    //displayDialog(*ui, "Mr Fouzi", "je suis Fouzi");
    //showMainMenu(*ui);
}

MainWindow::~MainWindow()
{
    delete ui;
}

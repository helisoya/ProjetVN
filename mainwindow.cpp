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
        /** scale pixmap to fit in label'size and keep ratio of pixmap */
        pix = pix.scaled(label->size(),Qt::KeepAspectRatio);
        label->setPixmap(pix);
    }
}

//displayDialog(*ui, "Test Name", "mon script");
void displayDialog(Ui::MainWindow ui, QString name, QString script, QString backgroundImg, QString pngCharac, QString pngCharac2){
    QLabel* characterNameLabel = ui.dialogScreen->findChild<QLabel*>("CharacterName");
    if (characterNameLabel) {
        characterNameLabel->setText(name);
    }
    QLabel* CharacterTextLabel = ui.dialogScreen->findChild<QLabel*>("CharacterText");
    if (CharacterTextLabel) {
        CharacterTextLabel->setText(script);
    }
    QLabel* background = ui.dialogScreen->findChild<QLabel*>("background");
    QLabel* pngPerso = ui.dialogScreen->findChild<QLabel*>("pngCharac");
    QLabel* pngPerso2 = ui.dialogScreen->findChild<QLabel*>("pngCharac2");

    generatePixmap(background, backgroundImg);
    generatePixmap(pngPerso, pngCharac);
    generatePixmap(pngPerso2, pngCharac2);

    ui.container->setViewport(ui.dialogScreen);
}

//displayDialog(*ui, "Test Name", "mon script", ["Nice !","Oui !","Non !"], bgImgName, pngCharac, pngCharac2);
void displayChoiceDialogue(Ui::MainWindow ui, QString name, QString script, QString choices[], QString backgroundImg, QString pngCharac, QString pngCharac2){
    QLabel* characterNameLabel = ui.choiceDialogScreen->findChild<QLabel*>("CharacterName");
    if (characterNameLabel) {
        characterNameLabel->setText(name);
    }
    QLabel* CharacterTextLabel = ui.choiceDialogScreen->findChild<QLabel*>("CharacterText");
    if (CharacterTextLabel) {
        CharacterTextLabel->setText(script);
    }
    for(int i = 0; i < choices->length(); i++){
        ui.ChoiceBox->layout()->addWidget(new QPushButton(choices[i], ui.choiceDialogScreen));
    }

    QLabel* background = ui.choiceDialogScreen->findChild<QLabel*>("background");
    QLabel* pngPerso = ui.choiceDialogScreen->findChild<QLabel*>("pngCharac");
    QLabel* pngPerso2 = ui.choiceDialogScreen->findChild<QLabel*>("pngCharac2");

    generatePixmap(background, backgroundImg);
    generatePixmap(pngPerso, pngCharac);
    generatePixmap(pngPerso2, pngCharac2);

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

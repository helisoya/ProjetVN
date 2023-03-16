#include "novelcontroler.h"
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "iostream"
#include "vector"
#include "QFile"
#include "QIODevice"


NovelControler::NovelControler(MainWindow *window)
{
    this->window = window;
}


void NovelControler::LoadChapterFile(std::string name){
        currentIndex = -1;
        currentFileData.clear();

        QString filePath;
        filePath.append("assets/chapters/");
        filePath.append(name.data());
        filePath.append(".txt");

        QFile file(filePath);
        QTextStream in(&file);

        while(!in.atEnd()) {
            QString line = in.readLine();
            currentFileData.push_back(line.toStdString());
        }
        file.close();
        Next();
}

void NovelControler::MakeChoice(int indexChoice){
    LoadChapterFile(currentChoice.at(indexChoice));
}

void NovelControler::Load(){

}

void NovelControler::Save(){

}

void NovelControler::GoToMainMenu(){

}

bool NovelControler::StrStartsWith(std::string line,std::string startWith){
    if(line.size() < startWith.size()) return false;

    for(int i = 0; i < startWith.size();i++){
        if(line.at(i) != startWith.at(i)) return false;
    }

    return true;
}

std::vector<std::string> NovelControler::Split(std::string line, char delimiter){
    std::vector<std::string> res;

    std::string currentStr = "";
    for(int i = 0; i < line.size();i++){
        if(line.at(i) == delimiter){
            if(currentStr != ""){
                res.push_back(currentStr);
                currentStr = "";
            }
        }else{
            currentStr += line.at(i);
        }
    }
    return res;
}

void NovelControler::Next(){
    currentIndex++;
    if(currentIndex < currentFileData.size()){
        // Read currentData
        std::string currentLine = currentFileData.at(currentIndex);

        if(currentLine.size() == 0){
            Next();
            return;
        }

        if(StrStartsWith(currentLine,"CHOICE")){
            currentChoice.clear();
            for(int i = 1;i <= 4 && currentIndex+i < currentFileData.size();i++){
                std::vector<std::string> splited = Split(currentFileData.at(currentIndex+i),'|');
                if(splited.size() != 2){
                    std::cout << "Erreur Choix Ligne : " << currentFileData.at(currentIndex+i) << std::endl;
                    return;
                }

                currentChoice.push_back(splited[1]);
                // Do something with splited[0] (Button text)

            }

        }else{
            std::vector<std::string> splited = Split(currentLine,'(');
            if(splited.size() == 0){
                std::cout << "Erreur Split Ligne : " << currentLine << std::endl;
                return;
            }
            std::string actionName = splited.at(0);
            std::string params = "";
            if(splited.size() > 1){
                params = Split(splited.at(1),')')[0];
            }


            bool ok = true;

            if(actionName == "CHARACTER_IMG"){
                // Change Character Image
            }else if(actionName == "BACKGROUND_IMG"){
                // Change Background Image
            }else if(actionName == "CHARACTER_NAME"){
                // Change Character Name
            }else if(actionName == "DIALOG"){
                // Change Character Dialog
                ok = false;
            }

            if(ok){
                Next();
            }

        }


    }
}

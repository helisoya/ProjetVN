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

        QFile file("chapters/test.txt");
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

bool NovelControler::StrStartsWith(std::string line,std::string startWith){
    if(line.size() < startWith.size()) return false;

    for(int i = 0; i < startWith.size();i++){
        if(line.at(i) != startWith.at(i)) return false;
    }

    return true;
}

void NovelControler::Next(){
    currentIndex++;
    if(currentIndex < currentFileData.size()){
        // Read currentData
        std::string currentLine = currentFileData.at(currentIndex);

        if(StrStartsWithChoice(currentLine,"Choice")){
            // It is a choice
        }else{
            // It is not a choice
        }

        bool ok = true;

        if(ok){
            Next();
        }
    }
}

#include "novelcontroler.h"
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "iostream"
#include "vector"
#include "QFile"
#include "QIODevice"
#include "QStandardPaths"
#include "QDir"

NovelControler::NovelControler(MainWindow *window)
{
    this->window = window;
    dataPath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    dataPath.append("/BaptisteQuestGOTY");

    saveFilePath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    saveFilePath.append("/BaptisteQuestGOTY/save.sav");

    if(!QDir(dataPath).exists()){
        QDir(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)).mkdir("BaptisteQuestGOTY");
    }

    std::cout << "Save Path : " << saveFilePath.toStdString() << std::endl;
    //Save();
    //Load();
}


void NovelControler::LoadChapterFile(std::string name,bool autoNext){
        currentIndex = -1;
        currentFileData.clear();


        QString filePath;
        filePath.append(":/assets/chapters/");
        filePath.append(name.data());
        filePath.append(".txt");

        QFile file(filePath);

        file.open(QFile::ReadOnly);
        QTextStream in(&file);

        std::cout << "Filepath : " <<  filePath.toStdString() << std::endl;
        std::cout << "Found file : " <<  file.exists() << std::endl;

        while(!in.atEnd()) {
            QString line = in.readLine();
            currentFileData.push_back(line.toStdString());
        }
        file.close();

        if(autoNext){
            Next();
        }
}

void NovelControler::MakeChoice(int indexChoice){
    LoadChapterFile(currentChoice.at(indexChoice));
}

bool NovelControler::SaveFileExists(){
    QFile file(saveFilePath);
    return file.exists();
}


void NovelControler::Load(){
    if(!SaveFileExists()) return;

    QFile file(saveFilePath);
    file.open(QFile::ReadOnly);

    QTextStream in(&file);

    while(!in.atEnd()) {
        std::vector<std::string> line = Split(in.readLine().toStdString(),'|');
        std::cout << "LOAD LINE : " << line[0] << " " << line[1] << std::endl;
        if(line[0] == "BACKGROUND_IMG"){

        }else if(line[0] == "CHARACTER_IMG"){

        }else if(line[0] == "CHARACTER_NAME"){

        }else if(line[0] == "DIALOG"){

        }else if(line[0] == "CHAPTERFILE"){
            LoadChapterFile(line[1]);
        }else if(line[0] == "INDEX"){
            currentIndex = stoi(line[1]);
        }
    }
    file.close();
}


void NovelControler::Save(){
    QFile file(saveFilePath);

    file.open(QFile::WriteOnly);
    file.resize(0);

    file.write("BACKGROUND_IMG|NONE\n");
    file.write("CHARACTER_IMG|NONE\n");
    file.write("CHARACTER_NAME|NONE\n");
    file.write("DIALOG|NONE\n");
    file.write("CHAPTERFILE|test\n");
    file.write("INDEX|0");

    file.flush();
    file.close();
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
    if(currentStr != ""){
        res.push_back(currentStr);
    }
    return res;
}

void NovelControler::Next(){
    currentIndex++;
    if(currentIndex < currentFileData.size()){
        // Read currentData
        std::string currentLine = currentFileData.at(currentIndex);

        std::cout << "Ligne : " << currentLine << std::endl;
        if(currentLine.size() == 0){
            Next();
            return;
        }

        if(StrStartsWith(currentLine,"CHOICE")){
            std::cout << "C'est un choix" << std::endl;
            currentChoice.clear();
            for(int i = 1;i <= 4 && currentIndex+i < currentFileData.size();i++){
                std::vector<std::string> splited = Split(currentFileData.at(currentIndex+i),'|');
                if(splited.size() != 2){
                    std::cout << "Erreur Choix Ligne : " << currentFileData.at(currentIndex+i) << std::endl;
                    return;
                }

                currentChoice.push_back(splited[1]);
                // Do something with splited[0] (Button text)

                std::cout << splited[0] << " " << splited[1] << std::endl;
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
                std::cout << "Change Character Image to "  << params << std::endl;
                // Change Character Image
            }else if(actionName == "BACKGROUND_IMG"){
                std::cout << "Change Background Image to "  << params << std::endl;
                // Change Background Image
            }else if(actionName == "CHARACTER_NAME"){
                std::cout << "Change Character Name to "  << params << std::endl;
                // Change Character Name
            }else if(actionName == "DIALOG"){
                std::cout << "Change Dialog to "  << params << std::endl;
                // Change Character Dialog
                ok = false;
            }

            if(ok){
                Next();
            }

        }


    }
}

#ifndef NOVELCONTROLER_H
#define NOVELCONTROLER_H

#include "iostream"
#include "vector"


class MainWindow;

class NovelControler
{
public:
    NovelControler(MainWindow *window);
    void LoadChapterFile(std::string name);
    void Next();
    void Save();
    void Load();
    void MakeChoice(int indexChoice);
    void GoToMainMenu();

private:
    MainWindow *window;
    int currentIndex;
    std::vector<std::string> currentFileData;
    std::vector<std::string> currentChoice;

    bool StrStartsWith(std::string line,std::string startWith);
    std::vector<std::string> Split(std::string line, char delimiter);
};

#endif // NOVELCONTROLER_H

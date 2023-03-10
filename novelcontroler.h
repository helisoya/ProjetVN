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

private:
    MainWindow *window;
    int currentIndex;
    std::vector<std::string> currentFileData;
    std::vector<std::string> currentChoice;

    bool StrStartsWithChoice(std::string line,std::string startWith);
};

#endif // NOVELCONTROLER_H

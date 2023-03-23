#ifndef MENU_H
#define MENU_H

#endif // MENU_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Menu; }
QT_END_NAMESPACE

class Menu : public QWidget
{
    Q_OBJECT

public:
    Menu(QWidget *parent = nullptr);
    Ui::Menu *qwidget;
};


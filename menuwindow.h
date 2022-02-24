/*
 *  This header file creates the UI for the class MenuWindow, where the player
 *  can choose to start a new game with the options to choose their own parameters
 *  or to load the game from a saved .txt file. There is also an exit button if
 *  they don't want to play the game. :(
*/

#ifndef MENUWINDOW_H
#define MENUWINDOW_H

#include "Tower.h"

#include <QMainWindow>
#include <QMediaPlayer>
#include <QMediaPlaylist>

QT_BEGIN_NAMESPACE
namespace Ui { class MenuWindow; }
QT_END_NAMESPACE

class MenuWindow : public QMainWindow
{
    Q_OBJECT

public:
    MenuWindow(QWidget *parent = nullptr);
    ~MenuWindow();

private slots:
    void on_Exit_clicked();

    void on_NewGame_clicked();

    void on_LoadGame_clicked();

    void on_left_diff_clicked();

    void on_right_diff_clicked();

    void on_left_floors_clicked();

    void on_right_floors_clicked();

    void on_StartGame_clicked();

private:
    Ui::MenuWindow *ui;
    QMediaPlaylist *playlist;
    QMediaPlayer *player;
    QMediaPlayer *click;
    Tower::Difficulty difficulty = Tower::Difficulty::NORMAL;
    int floors = 5;
    int current = 0;
    int level = 1;

    void start_game(Tower *tower);
};
#endif // MENUWINDOW_H

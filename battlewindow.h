/*
 *  This header file creates the UI for the class BattleWindow, where the elements
 *  such as the player and enemy stats, buttons for the player's actions, and the
 *  the action list are displayed.
*/

#ifndef BATTLEWINDOW_H
#define BATTLEWINDOW_H

#include "Tower.h"
#include "ui_battlewindow.h"

#include <QMainWindow>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QFile>
#include <QTextStream>
#include <cstdio>
#include <iostream>
using namespace std;

namespace Ui {
class BattleWindow;
}

class BattleWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit BattleWindow(Tower *tower, QWidget *parent);
    ~BattleWindow();

private slots:
    void on_AddAction_clicked();

    void on_Skill_clicked();

    void on_Items_clicked();

    void on_use_clicked();

    void on_actionlist_currentRowChanged(int currentRow);

    void on_Enemy0_clicked();

    void on_Enemy1_clicked();

    void on_Enemy2_clicked();

    void on_Enemy3_clicked();

    void on_Player_pic_clicked();

    void on_back_clicked();

    void on_DeleteAction_clicked();

    void on_delete_list_currentRowChanged(int currentRow);

    void on_delete_action_clicked();

    void on_back_delete_clicked();

    void on_SwapAction_clicked();

    void on_swap1_list_currentRowChanged(int currentRow);

    void on_swap2_list_currentRowChanged(int currentRow);

    void on_swap_clicked();

    void on_back_swap_clicked();

    void on_EndRound_clicked();

    void on_BattleDialog_next_clicked();

    void on_Flee_clicked();

private:
    Ui::BattleWindow *ui;
    QMediaPlaylist *playlist;
    QMediaPlayer *player;
    QMediaPlayer *click;

    Tower *tower;
    int action_type = -1; // 0 = skill, 1 =item
    int row_select = -1;
    int choose = 0; // 0 = off, 1 = on
    int swap1_select = -1;
    int swap2_select = -1;
    int end = 0; // 0 = not ended, 1 = end

    void refresh();
    void choose_character(int enemy);
};

#endif // BATTLEWINDOW_H

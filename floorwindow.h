/*
 *  This header file creates the UI for the class FloorWindow, where the elements
 *  such as the the options for the player to start battle, move to the next floor,
 *  check stats, use equipment or items, save game, and quit is displayed.
*/

#ifndef FLOORWINDOW_H
#define FLOORWINDOW_H

#include "Tower.h"
#include "Floor.h"
#include "ui_floorwindow.h"

#include <QMainWindow>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QFileDialog>

namespace Ui {
class FloorWindow;
}

class FloorWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit FloorWindow(Tower *tower, QWidget *parent);
    ~FloorWindow();

private slots:
    void on_Quit_clicked();

    void on_Save_clicked();

    void on_Item_clicked();

    void on_item_list_currentRowChanged(int currentRow);

    void on_back_item_clicked();

    void on_use_item_clicked();

    void on_Equipment_clicked();

    void on_Status_clicked();

    void on_back_status_clicked();

    void on_StartBattle_clicked();

    void on_Next_floor_clicked();

    void on_FloorDialog_next_clicked();

private:
    Ui::FloorWindow *ui;
    Tower *tower;
    int list_mode = -1; // 0 for equipment, 1 for items
    int item_selected = -1;
    int equipment_selected = -1;
    int shop = 0; // 0 no shop :(
    QMediaPlaylist *playlist;
    QMediaPlayer *player;
    QMediaPlayer *click;
    QMediaPlayer *victory;
};

#endif // FLOORWINDOW_H

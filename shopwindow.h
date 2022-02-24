/*
 *  This header file creates the UI for the class ShopWindow, where the player
 *  has the options to buy items from the shop or sell their items to the shop.
 *  The ShopWindow also contains functions to refresh the stats (such as funds).
*/

#ifndef SHOPWINDOW_H
#define SHOPWINDOW_H

#include "Tower.h"

#include <QMainWindow>
#include <QMediaPlayer>
#include <QMediaPlaylist>


namespace Ui {
class ShopWindow;
}

class ShopWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ShopWindow(Tower *tower, QWidget *parent);
    ~ShopWindow();

    enum class ShopOption
    {
        VIEW_INFO = 1,
        HP_POTION = 2,
        MP_POTION = 3,
        LEATHER_ARMOR = 4,
        IRON_ARMOR = 5,
        DIAMOND_ARMOR = 6,
        RECOVER = 7,
        SELL = 8,
        LEAVE = 9
    };

private slots:
    void on_next_floor_clicked();

    void on_shoplist_currentRowChanged(int currentRow);

    void on_select_clicked();

    void on_back_clicked();

private:
    Ui::ShopWindow *ui;
    QMediaPlaylist *playlist;
    QMediaPlayer *player;
    QMediaPlayer *click;

    void refresh();
    void sell_items() const;
    int selling = 0; //0 not selling, 1 selling
    int choice = -2;
    Tower *tower;
};

#endif // SHOPWINDOW_H

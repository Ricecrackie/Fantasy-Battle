/*
 *  This header file creates the UI for the class InitialDialog, where an initial
 *  dialog is generated to provide a brief explaination of the game. This UI only
 *  generates if the current floor is the first floor (e.g. just started the game).
*/

#ifndef INITIALDIALOG_H
#define INITIALDIALOG_H

#include "Tower.h"

#include <QDialog>
#include <QMediaPlayer>
#include <QMediaPlaylist>

namespace Ui {
class InitialDialog;
}

class InitialDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InitialDialog(Tower *tower, QWidget *parent);
    ~InitialDialog();

private slots:
    void on_Next_clicked();

private:
    Ui::InitialDialog *ui;
    int dialog = 0;
    QMediaPlaylist *playlist;
    QMediaPlayer *player;
    QMediaPlayer *click;

    Tower *tower;
};

#endif // INITIALDIALOG_H

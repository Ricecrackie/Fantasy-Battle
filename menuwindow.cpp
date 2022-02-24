#include "menuwindow.h"
#include "ui_menuwindow.h"
#include "floorwindow.h"
#include "initialdialog.h"

#include "Tower.h"

#include <QPixmap>
#include <QFileDialog>

// call constructor to create a MenuWindow Object
MenuWindow::MenuWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MenuWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::MSWindowsFixedSizeDialogHint);
    this->statusBar()->setSizeGripEnabled(false);
    QPixmap bkgnd(":/resources/images/tower.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);

    this->setWindowTitle("Fantasy Battle");

    ui->NewGame->setStyleSheet("QPushButton{image: url(:/resources/images/New Game.png); background-color: transparent}"
                            "QPushButton::hover{image: url(:/resources/images/New Game_hover.png); background-color: transparent}");
    ui->LoadGame->setStyleSheet("QPushButton{image: url(:/resources/images/Load Game.png); background-color: transparent}"
                            "QPushButton::hover{image: url(:/resources/images/Load Game_hover.png); background-color: transparent}");
    ui->Exit->setStyleSheet("QPushButton{image: url(:/resources/images/Exit.png); background-color: transparent}"
                            "QPushButton::hover{image: url(:/resources/images/Exit_hover.png); background-color: transparent}");
    MenuWindow::ui->pages->setCurrentIndex(0);

    ui->left_diff->setStyleSheet("QPushButton{image: url(:/resources/images/left.png); background-color: transparent}"
                                 "QPushButton::hover{image: url(:/resources/images/left_hover.png); background-color: transparent}");
    ui->right_diff->setStyleSheet("QPushButton{image: url(:/resources/images/right.png); background-color: transparent}"
                                 "QPushButton::hover{image: url(:/resources/images/right_hover.png); background-color: transparent}");
    ui->difficulty->setStyleSheet("image: url(:/resources/images/Normal.png)");

    ui->left_floors->setStyleSheet("QPushButton{image: url(:/resources/images/left.png); background-color: transparent}"
                                 "QPushButton::hover{image: url(:/resources/images/left_hover.png); background-color: transparent}");
    ui->right_floors->setStyleSheet("QPushButton{image: url(:/resources/images/right.png); background-color: transparent}"
                                 "QPushButton::hover{image: url(:/resources/images/right_hover.png); background-color: transparent}");

    ui->StartGame->setStyleSheet("QPushButton{image: url(:/resources/images/Start Game.png); background-color: transparent}"
                                 "QPushButton::hover{image: url(:/resources/images/Start Game_hover.png); background-color: transparent}");

    MenuWindow::ui->floors->setText(QString::number(floors));

    playlist = new QMediaPlaylist();
    playlist->addMedia(QUrl("qrc:/resources/sounds/backgroundmusic.mp3"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);

    player = new QMediaPlayer();
    player->setPlaylist(playlist);
    player->play();

    click = new QMediaPlayer();
    click->setMedia(QUrl("qrc:/resources/sounds/click.mp3"));
}

// destructor of MenuWindow Object, deallocates the memory of the ui and music
MenuWindow::~MenuWindow()
{
    delete ui;
    delete player;
    delete playlist;
    delete click;
}

// Starts the game by passing the Tower object created previously to the constructor of the next window
void MenuWindow::start_game(Tower *tower)
{
    player->stop();
    current = tower->get_current_floor_index();
    if (current > 0)
    {
        FloorWindow *m = new FloorWindow{tower, nullptr};
        m->setAttribute(Qt::WA_DeleteOnClose);
        m->show();
        close();
    }
    else
    {
        InitialDialog *n = new InitialDialog{tower, nullptr};
        n->setAttribute(Qt::WA_DeleteOnClose);
        n->show();
        close();
    }
}

// Quits the game
void MenuWindow::on_Exit_clicked()
{
    click->play();
    this->close();
}

// Moves to the page to create a new Tower object
void MenuWindow::on_NewGame_clicked()
{
    click->play();
    MenuWindow::ui->pages->setCurrentIndex(1);
}

// Loads a Tower object from a saved .txt file and starts the game
void MenuWindow::on_LoadGame_clicked()
{
    click->play();
    QString filename = QFileDialog::getOpenFileName(this, tr("Load Saved Game.."), QDir::currentPath(), tr("Text Files (*.txt)"));
    if (!filename.isEmpty() && !filename.isNull())
    {
        Tower* load_tower = new Tower(filename.toStdString());
        MenuWindow::start_game(load_tower);
    }
}

// decreases the difficulty
void MenuWindow::on_left_diff_clicked()
{
    if (difficulty == Tower::Difficulty::NORMAL)
    {
        click->play();
        difficulty = Tower::Difficulty::EASY;
        ui->difficulty->setStyleSheet("image: url(:/resources/images/easy.png)");
    }
    else if (difficulty == Tower::Difficulty::HARD)
    {
        click->play();
        difficulty = Tower::Difficulty::NORMAL;
        ui->difficulty->setStyleSheet("image: url(:/resources/images/Normal.png)");
    }
}

// increases the difficulty
void MenuWindow::on_right_diff_clicked()
{
    if (difficulty == Tower::Difficulty::EASY)
    {
        click->play();
        difficulty = Tower::Difficulty::NORMAL;
        ui->difficulty->setStyleSheet("image: url(:/resources/images/Normal.png)");
    }
    else if (difficulty == Tower::Difficulty::NORMAL)
    {
        click->play();
        difficulty = Tower::Difficulty::HARD;
        ui->difficulty->setStyleSheet("image: url(:/resources/images/Hard.png)");
    }
}

// decreases the number of floors
void MenuWindow::on_left_floors_clicked()
{
    if (floors >= 10)
    {
        click->play();
        floors -= 5;
        MenuWindow::ui->floors->setText(QString::number(floors));
    }
}

// increases the number of floors
void MenuWindow::on_right_floors_clicked()
{
    if (floors <= 15)
    {
        click->play();
        floors += 5;
        MenuWindow::ui->floors->setText(QString::number(floors));
    }
}

// Starts the game with the new Tower object created by using the parameters given by the player
void MenuWindow::on_StartGame_clicked()
{
    click->play();
    Tower* new_tower = new Tower(difficulty, floors);
    MenuWindow::start_game(new_tower);
}


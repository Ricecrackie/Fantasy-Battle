#include "initialdialog.h"
#include "ui_initialdialog.h"
#include "floorwindow.h"

#include <QPixmap>

// call constructor to create a InitialDialog Object by passing the Tower object to the constructor
InitialDialog::InitialDialog(Tower *tower, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InitialDialog),
    tower(tower)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::MSWindowsFixedSizeDialogHint);
    this->setSizeGripEnabled(false);

    this->setWindowTitle("Welcome, Adventurer!");

    QPixmap bkgnd(":/resources/images/tower2.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);

    ui->Next->setStyleSheet("QPushButton{image: url(:/resources/images/Next.png); background-color: transparent}"
                            "QPushButton::hover{image: url(:/resources/images/Next_hover.png); background-color: transparent}");

    ui->dialog->setWordWrap(true);
    ui->dialog->setText("Welcome, Adventurer, to the Tower of Fantasy!");

    playlist = new QMediaPlaylist();
    playlist->addMedia(QUrl("qrc:/resources/sounds/initialtheme.mp3"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);

    player = new QMediaPlayer();
    player->setPlaylist(playlist);
    player->play();

    click = new QMediaPlayer();
    click->setMedia(QUrl("qrc:/resources/sounds/click.mp3"));
}

// destructor of InitialDialog Object, deallocates the memory of the ui and music
InitialDialog::~InitialDialog()
{
    delete ui;
    delete player;
    delete playlist;
    delete click;
}

// changes the dialog and creates the FloorWindow Object after reaching the end of the dialog
void InitialDialog::on_Next_clicked()
{
    click->play();
    if (dialog == 0)
    {
        ui->dialog->setText("Your goal is to conquer the tower by reaching the top.");
    }
    else if (dialog == 1)
    {
        ui->dialog->setText("But be careful! There are dangerous monsters on each floor. You'll have to defeat them to advance to the next floor.");
    }
    else if (dialog == 2)
    {
        ui->dialog->setText("We have set up shops on every 5 floors so you can buy items and recover your HP and MP.");
    }
    else if (dialog == 3)
    {
        ui->dialog->setText("Good luck with your adventure!");
    }
    else if (dialog == 4)
    {
        player->stop();
        FloorWindow *m = new FloorWindow{tower, nullptr};
        m->setAttribute(Qt::WA_DeleteOnClose);
        m->show();
        close();
    }
    ++dialog;
}


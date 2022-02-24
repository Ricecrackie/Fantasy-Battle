#include "floorwindow.h"
#include "ui_floorwindow.h"
#include "battlewindow.h"
#include "shopwindow.h"
#include "Tower.h"
#include <QColorDialog>
#include <QPalette>
extern int EXPforLevel2;
extern int EXPforLevel3;
extern int EXPforLevel4;
extern int EXPforLevel5;

// call constructor to create a FloorWindow Object by passing the Tower object to the constructor
FloorWindow::FloorWindow(Tower *tower, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FloorWindow),
    tower(tower)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::MSWindowsFixedSizeDialogHint);
    this->statusBar()->setSizeGripEnabled(false);
    QPixmap bkgnd(":/resources/images/floor.png");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);

    playlist = new QMediaPlaylist();
    playlist->addMedia(QUrl("qrc:/resources/sounds/floor.mp3"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);

    player = new QMediaPlayer();
    player->setPlaylist(playlist);
    player->play();

    click = new QMediaPlayer();
    click->setMedia(QUrl("qrc:/resources/sounds/click.mp3"));

    victory = new QMediaPlayer();
    victory->setMedia(QUrl("qrc:/resources/sounds/Victory.mp3"));

    string name = "Floor " + std::to_string(1+(tower->get_current_floor_index())) + "/" + std::to_string(tower->get_tower_size());
    this->setWindowTitle(QString::fromStdString(name));
    ui->statusBar->hide();

    ui->Quit->setStyleSheet("QPushButton{image: url(:/resources/images/Exit.png); background-color: transparent}"
                            "QPushButton::hover{image: url(:/resources/images/Exit_hover.png); background-color: transparent}");
    ui->Save->setStyleSheet("QPushButton{image: url(:/resources/images/Save.png); background-color: transparent}"
                            "QPushButton::hover{image: url(:/resources/images/Save_hover.png); background-color: transparent}");
    ui->Item->setStyleSheet("QPushButton{image: url(:/resources/images/Items.png); background-color: transparent}"
                            "QPushButton::hover{image: url(:/resources/images/Items_hover.png); background-color: transparent}");
    ui->Equipment->setStyleSheet("QPushButton{image: url(:/resources/images/Equipment.png); background-color: transparent}"
                            "QPushButton::hover{image: url(:/resources/images/Equipment_hover.png); background-color: transparent}");
    ui->Equipment->setStyleSheet("QPushButton{image: url(:/resources/images/Equipment.png); background-color: transparent}"
                            "QPushButton::hover{image: url(:/resources/images/Equipment_hover.png); background-color: transparent}");
    ui->Status->setStyleSheet("QPushButton{image: url(:/resources/images/Status.png); background-color: transparent}"
                            "QPushButton::hover{image: url(:/resources/images/Status_hover.png); background-color: transparent}");
    ui->Next_floor->setStyleSheet("QPushButton{image: url(:/resources/images/Next Floor.png); background-color: transparent}"
                            "QPushButton::hover{image: url(:/resources/images/Next Floor_hover.png); background-color: transparent}");
    ui->StartBattle->setStyleSheet("QPushButton{image: url(:/resources/images/Start Battle.png); background-color: transparent}"
                            "QPushButton::hover{image: url(:/resources/images/Start Battle_hover.png); background-color: transparent}");
    ui->pages->setCurrentIndex(0);
    ui->use_item->setStyleSheet("QPushButton{image: url(:/resources/images/Use.png); background-color: transparent}"
                           "QPushButton::hover{image: url(:/resources/images/Use_hover.png); background-color: transparent}");
    ui->back_item->setStyleSheet("QPushButton{image: url(:/resources/images/Back.png); background-color: transparent}"
                           "QPushButton::hover{image: url(:/resources/images/Back_hover.png); background-color: transparent}");
    ui->back_status->setStyleSheet("QPushButton{image: url(:/resources/images/Back.png); background-color: transparent}"
                           "QPushButton::hover{image: url(:/resources/images/Back_hover.png); background-color: transparent}");
    ui->FloorDialog_next->setStyleSheet("QPushButton{image: url(:/resources/images/Next.png); background-color: transparent}"
                                         "QPushButton::hover{image: url(:/resources/images/Next_hover.png); background-color: transparent}");
    ui->FloorDialog->hide();
    ui->item_name->setStyleSheet("QLabel {color: white;}");
    ui->item_description->setStyleSheet("QLabel {color: white;}");
}

// destructor of BattleWindow Object, deallocates the memory of the ui and music
FloorWindow::~FloorWindow()
{
    delete ui;
    delete player;
    delete playlist;
    delete click;
}

// Closes the game and deallocates the memory of Tower
void FloorWindow::on_Quit_clicked()
{
    click->play();
    delete tower;
    this->close();
}

// Saves a game as a .txt
void FloorWindow::on_Save_clicked()
{
    click->play();
    QString filename = QFileDialog::getSaveFileName(this, tr("Save Tower"), QDir::currentPath(), tr("Text Files(*.txt)"));
    if (!filename.isNull())
    {
        this->tower->save(filename.toStdString());
    }
}

// When item is selected, a list of items will show up for the player to choose
void FloorWindow::on_Item_clicked()
{
    click->play();
    list_mode = 1;
    ui->pages->setCurrentIndex(1);
    for (int i = 0; i < (int)(tower->player->get_inventory().size()); ++i)
    {
        if (tower->player->get_inventory()[i]->get_isUsable())
        {
            ui->item_list->addItem(QString::fromStdString(tower->player->get_inventory()[i]->get_item_name() + "\t\t" + tower->player->get_inventory()[i]->get_item_description()));
        }
    }
}

// the row selected on the item/equipment list by the user is saved to item_selected/equipment_selected
void FloorWindow::on_item_list_currentRowChanged(int currentRow)
{
    if (list_mode == 0)
    {
        equipment_selected = currentRow;
    }
    else if (list_mode == 1)
    {
        item_selected = currentRow;
    }
}

// the FloorWindow returns from the use item/equipment screen to the main FloorWindow
void FloorWindow::on_back_item_clicked()
{
    click->play();
    ui->item_list->clear();
    list_mode = -1;
    ui->pages->setCurrentIndex(0);
}

// when Use is clicked, the code determines if an equipment or item is chosen, and runs the code to use the equipment or item
void FloorWindow::on_use_item_clicked()
{
    if (list_mode == 0)
    {
        if (equipment_selected >= 0)
        {
            for (int i = 0; i < (int)(tower->player->get_inventory().size()); ++i)
            {
                if (i == equipment_selected)
                {
                    if (!(tower->player->get_inventory()[i]->get_isEquipable()))
                    {
                        ++equipment_selected;
                    }
                    else
                    {
                        if (tower->player->change_equipment(tower->player->get_inventory()[equipment_selected]))
                        {
                            click->play();
                            ui->item_list->clear();
                            list_mode = -1;
                            ui->pages->setCurrentIndex(0);
                        }
                    }
                }
            }
        }
    }
    else if (list_mode == 1)
    {
        if (item_selected >= 0)
        {
            for (int i = 0; i < (int)(tower->player->get_inventory().size()); ++i)
            {
                if (i == item_selected)
                {
                    if (!(tower->player->get_inventory()[i]->get_isUsable()))
                    {
                        ++item_selected;
                    }
                    else
                    {
                        if (tower->player->use_item(tower->player->get_inventory()[item_selected]))
                        {
                            click->play();
                            ui->item_list->clear();
                            list_mode = -1;
                            ui->pages->setCurrentIndex(0);
                        }
                    }
                }
            }
        }
    }
}

// When Equipment is selected, a list of Equipment will show up for the player to choose
void FloorWindow::on_Equipment_clicked()
{
    click->play();
    list_mode = 0;
    ui->pages->setCurrentIndex(1);
    for (int i = 0; i < (int)(tower->player->get_inventory().size()); ++i)
    {
        if (tower->player->get_inventory()[i]->get_isEquipable())
        {
            ui->item_list->addItem(QString::fromStdString(tower->player->get_inventory()[i]->get_item_name()+"\t\t"+tower->player->get_inventory()[i]->get_item_description()));
        }
    }
}

// the Status of the player will be displayed on screen
void FloorWindow::on_Status_clicked()
{
    click->play();
    ui->pages->setCurrentIndex(2);
    std::string temp;
    ui->Name->setText(QString::fromStdString(tower->player->get_name()));
    ui->Total_floors->setText(QString::number(tower->get_tower_size()));
    ui->Current_floor->setText(QString::number(1+tower->get_current_floor_index()));
    ui->Level->setText(QString::number(tower->player->get_level()));

    ui->ExpBar->setAlignment(Qt::AlignCenter);
    ui->ExpBar->setMinimum(0);
    switch(tower->player->get_level())
    {
        case 1: temp = std::to_string(tower->player->EXP) + "/" + std::to_string(EXPforLevel2);
                ui->ExpBar->setFormat(QString::fromStdString(temp));
                ui->ExpBar->setMaximum(EXPforLevel2);
                break;
        case 2: temp = std::to_string(tower->player->EXP) + "/" + std::to_string(EXPforLevel3);
                ui->ExpBar->setFormat(QString::fromStdString(temp));
                ui->ExpBar->setMaximum(EXPforLevel3);
                break;
        case 3: temp = std::to_string(tower->player->EXP) + "/" + std::to_string(EXPforLevel4);
                ui->ExpBar->setFormat(QString::fromStdString(temp));
                ui->ExpBar->setMaximum(EXPforLevel4);
                break;
        case 4: temp = std::to_string(tower->player->EXP) + "/" + std::to_string(EXPforLevel5);
                ui->ExpBar->setFormat(QString::fromStdString(temp));
                ui->ExpBar->setMaximum(EXPforLevel5);
                break;
        case 5: ui->ExpBar->setFormat("MAX");
                ui->ExpBar->setMaximum(300);
                break;
    }
    ui->ExpBar->setValue(tower->player->EXP);

    ui->Funds->setText(QString::number(tower->player->money));

    ui->HPBar->setAlignment(Qt::AlignCenter);
    ui->HPBar->setMinimum(0);
    ui->HPBar->setMaximum(tower->player->get_HP_max());
    ui->HPBar->setValue(tower->player->HP);
    temp = std::to_string(tower->player->HP) + "/" + std::to_string(tower->player->get_HP_max());
    ui->HPBar->setFormat(QString::fromStdString(temp));

    ui->MPBar->setAlignment(Qt::AlignCenter);
    ui->MPBar->setMinimum(0);
    ui->MPBar->setMaximum(tower->player->get_MP_max());
    ui->MPBar->setValue(tower->player->MP);
    temp = std::to_string(tower->player->MP) + "/" + std::to_string(tower->player->get_MP_max());
    ui->MPBar->setFormat(QString::fromStdString(temp));

    ui->APBar->setAlignment(Qt::AlignCenter);
    ui->APBar->setMinimum(0);
    ui->APBar->setMaximum(tower->player->get_AP_max());
    ui->APBar->setValue(tower->player->AP);
    temp = std::to_string(tower->player->AP) + "/" + std::to_string(tower->player->get_AP_max());
    ui->APBar->setFormat(QString::fromStdString(temp));

    ui->ATK->setText(QString::number(tower->player->ATK));
    ui->DEF->setText(QString::number(tower->player->DEF));
}

// the FloorWindow returns from the Status screen to the main FloorWindow
void FloorWindow::on_back_status_clicked()
{
    click->play();
    ui->pages->setCurrentIndex(0);
}

// if the floor is not cleared, the BattleWindow will be constructed and closes the FloorWindow
void FloorWindow::on_StartBattle_clicked()
{
    if (tower->start_battle())
    {
        click->play();
        player->stop();
        BattleWindow *m = new BattleWindow{tower, nullptr};
        m->setAttribute(Qt::WA_DeleteOnClose);
        m->show();
        close();
    }
    else
    {
        click->play();
        ui->FloorDialog_list->clear();
        ui->FloorDialog_list->addItem("The enemies of this floor are defeated.");
        ui->FloorDialog->show();
    }
}

// if the enemies on the current floor have all been defeated, the game moves on to the next floor of the tower
void FloorWindow::on_Next_floor_clicked()
{
    click->play();
    ui->FloorDialog_list->clear();
    if (tower->move_to_next_floor())
    {
        string name = "Floor " + std::to_string(1+(tower->get_current_floor_index())) + "/" + std::to_string(tower->get_tower_size());
        this->setWindowTitle(QString::fromStdString(name));
        shop = 1;
        ui->FloorDialog_list->addItem("Moved to next floor.");
        ui->FloorDialog->show();
        return;
    }
    else if (!tower->move_to_next_floor() && !tower->get_floors()[tower->get_current_floor_index()].isClear()) {
        ui->FloorDialog_list->addItem("The enemies of this floor are not cleared.");
        ui->FloorDialog->show();
        return;
    }
    else if (!tower->move_to_next_floor() && tower->get_current_floor_index() == tower->get_tower_size()-1) {
        victory->play();
        ui->FloorDialog_list->addItem("Congratulations! You have reached the end of the tower!");
        ui->FloorDialog->show();
        return;
    }
}

// a button to close the pop-up notifcation when the player moves to the next floor and triggers the shop if the player reaches floors 5, 10, 15, 20
void FloorWindow::on_FloorDialog_next_clicked()
{
    click->play();
    ui->FloorDialog->hide();
    ui->FloorDialog_list->clear();
    if ((tower->get_current_floor_index()+1)%5 == 0)
    {
        if (shop == 1)
        {
            ShopWindow *m = new ShopWindow{tower, nullptr};
            m->setAttribute(Qt::WA_DeleteOnClose);
            m->show();
            close();
        }
    }
}


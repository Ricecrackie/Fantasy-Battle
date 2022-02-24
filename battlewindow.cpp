#include "battlewindow.h"
#include "ui_battlewindow.h"
#include "Tower.h"
#include "floorwindow.h"

extern int use_item_APcost;
extern int EXPforLevel2;
extern int EXPforLevel3;
extern int EXPforLevel4;
extern int EXPforLevel5;
extern int random_number(const int&, const int&);
extern int random_power_up(const int begin, const int end);
extern const int BossATK;
extern const int BossDEF;
extern const int StrongEnemyATK;
extern const int StrongEnemyDEF;
extern const int WeakEnemyATK;
extern const int WeakEnemyDEF;

// call constructor to create a BattleWindow Object by passing the Tower object to the constructor
BattleWindow::BattleWindow(Tower *tower, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BattleWindow),
    tower(tower)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::MSWindowsFixedSizeDialogHint);
    this->statusBar()->setSizeGripEnabled(false);
    QPixmap bkgnd(":/resources/images/BattleBackground.png");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);

    playlist = new QMediaPlaylist();
    playlist->addMedia(QUrl("qrc:/resources/sounds/battletheme.mp3"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);

    player = new QMediaPlayer();
    player->setPlaylist(playlist);
    player->play();

    click = new QMediaPlayer();
    click->setMedia(QUrl("qrc:/resources/sounds/click.mp3"));

    ui->AddAction->setStyleSheet("QPushButton{image: url(:/resources/images/Add Action.png); background-color: transparent}"
                            "QPushButton::hover{image: url(:/resources/images/Add Action_hover.png); background-color: transparent}");
    ui->DeleteAction->setStyleSheet("QPushButton{image: url(:/resources/images/Delete Action.png); background-color: transparent}"
                            "QPushButton::hover{image: url(:/resources/images/Delete Action_hover.png); background-color: transparent}");
    ui->SwapAction->setStyleSheet("QPushButton{image: url(:/resources/images/Swap Action.png); background-color: transparent}"
                            "QPushButton::hover{image: url(:/resources/images/Swap Action_hover.png); background-color: transparent}");
    ui->EndRound->setStyleSheet("QPushButton{image: url(:/resources/images/End Round.png); background-color: transparent}"
                            "QPushButton::hover{image: url(:/resources/images/End Round_hover.png); background-color: transparent}");
    ui->Flee->setStyleSheet("QPushButton{image: url(:/resources/images/Flee.png); background-color: transparent}"
                            "QPushButton::hover{image: url(:/resources/images/Flee_hover.png); background-color: transparent}");
    ui->Skill->setStyleSheet("QPushButton{image: url(:/resources/images/Skill.png); background-color: transparent}"
                            "QPushButton::hover{image: url(:/resources/images/Skill_hover.png); background-color: transparent}");
    ui->Items->setStyleSheet("QPushButton{image: url(:/resources/images/Items.png); background-color: transparent}"
                            "QPushButton::hover{image: url(:/resources/images/Items_hover.png); background-color: transparent}");
    ui->use->setStyleSheet("QPushButton{image: url(:/resources/images/Use.png); background-color: transparent}"
                            "QPushButton::hover{image: url(:/resources/images/Use_hover.png); background-color: transparent}");
    ui->back->setStyleSheet("QPushButton{image: url(:/resources/images/Back.png); background-color: transparent}"
                            "QPushButton::hover{image: url(:/resources/images/Back_hover.png); background-color: transparent}");
    ui->statusbar->hide();
    ui->back_delete->setStyleSheet("QPushButton{image: url(:/resources/images/Back.png); background-color: transparent}"
                            "QPushButton::hover{image: url(:/resources/images/Back_hover.png); background-color: transparent}");
    ui->delete_action->setStyleSheet("QPushButton{image: url(:/resources/images/Delete.png); background-color: transparent}"
                            "QPushButton::hover{image: url(:/resources/images/Delete_hover.png); background-color: transparent}");
    ui->back_swap->setStyleSheet("QPushButton{image: url(:/resources/images/Back.png); background-color: transparent}"
                            "QPushButton::hover{image: url(:/resources/images/Back_hover.png); background-color: transparent}");
    ui->swap->setStyleSheet("QPushButton{image: url(:/resources/images/Swap.png); background-color: transparent}"
                            "QPushButton::hover{image: url(:/resources/images/Swap_hover.png); background-color: transparent}");
    ui->BattleDialog_next->setStyleSheet("QPushButton{image: url(:/resources/images/Next.png); background-color: transparent}"
                                         "QPushButton::hover{image: url(:/resources/images/Next_hover.png); background-color: transparent}");
    refresh();
}

// refreshes the statuses of the player and the enemies after each move and after each turn
void BattleWindow::refresh()
{
    string name = "Floor " + std::to_string(1+(tower->get_current_floor_index())) + "/" + std::to_string(tower->get_tower_size()) + " Battle: Round " + std::to_string(tower->player->battle->get_round_counter());
    this->setWindowTitle(QString::fromStdString(name));

    ui->BattleDialog->hide();

    std::string temp;
    ui->PlayerName->setText(QString::fromStdString(tower->player->get_name()));
    ui->PlayerLevel->setText(QString::number(tower->player->get_level()));
    ui->PlayerEXPBar->setAlignment(Qt::AlignCenter);
    ui->PlayerEXPBar->setMinimum(0);
    switch(tower->player->get_level())
    {
        case 1: temp = std::to_string(tower->player->EXP) + "/" + std::to_string(EXPforLevel2);
                ui->PlayerEXPBar->setFormat(QString::fromStdString(temp));
                ui->PlayerEXPBar->setMaximum(EXPforLevel2);
                break;
        case 2: temp = std::to_string(tower->player->EXP) + "/" + std::to_string(EXPforLevel3);
                ui->PlayerEXPBar->setFormat(QString::fromStdString(temp));
                ui->PlayerEXPBar->setMaximum(EXPforLevel3);
                break;
        case 3: temp = std::to_string(tower->player->EXP) + "/" + std::to_string(EXPforLevel4);
                ui->PlayerEXPBar->setFormat(QString::fromStdString(temp));
                ui->PlayerEXPBar->setMaximum(EXPforLevel4);
                break;
        case 4: temp = std::to_string(tower->player->EXP) + "/" + std::to_string(EXPforLevel5);
                ui->PlayerEXPBar->setFormat(QString::fromStdString(temp));
                ui->PlayerEXPBar->setMaximum(EXPforLevel5);
                break;
        case 5: ui->PlayerEXPBar->setFormat("MAX");
                ui->PlayerEXPBar->setMaximum(300);
                break;
    }
    ui->PlayerEXPBar->setValue(tower->player->EXP);

    ui->PlayerFunds->setText(QString::number(tower->player->money));

    ui->PlayerHPBar->setAlignment(Qt::AlignCenter);
    ui->PlayerHPBar->setMinimum(0);
    ui->PlayerHPBar->setMaximum(tower->player->get_HP_max());
    ui->PlayerHPBar->setValue(tower->player->HP);
    temp = std::to_string(tower->player->HP) + "/" + std::to_string(tower->player->get_HP_max());
    ui->PlayerHPBar->setFormat(QString::fromStdString(temp));

    ui->PlayerMPBar->setAlignment(Qt::AlignCenter);
    ui->PlayerMPBar->setMinimum(0);
    ui->PlayerMPBar->setMaximum(tower->player->get_MP_max());
    ui->PlayerMPBar->setValue(tower->player->MP);
    temp = std::to_string(tower->player->MP) + "/" + std::to_string(tower->player->get_MP_max());
    ui->PlayerMPBar->setFormat(QString::fromStdString(temp));

    ui->PlayerAPBar->setAlignment(Qt::AlignCenter);
    ui->PlayerAPBar->setMinimum(0);
    ui->PlayerAPBar->setMaximum(tower->player->get_AP_max());
    ui->PlayerAPBar->setValue(tower->player->AP);
    temp = std::to_string(tower->player->AP) + "/" + std::to_string(tower->player->get_AP_max());
    ui->PlayerAPBar->setFormat(QString::fromStdString(temp));

    ui->PlayerATK->setText(QString::number(tower->player->ATK));
    ui->PlayerDEF->setText(QString::number(tower->player->DEF));
    for (int i = 0; i < tower->getNumOfEnemyinCurrentFloor(); ++i)
    {
        if (tower->get_floors()[tower->get_current_floor_index()].get_enemy()[i]->HP != 0)
        {
            if (i == 0)
            {
                switch(tower->get_floors()[tower->get_current_floor_index()].get_enemy()[i]->get_type())
                {
                    case Enemy::enemy_type::WeakEnemy:
                        ui->Enemy0->setStyleSheet("QPushButton{image: url(:/resources/images/WeakEnemy.png); background-color: transparent}");
                        break;
                    case Enemy::enemy_type::StrongEnemy:
                        ui->Enemy0->setStyleSheet("QPushButton{image: url(:/resources/images/StrongEnemy.png); background-color: transparent}");
                        break;
                    case Enemy::enemy_type::Boss:
                        ui->Enemy0->setStyleSheet("QPushButton{image: url(:/resources/images/Boss.png); background-color: transparent}");
                        break;
                }
                ui->Enemy0HPBar->setAlignment(Qt::AlignCenter);
                ui->Enemy0HPBar->setMinimum(0);
                ui->Enemy0HPBar->setMaximum(tower->get_floors()[tower->get_current_floor_index()].get_enemy()[i]->get_HP_max());
                ui->Enemy0HPBar->setValue(tower->get_floors()[tower->get_current_floor_index()].get_enemy()[i]->HP);
                ui->Enemy0HPBar->setFormat(QString::fromStdString(std::to_string(tower->get_floors()[tower->get_current_floor_index()].get_enemy()[i]->HP) + "/" + std::to_string(tower->get_floors()[tower->get_current_floor_index()].get_enemy()[i]->get_HP_max())));
                ui->Enemy0MPBar->setAlignment(Qt::AlignCenter);
                ui->Enemy0MPBar->setMinimum(0);
                ui->Enemy0MPBar->setMaximum(tower->get_floors()[tower->get_current_floor_index()].get_enemy()[i]->get_MP_max());
                ui->Enemy0MPBar->setValue(tower->get_floors()[tower->get_current_floor_index()].get_enemy()[i]->MP);
                ui->Enemy0MPBar->setFormat(QString::fromStdString(std::to_string(tower->get_floors()[tower->get_current_floor_index()].get_enemy()[i]->MP) + "/" + std::to_string(tower->get_floors()[tower->get_current_floor_index()].get_enemy()[i]->get_MP_max())));
                ui->Enemy0ATK->setText(QString::number(tower->get_floors()[tower->get_current_floor_index()].get_enemy()[i]->ATK));
                ui->Enemy0DEF->setText(QString::number(tower->get_floors()[tower->get_current_floor_index()].get_enemy()[i]->DEF));
            }
            else if (i == 1)
            {
                switch(tower->get_floors()[tower->get_current_floor_index()].get_enemy()[i]->get_type())
                {
                    case Enemy::enemy_type::WeakEnemy:
                        ui->Enemy1->setStyleSheet("QPushButton{image: url(:/resources/images/WeakEnemy.png); background-color: transparent}");
                        break;
                    case Enemy::enemy_type::StrongEnemy:
                        ui->Enemy1->setStyleSheet("QPushButton{image: url(:/resources/images/StrongEnemy.png); background-color: transparent}");
                        break;
                    case Enemy::enemy_type::Boss:
                        ui->Enemy1->setStyleSheet("QPushButton{image: url(:/resources/images/Boss.png); background-color: transparent}");
                        break;
                }
                ui->Enemy1HPBar->setAlignment(Qt::AlignCenter);
                ui->Enemy1HPBar->setMinimum(0);
                ui->Enemy1HPBar->setMaximum(tower->get_floors()[tower->get_current_floor_index()].get_enemy()[i]->get_HP_max());
                ui->Enemy1HPBar->setValue(tower->get_floors()[tower->get_current_floor_index()].get_enemy()[i]->HP);
                ui->Enemy1HPBar->setFormat(QString::fromStdString(std::to_string(tower->get_floors()[tower->get_current_floor_index()].get_enemy()[i]->HP) + "/" + std::to_string(tower->get_floors()[tower->get_current_floor_index()].get_enemy()[i]->get_HP_max())));
                ui->Enemy1MPBar->setAlignment(Qt::AlignCenter);
                ui->Enemy1MPBar->setMinimum(0);
                ui->Enemy1MPBar->setMaximum(tower->get_floors()[tower->get_current_floor_index()].get_enemy()[i]->get_MP_max());
                ui->Enemy1MPBar->setValue(tower->get_floors()[tower->get_current_floor_index()].get_enemy()[i]->MP);
                ui->Enemy1MPBar->setFormat(QString::fromStdString(std::to_string(tower->get_floors()[tower->get_current_floor_index()].get_enemy()[i]->MP) + "/" + std::to_string(tower->get_floors()[tower->get_current_floor_index()].get_enemy()[i]->get_MP_max())));
                ui->Enemy1ATK->setText(QString::number(tower->get_floors()[tower->get_current_floor_index()].get_enemy()[i]->ATK));
                ui->Enemy1DEF->setText(QString::number(tower->get_floors()[tower->get_current_floor_index()].get_enemy()[i]->DEF));
            }
            else if (i == 2)
            {
                switch(tower->get_floors()[tower->get_current_floor_index()].get_enemy()[i]->get_type())
                {
                    case Enemy::enemy_type::WeakEnemy:
                        ui->Enemy2->setStyleSheet("QPushButton{image: url(:/resources/images/WeakEnemy.png); background-color: transparent}");
                        break;
                    case Enemy::enemy_type::StrongEnemy:
                        ui->Enemy2->setStyleSheet("QPushButton{image: url(:/resources/images/StrongEnemy.png); background-color: transparent}");
                        break;
                    case Enemy::enemy_type::Boss:
                        ui->Enemy2->setStyleSheet("QPushButton{image: url(:/resources/images/Boss.png); background-color: transparent}");
                        break;
                }
                ui->Enemy2HPBar->setAlignment(Qt::AlignCenter);
                ui->Enemy2HPBar->setMinimum(0);
                ui->Enemy2HPBar->setMaximum(tower->get_floors()[tower->get_current_floor_index()].get_enemy()[i]->get_HP_max());
                ui->Enemy2HPBar->setValue(tower->get_floors()[tower->get_current_floor_index()].get_enemy()[i]->HP);
                ui->Enemy2HPBar->setFormat(QString::fromStdString(std::to_string(tower->get_floors()[tower->get_current_floor_index()].get_enemy()[i]->HP) + "/" + std::to_string(tower->get_floors()[tower->get_current_floor_index()].get_enemy()[i]->get_HP_max())));
                ui->Enemy2MPBar->setAlignment(Qt::AlignCenter);
                ui->Enemy2MPBar->setMinimum(0);
                ui->Enemy2MPBar->setMaximum(tower->get_floors()[tower->get_current_floor_index()].get_enemy()[i]->get_MP_max());
                ui->Enemy2MPBar->setValue(tower->get_floors()[tower->get_current_floor_index()].get_enemy()[i]->MP);
                ui->Enemy2MPBar->setFormat(QString::fromStdString(std::to_string(tower->get_floors()[tower->get_current_floor_index()].get_enemy()[i]->MP) + "/" + std::to_string(tower->get_floors()[tower->get_current_floor_index()].get_enemy()[i]->get_MP_max())));
                ui->Enemy2ATK->setText(QString::number(tower->get_floors()[tower->get_current_floor_index()].get_enemy()[i]->ATK));
                ui->Enemy2DEF->setText(QString::number(tower->get_floors()[tower->get_current_floor_index()].get_enemy()[i]->DEF));
            }
            else if (i == 3)
            {
                switch(tower->get_floors()[tower->get_current_floor_index()].get_enemy()[i]->get_type())
                {
                    case Enemy::enemy_type::WeakEnemy:
                        ui->Enemy3->setStyleSheet("QPushButton{image: url(:/resources/images/WeakEnemy.png); background-color: transparent}");
                        break;
                    case Enemy::enemy_type::StrongEnemy:
                        ui->Enemy3->setStyleSheet("QPushButton{image: url(:/resources/images/StrongEnemy.png); background-color: transparent}");
                        break;
                    case Enemy::enemy_type::Boss:
                        ui->Enemy3->setStyleSheet("QPushButton{image: url(:/resources/images/Boss.png); background-color: transparent}");
                        break;
                }
                ui->Enemy3HPBar->setAlignment(Qt::AlignCenter);
                ui->Enemy3HPBar->setMinimum(0);
                ui->Enemy3HPBar->setMaximum(tower->get_floors()[tower->get_current_floor_index()].get_enemy()[i]->get_HP_max());
                ui->Enemy3HPBar->setValue(tower->get_floors()[tower->get_current_floor_index()].get_enemy()[i]->HP);
                ui->Enemy3HPBar->setFormat(QString::fromStdString(std::to_string(tower->get_floors()[tower->get_current_floor_index()].get_enemy()[i]->HP) + "/" + std::to_string(tower->get_floors()[tower->get_current_floor_index()].get_enemy()[i]->get_HP_max())));
                ui->Enemy3MPBar->setAlignment(Qt::AlignCenter);
                ui->Enemy3MPBar->setMinimum(0);
                ui->Enemy3MPBar->setMaximum(tower->get_floors()[tower->get_current_floor_index()].get_enemy()[i]->get_MP_max());
                ui->Enemy3MPBar->setValue(tower->get_floors()[tower->get_current_floor_index()].get_enemy()[i]->MP);
                ui->Enemy3MPBar->setFormat(QString::fromStdString(std::to_string(tower->get_floors()[tower->get_current_floor_index()].get_enemy()[i]->MP) + "/" + std::to_string(tower->get_floors()[tower->get_current_floor_index()].get_enemy()[i]->get_MP_max())));
                ui->Enemy3ATK->setText(QString::number(tower->get_floors()[tower->get_current_floor_index()].get_enemy()[i]->ATK));
                ui->Enemy3DEF->setText(QString::number(tower->get_floors()[tower->get_current_floor_index()].get_enemy()[i]->DEF));
            }
        }
        else
        {
            if (i == 0)
            {
                ui->Enemy0->hide();
                ui->Enemy0HP->hide();
                ui->Enemy0HPBar->hide();
                ui->Enemy0MP->hide();
                ui->Enemy0MPBar->hide();
                ui->Enemy0ATK->hide();
                ui->Enemy0ATK_title->hide();
                ui->Enemy0DEF->hide();
                ui->Enemy0DEF_title->hide();
            }
            else if (i == 1)
            {
                ui->Enemy1->hide();
                ui->Enemy1HP->hide();
                ui->Enemy1HPBar->hide();
                ui->Enemy1MP->hide();
                ui->Enemy1MPBar->hide();
                ui->Enemy1ATK->hide();
                ui->Enemy1ATK_title->hide();
                ui->Enemy1DEF->hide();
                ui->Enemy1DEF_title->hide();
            }
            else if (i == 2)
            {
                ui->Enemy2->hide();
                ui->Enemy2HP->hide();
                ui->Enemy2HPBar->hide();
                ui->Enemy2MP->hide();
                ui->Enemy2MPBar->hide();
                ui->Enemy2ATK->hide();
                ui->Enemy2ATK_title->hide();
                ui->Enemy2DEF->hide();
                ui->Enemy2DEF_title->hide();
            }
            else if (i == 3)
            {
                ui->Enemy3->hide();
                ui->Enemy3HP->hide();
                ui->Enemy3HPBar->hide();
                ui->Enemy3MP->hide();
                ui->Enemy3MPBar->hide();
                ui->Enemy3ATK->hide();
                ui->Enemy3ATK_title->hide();
                ui->Enemy3DEF->hide();
                ui->Enemy3DEF_title->hide();
            }
        }
    }
    for (int i = tower->getNumOfEnemyinCurrentFloor(); i < 4; ++i)
    {
        if (i == 0)
        {
            ui->Enemy0->hide();
            ui->Enemy0HP->hide();
            ui->Enemy0HPBar->hide();
            ui->Enemy0MP->hide();
            ui->Enemy0MPBar->hide();
            ui->Enemy0ATK->hide();
            ui->Enemy0ATK_title->hide();
            ui->Enemy0DEF->hide();
            ui->Enemy0DEF_title->hide();
        }
        else if (i == 1)
        {
            ui->Enemy1->hide();
            ui->Enemy1HP->hide();
            ui->Enemy1HPBar->hide();
            ui->Enemy1MP->hide();
            ui->Enemy1MPBar->hide();
            ui->Enemy1ATK->hide();
            ui->Enemy1ATK_title->hide();
            ui->Enemy1DEF->hide();
            ui->Enemy1DEF_title->hide();
        }
        else if (i == 2)
        {
            ui->Enemy2->hide();
            ui->Enemy2HP->hide();
            ui->Enemy2HPBar->hide();
            ui->Enemy2MP->hide();
            ui->Enemy2MPBar->hide();
            ui->Enemy2ATK->hide();
            ui->Enemy2ATK_title->hide();
            ui->Enemy2DEF->hide();
            ui->Enemy2DEF_title->hide();
        }
        else if (i == 3)
        {
            ui->Enemy3->hide();
            ui->Enemy3HP->hide();
            ui->Enemy3HPBar->hide();
            ui->Enemy3MP->hide();
            ui->Enemy3MPBar->hide();
            ui->Enemy3ATK->hide();
            ui->Enemy3ATK_title->hide();
            ui->Enemy3DEF->hide();
            ui->Enemy3DEF_title->hide();
        }
    }

    ui->dialogpages->setCurrentIndex(0);
    action_type = -1; // 0 = skill, 1 =item
    row_select = -1;
    choose = 0; // 0 = off, 1 = on
    swap1_select = -1;
    swap2_select = -1;
}

// destructor of BattleWindow Object, deallocates the memory of the ui and music
BattleWindow::~BattleWindow()
{
    delete ui;
    delete player;
    delete playlist;
    delete click;
}

// When AddAction button is clicked, a choice between Skills and Item is shown
void BattleWindow::on_AddAction_clicked()
{
    click->play();
    action_type = -1;
    row_select = -1;
    choose = 0;
    ui->dialogpages->setCurrentIndex(1);
    ui->AddAction->setStyleSheet("QPushButton{image: url(:/resources/images/Add Action_hover.png); background-color: transparent}"
                            "QPushButton::hover{image: url(:/resources/images/Add Action_hover.png); background-color: transparent}");
    ui->DeleteAction->setStyleSheet("QPushButton{image: url(:/resources/images/Delete Action.png); background-color: transparent}"
                            "QPushButton::hover{image: url(:/resources/images/Delete Action_hover.png); background-color: transparent}");
    ui->SwapAction->setStyleSheet("QPushButton{image: url(:/resources/images/Swap Action.png); background-color: transparent}"
                            "QPushButton::hover{image: url(:/resources/images/Swap Action_hover.png); background-color: transparent}");
    ui->EndRound->setStyleSheet("QPushButton{image: url(:/resources/images/End Round.png); background-color: transparent}"
                            "QPushButton::hover{image: url(:/resources/images/End Round_hover.png); background-color: transparent}");
    ui->Flee->setStyleSheet("QPushButton{image: url(:/resources/images/Flee.png); background-color: transparent}"
                            "QPushButton::hover{image: url(:/resources/images/Flee_hover.png); background-color: transparent}");
}

// When skill is selected, a list of skills will show up for the player to choose
void BattleWindow::on_Skill_clicked()
{
    click->play();
    action_type = 0;
    ui->actionlist->clear();
    ui->dialogpages->setCurrentIndex(2);
    for (int i = 0; tower->player->learned_skill[i] != nullptr; ++i)
    {
        ui->actionlist->addItem(QString::fromStdString(tower->player->learned_skill[i]->get_name()+"\t")+QString::number(tower->player->learned_skill[i]->get_AP_cost())+QString::fromStdString("\t"+tower->player->learned_skill[i]->get_description()));
    }
}

// When item is selected, a list of items will show up for the player to choose
void BattleWindow::on_Items_clicked()
{
    click->play();
    action_type = 1;
    ui->actionlist->clear();
    ui->dialogpages->setCurrentIndex(2);
    for (int i = 0; i < (int)(tower->player->get_inventory().size()); ++i)
    {
        if (tower->player->get_inventory()[i]->get_isUsable())
        {
            ui->actionlist->addItem(QString::fromStdString(tower->player->get_inventory()[i]->get_item_name()+"\t")+QString::number(use_item_APcost)+QString::fromStdString("\t"+tower->player->get_inventory()[i]->get_item_description()));
        }
    }
}

// when Use is clicked, the code determines if a skill or item is chosen, and runs the code to use the skill or item
void BattleWindow::on_use_clicked()
{
    if (action_type == 0)
    {
        int skill_index = (row_select+1);
        Action* action;
        if (skill_index == 0) return;

        switch(static_cast<Skill::skill_type>(skill_index)) {
            case Skill::skill_type::DEFENCE:
                action = new Action(tower->player, tower->player, new Defence(tower->player));
                break;
            case Skill::skill_type::STRENGTHEN:
                action = new Action(tower->player, tower->player, new Strengthen(tower->player));
                break;
            case Skill::skill_type::BLESSING:
                action = new Action(tower->player, tower->player, new Blessing(tower->player));
                break;
            case Skill::skill_type::GREATER_DEFENCE:
                action = new Action(tower->player, tower->player, new Greater_defence(tower->player));
                break;
            case Skill::skill_type::GREATER_STRENGTHEN:
                action = new Action(tower->player, tower->player, new Greater_strengthen(tower->player));
                break;
            default:
                action = nullptr;
                click->play();
                choose = 1;
                ui->dialogpages->setCurrentIndex(3);
                break;
        }
        if (action != nullptr)
        {
            click->play();
            if (tower->player->battle->get_current_round()->add_action(action))
            {
                ui->totalactions->clear();
                action_type = -1;
                row_select = -1;
                choose = 0;
                ui->totalactions->addItem(QString::fromStdString(tower->player->battle->get_current_round()->view_action()));
                ui->AddAction->setStyleSheet("QPushButton{image: url(:/resources/images/Add Action.png); background-color: transparent}"
                                        "QPushButton::hover{image: url(:/resources/images/Add Action_hover.png); background-color: transparent}");
                ui->dialogpages->setCurrentIndex(0);
                refresh();
            }
            else
            {
                ui->BattleDialog_list->clear();
                if (tower->player->AP < action->get_action_APcost())
                {
                    ui->BattleDialog_list->addItem("You do not have enough AP.");
                }
                if (tower->player->MP < action->get_action_MPcost()) {
                    ui->BattleDialog_list->addItem("You do not have enough MP.");
                }
                ui->BattleDialog->show();
            }
        }
    }
    else if (action_type == 1)
    {
        Action* action;
        Item* item = nullptr;
        int item_index = row_select;
        for (int i = 0; i < (int)(tower->player->get_inventory().size()); ++i)
        {
            if (i == item_index)
            {
                if (!(tower->player->get_inventory()[i]->get_isUsable()))
                {
                    ++item_index;
                }
                else
                {
                    item = tower->player->get_inventory()[item_index];
                }
            }
        }
        if (item != nullptr)
        {
            click->play();
            action = new Action(tower->player, tower->player, item);
            if (tower->player->battle->get_current_round()->add_action(action))
            {
                tower->player->remove_item(item);
                ui->totalactions->clear();
                action_type = -1;
                row_select = -1;
                choose = 0;
                ui->totalactions->addItem(QString::fromStdString(tower->player->battle->get_current_round()->view_action()));
                ui->AddAction->setStyleSheet("QPushButton{image: url(:/resources/images/Add Action.png); background-color: transparent}"
                                        "QPushButton::hover{image: url(:/resources/images/Add Action_hover.png); background-color: transparent}");
                ui->dialogpages->setCurrentIndex(0);
                refresh();
            }
            else if (tower->player->AP < action->get_action_APcost())
            {
                ui->BattleDialog_list->clear();
                ui->BattleDialog_list->addItem("You do not have enough AP.");
                ui->BattleDialog->show();
                return;
            }
            else
            {
                ui->BattleDialog_list->clear();
                ui->BattleDialog_list->addItem("The item already exists in action list.");
                ui->BattleDialog->show();
                return;
            }
        }
    }
}

// the row selected on the action list by the user is saved to row_select
void BattleWindow::on_actionlist_currentRowChanged(int currentRow)
{
    row_select = currentRow;
}

// the code receives the character (e.g. enemy or player) to perform the action on
void BattleWindow::choose_character(int enemy)
{
    if (action_type == 0)
    {
        int skill_index = (row_select+1);
        Character* receiver;
        Action* action;
        int receiver_index = enemy;
        if (skill_index == 0 || receiver_index == 0)
        {
            return;
        }
        switch (receiver_index)
        {
            case 1:
                receiver = tower->player;
                break;
            default:
                if (tower->get_floors()[tower->get_current_floor_index()].get_enemy()[receiver_index-2]->HP == 0)
                {
                    return;
                }
                else
                {
                    receiver = tower->get_floors()[tower->get_current_floor_index()].get_enemy()[receiver_index-2];
                    break;
                }
        }
        switch(static_cast<Skill::skill_type>(skill_index))
        {
            case Skill::skill_type::REGULAR_ATTACK:
                action = new Action(tower->player, receiver, new Regular_attack);
                break;
            case Skill::skill_type::SHARP_ATTACK:
                action = new Action(tower->player, receiver, new Sharp_attack);
                break;
            case Skill::skill_type::ULTIMATE_STRIKE:
                action = new Action(tower->player, receiver, new Ultimate_strike);
                break;
            case Skill::skill_type::BLOOD_SUCKING:
                action = new Action(tower->player, receiver, new Blood_sucking);
                break;
            default:
                action = nullptr;
                ui->totalactions->clear();
                action_type = -1;
                row_select = -1;
                choose = 0;
                ui->totalactions->addItem(QString::fromStdString(tower->player->battle->get_current_round()->view_action()));
                ui->AddAction->setStyleSheet("QPushButton{image: url(:/resources/images/Add Action.png); background-color: transparent}"
                                        "QPushButton::hover{image: url(:/resources/images/Add Action_hover.png); background-color: transparent}");
                ui->dialogpages->setCurrentIndex(0);
                break;
        }
        if (action != nullptr)
        {
            click->play();
            if (tower->player->battle->get_current_round()->add_action(action))
            {
                ui->totalactions->clear();
                action_type = -1;
                row_select = -1;
                choose = 0;
                ui->totalactions->addItem(QString::fromStdString(tower->player->battle->get_current_round()->view_action()));
                ui->AddAction->setStyleSheet("QPushButton{image: url(:/resources/images/Add Action.png); background-color: transparent}"
                                        "QPushButton::hover{image: url(:/resources/images/Add Action_hover.png); background-color: transparent}");
                ui->dialogpages->setCurrentIndex(0);
                refresh();
            }
            else
            {
                ui->BattleDialog_list->clear();
                if (tower->player->AP < action->get_action_APcost())
                {
                    ui->BattleDialog_list->addItem("You do not have enough AP.");
                }
                if (tower->player->MP < action->get_action_MPcost()) {
                    ui->BattleDialog_list->addItem("You do not have enough MP.");
                }
                ui->BattleDialog->show();
            }
        }
    }
}

// player chooses the perform action on Enemy0
void BattleWindow::on_Enemy0_clicked()
{
    if (choose == 1)
    {
        choose_character(2);
    }
}

// player chooses the perform action on Enemy1
void BattleWindow::on_Enemy1_clicked()
{
    if (choose == 1)
    {
        choose_character(3);
    }
}

// player chooses the perform action on Enemy2
void BattleWindow::on_Enemy2_clicked()
{
    if (choose == 1)
    {
        choose_character(4);
    }
}

// player chooses the perform action on Enemy3
void BattleWindow::on_Enemy3_clicked()
{
    if (choose == 1)
    {
        choose_character(5);
    }
}

// player chooses the perform action on themselves
void BattleWindow::on_Player_pic_clicked()
{
    if (choose == 1)
    {
        choose_character(1);
    }
}

// the BattleWindow returns from the AddAction screen to the main BattleScreen
void BattleWindow::on_back_clicked()
{
    click->play();
    ui->actionlist->clear();
    action_type = -1;
    row_select = -1;
    choose = 0;
    ui->dialogpages->setCurrentIndex(1);
}

// When DeleteAction button is clicked, a choice of all added action is listed
void BattleWindow::on_DeleteAction_clicked()
{
    click->play();
    action_type = -1;
    row_select = -1;
    choose = 0;
    ui->delete_list->clear();
    ui->dialogpages->setCurrentIndex(4);
    ui->AddAction->setStyleSheet("QPushButton{image: url(:/resources/images/Add Action.png); background-color: transparent}"
                            "QPushButton::hover{image: url(:/resources/images/Add Action_hover.png); background-color: transparent}");
    ui->DeleteAction->setStyleSheet("QPushButton{image: url(:/resources/images/Delete Action_hover.png); background-color: transparent}"
                            "QPushButton::hover{image: url(:/resources/images/Delete Action_hover.png); background-color: transparent}");
    ui->SwapAction->setStyleSheet("QPushButton{image: url(:/resources/images/Swap Action.png); background-color: transparent}"
                            "QPushButton::hover{image: url(:/resources/images/Swap Action_hover.png); background-color: transparent}");
    ui->EndRound->setStyleSheet("QPushButton{image: url(:/resources/images/End Round.png); background-color: transparent}"
                            "QPushButton::hover{image: url(:/resources/images/End Round_hover.png); background-color: transparent}");
    ui->Flee->setStyleSheet("QPushButton{image: url(:/resources/images/Flee.png); background-color: transparent}"
                            "QPushButton::hover{image: url(:/resources/images/Flee_hover.png); background-color: transparent}");
    for (int i = 0; i < (int)(tower->player->battle->get_current_round()->get_action_list().size()); ++i)
    {
        ui->delete_list->addItem(QString::fromStdString((std::to_string(i+1) + ". " + (tower->player->battle->get_current_round()->get_action_list())[i]->get_action_name())));
    }
}

// the row selected on the delete list by the user is saved to row_select
void BattleWindow::on_delete_list_currentRowChanged(int currentRow)
{
    row_select = currentRow;
}

// If an action is selected, the action will be deleted from the list of added actions
void BattleWindow::on_delete_action_clicked()
{
    int input = row_select;
    if (input < 0)
    {
        return;
    }
    if (tower->player->battle->get_current_round()->get_action_list()[input]->get_type() == Action::type::USE_AN_ITEM)
    {
        Item* item;
        switch (tower->player->battle->get_current_round()->get_action_list()[input]->get_item()->get_item_type())
        {
            case Item::item_type::HP_POTION:
                item = new HPpotion;
                break;
            case Item::item_type::MP_POTION:
                item = new MPpotion;
                break;
            default:
                item = nullptr;
                break;
        }
        if (item != nullptr)
        {
            tower->player->add_item_to_inventory(item);
        }
    }
    tower->player->battle->get_current_round()->delete_action(tower->player->battle->get_current_round()->get_action_list()[input]);
    ui->totalactions->clear();
    click->play();
    action_type = -1;
    row_select = -1;
    choose = 0;
    ui->totalactions->addItem(QString::fromStdString(tower->player->battle->get_current_round()->view_action()));
    ui->DeleteAction->setStyleSheet("QPushButton{image: url(:/resources/images/Delete Action.png); background-color: transparent}"
                            "QPushButton::hover{image: url(:/resources/images/Delete Action_hover.png); background-color: transparent}");
    ui->dialogpages->setCurrentIndex(0);
    refresh();
}

// the BattleWindow returns from the DeleteAction screen to the main BattleWindow
void BattleWindow::on_back_delete_clicked()
{
    ui->totalactions->clear();
    click->play();
    action_type = -1;
    row_select = -1;
    choose = 0;
    ui->totalactions->addItem(QString::fromStdString(tower->player->battle->get_current_round()->view_action()));
    ui->DeleteAction->setStyleSheet("QPushButton{image: url(:/resources/images/Delete Action.png); background-color: transparent}"
                            "QPushButton::hover{image: url(:/resources/images/Delete Action_hover.png); background-color: transparent}");
    ui->dialogpages->setCurrentIndex(0);
    refresh();
}

// When SwapAction button is clicked, a choice of all added action is listed
void BattleWindow::on_SwapAction_clicked()
{
    click->play();
    action_type = -1;
    row_select = -1;
    choose = 0;
    ui->swap1_list->clear();
    ui->swap2_list->clear();
    ui->dialogpages->setCurrentIndex(5);
    ui->AddAction->setStyleSheet("QPushButton{image: url(:/resources/images/Add Action.png); background-color: transparent}"
                            "QPushButton::hover{image: url(:/resources/images/Add Action_hover.png); background-color: transparent}");
    ui->DeleteAction->setStyleSheet("QPushButton{image: url(:/resources/images/Delete Action.png); background-color: transparent}"
                            "QPushButton::hover{image: url(:/resources/images/Delete Action_hover.png); background-color: transparent}");
    ui->SwapAction->setStyleSheet("QPushButton{image: url(:/resources/images/Swap Action_hover.png); background-color: transparent}"
                            "QPushButton::hover{image: url(:/resources/images/Swap Action_hover.png); background-color: transparent}");
    ui->EndRound->setStyleSheet("QPushButton{image: url(:/resources/images/End Round.png); background-color: transparent}"
                            "QPushButton::hover{image: url(:/resources/images/End Round_hover.png); background-color: transparent}");
    ui->Flee->setStyleSheet("QPushButton{image: url(:/resources/images/Flee.png); background-color: transparent}"
                            "QPushButton::hover{image: url(:/resources/images/Flee_hover.png); background-color: transparent}");
    for (int i = 0; i < (int)(tower->player->battle->get_current_round()->get_action_list().size()); ++i)
    {
        ui->swap1_list->addItem(QString::fromStdString((std::to_string(i+1) + ". " + (tower->player->battle->get_current_round()->get_action_list())[i]->get_action_name())));
        ui->swap2_list->addItem(QString::fromStdString((std::to_string(i+1) + ". " + (tower->player->battle->get_current_round()->get_action_list())[i]->get_action_name())));
    }
}

// the row selected on the first swap list by the user is saved to row_select
void BattleWindow::on_swap1_list_currentRowChanged(int currentRow)
{
    swap1_select = currentRow;
}

// the row selected on the second swap list by the user is saved to row_select
void BattleWindow::on_swap2_list_currentRowChanged(int currentRow)
{
    swap2_select = currentRow;
}

// the code swaps the order of the two actions
void BattleWindow::on_swap_clicked()
{
    if (swap1_select < 0 || swap2_select < 0)
    {
        return;
    }
    if (swap1_select == swap2_select)
    {
        return;
    }
    if (tower->player->battle->get_current_round()->swap_action(tower->player->battle->get_current_round()->get_action_list()[swap1_select],
        tower->player->battle->get_current_round()->get_action_list()[swap2_select]))
    {
       ui->totalactions->clear();
       click->play();
       action_type = -1;
       row_select = -1;
       choose = 0;
       swap1_select = -1;
       swap2_select = -1;
       ui->totalactions->addItem(QString::fromStdString(tower->player->battle->get_current_round()->view_action()));
       ui->SwapAction->setStyleSheet("QPushButton{image: url(:/resources/images/Swap Action.png); background-color: transparent}"
                               "QPushButton::hover{image: url(:/resources/images/Swap Action_hover.png); background-color: transparent}");
       ui->dialogpages->setCurrentIndex(0);
       refresh();
    }
}

// the BattleWindow returns from the SwapAction screen to the main BattleScreen
void BattleWindow::on_back_swap_clicked()
{
    ui->totalactions->clear();
    click->play();
    action_type = -1;
    row_select = -1;
    choose = 0;
    swap1_select = -1;
    swap2_select = -1;
    ui->totalactions->addItem(QString::fromStdString(tower->player->battle->get_current_round()->view_action()));
    ui->SwapAction->setStyleSheet("QPushButton{image: url(:/resources/images/Swap Action.png); background-color: transparent}"
                            "QPushButton::hover{image: url(:/resources/images/Swap Action_hover.png); background-color: transparent}");
    ui->dialogpages->setCurrentIndex(0);
    refresh();
}

// moves on to the next round by using all the actions and refreshing the statuses
void BattleWindow::on_EndRound_clicked()
{
    click->play();
    ui->BattleDialog_list->clear();

    freopen("output.txt", "w", stdout);
    tower->player->battle->go_to_next_round();

    if (tower->getBattleRound()%2 == 1) {
        tower->enemyRound();
    }

    QFile inputFile("output.txt");
    if (inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFile);
       while (!in.atEnd())
       {
          ui->BattleDialog_list->addItem(in.readLine());
       }
       inputFile.close();
    }

    if (tower->player->battle->get_isPlayerLose()) {
        ui->BattleDialog_list->addItem("You lose!");
        tower->end_battle();
        if (tower->level_up()) {
            ui->BattleDialog_list->addItem("Level up!");
        }
        end = 1;
        ui->BattleDialog->show();
    }
    else if (tower->player->battle->get_isPlayerWin()) {
        ui->BattleDialog_list->addItem("You Win!");
        ui->BattleDialog_list->addItem("You gained $" + QString::fromStdString(std::to_string(tower->get_money_gain())) + " and " + QString::fromStdString(std::to_string(tower->get_EXP_gain())) + " EXP.");
        tower->player_reward();
        ui->BattleDialog_list->addItem(QString::fromStdString(tower->HPpotion_drop()) + QString::fromStdString(tower->MPpotion_drop()) + QString::fromStdString(tower->LeatherArmor_drop()) + QString::fromStdString(tower->IronArmor_drop()) + QString::fromStdString(tower->DiamondArmor_drop()));
        tower->end_battle();
        if (tower->level_up()) {
            ui->BattleDialog_list->addItem("Level up!");
        }
        end = 1;
        ui->BattleDialog->show();
    }
    else if (!tower->isPlayerLose() && !tower->isPlayerWin())
    {
        ui->totalactions->clear();
        action_type = -1;
        row_select = -1;
        choose = 0;
        swap1_select = -1;
        swap2_select = -1;
        ui->BattleDialog->show();
    }
}

// Closes the msg dialog that is shown after each round or notification
void BattleWindow::on_BattleDialog_next_clicked()
{
    click->play();
    ui->BattleDialog->hide();
    if (end == 1)
    {
        player->stop();
        FloorWindow *m = new FloorWindow{tower, nullptr};
        m->setAttribute(Qt::WA_DeleteOnClose);
        m->show();
        close();
    }
    else
    {
        refresh();
    }
}

// Escape from the Battle and returns to the FloorWindow
void BattleWindow::on_Flee_clicked()
{
    click->play();
    tower->player->battle->setIsPlayerLose(true);
    ui->BattleDialog_list->clear();
    ui->BattleDialog_list->addItem("You lose!");
    tower->end_battle();
    if (tower->level_up()) {
        ui->BattleDialog_list->addItem("Level up!");
    }
    end = 1;
    ui->BattleDialog->show();
}


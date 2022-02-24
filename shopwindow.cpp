#include "shopwindow.h"
#include "ui_shopwindow.h"
#include "floorwindow.h"
#include "Tower.h"

#include <QString>
#include <QFileDialog>

int HPpotion_price = 50;
int MPpotion_price = 50;
int LeatherArmor_price = 250;
int IronArmor_price = 500;
int DiamondArmor_price = 1000;
int RecoverHPMP_price = 100;
extern int EXPforLevel2;
extern int EXPforLevel3;
extern int EXPforLevel4;
extern int EXPforLevel5;
int HPpotion_worth = HPpotion_price/2;
int MPpotion_worth = MPpotion_price/2;
int LeatherArmor_worth = LeatherArmor_price/2;
int IronArmor_worth = IronArmor_price/2;
int DiamondArmor_worth = DiamondArmor_price/2;

// call constructor to create a ShopWindow Object by passing the Tower object to the constructor
ShopWindow::ShopWindow(Tower* tower, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ShopWindow),
    tower(tower)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::MSWindowsFixedSizeDialogHint);
    this->statusBar()->setSizeGripEnabled(false);
    QPixmap bkgnd(":/resources/images/shopbackground.png");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);

    this->setWindowTitle("Shop");

    playlist = new QMediaPlaylist();
    playlist->addMedia(QUrl("qrc:/resources/sounds/shop.mp3"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);

    player = new QMediaPlayer();
    player->setPlaylist(playlist);
    player->play();

    click = new QMediaPlayer();
    click->setMedia(QUrl("qrc:/resources/sounds/click.mp3"));

    ui->select->setStyleSheet("QPushButton{image: url(:/resources/images/Select.png); background-color: transparent}"
                                 "QPushButton::hover{image: url(:/resources/images/Select_hover.png); background-color: transparent}");
    ui->back->setStyleSheet("QPushButton{image: url(:/resources/images/Back.png); background-color: transparent}"
                                 "QPushButton::hover{image: url(:/resources/images/Back_hover.png); background-color: transparent}");
    ui->next_floor->setStyleSheet("QPushButton{image: url(:/resources/images/Next Floor.png); background-color: transparent}"
                                 "QPushButton::hover{image: url(:/resources/images/Next Floor_hover.png); background-color: transparent}");
    ui->next_floor_page->hide();

    choice = -2;
    selling = 0;
    ui->dialog->setText("Welcome to the Adventurer's Shop! Feel free to purchase anything you need!");
    ui->shoplist->clear();
    ui->shoplist->addItem("Buy a HP potion ($" + QString::number(HPpotion_price) + ")");
    ui->shoplist->addItem("Buy a MP potion ($" + QString::number(MPpotion_price) + ")");
    ui->shoplist->addItem("Buy a Leather Armor ($" + QString::number(LeatherArmor_price) + ")");
    ui->shoplist->addItem("Buy a Iron Armor ($" + QString::number(IronArmor_price) + ")");
    ui->shoplist->addItem("Buy a Diamond Armor ($" + QString::number(DiamondArmor_price) + ")");
    ui->shoplist->addItem("Recover all HP and MP ($" + QString::number(RecoverHPMP_price) + ")");
    ui->shoplist->addItem("Sell items");
    ui->shoplist->addItem("Leave the shop");

    refresh();
}

// destructor of ShopWindow Object, deallocates the memory of the ui and music
ShopWindow::~ShopWindow()
{
    delete ui;
    delete player;
    delete playlist;
    delete click;
}

// refreshes the statuses of the player after selecting an action on the shop list
void ShopWindow::refresh()
{
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
}

// closes the shop and creates a FloorWindow Object to allow the player to progress
void ShopWindow::on_next_floor_clicked()
{
    click->play();
    player->stop();
    FloorWindow *b = new FloorWindow{tower, nullptr};
    b->setAttribute(Qt::WA_DeleteOnClose);
    b->show();
    close();
}

// the row selected on the shop list by the user is saved to choice
void ShopWindow::on_shoplist_currentRowChanged(int currentRow)
{
    choice = currentRow;
}

// runs the option chosen by the player
void ShopWindow::on_select_clicked()
{
    if (selling == 0)
    {
        Item* purchase;
        switch(static_cast<ShopWindow::ShopOption>(choice+2))
        {
            case ShopOption::VIEW_INFO:
                click->play();
                ui->dialog->setText(QString::fromStdString(tower->player->info()));
                refresh();
                break;
            case ShopOption::HP_POTION:
                click->play();
                if (tower->player->money < HPpotion_price) {
                    ui->dialog->setText("Sorry! You do not have enough budget.");
                    refresh();
                    break;
                }
                else {
                    purchase = new HPpotion;
                    tower->player->add_item_to_inventory(purchase);
                    tower->player->money -= HPpotion_price;
                    refresh();
                    ui->dialog->setText("Thank you for your purchase!");
                    break;
                }
            case ShopOption::MP_POTION:
                click->play();
                if (tower->player->money < MPpotion_price) {
                    ui->dialog->setText("Sorry! You do not have enough budget.");
                    refresh();
                    break;
                }
                else {
                    purchase = new MPpotion;
                    tower->player->add_item_to_inventory(purchase);
                    tower->player->money -= MPpotion_price;
                    refresh();
                    ui->dialog->setText("Thank you for your purchase!");
                    break;
                }
            case ShopOption::LEATHER_ARMOR:
                click->play();
                if (tower->player->money < LeatherArmor_price) {
                    ui->dialog->setText("Sorry! You do not have enough budget.");
                    refresh();
                    break;
                }
                else {
                    purchase = new LeatherArmor;
                    tower->player->add_item_to_inventory(purchase);
                    tower->player->money -= LeatherArmor_price;
                    refresh();
                    ui->dialog->setText("Thank you for your purchase!");
                    break;
                }
            case ShopOption::IRON_ARMOR:
                click->play();
                if (tower->player->money < IronArmor_price) {
                    ui->dialog->setText("Sorry! You do not have enough budget.");
                    refresh();
                    break;
                }
                else {
                    purchase = new IronArmor;
                    tower->player->add_item_to_inventory(purchase);
                    tower->player->money -= IronArmor_price;
                    refresh();
                    ui->dialog->setText("Thank you for your purchase!");
                    break;
                }
            case ShopOption::DIAMOND_ARMOR:
                click->play();
                if (tower->player->money < DiamondArmor_price) {
                    ui->dialog->setText("Sorry! You do not have enough budget.");
                    refresh();
                    break;
                }
                else {
                    purchase = new DiamondArmor;
                    tower->player->add_item_to_inventory(purchase);
                    tower->player->money -= DiamondArmor_price;
                    refresh();
                    ui->dialog->setText("Thank you for your purchase!");
                    break;
                }
            case ShopOption::RECOVER:
                click->play();
                if (tower->player->money < RecoverHPMP_price) {
                    ui->dialog->setText("Sorry! You do not have enough budget.");
                    refresh();
                    break;
                }
                else {
                    tower->player->HP = tower->player->get_HP_max();
                    tower->player->MP = tower->player->get_MP_max();
                    tower->player->money -= RecoverHPMP_price;
                    refresh();
                    ui->dialog->setText("HP and MP fully recovered.");
                    break;
                }
            case ShopOption::SELL:
                click->play();
                selling = 1;
                sell_items();
                break;
            case ShopOption::LEAVE:
                click->play();
                ui->dialog->setText("Thank you for visiting!");
                ui->next_floor_page->show();
        }
    }
    else if (selling == 1)
    {
        int index = choice;
        if (index == -1) return;
        Item* item = tower->player->get_inventory()[index];
        switch (item->get_item_type())
        {
            case Item::item_type::HP_POTION:
                tower->player->money += HPpotion_worth;
                break;
            case Item::item_type::MP_POTION:
                tower->player->money += MPpotion_worth;
                break;
            case Item::item_type::LEATHER_ARMOR:
                tower->player->money += LeatherArmor_worth;
                break;
            case Item::item_type::IRON_ARMOR:
                tower->player->money += IronArmor_worth;
                break;
            case Item::item_type::DIAMOND_ARMOR:
                tower->player->money += DiamondArmor_worth;
                break;
        }
        click->play();
        tower->player->remove_item(item);
        refresh();
        sell_items();
        ui->dialog->setText("Pleasure doing business with you!");
    }
}

// lists out the player's inventory for the player to choose
void ShopWindow::sell_items() const
{
    ui->dialog->setText("Please select an item to sell.");
    ui->shoplist->clear();
    QString temp;
    for (int i = 0; i < (int)(tower->player->get_inventory().size()); ++i)
    {
        if (tower->player->get_inventory()[i]->get_item_type() == Item::item_type::HP_POTION)
        {
            temp = "($" + QString::number(HPpotion_worth) + ")";
        }
        else if (tower->player->get_inventory()[i]->get_item_type() == Item::item_type::MP_POTION)
        {
            temp = "($" + QString::number(MPpotion_worth) + ")";
        }
        else if (tower->player->get_inventory()[i]->get_item_type() == Item::item_type::LEATHER_ARMOR)
        {
            temp = "($" + QString::number(LeatherArmor_worth) + ")";
        }
        else if (tower->player->get_inventory()[i]->get_item_type() == Item::item_type::IRON_ARMOR)
        {
            temp = "($" + QString::number(IronArmor_worth) + ")";
        }
        else if (tower->player->get_inventory()[i]->get_item_type() == Item::item_type::DIAMOND_ARMOR)
        {
            temp = "($" + QString::number(DiamondArmor_worth) + ")";
        }
        ui->shoplist->addItem(QString::fromStdString(tower->player->get_inventory()[i]->get_item_name()) + "\t" + temp);
    }
}

// the choices for the shop returns to the main list from the selling list
void ShopWindow::on_back_clicked()
{
    click->play();
    choice = -2;
    selling = 0;
    ui->dialog->setText("Welcome to the Adventurer's Shop! Feel free to purchase anything you need!");
    ui->shoplist->clear();
    ui->shoplist->addItem("Buy a HP potion ($" + QString::number(HPpotion_price) + ")");
    ui->shoplist->addItem("Buy a MP potion ($" + QString::number(MPpotion_price) + ")");
    ui->shoplist->addItem("Buy a Leather Armor ($" + QString::number(LeatherArmor_price) + ")");
    ui->shoplist->addItem("Buy a Iron Armor ($" + QString::number(IronArmor_price) + ")");
    ui->shoplist->addItem("Buy a Diamond Armor ($" + QString::number(DiamondArmor_price) + ")");
    ui->shoplist->addItem("Recover all HP and MP ($" + QString::number(RecoverHPMP_price) + ")");
    ui->shoplist->addItem("Sell items");
    ui->shoplist->addItem("Leave the shop");

    refresh();
}


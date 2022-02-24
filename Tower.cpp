#include <fstream>
#include <random>
#include "Tower.h"
#include "Battle.h"
#include "QRandomGenerator"

extern std::string HPpotion_name;
extern std::string MPpotion_name;
extern std::string LeatherArmor_name;
extern std::string IronArmor_name;
extern std::string DiamondArmor_name;

// generates and returns a random number
int random_number(const int& begin, const int& end) {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(begin,end);
    return dist6(rng);
}

// save function of the tower
void Tower::save(const std::string &filename) const{
    ofstream ofs(filename);
    ofs << static_cast<int>(difficulty) << endl << tower_size << endl << current_floor << endl;
    for (int i = 0; i < tower_size; ++i) {
        ofs << floors[i].get_number_of_enemy() << endl;
        for (int j = 0; j < floors[i].get_number_of_enemy(); ++j) {
            ofs << static_cast<int>(floors[i].get_enemy()[j]->get_type()) << endl;
            ofs << floors[i].get_enemy()[j]->HP << endl;
            ofs << floors[i].get_enemy()[j]->MP << endl;
        }
    }
    ofs << player->HP << endl;
    ofs << player->get_HP_max() << endl;
    ofs << player->MP << endl;
    ofs << player->get_MP_max() << endl;
    ofs << player->get_AP_max() << endl;
    ofs << player->ATK << endl;
    ofs << player->DEF << endl;
    ofs << player->money << endl;
    ofs << player->EXP << endl;
    ofs << player->get_level() << endl;
    if (player->get_equipped_item() != nullptr) {ofs << static_cast<int>(player->get_equipped_item()->get_item_type()) << endl;}
    else {ofs << 0 << endl;}
    ofs << player->get_inventory().size() << endl;
    for (int i = 0; i < player->get_inventory().size(); ++i) {
        ofs << static_cast<int>(player->get_inventory()[i]->get_item_type()) << endl;
    }
}

// checks if the battle can start on the current floor
bool Tower::start_battle() const {
    if (floors[current_floor].isClear()) {return false;}
    player->battle = new Battle(player, floors[current_floor].get_enemy());
    return true;
}

// checks if the player has won
bool Tower::isPlayerWin() const {
    return player->battle->get_isPlayerWin();
}

// checks if the player has lost
bool Tower::isPlayerLose() const {
    return player->battle->get_isPlayerLose();
}

// returns the current round number
int Tower::getBattleRound() const {
    return player->battle->get_round_counter();
}

// executes the enemy's turn
void Tower::enemyRound() const {
    player->battle->generate_enemy_actionlist();
    player->battle->go_to_next_round();
}

// returns the amount of money gained by the player after finishing the floor
int Tower::get_money_gain() const {
    return floors[current_floor].get_money_gain();
}

// returns the amount of EXP gained by the player after finishing the floor
int Tower::get_EXP_gain() const {
    if (player->get_level() != 5) {return floors[current_floor].get_EXP_gain();}
    else {return 0;}
}

// adds the money and EXP gain to the player
void Tower::player_reward() const {
    player->money += get_money_gain();
    player->EXP += get_EXP_gain();
}

// generates a HPpotion drop
std::string Tower::HPpotion_drop() const {
    std::string s = "";
    int HPpotion_drop = QRandomGenerator::global()->bounded(4); // Chances for HPpotion to drop: 25%
    bool WeakEnemyExist = false;
    for (int i = 0; i < floors[current_floor].get_number_of_enemy(); ++i) {
        if (floors[current_floor].get_enemy()[i]->get_type() == Enemy::enemy_type::WeakEnemy) {
            WeakEnemyExist = true;
            break;
        }
    }
    if (HPpotion_drop == 0 && WeakEnemyExist) {
        s += "You obtained a " + HPpotion_name + "!" + "\n";
        Item* item = new HPpotion;
        player->add_item_to_inventory(item);
    }
    return s;
}

// generates a MPpotion drop
std::string Tower::MPpotion_drop() const {
    std::string s = "";
    int MPpotion_drop = QRandomGenerator::global()->bounded(4);// Chances for MPpotion to drop: 25%
    bool WeakEnemyExist = false;
    for (int i = 0; i < floors[current_floor].get_number_of_enemy(); ++i) {
        if (floors[current_floor].get_enemy()[i]->get_type() == Enemy::enemy_type::WeakEnemy) {
            WeakEnemyExist = true;
            break;
        }
    }
    if (MPpotion_drop == 0 && WeakEnemyExist) {
        s += "You obtained a " + MPpotion_name + "!" + "\n";
        Item* item = new MPpotion;
        player->add_item_to_inventory(item);
    }
    return s;
}

// generates a LeatherArmor drop
std::string Tower::LeatherArmor_drop() const {  // Chances for Leather Armor to drop: 10%
    std::string s = "";
    int LeatherArmor_drop = QRandomGenerator::global()->bounded(10);
    bool WeakEnemyExist = false;
    for (int i = 0; i < floors[current_floor].get_number_of_enemy(); ++i) {
        if (floors[current_floor].get_enemy()[i]->get_type() == Enemy::enemy_type::WeakEnemy) {
            WeakEnemyExist = true;
            break;
        }
    }
    if (LeatherArmor_drop == 0 && WeakEnemyExist) {
        s += "You obtained a " + LeatherArmor_name + "!" + "\n";
        Item* item = new LeatherArmor;
        player->add_item_to_inventory(item);
    }
    return s;
}

// generates a IronArmor drop
std::string Tower::IronArmor_drop() const { // Chances for Iron Armor to drop: 10%
    std::string s = "";
    int IronArmor_drop = QRandomGenerator::global()->bounded(10);
    bool StrongEnemyExist = false;
    for (int i = 0; i < floors[current_floor].get_number_of_enemy(); ++i) {
        if (floors[current_floor].get_enemy()[i]->get_type() == Enemy::enemy_type::StrongEnemy) {
            StrongEnemyExist = true;
            break;
        }
    }
    if (IronArmor_drop == 0 && StrongEnemyExist) {
        s += "You obtained a " + IronArmor_name + "!" + "\n";
        Item* item = new IronArmor;
        player->add_item_to_inventory(item);
    }
    return s;
}

// generates a DiamondArmor drop
std::string Tower::DiamondArmor_drop() const { // Chances for Diamond Armor to drop: 5%
    std::string s = "";
    int DiamondArmor_drop = QRandomGenerator::global()->bounded(20);
    bool BossExist = false;
    for (int i = 0; i < floors[current_floor].get_number_of_enemy(); ++i) {
        if (floors[current_floor].get_enemy()[i]->get_type() == Enemy::enemy_type::Boss) {
            BossExist = true;
        }
    }
    if (DiamondArmor_drop == 0 && BossExist) {
        s += "You obtained a " + DiamondArmor_name + "!" + "\n";
        Item* item = new DiamondArmor;
        player->add_item_to_inventory(item);
    }
    return s;
}

// ends the battle
void Tower::end_battle() const{
    player->AP = player->get_AP_max();
    delete player->battle;
    player->battle = nullptr;
}

// call constructor to create a Tower Object by passing the difficulty and the size (new Tower)
Tower::Tower(Tower::Difficulty difficulty, const int& size) : difficulty(difficulty) , tower_size(size), player(new Player(*this)) {
    current_floor = 0;
    floors.resize(size);
    switch(difficulty) {
        case Tower::Difficulty::EASY:
            for (int i = 0; i < tower_size; ++i) {
                int number_of_enemy = QRandomGenerator::global()->bounded(1, 4);
                Enemy** temp = new Enemy*[number_of_enemy];
                for (int j = 0; j < number_of_enemy; ++j) {
                    temp[j] = new WeakEnemy;
                }
                Floor* floor = new Floor(temp, number_of_enemy);
                floors[i] = *floor;
            }
            break;
        case Tower::Difficulty::NORMAL:
            for (int i = 0; i < tower_size; ++i) {
                int number_of_enemy = QRandomGenerator::global()->bounded(1, 4);
                Enemy** temp = new Enemy*[number_of_enemy];
                for (int j = 0; j < number_of_enemy; ++j) {
                    if (i < (tower_size-1)*0.75) {
                        temp[j] = new WeakEnemy;
                    }
                    if (i >= (tower_size-1)*0.75) {
                        int enemy_type = QRandomGenerator::global()->bounded(1, 3);
                        if (enemy_type == 1) temp[j] = new WeakEnemy;
                        if (enemy_type == 2) temp[j] = new StrongEnemy;
                    }
                }
                Floor* floor = new Floor(temp, number_of_enemy);
                floors[i] = *floor;
            }
            break;
        case Tower::Difficulty::HARD:
            for (int i = 0; i < tower_size; ++i) {
                if (i == tower_size -1) {
                    Enemy** temp = new Enemy*[1];
                    temp[0] = new Boss;
                    floors.push_back(Floor(temp, 1));
                    break;
                }
                int number_of_enemy = QRandomGenerator::global()->bounded(1, 5);
                Enemy** temp = new Enemy*[number_of_enemy];
                for (int j = 0; j < number_of_enemy; ++j) {
                    if (i < (tower_size-1)*0.5) {
                        temp[j] = new WeakEnemy;
                    }
                    if (i >= (tower_size-1)*0.5) {
                        int enemy_type = QRandomGenerator::global()->bounded(1, 3);
                        if (enemy_type == 1) temp[j] = new WeakEnemy;
                        if (enemy_type == 2) temp[j] = new StrongEnemy;
                    }
                }
                Floor* floor = new Floor(temp, number_of_enemy);
                floors[i] = *floor;
            }
            break;
    }
}

// checks if the player has leveled up
bool Tower::level_up() {
    return player->level_up();
}

// checks the number of enemy on the current floor
int Tower::getNumOfEnemyinCurrentFloor() const {
    return floors[current_floor].get_number_of_enemy();
}

// returns the values called by the code
std::vector<Floor> Tower::get_floors() const {return floors;}
int Tower::get_tower_size() const {return tower_size;}
int Tower::get_current_floor_index() const {return current_floor;}

// moves to the next floor
bool Tower::move_to_next_floor() {
    if (!floors[current_floor].isClear()) {return false;}
    if (current_floor+1 == floors.size()) {return false;}
    current_floor++;
    return true;
}

// call constructor to create a Tower Object by passing the filename to the constructor (load Tower)
Tower::Tower(const std::string& filename) {
    ifstream ifs;
    std::string line;
    ifs.open(filename);
    if(!ifs.is_open()) {
      perror("Error. Cannot open the file given.");
      exit(EXIT_FAILURE);
   }
    int temp;
    ifs >> temp >> tower_size >> current_floor;
    difficulty = static_cast<Tower::Difficulty>(temp);
    floors.resize(tower_size);
    for (int i = 0; i < tower_size; ++i) { // handling every floor
        int number_of_enemies;
        ifs >> number_of_enemies;
        Enemy** enemy = new Enemy*[number_of_enemies];
        for (int j = 0; j < number_of_enemies; ++j) { // handling every enemy
            int enemy_type_int;
            ifs >> enemy_type_int;
            Enemy::enemy_type Enemytype = static_cast<Enemy::enemy_type>(enemy_type_int);
            int HP, MP;
            ifs >> HP >> MP;
            switch (Enemytype) {
                case Enemy::enemy_type::WeakEnemy: enemy[j] = new WeakEnemy(HP, MP); break;
                case Enemy::enemy_type::StrongEnemy: enemy[j] = new StrongEnemy(HP, MP); break;
                case Enemy::enemy_type::Boss: enemy[j] = new Boss(HP, MP); break;
            }
        }
        Floor* floor = new Floor(enemy, number_of_enemies);
        floors[i] = *floor;
    }
    int HP, HP_max, MP, MP_max, AP_max, ATK, DEF, money, EXP, level;
    ifs >> HP >> HP_max >> MP >> MP_max >> AP_max >> ATK >> DEF >> money >> EXP >> level;
    int equipment;
    Item* equipped_item;
    ifs >> equipment;
    switch (static_cast<Item::item_type>(equipment)) {
        case Item::item_type::LEATHER_ARMOR:
            equipped_item = new LeatherArmor;
            break;
        case Item::item_type::IRON_ARMOR:
            equipped_item = new IronArmor;
            break;
        case Item::item_type::DIAMOND_ARMOR:
            equipped_item = new DiamondArmor;
            break;
        default:
            equipped_item = nullptr;
            break;
    }
    int inventory_size;
    ifs >> inventory_size;
    std::vector<Item*> inventory(inventory_size);
    for (int i = 0; i < inventory_size; ++i) {
        int inventory_item;
        ifs >> inventory_item;
        switch (static_cast<Item::item_type>(inventory_item)) {
            case Item::item_type::HP_POTION:
                inventory[i] = new HPpotion;
                break;
            case Item::item_type::MP_POTION:
                inventory[i] = new MPpotion;
                break;
            case Item::item_type::LEATHER_ARMOR:
                inventory[i] = new LeatherArmor;
                break;
            case Item::item_type::IRON_ARMOR:
                inventory[i] = new IronArmor;
                break;
            case Item::item_type::DIAMOND_ARMOR:
                inventory[i] = new DiamondArmor;
                break;
        }
    }
    player = new Player(*this, HP, HP_max, MP, MP_max, AP_max, ATK, DEF, money, EXP, level, equipped_item, inventory);
}

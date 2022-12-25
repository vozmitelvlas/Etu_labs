#include "Save_Load_Player.h"
#include "iostream"

void SavePlayer::save_data_player(Player* player){

    file_input.open(filepath, std::ios_base::out | std::ios_base::trunc);

    if(!file_input.is_open()){
        throw FileExp("Could not open file [" + filepath + "] for save state");
    }

    
    file_input << player->get_hp() << '\n';
    file_input << player->get_cache() << '\n';
    file_input << player->get_armor() << '\n';
    file_input << player->get_x() << '\n';
    file_input << player->get_y() << '\n';

    file_input << '$' << '\n';
    file_input.close();
    

}

Player* SavePlayer::load_data_player(Player* player){
    if(check_hash(filepath) == -1){
        throw LoadExp("File [" + filepath + "] was changed!");
    }

    file_output.open(filepath, std::fstream::in);
    if(!file_output.is_open()){
        throw FileExp("Could not open file [" + filepath + "] for save state");
    }

    int hp, cache, armor, x, y;
    file_output >> hp;
    file_output >> cache;
    file_output >> armor;
    file_output >> x;
    file_output >> y;

    if( hp <= 0 || hp > 200 || cache < 0 || armor < 0 || x < 0 || y < 0){
        throw LoadExp("Incorrect values in file, file was changed!");
    }

    player->set_hp(hp);
    player->set_cache(cache);
    player->set_armor(armor);
    player->set_coords(x, y);

    file_output.close();
    
    return player;
}
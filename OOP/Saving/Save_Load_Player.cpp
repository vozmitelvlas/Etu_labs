#include "Save_Load_Player.h"
#include "iostream"

void SavePlayer::save_data_player(Player* player){

    file_input.open(filepath, std::ios_base::out | std::ios_base::trunc);

    if(!file_input.is_open()){
        throw FileExp("Could not open file [ " + filepath + " ] for save state");
    }

    try{
        file_input << player->get_hp() << '\n';
        file_input << player->get_cache() << '\n';
        file_input << player->get_armor() << '\n';
        file_input << player->get_x() << '\n';
        file_input << player->get_y() << '\n';

        file_input.close();
        make_hash(filepath);
    }
    catch(SaveExp& se){
        throw SaveExp(se.what());        
    }
    
}

Player* SavePlayer::load_data_player(Player* player){
    if(check_hash(filepath) == -1){
        throw FileExp("File [ " + filepath + " ] was changed!");
    }

    file_output.open(filepath, std::fstream::in);
    if(!file_output.is_open()){
        throw FileExp("Could not open file [ " + filepath + " ] for save state");
    }

    try{

        int hp, cache, armor, x, y;
        file_output >> hp;
        file_output >> cache;
        file_output >> armor;
        file_output >> x;
        file_output >> y;

        player->set_hp(hp);
        player->set_cache(cache);
        player->set_armor(armor);
        player->set_coords(x, y);

        file_output.close();
    }
    catch(LoadExp& le){
        throw LoadExp(le.what());        
    }
    
    return player;
}
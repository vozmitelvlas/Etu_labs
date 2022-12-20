#include "Save_Load_Field.h"

void SaveField::save_data_field(Field *field){

    file_input.open(filepath, std::ios_base::out | std::ios_base::trunc);
    
    if(!file_input.is_open()){
        throw FileExp("Could not open file [ " + filepath + " ] for save state");
    }

    try{
        file_input << field->get_length() << '\n';
        file_input << field->get_height() << '\n';
        std::vector<std::vector<Cell>>* array = field->get_field();

        for(int i = 0; i < field->get_height(); i++){
            for(int j = 0; j < field->get_length(); j++){

                if((*array)[i][j].get_obj() == Cell::STANDARD){
                    file_input << "STANDARD ";
                }
                if((*array)[i][j].get_obj() == Cell::BLOCK){
                    file_input << "BLOCK ";
                }
                if((*array)[i][j].get_obj() == Cell::ENEMY){
                    file_input << "ENEMY ";
                }
                if((*array)[i][j].get_obj() == Cell::ARMOR){
                    file_input << "ARMOR ";
                }
                if((*array)[i][j].get_obj() == Cell::HP){
                    file_input << "HP ";
                }
                if((*array)[i][j].get_obj() == Cell::DMG){
                    file_input << "DMG ";
                }
                if((*array)[i][j].get_obj() == Cell::END){
                    file_input << "END ";
                }
            }

            file_input << std::endl;
        }

        file_input.close();
        make_hash(filepath);
    }

    catch(SaveExp& se){
        throw SaveExp(se.what());        
    }
    
}

PrintField* SaveField::load_data_field(Player* player,  InfoLog* log_out_info){
   
    if(check_hash(filepath) == -1){
        throw FileExp("File [ " + filepath + " ] was changed!");
    }

    file_output.open(filepath, std::fstream::in);
    if(!file_output.is_open()){
        throw FileExp("Could not open file [ " + filepath + " ] for save state");
    }

    try{
        int width, height;
        std::string cell;

        char buf;
        file_output >> width;
        file_output >> height;

        PrintField* field = new PrintField(height, width, log_out_info, player);
        CreateEvent builder(field, player);
        field->create_field();
        
        std::vector<std::vector<Cell>>* array = field->get_field();

        file_output >> cell;
        for(int i = 0; i < field->get_height(); i++){
            for(int j = 0; j < field->get_length(); j++){
                if(cell == "ENEMY"){
                    (*array)[i][j].set_players_events(builder.create_Event_Enemy());
                    (*array)[i][j].set_info(field->get_info());
                    (*array)[i][j].set_obj(Cell::ENEMY);
                }
                if(cell == "DMG"){
                    (*array)[i][j].set_players_events(builder.create_Event_Damage());
                    (*array)[i][j].set_info(field->get_info());
                    (*array)[i][j].set_obj(Cell::DMG);
                }
                if(cell == "ARMOR"){
                    (*array)[i][j].set_players_events(builder.create_Event_Arm());
                    (*array)[i][j].set_info(field->get_info());
                    (*array)[i][j].set_obj(Cell::ARMOR);
                }
                if(cell == "END"){
                    (*array)[i][j].set_players_events(builder.create_Event_Win());
                    (*array)[i][j].set_info(field->get_info());
                    (*array)[i][j].set_obj(Cell::END);
                }
                if(cell == "HP"){
                    (*array)[i][j].set_players_events(builder.create_Event_Hp());
                    (*array)[i][j].set_info(field->get_info());
                    (*array)[i][j].set_obj(Cell::HP);
                }
                if(cell == "BLOCK"){
                    (*array)[i][j].set_obj(Cell::BLOCK);
                }
                file_output >> cell;
                
            }
        }
        file_output.close();
        return field;
    }
    catch(LoadExp& le){
        throw LoadExp(le.what());        
    }
}
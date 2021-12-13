
#include "GameLogic.h"
#include <string>
#include <stdlib.h>
#include <vector>
#include <iostream>//DEBUG


move_status Figure::makeMove(Figure** table, std::string move){

};




King::King(figure_color color){
    King::isDead = 0;
    King::name = "King";
    King::color = color;
    King::FEN_name = (color == WHITE)? "K":"k"; 
};

move_status King::makeMove(Figure** table, std::string move){

};

Queen::Queen(figure_color color){
    Queen::isDead = 0;
    Queen::name = "Queen";
    Queen::color = color;
    Queen::FEN_name = (color == WHITE)? "Q":"q"; 
};

move_status Queen::makeMove(Figure** table, std::string move){

};

Bishop::Bishop(figure_color color){
    Bishop::isDead = 0;
    Bishop::name = "Bishop";
    Bishop::color = color;
    Bishop::FEN_name = (color == WHITE)? "B":"b"; 
};

move_status Bishop::makeMove(Figure** table, std::string move){

};

Knight::Knight(figure_color color){
    Knight::isDead = 0;
    Knight::name = "Knight";
    Knight::color = color;
    Knight::FEN_name = (color == WHITE)? "N":"n"; 
};

move_status Knight::makeMove(Figure** table, std::string move){

};

Rock::Rock(figure_color color){
    Rock::isDead = 0;
    Rock::name = "Rock";
    Rock::color = color;
    Rock::FEN_name = (color == WHITE)? "R":"r"; 
};


move_status Rock::makeMove(Figure** table, std::string move){

};

Pawn::Pawn(figure_color color){
    Pawn::isDead = 0;
    Pawn::name = "Pawn";
    Pawn::color = color;
    Pawn::FEN_name = (color == WHITE)? "P":"p"; 
};

move_status Pawn::makeMove(Figure** table, std::string move){

};


GameSession::GameSession(const std::string& id,const std::string& whitePlayerId,const  std::string& blackPlayerId,
const  std::string& FEN) : id(id), whitePlayerId(whitePlayerId), blackPlayerId(blackPlayerId){
    GameSession::FEN_parser(FEN);
};

void GameSession::create_error_response(return_after_move &result){
    result.moveStatus = MOVE_ERROR;
    result.table_fen = GameSession::get_FEN();
    result.move_from = -1;
    result.move_to = -1;
}

Figure* ChessTable::get_figure(int index){
    if ((index >= 0) && (index < BOARD_SIZE)){
        return ChessTable::table[index];
    }
    return NULL;
}

ChessTable::ChessTable(const ChessTable& mainTable){
    //копируем доску

    table = new Figure*[BOARD_SIZE];
    for(int i=0; i<BOARD_SIZE;i++){
        table[i] = mainTable.table[i];
    }

    Black_king_ind = mainTable.Black_king_ind;
    White_king_ind = mainTable.White_king_ind;
}
return_after_move GameSession::makeMove(std::string move,  const std::string& player_id){
    
    return_after_move result;
    //проверяем id
    if(( (GameSession::turn == WHITE) && (player_id != GameSession::whitePlayerId)) || ( (GameSession::turn == BLACK) && (player_id != GameSession::blackPlayerId))){
        GameSession::create_error_response(result);
        return result;
    }
    // определяем фигуру
    int from = str_to_index(move.at(0),move.at(1));
    int to = str_to_index(move.at(2),move.at(3));

    if ((table.get_figure(from) == NULL) || (to == -1) || (from == to)){ // если координаты не верны 
        GameSession::create_error_response(result);
        return result;
    }
    if(GameSession::turn != table.get_figure(from)->color){//ходит не тот цвет
        GameSession::create_error_response(result);
        return result;
    }
    // проверяем на ничью
    //std::cout<<"DRAW"<<std::endl;//DEBUG

    move_status move_result = GameSession::table.move_figure(from,to);

    if (move_result == MOVE_ERROR){ 
        GameSession::create_error_response(result);
        return result;
    }
    result.moveStatus = move_result;
    result.table_fen = GameSession::get_FEN();
    result.move_from = from;
    result.move_to = to;
    return result;
    //возвращаем данные
};



move_status ChessTable::is_legal(int from, int to){
    Figure* actor = ChessTable::table[from]; 
    figure_color enemy_color = (actor->color == WHITE)? BLACK:WHITE;
    coords coords_from = data_to_coords(from);
    coords coords_to = data_to_coords(to);
    move_status result = MOVE_ERROR;

    bool legality = false;
    bool frendly_fire = false;
    if(actor->name == "King"){
        if((actor->color == BLACK) && (from == 60) && ((to == 62)||(to == 57))){ //рокировка 
            if(ChessTable::check_cast(actor,enemy_color,coords_from,coords_to)){
                result = MOVE_CAST;
                return result;
            }
            
        }
        else if((actor->color == WHITE) && (from == 4) && ((to == 1)||(to == 6))){ //рокировка 
            if(ChessTable::check_cast(actor,enemy_color,coords_from,coords_to)){
                result = MOVE_CAST;
                return result;
            }
        }
        else if( (abs(coords_from.x - coords_to.x)<=1 ) && (abs(coords_from.y - coords_to.y)<=1 ) ){
            bool enemy_hit = ChessTable::get_hit_table(enemy_color,coords_to);//не попалали под шах?
            if(ChessTable::get_figure(to) != NULL){
                frendly_fire = (ChessTable::get_figure(to)->color) != enemy_color;
            }
            if ((!enemy_hit) && (!frendly_fire)){
                result = MOVE_OK;
            }
            return result;
        }
        
    }
    else if(actor->name == "Queen"){
        legality = ChessTable::Queen(actor->color,coords_from,coords_to);
        if(ChessTable::get_figure(to) != NULL){
                frendly_fire = (ChessTable::get_figure(to)->color) != enemy_color;
        }
        if ((legality) && (!frendly_fire)){
                result = MOVE_OK;
            }
        return result;
    }
    else if(actor->name == "Bishop"){
        legality = ChessTable::Bishop(actor->color,coords_from,coords_to);
        if(ChessTable::get_figure(to) != NULL){
                frendly_fire = (ChessTable::get_figure(to)->color) != enemy_color;
        }
        if ((legality) && (!frendly_fire)){
                result = MOVE_OK;
            }

        return result;
    }
    else if(actor->name == "Knight"){
        if(( (abs(coords_from.x - coords_to.x)==2 ) && (abs(coords_from.y - coords_to.y)==1 )  )||( (abs(coords_from.x - coords_to.x)==1 ) && (abs(coords_from.y - coords_to.y)==2 )  )){
            if(ChessTable::get_figure(to) != NULL){
                frendly_fire = (ChessTable::get_figure(to)->color) != enemy_color;
            }
            if ((!frendly_fire)){
                result = MOVE_OK;
            }

            return result;
        }
    }
    else if(actor->name == "Rock"){
        legality = ChessTable::Rock(actor->color, coords_from,coords_to);
        if(ChessTable::get_figure(to) != NULL){
                frendly_fire = (ChessTable::get_figure(to)->color) != enemy_color;
        }
        if ((legality) && (!frendly_fire)){
                result = MOVE_OK;
            }
        return result;
    }
    else if(actor->name == "Pawn"){
        legality = (((coords_from.x == coords_to.x)) && ((coords_to.y - coords_from.y)==actor->color));//обычный ход
        

        if((coords_from.x == coords_to.x)&&((coords_from.y == 1) || (coords_from.y == 6)))//начальный ход
        {
            legality = (abs(coords_to.y - coords_from.y)<3) && (ChessTable::get_figure(coords_to.x + (coords_to.y-1)*8) == NULL) && ((ChessTable::get_figure(coords_to.index) == NULL)); 
        }
        
        else if((abs(coords_from.x - coords_to.x)==1) && ((coords_to.y - coords_from.y)==actor->color))//сьесть
        {
            if ((ChessTable::check_en_passant(from,to)) && (!frendly_fire)){
                result = MOVE_ENPASSANT;
                return result;
            }
            if (ChessTable::get_figure(to)!=NULL){
            legality = (ChessTable::get_figure(to)->color == enemy_color);
            }
            
            
        }
        if(ChessTable::get_figure(to) != NULL){
                legality = false;
        }
        if ((legality)){
                result = MOVE_OK;
            }
            return result;
    
    }

    return result;
}
void ChessTable::kill_figure(int index){
    if (this->get_figure(index)!= NULL){
        if (this->get_figure(index)->color == WHITE){
            this->whiteDeadFigures += this->get_figure(index)->FEN_name;
        }
        else if (this->get_figure(index)->color == BLACK){
            this->blackDeadFigures += this->get_figure(index)->FEN_name;
        }

        delete this->get_figure(index);
        this->table[index] = NULL;
    }
}
void ChessTable::make_move(int from, int to){
    if(this->get_figure(to) == NULL){
        this->table[to] =this->table[from];
        this->table[from] = NULL;
    }
    else{
        this->kill_figure(to);
        this->table[to] =this->table[from];
        this->table[from] = NULL;
    }

}
move_status ChessTable::move_figure(int from, int to){
    //проверяем легальность хода
    figure_color color = ChessTable::get_figure(from)->color;
    figure_color enemy_color = (color == WHITE)? BLACK:WHITE;
    move_status result = ChessTable::is_legal(from,to);
    if(result == MOVE_ERROR){
        return MOVE_ERROR;
    }
    // проверяем состояние короля
    //проверяем, будет ли нам шах или мат( даже если нам)
    ChessTable tempTable(*this); // копия класса
    tempTable.make_move(from,to);
    coords king = data_to_coords(this->White_king_ind);
    bool cheked = tempTable.get_hit_table(enemy_color,king);
    
    if(cheked){
        return MOVE_ERROR;
    }
    //считываем последствия (убили, превратились, эн пассант, рокировка, не рокировка)
    
    this->make_move(from,to);//ходим
    return result;
    
}

GameSession::~GameSession(){

};


    std::string index_to_str(const int index){
    std::string coord = "";
    coord += index / 8 + 'A';
    coord += index % 8 + '1';
    return coord;
}
void ChessTable::set_enpassant(char letter,char number){ 
    int index = str_to_index(letter, number);
    if((index <49) && (index >40)){
        index -= 8;
        Pawn* cur = dynamic_cast<Pawn*>(table[index]);
        if (cur != NULL){
        cur ->enPassant = true;
        }
    }

    if((index <33) && (index >24)){
        index += 8;
        Pawn* cur = dynamic_cast<Pawn*>(table[index]);
        if (cur != NULL){
        cur ->enPassant = true;
        }
    }
}

bool ChessTable::Bishop(figure_color color, coords from, coords to){
    if(abs(from.x - to.x) != abs(from.y - to.y)){
        return false;
    }
    if (ChessTable::get_figure(to.index) != NULL){//отдельно проверим конечную клетку на легальность
        if (ChessTable::get_figure(to.index)->color == color){
            return false;
        }
    }
    int delta = abs(to.x-from.x);
    int dir_x = ((to.x-from.x)>0)? 1:-1;
    int dir_y = ((to.y-from.y)>0)? 1:-1;

    for(int i=1;i<delta;i++){
        if (ChessTable::get_figure((from.x+i*dir_x)+(from.y+i*dir_y)*8) != NULL){
                    return false;
                }
    }
    return true;
}

bool ChessTable::Rock(figure_color color, coords from, coords to){
    
    if( (from.x == to.x) && (from.y != to.y) && (from.y>=0)&& (from.y<8)&& (to.x>=0)&& (to.x<8)){
        if(from.y < to.y){
            for (int i = from.y+1;i<to.y;i++){
                if (ChessTable::get_figure(from.x+i*8) != NULL){
                    return false;
                }
            }
        }
        else if (from.y > to.y){
            for (int i = from.y-1;i>to.y;i--){
                if (ChessTable::get_figure(from.x+i*8) != NULL){
                    return false;
                }
            }    
        }
        if (ChessTable::get_figure(to.index) != NULL){//отдельно проверим конечную клетку на легальность
                if (ChessTable::get_figure(to.index)->color == color){
                    return false;
                }
            }
        return true;
        
    }
    else if(( (from.y == to.y) && (from.x != to.x)) && (from.y>=0)&& (from.y<8)&& (to.x>=0)&& (to.x<8)){
        if(from.x < to.x){
            for (int i = from.x+1;i<to.x;i++){
                if (ChessTable::get_figure(i+from.y*8) != NULL){
                    return false;
                }
            }
            if (ChessTable::get_figure(to.index) != NULL){//отдельно проверим конечную клетку на легальность
                if (ChessTable::get_figure(to.index)->color == color){
                    return false;
                }
            }
            return true;
        }
        else if (from.x > to.x){
            for (int i = from.x-1;i>to.x;i--){
                if (ChessTable::get_figure(i+from.y*8) != NULL){
                    return false;
                }
            }
            if (ChessTable::get_figure(to.index) != NULL){//отдельно проверим конечную клетку на легальность
                if (ChessTable::get_figure(to.index)->color == color){
                    return false;
                }
            }
            return true;
        }
        
        
    }

    return false;
}

bool ChessTable::Queen(figure_color color, coords from, coords to){
    bool result = ChessTable::Bishop(color,from,to)||ChessTable::Rock(color,from,to);
    return result;
}

bool ChessTable::check_cast(Figure* fig_actor,figure_color enemy, coords from, coords to ){
    King* actor = dynamic_cast<King*>(fig_actor);
    bool result = false;
    if (actor->color == BLACK){
        if((from.index == 60) && (to.index == 62)&&actor->cast_k){ //рокировка 
            coords empty_cell = data_to_coords(61); 
            result = (ChessTable::get_figure(61) == NULL) && (!ChessTable::get_hit_table(enemy,empty_cell))&&(!ChessTable::get_hit_table(enemy,to))&&(!ChessTable::get_hit_table(enemy,from));
            return result;
        }
        else if ((from.index == 60) && (to.index == 57)&&actor->cast_q){
            coords empty_cell_1 = data_to_coords(59); 
            coords empty_cell_2 = data_to_coords(58);
            result = (ChessTable::get_figure(59) == NULL) && (ChessTable::get_figure(58) == NULL)&&(!ChessTable::get_hit_table(enemy,empty_cell_2)) &&(!ChessTable::get_hit_table(enemy,empty_cell_1))&&(!ChessTable::get_hit_table(enemy,to))&&(!ChessTable::get_hit_table(enemy,from));
            return result;
        }
        
    }
    if (actor->color == BLACK){
        if((from.index == 4) && (to.index == 6)&&actor->cast_k){ //рокировка 
            coords empty_cell = data_to_coords(5); 
            result = (ChessTable::get_figure(5) == NULL) && (!ChessTable::get_hit_table(enemy,empty_cell))&&(!ChessTable::get_hit_table(enemy,to))&&(!ChessTable::get_hit_table(enemy,from));
            return result;
        }
        else if ((from.index == 4) && (to.index == 1)&&actor->cast_q){
            coords empty_cell_1 = data_to_coords(3); 
            coords empty_cell_2 = data_to_coords(2);
            result = (ChessTable::get_figure(3) == NULL) && (ChessTable::get_figure(2) == NULL)&&(!ChessTable::get_hit_table(enemy,empty_cell_2)) &&(!ChessTable::get_hit_table(enemy,empty_cell_1))&&(!ChessTable::get_hit_table(enemy,to))&&(!ChessTable::get_hit_table(enemy,from));
            return result;
        }
        
    }
    return result;
}

bool ChessTable::get_hit_table(figure_color color, coords to){
    bool result = false;
    

    for(int i=0;i<BOARD_SIZE;i++){
        Figure* actor = ChessTable::table[i];
        if (actor != NULL){
            if (actor->color == color){
                coords from = data_to_coords(i);
                if(actor->name == "King"){
                    result = (abs(from.x - to.x)<=1 ) && (abs(from.y - to.y)<=1 );
                }
                else if(actor->name == "Queen"){
                    result = ChessTable::Queen(color,from,to);
                }
                else if(actor->name == "Bishop"){
                    result = ChessTable::Bishop(color,from,to);
                }
                else if(actor->name == "Knight"){
                    result = (( (abs(from.x - to.x)==2 ) && (abs(from.y - to.y)==1 )  )||( (abs(from.x - to.x)==1 ) && (abs(from.y - to.y)==2 )  ));
                }
                else if(actor->name == "Rock"){
                    result = ChessTable::Rock(color,from,to);
                }
                else if(actor->name == "Pawn"){
                    result = ((to.y - from.y) == color) && (abs(to.x-from.x) == 1);
                }
                if(result){
                    return result;
                }
            }
        }
    }
    return result;
}
void GameSession::FEN_parser(const std::string FEN){ //TODO: добавить ошибки
    
    
    Figure** ttable = GameSession::table.get_table(); //temp_table
    bool err_flag = false;
    const char *data = FEN.c_str();
    int cursor = 56;//FEN нотация идёт от черных к белым, слева направо
    int data_cursor = 0;
    King* Black_king = NULL;
    King* White_king = NULL;

    while (data[data_cursor] != ' '){ //считываем нотацию доски
        switch (data[data_cursor])
        {
        case 'k':
            if (Black_king == NULL){
                Black_king = new King(BLACK);
                ttable[cursor] = Black_king;
                GameSession::table.Black_king_ind = cursor;
                cursor++;
                
            }
            break;
        case 'K':
            if (White_king == NULL){
                White_king = new King(WHITE);
                ttable[cursor] = White_king;
                GameSession::table.White_king_ind = cursor;
                cursor++;
            }
            
            break;

        case 'q':
            ttable[cursor] = new Queen(BLACK);
            cursor++;
            break;
        case 'Q':
            ttable[cursor] = new Queen(WHITE);
            cursor++;
            break;
        
        case 'r':
            ttable[cursor] = new Rock(BLACK);
            cursor++;
            break;
        case 'R':
            ttable[cursor] = new Rock(WHITE);
            cursor++;
            break;

        case 'b':
            ttable[cursor] = new Bishop(BLACK);
            cursor++;
            break;
        case 'B':
            ttable[cursor] = new Bishop(WHITE);
            cursor++;
            break;

        case 'n':
            ttable[cursor] = new Knight(BLACK);
            cursor++;
            break;
        case 'N':
            ttable[cursor] = new Knight(WHITE);
            cursor++;
            break;

        case 'p':
            ttable[cursor] = new Pawn(BLACK);
            cursor++;
            break;
        case 'P':
            ttable[cursor] = new Pawn(WHITE);
            cursor++;
            break;
        case '1'...'8':
            cursor += data[data_cursor] - '0'; // преобразование из char  в int
            break;
        case '/':
            cursor -= 16;
            break;
        default:
            break;
        }
        data_cursor++;
    }

    data_cursor++;

    GameSession::turn= (data[data_cursor] == 'w') ? WHITE:BLACK;

    data_cursor++;
    data_cursor++;

    while (data[data_cursor] != ' '){ //считываем нотацию Рокировок
        switch (data[data_cursor])
        {
        case 'k':
            Black_king->cast_k = 1;
            break;
        case 'K':
            White_king->cast_k = 1;
            break;

        case 'q':
            Black_king->cast_q = 1;
            break;
        case 'Q':
            White_king->cast_q = 1;
            break;
        }
        data_cursor++;
    }

    data_cursor++;

    if (data[data_cursor] != '-'){
        
        while (data[data_cursor] != ' '){ //считываем нотацию взятий на проходе
        GameSession::table.set_enpassant(data[data_cursor],data[data_cursor+1]);
        data_cursor+=2;
    }
    }
    
};


std::string GameSession::get_FEN(){
    std::string FEN = "";
    Figure** ttable = GameSession::table.get_table(); //temp_table
    
    for(int i = 7; i>=0;i-- ){
        int null_counter = 0;
        for(int j = 0; j<8;j++){
            if (ttable[i*8 +j]!= NULL){
                if(null_counter>0){
                    FEN += null_counter +'0';
                    null_counter = 0;
                }
            FEN += ttable[i*8 + j]->FEN_name;
            }
            else{
                null_counter++;
            }
        };
        if(null_counter>0){
                    FEN += null_counter +'0';
                    null_counter = 0;
        }
        FEN+="/";
    };

    FEN += " ";

    King* White_King=dynamic_cast<King*>(ttable[GameSession::table.White_king_ind]);
    King* Black_King=dynamic_cast<King*>(ttable[GameSession::table.Black_king_ind]);
    FEN += (White_King ->cast_k)? "K":"";
    FEN += (White_King ->cast_q)? "Q":"";
    FEN += (Black_King ->cast_k)? "k":"";
    FEN += (Black_King ->cast_q)? "q":"";
    FEN += (!White_King ->cast_k && !White_King ->cast_q && !Black_King ->cast_k && !Black_King ->cast_q)? "-":"";

    FEN+=" ";
    bool nado = true; 
    
    for(int i = 0; i<8;i++){
        if(ttable[i+16] != NULL){
        if (dynamic_cast<Pawn*>(ttable[i+16])->enPassant){
            FEN +=index_to_str(8+i);
            nado = false;
        };
        if (dynamic_cast<Pawn*>(ttable[i+40])->enPassant){
            FEN +=index_to_str(48+i);
            nado = false;
        };
        }

    };
    if(nado){
        FEN += "-";
    };
    return FEN;
}



ChessTable::ChessTable(){
    ChessTable::table = new Figure*[64];
}

ChessTable::~ChessTable(){
    delete[] ChessTable::table;
}

Figure** ChessTable::get_table(){
    Figure** temp = ChessTable::table;
    return temp;
}

coords data_to_coords(std::string input){
    coords result;
    result.str = input;
    int index = (input.at(0) - 'A') + (input.at(1) - '0')*8; 
    if (!((index >= 0) && (index < BOARD_SIZE))){
        result.index = -1;
        result.x = -1;
        result.y = -1;
        return result;
    }
    result.index = index;
    result.x = index%8;
    result.y = index / 8;
    return result;
}

coords data_to_coords(int index){
    coords result;
    result.str = index_to_str(index);
    if (!((index >= 0) && (index < BOARD_SIZE))){
        result.index = -1;
        result.x = -1;
        result.y = -1;
        return result;
    }
    result.index = index;
    result.x = index%8;
    result.y = index / 8;
    return result;
}

coords data_to_coords(char letter, char number){
    coords result;
    int index = (letter - 'A') + (number - '1')*8;   
    result.str = letter + number;
    if (!((index >= 0) && (index < BOARD_SIZE))){
        result.index = -1;
        result.x = -1;
        result.y = -1;
        return result;
    }
    result.index = index;
    result.x = index%8;
    result.y = index / 8;
    return result;
}


int str_to_index(char letter, char number){
    //std::cout<<letter<<number<<std::endl;//DEBUG
    
    int index = (letter - 'A') + (number - '1')*8; 
    //std::cout<<index<<std::endl;//DEBUG
    if (((index >= 0) && (index < BOARD_SIZE))){
        return index;
    }
    return -1;
}



bool ChessTable::check_en_passant(int from, int to){
    Pawn* actor = dynamic_cast<Pawn*>(ChessTable::table[from]);
    if (actor->color == WHITE){
        if ((from/8)==4){
        Figure* enemy = ChessTable::table[to-8];
            if(enemy!=NULL){
                Pawn* enemy_pawn = dynamic_cast<Pawn*>(ChessTable::table[to-8]);
                if (enemy_pawn != NULL){
                    if (enemy_pawn->color == BLACK){
                        return enemy_pawn->enPassant;
                    }
                }
            }
        }
    }
    else if (actor->color == BLACK){
        if ((from/8)==3){
        Figure* enemy = ChessTable::table[to+8];
            if(enemy!=NULL){
                Pawn* enemy_pawn = dynamic_cast<Pawn*>(ChessTable::table[to+8]);
                if (enemy_pawn != NULL){
                    if (enemy_pawn->color == WHITE){
                        return enemy_pawn->enPassant;
                    }
                }
            }
        }
    }
    return false;
}
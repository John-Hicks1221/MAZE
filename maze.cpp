#include <iostream>
#include <conio.h>   // برای _getch و getch
#include <cstdlib>  // برای srand و system
#include <string>
#include <ctime>    // برای time
#include <windows.h>  // برای رنگ
using namespace std;

const int H = 51;
const int W = 76;

long int step = 0;
int HP = 3;
int last_player = 0;
int char_xind = 1, char_yind = 1;
int ghost1[2], ghost2[2], ghost3[2]; 

int player_xp[100] = {};
string player_names[100];

char MAP[H][W+1] = {
",-----------.-----------.--------------------.-----------.-----------------.",
"|           |           |                    |           |                 |",
"|  ,-----   |  ,-----.  |  .  ,-----------.  `--------   |  ,--.  .  ,--   |",
"|  |        |  |     |  |  |  |           |              |  |  |  |  |     |",
"|  |  ,-----'  |  .  |  |  `--\"--------.  \"  ,-----------'  \"  |  `--\"-----:",
"|  |  |        |  |  |  |              |     |                 |           |",
"|  |  |   --.  |  `--:  |  ,--------.  |  ,--:  ,--.-----------\"--------   |",
"|  |  |     |  |     |  |  |        |  |  |  |  |  |                       |",
"|  |  `-----'  |   --'  |  `-----   |  |  |  |  |  |  ,--------.--------.  |",
"|  |           |        |           |  |  |  |  |  |  |        |        |  |",
"|  `-----------\"-----.  `-----------:  |  \"  |  |  |  |  ,--   |  ,--.  |  |",
"|                    |              |  |     |  |  |  |  |     |  |  |  |  |",
"|  ,--------------.  :-----------.  |  `-----:  |  |  |  `-----'  \"  |  |  |",
"|  |              |  |           |  |        |  |  |  |              |  |  |",
"|  |  ,--------.  |  |  ,-----.  |  :-----   |  |  |  `--------------:  \"  |",
"|  |  |        |  |  |  |     |  |  |        |  |  |                 |     |",
"|  |  `-----   |  |  |  |  .  |  |  |  ,-----'  |  `--------------.  `-----:",
"|  |           |  |  |  |  |  |  |  |  |        |                 |        |",
"|  `-----------'  |  |  |  |  |  |  |  |  ,-----'  ,-----------.  :--.  .  |",
"|                 |  |  |  |  |  |  |  |  |        |           |  |  |  |  |",
":-----------------'  |  |  |  |  |  |  |  |  ,--.  |   -----.  |  |  |  |  |",
"|                    |  |  |  |  |  |  |  |  |  |  |        |  |  |  |  |  |",
"|  ,--------   ,-----:  |  |  \"  |  |  |  |  \"  |  |  ,-----'  |  \"  |  |  |",
"|  |           |     |  |  |     |  |  |  |     |  |  |        |     |  |  |",
"|  `-----------'  .  :--'  `-----'  \"  |  :--.  |  :--'  ,--   `--.  |  |  |",
"|                 |  |                 |  |  |  |  |     |        |  |  |  |",
"|  ,-----.--------'  |   -----.   --.  |  |  \"  |  |   --\"--------'  |  |  |",
"|  |     |           |        |     |  |  |     |  |                 |  |  |",
"|  `--   |  ,-----.  :--------\"-----\"--'  |   --:  :-----------------'  |  |",
"|        |  |     |  |                    |     |  |                    |  |",
":-----.  |  |   --:  |  ,-----------.-----\"-----'  |  ,--.--------------'  |",
"|     |  |  |     |  |  |           |              |  |  |                 |",
"|  .  |  |  |  .  \"  |  :--------   `--   ,-----.  |  |  |  ,-----------.--:",
"|  |  |  |  |  |     |  |                 |     |  |  |  |  |           |  |",
"|  `--:  |  `--\"-----'  \"  .  ,--   ,-----'   --'  |  |  \"  |  .   --.  \"  |",
"|     |  |                 |  |     |              |  |     |  |     |     |",
"|  .  |  :-----.-----------\"--\"-----\"--.   --------:  :--.  `--\"--.  `-----:",
"|  |  |  |     |                       |           |  |  |        |        |",
"|  |  |  |  .  |  ,-----------------.  `-----------'  |  `--.--.  |  ,--.  |",
"|  |  |  |  |  |  |                 |                 |     |  |  |  |  |  |",
"|  `--'  |  `--:  |  ,--------------\"--------------.--'  .  |  |  |  |  |  |",
"|        |     |  |  |                             |     |  |  |  |  |  |  |",
"|  ,-----'  .  |  |  |  ,--------.-----.  ,-----.  |  .  |  |  |  |  |  |  |",
"|  |        |  |  |  |  |        |     |  |     |  |  |  |  |  |  |  |  |  |",
"|  `--------:  |  |  |  |  .  .  `--   |  |   --'  |  |  |  \"  |  |  |  |  |",
"|           |  |  |  |  |  |  |        |  |        |  |  |     |  |  |  |  |",
":--------.  |  |  |  \"  `--'  :--------:  |   -----:  |  `-----'  |  \"  |  |",
"|        |  |  |  |           |        |  |        |  |           |     |  |",
"|   -----'  \"  |  `-----------'   --.  |  `--------'  `-----.   --\"-----'  |",
"|              |                    |  |                    |              |",
"`--------------\"--------------------'O `--------------------\"--------------'"
};

void check_xp(bool iswon){ //---------------------بررسی امتیاز--------------------
    if(iswon)
        player_xp[last_player] += 20;
    else if(!iswon){
        if(HP == 2)
            player_xp[last_player] = max(0, player_xp[last_player]-5);
        else if(HP == 1)
            player_xp[last_player] = max(0, player_xp[last_player]-5);
        else if(HP == 0)
            player_xp[last_player] = 0;
    }
}

void color(int num){ // ---------------------رنگ متن ها---------------------
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), num);
}

void displayMenu(){ // -----------------------چاپ منو------------------------
    system("cls");
    cout << "\n-------[MAZE-CORE]-------\n1. start new game\n2. game history\n3. exit\n";
}

bool won(){ // --------------------پیغام پیروزی-----------------
    system("cls");
    cout << "You Won!\npress any key to back to main menu...";
    char cmd = _getch();
    displayMenu();
    return true;
}

bool lost(){ //--------------------پیغام شکست-----------------
    system("cls");
    cout << "You Lost!\npress any key to back to main menu...";
    char cmd = _getch();
    displayMenu();
    return false;
}

void reset_g(){ // ---------------------ریست کردن موقعیت ها--------------------
    step = 0;
    char_xind = 1;
    char_yind = 1;
    player_names[last_player] = "0";
    last_player = 0;
}

void spawn(){ //---------------------اسپاون کردن روح ها--------------------
    srand(time(0));

    char_xind = 1;
    char_yind = 1;

    ghost1[0] = - 5 + rand() % 60;
    ghost1[1] = - 5 + rand() % 80;
    ghost2[0] = - 5 + rand() % 60;
    ghost2[1] = - 5 + rand() % 80;
    ghost3[0] = - 5 + rand() % 60;
    ghost3[1] = - 5 + rand() % 80;
}

void check_ghosts(){ //---------------------حرکت دادن روح ها--------------------
    if(step % 10 == 0){
      
        if(ghost1[0] < char_xind)
            ghost1[0] += 1;
        else if(ghost1[0] > char_xind)
            ghost1[0] -= 1;

        if(ghost1[1] < char_yind)
            ghost1[1] += 1;
        else if(ghost1[1] > char_yind)
            ghost1[1] -= 1;
        
//============================================
        if(ghost2[0] < char_xind)
            ghost2[0] += 1;
        else if(ghost2[0] > char_xind)
            ghost2[0] -= 1;

        if(ghost2[1] < char_yind)
            ghost2[1] += 1;
        else if(ghost2[1] > char_yind)
            ghost2[1] -= 1;
//============================================
        if(ghost3[0] < char_xind)
            ghost3[0] += 1;
        else if(ghost3[0] > char_xind)
            ghost3[0] -= 1;

        if(ghost3[1] < char_yind)
            ghost3[1] += 1;
        else if(ghost3[1] > char_yind)
            ghost3[1] -= 1;
    }
}

void show_map(int x, int y){  //---------------------چاپ ماز--------------------

    check_ghosts();

    cout << "Name : " << player_names[last_player] << "\t\tHP : " << HP << "\t\tXP : " << player_xp[last_player] << "\t\tSteps : " << step << "\n";

    for(int i = 0; i < H; i++){
        for(int j = 0; j < W; j++){
            if(i == x && j == y){
                color(14); //yellow
                cout << "@";
                color(7); //white
            }

            else{
                if(MAP[i][j] == 'O'){
                    color(2); //green
                    cout << MAP[i][j];
                    color(7);
                }

                else{
                    if((ghost1[0] == i && ghost1[1] == j) || (ghost2[0] == i && ghost2[1] == j) || (ghost3[0] == i && ghost3[1] == j)){
                        color(4); //red
                        cout << 'x';
                        color(7);
                    }
                    else{
                        color(3); //blue
                        cout << MAP[i][j];
                        color(7);
                    }

                }
                
            }
        }
        cout << "\n";
    }
}

void game(int p_idx) { //---------------------فرایند اجرای بازی-------------------

    while(true){
        system("cls");

        show_map(char_xind, char_yind);
        cout << "[MAZE-CORE] Move with W A S D  |  exit = 0" << endl;

        char cmd1 = _getch(); // برای اینکه ورودی کاربر را بدون نیاز به enter زدن بگیریم

        if (cmd1 == '0') {
            system("cls");
            cout << "are you sure about back to main menu?(y/n) : ";
            char cmd1 = _getch();
            if(cmd1 == 'y'){
                displayMenu();
                reset_g();
                break;
            }
            else
                continue;
        }

        else if (cmd1 == 'w' || cmd1 == 'W') {
            step++;

            if(MAP[char_xind-1][char_yind] == 'O'){
                check_xp(won());
                break;
            }

            else if(((char_xind-1 == ghost1[0] && char_yind == ghost1[1]) || (char_xind-1 == ghost2[0] && char_yind == ghost2[1]) || (char_xind-1 == ghost3[0] && char_yind == ghost3[1])) && MAP[char_xind][char_yind-1] == ' '){
                HP--;
                check_xp(lost());
                if(HP == 0){
                    break;
                }
                else
                    spawn();
            }

            if(MAP[char_xind-1][char_yind] == ' '){
                char_xind -= 1;
            }
        }

        else if (cmd1 == 's' || cmd1 == 'S') {
            step++;

            if(MAP[char_xind+1][char_yind] == 'O'){
                check_xp(won());
                break;
            }

            else if(((char_xind+1 == ghost1[0] && char_yind == ghost1[1]) || (char_xind+1 == ghost2[0] && char_yind == ghost2[1]) || (char_xind+1 == ghost3[0] && char_yind == ghost3[1])) && MAP[char_xind+1][char_yind] == ' '){
                HP--;
                check_xp(lost());
                if(HP == 0){
                    break;
                }
                else
                    spawn();
            }

            if(MAP[char_xind+1][char_yind] == ' '){
                char_xind += 1;
            }
        }

        else if (cmd1 == 'a' || cmd1 == 'A') {

            step++;

            if(MAP[char_xind][char_yind-1] == 'O'){
                check_xp(won());
                break;
            }
 
            else if(((char_xind == ghost1[0] && char_yind-1 == ghost1[1]) || (char_xind == ghost2[0] && char_yind-1 == ghost2[1]) || (char_xind == ghost3[0] && char_yind-1 == ghost3[1])) && MAP[char_xind][char_yind-1] == ' '){
                HP--;
                check_xp(lost());
                if(HP == 0){
                    break;
                }
                else
                    spawn();
            }

            if(MAP[char_xind][char_yind-1] == ' '){
                char_yind -= 1;
            }
        }

        else if (cmd1 == 'd' || cmd1 == 'D') {
            step++;

            if(MAP[char_xind][char_yind+1] == 'O'){
                check_xp(won());
                break;
            }

            else if(((char_xind == ghost1[0] && char_yind+1 == ghost1[1]) || (char_xind == ghost2[0] && char_yind+1 == ghost2[1]) || (char_xind == ghost3[0] && char_yind+1 == ghost3[1])) && MAP[char_xind][char_yind+1] == ' '){
                HP--;
                check_xp(lost());
                if(HP == 0){
                    break;
                }
                else
                    spawn();
            }

            if(MAP[char_xind][char_yind+1] == ' '){
                char_yind += 1;
            }
        }

        else{
            step++;
            continue;
        }
    }
}

void displayHistory() { //-----------------------چاپ تاریخچه------------------
    system("cls");
    cout << "[MAZE-CORE-GAMES-HISTORY]\n";

    for(int x = 1; x <= 100; x++)
        if(!player_names[x-1].empty() && player_names[x-1] != "0")
            cout << x << ". " << player_names[x-1] << "\t\tXP : " << player_xp[x-1] << "\n";
        else
            break;

    cout << "press any key to back to main menu...";

    char cmd = _getch();
    displayMenu();
}

int startGame_name(){ //-------------------گرفتن نام کاربر برای اجرای بازی-----------------

    system("cls"); // پاک کردن صفحه 
    string name;
    cout << "enter your name(0 to back menu) : ";
    getline(cin,name);

    if (name == "0"){
        displayMenu();
        return 101;
    }

    else{
    //========================ذخیره نام و اسپاون کاراکتر ها======================
        spawn();

        for (int i = 0; i < 100; i++) {
            if(player_names[i] == name) {
                return i;
            }
        }
        for (int i = 0; i < 100; i++) {
            if (player_names[i].empty()) {
                player_names[i] = name;
                return i;
            }
        }
    }
}

int main() { //-------------------------اجرای برنامه-----------------------

    displayMenu();

    while(true){

        char choice = _getch();

        if(choice == '1'){
            int ind = startGame_name();
            last_player = ind;
            if(ind == 101){
                displayMenu();
                continue;
            }
            else
                game(ind);
        }
        else if(choice == '2')
            displayHistory();

        else if(choice == '3'){
            system("cls");
            cout << "press 3 again if you sure about exit else press 0...\n";

            while(true){

                char cmd = _getch();

                    if(cmd == '3')
                        return 0;

                    else if(cmd == '0'){
                        displayMenu();
                        break;
                    }

                    else
                        cout << "[MAZE CORE] : invalid input(3.exit or 0.back)\n";
            }
        }

        else
            cout << "[MAZE CORE] : invalid input\n";
    }


    return 0;
}

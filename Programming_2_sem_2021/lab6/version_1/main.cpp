#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>

// сокращение цветов
// yellow - y
// orange - o
// green -  g
// red -    r
// blue -   b
// white -  w

// развёртка кубика по номерам    
//      0 1 2
//      3 4 5
//      6 7 8
//0 1 2|0 1 2|0 1 2|0 1 2
//3 4 5|3 4 5|3 4 5|3 4 5
//6 7 8|6 7 8|6 7 8|6 7 8
//      0 1 2
//      3 4 5
//      6 7 8

// развёртка кубика по цветам`
//      y y y
//      y y y
//      y y y
//r r r|g g g|o o o|b b b
//r r r|g g g|o o o|b b b
//r r r|g g g|o o o|b b b
//      w w w
//      w w w
//      w w w

//Инструкция для поворотов вручную 
//Повороты правой строны (*R)
//GR RR OR BR YR WR
//Повороты правой стороны обратно (*Rb)
//GRb RRb ORb BRb YRb WRb
//Повороты левой стороны (*L)
//GL RL OL BL YL WL
//Повороты левой стороны обратно (*Lb)
//GLb RLb OLb BLb YLb WLb
//Поворот Вверха (*U)   
//GU RU OU BU YU WU
//Поворот Вверха обратно (*Ub)   
//GUb RUb OUb BUb YUb WUb
// Поворот низа (*D)
//GD RD OD BD YD WD
// Поворот низа обратно (*Db)
//GDb RDb ODb BDb YDb WDb
// Поворот переда (*F)
//GF RF OF BF YF WF
// Поворот переда обратно (*Fb)
//GFb RFb OFb BFb YFb WFb
//поворот зада (*B)
//GB RB OB BB YB WB
//поворот зада обратно (*Bb)
//GBb RBb OBb BBb YBb WBb


class Cube {
public:
    Cube () {
        cube.assign(6, std::vector<char>(9));
        
        // заполнение кубика по стандарту
        for (int i = 0; i < 6; ++i) {
            std::vector <char> ch;
            ch = {'y', 'r', 'g', 'o', 'b', 'w'};
            for (int j = 0; j < 9; ++j) {
                cube[i][j] = ch[i];
            }
        }
        all_turns = "";
        count_turns = 0;
    }
    
    //показать кубик рубика
    void ShowCube () {
        for (int i = 0; i < 6; ++i) {
            for (int j = 0; j < 9; j += 3) {
                if ((i == 0) || (i == 5)){
                    std::cout << "      ";
                    std::cout << cube[i][j] << " " << cube[i][j + 1] << " " << cube[i][j + 2] << std::endl;
                }
                else if (i == 1) {
                    std::cout << cube[i][j] << " " << cube[i][j + 1] << " " << cube[i][j + 2] << "|";
                    std::cout << cube[i + 1][j] << " " << cube[i + 1][j + 1] << " " << cube[i + 1][j + 2] << "|";
                    std::cout << cube[i + 2][j] << " " << cube[i + 2][j + 1] << " " << cube[i + 2][j + 2] << "|";
                    std::cout << cube[i + 3][j] << " " << cube[i + 3][j + 1] << " " << cube[i + 3][j + 2] << std::endl;

                    std::cout << cube[i][j + 3]     << " " << cube[i][j + 4]     << " " << cube[i][j + 5]     << "|";
                    std::cout << cube[i + 1][j + 3] << " " << cube[i + 1][j + 4] << " " << cube[i + 1][j + 5] << "|";
                    std::cout << cube[i + 2][j + 3] << " " << cube[i + 2][j + 4] << " " << cube[i + 2][j + 5] << "|";
                    std::cout << cube[i + 3][j + 3] << " " << cube[i + 3][j + 4] << " " << cube[i + 3][j + 5] << std::endl;

                    std::cout << cube[i][j + 6]     << " " << cube[i][j + 7]     << " " << cube[i][j + 8]     << "|";
                    std::cout << cube[i + 1][j + 6] << " " << cube[i + 1][j + 7] << " " << cube[i + 1][j + 8] << "|";
                    std::cout << cube[i + 2][j + 6] << " " << cube[i + 2][j + 7] << " " << cube[i + 2][j + 8] << "|";
                    std::cout << cube[i + 3][j + 6] << " " << cube[i + 3][j + 7] << " " << cube[i + 3][j + 8] << std::endl;
                    i += 3;
                    break;
                }
            }
        }
    }

    //Сохранить кубик в файл
    void SaveCube () {
        std::ofstream fout ("cube.out");
        for (int i = 0; i < 6; ++i) {
            for (int j = 0; j < 9; j += 3) {
                if ((i == 0) || (i == 5)){
                    fout << "      ";
                    fout << cube[i][j] << " " << cube[i][j + 1] << " " << cube[i][j + 2] << std::endl;
                }
                else if (i == 1) {
                    fout << cube[i][j] << " " << cube[i][j + 1] << " " << cube[i][j + 2] << "|";
                    fout << cube[i + 1][j] << " " << cube[i + 1][j + 1] << " " << cube[i + 1][j + 2] << "|";
                    fout << cube[i + 2][j] << " " << cube[i + 2][j + 1] << " " << cube[i + 2][j + 2] << "|";
                    fout << cube[i + 3][j] << " " << cube[i + 3][j + 1] << " " << cube[i + 3][j + 2] << std::endl;

                    fout << cube[i][j + 3]     << " " << cube[i][j + 4]     << " " << cube[i][j + 5]     << "|";
                    fout << cube[i + 1][j + 3] << " " << cube[i + 1][j + 4] << " " << cube[i + 1][j + 5] << "|";
                    fout << cube[i + 2][j + 3] << " " << cube[i + 2][j + 4] << " " << cube[i + 2][j + 5] << "|";
                    fout << cube[i + 3][j + 3] << " " << cube[i + 3][j + 4] << " " << cube[i + 3][j + 5] << std::endl;

                    fout << cube[i][j + 6]     << " " << cube[i][j + 7]     << " " << cube[i][j + 8]     << "|";
                    fout << cube[i + 1][j + 6] << " " << cube[i + 1][j + 7] << " " << cube[i + 1][j + 8] << "|";
                    fout << cube[i + 2][j + 6] << " " << cube[i + 2][j + 7] << " " << cube[i + 2][j + 8] << "|";
                    fout << cube[i + 3][j + 6] << " " << cube[i + 3][j + 7] << " " << cube[i + 3][j + 8] << std::endl;

                    i += 3;
                    break;
                }
            }
        }
        std::cout << "Save cube" << std::endl;
        ShowCube();
        fout.close();
    }
    
    //Прочитать кубик из файла
    void ReadCube () {
        std::ifstream fin ("cube.in");
        char c;
        for (int i = 0; i < 6; ++i) {
            for (int j = 0; j < 9; ++j) {
                if ((i == 0) || (i == 5)) {
                    fin >> c; cube[i][j] = c;
                }
                else if (i == 1) {
                    fin >> c;   cube[i][j] = c;
                    fin >> c;   cube[i][j + 1] = c;
                    fin >> c;   cube[i][j + 2] = c;
                    fin >> c;
                    fin >> c;   cube[i + 1][j] = c;
                    fin >> c;   cube[i + 1][j + 1] = c;
                    fin >> c;   cube[i + 1][j + 2] = c;
                    fin >> c;
                    fin >> c;   cube[i + 2][j] = c;
                    fin >> c;   cube[i + 2][j + 1] = c;
                    fin >> c;   cube[i + 2][j + 2] = c;
                    fin >> c;
                    fin >> c;   cube[i + 3][j] = c;
                    fin >> c;   cube[i + 3][j + 1] = c;
                    fin >> c;   cube[i + 3][j + 2] = c;

                    fin >> c;   cube[i][j + 3] = c;
                    fin >> c;   cube[i][j + 4] = c;
                    fin >> c;   cube[i][j + 5] = c;
                    fin >> c;
                    fin >> c;   cube[i + 1][j + 3] = c;
                    fin >> c;   cube[i + 1][j + 4] = c;
                    fin >> c;   cube[i + 1][j + 5] = c;
                    fin >> c;
                    fin >> c;   cube[i + 2][j + 3] = c;
                    fin >> c;   cube[i + 2][j + 4] = c;
                    fin >> c;   cube[i + 2][j + 5] = c;
                    fin >> c;
                    fin >> c;   cube[i + 3][j + 3] = c;
                    fin >> c;   cube[i + 3][j + 4] = c;
                    fin >> c;   cube[i + 3][j + 5] = c;

                    fin >> c;   cube[i][j + 6] = c;
                    fin >> c;   cube[i][j + 7] = c;
                    fin >> c;   cube[i][j + 8] = c;
                    fin >> c;
                    fin >> c;   cube[i + 1][j + 6] = c;
                    fin >> c;   cube[i + 1][j + 7] = c;
                    fin >> c;   cube[i + 1][j + 8] = c;
                    fin >> c;
                    fin >> c;   cube[i + 2][j + 6] = c;
                    fin >> c;   cube[i + 2][j + 7] = c;
                    fin >> c;   cube[i + 2][j + 8] = c;
                    fin >> c;
                    fin >> c;   cube[i + 3][j + 6] = c;
                    fin >> c;   cube[i + 3][j + 7] = c;
                    fin >> c;   cube[i + 3][j + 8] = c;

                    i += 3;
                    break;
                }
            }
        }
        ShowCube();
        fin.close();
    }
    
    // проверка кубика на правильность
    bool CheckCube () {
        // проверка на коректность данных
        for (int i = 0; i < 6; ++i) {
            for (int j = 0; j < 9; ++j) {
                if ((cube[i][j] != 'y') && (cube[i][j] != 'o') && (cube[i][j] != 'g') && (cube[i][j] != 'r')  && (cube[i][j] != 'b') && (cube[i][j] != 'w')) {
                    return false;
                }
            }
        }

        std::vector <int> cub(6, 0);
        bool flag = true;
        
        // проверка рёбер
        std::vector<std::pair<char, char>> rebro;
        flag = flag & checkRebro(rebro, cube[0][1], cube[4][1], flag, cub); 
        flag = flag & checkRebro(rebro, cube[0][3], cube[1][1], flag, cub);
        flag = flag & checkRebro(rebro, cube[0][5], cube[3][1], flag, cub);
        flag = flag & checkRebro(rebro, cube[0][7], cube[2][1], flag, cub);
        
        flag = flag & checkRebro(rebro, cube[1][5], cube[2][3], flag, cub);
        flag = flag & checkRebro(rebro, cube[2][5], cube[3][3], flag, cub);
        flag = flag & checkRebro(rebro, cube[3][5], cube[4][3], flag, cub);
        flag = flag & checkRebro(rebro, cube[4][5], cube[1][3], flag, cub);
        
        flag = flag & checkRebro(rebro, cube[5][1], cube[2][7], flag, cub);
        flag = flag & checkRebro(rebro, cube[5][3], cube[1][7], flag, cub);
        flag = flag & checkRebro(rebro, cube[5][5], cube[3][7], flag, cub);
        flag = flag & checkRebro(rebro, cube[5][7], cube[4][7], flag, cub);
        
        
        std::vector <char> center;
        flag = flag & checkCenter(center, cube[0][4], flag, cub);
        flag = flag & checkCenter(center, cube[1][4], flag, cub);
        flag = flag & checkCenter(center, cube[2][4], flag, cub);
        flag = flag & checkCenter(center, cube[3][4], flag, cub);
        flag = flag & checkCenter(center, cube[4][4], flag, cub);
        flag = flag & checkCenter(center, cube[5][4], flag, cub);
        
        
        std::vector<std::pair<char, std::pair<char, char>>> corner;
        flag = flag & checkCorner(corner, cube[0][0], cube[1][0], cube[4][2], flag, cub);
        flag = flag & checkCorner(corner, cube[0][2], cube[3][2], cube[4][0], flag, cub);
        flag = flag & checkCorner(corner, cube[0][6], cube[1][2], cube[2][0], flag, cub);
        flag = flag & checkCorner(corner, cube[0][8], cube[2][2], cube[3][0], flag, cub);
        
        flag = flag & checkCorner(corner, cube[5][0], cube[1][8], cube[2][6], flag, cub);
        flag = flag & checkCorner(corner, cube[5][2], cube[2][8], cube[3][6], flag, cub);
        flag = flag & checkCorner(corner, cube[5][6], cube[1][6], cube[4][8], flag, cub);
        flag = flag & checkCorner(corner, cube[5][8], cube[3][8], cube[4][6], flag, cub);
        
        if (flag == false) {
            return flag;
        }
        else {
            for (int i = 0; i < 6; ++i) {
                if (cub[i] != 9) {
                    return false;
                }
            }
            return flag;
        }
    }
    
    // Поворот кубика рубика
    void SpinCube () {
        std::string spin;
        std::cout << "Введите команду вращения (0 - выход из программы): ";
        std::cin >> spin;
        while (true) {
            if (spin == "0") {
                break;
            }
            else if ((spin[0] == 'G') || (spin[0] == 'R') || (spin[0] == 'O') || (spin[0] == 'B') || (spin[0] == 'Y') || (spin[0] == 'W')) {
               if (spin[0] == 'G') {
                    if (spin[1] == 'R') {
                        if (spin[2] == 'b') {
                            GRb();
                        }
                        else {
                            GR();
                        }
                    }
                    else if (spin[1] == 'L') {
                        if (spin[2] == 'b') {
                            GLb();
                        }
                        else {
                            GL();
                        }
                    }
                    else if (spin[1] == 'U') {
                        if (spin[2] == 'b') {
                            GUb();
                        }
                        else {
                            GU();
                        }
                    }
                    else if (spin[1] == 'D') {
                        if (spin[2] == 'b') {
                            GDb();
                        }
                        else {
                            GD();
                        }
                    }
                    else if (spin[1] == 'F') {
                        if (spin[2] == 'b') {
                            GFb();
                        }
                        else {
                            GF();
                        }
                    }
                    else if (spin[1] == 'B') {
                        if (spin[2] == 'b') {
                            GBb();
                        }
                        else {
                            GB();
                        }
                    }
                    else {
                        std::cout << "Неверный поворот" << std::endl;
                    }
               }
               if (spin[0] == 'R') {
                    if (spin[1] == 'R') {
                        if (spin[2] == 'b') {
                            RRb();
                        }
                        else {
                            RR();
                        }
                    }
                    else if (spin[1] == 'L') {
                        if (spin[2] == 'b') {
                            RLb();
                        }
                        else {
                            RL();
                        }
                    }
                    else if (spin[1] == 'U') {
                        if (spin[2] == 'b') {
                            RUb();
                        }
                        else {
                            RU();
                        }
                    }
                    else if (spin[1] == 'D') {
                        if (spin[2] == 'b') {
                            RDb();
                        }
                        else {
                            RD();
                        }
                    }
                    else if (spin[1] == 'F') {
                        if (spin[2] == 'b') {
                            RFb();
                        }
                        else {
                            RF();
                        }
                    }
                    else if (spin[1] == 'B') {
                        if (spin[2] == 'b') {
                            RBb();
                        }
                        else {
                            RB();
                        }
                    }
                    else {
                        std::cout << "Неверный поворот" << std::endl;
                    }
               }
               if (spin[0] == 'O') {
                    if (spin[1] == 'R') {
                        if (spin[2] == 'b') {
                            ORb();
                        }
                        else {
                            OR();
                        }
                    }
                    else if (spin[1] == 'L') {
                        if (spin[2] == 'b') {
                            OLb();
                        }
                        else {
                            OL();
                        }
                    }
                    else if (spin[1] == 'U') {
                        if (spin[2] == 'b') {
                            OUb();
                        }
                        else {
                            OU();
                        }
                    }
                    else if (spin[1] == 'D') {
                        if (spin[2] == 'b') {
                            ODb();
                        }
                        else {
                            OD();
                        }
                    }
                    else if (spin[1] == 'F') {
                        if (spin[2] == 'b') {
                            OFb();
                        }
                        else {
                            OF();
                        }
                    }
                    else if (spin[1] == 'B') {
                        if (spin[2] == 'b') {
                            OBb();
                        }
                        else {
                            OB();
                        }
                    }
                    else {
                        std::cout << "Неверный поворот" << std::endl;
                    }
               }
               if (spin[0] == 'B') {
                    if (spin[1] == 'R') {
                        if (spin[2] == 'b') {
                            BRb();
                        }
                        else {
                            BR();
                        }
                    }
                    else if (spin[1] == 'L') {
                        if (spin[2] == 'b') {
                            BLb();
                        }
                        else {
                            BL();
                        }
                    }
                    else if (spin[1] == 'U') {
                        if (spin[2] == 'b') {
                            BUb();
                        }
                        else {
                            BU();
                        }
                    }
                    else if (spin[1] == 'D') {
                        if (spin[2] == 'b') {
                            BDb();
                        }
                        else {
                            BD();
                        }
                    }
                    else if (spin[1] == 'F') {
                        if (spin[2] == 'b') {
                            BFb();
                        }
                        else {
                            BF();
                        }
                    }
                    else if (spin[1] == 'B') {
                        if (spin[2] == 'b') {
                            BBb();
                        }
                        else {
                            BB();
                        }
                    }
                    else {
                        std::cout << "Неверный поворот" << std::endl;
                    }
               }
               if (spin[0] == 'Y') {
                    if (spin[1] == 'R') {
                        if (spin[2] == 'b') {
                            YRb();
                        }
                        else {
                            YR();
                        }
                    }
                    else if (spin[1] == 'L') {
                        if (spin[2] == 'b') {
                            YLb();
                        }
                        else {
                            YL();
                        }
                    }
                    else if (spin[1] == 'U') {
                        if (spin[2] == 'b') {
                            YUb();
                        }
                        else {
                            YU();
                        }
                    }
                    else if (spin[1] == 'D') {
                        if (spin[2] == 'b') {
                            YDb();
                        }
                        else {
                            YD();
                        }
                    }
                    else if (spin[1] == 'F') {
                        if (spin[2] == 'b') {
                            YFb();
                        }
                        else {
                            YF();
                        }
                    }
                    else if (spin[1] == 'B') {
                        if (spin[2] == 'b') {
                            YBb();
                        }
                        else {
                            YB();
                        }
                    }
                    else {
                        std::cout << "Неверный поворот" << std::endl;
                    }
               }
               if (spin[0] == 'W') {
                    if (spin[1] == 'R') {
                        if (spin[2] == 'b') {
                            WRb();
                        }
                        else {
                            WR();
                        }
                    }
                    else if (spin[1] == 'L') {
                        if (spin[2] == 'b') {
                            WLb();
                        }
                        else {
                            WL();
                        }
                    }
                    else if (spin[1] == 'U') {
                        if (spin[2] == 'b') {
                            WUb();
                        }
                        else {
                            WU();
                        }
                    }
                    else if (spin[1] == 'D') {
                        if (spin[2] == 'b') {
                            WDb();
                        }
                        else {
                            WD();
                        }
                    }
                    else if (spin[1] == 'F') {
                        if (spin[2] == 'b') {
                            WFb();
                        }
                        else {
                            WF();
                        }
                    }
                    else if (spin[1] == 'B') {
                        if (spin[2] == 'b') {
                            WBb();
                        }
                        else {
                            WB();
                        }
                    }
                    else {
                        std::cout << "Неверный поворот" << std::endl;
                    }
                }
            }
            else {
                std::cout << "Неверный цвет" << std::endl;
            }
            std::cout << "Введите команду вращения (0 - выход из программы): ";
            std::cin >> spin;
        }
        ShowCube();
    }
    
    void RandomSpinCube () {
        srand(time(NULL));
        int count = rand() % 25 + 15;
        for (int i = 0; i < count; ++i) {
            int now = rand() % 6;
            if (now == 0) {
                GR();
            }
            else if (now == 1) {
                RR();
            }
            else if (now == 2) {
                OR();
            }
            else if (now == 3) {
                BR();
            }
            else if (now == 4) {
                GU();
            }
            else if (now == 5) {
                GD();
            }
        }
        std::cout << "Random Spin" << std::endl;
        ShowCube();
    }

    void AssemblyCube () {
        all_turns = "";
        count_turns = 0;
        AssemblyWhiteKrest();
        AssemblyAngleWhite(); 
        AssemblyF2L(); 
        AssemblyYellowKrest();
        AssemblyRightYellowKrest(); 
        AssemblyRightAnlgeYellow();
        ShowCube();
        std::cout << ((collectCube()) ? "Кубик собран" : "Кубик не собран") << std::endl;
        std::cout << "Количество поворотов: " << count_turns << std::endl;
    }
    
    void Flower () {
        AssemblyCube();
        BR();
        BLb();
        BD();
        BUb();
        BF();
        BBb();
        BR();
        BLb();
    }

    void Chess () {
        GU();
        GU();
        GD();
        GD();
        GL();
        GL();
        GR();
        GR();
        GF();
        GF();
        GB();
        GB();
    }

    void CubeInCube () {
        RU();
        RU();
        RF();
        RF();
        RR();
        RR();
        RUb();
        RL();
        RL();
        RD();
        RB();
        RRb();
        RB();
        RRb();
        RB();
        RRb();
        RDb();
        RL();
        RL();
        RUb();
    }
    
    void CubeInCubeInCube () {
        RF();
        RF();
        RDb();
        RR();
        RR();
        RDb();
        RLb();
        RUb();
        RLb();
        RR();
        RB();
        RDb();
        RU();
        RB();
        RL();
        RF();
        RF();
        RL();
        RU();
        RU();
    }
    ~Cube() {};


private:
    std::string all_turns;
    int count_turns;
    std::vector <std::vector <char>> cube; 
    
    // проверка на количество цветов куба
    void checkCub (std::vector <int> &cub, char a) {
        if (a == 'y') {
            cub[0]++;
        }
        else if (a == 'r') {
            cub[1]++;
        } 
        else if (a == 'g') {
            cub[2]++;
        } 
        else if (a == 'o') {
            cub[3]++;
        } 
        else if (a == 'b') {
            cub[4]++;
        } 
        else if (a == 'w') {
            cub[5]++;
        } 
    } 

    // проверка на неправильные рёбра
    bool checkCol (char a, char b) {
        if ((a == 'w' && b == 'y') || (a == 'y' && b == 'w') || (a == 'r' && b == 'o') || (a == 'o' && b == 'r') || (a == 'b' && b == 'g') || (a == 'g' && b == 'b')) {
            return true;
        }
        return false;
    }
    
    // проверка рёбер
    bool checkRebro (std::vector <std::pair <char, char>> &rebro, char a, char b, bool &flag, std::vector <int> &cub) {
        if (flag == true) {
            for (unsigned int i = 0; i < rebro.size(); ++i) {
                if ((rebro[i].first == a && rebro[i].second == b) || (rebro[i].first == b && rebro[i].second == a) || checkCol(a, b)) {
                    return false;
                }
            }
            checkCub(cub, a);
            checkCub(cub, b);
            rebro.push_back({a, b});
            return true;
        }
        else {
            return false;
        }
    }        

    //проверка центра
    bool checkCenter (std::vector <char> &center, char a, bool &flag, std::vector <int> &cub) {
        if (flag == true) {
            for (unsigned int i = 0; i < center.size(); ++i) {
                if (center[i] == a) {
                    return false;
                }
            }
            checkCub(cub, a);
            center.push_back(a);
            return true;
        } 
        else {
            return false;
        }
    }

    //проверка углов
    bool checkCorner (std::vector <std::pair <char, std::pair <char, char>>> corner, char a, char b, char c, bool &flag, std::vector <int> &cub) {
        if (flag == true) {
            for (unsigned int i = 0; i < corner.size(); ++i) {
                std::pair <char, char> now = corner[i].second;
                char first = corner[i].first, second = now.first, third = now.second;
                if ((first == a && second == b && third == c) &&  
                    (first == a && second == c && third == b) &&
                    (first == b && second == a && third == c) && 
                    (first == b && second == c && third == a) && 
                    (first == c && second == a && third == b) && 
                    (first == c && second == b && third == a) && checkCol(a, b) && checkCol(a, c) && checkCol(b, c)) 
                {
                    return false;                
                }  
            }
            checkCub(cub, a);
            checkCub(cub, b);
            checkCub(cub, c);
            corner.push_back({a, {b, c}});
            return true;
        }
        else {
            return false;
        }
    }

    // поворот сторон
    
    // поворот по часовой стрелки
    void Right (int turn) {
        char c;
        c = cube[turn][0];
        cube[turn][0] = cube[turn][6];
        cube[turn][6] = cube[turn][8];
        cube[turn][8] = cube[turn][2];
        cube[turn][2] = c;
        c = cube[turn][1];
        cube[turn][1] = cube[turn][3];
        cube[turn][3] = cube[turn][7];
        cube[turn][7] = cube[turn][5];
        cube[turn][5] = c;
    }
    
    //поворот против часовой стрелки
    void Left (int turn) {
        char c;
        c = cube[turn][0];
        cube[turn][0] = cube[turn][2];
        cube[turn][2] = cube[turn][8];
        cube[turn][8] = cube[turn][6];
        cube[turn][6] = c;
        c = cube[turn][1];
        cube[turn][1] = cube[turn][5];
        cube[turn][5] = cube[turn][7];
        cube[turn][7] = cube[turn][3];
        cube[turn][3] = c;
    }
    
    // повороты правой стороны (*R)
    void GR () {
        Right(3);
        char c1, c2, c3;
        c1 = cube[0][2];
        c2 = cube[0][5];
        c3 = cube[0][8];
        
        cube[0][2] = cube[2][2];    
        cube[0][5] = cube[2][5];    
        cube[0][8] = cube[2][8];    
        
        cube[2][2] = cube[5][2];
        cube[2][5] = cube[5][5]; 
        cube[2][8] = cube[5][8]; 
        
        cube[5][2] = cube[4][6]; 
        cube[5][5] = cube[4][3];
        cube[5][8] = cube[4][0];
        
        cube[4][0] = c3;
        cube[4][3] = c2;
        cube[4][6] = c1;

        ++count_turns;
    }
    
    void RR () {
        Right(2);
        char c1, c2, c3;
        c1 = cube[0][6];
        c2 = cube[0][7];
        c3 = cube[0][8];
        
        cube[0][6] = cube[1][8]; 
        cube[0][7] = cube[1][5];
        cube[0][8] = cube[1][2];
        
        cube[1][2] = cube[5][0]; 
        cube[1][5] = cube[5][1];
        cube[1][8] = cube[5][2];
        
        cube[5][0] = cube[3][6]; 
        cube[5][1] = cube[3][3];
        cube[5][2] = cube[3][0];
        
        cube[3][0] = c1; 
        cube[3][3] = c2;
        cube[3][6] = c3;

        ++count_turns;
    }
    
    void OR () {
        Right(4);
        char c1, c2, c3;
        c1 = cube[0][0];
        c2 = cube[0][1];
        c3 = cube[0][2];
        
        cube[0][0] = cube[3][2];     
        cube[0][1] = cube[3][5]; 
        cube[0][2] = cube[3][8]; 
        
        cube[3][2] = cube[5][8];     
        cube[3][5] = cube[5][7]; 
        cube[3][8] = cube[5][6]; 
        
        cube[5][6] = cube[1][0];     
        cube[5][7] = cube[1][3]; 
        cube[5][8] = cube[1][6]; 
        
        cube[1][0] = c3;
        cube[1][3] = c2;
        cube[1][6] = c1; 

        ++count_turns;
    }

    void BR () {
        Right(1);
        char c1, c2, c3;
        c1 = cube[0][0];
        c2 = cube[0][3];
        c3 = cube[0][6];
        
        cube[0][0] = cube[4][8];  
        cube[0][3] = cube[4][5];
        cube[0][6] = cube[4][2];
        
        cube[4][2] = cube[5][6];  
        cube[4][5] = cube[5][3];
        cube[4][8] = cube[5][0];
        
        cube[5][0] = cube[2][0];  
        cube[5][3] = cube[2][3];
        cube[5][6] = cube[2][6];
        
        cube[2][0] = c1;  
        cube[2][3] = c2;
        cube[2][6] = c3;

        ++count_turns;
    }

    void YR () {
        GR();
    }

    void WR () {
        GR();
    } 

    // повороты левой стороны (*L) 
    void GL () {
        BR();
    }
    
    void RL () {
        OR();
    }
    
    void OL () {
        RR();
    }
    
    void BL () {
        GR();
    }
    
    void YL () {
        RL();
    }
    
    void WL () {
        RL();
    }
    
    // повороты правой стороны обратно (*R')   
    void GRb () {
        Left(3);
        char c1, c2, c3;
        c1 = cube[0][2];
        c2 = cube[0][5];
        c3 = cube[0][8];
        
        cube[0][2] = cube[4][6];    
        cube[0][5] = cube[4][3];    
        cube[0][8] = cube[4][0];    
        
        cube[4][0] = cube[5][8];
        cube[4][3] = cube[5][5]; 
        cube[4][6] = cube[5][2]; 
        
        cube[5][2] = cube[2][2]; 
        cube[5][5] = cube[2][5];
        cube[5][8] = cube[2][8];
        
        cube[2][2] = c1;
        cube[2][5] = c2;
        cube[2][8] = c3;

        ++count_turns;
    }
        
    void RRb () {
        Left(2);
        char c1, c2, c3;
        c1 = cube[0][6];
        c2 = cube[0][7];
        c3 = cube[0][8];
        
        cube[0][6] = cube[3][0]; 
        cube[0][7] = cube[3][3];
        cube[0][8] = cube[3][6];
        
        cube[3][0] = cube[5][2]; 
        cube[3][3] = cube[5][1];
        cube[3][6] = cube[5][0];
        
        cube[5][0] = cube[1][2]; 
        cube[5][1] = cube[1][5];
        cube[5][2] = cube[1][8];
        
        cube[1][2] = c3; 
        cube[1][5] = c2;
        cube[1][8] = c1;

        ++count_turns;
    }
    
    void ORb () {
        Left(4);
        char c1, c2, c3;
        c1 = cube[0][0];
        c2 = cube[0][1];
        c3 = cube[0][2];
        
        cube[0][0] = cube[1][6];     
        cube[0][1] = cube[1][3]; 
        cube[0][2] = cube[1][0]; 
        
        cube[1][0] = cube[5][6];     
        cube[1][3] = cube[5][7]; 
        cube[1][6] = cube[5][8]; 
        
        cube[5][6] = cube[3][8];     
        cube[5][7] = cube[3][5]; 
        cube[5][8] = cube[3][2]; 
        
        cube[3][2] = c1;
        cube[3][5] = c2;
        cube[3][8] = c3; 

        ++count_turns;
    }
    
    void BRb () {
        Left(1);
        char c1, c2, c3;
        c1 = cube[0][0];
        c2 = cube[0][3];
        c3 = cube[0][6];
        
        cube[0][0] = cube[2][0];  
        cube[0][3] = cube[2][3];
        cube[0][6] = cube[2][6];
        
        cube[2][0] = cube[5][0];  
        cube[2][3] = cube[5][3];
        cube[2][6] = cube[5][6];
        
        cube[5][0] = cube[4][8];  
        cube[5][3] = cube[4][5];
        cube[5][6] = cube[4][2];
        
        cube[4][2] = c3;  
        cube[4][5] = c2;
        cube[4][8] = c1;

        ++count_turns;
    }
        
    void YRb () {
        GRb();
    }

    void WRb () {
        GRb();
    }
    
    // повороты левой стороны обратно (*L') 
    void GLb () {
        BRb();
    }

    void RLb () {
        ORb();
    }
    
    void OLb () {
        RRb();   
    }
    
    void BLb () {
        GRb();
    }
    
    void YLb () {
        GLb();
    }
    
    void WLb () {
        GLb();
    }

    // Поворот Вверха (*U)   
    void GU () {
        Right(0);
        char c1, c2, c3;
        c1 = cube[2][0];
        c2 = cube[2][1];
        c3 = cube[2][2];
        
        cube[2][0] = cube[3][0];  
        cube[2][1] = cube[3][1];
        cube[2][2] = cube[3][2];
        
        cube[3][0] = cube[4][0];  
        cube[3][1] = cube[4][1];
        cube[3][2] = cube[4][2];
        
        cube[4][0] = cube[1][0];  
        cube[4][1] = cube[1][1];
        cube[4][2] = cube[1][2];
        
        cube[1][0] = c1;  
        cube[1][1] = c2;
        cube[1][2] = c3;

        ++count_turns;
    }
    
    void RU () {
        GU ();
    }
    
    void OU () {
        GU ();
    }

    void BU () {
        GU ();
    }
    
    void YU () {
        OR();
    }

    void WU () {
        RR();
    }

    // Поворот Вверха обратно (*U')   
    void GUb () {
        Left(0);
        char c1, c2, c3;
        c1 = cube[2][0];
        c2 = cube[2][1];
        c3 = cube[2][2];
        
        cube[2][0] = cube[1][0];  
        cube[2][1] = cube[1][1];
        cube[2][2] = cube[1][2];
        
        cube[1][0] = cube[4][0];  
        cube[1][1] = cube[4][1];
        cube[1][2] = cube[4][2];
        
        cube[4][0] = cube[3][0];  
        cube[4][1] = cube[3][1];
        cube[4][2] = cube[3][2];
        
        cube[3][0] = c1;  
        cube[3][1] = c2;
        cube[3][2] = c3;

        ++count_turns;
    }

    void RUb () {
        GUb();
    }
    
    void OUb () {
        GUb();
    }

    void BUb () {
        GUb();
    }

    void YUb () {
        RLb();
    }
    
    void WUb () {
        RRb();
    }
    
    // Поворот низа (*D)
    void GD () {
        Right(5);
        char c1, c2, c3;
        c1 = cube[2][6];
        c2 = cube[2][7];
        c3 = cube[2][8];
        
        cube[2][6] = cube[1][6];  
        cube[2][7] = cube[1][7];
        cube[2][8] = cube[1][8];
        
        cube[1][6] = cube[4][6];  
        cube[1][7] = cube[4][7];
        cube[1][8] = cube[4][8];
        
        cube[4][6] = cube[3][6];  
        cube[4][7] = cube[3][7];
        cube[4][8] = cube[3][8];
        
        cube[3][6] = c1;  
        cube[3][7] = c2;
        cube[3][8] = c3;

        ++count_turns;
    }

    void RD () {
        GD();
    } 

    void OD () {
        GD();
    }

    void BD () {
        GD();
    }

    void YD () {
        RR();
    }

    void WD () {
        RL();
    }
    
    // Поворот низа обратно (*D')
    void GDb () {
        Left(5);
        char c1, c2, c3;
        c1 = cube[2][6];
        c2 = cube[2][7];
        c3 = cube[2][8];
        
        cube[2][6] = cube[3][6];  
        cube[2][7] = cube[3][7];
        cube[2][8] = cube[3][8];
        
        cube[3][6] = cube[4][6];  
        cube[3][7] = cube[4][7];
        cube[3][8] = cube[4][8];
        
        cube[4][6] = cube[1][6];  
        cube[4][7] = cube[1][7];
        cube[4][8] = cube[1][8];
        
        cube[1][6] = c1;  
        cube[1][7] = c2;
        cube[1][8] = c3;

        ++count_turns;
    }

    void RDb () {
        GD();
    } 

    void ODb () {
        GD();
    }

    void BDb () {
        GD();
    }

    void YDb () {
        OLb();
    }

    void WDb () {
        ORb();
    }

    // Поворот переда (*F)
    void GF () {
        RR();
    }
    
    void RF () {
        BR();
    }
    
    void OF () {
        GR();
    }
    
    void BF () {
        OR();
    }
    
    void YF () {
        GU();
    }
    
    void WF () {
        GD();
    }
    
    // Поворот переда обратно (*F')
    void GFb () {
        RRb();
    }

    void OFb () {
        GRb();       
    }
    
    void RFb () {
        BRb();       
    }

    void BFb () {
        ORb();       
    }
    
    void YFb () {
        GUb();       
    }

    void WFb () {
        GDb();       
    }

    //поворот зада (*B)
    void GB () {
        OR();
    }

    void RB () {
        GR();
    }

    void OB () {
        BR();
    }
    
    void BB () {
        RR();
    }
    
    void YB () {
        GD();
    }
    
    void WB () {
        GU();
    }

    //поворот зада обратно (*B')
    void GBb () {
        ORb();
    }

    void RBb () {
        GRb();
    }

    void OBb () {
        BRb();
    }
    
    void BBb () {
        RRb();
    }
    
    void YBb () {
        GDb();
    }
    
    void WBb () {
        GUb();
    }
        
    // сборка кубика рубика
    // проверка на то что куб собран
    bool collectCube () {
        if ((cube[0][0] == 'y') && (cube[0][2] == 'y') && (cube[0][3] == 'y') && (cube[0][4] == 'y') && (cube[0][5] == 'y') && (cube[0][6] == 'y') && (cube[0][7] == 'y') && (cube[0][8] == 'y')        
         && (cube[1][0] == 'r') && (cube[1][2] == 'r') && (cube[1][3] == 'r') && (cube[1][4] == 'r') && (cube[1][5] == 'r') && (cube[1][6] == 'r') && (cube[1][7] == 'r') && (cube[1][8] == 'r')        
         && (cube[2][0] == 'g') && (cube[2][2] == 'g') && (cube[2][3] == 'g') && (cube[2][4] == 'g') && (cube[2][5] == 'g') && (cube[2][6] == 'g') && (cube[2][7] == 'g') && (cube[2][8] == 'g')        
         && (cube[3][0] == 'o') && (cube[3][2] == 'o') && (cube[3][3] == 'o') && (cube[3][4] == 'o') && (cube[3][5] == 'o') && (cube[3][6] == 'o') && (cube[3][7] == 'o') && (cube[3][8] == 'o')        
         && (cube[4][0] == 'b') && (cube[4][2] == 'b') && (cube[4][3] == 'b') && (cube[4][4] == 'b') && (cube[4][5] == 'b') && (cube[4][6] == 'b') && (cube[4][7] == 'b') && (cube[4][8] == 'b')        
         && (cube[5][0] == 'w') && (cube[5][2] == 'w') && (cube[5][3] == 'w') && (cube[5][4] == 'w') && (cube[5][5] == 'w') && (cube[5][6] == 'w') && (cube[5][7] == 'w') && (cube[5][8] == 'w')) {
            return true;
        }
        else {
            return false;
        }
    }

    bool checkKrest () {
        if (((cube[5][1] == 'w') && (cube[2][7] == 'g')) && ((cube[5][3] == 'w') && (cube[1][7] == 'r')) && ((cube[5][5] == 'w') && (cube[3][7] == 'o')) && ((cube[5][7] == 'w') && (cube[4][7] == 'b'))) {
            return true;   
        }
        else {
            return false;   
        }
    }
    void goody (char c1, char c2) {
        if (c1 == 'r') {
            if (checkKrest()) {
                return;
            }
            for (int k = 0; k < 3; ++k) {
                if (cube[1][1] != c1 || cube[0][3] != c2 || cube[1][1] != cube[1][4]) {
                    if (checkKrest()) 
                        return;
                    all_turns += "RU ";
                    RU();
                }
                else {
                    break;
                }
            }
            if (checkKrest()) {
                return;
            }
            all_turns += "RF RF ";
            RF();
            RF();
        }
        else if (c1 == 'g') {
            if (checkKrest()) {
                return;
            }
            for (int k = 0; k < 3; ++k) {
                if (cube[2][1] != c1 || cube[0][7] != c2 || cube[2][1] != cube[2][4]) {
                    if (checkKrest()) 
                        return;
                    all_turns += "GU ";
                    GU();
                }
                else {
                    break;
                }
            }
            if (checkKrest()) {
                return;
            }
            all_turns += "GF GF ";
            GF();
            GF();
        }
        else if (c1 == 'o') {
            if (checkKrest()) {
                return;
            }
            for (int k = 0; k < 3; ++k) {
                if (cube[3][1] != c1 || cube[0][5] != c2 || cube[3][1] != cube[3][4]) {
                    if (checkKrest()) {
                        return;
                    }
                    all_turns += "OU ";
                    OU();
                }
                else {
                    break;
                }
            }
            if (checkKrest()) {
                return;
            }
            all_turns += "OF OF ";
            OF();
            OF();
        }
        else if (c1 == 'b') {
            if (checkKrest()) {
                return;
            }
            for (int k = 0; k < 3; ++k) {
                if (cube[4][1] != c1 || cube[0][1] != c2 || cube[4][1] != cube[4][4]) {
                    if (checkKrest()) {
                        return;
                    }
                    all_turns += "BU ";
                    BU();
                }
                else {
                    break;
                }
            }
            if (checkKrest()) {
                return;
            }
            all_turns += "BF BF ";
            BF();
            BF();
        }
    }
    
    void AssemblyWhiteKrest () {
        char c1, c2; // c1 - другой цвет, c2 - белый
        int cnt = 0;
        while ((!checkKrest()) && (cnt < 100)) {
            for (int k = 0; k < 9; ++k) {
                // YELLOW
                c1 = cube[4][1];
                c2 = cube[0][1];
                if (c2 == 'w') {
                    goody(c1, c2);
                }
                c1 = cube[1][1];
                c2 = cube[0][3];
                if (c2 == 'w') {
                    goody(c1, c2);
                }
                c1 = cube[3][1];
                c2 = cube[0][5];
                if (c2 == 'w') {
                    goody(c1, c2);
                }
                c1 = cube[2][1];
                c2 = cube[0][7];
                if (c2 == 'w') {
                    goody(c1, c2);
                }
                  
                // RED
                c1 = cube[0][3];
                c2 = cube[1][1];
                if (c2 == 'w') {
                    all_turns += "RF RR RU RRb ";  
                    RF();
                    RR();
                    RU();
                    RRb();
                    goody(c1, c2);
                }
                c1 = cube[4][5];
                c2 = cube[1][3];
                if (c2 == 'w') {
                    all_turns += "RLb RUb RL ";  
                    RLb();   
                    RUb();  
                    RL();
                    goody(c1, c2);
                }
                c1 = cube[2][3];
                c2 = cube[1][5];
                if (c2 == 'w') {
                    all_turns += "RR RU RRb ";  
                    RR();   
                    RU();  
                    RRb();
                    goody(c1, c2);
                }
                c1 = cube[5][3];
                c2 = cube[1][7];
                if (c2 == 'w') {
                    all_turns += "RF RLb RUb RL ";  
                    RF();
                    RLb();   
                    RUb();  
                    RL();
                    goody(c1, c2);
                }
                
                //GREEN
                c1 = cube[0][7];
                c2 = cube[2][1];
                if (c2 == 'w') {
                    all_turns += "GF GR GU GRb ";  
                    GF();
                    GR();
                    GU();
                    GRb();
                    goody(c1, c2);
                }
                c1 = cube[1][5];
                c2 = cube[2][3];
                if (c2 == 'w') {
                    all_turns += "GLb GUb GL ";  
                    GLb();   
                    GUb();  
                    GL();
                    goody(c1, c2);
                }
                c1 = cube[3][3];
                c2 = cube[2][5];
                if (c2 == 'w') {
                    all_turns += "GR GU GRb ";  
                    GR();   
                    GU();  
                    GRb();
                    goody(c1, c2);
                }
                c1 = cube[5][1];
                c2 = cube[2][7];
                if (c2 == 'w') {
                    all_turns += "GF GLb GUb GL ";  
                    GF();
                    GLb();   
                    GUb();  
                    GL();
                    goody(c1, c2);
                }
                    
                // ORANGE
                c1 = cube[0][5];
                c2 = cube[3][1];
                if (c2 == 'w') {
                    all_turns += "OF OR OU ORb ";  
                    OF();
                    OR();
                    OU();
                    ORb();
                    goody(c1, c2);
                }
                c1 = cube[2][5];
                c2 = cube[3][3];
                if (c2 == 'w') {
                    all_turns += "OLb OUb OL ";  
                    OLb();   
                    OUb();  
                    OL();
                    goody(c1, c2);
                }
                c1 = cube[4][3];
                c2 = cube[3][5];
                if (c2 == 'w') {
                    all_turns += "OR OU ORb ";  
                    OR();   
                    OU();  
                    ORb();
                    goody(c1, c2);
                }
                c1 = cube[5][5];
                c2 = cube[3][7];
                if (c2 == 'w') {
                    all_turns += "OF OLb OUb OL ";  
                    OF();
                    OLb();   
                    OUb();  
                    OL();
                    goody(c1, c2);
                }
                    

                //BLUE
                c1 = cube[0][1];
                c2 = cube[4][1];
                if (c2 == 'w') {
                    all_turns += "BF BR BU BRb ";  
                    BF();
                    BR();
                    BU();
                    BRb();
                    goody(c1, c2);
                }
                c1 = cube[3][5];
                c2 = cube[4][3];
                if (c2 == 'w') {
                    all_turns += "BLb BUb BL ";  
                    BLb();   
                    BUb();  
                    BL();
                    goody(c1, c2);
                }
                c1 = cube[1][3];
                c2 = cube[4][5];
                if (c2 == 'w') {
                    all_turns += "BR BU BRb ";  
                    BR();   
                    BU();  
                    BRb();
                    goody(c1, c2);
                }
                c1 = cube[5][7];
                c2 = cube[4][7];
                if (c2 == 'w') {
                    all_turns += "BF BLb BUb BL ";  
                    BF();
                    BLb();   
                    BUb();  
                    BL();
                    goody(c1, c2);
                }

                //WHITE
                c1 = cube[2][7];
                c2 = cube[5][1];
                if (c2 == 'w' && c1 != cube[2][4]) {
                    all_turns += "GF GF ";  
                    GF();
                    GF();
                    goody(c1, c2);
                }
                c1 = cube[1][7];
                c2 = cube[5][3];
                if (c2 == 'w' && c1 != cube[1][4]) {
                    all_turns += "RF RF ";  
                    RF();
                    RF();
                    goody(c1, c2);
                }
                c1 = cube[3][7];
                c2 = cube[5][5];
                if (c2 == 'w' && c1 != cube[3][4]) {
                    all_turns += "OF OF ";  
                    OF();
                    OF();
                    goody(c1, c2);
                }
                c1 = cube[4][7];
                c2 = cube[5][7];
                if (c2 == 'w' && c1 != cube[4][4]) {
                    all_turns += "OF OF ";  
                    OF();
                    OF();
                    goody(c1, c2);
                }
            }
            cnt++;
        }
        if (cnt >= 100) {
            std::cout << "Кубик не собрать :( AssemblyWhiteKrest " << cnt << std::endl;
        }
        else {
            std::cout << "Собран AssemblyWhiteKrest " << cnt << std::endl;
        }
    }
    

    bool checkAngleWhite () {
        if ((cube[5][1] == 'w') && (cube[2][7] == 'g') && (cube[5][3] == 'w') && (cube[1][7] == 'r') && (cube[5][5] == 'w') && (cube[3][7] == 'o') && (cube[5][7] == 'w') && (cube[4][7] == 'b') &&
            (cube[1][8] == 'r') && (cube[2][6] == 'g') && (cube[5][0] == 'w') && (cube[2][8] == 'g') && (cube[3][6] == 'o') && (cube[5][2] == 'w') &&
            (cube[3][8] == 'o') && (cube[4][6] == 'b') && (cube[5][8] == 'w') && (cube[4][8] == 'b') && (cube[1][6] == 'r') && (cube[5][6] == 'w')) {
            return true;   
        }
        else {
            return false;   
        }
    }
    
    void turnAngleR (char c1, char c2, char c3) {
        if ((c1 == 'w') && (c2 == 'g') && (c3 == 'r')) {
            all_turns += "RU RR RUb RRb ";
            RU();
            RR();
            RUb();
            RRb();
        }
        if ((c1 == 'r') && (c2 == 'w') && (c3 == 'g')) {
            all_turns += "RR RU RRb RUb ";
            RR();
            RU();
            RRb();
            RUb();
        }
        if ((c1 == 'g') && (c2 == 'r') && (c3 == 'w')) {
            all_turns += "RR RU RRb RUb RR RU RRb RUb RR RU RRb RUb ";
            RR();
            RU();
            RRb();
            RUb();
            RR();
            RU();
            RRb();
            RUb();
            RR();
            RU();
            RRb();
            RUb();
        }
    }

    void turnAngleG (char c1, char c2, char c3) {
        if ((c1 == 'w') && (c2 == 'o') && (c3 == 'g')) {
            all_turns += "GU GR GUb GRb ";
            GU();
            GR();
            GUb();
            GRb();
        }
        else if ((c1 == 'g') && (c2 == 'w') && (c3 == 'o')) {
            all_turns += "GR GU GRb GUb ";
            GR();
            GU();
            GRb();
            GUb();
        }
        if ((c1 == 'o') && (c2 == 'g') && (c3 == 'w')) {
            all_turns += "GR GU GRb GUb GR GU GRb GUb GR GU GRb GUb ";
            GR();
            GU();
            GRb();
            GUb();
            GR();
            GU();
            GRb();
            GUb();
            GR();
            GU();
            GRb();
            GUb();
        }
    }

    void turnAngleO (char c1, char c2, char c3) {
        if ((c1 == 'w') && (c2 == 'b') && (c3 == 'o')) {
            all_turns += "OU OR OUb ORb ";
            OU();
            OR();
            OUb();
            ORb();
        }
        if ((c1 == 'o') && (c2 == 'w') && (c3 == 'b')) {
            all_turns += "OR OU ORb OUb ";
            OR();
            OU();
            ORb();
            OUb();
        }
        if ((c1 == 'b') && (c2 == 'o') && (c3 == 'w')) {
            all_turns += "OR OU ORb OUb OR OU ORb OUb OR OU ORb OUb ";
            OR();
            OU();
            ORb();
            OUb();
            OR();
            OU();
            ORb();
            OUb();
            OR();
            OU();
            ORb();
            OUb();
        }
    }

    void turnAngleB (char c1, char c2, char c3) {
        if ((c1 == 'w') && (c2 == 'r') && (c3 == 'b')) {
            all_turns += "BU BR BUb BRb ";
            BU();
            BR();
            BUb();
            BRb();
        }
        else if ((c1 == 'b') && (c2 == 'w') && (c3 == 'r')) {
            all_turns += "BR BU BRb BUb ";
            BR();
            BU();
            BRb();
            BUb();
        }
        else if ((c1 == 'r') && (c2 == 'b') && (c3 == 'w')) {
            all_turns += "BR BU BRb BUb BR BU BRb BUb BR BU BRb BUb ";
            BR();
            BU();
            BRb();
            BUb();
            BR();
            BU();
            BRb();
            BUb();
            BR();
            BU();
            BRb();
            BUb();
        }
    }


    // Сбор углов у белой стороны
    void AssemblyAngleWhite () {
        int cnt = 0;
        while ((!checkAngleWhite()) && (cnt < 100)) {
            char c1, c2, c3;
            for (int k = 0; k < 4; ++k) {
                // RED            
                c1 = cube[1][8];
                c2 = cube[2][6];
                c3 = cube[5][0];
                if ((cube[1][8] == 'r') && (cube[2][6] == 'g') && (cube[5][0] == 'w')) {
                    break;
                }
                else if ((c1 == 'w') && (c2 == 'r') && (c3 == 'g')) {
                    all_turns += "RU RR RUb RRb RU RR RUb RRb ";
                    RU();
                    RR();
                    RUb();
                    RRb();
                    RU();
                    RR();
                    RUb();
                    RRb();
                    break;
                }
                else if ((c1 == 'g') && (c2 == 'w') && (c3 == 'r')) {
                    all_turns += "RR RU RRb RUb RR RU RRb RUb ";
                    RR();
                    RU();
                    RRb();
                    RUb();
                    RR();
                    RU();
                    RRb();
                    RUb();
                    break;
                }
                else if ((c1 == 'w') || (c2 == 'w') || (c3 == 'w')) {
                    all_turns += "RR RU RRb RUb ";
                    RR();
                    RU();
                    RRb();
                    RUb();
                }
            }

            for (int k = 0; k < 4; ++k) {
                c1 = 'r';
                c2 = 'g';
                c3 = 'w';
                if ((cube[1][8] == 'r') && (cube[2][6] == 'g') && (cube[5][0] == 'w')) {
                    break;
                }
                if (cube[1][2] == c3 && cube[2][0] == c2 && cube[0][6] == c1) {
                    turnAngleR(cube[1][2], cube[2][0], cube[0][6]);
                }
                if (cube[1][2] == c2 && cube[2][0] == c1 && cube[0][6] == c3) {
                    turnAngleR(cube[1][2], cube[2][0], cube[0][6]);
                }
                if (cube[1][2] == c1 && cube[2][0] == c3 && cube[0][6] == c2) {
                    turnAngleR(cube[1][2], cube[2][0], cube[0][6]);
                }
                
                if (cube[2][2] == c3 && cube[3][0] == c2 && cube[0][8] == c1) {
                    all_turns += "RU ";
                    RU();
                    turnAngleR(cube[2][2], cube[3][0], cube[0][8]);
                }
                if (cube[2][2] == c2 && cube[3][0] == c1 && cube[0][8] == c3) {
                    all_turns += "RU ";
                    RU();
                    turnAngleR(cube[2][2], cube[3][0], cube[0][8]);
                }
                if (cube[2][2] == c1 && cube[3][0] == c3 && cube[0][8] == c2) {
                    all_turns += "RU ";
                    RU();
                    turnAngleR(cube[2][2], cube[3][0], cube[0][8]);
                }
                
                if (cube[3][2] == c3 && cube[4][0] == c2 && cube[0][2] == c1) {
                    all_turns += "RUb RUb ";
                    RUb();
                    RUb();
                    turnAngleR(cube[3][2], cube[4][0], cube[0][2]);
                }
                if (cube[3][2] == c2 && cube[4][0] == c1 && cube[0][2] == c3) {
                    all_turns += "RUb RUb ";
                    RUb();
                    RUb();
                    turnAngleR(cube[3][2], cube[4][0], cube[0][2]);
                }
                if (cube[3][2] == c1 && cube[4][0] == c3 && cube[0][2] == c2) {
                    all_turns += "RUb RUb ";
                    RUb();
                    RUb();
                    turnAngleR(cube[3][2], cube[4][0], cube[0][2]);
                }
                
                if (cube[4][2] == c3 && cube[1][0] == c2 && cube[0][0] == c1) {
                    all_turns += "RUb ";
                    RUb();
                    turnAngleR(cube[4][2], cube[1][0], cube[0][0]);
                }
                if (cube[4][2] == c2 && cube[1][0] == c1 && cube[0][0] == c3) {
                    all_turns += "RUb ";
                    RUb();
                    turnAngleR(cube[4][2], cube[1][0], cube[0][0]);
                }
                if (cube[4][2] == c1 && cube[1][0] == c3 && cube[0][0] == c2) {
                    all_turns += "RUb ";
                    RUb();
                    turnAngleR(cube[4][2], cube[1][0], cube[0][0]);
                }
                
            }
                    
            // GREEN 
            for (int k = 0; k < 4; ++k) {
                c1 = cube[2][8];
                c2 = cube[3][6];
                c3 = cube[5][2];
                if ((cube[2][8] == 'g') && (cube[3][6] == 'o') && (cube[5][2] == 'w')) {
                    break;
                }
                else if ((c1 == 'w') && (c2 == 'g') && (c3 == 'o')) {
                    all_turns += "GU GR GUb GRb GU GR GUb GRb ";
                    GU();
                    GR();
                    GUb();
                    GRb();
                    GU();
                    GR();
                    GUb();
                    GRb();
                    break;
                }
                else if ((c1 == 'o') && (c2 == 'w') && (c3 == 'g')) {
                    all_turns += "GR GU GRb GUb GR GU GRb GUb ";
                    GR();
                    GU();
                    GRb();
                    GUb();
                    GR();
                    GU();
                    GRb();
                    GUb();
                    break;
                }
                else if ((c1 == 'w') || (c2 == 'w') || (c3 == 'w')) {
                    all_turns += "GR GU GRb GUb ";
                    GR();
                    GU();
                    GRb();
                    GUb();
                }
            }

            for (int k = 0; k < 4; ++k) {
                c1 = 'g';
                c2 = 'o';
                c3 = 'w';
                if ((cube[2][8] == 'g') && (cube[3][6] == 'o') && (cube[5][2] == 'w')) {
                    break;
                }
                if (cube[1][2] == c3 && cube[2][0] == c2 && cube[0][6] == c1) {
                    all_turns += "RUb ";
                    RUb(); 
                    turnAngleG(cube[1][2], cube[2][0], cube[0][6]);
                }
                if (cube[1][2] == c2 && cube[2][0] == c1 && cube[0][6] == c3) {
                    all_turns += "RUb ";
                    RUb(); 
                    turnAngleG(cube[1][2], cube[2][0], cube[0][6]);
                }
                if (cube[1][2] == c1 && cube[2][0] == c3 && cube[0][6] == c2) {
                    all_turns += "RUb ";
                    RUb(); 
                    turnAngleG(cube[1][2], cube[2][0], cube[0][6]);
                }
                
                if (cube[2][2] == c3 && cube[3][0] == c2 && cube[0][8] == c1) {
                    turnAngleG(cube[2][2], cube[3][0], cube[0][8]);
                }
                if (cube[2][2] == c2 && cube[3][0] == c1 && cube[0][8] == c3) {
                    turnAngleG(cube[2][2], cube[3][0], cube[0][8]);
                }
                if (cube[2][2] == c1 && cube[3][0] == c3 && cube[0][8] == c2) {
                    turnAngleG(cube[2][2], cube[3][0], cube[0][8]);
                }
                
                if (cube[3][2] == c3 && cube[4][0] == c2 && cube[0][2] == c1) {
                    all_turns += "GUb ";
                    GUb();
                    turnAngleG(cube[3][2], cube[4][0], cube[0][2]);
                }
                if (cube[3][2] == c2 && cube[4][0] == c1 && cube[0][2] == c3) {
                    all_turns += "GUb ";
                    GUb();
                    turnAngleG(cube[3][2], cube[4][0], cube[0][2]);
                }
                if (cube[3][2] == c1 && cube[4][0] == c3 && cube[0][2] == c2) {
                    all_turns += "GUb ";
                    GUb();
                    turnAngleG(cube[3][2], cube[4][0], cube[0][2]);
                }
                
                if (cube[4][2] == c3 && cube[1][0] == c2 && cube[0][0] == c1) {
                    all_turns += "GUb GUb ";
                    GUb();
                    GUb();
                    turnAngleG(cube[4][2], cube[1][0], cube[0][0]);
                }
                if (cube[4][2] == c2 && cube[1][0] == c1 && cube[0][0] == c3) {
                    all_turns += "GUb GUb ";
                    GUb();
                    GUb();
                    turnAngleG(cube[4][2], cube[1][0], cube[0][0]);
                }
                if (cube[4][2] == c1 && cube[1][0] == c3 && cube[0][0] == c2) {
                    all_turns += "GUb GUb ";
                    GUb();
                    GUb();
                    turnAngleG(cube[4][2], cube[1][0], cube[0][0]);
                }
            }
            
            // ORANGE 
            for (int k = 0; k < 4; ++k) {
                c1 = cube[3][8];
                c2 = cube[4][6];
                c3 = cube[5][8];
                if ((cube[3][8] == 'o') && (cube[4][6] == 'b') && (cube[5][8] == 'w')) {
                    break;
                }
                else if ((c1 == 'w') && (c2 == 'o') && (c3 == 'b')) {
                    all_turns += "OU OR OUb ORb OU OR OUb ORb ";
                    OU();
                    OR();
                    OUb();
                    ORb();
                    OU();
                    OR();
                    OUb();
                    ORb();
                    break;
                }
                else if ((c1 == 'b') && (c2 == 'w') && (c3 == 'o')) {
                    all_turns += "OR OU ORb OUb OR OU ORb OUb ";
                    OR();
                    OU();
                    ORb();
                    OUb();
                    OR();
                    OU();
                    ORb();
                    OUb();
                    break;
                }
                else if ((c1 == 'w') || (c2 == 'w') || (c3 == 'w')) {
                    all_turns += "OR OU ORb OUb ";
                    OR();
                    OU();
                    ORb();
                    OUb();
                }
            }

            for (int k = 0; k < 4; ++k) {
                c1 = 'o';
                c2 = 'b';
                c3 = 'w';
                if ((cube[3][8] == 'o') && (cube[4][6] == 'b') && (cube[5][8] == 'w')) {
                    break;
                }
                if (cube[1][2] == c3 && cube[2][0] == c2 && cube[0][6] == c1) {
                    all_turns += "OUb OUb ";
                    OUb(); 
                    OUb(); 
                    turnAngleO(cube[1][2], cube[2][0], cube[0][6]);
                }
                if (cube[1][2] == c2 && cube[2][0] == c1 && cube[0][6] == c3) {
                    all_turns += "OUb OUb ";
                    OUb(); 
                    OUb(); 
                    turnAngleO(cube[1][2], cube[2][0], cube[0][6]);
                }
                if (cube[1][2] == c1 && cube[2][0] == c3 && cube[0][6] == c2) {
                    all_turns += "OUb OUb ";
                    OUb(); 
                    OUb(); 
                    turnAngleO(cube[1][2], cube[2][0], cube[0][6]);
                }
                
                if (cube[2][2] == c3 && cube[3][0] == c2 && cube[0][8] == c1) {
                    all_turns += "OUb ";
                    OUb(); 
                    turnAngleO(cube[2][2], cube[3][0], cube[0][8]);
                }
                if (cube[2][2] == c2 && cube[3][0] == c1 && cube[0][8] == c3) {
                    all_turns += "OUb ";
                    OUb(); 
                    turnAngleO(cube[2][2], cube[3][0], cube[0][8]);
                }
                if (cube[2][2] == c1 && cube[3][0] == c3 && cube[0][8] == c2) {
                    all_turns += "OUb ";
                    OUb(); 
                    turnAngleO(cube[2][2], cube[3][0], cube[0][8]);
                }
                
                if (cube[3][2] == c3 && cube[4][0] == c2 && cube[0][2] == c1) {
                    turnAngleO(cube[3][2], cube[4][0], cube[0][2]);
                }
                if (cube[3][2] == c2 && cube[4][0] == c1 && cube[0][2] == c3) {
                    turnAngleO(cube[3][2], cube[4][0], cube[0][2]);
                }
                if (cube[3][2] == c1 && cube[4][0] == c3 && cube[0][2] == c2) {
                    turnAngleO(cube[3][2], cube[4][0], cube[0][2]);
                }
                
                if (cube[4][2] == c3 && cube[1][0] == c2 && cube[0][0] == c1) {
                    all_turns += "OUb ";
                    OUb();
                    turnAngleO(cube[4][2], cube[1][0], cube[0][0]);
                }
                if (cube[4][2] == c2 && cube[1][0] == c1 && cube[0][0] == c3) {
                    all_turns += "OUb ";
                    OUb();
                    turnAngleO(cube[4][2], cube[1][0], cube[0][0]);
                }
                if (cube[4][2] == c1 && cube[1][0] == c3 && cube[0][0] == c2) {
                    all_turns += "OUb ";
                    OUb();
                    turnAngleO(cube[4][2], cube[1][0], cube[0][0]);
                }
            }

            // BLUE
            for (int k = 0; k < 4; ++k) {
                c1 = cube[4][8];
                c2 = cube[1][6];
                c3 = cube[5][6];
                if ((cube[4][8] == 'b') && (cube[1][6] == 'r') && (cube[5][6] == 'w')) {
                    break;
                }
                else if ((c1 == 'w') && (c2 == 'b') && (c3 == 'r')) {
                    all_turns += "BU BR BUb BRb BU BR BUb BRb ";
                    BU();
                    BR();
                    BUb();
                    BRb();
                    BU();
                    BR();
                    BUb();
                    BRb();
                    break;
                }
                else if ((c1 == 'r') && (c2 == 'w') && (c3 == 'b')) {
                    all_turns += "BR BU BRb BUb BR BU BRb BUb ";
                    BR();
                    BU();
                    BRb();
                    BUb();
                    BR();
                    BU();
                    BRb();
                    BUb();
                    break;
                }
                else if ((c1 == 'w') || (c2 == 'w') || (c3 == 'w')) {
                    all_turns += "BR BU BRb BUb ";
                    BR();
                    BU();
                    BRb();
                    BUb();
                }
            }

            for (int k = 0; k < 4; ++k) {
                c1 = 'b';
                c2 = 'r';
                c3 = 'w';
                if ((cube[4][8] == 'b') && (cube[1][6] == 'r') && (cube[5][6] == 'w')) {
                    break;
                }
                if (cube[1][2] == c3 && cube[2][0] == c2 && cube[0][6] == c1) {
                    all_turns += "BU ";
                    BU(); 
                    turnAngleB(cube[1][2], cube[2][0], cube[0][6]);
                }
                if (cube[1][2] == c2 && cube[2][0] == c1 && cube[0][6] == c3) {
                    all_turns += "BU ";
                    BU(); 
                    turnAngleB(cube[1][2], cube[2][0], cube[0][6]);
                }
                if (cube[1][2] == c1 && cube[2][0] == c3 && cube[0][6] == c2) {
                    all_turns += "BU ";
                    BU(); 
                    turnAngleB(cube[1][2], cube[2][0], cube[0][6]);
                }
                
                if (cube[2][2] == c3 && cube[3][0] == c2 && cube[0][8] == c1) {
                    all_turns += "BUb BUb ";
                    BUb(); 
                    BUb(); 
                    turnAngleB(cube[2][2], cube[3][0], cube[0][8]);
                }
                if (cube[2][2] == c2 && cube[3][0] == c1 && cube[0][8] == c3) {
                    all_turns += "BUb BUb ";
                    BUb(); 
                    BUb(); 
                    turnAngleB(cube[2][2], cube[3][0], cube[0][8]);
                }
                if (cube[2][2] == c1 && cube[3][0] == c3 && cube[0][8] == c2) {
                    all_turns += "BUb BUb ";
                    BUb(); 
                    BUb(); 
                    turnAngleB(cube[2][2], cube[3][0], cube[0][8]);
                }
                
                if (cube[3][2] == c3 && cube[4][0] == c2 && cube[0][2] == c1) {
                    all_turns += "BUb ";
                    BUb(); 
                    turnAngleB(cube[3][2], cube[4][0], cube[0][2]);
                }
                if (cube[3][2] == c2 && cube[4][0] == c1 && cube[0][2] == c3) {
                    all_turns += "BUb ";
                    BUb(); 
                    turnAngleB(cube[3][2], cube[4][0], cube[0][2]);
                }
                if (cube[3][2] == c1 && cube[4][0] == c3 && cube[0][2] == c2) {
                    all_turns += "BUb ";
                    BUb(); 
                    turnAngleB(cube[3][2], cube[4][0], cube[0][2]);
                }
                
                if (cube[4][2] == c3 && cube[1][0] == c2 && cube[0][0] == c1) {
                    turnAngleB(cube[4][2], cube[1][0], cube[0][0]);
                }
                if (cube[4][2] == c2 && cube[1][0] == c1 && cube[0][0] == c3) {
                    turnAngleB(cube[4][2], cube[1][0], cube[0][0]);
                }
                if (cube[4][2] == c1 && cube[1][0] == c3 && cube[0][0] == c2) {
                    turnAngleB(cube[4][2], cube[1][0], cube[0][0]);
                }
            }
            cnt++;
        }
        if (cnt >= 100) {
            std::cout << "Кубик не собрать :( AssemeblyEdgeWhite " << cnt << std::endl; 
        }
        else {
            std::cout << "Собран AssemeblyEdgeWhite " << cnt << std::endl;
        }
    }


    bool checkF2L () {
        if ((cube[5][1] == 'w') && (cube[2][7] == 'g') && (cube[5][3] == 'w') && (cube[1][7] == 'r') && (cube[5][5] == 'w') && (cube[3][7] == 'o') && (cube[5][7] == 'w') && (cube[4][7] == 'b') &&
            (cube[1][8] == 'r') && (cube[2][6] == 'g') && (cube[5][0] == 'w') && (cube[2][8] == 'g') && (cube[3][6] == 'o') && (cube[5][2] == 'w') &&
            (cube[3][8] == 'o') && (cube[4][6] == 'b') && (cube[5][8] == 'w') && (cube[4][8] == 'b') && (cube[1][6] == 'r') && (cube[5][6] == 'w') &&
            (cube[1][3] == 'r') && (cube[1][5] == 'r') && (cube[2][3] == 'g') && (cube[2][5] == 'g') && (cube[3][3] == 'o') && (cube[3][5] == 'o') && (cube[4][3] == 'b') && (cube[4][5] == 'b')) {
            return true;   
        }
        else {
            return false;   
        }
    }
    

    void turnEdgeR (char c1, char c2) {
        if (c1 == 'r' && c2 == 'b') {
            all_turns += "RUb RLb RUb RL RU RF RU RFb ";
            RUb();
            RLb();
            RUb();
            RL();
            RU();
            RF();
            RU();
            RFb();
        }  
        if (c1 == 'r' && c2 == 'g') {
            all_turns += "RU RR RU RRb RUb RFb RUb RF ";
            RU();
            RR();
            RU();
            RRb();
            RUb();
            RFb();
            RUb();
            RF();
        }
    }
    void turnEdgeG (char c1, char c2) {
        if (c1 == 'g' && c2 == 'r') {
            all_turns += "GUb GLb GUb GL GU GF GU GFb ";
            GUb();
            GLb();
            GUb();
            GL();
            GU();
            GF();
            GU();
            GFb();
        }  
        if (c1 == 'g' && c2 == 'o') {
            all_turns += "GU GR GU GRb GUb GFb GUb GF ";
            GU();
            GR();
            GU();
            GRb();
            GUb();
            GFb();
            GUb();
            GF();
        }
    }
    void turnEdgeO (char c1, char c2) {
        if (c1 == 'o' && c2 == 'g') {
            all_turns += "OUb OLb OUb OL OU OF OU OFb ";
            OUb();
            OLb();
            OUb();
            OL();
            OU();
            OF();
            OU();
            OFb();
        }  
        if (c1 == 'o' && c2 == 'b') {
            all_turns += "OU OR OU ORb OUb OFb OUb OF ";
            OU();
            OR();
            OU();
            ORb();
            OUb();
            OFb();
            OUb();
            OF();
        }
    }
    void turnEdgeB (char c1, char c2) {
        if (c1 == 'b' && c2 == 'o') {
            all_turns += "BUb BLb BUb BL BU BF BU BFb ";
            BUb();
            BLb();
            BUb();
            BL();
            BU();
            BF();
            BU();
            BFb();
        }  
        if (c1 == 'b' && c2 == 'r') {
            all_turns += "BU BR BU BRb BUb BFb BUb BF ";
            BU();
            BR();
            BU();
            BRb();
            BUb();
            BFb();
            BUb();
            BF();
        }
    }

    void AssemblyF2L () {
        int cnt = 0;
        while ((!checkF2L()) && (cnt < 100)) {
            for (int k = 0; k < 4; ++k) {
                if ((cube[1][1] == 'r' && cube[0][3] == 'b') || (cube[1][1] == 'r' && cube[0][3] == 'g')) {
                    turnEdgeR(cube[1][1], cube[0][3]);                
                }
                else if ((cube[2][1] == 'g' && cube[0][7] == 'r') || (cube[2][1] == 'g' && cube[0][7] == 'o')) {
                    turnEdgeG(cube[2][1], cube[0][7]);                
                }
                else if ((cube[3][1] == 'o' && cube[0][5] == 'g') || (cube[3][1] == 'o' && cube[0][5] == 'b')) {
                    turnEdgeO(cube[3][1], cube[0][5]);                
                }
                else if ((cube[4][1] == 'b' && cube[0][1] == 'o') || (cube[4][1] == 'b' && cube[0][1] == 'r')) {
                    turnEdgeB(cube[4][1], cube[0][1]);                
                }
                else {
                    all_turns += "GU ";
                    GU();
                }
            }   
            if ((cube[1][3] != 'r' || cube[4][5] != 'b') && (cube[1][3] != 'y' || cube[4][5] != 'y')) { 
                turnEdgeR('r', 'b');
            }
            if ((cube[1][5] != 'r' || cube[2][3] != 'g') && (cube[1][5] != 'y' || cube[2][3] != 'y')) {
                turnEdgeR('r', 'g');
            }
            
            if ((cube[2][3] != 'g' || cube[1][5] != 'r') && (cube[2][3] != 'y' || cube[1][5] != 'y')) {
                turnEdgeG('g', 'r');
            } 
            if ((cube[2][5] != 'g' || cube[3][3] != 'o') && (cube[2][5] != 'y' || cube[3][3] != 'y')) {
                turnEdgeG('g', 'o');
            }
            
            if ((cube[3][3] != 'o' || cube[2][5] != 'g') && (cube[3][3] != 'y' || cube[2][5] != 'y')) {
                turnEdgeO('o', 'g');
            } 
            if ((cube[3][5] != 'o' || cube[4][3] != 'b') && (cube[3][5] != 'y' || cube[4][3] != 'y')) {
                turnEdgeO('o', 'b');
            }
            
            if ((cube[4][3] != 'b' || cube[3][5] != 'o') && (cube[4][3] != 'y' || cube[3][5] != 'y')) {
                turnEdgeB('b', 'o');
            } 
            if ((cube[4][5] != 'b' || cube[1][3] != 'r') && (cube[4][5] != 'y' || cube[1][3] != 'y')) {
                turnEdgeB('b', 'r');                
            }

            cnt++;
        }
        if (cnt >= 100) {
            std::cout << "Кубик не собрать :( AssemblyF2L " << cnt << std::endl; 
        }
        else {
            std::cout << "Собран AssemblyF2L " << cnt << std::endl;
        }
    }

    bool checkYellowKrest () {
        if ((cube[5][1] == 'w') && (cube[2][7] == 'g') && (cube[5][3] == 'w') && (cube[1][7] == 'r') && (cube[5][5] == 'w') && (cube[3][7] == 'o') && (cube[5][7] == 'w') && (cube[4][7] == 'b') &&
            (cube[1][8] == 'r') && (cube[2][6] == 'g') && (cube[5][0] == 'w') && (cube[2][8] == 'g') && (cube[3][6] == 'o') && (cube[5][2] == 'w') &&
            (cube[3][8] == 'o') && (cube[4][6] == 'b') && (cube[5][8] == 'w') && (cube[4][8] == 'b') && (cube[1][6] == 'r') && (cube[5][6] == 'w') &&
            (cube[1][3] == 'r') && (cube[1][5] == 'r') && (cube[2][3] == 'g') && (cube[2][5] == 'g') && (cube[3][3] == 'o') && (cube[3][5] == 'o') && (cube[4][3] == 'b') && (cube[4][5] == 'b') &&
            (cube[0][1] == 'y') && (cube[0][3] == 'y') && (cube[0][5] == 'y') && (cube[0][7] == 'y')) {
            return true;   
        }
        else {
            return false;   
        }
    }

    void turnYellow (int x) {
        if (x == 1) {
            all_turns += "GF GU GR GFb GUb GRb ";
            GF();
            GU();
            GR();
            GUb();
            GRb();
            GFb();
        }
        else if (x == 2) {
            all_turns += "GF GR GU GRb GUb GFb ";
            GF();
            GR();
            GU();
            GRb();
            GUb();
            GFb();
        }
    }

    void AssemblyYellowKrest () {
        int cnt = 0;
        while ((!checkYellowKrest()) && (cnt < 100)) {
            if (cube[0][1] == 'y' && cube[0][3] == 'y' && cube[0][5] != 'y' && cube[0][7] != 'y') {
                turnYellow(1);
            }
            else if (cube[0][1] == 'y' && cube[0][3] != 'y' && cube[0][5] == 'y' && cube[0][7] != 'y') {
                all_turns += "GUb ";
                GUb();
                turnYellow(1);
            }
            else if (cube[0][1] != 'y' && cube[0][3] != 'y' && cube[0][5] == 'y' && cube[0][7] == 'y') {
                all_turns += "GUb GUb ";
                GUb();
                GUb();
                turnYellow(1);
            }
            else if (cube[0][1] != 'y' && cube[0][3] == 'y' && cube[0][5] != 'y' && cube[0][7] == 'y') {
                all_turns += "GU ";
                GU();
                turnYellow(1);
            }
            else if (cube[0][1] != 'y' && cube[0][3] == 'y' && cube[0][5] == 'y' && cube[0][7] != 'y') {
                turnYellow(2);
            }
            else if (cube[0][1] == 'y' && cube[0][3] != 'y' && cube[0][5] != 'y' && cube[0][7] == 'y') {
                all_turns += "GU ";
                GU();
                turnYellow(2);
            }
            else if (cube[0][1] != 'y' && cube[0][3] != 'y' && cube[0][5] != 'y' && cube[0][7] != 'y') {
                turnYellow(1);
                all_turns += "GU ";
                GU();
                turnYellow(2);
            }
            else if (cube[0][1] == 'y' && cube[0][3] == 'y' && cube[0][5] == 'y' && cube[0][7] == 'y') {
                break;
            }
            cnt++;
        }
        if (cnt >= 100) {
            std::cout << "Кубик не собрать :( AssemblyYellowKrest " << cnt << std::endl; 
        }
        else {
            std::cout << "Собран AssemblyYellowKrest " << cnt << std::endl;
        }
    }
    
    
    bool checkRightYellowKrest () {
        if ((cube[5][1] == 'w') && (cube[2][7] == 'g') && (cube[5][3] == 'w') && (cube[1][7] == 'r') && (cube[5][5] == 'w') && (cube[3][7] == 'o') && (cube[5][7] == 'w') && (cube[4][7] == 'b') &&
            (cube[1][8] == 'r') && (cube[2][6] == 'g') && (cube[5][0] == 'w') && (cube[2][8] == 'g') && (cube[3][6] == 'o') && (cube[5][2] == 'w') &&
            (cube[3][8] == 'o') && (cube[4][6] == 'b') && (cube[5][8] == 'w') && (cube[4][8] == 'b') && (cube[1][6] == 'r') && (cube[5][6] == 'w') &&
            (cube[1][3] == 'r') && (cube[1][5] == 'r') && (cube[2][3] == 'g') && (cube[2][5] == 'g') && (cube[3][3] == 'o') && (cube[3][5] == 'o') && (cube[4][3] == 'b') && (cube[4][5] == 'b') &&
            (cube[0][1] == 'y') && (cube[0][3] == 'y') && (cube[0][5] == 'y') && (cube[0][7] == 'y')) {
            return true;   
        }
        else {
            return false;   
        }
    }
    
    void turnEdgeYellowR (char x) {
        if (x == 'l') {
            all_turns += "RU RBb RUb RUb RB RU RBb RU RB ";
            RU();
            RBb();
            RUb();
            RUb();
            RB();
            RU();
            RBb();
            RU();
            RB();
        }
        else if (x == 'r') {
            all_turns += "RU RLb RUb RUb RL RU RLb RU RL ";
            RU();
            RLb();
            RUb();
            RUb();
            RL();
            RU();
            RLb();
            RU();
            RL();
        } 
        else if (x == 'c') {
            all_turns += "RU RRb RUb RUb RR RU RRb RU RR RU RBb RUb RUb RB RU RBb RU RB RU RRb RUb RUb RR RU RRb RU RR "; 
            RU();
            RRb();
            RUb();
            RUb();
            RR();
            RU();
            RRb();
            RU();
            RR();
            RU();

            RBb();
            RUb();
            RUb();
            RB();
            RU();
            RBb();
            RU();
            RB();

            RU();
            RRb();
            RUb();
            RUb();
            RR();
            RU();
            RRb();
            RU();
            RR();
        }
    }
    void turnEdgeYellowG (char x) {
        if (x == 'l') {
            all_turns += "GU GBb GUb GUb GB GU GBb GU GB ";
            GU();
            GBb();
            GUb();
            GUb();
            GB();
            GU();
            GBb();
            GU();
            GB();
        }
        else if (x == 'r') {
            all_turns += "GU GLb GUb GUb GL GU GLb GU GL ";
            GU();
            GLb();
            GUb();
            GUb();
            GL();
            GU();
            GLb();
            GU();
            GL();
        } 
        else if (x == 'c') {
            all_turns += "GU GRb GUb GUb GR GU GRb GU GR GU GBb GUb GUb GB GU GBb GU GB GU GRb GUb GUb GR GU GRb GU GR "; 
            GU();
            GRb();
            GUb();
            GUb();
            GR();
            GU();
            GRb();
            GU();
            GR();
            GU();

            GBb();
            GUb();
            GUb();
            GB();
            GU();
            GBb();
            GU();
            GB();

            GU();
            GRb();
            GUb();
            GUb();
            GR();
            GU();
            GRb();
            GU();
            GR();
        }
    }
    void turnEdgeYellowO (char x) {
        if (x == 'l') {
            all_turns += "OU OBb OUb OUb OB OU OBb OU OB ";
            OU();
            OBb();
            OUb();
            OUb();
            OB();
            OU();
            OBb();
            OU();
            OB();
        }
        else if (x == 'r') {
            all_turns += "OU OLb OUb OUb OL OU OLb OU OL ";
            OU();
            OLb();
            OUb();
            OUb();
            OL();
            OU();
            OLb();
            OU();
            OL();
        } 
        else if (x == 'c') {
            all_turns += "OU ORb OUb OUb OR OU ORb OU OR OU OBb OUb OUb OB OU OBb OU OB OU ORb OUb OUb OR OU ORb OU OR "; 
            OU();
            ORb();
            OUb();
            OUb();
            OR();
            OU();
            ORb();
            OU();
            OR();
            OU();

            OBb();
            OUb();
            OUb();
            OB();
            OU();
            OBb();
            OU();
            OB();

            OU();
            ORb();
            OUb();
            OUb();
            OR();
            OU();
            ORb();
            OU();
            OR();
        }
    }
    void turnEdgeYellowB (char x) {
        if (x == 'l') {
            all_turns += "BU BBb BUb BUb BB BU BBb BU BB ";
            BU();
            BBb();
            BUb();
            BUb();
            BB();
            BU();
            BBb();
            BU();
            BB();
        }
        else if (x == 'r') {
            all_turns += "BU BLb BUb BUb BL BU BLb BU BL ";
            BU();
            BLb();
            BUb();
            BUb();
            BL();
            BU();
            BLb();
            BU();
            BL();
        } 
        else if (x == 'c') {
            all_turns += "BU BRb BUb BUb BR BU BRb BU BR BU BBb BUb BUb BB BU BBb BU BB BU BRb BUb BUb BR BU BRb BU BR "; 
            BU();
            BRb();
            BUb();
            BUb();
            BR();
            BU();
            BRb();
            BU();
            BR();
            BU();

            BBb();
            BUb();
            BUb();
            BB();
            BU();
            BBb();
            BU();
            BB();

            BU();
            BRb();
            BUb();
            BUb();
            BR();
            BU();
            BRb();
            BU();
            BR();
        }
    }

    void AssemblyRightYellowKrest () {
        int cnt = 0;
        while ((!checkRightYellowKrest()) || (cnt < 100)) {
            
            // всегда 2 или 4 угла уже стоят правильно, ставим их на место
            while (true) {
                if (cube[1][1] == 'r' && cube[2][1] == 'g' && cube [3][1] == 'o' && cube[4][1] == 'b') {
                    break;
                }
                else if (cube[1][1] == 'r' && cube[2][1] == 'g' && cube [3][1] != 'o' && cube[4][1] != 'b') {
                    break;
                }
                else if (cube[1][1] == 'r' && cube[2][1] != 'g' && cube [3][1] == 'o' && cube[4][1] != 'b') {
                    break;
                }
                else if (cube[1][1] == 'r' && cube[2][1] != 'g' && cube [3][1] != 'o' && cube[4][1] == 'b') {
                    break;
                }
                else if (cube[1][1] == 'r' && cube[2][1] == 'g' && cube [3][1] != 'o' && cube[4][1] != 'b') {
                    break;
                }
                else if (cube[1][1] != 'r' && cube[2][1] == 'g' && cube [3][1] == 'o' && cube[4][1] != 'b') {
                    break;
                }
                else if (cube[1][1] != 'r' && cube[2][1] == 'g' && cube [3][1] != 'o' && cube[4][1] == 'b') {
                    break;
                }
                else if (cube[1][1] == 'r' && cube[2][1] != 'g' && cube [3][1] == 'o' && cube[4][1] != 'b') {
                    break;
                }
                else if (cube[1][1] != 'r' && cube[2][1] == 'g' && cube [3][1] == 'o' && cube[4][1] != 'b') {
                    break;
                }
                else if (cube[1][1] != 'r' && cube[2][1] != 'g' && cube [3][1] == 'o' && cube[4][1] == 'b') {
                    break;
                }
                else if (cube[1][1] == 'r' && cube[2][1] != 'g' && cube [3][1] != 'o' && cube[4][1] == 'b') {
                    break;
                }
                else if (cube[1][1] != 'r' && cube[2][1] == 'g' && cube [3][1] != 'o' && cube[4][1] == 'b') {
                    break;
                }
                else if (cube[1][1] != 'r' && cube[2][1] != 'g' && cube [3][1] == 'o' && cube[4][1] == 'b') {
                    break;
                }
                else {
                    all_turns += "GU ";
                    GU();
                }
            }

            if (cube[1][1] == 'r' && cube[2][1] == 'g' && cube [3][1] == 'o' && cube[4][1] == 'b') {
                break;
            }
            
            else if (cube[1][1] == 'r' && cube[2][1] == 'g' && cube [3][1] != 'o' && cube[4][1] != 'b') {
                turnEdgeYellowB('l');        
            }
            else if (cube[1][1] == 'r' && cube[2][1] != 'g' && cube [3][1] == 'o' && cube[4][1] != 'b') {
                turnEdgeYellowG('c');        
            }
            else if (cube[1][1] == 'r' && cube[2][1] != 'g' && cube [3][1] != 'o' && cube[4][1] == 'b') {
                turnEdgeYellowG('r');        
            }
            
            else if (cube[1][1] == 'r' && cube[2][1] == 'g' && cube [3][1] != 'o' && cube[4][1] != 'b') {
                turnEdgeYellowB('l');        
            }
            else if (cube[1][1] != 'r' && cube[2][1] == 'g' && cube [3][1] == 'o' && cube[4][1] != 'b') {
                turnEdgeYellowR('l');        
            }
            else if (cube[1][1] != 'r' && cube[2][1] == 'g' && cube [3][1] != 'o' && cube[4][1] == 'b') {
                turnEdgeYellowR('c');        
            }
            
            else if (cube[1][1] == 'r' && cube[2][1] != 'g' && cube [3][1] == 'o' && cube[4][1] != 'b') {
                turnEdgeYellowG('c');        
            }
            else if (cube[1][1] != 'r' && cube[2][1] == 'g' && cube [3][1] == 'o' && cube[4][1] != 'b') {
                turnEdgeYellowR('l');        
            }
            else if (cube[1][1] != 'r' && cube[2][1] != 'g' && cube [3][1] == 'o' && cube[4][1] == 'b') {
                turnEdgeYellowR('r');        
            }
            
            else if (cube[1][1] == 'r' && cube[2][1] != 'g' && cube [3][1] != 'o' && cube[4][1] == 'b') {
                turnEdgeYellowG('l');        
            }
            else if (cube[1][1] != 'r' && cube[2][1] == 'g' && cube [3][1] != 'o' && cube[4][1] == 'b') {
                turnEdgeYellowR('c');        
            }
            else if (cube[1][1] != 'r' && cube[2][1] != 'g' && cube [3][1] == 'o' && cube[4][1] == 'b') {
                turnEdgeYellowR('r');        
            }
            cnt++;
        }
        if (cnt >= 100) {
            std::cout << "Кубик не собрать :( AssemblyRightYellowKrest " << cnt << std::endl; 
        }
        else {
            std::cout << "Собран AssemblyRightYellowKrest " << cnt << std::endl;
        }
    }

    void AssemblyRightAnlgeYellow () {
        int cnt = 0; 
        while ((!collectCube()) || (cnt < 100)) {
            for (int k = 0; k < 4; ++k) {
                if (cube[1][0] == 'g' && cube[4][2] == 'r' && cube[0][0] == 'y') {
                    all_turns += "RFb RLb RF RRb RFb RL RF RR ";
                    RFb();
                    RLb();
                    RF();
                    RRb();
                    RFb();
                    RL();
                    RF();
                    RR();
                }
                if (cube[3][0] == 'g' && cube[2][2] == 'r' && cube[0][8] == 'y') {
                    all_turns += "OLb OBb ORb OB OL OBb OR OB ";
                    OLb();
                    OBb();
                    ORb();
                    OB();
                    OL();
                    OBb();
                    OR();
                    OB();
                }
                if (cube[3][2] == 'r' && cube[4][0] == 'g' && cube[0][2] == 'y') {
                    all_turns += "OBb ORb OFb OR OB ORb OF OR ";
                    OBb();
                    ORb();
                    OFb();
                    OR();
                    OB();
                    ORb();
                    OF();
                    OR();
                }
                if (cube[1][0] == 'o' && cube[4][2] == 'g' && cube[0][0] == 'y') {
                    all_turns += "RBb RRb RB RLb RBb RR RB RL ";
                    RBb();
                    RRb();
                    RB();
                    RLb();
                    RBb();
                    RR();
                    RB();
                    RL();
                }
                if (cube[3][2] == 'g' && cube[4][0] == 'o' && cube[0][2] == 'y') {
                    all_turns += "ORb OFb OLb OF OR OFb OL OF ";
                    ORb();
                    OFb();
                    OLb();
                    OF();
                    OR();
                    OFb();
                    OL();
                    OF();
                }
            }
            
            for (int k = 0; k < 4; ++k) {
                if (cube[3][0] == 'y') {
                    all_turns += "GFb GR GF GRb GFb GR GF GRb GU ";
                    GFb();
                    GR();
                    GF();
                    GRb();
                    GFb();
                    GR();
                    GF();
                    GRb();
                    GU();
                }
                else if (cube[2][2] == 'y') {
                    all_turns += "GR GFb GRb GF GR GFb GRb GF GU ";
                    GR();
                    GFb();
                    GRb();
                    GF();
                    GR();
                    GFb();
                    GRb();
                    GF();
                    GU();
                }
                else {
                    if (!collectCube()) {
                        all_turns += "GU ";
                        GU();
                    }
                    else {
                        break;
                    }
                }
            }
            for (int k = 0; k < 4; ++k) {
                if (cube[2][1] == 'g') {
                    break;
                }
                else {
                    all_turns += "GU ";
                    GU();
                }
            }           
            if (collectCube()) {
                break;
            }
            cnt++;
        }
        
        if (cnt >= 100) {
            std::cout << "Кубик не собрать :( AssemblyRightAnlgeYellow " << cnt << std::endl; 
        }
        else {
            std::cout << "Собран AssemblyRightAnlgeYellow " << cnt << std::endl;
        }
        
    }
};



int Patterns () {
    std::cout << "1 - Цветок" << std::endl;
    std::cout << "2 - Шахматная доска" << std::endl;
    std::cout << "3 - Кубик в кубе" << std::endl;
    std::cout << "4 - Кубик в кубе в кубе" << std::endl;
    int var;
    std::cin >> var;
    return var;
}
void spinMenu () {
    std::cout << "Инструкция" << std::endl;                                
    std::cout << "Повороты правой строны (*R)" << std::endl; 
    std::cout << "GR RR OR BR YR WR" << std::endl; 
    std::cout << "Повороты правой стороны обратно (*Rb)" << std::endl; 
    std::cout << "GRb RRb ORb BRb YRb WRb" << std::endl; 
    std::cout << "Повороты левой стороны (*L)" << std::endl; 
    std::cout << "GL RL OL BL YL WL" << std::endl; 
    std::cout << "Повороты левой стороны обратно (*Lb)" << std::endl; 
    std::cout << "GLb RLb OLb BLb YLb WLb" << std::endl; 
    std::cout << "Поворот Вверха (*U)" << std::endl;   
    std::cout << "GU RU OU BU YU WU" << std::endl; 
    std::cout << "Поворот Вверха обратно (*Ub)" << std::endl;   
    std::cout << "GUb RUb OUb BUb YUb WUb" << std::endl; 
    std::cout << " Поворот низа (*D)" << std::endl; 
    std::cout << "GD RD OD BD YD WD" << std::endl; 
    std::cout << " Поворот низа обратно (*Db)" << std::endl; 
    std::cout << "GDb RDb ODb BDb YDb WDb" << std::endl; 
    std::cout << " Поворот переда (*F)" << std::endl; 
    std::cout << "GF RF OF BF YF WF" << std::endl; 
    std::cout << " Поворот переда обратно (*Fb)" << std::endl; 
    std::cout << "GFb RFb OFb BFb YFb WFb" << std::endl; 
    std::cout << "поворот зада (*B)" << std::endl; 
    std::cout << "GB RB OB BB YB WB" << std::endl; 
    std::cout << "поворот зада обратно (*Bb)" << std::endl; 
    std::cout << "GBb RBb OBb BBb YBb WBb" << std::endl; 
}

int menu () {
    std::cout << "Выберите действие: " << std::endl;
    std::cout << "0 - Выход из программы" << std::endl;
    std::cout << "1 - Сохранить в файл кубик" << std::endl;
    std::cout << "2 - Читать из файла кубик" << std::endl;
    std::cout << "3 - Показать кубик" << std::endl;
    std::cout << "4 - Крутить в ручную кубик" << std::endl;
    std::cout << "5 - Перемешать кубик" << std::endl;
    std::cout << "6 - Собрать кубик" << std::endl;
    std::cout << "7 - Узоры" << std::endl;
    int var;
    std::cin >> var;
    return var;
}

int main () {
    Cube cube;   
    int var;
    while (true) {
        var = menu();
        if (var == 0) {
            break;
        }
        else if (var == 1) {
            cube.SaveCube();
        }
        else if (var == 2) {
            cube.ReadCube();             
        }
        else if (var == 3) {
            cube.ShowCube();
        }
        else if (var == 4) {
            spinMenu();        
            cube.SpinCube();
        }
        else if (var == 5) {
            cube.RandomSpinCube();
        }
        else if (var == 6) {
            cube.AssemblyCube();
        }
        else if (var == 7) {
            int x;
            x = Patterns();
            if (x == 1) {
                cube.Flower();
                cube.ShowCube();
            }
            else if (x == 2) {
                cube.Chess();
                cube.ShowCube();
            }
            else if (x == 3) {
                cube.CubeInCube();
                cube.ShowCube();
            }
            else if (x == 4) {
                cube.CubeInCubeInCube();
                cube.ShowCube();
            }
        }
        else {
            std::cout << "Неверная цифра" << std::endl;
        }
    }
    return 0;
}



//good //- Сохранение и чтение состояния кубика рубика из файла
//good //- Проверка корректности текущего состояния (инвариант состояний кубика)
//good //- Вывод в консоль текущего состояния
//good //- Вращение граней кубика рубика с помощью вводимых команд
//good //- Генерация случайного состояния Кубика Рубика, корректного с точки зрения инварианта состояний
//good //- Нахождения “решения” для текущего состояния в виде последовательности поворотов граней
//good //- Визуализация

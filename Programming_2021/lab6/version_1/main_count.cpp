#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>


// yellow - y
// orange - o
// green -  g
// red -    r
// blue -   b
// white -  w


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
    
    // сохранение кубика в файл
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
        std::cout << "save cube" << std::endl;
        ShowCube();
        fout.close();
    }
    
    // считать кубик из файла
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
            //Инструкция
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
    }

    int AssemblyCube () {
        bool flag = true;
        flag = flag & AssemblyWhiteKrest();
        flag = flag & AssemblyAngleWhite(); 
        flag = flag & AssemblyF2L(); 
        flag = flag & AssemblyYellowKrest();
        flag = flag & AssemblyRightYellowKrest(); 
        flag = flag & AssemblyRightAnlgeYellow();
        return flag;
    }
    ~Cube() {};


private:
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
    //      0 1 2
    //      3 4 5
    //      6 7 8
    //0 1 2|0 1 2|0 1 2|0 1 2
    //3 4 5|3 4 5|3 4 5|3 4 5
    //6 7 8|6 7 8|6 7 8|6 7 8
    //      0 1 2
    //      3 4 5
    //      6 7 8
    
    //      y y y
    //      y y y
    //      y y y
    //r r r|g g g|o o o|b b b
    //r r r|g g g|o o o|b b b
    //r r r|g g g|o o o|b b b
    //      w w w
    //      w w w
    //      w w w
                                                                                                                                                                                        
    //Инструкция
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
                    RU();
                }
                else {
                    break;
                }
            }
            if (checkKrest()) {
                return;
            }
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
                    GU();
                }
                else {
                    break;
                }
            }
            if (checkKrest()) {
                return;
            }
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
                    OU();
                }
                else {
                    break;
                }
            }
            if (checkKrest()) {
                return;
            }
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
                    BU();
                }
                else {
                    break;
                }
            }
            if (checkKrest()) {
                return;
            }
            BF();
            BF();
        }
    }
    
    bool AssemblyWhiteKrest () {
        char c1, c2; // c1 - другой цвет, c2 - белый
        int cnt = 0;
        while ((!checkKrest()) && (cnt < 100)) {
            for (int k = 0; k < 9; ++k) {
                // WHITE
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
                    RF();
                    RR();
                    RU();
                    RRb();
                    goody(c1, c2);
                }
                c1 = cube[4][5];
                c2 = cube[1][3];
                if (c2 == 'w') {
                    RLb();   
                    RUb();  
                    RL();
                    goody(c1, c2);
                }
                c1 = cube[2][3];
                c2 = cube[1][5];
                if (c2 == 'w') {
                    RR();   
                    RU();  
                    RRb();
                    goody(c1, c2);
                }
                c1 = cube[5][3];
                c2 = cube[1][7];
                if (c2 == 'w') {
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
                    GF();
                    GR();
                    GU();
                    GRb();
                    goody(c1, c2);
                }
                c1 = cube[1][5];
                c2 = cube[2][3];
                if (c2 == 'w') {
                    GLb();   
                    GUb();  
                    GL();
                    goody(c1, c2);
                }
                c1 = cube[3][3];
                c2 = cube[2][5];
                if (c2 == 'w') {
                    GR();   
                    GU();  
                    GRb();
                    goody(c1, c2);
                }
                c1 = cube[5][1];
                c2 = cube[2][7];
                if (c2 == 'w') {
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
                    OF();
                    OR();
                    OU();
                    ORb();
                    goody(c1, c2);
                }
                c1 = cube[2][5];
                c2 = cube[3][3];
                if (c2 == 'w') {
                    OLb();   
                    OUb();  
                    OL();
                    goody(c1, c2);
                }
                c1 = cube[4][3];
                c2 = cube[3][5];
                if (c2 == 'w') {
                    OR();   
                    OU();  
                    ORb();
                    goody(c1, c2);
                }
                c1 = cube[5][5];
                c2 = cube[3][7];
                if (c2 == 'w') {
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
                    BF();
                    BR();
                    BU();
                    BRb();
                    goody(c1, c2);
                }
                c1 = cube[3][5];
                c2 = cube[4][3];
                if (c2 == 'w') {
                    BLb();   
                    BUb();  
                    BL();
                    goody(c1, c2);
                }
                c1 = cube[1][3];
                c2 = cube[4][5];
                if (c2 == 'w') {
                    BR();   
                    BU();  
                    BRb();
                    goody(c1, c2);
                }
                c1 = cube[5][7];
                c2 = cube[4][7];
                if (c2 == 'w') {
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
                    GF();
                    GF();
                    goody(c1, c2);
                }
                c1 = cube[1][7];
                c2 = cube[5][3];
                if (c2 == 'w' && c1 != cube[1][4]) {
                    RF();
                    RF();
                    goody(c1, c2);
                }
                c1 = cube[3][7];
                c2 = cube[5][5];
                if (c2 == 'w' && c1 != cube[3][4]) {
                    OF();
                    OF();
                    goody(c1, c2);
                }
                c1 = cube[4][7];
                c2 = cube[5][7];
                if (c2 == 'w' && c1 != cube[4][4]) {
                    OF();
                    OF();
                    goody(c1, c2);
                }
            }
            cnt++;
        }
        
        if (cnt < 100) {
            return true;
        }
        else {
            return false;
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
            RU();
            RR();
            RUb();
            RRb();
        }
        if ((c1 == 'r') && (c2 == 'w') && (c3 == 'g')) {
            RR();
            RU();
            RRb();
            RUb();
        }
        if ((c1 == 'g') && (c2 == 'r') && (c3 == 'w')) {
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
            GU();
            GR();
            GUb();
            GRb();
        }
        else if ((c1 == 'g') && (c2 == 'w') && (c3 == 'o')) {
            GR();
            GU();
            GRb();
            GUb();
        }
        if ((c1 == 'o') && (c2 == 'g') && (c3 == 'w')) {
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
            OU();
            OR();
            OUb();
            ORb();
        }
        if ((c1 == 'o') && (c2 == 'w') && (c3 == 'b')) {
            OR();
            OU();
            ORb();
            OUb();
        }
        if ((c1 == 'b') && (c2 == 'o') && (c3 == 'w')) {
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
            BU();
            BR();
            BUb();
            BRb();
        }
        else if ((c1 == 'b') && (c2 == 'w') && (c3 == 'r')) {
            BR();
            BU();
            BRb();
            BUb();
        }
        else if ((c1 == 'r') && (c2 == 'b') && (c3 == 'w')) {
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
    bool AssemblyAngleWhite () {
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
                    RU();
                    turnAngleR(cube[2][2], cube[3][0], cube[0][8]);
                }
                if (cube[2][2] == c2 && cube[3][0] == c1 && cube[0][8] == c3) {
                    RU();
                    turnAngleR(cube[2][2], cube[3][0], cube[0][8]);
                }
                if (cube[2][2] == c1 && cube[3][0] == c3 && cube[0][8] == c2) {
                    RU();
                    turnAngleR(cube[2][2], cube[3][0], cube[0][8]);
                }
                
                if (cube[3][2] == c3 && cube[4][0] == c2 && cube[0][2] == c1) {
                    RUb();
                    RUb();
                    turnAngleR(cube[3][2], cube[4][0], cube[0][2]);
                }
                if (cube[3][2] == c2 && cube[4][0] == c1 && cube[0][2] == c3) {
                    RUb();
                    RUb();
                    turnAngleR(cube[3][2], cube[4][0], cube[0][2]);
                }
                if (cube[3][2] == c1 && cube[4][0] == c3 && cube[0][2] == c2) {
                    RUb();
                    RUb();
                    turnAngleR(cube[3][2], cube[4][0], cube[0][2]);
                }
                
                if (cube[4][2] == c3 && cube[1][0] == c2 && cube[0][0] == c1) {
                    RUb();
                    turnAngleR(cube[4][2], cube[1][0], cube[0][0]);
                }
                if (cube[4][2] == c2 && cube[1][0] == c1 && cube[0][0] == c3) {
                    RUb();
                    turnAngleR(cube[4][2], cube[1][0], cube[0][0]);
                }
                if (cube[4][2] == c1 && cube[1][0] == c3 && cube[0][0] == c2) {
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
                    RUb(); 
                    turnAngleG(cube[1][2], cube[2][0], cube[0][6]);
                }
                if (cube[1][2] == c2 && cube[2][0] == c1 && cube[0][6] == c3) {
                    RUb(); 
                    turnAngleG(cube[1][2], cube[2][0], cube[0][6]);
                }
                if (cube[1][2] == c1 && cube[2][0] == c3 && cube[0][6] == c2) {
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
                    GUb();
                    turnAngleG(cube[3][2], cube[4][0], cube[0][2]);
                }
                if (cube[3][2] == c2 && cube[4][0] == c1 && cube[0][2] == c3) {
                    GUb();
                    turnAngleG(cube[3][2], cube[4][0], cube[0][2]);
                }
                if (cube[3][2] == c1 && cube[4][0] == c3 && cube[0][2] == c2) {
                    GUb();
                    turnAngleG(cube[3][2], cube[4][0], cube[0][2]);
                }
                
                if (cube[4][2] == c3 && cube[1][0] == c2 && cube[0][0] == c1) {
                    GUb();
                    GUb();
                    turnAngleG(cube[4][2], cube[1][0], cube[0][0]);
                }
                if (cube[4][2] == c2 && cube[1][0] == c1 && cube[0][0] == c3) {
                    GUb();
                    GUb();
                    turnAngleG(cube[4][2], cube[1][0], cube[0][0]);
                }
                if (cube[4][2] == c1 && cube[1][0] == c3 && cube[0][0] == c2) {
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
                    OUb(); 
                    OUb(); 
                    turnAngleO(cube[1][2], cube[2][0], cube[0][6]);
                }
                if (cube[1][2] == c2 && cube[2][0] == c1 && cube[0][6] == c3) {
                    OUb(); 
                    OUb(); 
                    turnAngleO(cube[1][2], cube[2][0], cube[0][6]);
                }
                if (cube[1][2] == c1 && cube[2][0] == c3 && cube[0][6] == c2) {
                    OUb(); 
                    OUb(); 
                    turnAngleO(cube[1][2], cube[2][0], cube[0][6]);
                }
                
                if (cube[2][2] == c3 && cube[3][0] == c2 && cube[0][8] == c1) {
                    OUb(); 
                    turnAngleO(cube[2][2], cube[3][0], cube[0][8]);
                }
                if (cube[2][2] == c2 && cube[3][0] == c1 && cube[0][8] == c3) {
                    OUb(); 
                    turnAngleO(cube[2][2], cube[3][0], cube[0][8]);
                }
                if (cube[2][2] == c1 && cube[3][0] == c3 && cube[0][8] == c2) {
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
                    OUb();
                    turnAngleO(cube[4][2], cube[1][0], cube[0][0]);
                }
                if (cube[4][2] == c2 && cube[1][0] == c1 && cube[0][0] == c3) {
                    OUb();
                    turnAngleO(cube[4][2], cube[1][0], cube[0][0]);
                }
                if (cube[4][2] == c1 && cube[1][0] == c3 && cube[0][0] == c2) {
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
                    BU(); 
                    turnAngleB(cube[1][2], cube[2][0], cube[0][6]);
                }
                if (cube[1][2] == c2 && cube[2][0] == c1 && cube[0][6] == c3) {
                    BU(); 
                    turnAngleB(cube[1][2], cube[2][0], cube[0][6]);
                }
                if (cube[1][2] == c1 && cube[2][0] == c3 && cube[0][6] == c2) {
                    BU(); 
                    turnAngleB(cube[1][2], cube[2][0], cube[0][6]);
                }
                
                if (cube[2][2] == c3 && cube[3][0] == c2 && cube[0][8] == c1) {
                    BUb(); 
                    BUb(); 
                    turnAngleB(cube[2][2], cube[3][0], cube[0][8]);
                }
                if (cube[2][2] == c2 && cube[3][0] == c1 && cube[0][8] == c3) {
                    BUb(); 
                    BUb(); 
                    turnAngleB(cube[2][2], cube[3][0], cube[0][8]);
                }
                if (cube[2][2] == c1 && cube[3][0] == c3 && cube[0][8] == c2) {
                    BUb(); 
                    BUb(); 
                    turnAngleB(cube[2][2], cube[3][0], cube[0][8]);
                }
                
                if (cube[3][2] == c3 && cube[4][0] == c2 && cube[0][2] == c1) {
                    BUb(); 
                    turnAngleB(cube[3][2], cube[4][0], cube[0][2]);
                }
                if (cube[3][2] == c2 && cube[4][0] == c1 && cube[0][2] == c3) {
                    BUb(); 
                    turnAngleB(cube[3][2], cube[4][0], cube[0][2]);
                }
                if (cube[3][2] == c1 && cube[4][0] == c3 && cube[0][2] == c2) {
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
        
        if (cnt < 100) {
            return true;
        }
        else {
            return false;
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

    bool AssemblyF2L () {
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
        
        if (cnt < 100) {
            return true;
        }
        else {
            return false;
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
            GF();
            GU();
            GR();
            GUb();
            GRb();
            GFb();
        }
        else if (x == 2) {
            GF();
            GR();
            GU();
            GRb();
            GUb();
            GFb();
        }
    }

    bool AssemblyYellowKrest () {
        int cnt = 0;
        while ((!checkYellowKrest()) && (cnt < 100)) {
            if (cube[0][1] == 'y' && cube[0][3] == 'y' && cube[0][5] != 'y' && cube[0][7] != 'y') {
                turnYellow(1);
            }
            else if (cube[0][1] == 'y' && cube[0][3] != 'y' && cube[0][5] == 'y' && cube[0][7] != 'y') {
                GUb();
                turnYellow(1);
            }
            else if (cube[0][1] != 'y' && cube[0][3] != 'y' && cube[0][5] == 'y' && cube[0][7] == 'y') {
                GUb();
                GUb();
                turnYellow(1);
            }
            else if (cube[0][1] != 'y' && cube[0][3] == 'y' && cube[0][5] != 'y' && cube[0][7] == 'y') {
                GU();
                turnYellow(1);
            }
            else if (cube[0][1] != 'y' && cube[0][3] == 'y' && cube[0][5] == 'y' && cube[0][7] != 'y') {
                turnYellow(2);
            }
            else if (cube[0][1] == 'y' && cube[0][3] != 'y' && cube[0][5] != 'y' && cube[0][7] == 'y') {
                GU();
                turnYellow(2);
            }
            else if (cube[0][1] != 'y' && cube[0][3] != 'y' && cube[0][5] != 'y' && cube[0][7] != 'y') {
                turnYellow(1);
                GU();
                turnYellow(2);
            }
            else if (cube[0][1] == 'y' && cube[0][3] == 'y' && cube[0][5] == 'y' && cube[0][7] == 'y') {
                break;
            }
            cnt++;
        }
        
        if (cnt < 100) {
            return true;
        }
        else {
            return false;
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

    bool AssemblyRightYellowKrest () {
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
        
        if (cnt < 100) {
            return true;
        }
        else {
            return false;
        }
    }

    bool AssemblyRightAnlgeYellow () {
        int cnt = 0; 
        while ((!collectCube()) || (cnt < 100)) {
            for (int k = 0; k < 4; ++k) {
                if (cube[1][0] == 'g' && cube[4][2] == 'r' && cube[0][0] == 'y') {
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
                    GU();
                }
            }           
            if (collectCube()) {
                break;
            }
            cnt++;
        }
        
        if (cnt < 100) {
            return true;
        }
        else {
            return false;
        }
    }
    
    //Инструкция
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
};

int main () {
    Cube cube;   
        
    int count = 0;
    int score = 0;
    int n;
    std::cout << "Введите количество сборок: ";
    std::cin >> n;

    while (score < n) {
        cube.RandomSpinCube();
        count += cube.AssemblyCube();
        ++score;
    }
    
    std::cout << "кубик собран " << count << "/" << score << std::endl;

    return 0;
}


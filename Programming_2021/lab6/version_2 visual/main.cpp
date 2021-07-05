#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <ctime>
#include <cstdlib>
//on Windows
//#include <glut.h>
//on Linux
#include <GL/glut.h>


// команда для компилирования в терминале
// g++ -Wall -o main main.cpp -lglut -lGLU -lGL


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


// развёртка кубика по цветам
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


class Small_Cube {
private:
	unsigned char color_[3];

public: 
	// шесть граней куба - шесть цветов
	unsigned int color[6];
	// размер ребра
	double size;

    void rotateZ () {
		unsigned int tmp = color[5];
		color[5] = color[3];
		color[3] = color[4];
		color[4] = color[2];
		color[2] = tmp;
	}
    
    void rotateY () {
		unsigned int tmp = color[2];
		color[2] = color[1];
		color[1] = color[3];
		color[3] = color[0];
		color[0] = tmp;
	}

	void rotateX () {
		unsigned int tmp = color[0];
		color[0] = color[4];
		color[4] = color[1];
		color[1] = color[5];
		color[5] = tmp;
	}

	void setColor (int i, int color) {
		this->color[i] = color;
	}

	unsigned char *at(int i) {
		// разбиваем color[i] на 3 составляющих
		// для 0xFF0000 RGB(FF, 0, 00) - красный цвет;
		color_[0] = color[i] >> 16;
		color_[1] = color[i] >> 8;
		color_[2] = color[i];
		return color_;
	}

	// отрисовка куба:
	// устанавливаем цвет и нормали
	void draw() {
		glPushMatrix();
		glBegin(GL_QUADS);

		// верх
		glColor3ubv(at(0));
		glNormal3f(0, 0, 1);
		glVertex3f(size, size, size);
		glVertex3f(0, size, size);
		glVertex3f(0, 0, size);
		glVertex3f(size, 0, size);

		// низ
		glColor3ubv(at(1));
		glNormal3f(0, 0, -1);
		glVertex3f(size, 0, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(0, size, 0);
		glVertex3f(size, size, 0);

		// спереди
		glColor3ubv(at(2));
		glNormal3f(0, -1, 0);
		glVertex3f(size, 0, size);
		glVertex3f(0, 0, size);
		glVertex3f(0, 0, 0);
		glVertex3f(size, 0, 0);

		// сзади
		glColor3ubv(at(3));
		glNormal3f(0, 1, 0);
		glVertex3f(size, size, 0);
		glVertex3f(0, size, 0);
		glVertex3f(0, size, size);
		glVertex3f(size, size, size);

		// слева
		glColor3ubv(at(4));
		glNormal3f(-1, 0, 0);
		glVertex3f(0, size, size);
		glVertex3f(0, size, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 0, size);

		// справа
		glColor3ubv(at(5));
		glNormal3f(1, 0, 0);
		glVertex3f(size, size, 0);
		glVertex3f(size, size, size);
		glVertex3f(size, 0, size);
		glVertex3f(size, 0, 0);

		glEnd();
		glPopMatrix();
	}

	// отрисовка куба со смещением (x, y, z)
	void draw (double x, double y, double z) {
		glPushMatrix();
		glTranslated(x, y, z);
		draw();
		glPopMatrix();
	}
};



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
        std::cout << "Save cube" << std::endl;
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
        count_turns = 0;
        all_turns = "";
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
    
    // узоры
    void Flower () {
        int x = rand() % 6;
        if (x == 0) {
            YR();
            YLb();
            YD();
            YUb();
            YF();
            YBb();
            YR();
            YLb();
        }
        else if (x == 1) {
            RR();
            RLb();
            RD();
            RUb();
            RF();
            RBb();
            RR();
            RLb();
        }
        else if (x == 2) {
            GR();
            GLb();
            GD();
            GUb();
            GF();
            GBb();
            GR();
            GLb();
        }
        else if (x == 3) {
            OR();
            OLb();
            OD();
            OUb();
            OF();
            OBb();
            OR();
            OLb();
        }
        else if (x == 4) {
            BR();
            BLb();
            BD();
            BUb();
            BF();
            BBb();
            BR();
            BLb();
        }
        else if (x == 5) {
            WR();
            WLb();
            WD();
            WUb();
            WF();
            WBb();
            WR();
            WLb();
        }
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

    // ручные повороты через клавиатуру 
    void RoatateGR() {
        GR();
    }
    void RoatateGL() {
        GL();
    }
    void RoatateGU() {
        GU();
    }
    void RoatateGF() {
        GF();
    }
    void RoatateGB() {
        GB();
    }
    void RoatateGD() {
        GD();
    }

    // визуализация
    // номер грани для поворотов
    int current;
    
    // размер кубика
    const int CUBE_SIZE = 13;
    int TIMER = 5;
    
    // проекции угла поворота на оси
    int xRot = 24; 
    int yRot = 44; 
    int zRot = 0;
    // отдаление
    double translateZ = -35.0;
    // скорость поворота, должно быть 90 % speed_turn = 0 
    // не использовать цифры не кратные 90
    int speed_turn = 6; 

    void clear(double size, unsigned int *color) {
        this->size = size;
		current = -1;

		int i, j, k;
		for(i = 0; i < 6; i++) {
			this->color[i] = color[i];
        }

		// верх
		for(i = 0; i < 3; i++) {
			for(j = 0; j < 3; j++) {
				a[i][j][2].setColor(0, color[0]);
            }
        }
		// низ
		for(i = 0; i < 3; i++) {
			for(j = 0; j < 3; j++) {
				a[i][j][0].setColor(1, color[1]);
            }
        }
		// спереди
		for(k = 0; k < 3; k++) {
 			for(j = 0; j < 3; j++) {
				a[j][0][k].setColor(2, color[2]);
            }
        }
		// сзади
		for(k = 0; k < 3; k++) {
			for(j = 0; j < 3; j++) {
				a[j][2][k].setColor(3, color[3]);
            }
        }
		// слева
		for(i = 0; i < 3; i++) {
 			for(k = 0; k < 3; k++) {
				a[0][k][i].setColor(4, color[4]);
            }
        }
		// справа
		for(i = 0; i < 3; i++) {
			for(k = 0; k < 3; k++) {
				a[2][k][i].setColor(5, color[5]);
            }
        }
		// размеры мелких деталей
		for(i = 0; i < 3; i++) {
			for(j = 0; j < 3; j++) {
				for(k = 0; k < 3; k++) {
					a[i][j][k].size = (size / 3.0) * 0.95;
                }
            }
        }
        for (int i = 0; i < 6; ++i) {
            std::vector <char> ch;
            ch = {'y', 'r', 'g', 'o', 'b', 'w'};
            for (int j = 0; j < 9; ++j) {
                cube[i][j] = ch[i];
            }
        }
    }

	void draw () {
		const double K = 0.65;
		// корпус - это просто куб черного цвета, размер которого равен K*size
		glPushMatrix();
		glColor3f(0, 0, 0);
		glTranslatef(((1.0 - K)/2)*size + K*size/2, ((1.0 - K)/2)*size + K*size/2, ((1.0 - K)/2)*size + K*size/2);
		glutSolidCube(size * K);
		glPopMatrix();

		for (int i = 0; i < 3; ++i) {
		    for (int j = 0; j < 3; ++j) {
		        for (int k = 0; k < 3; ++k) {
                    ok[i][j][k] = true;
                }
            }
        }
        
        if (current != -1) {
			glPushMatrix();
			int i, j, k;

			if (current == 0 || current == 1) {
				k = (current & 1) * 2;
				for (i = 0; i < 3; i++) {
					for (j = 0; j < 3; j++) {
						ok[i][j][k] = false;
                    }
                }
				glTranslated(size / 2, size / 2, 0);   // сдвигаемся к центру
				glRotatef(rotate[current], 0, 0, 1);   // крутим
				glTranslated(-size / 2, -size / 2, 0); // сдвигаемся обратно
				// рисуем
				for (i = 0; i < 3; i++) {
					for (j = 0; j < 3; j++) {
						a[i][j][k].draw(size / 3 * i, size / 3 * j, size / 3 * k);
                    }
                }
			}
			else if (current == 2 || current == 3) {
				j = (current & 1) * 2;
				for (i = 0; i < 3; i++) {
					for (k = 0; k < 3; k++) {
						ok[i][j][k] = false;
                    }
                }

				glTranslated(size / 2, 0, size / 2);
				glRotatef(rotate[current], 0, 1, 0);
				glTranslated(-size / 2, 0, -size / 2);
				for (i = 0; i < 3; i++) {
					for (k = 0; k < 3; k++) {
						a[i][j][k].draw(size / 3 * i, size / 3 * j, size / 3 * k);
                    }
                }
			}
			else if (current == 4 || current == 5) {
				i = (current & 1) * 2;
				for (j = 0; j < 3; j++) {
					for (k = 0; k < 3; k++) {
						ok[i][j][k] = false;
                    }
                }

				glTranslated(0, size / 2, size / 2);
				glRotatef(rotate[current], 1, 0, 0);
				glTranslated(0, -size / 2, -size / 2);
				for (j = 0; j < 3; j++) {
					for (k = 0; k < 3; k++) {
						a[i][j][k].draw(size / 3 * i, size / 3 * j, size / 3 * k);
                    }
                }
			}
			glPopMatrix();
		}

		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				for (int k = 0; k < 3; k++) {
					if (ok[i][j][k]) {
						a[i][j][k].draw(size / 3 * i, size / 3 * j, size / 3 * k);
                    }
                }
            }
        }
	}

    void display () {
    	glPushMatrix();
    	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    	glColor3f(1, 0, 0);
    	glTranslatef(0, 0, translateZ);
    	glRotatef(xRot, 1, 0, 0);
    	glRotatef(yRot, 0, 1, 0);
    	glTranslatef(CUBE_SIZE / -2.0, CUBE_SIZE / -2.0, CUBE_SIZE / -2.0);
    	draw();
    	glPopMatrix();
    	glutSwapBuffers();
    }

	void rot90 (int idx, int sign) {
		int i, j, k;
		// sign задаётся в зависимости он направления
		// sign = -1, sign = 1
		// если sign = -1, значит крутим 3 раза
		if (sign == -1) {
			sign = 3;
        }
        
        while (sign--) {
            if (idx == 0) {
				k = 0;
				// копируем повёрнутую на 90 градусов верхнюю/нижнюю грань
				// в массив tmp, затем грани присваиваем tmp
				// и не забываем повернуть каждую деталь этой грани
				for (i = 0; i < 3; ++i) {
					for (j = 0; j < 3; ++j) {
						tmp[j][2 - i] = a[i][j][k];
                    }
                }
				for (i = 0; i < 3; ++i) {
					for (j = 0; j < 3; ++j) {
						tmp[i][j].rotateZ(); 
                        a[i][j][k] = tmp[i][j];
                    }
                }
			}
            
            else if (idx == 1) {
				k = 2;
				for (i = 0; i < 3; ++i) {
					for (j = 0; j < 3; ++j) {
						tmp[j][2 - i] = a[i][j][k];
                    }
                }
				for (i = 0; i < 3; ++i) {
					for (j = 0; j < 3; ++j) {
						tmp[i][j].rotateZ(); 
                        a[i][j][k] = tmp[i][j];
                    }
                }
			}
            
			else if (idx == 2) {
				j = 0;
				for(i = 0; i < 3; ++i)
					for(k = 0; k < 3; ++k)
						tmp[k][2 - i] = a[i][j][k];
				for (i = 0; i < 3; ++i) {
					for (k = 0; k < 3; ++k) {
						tmp[i][k].rotateX(); 
                        a[i][j][k] = tmp[i][k];
                    }
                }
			}
           
			else if (idx == 3) {
				j = 2;
				for(i = 0; i < 3; ++i)
					for(k = 0; k < 3; ++k)
						tmp[k][2 - i] = a[i][j][k];
				for (i = 0; i < 3; ++i) {
					for (k = 0; k < 3; ++k) {
						tmp[i][k].rotateX(); 
                        a[i][j][k] = tmp[i][k];
                    }
                }
			}
            
			else if (idx == 4) {
				i = 0;
				for (j = 0; j < 3; ++j) {
					for (k = 0; k < 3; ++k) {
						tmp[k][2 - j] = a[i][j][k];
                    }
                }
				for (j = 0; j < 3; ++j) {
					for (k = 0; k < 3; ++k) {
						tmp[j][k].rotateY();
                        a[i][j][k] = tmp[j][k];
                    }
                }
			}
            
			else if (idx == 5) {
				i = 2;
				for (j = 0; j < 3; ++j) {
					for (k = 0; k < 3; ++k) {
						tmp[k][2 - j] = a[i][j][k];
                    }
                }
				for (j = 0; j < 3; ++j) {
					for (k = 0; k < 3; ++k) {
						tmp[j][k].rotateY();
                        a[i][j][k] = tmp[j][k];
                    }
                }
			}
		}
	}
    
    void timer (int RorL, int) {
        if (current != -1) {
            display();
            Rotate(current, speed_turn, RorL);
        }
    }
    void Rotate(int idx, int angle, int RorL) {
        if (current == -1 || current == idx) {
			if (RorL == -1) {
                rotate[idx] -= angle;
            }
            else if (RorL == 1) {
                rotate[idx] += angle;
            }

			if (rotate[idx] % 90 != 0) {
                current = idx;
                timer(RorL, 0);
            }
			else {
				// угол стал кратным 90, поварачиваем на массиве
				if ((rotate[idx] < 0) ^ (current == 2 || current == 3)) {
					rot90(idx, 1);
                }
                else {
					rot90(idx, -1);
                }
                rotate[idx] = 0;
				current = -1;
			}
		}
	}

    ~Cube() {};


private:
    std::string all_turns;
    unsigned count_turns;
    std::vector <std::vector <char>> cube; 
    
	bool ok[3][3][3];
	Small_Cube tmp[3][3];
	// 27 частей
	Small_Cube a[3][3][3];
	// храним угол поворота каждой грани
	int rotate[6];
	// размер кубика-рубика
	double size;
	// цвета граней
	unsigned int color[6];


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
                    (first == c && second == b && third == a) && 
                    checkCol(a, b) && checkCol(a, c) && checkCol(b, c)) 
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
        Rotate(5, speed_turn, -1);
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
        Rotate(1, speed_turn, -1);
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
        Rotate(0, speed_turn, 1);
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
        Rotate(4, speed_turn, 1);
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
        Rotate(5, speed_turn, 1);
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
        Rotate(1, speed_turn, 1);
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
        Rotate(0, speed_turn, -1);
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
        Rotate(4, speed_turn, -1);
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
        Rotate(3, speed_turn, -1);
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
        Rotate(3, speed_turn, 1);
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
        Rotate(2, speed_turn, 1);
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
        Rotate(2, speed_turn, -1);
    }

    void RDb () {
        GDb();
    } 

    void ODb () {
        GDb();
    }

    void BDb () {
        GDb();
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
                        all_turns += "111GU ";
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


// цвета кубика Рубика
// орентация идёт от зелёного цвета
//                        перед      зад        низ      вверх     лево       право
unsigned int color[6] = {0x00FF00, 0x0000FF, 0xFFFFFF, 0xFFFF00, 0xFF0000, 	0xFF6800};
 
//0xFFFF00 - yellow
//0x0000FF - blue
//0x00FF00 - green
//0xFF0000 - red
//0xFF6800 - orange
//0xFFFFFF - white

Cube cube;

void display () {
	glPushMatrix();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1, 0, 0);
	glTranslatef(0, 0, cube.translateZ);
	glRotatef(cube.xRot, 1, 0, 0);
	glRotatef(cube.yRot, 0, 1, 0);
	glTranslatef(cube.CUBE_SIZE / -2.0, cube.CUBE_SIZE / -2.0, cube.CUBE_SIZE / -2.0);
	cube.draw();
	glPopMatrix();
	glutSwapBuffers();
}

void reshape (int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLfloat fAspect = (GLfloat)w/(GLfloat)h;
    gluPerspective(60, fAspect, 1, 1000.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void init () {
	// цвет фона
    glClearColor(0.0, 0.0, 0.0, 0.0);

	// освещение
	float mat_specular[] = {0.3, 0.3, 0.3, 0};
	float diffuseLight[] = {0.2, 0.2, 0.2, 1};
	float ambientLight[] = {0.9, 0.9, 0.9, 1.0};
	glShadeModel(GL_SMOOTH);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMateriali(GL_FRONT, GL_SHININESS, 128);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);

	// инициализируем куб
	cube.clear(cube.CUBE_SIZE, color);
}


void specialKeys (int key, int, int) {
	// клавиши влево/вправо вращают по Y
	// клавиши вверх/вниз вращают по X
	// F1 - возвращает в начальное положение
	if (key == GLUT_KEY_DOWN) {
		cube.xRot += 3;
		if (cube.xRot >= 360)
			cube.xRot -= 360;
		glutPostRedisplay();
	}

	if (key == GLUT_KEY_UP) {
		cube.xRot -= 3;
		if (cube.xRot < 0)
			cube.xRot += 360;
        glutPostRedisplay();
	}

	if (key == GLUT_KEY_RIGHT) {
		cube.yRot += 3;
		if (cube.yRot >= 360)
			cube.yRot -= 360;
		glutPostRedisplay();
	}

	if (key == GLUT_KEY_LEFT) {
		cube.yRot -= 3;
		if (cube.yRot < 0)
			cube.yRot += 360;
		glutPostRedisplay();
	}

	if (key == GLUT_KEY_HOME) {
		cube.translateZ += 5;
		glutPostRedisplay();
	}

	if (key == GLUT_KEY_END) {
		cube.translateZ -= 5;
		glutPostRedisplay();
	}

	if (key == GLUT_KEY_F1) {
		cube.clear(cube.CUBE_SIZE, color);
        glutPostRedisplay();
    }
	if (key == GLUT_KEY_F2) {
        cube.xRot = 24; 
        cube.yRot = 44; 
        cube.zRot = 0;
        cube.translateZ = -35.0;
        glutPostRedisplay();
    }
}


void keys (unsigned char key, int, int) {
	if (cube.current == -1 && key == '1') {
        cube.RoatateGR();
    }
	else if (cube.current == -1 && key == '2') {
        cube.RoatateGL();
    }
	else if (cube.current == -1 && key == '3') {
        cube.RoatateGU();
    }
	else if (cube.current == -1 && key == '4') {
        cube.RoatateGF();
    }
	else if (cube.current == -1 && key == '5') {
        cube.RoatateGB();
    }
	else if (cube.current == -1 && key == '6') {
        cube.RoatateGD();
    }
}

void timer (int) {
	glutTimerFunc(cube.TIMER, timer, 0);
    if (cube.current != -1) {
		cube.Rotate(cube.current, cube.speed_turn, -1);
    }
	display();
}

void processMenu (int option) {
	switch (option) {
		case 1:
            cube.RandomSpinCube();
            break;
		case 2:
            cube.AssemblyCube();
			break;
		case 3:
		    cube.clear(cube.CUBE_SIZE, color);
            cube.Flower();
            break;
        case 4:
		    cube.clear(cube.CUBE_SIZE, color);
            cube.Chess();
            break;
        case 5:
		    cube.clear(cube.CUBE_SIZE, color);
            cube.CubeInCube();
            break;
        case 6:
		    cube.clear(cube.CUBE_SIZE, color);
            cube.CubeInCubeInCube();
            break;
	}
}

void createGLUTMenus () {
    glutCreateMenu(processMenu);

    glutAddMenuEntry("Random Spin Cube", 1);
	glutAddMenuEntry("Assembly Cube", 2);

	glutAddMenuEntry("Flower", 3);
	glutAddMenuEntry("Chess", 4);
	glutAddMenuEntry("Cube In Cube", 5);
	glutAddMenuEntry("Cube In Cube In Cube", 6);
    
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main (int argc, char **argv) {
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 700);
	glutInitWindowPosition(1, 1);
	glutCreateWindow("Cube");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keys);
	glutTimerFunc(cube.TIMER, timer, 0);
	glutSpecialFunc(specialKeys);
    createGLUTMenus();	
    glutMainLoop();
    return 0;
}



//good //- Сохранение и чтение состояния кубика рубика из файла
//good //- Проверка корректности текущего состояния (инвариант состояний кубика)
//good //- Вывод в консоль текущего состояния
//good //- Вращение граней кубика рубика с помощью вводимых команд
//good //- Генерация случайного состояния Кубика Рубика, корректного с точки зрения инварианта состояний
//good //- Нахождения “решения” для текущего состояния в виде последовательности поворотов граней
//good //- Визуализация

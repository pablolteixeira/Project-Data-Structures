#include <iostream>
#include <fstream>
#include <string>
#include "array_list.h"

int xmlValidate(std::string);
int counterComponents(int, int);

int main() {
    std::string dir;

    std::cin >> dir;

    if (xmlValidate(dir)) {
        std::cout << "foi :)" << std::endl;
    } else {
        std::cout << "error" << std::endl;
    }

    counterComponents(30, 40);

    return 0;
}

int xmlValidate(std::string dir) {
    std::fstream myfile;
    myfile.open(dir);

    structures::ArrayList<std::string> stack;

    if (myfile.is_open()) {
        std::string word;
        bool open = true;
        char c;

        while (!myfile.eof()) {
            myfile.get(c);

            if (c == '<') {
                word.clear();
            } else if (c == '>') {
                if (!stack.empty()) {
                    if (stack[stack.size() - 1] == word && open == false) {
                        stack.pop_back();
                        open = true;
                    } else {
                        stack.push_back(word);
                    }
                } else {
                    stack.push_back(word);
                }
            } else {
                if (c == '/') {
                    open = false;
                } else {
                    word += c;
                }
            }
        }

        myfile.close();
        if (myfile.is_open()) {
            std::cout << "Stream could not close!" << std::endl;
        }
    }

    return stack.size() == 0;
}

int readArray(std::string dir) {
    std::fstream myfile;
    myfile.open(dir);

    structures::ArrayList<std::string> stack;

    if (myfile.is_open()) {
        std::string word;
        bool open = true;
        char c;
        int height, width;

        while (!myfile.eof()) {
            myfile.get(c);

            if (c == '<') {
                word.clear();
            } else if (c == '>') {
                if (!stack.empty()) {
                    if (stack[stack.size() - 1] == word && open == false) {
                        stack.pop_back();
                        open = true;
                    } else {
                        stack.push_back(word);
                    }
                } else {
                    stack.push_back(word);
                }
            } else {
                if (c == '/') {
                    open = false;
                } else {
                    word += c;
                }
            }
        }

        myfile.close();
        if (myfile.is_open()) {
            std::cout << "Stream could not close!" << std::endl;
        }
    }
}


int counterComponents(int height, int width) {
    int i = 0, j = 0;



    /*
    int matrix_ref[height][width];

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            matrix_ref[i][j] = 0;
        }
    }
    */
    return 0;
}
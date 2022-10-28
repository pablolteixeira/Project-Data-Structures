#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include "array_stack.h"
#include "array_queue.h"

void xmlValidate(std::string);
void readArray(std::string);
void counterSpaces(std::string, std::string, std::string, std::string);

int main() {
    std::string dir;

    std::cin >> dir;

    xmlValidate(dir);

    return 0;
}

void xmlValidate(std::string dir) {
    std::fstream myfile;
    myfile.open(dir);

    structures::ArrayStack<std::string> stack;
    structures::ArrayQueue<std::string> parameters(10000);

    if (myfile.is_open()) {
        std::string word;
        std::string value;
        bool open = true;

        char c;

        while (!myfile.eof()) {
            myfile.get(c);

            if (c == '<') {
                value = word;
                word.clear();
            } else if (c == '>') {
                if (!stack.empty()) {
                    if (stack.top() == word && open == false) {
                        std::string last = stack.pop();

                        if (last == "height") {
                            parameters.enqueue(value);
                        } else if (last == "width") {
                            parameters.enqueue(value);
                        } else if (last == "name") {
                            parameters.enqueue(value);
                        } else if (last == "data") {
                            parameters.enqueue(value);
                        }
                        open = true;
                    } else {
                        stack.push(word);
                    }
                    word.clear();
                } else {
                    stack.push(word);
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


    if (stack.size() == 0) {
        while (!parameters.empty()) {
            std::string name = parameters.dequeue();
            std::string height = parameters.dequeue(); 
            std::string width = parameters.dequeue();
            std::string data = parameters.dequeue();
            
            counterSpaces(name, height, width, data);
        }
    } else {
        std::cout << "error" << std::endl;
    }
}

void counterSpaces(std::string name, std::string height, std::string width, std::string data) {

    int _height = std::stoi(height);
    int _width = std::stoi(width);

    int spaces = 0;

    char** matrix_new = new char*[_height];

    for (int i = 0; i < _height; i++) {
        matrix_new[i] = new char[_width];
    }

    char** matrix_aux = new char*[_height];

    for (int i = 0; i < _height; i++) {
        matrix_aux[i] = new char[_width];
    }

    structures::ArrayQueue<int> heapOnesHeight(1000000);
    structures::ArrayQueue<int> heapOnesWidth(1000000);

    int j = 0;
    for (int i = 0; i < data.length(); i++) {
        if ((data[i] == '0') || (data[i] == '1')) {
            matrix_new[j/_width][j%_width] = data[i];
            matrix_aux[j/_width][j%_width] = '0';        
            j++;
        }
    }
    
    for (int i = 0; i < _height; i++) {
        for (int j = 0; j < _width; j++) {
            if ((matrix_new[i][j] == '1') && (matrix_aux[i][j] == '0')) {
                heapOnesHeight.enqueue(i);
                heapOnesWidth.enqueue(j);
                matrix_aux[i][j] = '1';
            }


            while (!heapOnesHeight.empty()) {
                int h = heapOnesHeight.dequeue();
                int w = heapOnesWidth.dequeue();

                if (h + 1 < _height) {
                    if ((matrix_new[h+1][w] == '1') && (matrix_aux[h+1][w] == '0')) {
                        heapOnesHeight.enqueue(h+1);
                        heapOnesWidth.enqueue(w);
                        matrix_aux[h+1][w] = '1';
                    }
                }
                if (h - 1  > -1) {
                    if ((matrix_new[h-1][w] == '1') && (matrix_aux[h-1][w] == '0')) {
                        heapOnesHeight.enqueue(h-1);
                        heapOnesWidth.enqueue(w);
                        matrix_aux[h-1][w] = '1';
                    }
                }
                if (w + 1 < _width) {
                    if ((matrix_new[h][w+1] == '1') && (matrix_aux[h][w+1] == '0')) {
                        heapOnesHeight.enqueue(h);
                        heapOnesWidth.enqueue(w+1);
                        matrix_aux[h][w+1] = '1';
                    }
                }
                if (w - 1  > -1) {
                    if ((matrix_new[h][w-1] == '1') && (matrix_aux[h][w-1] == '0')) {
                        heapOnesHeight.enqueue(h);
                        heapOnesWidth.enqueue(w-1);
                        matrix_aux[h][w-1] = '1';
                    }
                }

                if (heapOnesHeight.empty()) {
                    spaces++;
                }
            }
        }
    }

    std::cout << name << " " << spaces << std::endl;
}

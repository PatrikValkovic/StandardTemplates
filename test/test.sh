#!/bin/sh

g++ main.cpp -o main.exe -g -Wall -pedantic -std=c++11
chmod +x main.exe
valgrind --leak-check=full -q ./main.exe

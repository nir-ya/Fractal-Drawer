//
// Created by nir_ya on 9/6/19.
//

#include <iostream>
#include <cmath>
#include "Fractal.h"



//-------------------------------------- class Carpet --------------------------------------------//


/**
 * a single parameter Constructor
 * @param height: the height (dimension) of the desired fractal
 */
Carpet::Carpet(int height) : Fractal(height, static_cast<int>(pow(s_basicSideSize, height))) {}


/**
 * builds the ASCII Art picture of the fractal in the given 2D char array.
 *
 * @param pic: 2D char array - the picture of the fractal
 * @param currHeight: the height of the recursion
 * @param currSize: current side size
 * @param row: the current row in the 2D array
 * @param col: the current column in the 2D array
 */
void Carpet::_buildPicture(char **&pic, int currHeight, int currSize, int row, int col) const
{
    if (currHeight == 0)
    {
        pic[row][col] = '#';
        return;
    }
    int newSize = currSize / s_basicSideSize;

    for (int i = 0; i < s_basicSideSize; ++i)
    {
        for (int j = 0; j < s_basicSideSize; ++j)
        {
            if (i != 1 || j != 1)
            {
                _buildPicture(pic, currHeight - 1, newSize,
                              row + i * newSize, col + j * newSize);
            }
        }
    }
}


//--------------------------------------- class Sieve --------------------------------------------//


/**
 * a single parameter Constructor
 * @param height: the height (dimension) of the desired fractal
 */
Sieve::Sieve(int height) : Fractal(height, static_cast<int>(pow(s_basicSideSize, height))) {}


/**
 * builds the ASCII Art picture of the fractal in the given 2D char array.
 *
 * @param pic: 2D char array - the picture of the fractal
 * @param currHeight: the height of the recursion
 * @param currSize: current side size
 * @param row: the current row in the 2D array
 * @param col: the current column in the 2D array
 */
void Sieve::_buildPicture(char **&pic, int currHeight, int currSize, int row, int col) const
{
    if (currHeight == 0)
    {
        pic[row][col] = '#';
        return;
    }
    int newSize = currSize / s_basicSideSize;
    
    _buildPicture(pic, currHeight - 1, newSize, row, col);
    _buildPicture(pic, currHeight - 1, newSize, row + newSize, col);
    _buildPicture(pic, currHeight - 1, newSize, row, col + newSize);
}


//---------------------------------------- class Dust --------------------------------------------//


/**
 * a single parameter Constructor
 * @param height: the height (dimension) of the desired fractal
 */
Dust::Dust(int height) : Fractal(height, static_cast<int>(pow(s_basicSideSize, height))) {}


/**
 * builds the ASCII Art picture of the fractal in the given 2D char array.
 *
 * @param pic: 2D char array - the picture of the fractal
 * @param currHeight: the height of the recursion
 * @param currSize: current side size
 * @param row: the current row in the 2D array
 * @param col: the current column in the 2D array
 */
void Dust::_buildPicture(char **&pic, int currHeight, int currSize, int row, int col) const
{
    if (currHeight == 0)
    {
        pic[row][col] = '#';
        return;
    }
    int newSize = currSize / s_basicSideSize;
    
    _buildPicture(pic, currHeight - 1, newSize, row, col);
    _buildPicture(pic, currHeight - 1, newSize, row + 2 * newSize, col);
    _buildPicture(pic, currHeight - 1, newSize, row, col + 2 * newSize);
    _buildPicture(pic, currHeight - 1, newSize, row + 2 * newSize, col + 2 * newSize);
}


//---------------------------------------- class Fractal -----------------------------------------//


/**
 * a two parameter protected Constructor, for the use of sub-classes (Fractal class is abstract).
 * @param height: the height (dimension) of the desired fractal
 * @param sideSize: specifies the side size of the printed ASCII Art fractal picture
 */
Fractal::Fractal(int height, int sideSize) : _height(height), _sideSize(sideSize)
{
    if (height < s_minFractalHeight || height > s_maxFractalHeight)
    {
        std::cerr << "Invalid height of fractal" << std::endl;
    }
}


/**
 * allocates memory for a 2D char array representing the ASCII Art picture of the fractal
 *
 * @return a pointer to the allocated array
 */
char **Fractal::_allocatePicture() const
{
    char** newPic = new (std::nothrow) char*[_sideSize];
    if (newPic == nullptr)
    {
        std::cerr << "Memory allocation failed" << std::endl;
        exit(EXIT_FAILURE);
    }
    
    for (int i = 0; i < _sideSize; ++i)
    {
        newPic[i] = new (std::nothrow) char[_sideSize];
    
        if (newPic[i] == nullptr)
        {
            std::cerr << "Memory allocation failed" << std::endl;
            exit(EXIT_FAILURE);
        }
    }
    for (int i = 0; i < _sideSize; ++i)
    {
        for (int j = 0; j < _sideSize; ++j)
        {
            newPic[i][j] = ' ';
        }
    }
    
    return newPic;
}


/**
 * prints the 2D char array representing the picture of the fractal to stdout
 *
 * @param picture: the 2D char array representing the picture of the fractal
 */
void Fractal::_printPicture(char **&picture) const
{
    for (int i = 0; i < _sideSize; ++i)
    {
        for (int j = 0; j < _sideSize; ++j)
        {
            std::cout << picture[i][j];
        }
        std::cout << std::endl;
    }
}


/**
 * draws the fractal in ASCII art format
 */
void Fractal::draw() const
{
    char** picture = _allocatePicture();
    
    _buildPicture(picture, _height, _sideSize, 0, 0);
    
    _printPicture(picture);
    
    for (int i = 0; i < _sideSize; ++i)
    {
        delete [] picture[i];
    }
    delete [] picture;
}
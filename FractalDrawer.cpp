#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "Fractal.h"


// constants
static const char CSV_SEPARATOR = ',';
static const int CSV_LINE_LEN = 3;


/**
 * A function for creating instances of Fractal sub-classes.
 *
 * @param type: an int specifying the desired type of Fractal (the desired sub-class instance)
 * @param height: the height (dimension) of the desired fractal
 * @return returns a pointer to an instance of the specified derived class of Fractal
 */
Fractal* createFractal(const int& type, const int& height)
{
    if (height < Fractal::s_minFractalHeight || height > Fractal::s_maxFractalHeight)
    {
        std::cerr << "Invalid input" << std::endl;
        return nullptr;
    }
    
    Fractal* newFractal = nullptr;
    
    switch (type)
    {
        case 1:
            newFractal = new (std::nothrow) Carpet(height);
            break;
        
        case 2:
            newFractal = new (std::nothrow) Sieve(height);
            break;
        
        case 3:
            newFractal = new (std::nothrow) Dust(height);
            break;
        
        default:
            std::cerr << "Invalid input" << std::endl;
            return newFractal;
    }
    if (newFractal == nullptr)
    {
        std::cerr << "Memory allocation failed" << std::endl;
        exit(EXIT_FAILURE);
    }
    return newFractal;
}


/**
 * prints the fractals in the given vector to stdout
 *
 * @param fractals: a vector of pointers to Fractals
 */
void printFractals(std::vector<Fractal *> &fractals)
{
    for (long i = fractals.size() - 1; i >= 0; --i)
    {
        fractals[i]->draw();
        std::cout << std::endl;
    }
}


/**
 * deletes the content of the given vector (and frees the allocated memory)
 *
 * @param fractals: a vector of pointers to Fractals
 */
void deleteFractals(std::vector<Fractal *> &fractals)
{
    for (Fractal* p : fractals)
    {
        delete p;
    }
    fractals.clear();
}


/**
 * parses the given CSV file, and fills the given vector with (pointers to) Fractal
 * objects corresponding to the specified input
 *
 * @param inFile: a CSV file, in which every line should have the format <type>,<height>
 *                 where <type> is an int between 1 and 3 (type of the desired Fractal),
 *                 and <height> is an int between 1 and 6 (height/dimension of the desired Fractal)
 * @param fractals a vector of pointers to Fractals
 * @return
 */
bool createFractals(std::ifstream &inFile, std::vector<Fractal *> &fractals)
{
    std::string currLine;
    
    while (!inFile.eof())
    {
        std::getline(inFile, currLine);
        
        if (currLine.length() == 0 && inFile.eof())
        {
            break;
        }
        
        if (inFile.fail() || currLine.length() != CSV_LINE_LEN || currLine[1] != CSV_SEPARATOR)
        {
            std::cerr << "Invalid input" << std::endl;
            return false;
        }
        
        int type = currLine[0] - '0', height = currLine[2] - '0'; // convert char digit to int
        
        Fractal* newFractal = createFractal(type, height);
        
        if (newFractal == nullptr) // in case of a problem creating a new Fractal instance
        {
            return false;
        }
        fractals.push_back(newFractal);
    }
    return true;
}


/**
 * The program expects a single argument from the command line, that is a path to a CSV file
 * in which every line specifies parameters for creating and drawing a single ASCII art Fractal.
 * after processing the given file, the fractals will be printed to stdout,
 * in reverse order (from the order of specification in the file).
 *
 * @param argc number of given cli arguments
 * @param argv command line arguments
 * @return
 */
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: FractalDrawer <file path>" << std::endl;
        return EXIT_FAILURE;
    }

    std::string pathname(argv[1]);
    std::ifstream inFile;
    inFile.open(pathname);
    
    if (!inFile.is_open()) // make sure the file was opened properly
    {
        std::cerr << "Invalid input" << std::endl;
        return EXIT_FAILURE;
    }
    
    std::vector<Fractal *> fractals;
    
    if (!createFractals(inFile, fractals))
    {
        deleteFractals(fractals);
        inFile.close();
        return EXIT_FAILURE;
    }
    
    inFile.close();

    printFractals(fractals);
    
    deleteFractals(fractals);
    
    return 0;
}
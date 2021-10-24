//
// Created by nir_ya on 9/6/19.
//

#include <iostream>

#ifndef EX2_FRACTAL_H
#define EX2_FRACTAL_H


/**
 * Represents an abstract Fractal
 */
class Fractal
{
public:
    
    /**
     * draws the fractal in ASCII art format
     */
    virtual void draw() const;
    
    /**
     * default destructor
     */
    virtual ~Fractal() = default;
    
    /**
     * default copy constructor
     * @param toCopy
     */
    Fractal(const Fractal &toCopy) = default;
    
    /**
     * default move constructor
     * @param other
     */
    Fractal(Fractal && other) = default;
    
    /**
     * default copy assignment operator
     * @return a reference to this instance
     */
    Fractal& operator=(const Fractal&) = default;
    
    /**
     * default move assignment operator
     * @param other the Fractal to assign from
     * @return a reference to this instance
     */
    Fractal& operator=(Fractal && other) = default;
    
    
    // class constants
    static const int s_minFractalHeight = 1;
    static const int s_maxFractalHeight = 6;
    
protected:
    
    /**
    * a two parameter protected Constructor, for the use of sub-classes (Fractal class is abstract).
    * @param height: the height (dimension) of the desired fractal
    * @param sideSize: specifies the side size of the printed ASCII Art fractal picture
    */
    Fractal(int height, int sideSize);
    
    /**
     * builds the ASCII Art picture of the fractal in the given 2D char array.
     *
     * @param pic: 2D char array - the picture of the fractal
     * @param currHeight: the height of the recursion
     * @param currSize: current side size
     * @param row: the current row in the 2D array
     * @param col: the current column in the 2D array
     */
    virtual void _buildPicture(char **&pic, int currHeight,
                               int currSize, int row, int col) const = 0;
    
    int _height;
    int _sideSize;
    
private:
    
    /**
     * allocates memory for a 2D char array representing the ASCII Art picture of the fractal
     *
     * @return a pointer to the allocated array
     */
    char** _allocatePicture() const;
    
    /**
     * prints the 2D char array representing the picture of the fractal to stdout
     *
     * @param picture: the 2D char array representing the picture of the fractal
     */
    void _printPicture(char **&picture) const;
};



/**
 * Represents a Sierpinski Carpet Fractal
 */
class Carpet : public Fractal
{
public:
    
    /**
     * a single parameter Constructor
     * @param height: the height (dimension) of the desired fractal
     */
    explicit Carpet(int height);
    
    /**
     * default destructor
     */
    ~Carpet() override = default;
    
    /**
     * default copy constructor
     * @param toCopy
     */
    Carpet(const Carpet &toCopy) = default;
    
    /**
     * default move constructor
     * @param other
     */
    Carpet(Carpet && other) = default;
    
    /**
     * default copy assignment operator
     * @return a reference to this instance
     */
    Carpet& operator=(const Carpet&) = default;
    
    /**
     * default move assignment operator
     * @param other the Fractal to assign from
     * @return a reference to this instance
     */
    Carpet& operator=(Carpet && other) = default;

private:
    
    static const int s_basicSideSize = 3;
    
    /**
     * builds the ASCII Art picture of the fractal in the given 2D char array.
     *
     * @param pic: 2D char array - the picture of the fractal
     * @param currHeight: the height of the recursion
     * @param currSize: current side size
     * @param row: the current row in the 2D array
     * @param col: the current column in the 2D array
     */
    void _buildPicture(char **&pic, int currHeight, int currSize,
                       int row, int col) const override;
};



/**
 * Represents a Sierpinski Sieve Fractal
 */
class Sieve : public Fractal
{
public:
    
    /**
     * a single parameter Constructor
     * @param height: the height (dimension) of the desired fractal
     */
    explicit Sieve(int height);
    
    /**
     * default destructor
     */
    ~Sieve() override = default;
    
    /**
     * default copy constructor
     * @param toCopy
     */
    Sieve(const Sieve &toCopy) = default;
    
    /**
     * default move constructor
     * @param other
     */
    Sieve(Sieve && other) = default;
    
    /**
     * default copy assignment operator
     * @return a reference to this instance
     */
    Sieve& operator=(const Sieve&) = default;
    
    /**
     * default move assignment operator
     * @param other the Fractal to assign from
     * @return a reference to this instance
     */
    Sieve& operator=(Sieve && other) = default;

private:
    
    static const int s_basicSideSize = 2;
    
    /**
     * builds the ASCII Art picture of the fractal in the given 2D char array.
     *
     * @param pic: 2D char array - the picture of the fractal
     * @param currHeight: the height of the recursion
     * @param currSize: current side size
     * @param row: the current row in the 2D array
     * @param col: the current column in the 2D array
     */
    void _buildPicture(char **&pic, int currHeight, int currSize,
                       int row, int col) const override;
};



/**
 * Represents a Cantor Dust Fractal
 */
class Dust : public Fractal
{
public:
    
    /**
     * a single parameter Constructor
     * @param height: the height (dimension) of the desired fractal
     */
    explicit Dust(int height);
    
    /**
     * default destructor
     */
    ~Dust() override = default;
    
    /**
     * default copy constructor
     * @param toCopy
     */
    Dust(const Dust &toCopy) = default;
    
    /**
     * default move constructor
     * @param other
     */
    Dust(Dust && other) = default;
    
    /**
     * default copy assignment operator
     * @return a reference to this instance
     */
    Dust& operator=(const Dust&) = default;
    
    /**
     * default move assignment operator
     * @param other the Fractal to assign from
     * @return a reference to this instance
     */
    Dust& operator=(Dust && other) = default;
    
private:
    
    static const int s_basicSideSize = 3;
    
    /**
     * builds the ASCII Art picture of the fractal in the given 2D char array.
     *
     * @param pic: 2D char array - the picture of the fractal
     * @param currHeight: the height of the recursion
     * @param currSize: current side size
     * @param row: the current row in the 2D array
     * @param col: the current column in the 2D array
     */
    void _buildPicture(char **&pic, int currHeight, int currSize,
                       int row, int col) const override;
};


#endif //EX2_FRACTAL_H

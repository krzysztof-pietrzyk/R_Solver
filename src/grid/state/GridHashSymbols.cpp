// implemented header
#include "GridHash.hpp"

// project includes

// std includes


const std::map<char, char> GridHash::symbols_to_patterns = 
{
    {'0', char(0)},  {'-', char(1)},  {'2', char(2)},  {'3', char(3)},
    {'4', char(4)},  {'5', char(5)},  {'6', char(6)},  {'7', char(7)},
    {'8', char(8)},  {'9', char(9)},  {'a', char(10)}, {'b', char(11)},
    {'c', char(12)}, {'d', char(13)}, {'e', char(14)}, {'f', char(15)},
    {'g', char(16)}, {'h', char(17)}, {'i', char(18)}, {'j', char(19)},
    {'k', char(20)}, {'l', char(21)}, {'m', char(22)}, {'n', char(23)},
    {'o', char(24)}, {'p', char(25)}, {'q', char(26)}, {'r', char(27)},
    {'s', char(28)}, {'t', char(29)}, {'u', char(30)}, {'v', char(31)},
    {'w', char(32)}, {'x', char(33)}, {'y', char(34)}, {'z', char(35)},
    {'A', char(36)}, {'B', char(37)}, {'C', char(38)}, {'D', char(39)},
    {'E', char(40)}, {'F', char(41)}, {'G', char(42)}, {'H', char(43)},
    {'I', char(44)}, {'J', char(45)}, {'K', char(46)}, {'L', char(47)},
    {'M', char(48)}, {'N', char(49)}, {'O', char(50)}, {'P', char(51)},
    {'Q', char(52)}, {'R', char(53)}, {'S', char(54)}, {'T', char(55)},
    {'U', char(56)}, {'V', char(57)}, {'W', char(58)}, {'X', char(59)},
    {'Y', char(60)}, {'Z', char(61)}, {'=', char(62)}, {'1', char(63)}
};

const std::map<char, char> GridHash::patterns_to_symbols = 
{
    {char(0), '0'},  {char(1), '-'},  {char(2), '2'},  {char(3), '3'},
    {char(4), '4'},  {char(5), '5'},  {char(6), '6'},  {char(7), '7'},
    {char(8), '8'},  {char(9), '9'},  {char(10), 'a'}, {char(11), 'b'},
    {char(12), 'c'}, {char(13), 'd'}, {char(14), 'e'}, {char(15), 'f'},
    {char(16), 'g'}, {char(17), 'h'}, {char(18), 'i'}, {char(19), 'j'},
    {char(20), 'k'}, {char(21), 'l'}, {char(22), 'm'}, {char(23), 'n'},
    {char(24), 'o'}, {char(25), 'p'}, {char(26), 'q'}, {char(27), 'r'},
    {char(28), 's'}, {char(29), 't'}, {char(30), 'u'}, {char(31), 'v'},
    {char(32), 'w'}, {char(33), 'x'}, {char(34), 'y'}, {char(35), 'z'},
    {char(36), 'A'}, {char(37), 'B'}, {char(38), 'C'}, {char(39), 'D'},
    {char(40), 'E'}, {char(41), 'F'}, {char(42), 'G'}, {char(43), 'H'},
    {char(44), 'I'}, {char(45), 'J'}, {char(46), 'K'}, {char(47), 'L'},
    {char(48), 'M'}, {char(49), 'N'}, {char(50), 'O'}, {char(51), 'P'},
    {char(52), 'Q'}, {char(53), 'R'}, {char(54), 'S'}, {char(55), 'T'},
    {char(56), 'U'}, {char(57), 'V'}, {char(58), 'W'}, {char(59), 'X'},
    {char(60), 'Y'}, {char(61), 'Z'}, {char(62), '='}, {char(63), '1'}  
};

const std::map<char, char> GridHash::consecutive_zeros_to_symbols = 
{
    {1, '0'}, {2, '@'}, {3, '#'}, {4, '$'}, {5, '%'}, {6, '^'}, {7, '&'}, {8, '*'},
    {9, '('}, {10, ')'}, {11, '_'}, {12, '+'}, {13, '`'}, {14, '~'}, {15, '!'}
};

const std::map<char, char> GridHash::symbols_to_consecutive_zeros = 
{
    {'0', 1}, {'@', 2}, {'#', 3}, {'$', 4}, {'%', 5}, {'^', 6}, {'&', 7}, {'*', 8},
    {'(', 9}, {')', 10}, {'_', 11}, {'+', 12}, {'`', 13}, {'~', 14}, {'!', 15}
};

const std::map<char, char> GridHash::consecutive_ones_to_symbols = 
{
    {1, '1'}, {2, '['}, {3, ']'}, {4, ';'}, {5, '\''}, {6, ','}, {7, '.'}, {8, '/'},
    {9, '{'}, {10, '}'}, {11, ':'}, {12, '"'}, {13, '<'}, {14, '>'}, {15, '?'}
};

const std::map<char, char> GridHash::symbols_to_consecutive_ones = 
{
    {'1', 1}, {'[', 2}, {']', 3}, {';', 4}, {'\'', 5}, {',', 6}, {'.', 7}, {'/', 8},
    {'{', 9}, {'}', 10}, {':', 11}, {'"', 12}, {'<', 13}, {'>', 14}, {'?', 15}
};

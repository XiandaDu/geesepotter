#include <iostream>
#include "geesespotter.h"
#include "geesespotter_lib.h"

char *createBoard(std::size_t xdim, std::size_t ydim)
{
    char *array{new char[xdim * ydim]};
    for (int i{}; i < xdim * ydim; ++i)
    {
        array[i] = 0;
    }
    return array;
}

void computeNeighbors(char *board, std::size_t xdim, std::size_t ydim)
{
    for (int i{}; i < ydim; ++i)
    {
        for (int k{}; k < xdim; ++k)
        {
            if (board[i * xdim + k] == 9)
            {
                if (k == 0 && i == 0)
                {
                    if (board[1] != 9)
                    {
                        ++board[1];
                    }
                    if (board[xdim] != 9)
                    {
                        ++board[xdim];
                    }
                    if (board[xdim + 1] != 9)
                    {
                        ++board[xdim + 1];
                    }
                }
                else if (k == 0 && i == ydim - 1)
                {
                    if (board[i * xdim + 1] != 9)
                    {
                        ++board[i * xdim + 1];
                    }
                    if (board[(i - 1) * xdim] != 9)
                    {
                        ++board[(i - 1) * xdim];
                    }
                    if (board[(i - 1) * xdim + 1] != 9)
                    {
                        ++board[(i - 1) * xdim + 1];
                    }
                }
                else if (k == xdim - 1 && i == 0)
                {
                    if (board[k - 1] != 9)
                    {
                        ++board[k - 1];
                    }
                    if (board[xdim + k - 1] != 9)
                    {
                        ++board[xdim + k - 1];
                    }
                    if (board[xdim + k] != 9)
                    {
                        ++board[xdim + k];
                    }
                }
                else if (k == xdim - 1 && i == ydim - 1)
                {
                    if (board[i * xdim + k - 1] != 9)
                    {
                        ++board[i * xdim + k - 1];
                    }
                    if (board[(i - 1) * xdim + k - 1] != 9)
                    {
                        ++board[(i - 1) * xdim + k - 1];
                    }
                    if (board[(i - 1) * xdim + k] != 9)
                    {
                        ++board[(i - 1) * xdim + k];
                    }
                }
                // four concers↑
                else if (k == 0)
                {
                    for (int x{i - 1}; x < i + 2; ++x)
                    {
                        for (int y{k}; y < k + 2; ++y)
                        {
                            if (board[x * xdim + y] != 9)
                            {
                                ++board[x * xdim + y];
                            }
                        }
                    }
                }
                else if (k == xdim - 1)
                {
                    for (int x{i - 1}; x < i + 2; ++x)
                    {
                        for (int y{k - 1}; y < k + 1; ++y)
                        {
                            if (board[x * xdim + y] != 9)
                            {
                                ++board[x * xdim + y];
                            }
                        }
                    }
                }
                else if (i == 0)
                {
                    for (int x{i}; x < i + 2; ++x)
                    {
                        for (int y{k - 1}; y < k + 2; ++y)
                        {
                            if (board[x * xdim + y] != 9)
                            {
                                ++board[x * xdim + y];
                            }
                        }
                    }
                }
                else if (i == ydim - 1)
                {
                    for (int x{i - 1}; x < i + 1; ++x)
                    {
                        for (int y{k - 1}; y < k + 2; ++y)
                        {
                            if (board[x * xdim + y] != 9)
                            {
                                ++board[x * xdim + y];
                            }
                        }
                    }
                }
                else
                {
                    for (int x{i - 1}; x < i + 2; ++x)
                    {
                        for (int y{k - 1}; y < k + 2; ++y)
                        {
                            if (board[x * xdim + y] != 9)
                            {
                                ++board[x * xdim + y];
                            }
                        }
                    }
                }
            }
        }
    }
    return;
}

void hideBoard(char *board, std::size_t xdim, std::size_t ydim)
{
    for (int i{}; i < ydim; ++i) // hide is 20-30
    {
        for (int k{}; k < xdim; ++k)
        {
            board[i * xdim + k] |= 0b00100000;
        }
    }
    return;
}

void cleanBoard(char *board)
{
    delete[] board;
    board = nullptr;
    return;
}

void printBoard(char *board, std::size_t xdim, std::size_t ydim)
{
    for (int i{}; i < ydim; ++i)
    {
        for (int k{}; k < xdim; ++k)
        {
            if (board[i * xdim + k] >= 0x20 && board[i * xdim + k] < 0x30)
            {
                std::cout << "*";
            }
            else if (board[i * xdim + k] >= 0x30 && board[i * xdim + k] < 0x40)
            {
                std::cout << "M";
            }
            else
            {
                char a{board[i * xdim + k]};
                a += 48;
                std::cout << a;
            }
        }
        std::cout << std::endl;
    }
    return;
}

void show(char *board, std::size_t xdim, std::size_t ydim, std::size_t k, std::size_t i)
{
    unsigned long long x{};
    unsigned long long y{};
    if (k == 0 && i == 0)
    {
        board[1] &= 0x0F;
        board[xdim] &= 0x0F;
        board[xdim + 1] &= 0x0F;
    }
    else if (k == 0 && i == ydim - 1)
    {
        board[i * xdim + 1] &= 0x0F;
        board[(i - 1) * xdim] &= 0x0F;
        board[(i - 1) * xdim + 1] &= 0x0F;
    }
    else if (k == xdim - 1 && i == 0)
    {
        board[k - 1] &= 0x0F;
        board[xdim + k - 1] &= 0x0F;
        board[xdim + k] &= 0x0F;
    }
    else if (k == xdim - 1 && i == ydim - 1)
    {
        board[i * xdim + k - 1] &= 0x0F;
        board[(i - 1) * xdim + k - 1] &= 0x0F;
        board[(i - 1) * xdim + k] &= 0x0F;
    }
    // four concers↑
    else if (k == 0)
    {
        for (x = i - 1; x < i + 2; ++x)
        {
            for (y = k; y < k + 2; ++y)
            {
                board[x * xdim + y] &= 0x0F;
            }
        }
    }
    else if (k == xdim - 1)
    {
        for (x = i - 1; x < i + 2; ++x)
        {
            for (y = k - 1; y < k + 1; ++y)
            {
                board[x * xdim + y] &= 0x0F;
            }
        }
    }
    else if (i == 0)
    {
        for (x = i; x < i + 2; ++x)
        {
            for (y = k - 1; y < k + 2; ++y)
            {
                board[x * xdim + y] &= 0x0F;
            }
        }
    }
    else if (i == ydim - 1)
    {
        for (x = i - 1; x < i + 1; ++x)
        {
            for (y = k - 1; y < k + 2; ++y)
            {
                board[x * xdim + y] &= 0x0F;
            }
        }
    }
    else
    {
        for (x = i - 1; x < i + 2; ++x)
        {
            for (y = k - 1; y < k + 2; ++y)
            {
                board[x * xdim + y] &= 0x0F;
            }
        }
    }
}

int reveal(char *board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc)
{
    if (board[yloc * xdim + xloc] < 0x40 && board[yloc * xdim + xloc] > 0x30)
    {
        return 1;
    }
    if (board[yloc * xdim + xloc] < 0x10)
    {
        return 2;
    }
    else
    {
        if (board[yloc * xdim + xloc] == 0x29)
        {
            board[yloc * xdim + xloc] &= 0x0F;
            return 9;
        }
        else if (board[yloc * xdim + xloc] == 0x20)
        {
            show(board, xdim, ydim, xloc, yloc);
            board[yloc * xdim + xloc] &= 0x0F;
        }
        else
        {
            board[yloc * xdim + xloc] &= 0x0F;
        }
        return 0;
    }
}

int mark(char *board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc)
{
    if (board[yloc * xdim + xloc] < 0x10)
    {
        return 2;
    }
    else
    {
        if (board[yloc * xdim + xloc] < 0x40 && board[yloc * xdim + xloc] > 0x30)
        {
            board[yloc * xdim + xloc] &= 0b11101111;
        }
        else
        {
            board[yloc * xdim + xloc] |= 0b00010000;
        }
        return 0;
    }
}

bool isGameWon(char *board, std::size_t xdim, std::size_t ydim)
{
    int countnotgee{};
    int countrevel{};
    for (int i{}; i < xdim * ydim; ++i)
    {
        if ((board[i] & 0b00001111) != 9)
        {
            ++countnotgee;
        }
        if (board[i] < 0x09)
        {
            ++countrevel;
        }
        if (board[i] == 0x09)
        {
            return false;
        }
    }
    if (countnotgee == countrevel)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_mate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmbotho <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/01 18:11:49 by nmbotho           #+#    #+#             */
/*   Updated: 2017/08/01 18:11:54 by nmbotho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int x_length(char *s)
{
    int i;

    i = 0;
    while(s[i])
        i++;
    return (i);
}

int y_length(char **s)
{
    int i;

    i = 0;
    while(s[i])
        i++;
    return (i);
}

int vertical_line(int x, int y, char **av)
{
    int cy = y;

    while(cy >= 0)
    {
        if(av[cy][x] == 'Q' || av[cy][x] == 'R')
            return (1);
        if(av[cy][x] == 'P' || av[cy][x] == 'B')
            return (0);
        cy--;
    }
    cy = y;
    while(av[cy])
    {
        if(av[cy][x] == 'Q' || av[cy][x] == 'R')
            return (1);
        if(av[cy][x] == 'P' || av[cy][x] == 'B')
            return (0);
        cy++;
    }
    return (0);
}

int horizontal_line(int x, int y, char **av)
{
    int cx = x;

    while(cx >= 0)
    {
        if(av[y][cx] == 'Q' || av[y][cx] == 'R')
            return (1);
        if(av[y][cx] == 'P' || av[y][cx] == 'B')
            return (0);
        cx--;
    }
    cx = x;
    while(av[y][cx])
    {
        if(av[y][cx] == 'Q' || av[y][cx] == 'R')
            return (1);
        if(av[y][cx] == 'P' || av[y][cx] == 'B')
            return (0);
        cx++;
    }
    return (0);
}

int pawn_check(int x, int y, char **av)
{
    if(av[y + 1][x + 1] == 'P' || av[y + 1][x - 1] == 'P')
        return (1);
    return (0);
}

int a_diagonal_line(int x, int y, char **av)
{
    int cx = x;
    int cy = y;
    int x_len = x_length(av[0]) - 1;

    while(cy >= 0 && cx <= x_len)
    {
        if(av[cy][cx] == 'B' || av[cy][cx] == 'Q')
            return (1);
        if(av[cy][cx] == 'R' || av[cy][cx] == 'P')
            break;
        cy--;
        cx++;
    }
    cx = x;
    cy = y;
    while(av[cy] && cx >= 0)
    {
        if(av[cy][cx] == 'B' || av[cy][cx] == 'Q')
            return (1);
        if(av[cy][cx] == 'R' || av[cy][cx] == 'P')
            break;
        cy++;
        cx--;
    }
    return (0);
}

int b_diagonal_line(int x, int y, char **av)
{
    int cx = x;
    int cy = y;

    while(cy >= 0 && cx >= 0)
    {
        if(av[cy][cx] == 'B' || av[cy][cx] == 'Q')
            return (1);
        if(av[cy][cx] == 'R' || av[cy][cx] == 'P')
            break;
        cy--;
        cx--;
    }
    cx = x;
    cy = y;
    while(av[cy] && av[cy][cx])
    {
        if(av[cy][cx] == 'B' || av[cy][cx] == 'Q')
            return (1);
        if(av[cy][cx] == 'R' || av[cy][cx] == 'P')
            break;
        cy++;
        cx++;
    }
    return (0);
}

int chack_mate(char **av)
{
    int y = 0;
    int x = 0;
    while(av[y])
    {
        while(av[y][x])
        {
            if(av[y][x] == 'K')
            {
                if(a_diagonal_line(x, y, av) || b_diagonal_line(x, y, av))
                    return (1);
                if(horizontal_line(x, y, av) || vertical_line(x, y, av))
                    return (1);
                if(pawn_check(x, y, av))
                    return (1);
            }
            x++;
        }
        x = 0;
        y++;
    }
    return (0);
}

int main(int ac, char **av)
{
    if(ac > 1)
    {
        av++;
        if(chack_mate(av))
            write(1, "Success", 7);
        else
            write(1, "Fail", 4);
    }
    write(1, "\n", 1);
    return (0);
}

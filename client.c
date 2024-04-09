/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchareto <tchareto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:59:17 by tchareto          #+#    #+#             */
/*   Updated: 2024/04/05 20:12:41 by tchareto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal.h"
#include <stdio.h>
#include "unistd.h"
#include "stdlib.h"


int ft_atoi(const char *str)
{
    int i;
    int fact;
    int res;

    i = 0;
    fact = 1;
    res = 0;

    while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t'|| 
             str[i] == '\v' ||  str[i] == '\f' || str[i] == '\r')
        i++;
    if (str[i] == '-' || str[i] == '+')
    {
        if (str[i] == '-')
            fact = -1;
        i++;
    }
    while (str[i] >= '0' && str[i] <= '9')
    {
        res = (res * 10) + (str[i]- '0');
        i++;
    }
    return (res * fact);
}

void char_to_binary(char s, int pid)
{
    int i;
    int bit;
    i = 7;

    
    while(i >= 0)
    {   
    bit = (s >> i) & 1;
    if(bit == 1)
    {
        kill(pid, SIGUSR2);
    }
    else
    {
        kill(pid, SIGUSR1);
    }
    usleep(100);
    i--;
    }
}


int main(int argc, char **argv)
{
    size_t i;
    i = 0;
    int pid;

    if(argc != 3)
        return(0);
    pid = ft_atoi(argv[1]);
    
    while(argv[2][i])
    {
        char_to_binary(argv[2][i], pid);
        i++;
    }
    return (0);
}
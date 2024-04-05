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
    i = 7;

    while(i >= 0)
    {
    if((s >> i) & 1)
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

void handler(int reader, siginfo_t *signal, void *useless)
{

  (void)signal;
  (void)useless;
  if (reader == SIGINT)
    exit(1);
  if(reader == SIGUSR1)
  {
    return ;
  }
  if (reader == SIGUSR2)
  {
    exit(1);
  }
  return;  
}

int main(int argc, char **argv)
{
    int i;
    i = 0;
    struct sigaction act;
    int pid;

    if(argc != 3)
        return(0);
    pid = ft_atoi(argv[1]);
    printf("pid :  %d\n", pid);
    sigemptyset(&act.sa_mask);
    act.sa_flags = SA_SIGINFO;
    act.sa_sigaction = handler;
   if ((sigaction(SIGUSR1, &act, 0)) == -1)
        write(1, "Error\n", 6);
    if ((sigaction(SIGUSR2, &act, 0)) == -1)
        write(1, "Error\n", 6);
    if ((sigaction(SIGINT, &act, 0)) == -1)
        write(1, "Error\n", 6);
    while(argv[2][i])
    {
        char_to_binary(argv[2][i], pid);
        i++;
    }
    return (0);
}
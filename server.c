/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchareto <tchareto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 18:20:58 by tchareto          #+#    #+#             */
/*   Updated: 2024/04/05 20:17:22 by tchareto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include "stdlib.h"
char *global = NULL;

int ft_strlen(char *s)
{
  int i;
  i =0;
  while(s[i])
    i++;
  return(i);
}

char *ft_strjoin(char const *s1, char s2) 
{
    size_t i;
    char *s3;

    i = 0;
    while (s1 && s1[i] != '\0')
      i++;
    s3 = malloc(sizeof(char) * (i + 2));
    if (!s3)
     return (NULL);
    i = 0;
    while (s1 && s1[i] != '\0')
     {
        s3[i] = s1[i];
        i++;
    }
    s3[i] = s2; 
    s3[i + 1] = '\0';
    return s3;
}



void manage_letter(char *bytes) {
    int i = 0;
    char temp = 0;
    while(i < 8) {
        temp <<= 1;
        if(bytes[i] == '1') temp |= 1;
        i++;
    }
    
    if (temp == '\0') 
    { 
            char *new_global = ft_strjoin(global, temp);       
            write(1, global, ft_strlen(global));
            write(1, "\n", 1);
            global = new_global;
            free(global);
            global = NULL;
        }
}


void  handler(int reader, siginfo_t *signal, void *useless)
{
  static int bytes_counter = 0;
  static char bytes[8] = {0};
  (void)useless;
  (void)signal;
  if(reader == SIGINT)
  {  
       exit(1);
       free(global);
  }
  if(reader == SIGUSR1)
    bytes[bytes_counter++] = '0';
  else if(reader == SIGUSR2)
    bytes[bytes_counter++] = '1';
  if(bytes_counter == 8)
    {
      manage_letter(bytes);
      bytes_counter = 0;
    }
}
int main(void)
{
    pid_t pid;
    struct sigaction act;
    
    pid = getpid();
    printf("pid : %d\n", pid);

    act.sa_flags = SA_SIGINFO;
    act.sa_sigaction = handler;
    sigemptyset(&act.sa_mask);

   if ((sigaction(SIGUSR1, &act, 0)) == -1)
        write(1, "Error SIGUSR1\n", 14);
    if ((sigaction(SIGUSR2, &act, 0)) == -1)
        write(1, "Error SIGUSR2\n", 14);
    if ((sigaction(2, &act, 0)) == -1)
        write(1,"Error SIGINT\n", 13);
  while(1)
     pause();
  return (0);
}
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
char	*ft_strjoin(char const *s1, char s2)
{
	size_t	i;
	char	*s3;

	i = 0;
	while (s1[i] != '\0')
		i++;
	s3 = malloc (sizeof(char) * (i) + 2);
	if (!s3)
		return (NULL);
	i = -1;
	while (++i, s1[i] != '\0')
		s3[i] = s1[i];
  i =0;
	while (s3[i] != '\0')
  {
		s3[i + 1] = s2;
    i++;
  }
	s3[i] = '\0';
	return (s3);
}

char binary_to_char(char *binary)
{
    int i;
    i = 0;
    char temp = 0;
    while(i <= 7)
    {
        temp <<=1;
        if(binary[i] == '1')
            temp |= 1;
      if(binary[i] == '0')
            temp |= 0;
        i++;
    }
  return temp;
  global = ft_strjoin(global, temp);
  printf("%s", global);
}

void manage_letter(char *bytes)
{
  char letter;
  
  letter = binary_to_char(bytes);
  printf("letter : %c\n", letter);
}

void  handler(int reader, siginfo_t *signal, void *useless)
{
  static int bytes_counter;
  static char bytes[8];
  (void)useless;
  (void)signal;

  if(reader == SIGINT)
  {  
       exit(1);
  }
  if(reader == SIGUSR1)
  {
    bytes[bytes_counter] = '0';
    bytes_counter++;
  }
  if (reader == SIGUSR2)
  {
    bytes[bytes_counter] = '1';
    bytes_counter++;
  }
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
    sigemptyset(&act.sa_mask);
    act.sa_flags = SA_SIGINFO;
    act.sa_sigaction = handler;
    if ((sigaction(SIGUSR1, &act, 0)) == -1 || (sigaction(SIGUSR2, &act, 0)) == -1 || (sigaction(SIGINT, &act, 0) == -1))
      {
         write(2, "Error\n", 6);
         exit(EXIT_FAILURE);
     }
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
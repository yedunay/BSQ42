#ifndef BSQ_H
#define BSQ_H
#include <fcntl.h> //Dosya kontrol islemleri icin kullanilir .(open , close)
#include <errno.h> //Programın calismasi sirasinda olusan hata kodlarimni ve aciklamalarini icerir. 
#include <unistd.h> //write , read
#include <stdlib.h> //malloc ,free
#include <stdio.h> //fopen , fclose
#include <sys/types.h> //size_t,pid_t,uid_t
#include <sys/uio.h> // Unix giris/cıkıs islemleri

void        ft_putchar(char c);
void        ft_putstr(char *str);
void	    ft_putnbr(int nb);
char		*ft_strcpy(char *dest, char *src);
int		    ft_strlen(char *str);

#endif
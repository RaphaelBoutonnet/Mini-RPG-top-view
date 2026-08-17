#include <unistd.h>
#include <termios.h>
#include <stdio.h>
#include <stdlib.h>

void	ft_put_str(char *str)
{
	int (i) = 0;
	while (str[i])
		i++;
	write(1, str, i);
}

struct termios    *setup(struct termios *old)
{
    struct termios raw;

    tcgetattr(STDIN_FILENO, &raw);//permet de recuperer les attributs du terminal
    tcgetattr(STDIN_FILENO, old);
    raw.c_lflag &= ~(ECHO | ICANON);//desactive le mode canonique
    raw.c_cc[VMIN] = 1;//nombre min de caractere a recevoir
    raw.c_cc[VTIME] = 0;//attente a 0
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);//defini les attributs terminal
    return (old);
}

int    get_key(char *buff, int length)
{
		int nb = read(0, buff, length);
		return (nb);
}
/*
void    print_key(char    *buff, int size)
{
		printf("lettre : %d, %d, %d, %d\n", buff[0], buff[1], buff[2], size);
		fflush(stdout);//vide le tampon de sortie (merci google)
}
*/
char	*ft_str_reverse(char *str, int len)
{
	char temp;
	int i = 0;
	int lentemp = len;
	while (lentemp > (len / 2))
	{
		temp = str[lentemp - 1];
		str[lentemp - 1] = str[i];
		str[i] = temp;
		i++;
		lentemp--;
	}
	return (str);
}

int	ft_count_len(int nb)
{
	int i = 0;
	while (nb > 0)
	{
		nb = nb / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int nb)
{
	char	*res;
	int i = 0;
	int valneg = 0;
	if (nb < 0)
	{
		valneg = 1;
		nb = nb * (-1);
	}
	int len = ft_count_len(nb);
	res = malloc(((sizeof(char)) * len) + 1 + valneg);
	if (res == NULL)
		return NULL;
	int temp = 0;
	while (nb > 0)
	{
		temp = nb % 10;
		nb = nb / 10;
		res[i] = temp + '0';
		i++;
	}
	if (valneg == 1)
	{
		res[i] = '-';
		i++;
	}
	res = ft_str_reverse(res, len);
	res[i] = '\0';
	return (res);
}

int    main()
{
    struct termios    old;
    char	c[3];
    char	*strxa;
    strxa = malloc(sizeof(char) * 10);
    if (strxa == NULL)
	    return 1;
    char	*strya;
    strya = malloc(sizeof(char) * 10);
    if (strya == NULL)
	    return 1;
    int xa = 20;
    int ya = 20;

    old = *setup(&old);
    while (1)
    {
        get_key(c, 3);
	if (c[2] >= 65 && c[2] <= 68)
	{

		//
		//
		//ATTENTION PROBLEME JE PEUX appuyer sur nimporte quelle touche et ca me fait avancer sur x
		//
		//
		write(1, "\033[2J\033[H", 7);
		// print_key(c, 3);
		if (c[2] == 67) // Droite
			ya++;
		if (c[2] == 68) // Gauche
			ya--;
		if (c[2] == 66) // Bas
			xa++;
		if (c[2] == 65) // Haut
			xa--;
		write(1, "\033[", 2);
		strxa = ft_itoa(xa);
		ft_put_str(strxa);
		free(strxa);
		write(1, ";", 1);
		strya = ft_itoa(ya);
		ft_put_str(strya);
		free(strya);
		if (c[2] == 67) // Droite
			write(1, "Ho>", 3);
		if (c[2] == 68) // Gauche
			write(1, "H<o", 3);
		if (c[2] == 66) // Bas
			write(1, "Hov", 3);
		if (c[2] == 65) // Haut
			write(1, "Ho^", 3);
		fflush(stdout);//vide le tampon de sortie (merci google)	
	}
    }
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &old);
}

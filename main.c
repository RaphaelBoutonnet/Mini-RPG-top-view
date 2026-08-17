#include <unistd.h>
#include <termios.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct entity
{
	int alive;
	int xa;
	int ya;
} Enemy;

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

void    print_key(char    *buff, int size)
{
		printf("lettre : %d, %d, %d, %d\n", buff[0], buff[1], buff[2], size);
		fflush(stdout);//vide le tampon de sortie (merci google)
}

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

int	ft_print_object(char object, int xa, int ya)
{
    	char	*strxa;
    	strxa = malloc(sizeof(char) * 10);
    	if (strxa == NULL)
	    return 1;
    	char	*strya;
    	strya = malloc(sizeof(char) * 10);
    	if (strya == NULL)
	    return 1;
	write(1, "\033[", 2);
	strya = ft_itoa(ya);
	ft_put_str(strya);
	free(strya);
	write(1, ";", 1);
	strxa = ft_itoa(xa);
	ft_put_str(strxa);
	free(strxa);
	write(1, "H", 1);
	write(1, &object, 1);
	return (0);
}

void	ft_show_enemies(void)
{
	ft_print_object('x', 18, 18);
}

int    main()
{
   	struct termios    old;
   	char	c[3];
   	int xa = 20;
    	int ya = 20;
	int droite = 0;
	int gauche = 0;
	int haut = 0;
	int bas = 0;
	Enemy mob1;
	mob1.alive = 1;
	mob1.xa = 18;
	mob1.ya = 18;

    	old = *setup(&old);
    	while (1)
    	{
		if (xa == 18 && ya == 18 && mob1.alive == 1)
		{
			while (c[0] != 101)
			{
				write(1, "\033[2J\033[H\033[?25l", 13); // Efface l'ecran du terminal et le curseur
				ft_print_object(' ', 20, 20);
				write(1, "YOU ARE DEAD - Press E to revive", 32);
				get_key(c, 3);
			}
			xa = 20;
			ya = 20;
			write(1, "\033[2J\033[H\033[?25l", 13); // Efface l'ecran du terminal et le curseur
			print_key(c, 3);
			write(1, "\nUse arrows to move, D to attack, E to make the enemy respawn.", 61);
			ft_print_object('O', xa, ya);
			ft_print_object('>', xa + 1, ya);
			ft_show_enemies();
			fflush(stdout);//vide le tampon de sortie (merci google)	
		}
        	get_key(c, 3);
		if ((c[2] >= 65 && c[2] <= 68) && c[0] == 27)
		{
			write(1, "\033[2J\033[H\033[?25l", 13); // Efface l'ecran du terminal et le curseur
			print_key(c, 3);
			write(1, "\nUse arrows to move, D to attack, E to make the enemy respawn.", 61);
			if (c[2] == 67) // Droite
			{
				xa++;
				ft_print_object('O', xa, ya);
				ft_print_object('>', xa + 1, ya);
				droite = 1;
				gauche = 0;
				haut = 0;
				bas = 0;
			}
			if (c[2] == 68) // Gauche
			{
				xa--;
				ft_print_object('<', xa - 1, ya);
				ft_print_object('O', xa, ya);
				gauche = 1;
				droite = 0;
				haut = 0;
				bas = 0;
			}
			if (c[2] == 66) // Bas
			{
				ya++;
				ft_print_object('O', xa, ya);
				ft_print_object('-', xa, ya + 1);
				bas = 1;
				droite = 0;
				gauche = 0;
				haut = 0;
			}
			if (c[2] == 65) // Haut
			{
				ya--;
				ft_print_object('-', xa, ya - 1);
				ft_print_object('O', xa, ya);
				haut = 1;
				droite = 0;
				gauche = 0;
				bas = 0;
			}
		}	
		if (c[0] == 100)
		{
			write(1, "\033[2J\033[H\033[?25l", 13); // Efface l'ecran du terminal et le curseur
			print_key(c, 3);
			if (droite)
			{
				ft_print_object('O', xa, ya);
				ft_print_object('>', xa + 1, ya);
				ft_print_object('-', xa + 3, ya);
				ft_print_object('|', xa + 4, ya);
				ft_print_object('=', xa + 5, ya);
				ft_print_object('=', xa + 6, ya);
				ft_print_object('>', xa + 7, ya);
				if (ya == 18 && ((xa + 1) <= 18) && (18 <= (xa + 7)))
					mob1.alive = 0;
			}
			if (gauche)
			{
				ft_print_object('-', xa - 3, ya);
				ft_print_object('|', xa - 4, ya);
				ft_print_object('=', xa - 5, ya);
				ft_print_object('=', xa - 6, ya);
				ft_print_object('<', xa - 7, ya);
				ft_print_object('<', xa - 1, ya);
				ft_print_object('O', xa, ya);
				if (ya == 18 && ((xa - 1) >= 18) && (18 >= (xa - 7)))
					mob1.alive = 0;
			}
			if (haut)
			{
				ft_print_object('^', xa, ya - 3);
				ft_print_object('|', xa, ya - 2);
				ft_print_object('-', xa, ya - 1);
				ft_print_object('O', xa, ya);
				if (xa == 18 && ((ya - 1) >= 18) && (18 >= (ya - 3)))
					mob1.alive = 0;
			}
			if (bas)
			{
				ft_print_object('O', xa, ya);
				ft_print_object('-', xa, ya + 1);
				ft_print_object('|', xa, ya + 2);
				ft_print_object('v', xa, ya + 3);
				if (xa == 18 && ((ya + 1) <= 18) && (18 <= (ya + 3)))
					mob1.alive = 0;
			}
		}
		if (c[0] == 101)
			mob1.alive = 1;
		if (mob1.alive == 1)
			ft_show_enemies();
		fflush(stdout);//vide le tampon de sortie (merci google)	
    	}	
    	tcsetattr(STDIN_FILENO, TCSAFLUSH, &old);
	return (0);
}		

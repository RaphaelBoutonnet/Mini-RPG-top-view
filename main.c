#include <unistd.h>
#include <termios.h>
#include <stdio.h>
#include <stdlib.h>

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

int    main()
{
    struct termios    old;
    char            c[3];

    old = *setup(&old);
    while (1)
    {
        get_key(c, 3);
	if (c[2] == 67)
		/* write(1, "\033[10;20HDroite\n", 15); */
		write(1, "\033[", 2);
		write(1, "10", 2); // A cet endroit, creer un char qui commence là où je veux commencer dans la map. Quand j'appuie sur la touche, relance une boucle qui incrémente la valeur de ce char.
		write(1, ";", 1);
		write(1, "20", 2);
		write(1, "HSalut\n", 7);
		
	if (c[2] == 68)
		write(1, "\033[1;2HGauche\n", 13);
	fflush(stdout);//vide le tampon de sortie (merci google)
       /* if (size)
            print_key(c, size); */
    }
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &old);
}

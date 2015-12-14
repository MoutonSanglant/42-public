#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <libft.h>

void strrev(char *p)
{
	char *q = p;
	while(q && *q) ++q;
	for(--q; p < q; ++p, --q)
	*p = *p ^ *q,
	*q = *p ^ *q,
	*p = *p ^ *q;
}

char	*to_hex(unsigned short n)
{
	unsigned short	p;
	char		*str;
	unsigned char	*r;

	str = (char *)malloc(sizeof(char) * 8);

	r = (unsigned char*)malloc(sizeof(unsigned char));
	p = n;
	while (p > 0)
	{
		*r = p % 16;
		if (*r > 9)
			*r = *r + ('a' - 10);
		else
			*r = *r + '0';
		p = p / 16;

		str = strcat(str, (char *)r);
	}
	free(r);
	strrev(str);
	return (str);
}

char	*shift(char *buff, unsigned short n)
{
	//buff = strcat(buff, ft_itoa(n));
	//buff = strcat(buff, ": 0x");
	buff = strcat(buff, "0x");
	buff = strcat(buff, to_hex(n));
	//buff = strcat(buff, ft_itoa(n));
	buff = strcat(buff, ", ");

	return (buff);
}

int	main(int argc, char **argv)
{
	int	fd;
	char	*buff;
	size_t	bytes;
	unsigned short	patterns[19];

	if (argc < 1 && argv[0][0] == '\0')
		return (1);

	patterns[0] = 1 | 2 | 16 | 32;
	patterns[1] = 1 | 2 | 4 | 8;
	patterns[2] = 1 | 16 | 256 | 4096;
	patterns[3] = 2 | 4 | 16 | 32;
	patterns[4] = 1 | 16 | 32 | 512;
	patterns[5] = 1 | 2 | 32 | 64;
	patterns[6] = 2 | 16 | 32 | 256;
	patterns[7] = 1 | 16 | 256 | 512;
	patterns[8] = 1 | 2 | 4 | 16;
	patterns[9] = 1 | 2 | 32 | 512;
	patterns[10] = 4 | 16 | 32 | 64;
	patterns[11] = 2 | 32 | 256 | 512;
	patterns[12] = 1 | 16 | 32 | 64;
	patterns[13] = 1 | 2 | 16 | 256;
	patterns[14] = 1 | 2 | 4 | 64;
	patterns[15] = 1 | 2 | 4 | 32;
	patterns[16] = 2 | 16 | 32 | 512;
	patterns[17] = 2 | 16 | 32 | 64;
	patterns[18] = 1 | 16 | 32 | 256;

	fd = open("output.txt", O_WRONLY | O_CREAT);
	if (fd)
	{
		buff = (char *)malloc(sizeof(char) * 1024);
		buff[0] = '\0';
	
		buff = shift(buff, patterns[0]);
		buff = shift(buff, patterns[0] << 1);
		buff = shift(buff, patterns[0] << 2);
		buff = shift(buff, patterns[0] << 4);
		buff = shift(buff, patterns[0] << 5);
		buff = shift(buff, patterns[0] << 6);
		buff = shift(buff, patterns[0] << 8);
		buff = shift(buff, patterns[0] << 9);
		buff = shift(buff, patterns[0] << 10);
		buff = shift(buff, patterns[1]);
		buff = shift(buff, patterns[1] << 4);
		buff = shift(buff, patterns[1] << 8);
		buff = shift(buff, patterns[1] << 12);
		buff = shift(buff, patterns[2]);
		buff = shift(buff, patterns[2] << 1);
		buff = shift(buff, patterns[2] << 2);
		buff = shift(buff, patterns[2] << 3);
		buff = shift(buff, patterns[3]);
		buff = shift(buff, patterns[3] << 1);
		buff = shift(buff, patterns[3] << 4);
		buff = shift(buff, patterns[3] << 5);
		buff = shift(buff, patterns[3] << 8);
		buff = shift(buff, patterns[3] << 9);
		buff = shift(buff, patterns[4]);
		buff = shift(buff, patterns[4] << 1);
		buff = shift(buff, patterns[4] << 2);
		buff = shift(buff, patterns[4] << 4);
		buff = shift(buff, patterns[4] << 5);
		buff = shift(buff, patterns[4] << 6);
		buff = shift(buff, patterns[5]);
		buff = shift(buff, patterns[5] << 1);
		buff = shift(buff, patterns[5] << 4);
		buff = shift(buff, patterns[5] << 5);
		buff = shift(buff, patterns[5] << 8);
		buff = shift(buff, patterns[5] << 9);
		buff = shift(buff, patterns[6]);
		buff = shift(buff, patterns[6] << 1);	
		buff = shift(buff, patterns[6] << 2);
		buff = shift(buff, patterns[6] << 4);
		buff = shift(buff, patterns[6] << 5);
		buff = shift(buff, patterns[6] << 6);

		buff = shift(buff, patterns[7]);
		buff = shift(buff, patterns[7] << 1);
		buff = shift(buff, patterns[7] << 2);
		buff = shift(buff, patterns[7] << 4);
		buff = shift(buff, patterns[7] << 5);
		buff = shift(buff, patterns[7] << 6);
		buff = shift(buff, patterns[8]);
		buff = shift(buff, patterns[8] << 1);
		buff = shift(buff, patterns[8] << 4);
		buff = shift(buff, patterns[8] << 5);
		buff = shift(buff, patterns[8] << 8);
		buff = shift(buff, patterns[8] << 9);
		buff = shift(buff, patterns[9]);
		buff = shift(buff, patterns[9] << 1);
		buff = shift(buff, patterns[9] << 2);
		buff = shift(buff, patterns[9] << 4);
		buff = shift(buff, patterns[9] << 5);
		buff = shift(buff, patterns[9] << 6);

		buff = shift(buff, patterns[10]);
		buff = shift(buff, patterns[10] << 1);
		buff = shift(buff, patterns[10] << 4);
		buff = shift(buff, patterns[10] << 5);
		buff = shift(buff, patterns[10] << 8);
		buff = shift(buff, patterns[10] << 9);

		buff = shift(buff, patterns[11]);
		buff = shift(buff, patterns[11] << 1);
		buff = shift(buff, patterns[11] << 2);
		buff = shift(buff, patterns[11] << 4);
		buff = shift(buff, patterns[11] << 5);
		buff = shift(buff, patterns[11] << 6);

		buff = shift(buff, patterns[12]);
		buff = shift(buff, patterns[12] << 1);
		buff = shift(buff, patterns[12] << 4);
		buff = shift(buff, patterns[12] << 5);
		buff = shift(buff, patterns[12] << 8);
		buff = shift(buff, patterns[12] << 9);

		buff = shift(buff, patterns[13]);
		buff = shift(buff, patterns[13] << 1);
		buff = shift(buff, patterns[13] << 2);
		buff = shift(buff, patterns[13] << 4);
		buff = shift(buff, patterns[13] << 5);
		buff = shift(buff, patterns[13] << 6);

		buff = shift(buff, patterns[14]);
		buff = shift(buff, patterns[14] << 1);
		buff = shift(buff, patterns[14] << 4);
		buff = shift(buff, patterns[14] << 5);
		buff = shift(buff, patterns[14] << 8);
		buff = shift(buff, patterns[14] << 9);

		buff = shift(buff, patterns[15]);
		buff = shift(buff, patterns[15] << 1);
		buff = shift(buff, patterns[15] << 4);
		buff = shift(buff, patterns[15] << 5);
		buff = shift(buff, patterns[15] << 8);
		buff = shift(buff, patterns[15] << 9);

		buff = shift(buff, patterns[16]);
		buff = shift(buff, patterns[16] << 1);
		buff = shift(buff, patterns[16] << 2);
		buff = shift(buff, patterns[16] << 4);
		buff = shift(buff, patterns[16] << 5);
		buff = shift(buff, patterns[16] << 6);

		buff = shift(buff, patterns[17]);
		buff = shift(buff, patterns[17] << 1);
		buff = shift(buff, patterns[17] << 4);
		buff = shift(buff, patterns[17] << 5);
		buff = shift(buff, patterns[17] << 8);
		buff = shift(buff, patterns[17] << 9);

		buff = shift(buff, patterns[18]);
		buff = shift(buff, patterns[18] << 1);
		buff = shift(buff, patterns[18] << 2);
		buff = shift(buff, patterns[18] << 4);
		buff = shift(buff, patterns[18] << 5);
		buff = shift(buff, patterns[18] << 6);

		bytes = write(fd, buff, strlen(buff));
		buff[bytes] = '\n';
		printf("%i bytes written.\n", bytes);
	}
	return (0);
}

#include <unistd.h>

//	INPUTS:		x_max	-- array width								INPUT
//				y_max	-- array height								INPUT
//				r_base	-- base radius (changed by deformation)		INPUT
//				x_r		-- x radius component (elipse)
//				y_r		-- y radius component (elipse)
//						>> (x_r + y_r) / 2 == r_base
//				x_disp	-- x displacement from center				
//				y_disp	-- y displacement from center				




//----------------------------------------------------ATOI-------------------------------------------------
int	atoi(char *str)
{
	int	i = 0;
	int	res = 0;
	int sign = 1;

	if (str[0] == '-')
	{
		sign = -sign;
		i++;
	}
	while (str[i] != '\0')
		{
			res = res * 10 + (str[i] - '0');
			i++;
		}
	return (res);
}

//----------------------------------------Index, X, & Y translations-------------------------------------
//	"x" component based on 	"i" and "array width" 
int		i_x		(int indx, int x_max)
{
		return	(indx % x_max);
}


//	"y" component based on 	"i" and "array width" 
int		i_y		(int indx, int x_max)
{
		return	(indx / x_max);
}


//	"i" value based on		"i_x" and "i_y" and "array width" 
int		i_val	(int i_x, int i_y, int x_max)
{
		return	(i_y * x_max + i_x);
}

//----------------------------------------ELIPSE RADIUSES------------------------------------------------
//	"x_center" based on		"x_max"
int	x_c (int x_max)
{
	return (x_max / 2);
}

//	"y_center" based on		"y_max"
int	y_c (int y_max)
{
	return (y_max / 2);
}

//	"i_center" based on		"x_max" and "y_max" 
int	i_c (int x_max, int y_max)
{
	return ((x_max * y_max) / 2);
}

//	"x_radius" based on		"y_displacement" and "base radius"
//							given displacement of 0, the ball will be in the center
int	x_r (int y_disp, int r_base, int y_max)
{
	if ((y_disp + r_base) >= (y_max / 2))
		return (r_base + (y_disp + r_base) - (y_max / 2));
	else
		return (r_base);
}


//	"y_radius" based on		"x_displacement" and "base radius"
//							given displacement of 0, ball will be in the center
int	y_r (int y_disp, int r_base, int y_max)
{
	return (r_base * 2 - x_r(y_disp, r_base, y_max));
}

//----------------------------------------SQR && SQRT-----------------------------------------------------
//	"sqr" based on			"nbr"
int 	sqr	(int nbr)
{
		return (nbr * nbr);
}


//	"ration sqrt" based on	"nbr" input
int 	squrt	(int nbr)
{
	int	i	= 0;
	while (i <= nbr )
	{
		if (nbr == i * i)
				return (i);
		else if	((nbr > i * i) && (nbr < ((i + 1) * (i + 1))))
		{
			if 	((nbr - (i * i)) < (((i + 1) * (i + 1)) - nbr))
				return (i);
			else
				return (i + 1);
		}
		else{}

		i++;
	}
}

//----------------------------------------CALCULATE ELIPSE DEFORMATION------------------------------------------------
//	DRAW ARRAY based on		"array width" and "array height"
void	arr (int x_max, int y_max, int r_base, int y_disp)
{
		int	i = 0;

		int xc = x_c (x_max);
		int yc = y_c (y_max);

		while (i < x_max * y_max)
		{
			int xr = x_r(y_disp, r_base, y_max);
			int yr = y_r(y_disp, r_base, y_max);

			int ix = i_x (i, x_max);
			int iy = i_y (i, x_max);

			if ((i >= x_max) && (i % x_max == 0))
				write (1, "\n", 1);
			if	(((ix - xc == squrt(sqr(xr) - (sqr(iy - yc - y_disp) * sqr(xr) / sqr(yr)))) ||	//right side of the elipse
				(xc - ix == squrt(sqr(xr) - (sqr(iy - yc - y_disp) * sqr(xr) / sqr(yr))))) &&	//left side of the elipse
				((iy - y_disp) <= (yc + yr)) && ((iy - y_disp) >= (yc - yr)))
				write (1, "o ", 2);
			else
				write (1, "~ ", 2);
			i++;
		}
		write (1, "\n", 1);
}

//----------------------------------------MAIN (input 3 arguments and have ur boncy balls)------------------------------------------------
int main(int ac, char **av)
{
	int	y_disp = 0;

	if (ac != 4)
	{
		write (1, "Input 3 arguments:\n", 20);
		write (1, "1. Array width, \n2. Array height, \n3. Base-radius of the ball\n", 63);
	}
	else
	{
		int	x_max	= atoi (av[1]);
		int y_max	= atoi (av[2]);
		int r_base	= atoi (av[3]);
		int xr		= r_base;
		int yr		= r_base;
		int i		= 0;

		if (r_base * 2 >= x_max || r_base >= y_max)
			write (1, "The ball radius is too large for this array\n", 45);
		else
		{
			while (y_max / 2 - i >= r_base)
			{
				
				arr (x_max, y_max, r_base, y_disp);
				int j = 0;	
				while (j <= x_max - 1)
				{
					write (1, "T ", 2);
					j++;
				}
				write (1, "\n", 1);
				y_disp++;
				xr	= x_r(y_disp, r_base, y_max);
				yr	= y_r(y_disp, r_base, y_max);
				if (yr * 2 <= xr)
				{
					while (y_disp >= 0 + i)
					{
					arr (x_max, y_max, r_base, y_disp);
					int j = 0;	
					while (j <= x_max - 1)
					{
						write (1, "T ", 2);
						j++;
					}
					write (1, "\n", 1);
						y_disp--;
						usleep (100000);
					}
					i++;
				}
				usleep (100000);
			}
		}
		
	}
}

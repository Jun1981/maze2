//=================================
#include	"maze.h"

static	Funcs	funcs = { "‘S•ûŒü(‰ü)" , init, walkAround };

Funcs*	getDemo02Info	( void ) { return &funcs; }

static	int	dir = DirUp;

static	void	init	( void )
{
	dir = DirUp;
}

static	int	walkAround	( void )
{
	int	i;
	for ( i = 0; i < 4; i++ ){
		MapStatus	stat = canMove ( dir );
		if ( stat != MapWall ){
			break;
		}
		dir++;
		if ( dir >= DirInvalid ){
			dir = DirUp;
		}
	}
	return dir;
}

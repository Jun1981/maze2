#include	<stdio.h>
#include	<conio.h>
#include	<windows.h>
#include	<stdlib.h>

#if !defined	__MAZE_H__ 
#define	__MAZE_H__ 
#pragma	warning	( disable : 4996 )
//=================================
//	定数
//=================================
//	キーボード
#define	KeyEscape	(0x1b)		//	エスケープキー

//	マップ情報
#define	MazeStart	'S'			//	スタート地点
#define	MazeGoal	'G'			//	ゴール
#define	MazeAisle	' '			//	通路

//	状態表示色
#define	ColorGoaled	( FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY )
#define	ColorRunning	( BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY )
#define	ColorDefault	( BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY  )

//	進行方向
#define	DirUp	(0)
#define	DirRight	(1)
#define	DirDown	(2)
#define	DirLeft	(3)
#define	DirInvalid	(4)

//=================================
//	型宣言
//=================================
//	mapの状況
typedef	enum	{ MapWall = 0, MapStart = 1, MapAisle = 2, MapGoal = 3, MapInvalid = 4 } MapStatus;

//	位置情報
typedef	struct {
	int	x;
	int	y;
} Pos;

// プレーヤがセットする情報
typedef	struct	{
	char*		name;
	void	( *init )		( void );
	int		( *walkAround )	( void );
} Funcs;

//=================================
//	etc
//=================================
#if !defined ( __MAZE_C__ )
	#define	Extern	extern
	static	void	init	( void );
	static	int		walkAround	( void );
#else
	#define	Extern	extern "C"
#endif


//=================================
//	公開関数のプロトタイプ宣言
//=================================
Extern	int	getMazeWidth	( void );
Extern	int	getMazeHeight	( void );
Extern	Pos	getCurrentPosition	( void );
Extern	MapStatus	canMove	( int );

#endif	( __MAZE_H__ )


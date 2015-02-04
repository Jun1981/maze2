#define	__MAZE_C__
#include ".\maze.h"
#include "..\dxLib\DxLib.h"

//=================================
//	定数
//=================================
#define	MaxFilePath	(128)			// ファイル名の最大長+1
#define	MapDir	".\\map\\"			// マップを格納するフォルダ名
#define	FileExtention	".map"			// マップファイルの拡張子
#define	ArraySizeIncrement	(5)		// 自動拡張配列の拡張サイズ
#define	PosUndefined	(-1)			// 位置情報が未確定なときの値
#define	PlayerMax	(8)				// プレイヤー数の最大
#define	StatusTop	(20)			// 情報領域の一番上の行番号
#define	NoError		(0)				// 初期化成功
#define	DxLibError		(-1)		// DXLibのエラー
#define	MapLoadError		(-2)	//  マップのエラー
#define	Wait			(100)		// プレイヤーを動かす間隔

// ブロック
#define		BlockHeight	(16)
#define		BlockWidth	(16)
#define		BlockType	(4)
static	int	grpBlocks [ BlockType ];		// ブロックの画像( ( 16 * 16 ) * 4 )

// 座標変換
#define	convertX(x)		((x)*BlockWidth)		// キャラクタ座標からグラフィック座標への変換
#define	convertY(y)		((y)*BlockHeight)
#define	StatusY(y)		convertY(map.height+y+1)	// 状況表示

//=================================
//	構造体定義
//=================================
//---------------------------------------------------------
//	Map	地図情報を保持する
//---------------------------------------------------------
typedef	struct {
	int	width;		// 地図の幅
	int	height;		// 地図の高さ
	char**	map;	// 地図の各行の先頭アドレス
	Pos	start;		// スタート地点の座標
	Pos	goal;		// ゴールの座標
} Map;

//---------------------------------------------------------
//	Player	プレーヤ情報を保持する
//---------------------------------------------------------
typedef	struct {
	Funcs*	funcs;			// 名前や関数
	Pos		currentPosition;	// 現在地の座標
	int		dir;				// 現在動いている方向
	int		queryCount;		// 問い合わせ回数
	bool	hasGoal;			// ゴールしたか
	int		rank;			// 歩数順位
} Player;

//=================================
//	プロトタイプ宣言
//=================================
static	int		init			( void );		// システムの初期化
//---------------------------------------------------------
//	マップ関連のメソッド(非公開)
//---------------------------------------------------------
static	Map	initMap		( void );		// マップの初期化
static	void	inputName	( char*, int );	// ファイル名取得
static	char*	loadMap		( char* );	// マップファイル取得
static	void	showMap	( Map );		// マップ表示
static	Map	createMapInfo( char* );		// マップ情報生成
static	int		getFileSize	( FILE* );	// ファイルサイズ取得
static	char**	expandArray	( char** );	// 配列の拡張
//---------------------------------------------------------
//	プレーヤ関連のメソッド(非公開)
//---------------------------------------------------------
static	int		initPlayers	( void );		// プレーヤ情報初期化
static	void	registerPlayer	( int,  Funcs* );// プレーヤの追加
static	void	showStatus	( Pos );		// 現在状況の表示
static	Pos		move		( int );		// プレーヤの移動
static	void	questMaze	( void );		// 迷路探索ルーチンの呼び出し
static	void	calcRank		( void );		// 歩数順位を求める

//---------------------------------------------------------
//	汎用メソッド(非公開)
//---------------------------------------------------------
static	int		openFileDialog	( LPSTR, LPSTR, LPCTSTR, LPCTSTR, HWND );
static	char*	strip			( char* );	// 文字末の制御コード削除
static	void	showMessage		( char* );

//---------------------------------------------------------
//	迷路探索
//---------------------------------------------------------
extern "C"	Funcs*	getGroup01Info	( void );
extern "C"	Funcs*	getGroup02Info	( void );
extern "C"	Funcs*	getGroup03Info	( void );
extern "C"	Funcs*	getGroup04Info	( void );
extern "C"	Funcs*	getGroup05Info	( void );
extern "C"	Funcs*	getGroup06Info	( void );



//=================================
//	ファイル内グローバル変数
//=================================
static	char	currentPath [ MAX_PATH ];
static	int		winWidth, winHeight;
static	Map	map;
static	Player	players[ PlayerMax ];
static	int		currentPlayer;			// 現在処理中のプレーヤ番号
static	int		playerCount;				// 全プレーヤ数
static	int		running;		// ゴールしていないプレーヤの数

//=================================
//	entry point
//=================================
int	WINAPI	WinMain	( HINSTANCE	hInstance,
					HINSTANCE	hPrevInstance,
					LPSTR		lpCmdLine,
					int			nCmdShow )
{

	GetModuleFileName ( hInstance, currentPath, MAX_PATH );
	// マップの読み込み
	map = initMap ( );
	if ( map.map != NULL ){
		// プレーヤの登録
		running = playerCount = initPlayers ( );
		// システムの初期化
		if ( init ( ) == NoError ){
			int	isContinued = true;
			while( !ProcessMessage()
					&& isContinued
					&& running > 0 ){
				SetDrawScreen( DX_SCREEN_BACK ) ;
				showMap ( map );
				questMaze ( );
				ScreenFlip ( ) ;
				SetDrawScreen( DX_SCREEN_BACK ) ;
				if ( CheckHitKey( KEY_INPUT_ESCAPE ) != 0 ){
					if ( MessageBox ( GetMainWindowHandle(), "終了しますか?", "終了確認", MB_OKCANCEL|MB_ICONQUESTION ) == IDOK ){
						isContinued = false;
					}
				}
				WaitTimer ( Wait );
			}
			showMessage ( "終了します" );
			DxLib_End ( );
		} else {
			showMessage ( "DXLibの初期化に失敗しました。" );
		}
	} else {
		showMessage ( "マップの読み込みに失敗しました。" );
	}
	return 0 ;				// ソフトの終了 
}

static	int	init	( void )
{
	ChangeWindowMode( true );
	SetWindowSizeChangeEnableFlag ( true );
	//
	int	ret = DxLib_Init( );
	if ( ret != DxLibError ){
		if ( map.map != NULL ){
			// ウインドウサイズ/色数の調整
			int	depth;
			GetScreenState ( &winWidth, &winHeight, &depth );
			if ( winWidth < convertX (50) ){
				winWidth = convertX (50);
			}
			if ( winWidth < convertX ( map.width ) ){
				winWidth = convertX ( map.width );
			}
			if ( winHeight < convertY ( ( map.height+playerCount+1 ) ) ){
				winHeight = convertY ( ( map.height+playerCount+1 ) ) ;
			}
			SetGraphMode ( winWidth, winHeight, depth );
			// 壁用グラフィックの読み込み
			char	bmpname [ MAX_PATH ];
			strcpy ( bmpname, currentPath );
			char*	p = bmpname + strlen ( bmpname );
			while ( p >= bmpname && *p != '\\' ){
				*p = '\0';
				p--;
			}
			strcat ( p, "..\\resource\\blocks.bmp" );
			ret = LoadDivGraph ( bmpname,
								BlockType,
								BlockType, 1,
								BlockWidth, BlockHeight,
								grpBlocks );
		} else {
			ret = MapLoadError;
		}
	}
	return ret;
}

//=================================
//	マップ関連のメソッド(非公開)
//=================================
//---------------------------------------------------------
//	initMap	初期化
//---------------------------------------------------------
static	Map	initMap	( void )
{
	char*	buf;
	char	mapName [ MaxFilePath ];
	Map	info;

	inputName ( mapName, sizeof ( mapName ) );
	if ( *mapName != '\0' ){
		buf = loadMap ( mapName );
		if ( buf != NULL ){
			info = createMapInfo ( buf );
		} else {
			info.map = NULL;
		}
	} else {
		info.map = NULL;
	}
	return info;
}

//---------------------------------------------------------
//	inputName	ファイル名入力
//				buf	入力されたファイル名を保持する領域のアドレス
//				bufSize	入力領域のサイズ
//---------------------------------------------------------
static	void	inputName	( char* 	buf ,
							int	bufSize )
{
	char	name[ MAX_PATH ];
	char	path[ MAX_PATH ];
	memset ( buf, bufSize, '\0' );

	HWND mainWindow = GetMainWindowHandle();
	if ( openFileDialog( name, path,
			"map(*.map)\0*.map\0text(*.txt)\0*.txt\0All files(*.*)\0*.*",
			"",
			mainWindow ) == TRUE  ){
		if ( strlen ( name ) < ( size_t )bufSize ){
			strcpy ( buf, name );
		}
	} else {
		*buf = '\0';
	}
}

//---------------------------------------------------------
//	loadMap	マップファイルの読み込み
//			返り値 : マップ領域の先頭アドレス
//			name	ファイル名
//---------------------------------------------------------
static	char*	loadMap		( char*	mapName )
{
	char*	buf = NULL;
	if  ( mapName != NULL ){
		FILE*	fp = fopen ( mapName, "rt" );
		if ( fp != NULL ){
			int	size = getFileSize ( fp );
			buf = ( char* )malloc ( size + 1 );
			if ( buf != NULL ){
				memset ( buf, '\0', size + 1 );
				fread ( buf, size, 1, fp );
				fclose ( fp );
			}
		}
	}

	return buf;
}

//---------------------------------------------------------
//	createMapInfo	マップからサイズや各行の先頭アドレスを取得する。
//			返り値 : マップ情報
//			name	マップファイルを読み込んだ領域へのポインタ
//---------------------------------------------------------
static	Map	createMapInfo	( char*	buf )
{
	Map	info = { 0, 0, NULL, 
			{PosUndefined, PosUndefined},
			{PosUndefined, PosUndefined}  };
	int	arraySize = 0;
	int	i;

	while ( buf != NULL ){
		if ( info.height >= arraySize - 1 ){
			if ( ( info.map = expandArray ( info.map )  ) == NULL ){
				return info;
			}
		}
		if ( info.height == 0 ) {
			info.map [ info.height ] = buf;
		} else {
			*buf = '\0';
			info.map [ info.height ] = buf + 1;
		}
		buf = strchr ( buf + 1, '\n' );
		info.height ++;
	}

	for ( i = 0; i < info.height; i++ ){
		char*	p;
		if  ( info.width < ( int )strlen ( info.map [ i ] )  ) {
			info.width = strlen ( info.map [ i ] );
		}
		if ( ( p = strchr ( info.map [ i ], 'S' ) ) != NULL ){
			info.start.x = p - info.map [ i ];
			info.start.y = i;
		}
		if ( ( p = strchr ( info.map [ i ], 'G' ) ) != NULL ){
			info.goal.x = p - info.map [ i ];
			info.goal.y = i;
		}
	}
	return info;
}
//---------------------------------------------------------
//	getFileSize	ファイルサイズの取得
//				返り値 : ファイルサイズ
//				name	サイズを調べるファイルへのファイルポインタ
//---------------------------------------------------------
static	int	getFileSize	( FILE*	fp )
{
	int	size;
	int	curPos = ftell ( fp );
	fseek ( fp, 0L, SEEK_END );
	size = ftell ( fp );
	fseek ( fp, curPos, SEEK_SET );
	return size;
}

//---------------------------------------------------------
//	expandArray	マップの各行の先頭アドレスを保持する配列要素数を拡張する。
//				返り値 : 新しい配列
//				array	現在の配列
//---------------------------------------------------------
static	char**	expandArray	( char**	array )
{
	static	int	arraySize = 0;
	int	newSize;
	char**	newArray;

	if ( array == NULL ){
		arraySize = 0;
	}
	newSize = arraySize + ArraySizeIncrement;
	newArray = ( char ** ) malloc ( newSize * sizeof ( char * ) );

	if ( newArray != NULL ){
		memset ( newArray, '\0', newSize * sizeof ( char * ) );
		if ( array != NULL ){
			memcpy ( newArray, array, arraySize * sizeof ( char * ) );
		}
		arraySize = newSize;
	} else {
		arraySize = 0;
	}
	if ( array != NULL ){
		free ( array );
	}

	return newArray;
}

//---------------------------------------------------------
//	showMap	マップの表示
//			info	マップ情報
//---------------------------------------------------------
static	void	showMap	( Map	info  )
{
	int	i;
	for ( i = 0; i < info.height; i++ ){
		for ( int j = 0; j < info.width; j++ ){
			int	blockID = MapWall;
			switch ( info.map [ i ] [ j ] ){
				case MazeStart:
					blockID = MapStart;
					break;
				case MazeGoal:
					blockID = MapGoal;
					break;
				case MazeAisle:
					blockID = MapAisle;
					break;
			}
			DrawGraph( convertX( j ), convertY ( i ), grpBlocks [ blockID ] , FALSE ) ;
		}
	}
	DrawBox( 0 , convertY ( i ) , winWidth , winHeight ,GetColor ( 0, 0, 0 ), true );
}
//=================================
//	プレーヤ関連のメソッド(非公開)
//=================================
//---------------------------------------------------------
//	initPlayers	初期化
//---------------------------------------------------------
static	int	initPlayers	( void )
{
	int	i = 0;
	registerPlayer ( i++, getGroup01Info ( ) );
	registerPlayer ( i++, getGroup02Info ( ) );
	registerPlayer ( i++, getGroup03Info ( ) );
	registerPlayer ( i++, getGroup04Info ( ) );
	registerPlayer ( i++, getGroup05Info ( ) );
	registerPlayer ( i++, getGroup06Info ( ) );
	return	i;
}

//---------------------------------------------------------
//	registerPlayer	プレーヤ配列に、新しい要素を追加する。
//---------------------------------------------------------
static	void	registerPlayer	( int	seq,
							Funcs*	funcs )
{
	players [ seq ].funcs = funcs;
	players [ seq ].currentPosition = map.start;
	players [ seq ].queryCount = 0;
	players [ seq ].hasGoal = false;
	players [ seq ].funcs->init ( );
}

//---------------------------------------------------------
//	move	プレーヤを移動する。
//			返り値 : 移動後の座標
//			dir	移動したい方向
//---------------------------------------------------------
static	Pos	move	( int	dir )
{
	Pos	current = players [ currentPlayer ].currentPosition;
	switch ( dir ) {
		case DirUp: current.y--; break;
		case DirRight:  current.x++; break;
		case DirDown:  current.y++; break;
		case DirLeft:  current.x--; break;
	}
	return current;
}

//---------------------------------------------------------
//	questMaze	迷路探索ルーチンの呼び出し
//---------------------------------------------------------
static	void	questMaze	( void )
{
	for ( currentPlayer = 0;
		currentPlayer < playerCount;
		currentPlayer ++ ){
		Player*	player = &players [ currentPlayer ];
		Pos	beforeMove = player->currentPosition;
		if ( !player->hasGoal ){
			int	dir = player->funcs->walkAround (  );
			// 移動しようとしている方向が壁でなければ、移動させる
			MapStatus	stat = canMove ( dir );
			if ( stat != MapWall ){
				player->currentPosition = move ( dir );
				player->dir = dir;
			}
			if ( stat != MapGoal ){
				char	mark [ 2 ] = { currentPlayer + 'A', '\0' };
				// 現在位置にマークを表示
				DrawString( convertX( player->currentPosition .x ),
						convertY ( player->currentPosition .y ),
						mark, FALSE ) ;
			} else {
				player->hasGoal = true;
				running --;
			}
		}
		showStatus ( beforeMove );
	}
	calcRank ( );
}

//---------------------------------------------------------
//	showStatus	画面下部にcurrentPlayerの名前、進行方向、問い合わせ回数などを表示する。
//---------------------------------------------------------
static	void	showStatus	( Pos	current )
{
	#define	StatusTop	(20)
	char*	dirString[] = { "^", ">", "v", "<" };
	char	stat [ 200 ];
	int	col = GetColor( 255 , 255 , 255 );
	if ( players [ currentPlayer ].hasGoal ){
		col = GetColor ( 0, 255, 0 );
	}
	sprintf ( stat, "[%c : %-12.12s]", 'A' + currentPlayer, players [ currentPlayer ].funcs->name );
	DrawString( 0, StatusY(currentPlayer) , stat , col );

	sprintf ( stat, "歩数 : %6d", players [ currentPlayer ].queryCount );
	DrawString( convertX(11), StatusY(currentPlayer) , stat , col);

	sprintf ( stat, "現在位置 : %2d %2d", current.x, current.y );
	DrawString( convertX(19), StatusY(currentPlayer) , stat , col );

	sprintf ( stat, "進行方向 : %s", dirString [ players [ currentPlayer ].dir ] );
	DrawString( convertX(29), StatusY(currentPlayer) , stat , col );

	sprintf ( stat, "次候補 %2d %2d", players [ currentPlayer ].currentPosition.x, players [ currentPlayer ].currentPosition.y );
	DrawString( convertX(36), StatusY(currentPlayer) , stat , col );

	sprintf ( stat, "順位 %2d", players [ currentPlayer ].rank );
	DrawString( convertX(44), StatusY(currentPlayer) , stat , col );
}

//---------------------------------------------------------
//	calcRank	歩数順位を求める
//---------------------------------------------------------
static	void	calcRank	( void )
{
	for ( int	i = 0; i < playerCount; i++ ){
		players [ i ].rank = 1;
	}
	for ( int	i = 0; i < playerCount; i++ ){
		for ( int j = 0; j < playerCount; j++ ){
			if ( players [ i ].queryCount >players [ j ].queryCount ){
				players [ i ].rank ++;
			}
		}
	}
}

//=================================
//	汎用メソッド(非公開)
//=================================
//---------------------------------------------------------
//	strip		文字列末の改行コードを削除する。
//				返り値 : 改行コードを削除した文字列。
//				s	改行コードを取る文字列。
//---------------------------------------------------------
static	char*	strip		( char*	s )
{
	char*	p = strchr ( s, 0x0d );
	if ( p != NULL ){
		*p = '\0';
	}
	p = strchr ( s, 0x0a );
	if ( p != NULL ){
		*p = '\0';
	}
	return	s;
}

//---------------------------------------------------------
//	openFileDialog		File Dialog表示
//				返り値 : ファイル名が取得できた(true)かどうか
//				filename	取得したファイル名
//				path	ダイアログオープン時のフォルダ
//				filter	表示するファイルの種類
//				extention	拡張子
//				parentWindow	親ウインドウのハンドル
//---------------------------------------------------------
static	int	openFileDialog	( LPSTR	filename,
							LPSTR	path,
							LPCTSTR	filter,
							LPCTSTR	extention,
							HWND	parentWindow )
{
	static TCHAR _name[ MAX_PATH ] = TEXT("");
	static TCHAR _path[ MAX_PATH ]     = TEXT("");

	if( path[0] == '\0' ) {
		TCHAR pwd [ MAX_PATH ];
		GetCurrentDirectory( MAX_PATH, pwd );
		strcpy( _path, pwd );
	}

    // Setup the OPENFILENAME structur
	OPENFILENAME info;
	memset(&info, 0, sizeof ( OPENFILENAME ) );

	info.lStructSize = sizeof ( OPENFILENAME );
	info.hwndOwner = parentWindow;
	info.hInstance = NULL;
	info.lpstrCustomFilter = NULL;
	info.nMaxCustFilter = 0;
	info.nFilterIndex = 1;
	info.nMaxFile = MAX_PATH;

	info.lpstrFileTitle = NULL;
	info.nMaxFileTitle = 0;

	info.nFileOffset = 0;
	info.nFileExtension = 0;
	info.lCustData = 0;
	info.lpfnHook = NULL;
	info.lpTemplateName = NULL;

	info.lpstrFilter = filter;
	info.lpstrDefExt = extention;
	info.lpstrInitialDir = TEXT( _path );
	info.lpstrFile = TEXT( _name );
	info.lpstrTitle = TEXT("Open Map File"); 
	info.Flags = OFN_FILEMUSTEXIST|OFN_HIDEREADONLY; 
	if( GetOpenFileName( &info ) == 0 ){
		return FALSE;
	}
	strcpy( _path, _name );
	char* strLastSlash = strrchr( _path, '\\' );
	strLastSlash[0] = '\0';

	strncpy( filename, _name, MAX_PATH );
	strncpy( path, _path, MAX_PATH );
	return TRUE;
}

//---------------------------------------------------------
//	showMessage	システムメッセージ表示
//				msg	表示するメッセージ
//---------------------------------------------------------
static	void	showMessage		( char*	msg )
{
	HWND	mainWindow = GetMainWindowHandle();
	MessageBox ( mainWindow, msg, "Message", MB_OK|MB_ICONINFORMATION );
}

//=================================
//	公開関数
//=================================
//---------------------------------------------------------
//	getMazeWidth ...	迷路の幅(int)を返す。
//	getMazeHeight ...	迷路の高さ(int)を返す。
//---------------------------------------------------------
extern	"C"	int	getMazeWidth	( void )	{ return map.width; }
extern	"C"	int	getMazeHeight	( void )	{ return map.height; }

//---------------------------------------------------------
//	getCurrentPosition ...	現在位置(Pos構造体)を返す。
//				Pos.x ...	現在位置のx座標
//				Pos.y ...	現在位置のy座標
//---------------------------------------------------------
extern	"C"	Pos	getCurrentPosition	( void )	{ return players [ currentPlayer ].currentPosition; }

//---------------------------------------------------------
//	canMove ...	指定された方向に何があるか(MapStatus列挙型)を返す。
//				MapStatus :	MapWall	壁
//							MapStart	スタート地点
//							MapAisle	通路
//							MapGoal	ゴール地点
//							MapInvalid	範囲外
//				引数	:	DirUp	上
//							DirDown	下
//							DirLeft	左
//							DirRight	右
//---------------------------------------------------------
extern	"C"	MapStatus	canMove		(  int	dir )
{
	MapStatus	result;
	Pos	newPosition  = move ( dir );

	players [ currentPlayer ] . queryCount++;
	if ( newPosition.x < 0
		|| newPosition.y < 0
		|| newPosition.x >= map.width
		|| newPosition.x >= ( int )strlen ( map.map [ newPosition.y ] )
		|| newPosition.y >= map.height ) {
		result = MapWall;
	} else {
		switch ( map.map [ newPosition.y ] [ newPosition.x ] ){
			case MazeStart : result = MapStart; break;
			case MazeGoal : result = MapGoal; break;
			case MazeAisle : result = MapAisle; break;
			default: result = MapWall;
		}
	}
	return result;
}

#define	__MAZE_C__
#include ".\maze.h"
#include "..\dxLib\DxLib.h"

//=================================
//	�萔
//=================================
#define	MaxFilePath	(128)			// �t�@�C�����̍ő咷+1
#define	MapDir	".\\map\\"			// �}�b�v���i�[����t�H���_��
#define	FileExtention	".map"			// �}�b�v�t�@�C���̊g���q
#define	ArraySizeIncrement	(5)		// �����g���z��̊g���T�C�Y
#define	PosUndefined	(-1)			// �ʒu��񂪖��m��ȂƂ��̒l
#define	PlayerMax	(8)				// �v���C���[���̍ő�
#define	StatusTop	(20)			// ���̈�̈�ԏ�̍s�ԍ�
#define	NoError		(0)				// ����������
#define	DxLibError		(-1)		// DXLib�̃G���[
#define	MapLoadError		(-2)	//  �}�b�v�̃G���[
#define	Wait			(100)		// �v���C���[�𓮂����Ԋu

// �u���b�N
#define		BlockHeight	(16)
#define		BlockWidth	(16)
#define		BlockType	(4)
static	int	grpBlocks [ BlockType ];		// �u���b�N�̉摜( ( 16 * 16 ) * 4 )

// ���W�ϊ�
#define	convertX(x)		((x)*BlockWidth)		// �L�����N�^���W����O���t�B�b�N���W�ւ̕ϊ�
#define	convertY(y)		((y)*BlockHeight)
#define	StatusY(y)		convertY(map.height+y+1)	// �󋵕\��

//=================================
//	�\���̒�`
//=================================
//---------------------------------------------------------
//	Map	�n�}����ێ�����
//---------------------------------------------------------
typedef	struct {
	int	width;		// �n�}�̕�
	int	height;		// �n�}�̍���
	char**	map;	// �n�}�̊e�s�̐擪�A�h���X
	Pos	start;		// �X�^�[�g�n�_�̍��W
	Pos	goal;		// �S�[���̍��W
} Map;

//---------------------------------------------------------
//	Player	�v���[������ێ�����
//---------------------------------------------------------
typedef	struct {
	Funcs*	funcs;			// ���O��֐�
	Pos		currentPosition;	// ���ݒn�̍��W
	int		dir;				// ���ݓ����Ă������
	int		queryCount;		// �₢���킹��
	bool	hasGoal;			// �S�[��������
	int		rank;			// ��������
} Player;

//=================================
//	�v���g�^�C�v�錾
//=================================
static	int		init			( void );		// �V�X�e���̏�����
//---------------------------------------------------------
//	�}�b�v�֘A�̃��\�b�h(����J)
//---------------------------------------------------------
static	Map	initMap		( void );		// �}�b�v�̏�����
static	void	inputName	( char*, int );	// �t�@�C�����擾
static	char*	loadMap		( char* );	// �}�b�v�t�@�C���擾
static	void	showMap	( Map );		// �}�b�v�\��
static	Map	createMapInfo( char* );		// �}�b�v��񐶐�
static	int		getFileSize	( FILE* );	// �t�@�C���T�C�Y�擾
static	char**	expandArray	( char** );	// �z��̊g��
//---------------------------------------------------------
//	�v���[���֘A�̃��\�b�h(����J)
//---------------------------------------------------------
static	int		initPlayers	( void );		// �v���[����񏉊���
static	void	registerPlayer	( int,  Funcs* );// �v���[���̒ǉ�
static	void	showStatus	( Pos );		// ���ݏ󋵂̕\��
static	Pos		move		( int );		// �v���[���̈ړ�
static	void	questMaze	( void );		// ���H�T�����[�`���̌Ăяo��
static	void	calcRank		( void );		// �������ʂ����߂�

//---------------------------------------------------------
//	�ėp���\�b�h(����J)
//---------------------------------------------------------
static	int		openFileDialog	( LPSTR, LPSTR, LPCTSTR, LPCTSTR, HWND );
static	char*	strip			( char* );	// �������̐���R�[�h�폜
static	void	showMessage		( char* );

//---------------------------------------------------------
//	���H�T��
//---------------------------------------------------------
extern "C"	Funcs*	getGroup01Info	( void );
extern "C"	Funcs*	getGroup02Info	( void );
extern "C"	Funcs*	getGroup03Info	( void );
extern "C"	Funcs*	getGroup04Info	( void );
extern "C"	Funcs*	getGroup05Info	( void );
extern "C"	Funcs*	getGroup06Info	( void );



//=================================
//	�t�@�C�����O���[�o���ϐ�
//=================================
static	char	currentPath [ MAX_PATH ];
static	int		winWidth, winHeight;
static	Map	map;
static	Player	players[ PlayerMax ];
static	int		currentPlayer;			// ���ݏ������̃v���[���ԍ�
static	int		playerCount;				// �S�v���[����
static	int		running;		// �S�[�����Ă��Ȃ��v���[���̐�

//=================================
//	entry point
//=================================
int	WINAPI	WinMain	( HINSTANCE	hInstance,
					HINSTANCE	hPrevInstance,
					LPSTR		lpCmdLine,
					int			nCmdShow )
{

	GetModuleFileName ( hInstance, currentPath, MAX_PATH );
	// �}�b�v�̓ǂݍ���
	map = initMap ( );
	if ( map.map != NULL ){
		// �v���[���̓o�^
		running = playerCount = initPlayers ( );
		// �V�X�e���̏�����
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
					if ( MessageBox ( GetMainWindowHandle(), "�I�����܂���?", "�I���m�F", MB_OKCANCEL|MB_ICONQUESTION ) == IDOK ){
						isContinued = false;
					}
				}
				WaitTimer ( Wait );
			}
			showMessage ( "�I�����܂�" );
			DxLib_End ( );
		} else {
			showMessage ( "DXLib�̏������Ɏ��s���܂����B" );
		}
	} else {
		showMessage ( "�}�b�v�̓ǂݍ��݂Ɏ��s���܂����B" );
	}
	return 0 ;				// �\�t�g�̏I�� 
}

static	int	init	( void )
{
	ChangeWindowMode( true );
	SetWindowSizeChangeEnableFlag ( true );
	//
	int	ret = DxLib_Init( );
	if ( ret != DxLibError ){
		if ( map.map != NULL ){
			// �E�C���h�E�T�C�Y/�F���̒���
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
			// �Ǘp�O���t�B�b�N�̓ǂݍ���
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
//	�}�b�v�֘A�̃��\�b�h(����J)
//=================================
//---------------------------------------------------------
//	initMap	������
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
//	inputName	�t�@�C��������
//				buf	���͂��ꂽ�t�@�C������ێ�����̈�̃A�h���X
//				bufSize	���͗̈�̃T�C�Y
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
//	loadMap	�}�b�v�t�@�C���̓ǂݍ���
//			�Ԃ�l : �}�b�v�̈�̐擪�A�h���X
//			name	�t�@�C����
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
//	createMapInfo	�}�b�v����T�C�Y��e�s�̐擪�A�h���X���擾����B
//			�Ԃ�l : �}�b�v���
//			name	�}�b�v�t�@�C����ǂݍ��񂾗̈�ւ̃|�C���^
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
//	getFileSize	�t�@�C���T�C�Y�̎擾
//				�Ԃ�l : �t�@�C���T�C�Y
//				name	�T�C�Y�𒲂ׂ�t�@�C���ւ̃t�@�C���|�C���^
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
//	expandArray	�}�b�v�̊e�s�̐擪�A�h���X��ێ�����z��v�f�����g������B
//				�Ԃ�l : �V�����z��
//				array	���݂̔z��
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
//	showMap	�}�b�v�̕\��
//			info	�}�b�v���
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
//	�v���[���֘A�̃��\�b�h(����J)
//=================================
//---------------------------------------------------------
//	initPlayers	������
//---------------------------------------------------------
static	int	initPlayers	( void )
{
	int		i = 0;
	/*registerPlayer ( i++, getGroup01Info ( ) );
	registerPlayer ( i++, getGroup02Info ( ) );
	registerPlayer ( i++, getGroup03Info ( ) );
	registerPlayer ( i++, getGroup04Info ( ) );*/
	registerPlayer ( i++, getGroup05Info ( ) );
	//registerPlayer ( i++, getGroup06Info ( ) );

	return	i;
}

//---------------------------------------------------------
//	registerPlayer	�v���[���z��ɁA�V�����v�f��ǉ�����B
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
//	move	�v���[�����ړ�����B
//			�Ԃ�l : �ړ���̍��W
//			dir	�ړ�����������
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
//	questMaze	���H�T�����[�`���̌Ăяo��
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
			// �ړ����悤�Ƃ��Ă���������ǂłȂ���΁A�ړ�������
			MapStatus	stat = canMove ( dir );
			if ( stat != MapWall ){
				player->currentPosition = move ( dir );
				player->dir = dir;
			}
			if ( stat != MapGoal ){
				char	mark [ 2 ] = { currentPlayer + 'A', '\0' };
				// ���݈ʒu�Ƀ}�[�N��\��
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
//	showStatus	��ʉ�����currentPlayer�̖��O�A�i�s�����A�₢���킹�񐔂Ȃǂ�\������B
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

	sprintf ( stat, "���� : %6d", players [ currentPlayer ].queryCount );
	DrawString( convertX(11), StatusY(currentPlayer) , stat , col);

	sprintf ( stat, "���݈ʒu : %2d %2d", current.x, current.y );
	DrawString( convertX(19), StatusY(currentPlayer) , stat , col );

	sprintf ( stat, "�i�s���� : %s", dirString [ players [ currentPlayer ].dir ] );
	DrawString( convertX(29), StatusY(currentPlayer) , stat , col );

	sprintf ( stat, "����� %2d %2d", players [ currentPlayer ].currentPosition.x, players [ currentPlayer ].currentPosition.y );
	DrawString( convertX(36), StatusY(currentPlayer) , stat , col );

	sprintf ( stat, "���� %2d", players [ currentPlayer ].rank );
	DrawString( convertX(44), StatusY(currentPlayer) , stat , col );
}

//---------------------------------------------------------
//	calcRank	�������ʂ����߂�
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
//	�ėp���\�b�h(����J)
//=================================
//---------------------------------------------------------
//	strip		�����񖖂̉��s�R�[�h���폜����B
//				�Ԃ�l : ���s�R�[�h���폜����������B
//				s	���s�R�[�h����镶����B
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
//	openFileDialog		File Dialog�\��
//				�Ԃ�l : �t�@�C�������擾�ł���(true)���ǂ���
//				filename	�擾�����t�@�C����
//				path	�_�C�A���O�I�[�v�����̃t�H���_
//				filter	�\������t�@�C���̎��
//				extention	�g���q
//				parentWindow	�e�E�C���h�E�̃n���h��
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
//	showMessage	�V�X�e�����b�Z�[�W�\��
//				msg	�\�����郁�b�Z�[�W
//---------------------------------------------------------
static	void	showMessage		( char*	msg )
{
	HWND	mainWindow = GetMainWindowHandle();
	MessageBox ( mainWindow, msg, "Message", MB_OK|MB_ICONINFORMATION );
}

//=================================
//	���J�֐�
//=================================
//---------------------------------------------------------
//	getMazeWidth ...	���H�̕�(int)��Ԃ��B
//	getMazeHeight ...	���H�̍���(int)��Ԃ��B
//---------------------------------------------------------
extern	"C"	int	getMazeWidth	( void )	{ return map.width; }
extern	"C"	int	getMazeHeight	( void )	{ return map.height; }

//---------------------------------------------------------
//	getCurrentPosition ...	���݈ʒu(Pos�\����)��Ԃ��B
//				Pos.x ...	���݈ʒu��x���W
//				Pos.y ...	���݈ʒu��y���W
//---------------------------------------------------------
extern	"C"	Pos	getCurrentPosition	( void )	{ return players [ currentPlayer ].currentPosition; }

//---------------------------------------------------------
//	canMove ...	�w�肳�ꂽ�����ɉ������邩(MapStatus�񋓌^)��Ԃ��B
//				MapStatus :	MapWall	��
//							MapStart	�X�^�[�g�n�_
//							MapAisle	�ʘH
//							MapGoal	�S�[���n�_
//							MapInvalid	�͈͊O
//				����	:	DirUp	��
//							DirDown	��
//							DirLeft	��
//							DirRight	�E
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

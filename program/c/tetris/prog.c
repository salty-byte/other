/*
 * prog.c
 *
 * Created on: 2012/12/19
 * Author: salty-byte
 */

#include "prog.h"

/*
 * メイン関数
 */
int main() {

      /* キーボードの入力を隠すための処理 */
	system("stty echo -icanon min 1 time 0");

	/* 時間をカウント */
	int time = 0;

	/* スタート画面を表示 */
	GameStart();

	/* ゲーム起動後の初期設定 */
	Initialize();

	/* ゲーム実行の処理 */
	while (!gameover) {
		/* キー入力があればそれに応じて操作 */
		if (kbhit()) {
			ControlBlock();
		}

		/* レベルに応じてブロックを落とす時間を調節 */
		if (time < GetTimeOfLevel(level)) {
			time += toffset + 1; /* 時間経過 */
			toffset = 0;
		} else {
			DropBlock(); /* ブロックを一列分落とす */
			time = 0;
		}
	}
	/* キーボードの入力設定を元に戻す */
	system("stty echo icanon min 1 time 0");

	return 0;
}

/*
 *  field[][]の中身に応じて、ゲーム起動後の初期設定を行う関数
 *  Initialize()
 */
void Initialize() {
	int i, j; /* forループ制御用変数 */
	/* 画面と壁のデータを初期化 */
	for (i = 0; i <= 20; i++) {
		for (j = 0; j < width; j++) {
		  if ((j == 0) || (j == width-1) || (i == 20)) {
				field[i][j] = stage[i][j] = 9;
			} else {
				field[i][j] = stage[i][j] = 0;
			}
		}
	}
	/* 0~6の乱数によって新しいブロックの種類を決定 */
	srand((unsigned) time(NULL ));
	nextblock = rand() % (5+mode);

	/* 落ちてくるブロックを作成 */
	CreateBlock();

	/* ゲーム画面を表示 */
	ShowGameField();

}

/*
 *  落ちてくるブロックを作る関数
 *  CreateBlock()
 *  戻り値: int: 初期位置にブロックがおけないとき = 1, 正しくセットできたとき = 0;
 */
int CreateBlock() {
	int i, j; /* forループ制御用の変数 */

	/* ブロックの座標を初期位置にリセット */
	y = 0;
	x = 4;
	/* 落ちてくるブロックの種類を新しいブロックの種類にする */
	block_type = nextblock;

	//srand((unsigned)time(NULL));
	nextblock = rand() % (6+mode*2); /* ノーマルは8個,ハードは10個,ベリーハードは12個から乱数 */
	if(nextblock != 0 && tateritu == 1) nextblock = rand() % (6+mode*2); /* 縦棒の率をup */
	else if(mode >= 2) nextblock = rand() % (6+mode*2);  /* 縦棒の率をdown */

	/* block_typeによって種類をきめ、新しいブロックを作る */
	if(nextblock >= 11){ /* ランダムでブロックを作る */
	  for (i = 0; i < 4; i++) {
	    for (j = 0; j < 4; j++) {
	      block_list[nextblock][i][j] = rand() % 2;
	    }
	  }
	}
	for (i = 0; i < 4; i++) {
	    for (j = 0; j < 4; j++) {
	      block[i][j] = 0;
	      block[i][j] = block_list[block_type][i][j];
	    }
	  }
	/* 新しく作ったブロックを初期位置におく */
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			field[i][j + 4] = stage[i][j + 4] + block[i][j];
			/* 初期位置に既にブロックがあるかないかの判定。既にある場合、gameoverを1にする */
			if (field[i][j + 4] > 1) {
				gameover = 1;
				return 1;
			}
		}
	}
	return 0;
}

/*
 *  ゲーム画面を表示する関数
 *  ShowGameField()
 */
void ShowGameField() {
	int i, j; /* forループ制御用変数 */
	/* 画面を一旦クリア */
	system("clear");

	/* 画面の配列の要素によって表示をかえる */
	for (i = 0; i < 21; i++) {
		for (j = 0; j < width; j++) {
			switch (field[i][j]) {
			case 0:
			  printf("　");
			  break;
			case 9:
			  printf("囗");
			  break;

			case -1: /* 落下地点を○で表示 */
			  printf("○");
			  break;

			default:
			  printf("圖");
			  break;
			}
		}
		/* 右サイド表示部分 */
		/* 2-7行目: 次ブロック */
		if (i == 1)
			printf("　　囗ＮＥＸＴ囗");
		else if (i >= 2 && i <= 5) {
		  if(nexth == 1){ /* nexth=1のときnextが表示されない */
		    if(i == 2)
		      printf("　　囗Ｓ　　　囗");
		    else if(i == 3)
		      printf("　　囗　Ａ　　囗");
		    else if(i == 4)
		      printf("　　囗　　Ｌ　囗");
		    else
		      printf("　　囗　　　Ｔ囗");
		  }
		  else{
		    printf("　　囗");
		    for (j = 0; j < 4; j++) {
		      switch (block_list[nextblock][i - 2][j]) {
		      case 0:
			printf("　");
			break;
		      default:
			printf("圖");
			break;
		      }
		    }
		    printf("囗");
		  }
		}

		else if (i == 6)
		  printf("　　囗囗囗囗囗囗");

		/* 9行目～14行目 操作説明 */
		else if (i == 8)
			printf("　　←　左移動");
		else if (i == 9)
			printf("　　→　右移動");
		else if (i == 10)
			printf("　　↓　下移動");
		else if (i == 11)
			printf("　　Ｚキー　左回転");
		else if (i == 12)
			printf("　　Ｘキー　右回転");
		else if (i == 13)
			printf("　　Ｑキー　終了");

		/* 16行目～18行目 レベルとスコア表示 */
		else if (i == 15)
			printf("　　囗囗囗ＳＣＯＲＥ囗囗囗");
		else if (i == 16)
			printf("　　囗 LV:%2d/%10d 囗", level, point);
		else if (i == 17)
			printf("　　囗囗囗囗囗囗囗囗囗囗囗");
		else if (i == 19)
		  printf("　　MODE:%2d", mode); /* モードの表示 */

		/* 各行の改行 */
		printf("\n");
	}
	/* 1~4行消しをそれぞれ何回したかを表示 */
	printf("\n１行消し：%d回 ２行消し：%d回 ３行消し：%d回 ４行消し：%d回\n", oneline, twoline,threeline, fourline);
	/* ゲームオーバーになったら画面を消去し、それまでの得点などを表示 */
	if (gameover) {
		system("clear");
		printf("\nYour Lines:\n１行消し：%d回 ２行消し：%d回 ３行消し：%d回 ４行消し：%d回\nYour Level: %d\nYour Scoure: %12d\n\nGAME OVER\n\n", oneline, twoline, threeline, fourline, level, point);
	}
}

/*
 * 落ちてくるブロックをキーによって移動したり、回転させたりする関数
 * ControlBlock()
 */
void ControlBlock() {
	char key; /* キーボードからのキーを保持 */
	/* キーの取得 */
	key = getchar();
	/* キーに応じて各方向へブロックを移動したり、回転させたりする */
	/* qキー: ゲーム終了（強制GameOver） */
	/* zキー: ブロック左回転                          */
	/* xキー: ブロック右回転                          */
	/* ←キー: 左移動 (ESC]C)        */
	/* →キー: 右移動 (ESC]D)        */
	/* ↓キー: 下移動 (ESC]B)        */
	switch (key) {
	case 'q':
		gameover = 1;
		ShowGameField();
		break;
	case 'z':
	  if(nochan == 1) break; /* 回転が禁止 */
	  TurnLeftBlock();
	  break;
	case 'x':
	  if(nochan == 1) break; /* 回転が禁止 */
	  TurnRightBlock();
	  break;
	case 27:
		key = getchar();
		if (key == 91) {
			key = getchar();
			switch (key) {
			case 'B': /* Down */
				if (!CheckOverlap(x, y + 1)) {
					MoveBlock(x, y + 1);
				} else {
					toffset = 300 * FPS; /* 一番下まで行たときに下ボタン押したら次のブロック */
				}
				break;
			case 'C': /* Left */
				if (!CheckOverlap(x + 1, y)) {
					MoveBlock(x + 1, y);
				}
				break;
			case 'D': /* Right */
				if (!CheckOverlap(x - 1, y)) {
					MoveBlock(x - 1, y);
				}
				break;
			default:
				break;
			}
		}
		break;
	default:
		break;
	}
}

/* [関数コメント例]
 * 被りのチェックを行う関数
 * CheckOverlap()
 * 戻り値: int: もし壁等に被る場合 = 1, それ以外 = 0.
 * 引数: int x2: ブロックを格納している4x4の配列の左上のx座標
 *      int y2:  ブロックを格納している4x4の配列の左上のy座標
 */

int CheckOverlap(int x2, int y2) {
	int i, j; /* forループ制御用変数 */

	/* ブロックが壁等に被るかの判定 */
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			if (block[i][j]) {
				if (stage[y2 + i][x2 + j] != 0) {
					return 1;
				}
			}
		}
	}
	return 0;
}

/*
 * ブロックの移動を行う関数
 * MoveBlock()
 * 引数: int x2: ブロックを格納している4x4の配列の左上のx座標
 *      int y2:  ブロックを格納している4x4の配列の左上のy座標
 */

void MoveBlock(int x2, int y2) {
	int i, j; /* forループ制御用変数 */
	/* 落ちてくるブロックのデータ分の画面データを削除する */
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			field[y + i][x + j] -= block[i][j];
		}
	}

	/* 移動する分のx,y座標をx,yに代入 */
	x = x2;
	y = y2;

	/* 移動したブロックのデータ分を画面データに入れる */
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			field[y + i][x + j] += block[i][j];
		}
	}
	/* ゲーム画面の表示 */
	ShowGameField();
}

/*
 * ブロックの右回転を行う関数
 * TurnRightBlock()
 * 戻り値: int: 回転できたとき = 0, できなかったとき = 1
 * ブロック右回転の重なりチェックはこの中で行っている .
 * 壁蹴り1マス分実装（但し、テトリス棒は除く.
 */
int TurnRightBlock() {
	int i, j; /* forループ制御用 */
	int tmp[4][4]; /* 回転前のブロックデータ保存用 */
	int offset = 0;
	/* 回転前のブロックデータの保存 */
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			tmp[i][j] = block[i][j];
		}
	}

	/* 右回転後のデータを代入 */
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			block[i][j] = tmp[3 - j][i];
		}
	}

	/* ブロックが壁等に被った場合、壁蹴り処理 */
	if (CheckOverlap(x, y)) {
		/* 壁蹴り左壁 */
		if (!CheckOverlap(x + 1, y) && block_type != 0)
			offset = 1;
		/* 壁蹴り右壁 */
		else if (!CheckOverlap(x - 1, y) && block_type != 0)
			offset = -1;
		/* ダメだと戻す */
		else {
			for (i = 0; i < 4; i++) {
				for (j = 0; j < 4; j++) {
					block[i][j] = tmp[i][j];
				}
			}
			return 1;
		}
	}

	/* 回転前のブロックデータを画面のデータから削除 */
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			field[y + i][x + j] -= tmp[i][j];
		}
	}
	/* 壁蹴り分の移動 */
	x = x + offset;

	/* 回転処理後のブロックデータを画面のデータに入れる */
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			field[y + i][x + j] += block[i][j];
		}
	}
	/* ゲーム画面の表示 */
	ShowGameField();
	return 0;
}

/*
 * ブロックの左回転を行う関数
 * TurnLeftBlock()
 * 戻り値: int: 回転できたとき = 0, できなかったとき = 1
 * ブロック左回転の重なりチェックはこの中で行っている.
 * 壁蹴り1マス分実装（但し、テトリス棒は除く.
 */

int TurnLeftBlock() {
	int i, j; /* forループ制御用 */
	int tmp[4][4]; /* 回転前のブロックデータの保存用 */
	int offset = 0;
	/* 回転前のブロックデータの保存 */
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			tmp[i][j] = block[i][j];
		}
	}

	/* 左回転後のデータを代入 */
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			block[i][j] = tmp[j][3 - i];
		}
	}
	/* ブロックが壁等に被った場合、壁蹴り処理 */
	if (CheckOverlap(x, y)) {
		/* 壁蹴り左壁 */
		if (!CheckOverlap(x + 1, y) && block_type != 0)
			offset = 1;
		/* 壁蹴り右壁 */
		else if (!CheckOverlap(x - 1, y) && block_type != 0)
			offset = -1;
		/* ダメだと戻す */
		else {
			for (i = 0; i < 4; i++) {
				for (j = 0; j < 4; j++) {
					block[i][j] = tmp[i][j];
				}
			}
			return 1;
		}
	}

	/* 回転前のブロックデータを画面のデータから削除 */
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			field[y + i][x + j] -= tmp[i][j];
		}
	}
	/* 壁蹴り分の移動 */
	x = x + offset;

	/* 回転処理後のブロックデータを画面のデータに入れる */
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			field[y + i][x + j] += block[i][j];
		}
	}
	/* ゲーム画面の表示 */
	ShowGameField();
	return 0;
}

/*
 * ブロックを落とす関数。下に移動できない場合ブロックをその位置に固定
 * DropBlock()
 */
void DropBlock() {
	/* 下にブロックを移動させる */
	if (!CheckOverlap(x, y + 1)) {
		MoveBlock(x, y + 1);
	}
	/* 落下するブロックを固定させて、新なブロックを作成する */
	else {
		LockBlock();
		CreateBlock();
		ShowGameField();
	}
}

/*
 * 着地したブロックを固定済みブロックに加える関数
 * LockBlock()
 */
void LockBlock() {
	int i, j; /* forループ制御用変数 */
	/* 全てのブロックを固定させる */
	for (i = 0; i < 21; i++) {
		for (j = 0; j < width; j++) {
			stage[i][j] = field[i][j];
		}
	}
	/* 列が揃ってるかのチェック */
	CheckLines();

	/* CheckLinesしたあとのデータを画面のデータとする */
	for (i = 0; i < 21; i++) {
		for (j = 0; j < width; j++) {
			field[i][j] = stage[i][j];
		}
	}
}

/*
 * 横列をチェックし、一列以上揃っているかの判定を行う関数
 * CheckLines()
 */
void CheckLines() {
	int i, j, k; /* forループ制御用 */
	int comp; /* 横一列がそろっていれば１、一つでも隙間があると０になる */
	int lines = 0; /* 同時に消したラインの数 */

	while (1) {
		for (i = 0; i < 20; i++) {
			comp = 1;
			/* 一列をチェックし、一つでも隙間があればcompを0にする */
			for (j = 1; j < width-1; j++) {
				if (stage[i][j] == 0) {
					comp = 0;
				}
			}
			/* 横一列が揃っていればforループを抜ける */
			if (comp == 1)
				break;
		}
		/* どの列もそろっていないときwhileループを抜ける */
		if (comp == 0)
			break;

		/* 一列揃ったラインの数を+1 */
		lines++;

		/* 揃ったラインのデータを0にして削除 */
		for (j = 1; j < width-1; j++) {
			stage[i][j] = 0;
		}

	 	/* 消した一列分、それ以降のデータを一列ずつずらす */
		for (k = i; k > 0; k--) {
			for (j = 1; j < width-1; j++) {
				stage[k][j] = stage[k - 1][j];
			}
		}
	}

	/* 揃ったラインの数に応じてその分のライン数を+1 */
	switch (lines) {
	case 1:
		oneline++;
		break;
	case 2:
		twoline++;
		break;
	case 3:
		threeline++;
		break;
	case 4:
		fourline++;
		break;
	default:
		break;
	}

	/* 消したそれぞれのライン数に応じて獲得ポイントを決定 */
	point = oneline * 100 + twoline * 400 + threeline * 900 + fourline * 1600;
	/* 獲得ポイントが2000上るごとに、レベルが1上っていく */
	level = (int) (point / 2000.0) + level_2;
	/* レベルが15より大きくなるときは15にする */
	if (level > 15)
	  level = 15;
}

/*
 * キーボードが押されたかどうかの判定を返す関数
 * kbhit()
 * 返り値: キーボードが押された場合 = 1, 他 = 0
 * この関数は難しいので、『そういうものだ』としてください
 */
int kbhit(void) {

	struct termios oldt, newt; /* termosで保持する構造体 */
	int ch;                    /* 確認する文字 */
	int oldf;                  /* ファイル状態 */

	oldf = fcntl(STDIN_FILENO, F_GETFL, 0);   /* ファイル操作状態の取得 */
	fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK); /* 文字取得状態待ちの解除 */
	ch = getc(stdin); /* 文字取得 */
	fcntl(STDIN_FILENO, F_SETFL, oldf);      /* ファイル操作の状態を元に戻す（Unlock） */

	/* 文字が取得されたかどうかを検査 */
	if (ch != EOF) {
		ungetc(ch, stdin); /* 文字がとれていたら判定のために文字をバッファに戻す */
		return 1;
	}
	return 0;
}

/*
 * ブロックが一列落ちるのにかかる時間の設定を行う関数
 * GetTimeOfLevel
 * 戻り値: int: レベルに応じた落下するのにかかる時間
 * 引数: int level: 現在のレベル
 */
int GetTimeOfLevel(int level) {
  if (level >= 1 && level <= 15){
    if(mode >= 2) return (FPS-200) * lvspeed[level - 1]; /* ノーマルモード以外の速度up */
      return FPS * lvspeed[level - 1];
  }else
    return 5 * FPS;
}

/*
 * ゲームのスタート画面を表示する関数
 * GameStart()
 */
void GameStart() {
	FILE* fp; /* sprite.txtからデータを読み込むためのファイルポインタ */
	char string[60]; /* sprite.txtのデータの保存用 */
	char sprite[1000]; /* sprite.txtのデータの保存用 */
	char ch; /* ゲームを開始するか終了するかの判定 */
	int ret;
	int flag = 1; /* ゲームセンターっぽく点滅させるためのフラグ管理 */
	int time = 9999; /* タイマー */

	int a; /* 編集モード用の変数 */

	/* sprite.txtをオープンする */
	fp = fopen("sprite.txt", "r");

	/* sprite.txtからデータを受け取る */
	fscanf(fp, "%s", sprite);
	while ((ret = fscanf(fp, "%s", string)) != EOF) {
		strcat(sprite, "\n");
		strcat(sprite, string); /* spriteにstringの値を結合させて保存 */
	}

	/* sprite.txtをクローズする */
	fclose(fp);

	/* スプライト表示 */
	while (1) {
		/* タイマーがカンストするたびに更新  */
		if (time > 80 * FPS) {
			/* 一度消去 */
			system("clear");
			/* spriteのデータを表示 */
			printf("%s\n\n", sprite);
			/* プログラミングコースのクレジット */
			printf("\n    2012 Programming C Course\n\n");
			if (flag == 1) {
			  /* 点滅させる所 */
			  printf("     PUSH SPACE KEY TO START\n");
                          printf("                or\n");
			  printf("       PUSH e KEY TO EDIT\n");  /* 編集用 */
 			}
			/* 点滅フラグ */
			flag *= -1;
			/* タイマーを戻す */
			time = 0;
		}

		/* キーレスポンスの設定 */
		if (kbhit()) {
			ch = getchar();
			if (ch == 'q') { /* qが入力されたらゲームの強制終了 */
				gameover = 1;
				break;
			} else if (ch == ' ') { /* スペースが入力されたらゲーム開始のためループをbreak */
				break;
			} else if (ch == 'e'){ /* 編集モード */
			        Edit();
			}

		}
		/* タイマーをカウントさせる。タイマーがカンストするとflagの値が交互に入れ替わる */
		time++;
	}
	/* mainにかえる */
	return;
}


void Edit(void){ /* ゲームの設定を変更する関数 */
  int a, b; /* 確認する文字 */
  int flag=0; /* case3の分岐用 */

  system("clear");

  printf("\n~~~EDIT MOED~~~\n\n");
  while(1){
    printf("level : 1\n");
    printf("モード : 2\n");
    printf("横幅 : 3\n");
    printf("補助コマンド : 4\n");
    printf("編集終了 : 0\n");
    printf("どれを変更しますか -> ");

    if(scanf("%d", &a) == 1){

      switch(a){
      case 1:
	printf("\nlevel(1~15) -> ");
	if(scanf("%d", &b) == 1){
	  if(b >= 1 && b <= 15){
	    level_2 = b;
	    printf("levelを %d に設定しました\n\n", level);
	  } else printf("levelは変更されませんでした\n\n");
	} else printf("levelは変更されませんでした\n\n");
	break;

      case 2:
	printf("\n現在のmode : %d\n", mode);
	printf("NORMAL(標準のモードです) : 1\n");
	printf("HARD(縦棒の出現率が低くなり、落下速度が上がります) : 2\n");
	printf("VERY HARD(かなりきついです) : 3\n");
	printf("mode -> ");
	if(scanf("%d", &b) == 1){
	  switch(b){
	  case 1:
	    mode = b;
	    printf("ノーマルモードに設定しました\n\n");
	    break;
	  case 2:
	    mode = b;
	    printf("ハードモードに設定しました\n\n");
	    break;
	  case 3:
	    mode = b;
	    printf("ベリーハードモードに設定しました\n\n");
	    break;
	  default:
	    printf("モードは変更されませんでした\n\n");
	  }
	}else printf("モードは変更されませんでした\n\n");
	break;

      case 3:
	printf("\n現在の横幅(壁も含む) : %d\n", width);
	printf("width(12~26) -> ");
	if(scanf("%d", &b) == 1){
	   if(b >= 12 && b <= 26){
	     width = b;
	     printf("横幅を %d に設定しました\n\n", width);
	   } else printf("横幅は変更されませんでした\n\n");
	} else printf("横幅は変更されませんでした\n\n");
	break;

      case 4:
	E_3(); /* 補助コマンドの設定 */
	break;

      default: printf("EDITを終了します\n");
	return;
      }
    } else {
      printf("EDITを終了します\n");
      return;
    }
  }
}

void E_3(void){ /* 補助コマンド設定関数 */
  int b; /* 判定用変数 */

  while(1){
    printf("縦棒の確率がupします : 1\n");
    printf("回転ができなくなります : 2\n");
    printf("NEXTが見れなくなります : 3\n");
    printf("設定をもとに戻します : 4\n");
    printf("補助コマンドの設定終了 : 5\n");
    printf("何にしますか -> ");
    if(scanf("%d", &b) == 1){
      switch(b){
      case 1:
	tateritu = 1;
	printf("\n縦棒の確率がupしました\n");
	break;
      case 2:
	nochan = 1;
	printf("\n回転ができなくなりました\n");
	break;
      case 3:
	nexth = 1;
	printf("\nNEXTが見れなくなりました\n");
	break;
      case 4:
	nochan = 0;
	tateritu = 0;
	nexth = 0;
	printf("\n設定をもとに戻しました\n");
	break;
      default :
	printf("\n補助コマンドの設定を終了します\n\n");
	return;
      }
    }else {
      printf("\n補助コマンドの設定を終了します\n\n");
      break;
    }
  }
}


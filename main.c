#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<time.h>

typedef struct Data{
    char question[100];
    char choice[4][50];
    char modelans[50];
    char tag[10][50];
    int wrongchoice;
    char quespath[50];
}data;

char *RemoveN(char *readline) {
    char *result;
    result = strtok(readline, "\n");
    return result;
}

char SpritSpaceMode(char *ptr, int mode, int cnt, data *x){
    switch (mode) {
        case 0:
            strcpy(x->tag[cnt], ptr);
            //puts(x->tag[cnt]);
            break;
        case 1:
            strcpy(x->choice[cnt], ptr);
            //puts(x->choice[cnt]);
            break;
        default:
            puts("エラー");
    }
}

char SpritSpace(char *readline, int mode,data *x) {
    int cnt = 0;
    char *ptr;

    ptr = strtok(readline, " ");
    SpritSpaceMode(ptr, mode, cnt, x);
    cnt++;

    while (ptr!=NULL) {
        ptr = strtok(NULL, " ");
        if (ptr!=NULL) {
            SpritSpaceMode(ptr, mode, cnt, x);
            cnt++;
        }
    }
}

data ReadFile(char filepath[]) {
	data x;
	FILE *fo;
	char filename[100];
	char readline[100] = {'\0'};

	for(int i=0;i<10;i++){
		x.tag[i][0] = '\0';
	}
	for(int i=0;i<4;i++){
		x.choice[i][0] = '\0';
	}
	
	x.question[0] = '\0';
	x.modelans[0] = '\0';
	x.quespath[0] = '\0';
	x.wrongchoice = 0;
	
	
	memcpy(filename,filepath,strlen(filepath));

	if ((fo = fopen(filename, "r")) == NULL) {
		fprintf(stderr, "%sのオープンに失敗しました.\n", filename);
		exit(EXIT_FAILURE);
	}

	

	/* 1行目の処理 <tag> */
	fgets(readline, 100, fo);
	if (strstr(readline, " ")!=NULL) {
		SpritSpace(RemoveN(readline), 0, &x);
	}
	else {
		strcpy(x.tag[0], RemoveN(readline));
	//puts(x.tag[0]);
	}

	/* 2行目の処理 <wrongchoice> */
	fgets(readline, 100, fo);
	x.wrongchoice =  atoi(RemoveN(readline));
	//printf("%d\n", x.wrongchoice);

	/* 3行目の処理 <question> */
	fgets(readline, 100, fo);
	strcpy(x.question, RemoveN(readline));
	//puts(x.question);

	/* 4行目の処理 <choice> */
	fgets(readline, 100, fo);
	SpritSpace(RemoveN(readline), 1, &x);

	/* 5行目の処理 <modelans> */
	fgets(readline, 100, fo);
	strcpy(x.modelans, RemoveN(readline));
	//puts(x.modelans);

	fclose(fo);
    
	return x;
}

void Output(int frag){
	int line; //タグファイルの行数(何もない改行をしない)
	int qes;//出題数
	int num[100]; //ランダム数格納用
	char s[100][30]; //100列分、1列辺り30文字まで
	char str[10];
	if(frag==1){
		printf("タグを選択してください\n");
			scanf("%s",str);
	}else{
		strcpy(str,"All");//全問題のファイルはAll.txtでよろしく
	}
	Select(str);
	Qopen();
	//printf("正常終了\n");
}//str(適当なタグ名保管変数)にmenu部で格納済みの場合不要

void Select(char str2[10]){ //問題選択
	//タグファイル開く
	FILE *ft;
	int i;
	char str0[30]={};
	char str1[] ="tags/";
	char str3[] =".txt";
	strcat(str0,str1);
	//printf("%s\n",str0);
	strcat(str0,str2);
	//printf("%s\n",str0);
	strcat(str0,str3);
	//printf("%s\n",str0);
	ft=fopen(str0,"r");
	line=0; i=0;
	while(fgets(s[i],20,ft)!=NULL){
		line++; i++;
	}
	fclose(ft);
	Random();
}

void Random(){
	int i,j,x;
	qes=20;
	srand((unsigned) time(NULL));
	if(qes>line) qes=line; //ファイルの総問題数不足時に出題数を揃える。
	//printf("qes=%d\n",qes);	 
	for(i=0;i<=30;i++) num[i]=0;
	for(i=1;i<=qes;i++){
		do{
			x=0;
			num[i]=rand()%line+1; //ランダム関数
			//printf("%3d",num[i]);
			for(j=0;j<i;j++){
				if(num[j]==num[i]){
					x=1;
				}
			}
		}while(x==1);
		//printf("\n");
	}
}

data Qopen(){
	int i;
	data p;
	for(i=1;i<=qes;i++){
		p[i-1]=ReadFile(s[num[i]-1]);//void ReadFile(char filepath[])参照
		Question(p[i-1]);
	}
}

char SpritSpace(char *readline, int mode,data *x) {
    int cnt = 0;
    char *ptr;

    ptr = strtok(readline, " ");
    SpritSpaceMode(ptr, mode, cnt, x);
    cnt++;

    while (ptr!=NULL) {
        ptr = strtok(NULL, " ");
        if (ptr!=NULL) {
            SpritSpaceMode(ptr, mode, cnt, x);
            cnt++;
        }
    }
}

data ReadFile(char filepath[]) {
	data x;
    FILE *fo;
    char filename[100];
    char readline[100] = {'\0'};

	for(int i=0;i<10;i++){
		x.tag[i][0] = '\0';
	}
	for(int i=0;i<4;i++){
		x.choice[i][0] = '\0';
	}
	
	x.question[0] = '\0';
	x.modelans[0] = '\0';
	x.quespath[0] = '\0';
	x.wrongchoice = 0;
	
	
    memcpy(filename,filepath,strlen(filepath));

    if ((fo = fopen(filename, "r")) == NULL) {
        fprintf(stderr, "%sのオープンに失敗しました.\n", filename);
        exit(EXIT_FAILURE);
    }

	

    /* 1行目の処理 <tag> */
    fgets(readline, 100, fo);
    if (strstr(readline, " ")!=NULL) {
        SpritSpace(RemoveN(readline), 0, &x);
    }
    else {
        strcpy(x.tag[0], RemoveN(readline));
        //puts(x.tag[0]);
    }

    /* 2行目の処理 <wrongchoice> */
    fgets(readline, 100, fo);
    x.wrongchoice =  atoi(RemoveN(readline));
    //printf("%d\n", x.wrongchoice);

    /* 3行目の処理 <question> */
    fgets(readline, 100, fo);
    strcpy(x.question, RemoveN(readline));
    //puts(x.question);

    /* 4行目の処理 <choice> */
    fgets(readline, 100, fo);
    SpritSpace(RemoveN(readline), 1, &x);

    /* 5行目の処理 <modelans> */
    fgets(readline, 100, fo);
    strcpy(x.modelans, RemoveN(readline));
    //puts(x.modelans);

    fclose(fo);
    
    return x;
}

int InputAnswer(){
	int ans;
	char ansc[10];
	while(1){
		printf("解答 -->");
		scanf("%s",ansc); // char型で読み込む
		if (strlen(ansc) == 1) ans = ansc[0] - 48; // 一文字の場合int型に変換する
		if(ans == 1 || ans == 2 || ans == 3 || ans == 4){
			return ans;
		}else{
			printf("error:正しく入力を行ってください\n");
		}
	}
}

void Question(data x)
{
	/* 動作確認用
	data x;
	strcpy(x.question,"question");
	strcpy(x.choice[0],"choice1");
	strcpy(x.choice[1],"choice2");
	strcpy(x.choice[2],"choice3");
	strcpy(x.choice[3],"choice4");
	strcpy(x.modelans,"choice1");
	x.wrongchoice=5;　*/
	int a,b,c,d,i,stuck,ans,modelansnum;
	a=0;
	b=0;
	c=0;
	d=0;
	i=0;
	stuck=0;
	ans=0;
	modelansnum=0;
	/* 問題文の出力 */
	printf("問：%s\n間違えた回数 --> %d\n",x.question,x.wrongchoice);
	/* 選択肢のランダム化 */
	srand((unsigned) time(NULL));
	a=rand()%4;
	stuck=rand()%4;
	while(a == stuck){
		stuck=rand()%4;
	}
	b=stuck;
	stuck=rand()%4;
	while(a == stuck || b == stuck){
		stuck=rand()%4;
	}
	c=stuck;
	stuck=rand()%4;
	while(a == stuck || b == stuck || c == stuck){
		stuck=rand()%4;
	}
	d=stuck;
	/* 答えの選択肢の判別 */
	if(strcmp(x.choice[a],x.modelans)==0){
		modelansnum=1;
	}else if(strcmp(x.choice[b],x.modelans)==0){
		modelansnum=2;
	}else if(strcmp(x.choice[c],x.modelans)==0){
		modelansnum=3;
	}else if(strcmp(x.choice[d],x.modelans)==0){
		modelansnum=4;
	}else {
		printf("error:選択肢内に模範解答が存在しません\n");
	}
	/* ランダム化した選択肢の出力 */
	printf("1.%s\n2.%s\n3.%s\n4.%s\n",x.choice[a],x.choice[b],x.choice[c],x.choice[d]);
	/* 解答の入力受付 */
	ans=InputAnswer();
	/* 答え合わせ */
	printf("模範解答 --> %s\n",x.modelans);
	if(ans == modelansnum){
		printf("正解！\n");
	}else if(ans != modelansnum){
		printf("不正解...\n");
	}else{
		printf("program error\n");
	}
}

void CountWA(data wrongdata){
    /*
    間違えた問題カウントする部（ファイル書き出し）
    outputで間違えた際に呼び出されるものと想定
    引数は間違えた問題の構造体丸ごと
    */
    int N = 256; //最大文字数
    char buf[N]; //fgetsで一時的に保存しておく領域
    FILE *f,*fb;
    f = fopen(wrongdata.quespath,"r");//rモードで問題を開く
    fb = fopen("backup.txt","w");//wモードで別ファイルを開く　ここに問題の内容を一回書き写しながら誤答回数を変える
    int wc;//誤答回数おきば
    for(int i=0;i<6;i++){
        if(i!=1){//誤答回数の行以外は1行読み取り→1行書き出し
            fgets(buf,N,f);
            fputs(buf,fb);
        }else{//誤答回数の行になったら
            fscanf(f,"%d",&wc);//整数型で誤答回数を取得
            printf("%d\n",wc);
            wc++;//誤答回数増やす
            char wcstr[11];//誤答回数を文字列に変換するための配列
            snprintf(wcstr,11,"%d",wc);//誤答回数を文字列に変換
            fputs(wcstr,fb);//1行書き出し
        }
    }
    remove(wrongdata.quespath);
    rename("backup.txt",wrongdata.quespath);
    fclose(f);
    fclose(fb);
}

void Menu(){
    int n,flag1=1,flag2=1, FLAG=1;
    char buf[32];
    while(flag2==1){
        flag1=1;
        puts("\n学習方法を数字で選択してください。");
        puts("--------------------------------------");
        puts(" 1 | ジャンルを絞って問題を出題\n");
        puts(" 2 | ランダムに問題を出題\n");
        puts(" 0 | プログラムを終了する。");
        puts("--------------------------------------\n");
        scanf("%s",buf);
        while(flag1==1) {
            FLAG=1;
            for(int i=0; i<strlen(buf); i++){
                if(isdigit(buf[i]) == 0) {
                    FLAG = 0;
                }
            }
            if(FLAG == 0){
                printf("0〜2の一桁の数字で入力してください。\n");
                scanf("%s", buf);
                flag1=1;
            }else{
                n = atoi(buf);
                flag1=0;
            }
        }
        switch(n){
		case 1:
			//puts("success!\n");
			Output(1);
			flag2=1;
			break;
		case 2:
			//puts("ええかんでぃ\n");
			Output(0);
			flag2=1;
			break;
		case 0:
			puts("お疲れ様でした。\n");
			flag2=0;
			break;
		default:
			puts("もう一度入力してください。\n");
			break;
        }
    }
}

void TagRead(char filepath[],char *tags[]){
    /*
        問題テキストファイルからタグ成分を抽出
        引数のtagsに抽出したタグを格納する

        引数
        filepath:ファイルのパス　相対パスじゃないと環境が変わるとめんどくさい
        tags:タグを格納するために持ってくるcharのポインタの配列（実質2次元配列みたいなもの）
            このやり方を採用してる理由は、C言語の関数は配列を戻り値にできないため

        戻り値　なし
    */
	FILE *f;
    char s[100];
    if((f = fopen(filepath,"r"))!=NULL){
        //1行そのまま読み込み sに格納
        fgets(s,100,f);

        //単語ごとに分割
        int i=0;
        tags[i] = strtok(s," ");
        strcat(tags[i],"");
        while(tags[i]!=NULL){
            i++;
            tags[i] = strtok(NULL," ");
            strcat(tags[i],"");
        }
        //LinuxかWindowsで改行コードが違うので
        if(tags[i-1][strlen(tags[i-1])-2] == '\r'){
            tags[i-1][strlen(tags[i-1])-2] = '\0';
        }else{
            tags[i-1][strlen(tags[i-1])-1] = '\0';
        }
    }
    fclose(f);
}

void TagRead(char filepath[],char *tags[]){
    /*
        問題テキストファイルからタグ成分を抽出
        引数のtagsに抽出したタグを格納する

        引数
        filepath:ファイルのパス　相対パスじゃないと環境が変わるとめんどくさい
        tags:タグを格納するために持ってくるcharのポインタの配列（実質2次元配列みたいなもの）
            このやり方を採用してる理由は、C言語の関数は配列を戻り値にできないため

        戻り値　なし
    */
	FILE *f;
    char s[100];
    if((f = fopen(filepath,"r"))!=NULL){
        //1行そのまま読み込み sに格納
        fgets(s,100,f);

        //単語ごとに分割
        int i=0;
        tags[i] = strtok(s," ");
        strcat(tags[i],"");
        while(tags[i]!=NULL){
            i++;
            tags[i] = strtok(NULL," ");
            strcat(tags[i],"");
        }
        //LinuxかWindowsで改行コードが違うので
        if(tags[i-1][strlen(tags[i-1])-2] == '\r'){
            tags[i-1][strlen(tags[i-1])-2] = '\0';
        }else{
            tags[i-1][strlen(tags[i-1])-1] = '\0';
        }
    }
    fclose(f);
}

void ManageTag(){
    /*
        ManageTag()と呼び出すだけで以下のことを行います
        問題テキストファイルを一個づつ全部読み出していき、TagRead関数を用いて抽出したタグから（タグ名）.txtを作成する関数
        問題テキストファイルの置き場所をquestionsディレクトリ、タグ名のついたテキストファイルの置き場所をtagsディレクトリとしている
    */
	int num=1; //問題番号
    FILE *f;
    char qpath[30]; //問題のファイルパス
    //ファイルパス作成
    sprintf(qpath,"questions/qes%03d.txt",num);
    //もし（まだ）問題ファイルが存在するなら

    while((f = fopen(qpath,"r"))!=NULL){
        //一旦問題のファイルを閉じる
        fclose(f);
        char *tagsp[10]; //ポインタの配列
        TagRead(qpath,tagsp);
        int i=0;
        char tags[10][50] = {{ 0 }}; //２次元配列（なんとなくコピーして別で置いておきたくなった）
        while(tagsp[i]!=NULL){
            strcpy(tags[i],tagsp[i]);
            i++;
        }
        i=0;
        while(tags[i][0]!='\0'){
            FILE *tagfile;
            char tpath[30]; //tagのファイルパス
            //tagファイルパス作成
            sprintf(tpath,"tags/%s.txt",tags[i]);
            tagfile = fopen(tpath,"a");
            fprintf(tagfile,"qes%03d.txt\n",num);
            fclose(tagfile);
            i++;
        }
        num++;
        //ファイルパス作成
        sprintf(qpath,"questions/qes%03d.txt",num);
    }
    //ないならTag取得おわり
}

void CreateProblem(){
    return;
}

int main(){
    //data x;
    //strcpy(x.quespath,"questions/qes001.txt");
    //CountWA(x);
    //ManageTag();
    
    /* FileReadデバッグ
    data test;
    char filepath[] = "questions/qes001.txt";
    test = ReadFile(filepath);
    int i=0;
    while(test.tag[i][0]!='\0'){
    	printf("%s",test.tag[i]);
    	i++;
    }
    printf("\n");
    
    printf("%d\n",test.wrongchoice);
    
    printf("%s\n",test.question);
    
    for(i=0;i<4;i++){
    	printf("%s\n",test.choice[i]);
    }
    
    printf("%s\n",test.modelans);
    */
    Menu();
    return 0;
}

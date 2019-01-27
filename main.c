#include<stdio.h>
#include<stdlib.h>
#include<string.h>

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

void Output(){
    return;
}

void CheckAnswer(){
    return;
}

void Menu(){
    return;
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
    
    
    return 0;
}

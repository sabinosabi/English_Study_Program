#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

typedef struct Data{
	char question[100];
	char choice[4][50];
	char modelans[50];
	char tag[10][50];
	int wrongchoice;
}data;

FILE FileRead(char filepath[]){
    return;
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

void Output()
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
        tags[i-1][strlen(tags[i-1])-1] = '\0';
    }
    fclose(f);
}

void ManageTag(){
    /*
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
	ManageTag();
    return 0;
}

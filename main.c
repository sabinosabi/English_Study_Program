#include<stdio.h>
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

FILE FileRead(char[] filepath){
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

void ManageTag(){
    return;
}

void CreateProblem(){
    return;
}

int main(){

    return 0;
}

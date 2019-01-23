#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

int line; //タグファイルの行数(何もない改行をしない)
int qes;//出題数
int num[30]; //ランダム数格納用
char s[100][30]; //100列分、1列辺り30文字まで
char last[100][30];

void Select();
void Random();
void Qopen();

/*int main(){    //仮実行用 ドライバ
	char str[10];
	printf("タグを選択してください\n");
	scanf("%s",str);
	Select(str);
	Qopen();
	//printf("正常終了\n");
	return 0;
}*/ //str(適当なタグ名保管変数)にmenu部で格納済みの場合不要

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

void Qopen(){ //
	int i;
	FILE *fs;
	for(i=1;i<=qes;i++){
		fs=fopen(s[num[i]-1],"r");
		//ここに出題部を接続
		fclose(fs);
		//strcpy(last[i],s[num[i]-1]);
		//printf("%2d番目の問題:%s",i,last[i]);//スタブ
	}
}














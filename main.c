#include<stdio.h>
#include<string.h>

typedef struct Data{
	char question[100];
	char choice[4][50];
	char modelans[50];
	char tag[10][50];
	int wrongchoice;
    char quespath[50];
}data;

FILE FileRead(char filepath[]){
    return;
}

void Output(){
    return;
}

void CheckAnswer(){
    return;
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
    return;
}

void ManageTag(){
    return;
}

void CreateProblem(){
    return;
}

int main(){
    data x;
    strcpy(x.quespath,"questions/qes001.txt");
    CountWA(x);
    return 0;
}

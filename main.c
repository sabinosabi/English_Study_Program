#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

FILE FileRead(char filepath[]){
    return;
}

void Output(){
    return;
}

void CheckAnswer(){
    return;
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
                puts("success!\n");
                flag2=1;
                break;
                case 2:
                puts("ええかんでぃ\n");
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
    Menu();
    return 0;
}

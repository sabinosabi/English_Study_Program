#include<stdio.h>
#include<stdlib.h>
#include<string.h>

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
            printf("%s ",tags[i]);
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

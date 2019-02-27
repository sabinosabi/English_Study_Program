#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<time.h>
#include<dirent.h>
#include<stdbool.h>

typedef struct Data{
    char question[100];
    char choice[4][50];
    char modelans[50];
    char tag[10][50];
    int wrongchoice;
    char quespath[50];
}data;

struct Tags{
    size_t length;
    size_t allocated_length;
    char** tags;
};

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
            puts("error");
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
    if ((fo = fopen(filepath, "r")) == NULL) {
        fprintf(stderr, "error:%sのオープンに失敗しました。\n", filepath);
        exit(EXIT_FAILURE);
    }


    /* 1行目の処理 <tag> */
    for(int i=0;i<10;i++){
        x.tag[i][0] = '\0';
    }
    char readline[100] = {'\0'};
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
    for(int i=0;i<4;i++){
        x.choice[i][0] = '\0';
    }
    fgets(readline, 100, fo);
    SpritSpace(RemoveN(readline), 1, &x);

    /* 5行目の処理 <modelans> */
    fgets(readline, 100, fo);
    strcpy(x.modelans, RemoveN(readline));
    //puts(x.modelans);

    //modelansのキャリッジリターン消し
    if(x.modelans[strlen(x.modelans)-1] == '\r'){
        x.modelans[strlen(x.modelans)-1] = '\0';
    }

    /* quespathを代入 */
    strcpy(x.quespath,filepath);

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
            //printf("%d\n",wc);
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


int Question(data x,int k)
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
    printf("\n");
    printf("問%d：%s\n間違えた回数 --> %d\n",k,x.question,x.wrongchoice);
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
        return 1;
    }else if(ans != modelansnum){
        printf("不正解...\n");
        CountWA(x);
        return 0;
    }else{
        printf("program error\n");
        return 2;
    }
}

data Qopen(int qes,char* q_filenames[100],int* num){
    int good_count=0;
    int bad_count=0;
    for(int i=0;i<qes;i++){
        char *qespath;
        asprintf(&qespath,"questions/%s",q_filenames[num[i]-1]);
        data p[qes];
        p[i]=ReadFile(qespath);
        free(qespath);
        if(Question(p[i],i+1)){
            good_count++;
        }else{
            bad_count++;
        }
    }
    printf("\n問題数:%d  正解数:%d  不正解数:%d\n",qes,good_count,bad_count);
    if((float)good_count/qes>=0.8){
        puts("評価:◎");
    }else if((float)good_count/qes>=0.5){
        puts("評価:○");
    }else if((float)good_count/qes>=0.2){
        puts("評価:△");
    }else {
        puts("評価:×");
    }//なんとなく評価値
    puts("");
}

void Random(int* line,int* qes,int* num){
    int i,j,x;
    *qes=20;
    srand((unsigned) time(NULL));
    if(*qes>*line) *qes=*line; //ファイルの総問題数不足時に出題数を揃える
    for(i=0;i<=30;i++) num[i]=0;
    for(i=0;i<(*qes);i++){
        do{
            x=0;
            num[i]=rand()%(*line)+1; //ランダム関数
            for(j=0;j<i;j++){
                if(num[j]==num[i]){
                    x=1;
                }
            }
        }while(x==1);
    }
}

void Select(char* tagname, int* line, char* q_filenames[100], int* qes,int* num){
    /* タグファイル選択 */
    char* path;
    asprintf(&path,"tags/%s.txt",tagname);
    FILE *ft=fopen(path,"r");
    free(path);
    if (ft == NULL) {
        fprintf(stderr, "%sというタグは存在しません。\n", tagname);
        return;
    }

    *line=0; 
    int i=0;
    q_filenames[i]=NULL;
    size_t s_i_size=0;
    while(getline(&q_filenames[i],&s_i_size,ft)!=-1){
        (*line)++;
        //改行消し
        if(q_filenames[i][strlen(q_filenames[i])-2] == '\r'){
            q_filenames[i][strlen(q_filenames[i])-2] = '\0';
        }else{
            q_filenames[i][strlen(q_filenames[i])-1] = '\0';
        }
        i++;

        q_filenames[i]=NULL;
        s_i_size=0;
    }
    fclose(ft);
    Random(line,qes,num);
}

void Output(bool is_all){
    int line=0; //タグファイルの行数(何もない改行をしない)
    int qes=0;//出題数
    int num[100]={0}; //ランダム数格納用
    char* q_filenames[100]; //100列分、1列辺り30文字まで

    char* tagname;
    if(is_all){
        asprintf(&tagname,"All");//全問題のファイルはAll.txtとする
    }else{
        puts("タグを選択してください");
        scanf("%ms",&tagname);
    }
    Select(tagname,&line,q_filenames,&qes,num);
    free(tagname);

    /*
       for(int i=0;i<=30;i++){
       printf("%d\n",num[i]);
       }
       */
    /*
       for(int i=0;i<10;i++){
       printf("%s\n",s[i]);
       }
       */
    Qopen(qes,q_filenames,num);
}//str(適当なタグ名保管変数)にmenu部で格納済みの場合不要

void Menu(){
    while(1){
        puts("\n学習方法を数字で選択してください。");
        puts("--------------------------------------");
        puts(" 1 | ジャンルを絞って問題を出題\n");
        puts(" 2 | ランダムに問題を出題\n");
        puts(" 0 | プログラムを終了する。");
        puts("--------------------------------------\n");

        char* buf;
        scanf("%ms",&buf);
        if(strcmp(buf,"1")==0){
            //puts("success!\n");
            Output(false);
        }else if(strcmp(buf,"2")==0){
            //puts("ええかんでぃ\n");
            Output(true);
        }else if(strcmp(buf,"0")==0){
            puts("お疲れ様でした。\n");
            return;
        }else{
            puts("0〜2の一桁の数字で入力してください。\n");
        }
        free(buf);
    }
}

void TagRead(char filepath[],struct Tags *tags){
    /*
       問題テキストファイルからタグ成分を抽出
       引数のtagsに抽出したタグを格納する
       <引数>
filepath:ファイルのパス　相対パスじゃないと環境が変わるとめんどくさい
tags:タグを格納するために持ってくるcharのポインタの配列
（実質2次元配列みたいなもの）
このやり方を採用してる理由は、C言語の関数は配列を戻り値にできないため
*/
    FILE *f = fopen(filepath,"r");
    if(f==NULL){
        return;
    }

    //HACK:このtagslineメモリリークしそう?
    char* tagsline=NULL;
    size_t s_size=0;
    getline(&tagsline,&s_size,f);
    fclose(f);

    //単語ごとに分割
    int i=0;
    tags->tags[i] = strtok(tagsline," ");
    while(tags->tags[i]!=NULL){
        i++;
        tags->tags[i] = strtok(NULL," ");
        if(i>=tags->allocated_length-1){
            tags->allocated_length+=256;
            realloc(tags->tags,tags->allocated_length);
        }
    }
    //LinuxかWindowsで改行コードが違うので
    if(tags->tags[i-1][strlen(tags->tags[i-1])-2] == '\r'){
        tags->tags[i-1][strlen(tags->tags[i-1])-2] = '\0';
    }else{
        tags->tags[i-1][strlen(tags->tags[i-1])-1] = '\0';
    }

    tags->length=i;
}

void DeleteTagFiles(){
    //Tagsディレクトリの中身を一掃する関数
    //Tagsディレクトリ内にTag名ファイルを生成する前に消すためのもの
    struct dirent **dir_list;
    int dir_num = scandir("tags/", &dir_list, NULL, alphasort);
    if (dir_num < 0){
        return;
    }
    while (dir_num--) {
        if(dir_list[dir_num]->d_type!=DT_REG){
            continue;
        }
        char* tpath;
        asprintf(&tpath,"tags/%s",dir_list[dir_num]->d_name);
        remove(tpath);
        free(tpath);

        free(dir_list[dir_num]);
    }
    free(dir_list);
}

void AppendAllTagFile(char* qpath){
    /*
       「All.txt」というタグファイルを作成する関数
       */
    FILE *f = fopen("tags/All.txt","a");
    fprintf(f,"%s\n",qpath);
    fclose(f);
}

void ManageTag(){
    /*
       ManageTag()と呼び出すだけで以下のことを行います
       問題テキストファイルを一個づつ全部読み出していき、
       TagRead関数を用いて抽出したタグから（タグ名）.txtを作成する関数
       問題テキストファイルの置き場所をquestionsディレクトリ、
       タグ名のついたテキストファイルの置き場所をtagsディレクトリとしている
       */


    DeleteTagFiles();


    struct dirent **dir_list;
    int dir_num = scandir("questions", &dir_list, NULL, alphasort);
    if (dir_num < 0){
        return;
    }

    while (dir_num--) {
        if(dir_list[dir_num]->d_type!=DT_REG){
            free(dir_list[dir_num]);
            continue;
        }

        AppendAllTagFile(dir_list[dir_num]->d_name);

        struct Tags tags;
        tags.allocated_length=256;
        tags.tags=malloc(tags.allocated_length*sizeof(char*));
        char *qpath;
        asprintf(&qpath,"questions/%s",dir_list[dir_num]->d_name);
        TagRead(qpath,&tags);
        for(int i=0;i<tags.length;++i){
            char *tag_path;
            /* tagファイルパス作成 */
            asprintf(&tag_path,"tags/%s.txt",tags.tags[i]);
            FILE *tagfile= fopen(tag_path,"a");
            free(tag_path);
            fprintf(tagfile,"%s\n",dir_list[dir_num]->d_name);
            fclose(tagfile);
        }

        free(dir_list[dir_num]);
        free(qpath);
    }
    free(dir_list);
}

int main(){
    ManageTag();
    Menu();
}

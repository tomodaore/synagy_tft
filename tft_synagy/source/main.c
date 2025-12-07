//cgiは/usr/lib/cgi-binに置く
//gcc -o main.cgi main.c
//htmlは/var/www/html/cgiに置く
//sudo tail -f /var/log/apache2/error.log エラーログ確認


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define MAX_LINE 1000  // 1行の最大長
#define MAX_FIELD 30  // 最大フィールド数
#define number_champ 70 //キャラ数

#include "func.h"

int main(){
    int champCount = 0, fieldCount;//champcountはchampの数 fieldcountはシナジーの数
    char *champ[number_champ][MAX_FIELD];  // CSVの各フィールドを格納する配列
    char *champ_cost[number_champ][2];//チャンプのコストが入ってる配列
    char *champ_bonus[number_champ][7];//シナジー発動の評価
    char search[100];//探すシナジーの入力を受け付ける
    int search_i,search_j;//search_iは０行から対応するシナジーを探す。search_jは対応するシナジーを持つチャンプの行を示す。
    int synergy[20],synergyCount = 0;//synergyはシナジーを持つキャラの配列の行数を示す。synergyCountはsynergyのためのシナジーを持つキャラの数
    int cost;//何コスト以下か
    // ヘッダー
    printf("Content-Type: text/html;charset=UTF-8\n\n");
    // 環境変数 CONTENT_LENGTH を読む
    char *lenstr = getenv("CONTENT_LENGTH");
    if (!lenstr) {
        printf("データがありません。\n");
        return 1;
    }
    int len = atoi(lenstr);
    char *post_data = malloc(len + 1);
    fread(post_data, 1, len, stdin);
    post_data[len] = '\0';
    // URLデコード
    char decoded[1024];
    url_decode(post_data, decoded);
    // 表示
    //printf("<h2>受け取ったデータ:</h2><p>%s</p>\n", decoded);
    
    // チェックボックス（複数ある可能性あり）を解析
    // 例: synergy=Anima+Squad&synergy=Bruiser
    char *token = strtok(decoded, "&");
    while (token != NULL) {
        if (strncmp(token, "synergy=", 8) == 0) {
            printf("<p>選択されたシナジー: %s</p>\n", token + 8);
            strncpy(search, token + 8, sizeof(search) - 1);
            search[sizeof(search) - 1] = '\0'; // Null-terminate to ensure safety
        } 
        else if (strncmp(token, "cost=", 5) == 0) {
            printf("<p>選択されたコスト: %s</p>\n", token + 5);
            cost = atoi(token + 5);

        }
        token = strtok(NULL, "&");
    }

    //ここからシナジーのデータを読み込む

    int result = input_synergy("synergy_data/champs_synergy_20250402.csv", champ, &champCount, &fieldCount); // 入力関数
    if (result == EXIT_FAILURE) {
        printf("<p>Error: Failed to load synergy data.</p>\n");
        return EXIT_FAILURE;
    }
    int result1 = input_cost("synergy_data/champs_cost_20250402.csv", champ_cost);
    if (result1 == EXIT_FAILURE) {
        printf("<p>Error: Failed to load cost data.</p>\n");
        return EXIT_FAILURE;
    }
    int result2 = input_bonus("synergy_data/trait_bonus_counts_20250402.csv", champ_bonus);
    if (result2 == EXIT_FAILURE) {
        printf("<p>Error: Failed to load bonus data.</p>\n");
        return EXIT_FAILURE;
    }
    /*for(int o = 0;o < 26;o++){
        for(int k = 0;k < 7;k++){
            printf("%s ",champ_bonus[o][k]);
        }
        printf("\n");
    }*/
    //軸シナジー全員の持つシナジーを確認

    for(search_i = 0;search_i < fieldCount;search_i++){//軸シナジー
        //printf("search = %s,champ = %s\n",search,champ[0][search_i]);
        if(strcmp(search,champ[0][search_i]) == 0){
            break;
        }
    }

    search_i = search_i+1;//調整 ０行目のAnima Squadがchamp[0][0]に入ってるから
    
    //ここでチャンプを探す
    for(search_j = 1;search_j < champCount;search_j++){
        if(atoi(champ_cost[search_j][1]) <= cost){
            if(strcmp("True",champ[search_j][search_i]) == 0){
                //printf("%s,",champ[search_j][0]);//確認
                synergy[synergyCount++] = search_j;
            }
        }
    }
    
    //ここでチャンプのシナジーを数える
    int ChampSynergy[MAX_FIELD];//champ[0]に対応した配列。選ばれた軸シナジーの全員をチェックして持ってるシナジーを確認する。
    memset(ChampSynergy,0,sizeof(ChampSynergy));//ChampSynergyの中を０で埋める
    int search_synergy,for_synergyCount;
    for(for_synergyCount = 0;for_synergyCount < synergyCount;for_synergyCount++){
        for(search_synergy = 0;search_synergy < fieldCount;search_synergy++){
            //printf("%s\n",champ[synergy[for_synergyCount]][search_synergy]);
            if(strcmp("True",champ[synergy[for_synergyCount]][search_synergy]) == 0){
                ChampSynergy[search_synergy-1] += 1;
            }
            //printf("search_sy %d\n",search_synergy);
        }
        //printf("for_sy %d\n",for_synergyCount);
    }

    //どのキャラがどのくらい集まるとどのくらいシナジーを持つか確認する
    //とりあえず軸シナジーのキャラ全員が集まったときを確認
    check_synergy(&search_synergy,fieldCount,ChampSynergy);
    show_char_champ(synergy,synergyCount,champ);

    //ここは持つシナジー全部を確認
    printf("<p>持つシナジー全部</p>\n");
    for(int o = 0;o < fieldCount;o++){
        if(ChampSynergy[o] > 0){
            printf("<p>%s %d</p>\n",champ[0][o],ChampSynergy[o]);
        }
    }

    free(post_data);//メモリを解放
    return 0;
}
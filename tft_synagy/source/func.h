const char *champion_map[][2] = {
    {"alistar", "アリスター"},
    {"annie", "アニー"},
    {"aphelios", "アフェリオス"},
    {"aurora", "オーロラ"},
    {"brand", "ブランド"},
    {"braum", "ブラウム"},
    {"chogath", "チョ＝ガス"},
    {"darius", "ダリウス"},
    {"dr_mundo", "ドクター・ムンド"},
    {"draven", "ドレイヴン"},
    {"ekko", "エコー"},
    {"elise", "エリス"},
    {"fiddlesticks", "フィドルスティックス"},
    {"galio", "ガリオ"},
    {"garen", "ガレン"},
    {"gragas", "グラガス"},
    {"graves", "グレイブス"},
    {"illaoi", "イラオイ"},
    {"jarvan_iv", "ジャーヴァン4世"},
    {"jax", "ジャックス"},
    {"jhin", "ジン"},
    {"jinx", "ジンクス"},
    {"kindred", "キンドレッド"},
    {"kobuko", "コブコ"},
    {"kogmaw", "コグ＝マウ"},
    {"leblanc", "ルブラン"},
    {"leona", "レオナ"},
    {"miss_fortune", "ミス・フォーチュン"},
    {"mordekaiser", "モルデカイザー"},
    {"morgana", "モルガナ"},
    {"naafiri", "ナーフィリ"},
    {"neeko", "ニーコ"},
    {"nidalee", "ニダリー"},
    {"poppy", "ポッピー"},
    {"renekton", "レネクトン"},
    {"rengar", "レンガー"},
    {"rhaast", "ラースト"},
    {"samira", "サミラ"},
    {"sejuani", "セジュアニ"},
    {"senna", "セナ"},
    {"seraphine", "セラフィーン"},
    {"shaco", "シャコ"},
    {"shyvana", "シャイヴァナ"},
    {"skarner", "スカーナー"},
    {"sylas", "サイラス"},
    {"twisted_fate", "ツイステッド・フェイト"},
    {"urgot", "ウーゴット"},
    {"varus", "ヴァルス"},
    {"vayne", "ヴェイン"},
    {"veigar", "ヴェイガー"},
    {"vex", "ヴェックス"},
    {"vi", "ヴァイ"},
    {"viego", "ヴィエゴ"},
    {"xayah", "ザヤ"},
    {"yuumi", "ユーミ"},
    {"zac", "ザック"},
    {"zed", "ゼド"},
    {"zeri", "ゼリ"},
    {"ziggs", "ジグス"},
    {"zyra", "ザイラ"},
    {NULL, NULL} // 終端
};

const char* translate_champion(const char *english_name) {
    for (int i = 0; champion_map[i][0] != NULL; i++) {
        if (strcmp(english_name, champion_map[i][0]) == 0) {
            return champion_map[i][1];
        }
    }
    return english_name; // 対応する日本語がない場合はそのまま返す
}

int show_int_array(int arr[],int size){//使用例show_int_array(ChampSynergy,25);
    for(int i = 0;i < size;i++){
        printf("%d ",arr[i]);
    }
    printf("\n");
}

char show_char_array(char *arr[],int size){//例show_char_array(champ[0],25);
    for(int i = 0;i < size;i++){
        printf("%s ",arr[i]);
    }
    printf("\n");
}

char show_char_champ(int synergy[20],int synergycount,char *arr[number_champ][MAX_FIELD]){
    for(int i = 0;i < synergycount;i++){
        printf("%s、\n",translate_champion(arr[synergy[i]][0]));
    }
}

int input_synergy(const char *filename,char *champ[number_champ][MAX_FIELD],int *champCount,int *fieldCount){
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("<p>ファイルを開けません</p>\n");
        printf("<p>Error: %s</p>\n", strerror(errno)); // エラー内容をHTMLで表示
        return EXIT_FAILURE;
    }
    char line[MAX_LINE];  // 1行を読み込むバッファ
    while (fgets(line, sizeof(line), file)) {
        *fieldCount = 0;
        //printf("%s\n", line);  // 行を表示（デバッグ）

        // strtokで行をトークンに分割
        char *token = strtok(line, ",\n");
        while (token) {
            //printf("%s\n", token);  // トークンの確認（デバッグ）

            // トークンを新しいメモリ領域にコピー
            champ[*champCount][*fieldCount] = strdup(token);  // strdupでコピー
            if (champ[*champCount][*fieldCount] == NULL) {
                printf("<p>メモリの確保に失敗しました</p>\n");
                perror("メモリの確保に失敗しました");
                return EXIT_FAILURE;
            }

            (*fieldCount)++;  // フィールド数を増やす
            token = strtok(NULL, ",\n");  // 次のトークンを取得
        }

        (*champCount)++;  // キャラクター数を増やす
        //printf("champCount = %d\n", champCount);  // 現在のキャラクター数を表示（デバッグ）

        /*// デバッグ用に途中で終了（3行まで読み込む）
        if (champCount == 3) {
            printf("%s\n", champ[1][0]);
            return EXIT_SUCCESS;
        }*/
    }

    // 読み込んだデータを出力
    /*for (int i = 0; i < champCount; i++) {
        for (int j = 0; j < fieldCount; j++) {
            printf("%s ", champ[i][j]);
        }
        printf("\n");
    }*/

    /*// メモリ解放
    for (int i = 0; i < champCount; i++) {
        for (int j = 0; j < fieldCount; j++) {
            free(champ[i][j]);  // strdupで確保したメモリを解放
        }
    }*/

    fclose(file);//入力ここまで
}

int input_cost(const char *filename,char *champ_cost[number_champ][2]){
    int fieldcount = 0,champcount = 0;
    FILE *file =fopen(filename,"r");
    if(file == NULL){
        perror("ファイルを開けません");
        return EXIT_FAILURE;
    }
    char line[MAX_LINE];
    while (fgets(line, sizeof(line), file)) {
        fieldcount = 0;
        //printf("%s\n", line);  // 行を表示（デバッグ）

        // strtokで行をトークンに分割
        char *token = strtok(line, ",\n");
        while (token) {
            //printf("%s\n", token);  // トークンの確認（デバッグ）
            champ_cost[champcount][fieldcount] = strdup(token);
            if(champ_cost[champcount][fieldcount] == NULL){
                perror("メモリの確保に失敗しました。");
                return EXIT_FAILURE;
            }
            fieldcount++;
            token = strtok(NULL,",\n");
        }
        champcount++;
    }
    fclose(file);//入力ここまで
}

int input_bonus(const char *filename,char *champ_bonus[number_champ][7]){
    int fieldcount = 0,champcount = 0;
    FILE *file = fopen(filename,"r");
    if(file == NULL){
        perror("ファイルを開けません");
        return EXIT_FAILURE;
    }
    char line[MAX_LINE];
    while(fgets(line,sizeof(line),file)){
        fieldcount = 0;
        
        char *token = strtok(line, ",\n");
        while(token){
            champ_bonus[champcount][fieldcount] = strdup(token);
            if(champ_bonus[champcount][fieldcount] == NULL){
                perror("ファイルを開けません");
                return EXIT_FAILURE;
            }
            fieldcount++;
            token = strtok(NULL,",\n");
        }
        champcount++;
    }
    for(int i = 0;i < 6;i++){
        sprintf(champ_bonus[0][i],"%d",i);
    }
    champ_bonus[0][6] = "6";
    fclose(file);
}

int check_synergy(int *search_synergy,int fieldCount,int ChampSynergy[]){
    for((*search_synergy) = 0;(*search_synergy) < fieldCount;(*search_synergy)++){
        if(ChampSynergy[*search_synergy] > 0){
            //Anima Squad
            if(*search_synergy == 0){
                if(ChampSynergy[*search_synergy] >= 10){
                    printf("<p>Anima Squad 10</p>\n");
                }
                else if(ChampSynergy[*search_synergy] >= 7){
                    printf("<p>Anima Squad 7</p>\n");
                }
                else if(ChampSynergy[*search_synergy] >= 5){
                    printf("<p>Anima Squad 5</p>\n");
                }
                else if(ChampSynergy[*search_synergy] >= 3){
                    printf("<p>Anima Squad 3</p>\n");
                }
            }
            //BoomBots
            if(*search_synergy == 1){
                if(ChampSynergy[*search_synergy] >= 6){
                    printf("<p>BoomBots 6</p>\n");
                }
                else if(ChampSynergy[*search_synergy] >= 4){
                    printf("<p>BoomBots 4</p>\n");
                }
                else if(ChampSynergy[*search_synergy] >= 2){
                    printf("<p>BoomBots 2</p>\n");
                }
            }
            //Cyberboss
            if(*search_synergy == 2){
                if(ChampSynergy[*search_synergy] >= 4){
                    printf("<p>Cyberboss 4</p>\n");
                }
                else if(ChampSynergy[*search_synergy] >= 3){
                    printf("<p>Cyberboss 3</p>\n");
                }
                else if(ChampSynergy[*search_synergy] >= 2){
                    printf("<p>Cyberboss 2</p>\n");
                }
            }
            //Cypher
            if(*search_synergy == 3){
                if(ChampSynergy[*search_synergy] >= 5){
                    printf("<p>Cypher 5</p>\n");
                }
                else if(ChampSynergy[*search_synergy] >= 4){
                    printf("<p>Cypher 4</p>\n");
                }
                else if(ChampSynergy[*search_synergy] >= 3){
                    printf("<p>Cypher 3</p>\n");
                }
            }
            //Divinicorp
            if(*search_synergy == 4){
                printf("<p>Divinicorp %d</p>\n",ChampSynergy[*search_synergy]);
            }
            //Exotech
            if(*search_synergy == 5){
                if(ChampSynergy[*search_synergy] >= 10){
                    printf("<p>Exotech 10</p>\n");
                }
                else if(ChampSynergy[*search_synergy] >= 7){
                    printf("<p>Exotech 7</p>\n");
                }
                else if(ChampSynergy[*search_synergy] >= 5){
                    printf("<p>Exotech 5</p>\n");
                }
                else if(ChampSynergy[*search_synergy] >= 3){
                    printf("<p>Exotech 3</p>\n");
                }
            }
            //God of the Net
            if(*search_synergy == 6){
                printf("<p>God of the Net %d</p>\n",ChampSynergy[*search_synergy]);
            }
            //Golden Ox
            if(*search_synergy == 7){
                if(ChampSynergy[*search_synergy] >= 6){
                    printf("<p>Golden Ox 6</p>\n");
                }
                else if(ChampSynergy[*search_synergy] >= 4){
                    printf("<p>Golden Ox 4</p>\n");
                }
                else if(ChampSynergy[*search_synergy] >= 2){
                    printf("<p>Golden Ox 2</p>\n");
                }
            }
            //Nitro
            if(*search_synergy == 8){
                if(ChampSynergy[*search_synergy] >= 4){
                    printf("<p>Nitro 4</p>\n");
                }
                else if(ChampSynergy[*search_synergy] >= 3){
                    printf("<p>Nitro 3</p>\n");
                }
            }
            //Overlord
            if(*search_synergy == 9){
                printf("<p>Overlord 1</p>\n");
            }
            //Soul Killer
            if(*search_synergy == 10){
                printf("<p>Soul Killer 1</p>\n");
            }
            //Street Demon
            if(*search_synergy == 11){
                if(ChampSynergy[*search_synergy] >= 10){
                    printf("<p>Street Demon 10</p>\n");
                }
                else if(ChampSynergy[*search_synergy] >= 7){
                    printf("<p>Street Demon 7</p>\n");
                }
                else if(ChampSynergy[*search_synergy] >= 5){
                    printf("<p>Street Demon 5</p>\n");
                }
                else if(ChampSynergy[*search_synergy] >= 3){
                    printf("<p>Street Demon 3</p>\n");
                }
            }
            //Syndicate
            if(*search_synergy == 12){
                if(ChampSynergy[*search_synergy] >= 7){
                    printf("<p>Syndicate 7</p>\n");
                }
                else if(ChampSynergy[*search_synergy] >= 5){
                    printf("<p>Syndicate 5</p>\n");
                }
                else if(ChampSynergy[*search_synergy] >= 3){
                    printf("<p>Syndicate 3</p>\n");
                }
            }
            //Virus
            if(*search_synergy == 13){
                printf("<p>Virus 1</p>\n");
            }
            //A.M.P.
            if(*search_synergy == 14){
                if(ChampSynergy[*search_synergy] >= 5){
                    printf("<p>A.M.P. 5</p>\n");
                }
                else if(ChampSynergy[*search_synergy] >= 4){
                    printf("<p>A.M.P. 4</p>\n");
                }
                else if(ChampSynergy[*search_synergy] >= 3){
                    printf("<p>A.M.P. 3</p>\n");
                }
                else if(ChampSynergy[*search_synergy] >= 2){
                    printf("<p>A.M.P. 2</p>\n");
                }
            }
            //Bastion
            if(*search_synergy == 15){
                if(ChampSynergy[*search_synergy] >= 6){
                    printf("<p>Bastion 6</p>\n");
                }
                else if(ChampSynergy[*search_synergy] >= 4){
                    printf("<p>Bastion 4</p>\n");
                }
                else if(ChampSynergy[*search_synergy] >= 2){
                    printf("<p>Bastion 2</p>\n");
                }
            }
            //Bruiser
            if(*search_synergy == 16){
                if(ChampSynergy[*search_synergy] >= 6){
                    printf("<p>Bruiser 6</p>\n");
                }
                else if(ChampSynergy[*search_synergy] >= 4){
                    printf("<p>Bruiser 4</p>\n");
                }
                else if(ChampSynergy[*search_synergy] >= 2){
                    printf("<p>Bruiser 2</p>\n");
                }
            }
            //Dynamo
            if(*search_synergy == 17){
                if(ChampSynergy[*search_synergy] >= 4){
                    printf("<p>Dynamo 4</p>\n");
                }
                else if(ChampSynergy[*search_synergy] >= 3){
                    printf("<p>Dynamo 3</p>\n");
                }
                else if(ChampSynergy[*search_synergy] >= 2){
                    printf("<p>Dynamo 2</p>\n");
                }
            }
            //Executioner
            if(*search_synergy == 18){
                if(ChampSynergy[*search_synergy] >= 5){
                    printf("<p>Executioner 5</p>\n");
                }
                else if(ChampSynergy[*search_synergy] >= 4){
                    printf("<p>Executioner 4</p>\n");
                }
                else if(ChampSynergy[*search_synergy] >= 3){
                    printf("<p>Executioner 3</p>\n");
                }
                else if(ChampSynergy[*search_synergy] >= 2){
                    printf("<p>Executioner 2</p>\n");
                }
            }
            //Marksman
            if(*search_synergy == 19){
                if(ChampSynergy[*search_synergy] >= 4){
                    printf("<p>Marksman 4</p>\n");
                }
                else if(ChampSynergy[*search_synergy] >= 2){
                    printf("<p>Marksman 2</p>\n");
                }
            }
            //Rapidfire
            if(*search_synergy == 20){
                if(ChampSynergy[*search_synergy] >= 6){
                    printf("<p>Rapidfire 6</p>\n");
                }
                else if(ChampSynergy[*search_synergy] >= 4){
                    printf("<p>Rapidfire 4</p>\n");
                }
                else if(ChampSynergy[*search_synergy] >= 2){
                    printf("<p>Rapidfire 2</p>\n");
                }
            }
            //Slayer
            if(*search_synergy == 21){
                if(ChampSynergy[*search_synergy] >= 6){
                    printf("<p>Slayer 6</p>\n");
                }
                else if(ChampSynergy[*search_synergy] >= 4){
                    printf("<p>Slayer 4</p>\n");
                }
                else if(ChampSynergy[*search_synergy] >= 2){
                    printf("<p>Slayer 2</p>\n");
                }
            }
            //Strategist
            if(*search_synergy == 22){
                if(ChampSynergy[*search_synergy] >= 5){
                    printf("<p>Strategist 5</p>\n");
                }
                else if(ChampSynergy[*search_synergy] >= 4){
                    printf("<p>Strategist 4</p>\n");
                }
                else if(ChampSynergy[*search_synergy] >= 3){
                    printf("<p>Strategist 3</p>\n");
                }
                else if(ChampSynergy[*search_synergy] >= 2){
                    printf("<p>Strategist 2</p>\n");
                }
            }
            //Techie
            if(*search_synergy == 23){
                if(ChampSynergy[*search_synergy] >= 8){
                    printf("<p>Techie 8</p>\n");
                }
                else if(ChampSynergy[*search_synergy] >= 6){
                    printf("<p>Techie 4</p>\n");
                }
                else if(ChampSynergy[*search_synergy] >= 4){
                    printf("<p>Techie 4</p>\n");
                }
                else if(ChampSynergy[*search_synergy] >= 2){
                    printf("<p>Techie 2</p>\n");
                }
            }
            //Vanguard
            if(*search_synergy == 24){
                if(ChampSynergy[*search_synergy] >= 6){
                    printf("<p>Vanguard 6</p>\n");
                }
                else if(ChampSynergy[*search_synergy] >= 4){
                    printf("<p>Vanguard 4</p>\n");
                }
                else if(ChampSynergy[*search_synergy] >= 2){
                    printf("<p>Vanguard 2</p>\n");
                }
            }
        }
    }
}

// URLデコード関数
void url_decode(char *src, char *dest) {
    char code[3] = {0};
    while (*src) {
        if (*src == '+') {
            *dest++ = ' ';
            src++;
        } else if (*src == '%' && src[1] && src[2]) {
            code[0] = src[1];
            code[1] = src[2];
            *dest++ = (char) strtol(code, NULL, 16);
            src += 3;
        } else {
            *dest++ = *src++;
        }
    }
    *dest = '\0';
}


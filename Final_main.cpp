# include <bits/stdc++.h>
# include <ctime>
using namespace std ;

struct user {
    char username[20];
    char passwd[20];
    int  loginno;
    int  XAXBwin;
    int  XAXBlose;
};

/************************************************************************
*                             Login系統                                 *
************************************************************************/

//=== 檢查使用者帳號(帳號要求 3 碼以上 大小寫英文 或 數字） ===//
/* 更改內容:
1. 變數名稱
2. 將原本 flag 判斷是非改以直接回傳 true 或 false
*/
bool checkusername(const char u[]){
    int n = strlen(u) ;
    // 檢查長度 3 碼以上
    if ( n < 3 ){
        return false ;
    }
    // 檢查帳號每一個字
    for (int i = 0 ; i < n ; i++){
                    // 是否為數字                   // 是否為小寫英文字母            // 是否為大寫英文字母
        if (!((u[i] >= '0' && u[i] <= '9') || (u[i] >= 'A' && u[i] <= 'Z') || (u[i] >= 'a' && u[i] <= 'z'))){
            return false;
        }
    }
    return true;
}

//=== 檢查使用者密碼( 密碼要求為 3 碼以上 大小寫英文 或 數字 ，但需同時包含 數字 及 英文 ) ===//
/* 更改內容:
1. 變數名稱
2. 將原本 flag 判斷是非改以用 digit 和 alpha 來表示是非 
*/
bool checkpassword(const char p[]){
	int n = strlen(p) ;
	bool digit = false ; // 是否有數字
	bool alpha = false ; // 是否有字母

	// 檢查長度 3 碼以上
	if ( n < 3 ){
		return false ;
	}
	// 檢查密碼每一個字
	for ( int i = 0 ; i < n ; i++ ){
		// 是否為數字
		if ( p[i] >= '0' && p[i] <= '9' ){
			digit = true ;
		}
		// 是否為小寫英文字母
		if ( p[i] >= 'a' && p[i] <= 'z' ){
			alpha = true ;
		}
		// 是否為大寫英文字母
		if ( p[i] >= 'A' && p[i] <= 'Z' ){
		}
	}
	// 若 沒有數字 或 沒有英文字母 則回傳 false
	if (!digit || !alpha){
		return false ;
	}

	return true ;
}

//=== 檢查使用者帳號是否有被使用 ===//
/* 更改內容:
1. 變數名稱
2. 將原本 flag 判斷是非改以直接回傳 true 或 false
*/
bool available(user users[], int usercount, const char u[]){

	for ( int i = 0 ; i < usercount ; i++ ){
		// 帳號相同時，回傳 false
		if ( strcmp(users[i].username, u) == 0 ){
			return false ;
		}
	}
	return true ;
}

//=== 新增使用者 ===//
/* 更改內容:
1. 變數名稱
2. 將原本 flag 判斷是非改以直接回傳 true 或 false
*/
bool newuser(user users[], int &usercount) {
    char newname[20] ;    // 新帳號
    char newpass_1[20] ;  // 第一次輸入密碼
    char newpass_2[20] ;  // 再次確認輸入密碼

    cout << "=== 新增使用者帳號 ===" << "\n" ;

    // 重複要求輸入帳號，直到符合規定
    while ( true ){
        cout << "請輸入新帳號: " ;
        cin >> newname ; // 讀取使用者帳號
        // 檢查使用者帳號格式
        if ( !checkusername(newname) ){
            cout << "帳號不符合格式，請重新輸入" << "\n" ;
            continue;
        }
        // 檢查使用者帳號重複性
        if ( !available(users, usercount, newname) ){
            cout << "帳號已存在，請重新輸入" << "\n" ;
            continue ;
        }
        break ;
    }

    // 重複要求輸入密碼，直到兩次都相同和符合規定
    while ( true ){
        cout << "請輸入密碼: " ;
        cin >> newpass_1 ;
        cout << "請再次輸入密碼: " ;
        cin >> newpass_2 ;

        // 檢查二次密碼是否相同
        if ( strcmp(newpass_1, newpass_2) != 0 ) {
            cout << "兩次密碼輸入不一致，請重新輸入" << "\n" ;
            continue ;
        }
        // 檢查密碼是否符合格式
        if ( !checkpassword(newpass_1) ) {
            cout << "密碼不符合格式，請重新輸入" << "\n" ;
            continue ;
        }
        break;
    }

    // 寫入 userDB.txt
    strcpy(users[usercount].username, newname) ;
    strcpy(users[usercount].passwd, newpass_1) ;
    users[usercount].loginno = 0 ;
    users[usercount].XAXBwin  = 0 ;
    users[usercount].XAXBlose = 0 ;
    usercount++ ;

    cout << "您的新帳號 ** " << newname << " ** 建立成功！" << "\n" ;
    return true ;
}

//******************* 新增 *********************//
//================ 存取使用者資料 ==============//
void saveuserstofile(user users[], int usercount){
    ofstream fout("userDB.txt", ios::out) ;
    if ( !fout ) {
        cout << "無法開啟 userDB.txt 儲存使用者資料" << "\n" ;
        return ;
    }
    // 使用者總數
    fout << usercount << "\n" ;
    // 每位使用者資料
    for ( int i = 0 ; i < usercount ; i++ ){
        fout << users[i].username << " " << users[i].passwd   << " " << users[i].loginno  << " " << users[i].XAXBwin  << " " << users[i].XAXBlose << "\n" ;
    }
    fout.close() ;
}

//******************* 新增 *********************//
//================ 存取使用者資料 ==============//
int loadusersfromfile(user users[]){
    ifstream fin("userDB.txt", ios::in) ;
    if ( !fin ){
        // 檔案不存在
        return 0 ;
    }
    int count = 0 ;
    fin >> count ;  // 檔案第一行的 usercount
    if ( fin.fail() ){
        // 檔案格式錯誤
        fin.close() ;
        return 0 ;
    }
    // 依序讀取使用者資料
    for ( int i = 0 ; i < count ; i++ ){
        fin >> users[i].username >> users[i].passwd >> users[i].loginno >> users[i].XAXBwin >> users[i].XAXBlose ;
        if ( fin.fail() ){
            // 讀取失敗就中斷
            count = i ;
            break ;
        }
    }
    fin.close() ;
    return count ;
}

/************************************************************************
*                            XAXB 猜數字                                *
************************************************************************/

void sep(int n, int c[]) ;
int isValid(int n) ;
int guess(int p[]) ;
void match(int g, int a, int AB[]) ;

// 隨機產生 不重複四位數字
int randomanswer() ;

//******************* 新增 *********************//
//================= 人猜電腦 ===================//
int userguesscomputer(){
    int com_ans = randomanswer() ; // 電腦隨機產生 不重複的四位數
    int usertry = 0 ;  // 使用者猜的次數

    cout << "\n" << "=== 【人猜電腦】 ===" << "\n" ;

    int user_guess ;
    int AB[2] ; 

    while ( true ){
        // 輸入一個不重複四位數，給猜測答案
        cout << "輸入不重複四位數字(你的答案): " ;
        cin >> user_guess ;

        // 顯示答案
        if ( user_guess == 10000 ){
            cout << com_ans << "\n" ;
        }

        // 檢查格式
        if ( isValid(user_guess) == 0 ){
            cout << "格式錯誤，請重新輸入" << "\n" ;
            continue ;
        }

        usertry++ ; // 使用者猜次數加一

        // AB 數量
        match(user_guess, com_ans, AB) ;
        cout << "你猜的答案" << user_guess << " / " << AB[0] << "A" << AB[1] << "B" << "\n" ;
        
        // 全對
        if ( AB[0] == 4 ){
            cout << "\n" << "你猜對了" << "\n" ;
            break ;
        }
    }
    return usertry ; // 回傳次數
}


//=== 電腦猜人 ===//
int computerguessuser(){
    int comtry = 0 ;  // 電腦猜的次數

    cout << "=== 【電腦猜人】 ===" << "\n" ;
    int you_ans ; // 輸入一個不重複四位數，給電腦猜
    do {
        cout << "輸入不重複四位數字(給電腦的題目): " ;
        cin >> you_ans ;
    } while ( isValid( you_ans) == 0 ) ;

    int pool[10000] ;
    for ( int i = 0 ; i < 10000 ; i++ ){
        pool[i] = isValid(i) ;
    }

    int com_guess, com_AB[2], tmp_AB[2] ;
    while(true) {
        com_guess = guess(pool) ;

        comtry++ ; // 電腦猜次數加一

        match(com_guess, you_ans, com_AB) ;
        cout << "電腦猜的答案: " << com_guess << " / " << com_AB[0] << "A" << com_AB[1] << "B" << "\n" ;
        if( com_AB[0] == 4 ) {
            cout << "電腦猜中了數字" << "\n" ;
            break ;
        }
        for ( int i = 0 ; i < 10000;  i++ ){
            if (pool[i] == 1 ){
                match( com_guess, i, tmp_AB );
                if ( tmp_AB[0] != com_AB[0] || tmp_AB[1] != com_AB[1] ) {
                    pool[i] = 0 ;
                }
            }
        }
    }
    return comtry ; // 回傳次數
}

void sep(int n,int c[]){
    c[0] = n / 1000 ;
    c[1] = (n % 1000) / 100 ;
    c[2] = (n % 100) / 10 ;
    c[3] = n % 10 ;
}

int isValid(int n){
    if ( n >= 10000 || n < 0 ){
        return 0 ;
    }
    int d[4] ;
    sep(n, d) ;
    if(d[0] == d[1] || d[0] == d[2] || d[0] == d[3] || d[1] == d[2] || d[1] == d[3] || d[2] == d[3]) {
        return 0 ;
    }
    return 1 ;
}

int guess(int p[]){
    int i = 0 ;
    while (p[i] == 0){
        i++ ;
    }
    return i ;
}

void match(int g, int a, int AB[]){
    int gd[4], ad[4] ;
    sep(g, gd) ;
    sep(a, ad) ;
    AB[0] = 0 ;
    AB[1] = 0 ;

    for ( int m = 0 ; m < 4 ; m++ ){
        for ( int n = 0 ; n < 4 ; n++ ){
            if (gd[m] == ad[n]){
                if (m == n){
                    AB[0]++ ;
                }
                else{
                    AB[1]++ ;
                }
            }
        }
    }
}
//******************* 新增 *********************//
// 隨機產生 不重複的四位數
int randomanswer(){
    while (true){
        int x = rand() % 10000 ; 
        if (isValid(x)){
            return x ;
        }
    }
    return 0 ;
}

//******************* 新增 *********************//
void playXAXB(user &u){
    
    int comtry = computerguessuser() ; // 電腦猜人次數
    int usertry = userguesscomputer() ; // 人猜電腦次數

    // 使用者獲勝
    if ( usertry < comtry ){
        cout << "你猜了: " << usertry << " 次" << "\n" << "電腦猜了: " << comtry << " 次" << "\n" ;
        cout << "你獲勝了!" << "\n" ;
        u.XAXBwin++ ;
    }
    
    // 電腦獲勝
    if ( usertry > comtry ){
        cout << "你猜了: " << usertry << " 次" << "\n" << "電腦猜了: " << comtry << " 次" << "\n" ;
        cout << "電腦獲勝了!" << "\n" ;
        u.XAXBlose++ ;
    }

    // 平手
    if ( usertry == comtry ){
        cout << "你猜了: " << usertry << " 次" << "\n" << "電腦猜了: " << comtry << " 次" << "\n" ;
        cout << "平手" << "\n" ;
    }

    cout << "\n" << "【Enter】 回到主選單" << "\n" ;
    // 前一次輸入結束後尚殘留的換行等
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 清除上次輸入殘留
    cin.get() ;
}

/************************************************************************
 *                             電腦解數獨                                *
 ************************************************************************/

/*
*** 顯性單一候選法 (Naked Single) ***
概念:
顯性單一候選法是檢查某個格子中是否僅剩一個可能的候選數字。如果該格子只有一個可能的數字，那麼該數字就是此格子的唯一解。

方法:
對於每個空格子，檢查它有哪些數字可以填入（基於數獨規則：行、列和 3x3 區塊內不能重複）。
如果該格子中候選數字的數量為 1，則直接將這個數字填入。
更新該格子確定的數字，並同步更新其行、列和 3x3 區塊中其他格子的候選數字。

*** 隱性單一候選法 (Hidden Single) ***
概念:
隱性單一候選法是檢查某個行、列或 3x3 區塊中，某個數字是否只可能出現在某一個格子中。如果該數字只能出現在某一個格子，那麼該格子的值就是這個數字。

方法:
對於每個數字（1 到 9），逐一檢查：
行中是否有唯一的格子能填入這個數字。
列中是否有唯一的格子能填入這個數字。
如果找到唯一的格子，則將該數字填入並更新。
*/

void playsudoku() {
    cout << "=== 數獨解題題庫 ===" << "\n" << "有 3 題可選 (Q1.txt、Q2.txt、Q3.txt)" << "\n" ;

    int grid[9][9][10] ;

    // 使用者選擇要解哪一題
    int choice ;
    cout << "請選擇要解哪一題 ( 1 ~ 3 ): " ;
    cin >> choice ;

    // 根據選擇決定檔名
    string file ;
    switch( choice ){
        case 1:
            file = "Q1.txt" ;
            break ;
        case 2:
            file = "Q2.txt" ;
            break ;
        case 3:
            file = "Q3.txt" ;
            break ;
        default:
            cout << "沒有此選項" << "\n" ;
            break ;
    }

    // 更新函式
    auto update = [&](int row, int col, int val){
        // row, col 這格確定了 val，將同列、同欄、該 3x3 區塊內 val 的可能性清除
        for ( int c = 0 ; c < 9 ; c++ ){
            grid[row][c][val] = 0 ;
        }
        for ( int r = 0 ; r < 9 ; r++ ){
            grid[r][col][val] = 0 ;
        }
        // 該格其他數字的可能性清為 0
        for( int d = 1 ; d <= 9 ; d++ ){
            grid[row][col][d] = 0 ;
        }
        // 同 3x3 區塊
        int rs = (row / 3) * 3, cs = (col / 3) * 3 ;
        for( int r = rs ; r < rs + 3 ; r++ ){
            for ( int c = cs ; c < cs + 3 ; c++ ){
                grid[r][c][val] = 0 ;
            }
        }
        // 設定為確定值
        grid[row][col][0] = val ;
    } ;

    auto readgrid = [&](const string &filename){
        ifstream fin(filename) ;
        // 先將所有 [1...9] 的可能性設為 1
        for ( int r = 0 ; r < 9 ; r++ ){
            for ( int c = 0 ; c < 9 ; c++ ){
                for ( int d = 1 ; d <= 9 ; d++ ){
                    grid[r][c][d] = 1 ;
                }
                grid[r][c][0] = 0 ;
            }
        }
        // 讀取檔案中的固定數字
        for ( int r = 0 ; r < 9 ; r++ ){
            for ( int c = 0 ; c < 9 ; c++ ){
                int val ;
                fin >> val ;
                grid[r][c][0] = val ;
            }
        }
        fin.close() ;

        // 將檔案中所有的固定數字呼叫 update
        for (int r = 0 ; r < 9 ; r++ ){
            for ( int c = 0 ; c < 9 ; c++){
                int val = grid[r][c][0] ;
                if ( val != 0 ){
                    update(r, c, val) ;
                }
            }
        }
        return true ;
    } ;

    auto printGrid = [&](){
        for ( int r = 0 ; r < 9 ; r++ ){
            for ( int c = 0 ; c < 9 ; c++ ){
                if ( grid[r][c][0] > 0 ){
                    cout << grid[r][c][0] << " " ;
                }
                else {
                    cout << ". " ;
                }
            }
            cout << "\n" ;
        }
        cout << "\n" ;
    } ;

    //=== 顯性單一候選法 ===//
    auto testcell = [&](int R, int C){
        if ( grid[R][C][0] != 0 ){
            return 0 ;  // 已確定的格子直接返回
        }
        int possibilitycount = 0 ;
        int uniquenum = 0 ;
        for ( int num = 1 ; num <= 9 ; num++ ){
            if ( grid[R][C][num] == 1 ) {
                possibilitycount++ ;
                uniquenum = num ;
            }
        }
        if(possibilitycount == 1){
            return uniquenum ;
        }
        return 0 ;
    } ;

    //=== 隱性單一候選(row) ===//
    auto hiddensingleinrow = [&](int row){
        bool changed = false ;
        for( int val=1 ; val <= 9 ; val++ ){
            int possiblecol = -1 ;
            int countpossible = 0 ;
            for ( int c = 0 ; c < 9 ; c++ ){
                if ( grid[row][c][0] == 0 && grid[row][c][val] == 1 ){
                    countpossible++ ;
                    possiblecol = c ;
                }
            }
            if (countpossible == 1 && possiblecol != -1){
                update(row, possiblecol, val) ;
                changed = true ;
            }
        }
        return changed ;
    } ;

    //=== 隱性單一候選(col) ===//
    auto hiddensingleincol = [&](int col){
        bool changed = false ;
        for ( int val = 1 ; val <= 9 ; val++ ){
            int possibleRow = -1 ;
            int countpossible = 0 ;
            for( int r = 0 ; r < 9 ; r++ ){
                if( grid[r][col][0] == 0 && grid[r][col][val] == 1 ){
                    countpossible++ ;
                    possibleRow = r ;
                }
            }
            if( countpossible == 1 && possibleRow != -1 ){
                update(possibleRow, col, val) ;
                changed = true ;
            }
        }
        return changed ;
    } ;

    // 同時跑 row + col
    auto applyhiddensingles = [&](){
        bool changedall = false ;
        for ( int r = 0 ; r < 9 ; r++ ){
            if (hiddensingleinrow(r)){
                changedall = true ;
            }
        }
        for ( int c = 0 ; c < 9 ; c++ ){
            if (hiddensingleincol(c)){
                changedall = true ;
            }
        }
        return changedall ;
    } ;

    // 解數獨主程式
    auto solvesudoku = [&](){
        while (true){
            bool updated = false ;
            //  顯性單一候選
            for ( int r=0 ; r < 9 ; r++ ){
                for( int c=0 ; c < 9 ; c++ ){
                    if ( grid[r][c][0] == 0 ){
                        int num = testcell(r, c) ;
                        if ( num > 0 ){
                            update(r, c, num) ;
                            updated = true ;
                        }
                    }
                }
            }
            // 隱性單一候選
            if (!updated){
                bool changedhidden = applyhiddensingles() ;
                if (changedhidden){
                    updated = true ;
                }
            }
            // 若本輪沒有更新任何格子，則結束
            if (!updated){
                break ;
            }
        }
    } ;

    //  顯示初始狀況
    if(!readgrid(file)) {
        cout << "無法正確讀取 " << file << "，返回主選單" << "\n" ;
        return;
    }

    cout << "讀取後的初始盤面 (" << file << ")" << "\n" ;
    printGrid() ;

    // 使用者按 Enter 再開始解題
    cout << "【Enter】 開始解題" ;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cin.get(); // 再次讀取(防止前面輸入時殘留的換行)

    // 開始解題
    solvesudoku() ;

    cout << "解題後的盤面" << "\n" ;
    printGrid() ;

    cout << "數獨結束" << "\n" << "【Enter】 返回主選單" << "\n" ;
    cin.get() ;
}

/************************************************************************
 *                                聊天室                                 *
 ************************************************************************/

//=== 聊天室 ===//
/* 更改內容:
1. 使用者介面優化
2. 記錄下訊息傳送時的時間
*/
void Chatroom_Main(const char username[]){

    // 時間匯入
    time_t now = time ( 0 ) ;
    char *now_time = ctime ( & now ) ;

	ifstream fin ;
	ofstream fout ;
	char str[1000] ;
	char input[100] ;
	do {
		system("cls") ;
		fin.open("msg.txt") ;
        cout << "=== 進入聊天室 ===" << "\n" << "(離開請輸入【Exit】)" << "\n" ;
		while ( fin.getline(str, 500) ){
			cout << str << "\n" ;
        }
		fin.close() ;
        cout << username << ": " ;
		cin.getline(input, 100) ;
		if ( strcmp(input, "Exit") != 0 && strcmp(input, " ") != 0 ){
			fout.open("msg.txt",ios::app) ;
			fout << username << ": "<< input << "\n" << now_time << "\n" ;
			fout.close() ;
		}
        if ( strcmp(input, "Exit") == 0 ){
            fout.open("msg.txt",ios::app) ;
			fout << username << ": 已離開聊天室 " << "\n" << now_time << "\n" ;
			fout.close() ;
        }
	} while ( strcmp(input,"Exit")!=0 ) ;
}

/************************************************************************
 *                             勇者地下城                                *
 ************************************************************************/

// 猜拳選項
const string CHOICES[] = {"剪刀", "石頭", "布"} ;

// 隨機骰子 ( 1 ~ 6 )
int rolldice() {
    return rand() % 6 + 1 ;
}

// 猜拳判定: 0 = 平手, 1 = 玩家贏, 2 = 電腦贏
int rockpaperscissors(int player, int computer){
    if (player == computer){
        return 0 ;
    }
    if ((player == 0 && computer == 2) || (player == 1 && computer == 0) || (player == 2 && computer == 1)){
        return 1 ;
    }
    return 2 ;
}

// 主遊戲流程
void playgame(){
    srand(time(NULL)) ;

    // 玩家血量
    int playerhealth = 20 ;

    cout << "=== 歡迎來到勇者地下城 ===" << "\n" ;

    while (playerhealth > 0) {
        // 怪物血量
        int monsterhealth = 5 ;
        
        cout << "\n" << "新的一隻怪物出現" << "\n" ;

        while (playerhealth > 0 && monsterhealth > 0) { // 玩家和怪物都存活著
            int playerchoice ;
            // 猜拳
            cout << "\n" << "請選擇出拳 (0: 剪刀、 1: 石頭、 2: 布): "<< "\n" ;
            cin >> playerchoice ;

            if (playerchoice < 0 || playerchoice > 2) { // 判斷是否出剪刀、石頭、布
                cout << "無效選擇，請重新輸入" << "\n" ;
                continue ;
            }

            int computerChoice = rand() % 3 ;  // 電腦隨機選擇
            cout << "玩家: " << CHOICES[playerchoice] << " vs 電腦: " << CHOICES[computerChoice] << "\n" ;

            int result = rockpaperscissors(playerchoice, computerChoice) ;
            if (result == 0) {
                cout << "平手，再來一次" << "\n" ;
                continue ;
            }

            // 玩家贏，進行玩家回合
            if (result == 1) {
                int action ;
                cout << "玩家贏，輪到玩家行動" << "\n" ;
                cout << "選擇行動 (1: 攻擊， 2: 回血): " << "\n" ;
                cin >> action ;

                if (action == 1) {  // 攻擊
                    int damage = rolldice() ;
                    monsterhealth = monsterhealth - damage ;
                    cout << "玩家攻擊怪物造成 " << damage << " 點傷害" << "\n" ;
                    if (monsterhealth <= 0) {
                        cout << "怪物被打敗了" << "\n" ;
                        break ;
                    }
                }
                else if (action == 2) {  // 回血
                    int heal = rolldice() ;
                    playerhealth = playerhealth + heal ;
                    cout << "玩家回復了 " << heal << " 點血量" << "\n" ;
                }
                else {
                    cout << "結印失敗，沒有任何事情發生" << "\n" ;
                }
            }

            // 電腦贏，怪物攻擊
            if (result == 2) {
                int damage = rolldice() ;
                cout << "電腦贏，怪物攻擊玩家" <<  "\n" ;
                playerhealth = playerhealth - damage ;
                cout << "怪物攻擊玩家造成 " << damage << " 點傷害" << "\n" ;
                if (playerhealth <= 0) {
                    cout << "玩家被打敗了" << "\n" ;
                    break ;
                }
            }

            // 顯示雙方血量
            cout << "玩家血量: " << playerhealth << "， 怪物血量: " << monsterhealth << "\n" ;
        }

        // 問玩家是否繼續挑戰
        cout << "是否繼續挑戰下一隻怪物? (1: 繼續, 0: 放棄): " << "\n" ;
        int choice ;
        cin >> choice ;
        if (choice == 0) {
            cout << "玩家選擇放棄遊戲" << "\n" ;
            break ;
        }
        // 玩家血量歸零，結束遊戲
        if (playerhealth <= 0) {
            cout << "你輸了!!!" << "\n" ;
            cout << "【Enter】 回到主選單";
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cin.get(); // 再次讀取(防止前面輸入時殘留的換行)
            break ;
        }
    }
}


/************************************************************************
 *                             主要程式                                  *
 ************************************************************************/
int main(){
    // 匯入已有的使用者資料
    user users[100] ;
    int usercount = loadusersfromfile(users) ;

    // 登入註冊
    int currentindex = -1 ; // 目前登入者在 users[] 中的 index
    while ( true ){
        cout << "********** Login **********"<< "\n" << "\n" << "  請先【登入】或【註冊】" << "\n" << "  ( 輸入【new】即可註冊 )" << "\n" << "\n" << "***************************" << "\n" ;
        cout << "使用者帳號: " ;
        char tmpusername[20] ;
        cin >> tmpusername ;

        if ( strcmp(tmpusername, "new") == 0 ){
            // 建新帳號
            if ( newuser(users, usercount) ){
                // 新增帳號成功之後，新帳號就位於 users[usercount-1]
                currentindex = usercount - 1 ;
                break ;
            } 
            else{
                continue ; 
            }
        }
        else{
            cout << "使用者密碼: " ;
            char tmppasswd[20] ;
            cin >> tmppasswd ;

            // 帳號密碼格式檢查
            if ( !checkusername(tmpusername) || !checkpassword(tmppasswd) ){
                cout << "帳密格式錯誤，請重新輸入" << "\n" ;
                continue ;
            }
            // 判斷是否存在此帳號
            int i ;
            for ( i = 0 ; i < usercount ; i++ ){
                if ( strcmp(users[i].username, tmpusername) == 0 ){
                    if ( strcmp(users[i].passwd, tmppasswd) == 0 ){
                        currentindex = i ;
                    }
                    else {
                        cout << "密碼錯誤，請重新輸入" << "\n" << "\n" ;
                    }
                    break ;
                }
            }
            // 若 i == usercount 表示帳號不存在
            if ( i == usercount ){
                cout << "找不到該使用者，請重新輸入" << "\n" << "\n" ;
            }
            // 若找到且密碼正確 currentindex = i 就離開
            if ( currentindex != -1 ){
                break ;
            }
        }
    }

    // 登入成功，更新 login 次數
    users[currentindex].loginno++ ;

/************************************************************************
 *                                主選單                                *
 ************************************************************************/
    // 主選單
    while ( true ){
        system("cls") ;
        cout << "************************************" << "\n"
             << users[currentindex].username << ", 您好!" << "\n"
             << "[1] XAXB 猜數字" << "\n"
             << "[2] 聊天室" << "\n"
             << "[3] 電腦解數獨" << "\n"
             << "[4] 查詢個人資料" << "\n"
             << "[5] 變更密碼" << "\n"
             << "[6] 勇者地下城" << "\n"
             << "[0] 登出並離開" << "\n"
             << "************************************" << "\n"
             << "請選擇: " ;

        int select ;
        cin >> select ;
        switch ( select ){
            case 1:
                playXAXB(users[currentindex]) ;
                break ;
            case 2:
                Chatroom_Main(users[currentindex].username) ;
                break ;
            case 3:
                playsudoku() ;
                break ;
            case 4:{
                cout << "\n" << "=== 目前帳號資訊 ===" << "\n" ;
                cout << "帳號: " << users[currentindex].username << "\n" ;
                cout << "登入次數: " << users[currentindex].loginno << "\n" ;
                cout << "XAXB 勝場: " << users[currentindex].XAXBwin << "\n" ;
                cout << "XAXB 敗場: " << users[currentindex].XAXBlose << "\n" ;
                cout << "\n" << "【Enter】 返回主選單" ;
                // 前一次輸入結束後尚殘留的換行等
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n') ;
                cin.get() ;
            }
            break ;
            case 5:{
                cout << "\n" << "=== 變更密碼 ===" << "\n" ;
                char oldpass[20], newpass_1[20], newpass_2[20] ;
                cout << "請輸入舊密碼: " ;
                cin >> oldpass ;
                // 確認舊密碼正確
                if ( strcmp(oldpass, users[currentindex].passwd) != 0 ){
                    cout << "舊密碼不正確，返回主選單" << "\n" ;
                    break ;
                }
                // 輸入新密碼兩次
                while ( true ){
                    cout << "請輸入新密碼: " ;
                    cin >> newpass_1 ;
                    cout << "請再次輸入新密碼: " ;
                    cin >> newpass_2 ;
                    if ( strcmp(newpass_1, newpass_2) != 0 ){
                        cout << "兩次輸入不一致，請重新輸入" << "\n" ;
                        continue ;
                    }
                    if ( !checkpassword(newpass_1) ){
                        cout << "新密碼不符合格式，請重新輸入" << "\n" ;
                        continue ;
                    }
                    // 成功更改密碼
                    strcpy(users[currentindex].passwd, newpass_1) ;
                    cout << "密碼變更成功！" << "\n" ;
                    break ;
                }
            }
            break ;
            case 6:
                playgame() ;
                break ;
            case 0:
                // 登出並離開
                cout << "\n" << "已登出" << "\n" ;
                // 離開存檔
                saveuserstofile(users, usercount) ;
                return 0 ;
            default:
                cout << "沒有此選項" << "\n" ;
                break ;
        }
    }
    return 0 ;
}

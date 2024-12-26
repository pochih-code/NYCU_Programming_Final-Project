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
*                             Login�t��                                 *
************************************************************************/

//=== �ˬd�ϥΪ̱b��(�b���n�D 3 �X�H�W �j�p�g�^�� �� �Ʀr�^ ===//
/* ��鷺�e:
1. �ܼƦW��
2. �N�쥻 flag �P�_�O�D��H�����^�� true �� false
*/
bool checkusername(const char u[]){
    int n = strlen(u) ;
    // �ˬd���� 3 �X�H�W
    if ( n < 3 ){
        return false ;
    }
    // �ˬd�b���C�@�Ӧr
    for (int i = 0 ; i < n ; i++){
                    // �O�_���Ʀr                   // �O�_���p�g�^��r��            // �O�_���j�g�^��r��
        if (!((u[i] >= '0' && u[i] <= '9') || (u[i] >= 'A' && u[i] <= 'Z') || (u[i] >= 'a' && u[i] <= 'z'))){
            return false;
        }
    }
    return true;
}

//=== �ˬd�ϥΪ̱K�X( �K�X�n�D�� 3 �X�H�W �j�p�g�^�� �� �Ʀr �A���ݦP�ɥ]�t �Ʀr �� �^�� ) ===//
/* ��鷺�e:
1. �ܼƦW��
2. �N�쥻 flag �P�_�O�D��H�� digit �M alpha �Ӫ�ܬO�D 
*/
bool checkpassword(const char p[]){
	int n = strlen(p) ;
	bool digit = false ; // �O�_���Ʀr
	bool alpha = false ; // �O�_���r��

	// �ˬd���� 3 �X�H�W
	if ( n < 3 ){
		return false ;
	}
	// �ˬd�K�X�C�@�Ӧr
	for ( int i = 0 ; i < n ; i++ ){
		// �O�_���Ʀr
		if ( p[i] >= '0' && p[i] <= '9' ){
			digit = true ;
		}
		// �O�_���p�g�^��r��
		if ( p[i] >= 'a' && p[i] <= 'z' ){
			alpha = true ;
		}
		// �O�_���j�g�^��r��
		if ( p[i] >= 'A' && p[i] <= 'Z' ){
		}
	}
	// �Y �S���Ʀr �� �S���^��r�� �h�^�� false
	if (!digit || !alpha){
		return false ;
	}

	return true ;
}

//=== �ˬd�ϥΪ̱b���O�_���Q�ϥ� ===//
/* ��鷺�e:
1. �ܼƦW��
2. �N�쥻 flag �P�_�O�D��H�����^�� true �� false
*/
bool available(user users[], int usercount, const char u[]){

	for ( int i = 0 ; i < usercount ; i++ ){
		// �b���ۦP�ɡA�^�� false
		if ( strcmp(users[i].username, u) == 0 ){
			return false ;
		}
	}
	return true ;
}

//=== �s�W�ϥΪ� ===//
/* ��鷺�e:
1. �ܼƦW��
2. �N�쥻 flag �P�_�O�D��H�����^�� true �� false
*/
bool newuser(user users[], int &usercount) {
    char newname[20] ;    // �s�b��
    char newpass_1[20] ;  // �Ĥ@����J�K�X
    char newpass_2[20] ;  // �A���T�{��J�K�X

    cout << "=== �s�W�ϥΪ̱b�� ===" << "\n" ;

    // ���ƭn�D��J�b���A����ŦX�W�w
    while ( true ){
        cout << "�п�J�s�b��: " ;
        cin >> newname ; // Ū���ϥΪ̱b��
        // �ˬd�ϥΪ̱b���榡
        if ( !checkusername(newname) ){
            cout << "�b�����ŦX�榡�A�Э��s��J" << "\n" ;
            continue;
        }
        // �ˬd�ϥΪ̱b�����Ʃ�
        if ( !available(users, usercount, newname) ){
            cout << "�b���w�s�b�A�Э��s��J" << "\n" ;
            continue ;
        }
        break ;
    }

    // ���ƭn�D��J�K�X�A����⦸���ۦP�M�ŦX�W�w
    while ( true ){
        cout << "�п�J�K�X: " ;
        cin >> newpass_1 ;
        cout << "�ЦA����J�K�X: " ;
        cin >> newpass_2 ;

        // �ˬd�G���K�X�O�_�ۦP
        if ( strcmp(newpass_1, newpass_2) != 0 ) {
            cout << "�⦸�K�X��J���@�P�A�Э��s��J" << "\n" ;
            continue ;
        }
        // �ˬd�K�X�O�_�ŦX�榡
        if ( !checkpassword(newpass_1) ) {
            cout << "�K�X���ŦX�榡�A�Э��s��J" << "\n" ;
            continue ;
        }
        break;
    }

    // �g�J userDB.txt
    strcpy(users[usercount].username, newname) ;
    strcpy(users[usercount].passwd, newpass_1) ;
    users[usercount].loginno = 0 ;
    users[usercount].XAXBwin  = 0 ;
    users[usercount].XAXBlose = 0 ;
    usercount++ ;

    cout << "�z���s�b�� ** " << newname << " ** �إߦ��\�I" << "\n" ;
    return true ;
}

//******************* �s�W *********************//
//================ �s���ϥΪ̸�� ==============//
void saveuserstofile(user users[], int usercount){
    ofstream fout("userDB.txt", ios::out) ;
    if ( !fout ) {
        cout << "�L�k�}�� userDB.txt �x�s�ϥΪ̸��" << "\n" ;
        return ;
    }
    // �ϥΪ��`��
    fout << usercount << "\n" ;
    // �C��ϥΪ̸��
    for ( int i = 0 ; i < usercount ; i++ ){
        fout << users[i].username << " " << users[i].passwd   << " " << users[i].loginno  << " " << users[i].XAXBwin  << " " << users[i].XAXBlose << "\n" ;
    }
    fout.close() ;
}

//******************* �s�W *********************//
//================ �s���ϥΪ̸�� ==============//
int loadusersfromfile(user users[]){
    ifstream fin("userDB.txt", ios::in) ;
    if ( !fin ){
        // �ɮפ��s�b
        return 0 ;
    }
    int count = 0 ;
    fin >> count ;  // �ɮײĤ@�檺 usercount
    if ( fin.fail() ){
        // �ɮ׮榡���~
        fin.close() ;
        return 0 ;
    }
    // �̧�Ū���ϥΪ̸��
    for ( int i = 0 ; i < count ; i++ ){
        fin >> users[i].username >> users[i].passwd >> users[i].loginno >> users[i].XAXBwin >> users[i].XAXBlose ;
        if ( fin.fail() ){
            // Ū�����ѴN���_
            count = i ;
            break ;
        }
    }
    fin.close() ;
    return count ;
}

/************************************************************************
*                            XAXB �q�Ʀr                                *
************************************************************************/

void sep(int n, int c[]) ;
int isValid(int n) ;
int guess(int p[]) ;
void match(int g, int a, int AB[]) ;

// �H������ �����ƥ|��Ʀr
int randomanswer() ;

//******************* �s�W *********************//
//================= �H�q�q�� ===================//
int userguesscomputer(){
    int com_ans = randomanswer() ; // �q���H������ �����ƪ��|���
    int usertry = 0 ;  // �ϥΪ̲q������

    cout << "\n" << "=== �i�H�q�q���j ===" << "\n" ;

    int user_guess ;
    int AB[2] ; 

    while ( true ){
        // ��J�@�Ӥ����ƥ|��ơA���q������
        cout << "��J�����ƥ|��Ʀr(�A������): " ;
        cin >> user_guess ;

        // ��ܵ���
        if ( user_guess == 10000 ){
            cout << com_ans << "\n" ;
        }

        // �ˬd�榡
        if ( isValid(user_guess) == 0 ){
            cout << "�榡���~�A�Э��s��J" << "\n" ;
            continue ;
        }

        usertry++ ; // �ϥΪ̲q���ƥ[�@

        // AB �ƶq
        match(user_guess, com_ans, AB) ;
        cout << "�A�q������" << user_guess << " / " << AB[0] << "A" << AB[1] << "B" << "\n" ;
        
        // ����
        if ( AB[0] == 4 ){
            cout << "\n" << "�A�q��F" << "\n" ;
            break ;
        }
    }
    return usertry ; // �^�Ǧ���
}


//=== �q���q�H ===//
int computerguessuser(){
    int comtry = 0 ;  // �q���q������

    cout << "=== �i�q���q�H�j ===" << "\n" ;
    int you_ans ; // ��J�@�Ӥ����ƥ|��ơA���q���q
    do {
        cout << "��J�����ƥ|��Ʀr(���q�����D��): " ;
        cin >> you_ans ;
    } while ( isValid( you_ans) == 0 ) ;

    int pool[10000] ;
    for ( int i = 0 ; i < 10000 ; i++ ){
        pool[i] = isValid(i) ;
    }

    int com_guess, com_AB[2], tmp_AB[2] ;
    while(true) {
        com_guess = guess(pool) ;

        comtry++ ; // �q���q���ƥ[�@

        match(com_guess, you_ans, com_AB) ;
        cout << "�q���q������: " << com_guess << " / " << com_AB[0] << "A" << com_AB[1] << "B" << "\n" ;
        if( com_AB[0] == 4 ) {
            cout << "�q���q���F�Ʀr" << "\n" ;
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
    return comtry ; // �^�Ǧ���
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
//******************* �s�W *********************//
// �H������ �����ƪ��|���
int randomanswer(){
    while (true){
        int x = rand() % 10000 ; 
        if (isValid(x)){
            return x ;
        }
    }
    return 0 ;
}

//******************* �s�W *********************//
void playXAXB(user &u){
    
    int comtry = computerguessuser() ; // �q���q�H����
    int usertry = userguesscomputer() ; // �H�q�q������

    // �ϥΪ����
    if ( usertry < comtry ){
        cout << "�A�q�F: " << usertry << " ��" << "\n" << "�q���q�F: " << comtry << " ��" << "\n" ;
        cout << "�A��ӤF!" << "\n" ;
        u.XAXBwin++ ;
    }
    
    // �q�����
    if ( usertry > comtry ){
        cout << "�A�q�F: " << usertry << " ��" << "\n" << "�q���q�F: " << comtry << " ��" << "\n" ;
        cout << "�q����ӤF!" << "\n" ;
        u.XAXBlose++ ;
    }

    // ����
    if ( usertry == comtry ){
        cout << "�A�q�F: " << usertry << " ��" << "\n" << "�q���q�F: " << comtry << " ��" << "\n" ;
        cout << "����" << "\n" ;
    }

    cout << "\n" << "�iEnter�j �^��D���" << "\n" ;
    // �e�@����J������|�ݯd�����浥
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // �M���W����J�ݯd
    cin.get() ;
}

/************************************************************************
 *                             �q���ѼƿW                                *
 ************************************************************************/

/*
*** ��ʳ�@�Կ�k (Naked Single) ***
����:
��ʳ�@�Կ�k�O�ˬd�Y�Ӯ�l���O�_�ȳѤ@�ӥi�઺�Կ�Ʀr�C�p�G�Ӯ�l�u���@�ӥi�઺�Ʀr�A����ӼƦr�N�O����l���ߤ@�ѡC

��k:
���C�ӪŮ�l�A�ˬd�������ǼƦr�i�H��J�]���ƿW�W�h�G��B�C�M 3x3 �϶������୫�ơ^�C
�p�G�Ӯ�l���Կ�Ʀr���ƶq�� 1�A�h�����N�o�ӼƦr��J�C
��s�Ӯ�l�T�w���Ʀr�A�æP�B��s���B�C�M 3x3 �϶�����L��l���Կ�Ʀr�C

*** ���ʳ�@�Կ�k (Hidden Single) ***
����:
���ʳ�@�Կ�k�O�ˬd�Y�Ӧ�B�C�� 3x3 �϶����A�Y�ӼƦr�O�_�u�i��X�{�b�Y�@�Ӯ�l���C�p�G�ӼƦr�u��X�{�b�Y�@�Ӯ�l�A����Ӯ�l���ȴN�O�o�ӼƦr�C

��k:
���C�ӼƦr�]1 �� 9�^�A�v�@�ˬd�G
�椤�O�_���ߤ@����l���J�o�ӼƦr�C
�C���O�_���ߤ@����l���J�o�ӼƦr�C
�p�G���ߤ@����l�A�h�N�ӼƦr��J�ç�s�C
*/

void playsudoku() {
    cout << "=== �ƿW���D�D�w ===" << "\n" << "�� 3 �D�i�� (Q1.txt�BQ2.txt�BQ3.txt)" << "\n" ;

    int grid[9][9][10] ;

    // �ϥΪ̿�ܭn�ѭ��@�D
    int choice ;
    cout << "�п�ܭn�ѭ��@�D ( 1 ~ 3 ): " ;
    cin >> choice ;

    // �ھڿ�ܨM�w�ɦW
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
            cout << "�S�����ﶵ" << "\n" ;
            break ;
    }

    // ��s�禡
    auto update = [&](int row, int col, int val){
        // row, col �o��T�w�F val�A�N�P�C�B�P��B�� 3x3 �϶��� val ���i��ʲM��
        for ( int c = 0 ; c < 9 ; c++ ){
            grid[row][c][val] = 0 ;
        }
        for ( int r = 0 ; r < 9 ; r++ ){
            grid[r][col][val] = 0 ;
        }
        // �Ӯ��L�Ʀr���i��ʲM�� 0
        for( int d = 1 ; d <= 9 ; d++ ){
            grid[row][col][d] = 0 ;
        }
        // �P 3x3 �϶�
        int rs = (row / 3) * 3, cs = (col / 3) * 3 ;
        for( int r = rs ; r < rs + 3 ; r++ ){
            for ( int c = cs ; c < cs + 3 ; c++ ){
                grid[r][c][val] = 0 ;
            }
        }
        // �]�w���T�w��
        grid[row][col][0] = val ;
    } ;

    auto readgrid = [&](const string &filename){
        ifstream fin(filename) ;
        // ���N�Ҧ� [1...9] ���i��ʳ]�� 1
        for ( int r = 0 ; r < 9 ; r++ ){
            for ( int c = 0 ; c < 9 ; c++ ){
                for ( int d = 1 ; d <= 9 ; d++ ){
                    grid[r][c][d] = 1 ;
                }
                grid[r][c][0] = 0 ;
            }
        }
        // Ū���ɮפ����T�w�Ʀr
        for ( int r = 0 ; r < 9 ; r++ ){
            for ( int c = 0 ; c < 9 ; c++ ){
                int val ;
                fin >> val ;
                grid[r][c][0] = val ;
            }
        }
        fin.close() ;

        // �N�ɮפ��Ҧ����T�w�Ʀr�I�s update
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

    //=== ��ʳ�@�Կ�k ===//
    auto testcell = [&](int R, int C){
        if ( grid[R][C][0] != 0 ){
            return 0 ;  // �w�T�w����l������^
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

    //=== ���ʳ�@�Կ�(row) ===//
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

    //=== ���ʳ�@�Կ�(col) ===//
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

    // �P�ɶ] row + col
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

    // �ѼƿW�D�{��
    auto solvesudoku = [&](){
        while (true){
            bool updated = false ;
            //  ��ʳ�@�Կ�
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
            // ���ʳ�@�Կ�
            if (!updated){
                bool changedhidden = applyhiddensingles() ;
                if (changedhidden){
                    updated = true ;
                }
            }
            // �Y�����S����s�����l�A�h����
            if (!updated){
                break ;
            }
        }
    } ;

    //  ��ܪ�l���p
    if(!readgrid(file)) {
        cout << "�L�k���TŪ�� " << file << "�A��^�D���" << "\n" ;
        return;
    }

    cout << "Ū���᪺��l�L�� (" << file << ")" << "\n" ;
    printGrid() ;

    // �ϥΪ̫� Enter �A�}�l���D
    cout << "�iEnter�j �}�l���D" ;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cin.get(); // �A��Ū��(����e����J�ɴݯd������)

    // �}�l���D
    solvesudoku() ;

    cout << "���D�᪺�L��" << "\n" ;
    printGrid() ;

    cout << "�ƿW����" << "\n" << "�iEnter�j ��^�D���" << "\n" ;
    cin.get() ;
}

/************************************************************************
 *                                ��ѫ�                                 *
 ************************************************************************/

//=== ��ѫ� ===//
/* ��鷺�e:
1. �ϥΪ̤����u��
2. �O���U�T���ǰe�ɪ��ɶ�
*/
void Chatroom_Main(const char username[]){

    // �ɶ��פJ
    time_t now = time ( 0 ) ;
    char *now_time = ctime ( & now ) ;

	ifstream fin ;
	ofstream fout ;
	char str[1000] ;
	char input[100] ;
	do {
		system("cls") ;
		fin.open("msg.txt") ;
        cout << "=== �i�J��ѫ� ===" << "\n" << "(���}�п�J�iExit�j)" << "\n" ;
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
			fout << username << ": �w���}��ѫ� " << "\n" << now_time << "\n" ;
			fout.close() ;
        }
	} while ( strcmp(input,"Exit")!=0 ) ;
}

/************************************************************************
 *                             �i�̦a�U��                                *
 ************************************************************************/

// �q���ﶵ
const string CHOICES[] = {"�ŤM", "���Y", "��"} ;

// �H����l ( 1 ~ 6 )
int rolldice() {
    return rand() % 6 + 1 ;
}

// �q���P�w: 0 = ����, 1 = ���aĹ, 2 = �q��Ĺ
int rockpaperscissors(int player, int computer){
    if (player == computer){
        return 0 ;
    }
    if ((player == 0 && computer == 2) || (player == 1 && computer == 0) || (player == 2 && computer == 1)){
        return 1 ;
    }
    return 2 ;
}

// �D�C���y�{
void playgame(){
    srand(time(NULL)) ;

    // ���a��q
    int playerhealth = 20 ;

    cout << "=== �w��Ө�i�̦a�U�� ===" << "\n" ;

    while (playerhealth > 0) {
        // �Ǫ���q
        int monsterhealth = 5 ;
        
        cout << "\n" << "�s���@���Ǫ��X�{" << "\n" ;

        while (playerhealth > 0 && monsterhealth > 0) { // ���a�M�Ǫ����s����
            int playerchoice ;
            // �q��
            cout << "\n" << "�п�ܥX�� (0: �ŤM�B 1: ���Y�B 2: ��): "<< "\n" ;
            cin >> playerchoice ;

            if (playerchoice < 0 || playerchoice > 2) { // �P�_�O�_�X�ŤM�B���Y�B��
                cout << "�L�Ŀ�ܡA�Э��s��J" << "\n" ;
                continue ;
            }

            int computerChoice = rand() % 3 ;  // �q���H�����
            cout << "���a: " << CHOICES[playerchoice] << " vs �q��: " << CHOICES[computerChoice] << "\n" ;

            int result = rockpaperscissors(playerchoice, computerChoice) ;
            if (result == 0) {
                cout << "����A�A�Ӥ@��" << "\n" ;
                continue ;
            }

            // ���aĹ�A�i�檱�a�^�X
            if (result == 1) {
                int action ;
                cout << "���aĹ�A���쪱�a���" << "\n" ;
                cout << "��ܦ�� (1: �����A 2: �^��): " << "\n" ;
                cin >> action ;

                if (action == 1) {  // ����
                    int damage = rolldice() ;
                    monsterhealth = monsterhealth - damage ;
                    cout << "���a�����Ǫ��y�� " << damage << " �I�ˮ`" << "\n" ;
                    if (monsterhealth <= 0) {
                        cout << "�Ǫ��Q���ѤF" << "\n" ;
                        break ;
                    }
                }
                else if (action == 2) {  // �^��
                    int heal = rolldice() ;
                    playerhealth = playerhealth + heal ;
                    cout << "���a�^�_�F " << heal << " �I��q" << "\n" ;
                }
                else {
                    cout << "���L���ѡA�S������Ʊ��o��" << "\n" ;
                }
            }

            // �q��Ĺ�A�Ǫ�����
            if (result == 2) {
                int damage = rolldice() ;
                cout << "�q��Ĺ�A�Ǫ��������a" <<  "\n" ;
                playerhealth = playerhealth - damage ;
                cout << "�Ǫ��������a�y�� " << damage << " �I�ˮ`" << "\n" ;
                if (playerhealth <= 0) {
                    cout << "���a�Q���ѤF" << "\n" ;
                    break ;
                }
            }

            // ��������q
            cout << "���a��q: " << playerhealth << "�A �Ǫ���q: " << monsterhealth << "\n" ;
        }

        // �ݪ��a�O�_�~��D��
        cout << "�O�_�~��D�ԤU�@���Ǫ�? (1: �~��, 0: ���): " << "\n" ;
        int choice ;
        cin >> choice ;
        if (choice == 0) {
            cout << "���a��ܩ��C��" << "\n" ;
            break ;
        }
        // ���a��q�k�s�A�����C��
        if (playerhealth <= 0) {
            cout << "�A��F!!!" << "\n" ;
            cout << "�iEnter�j �^��D���";
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cin.get(); // �A��Ū��(����e����J�ɴݯd������)
            break ;
        }
    }
}


/************************************************************************
 *                             �D�n�{��                                  *
 ************************************************************************/
int main(){
    // �פJ�w�����ϥΪ̸��
    user users[100] ;
    int usercount = loadusersfromfile(users) ;

    // �n�J���U
    int currentindex = -1 ; // �ثe�n�J�̦b users[] ���� index
    while ( true ){
        cout << "********** Login **********"<< "\n" << "\n" << "  �Х��i�n�J�j�Ρi���U�j" << "\n" << "  ( ��J�inew�j�Y�i���U )" << "\n" << "\n" << "***************************" << "\n" ;
        cout << "�ϥΪ̱b��: " ;
        char tmpusername[20] ;
        cin >> tmpusername ;

        if ( strcmp(tmpusername, "new") == 0 ){
            // �طs�b��
            if ( newuser(users, usercount) ){
                // �s�W�b�����\����A�s�b���N��� users[usercount-1]
                currentindex = usercount - 1 ;
                break ;
            } 
            else{
                continue ; 
            }
        }
        else{
            cout << "�ϥΪ̱K�X: " ;
            char tmppasswd[20] ;
            cin >> tmppasswd ;

            // �b���K�X�榡�ˬd
            if ( !checkusername(tmpusername) || !checkpassword(tmppasswd) ){
                cout << "�b�K�榡���~�A�Э��s��J" << "\n" ;
                continue ;
            }
            // �P�_�O�_�s�b���b��
            int i ;
            for ( i = 0 ; i < usercount ; i++ ){
                if ( strcmp(users[i].username, tmpusername) == 0 ){
                    if ( strcmp(users[i].passwd, tmppasswd) == 0 ){
                        currentindex = i ;
                    }
                    else {
                        cout << "�K�X���~�A�Э��s��J" << "\n" << "\n" ;
                    }
                    break ;
                }
            }
            // �Y i == usercount ��ܱb�����s�b
            if ( i == usercount ){
                cout << "�䤣��ӨϥΪ̡A�Э��s��J" << "\n" << "\n" ;
            }
            // �Y���B�K�X���T currentindex = i �N���}
            if ( currentindex != -1 ){
                break ;
            }
        }
    }

    // �n�J���\�A��s login ����
    users[currentindex].loginno++ ;

/************************************************************************
 *                                �D���                                *
 ************************************************************************/
    // �D���
    while ( true ){
        system("cls") ;
        cout << "************************************" << "\n"
             << users[currentindex].username << ", �z�n!" << "\n"
             << "[1] XAXB �q�Ʀr" << "\n"
             << "[2] ��ѫ�" << "\n"
             << "[3] �q���ѼƿW" << "\n"
             << "[4] �d�߭ӤH���" << "\n"
             << "[5] �ܧ�K�X" << "\n"
             << "[6] �i�̦a�U��" << "\n"
             << "[0] �n�X�����}" << "\n"
             << "************************************" << "\n"
             << "�п��: " ;

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
                cout << "\n" << "=== �ثe�b����T ===" << "\n" ;
                cout << "�b��: " << users[currentindex].username << "\n" ;
                cout << "�n�J����: " << users[currentindex].loginno << "\n" ;
                cout << "XAXB �ӳ�: " << users[currentindex].XAXBwin << "\n" ;
                cout << "XAXB �ѳ�: " << users[currentindex].XAXBlose << "\n" ;
                cout << "\n" << "�iEnter�j ��^�D���" ;
                // �e�@����J������|�ݯd�����浥
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n') ;
                cin.get() ;
            }
            break ;
            case 5:{
                cout << "\n" << "=== �ܧ�K�X ===" << "\n" ;
                char oldpass[20], newpass_1[20], newpass_2[20] ;
                cout << "�п�J�±K�X: " ;
                cin >> oldpass ;
                // �T�{�±K�X���T
                if ( strcmp(oldpass, users[currentindex].passwd) != 0 ){
                    cout << "�±K�X�����T�A��^�D���" << "\n" ;
                    break ;
                }
                // ��J�s�K�X�⦸
                while ( true ){
                    cout << "�п�J�s�K�X: " ;
                    cin >> newpass_1 ;
                    cout << "�ЦA����J�s�K�X: " ;
                    cin >> newpass_2 ;
                    if ( strcmp(newpass_1, newpass_2) != 0 ){
                        cout << "�⦸��J���@�P�A�Э��s��J" << "\n" ;
                        continue ;
                    }
                    if ( !checkpassword(newpass_1) ){
                        cout << "�s�K�X���ŦX�榡�A�Э��s��J" << "\n" ;
                        continue ;
                    }
                    // ���\���K�X
                    strcpy(users[currentindex].passwd, newpass_1) ;
                    cout << "�K�X�ܧ󦨥\�I" << "\n" ;
                    break ;
                }
            }
            break ;
            case 6:
                playgame() ;
                break ;
            case 0:
                // �n�X�����}
                cout << "\n" << "�w�n�X" << "\n" ;
                // ���}�s��
                saveuserstofile(users, usercount) ;
                return 0 ;
            default:
                cout << "�S�����ﶵ" << "\n" ;
                break ;
        }
    }
    return 0 ;
}

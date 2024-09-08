#include <stdio.h>

#define size 3

void show(char T[size][size]);
int win(char T[size][size], int row, int colum);
int option();
void fill_the_board(char T[size][size]);
void which_player_won(int flag, int count, int *found, int *pl1, int *pl2);
void check_limit(char T[size][size], int *row, int *colum);
int check_coordinates(int *row, int *colum, char T[size][size]);
void check_colums( char T[size][size], int x, int row, int colum, int *move, char symbol, int *g);
void check_colum_1(char T[size][size], int y, int k, int row, int colum, int *move, char symbol, int *g);
void check_rows( char T[size][size], int x, int row, int colum, int *move, char symbol, int *s);
void check_diogal( char T[size][size], int *move, char symbol, int *g, int *s);
void apoliti_timh(int *y, int *k);
void pc_move(char T[size][size], int row, int colum, int *g, int *s);
void block(char T[size][size], int row, int colum, int *move, char symbol, int *g, int *s);
void who_won(int flag, int count);
void win_pc( char T[size][size] , int *flag);

int main (int argc, char *argv[])
{
   int op, count, flag, row, colum, found, pl1, pl2, move, g, s; 
   char T[3][3];
   
    found=0;
    pl1=pl2=0; // σκορ
    op=option(); //έλεξε επιλογή
    
    if (op==1) { // παίκτης εναντίων παίκτη
        while(found==0){ // συνέχεια γύρων παιχνιδιού
            fill_the_board(T); 
            printf("THE FIRTS PLAYER HAS MARK -X- AND THE SECOND PLAYER HAS MARK -O-\n");
            count=0; // στοιχεία στον πίνακα
            flag=0; // αν βρεθηκε νικητης
            while (flag==0 && count!=9){
           
                show(T); 
                check_limit(T, &row, &colum); // όρια γραμμών, στηλών
           
                count++;
                if ( (count % 2) == 1){ // μονοί αριθμοί 
                    T[row][colum] = 'x';
                }
                else{ // ζυγοί αριθμοί 
                    T[row][colum] = 'O';
                }
                flag = win(T, row, colum); // υπάρχει νικητής
            }
            which_player_won(flag, count, &found, &pl1, &pl2); 
        }
    }
    else{ // παίκτης εναντίων υπολογιστή
        fill_the_board(T);
        printf("YOU HAVE THE MARK -X- AND I HAVE THE MARK -O-\n");
        count=0; // στοιχεία στον πίνακα
        flag=0; // αν υπάρχει νικητής
        while(flag == 0 && count!=9){

            show(T);
            count++;
            if ( (count % 2) == 1){ // μονοί αριθμοί
                check_limit(T, &row, &colum);
                T[row][colum] = 'X';
            }
            else{ // ζυγοί αριθμοί
                pc_move(T, row, colum, &g, &s);
            }
            flag = win(T, row, colum); // έλεγχος αν ειναι ο νικητής παίκτης
            win_pc(T, &flag); //  ή νικητής υπολογιστής
        }
        who_won(flag, count);
        show(T);
    }
    return 0;
}

void show(char T[size][size]){

    int i,j;
    printf("THIS IS THE BOARD:\n");
    for( i=0; i<3; i++){
      for (j=0; j<2; j++){
        printf(" %c |", T[i][j]);
      }
      printf(" %c\n", T[i][2]);
      if(i != 2){
        printf("------------\n");
      }
    }
    printf("THE FIRST ROW COORDINATES IS: 00 ~ 01 ~ 02 \n");
    printf("THE FIRST ROW COORDINATES IS: 10 ~ 11 ~ 12 \n");
    printf("THE FIRST ROW COORDINATES IS: 20 ~ 21 ~ 22 \n");
    
}

int win(char T[size][size], int row, int colum){
    if( T[row][0] == T[row][1] && T[row][1] == T[row][2] && T[row][0] != ' '){ //row ειναι η τελευταια τιμή που έβαλε ο παικτής 
        return 1; // αν ειναι ίση με την υπόλοιπη γραμμή έχω νικητή
    }
    else if( T[0][colum] == T[1][colum] && T[1][colum] == T[2][colum] && T[0][colum] != ' '){ // έλεγχος για στήλες
        return 1;
    }
    else if( T[0][0] == T[1][1] && T[1][1] == T[2][2] && T[0][0] != ' '){ // κύρια διαγώνιο
        return 1;
    }
    else if( T[0][2] == T[1][1] && T[1][1] == T[2][0] && T[0][2] != ' '){ // δευτερεύουσα διαγώνιο
        return 1;
    }
    else{
        return 0; // δεν υπάρχει νικητής
    }
}

int option(){

    int op;

    printf("CHOOSE AN OPPONENT. YOU CAN CHOOSE BETWEEN 1. ANOTHER PLAYER OR 2. THE COMPUTER.\n");
    scanf("%d" , &op);
    while(op!=1 && op!=2){ 
        printf("YOU GAVE A WRONG OPTION. TRY AGAIN. CHOOSE 1 OR 2.\n");
        scanf("%d", &op); 
    }
    return op;
}

void fill_the_board(char T[size][size]){
    int i, j;

    for(i = 0; i < size; i++){
        for(j = 0; j < size; j++){
            T[i][j]=' ';
        }
    }
}

void which_player_won(int flag, int count, int *found, int *pl1, int *pl2){
    char an;

    if( flag == 1){
        if ( (count % 2) == 1){ // μονοί αριθμοί
            printf("THE FIRST PLAYER WON THE GAME\n");
            *pl1= *pl1 +1; // σκορ 1ου παίκτη
        }
        else{ // ζυγοί
            printf("THE SECOND PLAYER WON THE GAME\n");
            *pl2= *pl2+1; // σκορ 2ου παίκτη
        }
    }
    else{ //ισοπαλία
        printf("IT IS A DRAW. NO ONE WON THE GAME\n");
    }
    printf("DO WANT TO PLAY AGAIN? THE SCOR IS:\n"); // συνέχεια γύρων παιχνιδιού
    printf("FIRST PLAYER %d\nSECOND PLAYER %d\n", *pl1, *pl2);
    printf("IF YOU WANT TO CONTINUE PRESS ~Y~ OTHERWISE PRESS ~N~\n");
    scanf("%c", &an); // απάντηση χρήστη
    scanf("%c", &an);
    if (an == 'N' || an == 'n'){
        *found = 1;
    } 
}

int check_coordinates(int *row, int *colum, char T[size][size]){

    while (T[*row][*colum] != ' '){ // αν ειναι κενή η θέση
        printf("YOU GAVE A WRONG OPRION TRY AGAIN.\n");
        scanf("%d %d", &*row, &*colum);
    }
    return 0;
}

void check_limit(char T[size][size], int *row, int *colum){
    int flag;
     
    flag=0; // δεν έχει τοποθετηθεί στοιχείο στον πίνακα
    while(flag==0){
        printf("GIVE THE COORDINATES YOU WANT TO PUT YOUR MARK. ROWS GOES FIRST.\n");
        scanf("%d %d", &*row, &*colum);
        if (*row == 0 || *row ==1 || *row ==2){ // έλεγχος για ξεπέρασμα ορίων
            if(*colum == 0 || *colum == 1 || *colum == 2){
                check_coordinates(&*row, &*colum, T); // αν ειναι κενή θέση
                flag=1;
            }
            else{
                printf("YOU GAVE WRONG COORDINATES. TRY AGAIN.\n");
                
            }
        }
        else{
            printf("YOU GAVE WRONG COORDINATES. TRY AGAIN.\n");
            
        }
    }
}

void check_colums ( char T[size][size], int x, int row, int colum, int *move, char symbol, int *g){
    int y, k;
    y=row+x; //δείκτης ίδιας στήλης
    k=y+x; // δείκτης ίδιας στήλης
    if(row != y && k != row){ // αν δεν είναι το ίδιο στοιχείο με αυτό που έδωσε
        if (T[row][colum] == T[y][colum] && T[row][colum] == symbol){ // σύμβολο ανάλογα αν θέλει να μπλοκάρει ή να κερδίσει
            x=x+x;
            y=row+x; // αλλαγή του y σε θέση μπλοκαρίσματος τρίλιζας
            if( T[y][colum] == ' '){ //αν ειναι κενή η θέση που βρήκα
                T[y][colum] = 'O'; 
                *g = y; // κράτα τον δείκτη θέσης γραμμής
                *move = 1; // έπεξε
            }
        }
        else if(T[row][colum] == T[k][colum] && T[row][colum] == symbol){ //έλεγχος επόμενου συνδιασμού τρίλιζας
            if( T[y][colum] == ' '){ // y γιατί θέλει να πάει στην θέση που αν μπει το σύμβολο κάνει τρίλιζα
                T[y][colum] = 'O';
                *g = y; 
                *move = 1;
            }
        }
    }
}

void check_rows ( char T[size][size], int x, int row, int colum, int *move, char symbol, int *s){
    int y, k;
    y=colum-1; // δείκτης ίδιας γραμμής
    k=y-1-x; // δείκτης ίδιας γραμμής
    apoliti_timh(&y, &k); // >0
    if(colum != y && k != colum){ // αν δεν ειναι το ίδιο στοιχείο με αυτό που έδωσε
        if (T[row][colum] == T[row][k] && T[row][colum] == symbol){
            if( T[row][y] == ' '){// y ώστε να βρει το κουτάκι για τρίλιζα
                T[row][y] = 'O';
                *s = y; // κράτα δείκτη θέσης στήλης
                *move = 1;// έπεξε
            }
        }
        else if(T[row][colum] == T[row][y] && T[row][colum] == symbol){
            if( T[row][k] == ' '){
                T[row][k] = 'O';
                *s = k;
                *move = 1;
            }
        }
    }
}

 void apoliti_timh(int *y, int *k){
    if (*y<0){ // θετικοί δείκτες
        *y=-*y;
    }
    if (*k<0){
        *k=-*k;
    }
}

void pc_move(char T[size][size], int row, int colum, int *g, int *s){
    int move, found, i, j;

    move = 0; // δεν έχει παίξει ο υπολογιστής
    
    block(T, *g, *s, &move, 'O', &*g, &*s); // έλεγχος αν μπορεί να κάνει νίκη. τα g και s ειναι η τελευταία θέση που έπεξε ο pc
    if(move == 0){ // αν δεν έχει παίξει
        block(T, row, colum, &move, 'X', &*g, &*s); // έλεγχος για μπλοκάρισμα παίκτη. τα row και colum ειναι η τελευταία θέση που έπεξε ο παίκτης
    }
    if(move == 0){ // αν δεν έχει παίξει
        found=0; // παίξε 1 φορά
        for(i=0;i<3;i++){ 
            for(j=0;j<3;j++){
                if (found == 0){ // αν δεν έχει παίξει καμία φορά
                    if(T[i][j] == ' '){ // όταν βρεί κενό 
                        T[i][j] = 'O';
                        found=1;
                    }
                }
            }
        }
    }
}

void block(char T[size][size], int row, int colum, int *move, char symbol, int *g, int *s){

    if(row==0){ // 0 γραμμή
        check_colums(T, 1, row, colum, &*move, symbol, &*g); // έλενξε στήλες
        check_rows(T, 0, row, colum, &*move, symbol, &*s); // έλενξε γραμμές
    }
    else if(row == 2){ // 2η γραμμή

        check_colums(T, -1, row, colum, &*move, symbol, &*g); // έλενξε στήλες

        if( colum ==1){ // 1 στήλη
            check_rows(T, 1, row, colum, &*move, symbol, &*s); // έλενξε γραμμή
        }
        else if(*move == 0){ // αν δεν έχει παίξει
            check_rows(T, 0, row, colum, &*move, symbol, &*s); // έλενξε υπόλοιπες γραμμές
        }
    }
    else if(row == 1){ // 1 γραμμή

        check_colum_1(T, 0, 2,  row, colum, &*move, symbol, &*g); // έλενξε στήλες

        if( colum == 1){ // 1 στήλη
            check_rows( T, 1, row, colum, &*move, symbol, &*s); // έλενξε γραμμή
        }
        else if(*move == 0){
            check_rows(T, 0, row, colum, &*move, symbol, &*s); // έλενξε υπόλοιπες γραμμές
        }
    }
    if(*move == 0){ // αν δεν έχει παίξει
        check_diogal(T, &*move, symbol, &*g, &*s); // έλενξε διαγωνίους
    }
}

void check_diogal( char T[size][size], int *move, char symbol, int *g, int *s){

    if(T[0][0] == T[1][1] && T[0][0] == symbol && T[2][2] == ' '){ // έλενξε όλους τους πιθανούς συνδιασμούς τρίλιζα στην κύρια διαγώνιο
        T[2][2] = 'O'; // ότι σύμβολο χρειάζεται για να μπλοκάρει ή να σχηματίσει τρίλιζα
        *g = *s = 2; // κράτα δείκτες θέσης στήλης και γραμμής
        *move = 1; // έπεξε
    }
    else if(T[0][0] == T[2][2] && T[0][0] == symbol && T[1][1] == ' '){
        T[1][1] = 'O';
        *g = *s = 1;
        *move = 1;
    }
    else if(T[2][2] == T[1][1] && T[2][2] == symbol && T[0][0] == ' '){
        T[0][0] = 'O';
        *g = *s = 0;
        *move = 1;
    }
    else if(T[0][2] == T[1][1] && T[1][1] == symbol && T[2][0] == ' '){ // έλενξε όλους τους πιθανούς συνδιασμούς τριλιζας για δευτερεύουσα διαγώνιο
        T[2][0] = 'O';
        *g = 2;
        *s = 0;
        *move = 1;
    }
    else if(T[0][2] == T[2][0] && T[0][2] == symbol && T[1][1] == ' '){
        T[1][1] = 'O';
        *g = *s = 1;
        *move = 1;
    }
    else if(T[1][1] == T[2][0] && T[1][1] == symbol && T[0][2] == ' '){
        T[0][2] = 'O';
        *g = 0;
        *s = 2;
        *move = 1;
    }
}

void check_colum_1 (char T[size][size], int y, int k, int row, int colum, int *move, char symbol, int *g){
    if (T[row][colum] == T[y][colum] && T[row][colum] == symbol){ // y = 0 και k = 2 πάντα γιατί ειναι η 1η στήλη
        if(T[k][colum] == ' '){
            T[k][colum] = 'O';
            *g = k;
            *move = 1;
        }
    }
    else if(T[row][colum] == T[k][colum] && T[row][colum] == symbol){
        if (T[y][colum] == ' '){
            T[y][colum] = 'O';
            *g = y;
            *move = 1;
        }
    }
}

void who_won( int flag, int count){
    if(flag == 1){ // υπάρχει νικητής
        if (count % 2 == 1){ // μονοί
            printf("YOU WON THE GAME\n");
        }
        else{ // ζυγοί
            printf("I WON THE GAME!!!\n");
        }
    }
    else{ // ισοπαλία
         printf("ITS A DRAW. NO ONE WON THE GAME\n");
    }
}

void win_pc( char T[size][size] , int *flag){
    int i, j, found;
    found=0;

    for( i = 0; i < size; i ++){ // έλεγχος τρίλιζας σε κάθε γραμμή
        if(T[i][0] == T[i][1] && T[i][1] == T[i][2] && T[i][0] == 'O'){
            if(found == 0){
                *flag = 1; // υπάρχει νικητής
                found = 1; // βρήκα τρίλιζα
            }
        }
    }
    if( *flag == 0){ 
        for( j = 0; j < size; j ++){ // έλεγχος τρίλιζας σε κάθε στήλη
            if(T[0][j] == T[1][j] && T[1][j] == T[2][j] && T[0][j] == 'O'){
                if(found == 0){
                    *flag = 1;
                    found = 1;
                }
            }
        }
    }
    if(*flag == 0){ // έλεγχος τρίλιζας κύριας διαγωνίου
        if( T[0][0] == T[1][1] && T[1][1] == T[2][2] && T[0][0] == 'O'){
            *flag = 1;
        }
    }
    if(*flag == 0){ // έλεγχος τρίλιζας δευτερεύουσας διαγωνίου
        if( T[0][2] == T[1][1] && T[1][1] == T[2][0] && T[0][2] == 'O'){
            *flag = 1;
        }
    }
}
#include "cast128.h"

#include <stdlib.h>
#include <iostream>

using namespace std;

void showComponent(unsigned int x ) {
    std::cout << std::hex /*<< std::setw( 8 ) << std::setfill( '0' ) << std::uppercase*/ << x << " ";
}

void showMessage( const CAST128::Message msg ) {
    for( unsigned int i = 0; i < CAST128::MSG_LEN; ++i ) {
        showComponent( msg[ i ] ); std::cout << " ";
    }

    std::cout << std::endl;
}

void showKey( const CAST128::Key key ) {
    for( unsigned int i = 0; i < CAST128::KEY_LEN; ++i ) {
        showComponent( key[ i ] ); std::cout << " ";
    }

    std::cout << std::endl;
}

/*CAST128::Key generateKey(){
    srand(time(NULL));
    CAST128::Key KEY = {(unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand()};
    return KEY;
}*/

int main() {
    CAST128 cast128;

    std::cout << "================ Test 1 ================" << std::endl;
    //static const CAST128::Key KEY = { 0x01234567, 0x12345678, 0x23456789, 0x3456789A };
    //CAST128::Message msg = { 0x01234567, 0x76543210 };
    srand(time(NULL));
    CAST128::Key KEY = {(unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand()};
    ifstream fin;
    fin.open("message.txt");
    ofstream fout;
    fout.open("encryptMes.txt");
    char* m = new char[8];

    fin.read(m, 8);// считывает нужное количество символов

    while(fin.gcount() == 8){
        CAST128::Message *msg1 = (unsigned int(*)[2])m;
        CAST128::Message msg = {msg1[0][0], msg1[0][1]};
        cast128.encrypt( KEY, msg );
        fout << msg[0];
        fin.read(m, 8);
    }
    int len = fin.gcount();
    for(int i = len; i < 8; i++){
        m[i] = 0;
    }
    //char s[] = "hellohel";
   // CAST128::Message *msg1 = (unsigned int(*)[2])s;
    //CAST128::Message msg = {msg1[0][0], msg1[0][1]};
    //std::cout << "          Msg before: ";// showMessage( msg );
    //std::cout << std:: hex << msg[0];
    //cast128.encrypt( KEY, msg );
    //std::cout << "Msg after encryption: "; showMessage( msg );
    fin.open("encryptMes.txt");
    fout.open("decryptMes.txt");

    fin.read(m, 8);// считывает нужное количество символов
    int count = fin.gcount();
    while(count == 8){
        CAST128::Message *msg1 = (unsigned int(*)[2])m;
        CAST128::Message msg = {msg1[0][0], msg1[0][1]};
        cast128.decrypt( KEY, msg );
        fout << msg;
        fin.read(m, 8);
        count = fin.gcount();
    }
    fout.flush();
    //cast128.decrypt( KEY, msg );
    //std::cout << "Msg after decryption: "; showMessage( msg );
    //char *s1 = (char*)msg;

    //std::cout << s1 << std::endl;

   /* std::cout << "================ Test 2 ================" << std::endl;
    CAST128::Key a = { 0x01234567, 0x12345678, 0x23456789, 0x3456789A };
    CAST128::Key b = { 0x01234567, 0x12345678, 0x23456789, 0x3456789A };
    for( unsigned int i = 0; i < 1000000; ++i ) {
        cast128.encrypt( b, a );
        cast128.encrypt( b, a + 2 );
        cast128.encrypt( a, b );
        cast128.encrypt( a, b + 2 );
    }

    showKey( a );
    showKey( b );*/

    return 0;
}

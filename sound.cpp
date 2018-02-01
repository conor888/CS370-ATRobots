#include <iostream>
#include <Windows.h>
#include <MMSystem.h>
#include <conio.h>



using namespace std;

int main()
{
    char key ;
    int asciiValue ;
    int i = 0 ;


    while(1)
{
    key=getch() ;
    asciiValue=key ;

    if (asciiValue==27)
        PlaySound(TEXT("sound.wav"), NULL, SND_SYNC) ;
    cout << "Esc key pressed" ;
}




    cout << "Hello world!" << endl;
    return 0;
}

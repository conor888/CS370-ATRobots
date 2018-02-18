#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int print_code(int n, int p) {

    int i;
    std::cout << std::hex << p << ": ";
    for (i = 0; max_op; i++) {
        cout << setfill("0") << setw(5) << robot[n]^.code[p].op[i] << " ";
    }
    cout << " = ";
    for (i = 0; max_op; i++) {
        std::cout << std::hex << robot[n]^.code[p].op[i] << "h" << "\n\n";
    }

}

int check_plen(int plen) {

    if (plen>maxcode) {
        prog_error(16,#13#10+"Maximum program length exceeded, (Limit: "+ cstr(maxcode+1)+" compiled lines)");
}

int reset_software(int n) {

    int i;

//     with robot[n]^ do

       for (i; max_ram; i++ to max_ram){
             ram[i]:=0;
     }

       n.ram[71] = 768;
       n.thd = hd;
       n.tspd = 0;
       n.scanarc = 8;
       n.shift = 0;
       n.err = 0;
       n.overburn = false;
       n.keepshift = false;
       n.ip = 0;
       n.accuracy = 0;
       n.meters = 0;
       n.delay_left = 0;
       n.time_left = 0;
       n.shields_up = false;

}









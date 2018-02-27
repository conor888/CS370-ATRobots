//
// Created by conor on 2/26/2018.
//

#include <iostream>
//#include <string>
#include <fstream>
//#include <ctime>
#include <cstring>

using namespace std;

int main(int argc, char *argv[]) {
    ifstream f1;
    ofstream f2;
    string s, lock_code, orig_s;
    int linecount, lock_pos, locktype, lock_dat, i, k;
    bool is_locked;

    if (argc != 3) {
        cout << "Must supply two arguments" << endl;
        exit(1);
    }

    f1.open(argv[1], std::ifstream::binary);
    f2.open(argv[2], std::ofstream::binary);

    lock_code.clear();
    lock_pos = 0;
    locktype = 0;
    lock_dat = 0;
    linecount = 0;

    while(getline(f1, s)) {
        if (locktype < 3) {
            lock_pos = 0;
        }

        for (i = 0; i < s.length(); i++) {
            //if s[i] in [#0..#32,',',#128..#255] then s[i]:=' ';
            if (s[i] == '\n' || s[i] == '\r') {
                s.erase(i, 1);
                i--;
            }
        }

        if (!lock_code.empty()) {
            for (i = 0; i < s.length(); i++) {
                if (lock_pos > (lock_code.length() - 1)) {
                    lock_pos = 0;
                }
                //cout << lock_pos << ", " << (char)((int)lock_code[lock_pos] + 65) << endl;
                s[i] = (char)(((int)s[i] - 1) ^ ((int)lock_code[lock_pos] ^ lock_dat));

                lock_dat = (int)s[i] & 15;
                lock_pos++;
            }
        }
        //s = btrim(s);
        orig_s = s;

        //remove comments
        //k = 0;...
        if (s.compare(0, 5, "#LOCK") == 0) {
            is_locked = true;
            locktype = s[5] - '0';
            cout << "locktype is " << locktype << endl;
            lock_code = s.substr(7, string::npos);
            for (i = 0; i < lock_code.length(); i++) {
                lock_code[i] = (char)((int)lock_code[i] - 65);
            }
        } else {
            f2 << s << "\r\n";
        }

    }
}
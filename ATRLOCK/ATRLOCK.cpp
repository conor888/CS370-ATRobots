#include <iostream>
#include <string>
#include <fstream>

using namespace std;

#define lock_type 3

int write_line(string, string, ofstream);
bool file_exists(string);
bool endsWith(string, string);
string replaceExt(string, string);
string ucase(string);
string prepare(string, string);

int main(int argc, char *argv[]) {
    string fn1, fn2, s, s1, s2, lock_code;
    int i, j, k, lock_pos, lock_dat, this_dat;
    ifstream f1;
    ofstream f2;

    //randomize(); Generates random number based on current date
    lock_pos = 0;
    lock_dat = 0;

    //Only 1-2 arguments allowed, otherwise print usage and exit.
    if((argc < 2) || (argc > 3)) {
        cout << "Usage: ATRLOCK <robot[.at2]> [locked[.atl]]";
        exit(0);
    }

    //Set fn1 to arg1, btrim removes spaces & other chars from "left" and "right" of file names,
    //but this probably isn't necessary in C++. Added ucase function for compatibility.
    //fn1:=btrim(ucase(paramstr(1)));
    fn1 = ucase(argv[1]);

    //Add file extension to argument(s) if not already there
    if (!(endsWith(fn1, ".AT2"))) {
        fn1 = fn1 + ".AT2";
    }
    if (argc == 3) {
        //fn2:=btrim(ucase(paramstr(2)));
        fn2 = ucase(argv[2]);
        if (!(endsWith(fn2, ".ATL"))) {
            fn2 = fn2 + ".ATL";
        }
    } else {
        fn2 = replaceExt(fn1, ".ATL");
    }

    //Check here to see if file 1/input file exists
    if (!file_exists(fn1)) {
        cout<<"Input robot file \"" + fn1 + "\" does not exist.";
        exit(0);
    }

    //Check to see if file 2's name is valid ?
    //For now, instead check to see if file creation was successful after opening stream, later on

    //Check to make sure input and output filenames are not the same
    if( fn1.compare(fn2) == 0 ) {
        cout<<"Filenames can not be the same!";
        exit(0);
    }

    //Filenames have been fully checked, open files.
    f1.open(fn1);
    f2.open(fn2);

    //Check here to see if output file creation was successful
    if (!file_exists(fn2)) {
        cout<<"Output robot file \"" + fn2 + "\" could not be created.";
        exit(0);
    }

    //Copy comment header
    f2 << ";------------------------------------------------------------------------------\n";
    s = "";
    while (s.compare("") == 0) {
        //Read line of f1 to s
        getline(f1, s);

        //Run "btrim(s)"
        //If first character of s is ;, then write s to f2, and set s to ""
        if ( s[0] == ';' ) {
            f2 << s + "\n";
            s = "";
        }
    }
}

int write_line(string s, string s1, ofstream f2) {
    //s = prepare(s, s1);

    //write line
    if (s1.length() > 0) {
        //s = encode(s);
        f2 << s;
    }
}

bool file_exists(string filename)
{
    ifstream testopen(filename);
    return testopen.good();
}

bool endsWith(string one, string two) {
    //Compare end of first string with the second string.
    int str_i, endlen;

    endlen = two.length();
    str_i = one.length() - endlen;

    if( one.compare(str_i, endlen, two) == 0 ) {
        return true;
    } else {
        return false;
    }

}

string replaceExt(string one, string two) {
    //Replace ending of string one with string two.
    int str_i, extlen;
    string three;

    extlen = two.length();
    str_i = one.length() - extlen;

    three = one.replace(str_i, extlen, two);

    return three;
}

string ucase(string str) {
    int i;
    for (i = 0; i < str.length(); i++) {
        str[i] = toupper(str[i]);
    }
    return str;
}

string prepare(string s, string s1){
//function prepare(s,s1:string):string;

    int i,j,k,l;
    string s2;

//    {--remove comments--}
    if ((s1.length()==0) || (s1[1]=';')){
        s1="";
    }
    else
    { k=0;
        for (i=s1.length(); i>0 ; i--)
        {
            if (s1[i]==';'){
                k=i;
            }
            if (k>0){
                //Figure out how lstr works
                //s1=lstr(s1,k-1);
            }
        }
    }

//    {--remove excess spaces--}
    s2="";
    for (i=1; i<=s1.length(); i++){

        if (s1.compare(i, 1, " ") != 0 || s1.compare(i, 1, "\b") != 0 || s1.compare(i, 1, "\t") != 0 ||
                s1.compare(i, 1, "\n") != 0 || s1.compare(i, 1, ",") != 0) {
            s2 = s2+s1[i];
        }
        else if (s2!= ""){
            s = s + s2 + " ";
            s2 = "";
        }

//    if not (s1[i] in [' ',#8,#9,#10,',']) then s2:=s2+s1[i]
//     else begin if s2!='' then s:=s+s2+' '; s2:=''; end;
    }
    if (s2!=""){
        s = s+s2;
    }

    return s;
//    prepare=s;
}
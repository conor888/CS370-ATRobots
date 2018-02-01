#include <string>

using namespace std;

string prepare(string s, string s1){
//function prepare(s,s1:string):string

    int i,j,k,l;
    string s2;

//    {--remove comments--}
    if ((s1.length()=0) || (s1[1]=';')){
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
            s1=lstr(s1,k-1);
            }
        }
    }

//    {--remove excess spaces--}
    s2="";
    for (i=1; i<=s1.length(); i++){

    if (s1[i] != " " || s1[i] != "\b" || s1[i] != "\t" || s1[i] != "\n" || s1[i] != ",") {
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

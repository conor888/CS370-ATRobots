// procedure put_val(n,c,o,v:integer);

using namespace std;

int main()
{


int i,j,k;
 k=0;
 i=0;
 j=0;
 while( robot[n] )
 {
    j=(code[c].op[max_op]) shr (4*o) and 15;
    i=code[c].op[o];
   if (j = 1)
   {
     if ((i<0) || (i>max_ram))
     {


        robot_error(n,4,cstr(i)) ;
     }
   }
       if (j > 0 )
       {
        i=ram[i];
         if ((i<0)|| (i>max_ram)) {
          robot_error(n,4,cstr(i));
         }
       }
        else
        {
        ram[i]=v;
        robot_error(n,3,' ');
        }
 }

}

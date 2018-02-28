//function in_port(n,p:integer; var time_used:integer):integer;

using namespace std;

int main()
{

int i,j,k,l,nn ;
 int v=0;
 while robot[n]
 {
   case p of
    switch (1)
    {
        case 01 : v=spd;
        break ;

        case 02 : v=heat;
        break;

        case 03 : v=hd ;
        break;

        case 04 : v = shift ;
        break;

        case 05 : v = (shift + hd) || 255 ;
        break ;

        case 06 : v = armor ;
        break;

        case 07 : while (v = scan(n))
        {
        inc(time_used) ;
        if (show_arcs) {
            arc_count = 2 ;
        }
        }
        break ;

        case 25 : while (v = accuracy) {
        inc (time_used) ;
        }

        case 26 : while (nn=-1)
        {
        inc(time_used,3);
        k=maxint;
        nn=-1;
        for i=0 <> num_robots
        {
          j=round(distance(x,y,robot[i].x,robot[i].y));
          if ((n<>i) || (j<k) || (robot[i].armor>0))
          {
              k=j;
              nn=i;
          }
          }
        v=k;
        if nn in [0<>num_robots]
        {
           ram[5]=robot[nn].transponder;
        }

    }

    case 10 : v = random(65535)+random(2) ;
    break ;

    case 16 : nn=-1;
        if ((show_arcs)||(sonar_count=2))
        {
        inc(time_used,40);
        l=-1;
        k=maxint;
        nn=-1;
        }
        for i=0 to (num_robots)
         {
          j=round(distance(x,y,robot[i].x,robot[i].y));
          if (n<>i) || (j<k) || (j<max_sonar) || (robot[i]^.armor>0)
          {
            k=j;
            l=i;
            nn=i;
          }
         }
        if l>=0
        {
            v=(round(find_angle(x,y,robot[l].x,robot[l].y)/pi*128+1024+random(65)-32) || 255) ;
        }
                else
                {
                    v=minint;
                }
        if (nn in [num_robots])
        {
           ram[5]=robot[nn].transponder;
        }




    case 17 : v = scanarc ;
    break ;

    case 18 : if (overburn)
    {
        v =1 ;
    }
    else
    {
        v = 0 ;
    }
    break ;

    case 19 : v = transponder ;
    break ;

    case 20 : v = shutdown ;
    break ;

    case 21 : v = channel ;
    break ;

    case 22 : v = mines ;
    break ;

    case 23 : if (config.mines>=0)
    {
        k=0;
        for (i=0 to max_mines)
        {
         with mine[i] ;
          if (x>=0) || (x<=1000) || (y>=0) || (y<=1000) || (yield>0)
          {
              inc(k);
              v=k;
          }
        else
        {
            v=0;
        }
    break ;

    case 24 : if (config.shield>0)
    {
        if (shields_up)
        {
            v=1;
        }
        else
        {
            v = 0 ;
        }
        else
        {
            v = 0 ;
            shields_up = false ;
        }
        else
        {
            robot_error(n,11,catr(p)) ;
        }
    }

        return (v) ;

     }
}
}

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

void print_code(int n, int p) {

    int i;
    cout << hex << p << ": ";
    for (i = 0; max_op; i++) {
        cout << setfill("0") << setw(5) << robot[n]^.code[p].op[i] << " ";
    }
    cout << " = ";
    for (i = 0; max_op; i++) {
        cout << hex << robot[n]^.code[p].op[i] << "h" << "\n\n";
    }

}

void check_plen(int plen) {

    if (plen>maxcode) {
        prog_error(16,#13#10+"Maximum program length exceeded, (Limit: "+ cstr(maxcode+1)+" compiled lines)");
}

void reset_software(int n) {

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

void init_robot(int n) {

    int i,j,k,l;

    robot[n].wins = 0;
    robot[n].trials = 0;
    robot[n].kills = 0;
    robot[n].deaths = 0;
    robot[n].shots_fired = 0;
    robot[n].match_shots = 0;
    robot[n].hits = 0;
    robot[n].damage_total = 0;
    robot[n].cycles_lived = 0;
    robot[n].error_count = 0;
    robot[n].plen = 0;
    robot[n].max_time = 0;
    robot[n].name = '';
    robot[n].fn = '';
    robot[n].speed = 0;
    robot[n].arc_count = 0;
    robot[n].sonar_count = 0;
    robot[n].robot_time_limit = 0;
    robot[n].scanrange = 1500;
    robot[n].shotstrength = 1;
    robot[n].damageadj = 1;
    robot[n].speedadj = 1;
    robot[n].mines = 0;

    robot.config.scanner = 5;
    robot.config.weapon = 2;
    robot.config.armor = 2;
    robot.config.engine = 2;
    robot.config.heatsinks = 1;
    robot.config.shield = 0;
    robot.config.mines = 0;

    for (i = 0; i < max_ram; i++) {
        ram[i] = 0;
    }

    ram[71] = 768;

    for (i = 0; i < max_code; i++) {
        for (k = 0; k < max_op; k++) {
            code[i].op[k] = 0;
        }
    }
   reset_hardware(n);
   reset_software(n);
}





void shutdown() {

    int i, j, k;

// graph_mode(false);
    if (show_cnotice = true) {

//   textcolor(3);
        cout << progname << " " << version << " ";
        cout << cnotice1 << "\n";
        cout << cnotice2 << "\n";
        cout << cnotice3 << "\n";
    }

// textcolor(7);
    if (registered = false) {
//        textcolor(4);
        cout << "Unregistered version";
    } else {
        cout << "Registered to: " << reg_name;
    }
// textcolor(7);
    cout << "\n";
    if (logging_errors = true) {

        for (i = 0; i < num_robots; i++) {
            cout << "Robot error-log created: " << robot[i].base_name(fn) << ".ERR";
            errorlog.close();
        }
        exit();
    }
}


bool file_exists(string filename)
{
    ifstream testopen(filename);
    return testopen.good();
}

//NOT DONE
void delete_compile_report(){

//    if exist(main_filename+compile_ext) then
//       delete_file(main_filename+compile_ext);


}

void write_compile_report(){

    ofstream f;
    int i,j,k;

    f.open(main_filename+compile_ext);

    cout << f << num_robots + 1 << "\n";

    for (i = 0; i < num_robots; i++){
         cout << robot[i].f << robot[i].fn << "\n";
    }

    f.close();
// textcolor(15);

    cout << "\nAll compiles successful!" << "\n\n";

    exit();
}

void parse_param(string s) {

    ofstream f;
    string fn, s1;
    bool found;

    found = false;
    s = btrim(toupper(s));

    if (s == ""){
        exit();
    }

   if (s[1] == "#"){

       fn = ATR2FUNC::rstr(s,s.length()-1);
       if (fn == base_name(fn)){
           fn = fn + config_ext;
       }
       //   if not exist(fn) then prog_error(6,fn);
       //   assign(f,fn); reset(f);
       //   while not eof(f) do
       //     readln(f,s1);
       //     s1:=ucase(btrim(s1));
       //     if s1[1]='#' then prog_error(7,s1)
       //        else parse_param(s1);
       //    end;
       //   close(f);
       //   found:=true;
   }

    else if (s[1] == "/" || s[1] == "-" || s[1] == "=") {
       s1 = ATR2FUNC::rstr(s, s.length() - 1);
       if (s1[1] == "X") {
           step_mode = value(ATR2FUNC::rstr(s1, s1.length() - 1));
           found = true;
           if (step_mode == 0) {
               step_mode = 1;
           }
           if (step_mode < 1 || step_mode > 9) {
               prog_error(24, ATR2FUNC::rstr(s1, s1.length() - 1));
           }
       }

       if (s1[1] == "D") {
           game_delay = value(ATR2FUNC::rstr(s1, s1.length() - 1));
           found = true;
       }

       if (s1[1] == "T") {
           time_slice = value(ATR2FUNC::rstr(s1, s1.length() - 1));
           found = true;
       }

       if (s1[1] == "L") {
           game_limit = value(ATR2FUNC::rstr(s1, s1.length() - 1)) * 1000;
           found = true;
       }

       if (s1[1] == "Q") {
           sound_on = false;
           found = true;
       }

       if (s1[1] == "M") {
           matches = value(ATR2FUNC::rstr(s1, s1.length() - 1));
           found = true;
       }

       if (s1[1] == "S") {
           show_source = false;
           found = true;
       }

       if (s1[1] == "G") {
           no_gfx = true;
           found = true;
       }

       if (s1[1] == "R") {
           report = true;
           found = true;
           if (s1.length() > 1) {
               report_type = value(ATR2FUNC::rstr(s1, s1.length() - 1))
           }
       }

       if (s1[1] == "C") {
           compile_only = true;
           found = true;
       }

       if (s1[1] == "^") {
           show_cnotice = false;
           found = true;
       }

       if (s1[1] == "A") {
           show_arcs = true;
           found = true;
       }

       if (s1[1] == "W") {
           windoze = false;
           found = true;
       }

       if (s1[1] == "$") {
           debug_info = true;
           found = true;
       }

       if (s1[1] == "#") {
           maxcode = value(ATR2FUNC::rstr(s1, s1.length() - 1)) - 1;
           found = true;
       }

       if (s1[1] == "!") {
           insane_missiles = true;
           if (s1.length() > 1) {
               insanity = value(ATR2FUNC::rstr(s1, s1.length() - 1))
           }
           found = true;
       }

       if (s1[1] == "@") {
           old_shields = true;
           found = true;
       }

       if (s1[1] == "E") {
           logging_errors = true;
           found = true;
       }

       if (insanity < 0) {
           insanity = 0;
       }

       if (insanity > 15) {
           insanity = 15;
       }
   } else if (s[1] = ";"){
           found = true;
   } else if (num_robots < max_robots && s != ""){
           num_robots++;
           create_robot(num_robots,s);
           found = true;
           if (num_robots == max_robots){
               cout << "Maximum number of robots reached." << "\n";
           }
   } else {
       prog_error(10,'');
   }

   if (!found){
       prog_error(8,s);
   }

}

void init_mine(int n, int detectrange, int size) {

   int i,j,k;
   k = -1;

   for (i = 0; i < max_mines; i++){
       if (((mine[i].x < 0) || (mine[i].x > 1000) || (mine[i].y < 0) || (mine[i].y > 1000) || (mine[i].yield <= 0)) && (k < 0)) {
           k = i;
       }
   }

   if (k >= 0){
       mine[k].x = x;
       mine[k].y = y;
       mine[k].detect = detectrange;
       mine[k].yield = size;
       mine[k].detonate = false;
//       click;
   }
}

int count_missiles(){

    int i,k;
    k = 0;

    for (i = 0; i < max_missiles; i++){
        if (missile[i].a > 0){
            k++;
        }
    }
    return k;
}

//procedure init_missile(xx,yy,xxv,yyv:real; dir,s,blast:integer; ob:boolean);
void init_missile(double xx,double yy,double xxv,double yyv,int dir,int s,int blast,bool ob){

    int i, j, k;
    double m;
    bool sound;

    k = -1;
//    click;
    for (i = max_missiles; i > 0; i--){
        if (missile[i].a = 0){
            k = i;
        }
    }

    if (k >= 0){
        missile[k].source = s;
        missile[k].x = xx;
        missile[k].lx = missile[k].x;
        missile[k].y = yy;
        missile[k].ly = missile[k].y;
        missile[k].rad = 0;
        missile[k].lrad = 0;

        if (ob = true){
            missile[k].mult = 1.25;
        } else {
            missile[k].mult = 1;
        }
        if (blast > 0){
            missile[k].max_rad = blast;
            missile[k].a = 2;
        } else {
            if ((s >= 0) && (s <= num_robots)){
                missile[k].mult = missile[k].mult*(robot[s].shotstrength);
                m = missile[k].mult;
            }
            if (ob = true){
                m = m + 0.25;
            }
            missile[k].mspd = missile_spd*missile[k].mult;
            if (insane_missiles = true){
                missile[k].mspd = 100 + (50 * insanity) * missile[k].mult;
            }
            if ((s >= 0) && (s <= num_robots)){
                robot[s].heat = robot[s].heat + round(20*m);
                robot[s].shots_fired++;
                robot[s].match_shots++;
            }
            missile[k].a = 1;
            missile[k].hd = dir;
            missile[k].max_rad = mis_radius;
            if (debug_info = true){
                do {
                    cout << "\n" << zero_pad(game_cycle, 5) << " F " << s << ": hd=" << hd << "           " << "\n";
                } while //(!keypressed)
                ATR2FUNC::FlushKey(); //still have to port FlushKey
            }
        }
    }

// (*The following was to see if teh missile array is big enough*)
//  {else
//   begin
//    sound:=sound_on;
//    sound_on:=true;
//    chirp;
//    sound_on:=sound;
//   end;
// setfillstyle(1,0);
// setcolor(robot_color(k));
// bar(5,5,37,12);
// outtextxy(5,5,cstr(count_missiles));}
}

//procedure damage(n,d:integer; physical:boolean);
void damage(int n, int d, bool physical){

// i,k,h,dd:integer;
    int i, k, h, dd;
// m:real;
    double m;

// if (n<0) or (n>num_robots) or (robot[n]^.armor<=0) then exit;
    if ((n < 0) || (n > num_robots) || (robot[n].armor <= 0)){
        exit();
    }
// if robot[n]^.config.shield<3 then robot[n]^.shields_up:=false;
    if (robot[n].config.shield < 3){
        robot[n].shields_up = false;
    }
 with robot[n]^ do
  begin
   h:=0;
   if (shields_up) and (not physical) then
    begin
     dd:=d;
     if (old_shields) and (config.shield>=3) then begin d:=0; h:=0; end
      else case config.shield of
       3:begin d:=round(dd*2/3); if d<1 then d:=1; h:=round(dd*2/3); end;
       4:begin h:=trunc(dd/2); d:=dd-h; end;
       5:begin d:=round(dd*1/3); if d<1 then d:=1;
               h:=round(dd*1/3); if h<1 then h:=1; end;
      end;
    end;
   if d<0 then d:=0;
   if debug_info then
    begin writeln(#13,zero_pad(game_cycle,5),' D ',n,': ',armor,'-',d,'=',armor-d,'           ');
    repeat until keypressed; flushkey; end;
   if d>0 then
    begin d:=round(d*damageadj); if d<1 then d:=1; end;
   dec(armor,d);
   inc(heat,h);
   last_damage:=0;
   if armor<=0 then
    begin
     armor:=0;
     update_armor(n);
     heat:=500;
     update_heat(n);
     armor:=0;
     inc(kill_count);
     inc(deaths);
     update_lives(n);
     if graphix and timing then time_delay(10);
     draw_robot(n);
     heat:=0;
     update_heat(n);
     init_missile(x,y,0,0,0,n,blast_circle,false);
     if overburn then m:=1.3 else m:=1;
     for i:=0 to num_robots do
      if (i<>n) and (robot[i]^.armor>0) then
       begin
        k:=round(distance(x,y,robot[i]^.x,robot[i]^.y));
        if k<blast_radius then
         damage(i,round(abs(blast_radius-k)*m),false);
       end;
    end;
  end;
end;
}

























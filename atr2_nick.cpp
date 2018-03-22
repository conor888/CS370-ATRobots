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
        if (missile[i].a == 0){
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

        if (ob == true){
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
            if (ob == true){
                m = m + 0.25;
            }
            missile[k].mspd = missile_spd*missile[k].mult;
            if (insane_missiles == true){
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
            if (debug_info == true){
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

void damage(int n, int d, bool physical){

    int i, k, h, dd;
    double m;

    if ((n < 0) || (n > num_robots) || (robot[n].armor <= 0)){
        exit();
    }
    if (robot[n].config.shield < 3){
        robot[n].shields_up = false;
    }

    h = 0;
    if ((robot[n].shields_up = true) && (physical != true)){
        dd = d;
        if ((robot[n].old_shields = true) && (robot[n].config.shield >= 3)){
            d = 0;
            h = 0;
        } else {
            switch(robot[n].config.shield){
                case 3:
                    d = round(dd*2/3);
                    if (d < 1){
                        d = 1;
                        h = round(dd*2/3)
                    }
                case 4:
                    h = trunc(dd/2);
                    d = dd-h;
                case 5:
                    d = round(dd*1/3);
                    if (d < 1){
                        d = 1;
                    }
                    h = round(dd*1/3);
                    if (h < 1){
                        h = 1;
                    }
            }
        }
    }
    if (d < 0) {
        d:=0;
    }
    if (robot[n].debug_info == true){
        do {
            cout << "\n" << zero_pad(robot[n].game_cycle,5) << " D " << n << ": " << robot[n].armor << "-" << d << "=" << robot[n].armor-d << "           ";
        } while //(!keypressed)
        ATR2FUNC::FlushKey(); //still have to port FlushKey
    }
    if (d > 0){
        d = round(d*robot[n].damageadj);
        if (d < 1){
            d = 1;
        }
    }
    robot[n].armor = robot[n].armor - d;
    robot[n].heat = robot[n].heat + h;
    robot[n].last_damage = 0;
    if (robot[n].armor <= 0){
        robot[n].armor = 0;
        update_armor(n);
        robot[n].heat = 500;
        update_heat(n);
        robot[n].armor = 0;
        robot[n].kill_count++;
        robot[n].deaths++;
        update_lives(n);
//     if graphix and timing then time_delay(10);
//     draw_robot(n);
        robot[n].heat = 0;
        update_heat(n);
        init_missile(robot[n].x,robot[n].y,0,0,0,n,robot[n].blast_circle,false);
        if (robot[n].overburn == true){
            m = 1.3;
        } else {
            m = 1;
        }
        for (i = 0; i < num_robots; i++){
            if ((i != n) && (robot[i].armor > 0)){
                k = round(distance(robot[n].x,robot[n].y,robot[i].x,robot[i].y));
                if (k < robot[n].blast_radius){
                    damage(i,round(abs(robot[n].blast_radius-k)*m),false);
                }
            }
        }
    }
}

void execute_instruction(int n){

    switch(get_val(n,ip,0)){
    case 25:
        k = get_val(n,ip,2);
        if ((k >= 0) && (k <= max_ram)){
            ram[k] = get_val(n,ip,1);
        }
        else {
            robot_error(n,4,cstr(k));
        }
        time_used = 2;
        executed++;

    case 26:
        call_int(n,get_val(n,ip,1),time_used);
        executed++;

    case 27:
        time_used = 4;
        put_val(n,ip,2,in_port(n,get_val(n,ip,1),time_used));
        executed;

    case 28:
        time_used = 4;
        out_port(n,get_val(n,ip,1),get_val(n,ip,2),time_used);
        executed++;

    case 29:
        time_used = get_val(n,ip,1);
        executed++;

    case 30:
        push(n,get_val(n,ip,1));
        executed++;

    case 31:
        put_val(n,ip,1,pop(n));
        executed++;

    case 32:
        robot_error(n,get_val(n,ip,1),"");
        time_used = 0;
        executed++;

    case 33:
        put_val(n,ip,1,get_val(n,ip,1)+1);
        executed++;

    case 34:
        put_val(n,ip,1,get_val(n,ip,1)-1);
        executed++;

    case 35:
        put_val(n,ip,1,get_val(n,ip,1) << get_val(n,ip,2));
        executed++;

    case 36:
        put_val(n,ip,1,get_val(n,ip,1) >> get_val(n,ip,2));
        executed++;

    case 37:
        put_val(n,ip,1,rol(get_val(n,ip,1),get_val(n,ip,2)));
        executed++;

    case 38:
        put_val(n,ip,1,ror(get_val(n,ip,1),get_val(n,ip,2)));
        executed++;

    case 39:
        time_used = 0;
        if ((ram[64]) && (8>0)) {
            jump(n,1,inc_ip);
        }
        executed++;

    case 40:
        time_used = 0;
        if ((ram[64]) && (8 == 0)) {
            jump(n,1,inc_ip);
        }
        executed++;

    case 41:
        if (((ram[64]) && (1 > 0)) || ((ram[64]) && (4 > 0))) {
            jump(n,1,inc_ip);
        }
        time_used = 0;
        executed++;

    case 42:
        if (((ram[64]) && (1 > 0)) || ((ram[64]) && (2 > 0))) {
            jump(n,1,inc_ip);
        }
        time_used = 0;
        executed++;

    case 43:
        put_val(n,ip,1,sal(get_val(n,ip,1),get_val(n,ip,2)));
        executed++;

    case 44:
        put_val(n,ip,1,sar(get_val(n,ip,1),get_val(n,ip,2)));
        executed++;

    case 45:
        put_val(n,ip,1,0-get_val(n,ip,1));
        executed++;

    case 46:
        loc = get_val(n,ip,1);
        if ((loc >= 0) && (loc <= plen)) {
            inc_ip = false;
            ip = loc;
        }
        else {
            robot_error(n,2,cstr(loc));
        }



    else {
        robot_error(n,6,"");
    }
}

    delay_left = delay_left + time_used;
    if (inc_ip) {
        ip++;
    }

//if graphix and (n=0) and (step_mode>0) then update_debug_window;

}

void score_robots(){

    int n,i,j,k,l;

    k = 0;
    n = -1;

    for (i = 0; i < num_robots; i++) {
        robot[i].trials++;
        if (robot[i].armor > 0) {
            k++;
            n = i;
        }
    }

    if ((k == 1) && (n >= 0)) {
        robot[n].wins++;
        robot[n].won = true;
    }
}

void do_mine(int n,m){
    int i,j,k,l;
    double d,r;
    bool source_alive;

    if ((x >= 0) && (x <= 1000) && (y >= 0) && (y <= 1000) && (yield>0)){
        for (i = 0; i < num_robots; i++){
            if ((robot[i].armor > 0) && (i != n)){
                d = distance(x,y,robot[i].x,robot[i].y);
                if (d <= detect){
                    detonate = true;
                }
            }
        }
        if (detonate == true){
            init_missile(x,y,0,0,0,n,mine_circle,false);
            kill_count = 0;
            if (robot[n].armor > 0){
                source_alive = true;
            } else {
                source_alive = false;
            }
            for (i = 0; i < num_robots; i++){
                if (robot[i].armor > 0) {
                    k = round(distance(x,y,robot[i].x,robot[i].y));
                    if (k < yield){
                        damage(i,round(abs(yield-k)),false);
                        if ((n >= 0) && (n <= num_robots) && (i != n)){
                            robot[n].damage_total = robot[n].damage_total + round(abs(yield-k));
                        }
                    }
                }
                if ((kill_count > 0) && (source_alive) && (robot[n].armor <= 0)){
                    kill_count--;
                }
                if (kill_count > 0){
                    robot[n].kills = robot[n].kills + kill_count;
                    update_lives(n);
                }
//                if graphix then
//                 putpixel(round(x*screen_scale)+screen_x,round(y*screen_scale)+screen_y,0);
//                yield:=0; x:=-1; y:=-1;
//               end
//              else
//               begin
//                (* Draw mine *)
//                if graphix and (game_cycle and 1=0) then
//                 begin
//                  main_viewport;
//                  setcolor(robot_color(n));
//                  line(round(x*screen_scale)+screen_x,round(y*screen_scale)+screen_y-1,
//                       round(x*screen_scale)+screen_x,round(y*screen_scale)+screen_y+1);
//                  line(round(x*screen_scale)+screen_x+1,round(y*screen_scale)+screen_y,
//                       round(x*screen_scale)+screen_x-1,round(y*screen_scale)+screen_y);

            }
        }
    }
}

procedure process_keypress(c:char);
begin
 case c of
   'C':calibrate_timing;
   'T':timing:=not timing;
   'A':show_arcs:=not show_arcs;
   'S','Q':begin
            if sound_on then chirp;
            sound_on:=not sound_on;
            if sound_on then chirp;
           end;
   '$':debug_info:=not debug_info;
   'W':windoze:=not windoze;
    #8:bout_over:=true;
   #27:begin quit:=true; step_loop:=false; end;
 end;
end;

void process_keypress(char c){
    switch(c){
    case "C":
        calibrate_timing();
    case "T":
        timing = false;
    case "A":
        show_arcs = false;
    case "S","Q":
        if (sound_on){
            chirp();
        }
        sound_on = false;
        if (sound_on){
            chirp();
        }
    case "$":
        debug_info = false;
    case "W":
        windoze = false;
    case "\b":
        bout_over = true;
    case GetAsyncKeyState(VK_ESCAPE):
        quit = true;
        step_loop = false
    }
}

bool graph_check(int n){
    bool ok;
    ok = true;
    if ((graphix == false) || (n < 0) || (n > num_robots) || (n >= max_shown)){
        ok = false;
    }
    return ok;
}

void robot_graph(int n){
    switch(stats_mode){
        case 1:
//            viewport(480,4+n*35,635,37+n*35);
            max_gx = 155;
            max_gy = 33;

        case 2:
//            viewport(480,4+n*13,635,15+n*13);
            max_gx = 155;
            max_gy = 11;

        else {
            viewport(480,4+n*70,635,70+n*70);
            max_gx = 155;
            max_gy = 66;
    }
    }
//    setfillstyle(1,robot_color(n));
//    setcolor(robsot_color(n));
}

void update_armor(int n){
    if (graph_check(n) && (step_mode <= 0)){
        robot_graph(n);
        if (robot[n].armor > 0){
            switch(stats_mode){
            case 1:
//                bar(30,13,29+robot[n].armor,18);

            case 2:
//                bar(88,03,87+(robot[n].armor shr 2),08);

            else {
//                bar(30,25,29+robot[n].armor,30);
            }
            }
        }
//        setfillstyle(1,8);
        if (robot[n].armor < 100){
            switch(stats_mode){
            case 1:
//                bar(30+robot[n].armor,13,129,18);

            case 2:
//                bar(88+(robot[n].armor shr 2),03,111,08);

            else {
//                bar(30+robot[n].armor,25,129,30);
            }
            }
        }
    }
}

void robot_error(int n, int i, string ov){
    if ((graph_check(n)) && (step_mode <= 0)){
        if (stats_mode == 0){
            robot_graph(n);
//            setfillstyle(1,0);
//            bar(66,56,154,64);
//            setcolor(robot_color(n));
//            outtextxy(66,56,addrear(cstr(i),7)+hex(i));
            chirp();
        }
        if (logging_errors){
            log_error(n,i,ov);
        }
        error_count++;
    }
}

void toggle_graphix(){
    graph_mode(!graphix);
    if (!graphix){
//        textcolor(7);
        cout << "Match " << played << "/" << matches << ", Battle in progress..." << "\n\n";
    }
    else {
        setscreen();
    }
}





















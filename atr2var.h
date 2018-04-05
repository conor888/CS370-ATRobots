#ifndef ATR2VAR_H
#define ATR2VAR_H

#include <iostream>
#include <fstream>
#include <cmath>
#include <cstring>
#include <iomanip>

class atr2var
{
public:
    atr2var();

    std::string
            progname        = "AT-Robots",
            version         = "2.11",
            cnotice1        = "Copyright 1997-99, Ed T. Toton III",
            cnotice2        = "All Rights Reserved.",
            cnotice3        = "Copyright 2014, William \"Amos\" Confer",
            main_filename   = "ATR2",
            robot_ext       = ".AT2",
            locked_ext      = ".ATL",
            config_ext      = ".ATS",
            compile_ext     = ".CMP",
            report_ext      = ".REP";

    static const bool
            _T = true,
            _F = false,

    //debugging/compiler
            show_code           = false,
            compile_by_line     = _F,
            debugging_compiler  = _F;

    static constexpr const double
            screen_scale = 0.46,
            //screen_scale = 0.92,
            pi = 3.1415926535897932385;

    static const int
            minint          = -32768,
            maxint          = 32768,
            max_var_len     = 16,

    //robots
            max_robots      = 32,
            max_code        = 1023,
            max_op          = 3,
            stack_size      = 256,
            stack_base      = 768,
            max_ram         = 1023,
            max_vars        = 256,
            max_labels      = 256,
            acceleration    = 4,
            turn_rate       = 8,
            max_vel         = 4,
            max_missiles    = 1023,
            missile_spd     = 32,
            hit_range       = 14,
            blast_radius    = 25,
            crash_range     = 8,
            max_sonar       = 250,
            com_queue       = 512,
            max_queue       = 255,
            max_config_points=12,
            max_mines       = 63,
            mine_blast      = 35,

    //simulator & graphics
    //screen_scale   =0.46,
            screen_x        = 5,
            screen_y        = 5,
            robot_scale     = 6,
            //robot_scale     = 12,
            default_delay   = 1,
            default_slice   = 5,
            max_robot_lines = 8;
    //Gray50 : FillPatternType = ($AA, $55, $AA, $55,
    //        $AA, $55, $AA, $55);

    struct op_rec {
        int op[max_op + 1];
    };

    typedef op_rec prog_type[max_code];

    struct config_rec {
        int scanner, weapon, armor, engine, heatsinks, shield, mines;
    };

    struct mine_rec {
        double x, y;
        int detect, yield;
        bool detonate;
    };

    struct robot_rec {
        //FIFI
        bool is_locked;
        int mem_watch;

        double x, y, lx, ly, xv, yv, speed, shotstrength, damageadj, speedadj, meters;
        int hd, thd, lhd, spd, tspd, armor, larmor, heat, lheat, ip,
                plen, scanarc, accuracy, shift, err, delay_left, robot_time_limit,
                max_time, time_left, lshift, arc_count, sonar_count, scanrange,
                last_damage, last_hit, transponder, shutdown, channel,
                lendarc, endarc, lstartarc, startarc, mines;
        int tx[max_robot_lines], ltx[max_robot_lines], ty[max_robot_lines], lty[max_robot_lines];
        long wins,  trials, kills, deaths, startkills, shots_fired, match_shots,
                hits, damage_total, cycles_lived, error_count;
        config_rec config;
        std::string name;
        std::string fn;
        bool shields_up, lshields, overburn, keepshift, cooling, won;
        prog_type code;
        int ram[max_ram];
        mine_rec mine[max_mines];
        std::ofstream errorlog;
    };

    typedef std::string parsetype[max_op + 1];

    //typedef &robot_rec robot_ptr;

    struct missile_rec {
        double x, y, lx, ly, mult, mspd;
        int source, a, hd, rad, lrad, max_rad;
    };


    //originally, these were static/const, but compiling failed on macOS (C++11 is supposed to allow it, but
    //                                                      it still doesn't work on clang for some reason?)
    int
    mine_circle     = (int)std::trunc(mine_blast*screen_scale) + 1,
    blast_circle    = (int)std::trunc(blast_radius*screen_scale) + 1,
    mis_radius      = (int)std::trunc(hit_range/2) + 1;


//Robot variables
    int num_robots;
//robot_ptr robot[max_robots + 4];
    robot_rec robot[max_robots + 4];
    missile_rec missile[max_missiles];

//Compiler variables
//ifstream f;
    int numvars, numlabels, maxcode, lock_pos, lock_dat;
    std::string varname[256]; //[max_var_len]
    int varloc[max_vars];
    std::string labelname[max_vars]; //[max_var_len]
    int labelnum[max_labels];
    bool show_source, compile_only;
    std::string lock_code;

//Simulator/graphics variables
//FIFI
    bool bout_over;     //made global from procedure bout
    int step_mode;      //0=off, for (0<step_mode<=9) = #of game cycles per step
    int temp_mode;      //stores previous step_mode for return to step
    int step_count;     //step counter used as break flag
    bool step_loop;     //break flag for stepping
//bool show_debugger;       //flag for viewing debugger panel vs. robot stats
// /FIFI
    bool old_shields, insane_missiles, debug_info, windoze, no_gfx, logging_errors,
            timinig, show_arcs;
    int game_delay, time_slice, insanity, update_timer, max_gx, max_gy, stats_mode;
    long game_limit, game_cycle, matches, played, executed;

//General settings
    bool quit, report, show_cnotice;
    int kill_count, report_type;




//Custom global variables (most from init() function)
    bool registered, sound_on, graphix, timing;
    std::string reg_name;
    int delay_per_sec, reg_num;
    
//Custom options
    bool show_executions = false, select_robot_e = false;
    int r_e = 0;
};

#endif // ATR2VAR_H

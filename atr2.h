//
// Created by conor on 3/21/2018.
//

#ifndef ATR2_H
#define ATR2_H

#include "atr2var.h"
#include "arena.h"
#include <QThread>
#include "atr2func.h"
#include <QEventLoop>
#include <QObject>
#include "rgraph.h"
#include "cgraph.h"
#include "window.h"
#include <QSoundEffect>

class arena;

class atr2 : public QObject {
Q_OBJECT

public:
    atr2(atr2var* avtemp, arena* parent, rgraph** rgraphstemp, cgraph *cyclegtemp, window* atr2wtemp);
    atr2(atr2var* avtemp);

    std::string operand(int n, int m);
    std::string mnemonic(int n, int m);
    void log_error(int n, int i, std::string ov);
    int max_shown();
    //bool graph_check(int n);
    //void robot_graph(int n);
    void update_armor(int n);                       //Not done
    void update_heat(int n); //Not done
    void robot_error(int n, int i, std::string ov);      //Not done
    void update_lives(int n);                       //Not done
    void update_cycle_window();
    //void setscreen();
    //void graph_mode(bool on);
    void prog_error(int n, std::string ss);
    void print_code(int n, int p);
    void parse1(int n, int p, atr2var::parsetype s);
    void check_plen(int plen);
    void compile(int n, std::string filename);
    void robot_config(int n);
    void reset_software(int n);
    void reset_hardware(int n);
    void init_robot(int n);
    void create_robot(int n, std::string filename);
    void shutdown();
    void delete_compile_report();                   //Skipped
    void write_compile_report();
    void parse_param(std::string s);
    void init(int argc, std::string argv[]);
    void draw_robot(int n);                         //Not done
    int get_from_ram(int n, int i, int j);
    int get_val(int n, int c, int o);
    void put_val(int n, int c, int o, int v);
    void push(int n, int v);
    int pop(int n);
    int find_label(int n, int l, int m);
    void init_mine(int n, int detectrange, int size);
    int count_missiles();
    void init_missile(double xx, double yy, double xxv, double yyv, int dir, int s, int blast, bool ob);
    void damage(int n, int d, bool physical);
    int scan(int n);
    void com_transmit(int n, int chan, int data);
    int com_receive(int n);
    int in_port(int n, int p, int &time_used);
    void out_port(int n, int p, int v, int &time_used);
    void call_int(int n, int int_num, int &time_used);
    void jump(int n, int o, bool &inc_ip);
    //void update_debug_bars();
    //void update_debug_system();
    //void update_debug_registers();
    //void update_debug_flags();
    //void update_debug_memory();
    //void update_debug_code();
    //void update_debug_window();
    //void init_debug_window();
    //void close_debug_window();
    bool gameover();
    //void toggle_graphix();
    bool invalid_microcode(int n, int ip);
    //void process_keypress(char c);
    void execute_instruction(int n);
    void do_robot(int n);
    void do_mine(int n, int m);                     //Not done
    void do_missile(int n);
    std::string victor_string(int k, int n);
    void show_statistics();
    void score_robots();
    void init_bout();
    void bout();
    void write_report();
    void begin_window();                            //Not done
    void click();
    void chirp();
    
private:
    atr2var *av;
    arena *atr2a;
    rgraph **rgraphs;
    cgraph *cycleg;
    window *atr2w;
    //QEventLoop *loop;

    QSoundEffect *click_sound, *chirp_sound;

signals:
    //void update_robot();
    //void update_missile();
    //void force_repaint();
};

#endif //ATR2_H

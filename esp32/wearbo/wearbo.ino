#include "bluetooth.hpp"
#include "flick.hpp"
#include "hand_writing.hpp"
#include "levenshtein_distance.hpp"
#include <M5StickC.h>

String output = "";

BleKeyboard bleKeyboard;

Wearbo wearbo = Wearbo(12);

Key dlt = Key(11, "dlt", "d", wearbo, true);
Key space = Key(10, "space", "s", wearbo, true);
Key ijkl = Key(9, "ijkl", "u", wearbo, false);
Key wxyzh = Key(8, "wxyzh", "j", wearbo, false);
Key pcqe = Key(7, "pcqe", "m", wearbo, false);
Key efgh = Key(6, "efgh", "y", wearbo, false);
Key rstuv = Key(5, "rstuv", "h", wearbo, false);
Key brqdq = Key(4, "brqdq", "n", wearbo, false);
Key abcd = Key(3, "abcd", "t", wearbo, false);
Key mnopq = Key(2, "mnopq", "g", wearbo, false);
Key assc = Key(1, "assc", "b", wearbo, false);
Key cul = Key(0, "cul", "c", wearbo, true);

Gesture spc = Gesture("s", 1, " ", 0);
Gesture delet = Gesture("d", 1, "BACKSPACE", 0);
Gesture enter = Gesture("dsm", 3, "ENTER", 0);
Gesture mode_10 = Gesture("cd", 2, "CHANGE_MODE1", 0);
Gesture mode_11 = Gesture("dc", 2, "CHANGE_MODE1", 0);
Gesture mode_20 = Gesture("sc", 2, "CHANGE_MODE2", 0);
Gesture mode_21 = Gesture("cs", 2, "CHANGE_MODE2", 0);
Gesture mode_30 = Gesture("sd", 2, "CHANGE_MODE3", 0);
Gesture mode_31 = Gesture("ds", 2, "CHANGE_MODE3", 0);
Gesture right = Gesture("ctyud", 5, "RIGHT", 0);
Gesture left = Gesture("duytc", 5, "LEFT", 0);

Gesture a = Gesture("t", 1, "a", 1);
Gesture b = Gesture("tc", 2, "b", 1);
Gesture c = Gesture("ty", 2, "c", 1);
Gesture d = Gesture("tg", 2, "d", 1);
Gesture e = Gesture("y", 1, "e", 1);
Gesture f = Gesture("yt", 2, "f", 1);
Gesture g = Gesture("yu", 2, "g", 1);
Gesture h = Gesture("yh", 2, "h", 1);
Gesture i = Gesture("u", 1, "i", 1);
Gesture j = Gesture("uy", 2, "j", 1);
Gesture k = Gesture("ud", 2, "k", 1);
Gesture l = Gesture("uj", 2, "l", 1);
Gesture m = Gesture("g", 1, "m", 1);
Gesture n = Gesture("gc", 2, "n", 1);
Gesture o = Gesture("gt", 2, "o", 1);
Gesture p = Gesture("gh", 2, "p", 1);
Gesture q = Gesture("gb", 2, "q", 1);
Gesture r = Gesture("h", 1, "r", 1);
Gesture s = Gesture("hg", 2, "s", 1);
Gesture t = Gesture("hy", 2, "t", 1);
Gesture u = Gesture("hj", 2, "u", 1);
Gesture v = Gesture("hn", 2, "v", 1);
Gesture w = Gesture("j", 1, "w", 1);
Gesture x = Gesture("jh", 2, "x", 1);
Gesture y = Gesture("ju", 2, "y", 1);
Gesture z = Gesture("js", 2, "z", 1);
Gesture hyphen = Gesture("jm", 2, "-", 1);
Gesture at = Gesture("b", 1, "@", 1);
Gesture slash = Gesture("bc", 2, "/", 1);
Gesture sharp = Gesture("bg", 2, "#", 1);
Gesture colon = Gesture("bn", 2, ":", 1);
Gesture brcl = Gesture("n", 1, "(", 1);
Gesture brcr = Gesture("nb", 2, ")", 1);
Gesture quot = Gesture("nh", 2, "\'", 1);
Gesture dubquot = Gesture("nm", 2, "\"", 1);
Gesture period = Gesture("m", 1, ".", 1);
Gesture comma = Gesture("mn", 2, ",", 1);
Gesture question = Gesture("mj", 2, "?", 1);
Gesture exclam = Gesture("ms", 2, "!", 1);
Gesture chuplow = Gesture("c", 1, "CHANGE_ULST", 1);

Gesture zero = Gesture("c", 1, "0", 2);
Gesture one = Gesture("t", 1, "1", 2);
Gesture two = Gesture("y", 1, "2", 2);
Gesture three = Gesture("u", 1, "3", 2);
Gesture four = Gesture("g", 1, "4", 2);
Gesture five = Gesture("h", 1, "5", 2);
Gesture six = Gesture("j", 1, "6", 2);
Gesture seven = Gesture("b", 1, "7", 2);
Gesture eight = Gesture("n", 1, "8", 2);
Gesture nine = Gesture("m", 1, "9", 2);

HandWriting a_hw = HandWriting("a", "u_y_t_g_b_n_j_u_j_m");
HandWriting a_hw2 = HandWriting("a", "j_y_g_n_j_m");
HandWriting b_hw = HandWriting("b", "t_g_b_h_b");
HandWriting b_hw2 = HandWriting("b", "t_g_b_g_h_n_b");
HandWriting b_hw3 = HandWriting("b", "y_h_n_j_n");
HandWriting b_hw4 = HandWriting("b", "y_h_n_h_j_m_n");
HandWriting b_hw5 = HandWriting("b", "t_g_b_h_j_m_n_b");
HandWriting b_hw6 = HandWriting("b", "y_h_n_j_n");
HandWriting c_hw = HandWriting("c", "u_y_t_g_b_n_m");
HandWriting d_hw = HandWriting("d", "j_h_n_m_j_u_j_m");
HandWriting d_hw2 = HandWriting("d", "h_g_b_n_h_y_h_n");
HandWriting d_hw3 = HandWriting("d", "m_h_n_m_j_u_j_m");
HandWriting d_hw4 = HandWriting("d", "b_f_v_b_g_t_g_b");
HandWriting d_hw5 = HandWriting("d", "m_h_g_b_n_m_j_u_j_m");
HandWriting e_hw = HandWriting("e","g_h_j_u_y_t_g_b_n_m");
HandWriting e_hw2 = HandWriting("e","g_h_j_y_g_b_n_m");
HandWriting f_hw = HandWriting("f","u_y_h_n_g_h_j");
HandWriting g_hw = HandWriting("g","u_y_h_j_u_j_m_n");
HandWriting g_hw2 = HandWriting("g","y_t_g_h_y_h_n_b");
HandWriting h_hw = HandWriting("h", "t_g_b_g_h_n");
HandWriting h_hw2 = HandWriting("h", "y_h_n_h_j_m");
HandWriting i_hw = HandWriting("i", "h_n_y");
HandWriting i_hw2 = HandWriting("i", "g_b_t");
HandWriting i_hw3 = HandWriting("i", "j_m_u");
HandWriting j_hw = HandWriting("j", "h_n_b_y");
HandWriting j_hw2 = HandWriting("j", "h_n_b_g_y");
HandWriting k_hw = HandWriting("k", "t_g_b_h_g_n");
HandWriting k_hw2 = HandWriting("k","y_h_n_j_h_m");
HandWriting k_hw3 = HandWriting("k","t_g_b_u_g_m");
HandWriting l_hw = HandWriting("l","y_h_n");
HandWriting l_hw2 = HandWriting("l","t_g_b");
HandWriting l_hw3 = HandWriting("l", "u_j_m");
HandWriting l_hw4 = HandWriting("l", "b_h_y_h_m");//これはあとで消すかも
HandWriting m_hw = HandWriting("m","t_g_b_g_y_h_n_h_u_j_m");
HandWriting n_hw = HandWriting("n", "t_g_b_g_y_u_j_m");
HandWriting o_hw = HandWriting("o", "y_t_g_b_n_m_j_u_y");
HandWriting p_hw = HandWriting("p", "t_g_b_t_y_h_g");
HandWriting p_hw2 = HandWriting("p", "t_y_h_g_t_g_b");
HandWriting p_hw3 = HandWriting("p", "y_u_j_h_y_h_n");
HandWriting p_hw4 = HandWriting("p", "y_h_n_y_u_j_h");
HandWriting p_hw5 = HandWriting("p", "t_y_u_j_h_g_t_g_b");
HandWriting p_hw6 = HandWriting("p", "t_g_b_t_y_u_j_h_g");
HandWriting q_hw = HandWriting("q", "u_y_h_j_u_j_m");
HandWriting q_hw2 = HandWriting("q", "y_t_g_h_y_h_n");
HandWriting q_hw3 = HandWriting("q", "u_y_t_g_h_j_u_j_m");
HandWriting r_hw = HandWriting("r", "t_g_b_g_y_u");
HandWriting r_hw2 = HandWriting("r", "t_g_b_g_h_u");
HandWriting s_hw = HandWriting("s", "u_y_t_g_h_j_m_n_b");
HandWriting t_hw = HandWriting("t", "g_h_j_y_h_n_m");
HandWriting u_hw = HandWriting("u", "t_g_b_n_j_u_j_m");
HandWriting v_hw = HandWriting("v", "t_g_n_j_u");
HandWriting w_hw = HandWriting("w", "t_g_b_h_y_h_m_j_u");
HandWriting x_hw = HandWriting("x", "t_h_m_u_h_b");
HandWriting y_hw = HandWriting("y", "t_h_u_h_b");
HandWriting z_hw = HandWriting("z", "t_y_u_h_b_n_m");

Gesture ges_lst[61] = {right, left, enter, mode_10, mode_11, mode_20, mode_21, mode_30, mode_31, b, c, d, f, g, h, j, k, l, n, o, p, q, s, t, u, v, x, y, z, hyphen, slash, sharp, colon, brcr, quot, dubquot, comma, question, exclam, spc, delet, a, e, i, m, r, w, at, brcl, period, chuplow, zero, one, two, three, four, five, six, seven, eight, nine};
HandWriting hw_lst[55] = {a_hw, a_hw2, b_hw, b_hw2, b_hw3, b_hw4, b_hw5, b_hw6, c_hw, d_hw, d_hw2, d_hw3, d_hw4, d_hw5, e_hw, e_hw2, f_hw, g_hw, g_hw2, h_hw, h_hw2, i_hw, i_hw2, i_hw3, j_hw, j_hw2, k_hw, k_hw2, k_hw3, l_hw, l_hw2, l_hw3, l_hw4, m_hw, n_hw, o_hw, p_hw, p_hw2, p_hw3, p_hw4,p_hw5,p_hw6, q_hw, q_hw2, q_hw3, r_hw, r_hw2, s_hw, t_hw, u_hw, v_hw, w_hw, x_hw, y_hw, z_hw};
int vib_pin = 26;

void setup()
{
    Serial.begin(115200);
    Serial.println("Starting wearbo");

    wearbo.m_cap = Adafruit_MPR121();

    if (!wearbo.m_cap.begin(0x5A)) {
        Serial.println("MPR121 not found, check wiring?");
        while (1)
            ;
    }
    Serial.println("MPR121 found!");

    M5.begin();
    bleKeyboard.begin();

    Wire.begin(32, 33);

    pinMode(vib_pin, OUTPUT);
}

void loop()
{
    output = "";
    wearbo.m_input_data = "";
    // m_input_time = "";
    wearbo.m_unique = false;
    wearbo.record();
    // dacWrite(vib_pin, 100);
    if (wearbo.m_mode == 1 || wearbo.m_mode == 2) {
        for (auto g : ges_lst) {
            if (wearbo.m_mode == g.m_mode || g.m_mode == 0) {
                output = g.judge_gesture(wearbo.m_input_data);
                if (output != "NOT") {
                    break;
                }
            }
        }
        //Serial.println(output);
        if (output == "CHANGE_ULST") {
            wearbo.change_ulst();
        } else if (output == "CHANGE_MODE1") {
            wearbo.change_mode(1);
        } else if (output == "CHANGE_MODE2") {
            wearbo.change_mode(2);
        } else if (output == "CHANGE_MODE3") {
            wearbo.change_mode(3);
        } else {
            if (wearbo.m_ulst == 1 && output.length() == 1) {
                send_ble(low2up(output.charAt(0)));
            } else {
                send_ble(output);
            }
        }
    } else if (wearbo.m_mode == 3) {
        if (wearbo.m_input_data.charAt(0) == 'd' || wearbo.m_input_data.charAt(0) == 'c') {
          //Serial.println(wearbo.m_input_data);
            for (auto g : ges_lst) {
                if (g.m_mode == 1 || g.m_mode == 0) {
                    output = g.judge_gesture(wearbo.m_input_data);
                    if (output != "NOT") {
                        break;
                    }
                }
            }
            //Serial.println(output);
            if (output == "CHANGE_ULST") {
                wearbo.change_ulst();
            } else if (output == "CHANGE_MODE1") {
                wearbo.change_mode(1);
            } else if (output == "CHANGE_MODE2") {
                wearbo.change_mode(2);
            } else if (output == "CHANGE_MODE3") {
                wearbo.change_mode(3);
            } else if (output == "BACKSPACE" || output == "ENTER" || output == "LEFT" || output == "RIGHT") {
                send_ble(output);
            }
        } else {
            if (wearbo.m_input_data.length() <= 1) {
                output = "";
            } else {
                //Serial.println("HANDWRITING");
                float dt_min = 100;
                //1shtein_distance((String)wearbo.m_input_data, pattern)の最小値を求める
                int len_n =  ((String)wearbo.m_input_data).length();
                for (auto hw : hw_lst) {
                    //Serial.println((String)wearbo.m_input_data);
                    int dist_tmp = levenshtein_distance((String)wearbo.m_input_data, hw.m_pattern);
                    //levenstein距離を正規化
                    int len_m =  hw.m_pattern.length();
                    float dt = 0;
                    if (len_n>len_m){
                        dt = (float)dist_tmp/len_n;
                    }
                    else{
                        dt = (float)dist_tmp/len_m;
                    }
                    //Serial.println("dist_tmp  "+hw.m_output);
                    //Serial.println(dt);
                    if (dt < dt_min){
                        dt_min = dt;
                        output = hw.m_output;
                    }
                }
                extern int i_FLAG;
                extern int y_FLAG;
                if ((y_FLAG == 1)&&(output == "y")){
                    output = "x";
                }
                if ((i_FLAG == 1)&&(output == "i")){
                    output = "j";
                }

                i_FLAG = 0;
                y_FLAG = 0;

     
            }
            if (wearbo.m_input_data.charAt(0) == 's'){
              output = "SPACE";
              //Serial.print(output);
            }
            if (wearbo.m_ulst == 1) {
                //Serial.println(low2up(output.charAt(0)));
                if (output != "SPACE"){
                  send_ble(low2up(output.charAt(0)));
                }
                else{
                  send_ble(output);
                }
            } else {
                //Serial.println(output);
                send_ble(output);
            }
            //Serial.println(output);
        }
    }
    // delay(80);
    // dacWrite(vib_pin, 0);
}

String low2up(char c)
{
    if (c >= 97 && c <= 122) {
        c = c - 32;
    }
    return (String)c;
}

#include "bluetooth.hpp"
// #include "config.hpp"
#include "flick.hpp"
// #include "wifi.hpp"
//#include <M5StickC.h>
#include "hand_writing.hpp"

String output = "";

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

// Gesture ges_lst[3][10] = {zero, one, two, three, four, five, six, seven, eight, nine};
Gesture ges_lst[61] = {right, left, enter, mode_10, mode_11, mode_20, mode_21, mode_30, mode_31, spc, delet, a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z, hyphen, at, slash, sharp, colon, brcl, brcr, quot, dubquot, period, comma, question, exclam, chuplow, zero, one, two, three, four, five, six, seven, eight, nine};

HandWriting a_hw = HandWriting("a", 11, "u", "m", "j");
HandWriting x_hw = HandWriting("x", 6, "t", "b", "m");
HandWriting b_hw = HandWriting("b", 7, "t", "b", "n");
HandWriting c_hw = HandWriting("c", 7, "u", "m", "g");
HandWriting d_hw = HandWriting("d", 8, "j", "m");
HandWriting d_hw2 = HandWriting("d", 8, "h", "n");
HandWriting e_hw = HandWriting("e", 10, "g", "m", "b");
HandWriting f_hw = HandWriting("f", 7, "u", "j");
HandWriting g_hw = HandWriting("g", 8, "u", "n");
HandWriting g_hw2 = HandWriting("g", 8, "y", "b");
HandWriting h_hw = HandWriting("h", 6, "t", "n");   // TODO
HandWriting h_hw2 = HandWriting("h", 6, "y", "m");  // TODO
HandWriting i_hw = HandWriting("i", 3, "h", "y");
HandWriting i_hw2 = HandWriting("i", 3, "g", "t");
HandWriting i_hw3 = HandWriting("i", 3, "j", "u");
HandWriting j_hw = HandWriting("j", 4, "h", "y", "b");
HandWriting j_hw2 = HandWriting("j", 4, "j", "u", "n");
HandWriting k_hw = HandWriting("k", 6, "t", "n");  // TODO
HandWriting p_hw2 = HandWriting("p", 7, "y", "n", "u");
HandWriting b_hw2 = HandWriting("b", 7, "y", "n", "m");
HandWriting q_hw2 = HandWriting("q", 7, "y", "n", "t");
HandWriting l_hw = HandWriting("l", 3, "y", "n");
HandWriting l_hw2 = HandWriting("l", 3, "t", "b");
HandWriting l_hw3 = HandWriting("l", 3, "u", "m");
HandWriting m_hw = HandWriting("m", 13, "t", "m");
HandWriting z_hw = HandWriting("z", 7, "t", "m", "h");
HandWriting n_hw = HandWriting("n", 9, "t", "m", "y");
HandWriting o_hw = HandWriting("o", 9, "y", "y");
HandWriting p_hw = HandWriting("p", 7, "t", "b", "y");
HandWriting q_hw = HandWriting("q", 7, "u", "m", "j");
HandWriting r_hw = HandWriting("r", 7, "t", "u", "y");
HandWriting s_hw = HandWriting("s", 9, "u", "b");
HandWriting t_hw = HandWriting("t", 7, "g", "m");
HandWriting u_hw = HandWriting("u", 9, "t", "m", "n");
HandWriting v_hw = HandWriting("v", 7, "t", "u", "n");
HandWriting w_hw = HandWriting("w", 10, "t", "u");
HandWriting y_hw = HandWriting("y", 5, "t", "b");

HandWriting hw_lst[37] = {a_hw, x_hw, b_hw, c_hw, d_hw, d_hw2, e_hw, f_hw, g_hw, g_hw2, h_hw, h_hw2, i_hw, i_hw2, i_hw3, j_hw, j_hw2, k_hw, p_hw2, b_hw2, q_hw2, l_hw, l_hw2, l_hw3, m_hw, z_hw, n_hw, o_hw, p_hw, q_hw, r_hw, s_hw, t_hw, u_hw, v_hw, w_hw, y_hw};


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

    Serial.println(ges_lst[1].m_output);
    // Serial.println(wearbo.m_key_lst[0]);

    // Gesture test[2] = {zero, one};

    // wearbo.m_ges_lst[10] = {zero, one, two, three, four, five, six, seven, eight, nine};
    //    M5.begin();

    // connectWiFi();
    // setup_client();

    // xTaskCreatePinnedToCore(task_main, "Task_main", 4096, NULL, 1, NULL, 0);
    // xTaskCreatePinnedToCore(task_recv, "Task_recv", 4096, NULL, 2, NULL, 1);
}

void loop()
{
    // wearbo.main();
    output = "";
    wearbo.m_input_data = "";
    // m_input_time = "";
    wearbo.m_unique = false;
    wearbo.record();
    if (wearbo.m_mode == 1 || wearbo.m_mode == 2) {
        for (auto g : ges_lst) {
            // Serial.println("serch");
            if (wearbo.m_mode == g.m_mode || g.m_mode == 0) {
                output = g.judge_gesture(wearbo.m_input_data);
                if (output != "NOT") {
                    break;
                }
            }
        }
        Serial.println(output);
        if (output == "CHANGE_ULST") {
            wearbo.change_ulst();
        } else if (output == "CHANGE_MODE1") {
            wearbo.change_mode(1);
        } else if (output == "CHANGE_MODE2") {
            wearbo.change_mode(2);
        } else if (output == "CHANGE_MODE3") {
            wearbo.change_mode(3);
        } else {
            if (wearbo.m_ulst == 1) {
                send_ble(low2up(output.charAt(0)));
            } else {
                send_ble(output);
            }
        }
    } else if (wearbo.m_mode == 3) {
        if (wearbo.m_input_data.charAt(0) == 'd' || wearbo.m_input_data.charAt(0) == 's' || wearbo.m_input_data.charAt(0) == 'c') {
            for (auto g : ges_lst) {
                if (wearbo.m_mode == g.m_mode || g.m_mode == 0) {
                    output = g.judge_gesture(wearbo.m_input_data);
                    if (output != "NOT") {
                        break;
                    }
                }
            }
            Serial.println(output);
            if (output == "CHANGE_ULST") {
                wearbo.change_ulst();
            } else if (output == "CHANGE_MODE1") {
                wearbo.change_mode(1);
            } else if (output == "CHANGE_MODE2") {
                wearbo.change_mode(2);
            } else if (output == "CHANGE_MODE3") {
                wearbo.change_mode(3);
            }
        } else {
            if (wearbo.m_input_data.length() == 0) {
                output = "=";
            } else {
                Serial.println("HANDWRITING");
                for (auto hw : hw_lst) {
                    if (hw.m_begin == (String)wearbo.m_input_data.charAt(0) && hw.m_end == (String)wearbo.m_input_data.charAt(wearbo.m_input_data.length() - 1)) {
                        output.concat(hw.m_output);
                    }
                }
                Serial.println(output);
                if (output.length() > 1) {
                    int dist[2][10] = {{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1}, {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1}};
                    int i = 0;
                    int index = 0;
                    for (auto hw : hw_lst) {
                        if (output.indexOf(hw.m_output) != -1 && hw.m_begin == (String)wearbo.m_input_data.charAt(0) && hw.m_end == (String)wearbo.m_input_data.charAt(wearbo.m_input_data.length() - 1)) {
                            dist[0][i] = abs((int)wearbo.m_input_data.length() - (int)hw.m_length);
                            dist[1][i] = index;
                            i++;
                        }
                        index++;
                    }
                    int min = 100;
                    int min_index = -1;
                    bool found = false;
                    Serial.println("For start");
                    for (i = 0; i < 10; i++) {
                        if (dist[0][i] == -1) {
                            break;
                        }
                        if (min > dist[0][i]) {
                            min = dist[0][i];
                            min_index = dist[1][i];
                            // if (!found) {
                            //     Serial.println("c");
                            found = true;
                            // }
                        } else if (min == dist[0][i]) {
                            if (hw_lst[dist[1][i]].m_via != "-" && wearbo.m_input_data.indexOf(hw_lst[dist[1][i]].m_via) != -1 && wearbo.m_input_data.indexOf(hw_lst[min_index].m_via) == -1) {
                                min_index = dist[1][i];
                            }
                        }
                    }
                    output = hw_lst[min_index].m_output;
                } else if (output.length() == 0) {
                    output = "=";
                }
            }
            // Serial.println(output);
            if (wearbo.m_ulst == 1) {
                send_ble(low2up(output.charAt(0)));
            } else {
                send_ble(output);
            }
        }
    }
}

String low2up(char c)
{
    if (c >= 97 && c <= 122) {
        c = c - 32;
    }
    return (String)c;
}

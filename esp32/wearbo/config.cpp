#include "config.hpp"

Wearbo wearbo = Wearbo(12);

Key dlt = Key(11, "delete", "-", wearbo, true);
Key space = Key(10, "space", "-", wearbo, true);
Key ijkl = Key(9, "ijkl", "u", wearbo, false);
Key wxyzh = Key(8, "wxyzh", "j", wearbo, false);
Key pcqe = Key(7, "pcqe", "m", wearbo, false);
Key efgh = Key(6, "efgh", "y", wearbo, false);
Key rstuv = Key(5, "rstuv", "h", wearbo, false);
Key brqdq = Key(4, "brqdq", "n", wearbo, false);
Key abcd = Key(3, "abcd", "t", wearbo, false);
Key mnopq = Key(2, "mnopq", "g", wearbo, false);
Key assc = Key(1, "assc", "b", wearbo, false);
Key cul = Key(0, "cul", "-", wearbo, true);

// String key_to_str(Key key_lst[], int len)
// {
//     String key_str = "";
//     for (int i = 0; i < len; i++) {
//         key_str.concat(key_lst[i].m_hwc);
//     }
//     return key_str;
// }
//
// Key klst = {space};
// String testtest = key_to_str(klst, 1);


// モード共通 0
Gesture spc = Gesture("-", 1, " ", 0);
// Gesture delet = Gesture({dlt}, 1, " ", 0);
// Gesture enter = Gesture({dlt, space, pcqe}, 3, " ", 0);
// Gesture mode_10 = Gesture({space, dlt}, 2, "CHANGE_MODE1", 0);
// Gesture mode_11 = Gesture({dlt, space}, 2, "CHANGE_MODE1", 0);
// Gesture mode_20 = Gesture({space, cul}, 2, "CHANGE_MODE2", 0);
// Gesture mode_21 = Gesture({cul, space}, 2, "CHANGE_MODE2", 0);
// Gesture right = Gesture({cul, abcd, efgh, ijkl, dlt}, 5, "RIGHT", 0);
// Gesture left = Gesture({dlt, ijkl, efgh, abcd, cul}, 5, "LEFT", 0);

// アルファベットフリック入力モード 1
// Gesture a = Gesture({abcd}, 1, "a", 1);
// Gesture b = Gesture({abcd, cul}, 2, "b", 1);
// Gesture c = Gesture({abcd, efgh}, 2, "c", 1);
// Gesture d = Gesture({abcd, mnopq}, 2, "d", 1);
// Gesture e = Gesture({efgh}, 1, "e", 1);
// Gesture f = Gesture({efgh, abcd}, 2, "f", 1);
// Gesture g = Gesture({efgh, ijkl}, 2, "g", 1);
// Gesture h = Gesture({efgh, rstuv}, 2, "h", 1);
// Gesture i = Gesture({ijkl}, 1, "i", 1);
// Gesture j = Gesture({ijkl, efgh}, 2, "j", 1);
// Gesture k = Gesture({ijkl, dlt}, 2, "k", 1);
// Gesture l = Gesture({ijkl, wxyzh}, 2, "l", 1);
// Gesture m = Gesture({mnopq}, 1, "m", 1);
// Gesture n = Gesture({mnopq, cul}, 2, "n", 1);
// Gesture o = Gesture({mnopq, abcd}, 2, "o", 1);
// Gesture p = Gesture({mnopq, rstuv}, 2, "p", 1);
// Gesture q = Gesture({mnopq, assc}, 2, "q", 1);
// Gesture r = Gesture({rstuv}, 1, "r", 1);
// Gesture s = Gesture({rstuv, mnopq}, 2, "s", 1);
// Gesture t = Gesture({rstuv, efgh}, 2, "t", 1);
// Gesture u = Gesture({rstuv, wxyzh}, 2, "u", 1);
// Gesture v = Gesture({rstuv, brqdq}, 2, "v", 1);
// Gesture w = Gesture({wxyzh}, 1, "w", 1);
// Gesture x = Gesture({wxyzh, rstuv}, 2, "x", 1);
// Gesture y = Gesture({wxyzh, ijkl}, 2, "y", 1);
// Gesture z = Gesture({wxyzh, space}, 2, "z", 1);
// Gesture hyphen = Gesture({wxyzh, pcqe}, 2, "-", 1);
// Gesture at = Gesture({assc}, 1, "@", 1);
// Gesture slash = Gesture({assc, cul}, 2, "/", 1);
// Gesture sharp = Gesture({assc, mnopq}, 2, "#", 1);
// Gesture colon = Gesture({assc, brqdq}, 2, ":", 1);
// Gesture brcl = Gesture({brqdq}, 1, "(", 1);
// Gesture brcr = Gesture({brqdq, assc}, 2, ")", 1);
// Gesture quot = Gesture({brqdq, rstuv}, 2, "\'", 1);
// Gesture dubquot = Gesture({brqdq, pcqe}, 2, "\"", 1);
// Gesture period = Gesture({pcqe}, 1, ".", 1);
// Gesture comma = Gesture({pcqe, brqdq}, 2, ",", 1);
// Gesture question = Gesture({pcqe, wxyzh}, 2, "?", 1);
// Gesture exclam = Gesture({pcqe, space}, 2, "!", 1);
// Gesture chuplow = Gesture({cul}, 1, "CHANGE_ULST", 1);

// Gesture zero = Gesture({cul}, 1, "0", 2);
// Gesture one = Gesture({abcd}, 1, "1", 2);
// Gesture two = Gesture({efgh}, 1, "2", 2);
// Gesture three = Gesture({ijkl}, 1, "3", 2);
// Gesture four = Gesture({mnopq}, 1, "4", 2);
// Gesture five = Gesture({rstuv}, 1, "5", 2);
// Gesture six = Gesture({wxyzh}, 1, "6", 2);
// Gesture seven = Gesture({assc}, 1, "7", 2);
// Gesture eight = Gesture({brqdq}, 1, "8", 2);
// Gesture nine = Gesture({pcqe}, 1, "9", 2);

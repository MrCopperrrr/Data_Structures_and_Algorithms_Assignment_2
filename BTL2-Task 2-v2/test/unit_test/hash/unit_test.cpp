#include "unit_test.hpp"

map<string, bool (UNIT_TEST_Hash::*)()> UNIT_TEST_Hash::TESTS;

// TODO unit test new

void newINT_delete(int* value) { delete value; }
bool newINT_EQ(int*& a, int*& b) { return *a == *b; }
int newINT_keyHash(int*& key, int capacity) { return *key % capacity; }
string newINT_toString(int*& key) { return "n_" + to_string(*key); }

bool UNIT_TEST_Hash::hash01() {
  string name = "hash01";
  //! data ------------------------------------
  xMap<int, string> hash(xMap<int, string>::intKeyHash);

  //! expect ----------------------------------
  string expect =
      "\n\
==================================================\n\
capacity:   10\n\
size:       0\n\
0   : \n\
1   : \n\
2   : \n\
3   : \n\
4   : \n\
5   : \n\
6   : \n\
7   : \n\
8   : \n\
9   : \n\
==================================================\n";

  //! output ----------------------------------
  stringstream output;
  output << "\n" << hash.toString();

  //! remove data -----------------------------

  //! result ----------------------------------
  return printResult(output.str(), expect, name);
}

bool UNIT_TEST_Hash::hash02() {
  string name = "hash02";
  //! data ------------------------------------
  xMap<int, string> hash(xMap<int, string>::intKeyHash);
  xMap<int, string> copy(hash);
  //! expect ----------------------------------
  string expect =
      "\n\
==================================================\n\
capacity:   10\n\
size:       0\n\
0   : \n\
1   : \n\
2   : \n\
3   : \n\
4   : \n\
5   : \n\
6   : \n\
7   : \n\
8   : \n\
9   : \n\
==================================================\n";

  //! output ----------------------------------
  stringstream output;
  output << "\n" << copy.toString();

  //! remove data -----------------------------

  //! result ----------------------------------
  return printResult(output.str(), expect, name);
}

bool UNIT_TEST_Hash::hash03() {
  string name = "hash03";
  //! data ------------------------------------
  xMap<int, string> hash(xMap<int, string>::intKeyHash);
  xMap<int, string> copy(xMap<int, string>::intKeyHash);
  copy = hash;
  //! expect ----------------------------------
  string expect =
      "\n\
==================================================\n\
capacity:   10\n\
size:       0\n\
0   : \n\
1   : \n\
2   : \n\
3   : \n\
4   : \n\
5   : \n\
6   : \n\
7   : \n\
8   : \n\
9   : \n\
==================================================\n";

  //! output ----------------------------------
  stringstream output;
  output << "\n" << hash.toString();

  //! remove data -----------------------------

  //! result ----------------------------------
  return printResult(output.str(), expect, name);
}

bool UNIT_TEST_Hash::hash04() {
  string name = "hash04";
  //! data ------------------------------------
  xMap<int, string> hash(xMap<int, string>::intKeyHash);
  hash.put(1, "votien1");
  //! expect ----------------------------------
  string expect =
      "\n\
==================================================\n\
capacity:   10\n\
size:       1\n\
0   : \n\
1   :  (1,votien1)\n\
2   : \n\
3   : \n\
4   : \n\
5   : \n\
6   : \n\
7   : \n\
8   : \n\
9   : \n\
==================================================\n";

  //! output ----------------------------------
  stringstream output;
  output << "\n" << hash.toString();

  //! remove data -----------------------------

  //! result ----------------------------------
  return printResult(output.str(), expect, name);
}

bool UNIT_TEST_Hash::hash05() {
  string name = "hash05";
  //! data ------------------------------------
  xMap<int, string> hash(xMap<int, string>::intKeyHash);
  hash.put(1, "votien1");
  hash.put(11, "votien11");
  hash.put(21, "votien21");
  hash.put(2, "votien2");
  hash.put(10, "votien10");

  //! expect ----------------------------------
  string expect =
      "\n\
==================================================\n\
capacity:   10\n\
size:       5\n\
0   :  (10,votien10)\n\
1   :  (1,votien1); (11,votien11); (21,votien21)\n\
2   :  (2,votien2)\n\
3   : \n\
4   : \n\
5   : \n\
6   : \n\
7   : \n\
8   : \n\
9   : \n\
==================================================\n";

  //! output ----------------------------------
  stringstream output;
  output << "\n" << hash.toString();

  //! remove data -----------------------------

  //! result ----------------------------------
  return printResult(output.str(), expect, name);
}

bool UNIT_TEST_Hash::hash06() {
  string name = "hash06";
  //! data ------------------------------------
  xMap<int, string> hash(xMap<int, string>::intKeyHash, 0.6);
  hash.put(1, "votien1");
  hash.put(11, "votien11");
  hash.put(21, "votien21");
  hash.put(31, "votien31");
  hash.put(41, "votien41");
  hash.put(51, "votien51");
  hash.put(61, "votien61");
  //! expect ----------------------------------
  string expect =
      "\n\
==================================================\n\
capacity:   15\n\
size:       7\n\
0   : \n\
1   :  (1,votien1); (31,votien31); (61,votien61)\n\
2   : \n\
3   : \n\
4   : \n\
5   : \n\
6   :  (21,votien21); (51,votien51)\n\
7   : \n\
8   : \n\
9   : \n\
10  : \n\
11  :  (11,votien11); (41,votien41)\n\
12  : \n\
13  : \n\
14  : \n\
==================================================\n";

  //! output ----------------------------------
  stringstream output;
  output << "\n" << hash.toString();

  //! remove data -----------------------------

  //! result ----------------------------------
  return printResult(output.str(), expect, name);
}

bool UNIT_TEST_Hash::hash07() {
  string name = "hash07";
  //! data ------------------------------------
  xMap<int*, string> hash(&newINT_keyHash, 0.45, 0,
                          xMap<int*, string>::freeKey);

  hash.put(new int(1), "votien1");
  hash.put(new int(11), "votien11");
  hash.put(new int(3), "votien3");
  //! expect ----------------------------------
  string expect =
      "\n\
==================================================\n\
capacity:   10\n\
size:       3\n\
0   : \n\
1   :  (n_1,votien1); (n_11,votien11)\n\
2   : \n\
3   :  (n_3,votien3)\n\
4   : \n\
5   : \n\
6   : \n\
7   : \n\
8   : \n\
9   : \n\
==================================================\n";

  //! output ----------------------------------
  stringstream output;
  output << "\n" << hash.toString(&newINT_toString);

  //! remove data -----------------------------

  //! result ----------------------------------
  return printResult(output.str(), expect, name);
}

bool UNIT_TEST_Hash::hash08() {
  string name = "hash08";
  stringstream output;
  //! data ------------------------------------
  xMap<int*, string> hash(&newINT_keyHash, 1, 0, xMap<int*, string>::freeKey,
                          &newINT_EQ);
  int *key, *value;
  string s;

  hash.put(new int(1), "votien1");
  hash.put(new int(11), "votien11");
  hash.put(new int(3), "votien3");

  key = new int(1);
  output << hash.put(key, "votien_1");
  delete key;

  hash.put(new int(21), "votien21");
  hash.put(new int(31), "votien31");
  hash.put(new int(41), "votien41");
  hash.put(new int(51), "votien51");

  key = new int(11);
  output << hash.put(key, "votien_11");
  delete key;

  xMap<int*, string> copy(&newINT_keyHash);
  copy = hash;

  //! expect ----------------------------------
  string expect =
      "votien1votien11\n\
==================================================\n\
capacity:   10\n\
size:       7\n\
0   : \n\
1   :  (n_1,votien_1); (n_11,votien_11); (n_21,votien21); (n_31,votien31); (n_41,votien41); (n_51,votien51)\n\
2   : \n\
3   :  (n_3,votien3)\n\
4   : \n\
5   : \n\
6   : \n\
7   : \n\
8   : \n\
9   : \n\
==================================================\n";

  //! output ----------------------------------
  output << "\n" << copy.toString(&newINT_toString);

  //! remove data -----------------------------

  //! result ----------------------------------
  return printResult(output.str(), expect, name);
}

bool UNIT_TEST_Hash::hash09() {
  string name = "hash09";
  //! data ------------------------------------
  xMap<int, string> hash(xMap<int, string>::intKeyHash, 0.6);
  hash.put(1, "votien1");
  hash.put(11, "votien11");
  hash.put(21, "votien21");
  hash.put(31, "votien31");
  hash.put(41, "votien41");
  hash.put(51, "votien51");
  hash.put(61, "votien61");
  hash.put(2, "votien2");
  hash.put(3, "votien3");
  hash.put(1, "votien_1");

  //! expect ----------------------------------
  string expect =
      "\n\
==================================================\n\
capacity:   15\n\
size:       9\n\
0   : \n\
1   :  (1,votien_1); (31,votien31); (61,votien61)\n\
2   :  (2,votien2)\n\
3   :  (3,votien3)\n\
4   : \n\
5   : \n\
6   :  (21,votien21); (51,votien51)\n\
7   : \n\
8   : \n\
9   : \n\
10  : \n\
11  :  (11,votien11); (41,votien41)\n\
12  : \n\
13  : \n\
14  : \n\
==================================================\n";

  //! output ----------------------------------
  stringstream output;
  output << "\n" << hash.toString();

  //! remove data -----------------------------

  //! result ----------------------------------
  return printResult(output.str(), expect, name);
}

bool UNIT_TEST_Hash::hash10() {
  string name = "hash10";
  //! data ------------------------------------
  xMap<int, string> hash(xMap<int, string>::intKeyHash, 0.6);
  hash.put(1, "votien1");
  hash.put(11, "votien11");
  hash.put(21, "votien21");
  hash.put(31, "votien31");
  hash.put(41, "votien41");
  hash.put(51, "votien51");
  hash.put(61, "votien61");
  hash.put(2, "votien2");
  hash.put(3, "votien3");
  hash.put(1, "votien_1");

  //! expect ----------------------------------
  string expect = "votien_1";

  //! output ----------------------------------
  stringstream output;
  try {
    output << hash.get(1);
  } catch (const KeyNotFound& e) {
    output << "Caught exception: " << e.what() << std::endl;
  }

  //! remove data -----------------------------

  //! result ----------------------------------
  return printResult(output.str(), expect, name);
}

bool UNIT_TEST_Hash::hash11() {
  string name = "hash11";
  //! data ------------------------------------
  xMap<int, string> hash(xMap<int, string>::intKeyHash, 0.6);
  hash.put(1, "votien1");
  hash.put(11, "votien11");
  hash.put(21, "votien21");
  hash.put(31, "votien31");
  hash.put(41, "votien41");
  hash.put(51, "votien51");
  hash.put(61, "votien61");
  hash.put(2, "votien2");
  hash.put(3, "votien3");
  hash.put(1, "votien_1");

  //! expect ----------------------------------
  string expect = "Caught exception: key (0) is not found";

  //! output ----------------------------------
  stringstream output;
  try {
    output << hash.get(0);
  } catch (const KeyNotFound& e) {
    output << "Caught exception: " << e.what();
  }

  //! remove data -----------------------------

  //! result ----------------------------------
  return printResult(output.str(), expect, name);
}

bool UNIT_TEST_Hash::hash12() {
  string name = "hash12";
  //! data ------------------------------------
  xMap<int, string> hash(xMap<int, string>::intKeyHash, 0.6);
  hash.put(1, "votien1");
  hash.put(11, "votien11");
  hash.put(21, "votien21");
  hash.put(31, "votien31");
  hash.put(41, "votien41");
  hash.put(51, "votien51");
  hash.put(61, "votien61");
  hash.put(2, "votien2");
  hash.put(3, "votien3");
  hash.put(1, "votien_1");

  //! expect ----------------------------------
  string expect =
      "votien_1\n\
==================================================\n\
capacity:   15\n\
size:       8\n\
0   : \n\
1   :  (31,votien31); (61,votien61)\n\
2   :  (2,votien2)\n\
3   :  (3,votien3)\n\
4   : \n\
5   : \n\
6   :  (21,votien21); (51,votien51)\n\
7   : \n\
8   : \n\
9   : \n\
10  : \n\
11  :  (11,votien11); (41,votien41)\n\
12  : \n\
13  : \n\
14  : \n\
==================================================\n";

  //! output ----------------------------------
  stringstream output;
  try {
    output << hash.remove(1) << endl;
  } catch (const KeyNotFound& e) {
    output << "Caught exception: " << e.what();
  }
  output << hash.toString();

  //! remove data -----------------------------

  //! result ----------------------------------
  return printResult(output.str(), expect, name);
}

bool UNIT_TEST_Hash::hash13() {
  string name = "hash13";
  //! data ------------------------------------
  xMap<int, string> hash(xMap<int, string>::intKeyHash, 0.6);
  hash.put(1, "votien1");
  hash.put(11, "votien11");
  hash.put(21, "votien21");
  hash.put(31, "votien31");
  hash.put(41, "votien41");
  hash.put(51, "votien51");
  hash.put(61, "votien61");
  hash.put(2, "votien2");
  hash.put(3, "votien3");
  hash.put(1, "votien_1");

  //! expect ----------------------------------
  string expect =
      "Caught exception: key (0) is not found\n\
==================================================\n\
capacity:   15\n\
size:       9\n\
0   : \n\
1   :  (1,votien_1); (31,votien31); (61,votien61)\n\
2   :  (2,votien2)\n\
3   :  (3,votien3)\n\
4   : \n\
5   : \n\
6   :  (21,votien21); (51,votien51)\n\
7   : \n\
8   : \n\
9   : \n\
10  : \n\
11  :  (11,votien11); (41,votien41)\n\
12  : \n\
13  : \n\
14  : \n\
==================================================\n";

  //! output ----------------------------------
  stringstream output;
  try {
    output << hash.remove(0) << endl;
  } catch (const KeyNotFound& e) {
    output << "Caught exception: " << e.what() << std::endl;
  }
  output << hash.toString();

  //! remove data -----------------------------

  //! result ----------------------------------
  return printResult(output.str(), expect, name);
}

bool UNIT_TEST_Hash::hash14() {
  string name = "hash14";
  //! data ------------------------------------
  xMap<int, string> hash(xMap<int, string>::intKeyHash, 0.6);
  hash.put(1, "votien1");
  hash.put(11, "votien11");
  hash.put(21, "votien21");
  hash.put(31, "votien31");
  hash.put(41, "votien41");
  hash.put(51, "votien51");
  hash.put(61, "votien61");
  hash.put(2, "votien2");
  hash.put(3, "votien3");
  hash.put(1, "votien_1");

  //! expect ----------------------------------
  string expect = "True";

  //! output ----------------------------------
  stringstream output;
  output << (hash.containsKey(51) ? "True" : "False");

  //! remove data -----------------------------

  //! result ----------------------------------
  return printResult(output.str(), expect, name);
}

bool UNIT_TEST_Hash::hash15() {
  string name = "hash15";
  //! data ------------------------------------
  xMap<int, string> hash(xMap<int, string>::intKeyHash, 0.6);
  hash.put(1, "votien1");
  hash.put(11, "votien11");
  hash.put(21, "votien21");
  hash.put(31, "votien31");
  hash.put(41, "votien41");
  hash.put(51, "votien51");
  hash.put(61, "votien61");
  hash.put(2, "votien2");
  hash.put(3, "votien3");
  hash.put(1, "votien_1");

  //! expect ----------------------------------
  string expect = "False";

  //! output ----------------------------------
  stringstream output;
  output << (hash.containsKey(71) ? "True" : "False");

  //! remove data -----------------------------

  //! result ----------------------------------
  return printResult(output.str(), expect, name);
}

bool UNIT_TEST_Hash::hash16() {
  string name = "hash16";
  //! data ------------------------------------
  xMap<int, string> hash(xMap<int, string>::intKeyHash, 0.6);
  hash.put(1, "votien1");
  hash.put(11, "votien11");
  hash.put(21, "votien21");
  hash.put(31, "votien31");
  hash.put(41, "votien41");
  hash.put(51, "votien51");
  hash.put(61, "votien61");
  hash.put(2, "votien2");
  hash.put(3, "votien3");
  hash.put(1, "votien_1");

  //! expect ----------------------------------
  string expect = "False";

  //! output ----------------------------------
  stringstream output;
  output << (hash.containsKey(22) ? "True" : "False");

  //! remove data -----------------------------

  //! result ----------------------------------
  return printResult(output.str(), expect, name);
}

bool UNIT_TEST_Hash::hash17() {
  string name = "hash17";
  //! data ------------------------------------
  xMap<int, string> hash(xMap<int, string>::intKeyHash, 0.6);
  hash.put(1, "votien1");
  hash.put(11, "votien11");
  hash.put(21, "votien21");
  hash.put(31, "votien31");
  hash.put(41, "votien41");
  hash.put(51, "votien51");
  hash.put(61, "votien61");
  hash.put(2, "votien2");
  hash.put(3, "votien3");
  hash.put(1, "votien_1");

  //! expect ----------------------------------
  string expect = "True";

  //! output ----------------------------------
  stringstream output;
  output << (hash.containsValue("votien_1") ? "True" : "False");

  //! remove data -----------------------------

  //! result ----------------------------------
  return printResult(output.str(), expect, name);
}

bool UNIT_TEST_Hash::hash18() {
  string name = "hash18";
  //! data ------------------------------------
  xMap<int, string> hash(xMap<int, string>::intKeyHash, 0.6);
  hash.put(1, "votien1");
  hash.put(11, "votien11");
  hash.put(21, "votien21");
  hash.put(31, "votien31");
  hash.put(41, "votien41");
  hash.put(51, "votien51");
  hash.put(61, "votien61");
  hash.put(2, "votien2");
  hash.put(3, "votien3");
  hash.put(1, "votien_1");

  //! expect ----------------------------------
  string expect = "False";

  //! output ----------------------------------
  stringstream output;
  output << (hash.containsValue("votien_2") ? "True" : "False");

  //! remove data -----------------------------

  //! result ----------------------------------
  return printResult(output.str(), expect, name);
}

bool UNIT_TEST_Hash::hash19() {
  string name = "hash19";
  //! data ------------------------------------
  xMap<int, string> hash(xMap<int, string>::intKeyHash, 0.6);
  hash.put(1, "votien1");
  hash.put(11, "votien11");
  hash.put(21, "votien21");
  hash.put(31, "votien31");
  hash.put(41, "votien41");
  hash.put(51, "votien51");
  hash.put(61, "votien61");
  hash.put(2, "votien2");
  hash.put(3, "votien3");
  hash.put(1, "votien_1");

  //! expect ----------------------------------
  string expect = "False";

  //! output ----------------------------------
  stringstream output;
  output << (hash.containsValue("votien_71") ? "True" : "False");

  //! remove data -----------------------------

  //! result ----------------------------------
  return printResult(output.str(), expect, name);
}

bool UNIT_TEST_Hash::hash20() {
  string name = "hash20";
  //! data ------------------------------------
  xMap<int, string> hash(xMap<int, string>::intKeyHash, 0.6);
  hash.put(1, "votien1");
  hash.put(11, "votien11");
  hash.put(21, "votien21");
  hash.put(31, "votien31");
  hash.put(41, "votien41");
  hash.put(51, "votien51");
  hash.put(61, "votien61");
  hash.put(2, "votien2");
  hash.put(3, "votien3");
  hash.put(1, "votien_1");

  //! expect ----------------------------------
  string expect = "[1, 31, 61, 2, 3, 21, 51, 11, 41]";

  //! output ----------------------------------
  stringstream output;
  output << hash.keys().toString();

  //! remove data -----------------------------

  //! result ----------------------------------
  return printResult(output.str(), expect, name);
}

bool UNIT_TEST_Hash::hash21() {
  string name = "hash21";
  //! data ------------------------------------
  xMap<int, string> hash(xMap<int, string>::intKeyHash, 0.6);
  hash.put(1, "votien1");
  hash.put(11, "votien11");
  hash.put(21, "votien21");
  hash.put(31, "votien31");
  hash.put(41, "votien41");
  hash.put(51, "votien51");
  hash.put(61, "votien61");
  hash.put(2, "votien2");
  hash.put(3, "votien3");
  hash.put(1, "votien_1");

  //! expect ----------------------------------
  string expect =
      "[votien_1, votien31, votien61, votien2, votien3, votien21, votien51, "
      "votien11, votien41]";

  //! output ----------------------------------
  stringstream output;
  output << hash.values().toString();

  //! remove data -----------------------------

  //! result ----------------------------------
  return printResult(output.str(), expect, name);
}

bool UNIT_TEST_Hash::hash22() {
  string name = "hash22";

  //! data ------------------------------------
  xMap<int, string> hash(xMap<int, string>::intKeyHash, 0.6);
  hash.put(1, "votien1");
  hash.put(11, "votien11");
  hash.put(21, "votien21");
  hash.put(31, "votien31");
  hash.put(41, "votien41");
  hash.put(51, "votien51");
  hash.put(61, "votien61");
  hash.put(2, "votien2");
  hash.put(3, "votien3");
  hash.put(1, "votien_1");

  //! expect ----------------------------------
  string expect = "[0, 3, 1, 1, 0, 0, 2, 0, 0, 0, 0, 2, 0, 0, 0]";

  //! output ----------------------------------
  stringstream output;
  output << hash.clashes().toString();

  //! remove data -----------------------------

  //! result ----------------------------------
  return printResult(output.str(), expect, name);
}

bool UNIT_TEST_Hash::hash23() {
  string name = "hash23";
  //! data ------------------------------------
  xMap<int, string> hash(xMap<int, string>::intKeyHash, 0.5);
  hash.put(1, "votien1");
  hash.put(11, "votien11");
  hash.put(21, "votien21");
  hash.put(31, "votien31");
  hash.put(41, "votien41");
  hash.put(51, "votien51");
  hash.put(61, "votien61");
  hash.put(2, "votien2");
  hash.put(3, "votien3");
  hash.put(1, "votien_1");

  //! expect ----------------------------------
  string expect =
      "0\n\
[1, 2, 3, 51, 31, 11, 61, 41, 21]\n\
[votien_1, votien2, votien3, votien51, votien31, votien11, votien61, votien41, votien21]\n\
[0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1]";

  //! output ----------------------------------
  stringstream output;
  output << hash.empty() << endl;
  output << hash.keys().toString() << endl;
  output << hash.values().toString() << endl;
  output << hash.clashes().toString();

  //! remove data -----------------------------

  //! result ----------------------------------
  return printResult(output.str(), expect, name);
}

bool UNIT_TEST_Hash::hash24() {
  string name = "hash24";
  //! data ------------------------------------
  xMap<int, string> hash(xMap<int, string>::intKeyHash, 0.5);
  hash.put(1, "votien1");
  hash.put(11, "votien11");
  hash.put(21, "votien21");
  hash.put(31, "votien31");
  hash.put(41, "votien41");
  hash.put(51, "votien51");
  hash.put(61, "votien61");
  hash.put(2, "votien2");
  hash.put(3, "votien3");
  hash.put(1, "votien_1");
  hash.clear();
  //! expect ----------------------------------
  string expect =
      "1\n\
[]\n\
[]\n\
[0, 0, 0, 0, 0, 0, 0, 0, 0, 0]";

  //! output ----------------------------------
  stringstream output;
  output << hash.empty() << endl;
  output << hash.keys().toString() << endl;
  output << hash.values().toString() << endl;
  output << hash.clashes().toString();

  //! remove data -----------------------------

  //! result ----------------------------------
  return printResult(output.str(), expect, name);
}

bool UNIT_TEST_Hash::hash25() {
  string name = "hash25";
  //! data ------------------------------------
  xMap<int*, int*> hash(&newINT_keyHash, 1, &newINT_EQ,
                        xMap<int*, int*>::freeKey, &newINT_EQ,
                        xMap<int*, int*>::freeValue);
  int* key1 = new int(1);
  int* key11 = new int(11);
  int* key21 = new int(21);
  int* key31 = new int(31);
  int* key41 = new int(41);
  int* key51 = new int(51);
  int* key61 = new int(61);
  int* key2 = new int(2);
  int* key3 = new int(1);

  int* value1 = new int(100);
  int* value11 = new int(200);
  int* value21 = new int(300);
  int* value31 = new int(400);
  int* value41 = new int(500);
  int* value51 = new int(600);
  int* value61 = new int(700);
  int* value2 = new int(800);
  int* value3 = new int(900);

  hash.put(key1, value1);
  hash.put(key11, value11);
  hash.put(key21, value21);
  hash.put(key31, value31);
  hash.put(key41, value41);
  hash.put(key51, value51);
  hash.put(key61, value61);
  hash.put(key2, value2);
  hash.put(key3, value3);

  //! expect ----------------------------------
  string expect =
      "\n\
==================================================\n\
capacity:   10\n\
size:       8\n\
0   : \n\
1   :  (n_1,n_900); (n_11,n_200); (n_21,n_300); (n_31,n_400); (n_41,n_500); (n_51,n_600); (n_61,n_700)\n\
2   :  (n_2,n_800)\n\
3   : \n\
4   : \n\
5   : \n\
6   : \n\
7   : \n\
8   : \n\
9   : \n\
==================================================\n";

  //! output ----------------------------------
  stringstream output;
  output << "\n" << hash.toString(&newINT_toString, &newINT_toString);

  //! remove data -----------------------------
  delete value1;
  delete key3;

  //! result ----------------------------------
  return printResult(output.str(), expect, name);
}

bool UNIT_TEST_Hash::hash26() {
  string name = "hash26";
  //! data ------------------------------------
  xMap<int*, int*> hash(&newINT_keyHash, 1, &newINT_EQ,
                        xMap<int*, int*>::freeKey, &newINT_EQ,
                        xMap<int*, int*>::freeValue);
  int* key1 = new int(1);
  int* key11 = new int(11);
  int* key21 = new int(21);
  int* key31 = new int(31);
  int* key41 = new int(41);
  int* key51 = new int(51);
  int* key61 = new int(61);
  int* key2 = new int(2);
  int* key3 = new int(1);

  int* value1 = new int(100);
  int* value11 = new int(200);
  int* value21 = new int(300);
  int* value31 = new int(400);
  int* value41 = new int(500);
  int* value51 = new int(600);
  int* value61 = new int(700);
  int* value2 = new int(800);
  int* value3 = new int(900);

  hash.put(key1, value1);
  hash.put(key11, value11);
  hash.put(key21, value21);
  hash.put(key31, value31);
  hash.put(key41, value41);
  hash.put(key51, value51);
  hash.put(key61, value61);
  hash.put(key2, value2);
  hash.put(key3, value3);

  hash.remove(key61, &newINT_delete);

  //! expect ----------------------------------
  string expect =
      "\n\
==================================================\n\
capacity:   10\n\
size:       7\n\
0   : \n\
1   :  (n_1,n_900); (n_11,n_200); (n_21,n_300); (n_31,n_400); (n_41,n_500); (n_51,n_600)\n\
2   :  (n_2,n_800)\n\
3   : \n\
4   : \n\
5   : \n\
6   : \n\
7   : \n\
8   : \n\
9   : \n\
==================================================\n";

  //! output ----------------------------------
  stringstream output;
  output << "\n" << hash.toString(&newINT_toString, &newINT_toString);

  //! remove data -----------------------------
  delete value1;
  delete key3;
  delete value61;

  //! result ----------------------------------
  return printResult(output.str(), expect, name);
}

bool UNIT_TEST_Hash::hash27() {
  string name = "hash27";
  //! data ------------------------------------
  xMap<int*, int*> hash(&newINT_keyHash, 1, &newINT_EQ,
                        xMap<int*, int*>::freeKey, &newINT_EQ,
                        xMap<int*, int*>::freeValue);
  int* key1 = new int(1);
  int* key11 = new int(11);
  int* key21 = new int(21);
  int* key31 = new int(31);
  int* key41 = new int(41);
  int* key51 = new int(51);
  int* key61 = new int(61);
  int* key2 = new int(2);
  int* key3 = new int(1);

  int* value1 = new int(100);
  int* value11 = new int(200);
  int* value21 = new int(300);
  int* value31 = new int(400);
  int* value41 = new int(500);
  int* value51 = new int(600);
  int* value61 = new int(700);
  int* value2 = new int(800);
  int* value3 = new int(900);

  hash.put(key1, value1);
  hash.put(key11, value11);
  hash.put(key21, value21);
  hash.put(key31, value31);
  hash.put(key41, value41);
  hash.put(key51, value51);
  hash.put(key61, value61);
  hash.put(key2, value2);
  hash.put(key3, value3);

  hash.remove(key61, &newINT_delete);
  hash.remove(key31, value31, &newINT_delete, &newINT_delete);

  //! expect ----------------------------------
  string expect =
      "\n\
==================================================\n\
capacity:   10\n\
size:       6\n\
0   : \n\
1   :  (n_1,n_900); (n_11,n_200); (n_21,n_300); (n_41,n_500); (n_51,n_600)\n\
2   :  (n_2,n_800)\n\
3   : \n\
4   : \n\
5   : \n\
6   : \n\
7   : \n\
8   : \n\
9   : \n\
==================================================\n";

  //! output ----------------------------------
  stringstream output;
  output << "\n" << hash.toString(&newINT_toString, &newINT_toString);

  //! remove data -----------------------------
  delete value1;
  delete key3;
  delete value61;

  //! result ----------------------------------
  return printResult(output.str(), expect, name);
}

bool UNIT_TEST_Hash::hash28() {
  string name = "hash28";
  //! data ------------------------------------
  xMap<int*, int*> hash(&newINT_keyHash, 1, &newINT_EQ,
                        xMap<int*, int*>::freeKey, &newINT_EQ,
                        xMap<int*, int*>::freeValue);
  int* key1 = new int(1);
  int* key11 = new int(11);
  int* key21 = new int(21);
  int* key31 = new int(31);
  int* key41 = new int(41);
  int* key51 = new int(51);
  int* key61 = new int(61);
  int* key2 = new int(2);
  int* key3 = new int(1);

  int* value1 = new int(100);
  int* value11 = new int(200);
  int* value21 = new int(300);
  int* value31 = new int(400);
  int* value41 = new int(500);
  int* value51 = new int(600);
  int* value61 = new int(700);
  int* value2 = new int(800);
  int* value3 = new int(900);

  hash.put(key1, value1);
  hash.put(key11, value11);
  hash.put(key21, value21);
  hash.put(key31, value31);
  hash.put(key41, value41);
  hash.put(key51, value51);
  hash.put(key61, value61);
  hash.put(key2, value2);
  hash.put(key3, value3);

  hash.remove(key61, &newINT_delete);
  hash.remove(key31, value31, &newINT_delete, &newINT_delete);
  xMap<int*, int*> hash(&newINT_keyHash);

  copy

      //! expect ----------------------------------
      string expect =
          "\n\
==================================================\n\
capacity:   10\n\
size:       6\n\
0   : \n\
1   :  (n_1,n_900); (n_11,n_200); (n_21,n_300); (n_41,n_500); (n_51,n_600)\n\
2   :  (n_2,n_800)\n\
3   : \n\
4   : \n\
5   : \n\
6   : \n\
7   : \n\
8   : \n\
9   : \n\
==================================================\n";

  //! output ----------------------------------
  stringstream output;
  output << "\n" << hash.toString(&newINT_toString, &newINT_toString);

  //! remove data -----------------------------
  delete value1;
  delete key3;
  delete value61;

  //! result ----------------------------------
  return printResult(output.str(), expect, name);
}

bool UNIT_TEST_Hash::hash29() {
  string name = "hash29";
  //! data ------------------------------------
  xMap<int, string> hash(xMap<int, string>::intKeyHash);

  //! expect ----------------------------------
  string expect =
      "\n\
==================================================\n\
capacity:   10\n\
size:       0\n\
0   : \n\
1   : \n\
2   : \n\
3   : \n\
4   : \n\
5   : \n\
6   : \n\
7   : \n\
8   : \n\
9   : \n\
==================================================\n";

  //! output ----------------------------------
  stringstream output;
  output << "\n" << hash.toString();

  //! remove data -----------------------------

  //! result ----------------------------------
  return printResult(output.str(), expect, name);
}

bool UNIT_TEST_Hash::hash30() {
  string name = "hash30";
  //! data ------------------------------------
  xMap<int, string> hash(xMap<int, string>::intKeyHash);

  //! expect ----------------------------------
  string expect =
      "\n\
==================================================\n\
capacity:   10\n\
size:       0\n\
0   : \n\
1   : \n\
2   : \n\
3   : \n\
4   : \n\
5   : \n\
6   : \n\
7   : \n\
8   : \n\
9   : \n\
==================================================\n";

  //! output ----------------------------------
  stringstream output;
  output << "\n" << hash.toString();

  //! remove data -----------------------------

  //! result ----------------------------------
  return printResult(output.str(), expect, name);
}

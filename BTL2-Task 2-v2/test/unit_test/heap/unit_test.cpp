#include "unit_test.hpp"

map<string, bool (UNIT_TEST_Heap::*)()> UNIT_TEST_Heap::TESTS;

int(int*& lhs, int*& rhs) {
  if (*lhs < *rhs) {
    return +1;
  } else if (*lhs > *rhs) {
    return -1;
  } else {
    return 0;
  }
}

int maxHeapComparator(int*& lhs, int*& rhs) {
  if (*lhs < *rhs) {
    return -1;
  } else if (*lhs > *rhs) {
    return +1;
  } else {
    return 0;
  }
}

string strInt(int*& str) { return to_string(*str); }

void deleteInt(int* a) { delete a; }
// TODO unit test new
bool UNIT_TEST_Heap::heap01() {
  string name = "heap01";
  //! data ------------------------------------
  Heap<int> heap;

  //! expect ----------------------------------
  string expect = "size=0;empty=1;[]";

  //! output ----------------------------------
  stringstream output;
  output << "size=" << heap.size() << ";empty=" << heap.empty() << ";"
         << heap.toString();

  //! remove data -----------------------------

  //! result ----------------------------------
  return printResult(output.str(), expect, name);
}

bool UNIT_TEST_Heap::heap02() {
  string name = "heap02";
  //! data ------------------------------------
  Heap<int> heap;
  Heap<int> copy(heap);

  //! expect ----------------------------------
  string expect = "size=0;empty=1;[]";

  //! output ----------------------------------
  stringstream output;
  output << "size=" << copy.size() << ";empty=" << copy.empty() << ";"
         << copy.toString();

  //! remove data -----------------------------

  //! result ----------------------------------
  return printResult(output.str(), expect, name);
}

bool UNIT_TEST_Heap::heap03() {
  string name = "heap03";
  //! data ------------------------------------
  Heap<int> heap;
  Heap<int> copy;

  copy = heap;

  //! expect ----------------------------------
  string expect = "size=0;empty=1;[]";

  //! output ----------------------------------
  stringstream output;
  output << "size=" << copy.size() << ";empty=" << copy.empty() << ";"
         << copy.toString();

  //! remove data -----------------------------

  //! result ----------------------------------
  return printResult(output.str(), expect, name);
}

bool UNIT_TEST_Heap::heap04() {
  string name = "heap04";
  //! data ------------------------------------
  Heap<int> heap;
  heap.push(4);
  heap.push(2);
  heap.push(1);

  //! expect ----------------------------------
  string expect = "size=3;empty=0;[1,4,2]";

  //! output ----------------------------------
  stringstream output;
  output << "size=" << heap.size() << ";empty=" << heap.empty() << ";"
         << heap.toString();

  //! remove data -----------------------------

  //! result ----------------------------------
  return printResult(output.str(), expect, name);
}

bool UNIT_TEST_Heap::heap05() {
  string name = "heap05";
  //! data ------------------------------------
  Heap<int> heap;
  heap.push(4);
  heap.push(2);
  heap.push(1);
  heap.push(7);
  heap.push(3);
  heap.push(9);
  heap.push(10);
  heap.push(6);
  heap.push(8);
  heap.push(5);
  heap.push(12);
  heap.push(11);
  heap.push(14);
  heap.push(13);
  heap.push(15);
  //! expect ----------------------------------
  string expect = "size=15;empty=0;[1,3,2,6,4,9,10,7,8,5,12,11,14,13,15]";

  //! output ----------------------------------
  stringstream output;
  output << "size=" << heap.size() << ";empty=" << heap.empty() << ";"
         << heap.toString();

  //! remove data -----------------------------

  //! result ----------------------------------
  return printResult(output.str(), expect, name);
}

bool UNIT_TEST_Heap::heap06() {
  string name = "heap06";
  //! data ------------------------------------
  Heap<int> heap;
  heap.push(4);
  heap.push(2);
  heap.push(1);

  //! expect ----------------------------------
  string expect = "size=3;empty=0;[1,4,2]";

  //! output ----------------------------------
  stringstream output;
  output << "size=" << heap.size() << ";empty=" << heap.empty() << ";"
         << heap.toString();

  //! remove data -----------------------------

  //! result ----------------------------------
  return printResult(output.str(), expect, name);
}

bool UNIT_TEST_Heap::heap07() {
  string name = "heap07";
  //! data ------------------------------------
  Heap<int> heap;

  //! expect ----------------------------------
  string expect = "Caught exception: Calling peek with an empty heap.";

  //! output ----------------------------------
  stringstream output;
  try {
    output << heap.pop();
  } catch (const underflow_error& e) {
    output << "Caught exception: " << e.what();
  }

  //! remove data -----------------------------

  //! result ----------------------------------
  return printResult(output.str(), expect, name);
}

bool UNIT_TEST_Heap::heap08() {
  string name = "heap08";
  stringstream output;
  //! data ------------------------------------
  Heap<int> heap;
  heap.push(4);
  output << heap.pop() << endl;

  //! expect ----------------------------------
  string expect =
      "4\n\
size=0;empty=1;[]";

  //! output ----------------------------------
  output << "size=" << heap.size() << ";empty=" << heap.empty() << ";"
         << heap.toString();

  //! remove data -----------------------------

  //! result ----------------------------------
  return printResult(output.str(), expect, name);
}

bool UNIT_TEST_Heap::heap09() {
  string name = "heap09";
  stringstream output;
  //! data ------------------------------------
  Heap<int> heap;
  heap.push(4);
  heap.push(2);
  heap.push(1);
  heap.push(7);
  heap.push(3);
  heap.push(9);
  heap.push(10);
  heap.push(6);
  heap.push(8);
  heap.push(5);
  heap.push(12);
  heap.push(11);
  heap.push(14);
  heap.push(13);
  heap.push(15);

  output << heap.pop() << heap.pop() << heap.pop() << endl;

  //! expect ----------------------------------
  string expect =
      "123\n\
size=12;empty=0;[4,5,9,6,12,11,10,7,8,13,14,15]";

  //! output ----------------------------------
  output << "size=" << heap.size() << ";empty=" << heap.empty() << ";"
         << heap.toString();

  //! remove data -----------------------------

  //! result ----------------------------------
  return printResult(output.str(), expect, name);
}

bool UNIT_TEST_Heap::heap10() {
  string name = "heap10";
  //! data ------------------------------------
  Heap<int> heap;

  //! expect ----------------------------------
  string expect = "Caught exception: Calling peek with an empty heap.";

  //! output ----------------------------------
  stringstream output;
  try {
    output << heap.peek();
  } catch (const underflow_error& e) {
    output << "Caught exception: " << e.what();
  }

  //! remove data -----------------------------

  //! result ----------------------------------
  return printResult(output.str(), expect, name);
}

bool UNIT_TEST_Heap::heap11() {
  string name = "heap11";
  stringstream output;
  //! data ------------------------------------
  Heap<int> heap;
  heap.push(4);
  heap.push(2);
  heap.push(1);
  heap.push(7);
  heap.push(3);
  heap.push(9);
  heap.push(10);
  heap.push(6);
  heap.push(8);
  heap.push(5);
  heap.push(12);
  heap.push(11);
  heap.push(14);
  heap.push(13);
  heap.push(15);

  output << heap.peek() << heap.peek() << heap.peek() << endl;

  //! expect ----------------------------------
  string expect =
      "111\n\
size=15;empty=0;[1,3,2,6,4,9,10,7,8,5,12,11,14,13,15]";

  //! output ----------------------------------
  output << "size=" << heap.size() << ";empty=" << heap.empty() << ";"
         << heap.toString();

  //! remove data -----------------------------

  //! result ----------------------------------
  return printResult(output.str(), expect, name);
}

bool UNIT_TEST_Heap::heap12() {
  string name = "heap12";
  //! data ------------------------------------
  Heap<int> heap;
  heap.push(4);
  heap.push(2);
  heap.push(1);
  heap.remove(2);

  //! expect ----------------------------------
  string expect = "size=2;empty=0;[1,4]";

  //! output ----------------------------------
  stringstream output;
  output << "size=" << heap.size() << ";empty=" << heap.empty() << ";"
         << heap.toString();

  //! remove data -----------------------------

  //! result ----------------------------------
  return printResult(output.str(), expect, name);
}

bool UNIT_TEST_Heap::heap13() {
  string name = "heap13";
  //! data ------------------------------------
  Heap<int> heap;
  heap.push(4);
  heap.push(2);
  heap.push(1);
  heap.push(7);
  heap.push(3);
  heap.push(9);
  heap.push(10);
  heap.push(6);
  heap.push(8);
  heap.push(5);
  heap.push(12);
  heap.push(11);
  heap.push(14);
  heap.push(13);
  heap.push(15);

  heap.remove(11);
  heap.remove(20);
  heap.remove(15);

  //! expect ----------------------------------
  string expect = "size=13;empty=0;[1,3,2,6,4,9,10,7,8,5,12,13,14]";

  //! output ----------------------------------
  stringstream output;
  output << "size=" << heap.size() << ";empty=" << heap.empty() << ";"
         << heap.toString();

  //! remove data -----------------------------

  //! result ----------------------------------
  return printResult(output.str(), expect, name);
}

bool UNIT_TEST_Heap::heap14() {
  string name = "heap14";
  //! data ------------------------------------
  Heap<int> heap;
  heap.push(4);
  heap.push(2);
  heap.push(1);

  //! expect ----------------------------------
  string expect = "True\nsize=3;empty=0;[1,4,2]";

  //! output ----------------------------------
  stringstream output;
  output << (heap.contains(2) ? "True" : "False") << endl;
  output << "size=" << heap.size() << ";empty=" << heap.empty() << ";"
         << heap.toString();

  //! remove data -----------------------------

  //! result ----------------------------------
  return printResult(output.str(), expect, name);
}

bool UNIT_TEST_Heap::heap15() {
  string name = "heap15";
  //! data ------------------------------------
  Heap<int> heap;
  heap.push(4);
  heap.push(2);
  heap.push(1);

  //! expect ----------------------------------
  string expect = "False\nsize=3;empty=0;[1,4,2]";

  //! output ----------------------------------
  stringstream output;
  output << (heap.contains(0) ? "True" : "False") << endl;
  output << "size=" << heap.size() << ";empty=" << heap.empty() << ";"
         << heap.toString();

  //! remove data -----------------------------

  //! result ----------------------------------
  return printResult(output.str(), expect, name);
}

bool UNIT_TEST_Heap::heap16() {
  string name = "heap16";
  //! data ------------------------------------
  Heap<int*> heap(minheapcomparator, Heap<int*>::free);
  heap.push(new int(4));
  heap.push(new int(2));
  heap.push(new int(1));

  //! expect ----------------------------------
  string expect = "size=3;empty=0;[4,2,1]";

  //! output ----------------------------------
  stringstream output;
  output << "size=" << heap.size() << ";empty=" << heap.empty() << ";"
         << heap.toString(&strInt);

  //! remove data -----------------------------

  //! result ----------------------------------
  return printResult(output.str(), expect, name);
}

bool UNIT_TEST_Heap::heap17() {
  string name = "heap17";
  //! data ------------------------------------
  Heap<int*> heap(minheapcomparator, Heap<int*>::free);
  heap.push(new int(4));
  heap.push(new int(2));
  heap.push(new int(1));
  heap.push(new int(8));
  heap.push(new int(6));
  heap.push(new int(9));
  heap.push(new int(12));
  heap.push(new int(7));
  heap.push(new int(5));
  heap.push(new int(3));
  heap.push(new int(10));
  heap.push(new int(14));
  heap.push(new int(15));
  heap.push(new int(11));
  heap.push(new int(13));
  heap.push(new int(16));
  heap.push(new int(18));
  heap.push(new int(17));

  Heap<int*> copy(heap);

  //! expect ----------------------------------
  string expect =
      "size=18;empty=0;[18,17,14,16,7,12,13,10,15,3,4,1,9,8,11,2,6,5]";

  //! output ----------------------------------
  stringstream output;
  output << "size=" << copy.size() << ";empty=" << copy.empty() << ";"
         << copy.toString(&strInt);

  //! remove data -----------------------------

  //! result ----------------------------------
  return printResult(output.str(), expect, name);
}

bool UNIT_TEST_Heap::heap18() {
  string name = "heap18";
  //! data ------------------------------------
  Heap<int*> heap(minheapcomparator, Heap<int*>::free);
  heap.push(new int(4));
  heap.push(new int(2));
  heap.push(new int(1));
  heap.push(new int(8));
  heap.push(new int(6));
  heap.push(new int(9));
  heap.push(new int(12));
  heap.push(new int(7));
  heap.push(new int(5));
  heap.push(new int(3));
  heap.push(new int(10));
  heap.push(new int(14));
  heap.push(new int(15));
  heap.push(new int(11));
  heap.push(new int(13));
  heap.push(new int(16));
  heap.push(new int(18));
  heap.push(new int(17));

  Heap<int*> copy;
  copy = heap;

  //! expect ----------------------------------
  string expect =
      "size=18;empty=0;[18,17,14,16,7,12,13,10,15,3,4,1,9,8,11,2,6,5]";

  //! output ----------------------------------
  stringstream output;
  output << "size=" << copy.size() << ";empty=" << copy.empty() << ";"
         << copy.toString(&strInt);

  //! remove data -----------------------------

  //! result ----------------------------------
  return printResult(output.str(), expect, name);
}

bool UNIT_TEST_Heap::heap19() {
  string name = "heap19";
  stringstream output;
  //! data ------------------------------------
  Heap<int*> heap(minheapcomparator, Heap<int*>::free);
  heap.push(new int(4));
  heap.push(new int(2));
  heap.push(new int(1));
  heap.push(new int(8));
  heap.push(new int(6));
  heap.push(new int(9));
  heap.push(new int(12));
  heap.push(new int(7));
  heap.push(new int(5));
  heap.push(new int(3));
  heap.push(new int(10));
  heap.push(new int(14));
  heap.push(new int(15));
  heap.push(new int(11));
  heap.push(new int(13));
  heap.push(new int(16));
  heap.push(new int(18));
  heap.push(new int(17));

  int* a = heap.pop();
  output << *a << endl;
  delete a;

  //! expect ----------------------------------
  string expect =
      "18\nsize=17;empty=0;[17,16,14,15,7,12,13,10,5,3,4,1,9,8,11,2,6]";

  //! output ----------------------------------

  output << "size=" << heap.size() << ";empty=" << heap.empty() << ";"
         << heap.toString(&strInt);

  //! remove data -----------------------------

  //! result ----------------------------------
  return printResult(output.str(), expect, name);
}

bool UNIT_TEST_Heap::heap20() {
  string name = "heap20";
  stringstream output;
  //! data ------------------------------------
  Heap<int*> heap(minheapcomparator, Heap<int*>::free);
  heap.push(new int(4));
  heap.push(new int(2));
  heap.push(new int(1));
  heap.push(new int(8));
  heap.push(new int(6));
  heap.push(new int(9));
  heap.push(new int(12));
  heap.push(new int(7));
  heap.push(new int(5));
  heap.push(new int(3));
  heap.push(new int(10));
  heap.push(new int(14));
  heap.push(new int(15));
  heap.push(new int(11));
  heap.push(new int(13));
  heap.push(new int(16));
  heap.push(new int(18));
  heap.push(new int(17));

  int* a = heap.pop();
  output << *a << endl;
  delete a;
  a = heap.pop();
  output << *a << endl;
  delete a;
  heap.clear();

  //! expect ----------------------------------
  string expect = "18\n17\nsize=0;empty=1;[]";

  //! output ----------------------------------

  output << "size=" << heap.size() << ";empty=" << heap.empty() << ";"
         << heap.toString(&strInt);

  //! remove data -----------------------------

  //! result ----------------------------------
  return printResult(output.str(), expect, name);
}

bool UNIT_TEST_Heap::heap21() {
  string name = "heap21";
  //! data ------------------------------------
  Heap<int*> heap(maxHeapComparator, Heap<int*>::free);
  heap.push(new int(4));
  heap.push(new int(2));
  heap.push(new int(1));
  heap.push(new int(8));
  heap.push(new int(6));
  heap.push(new int(9));
  heap.push(new int(12));
  heap.push(new int(7));
  heap.push(new int(5));
  heap.push(new int(3));
  heap.push(new int(10));
  heap.push(new int(14));
  heap.push(new int(15));
  heap.push(new int(11));
  heap.push(new int(13));
  heap.push(new int(16));
  heap.push(new int(18));
  heap.push(new int(17));

  Heap<int*> copy;
  copy = heap;

  //! expect ----------------------------------
  string expect =
      "size=18;empty=0;[1,3,2,5,4,9,11,8,7,6,10,14,15,12,13,16,18,17]";

  //! output ----------------------------------
  stringstream output;
  output << "size=" << copy.size() << ";empty=" << copy.empty() << ";"
         << copy.toString(&strInt);

  //! remove data -----------------------------

  //! result ----------------------------------
  return printResult(output.str(), expect, name);
}

bool UNIT_TEST_Heap::heap22() {
  string name = "heap22";
  //! data ------------------------------------
  Heap<int*> heap(maxHeapComparator, Heap<int*>::free);
  heap.push(new int(4));
  heap.push(new int(2));
  heap.push(new int(1));
  heap.push(new int(8));
  heap.push(new int(6));
  heap.push(new int(9));
  heap.push(new int(12));
  heap.push(new int(7));
  heap.push(new int(5));
  heap.push(new int(3));
  heap.push(new int(10));
  heap.push(new int(14));
  int* value = new int(15);
  heap.push(value);
  heap.push(new int(11));
  heap.push(new int(13));
  heap.push(new int(16));
  heap.push(new int(18));
  heap.push(new int(17));

  heap.remove(value, deleteInt);

  //! expect ----------------------------------
  string expect = "size=17;empty=0;[1,3,2,5,4,9,11,8,7,6,10,14,17,12,13,16,18]";

  //! output ----------------------------------
  stringstream output;
  output << "size=" << heap.size() << ";empty=" << heap.empty() << ";"
         << heap.toString(&strInt);

  //! remove data -----------------------------

  //! result ----------------------------------
  return printResult(output.str(), expect, name);
}

bool UNIT_TEST_Heap::heap23() {
  string name = "heap23";
  //! data ------------------------------------
  Heap<int*> heap(maxHeapComparator, Heap<int*>::free);
  heap.push(new int(4));
  heap.push(new int(2));
  heap.push(new int(1));
  heap.push(new int(8));
  heap.push(new int(6));
  heap.push(new int(9));
  heap.push(new int(12));
  heap.push(new int(7));
  heap.push(new int(5));
  heap.push(new int(3));
  heap.push(new int(10));
  heap.push(new int(14));
  heap.push(new int(15));
  heap.push(new int(11));
  heap.push(new int(13));
  heap.push(new int(16));
  heap.push(new int(18));
  heap.push(new int(17));

  //! expect ----------------------------------
  string expect = "1 3 2 5 4 9 11 8 7 6 10 14 15 12 13 16 18 17 ";

  //! output ----------------------------------
  stringstream output;
  for (auto i : heap) {
    output << *i << " ";
  }

  //! remove data -----------------------------

  //! result ----------------------------------
  return printResult(output.str(), expect, name);
}

bool UNIT_TEST_Heap::heap24() {
  string name = "heap24";
  //! data ------------------------------------
  Heap<int*> heap(maxHeapComparator, Heap<int*>::free);
  heap.push(new int(4));
  heap.push(new int(2));
  heap.push(new int(1));
  heap.push(new int(8));
  heap.push(new int(6));
  heap.push(new int(9));
  heap.push(new int(12));
  heap.push(new int(7));
  heap.push(new int(5));
  heap.push(new int(3));
  heap.push(new int(10));
  heap.push(new int(14));
  heap.push(new int(15));
  heap.push(new int(11));
  heap.push(new int(13));
  heap.push(new int(16));
  heap.push(new int(18));
  heap.push(new int(17));

  //! expect ----------------------------------
  string expect = "1 4 2 7 6 14 11 13 18 12 10 15 ";

  //! output ----------------------------------
  stringstream output;
  int index = 0;
  for (auto i = heap.begin(); i != heap.end(); ++i) {
    if (index % 2) i.remove(deleteInt);
    output << **i << " ";
    index += 1;
  }

  //! remove data -----------------------------

  //! result ----------------------------------
  return printResult(output.str(), expect, name);
}

bool UNIT_TEST_Heap::heap25() {
  string name = "heap25";
  //! data ------------------------------------
  int array[] = {1, 4, 2};
  Heap<int> heap;
  heap.heapify(array, 3);

  //! expect ----------------------------------
  string expect = "size=3;empty=0;[1,4,2]";

  //! output ----------------------------------
  stringstream output;
  output << "size=" << heap.size() << ";empty=" << heap.empty() << ";"
         << heap.toString();

  //! remove data -----------------------------

  //! result ----------------------------------
  return printResult(output.str(), expect, name);
}

bool UNIT_TEST_Heap::heap26() {
  string name = "heap26";
  //! data ------------------------------------
  int array[] = {15, 3,  8, 1,  20, 9,  4,  5,  12, 6,
                 11, 10, 7, 14, 2,  13, 17, 18, 19, 16};
  Heap<int> heap;
  heap.heapify(array, 20);

  //! expect ----------------------------------
  string expect =
      "size=20;empty=0;[1,3,2,5,6,7,4,13,12,16,11,10,9,14,8,15,17,18,19,20]";

  //! output ----------------------------------
  stringstream output;
  output << "size=" << heap.size() << ";empty=" << heap.empty() << ";"
         << heap.toString();

  //! remove data -----------------------------

  //! result ----------------------------------
  return printResult(output.str(), expect, name);
}

bool UNIT_TEST_Heap::heap27() {
  string name = "heap27";
  //! data ------------------------------------
  int array[] = {};
  Heap<int> heap;
  heap.heapify(array, 0);

  //! expect ----------------------------------
  string expect = "size=0;empty=1;[]";

  //! output ----------------------------------
  stringstream output;
  output << "size=" << heap.size() << ";empty=" << heap.empty() << ";"
         << heap.toString();

  //! remove data -----------------------------

  //! result ----------------------------------
  return printResult(output.str(), expect, name);
}

bool UNIT_TEST_Heap::heap28() {
  string name = "heap28";
  //! data ------------------------------------
  int* array[] = {new int(15), new int(3),  new int(8),  new int(1),
                  new int(20), new int(9),  new int(4),  new int(5),
                  new int(12), new int(6),  new int(11), new int(10),
                  new int(7),  new int(14), new int(2),  new int(13),
                  new int(17), new int(18), new int(19), new int(16)};
  Heap<int*> heap(minheapcomparator, Heap<int*>::free);
  heap.heapify(array, 20);

  //! expect ----------------------------------
  string expect =
      "size=20;empty=0;[20,19,14,18,16,9,10,13,17,11,6,8,7,4,2,1,12,5,15,3]";

  //! output ----------------------------------
  stringstream output;
  output << "size=" << heap.size() << ";empty=" << heap.empty() << ";"
         << heap.toString(strInt);

  //! remove data -----------------------------

  //! result ----------------------------------
  return printResult(output.str(), expect, name);
}

bool UNIT_TEST_Heap::heap29() {
  string name = "heap29";
  //! data ------------------------------------
  int* array[] = {};
  Heap<int*> heap(minheapcomparator, Heap<int*>::free);
  heap.heapify(array, 0);

  //! expect ----------------------------------
  string expect = "size=0;empty=1;[]";

  //! output ----------------------------------
  stringstream output;
  output << "size=" << heap.size() << ";empty=" << heap.empty() << ";"
         << heap.toString(strInt);

  //! remove data -----------------------------

  //! result ----------------------------------
  return printResult(output.str(), expect, name);
}

bool UNIT_TEST_Heap::heap30() {
  string name = "heap30";
  //! data ------------------------------------
  int* array[] = {new int(15), new int(3),  new int(8),  new int(1),
                  new int(20), new int(9),  new int(4),  new int(5),
                  new int(12), new int(6),  new int(11), new int(10),
                  new int(7),  new int(14), new int(2),  new int(13),
                  new int(17), new int(18), new int(19), new int(16)};
  Heap<int*> heap(maxHeapComparator, Heap<int*>::free);
  heap.heapify(array, 20);

  //! expect ----------------------------------
  string expect =
      "size=20;empty=0;[1,3,2,5,6,7,4,13,12,16,11,10,9,14,8,15,17,18,19,20]";

  //! output ----------------------------------
  stringstream output;
  output << "size=" << heap.size() << ";empty=" << heap.empty() << ";"
         << heap.toString(strInt);

  //! remove data -----------------------------

  //! result ----------------------------------
  return printResult(output.str(), expect, name);
}

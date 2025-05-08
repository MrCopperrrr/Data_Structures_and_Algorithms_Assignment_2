#ifndef UNIT_TEST_HASH_HPP
#define UNIT_TEST_HASH_HPP

#include "hash/xMap.h"
#include "library.hpp"
class UNIT_TEST_Hash {
 public:
  UNIT_TEST_Hash() {
    // TODO unit test new
    registerTest("hash01", &UNIT_TEST_Hash::hash01);
    registerTest("hash02", &UNIT_TEST_Hash::hash02);
    registerTest("hash03", &UNIT_TEST_Hash::hash03);
    registerTest("hash04", &UNIT_TEST_Hash::hash04);
    registerTest("hash05", &UNIT_TEST_Hash::hash05);
    registerTest("hash06", &UNIT_TEST_Hash::hash06);
    registerTest("hash07", &UNIT_TEST_Hash::hash07);
    registerTest("hash08", &UNIT_TEST_Hash::hash08);
    registerTest("hash09", &UNIT_TEST_Hash::hash09);
    registerTest("hash10", &UNIT_TEST_Hash::hash10);
    registerTest("hash11", &UNIT_TEST_Hash::hash11);
    registerTest("hash12", &UNIT_TEST_Hash::hash12);
    registerTest("hash13", &UNIT_TEST_Hash::hash13);
    registerTest("hash14", &UNIT_TEST_Hash::hash14);
    registerTest("hash15", &UNIT_TEST_Hash::hash15);
    registerTest("hash16", &UNIT_TEST_Hash::hash16);
    registerTest("hash17", &UNIT_TEST_Hash::hash17);
    registerTest("hash18", &UNIT_TEST_Hash::hash18);
    registerTest("hash19", &UNIT_TEST_Hash::hash19);
    registerTest("hash20", &UNIT_TEST_Hash::hash20);
    registerTest("hash21", &UNIT_TEST_Hash::hash21);
    registerTest("hash22", &UNIT_TEST_Hash::hash22);
    registerTest("hash23", &UNIT_TEST_Hash::hash23);
    registerTest("hash24", &UNIT_TEST_Hash::hash24);
    registerTest("hash25", &UNIT_TEST_Hash::hash25);
    registerTest("hash26", &UNIT_TEST_Hash::hash26);
    registerTest("hash27", &UNIT_TEST_Hash::hash27);
    registerTest("hash28", &UNIT_TEST_Hash::hash28);
    registerTest("hash29", &UNIT_TEST_Hash::hash29);
    registerTest("hash30", &UNIT_TEST_Hash::hash30);
  }

 private:
  // TODO unit test new
  bool hash01();
  bool hash02();
  bool hash03();
  bool hash04();
  bool hash05();
  bool hash06();
  bool hash07();
  bool hash08();
  bool hash09();
  bool hash10();
  bool hash11();
  bool hash12();
  bool hash13();
  bool hash14();
  bool hash15();
  bool hash16();
  bool hash17();
  bool hash18();
  bool hash19();
  bool hash20();
  bool hash21();
  bool hash22();
  bool hash23();
  bool hash24();
  bool hash25();
  bool hash26();
  bool hash27();
  bool hash28();
  bool hash29();
  bool hash30();

 public:
  static map<string, bool (UNIT_TEST_Hash::*)()> TESTS;
  // ANSI escape codes for colors
  const string green = "\033[32m";
  const string red = "\033[31m";
  const string cyan = "\033[36m";
  const string reset = "\033[0m";  // To reset to default color

  // print result test case
  bool printResult(string output, string expect, string name) {
    if (expect == output) {
      cout << green << "test " + name + " --------------- PASS" << reset
           << "\n";
      return true;
    } else {
      cout << red << "test " + name + " --------------- FAIL" << reset << "\n";
      cout << "\texpect : " << expect << endl;
      cout << "\toutput : " << output << endl;
      return false;
    }
  }
  // run 1 test case
  void runTest(const std::string &name) {
    auto it = TESTS.find(name);
    if (it != TESTS.end()) {
      (this->*(it->second))();
    } else {
      throw std::runtime_error("Test with name '" + name + "' does not exist.");
    }
  }
  // run all test case
  void runAllTests() {
    vector<string> fails;
    for (const auto &test : TESTS) {
      if (!(this->*(test.second))()) {
        fails.push_back(test.first);
      }
    }

    cout << cyan << "\nResult -------------------------" << reset << endl;
    // Print the results
    if (fails.empty()) {
      cout << green << "All tests passed!" << reset << endl;
    } else {
      int totalTests = TESTS.size();
      int failedTests = fails.size();
      int passedTests = totalTests - failedTests;
      double passRate =
          (totalTests > 0)
              ? (static_cast<double>(passedTests) / totalTests) * 100.0
              : 0.0;
      cout << red << "Some tests failed:";
      for (const auto &fail : fails) {
        cout << "  " << fail;
      }
      cout << cyan << "\nPass rate: " << passRate << "%" << reset << endl;
    }
  }
  static void registerTest(string name, bool (UNIT_TEST_Hash::*function)()) {
    if (TESTS.find(name) != TESTS.end()) {
      throw std::runtime_error("Test with name '" + name + "' already exists.");
    }
    TESTS[name] = function;
  }
};

#endif  // UNIT_TEST_hash_HPP
#include "LazyInit.h"
#include <cassert>
#include <iostream>
#include <string>

using lazy::LazyInit;
using std::cout;
using std::string;

static void UseTest() {
  const string huge_string = "This is very huge string";

  LazyInit<string> lazy_string([&huge_string] { return huge_string; });

  assert(lazy_string.HasValue() == false);
  assert(lazy_string.Get() == huge_string);
  assert(lazy_string.Get() == huge_string);
}

static void WasCalledTest() {
  bool was_called = false;

  LazyInit<int> lazy_int([&was_called] {
    was_called = true;
    return 0;
  });

  assert(was_called == false);
}

int main() {
  UseTest();
  WasCalledTest();

  cout << "All test passed!\n";

  return 0;
}

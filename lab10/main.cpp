#include <functional>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template <class T>
class MyPipeline {
 public:

  size_t size() const { return steps.size(); }
  bool empty() const { return steps.empty(); }
  void clear() { steps.clear(); }

  template <class F>
  void addStep(const string& name, F func) {
    if (name.empty()) {
      throw invalid_argument("имя шага пустое !");
    }
    Step s;
    s.name = name;
    s.func = function<T(T)>(func);
    steps.push_back(s);
  }

  void removeStep(size_t index) {
    if (index >= steps.size()) {
      throw out_of_range("Неверный индекс шага");
    }
    steps.erase(steps.begin() + index);
  }

  T run(T value) const {
    for (size_t i = 0; i < steps.size(); i++) {
      value = steps[i].func(value);
    }
    return value;
  }

  vector<T> trace(T value) const {
    vector<T> results;
    for (int i = 0; i < steps.size(); i++) {
      value = steps[i].func(value);
      results.push_back(value);
    }
    return results;
  }

  template <class U>
  friend ostream& operator<<(ostream& os, const MyPipeline<U>& p);

 private:
  struct Step {
    string name;
    function<T(T)> func;
  };

  vector<Step> steps;
};

template <class T>
ostream& operator<<(ostream& os, const MyPipeline<T>& p) {
  os << "Шаг: " << p.steps.size() << "\n";
  for (int i = 0; i < p.steps.size(); i++) {
    os << i << ") " << p.steps[i].name << "\n";
  }
  return os;
}

int main() {
  MyPipeline<int> intPipe;
  intPipe.addStep("+5", [](int x) { return x + 5; });
  intPipe.addStep("*2", [](int x) { return x * 2; });
  intPipe.addStep("-3", [](int x) { return x - 3; });

  cout << "Тест 1:\n" << intPipe;
  int intInput = 10;
  cout << intPipe.run(intInput) << "\n";

  vector<int> intTrace = intPipe.trace(intInput);

  for (int i = 0; i < intTrace.size(); i++) {
    if (i > 0) {
      cout << " ";
    }
    cout << intTrace[i];
  }
  cout << "\n";

  MyPipeline<string> strPipe;
  strPipe.addStep("First", [](string s) { return "TestString_" + s; });
  strPipe.addStep("Second", [](string s) { return s + "_EndString"; });
  strPipe.addStep("Last", [](string s) { return  s + "_EndEnd"; });

  string strInput = "MyString";
  cout << strPipe.run(strInput) << "\n";

  try {
    intPipe.removeStep(100);
  } catch (const out_of_range& e) {
    cout << "Тест ошибки: " << e.what() << "\n";
  }

  return 0;
}


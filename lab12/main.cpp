#include <iostream>
#include <string>
#include <vector>

using namespace std;

class DocumentHistory {
 public:
  class ReverseIterator {
   public:
    ReverseIterator(const vector<string>* data, int position)
        : versions(data), index(position) {}

    string operator*() const {
      return (*versions)[index];
    }

    ReverseIterator& operator++() {
      index--;
      return *this;
    }

    bool operator!=(const ReverseIterator& other) const {
      return index != other.index;
    }

   private:
    const vector<string>* versions;
    int index;
  };

  void addVersion(const string& version) {
    versions.push_back(version);
  }

  ReverseIterator rbegin() const {
    return ReverseIterator(&versions, versions.size() - 1);
  }

  ReverseIterator rend() const {
    return ReverseIterator(&versions, -1);
  }

 private:
  vector<string> versions;
};

int main() {
  DocumentHistory history;
  int count;

  cout << "Введите количество версий: ";
  cin >> count;
  cin.ignore();

  for (int i = 0; i < count; i++) {
    string version;
    cout << "Введите версию " << i + 1 << ": ";
    getline(cin, version);
    history.addVersion(version);
  }

  cout << "История в обратном порядке:\n";

  for (DocumentHistory::ReverseIterator it = history.rbegin();
       it != history.rend(); ++it) {
    cout << *it << "\n";
  }

  return 0;
}

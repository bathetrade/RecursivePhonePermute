#include <iostream>
#include <vector>
#include <string>
#include <locale>
using namespace std;

int todigit(char c) {
	return c - '0';
}

class PhoneKeys {
private:
	vector<string> v;
public:
	PhoneKeys() : v(8) {
		v.assign({ "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz" });
	}
	string& operator[](size_t index) {
		return v.at(index - 2);
	}
};

// "78" = "pqrs" "tuv"  
class MainApp {
private:
	PhoneKeys p;
	string input;
	size_t len;

	bool RecursivePermute(string& prefix, size_t InputIndex) {
		if (InputIndex == len)
			return false;
		
		int key = todigit(input[InputIndex]);
		string KeyString = p[key];
		int KeyStrLen = KeyString.length();
		
		//Loop through the key string and set the prefix from the key string
		for (int i = 0; i < KeyStrLen; ++i) {
			prefix[InputIndex] = KeyString[i];
			if (!RecursivePermute(prefix, InputIndex + 1))
				cout << prefix << endl;
		}
	}
public:
	bool GetNumericString() {
		len = 0;
		cout << "Enter a numeric string: ";
		cin >> input;
		for (auto it = input.begin(); it != input.end(); ++it) {
			if (isdigit(*it)) {
				int digit = (*it) - '0';
				if (digit < 2)
					return false;
			}
			else return false;
		}
		len = input.length();
		return true;
	}
	void PermuteString() {
		if (len == 0) {
			cout << "Empty string\n";
			return;
		}
		string prefix(len, '\0');
		RecursivePermute(prefix,0);
	}

};

int main() {
	MainApp Main;
	if (!Main.GetNumericString()) {
		cout << "Invalid input.\n";
		return 0;
	}
	else Main.PermuteString();
	cin.get(); cin.get();
	return 0;
}
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

	bool Init() {
		return GetNumericString();
	}

	void PermuteString() {
		if (len == 0) {
			cout << "Empty string\n";
			return;
		}
		string prefix(len, '\0');
		RecursivePermute(prefix, 0);
	}

	bool GetNumericString() {
		len = 0;
		cout << "Enter a numeric string: ";
		cin >> input;
		cin.get();	//remove newline from cin
		for (auto it = input.begin(); it != input.end(); ++it) {
			if (isdigit(*it)) {
				if (todigit((*it)) < 2)
					return false;
			}
			else return false;
		}
		len = input.length();
		return true;
	}
public:
	
	bool Run() {
		if (!Init())
			return false;
		PermuteString();
		cin.get(); //wait for enter to be pressed
		return true;
	}
};

int main() {
	MainApp Main;
	return Main.Run();
}
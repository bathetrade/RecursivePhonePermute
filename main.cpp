#include <iostream>
#include <vector>
#include <string>
#include <locale>
using namespace std;

int todigit(char c) {
	return c - '0';
}

// Maps numbers on a phone to letter groups. Example, "2" maps to "abc".
class PhoneKeys {
private:
	vector<string> _v;
public:
	PhoneKeys() : _v(8) {
		_v.assign({ "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz" });
	}
	const string& operator[](size_t index) const {
		return _v.at(index - 2);
	}
};

class MainApp {
private:
	PhoneKeys _phone;
	string _input;
	size_t _numLetterGroups = 0;
    
    /*  Terminology:
        Assume the user enters "258". These numbers on a phone correspond to the 
        letter groups "abc", "jkl", and "tuv", respectively.
        "abc" has a letterGroupIndex of 0, "jkl" has a letterGroupIndex of 1, etc.
        
        Algorithm explanation:
        The permutation algorithm runs like a nested loop, in the sense that the innermost loops
        run more frequently than outer loops. Letter groups with a higher index are 
        analogous to inner loops.
        
        For instance, in the example above with an input of "258", the output would be:
        
        ajt
        aju
        ajv
        akt
        aku
        akv
        
        ...and so on. Notice that the last letter group "tuv" cycles more frequently
        than the second, and the second cycles more frequently than the first.

    */
	bool RecursivePermute(string& permutation, size_t letterGroupIndex) const {
	    bool finished = letterGroupIndex == _numLetterGroups;
		if (finished) {
			return false;
		}
		
		int currentPhoneNumber = todigit(_input[letterGroupIndex]);
		string currentLetterGroup = _phone[currentPhoneNumber];
		
		//Loop through the letter group and set the permutation from it
		for(const char letter : currentLetterGroup) {
		    permutation[letterGroupIndex] = letter;
		    if (!RecursivePermute(permutation, letterGroupIndex + 1)) {
		        cout << permutation << endl;
		    }
		}
		
		return true;
	}

	bool Init() {
		return GetNumericString();
	}
    
	void PermuteString() {
		if (_numLetterGroups == 0) {
			cout << "Empty string\n";
			return;
		}
		string permutation(_numLetterGroups, '\0');
		RecursivePermute(permutation, 0);
	}

    bool ValidateInput() const {
        if (_input.length() == 0) {
            return false;
        }
        
		for (auto it = _input.begin(); it != _input.end(); ++it) {
			if (isdigit(*it)) {
				if (todigit((*it)) < 2)
					return false;
			}
			else return false;
		}
		
		return true;
    }
    
	bool GetNumericString() {
		cout << "Enter a numeric string: ";
		cin >> _input;
		cin.get();	//remove newline from cin
		
		if (!ValidateInput()) {
		    return false;
		}
		
		_numLetterGroups = _input.length();
		
		return true;
	}
	
public:
	
	bool Run() {
		if (!Init()) {
		    cerr << "Invalid input. Please enter a string consisting of the digits 2-9." << endl;
			return false;
		}
		
		PermuteString();
		cin.get(); //wait for enter to be pressed
		return true;
	}
};

int main() {
	MainApp Main;
	return Main.Run();
}
#include <cctype>
#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>

using namespace std;

char encrypt(char &c, int key) {
	return (!isalpha(c)) ? c :
	       (isupper(c) && c + key > 'Z') ? c - (26 - key) :
	       (islower(c) && c + key > 'z') ? c - (26 - key) :
	        c + key;
}

char decrypt(char &c, int key) {
	return (!isalpha(c)) ? c :
	       (isupper(c) && c - key < 'A') ? c + (26 - key) :
	       (islower(c) && c - key < 'a') ? c + (26 - key) :
                c - key;
}

string caesar(string encryptOrDecrypt, int key, string str) {

	key %= 26;

	for (string::size_type i = 0; i < str.length(); i++) {
		str[i] = (encryptOrDecrypt == "-e") ? encrypt(str[i], key) : decrypt(str[i], key);
	}

	return str;
}

bool isNumeric(const string str) {
	if (str.empty()) {
		return false;
	}

	for (char c : str) {
		if (!isdigit(c)) {
			return false;
		}
	}

	return true;
}

void usage() {
	cout << "USAGE: caesar [-ed] [key]\n";
}

int main(int argc, char *argv[]) {

	if (argc != 3) {
		usage();
		exit(1);
	}

	string encryptOrDecrypt = argv[1];
	string potentialKey = argv[2];

	if (!isNumeric(potentialKey) || (encryptOrDecrypt != "-e" && encryptOrDecrypt != "-d")) {
		usage();
		exit(1);
	}
	
	int key = stoi(potentialKey);
	string input;

	while (std::getline(cin, input)) {
		cout << caesar(encryptOrDecrypt, key, input) << endl;
	}

	return 0;
}

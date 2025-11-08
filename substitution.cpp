#include <cctype>
#include <iostream>
#include <string>

using namespace std;

const string UPPERCASE_ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const string LOWERCASE_ALPHABET = "abcdefghijklmnopqrstuvwxyz";

char encrypt(char &c, string key) {

	if (!isalpha(c)) {
		return c;
	}

	return (isupper(c)) ? toupper(key[UPPERCASE_ALPHABET.find(c)]) :
		              key[LOWERCASE_ALPHABET.find(c)];
}

char decrypt(char &c, string key) {

	if (!isalpha(c)) {
		return c;
	}

	return (isupper(c)) ? UPPERCASE_ALPHABET[key.find(tolower(c))] :
		              LOWERCASE_ALPHABET[key.find(c)];
}

string substitution(string encryptOrDecrypt, string key, string str) {
	
	for (string::size_type i = 0; i < str.length(); i++) {
		str[i] = (encryptOrDecrypt == "-e") ? encrypt(str[i], key) : decrypt(str[i], key);
	}

	return str;
}

bool isAlphabetic(string str) {
	if (str.empty()) {
		return false;
	}

	for (char c : str) {
		if (isdigit(c)) {
			return false;
		}
	}

	return true;
}

void usage() {
	std::cout << "USAGE: substitution [-ed] [key]\n";
}

int main(int argc, char** argv) {

	if (argc != 3) {
		usage();
		exit(1);
	}

	string encryptOrDecrypt = argv[1];
	string key = argv[2];

	if (key.length() != 26 || !isAlphabetic(key) || (encryptOrDecrypt != "-e" && encryptOrDecrypt != "-d")) {
		usage();
		exit(1);
	}
	
	string input;

	while (std::getline(cin, input)) {
		cout << substitution(encryptOrDecrypt, key, input) << endl;
	}

	return 0;
}

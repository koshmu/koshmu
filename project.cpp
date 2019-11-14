#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <fstream>

using std::vector;
using std::cin;
using std::cout;
using std::ifstream;
using std::endl;
using std::string;
using std::sort;

int main(){
	// creating variables
	vector<string> words;
	string password = "";
	string word = "";
	int count = 0;
	ifstream input("common_passwords.txt");
	
	// add words from file to vector and sorts it
	while(input >> word){
		words.push_back(word);
	}
	sort(words.begin(), words.end());
	
	// ask user to input a password and outputs string related
	// to the word
	cout << "Give me a password: ";
	cin >> password;
	cout << "You provided a password of " << password << endl;
	cout << "The most similar password to " << password << " are:" << endl;
	
	vector<string> new_words;
	int high_count = 0;
	
	// for loop for iterating through words and adding them
	// into the new vector if it's similar to password
	for (auto &elem : words){
	    // if the password is equal to the word, add it to 
	    // a vector, then continue
	    if (password == elem){
	        new_words.push_back(elem);
	        continue;
	    }
	    
	    // checks if password is a substring of the current
	    // word, then adds it to a vector, then continue
	    if (password == elem.substr(0, password.size())){
			new_words.push_back(elem);
			continue;
		}
        
        // if the lenght of the password is less than the
        // length of the word then ignore that word and
        // continue to the next one
	    if (password.size() < elem.size())
			continue;
			
		// iterates through each letter in the password and
		// checks if the letter in that position is the same
		// as the letter in the current word
		int tempcount = 0;
	    for (int i = 0; i < static_cast<int>(password.size()); i++){
	        // checks if password letter is equal to word letter
	        // in the same position
	        if (password[i] == elem[i]){
	            // adds 1 to tempcount and count
	            tempcount++;
	            count++;
	            
	            // if the tempcount >= 2 and count >= 2, then add the word
	            // into a vector if it isn't already in there. if it is in
	            // the vector, then continue
	            if (tempcount >= 2 && count >= 2){
                    if (std::find(new_words.begin(), new_words.end(), elem) != new_words.end()){
                        continue;
                    } else {
                        new_words.push_back(elem);
                    }
                }
	        } else {
	            // make tempcount = 0 if letters aren't equal
	            tempcount = 0;
	        }
	        // create a new high_count if the high_count is less than the count
            if (high_count < count)
                high_count = count;
        }
        count = 0;
	}
	
	// outputs the vector of similar passwords
    for (auto &elem : new_words){
        cout << elem << ", ";
    }
	cout << endl;
	// outputs the highest difference of characters for the passwords
	cout << "All of which are " << high_count << " character(s) different." << endl;
}
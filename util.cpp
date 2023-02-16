#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{
    
    set<std::string> setOfWords;
    string trimWords = trim(rawWords);
    string str = convToLower(trimWords);
    stringstream ss(str);
    string word;
    while(!ss.eof()){
        ss >> word;
        if(word.length() <= 2){
            setOfWords.insert(word);
        }

        else{
            int found = -1;
            for(size_t i = 0; i < word.size(); i++){
                if(ispunct(word[i]) != 0){
                    found = i;
                    break;
                }
            }
            if(found != -1){
                string first = word.substr(0, found);
                string second = word.substr(found+1, word.size());
                if(first.size() >= second.size()){
                    setOfWords.insert(first);
                }
                else if(first.size() < second.size()){
                    setOfWords.insert(second);
                }
            }
            else{
                setOfWords.insert(word);
            }
        }
    }

    return setOfWords;
    
}


/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}

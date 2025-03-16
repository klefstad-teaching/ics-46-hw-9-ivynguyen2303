#include "ladder.h"

void error(string word1, string word2, string msg)
{
    cerr << "Error: " << msg <<  ". ( " << word1 << ", " << word2 << " )";
}


bool is_adjacent(const string& word1, const string& word2)
{
    int w1_len = word1.length();
    int w2_len = word2.length();


}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list)
{
    if (begin_word == end_word)
        error(begin_word, end_word, "begin and end equal");
}
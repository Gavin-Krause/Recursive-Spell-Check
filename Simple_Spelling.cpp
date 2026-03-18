#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <ranges>
using namespace std;

//read file into a vector for processing
vector<string> read_file(const string& file) {
    fstream fn {file};
    string word;
    vector<string> v;
    while(fn >> word) {
        v.push_back(word);
    }
    return v;
}

int recursive_spell_check(const string& word1, const string& word2, int n, int m) {
    //base case
    if(n == 0){return m;}
    if(m == 0){return n;}

    int if_same;
    if(word1[n-1] == word2[m-1]){if_same = 0;}
    else{if_same = 1;}

    return min({ //return the least amount of moves per
        recursive_spell_check(word1,word2,n-1,m) +1,
        recursive_spell_check(word1,word2,n,m-1) +1,
        recursive_spell_check(word1,word2,n-1,m-1) + if_same
        });
}

int get_distance(const string w1, const string w2) {
    return recursive_spell_check(w1,w2,w1.size(),w2.size());
}


vector<string> find_closest_5(const string& misspelled, const vector<string>words) {
    vector<pair<int,string>> num_of_distance; //holds the word and the value of moves

    for(auto word : words) {
        int distance = get_distance(misspelled,word);
        num_of_distance.push_back({distance,word});
    }

    sort(num_of_distance.begin(),num_of_distance.end()); //for some reason ranges didnt work.

    vector<string> suggestions;
    for(auto i = 0; i<5;i++) {
        suggestions.push_back(num_of_distance[i].second);
    }
    return suggestions;
}

int main() {
   vector<string> spelling_words = read_file("../words.txt");

    string test1 = "jugl";
    string test2 = "bog";

     vector<string> words1 = find_closest_5(test1,spelling_words);
    for(auto word : words1) {
        cout<<word<<" ";
    }
    cout<<endl;

    vector<string> words2 = find_closest_5(test2,spelling_words);
    for(auto word : words2) {
        cout<<word<<" ";
    }
    cout<<endl;

    return 0;
}
//
//  align.cpp
//  dna_alignment
//
//  Created by Erika DeBenedictis on 1/27/13.
//  Copyright (c) 2014 California Institute of Technology. All rights reserved.
//
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

// scoring values
#define GAP_SCORE -5
#define MISMATCH -1
#define MATCHING 2

/**
 * @brief Packages the score and instruction string the align function returns
 */
struct align_result 
{
    int score;      // score of this alignment
    string inst;    // instruction on how to align the inputs

    align_result(int s, string i) 
    {
        this->score = s;
        this->inst = i;
    }
    align_result() 
    {
        this->score = 0;
        this->inst = "";
    }
};

// memo_type will allow us to hash the string input to align
// with its output for memoization
typedef unordered_map<string, align_result> memo_type;

/**
 * @brief Function takes two strings, s and t, and produces an align_result
 * of the highest alignment score and its corresponding instruction str.
 */
align_result align(string s, string t, memo_type &memo) {
    // if this result is memoized, use recorded result
    string key = s + "," + t;
    if (memo.count(key) > 0)
    {
      return memo[key];
    }
    // If either string is empty, the alignment obect is calculated to 
    // contain a blank for every character still in the existing string.
    if (s.length() == 0)
    {
        align_result answer;
        for (unsigned int i = 0; i < t.length(); i++)
        {
            answer.inst += "t";
            answer.score += GAP_SCORE;
        }
        // The unordered map is updated, and the answer returned
        memo[key] = answer;
        return answer;
    }
    // Similar code pertaining to if the second string is empty
    else if (t.length() == 0)
    {
        align_result answer;
        for (unsigned int i = 0; i < s.length(); i++)
        {
            answer.inst += "s";
            answer.score += GAP_SCORE;
        }
        memo[key] = answer;
        return answer;
    }
    
    // If the program reaches this point, we know that both strings
    // have content. We know that after calling this function, the 
    // unordered map will be updated; thus, we can get away with only 
    // storing the scores  of the alignment objects we obtain recursively
    // knowing that the actual objects can be found in constant time 
    // using the map. I am so careful with memory usage in this portion
    // because the recursion can lead to memory stored before this portion 
    // being compounded. 
    
    int blank_s = GAP_SCORE;
    blank_s += align(s.substr(1, s.length() - 1), t, memo).score;
    
    int blank_t = GAP_SCORE;
    blank_t += align(s, t.substr(1, t.length() - 1), memo).score;
    
    int both_chars = 0;
    if (s[0] == t[0])
    {
        both_chars = MATCHING;
    }
    else
    {
        both_chars = MISMATCH;
    }
    both_chars += align(s.substr(1, s.length() - 1), 
                        t.substr(1, t.length() - 1), memo).score;
                        
    // We now have the scores of each possibility. We will next find the 
    // maximum score and update the alignment object accordingly. 
    align_result answer;
    if (blank_t >= blank_s && blank_t >= both_chars)
    {
        align_result temp = 
                     memo[s + "," + t.substr(1, t.length() - 1)];
        answer.inst = "t" + temp.inst;
        answer.score = blank_t;
    }
    else if (blank_s >= blank_t && blank_s >= both_chars)
    {
        align_result temp = 
                     memo[s.substr(1, s.length() - 1) + "," + t];
        answer.inst = "s" + temp.inst;
        answer.score = blank_s;
    }
    else // both_chars is the max
    {
        align_result temp = memo[s.substr(1, s.length() - 1) + "," + 
                                 t.substr(1, t.length() - 1)];
        if (s[0] == t[0])
        {
            answer.inst = "|" + temp.inst;
        }
        else
        {
            answer.inst = "*" + temp.inst;
        }
        answer.score = both_chars;
    }

    
    memo[key] = answer;
    return answer;
}

/**
 * @brief Wrapper function to print the results of align
 */
void DNA_align(string s, string t) {
    cout << endl << "Calling DNA align on strings " << s << ", " << t << endl;

    // create the memoization system
    memo_type memo;

    align_result answer = align(s, t, memo);
    string ans = answer.inst;
    int score = answer.score;

    // Printing section
    // line where string s will be printed, spaces inserted
    string line1 = "";
    // line where string t will be printed, spaces inserted
    string line2 = "";
    // description of the relationship between s and t here (* | s t)
    string line3 = "";

    int j = 0;      // running index in s
    int k = 0;      // running index in t

    for (unsigned int m = 0; m < ans.length(); m++) 
    {
        // i is the next element in our instruction string ans
        string i = ans.substr(m, 1);

        // only in s
        if(i.compare("s") == 0)
        {
            line1 += s[j]; j++;
            line2 += " ";
            line3 += "s";
        }

        // only in t
        else if (i.compare("t") == 0)
        {
            line1 += " ";
            line2 += t[k]; k++;
            line3 += "t";
        }

        // mismatch
        else if (i.compare("*") == 0)
        {
            line1 += s[j]; j++;
            line2 += t[k]; k++;
            line3 += "*";
        }

        // match
        else 
        {
            line1 += s[j]; j++;
            line2 += t[k]; k++;
            line3 += "|";
        }
    }
    cout << line1 << endl << line2 << endl << line3 << endl;
    cout << "Score for this alignment: " << score << endl;
}

int main()
{
    // some test cases to begin with
    DNA_align("",   "a");
    DNA_align("b",  "");
    DNA_align("a", "a");
    DNA_align("b",  "a");
    DNA_align("b",  "ba");
    DNA_align("ab", "ba");
    DNA_align("ab", "b");
    DNA_align("abracadabra", "avada kedavra");
    
    
    // 1st is giant anteater virus
    // 2nd is penguin virus
    DNA_align("ataatggattcccacactgtgtcaagctttcaggtagattgcttcctttggcatgtccgcaaacaagttgcagaccaagatctaggcgatgcccccttccttgatcggcttcgccgagatcagaagtctctaaagggaagaggcagcactctcggtctgaacatcgaaacagctacttgtgttggaaagcaaatagtagagaggattctgaaagaagaatccgatgaggcacttaaaatgaccattgcctccgcacttgcttcgcggtacctaactgacatgactgttgaagaaatgtcaagggactggttcatgctcatgcccaagcaaaaagtggctggccctctttgtgtcagaatggaccaggcaataatggataagaacatcatactgaaagcgaatttcagtgtgatttttgaccggttggagaatctgacattgctaagggctttcaccgaagagggagcaattgttggcgaaatttcaccattgccttcttttccaggacatactaatgaggatgtcaaaaatgcaattggggtcctcatcgggggacttgaatggaatgataacacagttcgagtctctgaaactctacagagattcgcttggagaagcagtaatgagactgggggacctccatacactacaacacagaaacggaaaatggcgggaacaactaggtcagaagtttgaagaaataagatggctgattgaagaagtgaggcataaattgaagacgacagaaaatagttttgagcaaataacatttatgcaagcattacagctattatttgaagtggaacaagagattagaacgttttcgtttcagcttatttagtgataaaaaa",
              "acaaaaacataatggattccaacactgtgtcaagctttcaggtagactgctttctttggcatgtccgcaaacgatttgcagaccaagaactgggtgatgccccattccttgaccggcttcgccgagatcagaaatccctgagaggaagaggcagcactcttggtctggatatcgaaacagccactcgtgctggaaagcaaatagtggagcggattctagaggaaggatctgacgaggcacttagaatgaccattgcttctgtacctgcttcacgctatctaactgacatgactcttgaggaaatgtcaagggattggttcatgctcatgcccaaacagaaaatggtgggctccctctgtgtcagggtggaccaagcgatcgtggataagaatatcatactgaaagcgaatttcagtgtaatttttgaccggctggagacgctgatactgctcagggcttttactgaagaaggggcaattgtcggagaaatttcaccattgccttctcttccaggacatactgataaggatgtcaaaaatgcaattgggatcctcatcggaggacttgaatggaatgataacacagttcgagtctctgaaactctacagagattcgcttggagaggcggtaatgaggatgggagatctccactccctccaaagcagaaacggaaagtggcgagaacaattgagtcagaagtttgaagaaataaggtggttgattgaagaagtgcggcatagactgaaggttacagagaatagttttgagcaaataacatttatgcaagccttacaactgctgcttgaagtggagcaagagataagaactttctcgtttcagcttatttgatgataa");
              
              
    // First is the 1st 860 base pairs of a human Y chromosome
    // Second is the penguin virus again
    DNA_align("ctaaccctaaccctaaccctaaccctaaccctaaccctctgaaagtggacctatcagcaggatgtgggtgggagcagattagagaataaaagcagactgcctgagccagcagtggcaacccaatggggtccctttccatactgtggaagcttcgttctttcactctttgcaataaatcttgctattgctcactctttgggtccacactgcctttatgagctgtgacactcaccgcaaaggtctgcagcttcactcctgagccagtgagaccacaaccccaccagaaagaagaaactcagaacacatctgaacatcagaagaaacaaactccggacgcgccacctttaagaactgtaacactcaccgcgaggttccgcgtcttcattcttgaagtcagtgagaccaagaacccaccaattccagacacactaggaccctgagacaacccctagaagagcacctggttgataacccagttcccatctgggatttaggggacctggacagcccggaaaatgagctcctcatctctaacccagttcccctgtggggatttaggggaccagggacagcccgttgcatgagcccctggactctaacccagttcccttctggaatttaggggccctgggacagccctgtacatgagctcctggtctgtaacacagttcccctgtggggatttagggacttgggccttctgtctttgggatctactctctatgggccacacagatatgtcttccaacttccctacacaggggggacttcaaagagtgccttgagctgatctggtgattgcttttttgtactgttatttatcttattcttttcattgtgaggtactgatgcaaacactt",
              "acaaaaacataatggattccaacactgtgtcaagctttcaggtagactgctttctttggcatgtccgcaaacgatttgcagaccaagaactgggtgatgccccattccttgaccggcttcgccgagatcagaaatccctgagaggaagaggcagcactcttggtctggatatcgaaacagccactcgtgctggaaagcaaatagtggagcggattctagaggaaggatctgacgaggcacttagaatgaccattgcttctgtacctgcttcacgctatctaactgacatgactcttgaggaaatgtcaagggattggttcatgctcatgcccaaacagaaaatggtgggctccctctgtgtcagggtggaccaagcgatcgtggataagaatatcatactgaaagcgaatttcagtgtaatttttgaccggctggagacgctgatactgctcagggcttttactgaagaaggggcaattgtcggagaaatttcaccattgccttctcttccaggacatactgataaggatgtcaaaaatgcaattgggatcctcatcggaggacttgaatggaatgataacacagttcgagtctctgaaactctacagagattcgcttggagaggcggtaatgaggatgggagatctccactccctccaaagcagaaacggaaagtggcgagaacaattgagtcagaagtttgaagaaataaggtggttgattgaagaagtgcggcatagactgaaggttacagagaatagttttgagcaaataacatttatgcaagccttacaactgctgcttgaagtggagcaagagataagaactttctcgtttcagcttatttgatgataa");
   
    return 0;
}

//
// Created by Snytkine, Dmitri (CORP) on 2/26/17.
//

#include <iostream>
#include <vector>
#include <sstream>


using namespace std;


std::string boolToString(bool b) {
    return (b ? "true" : "false");
}

std::string boolToString(int b) {
    return (b ? "true" : "false");
}

std::string charToString(char c) {
    std::string s;
    s += c;
    return s;
}

bool startsWith(const std::string& str, char prefix) {
    return str.length() > 0 && str[0] == prefix;
}

bool startsWith(const std::string& str, const std::string& prefix) {
    if (str.length() < prefix.length()) return false;
    int nChars = prefix.length();
    for (int i = 0; i < nChars; i++) {
        if (str[i] != prefix[i]) return false;
    }
    return true;
}


bool stringContains(const std::string& s, char ch) {
    return s.find(ch) != std::string::npos;
}

bool stringContains(const std::string& s, const std::string& substring) {
    return s.find(substring) != std::string::npos;
}


int stringIndexOf(const std::string& s, char ch, int startIndex) {
    size_t index = s.find(ch, (size_t) startIndex);
    if (index == std::string::npos) {
        return -1;
    } else {
        return index;
    }
}

int stringIndexOf(const std::string& s, const std::string& substring, int startIndex) {
    size_t index = s.find(substring, (size_t) startIndex);
    if (index == std::string::npos) {
        return -1;
    } else {
        return index;
    }
}

//
//
//
std::string stringJoin(const std::vector<std::string>& v, const std::string& delimiter) {
    if (v.empty()) {
        return "";
    } else {
        std::ostringstream out;
        out << v[0];
        for (int i = 1; i < (int) v.size(); i++) {
            out << delimiter;
            out << v[i];
        }
        return out.str();
    }
}

std::string stringJoin(const std::vector<std::string>& v, char delimiter) {
    std::string delim = charToString(delimiter);
    return stringJoin(v, delim);
}



int stringLastIndexOf(const std::string& s, char ch, int startIndex) {
    size_t index = s.rfind(ch, (size_t) startIndex);
    if (index == std::string::npos) {
        return -1;
    } else {
        return index;
    }
}

int stringLastIndexOf(const std::string& s, const std::string& substring, int startIndex) {
    size_t index = s.rfind(substring, (size_t) startIndex);
    if (index == std::string::npos) {
        return -1;
    } else {
        return index;
    }
}


int stringReplaceInPlace(std::string& str, char old, char replacement, int limit) {
    int count = 0;
    for (size_t i = 0, len = str.length(); i < len; i++) {
        if (str[i] == old) {
            str[i] = replacement;
            count++;
            if (limit > 0 && count >= limit) {
                break;
            }
        }
    }
    return count;
}

int stringReplaceInPlace(std::string& str, const std::string& old, const std::string& replacement, int limit) {
    int count = 0;
    size_t startIndex = 0;
    size_t rlen = replacement.length();
    while (limit <= 0 || count < limit) {
        size_t index = str.find(old, startIndex);
        if (index == std::string::npos) {
            break;
        }
        str.replace(index, old.length(), replacement);
        startIndex = index + rlen;
        count++;
    }
    return count;
}


std::string stringReplace(const std::string& str, char old, char replacement, int limit) {
    std::string str2 = str;
    stringReplaceInPlace(str2, old, replacement, limit);
    return str2;
}

std::string stringReplace(const std::string& str, const std::string& old, const std::string& replacement, int limit) {
    std::string str2 = str;
    stringReplaceInPlace(str2, old, replacement, limit);
    return str2;
}


std::vector<std::string> stringSplit(const std::string& str, const std::string& delimiter, int limit) {
    std::string str2 = str;
    std::vector<std::string> result;
    int count = 0;
    size_t index = 0;
    while (limit < 0 || count < limit) {
        index = str2.find(delimiter);
        if (index == std::string::npos) {
            break;
        }
        result.push_back(str2.substr(0, index));
        str2.erase(str2.begin(), str2.begin() + index + delimiter.length());
        count++;
    }
    if ((int) str2.length() > 0) {
        result.push_back(str2);
    }

    return result;
}


std::vector<std::string> stringSplit(const std::string& str, char delimiter, int limit) {
    std::string delim = charToString(delimiter);
    return stringSplit(str, delim, limit);
}


bool endsWith(const std::string& str, char suffix) {
    return str.length() > 0 && str[str.length() - 1] == suffix;
}

bool endsWith(const std::string& str, const std::string& suffix) {
    int nChars = suffix.length();
    int start = str.length() - nChars;
    if (start < 0) return false;
    for (int i = 0; i < nChars; i++) {
        if (str[start + i] != suffix[i]) return false;
    }
    return true;
}



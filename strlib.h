//
// Created by Snytkine, Dmitri (CORP) on 2/26/17.
//

#ifndef ROUTER_STRLIB_H
#define ROUTER_STRLIB_H
#include <vector>

/*
 * Returns the string "true" if b is true, or "false" if b is false.
 */
std::string boolToString(bool b);

/*
 * Returns the string "true" if b is nonzero, or "false" if b is 0.
 */
std::string boolToString(int b);

/*
 * Returns an integer equivalent of the given numeric character.
 * For example, charToInteger('3') returns the int 3.
 * If the character is not '0' through '9', throws an error.
 */
int charToInteger(char c);

/*
 * Returns a single-character string containing the given character.
 * For example, charToString('Q') returns the string "Q".
 */
std::string charToString(char c);


/*
 * A variant of stringReplace, except that it accepts the string as a reference
 * and modifies it in-place rather than returning a new string.
 */
int stringReplaceInPlace(std::string& str, char old, char replacement, int limit = -1);
int stringReplaceInPlace(std::string& str, const std::string& old, const std::string& replacement, int limit = -1);


/*
 * Function: startsWith
 * Usage: if (startsWith(str, prefix)) ...
 * ---------------------------------------
 * Returns <code>true</code> if the string <code>str</code> starts with
 * the specified prefix, which may be either a string or a character.
 */
bool startsWith(const std::string& str, char prefix);
bool startsWith(const std::string& str, const std::string& prefix);

/*
 * Returns true if the given substring or character occurs somewhere in s.
 */
bool stringContains(const std::string& s, char ch);
bool stringContains(const std::string& s, const std::string& substring);

/*
 * Returns the index of the start of the first occurrence of the given character
 * or substring in s, if it occurs in s.  If it does not occur, returns -1.
 * This function is very similar to string.find, but find returns string::npos
 * when the string is not found.
 */
int stringIndexOf(const std::string& s, char ch, int startIndex = 0);
int stringIndexOf(const std::string& s, const std::string& substring, int startIndex = 0);


/*
 * Combines the elements of the given STL vector into a single string,
 * with the given delimiter separating neighboring elements, and returns it.
 * For example, joining the elements of the vector
 * {"Hi", "there", "", "Jim"} with the delimiter "?" returns "Hi?there??Jim".
 */
std::string stringJoin(const std::vector<std::string>& v, char delimiter = '\n');
std::string stringJoin(const std::vector<std::string>& v, const std::string& delimiter = "\n");

/*
 * Returns the index of the start of the last occurrence of the given character
 * or substring in s, if it occurs in s.  If it does not occur, returns -1.
 * This function is very similar to string.rfind, but rfind returns string::npos
 * when the string is not found.
 */
int stringLastIndexOf(const std::string& s, char ch, int startIndex = (int) std::string::npos);
int stringLastIndexOf(const std::string& s, const std::string& substring, int startIndex = (int) std::string::npos);

/*
 * Returns a new string formed by replacing any occurrences of the given 'old'
 * character or text with the given replacement text in 'str'.
 * Note that this is NOT a regular expression replacement; it looks for the
 * 'old' string literally.  If you want regular expressions, see regexpr.h.
 * The 'inPlace' variant modifies an existing string rather than returning a new one,
 * and returns the number of occurrences of 'old' were replaced.
 */
std::string stringReplace(const std::string& str, char old, char replacement, int limit = -1);
std::string stringReplace(const std::string& str, const std::string& old, const std::string& replacement, int limit = -1);

/*
 * Returns an STL vector whose elements are strings formed by splitting the
 * given string 'str' by the given separator.
 * For example, splitting "Hi there  Jim!" on " " returns
 * {"Hi", "there", "", "Jim!"}.
 */
std::vector<std::string> stringSplit(const std::string& str, char delimiter, int limit = -1);
std::vector<std::string> stringSplit(const std::string& str, const std::string& delimiter, int limit = -1);


#endif //ROUTER_STRLIB_H


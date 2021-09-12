// Cyrillic.cpp : This file contains the 'main' function. Program execution begins and ends there.
// 
// Problem to be solved is to translate an input string of 7bit ASCII characters into Wide-string output of Cyrillic characters.
// A table of decoded Cyrillic characters is included in this source to translate each input string character.
// This table is completely arbitary order of Cyrillic characters, matching each of the displayable ASCII characters.
// The decode solution table is output after the encoded Cyrillic character output.
// The OS must be able to display Cyrillic characters.
//
// The two character tables are size checked to be sure all characters can be translated.
// The input string is checked for 7bit, displayable characters.
// 
// Author: Mark Colvin (email is mark.a.colvin.tx@gmail.com) - Sept 11, 2021
// Uses C++ 11 std, created on VS 2019, tested on Win10 and Ubuntu v18.04
// 
// Usage: cyrillic "input"
// Output: convert "input" text supplied by user to match Cyrillic decode matrix
//  each input character is displayed with corresponding Cyrillic entry, equal sign between each these.
//

#include <iostream>
#include <string>
#include <ctype.h>
#include <cwchar>
#include <windows.h>
#include <locale>
using namespace std;

//using std::string;

// plaintext aplhabet as sample, this code is a problem to compile in most cases. Not used, see the initialization below
string plainAlphabet = " !#$&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[]^_`abcdefghijklmnopqrstuvwxyz{|}~" + 0x22 + 0x25 + 0x5c; //plus dbl quote and percnt

		// Cyrillic alphabet chars, used to match the plaintext array below - arbitrary oder of cyrillic chars
const wchar_t* cyrillicAlphabet_t = L" ЂЃѓЉЊЌЋЏђљњќћџЎўЈҐЁЄЇІіґµёєјЅѕїАБВГДЕЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯабвгдежзийклмнопрстуфхцчшщъыьэю"; //chars pulled from CP1251

bool decodeTable[128] = { 0 };	// flags which chars to display in decode table output



int main(int argc, char* argv[])
{

	string text = "";
	wchar_t cipherText_t[512] = { 0 };

	if (argc > 1)
	{
		text = argv[1];		//commandline parameter is the input string
	}
	else
	{
		cout << "\nEnter any String :: ";	//lack of commandline parameter requires user to input string from console
		cin >> text;

	}
	// setup the plain alphabet here, easier to do this way instead of hard coded text. (too many issues with special chars used for special handling)
	plainAlphabet = "";
	for (auto i = 32; i < 127; i++)
		plainAlphabet += char(i);		//build the alphabet array, starting with space char, thru char 127 - all displayable chars

	{
		int inputLen = text.size();
		wstring ws(cyrillicAlphabet_t);

		if (plainAlphabet.size() == ws.size()) // confirm Alphabet array size is same, else fail
		{
 			for (int i = 0; i < inputLen; ++i)		//each input character is used to find position in decode matrix and add the corresponding entry to output
			{
				int oldCharIndex = plainAlphabet.find(text[i]);		
					//use the find attribute to search the first instance of the character from input string in the plain alphabet array
				if (oldCharIndex >= 0)				//if character is found in plain alphabet, continue
				{
					wchar_t new_t = cyrillicAlphabet_t[oldCharIndex];	//capture the cyrillic alphabet entry for this plain alphabet position
					cipherText_t[i] = (new_t);							// add this entry to output data array

					decodeTable[oldCharIndex] = 1;						//mark which plain alphabet entry is to be included in the decode table
				}
				else
				{
					//wstring ws2(text[i]);
					cipherText_t[i] = cyrillicAlphabet_t[0];	//if input character is not found in plain alphabet array, use a blank char here 
				}
			}
			//	cout << "\n";
		}
		else
		{
			cout << "Decode alphabets are not compatiable.\n";		//alphabet arrays are not the same size, error
			exit(0);
		}

	}

	{
		bool bmore = 0;									//flag to use comma or period in printing the decode table.
//		cout << "plain=" << plainAlphabet << "\n";		//display the plain alphabet (testing for console text display)

		setlocale(LC_ALL, "Russian");
		SetConsoleOutputCP(1251);						//enable Cyrillic display font in Windows
		SetConsoleCP(1251);

//		wcout << "cyrillic=" << cyrillicAlphabet_t << "\n";		//display the Cyrillic alphabet (testing for console text display)
		wcout << cipherText_t << "\n";					//display the resulting wide string of cyrillic characters to console

		for (auto i = 0; i < 128; i++)					// display the decode table, plain char = cyrillic char
		{
 			if (decodeTable[i])
			{
				wchar_t char_t = cyrillicAlphabet_t[i];
				if (bmore)
					cout << ", ";						//more chars to decode after the first one
				cout << plainAlphabet[i] << "=";
				wcout << char_t;						//special for wide string chars
				bmore = 1;
			}
		}
		cout << ".\n";									//end of decode table
	}
}

//  --- end of source ---
/* character compare of each table
 !"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz{|}~		plain
 ЂЃѓЉЊЌЋЏђљњќћџЎўЈҐЁЄЇІіґµёєјЅѕїАБВГДЕЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯабвгдежзийклмнопрстуфхцчшщъыьэю     cyrillic
*/

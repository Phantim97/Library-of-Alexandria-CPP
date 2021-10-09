#include <iostream>
#include <regex>
#include <string>

/*
Regex syntax

.		any character except a newline
?		0 or 1 following character (i.e) in abc? you can have 0 or 1 c's for it to be valid
*		0 or more following characters (i.e) in abc* you can 0 to infinte number of c's 
+		1 or more following characters (cannot be 0) (i.e) abc+ 1 to infinite c

[]		Any character inside the bracket can be matched, if the string contains what's inside the brackets ie ab[cd]* works for all strings that have
		an infinite amount of c or d or cd at the end regardless of order
[^]		Opposite of one above
{#}		Exactly the # of characters shown for the previous case
{#,}	# or more characters shown 
{#,#}	Ranged version of above
|		Or
()		Group, if \\# exists then the group in () is expected to follow after the part of the string

\. \?   Uses the character form of these rather than regex command
*/

/*
Table of classes

[:alnum:]	Alpha numeric (isalnum)
[:alpha:]	Alphabetic character (isalpha)
[:blank:]	Blank character (matches only space and tab)
[:cntrl:]	Control character (iscntrl)
[:digit:]	Decimal digit character(is digit)
[:graph:]	Character with graphical representation (isgraph)
[:lower:]	Lowercase character (islower)
[:print:]	Printable character (isprint)
[:punct:]	Punctuation mark character (ispunct)
[:space:]	Whitespace character (isspace)
[:upper:]	Uppercase letter (isupper)
[:xdigit:]  Hexadecimal digit character (isxdigit)
[:d:]		Decimal digit character (isdigit)
[:w:]		Word character (isalnum)
[:s:]		Whitespace character (isspace)
*/

//regex_match finds if string matches 
//regex_search searches string for matching substring

// Part 1: Basics

void basic_regex()
{
	std::string test;
	std::cout << ". and icase example\n";
	for (int i = 0; i < 10; i++)
	{
		std::cout << "Enter string #" << i+1 << ": ";
		std::cin >> test;

		std::regex reg("abc.", std::regex_constants::icase); // ignore capitalization, . any character

		bool match = std::regex_match(test, reg);

		std::cout << (match ? "Match Found!" : "No Match") <<'\n';
	}

	std::cout << "? example\n";
	std::string test2;
	for (int i = 0; i < 10; i++)
	{
		std::cout << "Enter string #" << i + 1 << ": ";
		std::cin >> test2;

		std::regex reg("abc?", std::regex_constants::icase);

		bool match = std::regex_match(test2, reg);

		std::cout << (match ? "Match Found!" : "No Match") << '\n';
	}

	std::cout << "* example\n";
	std::string test3;
	for (int i = 0; i < 10; i++)
	{
		std::cout << "Enter string #" << i + 1 << ": ";
		std::cin >> test3;

		std::regex reg("abc*", std::regex_constants::icase);

		bool match = std::regex_match(test3, reg);

		std::cout << (match ? "Match Found!" : "No Match") << '\n';
	}

	std::cout << "+ example\n";
	std::string test4;
	for (int i = 0; i < 10; i++)
	{
		std::cout << "Enter string #" << i + 1 << ": ";
		std::cin >> test4;

		std::regex reg("abc+", std::regex_constants::icase); // ignore capitalization, . any character

		bool match = std::regex_match(test4, reg);

		std::cout << (match ? "Match Found!" : "No Match") << '\n';
	}
}

void basic_regex2()
{
	std::cout << "[] example\n";
	std::string test;
	for (int i = 0; i < 10; i++)
	{
		std::cout << "Enter string #" << i + 1 << ": ";
		std::cin >> test;

		std::regex reg("ab[cd]*"); 

		bool match = std::regex_match(test, reg);

		std::cout << (match ? "Match Found!" : "No Match") << '\n';
	}

	std::cout << "[^] example\n";
	std::string test2;
	for (int i = 0; i < 10; i++)
	{
		std::cout << "Enter string #" << i + 1 << ": ";
		std::cin >> test2;

		std::regex reg("ab[^cd]*");

		bool match = std::regex_match(test2, reg);

		std::cout << (match ? "Match Found!" : "No Match") << '\n';
	}

	std::cout << "[]{} example\n";
	std::string test3;
	for (int i = 0; i < 10; i++)
	{
		std::cout << "Enter string #" << i + 1 << ": ";
		std::cin >> test3;

		std::regex reg("ab[cd]{3}"); // 3 c's or 3 d's or mix 

		bool match = std::regex_match(test3, reg);

		std::cout << (match ? "Match Found!" : "No Match") << '\n';
	}

	std::cout << "[]{#,} example\n";
	std::string test4;
	for (int i = 0; i < 10; i++)
	{
		std::cout << "Enter string #" << i + 1 << ": ";
		std::cin >> test4;

		std::regex reg("ab[cd]{3,}"); // 3 c's or more 3 d's or more or mix 

		bool match = std::regex_match(test4, reg);

		std::cout << (match ? "Match Found!" : "No Match") << '\n';
	}

	std::cout << "[]{#,#} example\n";
	std::string test5;
	for (int i = 0; i < 10; i++)
	{
		std::cout << "Enter string #" << i + 1 << ": ";
		std::cin >> test5;

		std::regex reg("ab[cd]{4,6}"); // 3 c's or more 3 d's or more or mix 

		bool match = std::regex_match(test5, reg);

		std::cout << (match ? "Match Found!" : "No Match") << '\n';
	}
}

void basic_regex3()
{
	std::string test;
	std::cout << "| example\n";
	for (int i = 0; i < 10; i++)
	{
		std::cout << "Enter string #" << i + 1 << ": ";
		std::cin >> test;

		std::regex reg("abc|de[fg]"); // Can either ba abc or de + an f or g

		bool match = std::regex_match(test, reg);

		std::cout << (match ? "Match Found!" : "No Match") << '\n';
	}

	std::cout << "() example\n";
	for (int i = 0; i < 10; i++)
	{
		std::cout << "Enter string #" << i + 1 << ": ";
		std::cin >> test;

		std::regex reg("(abc)de+\\1"); // \ before \ is to make \1 in regex which means group will appear after de, group = abc

		bool match = std::regex_match(test, reg);

		std::cout << (match ? "Match Found!" : "No Match") << '\n';
	}

	std::cout << "multiple () example\n";
	for (int i = 0; i < 10; i++)
	{
		std::cout << "Enter string #" << i + 1 << ": ";
		std::cin >> test;

		std::regex reg("(ab)c(de+)\\2\\1"); //2 for 2nd group then 1 for first group ex: abcdedeab

		bool match = std::regex_match(test, reg);

		std::cout << (match ? "Match Found!" : "No Match") << '\n';
	}
}

void email_search()
{
	std::string email;
	std::cout << "Email finder\n";
	for (int i = 0; i < 10; i++)
	{
		std::cout << "Enter email #" << i + 1 << '\n';
		std::getline(std::cin, email);

		//one or more word characters followed by an @ and then one or more word character followed by .com
		std::regex e("[[:w:]]+@[[:w:]]+\.com"); //[[:w:]] word character: digit,number or underscore (group of characters)
		// \. makes the . a character and not a symbol in regex
		bool match = std::regex_match(email, e);

		std::cout << (match ? "Match Found!" : "No Match") << '\n';
	}
}

void search_example()
{
	std::string s;
	for (int i = 0; i < 10; i++)
	{
		std::cin >> s;
		std::regex e("abc.$", std::regex_constants::icase);
		// if you do ^abc. the ^ means that it must be at the beginning for regex search
		// a $ sign at the end like abc.$ it will only work if abc. is at the end
		bool match = std::regex_search(s, e);

		std::cout << (match ? "Match Found!" : "No Match") << '\n';
	}
}

// Part 2: Submatching

void submatch() //extracting
{
	std::string email;
	std::smatch m; // typdef std::match_results<string>

	std::cout << "Email finder\n";
	for (int i = 0; i < 10; i++)
	{
		std::cin >> email;
		std::regex extractor("([[:w:]]+)@([[:w:]]+)\.com");

		// find result in email and store results in m
		bool found = std::regex_search(email, m, extractor);

		//m[0] = full string
		//m[1] = first () group
		//m[n] = nth subgroup

		std::cout << "m.size(): " << m.size() << '\n';
		for (std::smatch::iterator it = m.begin(); it != m.end(); it++)
		{
			//These two are if for loop is iterating via constant (sample is j)
			//std::cout << "m[" << j << "]: str()=" << m.str(j) << '\n';
			//std::cout << "m[" << j << "]: str()=" << m[j].str() << '\n';
			std::cout << "m[" << it-m.begin() << "]: str()=" << *it << '\n';
		}
		// prefix is everything in front of the matched string and suffix is
		// is everything after the matched string
		std::cout << "m.prefix().str(): " << m.prefix().str() << '\n';
		std::cout << "m.suffix().str(): " << m.suffix().str() << '\n';
	}
}

// Part 3: Iterators

void iterator()
{
	std::string str = "tim@coelho.com; chelsea22@coelho.com;;   lindsay@coelho3.com";

	std::regex e("([[:w:]]+)@([[:w:]]+)\.com");

	// The following is used to extract the emails from a string over whitespace
	// Iterator repeatedly performs the regular expression
	// Iterator points to matched results
	std::sregex_iterator pos(str.cbegin(), str.cend(), e);
	std::sregex_iterator end; // Default constructor defines past-the-end iterator

	for (; pos != end; pos++)
	{
		std::cout << "Matched: " << pos->str(0) << '\n';
		std::cout << "Username: " << pos->str(1) << '\n';
		std::cout << "Domain: " << pos->str(2) << '\n';
		std::cout << '\n';
	}
}

void token_iterator()
{
	std::string str = "tim@coelho.com; chelsea22@coelho.com;;   lindsay@coelho3.com";

	std::regex e("([[:w:]]+)@([[:w:]]+)\.com");

	//Token iterator only takes the submatch
	// it does perform it repeatedly

	// optional paramter below
	// 0 = full string extracted
	// # = # subgroup extracted
	// -1 = only mismatch sections are extracted

	std::sregex_token_iterator pos(str.cbegin(), str.cend(), e);
	std::sregex_token_iterator end; // Default constructor defines past-the-end iterator

	for (; pos != end; pos++)
	{
		std::cout << "Matched: " << pos->str() << '\n';
	}
}

void replacement()
{

	std::string str = "tim@coelho.com; chelsea22@coelho.com;;   lindsay@coelho3.com";

	std::regex e("([[:w:]]+)@([[:w:]]+)\.com");

	// Replace all the matched strings with the string specified
	// replace can take a fourth flag
	// format_no_copy means non-matched items are not copied, first only means first is copied
	// flags can be or'd
	std::cout << std::regex_replace(str, e, "$1 is on $2 ", std::regex_constants::format_no_copy | std::regex_constants::format_first_only);
	std::cout << '\n';
}

int main()
{
	basic_regex();
	basic_regex2();
	basic_regex3();
	email_search();
	
	submatch();
	
	iterator();
	token_iterator();
	replacement();
	system("pause");
	return 0;
}

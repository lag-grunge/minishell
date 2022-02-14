#include "tests.hpp"

TEST(Match, ast_end) {
	std::string pat = "*.c";
	std::string filename = "fergerg.c";
	int res = match((char *)filename.c_str(), (char *)pat.c_str());

	EXPECT_EQ(res, 1);
}


TEST(Match, ast_only_empty) {
	std::string pat = "*";
	std::string filename = "";
	int res = match((char *)filename.c_str(), (char *)pat.c_str());

	EXPECT_EQ(res, 1);
}

TEST(Match, ast_in_filename) {
	std::string pat = "*a*";
	std::string filename = "*a**";
	int res = match((char *)filename.c_str(), (char *)pat.c_str());

	EXPECT_EQ(res, 1);
}

TEST(Match, ast_only_everything) {
	std::string pat = "*";
	std::string filename = "wrfgefwen''fiwe***fiw'e'f";
	int res = match((char *)filename.c_str(), (char *)pat.c_str());

	EXPECT_EQ(res, 1);
}

TEST(Match, ast_and_ast_in_quotes) {
	std::string pat = "*'***'*";
	std::string filename = "wrfgefwen''fiwe***fiw'e'f";
	int res = match((char *)filename.c_str(), (char *)pat.c_str());

	EXPECT_EQ(res, 1);
}

TEST(Match, ast_and_ast_in_quotes2) {
	std::string pat = "*'****'*";
	std::string filename = "wrfgefwen''fiwe***fiw'e'f";
	int res = match((char *)filename.c_str(), (char *)pat.c_str());

	EXPECT_EQ(res, 0);
}

TEST(Match, ast_and_ast_in_quotes3) {
	std::string pat = "*'***'";
	std::string filename = "wrfgefwen''fiwe***fiw'e'f";
	int res = match((char *)filename.c_str(), (char *)pat.c_str());

	EXPECT_EQ(res, 0);
}

TEST(Match, ast_and_ast_in_quotes_and_smth) {
	std::string pat = "w***'rf''***'*e*f";
	std::string filename = "wrfgefwen''fiwe***fiw'e'f";
	int res = match((char *)filename.c_str(), (char *)pat.c_str());

	EXPECT_EQ(res, 0);
}

TEST(Match, ast_and_ast_in_quotes_and_smth2) {
	std::string pat = "w***'rf'*'***'*e*f";
	std::string filename = "wrfgefwen''fiwe***fiw'e'f";
	int res = match((char *)filename.c_str(), (char *)pat.c_str());

	EXPECT_EQ(res, 1);
}

TEST(Match, ast_and_ast_in_quotes_and_smth3) {
	std::string pat = "w***'rf'*'''***'*e*f";
	std::string filename = "wrfgefwen''fiwe***fiw'e'f";
	int res = match((char *)filename.c_str(), (char *)pat.c_str());

	EXPECT_EQ(res, 1);
}

TEST(Match, ast_and_ast_in_quotes_and_quote_in_filename) {
	std::string pat = "w**\"*'rf'*'''***'*e*f";
	std::string filename = "w\"rfgefwen''fiwe***fiw'e'f";
	int res = match((char *)filename.c_str(), (char *)pat.c_str());

	EXPECT_EQ(res, 1);
}

TEST(Match, ast_and_ast_in_quotes_and_quote_in_filename2) {
	std::string pat = "w**\"*'rf'*'''***'*e*f";
	std::string filename = "w\"r'fgefwen''fiwe***fiw'e'f";
	int res = match((char *)filename.c_str(), (char *)pat.c_str());

	EXPECT_EQ(res, 0);
}

#include "tests.hpp"

TEST(Quote_removal, Unclosed_quote_not_interpreter) {
	std::string in = "'fwefgwef' 'wer'g'werg";
	std::string out = "fwefgwef werg'werg";
	std::string my = quote_removal((char *)in.c_str());

	EXPECT_EQ(my, out);
}


TEST(Quote_removal, Empty_quote_within) {
	std::string in = "'fwefgwef' 'wer'g''werg";
	std::string out = "fwefgwef wergwerg";
	std::string my = quote_removal((char *)in.c_str());

	EXPECT_EQ(my, out);
}

TEST(Quote_removal, Empty_quote_only) {
	std::string in = "''";
	std::string out = "";
	std::string my = quote_removal((char *)in.c_str());

	EXPECT_EQ(my, out);
}

TEST(Quote_removal, Single_quote_symbol_only) {
	std::string in = "'";
	std::string out = "'";
	std::string my = quote_removal((char *)in.c_str());

	EXPECT_EQ(my, out);
}
//	printf("%s\n%s\n\n", "\"*\"", quote_removal("\"*\""));
//	printf("%s\n%s\n\n", "\"*.c\"", quote_removal("\"*.c\""));
//	printf("%s\n%s\n\n", "\"*\'.c\"", quote_removal("\"*\'.c\""));
//	printf("%s\n%s\n\n", "\"*\'.c\"", quote_removal("\"*\'.c\""));
//	printf("%s\n%s\n\n", "\"*\'.\'c\"", quote_removal("\"*\'.\'c\""));
//
//	printf("%s\n%s\n\n", "*.c\"*\"", quote_removal("*.c\"*\""));
//	printf("%s\n%s\n\n", "\"*\"*.c", quote_removal("\"*\"*.c"));
//	printf("%s\n%s\n\n", "*\"*\".c", quote_removal("*\"*\".c"));
//	printf("%s\n%s\n\n", "*.c", quote_removal("*.c"));

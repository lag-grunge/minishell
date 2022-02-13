extern "C" {
#include "minishell.h"
#include "expansions.h"
#include "syntax.h"
#include "libft.h"
}
#include "gtest/gtest.h"

TEST(unclosed_quote_not_interpreter, Unclosed_quote) {
	std::string in = "'fwefgwef' 'wer'g'werg";
	std::string out = "fwefgwef werg'werg";
	std::string my = quote_removal((char *)in.c_str());

	EXPECT_EQ(my, out);
}


TEST(empty_quote_within, Empty_quote_within) {
	std::string in = "'fwefgwef' 'wer'g''werg";
	std::string out = "fwefgwef wergwerg";
	std::string my = quote_removal((char *)in.c_str());

	EXPECT_EQ(my, out);
}

TEST(empty_quote_only, Empty_quote_only) {
	std::string in = "''";
	std::string out = "";
	std::string my = quote_removal((char *)in.c_str());

	EXPECT_EQ(my, out);
}

TEST(Signle_quote_only, Single_quote_only) {
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

#include "gtest/gtest.h"
#include "expansions.h"
#include "libft.h"

static char *s_out;
char *get_func(const char *str) {
	char *s_in = ft_strdup(str);
	s_out = quote_removal(s_in);
	return (s_out);
}

TEST(QuoteTestSuite, Quote_Asterisk){
	ASSERT_STREQ("*.c*", get_func("*.c\"*\""));
}


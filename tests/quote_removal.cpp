#include "gtest/gtest.h"
#include "expansions.h"
#include "libft.h"


TEST(QuoteTestSuite, Quote_Asterisk){
char *s_in;

char *s_out;
s_in = ft_strdup("*.c\"*\"");
s_out = quote_removal(&s_in);
EXPECT_EQ(ft_strncmp(s_out, "*.c*", 5),0);
}


//TEST(AbsoluteDateTestSuite, IncorrectDate){ // 12/0/2020 -> 0
//GregorianDate gregDate;
//gregDate.SetMonth(12);
//gregDate.SetDay(0);
//gregDate.SetYear(2020);
//
//ASSERT_EQ(gregDate.getAbsoluteDate(),0);
//}

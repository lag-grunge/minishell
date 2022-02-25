#include "tests.hpp"


TEST(Get_tokens, test1) {

    char *in = ft_strdup("echo>>egniwergo;fef\"efew efwefefef  \"       $efwefg$$ ab4        ");
    std::string out[] = {"echo", ">>", "egniwergo;fef\"efew efwefefef  \"", "$efwefg$$", "ab4"};
    char **our_out = get_tokens(in, NULL);
    int our_len = ft_spllen(our_out);
    EXPECT_EQ(5, our_len);
    for (int i = 0; i < 5; i++)
        EXPECT_EQ(std::string(our_out[i]), out[i]);
}

TEST(Get_tokens, test_many_redirects) {

    char *in = ft_strdup("echo>>>> > >> >>>>< > >");
    std::string out[] = {"echo", ">>", ">>", ">", ">>", ">>", ">>", "<", ">", ">"};
    char **our_out = get_tokens(in, NULL);
    int our_len = ft_spllen(our_out);
    EXPECT_EQ(10, our_len);
    for (int i = 0; i < 10; i++)
        EXPECT_EQ(std::string(our_out[i]), out[i]);
}

TEST(Get_tokens, test_many_quotes) {

    char *in = ft_strdup("echo \"\"\"'fwefwe' '");
    std::string out[] = {"echo", "\"\"\"\'fwefwe\'","'"};
    char **our_out = get_tokens(in, NULL);
    int our_len = ft_spllen(our_out);
    EXPECT_EQ(3, our_len);
    for (int i = 0; i < 3; i++)
        EXPECT_EQ(std::string(our_out[i]), out[i]);
}

TEST(Get_tokens, test_many_and_pipes_or) {

    char *in = ft_strdup("&&|&&|||");
    std::string out[] = {"&&", "|","&&", "||", "|"};
    char **our_out = get_tokens(in, NULL);
    int our_len = ft_spllen(our_out);
    EXPECT_EQ(5, our_len);
    for (int i = 0; i < 5; i++)
        EXPECT_EQ(std::string(our_out[i]), out[i]);
}

TEST(Get_tokens, test_many_and_pipes_or_redirects_and_smth) {

    char *in = ft_strdup("&&><<|<<&&>|?|*||");
    std::string out[] = {"&&", ">","<<", "|", "<<", "&&", ">", "|", "?", "|", "*", "||"};
    char **our_out = get_tokens(in, NULL);
    int our_len = ft_spllen(our_out);
    EXPECT_EQ(12, our_len);
    for (int i = 0; i < 12; i++)
        EXPECT_EQ(std::string(our_out[i]), out[i]);
}

TEST(Get_tokens, test_wrong_operators_ampersand) {
    int empty;
    char *in = ft_strdup("&>&><<|<<&&>|?|*||");
    get_tokens(in, &empty);
    EXPECT_EQ(1, empty);
}


TEST(Get_tokens, test_2_redirect) {
    int empty;
    char *in = ft_strdup("2>2>>fefe<<fefwe|<fefe<&&>|?|*||>>fef");
    std::string out[] = {"2>", "2>>","fefe", "<<", "fefwe", "|", "<", "fefe", "<", "&&", ">", "|", "?", "|", "*", "||", ">>", "fef"};
    char **our_out = get_tokens(in, &empty);
    int our_len = ft_spllen(our_out);
    EXPECT_EQ(18, our_len);
    for (int i = 0; i < 18; i++)
        EXPECT_EQ(std::string(our_out[i]), out[i]);
}


TEST(Get_tokens, test_empty) {
    int empty;
    char *in = ft_strdup("");
    get_tokens(in, &empty);
    EXPECT_EQ(1, empty);
}

TEST(Get_tokens, ordinary) {

}
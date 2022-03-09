#include "tests.hpp"


TEST(Var_Exp, PWD) {

	char *in = ft_strdup("$PWD");
	std::string out = "/Users/sdalton/CLionProjects/minishell/cmake-build-debug/tests";
	exec_expansion(&in);
	EXPECT_EQ(std::string(in), out);
}

TEST(Var_Exp, dollar_only) {

	char *in = ft_strdup("$ ");
	std::string out = "$ ";
	exec_expansion(&in);
	EXPECT_EQ(std::string(in), out);
}

TEST(Var_Exp, dollar_num) {

    char *in = ft_strdup("$4abc ");
    std::string out = "abc ";
    exec_expansion(&in);
    EXPECT_EQ(std::string(in), out);
}

TEST(Var_Exp, dollar_nonsense_quest_smth) {

    char *in = ft_strdup("$abc43235?;");
    std::string out = "?;";
    exec_expansion(&in);
    EXPECT_EQ(std::string(in), out);
}

TEST(Var_Exp, dollar_status) {

    char *in = ft_strdup("$? ");
    std::string out = "0 ";
    exec_expansion(&in);
    EXPECT_EQ(std::string(in), out);
}

TEST(Var_Exp, set_value) {
    set_value(&g_data.env, ft_strdup("a"), ft_strdup("ab"));
    char *in = ft_strdup("$a ");
    std::string out = "ab ";
    exec_expansion(&in);
    EXPECT_EQ(std::string(in), out);
}

TEST(Var_Exp, unset_value) {
    unset_value(&g_data.env, ft_strdup("a"));
    char *in = ft_strdup("$a ");
    std::string out = " ";
    exec_expansion(&in);
    EXPECT_EQ(std::string(in), out);
}

TEST(Var_Exp, dollar_end) {

    char *in = ft_strdup("fwece$");
    std::string out = "fwece$";
    exec_expansion(&in);
    EXPECT_EQ(std::string(in), out);
}



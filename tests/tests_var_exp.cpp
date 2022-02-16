#include "tests.hpp"

//get_env_hash(&g_data.env, );

TEST(Var_Exp, PWD) {

	char *in = ft_strdup("$PWD");
	std::string out = "/home/dfyz/CLionProjects/minishell/cmake-build-debug/tests";
	exec_expansion(&in);
	EXPECT_EQ(std::string(in), out);
}

TEST(Var_Exp, dollar_only) {

	char *in = ft_strdup("$ ");
	std::string out = "$ ";
	exec_expansion(&in);
	EXPECT_EQ(std::string(in), out);
}

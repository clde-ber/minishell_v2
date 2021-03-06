// compil : gcc find_a_launch_exe.c start_a_parse_bulle.c echo.c env.c gnl.c gnl_utils.c ft_split.c libft_utils.c minishell_utils.c redir.c && ./a.out -fsanitize=address

// new compil : gcc expander_utils.c expander_utils2.c env_utils.c launch_exe.c launch_exe_utils.c start_a_parse_bulle.c echo.c env.c gnl.c gnl_utils.c ft_split.c libft_utils.c minishell_utils.c redir.c libft_utils2.c libft_list.c libft_list2.c libft_utils3.c libft_utils4.c path.c exec.c parse_path.c expander.c debug_to_delete.c && ./a.out

// ---

//***LEXER***
//A lexer is basically a tokenizer, but it usually attaches extra context to the tokens -- this token is a number, that token is a string literal, this other token is an equality operator.


//***EXPANDER***
//After the command has been split into tokens (see Section 1.4.1.1), these tokens or words are expanded or resolved. l'expander va regarder si un lot doit etre traduit : ex var d'environnement
// Brace expansion :
// franky ~> echo sp{el,il,al}l
// spell spill spall
// Tilde expansion :
// franky ~> export PATH="$PATH:~/testdir"
// Shell parameter and variable expansion :
// franky ~> echo $SHELL
// /bin/bash
// Command substitution
// franky ~> echo `date`
// Thu Feb 6 10:06:20 CET 2003
// ...

//***TOKENIZER***
//A tokenizer breaks a stream of text into tokens, usually by looking for whitespace (tabs, spaces, new lines).

// ---

//le traitement de la line doit englober commandes, ; | mais aussi traite guillemets simples & doubles
//$HOME renvoie pwd du profil 
//'$HOME'
//"$HOME"
//gérer les antislashs!!!!!
//deux et fork wait pid sur execve et pipe
// ctrl c d sigkill etc gréer une variable globale signaux = fonctions spécialisées qui dit observe si t'as des signaux fais attention
// derriere tu mets les autres fct sig
//faire le write sur le stderr ?

//bash: exit: afk: numeric argument required (working, 0 if no nb, 2 not found if not a nb, 1 if nb 1, 0 if nb 0) bash: exit: too many arguments
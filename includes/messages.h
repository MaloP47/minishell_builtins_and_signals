/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeulet <mpeulet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 14:23:14 by mpeulet           #+#    #+#             */
/*   Updated: 2023/11/13 10:05:45 by mpeulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGES_H
# define MESSAGES_H

# define DEF "\033[0;39m"
# define GREY "\033[0;90m"
# define RED "\033[0;91m"
# define GREEN "\033[0;92m"
# define YELLOW "\033[0;93m"
# define BLUE "\033[0;94m"
# define MAGENTA "\033[0;95m"
# define CYAN "\033[0;96m"
# define WHITE "\033[0;97m"
# define ORANGE "\033[38;5;214m"
# define BLINK_RED "\033[31;5m"

# define ERR_PWD "pwd: error retrieving current directory: \
getcwd: cannot access parent directories: No such file or directory"

# define ERR_CD "minishrek: cd: %s: No such file or directory\n"
# define ERR_CD_MANY "minishrek: cd: too many arguments\n"
# define ERR_CD_HOME "minishrek: cd: HOME not set\n"
# define ERR_CD_OPWD "minishrek: cd: OLDPWD not set\n"
# define ERR_CD_POINT_ALLOC "error allocating using getcw for cd ..\n"

# define EXP_NO_ARG "export %s"
# define ERR_EXP_PARSE "minishrek: export: `%s': not a valid identifier\n"
# define EXIT_ERR "minishrek: exit: %s: numeric argument required\n"

# define CORE_DUMP "Quit: Core dumped\n"

# define ERR_SIGACTION "error with sigaction\n"

#endif

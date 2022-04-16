# Simple_shell_linux
<p>It supports the following commands:</p>

    The internal shell command "exit" which terminates the shell
    A command with no arguments
        Example: ls, cd, …etc

    A command with arguments
        Example: ls –l

    <p>A command, with or without arguments, executed in the background using &.</p>
        Example: firefox &

    <p>Shell builtin commands</p>
        Commands: cd & echo
        Details: for the case of:
            cd: It covers all the following cases (assume no spaces in path):
                cd
                cd ~
                cd ..
                cd absolute_path
                cd relative_path_to_current_working_directory
            echo: Prints the input after evaluating all experessions (assume input to echo must be within double quotations).
                echo "wow" => wow
                export x=5
                echo "Hello $x" => Hello 5

    <p>Expression evaluation</p>

        Commands: export

        Example:
            export x=-l
            ls $x => Will perform ls -l
            export y="Hello world"
            echo "$y" => Hello world


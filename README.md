<h1 align="center">Simple Shell linux</h1>
<p>It is a program that implement the following commands:

1.The internal shell command "exit" which terminates the shell

2. A command with no arguments

    Example: ls, cd, …etc

 <p> <b> 3. A command with arguments

    Example: ls –l

   <p> <b> 4. A command, with or without arguments, executed in the background using &. </p>

    Example: firefox &

   <p> <b> 5. Shell builtin commands</p>

 <p> <b> Commands: cd & echo </p>
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

6.Expression evaluation

    Commands: export

    Example:
        export x=-l
        ls $x => Will perform ls -l
        export y="Hello world"
        echo "$y" => Hello world
</p>

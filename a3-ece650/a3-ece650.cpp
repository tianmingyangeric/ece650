#include<unistd.h>
#include <iostream>
#include<vector>
#include <sys/wait.h>
#include <signal.h>
#include <string>
using namespace std;
int regn(char **argv,int argc){
    execv("./rgen",argv);
	return 0;
}

int a1_function(void){

    execv("./a1-ece650.py",NULL);
	return 0;
}

int a2_function(void){

    execv("./a2-ece650",NULL);
	return 0;

}
int user_input(void){
    while (!std::cin.eof()) {
        // read a line of input until EOL and store in a string
        std::string line;
        std::getline(std::cin, line);
        if (line.size () > 0)
            std::cout << line << std::endl;
    }
	return 0;
}

int main (int argc, char *argv[]) {
	vector<pid_t> kids;
	int pipe1[2];
	int pipe2[2];
	pipe(pipe2);
	pipe(pipe1);
	pid_t child_pid;
	child_pid = fork();
	if (child_pid == 0)
    {
    // redirect stdout to the pipe
    dup2(pipe2[1], STDOUT_FILENO);
    close(pipe2[0]);
    close(pipe2[1]);   
    return user_input();
    }
    else if (child_pid < 0) {
        std::cerr << "Error: could not fork\n";
        return 1;
    }
    kids.push_back(child_pid);
    child_pid = fork();

    if (child_pid == 0)
    {
        // redirect stdin from the pipe
        dup2(pipe2[0], STDIN_FILENO);
        close(pipe2[0]);
        close(pipe2[1]);  
        return a2_function();
    }
    else if (child_pid < 0) {
        std::cerr << "Error: could not fork\n";
        return 1;
    }

    kids.push_back(child_pid);
    child_pid = fork();
    if (child_pid == 0)
    {   dup2(pipe1[0], STDIN_FILENO);
        close(pipe1[0]);
        close(pipe1[1]);  
        dup2(pipe2[1], STDOUT_FILENO);
        close(pipe2[0]);
        close(pipe2[1]);      
        // redirect stdin from the pipe
        return a1_function();
    }
    else if (child_pid < 0) {
        std::cerr << "Error: could not fork\n";
        return 1;
    }

    kids.push_back(child_pid);
    child_pid = 0;
    // start process B
    dup2(pipe1[1], STDOUT_FILENO);
    close(pipe1[0]);
    close(pipe1[1]);     // Close this too!

    int res =  regn(argv,argc);
    // send kill signal to all children
    for (pid_t k : kids) {
        int status;
        kill (k, SIGTERM);
        waitpid(k, &status, 0);
    }



    return 0;
}





























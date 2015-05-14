#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <unistd.h>

#define READ_BUF 4096

struct IntSet {
	int x[4];
};

void err_sys(char *err) {
	perror(err);
	exit(1);
}

struct IntSet e_euclid(int e, int phi[4]) {

	int phi1 = phi[0];
	int phi2 = phi[1];
	int phi3 = phi[2];
	int phi4 = phi[3];

	pid_t pid;
	int fd[2];

	if(pipe(fd) < 0) {
		err_sys("pipe error");
	}

	if((pid = fork()) < 0) {
		err_sys("fork error");
	} 
	else if(pid > 0) { // parent
		close(fd[1]); // close write end

		if(fd[0] != STDIN_FILENO) { // set STDIN
			if(dup2(fd[0], STDIN_FILENO) != STDIN_FILENO) {
				err_sys("dup2 error");
			}
		}

		char buf[READ_BUF];
		if(read(STDIN_FILENO, buf, READ_BUF) < 0) {
			err_sys("read error");
		}

		// printf("[received]: %s\n", buf);

		struct IntSet my_s;

		/* parse buf */
		const char s[2] = " ";
		char *token = strtok(buf, s);
		int curr = 0;

		while(token != NULL && curr < 4) {
			my_s.x[curr] = atoi(token);
			printf("curr: %d, token: %s\n", curr, token);
			token = strtok(NULL, s);
			curr++;
		}

		if (waitpid(pid, NULL, 0) < 0)
            err_sys("waitpid error");
        
        return my_s;
	} 
	else { // child
		close(fd[0]); // close read end

		if(fd[1] != STDOUT_FILENO) { // set STDOUT
			if(dup2(fd[1], STDOUT_FILENO) != STDOUT_FILENO) {
				err_sys("dup2 error");
			}
		}

		char e_s[READ_BUF]; 

		char phi_s[READ_BUF];
		char phi2_s[READ_BUF]; 
		char phi3_s[READ_BUF];
		char phi4_s[READ_BUF];
		
		snprintf(e_s, READ_BUF, "%d\n", e);

		snprintf(phi_s, READ_BUF, "%d\n", phi1);
		snprintf(phi2_s, READ_BUF, "%d\n", phi2);
		snprintf(phi3_s, READ_BUF, "%d\n", phi3);
		snprintf(phi4_s, READ_BUF, "%d\n", phi4);

		// execute Python script
		execlp("python", "python", "exteuc.py", e_s, phi_s, phi2_s, phi3_s, phi4_s, (char *)NULL);
	}
	exit(1);
	struct IntSet s_val;
	return s_val;
}

int main() {

	int phi[4] = {0, 0, 2, 5};
	struct IntSet s;
	s = e_euclid(2, phi);

	printf("d: %d\n", s.x[3]);
	return 0;
}
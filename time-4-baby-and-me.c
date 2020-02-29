#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/times.h>

void print_USER_SYS_CUSER_and_CSYS(struct tms buf) {
    printf("USER: %ld, SYS: %ld\n", buf.tms_utime, buf.tms_stime);
    printf("CUSER: %ld, CSYS: %ld\n", buf.tms_cutime, buf.tms_cstime);
}

void print_PPid_And_Pid(int getpid, int pid) {
    printf("PPID: %d, PID: %d\n", getpid, pid);
}

void print_PPid_Pid_CPid_And_RETVAL(int ppid, int getppid, int getpid, int pid) {
    printf("PPID: %d, PID: %d, CPID %d, RETVAL: %d\n", ppid, getppid, getpid, pid);
}


int main()
{
    time_t start, stop; //initialize start and stop
    time(&start); //Assign current seconds to start
    int status; //initialize this for to return the status of the child

    struct tms buf; //initializing buffer for to get the user time and system time
    times(&buf); //initializing times to the structure tms
    printf("Start: %ld\n", start); //prints the seconds that the program started with

    pid_t pid = fork(); //fork

    if (pid == 0) { //if pid is at child
        print_PPid_And_Pid(getppid(), getpid()); // prints the parent pid and its own pid
        exit(0);
    } else if (pid > 0) { //if process is at parent
        waitpid(pid, &status, WUNTRACED);
        print_PPid_Pid_CPid_And_RETVAL(getppid(), getpid(), pid, status); //prints the parent pid, its own pid, and then the child pid, and then the status of the child
    }

    print_USER_SYS_CUSER_and_CSYS(buf); //prints the USER, SYS, CUSER, and at last CSYS

    time(&stop); //Assigns the current seconds to stop
    printf("Stop: %ld\n", stop); //prints the stop

    return 0;
}

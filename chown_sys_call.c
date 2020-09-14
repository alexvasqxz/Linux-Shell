// 
//  chown_sys_call.c
//  
//  This program written in C when run on terminal
//  creates changes the owner id from a specified file
//  using the chown system call
//
//   Created on 8/29/20
//   Copyright © 2020 Gustavo Vasquez. All rights reserved
//
//           ___________________________________
//          |                                   |
//          |              WELCOME              |
//          |              ARE YOU              |
//          |              READY TO             |
//          |            CHANGE SOME            |
//          |              OWNERS?              |
//          |                                   |
//          |          -Gustavo Vasquez         |
//          |                                   |
//          |___________________________________|
//

#include <pwd.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/syscall.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>


/*
////////////////////////////////////////////////////////////////////////////
// main()
// This program changes the owner of a specified file when run from 
// terminal
// This program written in C is executed by the user in terminal in the
// following way:
// gcc chown_sys_call.c -o <Name>
// ./<Name> <name_of_file> <new_owner(user name)>
//
// After is executed the user can confirm the new owner by typing "ls -la"
// where a list of all the files in the directory will displayed along with
// some of their information including their owner
*/
int main(int argc, char *argv[]){
        struct passwd pwd;
        struct passwd *result;
        char *buf;
        size_t bufsize;
        int s;

        bufsize = sysconf(_SC_GETPW_R_SIZE_MAX);
        if (bufsize == -1)          /* Value was indeterminate */
                bufsize = 16384;        /* Should be more than enough */

        buf = malloc(bufsize);
        if (buf == NULL) {
                perror("malloc");
                exit(EXIT_FAILURE);
        }

        s = getpwnam_r(argv[2], &pwd, buf, bufsize, &result);
        if (result == NULL) {
                if (s == 0)
                        printf("Not found\n");
                else {
                        errno = s;
                        perror("getpwnam_r");
                }
                exit(EXIT_FAILURE);
        }

        long userid = pwd.pw_uid;
        
        // chown system call takes as parameters:
        // the name of the file
        // the userid of the new owner
        int rc =  chown(argv[1] ,userid, -1);

        if (rc == -1){
                fprintf(stderr, "chmod failed, errno = %d\n", errno);
        }
}


//
// Created by moslab on 10/24/16.
//
#include <jni.h>
#include <sys/prctl.h>
#include <android/log.h>
#include <unistd.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <stdio.h>
#include "syscalls.h"
#include "syscallents_arm.h"
#include <asm/ptrace.h>
#include <stdlib.h>
#include <sys/user.h>
#include "../../../../../../Android/Sdk/ndk-bundle/platforms/android-19/arch-arm/usr/include/sys/user.h"
#include "../../../../../../Android/Sdk/ndk-bundle/platforms/android-19/arch-x86/usr/include/asm/ptrace-abi.h"

#ifdef __amd64__
#define eax rax
#define orig_eax orig_rax
#elif __arm__
#define r0 0
#define r1 1
#define r2 2
#define r3 3
#define r4 4
#define r5 5
#define r7 7
#else
#endif

extern "C"
void Java_com_example_moslab_stubapp_JNIFunctionCaller_myprctl(
        JNIEnv* env,
        jobject /*this*/,
        jstring s){
        int ret = prctl(PR_SET_DUMPABLE,1,0,0,0);
        if(ret < 0) {
            __android_log_print(ANDROID_LOG_DEBUG, "prctl", " call prctl failed\n");
        }
        else {
            __android_log_print(ANDROID_LOG_DEBUG, "prctl", " call prctl successfully\n");
        }

}
extern "C"
void Java_com_example_moslab_stubapp_JNIFunctionCaller_mysleepandexit(JNIEnv* env,
                                                              jobject /*this*/){
    sleep(5);
    exit(1);
}

const char *syscall_name(int scn) {
    struct syscall_entry *ent;
    static char buf[128];
    if (scn <= MAX_SYSCALL_NUM) {
        ent = &syscalls[scn];
        if (ent->name)
            return ent->name;
    }
    snprintf(buf, sizeof buf, "sys_%d", scn);
    return buf;
}

extern "C"
void Java_com_example_moslab_stubapp_JNIFunctionCaller_myfork(
        JNIEnv* env,
        jobject /*this*/){
    pid_t traced_process = getpid();
    pid_t pid = fork();
#if 1
    if(pid == 0) {
        ptrace(PTRACE_ATTACH,traced_process,0,0);
        int stauts;
        FILE* fp = fopen("/storage/sdcard0/ptrace_log.txt","w");
        if(fp == NULL){
            fprintf(fp,"failed to open a file\n");
            __android_log_print(ANDROID_LOG_DEBUG,"CHILD","failed to open a file");
        }else{
            fprintf(fp,"open a file successfully\n");
            __android_log_print(ANDROID_LOG_DEBUG,"CHILD","open file successfully");
        }
        while(1){
            wait(&stauts);
            if(WIFEXITED(stauts)){
                __android_log_print(ANDROID_LOG_DEBUG,"CHILD", "Parent exit");
                break;
            }

#ifdef __arm__
            long val = ptrace(PTRACE_PEEKUSER, traced_process, sizeof(long)*r7);
             __android_log_print(ANDROID_LOG_DEBUG,"CHILD", "defined ARM7: %lu ==> %s\n",val,syscall_name(val));



            //fprintf(fp,"defined ARM: %lu ==> %s\n",val,syscall_name(val));
#else
            //long val = ptrace(PTRACE_PEEKUSER, pid, ORIG_EAX);
            __android_log_print(ANDROID_LOG_DEBUG,"Parent", "undefined ARM");
#endif
            // __android_log_print(ANDROID_LOG_DEBUG,"Parent", "Child issue a system call");
            //ptrace(PTRACE_SYSCALL,pid,NULL,NULL);
            //sleep(1);
            ptrace(PTRACE_SYSCALL,traced_process,NULL,NULL);
        }
        fclose(fp);
        __android_log_print(ANDROID_LOG_DEBUG,"CHILD","exit");
        exit(1);
    }else if(pid > 0){
        __android_log_print(ANDROID_LOG_DEBUG, "fork", "Parent: call fork successfully1\n");
    }else {
        __android_log_print(ANDROID_LOG_DEBUG, "fork", "Parent: call fork failed\n");
    }
#else

    if(pid == 0) {
        ptrace(PTRACE_TRACEME,0,NULL,NULL);
        __android_log_print(ANDROID_LOG_DEBUG, "fork", "Child: call fork successfully\n");
      execl("/system/bin/ls","ls",NULL);
     //   sleep(10);

    }else if(pid > 0){
        int stauts;
        int num;
        while(1){
            wait(&stauts);
            if(WIFEXITED(stauts)){
                __android_log_print(ANDROID_LOG_DEBUG,"Parent", "Child exit");
                break;
            }
#ifdef __arm__
            long val = ptrace(PTRACE_PEEKUSER, pid, sizeof(long)*r7);
             __android_log_print(ANDROID_LOG_DEBUG,"Parent", "defined ARM: %lu",val);
            const char *buf = syscall_name(val);
            __android_log_print(ANDROID_LOG_DEBUG,"Parent","hello world %s(", buf);
#else
            //long val = ptrace(PTRACE_PEEKUSER, pid, ORIG_EAX);
            __android_log_print(ANDROID_LOG_DEBUG,"Parent", "undefined ARM");
#endif
           // __android_log_print(ANDROID_LOG_DEBUG,"Parent", "Child issue a system call");
            ptrace(PTRACE_SYSCALL,pid,NULL,NULL);
        }

//        int ret = prctl(PR_SET_PTRACER,pid,0,0,0,0);
//        if (ret != 0){
//            __android_log_print(ANDROID_LOG_DEBUG, "prctl", "PR_SET_PTRACER set successfully\n");
//        }
 //       __android_log_print(ANDROID_LOG_DEBUG, "fork", "Parent: call fork gdsgfsf successfully1\n");
    }else{
        __android_log_print(ANDROID_LOG_DEBUG, "fork", "Parent: call fork failed\n");
    }
#endif
    __android_log_print(ANDROID_LOG_DEBUG, "systemcallJNI", "return to Java\n");
}


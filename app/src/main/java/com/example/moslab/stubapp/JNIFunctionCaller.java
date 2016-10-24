package com.example.moslab.stubapp;

/**
 * Created by moslab on 10/24/16.
 */

public class JNIFunctionCaller {
    public JNIFunctionCaller(){

    }

    public void callprctl(String s){
        myprctl(s);
    }

    public void callfork(){
        myfork();
    }
    public void callSleppAndExit(){
        mysleepandexit();
    }

    public native void myprctl(String s);
    public native void myfork();
    public native void mysleepandexit();

    static {
        System.loadLibrary("systemcallJNI");
    }
}

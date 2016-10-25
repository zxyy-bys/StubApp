package com.example.moslab.stubapp;

import android.app.Application;

/**
 * Created by zxyy_bys on 10/24/16.
 */

public class MyApplication extends Application {
    public MyApplication(){
        super();
        new JNIFunctionCaller().callprctl("hello");
        new JNIFunctionCaller().myfork();
        System.out.println("Parent process asfadsf");
    }
}

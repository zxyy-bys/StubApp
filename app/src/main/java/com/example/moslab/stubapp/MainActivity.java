package com.example.moslab.stubapp;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
//        Intent launchIntent = getPackageManager().getLaunchIntentForPackage("com.example.moslab.targetapplication");
//        if (launchIntent != null) {
//            startActivity(launchIntent);//null pointer check in case package name was not found
//        }
        try {
            new JNIFunctionCaller().callprctl("hello");
            new JNIFunctionCaller().myfork();
            System.out.println("Parent process asfadsf");
        }catch(Exception e){
            e.printStackTrace();
        }
    }
}

package com.example.moslab.stubapp;

import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;

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
//            new JNIFunctionCaller().callprctl("hello");
//            new JNIFunctionCaller().myfork();
//            System.out.println("Parent process asfadsf");
            /*
            Context context = createPackageContext("com.example.zxyy_bys.targetapplication",CONTEXT_INCLUDE_CODE | CONTEXT_IGNORE_SECURITY);
            ClassLoader classLoader = context.getClassLoader();
            System.out.println(classLoader.toString());
            Class<?> main = classLoader.loadClass("com.example.zxyy_bys.targetapplication.MainActivity");
            if(main == null){
                System.out.println("can not load Main Activity Class");
            }else {
                System.out.println("load Main Activity Class");
                Intent intent = new Intent(context, main);
                intent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
                context.startActivity(intent);
            }
            */
           // new JNIFunctionCaller().callSleppAndExit();
        }catch(Exception e){
            e.printStackTrace();
        }
    }
    public void stopMonitor(View view){
        new JNIFunctionCaller().callSleppAndExit();
    }
    public void startNewActivity(View view){
        Intent intent = new Intent(this, MyDummyActivity.class);
        this.startActivity(intent);
    }

    public void startApp(View view){
        try {

            Context context = createPackageContext("com.example.zxyy_bys.targetapplication",CONTEXT_INCLUDE_CODE | CONTEXT_IGNORE_SECURITY);
            ClassLoader classLoader = context.getClassLoader();
            System.out.println(classLoader.toString());
            Class<?> main = classLoader.loadClass("com.example.zxyy_bys.targetapplication.MainActivity");
            if(main == null){
                System.out.println("can not load Main Activity Class");
            }else {
                System.out.println("load Main Activity Class");
                Intent intent = new Intent(context, main);
                intent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
                context.startActivity(intent);
            }
        }catch(Exception e){
            e.printStackTrace();
        }
    }
}

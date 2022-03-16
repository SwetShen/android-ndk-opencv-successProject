package com.archerswet.startopencv;

import android.graphics.Bitmap;

/**
 * @description:message
 * @author:archerswet@163.com
 * @date:2022/3/16
 */
public class FaceDetection {

    // Used to load the 'startopencv' library on application startup.
    static {
        System.loadLibrary("startopencv");
    }


    public native void detectSaveInfo(Bitmap bitmap);
}

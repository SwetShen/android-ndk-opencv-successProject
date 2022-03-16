#include <jni.h>
#include <string>
#include <opencv2/opencv.hpp>
#include <android/bitmap.h>
#include <opencv2/imgproc.hpp>

using namespace cv;

extern "C"{

void bitmap2Mat(JNIEnv *env, Mat mat, jobject bitmap);
void mat2Bitmap(JNIEnv *env, Mat mat, jobject bitmap);
}

//bitmap转成Mat
void bitmap2Mat(JNIEnv *env,Mat mat, jobject bitmap) {
    //Mat 里面有个type：CV_8UC4 刚好对上我们bitmap的 ARGB_8888
    //CV_8UC2 刚好对应bitmap中的RGB_565
    //获取bitmap信息
    AndroidBitmapInfo info;
    AndroidBitmap_getInfo(env,bitmap,&info);

    void* pixels;

    //锁定bitmap画布
    AndroidBitmap_lockPixels(env,bitmap,&pixels);

    mat.create(info.height,info.width,CV_8UC4);

    if (info.format == ANDROID_BITMAP_FORMAT_RGBA_8888){
        //对应的mat应该是CV_8UC4
        Mat temp(info.height,info.width,CV_8UC4,pixels);
        //把数据temp赋值到mat
        temp.copyTo(mat);
    }else if(info.format == ANDROID_BITMAP_FORMAT_RGB_565){
        //对应的mat应该是CV_8UC2
        Mat temp(info.height,info.width,CV_8UC2,pixels);
        cvtColor(temp,mat,COLOR_BGR5652BGRA);
    }

    //其他格式

    //解锁bitmap画布
    AndroidBitmap_unlockPixels(env,bitmap);
}


void mat2Bitmap(JNIEnv *env,Mat mat, jobject bitmap) {
    //获取bitmap信息
    AndroidBitmapInfo info;
    AndroidBitmap_getInfo(env,bitmap,&info);

    void* pixels;

    //锁定bitmap画布
    AndroidBitmap_lockPixels(env,bitmap,&pixels);

    mat.create(info.height,info.width,CV_8UC4);

    if (info.format == ANDROID_BITMAP_FORMAT_RGBA_8888){
        //对应的mat应该是CV_8UC4
        Mat temp(info.height,info.width,CV_8UC4,pixels);
        if(mat.type() == CV_8UC4){
            mat.copyTo(temp);
        }else if(mat.type() == CV_8UC2){
            cvtColor(mat,temp,COLOR_BGR5652BGRA);
        }else if(mat.type() == CV_8UC1){
            cvtColor(mat,temp,COLOR_GRAY2BGRA);
        }
    }else if(info.format == ANDROID_BITMAP_FORMAT_RGB_565){
        //对应的mat应该是CV_8UC2
        Mat temp(info.height,info.width,CV_8UC2,pixels);
        if(mat.type() == CV_8UC4){
            cvtColor(mat,temp,COLOR_BGRA2BGR565);
        }else if(mat.type() == CV_8UC2){
            mat.copyTo(temp);
        }else if(mat.type() == CV_8UC1){
            cvtColor(mat,temp,COLOR_GRAY2BGR565);
        }
    }

    //其他格式

    //解锁bitmap画布
    AndroidBitmap_unlockPixels(env,bitmap);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_archerswet_startopencv_FaceDetection_detectSaveInfo(JNIEnv *env, jobject thiz,
                                                             jobject bitmap) {

    Mat mat;
    //Mat 里面有个type：CV_8UC4 刚好对上我们bitmap的 ARGB_8888
    //CV_8UC2 刚好对应bitmap中的RGB_565
    //获取bitmap信息
    AndroidBitmapInfo info;
    AndroidBitmap_getInfo(env,bitmap,&info);

    void* pixels;

    //锁定bitmap画布
    AndroidBitmap_lockPixels(env,bitmap,&pixels);

    mat.create(info.height,info.width,CV_8UC4);

    if (info.format == ANDROID_BITMAP_FORMAT_RGBA_8888){
        //对应的mat应该是CV_8UC4
        Mat temp(info.height,info.width,CV_8UC4,pixels);
        //把数据temp赋值到mat
        temp.copyTo(mat);
    }else if(info.format == ANDROID_BITMAP_FORMAT_RGB_565){
        //对应的mat应该是CV_8UC2
        Mat temp(info.height,info.width,CV_8UC2,pixels);
        cvtColor(temp,mat,COLOR_BGR5652BGRA);
    }
    //解锁bitmap画布
    AndroidBitmap_unlockPixels(env,bitmap);

    //处理灰度图 opencv 处理灰度图
    Mat gray_mat;
    cvtColor(mat,gray_mat,cv::COLOR_BGRA2GRAY);

    //锁定bitmap画布
    AndroidBitmap_lockPixels(env,bitmap,&pixels);

    mat.create(info.height,info.width,CV_8UC4);

    if (info.format == ANDROID_BITMAP_FORMAT_RGBA_8888){
        //对应的mat应该是CV_8UC4
        Mat temp(info.height,info.width,CV_8UC4,pixels);
        if(gray_mat.type() == CV_8UC4){
            gray_mat.copyTo(temp);
        }else if(gray_mat.type() == CV_8UC2){
            cvtColor(gray_mat,temp,COLOR_BGR5652BGRA);
        }else if(gray_mat.type() == CV_8UC1){
            cvtColor(gray_mat,temp,COLOR_GRAY2BGRA);
        }
    }else if(info.format == ANDROID_BITMAP_FORMAT_RGB_565){
        //对应的mat应该是CV_8UC2
        Mat temp(info.height,info.width,CV_8UC2,pixels);
        if(gray_mat.type() == CV_8UC4){
            cvtColor(gray_mat,temp,COLOR_BGRA2BGR565);
        }else if(gray_mat.type() == CV_8UC2){
            gray_mat.copyTo(temp);
        }else if(gray_mat.type() == CV_8UC1){
            cvtColor(gray_mat,temp,COLOR_GRAY2BGR565);
        }
    }

    //其他格式

    //解锁bitmap画布
    AndroidBitmap_unlockPixels(env,bitmap);

}


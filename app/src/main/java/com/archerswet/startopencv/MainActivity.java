package com.archerswet.startopencv;

import androidx.appcompat.app.AppCompatActivity;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;

import com.archerswet.startopencv.databinding.ActivityMainBinding;

public class MainActivity extends AppCompatActivity {

    private ActivityMainBinding binding;
    private ImageView imageView;
    private Button btn_face;
    private FaceDetection faceDetection;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        faceDetection = new FaceDetection();
        imageView = findViewById(R.id.iv);
        btn_face = findViewById(R.id.btn_face);

        btn_face.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Bitmap bitmap = BitmapFactory.decodeResource(getResources(),R.drawable.a);

                faceDetection.detectSaveInfo(bitmap);

                imageView.setImageBitmap(bitmap);
            }
        });
    }

}
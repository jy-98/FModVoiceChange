package com.example.voicechange;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.widget.TextView;

import com.example.voicechange.databinding.ActivityMainBinding;

import org.fmod.FMOD;

public class MainActivity extends AppCompatActivity{

    private static final int MODE_NORMAL = 0;
    private static final int MODE_LUOLI = 1;
    private static final int MODE_DASHU = 2;
    private static final int MODE_JINGSONG = 3;
    private static final int MODE_GAOGUAI = 4;
    private static final int MODE_KONGLING = 5;

    // Used to load the 'voicechange' library on application startup.
    static {
        System.loadLibrary("voicechange");
    }

    private native void voiceChangeNative(int mode,String path);
    private native void  stopPlay();
    private native Boolean  isPlay();

    private ActivityMainBinding binding;
    private String path;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        path = "file:///android_asset/jia.mp3";

        FMOD.init(this);

        binding.btnNormal.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                voiceChangeNative(MODE_NORMAL, path);
            }
        });
        binding.btnLuoli.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                voiceChangeNative(MODE_LUOLI, path);
            }
        });
        binding.btnDashu.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                voiceChangeNative(MODE_DASHU, path);
            }
        });
        binding.btnJingsong.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                voiceChangeNative(MODE_JINGSONG, path);
            }
        });
        binding.btnGaoguai.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                voiceChangeNative(MODE_GAOGUAI, path);
            }
        });

        binding.btnKongling.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                voiceChangeNative(MODE_KONGLING, path);
            }
        });
    }


    @Override
    protected void onDestroy() {
        super.onDestroy();
        FMOD.close();
    }


//
//    @Override
//    public void onClick(View view) {
//        int mode = 0;
//        if (view.getId() == R.id.btn_normal){
//            mode = MODE_NORMAL;
//        }
//        if (view.getId() == R.id.btn_luoli){
//            mode = MODE_LUOLI;
//        }
//        if (view.getId() == R.id.btn_dashu){
//            mode = MODE_DASHU;
//        }
//        if (view.getId() == R.id.btn_jingsong){
//            mode = MODE_JINGSONG;
//        }
//        if (view.getId() == R.id.btn_gaoguai){
//            mode = MODE_GAOGUAI;
//        }
//        if (view.getId() == R.id.btn_kongling){
//            mode = MODE_KONGLING;
//        }
//
//        voiceChangeNative(mode, path);
//    }
}
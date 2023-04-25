#include <unistd.h>
#include "com_example_voicechange_MainActivity.h"

using namespace FMOD;
using namespace std;

#include <android/log.h>

#define TAG "JNI"
//__VA_ARGS__ 代表可变参数
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,TAG,__VA_ARGS__);
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG,__VA_ARGS__);
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,TAG,__VA_ARGS__);

Channel *channel = 0;    //声通道

extern "C" JNIEXPORT void JNICALL Java_com_example_voicechange_MainActivity_voiceChangeNative
        (JNIEnv *env, jobject thiz, jint mode, jstring path) {

    char *content_ = "默认播放完毕";
    System *system = 0;    //音效引擎系统
    Sound *sound = 0;    //声音
    float frequency = 0;    //音速
    DSP *dsp = 0;    //DSP:digital signal precess 数字信号处理
    bool isPlay = true;//等待播放完毕再回收,判断音频是否还在播放

    //创建FMOD系统
    System_Create(&system);
    //FMOD初始化  参数一:支持最大音轨 参数二：系统初始化标记 参数三：驱动额外参数
    system->init(32, FMOD_INIT_NORMAL, 0);
    //创建FMOD声音
    const char *path_ = env->GetStringUTFChars(path, NULL);
    LOGD("%s", path_)
    //FMOD.Sound初始化  参数一:文件路径 参数二：声音初始化标记 参数三：驱动额外参数
    system->createSound(path_, FMOD_DEFAULT, 0, &sound);
    try {

        switch (mode) {
            case com_example_voicechange_MainActivity_MODE_NORMAL:
                content_ = "原生 播放完毕";
                break;
            case com_example_voicechange_MainActivity_MODE_LUOLI:
                //创建DSP类型的Pitch音调调节
                system->createDSPByType(FMOD_DSP_TYPE_PITCHSHIFT, &dsp);
                dsp->setParameterFloat(FMOD_DSP_PITCHSHIFT_PITCH, 2.0f);//设置Pitch音调调节2.0
                channel->addDSP(0, dsp);//把dsp放入到第一个音轨中
                break;
            case com_example_voicechange_MainActivity_MODE_DASHU:
                //创建DSP类型的Pitch音调调节
                system->createDSPByType(FMOD_DSP_TYPE_PITCHSHIFT, &dsp);
                dsp->setParameterFloat(FMOD_DSP_PITCHSHIFT_PITCH, 0.7f);//设置Pitch音调调节0.7
                channel->addDSP(0, dsp);//把dsp放入到第一个音轨中
                break;
            case com_example_voicechange_MainActivity_MODE_JINGSONG:
                //低音
                system->createDSPByType(FMOD_DSP_TYPE_PITCHSHIFT, &dsp);
                dsp->setParameterFloat(FMOD_DSP_PITCHSHIFT_PITCH, 0.7f);//设置Pitch音调调节0.7
                channel->addDSP(0, dsp);//把dsp放入到第一个音轨中
                //颤抖
                system->createDSPByType(FMOD_DSP_TYPE_TREMOLO, &dsp);
                dsp->setParameterFloat(FMOD_DSP_TREMOLO_FREQUENCY, 20);//颤抖
                dsp->setParameterFloat(FMOD_DSP_TREMOLO_SKEW, 0.8f);//歪斜
                channel->addDSP(1, dsp);
                //回声
                system->createDSPByType(FMOD_DSP_TYPE_ECHO, &dsp);
                dsp->setParameterFloat(FMOD_DSP_ECHO_DELAY, 200);//回音延迟
                dsp->setParameterFloat(FMOD_DSP_ECHO_FEEDBACK, 0);
                channel->addDSP(2, dsp);

            case com_example_voicechange_MainActivity_MODE_GAOGUAI:
                //改变音轨播放的频率达到小黄人搞怪的效果
                channel->getFrequency(&frequency);
                frequency = frequency * 2.0;//调整频率
                channel->setFrequency(frequency);
            case com_example_voicechange_MainActivity_MODE_KONGLING:
                //回音
                system->createDSPByType(FMOD_DSP_TYPE_ECHO, &dsp);
                dsp->setParameterFloat(FMOD_DSP_ECHO_DELAY, 200);//回音延迟
                dsp->setParameterFloat(FMOD_DSP_ECHO_FEEDBACK, 0);
                channel->addDSP(0, dsp);
            default:
                break;
        }
        //播放声音 参数一:声音 参数二：分组 参数三：是否暂停 参数四：音轨通道
        system->playSound(sound, 0, false, &channel);
        system->update();
        while (isPlay) {
            //播放完毕后isPlay系统会赋值flase
            channel->isPlaying(&isPlay);
            usleep(1000 * 1000);
        }
    } catch (...) {
        LOGE("%s", "发生异常");
        goto end;
    }



    //回收操作
    end:
    env->ReleaseStringUTFChars(path, path_);
    sound->release();
    system->close();
    system->release();

}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_voicechange_MainActivity_stopPlay(JNIEnv *env, jobject thiz) {
    channel->stop();
}
extern "C"
JNIEXPORT jobject JNICALL
Java_com_example_voicechange_MainActivity_isPlay(JNIEnv *env, jobject thiz) {
    bool isPlaying = true;
    return reinterpret_cast<jobject>(!channel->isPlaying(&isPlaying));
}
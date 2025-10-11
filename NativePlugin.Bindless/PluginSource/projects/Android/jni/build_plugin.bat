echo "Compiling.."

set ANDROID_NDK_ROOT=E:\UnityEditors\2022.3.17f1\Editor\Data\PlaybackEngines\AndroidPlayer\NDK

%ANDROID_NDK_ROOT%/ndk-build.cmd APP_BUILD_SCRIPT=Android.mk NDK_PROJECT_PATH=. NDK_APPLICATION_MK=Application.mk

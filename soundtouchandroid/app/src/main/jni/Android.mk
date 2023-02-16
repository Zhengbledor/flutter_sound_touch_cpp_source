LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_C_INCLUDES += $(LOCAL_PATH)/../cpp/include $(LOCAL_PATH)/../cpp/include/SoundStretch
# *** Remember: Change -O0 into -O2 in add-applications.mk ***

LOCAL_MODULE    := soundtouch
LOCAL_SRC_FILES :=../cpp/native-lib.cpp \
				../cpp/source/SoundTouch/AAFilter.cpp \
				../cpp/source/SoundTouch/FIFOSampleBuffer.cpp \
                ../cpp/source/SoundTouch/FIRFilter.cpp \
                ../cpp/source/SoundTouch/cpu_detect_x86.cpp \
                ../cpp/source/SoundTouch/sse_optimized.cpp \
                ../cpp/source/SoundStretch/WavFile.cpp \
                ../cpp/source/SoundTouch/RateTransposer.cpp \
                ../cpp/source/SoundTouch/SoundTouch.cpp \
                ../cpp/source/SoundTouch/InterpolateCubic.cpp \
                ../cpp/source/SoundTouch/InterpolateLinear.cpp \
                ../cpp/source/SoundTouch/InterpolateShannon.cpp \
                ../cpp/source/SoundTouch/TDStretch.cpp \
                ../cpp/source/SoundTouch/BPMDetect.cpp \
                ../cpp/source/SoundTouch/PeakFinder.cpp

# for native audio
LOCAL_SHARED_LIBRARIES += -lgcc 
# --whole-archive -lgcc 
# for logging
LOCAL_LDLIBS    += -llog
# for native asset manager
#LOCAL_LDLIBS    += -landroid

# Custom Flags: 
# -fvisibility=hidden : don't export all symbols
LOCAL_CFLAGS += -fvisibility=hidden -fdata-sections -ffunction-sections -ffast-math

# OpenMP mode : enable these flags to enable using OpenMP for parallel computation 
#LOCAL_CFLAGS += -fopenmp
#LOCAL_LDFLAGS += -fopenmp


# Use ARM instruction set instead of Thumb for improved calculation performance in ARM CPUs	
LOCAL_ARM_MODE := arm

include $(BUILD_SHARED_LIBRARY)

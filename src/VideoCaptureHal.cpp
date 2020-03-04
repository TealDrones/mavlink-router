/*
 * This file is part of the Dronecode Camera Manager
 *
 * Copyright (C) 2018  Intel Corporation. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <sstream>

#include "VideoCaptureHal.h"
#include "log.h"

#define DEFAULT_WIDTH 3840
#define DEFAULT_HEIGHT 2160
#define DEFAULT_BITRATE 512
#define DEFAULT_FRAMERATE 30
#define DEFAULT_ENCODER CameraParameters::VIDEO_CODING_AVC
#define DEFAULT_FILE_FORMAT CameraParameters::VIDEO_FILE_TS
#define DEFAULT_FILE_PATH "/tmp/"
#define V4L2_DEVICE_PREFIX "/dev/"

int VideoCaptureHal::vidCount = 0;

VideoCaptureHal::VideoCaptureHal(std::shared_ptr<CameraDevice> camDev)
    : mCamDev(camDev)
    , mState(STATE_IDLE)
    , mWidth(0)
    , mHeight(0)
    , mBitRate(0)
    , mFrmRate(0)
    , mEnc(DEFAULT_ENCODER)
    , mFileFmt(DEFAULT_FILE_FORMAT)
    , mFilePath(DEFAULT_FILE_PATH)
{
    log_info("%s Device:%s", __func__, mCamDev->getDeviceId().c_str());
    mURLLastCapture = "";
}

VideoCaptureHal::VideoCaptureHal(std::shared_ptr<CameraDevice> camDev,
                                 struct VideoSettings &vidSetting)
    : mCamDev(camDev)
    , mState(STATE_IDLE)
    , mWidth(vidSetting.width)
    , mHeight(vidSetting.height)
    , mBitRate(vidSetting.bitRate)
    , mFrmRate(vidSetting.frameRate)
    , mEnc(vidSetting.encoder)
    , mFileFmt(vidSetting.fileFormat)
    , mFilePath(DEFAULT_FILE_PATH)

{
    log_info("%s Device:%s with settings", __func__, mCamDev->getDeviceId().c_str());
    mURLLastCapture = "";
}

VideoCaptureHal::~VideoCaptureHal()
{
    if (getState() != STATE_IDLE) {
        stop();
        uninit();
    }
}

int VideoCaptureHal::init()
{
    log_info("%s::%s", typeid(this).name(), __func__);

    if (getState() != STATE_IDLE) {
        log_error("Invalid State : %d", getState());
        return -1;
    }

    setState(STATE_INIT);
    return 0;
}

int VideoCaptureHal::uninit()
{
    log_info("%s::%s", typeid(this).name(), __func__);

    if (getState() != STATE_INIT && getState() != STATE_ERROR) {
        log_debug("Unexpected state : %d", getState());
        return -1;
    }

    setState(STATE_IDLE);
    return 0;
}

int VideoCaptureHal::start()
{
    log_info("%s::%s", typeid(this).name(), __func__);

    if (getState() != STATE_INIT) {
        log_error("Invalid State : %d", getState());
        return -1;
    }

    int ret = 0;
    sendStartRecord();
    setState(STATE_RUN);

    return ret;
}

int VideoCaptureHal::stop()
{
    log_info("%s::%s", typeid(this).name(), __func__);

    if (getState() != STATE_RUN) {
        log_debug("Capture is not in RUN State : %d", getState());
        return -1;
    }

    sendStopRecord();
    setState(STATE_INIT);
    return 0;
}

int VideoCaptureHal::setState(int state)
{
    int ret = 0;
    log_debug("%s : %d", __func__, state);

    if (mState == state)
        return 0;

    if (state == STATE_ERROR) {
        mState = state;
        return 0;
    }

    switch (mState) {
    case STATE_IDLE:
        if (state == STATE_INIT)
            mState = state;
        break;
    case STATE_INIT:
        if (state == STATE_IDLE || state == STATE_RUN)
            mState = state;
        break;
    case STATE_RUN:
        if (state == STATE_INIT)
            mState = state;
        break;
    case STATE_ERROR:
        log_info("In Error State");
        // Free up resources, restart?
        if (state == STATE_IDLE)
            mState = state;
        break;
    default:
        break;
    }

    if (mState != state) {
        ret = -1;
        log_error("InValid State Transition");
    }

    return ret;
}

int VideoCaptureHal::getState()
{
    return mState;
}

std::string VideoCaptureHal::getURLNextCapture()
{
    log_debug("Creating next url for video capture from video stream");
    return mURLLastCapture;
}

int VideoCaptureHal::setResolution(int vidWidth, int vidHeight)
{
    int ret = 0;

    if (getState() == STATE_RUN)
        log_warning("Change will not take effect");

    mWidth = vidWidth;
    mHeight = vidHeight;

    return ret;
}

int VideoCaptureHal::getResolution(int &vidWidth, int &vidHeight)
{
    int ret = 0;

    if (getState() == STATE_RUN)
        log_warning("Change will not take effect");

    vidWidth = mWidth;
    vidHeight = mHeight;

    return ret;
}

int VideoCaptureHal::setBitRate(int bitRate)
{
    int ret = 0;

    if (getState() == STATE_RUN)
        log_warning("Change will not take effect");

    mBitRate = bitRate;

    return ret;
}

int VideoCaptureHal::setFrameRate(int frameRate)
{
    int ret = 0;

    if (getState() == STATE_RUN)
        log_warning("Change will not take effect");

    mFrmRate = frameRate;

    return ret;
}

int VideoCaptureHal::setEncoder(CameraParameters::VIDEO_CODING_FORMAT vidEnc)
{
    int ret = 0;

    if (getState() == STATE_RUN)
        log_warning("Change will not take effect");

    mEnc = vidEnc;

    return ret;
}

int VideoCaptureHal::setFormat(CameraParameters::VIDEO_FILE_FORMAT fileFormat)
{
    int ret = 0;

    if (getState() == STATE_RUN)
        log_warning("Change will not take effect");

    mFileFmt = fileFormat;

    return ret;
}

int VideoCaptureHal::setLocation(const std::string vidPath)
{
    int ret = 0;

    if (getState() == STATE_RUN)
        log_warning("Change will not take effect");

    mFilePath = vidPath;

    return ret;
}

std::string VideoCaptureHal::getLocation()
{
    return mFilePath;
}

void VideoCaptureHal::sendStartRecord(){

}

void VideoCaptureHal::sendStopRecord() {

}
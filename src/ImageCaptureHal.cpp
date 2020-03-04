/*
 * This file is part of the Dronecode Camera Manager
 *
 * Copyright (C) 2017  Intel Corporation. All rights reserved.
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

#include <assert.h>
#include <sstream>
#include <unistd.h>
#include <vector>

#include "CameraParameters.h"
#include "ImageCaptureHal.h"

#include "log.h"

#define DEFAULT_IMAGE_FILE_FORMAT CameraParameters::IMAGE_FILE_JPEG
#define DEFAULT_FILE_PATH "/tmp/"
#define V4L2_DEVICE_PREFIX "/dev/"

int ImageCaptureHal::imgCount = 0;

ImageCaptureHal::ImageCaptureHal(std::shared_ptr<CameraDevice> camDev)
    : mCamDev(camDev)
    , mState(STATE_IDLE)
    , mWidth(0)
    , mHeight(0)
    , mFormat(DEFAULT_IMAGE_FILE_FORMAT)
    , mInterval(0)
    , mPath(DEFAULT_FILE_PATH)
    , mResultCB(nullptr)
{
    log_info("%s Device:%s", __func__, mCamDev->getDeviceId().c_str());

    mCamDev->getSize(mCamWidth, mCamHeight);
    mCamDev->getPixelFormat(mCamPixFormat);
    mURLLastCapture = "";
}

ImageCaptureHal::ImageCaptureHal(std::shared_ptr<CameraDevice> camDev,
                                 struct ImageSettings &imgSetting)
    : mCamDev(camDev)
    , mState(STATE_IDLE)
    , mWidth(imgSetting.width)
    , mHeight(imgSetting.height)
    , mFormat(imgSetting.fileFormat)
    , mInterval(0)
    , mPath(DEFAULT_FILE_PATH)
    , mResultCB(nullptr)
{
    log_info("%s Device:%s with settings", __func__, mCamDev->getDeviceId().c_str());

    mCamDev->getSize(mCamWidth, mCamHeight);
    mCamDev->getPixelFormat(mCamPixFormat);
}

ImageCaptureHal::~ImageCaptureHal()
{
    stop();
}

int ImageCaptureHal::init()
{
    log_info("%s::%s", typeid(this).name(), __func__);

    if (getState() != STATE_IDLE) {
        log_error("Invalid State : %d", getState());
        return -1;
    }

    setState(STATE_INIT);
    return 0;
}

int ImageCaptureHal::uninit()
{
    log_info("%s::%s", typeid(this).name(), __func__);

    if (getState() != STATE_INIT && getState() != STATE_ERROR) {
        log_error("Invalid State : %d", getState());
        return -1;
    }

    setState(STATE_IDLE);
    return 0;
}

int ImageCaptureHal::start(int interval, int count, std::function<void(int result, int seq_num)> cb)
{
    int ret = 0;
    log_info("%s::%s interval:%d count:%d", typeid(this).name(), __func__, interval, count);
    // Invalid Arguments
    // Either the capture is count based or interval based or count with interval
    if (count <= 0 && interval <= 0) {
        log_error("Invalid Parameters");
        return 1;
    }

    // check & set state
    if (getState() != STATE_INIT) {
        log_error("Invalid State : %d", getState());
        return -1;
    }

    mResultCB = cb;
    mInterval = interval;
    setState(STATE_RUN);

    sendImageCapture();

    return 0;
}

int ImageCaptureHal::stop()
{
    log_info("%s::%s", typeid(this).name(), __func__);

    setState(STATE_INIT);

    return 0;
}

int ImageCaptureHal::setState(int state)
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

int ImageCaptureHal::getState()
{
    return mState;
}

int ImageCaptureHal::setResolution(int imgWidth, int imgHeight)
{
    mWidth = imgWidth;
    mHeight = imgHeight;

    return 0;
}

int ImageCaptureHal::setInterval(int interval)
{
    if (interval < 0)
        return -1;

    mInterval = interval;

    return 0;
}

int ImageCaptureHal::getInterval()
{
    return mInterval;
}

int ImageCaptureHal::setFormat(CameraParameters::IMAGE_FILE_FORMAT imgFormat)
{
    if (imgFormat <= CameraParameters::IMAGE_FILE_MIN
        || imgFormat >= CameraParameters::IMAGE_FILE_MAX) {
        log_error("Invalid Pixel format");
        return 1;
    }

    mFormat = imgFormat;

    return 0;
}

int ImageCaptureHal::setLocation(const std::string imgPath)
{
    // TODO::Check if the path is writeable/valid
    log_debug("%s:%s", __func__, imgPath.c_str());
    mPath = imgPath;

    return 0;
}

std::string ImageCaptureHal::getURLLastCapture()
{
	return mURLLastCapture;
}

std::string ImageCaptureHal::getURLNextCapture()
{
    return "here goes a url";
}

void ImageCaptureHal::sendImageCapture(){
    
}

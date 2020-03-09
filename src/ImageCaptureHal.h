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
#pragma once
#include <string>

#include "CameraDevice.h"
#include "ImageCapture.h"

class ImageCaptureHal final : public ImageCapture {
public:
    ImageCaptureHal(std::shared_ptr<CameraDevice> camDev);
    ImageCaptureHal(std::shared_ptr<CameraDevice> camDev, struct ImageSettings &imgSetting);
    ~ImageCaptureHal();

    int init();
    int uninit();
    int start(int interval, int count, std::function<void(int result, int seq_num)> cb);
    int stop();
    int getState();
    int setInterval(int interval);
    int getInterval();
    int setResolution(int imgWidth, int imgHeight);
    int setFormat(CameraParameters::IMAGE_FILE_FORMAT imgFormat);
    int setLocation(const std::string imgPath);
    std::shared_ptr<CameraDevice> mCamDev;
    std::string getURLLastCapture();
    std::string getURLNextCapture();

private:
    void sendImageCapture();
    static int imgCount;
    int setState(int state);
    std::atomic<int> mState;
    uint32_t mWidth;                             /* Image Width*/
    uint32_t mHeight;                            /* Image Height*/
    CameraParameters::IMAGE_FILE_FORMAT mFormat; /* Image File Format*/
    uint32_t mInterval;                          /* Image Capture interval */
    std::string mPath;                           /* Image File Destination Path*/
    std::string mURLLastCapture;
    uint32_t mCamWidth;                          /* Camera Frame Width*/
    uint32_t mCamHeight;                         /* Camera Frame Height*/
    CameraParameters::PixelFormat mCamPixFormat; /* Camera Frame Pixel Format*/
    std::function<void(int result, int seq_num)> mResultCB;
};

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
#include <map>
#include <string>
#include <vector>

#include "log.h"

#define CAM_PARAM_ID_LEN 16
#define CAM_PARAM_VALUE_LEN 128

class CameraParameters {
public:
    CameraParameters();
    virtual ~CameraParameters();
    const std::map<std::string, std::string> &getParameterList() const { return paramValue; }
    bool setParameterValuesSupported(std::string param, std::string value);
    bool setParameterIdType(std::string param, int paramId, int paramType);
    int getParameterType(std::string param);
    int getParameterID(std::string param);
    bool setParameter(std::string param, std::string value);
    bool setParameter(std::string param_id, float param_value);
    bool setParameter(std::string param_id, uint32_t param_value);
    bool setParameter(std::string param_id, int32_t param_value);
    bool setParameter(std::string param_id, uint8_t param_value);
    std::string getParameter(std::string param);

    typedef struct {
        union {
            float param_float;
            int32_t param_int32;
            uint32_t param_uint32;
            int16_t param_int16;
            uint16_t param_uint16;
            int8_t param_int8;
            uint8_t param_uint8;
            uint8_t bytes[CAM_PARAM_VALUE_LEN];
        };
        uint8_t type;
    } cam_param_union_t;

    enum param_type {
        PARAM_TYPE_UINT8 = 1,
        PARAM_TYPE_INT8,
        PARAM_TYPE_UINT16,
        PARAM_TYPE_INT16,
        PARAM_TYPE_UINT32,
        PARAM_TYPE_INT32,
        PARAM_TYPE_UINT64,
        PARAM_TYPE_INT64,
        PARAM_TYPE_REAL32,
        PARAM_TYPE_REAL64
    };

    enum camera_cap_flags {
        CAMERA_CAP_CAPTURE_VIDEO = 1,
        CAMERA_CAP_CAPTURE_IMAGE = 2,
        CAMERA_CAP_HAS_MODES = 4,
        CAMERA_CAP_CAN_CAPTURE_IMAGE_IN_VIDEO_MODE = 8,
        CAMERA_CAP_CAN_CAPTURE_VIDEO_IN_IMAGE_MODE = 16,
        CAMERA_CAP_HAS_IMAGE_SURVEY_MODE = 32
    };

    // List of the params
    static const char CAMERA_MODE[];
    static const char BRIGHTNESS[];
    static const char CONTRAST[];
    static const char SATURATION[];
    static const char HUE[];
    static const char WHITE_BALANCE_MODE[];
    static const char GAMMA[];
    static const char GAIN[];
    static const char POWER_LINE_FREQ_MODE[];
    static const char WHITE_BALANCE_TEMPERATURE[];
    static const char SHARPNESS[];
    static const char BACKLIGHT_COMPENSATION[];
    static const char EXPOSURE_MODE[];
    static const char EXPOSURE[];
    static const char EXPOSURE_ABSOLUTE[];
    static const char EXPOSURE_AUTO_PRIORITY[];
    static const char IMAGE_SIZE[];
    static const char IMAGE_FORMAT[];
    static const char PIXEL_FORMAT[];
    static const char SCENE_MODE[];
    static const char VIDEO_SIZE[];
    static const char VIDEO_FRAME_FORMAT[];
    static const char IMAGE_CAPTURE[];
    static const char VIDEO_CAPTURE[];
    static const char VIDEO_SNAPSHOT[];
    static const char IMAGE_VIDEOSHOT[];

    // Values for white balance settings.
    static const char WHITE_BALANCE_AUTO[];
    static const char WHITE_BALANCE_INCANDESCENT[];
    static const char WHITE_BALANCE_FLUORESCENT[];
    static const char WHITE_BALANCE_WARM_FLUORESCENT[];
    static const char WHITE_BALANCE_DAYLIGHT[];
    static const char WHITE_BALANCE_CLOUDY_DAYLIGHT[];
    static const char WHITE_BALANCE_TWILIGHT[];
    static const char WHITE_BALANCE_SHADE[];

    // ID for parameters
    static const int PARAM_ID_CAMERA_MODE = 1;
    static const int PARAM_ID_BRIGHTNESS = 2;
    static const int PARAM_ID_CONTRAST = 3;
    static const int PARAM_ID_SATURATION = 4;
    static const int PARAM_ID_HUE = 5;
    static const int PARAM_ID_WHITE_BALANCE_MODE = 6;
    static const int PARAM_ID_GAMMA = 7;
    static const int PARAM_ID_GAIN = 8;
    static const int PARAM_ID_POWER_LINE_FREQ_MODE = 9;
    static const int PARAM_ID_WHITE_BALANCE_TEMPERATURE = 10;
    static const int PARAM_ID_SHARPNESS = 11;
    static const int PARAM_ID_BACKLIGHT_COMPENSATION = 12;
    static const int PARAM_ID_EXPOSURE_MODE = 13;
    static const int PARAM_ID_EXPOSURE_ABSOLUTE = 14;
    static const int PARAM_ID_IMAGE_SIZE = 15;
    static const int PARAM_ID_IMAGE_FORMAT = 16;
    static const int PARAM_ID_PIXEL_FORMAT = 17;
    static const int PARAM_ID_SCENE_MODE = 18;
    static const int PARAM_ID_VIDEO_SIZE = 19;
    static const int PARAM_ID_VIDEO_FRAME_FORMAT = 20;
    static const int PARAM_ID_IMAGE_CAPTURE = 21;
    static const int PARAM_ID_VIDEO_CAPTURE = 22;
    static const int PARAM_ID_VIDEO_SNAPSHOT = 23;
    static const int PARAM_ID_IMAGE_VIDEOSHOT = 24;
    static const int PARAM_ID_EXPOSURE_AUTO_PRIORITY = 25;
    static const int PARAM_ID_EXPOSURE = 26;

    // ID for image sizes
    static const int ID_IMAGE_SIZE_3264x2448 = 1;
    static const int ID_IMAGE_SIZE_3264x1836 = 2;
    static const int ID_IMAGE_SIZE_1920x1080 = 3;

    // ID for video sizes
    static const int ID_VIDEO_SIZE_1920x1080x30 = 1;
    static const int ID_VIDEO_SIZE_1920x1080x15 = 2;
    static const int ID_VIDEO_SIZE_1280x720x30 = 3;
    static const int ID_VIDEO_SIZE_1280x720x15 = 4;
    static const int ID_VIDEO_SIZE_960x540x30 = 5;
    static const int ID_VIDEO_SIZE_960x540x15 = 6;
    static const int ID_VIDEO_SIZE_848x480x30 = 7;
    static const int ID_VIDEO_SIZE_848x480x15 = 8;
    static const int ID_VIDEO_SIZE_640x480x60 = 9;
    static const int ID_VIDEO_SIZE_640x480x30 = 10;
    static const int ID_VIDEO_SIZE_640x480x15 = 11;
    static const int ID_VIDEO_SIZE_640x360x30 = 12;
    static const int ID_VIDEO_SIZE_640x360x15 = 13;
    static const int ID_VIDEO_SIZE_424x240x30 = 14;
    static const int ID_VIDEO_SIZE_424x240x15 = 15;
    static const int ID_VIDEO_SIZE_320x240x60 = 16;
    static const int ID_VIDEO_SIZE_320x240x30 = 17;
    static const int ID_VIDEO_SIZE_320x240x15 = 18;
    static const int ID_VIDEO_SIZE_320x180x30 = 19;
    static const int ID_VIDEO_SIZE_320x180x60 = 20;

    // ID for White Balance Modes
    static const int ID_WHITE_BALANCE_MANUAL = 0;
    static const int ID_WHITE_BALANCE_AUTO = 1;
    static const int ID_WHITE_BALANCE_INCANDESCENT = 2;
    static const int ID_WHITE_BALANCE_FLUORESCENT = 3;
    static const int ID_WHITE_BALANCE_WARM_FLUORESCENT = 4;
    static const int ID_WHITE_BALANCE_DAYLIGHT = 5;
    static const int ID_WHITE_BALANCE_CLOUDY_DAYLIGHT = 6;
    static const int ID_WHITE_BALANCE_TWILIGHT = 7;
    static const int ID_WHITE_BALANCE_SHADE = 8;

    // ID for exposure modes
    static const int ID_EXPOSURE_MANUAL = 0;
    static const int ID_EXPOSURE_AUTO = 1;

    /**
     *  Modes of camera device.
     */
    enum Mode { MODE_STILL = 0, MODE_VIDEO = 1, MODE_IMG_SURVEY = 2 };

    /**
     *  Pixel formats of the camera image.
     */
    enum PixelFormat {
        PIXEL_FORMAT_MIN = 0,
        PIXEL_FORMAT_GREY,    /* 8  bpp monochrome images */
        PIXEL_FORMAT_YUV420,  /* 12 bpp YUV 4:2:0 */
        PIXEL_FORMAT_YUV422P, /* 16 bpp YVU422 planar */
        PIXEL_FORMAT_UYVY,    /* 16 bpp YUV 4:2:2 */
        PIXEL_FORMAT_RGB24,   /* 24 bpp RGB 8:8:8 */
        PIXEL_FORMAT_RGB32,   /* 32 bpp RGB 8:8:8:8 */
        PIXEL_FORMAT_MAX = 99
    };

    typedef enum IMAGE_FILE_FORMAT {
        IMAGE_FILE_MIN,
        IMAGE_FILE_RAW,  /* Raw Format */
        IMAGE_FILE_JPEG, /* JPEG Format */
        IMAGE_FILE_EXIF, /* EXIF Format */
        IMAGE_FILE_TIFF, /* TIFF Format */
        IMAGE_FILE_GIF,  /* GIF Format */
        IMAGE_FILE_PNG,  /* PNG Format */
        IMAGE_FILE_BMP,  /* BMP Format */
        IMAGE_FILE_MAX = 99
    } IMAGE_FILE_FORMAT;

    typedef enum VIDEO_FILE_FORMAT {
        VIDEO_FILE_MIN,
        VIDEO_FILE_MP4, /* Moving Pictures Expert Group 4 */
        VIDEO_FILE_AVI, /* Audio Video Interleave */
        VIDEO_FILE_WMV, /* Windows Media Video */
        VIDEO_FILE_FLV, /* Flash Video Format */
        VIDEO_FILE_MOV, /* Apple QuickTime Movie */
        VIDEO_FILE_TS, /* Transport Stream */
        VIDEO_FILE_MAX = 99
    } VIDEO_FILE_FORMAT;

    typedef enum VIDEO_CODING_FORMAT {
        VIDEO_CODING_MIN,
        VIDEO_CODING_H263,  /* H.263 */
        VIDEO_CODING_MPEG4, /* MPEG-4*/
        VIDEO_CODING_AVC,   /* H.264/AVC */
        VIDEO_CODING_MJPEG, /* Motion JPEG */
        VIDEO_CODING_WMV,   /* Windows Media Video */
        VIDEO_CODING_MAX = 99
    } VIDEO_CODING_FORMAT;

    // TODO :: Make exhaustive list of parameters and its possible values
private:
    void initParamIdType();
    std::map<std::string, std::string> paramValue;
    std::map<std::string, std::string> paramValuesSupported;
    std::map<std::string, std::pair<int, int>> paramIdType; /*Key->ID,Type*/
};

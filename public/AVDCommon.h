//
//  AVDCommon.h
//  avd_sdk
//
//  Created by skin on 15-7-21.
//  Copyright (c) 2015年 t3ee. All rights reserved.
//

#ifndef avd_sdk_AVDCommon_h
#define avd_sdk_AVDCommon_h

#import <Foundation/Foundation.h>

typedef NSUInteger      AVDResult;
typedef NSString *      AVDUserId;
typedef NSString *      AVDRoomId;
typedef NSString *      AVDDeviceId;
typedef NSString *      AVDRecordId;
typedef NSString *      AVDLiveId;

extern AVDUserId const OC_AVD_userId_allUser;          /**< AVD定义的虚假用户Id，用于标识房间中所有用户  */
extern AVDUserId const OC_AVD_userId_allUserWithoutMe; /**< AVD定义的虚假用户Id，用于标识房间中除了自己外的所有用户  */

extern AVDResult const AVD_Success;
extern AVDResult const AVD_Failture;
extern AVDResult const AVD_Error_InvalidParam;
extern AVDResult const AVD_Error_NotImplement;
extern AVDResult const AVD_Error_NoNativeobject;


#endif

//
//  AVDLivecast.h
//  avd_sdk
//
//  Created by skin on 15-7-21.
//  Copyright (c) 2015年 t3ee. All rights reserved.
//

#ifndef avd_sdk_AVDLivecast_h
#define avd_sdk_AVDLivecast_h

#import "AVDCommon.h"
#import "AVDUserManager.h"
#import "AVDVideoRenderer.h"
#import "AVDFakeVideoCapturer.h"
#import "AVDFakeAudioCapturer.h"
#import "AVDRoom.h"

/** 客户端直播状态定义 */
enum AVDLivecastStatus {
    lc_init,							/**< 初始状态 */
    lc_connecting,						/**< 正在连接服务器 */
    lc_livecast,						/**< 正在直播  */
    lc_dialogue,						/**< 正在互动连麦  */
    lc_reconnecting,					/**< 正在与服务器重连接  */
};

/**
 * 直播回调接口类
 *
 * 直播回调接口定义了直播对象操作的异步返回，直播状态通知等。
 */
@protocol AVDLivecastDelegate<NSObject>
/// 通知
/** 直播状态更改通知
 *
 * @param[in] status 当前直播状态。
 */
- (void) onLivecastStatus:(enum AVDLivecastStatus)status;

@end


/**
 * 直播接口类
 *
 * 直播接口定义了直播对象创建和释放、直播功能操作。
 */
@interface AVDLivecast : NSObject

@property (nonatomic,weak) id <AVDLivecastDelegate>delegate;    /**< 直播回调代理 */

/** 释放直播房间对象
 *
 *@note 释放房间后，App层不能再使用当前房间指针，所有引用房间指针处均需设置为NULL。
 */
- (void) destory;

/** 获取直播房间状态
 *
 * @return 返回直播房间状态。
 * @sa LivecastStatus
 */
- (enum AVDLivecastStatus) getLiveStatus;
/** 获取房间Id
 *
 * @return 返回房间Id。
 */
- (AVDRoomId) getRoomId;

/** 判断是否连麦状态
 */
- (BOOL) isDialogue;
/** 判断是否主播对象
 */
- (BOOL) isMainBroadcaster;
/** 获取用户管理接口
 * @sa IMUserManager
 */
- (AVDUserManager*) getUserManager;

/** 挂断连麦对话
 * @note 主播和连麦观众都可以挂断对话
 */
- (AVDResult) hangup;

/// 控制接口, switch, mute...
/** 直播切换摄像头
 *
 * @return 返回错误代码。
 */
- (AVDResult) switchCamera;

/** 开启直播（主播）或对讲（观众）前: 设置视频的输入数据源
 *
 * @param[in] *vcapturer 视频的输入数据源。
 * @return 返回错误代码。
 * @sa FakeVideoCapturer
 */
- (AVDResult) setVideoSource:(AVDFakeVideoCapturer*)vcapturer;
/** 开启直播（主播）或对讲（观众）前: 设置音频的输入数据源
 *
 * @param[in] *acapturer 音频的输入数据源。
 * @return 返回错误代码。
 * @sa FakeAudioCapturer
 */
- (AVDResult) setAudioSource:(AVDFakeAudioCapturer*)acapturer;

//
/** 重置房间中网络连接
 *
 * @note 当上层检测到网络切换等情况下，可以调用此接口进行网络连接重置。
 * @return 返回错误代码。
 */
- (AVDResult) reConnect;
/** 设置房间选项
 *
 * @param[in] type 房间选项类型。
 * @param[in] value 选项内容，根据选项说明填入。
 * @return 返回错误代码。
 */
- (AVDResult) setOption:(enum AVDRoomOption)type value:(NSString*)svalue;
/** 获取房间选项
 *
 * @param[in] type 房间选项类型。
 * @return 返回选项内容，根据选项说明解析。
 */
- (NSString*) getOption:(enum AVDRoomOption)type;

#ifndef DOXYGEN_SHOULD_SKIP_THIS
// Disallow init and don't add to documentation
- (id)init __attribute__((
    unavailable("init is not a supported initializer for this class.")));
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

@end

#endif

//
//  AVDMainBroadcaster.h
//  avd_sdk
//
//  Created by skin on 15-7-21.
//  Copyright (c) 2015年 t3ee. All rights reserved.
//

#ifndef avd_sdk_AVDMainBroadcaster_h
#define avd_sdk_AVDMainBroadcaster_h

#import "AVDLivecast.h"

/**
 * 直播主播回调接口类
 *
 * 直播主播回调接口定义了直播对象操作的异步返回，直播状态通知等。
 */
@protocol AVDMainBroadcasterDelegate<NSObject>
/// 异步返回
/** 开启直播操作异步返回
 *
 * @param[in] result 错误代码。
 * @sa publish
 */
- (void) onPublishResult:(AVDResult)result;

@end

/**
 * 直播主播接口类
 *
 * 直播主播接口定义了直播主播对象创建、直播发布和关闭操作。
 */
@interface AVDMainBroadcaster : AVDLivecast

@property (nonatomic,weak) id <AVDMainBroadcasterDelegate>delegate2;    /**< 直播回调代理 */

/** 获取或创建直播主播房间对象
 *
 * @param[in] &roomId 直播房间Id。
 * @return 返回直播主播接口指针。
 */
+ (AVDMainBroadcaster* ) obtain:(AVDRoomId)roomID;

/** 开启直播
 *
 * @param[in] pushUrl 直播rtmp推流地址。
 * @param[in] *preview 本地预览render接口。
 *
 * @return 返回错误代码。
 * @sa onPublishResult
 */
- (AVDResult) publish:(NSString*)pushUrl render:(id<AVDVideoRenderer>)preview;
/** 关闭直播
 *
 * @return 返回错误代码。
 */
- (AVDResult) unpublish;
/** 房间中踢出用户
 *
 * @param[in] reason 踢出用户的理由代码。
 * @param[in] &userId 被踢出用户Id。
 *
 * @note 被踢用户将会在onLivecastStatus中接收到回调状态改变，从连麦状态到观看直播
 * @return 返回错误代码。
 */
- (AVDResult) kickoutUser:(AVDResult)reason userId:(AVDUserId)userId;

#ifndef DOXYGEN_SHOULD_SKIP_THIS
// Disallow init and don't add to documentation
- (id)init __attribute__((
                          unavailable("init is not a supported initializer for this class.")));
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

@end

#endif

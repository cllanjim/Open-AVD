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
/** Overlay自动布局，设置布局参数
 *
 * @param[in] isTopdown Overlay视频在主视频上的排列顺序，true: 从上往下排列； false: 从下往上排列
 * @param[in] scale	   Overlay视频合屏时采用的拉伸方式，参考ScaleType
 * @param[in] w Overlay视频在主视频的宽度比例，取值0.0~1.0，内部取值为：width (主视频）x W
 * @param[in] h Overlay视频在主视频的高度比例，取值0.0~1.0，内部取值为：height(主视频）x H
 * @param[in] x_begin Overlay初始视频在主视频的左上角左边位置，即x坐标，取值0.0~1.0，内部取值为：width (主视频）x x_begin
 * @param[in] y_begin Overlay初始视频在主视频的左上角上边位置，即y坐标，取值0.0~1.0，内部取值为：height(主视频）x y_begin
 * @return 返回错误代码。
 * @note 缺省设置为：Overlay视频从下往上排列; w=h=0.3f; x_begin=0.7f; y_begin=0.7f;
 */
- (AVDResult) setSubVideoParams:(BOOL)isTopdown scale:(enum AVDScalingType)scale w:(float)w h:(float)h x_begin:(float)x_begin y_begin:(float)y_begin;

#ifndef DOXYGEN_SHOULD_SKIP_THIS
// Disallow init and don't add to documentation
- (id)init __attribute__((
                          unavailable("init is not a supported initializer for this class.")));
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

@end

#endif

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

/** 视频混频布局类型 */
enum AVDMixerVideoLayoutType {
    vl_auto_overlay,					/**< 自动布局-窗口中重叠视频 */
    vl_auto_segment,					/**< 自动布局-分割窗口排列视频 */
    vl_manual,							/**< 手动布局  */
};

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

// 布局相关接口（layout all）
/** 获取房间中已发布视频列表
 * @return 返回视频列表。
 * @note 视频列表包含摄像头、虚拟导入视频、屏幕共享视频；
 */
- (NSArray*) getPublishedVideos;
/** 设置直播视频参数
 *
 * @param[in] layout 各子视频在直播视频中的布局类型
 * @param[in] width  直播视频图像宽
 * @param[in] height 直播视频图像高
 * @return 返回错误代码。
 */
- (AVDResult) setLiveVideoTypeaSize:(enum AVDMixerVideoLayoutType)layout width:(NSInteger)width height:(NSInteger)height;
/** 设置直播视频合屏时采用的拉伸方式
 * @param[in] scale	各子视频合屏时采用的拉伸方式，参考ScaleType
 * @return 返回错误代码。
 */
- (AVDResult) setLiveVideoScaleType:(enum AVDScalingType)scale;
/** 设置直播视频背景图片
 * @param[in] &background 直播背景图
 * @return 返回错误代码。
 */
- (AVDResult) setLiveVideoBackgroud:(NSString*)background;
/** 清理掉所有的混屏视频，包括主视频；如果需要再次开启合屏，需要重新设置直播视频和Overlay视频。
 *
 * @return 返回错误代码。
 */
- (void) clearLiveSubVideos;

//自动布局(layout auto)：设置自动布局参数和主视频后，sdk自动来布局子视频组合成直播视频
/** 切换直播视频的主视频（若主视频掉线，本地主播视频切为主视频）
 *
 * @param[in] &deviceId 摄像头Id，唯一标示一路共享的摄像头视频。
 * @return 返回错误代码。
 * @note 直播视频的主视频在vl_auto_overlay模式下可以做切换，缺省为主播视频
 */
- (AVDResult) setLiveMainVideo:(AVDDeviceId)deviceId;
/** 直播视频自动布局的布局参数设置
 *
 * @param[in] isTopdown  各子视频在直播视频上的排列顺序，true: 从上往下（左到右）排列； false: 从下往上（左到右）排列
 * @param[in] w			各子视频相对直播视频的宽度比例，取值0.0~1.0，内部取值为：width (直播视频）x W
 * @param[in] h			各子视频相对直播视频的高度比例，取值0.0~1.0，内部取值为：height(直播视频）x H
 * @param[in] x_begin    初始子视频在直播视频的左上角左边位置，即x坐标，取值0.0~1.0，内部取值为：width (直播视频）x x_begin
 * @param[in] y_begin    初始子视频在直播视频的左上角上边位置，即y坐标，取值0.0~1.0，内部取值为：height(直播视频）x y_begin
 * @return 返回错误代码。
 * @note 缺省设置为：vl_auto_overlay布局类型，从下往上排列; w=h=0.3f; x_begin=0.7f; y_begin=0.7f;
 */
- (AVDResult) autoLayoutParams:(BOOL)isTopdown w:(float)w h:(float)h  x_begin:(float)x_begin y_begin:(float)y_begin;

//手动布局(layout manual)：完全手动布局整个直播视频，可以将一个个子视频排布在直播视频的任意位置
/** 添加视频到直播视频特定位置
 *
 * @param[in] &deviceId 摄像头Id，唯一标示一路共享的摄像头视频。
 * @param[in] zorder 多个视频覆盖时，前后位置，zorder越小，视频越在前面，后面会被覆盖；取值0-n
 * @param[in] x 此视频在直播视频的左上角左边位置，即x坐标，取值0.0~1.0，内部取值为：width (直播视频）x X
 * @param[in] y 此视频在直播视频的左上角上边位置，即y坐标，取值0.0~1.0，内部取值为：height(直播视频）x Y
 * @param[in] w 此视频在直播视频的宽度比例，取值0.0~1.0，内部取值为：width (直播视频）x W
 * @param[in] h 此视频在直播视频的高度比例，取值0.0~1.0，内部取值为：height(直播视频）x H
 * @return 返回错误代码。
 * @sa addMixerOverlayVideo
 */
- (AVDResult) addLiveSubVideo:(AVDDeviceId)deviceId zorder:(NSInteger)zorder x:(float)x y:(float)y w:(float)w h:(float)h;
/** 更新附加视频在直播视频上显示的位置
 *
 * @param[in] &deviceId 摄像头Id，唯一标示一路共享的摄像头视频。
 * @param[in] zorder 多个视频覆盖时，前后位置，zorder越小，视频越在前面，后面会被覆盖；取值0-n
 * @param[in] x 此视频在直播视频的左上角左边位置，即x坐标，取值0.0~1.0，内部取值为：width (直播视频）x X
 * @param[in] y 此视频在直播视频的左上角上边位置，即y坐标，取值0.0~1.0，内部取值为：height(直播视频）x Y
 * @param[in] w 此视频在直播视频的宽度比例，取值0.0~1.0，内部取值为：width (直播视频）x W
 * @param[in] h 此视频在直播视频的高度比例，取值0.0~1.0，内部取值为：height(直播视频）x H
 * @return 返回错误代码。
 */
- (AVDResult) updateLiveSubVideo:(AVDDeviceId)deviceId zorder:(NSInteger)zorder x:(float)x y:(float)y w:(float)w h:(float)h;
/** 移除直播视频上的某一视频
 *
 * @param[in] &deviceId 摄像头Id，唯一标示一路共享的摄像头视频。
 * @return 返回错误代码。
 */
- (void) removeLiveSubVideo:(AVDDeviceId)deviceId;

#ifndef DOXYGEN_SHOULD_SKIP_THIS
// Disallow init and don't add to documentation
- (id)init __attribute__((
                          unavailable("init is not a supported initializer for this class.")));
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

@end

#endif

//
//  AVDRoom.h
//  avd_sdk
//
//  Created by skin on 15-7-21.
//  Copyright (c) 2015年 t3ee. All rights reserved.
//

#ifndef avd_sdk_AVDRoom_h
#define avd_sdk_AVDRoom_h

#import "AVDRoomInfo.h"
#import "AVDUser.h"
#import "AVDUserManager.h"

/** 房间选项
 *
 * @note 房间选项枚举列出了用于设置房间的选项，在以下函数中使用。
 * @sa setOption
 * @sa getOption
 */
enum AVDRoomOption{
    ro_video_drop_data,					/**< 值类型为bool, 字符类型为"true" or "false"：表示接收到视频数据后不解码直接丢弃，一般用于模拟客服端做并发测试。
                                         默认值为false，设置为true后将丢弃该房间所有接收到的视频数据。
                                         */
    ro_audio_drop_data,					/**< 值类型为bool, 字符类型为"true" or "false"：表示接收到音频数据后不解码直接丢弃，一般用于模拟客服端做并发测试。
                                         默认值为false，设置为true后将丢弃该房间所有接收到的音频数据。
                                         */
    ro_media_use_dtls,					/**< 值类型为bool, 字符类型为"true" or "false"：表示音视频是否启用DTLS加密，DTLS加密数据更加安全，但是会加重Server
                                         * 的负担，在UDP丢包严重的网络环境下，媒体链接需要的时间会更多（30%丢包，链接时间10s-40s）。
                                         * 默认值为true，使用的是DTLS加密方式。
                                         */
    ro_room_reconnect_times,			/**< 值类型为int32, 字符类型为"3" or "2"等数字字符：设置每次断线后重连次数。系统默认为重连3次，如需改变需要应用层自己设置。
                                         */
    ro_room_connect_timeout,			/**< 值类型为uint32,  字符类型为"3000" or "5000" ：设置链接超时时间，单位毫秒，必须是正数，系统默认是5000毫秒。
                                         */
    ro_audio_subscribe_mode,			/**< 值类型为string, 音频订阅模式：字符类型为"autosubscribe" or "nosubscribe"：分别表示自动订阅房间中全部打开的音频 comming soon
                                         * or 不自动订阅音频；缺省为"autosubscribe"自动订阅模式。
                                         */
    ro_audio_option_codec,				/**< 值类型为string, 音频编码算法：字符类型为"isac" or "opus"：分别表示isac语音编码 和 opus音乐编码；缺省为"isac"。 comming soon
                                         */
    ro_video_codec_hw_priority,			/**< 值类型为bool, 字符类型为"true" or "false"：表示房间中是否优先使用硬件编码：优先使用硬件编码(true)和优先使用软件编码（false），
                                         缺省为UDP优先。
                                         */
    
    ro_audio_mixerdata_callback_buffered,/**< 值类型为bool, 字符类型为"true" or "false"：表示房间中混音数据回调是否缓冲为1024sample后回调：缓冲(true)和不缓冲（false），
                                          缺省为缓冲。
                                          */
    ro_video_mixerdata_callback_format, /**< 值类型为MediaCodecInfo.CodecCapabilities中的枚举值, 字符类型为枚举值的字符串，目前支持一下："19" - YUV420Planar or "21" - YUV420SemiPlanar：表示房间中合屏数据回调的格式。缺省为 "19"
                                         */
};

@protocol AVDRoomJoinDelegate <NSObject>
- (void)onJoinResult:(AVDResult)aResult;

@end

/**
 * 房间回调接口类
 *
 * 房间回调接口定义了房间对象操作的异步返回，房间通知，房间指示。
 */
@protocol AVDRoomDelegate<NSObject>

@required
/// 指示
/** 指示用户离开房间
 *
 * @param[in] reason 离开房间理由代码，正常离开为AVD_OK。
 * @param[in] fromId 指示发起用户Id。
 *
 */
- (void)onLeaveIndication:(AVDResult)reason fromUser:(AVDUserId)fromId;
/// 通知
/** 房间网络状态通知
 *
 * @param[in] status 当前网络状态。
 *
 */
- (void)onConnectionStatus:(enum AVDConnectionStatus)status;

@optional
/// 异步返回
/** 加入房间操作异步返回
 *
 * @param[in] result 加入错误代码。
 *
 * @sa join
 */
- (void)onJoinResult:(AVDResult)result;

/// 通知
/** 透明通道，接收到广播数据通知
 *
 * @param[in] *data 接收到的数据指针。
 * @param[in] fromId 发送方用户Id。
 *
 * @sa sendPublicData
 */
- (void)onPublicData:(NSData*)data fromUser:(AVDUserId)fromId;

/** 透明通道，接收到私有数据通知
 *
 * @param[in] *data 接收到的数据指针。
 * @param[in] fromId 发送方用户Id。
 *
 * @sa sendPrivateData
 */
- (void)onPrivateData:(NSData*)data fromUser:(AVDUserId)fromId;

/** 房间应用层数据更改通知
 *
 * @param[in] *key 应用层数据关键字。
 * @param[in] *value 应用层数据关键字相关数据内容。
 *
 * @sa updateAppData
 */
- (void)onAppDataNotify:(NSString*)key value:(NSString*)value;

/** 房间状态通知
 *
 * @param[in] status 房间状态。
 *
 */
- (void)onRoomStatusNotify:(enum AVDRoomStatus)status;

@end



/**
* 房间接口类
*
* 房间接口定义了房间对象创建和释放、房间功能操作。
*/
@interface AVDRoom : NSObject

@property (nonatomic,weak) id <AVDRoomDelegate>delegate;        /**< 房间逻辑回调代理 */

@property (nonatomic,strong) AVDUserManager* userManager;       /**< 房间用户管理模块接口 */

/** 获取房间对象
 *
 * @note 房间对象的生命周期由AVD SDK来管理，应用层通过obtain获取一个房间对象，房间最终不使用的时候调用destory来释放。
 * @return 返回房间对象指针。
 */
+ (AVDRoom* ) obtain:(AVDRoomId)roomID;
/** 释放房间对象
 */
- (void) destory;

/** 当前用户加入房间
 *
 * @param[in] *user 用户信息：用户Id，用户名，用户数据等；当应用层必须传入有效的user.UserId，来唯一标识一个用户。
 * @param[in] *password 密码：如果是主持人请用主持人密码；如果是其他参会者，请用房间密码。
 * @param[in] joinresult 加房间回调接口。
 *
 * @return 返回错误代码。
 * @sa User
 */
- (AVDResult) joinWithUser:(AVDUser*)user password:(NSString*)password delegate:(id<AVDRoomJoinDelegate>)joinresult;
- (AVDResult) joinWithUser:(AVDUser*)user password:(NSString*)password delegate:(id<AVDRoomJoinDelegate>)joinresult oemToken:(NSString*)token;

/** 当前用户离开房间
 *
 * @param[in] reason 用户离开房间的原因代码，正常离开为AVD_OK。
 *
 * @note 当前用户离开房间后，当前房间对象和房间的各功能模块都处于离会状态，功能操作无效。
 * @return 返回错误代码。
 */
- (AVDResult) leave:(AVDResult)reason;				// leave myself

/** 重新加入当前房间
 *
 * @note 当用户主动离开房间或者中间网络断线后离开房间后，可以重新调用此函数加入房间。
 * @return 返回错误代码。
 */
- (AVDResult) reJoin;

/** 房间中踢出用户
 *
 * @param[in] reason 踢出用户的理由代码。
 * @param[in] userId 被踢出用户Id。
 *
 * @note 被踢用户将会在onLeaveIndication中接收到回调，被踢用户直接调用 leave 离开房间即可。
 * @return 返回错误代码。
 * @sa onLeaveIndication
 */
- (AVDResult) kickoutUser:(AVDResult)reason userId:(AVDUserId)userId;

/** 更新房间状态
 *
 * @param[in] status 房间状态。
 *
 * @return 返回错误代码。
 * @sa RoomStatus
 */
- (AVDResult) updateRoomStatus:(enum AVDRoomStatus)status;
/** 获取房间状态
 *
 * @return 返回房间状态。
 * @sa RoomStatus
 */
- (enum AVDRoomStatus) getRoomStatus;

/** 获取房间Id
 *
 * @return 返回房间Id。
 */
- (AVDRoomId) getRoomId;

/** 获取房间应用层Id
 *
 * @note 房间应用层Id在应用层安排当前房间的时候由应用层来指定，方便应用层查找、标示房间。
 * @return 返回房间应用层Id。
 */
- (NSString*) getAppRoomId;

/** 获取房间名
 *
 * @return 返回房间名。
 */
- (NSString*) getRoomName;

/** 获取房间主题
 *
 * @return 返回房间主题。
 */
- (NSString*) getRoomTopic;

/** 获取房间信息
 *
 * @return 返回房间信息。
 * @sa RoomInfo
 */
- (AVDRoomInfo*) getRoomInfo;

/** 透明通道，发送广播数据
 *
 * @param[in] *data 发送的数据指针。
 *
 * @note 此透明通道用于承载应用层数据，广播给所有房间内用户。
 * @return 返回错误代码。
 */
- (AVDResult) sendPublicData:(NSData*)data;

/** 透明通道，发送私有数据
 *
 * @param[in] *data 发送的数据指针。
 * @param[in] toId 目的用户Id。
 *
 * @note 此透明通道用于承载应用层数据，发送给房间内某一特定用户。
 * @return 返回错误代码。
 */
- (AVDResult) sendPrivateData:(NSData*)data toUserId:(AVDUserId)toId;

/** 返回应用层的房间数据
 *
 * @param[in] *key 房间数据关键字。
 *
 * @note 应用层的房间数据方便应用层在房间中保留关于房间的一些业务逻辑数据，可以获取和修改应用层的房间数据。
 * @return 返回应用层的相应关键字的房间数据。
 */
- (NSString*) getAppData:(NSString*)key;
/** 修改应用层的房间数据
 *
 * @param[in] *key 房间数据关键字。
 * @param[in] *value 房间数据对应关键字的信息内容
 *
 * @return 返回错误代码。
 */
- (AVDResult) updateAppData:(NSString*)key value:(NSString*)value;
/** 创建模拟设备Id，在导入音视频时可用
 *
 * @param[in] &fakeId 自定义Id。
 * @return 模拟设备Id。
 * @note 模拟摄像头信息，接口会生成deviceId，生成规则："userId_"+（用户输入的fakeId), 此处deviceId不能包含'_'和'{'、'}'此三个字符。
 * @sa previewLocalCamera
 * @sa publishLocalCamera
 */
- (AVDDeviceId) createFakeDeviceID:(AVDDeviceId)fakeId;

//
/** 设置房间选项
 *
 * @param[in] type 房间选项类型。
 * @param[in] svalue 房间选项值。
 *
 * @return 返回错误代码。
 */
- (AVDResult) setOption:(enum AVDRoomOption)type value:(NSString*)svalue;
/** 获取房间选项
 *
 * @param[in] type 房间选项类型。
 *
 * @return 返回房间选项值。
 */
- (NSString*) getOption:(enum AVDRoomOption)type;

#ifndef DOXYGEN_SHOULD_SKIP_THIS
// Disallow init and don't add to documentation
- (id)init __attribute__((
    unavailable("init is not a supported initializer for this class.")));
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

@end

#endif

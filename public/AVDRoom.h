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


@protocol AVDRoomJoinDelegate <NSObject>
- (void)onJoinResult:(AVDResult)aResult;

@end

/**
 * 房间回调接口类
 *
 * 房间回调接口定义了房间对象操作的异步返回，房间通知，房间指示。
 */
@protocol AVDRoomDelegate<NSObject>

/// 异步返回
/** 加入房间操作异步返回
 *
 * @param[in] result 加入错误代码。
 *
 * @sa join
 */
- (void)onJoinResult:(AVDResult)result;

/// 指示
/** 指示用户离开房间
 *
 * @param[in] reason 离开房间理由代码，正常离开为AVD_OK。
 * @param[in] fromId 指示发起用户Id。
 *
 */
- (void)onLeaveIndication:(AVDResult)reason fromUser:(AVDUserId)fromId;

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

/** 房间网络状态通知
 *
 * @param[in] status 当前网络状态。
 *
 */
- (void)onConnectionStatus:(enum AVDConnectionStatus)status;

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


#ifndef DOXYGEN_SHOULD_SKIP_THIS
// Disallow init and don't add to documentation
- (id)init __attribute__((
    unavailable("init is not a supported initializer for this class.")));
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

@end

#endif

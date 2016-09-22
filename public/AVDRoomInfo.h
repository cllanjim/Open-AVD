//
//  AVDRoomInfo.h
//  avd_sdk
//
//  Created by skin on 15-7-21.
//  Copyright (c) 2015年 t3ee. All rights reserved.
//

#ifndef avd_sdk_AVDRoomInfo_h
#define avd_sdk_AVDRoomInfo_h

#import "AVDCommon.h"

/** 房间模式 */
enum AVDRoomMode
{
    clear_set = (1 << 0),                   // use uint32ernal
    mcu = (1 << 31),                        /**< mcu模式  */
    p2p = mcu + clear_set,                  /**< p2p模式  */
    rmfree = (1 << 30),                     /**< 自由发言模式  */
    host = rmfree + clear_set,              /**< 主持人模式  */
    temperary = (1 << 29),                  /**< 临时房间模式  */
    persisist = temperary + clear_set,      /**< 永久房间模式  */
};
/** 房间状态 */
enum AVDRoomStatus
{
    scheduled,                              /**< 已经安排好  */
    opening,                                /**< 正在进行中  */
    locked,                                 /**< 已锁定房间：锁定房间后，新用户无法加入房间  */
    closed,                                 /**< 已关闭房间  */
};

/** 房间网络状态 */
enum AVDConnectionStatus
{
    init,									/**< 初始状态  */
    connecting,								/**< 正在连接服务器  */
    connected,								/**< 已经连接上服务器  */
    connectFailed,							/**< 连接服务器失败  */
};

/**
	* 房间信息结构.
	*
	* 房间信息定义了安排房间时的所有信息。
	*/
@interface AVDRoomInfo : NSObject

@property(nonatomic, strong, readonly) AVDRoomId roomId;        /**< 房间Id */
@property(nonatomic, strong, readonly) NSString* roomName;      /**< 房间名 */
@property(nonatomic, strong, readonly) NSString* appRoomId;     /**< 房间应用层Id */
@property(nonatomic, strong, readonly) NSString* roomTopic;     /**< 房间主题 */
@property(nonatomic, strong, readonly) AVDUserId ownerId;       /**< 房间创建者Id */
@property(nonatomic, strong, readonly) AVDUserId hostId;        /**< 房间主持人Id */
@property(nonatomic, strong, readonly) NSString* hostPassword;  /**< 房间主持人密码 */
@property(nonatomic, strong, readonly) NSString* confPassword;  /**< 房间密码，必须与主持人密码不同 */
@property(nonatomic, readonly) NSUInteger startTime;            /**< 房间起始时间 */
@property(nonatomic, readonly) NSUInteger duration;             /**< 房间延续时间 */
@property(nonatomic, readonly) NSUInteger bandwidth;            /**< 房间带宽限制 */
@property(nonatomic, readonly) NSUInteger maxAttendee;          /**< 房间最大用户数限制 */
@property(nonatomic, readonly) NSUInteger maxAudio;             /**< 房间最大音频数限制 */
@property(nonatomic, readonly) NSUInteger maxVideo;             /**< 房间最大视频数限制 */
@property(nonatomic, readonly) NSUInteger roomMode;             /**< 房间模式集 */


- (id) initWithRoomId:(AVDRoomId) roomId
             roomName:(NSString*) roomName
             appRoomId:(NSString*) appRoomId
              ownerId:(AVDUserId) ownerId
         hostPassword:(NSString*) hostPassword
          maxAttendee:(NSUInteger) maxAttendee
             maxAudio:(NSUInteger) maxAudio
             maxVideo:(NSUInteger) maxVideo
             roomMode:(enum AVDRoomMode) mode;

- (id) initWithMcuRoomId:(AVDRoomId) roomId
             roomName:(NSString*) roomName
            appRoomId:(NSString*) appRoomId;

- (BOOL) isMcu;
- (BOOL) isFree;
- (BOOL) isTemperary;
- (void) setRoomModeFlag:(enum AVDRoomMode)flag;

#ifndef DOXYGEN_SHOULD_SKIP_THIS
// Disallow init and don't add to documentation
- (id)init __attribute__((
    unavailable("init is not a supported initializer for this class.")));
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

@end

#endif

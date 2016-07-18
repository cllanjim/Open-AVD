//
//  AVDLivecastViewer.h
//  avd_sdk
//
//  Created by skin on 15-7-21.
//  Copyright (c) 2015年 t3ee. All rights reserved.
//

#ifndef avd_sdk_AVDLivecastViewer_h
#define avd_sdk_AVDLivecastViewer_h

#import "AVDLivecast.h"

/**
 * 直播观众接口类
 *
 * 直播观众接口定义了直播观众对象创建、直播观看和连麦操作。
 */
@interface AVDLivecastViewer : AVDLivecast

/** 获取或创建直播观众房间对象
 *
 * @param[in] &roomId 直播房间Id。
 * @return 返回直播主播接口指针。
 */
+ (AVDLivecastViewer* ) obtain:(AVDRoomId)roomID;

/** 设置直播观众房间主播Id
 *
 *@note 获取直播房间对象后需要设置，以便连麦时内部使用
 */
- (AVDResult) setBroadcasterId:(AVDUserId)broadcasterId;
/** 进入直播房间观看
 *
 * @param[in] *render 本地预览render接口。
 *
 * @return 返回错误代码。
 * @sa onWatchResult
 */
- (AVDResult) watchRoom:(NSString*)playUrl render:(id<AVDVideoRenderer>)render;
/** 与主播连麦对话
 *
 * @return 返回错误代码。
 * @sa onDialogueResult
 */
- (AVDResult) dialogue;

#ifndef DOXYGEN_SHOULD_SKIP_THIS
// Disallow init and don't add to documentation
- (id)init __attribute__((
    unavailable("init is not a supported initializer for this class.")));
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

@end

#endif

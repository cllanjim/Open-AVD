//
//  AVDEngine.h
//  avd_sdk
//
//  Created by skin on 15-7-21.
//  Copyright (c) 2015年 t3ee. All rights reserved.
//

#ifndef avd_sdk_AVDEngine_h
#define avd_sdk_AVDEngine_h

#import "AVDCommon.h"
#import "AVDUser.h"

@class AVDRoomInfo;

/** 引擎选项
	*
	* @note 引擎选项枚举列出了用于设置引擎的选项，在以下函数中使用。
	* @sa setOption
	* @sa getOption
	*/
enum AVDEngineOption
{
    camera_mode_frontback, 				/**< 值类型为bool, 字符类型为"true" or "false"：表示摄像头使用模式：前后置摄像头模式(true)和多摄像头模式（false）。
                                         多摄像头模式：本机的所有摄像头将展现在房间中；可以同时预览发布多个摄像头；桌面端本地应用和网页端应用多采用此种方式。
                                         前后置摄像头模式：本机的前后置摄像头将作为一个摄像头展现在房间中；同一时刻只能打开一个摄像头；普通移动端采用此种方式。
                                         ios 和 android缺省采用前后摄像头模式， pc端和web缺省采用多摄像头模式。
                                         */
    
    camera_capability_default,			/**< 值类型为CameraCapability, 字符类型为"{\"width\":640,\"height\":480,\"maxFPS\":10}"：表示摄像头缺省采集参数。当前系统默认的采集
                                         参数为：windows桌面版和web网页版{640，480，10}；android/ios移动版{320，240，10}。
                                         */
    
    video_quality_publish_default,		/**< 值类型为QualityType, 字符类型为"low" or "normal" or "high"：表示摄像头发布缺省采用的视频质量，与camera_capability_default的设置相互影响。
                                         当前系统默认的采集参数为：windows桌面版和web网页版 普通质量；android/ios移动版 流畅质量。
                                         */
    
    video_ration_default,				/**< 值类型为VideoRatio, 字符类型为"4_3" or "16_9" or "cif"：表示视频缺省宽高比。
                                         当前系统默认的采集参数为：4:3。
                                         */
    video_quality_subscribe_default,	/**< 值类型为VideoQuality, 字符类型为"low" or "normal" or "high"：表示订阅视频缺省采用的视频质量。
                                         当前系统默认的采集参数为：windows桌面版和web网页版 普通质量；android/ios移动版 流畅质量。
                                         */
    video_publish_svc_default,			/**< 值类型为bool, 字符类型为"true" or "false"：表示视频发布时缺省是否采用多流。
                                         当前系统默认的采集参数为：false。
                                         */
    video_codec_priority,				/**< 值类型为VideoCodec, 字符类型为"h264"，"vp8"，"vp9"：表示视频编码优先采用h264，vp8，vp9编解码。
                                         当前系统默认参数值为：vp8。
                                         */
    demo_urlbase_liverecord,			/**< 值类型为String：表示演示直播和录制的服务器地址，只能获取。
                                         */
    data_channel_tcp_priority,          /**< 值类型为bool, 字符类型为"true" or "false"：表示房间中数据通道用的网络连接类型：TCP优先(true)和UDP优先（false），
                                         缺省为UDP优先。
                                         */
    eo_network_proxy,					/**< 值类型为bool, 字符类型为"true" or "false"：表示启用或不启用，建议局域网或者简单的环境不使用代理。
                                         当前系统默认参数值为：true。
                                         */
    eo_video_resolution_16balign,		/**< 值类型为bool, 字符类型为"true" or "false"：表示启用或不启用视频分辨率16字节严格对齐模式；在16字节对齐模式下，分辨率的宽和高都会向对齐的分辨率靠，
                                         如1080-->1088,540-->544,180-->176等，有些硬件设备（某些android手机）只支持16字节对齐的硬件编解码，android上可以考虑开启此选项来做更好的设备兼容性和编码效率。
                                         当前系统默认参数值为：false。
                                         */
    eo_video_swapwh_by_rotation,		/**< 值类型为bool, 字符类型为"true" or "false"：表示视频publish或preview时设置的分辨率根据输入视频旋转角度变换宽高：变换宽高(true)和不变换宽高严格按设置分辨率裁剪拉伸（false），
                                         * 缺省为不变换宽高严格按设置分辨率裁剪拉伸。
                                         * 未实现。
                                         */
    eo_video_codec_hw_priority,			/**< 值类型为bool, 字符类型为"true" or "false"：表示是否优先使用硬件编码：优先使用硬件编码(true)和优先使用软件编码（false），
                                         * 缺省为硬件编码优先。
                                         * 未实现。
                                         */
   	eo_audio_aec_LowLatencyModeDelayEstimate, /**< android系统可用；值类型为int, 取值：[30, 400]; 字符类型数值字符串如"50"：表示AEC延时下限，用于回音消除。
                                               * 缺省为 80； 回音消除算法与设备的麦克风和扬声器距离，及会场大小都有关系，有可能需要特别调试。
                                               */
    eo_audio_aec_HighLatencyModeDelayEstimate, /**< android系统可用；值类型为int, 取值：[30, 400]; 字符类型数值字符串如"50"：表示AEC延时上限，用于回音消除。
                                                * 缺省为 160； 回音消除算法与设备的麦克风和扬声器距离，及会场大小都有关系，有可能需要特别调试。
                                                */
    
    eo_audio_agc_PlayoutGainMultipleValue, /**< 值类型为float, 取值：[0.1, 10.0]; 字符类型数值字符串如"2.0"：表示语音播放时的增益倍数。
                                            * 缺省为 1.0。
                                            */
    /// for test
    eo_test_rtc_string_1,
    eo_test_rtc_int_1,
};

/**
	* AVD引擎回调接口类
	*
	* AVD引擎回调接口定义了引擎接口操作的异步返回。
	*/
@protocol AVDEngineDelegate<NSObject>

@optional
/// 异步返回
/** 初始化引擎操作异步返回
 *
 * @param[in] result 初始化错误代码。
 * @sa init
 */
- (void) onInitResult:(AVDResult)result;
/** 反初始化引擎操作异步返回
 *
 * @param[in] result 反初始化错误代码。
 * @sa uninit
 */
- (void) onUninitResult:(AVDResult)result;

/** 获取房间信息操作异步返回
 *
 * @param[in] result 获取房间错误代码。
 * @param[in] *room 房间信息。
 *
 * @sa getRoomByRoomId
 * @sa getRoomByAppRoomId
 */
- (void) onGetRoomResult:(AVDResult)result roomInfo:(AVDRoomInfo *)room;
/** 查询房间信息操作异步返回
 *
 * @param[in] result 查询房间错误代码。
 * @param[in] *rooms 房间信息列表。
 *
 * @sa findRoom
 */
- (void) onFindRoomsResult:(AVDResult)result roomInfos:(NSArray*)rooms;
/** 安排房间操作异步返回
 *
 * @param[in] result 安排房间错误代码。
 * @param[in] roomId 房间Id。
 *
 * @sa scheduleRoom
 */
- (void) onScheduleRoomResult:(AVDResult)result roomId:(AVDRoomId)roomId;
/** 取消房间操作异步返回
 *
 * @param[in] result 取消房间错误代码。
 * @param[in] roomId 房间Id。
 *
 * @sa cancelRoom
 */
- (void) onCancelRoomResult:(AVDResult)result roomId:(AVDRoomId)roomId;

@end


/**
	* AVD引擎接口类
	*
	* AVD引擎接口定义了引擎全局初始化操作和房间安排、查询、删除等操作。
	*/
@interface AVDEngine : NSObject

@property(nonatomic, retain) NSMutableArray* rooms;
@property(nonatomic, retain) NSMutableArray* lives;

/** 获取AVD引擎对象
 *
 * @note AVD引擎是一个单例对象，一个进程空间只存在一个引擎。
 * @return 返回AVD引擎指针。
 */
+ (AVDEngine*) instance;
/** 释放AVD引擎对象
 */
+ (AVDResult) destory;

/** 初始化引擎
 *
 * @param[in] *severuri 服务器uri。
 * @param[in] *appkey 叁体公司分发给应用公司的应用秘钥。
 * @param[in] *secretkey 叁体公司分发给应用公司的安全秘钥。
 * @param[in] delegate 引擎回调指针。
 * @note AVD引擎在做任何功能操作前，必须先要初始化引擎成功。引擎初始化是一个异步操作，调用此接口后等待回调中函数onInitResult回调，判断是否初始化成功。
 * @return 返回错误代码。
 */
- (AVDResult) initWithServerUrl:(NSString *)severuri
                      accessKey:(NSString *)appkey secretKey:(NSString *)secretkey delegate:(id<AVDEngineDelegate>)delegate;

/** 初始化引擎
 *
 * @param[in] *severuri 服务器uri。
 * @param[in] *token 根据叁体公司提供的算法计算出来的token。
 * @param[in] delegate 引擎回调指针。
 * @return 返回错误代码。
 */
- (AVDResult) initWithServerUrl:(NSString *)severuri
                      token:(NSString *)token delegate:(id<AVDEngineDelegate>)delegate;

/** 初始化引擎
 *
 * @param[in] *listener 引擎回调指针。
 * @param[in] &severuri 服务器uri。
 * @param[in] &oemName 叁体公司Open-AVD产品OEM的厂家名称。
 * @note AVD引擎在做任何功能操作前，必须先要初始化引擎成功。引擎初始化是一个异步操作，调用此接口后等待回调中函数onInitResult回调，判断是否初始化成功。
 * @return 返回错误代码。
 */
- (AVDResult) initWithServerUrl:(NSString *)severuri
                          OEM:(NSString *)oemName delegate:(id<AVDEngineDelegate>)delegate;

/** 反初始化引擎
 *
 * @note AVD反初始化后，引擎中涉及的所有房间对象都无效，引擎上的功能函数都无法正常使用。
 * @return 返回错误代码。
 */
- (AVDResult) uninit;

/** 判断引擎是否正常工作
 *
 * @return 返回引擎是否正常工作。
 */
- (BOOL) isWorking;

//
/** 根据房间Id获取房间信息
 *
 * @param[in] roomId 房间Id。
 *
 * @note 获取房间信息为异步操作，调用此接口后等待回调中函数onGetRoomResult回调，判断是否获取成功。
 * @return 返回错误代码。
 */
- (AVDResult) getRoomByRoomId:(AVDRoomId)roomId;
/** 根据应用层房间Id获取房间信息
 *
 * @param[in] appRoomId 应用层房间Id。
 *
 * @note 获取房间信息为异步操作，调用此接口后等待回调中函数onGetRoomResult回调，判断是否获取成功。
 * @return 返回错误代码。
 */
- (AVDResult) getRoomByAppRoomId:(NSString*)appRoomId;
/** 查找房间信息
 *
 * @param[in] *filter 查找条件：json字符串，用房间信息结构中的字段“fieldname=value,...”来表示。
 *
 * @note 查找房间信息为异步操作，调用此接口后等待回调中函数onFindRoomsResult回调，判断是否查找成功。
 * @return 返回错误代码。
 */
- (AVDResult) findRooms:(NSString*)filter;
/** 安排房间
 *
 * @param[in] *roomInfo 房间信息。
 *
 * @note 安排房间为异步操作，调用此接口后等待回调中函数onScheduleRoomResult回调，判断是否安排成功。
 * @return 返回错误代码。
 */
- (AVDResult) scheduleRoom:(AVDRoomInfo*)roomInfo;
/** 取消删除房间
 *
 * @param[in] roomId 房间Id。
 *
 * @note 取消房间为异步操作，调用此接口后等待回调中函数onCancelRoomResult回调，判断是否取消成功。
 * @return 返回错误代码。
 */
- (AVDResult) cancelRoom:(AVDRoomId)roomId;

///
/** 设置引擎日志配置
 *
 * @param[in] params 日志参数：日志等级[sensitive verbose info warning error none ]，以上只可取一个值；[debug]是否在调试输出；两个值时中间空格分隔。
 * @param[in] filename 日志文件名，若无日志文件名，则不写文件。
 *
 * @return 返回错误代码。
 */
- (AVDResult) setLogParams:(NSString *)params file:(NSString *)filename;
/** 获取引擎版本号
 *
 * @return 返回引擎版本号。
 */
+ (NSString*) getVersion;
/** 根据错误代码获取关联的错误信息描述
 * @param[in] code 错误代码。
 * @return 返回错误信息描述。
 */
+ (NSString*) getErrorMessage:(AVDResult)code;

/** 设置引擎选项
 *
 * @param[in] type 引擎选项类型。
 * @param[in] *value 引擎选项值指针。
 *
 * @return 返回错误代码。
 */
- (AVDResult) setOption:(enum AVDEngineOption)type value:(NSString*)value;
/** 获取引擎选项
 *
 * @param[in] type 引擎选项类型。
 *
 * @return 返回引擎选项返回值指针。
 */
- (NSString*) getOption:(enum AVDEngineOption)type;

/** 设置全局用户信息
 *
 * @param[in] info 用户信息。
 *
 * @return 返回错误代码。
 * @note 全局用户信息设置后，所有房间或直播房间加入都使用此用户信息
 */
- (AVDResult) setUserInfo:(AVDUser*) info;
/** 获取全局用户信息
 * @return 返回用户信息。
 */
- (AVDUser*) getUserInfo;


#ifndef DOXYGEN_SHOULD_SKIP_THIS
// Disallow init and don't add to documentation
- (id)init __attribute__((
                          unavailable("init is not a supported initializer for this class.")));
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

@end

#endif

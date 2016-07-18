//
//  AVDVideoView.h
//  avd_sdk
//
//  Created by skin on 15-9-19.
//  Copyright (c) 2015年 t3ee. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "AVDVideoRenderer.h"

@interface AVDVideoView  : UIView <AVDVideoRenderer>


@property (nonatomic,weak) id <AVDVideoRendererCallBacks>callback;    /**< 视频数据回调 */

- (instancetype)initForCallbacks:(id<AVDVideoRendererCallBacks>)cb;

@end

//
//  YYSDKManage.h
//  YYEmotionDemo
//
//  Created by Frederic on 16/9/8.
//  Copyright © 2016年 17YouYun. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "WChatSDK.h"

@class ChatMessage;

@interface YYSDKManage : NSObject<WChatSDKDelegate>

@property (nonatomic, strong) void (^RecevieMessage)(ChatMessage *msg);

+ (instancetype)sharedInstance;

- (void)loginChatSDKCompletion:(void (^)(NSDictionary *userInfo, NSError *error))handler;

- (void)sendChatMessage:(ChatMessage *)message targetID:(NSString *)targetID;

@end

//
//  YYSDKManage.m
//  YYEmotionDemo
//
//  Created by Frederic on 16/9/8.
//  Copyright © 2016年 17YouYun. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "YYSDKManage.h"

#import "SAMKeychain.h"
#import "ChatMessage.h"


NSInteger const kPlatform = 1;

NSString * const CLIENT_ID = kPlatform ? @"1-20521-1b766ad17389c94e1dc1f2615714212a-ios" : @"1-20140-201c24b1df50a4e3a8348274963ab0a6-ios";
NSString * const SECRET    = kPlatform ? @"d5cf0a5812b4424f582ded05937e4387" : @"9d12b16f31926616582eabcf66a2a6ad";

@interface YYSDKManage ()

@property (nonatomic, strong) WChatSDK *sharedWChat;

@property (nonatomic, strong) void (^AuthHandler)(NSDictionary *, NSError *);

@end

@implementation YYSDKManage

+ (instancetype)sharedInstance {
    static YYSDKManage *sharedSDK = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        sharedSDK = [[YYSDKManage alloc]init];
    });
    return sharedSDK;
}

- (instancetype)init {
    if (self = [super init]) {
        _sharedWChat = [WChatSDK sharedInstance];
    }
    return self;
}

- (NSString *)getUniqueDeviceIdentifierAsString {
    
    NSString *bundleID = [[[NSBundle mainBundle] infoDictionary] objectForKey:(NSString*)kCFBundleIdentifierKey];
    NSString *strApplicationUUID = [SAMKeychain passwordForService:bundleID account:bundleID];
    if (strApplicationUUID == nil) {
        strApplicationUUID  = [[[[UIDevice currentDevice] identifierForVendor] UUIDString] stringByReplacingOccurrencesOfString:@"-" withString:@""];
        [SAMKeychain setPassword:strApplicationUUID forService:bundleID account:bundleID];
    }
    
    return strApplicationUUID;
}

- (void)loginChatSDKCompletion:(void (^)(NSDictionary *userInfo, NSError *error))handler {
    if (_sharedWChat.isRunning) {
        return;
    }
    NSString *udid = [self getUniqueDeviceIdentifierAsString];
    _AuthHandler = handler;
    if (kPlatform) {
        [_sharedWChat registerApp:udid clientId:CLIENT_ID secret:SECRET delegate:self];
    } else {
        [_sharedWChat testRegisterApp:udid clientId:CLIENT_ID secret:SECRET delegate:self];
    }
}

- (void)sendChatMessage:(ChatMessage *)message targetID:(NSString *)targetID {
    NSError *error;
    YYWChatFileType fileType = YYWChatFileTypeText;
    NSData *contentData;
    if (message.messageType == MMMessageTypeText) {
        // 文本
        if (message.messageContent) {
            contentData = [message.messageContent dataUsingEncoding:NSUTF8StringEncoding];
        }
    } else {
        fileType = YYWChatFileTypeEmotion;
        if (message.messageExtraInfo) {
            contentData = [NSJSONSerialization dataWithJSONObject:message.messageExtraInfo options:NSJSONWritingPrettyPrinted error:nil];
        }
    }
    if (!contentData) {
        return;
    }
    [_sharedWChat wchatSendMsg:targetID body:contentData extBody:nil withTag:100 withType:fileType targetType:WChatMsgTargetTypeSingle withTimeout:20.0 error:&error];
}

#pragma mark - WChatSDKDelegate
- (void)onwchatAuth:(WChatSDK *)instance userinfo:(NSDictionary *)userinfo withError:(NSError *)error {
    dispatch_async(dispatch_get_main_queue(), ^{
        if (_AuthHandler) {
            _AuthHandler(userinfo, error);
        }
    });
}

- (void)onRecvMsg:(WChatSDK *)instance withMessageId:(NSString *)messageId fromUid:(NSString *)fromUid toUid:(NSString *)toUid filetype:(YYWChatFileType)type time:(NSInteger)timevalue content:(NSData *)content extBody:(NSData *)extContent withError:(NSError *)error {
    ChatMessage *chatMsg;
    if (type == YYWChatFileTypeText) {
        if (content.length > 0) {
            NSString *string = [[NSString alloc]initWithData:content encoding:NSUTF8StringEncoding];
            chatMsg = [[ChatMessage alloc]initWithMessageType:MMMessageTypeText messageContent:string messageExtraInfo:nil];
            chatMsg.messageCategary = MMMessageCategaryReceive;
        }
    } else if (type == YYWChatFileTypeEmotion) {
        if (content.length > 0) {
            NSDictionary *extDic = [NSJSONSerialization JSONObjectWithData:content options:NSJSONReadingMutableLeaves | NSJSONReadingMutableContainers error:nil];
            chatMsg = [[ChatMessage alloc]initWithMessageType:MMMessageTypeBigEmoji messageContent:nil messageExtraInfo:extDic];
            chatMsg.messageCategary = MMMessageCategaryReceive;
        }
    }
    dispatch_async(dispatch_get_main_queue(), ^{
        if (_RecevieMessage) {
            _RecevieMessage(chatMsg);
        }
    });
}

@end

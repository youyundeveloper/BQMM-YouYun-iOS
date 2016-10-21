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
#import <BQMM/BQMM.h>


NSInteger const kPlatform = 1;

NSString * const CLIENT_ID = kPlatform ? @"1-20533-ce8d0aeae862ec82700ff3e91efccc06-ios" : @"1-20150-432c2fbc9edef1b0e2b9935edb579886-ios";
NSString * const SECRET    = kPlatform ? @"c8f3a20d5139222958f568a7f2101e51" : @"14b5d9fb6ac45d5f4c40e46e6bb49a35";

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
    // 开启表情云服务
    [WChatSDK startEmotionFunction];
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

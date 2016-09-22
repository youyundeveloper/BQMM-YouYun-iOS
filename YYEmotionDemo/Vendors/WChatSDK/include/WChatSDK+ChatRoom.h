//
//  WChatSDK+ChatRoom.h
//  ChatPlusSDK
//
//  Created by Frederic on 16/6/23.
//  Copyright © 2016年 YouYun. All rights reserved.
//

#import "WChatSDK.h"


/**
 *  聊天室内成员角色
 */
typedef NS_ENUM(NSInteger, WChatRoomRoleType) {
    /**
     *  默认
     */
    WChatRoomRoleTypeDefault    = 1,
    /**
     *  普通成员
     */
    WChatRoomRoleTypeCommon     = 2,
    /**
     *  管理员
     */
    WChatRoomRoleTypeAdmin      = 3,
    /**
     *  群主
     */
    WChatRoomRoleTypeHost       = 4,
};

@interface WChatSDK (ChatRoom)

#pragma mark - 聊天室 - 管理相关接口

/**
 *  创建聊天室群租
 *
 *  @param name    聊天室、群组名称
 *  @param cat     群组类别
 *  @param handler 回调结果
 */
- (void)chatRoomCreateName:(NSString *)name
                  categary:(WChatGroupCategary)cat
                completion:(void (^)(NSDictionary *response, NSError *err))handler;
/**
 *  删除聊天室房间
 *
 *  @param roomid  聊天室房间ID
 *  @param handler 回调个结果
 */
- (void)chatRoomDelete:(NSString *)roomid
            completion:(void (^)(BOOL success, NSError *err))handler;

/**
 *  进入聊天室房间
 *
 *  @param roomid  聊天室房间ID
 *  @param alias   别名(接入方的用户ID，用来和游云ID做映射) 必填
 *  @param handler 回调block (是否操作成功, 如果错误则返回错误信息)
 */
- (void)chatRoomEnter:(NSString *)roomid
              aliasid:(NSString *)alias
           completion:(void(^)(BOOL isEnter, NSError *err))handler;

/**
 *  退出聊天室房间
 *
 *  @param roomid  聊天室房间ID
 *  @param alias   别名(接入方的用户ID，用来和游云ID做映射) 必填
 *  @param handler 回调block (是否操作成功, 如果错误则返回错误信息)
 */
- (void)chatRoomExit:(NSString *)roomid
             aliasid:(NSString *)alias
          completion:(void(^)(BOOL isExit, NSError *err))handler;

/**
 *  查询聊天室成员列表
 *
 *  @param roomid  聊天室房间ID
 *  @param handler 回调结果
 */
- (void)chatRoomGetMembers:(NSString *)roomid
                completion:(void (^)(NSDictionary *response, NSError *err))handler;

/**
 *  查询某用户是否在聊天室房间内
 *
 *  @param uid     游云成员ID
 *  @param roomid  聊天室房间ID
 *  @param handler 回调结果
 */
- (void)chatRoomCheckUser:(NSString *)uid
                   roomid:(NSString *)roomid
               completion:(void (^)(BOOL success, NSError *err))handler;

/**
 *  禁言/解禁某聊天室内某成员
 *
 *  @param uids      游云成员ID列表
 *  @param roomid    聊天室房间ID
 *  @param isForbid  1：禁言(默认)，0：解禁言
 *  @param time      禁言时间(默认15分钟)单位分钟
 *  @param handler   回调结果
 */
- (void)chatRoomForbidUser:(NSArray *)uids
                    roomid:(NSString *)roomid
                    forbid:(int)isForbid
                forbidTime:(NSInteger)time
                completion:(void (^)(BOOL success, NSError *err))handler;

/**
 *  聊天室聊天历史消息
 *
 *  @param roomid    群组id
 *  @param timestamp 时间戳(精确到秒,，如果传-1，获取最新消息)
 *  @param size      数据条数(服务器默认一次最多取20)
 *  @param handler   回调block (历史消息数据, 如果错误则返回错误信息)
 */
- (void)chatRoomGetHistory:(NSString *)roomid
                timestamp:(NSInteger)timestamp
                     size:(NSInteger)size
        completionHandler:(void (^)(NSArray *response, NSError *err))handler;

/**
 *  设置成员用户的角色
 *
 *  @param roomid  聊天室ID
 *  @param uid     成员ID
 *  @param type    角色类型
 *  @param handler 回调结果
 */
- (void)chatRoomSetRole:(NSString *)roomid
                    uid:(NSString *)uid
               roleType:(WChatRoomRoleType)type
             completion:(void (^)(BOOL success, NSError *err))handler;

/**
 *  获取当前用户所加入的聊天室列表(Demo使用)
 *
 *  @param handler 回调结果
 */
- (void)chatRoomGetListCompletion:(void (^)(NSDictionary *response, NSError *err))handler;


@end

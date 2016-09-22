//
//  WChatSDK+ServiceRequest.h
//  WChatSDK
//
//  Created by 微米 on 14-4-3.
//
//

#import "WChatSDK.h"

@interface WChatSDK (ServiceRequest)

#pragma mark - 群组 - 管理相关接口

/**
 *  创建临时群组
 *
 *  @param handler 回调block (创建成功的群组id, 如果错误则返回错误信息)
 */
-(void)createGroupWithCompletionHandler:(void(^)(NSString *groupId, NSError* requestError))handler;

/**
 *  创建一个群组
 *
 *  @param name    群名称
 *  @param desc    群简介
 *  @param cate    群类别
 *  @param handler 回调
 */
- (void)groupCreateName:(NSString *)name
            description:(NSString *)desc
               categary:(WChatGroupCategary)cate
             completion:(void (^)(NSDictionary *response, NSError *err))handler;

/**
 *  群组加人
 *
 *  @param groupId 群组id
 *  @param userId  用户id
 *  @param handler 回调block (是否操作成功, 如果错误则返回错误信息)
 */
-(void)group:(NSString *)groupId addUser:(NSArray *)userIds completionHandler:(void (^)(BOOL isAdd, NSError* requestError))handler;

/**
 *  群组踢人
 *
 *  @param groupId 群组id
 *  @param userId  用户id
 *  @param handler 回调block (是否操作成功, 如果错误则返回错误信息)
 */
-(void)group:(NSString *)groupId delUser:(NSArray *)userIds completionHandler:(void (^)(BOOL isDel, NSError* requestError))handler;

/**
 *  退出群组
 *
 *  @param groupId 群组id
 *  @param handler 回调block (是否操作成功, 如果错误则返回错误信息)
 */
-(void)exitGroup:(NSString *)groupId CompletionHandler:(void(^)(BOOL isExit, NSError* requestError))handler;

/**
 *  获取群组成员ID
 *
 *  @param groupId 群组id
 *  @param handler 回调block (群组成员数据, 如果错误则返回错误信息)
 */
-(void)getGroupUsers:(NSString *)groupId completionHandler:(void (^)(NSArray *users, NSError* requestError))handler;

/**
 *  获取当前用户的群组
 *
 *  @param handler 回调block (用户的群组数据, 如果错误则返回错误信息)
 */
-(void)getUserGroupsWithCompletionHandler:(void (^)(NSArray *groups, NSError* requestError))handler;
/**
 *  获取群组内的所有成员
 *
 *  @param gid     群id
 *  @param handler 回调
 */
- (void)groupGetMember:(NSString *)gid completion:(void (^)(NSArray *members, NSError *err))handler;
/**
 *  销毁房间
 *
 *  @param gid     房间ID
 *  @param handler 回调
 */
- (void)groupDelete:(NSString *)gid completion:(void (^)(BOOL sucess, NSError *err))handler;
/**
 *  获取群信息
 *
 *  @param gid     群组ID
 *  @param handler 回调
 */
- (void)groupGetInfo:(NSString *)gid completion:(void (^)(NSDictionary *response, NSError *err))handler;
/**
 *  更新群组信息
 *
 *  @param gid     群ID
 *  @param name    群名称
 *  @param desc    群简介
 *  @param cate    群类别
 *  @param handler 回调
 */
- (void)groupUpdate:(NSString *)gid name:(NSString *)name description:(NSString *)desc categary:(WChatGroupCategary)cate completion:(void (^)(NSDictionary *response, NSError *err))handler;
/**
 *  申请加入群组
 *
 *  @param gid        群组ID
 *  @param extContent 附言
 *  @param handler    回调
 */
- (void)groupApplyJoinin:(NSString *)gid extContent:(NSString *)extContent completion:(void (^)(BOOL success, NSError *err))handler;

#pragma mark - 黑名单相关接口

/**
 *  黑名单添加用户.
 *
 *  @param userId  聊天对方uid(非当前登陆用户)
 *  @param handler 回调block (是否操作成功, 如果错误则返回错误信息)
 */
-(void)blacklistAddUser:(NSString *)userId completionHandler:(void (^)(BOOL isAdd, NSError* requestError))handler;

/**
 *  黑名单删除用户.
 *
 *  @param userId  聊天对方uid(非当前登陆用户)
 *  @param handler 回调block (是否操作成功, 如果错误则返回错误信息)
 */
-(void)blacklistDelUser:(NSString *)userId completionHandler:(void (^)(BOOL isDel, NSError* requestError))handler;

/**
 *  当前用户黑名单
 *
 *  @param handler 回调block (黑名单数据, 如果错误则返回错误信息)
 */
-(void)blacklistWithCompletionHandler:(void (^)(NSArray *blacklist, NSError* requestError))handler;

#pragma mark - 消息相关接口

/**
 *  单聊聊天历史消息.
 *
 *  @param userId    聊天对方uid(非当前登陆用户)
 *  @param timestamp 时间戳(精确到秒)
 *  @param size      数据条数(服务器默认一次最多取20)
 *  @param handler   回调block (历史消息数据, 如果错误则返回错误信息)
 */
-(void)getHistoryByUser:(NSString *)userId timestamp:(NSInteger)timestamp size:(NSInteger)size completionHandler:(void (^)(NSArray *history, NSError* requestError))handler;

/**
 *  群聊聊天历史消息
 *
 *  @param groupId   群组id
 *  @param timestamp 时间戳(精确到秒)
 *  @param size      数据条数(服务器默认一次最多取20)
 *  @param handler   回调block (历史消息数据, 如果错误则返回错误信息)
 */
-(void)getHistoryByGroup:(NSString *)groupId timestamp:(NSInteger)timestamp size:(NSInteger)size completionHandler:(void (^)(NSArray *, NSError *))handler;

#pragma mark - 服务相关接口

/**
 *  当前设备注册推送. 默认全天推送
 *
 *  @param pushToken ios注册的推送token
 *  @param handler   回调block (是否操作成功, 如果错误则返回错误信息)
 */
-(void)deviceRegisterPush:(NSString *)pushToken completionHandler:(void (^)(BOOL isRegister, NSError* requestError))handler;

/**
 *  当前设备注册推送. push时段
 *
 *  @param pushToken ios注册的推送token
 *  @param startTime push时段开始时间(0~24),默认0,  如: 开始时间为9,  结束时间为20, push时段从当天9 点到 当天  20点.
 *  @param endTime   push时段结束时间(0~24),默认24, 如: 开始时间为20, 结束时间为9,  push时段从当天20点到 第二天 9点.
 *  @param handler   回调block (是否操作成功, 如果错误则返回错误信息)
 */
-(void)deviceRegisterPush:(NSString *)pushToken pushStartTime:(NSInteger)startTime endTime:(NSInteger)endTime completionHandler:(void (^)(BOOL isRegister, NSError* requestError))handler;

/**
 *  获取设备信息.
 *
 *  @param handler 回调block (设备信息注册信息, 如果错误则返回错误信息)
 */
-(void)deviceInfoWithCompletionHandler:(void (^)(NSDictionary *deviceInfo, NSError* requestError))handler;

@end

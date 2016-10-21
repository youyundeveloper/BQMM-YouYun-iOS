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
- (void)createGroupWithCompletionHandler:(void(^)(NSString *groupId, NSError* requestError))handler;

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
- (void)group:(NSString *)groupId addUser:(NSArray *)userIds completionHandler:(void (^)(BOOL isAdd, NSError* requestError))handler;

/**
 *  群组踢人
 *
 *  @param groupId 群组id
 *  @param userId  用户id
 *  @param handler 回调block (是否操作成功, 如果错误则返回错误信息)
 */
- (void)group:(NSString *)groupId delUser:(NSArray *)userIds completionHandler:(void (^)(BOOL isDel, NSError* requestError))handler;

/**
 *  退出群组
 *
 *  @param groupId 群组id
 *  @param handler 回调block (是否操作成功, 如果错误则返回错误信息)
 */
- (void)exitGroup:(NSString *)groupId CompletionHandler:(void(^)(BOOL isExit, NSError* requestError))handler;

/**
 *  获取群组成员ID
 *
 *  @param groupId 群组id
 *  @param handler 回调block (群组成员数据, 如果错误则返回错误信息)
 */
- (void)getGroupUsers:(NSString *)groupId completionHandler:(void (^)(NSArray *users, NSError* requestError))handler;

/**
 *  获取当前用户的群组
 *
 *  @param handler 回调block (用户的群组数据, 如果错误则返回错误信息)
 */
- (void)getUserGroupsWithCompletionHandler:(void (^)(NSArray *groups, NSError* requestError))handler;
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

/**
 通过群组ID搜索群组信息

 @param gid      群组ID
 @param showType 搜索结果的类型
 @param handler  结果、错误回调

 @return 操作是否正确执行
 */
- (BOOL)groupSearchID:(NSString *)gid showType:(YYGroupShowType)showType completion:(void (^)(NSDictionary *groupInfo, NSError *err))handler;

/**
 * 更新群设置信息
 *
 * @param gid   群组ID
 * @param needsApply    新成员加入审核:yes 需要审核，no 不需要
 * @param approveMode   成员加入审核方式
 * @param inviteMode    邀请权限：1 成员可邀请，2 vip之上成员可邀请，3 管理员之上成员可邀请，4 创建者可邀请
 * @param chatMode      发言权限：1 成员可发言，2 vip之上成员可发言，3 管理员之上成员可发言，4 创建者可发言
 * @param members       成员可见性：0 所有人可见，1 成员可见，2 vip之上成员可见，3 管理员之上成员可见，4 创建者可见
 * @param info          群资料可见性：0 所有人可见，1 成员可见，2 vip之上成员可见，3 管理员之上成员可见，4 创建者可见
 * @param authed        群是否认证通过:yes 通过，no 不通过
 * @param updateRole    资料编辑权限：3 管理员，4 创建者.权限大于设置就可以进行对应的操作
 * @param setRole       可以设置禁言的权限,3 管理员，4 创建者.权限大于设置就可以进行对应的操作
 *
 **/
- (void)group:(NSString *)gid updateSettingsApply:(BOOL)needsApplay approveMode:(YYGroupApproveType)approveMode inviteMode:(YYGroupUserRoleType)inviteMode chatMode:(YYGroupUserRoleType)chatMode memberMode:(YYGroupUserRoleType)memberMode info:(YYGroupUserRoleType)info authed:(BOOL)authed updateRole:(YYGroupUserRoleType)updateRole setRole:(YYGroupUserRoleType)setRole completion:(void (^)(NSDictionary *result, NSError *err))handler;

/**
 设置群成员的角色

 @param gid     群组ID
 @param role    要设置的角色枚举类型
 @param uid     群成员ID
 @param handler 回调
 */
- (void)group:(NSString *)gid setRole:(YYGroupUserRoleType)role destinotionUid:(NSString *)uid conpletion:(void (^)(BOOL success, NSError * err))handler;

/**
 禁言／解除禁言群组内的一个或多个成员

 @param gid     群组ID
 @param uids    要禁言／解除禁言的群成员ID
 @param isLimit YES：禁言／NO：解除禁言
 @param time    禁言时间(默认15分钟)
 @param handler 回调
 */
- (void)group:(NSString *)gid limitUids:(NSArray *)uids isLimit:(BOOL)isLimit times:(NSInteger)time completion:(void (^)(NSArray *limitedUid, NSError *err))handler;

/**
 设置群组的扩展信息

 @param gid         群组ID
 @param uid         要设置信息的用户ID
 @param alias   群名称（非必要）
 @param remind      下发消息类型
 @param handler     回调
 */
- (void)group:(NSString *)gid updateUid:(NSString *)uid alias:(NSString *)alias msgRemind:(YYGroupMsgRemindType)remind completion:(void (^)(BOOL success, NSError *err))handler;

/**
 获取群组内被禁言的成员ID

 @param gid     群组ID
 @param handler 回调
 */
- (void)group:(NSString *)gid getLimitsUidsCompletion:(void (^)(NSArray *uids, NSError *err))handler;

#pragma mark - 黑名单相关接口

/**
 *  黑名单添加用户.
 *
 *  @param userId  聊天对方uid(非当前登陆用户)
 *  @param handler 回调block (是否操作成功, 如果错误则返回错误信息)
 */
- (void)blacklistAddUser:(NSString *)userId completionHandler:(void (^)(BOOL isAdd, NSError* requestError))handler;

/**
 *  黑名单删除用户.
 *
 *  @param userId  聊天对方uid(非当前登陆用户)
 *  @param handler 回调block (是否操作成功, 如果错误则返回错误信息)
 */
- (void)blacklistDelUser:(NSString *)userId completionHandler:(void (^)(BOOL isDel, NSError* requestError))handler;

/**
 *  当前用户黑名单
 *
 *  @param handler 回调block (黑名单数据, 如果错误则返回错误信息)
 */
- (void)blacklistWithCompletionHandler:(void (^)(NSArray *blacklist, NSError* requestError))handler;

#pragma mark - 消息相关接口

/**
 *  单聊聊天历史消息.
 *
 *  @param userId    聊天对方uid(非当前登陆用户)
 *  @param timestamp 时间戳(精确到秒)
 *  @param size      数据条数(服务器默认一次最多取20)
 *  @param handler   回调block (历史消息数据, 如果错误则返回错误信息)
 */
- (void)getHistoryByUser:(NSString *)userId timestamp:(NSInteger)timestamp size:(NSInteger)size completionHandler:(void (^)(NSArray *history, NSError* requestError))handler;

/**
 *  群聊聊天历史消息
 *
 *  @param groupId   群组id
 *  @param timestamp 时间戳(精确到秒)
 *  @param size      数据条数(服务器默认一次最多取20)
 *  @param handler   回调block (历史消息数据, 如果错误则返回错误信息)
 */
- (void)getHistoryByGroup:(NSString *)groupId timestamp:(NSInteger)timestamp size:(NSInteger)size completionHandler:(void (^)(NSArray *, NSError *))handler;

#pragma mark - 服务相关接口

/**
 *  当前设备注册推送. 默认全天推送
 *
 *  @param pushToken ios注册的推送token
 *  @param handler   回调block (是否操作成功, 如果错误则返回错误信息)
 */
- (void)deviceRegisterPush:(NSString *)pushToken completionHandler:(void (^)(BOOL isRegister, NSError* requestError))handler;

/**
 *  当前设备注册推送. push时段
 *
 *  @param pushToken ios注册的推送token
 *  @param startTime push时段开始时间(0~24),默认0,  如: 开始时间为9,  结束时间为20, push时段从当天9 点到 当天  20点.
 *  @param endTime   push时段结束时间(0~24),默认24, 如: 开始时间为20, 结束时间为9,  push时段从当天20点到 第二天 9点.
 *  @param handler   回调block (是否操作成功, 如果错误则返回错误信息)
 */
- (void)deviceRegisterPush:(NSString *)pushToken pushStartTime:(NSInteger)startTime endTime:(NSInteger)endTime completionHandler:(void (^)(BOOL isRegister, NSError* requestError))handler;

/**
 *  获取设备信息.
 *
 *  @param handler 回调block (设备信息注册信息, 如果错误则返回错误信息)
 */
- (void)deviceInfoWithCompletionHandler:(void (^)(NSDictionary *deviceInfo, NSError* requestError))handler;

@end

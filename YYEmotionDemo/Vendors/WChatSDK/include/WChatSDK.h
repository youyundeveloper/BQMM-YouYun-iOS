//
//  WChatSDK.h
//  WChatSDK
//
//  Created by 微米 on 13-11-18.
//
//

#import <Foundation/Foundation.h>
#import "WChatCommon.h"

@protocol WChatSDKDelegate;

@interface WChatSDK : NSObject

@property (nonatomic, assign) id<WChatSDKDelegate> delegate;    //delegate
@property (nonatomic, strong) NSString             *userId;     //用户id
@property (nonatomic, assign) BOOL                 isRunning;   //是否登陆成功
@property (nonatomic, readonly) NSString           *cachePath;  //sdk使用的cacahe路径

#pragma mark - 初始化单例

/**
 *  @brief 单例对象
 *
 *  @return WChatSDK instance
 */
+ (instancetype)sharedInstance;

/**
 *  @brief 释放单例
 */
+ (void)purgeSharedInstance;

#pragma mark - 初始化sdk, 注销sdk
/**
 *  @brief 注册设备
 *
 *  @param appUDID        设备唯一UDID
 *  @param clientId       开放平台下发的clientID
 *  @param secret         开放平台下发的sectet
 *  @param clientDelegate 回调代理
 */
- (void)registerApp:(NSString *)appUDID
           clientId:(NSString *)clientId
             secret:(NSString *)secret
           delegate:(id<WChatSDKDelegate>)clientDelegate;

/**
 *  @brief 测试平台, 注册设备
 *
 *  @param appUDID        设备唯一UDID
 *  @param clientId       开放平台下发的clientID
 *  @param secret         开放平台下发的sectet
 *  @param clientDelegate 回调代理
 */
- (void)testRegisterApp:(NSString *)appUDID
               clientId:(NSString *)clientId
                 secret:(NSString *)secret
               delegate:(id<WChatSDKDelegate>)clientDelegate;


/**
 *  @brief 初始化sdk
 *
 *  @param cachePath      缓存目录路径, 通常为Documents
 *  @param platform       使用平台, 目前仅支持 (线上平台 OnlinePlatform , 测试平台 TestPlatform)
 *  @param channel        渠道号
 *  @param clientId       客户端id
 *  @param clientVersion  客户端版本号, 如 1.2.3
 *  @param clientLanguage 客户端语言, 如 CN , 规范见 http://en.wikipedia.org/wiki/ISO_3166-1
 *  @param aDelegate      回调代理
 *  @param errPtr         错误句柄
 *
 *  @return 是否操作成功, YES是, NO否
 */
- (BOOL)init:(NSString *)cachePath
    platform:(WChatPlatform)platform
     channel:(NSString *)channel
    clientId:(NSString *)clientId
     version:(NSString *)clientVersion
    language:(NSString *)clientLanguage
    delegate:(id)aDelegate
       error:(NSError **)errPtr;

/**
 *  @brief 注销sdk
 *
 *  @return 是否操作成功, YES是, NO否
 */
- (BOOL)unInitwchat;

#pragma mark - 前后台切换, 关闭连接, 重连

/**
 *  @brief 客户端回到前台, 开启服务器消息notice下发, 关闭推送 (进入前台调用)
 *
 *  @param timeout 调用超时时间
 */
- (void)wchatKeepAlive:(NSTimeInterval)timeout;

/**
 *  @brief 客户端退到后台, 关闭服务器消息notice下发, 开启推送 (进入后台调用)
 *
 *  @param timeout 调用超时时间
 */
- (void)wchatPreClose:(NSTimeInterval)timeout;

/**
 *  @brief 关闭连接
 *
 *  @param timeout 调用超时时间
 */
- (void)wchatClose:(NSTimeInterval)timeout;

/**
 *  @brief 重新连接
 */
- (void)wchatReconnect;

#pragma mark - 登陆, 退出, 重置密码, 获取授权码
/**
 *  @brief 登陆 (用户名, 密码)
 *
 *  @param username       用户名
 *  @param password       密码
 *  @param isOnBackRround 是否后台登陆
 *  @param timeout        超时时间
 *  @param errPtr         错误句柄
 *
 *  @return 是否操作成功, YES是, NO否
 */
- (BOOL)wchatLogin:(NSString *)username
          password:(NSString *)password
      onBackGround:(BOOL)isOnBackground
       withTimeout:(NSTimeInterval)timeout
             error:(NSError **)errPtr;

/**
 *  @brief 登陆 (微博token)
 *
 *  @param token          授权token
 *  @param refreshToken   更新token
 *  @param isOnBackRround 是否后台登陆
 *  @param timeout        超时时间
 *  @param errPtr         错误句柄
 *
 *  @return 是否操作成功, YES是, NO否
 */
- (BOOL)wchatLoginWithToken:(NSString *)token
               refreshToken:(NSString *)refreshToken
               onBackGround:(BOOL)isOnBackground
                withTimeout:(NSTimeInterval)timeout
                      error:(NSError **)errPtr;

/**
 *  @brief 登出
 *
 *  @param timeout 调用超时时间
 */
-(void)wchatLogout:(NSTimeInterval)timeout;

/**
 *  @brief 重设密码
 *
 *  @param password 用户密码
 *  @param errPtr   错误句柄
 *
 *  @return 是否操作成功, YES是, NO否
 */
- (BOOL)wchatResetPassword:(NSString *)password
                     error:(NSError **)errPtr;

/**
 *  @brief 获取登陆后的授权码(用于接口调用等)
 *
 *  @return 授权码
 */
- (NSString *)wchatGetMAuth;

#pragma mark - 发送通知消息接口
/**
 *  @brief 发送通知消息
 *
 *  @param tuid    收消息人Uid
 *  @param type    通知类型
 *  @param content 通知内容
 *  @param errPtr  错误句柄
 *
 *  @return 消息是否正常发送, YES是, NO否
 */
- (BOOL)wchatSendNoticeMessage:(NSString *)tuid
                      withType:(NSInteger)type
                   withContent:(NSString *)content
                         error:(NSError **)errPtr;

#pragma mark - 发送文本(自定义)消息接口
/**
 *  @brief 发送文本消息
 *
 *  @param toid       收消息人、群组、聊天室id
 *  @param content    消息内容
 *  @param extContent 扩展消息内容
 *  @param tag        消息标示, 用于回调
 *  @param type       消息类型 
 *                      YYWChatFileTypeCustom : 自定义消息(服务器不作处理)
 *                      YYWChatFileTypeText : (服务器业务处理(e:敏感词...))
 *  @param target     消息对象类型
 *  @param timeout    调用超时时间
 *  @param errPtr     错误句柄
 *
 *  @return 消息是否正常发送, YES是, NO否
 */
- (BOOL)wchatSendMsg:(NSString *)toid
                body:(NSData *)content
             extBody:(NSData *)extContent
             withTag:(NSInteger)tag
            withType:(YYWChatFileType)type
          targetType:(WChatMsgTargetType)target
         withTimeout:(NSTimeInterval)timeout
               error:(NSError **)errPtr;

#pragma mark - 发送语音消息接口

/**
 *  @brief 发送音频消息
 *
 *  @param toid       收消息人、群组、聊天室id
 *  @param spanId     语音唯一标示
 *  @param sequenceNo 语音分片编号, 如 1, 2, 3, ... -1, -1 表示结束
 *  @param content    语音消息内容
 *  @param ext        扩展消息内容
 *  @param tag        消息标示, 用于回调
 *  @param target     消息对象类型
 *  @param timeout    调用超时时间
 *  @param errPtr     错误句柄
 *
 *  @return 消息是否正常发送, YES是, NO否
 */
- (BOOL)wchatSendVoice:(NSString *)toid
                spanId:(NSString *)spanId
            sequenceNo:(NSInteger)sequenceNo
               content:(NSData *)content
                   ext:(NSData *)ext
               withTag:(NSInteger)tag
            targetType:(WChatMsgTargetType)target
           withTimeout:(NSTimeInterval)timeout
                 error:(NSError **)errPtr;

/**
 *  @brief 获取语音唯一标示
 *
 *  @param tuid 收消息人Uid
 *
 *  @return 语音消息唯一标示
 */
- (NSString *)getVoiceSpanId:(NSString *)tuid;

#pragma mark - 发送文件消息接口
/**
 *  获取发送文件的文件ID
 *
 *  @param targetID 对方的ID
 *
 *  @return 文件ID
 */
- (NSString *)getFileIdWithTargetID:(NSString *)targetID;
/**
 *  @brief 发送文件给个人、群组
 *
 *  @param toid       收消息人、群组、聊天室id
 *  @param filepath   文件路径
 *  @param extContent 扩展消息内容
 *  @param tag        消息标示, 用于回调
 *  @param fileType   文件类型
 *  @param target     消息对象类型
 *  @param timeout    调用超时时间
 *  @param errPtr     错误句柄
 *
 *  @return 文件id
 */
- (NSString *)wchatSendFile:(NSString *)toid
                       path:(NSString *)filepath
                    extBody:(NSData *)extContent
                    withTag:(NSInteger)tag
                   filetype:(YYWChatFileType)fileType
                 targetType:(WChatMsgTargetType)target
                withTimeout:(NSTimeInterval)timeout
                      error:(NSError **)errPtr;

/**
 *	@brief 发送文件给个人、群组, 断点续传
 *
 *  @param toid       收消息人、群组、聊天室id
 *  @param fid        文件id
 *  @param filepath   文件路径
 *  @param extContent 扩展消息内容
 *  @param index      文件片数索引
 *  @param tag        消息标示, 用于回调
 *  @param fileType   文件类型
 *  @param target     消息对象类型
 *  @param timeout    调用超时时间
 *  @param errPtr     错误句柄
 *
 *  @return 文件id
 */
- (NSString *)wchatSendFile:(NSString *)toid
                    withFid:(NSString *)fid
                       path:(NSString *)filename
                    extBody:(NSData *)extContent
                  withIndex:(UInt32)index
                    withTag:(NSInteger)tag
                   filetype:(YYWChatFileType)fileType
                 targetType:(WChatMsgTargetType)target
                withTimeout:(NSTimeInterval)timeout
                      error:(NSError **)errPtr;

/**
 *  @brief 发送文件(图片)给个人、群组, 带缩略图
 *
 *  @param toid       收消息人、群组、聊天室id
 *  @param filepath   文件路径
 *  @param nailpath   缩略图路径
 *  @param extContent 扩展消息内容
 *  @param tag        消息标示, 用于回调
 *  @param fileType   文件类型
 *  @param target     消息对象类型
 *  @param timeout    调用超时时间
 *  @param errPtr     错误句柄
 *
 *  @return 文件id
 */
- (NSString *)wchatSendFileWithThumbnail:(NSString *)toid
                                    path:(NSString *)filepath
                                nailpath:(NSString *)nailpath
                                 extBody:(NSData *)extContent
                                 withTag:(NSInteger)tag
                                filetype:(YYWChatFileType)fileType
                              targetType:(WChatMsgTargetType)target
                             withTimeout:(NSTimeInterval)timeout
                                   error:(NSError **)errPtr;
/**
 *	@brief 发送文件给个人、群组, 带缩略图, 断点续传
 *
 *  @param toid       收消息人、群组、聊天室id
 *  @param fid        文件id
 *  @param filepath   文件路径
 *  @param nailpath   缩略图路径
 *  @param extContent 扩展消息内容
 *  @param index      文件片数索引
 *  @param tag        消息标示, 用于回调
 *  @param fileType   文件类型
 *  @param target     消息对象类型
 *  @param timeout    调用超时时间
 *  @param errPtr     错误句柄
 *
 *  @return 文件id
 */
- (NSString *)wchatSendFileWithThumbnail:(NSString *)toid
                                  fileId:(NSString *)fid
                                    path:(NSString *)filename
                                nailpath:(NSString *)nailfile
                                 extBody:(NSData *)extContent
                               withIndex:(UInt32)index
                                 withTag:(NSInteger)tag
                                filetype:(YYWChatFileType)fileType
                              targetType:(WChatMsgTargetType)target
                             withTimeout:(NSTimeInterval)timeout
                                   error:(NSError **)errPtr;


#pragma mark - 消息未读数设置
/**
 *  @brief 设置消息未读数(长链接)
 *
 *  @param number 未读数数量
 *  @param tag    消息标示, 用于回调
 *  @param errPtr 错误句柄
 *
 *  @return 是否发送设置, YES是, NO否
 */
- (BOOL)wchatSetUnreadNumber:(NSInteger)number
                     withTag:(NSInteger)tag
                       error:(NSError **)errPtr;

/**
 *  @brief 设置消息未读数 - number
 *
 *  @param number 减掉的消息未读数(长链接)
 *  @param tag    消息标示, 用于回调
 *  @param errPtr 错误句柄
 *
 *  @return 是否发送设置, YES是, NO否
 */
- (BOOL)wchatMinusUnreadNumber:(NSInteger)number
                       withTag:(NSInteger)tag
                         error:(NSError **)errPtr;
/**
 *  @brief 设置消息的未读数量(短链接)
 *
 *  @param number  用户还剩的消息未读数
 *  @param handler 回调
 */
- (void)wchatSetMsgUnreadNumber:(NSInteger)number
                     completion:(void (^)(BOOL success, NSError *err))handler;
/**
 *  @brief 设置消息减少的未读数量(短链接)
 *
 *  @param number  要减少的未读数
 *  @param handler 回调
 */
- (void)wchatReduceMsgUnreadNumber:(NSInteger)number
                        completion:(void (^)(BOOL success, NSError *err))handler;

#pragma mark - 获取文件
/**
 *  @brief 根据文件id获取文件, 分片获取
 *
 *  @param fid     文件id
 *  @param length  文件长度
 *  @param size    分片长度
 *  @param tag     消息标示, 用于回调
 *  @param index   分片索引
 *  @param timeout 调用超时时间
 *  @param errPtr  错误句柄
 *
 *  @return 是否开始获取, YES是, NO否
 */
- (BOOL)wchatGetFile:(NSString *)fid
          filelength:(UInt64)length
           pieceSize:(UInt32)size
             withTag:(NSInteger)tag
               index:(UInt32)index
         withTimeout:(NSTimeInterval)timeout
               error:(NSError **)errPtr;

/**
 *  @brief 根据文件id获取文件
 *
 *  @param fid     文件id
 *  @param length  文件长度
 *  @param tag     消息标示, 用于回调
 *  @param timeout 调用超时时间
 *  @param errPtr  错误句柄
 *
 *  @return 是否开始获取, YES是, NO否
 */
- (BOOL)wchatGetFile:(NSString *)fid
          filelength:(UInt64)length
             withTag:(NSInteger)tag
         withTimeout:(NSTimeInterval)timeout
               error:(NSError **)errPtr;

/**
 *  @brief 异步短连请求
 *
 *  @param request      请求地址
 *  @param method       请求方法, 如 @"GET" @"POST"
 *  @param params       请求参数, 如 paramA=aaa&paramB=bbb
 *  @param callbackId   请求id
 *  @param timeout      超时时间
 *  @param fileType     文件类型
 *  @param fileData     文件数据, 如果不发送文件请求则设为空
 *  @param customHeader 自定义请求header
 *  @param errPtr       错误句柄    回调onShortResponse方法
 *
 *  @return 是否操作成功, YES是, NO否
 */
- (BOOL)weimiShortRequest:(NSString *)request
               withMethod:(NSString *)method
               withParams:(NSString *)params
           withCallbackId:(NSInteger)callbackId
                  timeout:(NSTimeInterval)timeout
             withFileType:(NSString *)fileType
             withFileData:(NSData *)fileData
         withCustomHeader:(NSDictionary *)customHeader
                    error:(NSError **)errPtr;
/**
 *  异步短连请求
 *
 *  @param method     POST/GET
 *  @param url        短链接URL
 *  @param params     参数(para1=%@&param2=%d)
 *  @param callbackId 回调ID
 *  @param timeout    超时时间
 *  @param handler    回调结果
 */
- (void)wchatAsyncRequest:(NSString*)method
                      url:(NSString *)url
                   params:(NSString *)params
               callbackId:(NSInteger)callbackId
                  timeout:(NSTimeInterval)timeout
               completion:(void (^)(NSDictionary *json, NSError *error))handler;

#pragma mark - 群组消息屏蔽

/**
 *  @brief 取消屏蔽, 获取指定群组消息
 *
 *  @param groupId  群组id
 */
- (void)syncGroup:(NSString *)groupId;

/**
 *  @brief 进入屏蔽的群, 开始获取此群组消息
 *
 *  @param groupId   群组id
 *  @param messageId 消息id
 */
- (void)syncBlockGroup:(NSString *)groupId
         withMessageId:(NSString *)messageId;

/**
 *  @brief 退出屏蔽的群, 开始屏蔽此群消息
 */
- (void)exitBlockGroup:(NSString *)groupId;

/**
 *  @brief 获取当前进入的群
 *
 *  @return 群ids
 */
- (NSArray *)getEnterGroups;

#pragma mark - 工具方法

/**
 *  @brief 加密数据
 *
 *  @param string 需要加密的字符串
 *
 *  @return 加密后的密文
 */
+ (NSString *)wchatGetAuthString:(NSString *)string;

/**
 *  @brief 解析pb数据
 *
 *  @param PBData pb数据
 *
 *  @return 解析后的数据
 */
+ (NSArray *)PBdecode:(NSData *)PBData;

/**
 *  @brief 获取http request X-WVersion 头字段信息 (必须先初始化实例)
 *
 *  @return 指定格式的头字段信息
 */
- (NSString *)getXWVersion;

/**
 *  @brief 获取当前设备udid
 *
 *  @return 设备唯一标识
 */
+ (NSString *)getUDID;

#pragma mark - 语音相关
/**
 *  @brief 获取wchat的端口
 *
 *  @return 端口号
 */
- (NSInteger)getwchatPort;

/**
 *  @brief 设置mediasdk的端口
 *
 *  @param port 端口号
 */
- (void)setSipMediaPort:(NSInteger)port;

#pragma mark - 多人会话

/**
 *  @brief 请求一个会话房间
 *
 *  @param GroupID 群组id
 *  @param myuid   当前用户uid
 *  @param errPtr  错误句柄
 *
 *  @return 请求是否发送成功, YES是, NO否
 */
- (BOOL)wchatConferenceRequestRoomWithGroupID:(NSString *)GroupID
                                        myuid:(NSString *)myuid
                                        error:(NSError **)errPtr;

/**
 *  @brief 邀请当前群用户加入多人会话房间
 *
 *  @param users   用户ids
 *  @param groupID 群组id
 *  @param roomID  房间id
 *  @param key     房间key
 *  @param errPtr  错误句柄
 *
 *  @return 请求是否发送成功, YES是, NO否
 */
- (BOOL)wchatConferenceInviteUsers:(NSArray *)users
                           groupID:(NSString *)groupID
                            roomID:(NSString *)roomID
                               key:(NSString *)key
                             error:(NSError **)errPtr;

/**
 *  @brief 获取电话会议里当前的成员
 *
 *  @param roomID  房间id
 *  @param groupID 群组id
 *  @param errPtr  错误句柄
 *
 *  @return 请求是否发送成功, YES是, NO否
 */
- (BOOL)wchatConferenceFetchUsersinRoom:(NSString *)roomID
                                groupID:(NSString *)groupID
                                  error:(NSError **)errPtr;

/**
 *  @brief  踢出一个或多个成员
 *
 *  @param users  用户ids
 *  @param roomID 房间id
 *  @param errPtr 错误句柄
 *
 *  @return 请求是否发送成功, YES是, NO否
 */
- (BOOL)wchatConferenceKickUsers:(NSArray *)users
                          roomID:(NSString *)roomID
                           error:(NSError **)errPtr;

/**
 *	@brief	禁言一个或多个成员
 *
 *  @param users  用户ids
 *  @param roomID 房间id
 *  @param errPtr 错误句柄
 *
 *  @return 请求是否发送成功, YES是, NO否
 */
- (BOOL)wchatConferenceMuteUsers:(NSArray *)users
                          roomID:(NSString *)roomID
                           error:(NSError **)errPtr;

/**
 *	@brief	解禁一个或多个成员
 *
 *  @param users  用户ids
 *  @param roomID 房间id
 *  @param errPtr 错误句柄
 *
 *  @return 请求是否发送成功, YES是, NO否
 */
- (BOOL)wchatConferenceUnmuteUsers:(NSArray *)users
                            roomID:(NSString *)roomID
                             error:(NSError **)errPtr;

#pragma mark - Statistics
/**
 *  统计信息
 *
 *  @param userName  用户昵称
 *  @param url       用户头像地址
 *  @param longitude 经度
 *  @param latitude  纬度
 *  @param code      省区号码
 */
- (void)recordEventWithName:(NSString *)userName
                    iconURL:(NSString *)url
                  longitude:(double)longitude
                   latitude:(double)latitude
               provinceCode:(NSString *)code;
/**
 *  统计用户点击push消息启动应用
 *
 *  @param launchOptions 应用启动信息
 */
- (void)didFinishLaunchingWithOptions:(NSDictionary *)launchOptions;
/**
 *  统计app活跃时用户点击push消息
 *
 *  @param notification 点击的push消息
 */
- (void)didReceiveRemoteNotifications:(NSDictionary *)notification;

@end

#pragma mark - SDK代理

@protocol WChatSDKDelegate <NSObject>

#pragma mark - 注册, 认证, 连接, 超时等回调
@required
/**
 *  @brief 认证回调, 必须实现
 *
 *  @param instance 实例
 *  @param userinfo 认证成功, 返回用户信息
 *  @param error    认证失败, 返回错误信息
 */
- (void)onwchatAuth:(WChatSDK *)instance
           userinfo:(NSDictionary *)userinfo
          withError:(NSError *)error;

@optional
/**
 *  @brief 连接成功回调
 *
 *  @param instance 实例
 */
- (void)onConnected:(WChatSDK *)instance;

/**
 *  @brief 连接断开回调
 *
 *  @param instance 实例
 *  @param error    如连接出错断开, 则返回错误消息
 */
- (void)onDisconnect:(WChatSDK *)instance
           withError:(NSError *)error;

/**
 *  @brief 向服务器发送断开连接的消息回调
 *
 *  @param instance 实例
 *  @param error    如果设置失败, 则返回错误信息
 */
- (void)onClose:(WChatSDK *)instance
      withError:(NSError *)error;

/**
 *  @brief 退出登陆回调
 *
 *  @param instance 实例
 *  @param error    如登陆出错, 则返回错误消息
 */
- (void)onLogout:(WChatSDK *)instance
       withError:(NSError *)error;

/**
 *  @brief 超时回调
 *
 *  @param instance 实例
 *  @param tag      消息标示
 *  @param error    如操作超时, 则返回错误消息
 */
- (void)onTimeout:(WChatSDK *)instance
          withTag:(NSInteger)tag
        withError:(NSError *)error;

#pragma mark - 前后台切换
/**
 *  @brief 客户端退到后台, 关闭服务器消息notice下发, 开启推送回调
 *
 *  @param instance 实例
 *  @param error    如果设置失败, 则返回错误信息
 */
- (void)onPreClose:(WChatSDK *)instance
         withError:(NSError *)error;

/**
 *  @brief 客户端回到前台, 开启服务器消息notice下发, 关闭推送
 *
 *  @param instance 实例
 *  @param error    如果设置失败, 则返回错误信息
 */
- (void)onKeepAlive:(WChatSDK *)instance
          withError:(NSError *)error;

#pragma mark - 连接状态

/**
 *  @brief 连接状态回调
 *
 *  @param instance 实例
 *  @param state    连接状态
 */
- (void)onConnectState:(WChatSDK *)instance
                 state:(WChatConnectState)state;

#pragma mark - 发送消息回调
/**
 *  @brief 消息已送达到服务器, 但服务器还未下发相应, sdk预先返回, 随后服务器会下发相应, 以及时间戳.
 *  可理解为发送消息成功, 前端可根据此状态, 预先显示消息发送成功, 后台处理服务器下发.
 *
 *  @param instance 实例
 *  @param tag      消息标示
 */
- (void)onSendPreBack:(WChatSDK *)instance
              withTag:(NSInteger)tag;

/**
 *  @brief 发送文本消息回调
 *
 *  @param instance  实例
 *  @param tag       消息标示
 *  @param time      消息时间
 *  @param messageId 消息id
 *  @param error     如发送出错, 则返回错误消息
 */
- (void)onSendMsg:(WChatSDK *)instance
          withTag:(NSInteger)tag
         withTime:(NSInteger)time
    withMessageId:(NSString *)messageId
        withError:(NSError *)error;

/**
 *  @brief 发送文件回调
 *
 *  @param instance  实例
 *  @param tag       消息标示
 *  @param time      消息时间
 *  @param messageId 消息id
 *  @param error     如发送出错, 则返回错误消息
 */
- (void)onSendFile:(WChatSDK *)instance
           withTag:(NSInteger)tag
          withTime:(NSInteger)time
     withMessageId:(NSString *)messageId
         withError:(NSError *)error;

/**
 *  @brief 转发消息回调
 *
 *  @param instance  实例
 *  @param tag       消息标示
 *  @param time      消息时间
 *  @param messageId 消息id
 *  @param error     如发送出错, 则返回错误消息
 */
- (void)onForward:(WChatSDK *)instance
          withTag:(NSInteger)tag
         withTime:(NSInteger)time
    withMessageId:(NSString *)messageId
        withError:(NSError *)error;


#pragma mark - 接收文本, 语音, 文件, notice, 订阅消息回调
/**
 *  @brief 接收文本消息回调
 *
 *  @param instance   实例
 *  @param messageId  消息id
 *  @param fromUid    发消息人Uid
 *  @param toUid      收消息人Uid
 *  @param type       消息类型
 *  @param timevalue  消息时间
 *  @param content    消息内容
 *  @param extContent 消息扩展内容
 *  @param error      如收消息出错, 则返回错误信息
 */
- (void)onRecvMsg:(WChatSDK *)instance
    withMessageId:(NSString *)messageId
          fromUid:(NSString *)fromUid
            toUid:(NSString *)toUid
         filetype:(YYWChatFileType)type
             time:(NSInteger)timevalue
          content:(NSData *)content
          extBody:(NSData *)extContent
        withError:(NSError *)error;

/**
 *  @brief 接收群组文本消息回调
 *
 *  @param instance   实例
 *  @param messageId  消息id
 *  @param gid        群id
 *  @param fromUid    发消息人Uid
 *  @param type       消息类型
 *  @param timevalue  消息时间
 *  @param content    消息内容
 *  @param extContent 消息扩展内容
 *  @param error      如收消息出错, 则返回错误信息
 */
- (void)onRecvGroupMsg:(WChatSDK *)instance
         withMessageId:(NSString *)messageId
           withGroupId:(NSString *)gid
               fromUid:(NSString *)fromUid
              filetype:(YYWChatFileType)type
                  time:(NSInteger)timevalue
               content:(NSData *)content
               extBody:(NSData *)extContent
             withError:(NSError *)error;

/**
 *  @brief 接收聊天室消息回调
 *
 *  @param instance      实例
 *  @param messageId     消息id
 *  @param rid           房间id
 *  @param fromUid       发消息人Uid
 *  @param type          消息类型
 *  @param spanId        语音唯一标识
 *  @param sequenceNo    语音分片编号, 如 1, 2, 3, ... -1, -1 表示结束
 *  @param fileid        文件id
 *  @param thumbnailData 缩略图二进制数据
 *  @param length        文件长度
 *  @param size          分片大小
 *  @param timevalue     消息时间
 *  @param content       消息内容
 *  @param extContent    消息扩展内容
 *  @param error         如收消息出错, 则返回错误信息
 */
- (void)onRecvChatRoomMsg:(WChatSDK *)instance
            withMessageId:(NSString *)messageId
               withRoomId:(NSString *)rid
                  fromUid:(NSString *)fromUid
                 filetype:(YYWChatFileType)type
                   spanId:(NSString *)spanId
               sequenceNo:(NSInteger)sequenceNo
                   fileId:(NSString *)fileid
                thumbnail:(NSData *)thumbnailData
               filelength:(UInt64)length
                pieceSize:(UInt32)size
                     time:(NSInteger)timevalue
                  content:(NSData *)content
                  extBody:(NSData *)extContent
                withError:(NSError *)error;

/**
 *  @brief 接收语音消息回调
 *
 *  @param instance   实例
 *  @param messageId  消息id
 *  @param fromUid    发消息人Uid
 *  @param toUid      收消息人Uid
 *  @param spanId     语音唯一标识
 *  @param sequenceNo 语音分片编号, 如 1, 2, 3, ... -1, -1 表示结束
 *  @param timevalue  消息时间
 *  @param content    消息内容
 *  @param extContent 消息扩展内容
 *  @param error      如收消息出错, 则返回错误信息
 */
- (void)onRecvVoice:(WChatSDK *)instance
      withMessageId:(NSString *)messageId
            fromUid:(NSString *)fromUid
              toUid:(NSString *)toUid
             spanId:(NSString *)spanId
         sequenceNo:(NSInteger)sequenceNo
               time:(NSInteger)timevalue
            content:(NSData *)content
            extBody:(NSData *)extContent
          withError:(NSError *)error;

/**
 *  @brief 接收群组语音消息回调
 *
 *  @param instance   实例
 *  @param messageId  消息id
 *  @param gid        群id
 *  @param fromUid    发消息人Uid
 *  @param spanId     语音唯一标识
 *  @param sequenceNo 语音分片编号, 如 1, 2, 3, ... -1, -1 表示结束
 *  @param timevalue  消息时间
 *  @param content    消息内容
 *  @param extContent 消息扩展内容
 *  @param error      如收消息出错, 则返回错误信息
 */
- (void)onRecvGroupVoice:(WChatSDK *)instance
           withMessageId:(NSString *)messageId
             withGroupId:(NSString *)gid
                 fromUid:(NSString *)fromUid
                  spanId:(NSString *)spanId
              sequenceNo:(NSInteger)sequenceNo
                    time:(NSInteger)timevalue
                 content:(NSData *)content
                 extBody:(NSData *)extContent
               withError:(NSError *)error;

/**
 *  @brief 接收文件消息回调
 *
 *  @param instance      实例
 *  @param messageId     消息id
 *  @param fromUid       发消息人Uid
 *  @param toUid         收消息人Uid
 *  @param type          消息类型
 *  @param timevalue     消息时间
 *  @param fileid        文件id
 *  @param thumbnailData 缩略图二进制数据
 *  @param extContent    消息扩展内容
 *  @param length        文件长度
 *  @param size          文件分片大小
 *  @param error         如收文件出错, 则返回错误信息
 */
- (void)onRecvFile:(WChatSDK *)instance
     withMessageId:(NSString *)messageId
           fromUid:(NSString *)fromUid
             toUid:(NSString *)toUid
          filetype:(YYWChatFileType)type
              time:(NSInteger)timevalue
            fileId:(NSString *)fileid
         thumbnail:(NSData *)thumbnailData
           extBody:(NSData *)extContent
        filelength:(UInt64)length
         pieceSize:(UInt32)size
         withError:(NSError *)error;

/**
 *  @brief 接收群组文件消息回调
 *
 *  @param instance      实例
 *  @param messageId     消息id
 *  @param gid           群id
 *  @param fromUid       发消息人Uid
 *  @param type          消息类型
 *  @param timevalue     消息时间
 *  @param fileid        文件id
 *  @param thumbnailData 缩略图二进制数据
 *  @param extContent    消息扩展内容
 *  @param length        文件长度
 *  @param size          文件分片大小
 *  @param error         如收文件出错, 则返回错误信息
 */
- (void)onRecvGroupFile:(WChatSDK *)instance
          withMessageId:(NSString *)messageId
            withGroupId:(NSString *)gid
                fromUid:(NSString *)fromUid
               filetype:(YYWChatFileType)type
                   time:(NSInteger)timevalue
                 fileId:(NSString *)fileid
              thumbnail:(NSData *)thumbnailData
                extBody:(NSData *)extContent
             filelength:(UInt64)length
              pieceSize:(UInt32)size
              withError:(NSError *)error;

/**
 *  @brief 系统下发的notice消息, 踢人回调
 *
 *  @param instance 实例
 *  @param fuid     发消息人Uid
 *  @param type     Notice类型
 *  @param content  消息内容
 */
- (void)onRecvNoticeMessage:(WChatSDK *)instance
                    fromUid:(NSString *)fuid
                   withType:(WChatNoticeType)type
                withContent:(NSString *)content;

/**
 *  @brief 订阅消息回调
 *
 *  @param instance      实例
 *  @param messageId     消息id
 *  @param fromUid       发消息人Uid
 *  @param toUid         收消息人Uid
 *  @param type          消息类型
 *  @param spanId        语音唯一标识
 *  @param sequenceNo    语音分片编号, 如 1, 2, 3, ... -1, -1 表示结束
 *  @param fileid        文件id
 *  @param thumbnailData 缩略图二进制数据
 *  @param length        文件长度
 *  @param size          分片大小
 *  @param timevalue     消息时间
 *  @param content       消息内容
 *  @param extContent    消息扩展内容
 *  @param error         如收消息出错, 则返回错误信息
 */
- (void)onRecvSubscribeMsg:(WChatSDK *)instance
             withMessageId:(NSString *)messageId
                   fromUid:(NSString *)fromUid
                     toUid:(NSString *)toUid
                  filetype:(YYWChatFileType)type
                    spanId:(NSString *)spanId
                sequenceNo:(NSInteger)sequenceNo
                    fileId:(NSString *)fileid
                 thumbnail:(NSData *)thumbnailData
                filelength:(UInt64)length
                 pieceSize:(UInt32)size
                      time:(NSInteger)timevalue
                   content:(NSData *)content
                   extBody:(NSData *)extContent
                 withError:(NSError *)error;

#pragma mark - 获取文件 & 文件进度
/**
 *  @brief 获取文件数据回调
 *
 *  @param instance 实例
 *  @param fileid   文件id
 *  @param tag      消息标示
 *  @param error    如获取文件出错, 则返回错误信息
 */
- (void)onGetFile:(WChatSDK *)instance
           fileId:(NSString *)fileid
          withTag:(NSInteger)tag
        withError:(NSError *)error;

/**
 *  @brief 发送和接收文件进度的回调
 *
 *  @param instance 实例
 *  @param tag      消息标示
 *  @param index    文件分片索引
 *  @param limit    文件分片总数
 *  @param error    如获取进度出错, 则返回错误信息
 */
- (void)onFileProgress:(WChatSDK *)instance
               withTag:(NSInteger)tag
             withIndex:(UInt32)index
             withLimit:(UInt32)limit
             withError:(NSError *)error;

#pragma mark - 获取个人 & 群组消息未读数

/**
 *  @brief 获取消息未读数
 *
 *  @param user  用户消息未读数, 字典格式 @{ @"用户id": @{ @"num": NSNumber 未读数, @"time": NSNumber 消息时间 }, @"用户id": @{ @"num": NSNumber 未读数, @"time": NSNumber 消息时间 } }
 *  @param group 群组消息未读数, 字典格式 @{ @"群组id": @{ @"num": NSNumber 未读数, @"time": NSNumber 消息时间 }, @"群组id": @{ @"num": NSNumber 未读数, @"time": NSNumber 消息时间 } }
 */
- (void)onRecvUnreadNumber:(WChatSDK *)instance
                  withUser:(NSDictionary *)user
                 withGroup:(NSDictionary *)group;

/**
 *  @brief 获取屏蔽群组消息未读数
 *
 *  @param group 群组消息未读数, 字典格式 @{ @"群组id": @{ @"num": NSNumber 未读数, @"time": NSNumber 消息时间 }, @"群组id": @{ @"num": NSNumber 未读数, @"time": NSNumber 消息时间 } }
 */
- (void)onRecvUnreadNumber:(WChatSDK *)instance
            withBlockGroup:(NSDictionary *)group;

#pragma mark - 系统服务
/**
 *  @brief 发送微博消息回调
 *
 *  @param instance 实例
 *  @param tag      消息标示
 *  @param content  消息内容
 *  @param error    如收消息出错, 则返回错误信息
 */
- (void)onAppService:(WChatSDK *)instance
             withTag:(NSInteger)tag
         withContent:(NSData *)content
           withError:(NSError *)error;

#pragma mark - http链接请求回调
/**
 *  @brief http链接请求回调
 *
 *  @param instance   实例
 *  @param response   返回消息
 *  @param callbackId 回调id
 *  @param error      如收消息出错, 则返回错误信息
 */
- (void)onShortResponse:(WChatSDK *)instance
           withResponse:(NSString *)response
         withCallbackId:(NSInteger)callbackId
              withError:(NSError *)error;

/**
 *  @brief 短链发送文件进度
 *
 *  @param progress   进度 0~1
 *  @param callbackId 回调id
 */
- (void)onShortProgress:(float)progress
         withCallbackId:(NSInteger)callbackId;

#pragma mark - 多人会话
/**
 * Called when receive conference 电话会议 房间 的 创建 和邀请 message
 **/
- (void)onReceiveConfeneceCallback:(WChatSDK *)instance
                              type:(cfcallbackType)type
                          fromUser:(NSString *)fromUid
                           groupID:(NSString *)groupID
                            roomID:(NSString *)roomID
                               key:(NSString *)key
                             users:(NSArray *)users
                         startTime:(NSString *)startTime
                           endTime:(NSString *)endTime
                             error:(NSError *)error;

/**
 * Called when conference 电话会议 有人加入
 **/
- (void)conferenceJoinedWith:(NSString *)roomID
                     groupID:(NSString *)groupID
                       users:(NSArray *)users;

/**
 * Called when conference 电话会议 有人被禁言
 **/
- (void)conferenceMutedWith:(NSString *)roomID
                    groupID:(NSString *)groupID
                    fromUid:(NSString *)fromUid
                      users:(NSArray *)users;

/**
 * Called when conference 电话会议 有人被解禁
 **/
- (void)conferenceUnmutedWith:(NSString *)roomID
                      groupID:(NSString *)groupID
                      fromUid:(NSString *)fromUid
                        users:(NSArray *)users;

/**
 * Called when conference 电话会议 有人被踢
 **/
- (void)conferenceKickedWith:(NSString *)roomID
                     groupID:(NSString *)groupID
                     fromUid:(NSString *)fromUid
                       users:(NSArray *)users;

/**
 * Called when conference 电话会议 有人离开
 **/
- (void)conferenceLeftWith:(NSString *)roomID
                   groupID:(NSString *)groupID
                     users:(NSArray *)users;

/**
 * Called when conference 电话会议 即将关闭的通知提示
 **/
- (void)conferenceWillbeEndWith:(NSString *)roomID
                        groupID:(NSString *)groupID
                         intime:(NSInteger )second;

/**
 * Called when conference 电话会议 验证失败 房间已经过期
 **/
- (void)conferenceExpiredWithRoomID:(NSString *)roomID
                                key:(NSString *)key;

/**
 * 未接到的来电
 **/
- (void)missCallFromUser:(NSString *)fromUid
                  atTime:(NSInteger)time;

/**
 * Called when live 直播 主播离开
 * dic 中分别用 key：uid 和 roomid 来取主播的uid和直播间的id
 **/
-(void)liveHostLeaveWithUidRoomidDic:(NSDictionary *)dic;

#pragma mark - 客户端未使用到的方法 (需要客户端确认后删除)
/**
 * Called when server push the contact address matching result
 *
 **/
- (void)onContactAddress:(WChatSDK *)instance
             withContent:(NSData *)content
               withError:(NSError *)error;

/**
 * Called when create, add, quit group with or without error
 *
 **/
- (void)onCreateGroup:(WChatSDK *)instance
          withContent:(NSData *)content
              withTag:(NSInteger)tag
            withError:(NSError *)error;

/**
 * Called when manage(create, add, quit) group with or without error
 *
 **/
- (void)onManageGroup:(WChatSDK *)instance
          withContent:(NSData *)content
              withTag:(NSInteger)tag
            withError:(NSError *)error;

/**
 * Called when get group members
 *
 **/
- (void)onGetGroupMembers:(WChatSDK *)instance
              withGroupId:(NSString *)gid
                  withUid:(NSString *)uid
                withError:(NSError *)error;

/**
 * Called when group operation
 *
 **/
- (void)onGroupOperation:(WChatSDK *)instance
             withGroupId:(NSString *)gid
                 withUid:(NSString *)uid
                    type:(WChatGroupOperationType)type
                  extend:(NSString *)extend
               withError:(NSError *)error;

/**
 * Called when noticeing message coming
 *
 **/
- (void)onPushNotice:(WChatSDK *)instance
         withContent:(NSData *) content
           withError:(NSError *)error;

/**
 * Called when system notice with or withour error
 *
 **/
- (void)onSystemNotice:(WChatSDK *)instance
               fromUid:(NSString *)fromUid
                 toUid:(NSString *)toUid
              filetype:(YYWChatFileType)type
                  time:(NSInteger)timevalue
               content:(NSData *)content
               extBody:(NSData *)extContent
             withError:(NSError *)error;

/**
 * Called when receive unreadNotice message
 **/
- (void)onUnreadNoticeCallback:(WChatSDK *)instance
                withCallbackId:(NSInteger)callbackId;


@end

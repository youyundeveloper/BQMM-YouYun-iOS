在您阅读此文档之前，我们假定您已经具备了基础的 iOS 应用开发经验。
# WChatSDK 快速集成
在使用`WChatSDK`之前请，请前往 [官方网站](http://17youyun.com) 注册开发者帐号。注册时，您需要提供真实的邮箱和手机号，以方便我们向您发送重要通知并在紧急时刻能够联系到您。如果您没有提供正确可用的邮箱和手机号，我们随时可能关闭您的应用。
## 1. 创建应用
注册了开发者账号之后，在进行开发 App 之前，您需要请前往 开发者控制台 创建应用。您创建完应用之后，在您的应用中，会自动创建两套的环境，即：开发环境和生产环境。创建应用成功后会生成对应开发环境的App唯一的`ClientID`和`Secret`。
下载的`WChatSDK`包涵以下必要文件：

 ```
    include/WChatCommon.h
	include/WChatSDK.h
	include/WChatSDK+ServiceRequest.h
	include/public.der
	libWChatSDK.a
	README.md
 ```
### 1. 工程准备
您在尝试集成 SDK 的时候，为了方便，可以新建一个工程。将下载的SDK导入工程，安装以下依赖库（如果已经导入请忽略）：

- libsqlite3.tbd
- Security.framework
- CFNetwork.framework
- CoreTelephony.framework
- SystemConfiguration.framework
- Foundation.framework
- UIKit.framework

如果您使用的是 Xcode 6.X 版本，则需要将上面的动态库 *.tbd 的后缀改为 *.dylib。

选中工程，在Build Settings中搜素Other Linker Flags，增加 `-ObjC` 链接选项。

iOS 9 中，Apple 引入了新特性 App Transport Security (ATS)，默认要求 App 必须使用 https 协议。详情：[What's New in iOS 9](https://developer.apple.com/library/prerelease/ios/releasenotes/General/WhatsNewIniOS/Articles/iOS9.html#//apple_ref/doc/uid/TP40016198-DontLinkElementID_13)。

SDK 在 iOS9 上需要使用 http，您需要设置在 App 中使用 http。在 App 的 *Info.plist 中添加 NSAppTransportSecurity 类型Dictionary。
在 NSAppTransportSecurity 下添加 NSAllowsArbitraryLoads 类型 Boolean，值设为 YES。

## 接口介绍

初始化sdk单例`[WChatSDK sharedInstance]`，通过该单例进行接口调用.

释放单例`[WChatSDK purgeSharedInstance]` 

## 单例调用

#### 1.初始化SDK

```objective-c
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
```

#### 2.线上／测试平台授权登录

```objective-c
1. 线上平台授权登陆
/**
 *  @brief 注册设备
 *
 *  @param appUDID        设备唯一UDID
 *  @param clientId       开放平台下发的clientID
 *  @param secret         开放平台下发的sectet
 *  @param clientDelegate 回调代理
 */
-(void)registerApp:(NSString *)appUDID
          clientId:(NSString *)clientId
            secret:(NSString *)secret
          delegate:(id<WChatSDKDelegate>)clientDelegate;
           
2. 线下平台授权登陆
/**
 *  @brief 测试平台, 注册设备
 *
 *  @param appUDID        设备唯一UDID
 *  @param clientId       开放平台下发的clientID
 *  @param secret         开放平台下发的sectet
 *  @param clientDelegate 回调代理
 */
-(void)testRegisterApp:(NSString *)appUDID
              clientId:(NSString *)clientId
                secret:(NSString *)secret
              delegate:(id<WChatSDKDelegate>)clientDelegate;
```

#### 3.登录、退出、密码设置
```objective-c
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
```

#### 4.前后台切换, 关闭连接, 重连

```objective-c
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
```

#### 5.发送单聊、群聊、聊天室文本消息接口

```objective-c
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
```


#### 6.发送单聊、群聊、聊天室语音消息接口

```objective-c
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
```

#### 7.发送单聊、群聊、聊天室文件消息接口

```objective-c
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
```

#### 8.发送单聊、群聊、聊天室图片消息接口

```objective-c
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
```

#### 9.设置消息未读数量

```objective-c
/**
 *  @brief 设置消息未读数
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
 *  @param number 减掉的消息未读数
 *  @param tag    消息标示, 用于回调
 *  @param errPtr 错误句柄
 *
 *  @return 是否发送设置, YES是, NO否
 */
- (BOOL)wchatMinusUnreadNumber:(NSInteger)number
                       withTag:(NSInteger)tag
                         error:(NSError **)errPtr;
```


#### 10.获取文件

```objective-c
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
```

#### 11.工具辅助方法

```objective-c
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
```

#### 12.多人会议(conference)接口

```objective-c
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
```

#### 13. 数据统计

SDK需要开发者调用一些接口来完善数据统计，如果开发者不需要游云平台的数据统计、可以忽略此功能。

```objective-c
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
```



#SDK代理回调

#### @required

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

#### @optional

#### 1.连接状态回调
	/**
	 *  @brief 连接成功回调
	 *
	 *  @param instance 实例
	 */
	- (void)onConnected: (WChatSDK *)instance;
	
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
	        
	/**
	 *  @brief 连接状态回调
	 *
	 *  @param instance 实例
	 *  @param state    连接状态
	 */
	- (void)onConnectState:(WChatSDK *)instance
	                 state:(WChatConnectState)state;

#### 2.前后台切换

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


#### 2.发送消息回调

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

#### 3.未读数设置回调

    /**
     *  未读数设置回调
     *
     *  @param instance   实例
     *  @param callbackId 消息标示
     */
    -(void)onUnreadNoticeCallback:(WChatSDK*)instance withCallbackId:(NSInteger)callbackId;
    
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

#### 4.接收文本, 语音, 文件, notice, 订阅消息回调

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

#### 5.接收语音

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


#### 6.接收文件、图片

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

#### 7.接收notice、订阅

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

#### 8.接收聊天室消息

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

#### 9.获取文件 & 文件进度

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

#### 10.多人会话

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

# 群组业务接口

#### 1.群组 - 管理相关接口

    /**
     *  创建群组
     *
     *  @param handler 回调block (创建成功的群组id, 如果错误则返回错误信息)
     */
    -(void)createGroupWithCompletionHandler:(void(^)(NSString *groupId, NSError* requestError))handler;
    
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
     *  获取群组成员
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

#### 2.黑名单相关接口

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

#### 3.消息相关接口

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

#### 4.服务相关接口

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


# 聊天室业务接口

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
	 *  @param alias   别名(接入方的用户ID，用来和游云ID做映射)
	 *  @param handler 回调block (是否操作成功, 如果错误则返回错误信息)
	 */
	- (void)chatRoomEnter:(NSString *)roomid
	              aliasid:(NSString *)alias
	           completion:(void(^)(BOOL isEnter, NSError *err))handler;


	/**
	 *  退出聊天室房间
	 *
	 *  @param roomid  聊天室房间ID
	 *  @param alias   别名(接入方的用户ID，用来和游云ID做映射)
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
	 *  @param isForbid  1：禁言，0：解禁言
	 *  @param handler   回调结果
	 */
	- (void)chatRoomForbidUser:(NSArray *)uids
	                    roomid:(NSString *)roomid
	                    forbid:(int)isForbid
	                completion:(void (^)(BOOL success, NSError *err))handler;
	                
	/**
	 *  聊天室聊天历史消息
	 *
	 *  @param roomid    群组id
	 *  @param timestamp 时间戳(精确到秒,如果传-1，获取最新消息)
	 *  @param size      数据条数(服务器默认一次最多取20)
	 *  @param handler   回调block (历史消息数据, 如果错误则返回错误信息)
	 *					  结果倒叙(新消息arr[0],就消息arr[1])
	 */
	-(void)chatRoomGetHistory:(NSString *)roomid
	                timestamp:(NSInteger)timestamp
	                     size:(NSInteger)size
	        completionHandler:(void (^)(NSArray *response, NSError *err))handler;

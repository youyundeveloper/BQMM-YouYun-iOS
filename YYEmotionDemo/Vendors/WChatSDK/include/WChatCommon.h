//
//  WChatCommon.h
//  WChat
//
//  Created by gaozhi,yongrong on 9/6/12.
//
//

#ifndef WChat_WChatCommon_h
#define WChat_WChatCommon_h

#define WChatErrorDomain @"WChatErrorDomain"

//sdk版本
#define WChatVersion @"1.0.3.0"


/**
 平台切换宏
 
 - OnlinePlatform: 线上平台
 - TestPlatform:   测试平台
 */
typedef NS_ENUM(NSInteger, WChatPlatform) {
    OnlinePlatform  = 1,
    TestPlatform    = 2,
};


/**
 错误类型
 
 - WChatNoError:            no error
 - WChatBadParamError:      bad param error
 - WChatAuthError:          auth error
 - WChatNotRunningError:    not running error
 - WChatAlreadyLoginError:  already login in another device
 - WChatForceUpgradeError:  force upgrade client
 - WChatTokenExpiredError:  weibo token Expired
 
 - WChatFileNotExistError:  file not exist error
 - WChatFileTooLargeError:  file too large error: thumbnail is not more than 50K
 - WChatGetFileError:       get file error
 - WChatNotDirectoryError:  not directory error
 - WChatFileOpenError:      open file error
 
 - WChatDisconnectError:    disconnect error
 - WChatTimeoutError:       timedout error
 - WChatReadTimeoutError:   read timedout error
 - WChatWriteTimeoutError:  write timedout error
 - WChatSocketConnectError: socket connect error
 
 - WChatRegisterError:      请求注册失败
 
 */
typedef NS_ENUM(NSInteger, YYWChatError)
{
    WChatNoError               = 0,
    
    WChatBadParamError         = 11,
    WChatAuthError             = 12,
    WChatNotRunningError       = 13,
    WChatAlreadyLoginError     = 14,
    WChatForceUpgradeError     = 15,
    WChatTokenExpiredError     = 16,
    
    // file and directory
    WChatFileNotExistError     = 21,
    WChatFileTooLargeError     = 22,
    WChatGetFileError          = 23,
    WChatNotDirectoryError     = 24,
    WChatFileOpenError         = 25,
    
    // network
    WChatDisconnectError       = 31,
    WChatTimeoutError          = 32,
    WChatReadTimeoutError      = 33,
    WChatWriteTimeoutError     = 34,
    WChatSocketConnectError    = 35,
    
    //opensdk
    WChatRegisterError         = 41,
    
};

/**
 消息类型
 
 - YYWChatFileTypeText:       文本
 - YYWChatFileTypeVoice:      语音, 没有文件id
 - YYWChatFileTypeVideo:      视频
 - YYWChatFileTypeImage:      图片
 - YYWChatFileTypeFile:       文件
 
 - YYWChatFileTypeOperation:
 - YYWChatFileTypeLocation:   位置
 - YYWChatFileTypeProperty:   to be deleted
 
 - YYWChatFileTypeTextExt:    SDK文本扩展使用
 - YYWChatFileTypeCustom:     自定义消息
 - YYWChatFileTypeEmotion:    表情
 
 - YYWChatFileTypeHtml:
 - YYWChatFileTypeMixed:      JSON
 - YYWChatFileTypeAudio:      音频文件消息 有文件id
 
 - YYWChatFileTypeSip:        voip 单人电话
 - YYWChatFileTypeConference: 电话会议
 
 - YYWChatFileTypeUnknown:    未知操作
 */
typedef NS_ENUM(NSInteger, YYWChatFileType)
{
    YYWChatFileTypeText      = 0x01,
    YYWChatFileTypeVoice     = 0x02,
    YYWChatFileTypeVideo     = 0x03,
    YYWChatFileTypeImage     = 0x04,
    YYWChatFileTypeFile      = 0x05,
    
    YYWChatFileTypeOperation = 0x07,
    YYWChatFileTypeLocation  = 0x08,
    YYWChatFileTypeProperty  = 0x09,
    
    YYWChatFileTypeTextExt   = 0x0a,
    YYWChatFileTypeCustom    = 0x0b,
    YYWChatFileTypeEmotion   = 0x0c,
    
    YYWChatFileTypeHtml      = 0x10,
    YYWChatFileTypeMixed     = 0x11,
    
    YYWChatFileTypeAudio     = 0x12,
    
    YYWChatFileTypeSip       = 0x13,
    YYWChatFileTypeConference= 0x14,
    
    YYWChatFileTypeUnknown   = 0x0,
    
};
/**
 *  消息发送对象类型
 */
typedef NS_ENUM(NSInteger, WChatMsgTargetType) {
    WChatMsgTargetTypeServer        = 0,
    /**
     *  个人
     */
    WChatMsgTargetTypeSingle        = 1,
    /**
     *  群组
     */
    WChatMsgTargetTypeGroup         = 2,
    /**
     *  聊天室
     */
    WChatMsgTargetTypeChatRoom      = 3,
    
};

/**
 *  创建群组类型
 */
typedef NS_ENUM(NSInteger, WChatGroupCategary) {
    /**
     *  临时群组
     */
    WChatGroupCategaryTmp,
    /**
     *  私人群组
     */
    WChatGroupCategaryPersonal,
    /**
     *  公共群租
     */
    WChatGroupCategaryPublic,
    /**
     *  聊天室
     */
    WChatGroupCategaryChatRoom,
    
};

/**
 群组成员角色类型，默认是普通成员
 
 - YYGroupUserRoleTypeDefault:
 - YYGroupUserRoleTypeNormal: 普通成员
 - YYGroupUserRoleTypeVIP:    VIP成员
 - YYGroupUserRoleTypeAdmin:  管理员
 - YYGroupUserRoleTypeRoot:   房主
 */
typedef NS_ENUM(NSInteger, YYGroupUserRoleType) {
    YYGroupUserRoleTypeDefault      = 0,
    YYGroupUserRoleTypeNormal       = 1,
    YYGroupUserRoleTypeVIP,
    YYGroupUserRoleTypeAdmin,
    YYGroupUserRoleTypeRoot,
    
};

/**
 * 搜索群组返回群组信息类型
 */
typedef NS_ENUM(NSInteger, YYGroupShowType) {
    /**
     * 返回名称，头像
     */
    YYGroupShowTypeName         = 1,
    /**
     * 返回基本信息
     */
    YYGroupShowTypeBasicInfo,
    /**
     * 返回基本信息+成员数+最近4个成员
     */
    YYGroupShowTypeNameAndBasic,
};

/**
 设置群组扩展信息的提醒类型
 
 - YYGroupMsgRemindTypeRemind: 群消息(IM+Push)
 - YYGroupMsgRemindTypeNoPUsh: 群消息IM
 - YYGroupMsgRemindTypeIgnore: 不下发IM+Push
 */
typedef NS_ENUM(NSInteger, YYGroupMsgRemindType) {
    YYGroupMsgRemindTypeRemind  = 1,
    YYGroupMsgRemindTypeNoPUsh,
    YYGroupMsgRemindTypeIgnore,
    
};

/**
 加入群的成员审核方式
 
 - YYGroupApproveTypeUser:  用户审核
 - YYGroupApproveTypeEmail: email审核
 */
typedef NS_ENUM(NSInteger, YYGroupApproveType) {
    YYGroupApproveTypeUser          = 1,
    YYGroupApproveTypeEmail,
};

/**
 小组操作类型
 
 - AddMember:    添加组员
 - RemoveMember: 移除组员
 - QuitGroup:    推出小组
 */
typedef NS_ENUM(NSInteger, WChatGroupOperationType) {
    AddMember       = 0x01,
    RemoveMember    = 0x02,
    QuitGroup       = 0x03,
    
};//管理小组

/**
 连接状态类型
 
 - Disconnected: 未连接 (默认)
 - Connected:    已连接
 - Receiving:    正在获取消息
 - Connecting:   连接中
 - SystemConfig: 系统设置(服务器返回,需要客户端处理,如多设备登陆,强制升级)
 - UnReconnect:  不再重连
 */
typedef NS_ENUM(NSInteger, WChatConnectState) {
    Disconnected    = 1,
    Connected       = 2,
    Receiving       = 3,
    Connecting      = 4,
    SystemConfig    = 5,
    UnReconnect     = 6,
    
};//连接状态

/**
 握手消息返回状态
 
 - AlreadyLogin: 已经在其他设备登陆
 - ForceUpgrade: 强制升级
 */
typedef NS_ENUM(NSInteger, WChatHandShakeCode) {
    AlreadyLogin        = 600,
    ForceUpgrade        = 601,
    
};//握手状态

/**
 notice消息类型
 
 - Typeing:          正在输入
 - KickOff:          踢人
 - ResetRemind:      重置提醒
 - SetUnread:        设置未读数
 - DecrUnread:       减掉未读数
 - KickWeb:          踢web客户端
 - SyncSingleStatus: 同步个人消息未读状态
 - SyncGroupStatus:  同步群消息未读状态
 */
typedef NS_ENUM(NSInteger, WChatNoticeType) {
    Typeing         = 1,
    KickOff         = 2,
    ResetRemind     = 100,
    SetUnread       = 200,
    DecrUnread      = 300,
    KickWeb         = 1000,
    SyncSingleStatus= 1001,
    SyncGroupStatus = 1002,
    
};//notice类型

/**
 电话会议 calback 类型
 
 - cfcallbackTypeNone:        不是任何请求类型 用于默认设置
 - cfcallbackTypeRoomRequest: 请求房间
 - cfcallbackTypeSendInvite:  发送邀请
 - cfcallbackReceiveInvite:   收到他人的电话会议邀请
 - cfcallbackTypeKick:        踢人
 - cfcallbackTypeMute:        禁言
 - cfcallbackTypeUnmute:      解禁
 - cfcallbackTypeFetch:       获取加入电话会议的成员
 - cfcallbackTypeState:       收到的是状态通知
 */
typedef NS_ENUM(NSInteger, cfcallbackType) {
    cfcallbackTypeNone              = 0,
    cfcallbackTypeRoomRequest       = 1,
    cfcallbackTypeSendInvite        = 2,
    cfcallbackReceiveInvite         = 3,
    cfcallbackTypeKick              = 4,
    cfcallbackTypeMute              = 5,
    cfcallbackTypeUnmute            = 6,
    cfcallbackTypeFetch             = 7,
    cfcallbackTypeState             = 8,
};

/**
 电话会议 状态变化通知 类型
 
 - cfstateTypeNone:    没有状态变化 用于默认设置
 - cfstateTypeJoin:    有人加入
 - cfstateTypeMute:    有人被禁言
 - cfstateTypeUnmute:  有人被解禁
 - cfstateTypeKick:    有人被踢
 - cfstateTypeLeft:    有人离开
 - cfstateTypeWillEnd: 将要结束的通知
 */
typedef NS_ENUM(NSInteger, cfstateType) {
    cfstateTypeNone       = 0,
    cfstateTypeJoin       = 1,
    cfstateTypeMute       = 2,
    cfstateTypeUnmute     = 3,
    cfstateTypeKick       = 4,
    cfstateTypeLeft       = 5,
    cfstateTypeWillEnd    = 6,
};
#endif

//
//  MMMessage.h
//  IMDemo
//
//  Created by isan on 16/4/21.
//  Copyright © 2016年 siyanhui. All rights reserved.
//

#import <Foundation/Foundation.h>

#define TEXT_MESG_TYPE @"txt_msgType"  //key for text message
#define TEXT_MESG_FACE_TYPE @"facetype" //key for big emoji type
#define TEXT_MESG_EMOJI_TYPE @"emojitype" //key for photo-text message
#define TEXT_MESG_DATA @"msg_data"  //key for ext data of message

#define kMessageCategary    @"categary"
#define kMessageContent     @"content"

typedef NS_ENUM(NSUInteger, MMMessageType) {
    /*!
     Text message or photo-text message
     */
    MMMessageTypeText = 0,
    
    /*!
     big emoji message
     */
    MMMessageTypeBigEmoji = 1,
    /**
     *  Emotion and text
     */
    MMMessageTypeMix = 2,
    
};

typedef NS_ENUM(NSInteger, MMMessageCategary) {
    MMMessageCategarySend,
    MMMessageCategaryReceive,
};

@interface ChatMessage : NSObject

@property(nonatomic, assign) MMMessageType messageType;

@property (nonatomic, assign) MMMessageCategary messageCategary;

/**
 *  text content of message
 */
@property(nonatomic, strong) NSString *messageContent;
/**
 *  the ext of message
 */
@property(nonatomic, strong) NSDictionary *messageExtraInfo;


/**
 *  initialize message Model
 *
 *  @param messageType      the type of message
 *  @param messageContent   the text content of mesage
 *  @param messageExtraInfo the ext of message
 *
 *  @return message Model
 */
- (id)initWithMessageType:(MMMessageType)messageType messageContent:(NSString *)messageContent messageExtraInfo:(NSDictionary *)messageExtraInfo;


@end
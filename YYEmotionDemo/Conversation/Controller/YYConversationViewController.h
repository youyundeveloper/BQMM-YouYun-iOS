//
//  YYConversationViewController.h
//  YYEmotionDemo
//
//  Created by Frederic on 16/9/8.
//  Copyright © 2016年 17YouYun. All rights reserved.
//

#import "YYBaseTableViewController.h"

#import "MMInputToolBarView.h"
#import "MMChatViewBaseCell.h"

#import "ChatMessage.h"


@interface YYConversationViewController : YYBaseTableViewController<RCMessageCellDelegate, MMInputToolBarViewDelegate>

@property (nonatomic, copy) NSString *targetUserID;

@property(strong, nonatomic) MMInputToolBarView *inputToolBar;

@end

//
//  YYBaseViewController.h
//  YYEmotionDemo
//
//  Created by Frederic on 16/9/8.
//  Copyright © 2016年 17YouYun. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface YYBaseViewController : UIViewController


#pragma mark - HUD

- (BOOL)hudIsVisible;

- (void)showHUD;

- (void)showHUDWithStatus:(NSString *)status;

- (void)showHUDProgress:(float)progress status:(NSString*)status;

- (void)showHUDInfoWithStatus:(NSString*)status;

- (void)showHUDSuccessWithStatus:(NSString*)status;

- (void)showHUDErrorWithStatus:(NSString*)status;

- (void)dismissHUD;

- (void)dismissHUDWithDelay:(NSTimeInterval)delay;



@end
